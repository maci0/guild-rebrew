#!/usr/bin/env python3
"""Consolidate #include, extern, typedef, and #pragma declarations in
multi-function source files.

Each merged compilation unit has per-function declarations that conflict
when compiled as a single translation unit.  This script:

1. Removes ``#include "rebrew_types.h"`` (file no longer exists)
2. Moves unique ``#include`` directives to the top (before first function)
3. Moves unique ``extern`` declarations to the top, resolving conflicts
   by picking the most specific signature for each symbol name
4. Moves unique ``typedef`` declarations to the top
5. Moves unique ``#pragma intrinsic(...)`` to the top (merged)
6. Strips the moved lines from function bodies
"""

import re
import sys
from pathlib import Path

FUNC_MARKER_RE = re.compile(r"//\s*(?:FUNCTION|LIBRARY|STUB):\s*\S+\s+0x[0-9a-fA-F]+")
KV_RE = re.compile(r"//\s*[A-Z_]+:\s*")
INCLUDE_RE = re.compile(r"^\s*#\s*include\s+")
EXTERN_RE = re.compile(r"^\s*extern\s+")
TYPEDEF_RE = re.compile(r"^\s*typedef\s+")
PRAGMA_INTRINSIC_RE = re.compile(r"^\s*#\s*pragma\s+intrinsic\s*\(")
GLOBAL_COMMENT_RE = re.compile(r"^\s*/\*\s*GLOBAL:")


def extract_extern_name(decl: str) -> str | None:
    """Extract the symbol name from an extern declaration."""
    d = decl.strip().rstrip(";").strip()
    d = re.sub(r"/\*.*?\*/", "", d).strip()
    m = re.search(r"(\w+)\s*[\[;(]", decl)
    if m:
        return m.group(1)
    m = re.search(r"(\w+)\s*$", d)
    if m:
        return m.group(1)
    return None


def specificity_score(decl: str) -> int:
    """Higher score = more specific/better declaration."""
    score = 0
    if "void*" in decl or "void *" in decl:
        score += 2
    if "char*" in decl or "char *" in decl:
        score += 2
    if "short*" in decl or "short *" in decl:
        score += 2
    if "unsigned" in decl:
        score += 1
    named_params = len(re.findall(r"\b[a-z_]\w*(?=\s*[,)])", decl))
    score += named_params * 3
    if "..." in decl:
        score += 5
    if "struct" in decl:
        score += 2
    if "const" in decl:
        score += 1
    return score


def resolve_externs(externs: list[str]) -> list[str]:
    """Deduplicate externs, picking the best declaration per symbol."""
    by_name: dict[str, list[str]] = {}
    order: list[str] = []
    for ext in externs:
        name = extract_extern_name(ext)
        if name is None:
            continue
        if name not in by_name:
            order.append(name)
        by_name.setdefault(name, []).append(ext)

    result = []
    for name in order:
        decls = by_name[name]
        unique = list(dict.fromkeys(decls))
        if len(unique) == 1:
            result.append(unique[0])
        else:
            best = max(unique, key=specificity_score)
            result.append(best)
    return result


def extract_pragma_funcs(pragmas: list[str]) -> set[str]:
    """Extract function names from #pragma intrinsic(...) lines."""
    funcs: set[str] = set()
    for p in pragmas:
        m = re.search(r"intrinsic\s*\(([^)]+)\)", p)
        if m:
            for f in m.group(1).split(","):
                f = f.strip()
                if f:
                    funcs.add(f)
    return funcs


def is_annotation_line(line: str) -> bool:
    stripped = line.strip()
    if not stripped:
        return False
    if FUNC_MARKER_RE.match(stripped):
        return True
    if KV_RE.match(stripped):
        return True
    if stripped.startswith("//") and not stripped.startswith("// FUNCTION"):
        m = re.match(r"//\s*[A-Z_]+:", stripped)
        if m:
            return True
        if re.match(r"//\s*\w+", stripped) and ":" not in stripped:
            return True
    return False


