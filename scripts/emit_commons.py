#!/usr/bin/env python3
"""Emit one tiny object per LIBCMT member holding that member's commons.

Why: a COFF *common* (storage class 2, section 0, `Value` = size — LIBCMT uses
these for `__mbctype` 0x101, `___mbcodepage` 4, `__XcptActTab`, `__except_list`,
`__cinit`, ...) is allocated by the linker, so no member *section* defines it.
A reference to one therefore makes LINK search the archive, find the member
that declares it, and append that member's whole `.text` after the split-set
region — which is what keeps the last six members (1,635 bytes) in
`docs/TODO.md` round 29's pull list.

Defining the commons on the command line stops that.  They are emitted as
standalone one-section objects rather than folded into the split objects
because appending a synthetic `.bss` to an existing object makes LINK reject it
(`LNK1143: no symbol for comdat section`), and a one-section object has none of
that complexity.

Usage:
    python3 scripts/emit_commons.py --lib ... --map ... --out build/libcmt_commons
then add the resulting objects to the rsp (see scripts/make_split_rsp.py).
"""

from __future__ import annotations

import argparse
import json
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from split_coff import Coff, ar_members, name_resolver  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent

#: IMAGE_SCN_CNT_UNINITIALIZED_DATA | MEM_READ | MEM_WRITE | align 4
BSS_CHARS = 0xC0300080


def build_commons_object(entries: list[tuple[str, int]]) -> bytes:
    """A one-section COFF defining each `(name, size)` as a common."""
    offsets = []
    off = 0
    for _name, size in entries:
        align = 8 if size >= 8 else 4
        off = (off + align - 1) & ~(align - 1)
        offsets.append(off)
        off += size
    total = (off + 3) & ~3

    strtab = bytearray(b"\0\0\0\0")
    symbols = bytearray()
    for (name, _size), value in zip(entries, offsets):
        if len(name) <= 8:
            raw = name.encode("ascii", "replace").ljust(8, b"\0")
        else:
            o = len(strtab)
            strtab += name.encode("ascii", "replace") + b"\0"
            raw = b"\0\0\0\0" + struct.pack("<I", o)
        symbols += raw + struct.pack("<IhHBB", value, 1, 0, 2, 0)

    sec = bytearray(40)
    sec[0:8] = b".bss\0\0\0\0"
    struct.pack_into("<I", sec, 8, total)
    struct.pack_into("<I", sec, 16, total)
    struct.pack_into("<I", sec, 20, 0)
    struct.pack_into("<I", sec, 24, 0)
    struct.pack_into("<I", sec, 28, 0)
    struct.pack_into("<H", sec, 32, 0)
    struct.pack_into("<H", sec, 34, 0)
    struct.pack_into("<I", sec, 36, BSS_CHARS)

    header = struct.pack("<HHIIIHH", 0x14C, 1, 0, 20 + 40, len(entries), 0, 0)
    struct.pack_into("<I", strtab, 0, len(strtab))
    return bytes(header) + bytes(sec) + bytes(symbols) + bytes(strtab)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--lib", action="append", required=True)
    ap.add_argument("--map", required=True)
    ap.add_argument("--out", required=True)
    args = ap.parse_args()

    libs = []
    for spec in args.lib:
        lp = Path(spec)
        libs.append(lp if lp.is_absolute() else ROOT / lp)
    outdir = Path(args.out)
    outdir.mkdir(parents=True, exist_ok=True)

    # Every member of the libraries, not just the mapped ones: the members
    # LINK still pulls are exactly the ones the map could not map, so scanning
    # only the mapped set would miss the commons that cause the pull.
    by_name: dict[str, bytes] = {}
    for lp in libs:
        ar = ar_members(lp.read_bytes())
        resolve = name_resolver(ar)
        for raw, obj in ar:
            by_name.setdefault(resolve(raw), obj)
    members = set(by_name)

    seen: set[str] = set()
    written = 0
    for member in sorted(members):
        obj = by_name.get(member)
        if obj is None:
            continue
        try:
            syms = Coff(obj).symbols
        except (struct.error, IndexError):
            continue
        commons = [
            (s["name"], s["value"])
            for s in syms
            if s is not None
            and s["storage_class"] == 2
            and s["section"] == 0
            and s["value"] > 0
        ]
        commons = [(n, v) for n, v in commons if n not in seen]
        if not commons:
            continue
        seen.update(n for n, _ in commons)
        safe = re.sub(r"[^A-Za-z0-9._]", "_", member.split("\\")[-1])
        (outdir / f"commons_{safe}.obj").write_bytes(build_commons_object(commons))
        written += 1
    print(f"wrote {written} commons objects to {outdir}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
