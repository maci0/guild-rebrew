#!/usr/bin/env python3
"""Answer "has this address already been probed, and what did it say?" before spending a round.

Round 853 cost a whole round re-deriving `msvc6-c-shapes.md` section 127: the exact
instruction pair at `ServerMainThread`'s anchor was already recorded, with the decisive
probe and its `+0` result. The objective's rule is "before reshaping a
compiling-but-mismatched function, read shapes first" -- but the docs are ~8,000 lines
across four files plus a 23,000-line TODO, and a `grep` only helps if you already know
the words the entry used. The entries are keyed by *address*, so look the address up.

usage:
    python3 scripts/whathas.py 0x10009838            # what is recorded at this VA
    python3 scripts/whathas.py 0x10009838 --window 64 # widen the band
    python3 scripts/whathas.py --va 0x100093a0 0x10009936   # a whole function's span
    python3 scripts/whathas.py 0x10009838 --json

Exit status is 0 whether or not anything is found; the tool reports, it does not judge.
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

# Every doc that records a probe against an address. codegen-walls.md indexes by
# mechanism rather than VA and is searched for context only.
VA_DOCS = [
    "docs/msvc6-c-shapes.md",
    "docs/msvc6-allocator.md",
    "docs/codegen-walls.md",
    "docs/measure-traps.md",
    "docs/workflow-traps.md",
    "docs/TODO.md",
]

VA_RE = re.compile(r"0x(100[0-9a-f]{5})", re.IGNORECASE)


def parse_va(text: str) -> int:
    return int(text, 16)


def section_of(lines: list[str], idx: int) -> str:
    """Nearest preceding markdown heading, so a hit can be cited."""
    for j in range(idx, -1, -1):
        m = re.match(r"^(#{2,4})\s+(.*)$", lines[j])
        if m:
            return m.group(2).strip()
    return "(no heading)"


def scan(vas: list[int], window: int, docs: list[str]) -> list[dict]:
    lo, hi = min(vas) - window, max(vas) + window
    hits: list[dict] = []
    for rel in docs:
        p = ROOT / rel
        if not p.exists():
            continue
        lines = p.read_text(errors="ignore").splitlines()
        for i, line in enumerate(lines):
            found = {int(m.group(1), 16) for m in VA_RE.finditer(line)}
            if not found:
                continue
            if not any(lo <= va <= hi for va in found):
                continue
            near = [f"0x{va:x}" for va in sorted(found) if lo <= va <= hi]
            hits.append(
                {
                    "doc": rel,
                    "line": i + 1,
                    "va": near,
                    "section": section_of(lines, i),
                    "text": line.strip(),
                }
            )
    return hits


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("va", nargs="*", help="address(es), e.g. 0x10009838")
    ap.add_argument("--va", nargs="+", dest="va_range", help="span: start end")
    ap.add_argument("--window", type=int, default=0, help="widen the match band (bytes)")
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--context", type=int, default=0, help="also print N lines around each hit")
    args = ap.parse_args()

    raw = list(args.va_range or []) + list(args.va or [])
    if not raw:
        ap.error("give at least one VA (or --va start end)")

    vas = [parse_va(v) for v in raw]
    docs = VA_DOCS
    hits = scan(vas, args.window, docs)

    if args.json:
        print(json.dumps({"vas": [f"0x{v:x}" for v in vas], "window": args.window, "hits": hits}, indent=2))
        return 0

    span = f"0x{min(vas):x}" if len(vas) == 1 else f"0x{min(vas):x}..0x{max(vas):x}"
    if not hits:
        print(f"{span}: no documented probe in {len(docs)} docs.")
        print("Nothing recorded at this address -- it is not automatically novel, but no round")
        print("has written up a probe against it. Check the file header for the enclosing")
        print("function before assuming it is unexplored.")
        return 0

    by_doc: dict[str, list[dict]] = {}
    for h in hits:
        by_doc.setdefault(h["doc"], []).append(h)

    print(f"{span}: {len(hits)} documented mention(s){' (window %d)' % args.window if args.window else ''}\n")
    for doc, hs in by_doc.items():
        print(f"== {doc}  ({len(hs)})")
        for h in hs:
            print(f"  :{h['line']:<6} [{h['section']}]")
            print(f"          {h['text'][:150]}")
        print()
    return 0


if __name__ == "__main__":
    sys.exit(main())
