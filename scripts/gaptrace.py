#!/usr/bin/env python3
"""Where does our function lose (or gain) length relative to the reference?

Aligns the two instruction streams and prints our offset minus the reference's at
the start of each equal block.  The running gap is the instrument for a LENGTH
hypothesis, which neither probe_function nor instr_diff can see: a function whose
real COMDAT body is N bytes short has its out-of-line jump table / case map N bytes
early, moving every 4-byte relocated entry in it, while the object score stays flat.

    scripts/gaptrace.py <va> <size> <source> <comdat-symbol>
"""
import sys, difflib, re, subprocess, capstone
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
import instr_diff as ID
from split_coff import Coff

va = int(sys.argv[1], 0); size = int(sys.argv[2]); src = sys.argv[3]; sym = sys.argv[4]
MD = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32); MD.skipdata = True
secs = ID.sections(ID.REFERENCE)
off = secs[".text"][2] + (va - secs[".text"][0] - ID.IMAGE_BASE)
rbody = ID.REFERENCE.read_bytes()[off:off + size]
rmask = ID.mask(ID.REFERENCE, secs, va, size)
out = subprocess.run([".venv/bin/python", "-u", "scripts/probe_function.py", "--va", hex(va),
                      "--file", src], capture_output=True, text=True).stdout
print(out.strip().splitlines()[0])
obj = Path(re.search(r"object: (\S+)", out).group(1)); c = Coff(obj.read_bytes())
body = None
for si, s in enumerate(c.sections):
    if not s["name"].startswith(b".text"):
        continue
    if next((x["name"] for x in c.symbols if x and x["section"] == si + 1
             and x["storage_class"] == 2), None) == sym:
        body = bytes(c.section_body(si))
        rel = [r for r, _, _ in c.section_relocs(si)]
cm = bytearray(len(body))
for r in rel:
    for k in range(r, min(r + 4, len(body))):
        cm[k] = 1
def dec(b, m):
    o = []
    for x in MD.disasm(b, va):
        i = x.address - va
        bb = bytes(0 if (i + k) < len(m) and m[i + k] else v for k, v in enumerate(x.bytes))
        if x.mnemonic in ID.BRANCHES:
            bb = bb[:1] + bytes(len(bb) - 1)
        o.append((i, len(x.bytes), bb, x.mnemonic, x.op_str))
    return o
r = dec(rbody, rmask); b = dec(body, cm)
print(f"  reference {len(r)} insns, ours {len(b)};  last ref off {r[-1][0]:#x}, ours {b[-1][0]:#x}")
sm = difflib.SequenceMatcher(a=[x[2] for x in r], b=[x[2] for x in b], autojunk=False)
last = None
for tag, i1, i2, j1, j2 in sm.get_opcodes():
    if tag == "equal":
        gap = b[j1][0] - r[i1][0]
        if gap != last:
            print(f"  gap {gap:+3d}  from refoff {r[i1][0]:#06x}  (ouroff {b[j1][0]:#06x})   {r[i1][3]} {r[i1][4]}")
            last = gap
    else:
        print(f"    -- {tag:7s} ref[{i1}:{i2}] at {r[i1][0]:#06x}  built[{j1}:{j2}] at {b[j1][0]:#06x}")
        for k in range(i1, min(i2, i1 + 4)): print(f"       R {r[k][0]:#06x} {r[k][3]} {r[k][4]}")
        for k in range(j1, min(j2, j1 + 4)): print(f"       B {b[k][0]:#06x} {b[k][3]} {b[k][4]}")
