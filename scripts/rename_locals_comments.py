"""Follow a local's rename through the comments that name it.

A probe log refers to locals by name, so renaming the code alone leaves the
prose stale.  This rewrites the mapping in comments, skipping the verbatim
Ghidra quote blocks (those name Ghidra's own `iVar1`/`param_1` output, not the
reconstruction's locals).

usage: python3 scripts/rename_locals_comments.py <file> <old=new> [...]
"""
from __future__ import annotations

import re
import sys
from pathlib import Path

GHIDRA = "Ghidra decompilation reference"


def main() -> None:
    path = Path(sys.argv[1])
    mapping = dict(x.split("=", 1) for x in sys.argv[2:])
    pattern = re.compile(r"\b(" + "|".join(map(re.escape, mapping)) + r")\b")
    text = path.read_text()
    parts = re.split(r"(?s)(/\*.*?\*/)", text)
    total = 0
    for i, part in enumerate(parts):
        if part.startswith("/*"):
            if GHIDRA in part:
                continue
            new, n = pattern.subn(lambda m: mapping[m.group(1)], part)
        else:
            lines = []
            for line in part.splitlines(keepends=True):
                s = line.lstrip()
                if s.startswith("//") or s.startswith("*"):
                    line, n = pattern.subn(lambda m: mapping[m.group(1)], line)
                    total += n
                lines.append(line)
            new = "".join(lines)
            n = 0
        total += n
        parts[i] = new
    path.write_text("".join(parts))
    print(f"{path.name}: {total} comment reference(s) renamed")


if __name__ == "__main__":
    main()
