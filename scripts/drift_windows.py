"""Bound where bytes go missing or extra, from branch displacements alone.

SUPERSEDED by `rebrew drift` (upstream 97c5777), which fixes three bugs in this
script: it filtered branch operands on a "0x" prefix, but capstone renders small
targets as bare decimal, so every window in a function under 0x10 bytes was
silently dropped; it truncated the window list to six BEFORE deriving regions,
so derivations were computed from incomplete data; and it subtracted the
NARROWEST containing window, which gives a true remainder about a less useful
region than the widest does.  Prefer:

    rebrew drift --va <va> --json <source.c>

Kept for provenance -- docs/msvc6-c-shapes.md sections 123, 138 and 145 quote
its output.

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
    spans = []
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
        spans.append((lo, hi, signed))

    # Nested subtraction.  A window strictly inside another accounts for part of
    # the outer window's drift, so the REMAINDER is attributable to the region
    # the inner one does not cover -- and that remainder can have the opposite
    # sign.  This is the only way to see a surplus the tool cannot report
    # directly: on guild-rebrew's CrashDump every measured window was negative
    # while the object was size-exact, and subtracting a -19 inner window from
    # its -10 outer one exposed a ~+9 region with no positive window of its own
    # (docs/msvc6-c-shapes.md section 137).
    derived = []
    for lo1, hi1, d1 in spans:
        for lo2, hi2, d2 in spans:
            if (lo1, hi1) == (lo2, hi2):
                continue
            if lo1 <= lo2 and hi2 <= hi1 and (hi2 - lo2) < (hi1 - lo1):
                rest = d1 - d2
                if rest:
                    derived.append((lo1, hi1, lo2, hi2, rest, d1, d2))
    if derived:
        # Report the tightest containing pair per outer window only.
        best = {}
        for lo1, hi1, lo2, hi2, rest, d1, d2 in derived:
            key = (lo1, hi1)
            if key not in best or (hi2 - lo2) < (best[key][1] - best[key][0]):
                best[key] = (lo2, hi2, rest, d1, d2)
        print('\nderived by subtraction (regions with no window of their own):')
        for (lo1, hi1), (lo2, hi2, rest, d1, d2) in sorted(best.items()):
            print(f'  [{lo1:#x}, {hi1:#x}) {d1:+d} minus inner [{lo2:#x}, {hi2:#x}) '
                  f'{d2:+d}  =>  {rest:+d} outside the inner window')