def consolidate_file(filepath: Path) -> bool:
    text = filepath.read_text(encoding="utf-8", errors="replace")
    lines = text.splitlines(keepends=True)

    marker_indices = []
    for i, line in enumerate(lines):
        if FUNC_MARKER_RE.match(line.strip()):
            marker_indices.append(i)

    if len(marker_indices) <= 1:
        if '#include "rebrew_types.h"' in text:
            new_text = text.replace('#include "rebrew_types.h"\n', "")
            new_text = new_text.replace('#include "rebrew_types.h"', "")
            if new_text != text:
                filepath.write_text(new_text, encoding="utf-8")
                return True
        return False

    includes: list[str] = []
    externs: list[str] = []
    typedefs: list[str] = []
    pragmas: list[str] = []

    lines_to_remove: set[int] = set()
    global_comments: dict[int, str] = {}

    i = 0
    while i < len(lines):
        line = lines[i]
        stripped = line.strip()

        if stripped == '#include "rebrew_types.h"':
            lines_to_remove.add(i)
            i += 1
            continue

        if INCLUDE_RE.match(stripped):
            includes.append(stripped)
            lines_to_remove.add(i)
            i += 1
            continue

        if GLOBAL_COMMENT_RE.match(stripped):
            global_comments[i] = stripped
            i += 1
            continue

        if EXTERN_RE.match(stripped):
            if i > 0 and GLOBAL_COMMENT_RE.match(lines[i - 1].strip()):
                i += 1
                continue
            externs.append(stripped)
            lines_to_remove.add(i)
            i += 1
            continue

        if TYPEDEF_RE.match(stripped):
            typedefs.append(stripped)
            lines_to_remove.add(i)
            i += 1
            continue

        if PRAGMA_INTRINSIC_RE.match(stripped):
            pragmas.append(stripped)
            lines_to_remove.add(i)
            i += 1
            continue

        i += 1

    unique_includes = list(dict.fromkeys(includes))
    unique_includes = [inc for inc in unique_includes if "rebrew_types" not in inc]

    resolved_externs = resolve_externs(externs)
    unique_typedefs = list(dict.fromkeys(typedefs))

    pragma_funcs = extract_pragma_funcs(pragmas)
    merged_pragma = ""
    if pragma_funcs:
        merged_pragma = "#pragma intrinsic(" + ", ".join(sorted(pragma_funcs)) + ")"

    header_lines: list[str] = []
    if unique_includes:
        for inc in unique_includes:
            header_lines.append(inc + "\n")
        header_lines.append("\n")
    if unique_typedefs:
        for td in unique_typedefs:
            header_lines.append(td + "\n")
        header_lines.append("\n")
    if merged_pragma:
        header_lines.append(merged_pragma + "\n")
        header_lines.append("\n")
    if resolved_externs:
        for ext in resolved_externs:
            if not ext.endswith(";"):
                ext += ";"
            header_lines.append(ext + "\n")
        header_lines.append("\n")

    body_lines: list[str] = []
    prev_blank = False
    for i, line in enumerate(lines):
        if i in lines_to_remove:
            continue
        stripped = line.strip()
        if not stripped:
            if prev_blank:
                continue
            prev_blank = True
        else:
            prev_blank = False
        body_lines.append(line)

    while body_lines and body_lines[0].strip() == "":
        body_lines = body_lines[1:]

    new_text = "".join(header_lines) + "".join(body_lines)

    if not new_text.endswith("\n"):
        new_text += "\n"

    filepath.write_text(new_text, encoding="utf-8")
    return True


def main():
    src_dir = Path(sys.argv[1]) if len(sys.argv) > 1 else Path("src/server.dll")
    fixed = 0
    for cfile in sorted(src_dir.rglob("*.c")):
        if consolidate_file(cfile):
            print(f"Consolidated: {cfile}")
            fixed += 1
    print(f"\nConsolidated {fixed} files")


if __name__ == "__main__":
    main()
