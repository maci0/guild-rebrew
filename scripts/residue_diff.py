#!/usr/bin/env python3
"""Compare two `postlink_residual` per-function tables.

The object-level scores are proxies and they disagree with the deliverable in
both directions: CrashDump gained 52 object bytes and lost 10 linked bytes, and
in round 173 four changes that *raised* the aligned (LCS) score -- including two
of the coordinator's -- were linked regressions of +7 to +672.  The only
measurement that decides is the composed image's per-function residue, so every
candidate is validated by relinking once and diffing this table.

Pair it with `scripts/linktest.sh`, which does the recompile-relink-diff cycle.

Usage:
    python3 scripts/residue_diff.py .scratch/residue_base.log .scratch/linktest-residue.log
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

ROW = re.compile(r"^(\S.*?)\s{2,}(\d+)\s+0x[0-9a-f]+$")


def table(path: Path) -> dict[str, int]:
    out: dict[str, int] = {}
    for line in path.read_text().splitlines():
        m = ROW.match(line)
        if m:
            out[m.group(1).strip()] = int(m.group(2))
    return out


def total(path: Path) -> int | None:
    m = re.search(r"^\.text differing 0x([0-9a-f]+)", path.read_text(), re.M)
    return int(m.group(1), 16) if m else None


def main() -> int:
    if len(sys.argv) != 3:
        sys.exit(__doc__)
    before, after = (table(Path(p)) for p in sys.argv[1:3])
    tb, ta = (total(Path(p)) for p in sys.argv[1:3])
    names = sorted(set(before) | set(after))
    print(f"{'function':40s} {'before':>7s} {'after':>7s} {'delta':>7s}")
    worse = []
    for n in names:
        b, a = before.get(n, 0), after.get(n, 0)
        if a == b:
            continue
        if a > b:
            worse.append((n, a - b))
        print(f"{n[:40]:40s} {b:7d} {a:7d} {a - b:+7d}{'  <-- worse' if a > b else ''}")
    print(f"\n.text total {tb} -> {ta}  ({ta - tb:+d})")
    if worse:
        print("revert candidates: " + ", ".join(f"{n} (+{d})" for n, d in worse))
    return 0


if __name__ == "__main__":
    sys.exit(main())
