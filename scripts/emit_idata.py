#!/usr/bin/env python3
"""Emit a complete `.idata` import directory as a command-line COFF object.

Why (round 10).  The 642-byte `.text` overshoot is 89 import thunks that exist
only because the link carries `/OPT:NOREF`: an MSVC6 import library keeps each
function's `jmp dword ptr [IAT]` thunk in the member's `.text`, and NOREF keeps
unreferenced sections.  Round 9 measured that `/OPT:REF` removes the thunks but
also drops 177 real symbols, and that `.def IMPORTS` cannot express this DLL's
mostly-stdcall imports (LNK4017).  So the remaining route is to stop taking the
descriptors from the import libraries and supply `.idata` ourselves, with
`__imp_X` as absolute symbols pointing into the IAT we lay down.

The loader reads the import directory out of the image; it does not care that
LINK did not build it.  That is the whole point of doing it here.

`--poc` emits the single-DLL case, used to prove LINK accepts a hand-built
descriptor before the full 4-DLL / 100-symbol version is trusted in a real link.
"""

from __future__ import annotations

import argparse
import struct
from pathlib import Path

IMAGE_BASE = 0x10000000

#: .idata is initialized, read-only data.
IDATA_CHARS = 0x40000040


def build_idata_object(dlls: list[tuple[str, list[str]]], section_rva: int
                       ) -> tuple[bytes, dict[str, int]]:
    """Return (COFF object bytes, {import name -> IAT slot VA}).

    `dlls` is [(dll name, [symbol, ...])] in the order the IAT must have.
    `section_rva` is the RVA this section will be placed at, so every RVA
    inside it (descriptors, ILT, IAT, hint/name, dll names) is computed against
    it and the absolute `__imp_X` values come out right.
    """
    ndesc = len(dlls) + 1                       # + the null terminator

    # ---- pass 1: lay the section out, in this order -----------------------
    desc_off = 0
    ilt_start: dict[str, int] = {}
    p = desc_off + ndesc * 20
    for dll, syms in dlls:
        ilt_start[dll] = p
        p += (len(syms) + 1) * 4
    iat_start: dict[str, int] = {}
    slot_off: dict[str, int] = {}
    for dll, syms in dlls:
        iat_start[dll] = p
        for s in syms:
            slot_off[s] = p
            p += 4
        p += 4                                 # null terminator
    hint_at: dict[str, int] = {}
    for _dll, syms in dlls:
        for s in syms:
            hint_at[s] = p
            p += 2 + len(s) + 1
            if p & 1:
                p += 1                        # hint/name entries are WORD aligned
    dllname_at: dict[str, int] = {}
    for dll, _syms in dlls:
        dllname_at[dll] = p
        p += len(dll) + 1

    body = bytearray(p)

    def rva(off: int) -> int:
        return section_rva + off

    # ---- pass 2: fill it --------------------------------------------------
    for s, off in hint_at.items():
        struct.pack_into("<H", body, off, 0)   # hint 0
        body[off + 2:off + 2 + len(s)] = s.encode("ascii")
        body[off + 2 + len(s)] = 0
    for dll, off in dllname_at.items():
        body[off:off + len(dll)] = dll.encode("ascii")
        body[off + len(dll)] = 0

    for gi, (dll, syms) in enumerate(dlls):
        lp, ap = ilt_start[dll], iat_start[dll]
        for s in syms:
            struct.pack_into("<I", body, lp, rva(hint_at[s]))
            struct.pack_into("<I", body, ap, rva(hint_at[s]))
            lp += 4
            ap += 4
        struct.pack_into("<I", body, lp, 0)   # ILT null
        struct.pack_into("<I", body, ap, 0)   # IAT null
        d = desc_off + gi * 20
        struct.pack_into("<IIIII", body, d,
                         rva(ilt_start[dll]), 0, 0,
                         rva(dllname_at[dll]), rva(iat_start[dll]))
    # the trailing null descriptor is already zeroed

    slots = {s: IMAGE_BASE + section_rva + off for s, off in slot_off.items()}
    return _wrap(body, slots), slots


def _wrap(body: bytearray, iat_slots: dict[str, int]) -> bytes:
    """Wrap `body` as a one-section COFF object carrying the `__imp_X` symbols."""
    strtab = bytearray(b"\0\0\0\0")

    def name_bytes(n: str) -> bytes:
        if len(n) <= 8:
            return n.encode("ascii").ljust(8, b"\0")
        o = len(strtab)
        strtab.extend(n.encode("ascii") + b"\0")
        return b"\0\0\0\0" + struct.pack("<I", o)

    symtab = bytearray()
    symtab += name_bytes(".idata") + struct.pack("<IHHBB", 0, 1, 0, 3, 0)
    index = 1
    for imp, va in sorted(iat_slots.items(), key=lambda kv: kv[1]):
        # section number 0xFFFF == ABSOLUTE: the symbol IS the address
        symtab += name_bytes("__imp__" + imp) + struct.pack("<IHHBB",
                                                           va & 0xFFFFFFFF, 0xFFFF, 0, 2, 0)
        index += 1

    raw = 20 + 40 + len(body)
    sec = bytearray(40)
    sec[0:8] = b".idata\0\0"
    struct.pack_into("<I", sec, 8, len(body))
    struct.pack_into("<I", sec, 16, len(body))
    struct.pack_into("<I", sec, 20, 20 + 40)                 # PointerToRawData
    struct.pack_into("<I", sec, 24, 0)                        # no relocations
    struct.pack_into("<I", sec, 36, IDATA_CHARS)

    struct.pack_into("<I", strtab, 0, len(strtab))
    header = struct.pack("<HHIIIHH", 0x14C, 1, 0, 20 + 40 + len(body), index, 0, 0)
    return header + bytes(sec) + bytes(body) + bytes(symtab) + bytes(strtab)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--poc", action="store_true",
                    help="emit the single-DLL proof of case")
    ap.add_argument("--out", required=True)
    args = ap.parse_args()

    if not args.poc:
        raise SystemExit("full 4-DLL emission is not implemented; run --poc first")
    obj, slots = build_idata_object([("KERNEL32.dll", ["GetTickCount@0"])], 0x26000)
    Path(args.out).write_bytes(obj)
    for k, v in sorted(slots.items(), key=lambda kv: kv[1]):
        print(f"  __imp__{k} = {v:#x}")
    print(f"wrote {args.out} ({len(obj)} bytes)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
