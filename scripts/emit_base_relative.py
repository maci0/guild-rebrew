#!/usr/bin/env python3
"""Emit ONE `.bss` object holding the pool symbols at base-relative offsets.

Why this exists (round 177).  The raw link's uninitialised symbols were scattered
across a 24 MB region while the reference has them at a fixed set of addresses.
Every previous attempt asked the linker to *choose* a better place -- reordering,
reclassifying, packing, absolute symbols -- and each one measured worse or broke
the image (rounds 128-176).

The base is not unknown.  Round 151 measured where the linker starts the
uninitialised region: the end of `.data`'s initialised content, and round 177/178
pinned it at **0x10034620** (a `+20` uniform error from the first guess showed the
method was sound and the constant merely wrong).  So: hand the linker one `.bss`
object whose symbols already sit at `reference_address - BASE`.  It places the
object at the base it was always going to use, and every symbol lands where the
reference has it.

Measured (round 177, against the split link):

    symbols at their reference address   428/636  ->  533/636
    .text differing                       4,419   ->  2,306
    OBJECTIVE GAP                        41,619   ->  39,519
    relocation records (missing/shared)  590/2936 ->  590/2936
    wine load                             OK      ->  OK
    raw-link .data differing              0       ->  13

The 13 `.data` bytes are relocation targets the linker rewrites from the symbols
this moves -- all 13 are relocation targets in the reference (round 180) -- so they
are consistency, not corruption, and DATA_BASELINE was raised to 13 to accept them
with the user's agreement (round 182).

The remaining 21 symbols are still provided by `1001a643_.text.obj` in a `.text`
section, which wins over this object's `.bss` definition; stripping it breaks the
image (rounds 179, 181).  Placing those needs the same treatment applied to the
blob's own contribution, which is not done here.

Usage (called by scripts/split_link.sh):
    python3 scripts/emit_base_relative.py --map build/split_poc.map \\
        --rsp build/split_poc/rsp.rsp --refer build/common_addresses.json \\
        --out build/split_poc/base_relative.obj --base 0x10034620
"""
from __future__ import annotations

import argparse
import json
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "scripts"))

from split_coff import Coff  # noqa: E402

#: Where the linker starts the uninitialised region.  Measured, not chosen:
#: round 151 (the end of `.data`'s initialised content), round 177/178 (the
#: value that makes the object's symbols land exactly -- a first guess of
#: 0x1003460c put all 106 of them a uniform +20 high).
DEFAULT_BASE = 0x10034620
MAP_RE = re.compile(r"^\s*\d{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{8})\s+[fF]?\s+(\S+)\s*$")


def build_object(symbols: list[tuple[str, int]], span: int) -> bytes:
    """One `.bss` section, each symbol at its offset.  Raw bytes are kept because
    LINK refuses a member whose section has SizeOfRawData 0 (LNK1106, round 90)."""
    strtab = bytearray(b"\x04\x00\x00\x00")

    def nm(s: str) -> bytes:
        b = s.encode("ascii")
        if len(b) <= 8:
            return b.ljust(8, b"\0")
        off = len(strtab)
        strtab.extend(b + b"\0")
        return b"\0\0\0\0" + struct.pack("<I", off)

    syms = bytearray()
    syms += nm(".bss") + struct.pack("<IhHBB", 0, 1, 0, 3, 0)
    for name, off in symbols:
        syms += nm(name) + struct.pack("<IhHBB", off & 0xFFFFFFFF, 1, 0, 2, 0)
    # the string table's first dword is its own total length, including itself;
    # leaving it stale is what produced LNK1136/ReadSymbolTable in rounds 124/177
    struct.pack_into("<I", strtab, 0, len(strtab))
    pad = 4
    sec = bytearray(40)
    sec[0:8] = b".bss\0\0\0\0"
    struct.pack_into("<I", sec, 8, span)
    struct.pack_into("<I", sec, 16, pad)
    struct.pack_into("<I", sec, 20, 20 + 40)
    struct.pack_into("<I", sec, 36, 0xC0000080)
    # 0x014C = IMAGE_FILE_MACHINE_I386.  Packing it as 0x4C01 stores the bytes
    # reversed and LINK rejects the object as foreign (LNK1136, round 124).
    hdr = struct.pack("<HHIIIHH", 0x014C, 1, 0, 20 + 40 + pad, len(symbols) + 1, 0, 0)
    return bytes(hdr) + bytes(sec) + b"\x00" * pad + bytes(syms) + bytes(strtab)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--map", default="build/split_poc.map")
    ap.add_argument("--rsp", default="build/split_poc/rsp.rsp")
    ap.add_argument("--refer", default="build/common_addresses.json")
    ap.add_argument("--out", default="build/split_poc/base_relative.obj")
    ap.add_argument("--base", default=hex(DEFAULT_BASE))
    ap.add_argument("--json", action="store_true")
    args = ap.parse_args()
    base = int(args.base, 0)

    refer = json.loads((ROOT / args.refer).read_text())
    got: set[str] = set()
    for line in (ROOT / args.map).read_text(errors="replace").splitlines():
        m = MAP_RE.match(line)
        if m:
            got.add(m.group(1).lstrip("_"))

    # a symbol's size: the COMMON `value` when it has one, else 4
    size: dict[str, int] = {}
    for rel in (ROOT / args.rsp).read_text().split():
        p = ROOT / "build" / rel.replace("\\", "/")
        if not p.exists():
            continue
        try:
            c = Coff(p.read_bytes())
        except Exception:
            continue
        for s in c.symbols:
            if s and s["section"] == 0 and s["storage_class"] == 2 and s["value"]:
                n = s["name"]
                if isinstance(n, bytes):
                    n = n.decode("ascii", "replace")
                size.setdefault(n.lstrip("_"), s["value"])

    pool = sorted((v, n) for n, v in refer.items() if v >= base)
    span = max(v - base + max(4, size.get(n, 4)) for v, n in pool)
    (ROOT / args.out).write_bytes(build_object([("_" + n, v - base) for v, n in pool], span))

    info = {"base": hex(base), "symbols": len(pool), "span": span,
            "in_our_link": sum(1 for _v, n in pool if n in got)}
    if args.json:
        print(json.dumps(info, indent=2))
    else:
        print("base-relative object: %d symbols, span %d, base %s"
              % (info["symbols"], span, info["base"]))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
