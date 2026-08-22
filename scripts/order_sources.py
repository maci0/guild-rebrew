#!/usr/bin/env python3
"""Order source files for linking by their first function's original VA.

MSVC6 LINK places objects in command-line order and (without /Gy) does not
reorder functions.  The original DLL's .text/.data layout therefore equals its
object link order.  Sorting our sources by each file's lowest original
function VA reproduces that layout, so functions and globals land at their
original addresses (fixes reccmp "0 functions aligned" and shrinks the byte
diff to real content differences only).

VA sources, in priority:
  1. "// FUNCTION:" headers inside game .c files
  2. ZLIB_FIRST_VA table (zlib functions cataloged in db/server.dll_functions.csv)
Files with no discoverable VA sort last (path order).  Files listed in
ZLIB_FIRST_VA with value None are absent from the original binary and are
dropped from the build entirely.

Usage:
  python3 scripts/order_sources.py <src.c>...   # prints ordered paths
"""
import re
import sys
import pathlib

# zlib translation units -> VA of their first function in the original.
# None = not present in original -> exclude from build.
ZLIB_FIRST_VA = {
    "adler32.c":   0x10001000,
    "crc32.c":     0x100011F0,   # cataloged as vfs_Crc32Update
    "deflate.c":   0x10001330,
    "gzio.c":      None,          # emitted as gz_gzread.c dump
    "infblock.c":  0x10003D20,
    "inffast.c":   None,          # different revision; dumped as inffast_dump.c
    "infcodes.c":  None,          # different revision; dumped as infcodes_dump.c
    "inflate.c":   0x10005720,
    "inftrees.c":  0x10005D00,
    "infutil.c":   0x10006440,
    "trees.c":     0x10006EC0,   # _tr_init
    "trees2.c":    0x10008800,   # set_data_type
    "zutil.c":     0x100092E0,   # zcalloc
    "compress.c":  None,          # not in original server.dll
    "uncompr.c":   None,          # not in original server.dll
}

FUNC_RE = re.compile(r"^//\s*FUNCTION:\s*(?:server\.dll|SERVER)\s+0x([0-9A-Fa-f]+)", re.M)


def file_va(path):
    p = pathlib.Path(path)
    if p.name in ZLIB_FIRST_VA:
        return ZLIB_FIRST_VA[p.name]
    try:
        text = p.read_text(errors="replace")
    except OSError:
        return None
    vas = [int(m.group(1), 16) for m in FUNC_RE.finditer(text)]
    return min(vas) if vas else None


def main():
    excluded = set()
    known = []
    unknown = []
    for arg in sys.argv[1:]:
        f = pathlib.Path(arg)
        if f.name in ZLIB_FIRST_VA and ZLIB_FIRST_VA[f.name] is None:
            excluded.add(f.name)
            continue
        va = file_va(f)
        if va is None:
            unknown.append(f)
        else:
            known.append((va, f))
    known.sort(key=lambda t: t[0])
    unknown.sort(key=lambda p: str(p))
    for _, f in known:
        print(f)
    for f in unknown:
        print(f)
    if excluded:
        print(f"# excluded (absent from original): {sorted(excluded)}", file=sys.stderr)


if __name__ == "__main__":
    main()
