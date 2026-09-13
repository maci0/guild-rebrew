"""Honest instruction alignment between a candidate object and the target.

usage: ndiff.py <obj> <symbol> <va-hex> <size> [--show N] [--list]

Both sides are disassembled with capstone from a correctly bounded byte range
(`--disassemble=<symbol>` bounds the candidate; the VA+size window bounds the
target), then normalised so relocated operands read the same on both sides.
Masking relocations by byte offset (as triage2.py does) is only valid while the
two byte streams are in step, which is exactly what a mismatch breaks; this
compares instruction text instead, so a shift cannot corrupt it.

--list prints the hunks largest first, with the target VA each starts at.
"""

import difflib
import sys
from pathlib import Path

import capstone

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
import seqdiff  # noqa: E402
import zlibcheck  # noqa: E402

obj, sym, va, size = Path(sys.argv[1]), sys.argv[2], int(sys.argv[3], 16), int(sys.argv[4])
show = 0
if "--show" in sys.argv:
    show = int(sys.argv[sys.argv.index("--show") + 1])

tb = ROOT / ".scratch" / f"nd_{obj.stem}.bin"
seqdiff.extract(va, size, tb)
tbytes, _ = zlibcheck.cand_bytes(Path(obj), sym)
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
tins = list(md.disasm(tb.read_bytes(), va))
cins = list(md.disasm(tbytes, 0))
target = [seqdiff.norm(f"{i.mnemonic} {i.op_str}".strip()) for i in tins]
ours = [seqdiff.norm(f"{i.mnemonic} {i.op_str}".strip()) for i in cins]

sm = difflib.SequenceMatcher(None, target, ours, autojunk=False)
same = sum(b.size for b in sm.get_matching_blocks())
kinds: dict[str, int] = {"sched": 0, "operand": 0, "instr": 0}
hunks = [h for h in sm.get_opcodes() if h[0] != "equal"]
for tag, i1, i2, j1, j2 in hunks:
    kinds[seqdiff.classify(target[i1:i2], ours[j1:j2])] += 1
print(
    f"target {len(target)} ours {len(ours)} bytes {len(tbytes)} (tgt {size}, {len(tbytes)-size:+d})"
)
print(f"aligned {same}/{len(target)}  hunks {len(hunks)} {kinds}")

if "--trange" in sys.argv:
    lo, hi = (int(x) for x in sys.argv[sys.argv.index("--trange") + 1 :][:2])
    for tag, i1, i2, j1, j2 in hunks:
        if i2 < lo or i1 > hi:
            continue
        where = f"{tins[i1].address:#x}" if i1 < len(tins) else "end"
        print(f"--- {tag} size {max(i2-i1, j2-j1)} T[{i1}:{i2}] C[{j1}:{j2}] at {where}")
        for x in target[i1:i2]:
            print("  T", x)
        for x in ours[j1:j2]:
            print("  C", x)
    sys.exit(0)

if "--hunk" in sys.argv:
    want = {int(x) for x in sys.argv[sys.argv.index("--hunk") + 1].split(",")}
    rows = sorted(
        (
            max(i2 - i1, j2 - j1),
            seqdiff.classify(target[i1:i2], ours[j1:j2]),
            tag,
            i1,
            i2,
            j1,
            j2,
        )
        for tag, i1, i2, j1, j2 in hunks
    )[::-1]
    for n, (sz, kind, tag, i1, i2, j1, j2) in enumerate(rows):
        if n not in want:
            continue
        where = f"{tins[i1].address:#x}" if i1 < len(tins) else "end"
        print(f"=== hunk {n} size {sz} {kind} {tag} T[{i1}:{i2}] C[{j1}:{j2}] at {where}")
        for x in target[i1:i2]:
            print("  T", x)
        for x in ours[j1:j2]:
            print("  C", x)
    sys.exit(0)

if "--list" in sys.argv:
    rows = [
        (
            max(i2 - i1, j2 - j1),
            seqdiff.classify(target[i1:i2], ours[j1:j2]),
            tag,
            i1,
            i2,
            j1,
            j2,
        )
        for tag, i1, i2, j1, j2 in hunks
    ]
    for n, (sz, kind, tag, i1, i2, j1, j2) in enumerate(sorted(rows, reverse=True)[:40]):
        where = f"{tins[i1].address:#x}" if i1 < len(tins) else "end"
        print(f"{n:3d} size {sz:3d} {kind:6s} {tag:8s} T[{i1}:{i2}] C[{j1}:{j2}] at {where}")
    sys.exit(0)

for tag, i1, i2, j1, j2 in hunks[:show]:
    print(f"--- {tag} T[{i1}:{i2}] C[{j1}:{j2}] at {tins[i1].address:#x}")
    for x in target[i1:i2]:
        print("  T", x)
    for x in ours[j1:j2]:
        print("  C", x)
