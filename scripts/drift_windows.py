"""Bound where bytes go missing or extra, from branch displacements alone.

A jump whose *encoding* matches the reference but whose *target* differs is not
a defect -- it is a measurement.  The difference in targets is exactly the byte
drift accumulated between the jump and its target, so every such pair yields a
window `[jump, target)` with a signed byte count, for free and without
disassembling the window's contents (docs/msvc6-c-shapes.md sections 95, 122).

Nested windows subtract, which is what makes this worth scripting: if
`[0x3a,0x4fa)` drifts -2 and `[0x292,0x3b6)` inside it drifts +2, then the
shortfall lives in `[0x3a,0x292)` or `[0x3b6,0x4fa)` and there is a separate
surplus in the inner window -- two independent faults, localised without
reading a single instruction.

    python3 scripts/drift_windows.py <va> <size> <our.obj>

Build the object with `scripts/probe_function.py --va <va> --file <src>` first;
it leaves the object under `build/objtest/`.
"""
import struct, subprocess, json, sys, glob, os
import capstone

def our_text(objpath, minsize):
    d=open(objpath,'rb').read(); n=struct.unpack_from('<H',d,2)[0]
    best=None
    for k in range(n):
        e=d[20+k*40:20+(k+1)*40]; sz,ptr=struct.unpack_from('<II',e,16)
        if e[:8].rstrip(b'\0').startswith(b'.text') and sz>=minsize:
            if best is None or sz>best[0]: best=(sz,ptr)
    sz,ptr=best
    return bytes(d[ptr:ptr+sz])

def branches(buf):
    md=capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    out={}
    for i in md.disasm(buf,0):
        # calls only ever target an unresolved reloc in our object, so their
        # "targets" are noise; conditional/unconditional jumps are intra-function
        # and are the ones that measure layout.
        if i.mnemonic.startswith('j') and i.op_str.startswith('0x'):
            out[i.address]=(i.size, int(i.op_str,16))
    return out

va=int(sys.argv[1],16); size=int(sys.argv[2]); obj=sys.argv[3]
ref=json.loads(subprocess.run(['rebrew','asm',hex(va),'--size',str(size),'--json'],
    capture_output=True,text=True).stdout)
ins=ref if isinstance(ref,list) else ref.get('instructions',[])
rb=b''.join(bytes.fromhex(x['bytes']) for x in ins if 'bytes' in x)
ob=our_text(obj, min(size-64, 200))
rbr, obr = branches(rb), branches(ob)
common=sorted(set(rbr) & set(obr))
drifts=[]
for a in common:
    rs,rt = rbr[a]; os_,ot = obr[a]
        # a target outside the function is a tail-call/thunk, not a layout signal
    for _ in ():
        pass
    if rs==os_ and rt!=ot and 0 <= rt < len(rb) and 0 <= ot < len(ob):
        drifts.append((a, rt, ot, ot-rt))
if not drifts:
    print('no aligned branch pairs with differing targets')
else:
    print(f'{len(drifts)} aligned branches whose targets differ:')
    for a,rt,ot,d in drifts[:6]:
        # The measured span runs between the jump and its target, in whichever
        # order they fall.  A BACKWARD jump (target < source) measures the drift
        # accumulated in [target, jump) and its sign is inverted relative to a
        # forward one: if our backward target sits 2 bytes earlier than the
        # reference's, the code between target and jump grew by 2, not shrank.
        lo, hi = (a, rt) if rt >= a else (rt, a)
        signed = d if rt >= a else -d
        print(f'  at +{a:#06x}: ref->{rt:#06x} ours->{ot:#06x}  '
              f'drift {signed:+d} bytes in [{lo:#x}, {hi:#x})'
              + ('' if rt >= a else '  (backward)'))
