#!/usr/bin/env python3
"""Sweep compiler-flag variants for one function and report the best.

The single largest win in this project came from a flag: `gm_AllocSpieler`'s
annotation said `/O2 /Gd /Oa` while every measurement had been taken with
`/Oa /Ow`, and putting `/Ow` where the build reads it moved 363 linked bytes.
Every function's flags live in `rebrew-functions.toml` and are resolved by the
same chain the build uses, so a wrong set is invisible until someone sweeps it.

This compiles one function under each variant with `scripts/probe_function.py`
(which resolves the function's own metadata flags first, then applies the
override) and prints the scored table, best first.  It does NOT write metadata --
pair it with `rebrew test --no-promote`-style care when adopting a winner.

Usage:
    python3 scripts/flagsweep.py --va 0x10002770 --file <src>
    python3 scripts/flagsweep.py --va 0x10002770 --file <src> --variants "/Ox /Gd" ...
"""

from __future__ import annotations

import argparse
import concurrent.futures as cf
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
PROBE = ROOT / "scripts" / "probe_function.py"

# Optimization/codegen flags only: the base (/Gd, defines, includes) is
# orthogonal and already comes from the project.
VARIANTS = [
    "/O2 /Gd", "/O1 /Gd", "/Ox /Gd",
    "/O2 /Gd /Ot", "/O2 /Gd /Os", "/O2 /Gd /Oa", "/O2 /Gd /Ow",
    "/O2 /Gd /Oa /Ow", "/O2 /Gd /Ob0", "/O2 /Gd /Ob1", "/O2 /Gd /Oy-",
    "/O2 /Gd /G6", "/O2 /Gd /G5", "/O2 /Gd /Og-", "/O2 /Gd /Oi-",
    "/O2 /Gd /Ot /Ow", "/O2 /Gd /Ow /Ob1", "/Ox /Gd /Ow",
]


def score(file: Path, va: str, flags: str) -> tuple[int, int, int]:
    r = subprocess.run([sys.executable, str(PROBE), "--va", va, "--file", str(file),
                        "--cflags", flags],
                       capture_output=True, text=True, cwd=ROOT)
    m = re.search(r"matched (\d+)/(\d+).*instructions (\d+) vs (\d+), object size (\d+)",
                  r.stdout, re.S)
    if not m:
        return -1, -1, -1
    return int(m.group(1)), -abs(int(m.group(3)) - int(m.group(4))), int(m.group(5))


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--va", required=True)
    ap.add_argument("--file", required=True)
    ap.add_argument("--variants", nargs="*", default=VARIANTS)
    ap.add_argument("--jobs", type=int, default=4)
    args = ap.parse_args()
    src = ROOT / args.file

    with cf.ThreadPoolExecutor(max_workers=args.jobs) as ex:
        rows = list(ex.map(lambda fl: (fl, score(src, args.va, fl)), args.variants))
    rows.sort(key=lambda kv: (-kv[1][0], -kv[1][1]))
    base = dict(rows).get("/O2 /Gd")
    print(f"{Path(args.file).name} 0x{args.va}")
    print(f"{'flags':24s} {'matched':>8s} {'insnΔ':>6s} {'obj':>6s}")
    for flags, (matched, delta, obj) in rows:
        print(f"{flags:24s} {matched:8d} {delta:6d} {obj:6d}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
