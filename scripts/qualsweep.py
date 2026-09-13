#!/usr/bin/env python3
"""Sweep declaration qualifiers/types for the functions statement order cannot fix.

`scripts/hillclimb.py` moves whole statements.  Several of the remaining
functions converge there because their residue is register *naming* rather than
order: the target keeps a loop counter in `ebx` where we keep it in `edi`, the
same instruction kinds in the same sequence.  msvc6's allocator is driven by
live ranges, so the cheap way to perturb it without changing what the code does
is to change a local's qualifying type.

Two qualifier wins are already recorded in this tree and both came from exactly
that: `ServerMainThread` went 1114 -> 501 residual bytes by reading a progress
counter through a `volatile` alias, and `ls_LoadBuildingEntityState` recovered
`or ebp,-1` by making eight `*(volatile int*) (esi + 0x71)` reads volatile
(docs/TODO.md).  This runs the same idea over every declaration in a function,
one at a time, keeping only moves that make the compiled function more identical
to the reference and never let it come out shorter than the reference's (the
composition trims an overrun but cannot pad a gap -- see hillclimb.py).

Usage:
    python3 scripts/qualsweep.py --va 0x10015f70 --file <src>
    python3 scripts/qualsweep.py --va 0x10015f70 --file <src> --dry-run
"""

from __future__ import annotations

import argparse
import concurrent.futures as cf
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
from hillclimb import function_body, is_decl, score, statements, strip_literals  # noqa: E402
from hillclimb import symbol_for, target_size  # noqa: E402

# (label, regex to find the type, replacement) — each must keep the declaration
# legal and the function semantically identical.
QUALIFIERS = [
    ("volatile", r"^(\s*)(?!(?:.*\bvolatile\b))", r"\1volatile "),
]


def variants(decl: str):
    """Candidate rewrites of one declaration, as (label, text)."""
    body = strip_literals(decl).strip()
    for label, pat, repl in QUALIFIERS:
        new = re.sub(pat, repl, decl, count=1, flags=re.M)
        if strip_literals(new).strip() != body:
            yield label, new


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--va", required=True)
    ap.add_argument("--file", required=True)
    ap.add_argument("--symbol", default=None)
    ap.add_argument("--rounds", type=int, default=4)
    ap.add_argument("--jobs", type=int, default=4)
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()

    src = ROOT / args.file
    name = args.symbol or symbol_for(int(args.va, 0))
    if not name:
        sys.exit("pass --symbol (no map entry for that VA)")
    text = src.read_text()
    lo, hi = function_body(text, name)
    head, body, tail = text[:lo], text[lo:hi], text[hi:]
    spans = statements(body)
    units = [body[a:b] for a, b in spans]
    decls = [k for k, u in enumerate(units) if is_decl(u)]
    print(f"{name}: {len(units)} statements, {len(decls)} declarations")

    base = score(src, args.va)
    print(f"baseline {base[1]} matched, object size {base[3]} "
          f"vs target {target_size(args.va)}")

    for rnd in range(args.rounds):
        cands = [(k, lab, new) for k in decls for lab, new in variants(units[k])]
        if args.dry_run:
            for k, lab, new in cands:
                print(f"  [{k:3d}] {lab}: {strip_literals(new).strip()[:70]}")
            return 0

        def submit(k, lab, new):
            tmp = src.with_name(f"_qs_{name}_{k}_{lab}.c")
            alt = units[:]
            alt[k] = new
            tmp.write_text(head + "".join(alt) + tail)
            return (k, lab, new), score(tmp, args.va)

        with cf.ThreadPoolExecutor(max_workers=args.jobs) as ex:
            results = list(ex.map(lambda c: submit(*c), cands))
        for p in src.parent.glob(f"_qs_{name}_*.c"):
            p.unlink(missing_ok=True)

        best, best_c = base, None
        for (_k, _lab, _new), sc in results:
            if sc > best:
                best, best_c = sc, (_k, _lab, _new)
        if best_c is None:
            print(f"round {rnd}: no improving qualifier among {len(cands)}; "
                  f"converged at {base[1]}")
            break
        k, lab, new = best_c
        units[k] = new
        base = best
        src.write_text(head + "".join(units) + tail)
        print(f"round {rnd}: {lab} on [{k}] -> {base[1]} matched "
              f"(object {base[3]})  {strip_literals(new).strip()[:50]!r}")
    for p in src.parent.glob(f"_qs_{name}_*.c"):
        p.unlink(missing_ok=True)
    print(f"final {base[1]} matched, object size {base[3]}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
