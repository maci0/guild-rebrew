#!/usr/bin/env python3
"""Split a source file at // FUNCTION: boundaries into per-TU files.

Usage: python3 scripts/split_tu.py <file> <line-or-VA> [<line-or-VA> ...]

Each split point = a line number (1-based) or a VA (0x...). The file is split
BEFORE the given line. The FIRST resulting TU keeps the original path; the
rest become <name>2.c, <name>3.c, ... with the shared header (everything
before the first // FUNCTION: line) prepended. The header's first FUNCTION
marker is NEVER copied — this avoids the recurring stale-anchor bug where a
split TU re-sorts at its parent's VA.

Shared declarations used across TUs (e.g. gm_StartEntityQuery) live in the
header block of the original file; keep them there before splitting.
"""
import re
import sys
from pathlib import Path


def main():
    args = sys.argv[1:]
    if len(args) < 2:
        print(__doc__)
        sys.exit(2)
    path = Path(args[0])
    lines = path.read_text().splitlines(True)
    cuts = []
    for a in args[1:]:
        if a.lower().startswith("0x"):
            va = a
            for i, l in enumerate(lines):
                if l.startswith("// FUNCTION:") and va.lower() in l.lower():
                    cuts.append(i)
                    break
            else:
                print(f"VA {va} not found", file=sys.stderr)
                sys.exit(1)
        else:
            cuts.append(int(a) - 1)
    cuts = sorted(set(cuts))
    marks = [i for i, l in enumerate(lines) if l.startswith("// FUNCTION:")]
    header_end = marks[0] if marks else 0
    header = "".join(lines[:header_end])

    parts = []
    prev = 0
    for c in cuts:
        parts.append(lines[prev:c])
        prev = c
    parts.append(lines[prev:])

    stem = path.stem
    out = []
    for idx, part in enumerate(parts):
        if idx == 0:
            out_path = path
            content = "".join(part)
        else:
            out_path = path.with_name(f"{stem}{idx + 1}{path.suffix}")
            content = header + "".join(part)
        out_path.write_text(content)
        out.append(str(out_path))
    print("split into:", *out, sep="\n  ")


if __name__ == "__main__":
    main()
