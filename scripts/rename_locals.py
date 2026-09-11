"""Rename identifiers in code, never inside a comment.

The Ghidra reference blocks quote the original decompiler output verbatim, so
`param_1` / `iVar2` inside them are documentation and must keep their names;
only the C code around them is renamed.

usage: python3 .scratch/rename_locals.py <file> <old=new> [<old=new> ...]
"""
from __future__ import annotations

import re
import sys
from pathlib import Path


def main() -> None:
    path = Path(sys.argv[1])
    mapping = dict(x.split("=", 1) for x in sys.argv[2:])
    pattern = re.compile(r"\b(" + "|".join(map(re.escape, mapping)) + r")\b")
    out: list[str] = []
    in_block = False
    struct_depth = 0
    depth = 0
    pending_struct = False
    changed = 0
    for line in path.read_text().splitlines(keepends=True):
        s = line.strip()
        if in_block:
            out.append(line)
            if "*/" in s:
                in_block = False
            continue
        if s.startswith("/*") and "*/" not in s:
            in_block = True
            out.append(line)
            continue
        if s.startswith("//") or s.startswith("/*"):
            out.append(line)
            continue
        if struct_depth or pending_struct:
            # Never rename a field declaration: the accesses are skipped, so a
            # renamed member would leave the struct inconsistent.
            if pending_struct and "{" in line:
                struct_depth = depth + line.count("{")
                pending_struct = False
            out.append(line)
            depth += line.count("{") - line.count("}")
            if struct_depth and depth < struct_depth:
                struct_depth = 0
            continue
        # `struct Foo* x;` uses a struct type; only a line that opens a
        # definition (no `;` on it) starts a block whose fields must not move.
        if re.match(r"^\s*(typedef\s+)?(struct|union)\b[^;]*$", line):
            pending_struct = True
            out.append(line)
            continue
        new, n = pattern.subn(lambda m: mapping[m.group(1)], line)
        # A member access (`.b`, `->p`) names a struct field, not the local.
        def _skip_member(mm: re.Match[str]) -> str:
            head = mm.string[: mm.start()].rstrip()
            if head.endswith((".", "->")):
                return mm.group(0)
            return mapping[mm.group(1)]

        new = pattern.sub(_skip_member, line)
        n = sum(1 for mm in pattern.finditer(line) if not mm.string[: mm.start()].rstrip().endswith((".", "->")))
        changed += n
        out.append(new)
    path.write_text("".join(out))
    print(f"{path.name}: {changed} identifier(s) renamed {mapping}")


if __name__ == "__main__":
    main()
