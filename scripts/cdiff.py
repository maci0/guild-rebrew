"""Content-only alignment: registers collapsed, so hunks are real content gaps.

usage: cdiff.py <obj> <symbol> <va-hex> <size> [--show N] [--list]
"""
import difflib
import re
import sys
from pathlib import Path

import capstone

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
import seqdiff  # noqa: E402
import zlibcheck  # noqa: E402

REG = re.compile(
    r"\b(eax|ebx|ecx|edx|esi|edi|ebp|esp|ax|bx|cx|dx|si|di|bp|sp|"
    r"al|bl|cl|dl|ah|bh|ch|dh|st\(0\)|st\(1\)|st\(2\))\b"
)

obj, sym, va, size = Path(sys.argv[1]), sys.argv[2], int(sys.argv[3], 16), int(sys.argv[4])
show = int(sys.argv[sys.argv.index("--show") + 1]) if "--show" in sys.argv else 0

tb = ROOT / ".scratch" / f"cd_{obj.stem}.bin"
seqdiff.extract(va, size, tb)
tbytes, _ = zlibcheck.cand_bytes(Path(obj), sym)
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
tins = list(md.disasm(tb.read_bytes(), va))
cins = list(md.disasm(tbytes, 0))
target = [REG.sub("r", seqdiff.norm(f"{i.mnemonic} {i.op_str}".strip())) for i in tins]
ours = [REG.sub("r", seqdiff.norm(f"{i.mnemonic} {i.op_str}".strip())) for i in cins]

sm = difflib.SequenceMatcher(None, target, ours, autojunk=False)
same = sum(b.size for b in sm.get_matching_blocks())
hunks = [h for h in sm.get_opcodes() if h[0] != "equal"]
print(f"target {len(target)} ours {len(ours)} bytes {len(tbytes)} (tgt {size}, {len(tbytes)-size:+d})")
print(f"content-aligned {same}/{len(target)}  hunks {len(hunks)}")

if "--list" in sys.argv:
    rows = sorted(
        ((max(i2 - i1, j2 - j1), tag, i1, i2, j1, j2) for tag, i1, i2, j1, j2 in hunks),
        reverse=True,
    )
    for n, (sz, tag, i1, i2, j1, j2) in enumerate(rows[:40]):
        where = f"{tins[i1].address:#x}" if i1 < len(tins) else "end"
        print(f"{n:3d} size {sz:3d} {tag:8s} T[{i1}:{i2}] C[{j1}:{j2}] at {where}")
    sys.exit(0)

if "--hunk" in sys.argv:
    want = {int(x) for x in sys.argv[sys.argv.index("--hunk") + 1].split(",")}
    rows = sorted(
        ((max(i2 - i1, j2 - j1), tag, i1, i2, j1, j2) for tag, i1, i2, j1, j2 in hunks),
        reverse=True,
    )
    for n, (sz, tag, i1, i2, j1, j2) in enumerate(rows):
        if n not in want:
            continue
        where = f"{tins[i1].address:#x}" if i1 < len(tins) else "end"
        print(f"=== hunk {n} size {sz} {tag} T[{i1}:{i2}] C[{j1}:{j2}] at {where}")
        for x in target[i1:i2]:
            print("  T", x)
        for x in ours[j1:j2]:
            print("  C", x)
    sys.exit(0)

for tag, i1, i2, j1, j2 in hunks[:show]:
    where = f"{tins[i1].address:#x}" if i1 < len(tins) else "end"
    print(f"--- {tag} T[{i1}:{i2}] C[{j1}:{j2}] at {where}")
    for x in target[i1:i2]:
        print("  T", x)
    for x in ours[j1:j2]:
        print("  C", x)
