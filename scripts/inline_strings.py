#!/usr/bin/env python3
"""Inline real string literals from the original DLL into reversed .c files.

Decompiled call sites reference 1-byte placeholder globals
(s_<hint>_<0xADDR>, defined in src/link_stubs.c) instead of the actual string.
Each placeholder name encodes the string's original .data address; this script
reads the string bytes from the original DLL at that address and rewrites the
use-site to an inline C literal, so MSVC6 emits the real string COMDAT into
.data at the owning translation unit's link position (placement fix).

Rules:
- Only rewrites code, not comments (`/* */`, `//`).
- Never touches lines inside `__asm { ... }` blocks (asm needs the symbol).
- Leaves `extern char s_...;` declarations alone (harmless once unused).
- Fixed-width octal escapes (\\NNN) so a following hex digit cannot merge.

Usage:
  python3 scripts/inline_strings.py [--dry-run] [--files a.c b.c ...]
"""
import argparse
import pathlib
import re
import sys

ORIGINAL = "original/Server/server.dll"
DATA_BASE = 0x10027000
DATA_OFF = 0x27000
TOKEN_RE = re.compile(r"\bs_[A-Za-z0-9_]+_(100[0-9a-fA-F]{5,6})\b")


def load_orig():
    return pathlib.Path(ORIGINAL).read_bytes()


def read_string(orig, addr):
    off = DATA_OFF + (addr - DATA_BASE)
    if off < 0 or off >= len(orig):
        return None
    end = orig.find(b"\x00", off)
    if end < 0:
        return None
    return orig[off:end]


def c_literal(data):
    out = ['"']
    for b in data:
        if b == 0x5C:
            out.append("\\\\")
        elif b == 0x22:
            out.append('\\"')
        elif b == 0x0A:
            out.append("\\n")
        elif b == 0x0D:
            out.append("\\r")
        elif b == 0x09:
            out.append("\\t")
        elif b < 0x20 or b >= 0x7F:
            out.append("\\%03o" % b)  # fixed-width octal, no hex-merge risk
        else:
            out.append(chr(b))
    out.append('"')
    return "".join(out)


def strip_comments_and_asm(text):
    """Return bytearray mask: 49 ('1') = replaceable, 48 ('0') = keep.

    Masks /* */ and // comments, extern declarations, and __asm { } blocks.
    """
    n = len(text)
    mask = bytearray(b"1" * n)
    line_start = [0]
    for idx, ch in enumerate(text):
        if ch == "\n" and idx + 1 < n:
            line_start.append(idx + 1)
    i = 0
    in_asm = 0
    while i < n:
        if in_asm:
            if text[i] == "{":
                in_asm += 1
            elif text[i] == "}":
                in_asm -= 1
            mask[i] = 48
            i += 1
            continue
        if text.startswith("__asm", i) and (i == 0 or not (text[i-1].isalnum() or text[i-1] == "_")):
            while i < n and text[i] != "{":
                mask[i] = 48
                i += 1
            if i < n:
                mask[i] = 48
                in_asm = 1
                i += 1
            continue
        if text[i] == "/" and i + 1 < n and text[i+1] == "/":
            while i < n and text[i] != "\n":
                mask[i] = 48
                i += 1
            continue
        if text[i] == "/" and i + 1 < n and text[i+1] == "*":
            while i + 1 < n and not (text[i] == "*" and text[i+1] == "/"):
                mask[i] = 48
                i += 1
            if i + 1 < n:
                mask[i] = mask[i+1] = 48
                i += 2
            continue
        i += 1
    # mask whole extern declaration lines
    for ls in line_start:
        line = text[ls:text.index("\n", ls) if "\n" in text[ls:] else n]
        if line.lstrip().startswith("extern"):
            mask[ls:ls+len(line)] = b"0" * len(line)
    return mask


def process_file(path, orig, dry_run, cache):
    text = path.read_text()
    mask = strip_comments_and_asm(text)
    n_changed = 0
    out = []
    last = 0
    for m in TOKEN_RE.finditer(text):
        s, e = m.span()
        if b"0" in mask[s:e]:
            continue  # comment or asm
        addr = int(m.group(1), 16)
        if addr not in cache:
            cache[addr] = read_string(orig, addr)
        data = cache[addr]
        if data is None:
            continue
        out.append(text[last:s])
        out.append(c_literal(data))
        last = e
        n_changed += 1
    if n_changed:
        out.append(text[last:])
        if not dry_run:
            path.write_text("".join(out))
        print(f"{path}: {n_changed} string(s) inlined", file=sys.stderr)
    return n_changed


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--files", nargs="*", help="restrict to these files")
    args = ap.parse_args()

    orig = load_orig()
    cache = {}
    if args.files:
        files = [pathlib.Path(f) for f in args.files]
    else:
        files = sorted(pathlib.Path("src/server.dll").rglob("*.c"))
    total = 0
    for f in files:
        total += process_file(f, orig, args.dry_run, cache)
    print(f"total inlined: {total} use-sites across {len(files)} files", file=sys.stderr)


if __name__ == "__main__":
    main()
