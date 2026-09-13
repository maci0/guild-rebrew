#!/usr/bin/env python3
"""Where does our function lose (or gain) length relative to the reference?

Aligns the two instruction streams and prints our offset minus the reference's at
the start of each equal block.  The running gap is the instrument for a LENGTH
hypothesis, which neither probe_function nor instr_diff can see: a function whose
real COMDAT body is N bytes short has its out-of-line jump table / case map N bytes
early, moving every 4-byte relocated entry in it, while the object score stays flat.

    scripts/gaptrace.py <va> [size] <source> <comdat-symbol>

`size` is optional and is best omitted.  The window that matters is the
reference's *real body*, which for a function with an out-of-line jump table or
case map is longer than the metadata `size` (that covers the code only):
`vfs_OpenStream` is 667 bytes of code inside a 701-byte real body inside a
704-byte window before the next function.  Passing the metadata size there
compares 667 reference bytes against our 704-byte object, and the table bytes get
disassembled as ~20 phantom instructions -- it reads as "37 bytes too long, 20
extra instructions" when in fact the two are byte-aligned.  Omitting `size`
derives the window from the next function's VA in db/server.dll_functions.csv,
which is correct in both cases; passing a size that disagrees with it prints a
warning.
"""
import sys, difflib, re, subprocess, capstone
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
import instr_diff as ID
from split_coff import Coff


def window(va):
    """Bytes from `va` to the next function's VA -- the reference real body."""
    rows = []
    for ln in open(ROOT / "db/server.dll_functions.csv"):
        p = ln.strip().split("|")
        if len(p) >= 5:
            try: rows.append((int(p[0], 16), int(p[4])))
            except ValueError: pass
    nxt = next((a for a, _ in sorted(rows) if a > va), None)
    return (nxt - va) if nxt else None


argv = sys.argv[1:]
va = int(argv[0], 0)
try:
    size = int(argv[1], 0)
    src, sym = argv[2], argv[3]
except ValueError:
    size, src, sym = None, argv[1], argv[2]
real = window(va)
if size is None:
    size = real
elif real and size != real:
    print(f"  NOTE: size {size} passed but the next function starts {real} bytes on "
          f"({real - size:+d}); the reference real body is {real}.  Omit size to use it.")
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
def off(seq, i):
    """Offset at index i, or "end" past the last instruction.

    Either side can be exhausted at the final opcode -- the two streams are
    different lengths, which is the whole point of the trace -- so both ends are
    indexed defensively.
    """
    return f"{seq[i][0]:#06x}" if i < len(seq) else "end"


def real_body(seq):
    """Length of the decoded code: end of the last instruction.

    NOT `len(seq)` as an instruction count -- both streams are decoded over their
    whole window, and that window ends in alignment fill (cl rounds every COMDAT up
    to 16, and the reference has its own pad before the next function).  Those fill
    bytes decode as instructions (`nop`, or `add [eax],al` for 0x00), so the counts
    read high and disagree between the sides even when the code is byte-aligned.
    Compare this number, not the count.
    """
    return f"{seq[-1][0] + seq[-1][1]:#06x}" if seq else "0"


print(f"  reference {len(r)} insns, ours {len(b)} "
      f"(COUNTS INCLUDE TRAILING ALIGNMENT FILL -- do not use them for length);")
print(f"  real code ends:  reference {real_body(r)}, ours {real_body(b)};  "
      f"last insn off {off(r, len(r)-1)} / {off(b, len(b)-1)}")
sm = difflib.SequenceMatcher(a=[x[2] for x in r], b=[x[2] for x in b], autojunk=False)
last = None
for tag, i1, i2, j1, j2 in sm.get_opcodes():
    if tag == "equal":
        gap = b[j1][0] - r[i1][0]
        if gap != last:
            print(f"  gap {gap:+3d}  from refoff {r[i1][0]:#06x}  (ouroff {b[j1][0]:#06x})   {r[i1][3]} {r[i1][4]}")
            last = gap
    else:
        print(f"    -- {tag:7s} ref[{i1}:{i2}] at {off(r, i1)}  built[{j1}:{j2}] at {off(b, j1)}")
        for k in range(i1, min(i2, i1 + 4)): print(f"       R {r[k][0]:#06x} {r[k][3]} {r[k][4]}")
        for k in range(j1, min(j2, j1 + 4)): print(f"       B {b[k][0]:#06x} {b[k][3]} {b[k][4]}")
