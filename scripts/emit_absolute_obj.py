#!/usr/bin/env python3
"""Write a COFF object that defines one absolute symbol.

The symbol has no section, so the link gains no .data and no .bss.
z_errmsg's empty slots name ``_z_errmsg_empty``; the reference resolves
that to 0x10034620 inside the gap blob. A C definition would emit bytes.
"""

from __future__ import annotations

import argparse
import struct
from pathlib import Path


def absolute_object(name: str, value: int) -> bytes:
    """One external absolute (section number -1) and nothing else."""
    strtab = bytearray(b"\0\0\0\0")
    encoded = name.encode("ascii")
    if len(encoded) <= 8:
        raw = encoded.ljust(8, b"\0")
    else:
        off = len(strtab)
        strtab += encoded + b"\0"
        raw = b"\0\0\0\0" + struct.pack("<I", off)
    symbols = raw + struct.pack("<IhHBB", value & 0xFFFFFFFF, -1, 0, 2, 0)
    header = struct.pack("<HHIIIHH", 0x14C, 0, 0, 20, 1, 0, 0)
    struct.pack_into("<I", strtab, 0, len(strtab))
    return bytes(header) + bytes(symbols) + bytes(strtab)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--name", required=True)
    ap.add_argument("--value", required=True, help="absolute value, decimal or 0x")
    ap.add_argument("--out", required=True, type=Path)
    args = ap.parse_args()
    args.out.parent.mkdir(parents=True, exist_ok=True)
    args.out.write_bytes(absolute_object(args.name, int(args.value, 0)))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
