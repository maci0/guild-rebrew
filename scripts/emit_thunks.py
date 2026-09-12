#!/usr/bin/env python3
"""Emit the reference's `jmp dword ptr [IAT]` import thunks as command-line objects.

The reference has seven such stubs at 0x1001a160..0x1001a18a, immediately
before `_fclose`, for the socket imports.  They are live code: the reference's
`SendBroadcastPacket` (0x10001130) makes nine direct `call`/`jmp` to them
between 0x10001142 and 0x100011c0, because the original source declares those
imports without `__declspec(dllimport)` and MSVC therefore emits a five-byte
`call _socket@12` that LINK resolves to a thunk.

Our builds do produce equivalent thunks — from `WS2_32.lib` — but LINK appends
archive members after every command-line object, so they land at the end of
`.text` (0x1001c2b8+ in the standard build) instead of at 0x1001a160.  Defining
them on the command line before the CRT objects puts them where the reference
has them.

Each emitted thunk is the reference's own six bytes (`ff 25 <IAT>`) with the
four-byte operand as a DIR32 relocation against the import library's
`__imp_<decorated>` symbol, so the displacement is filled in by LINK.

Usage:
    python3 scripts/emit_thunks.py --target-bin original/Server/server.dll \\
        --out build/libcmt_thunks
then scripts/make_split_rsp.py --thunks DIR inserts them between the game
objects and the CRT objects.
"""

from __future__ import annotations

import argparse
import json
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

#: IAT VA -> the stdcall symbol the thunk must define.  The `@N` suffix is the
#: argument bytes; the import's `__imp_` twin is what the relocation names.
THUNKS = {
    0x10024198: "_closesocket@4",   # closesocket(SOCKET)          4 bytes
    0x10024194: "_sendto@24",       # sendto(s, buf, len, flags, to, tolen)
    0x10024190: "_bind@12",         # bind(s, name, namelen)
    0x1002418C: "_htons@4",         # htons(u_short)
    0x10024188: "_htonl@4",         # htonl(u_long)
    0x10024184: "_setsockopt@20",   # setsockopt(s, level, optname, optval, optlen)
    0x10024180: "_socket@12",       # socket(af, type, protocol)
}


def text_at(data: bytes, va: int, size: int) -> bytes:
    e = struct.unpack_from("<I", data, 0x3C)[0]
    nsec = struct.unpack_from("<H", data, e + 6)[0]
    optsz = struct.unpack_from("<H", data, e + 20)[0]
    base = struct.unpack_from("<I", data, e + 52)[0]
    off = e + 24 + optsz
    for i in range(nsec):
        s = data[off + i * 40:off + (i + 1) * 40]
        if s[0:5] == b".text":
            vs, rva, raw, ptr = struct.unpack_from("<IIII", s, 8)
            if va >= base + rva:
                return data[ptr + (va - base - rva):ptr + (va - base - rva) + size]
    raise SystemExit("no .text")


def build_object(thunks: list[tuple[str, bytes, int]]) -> bytes:
    """One COMDAT `.text` section holding `(symbol, six bytes, iat)` in order.

    The section is COMDAT, so like every LIBCMT section it carries a section
    symbol with one AUX record; LINK requires that for a comdat section.
    """
    body = bytearray()
    relocs = []
    for sym, code, _iat in thunks:
        off = len(body)
        body += code
        relocs.append((off + 2, sym))

    strtab = bytearray(b"\0\0\0\0")

    def name_bytes(n: str) -> bytes:
        if len(n) <= 8:
            return n.encode("ascii").ljust(8, b"\0")
        o = len(strtab)
        strtab.extend(n.encode("ascii") + b"\0")
        return b"\0\0\0\0" + struct.pack("<I", o)

    symtab = bytearray()
    # section symbol, class 3, one AUX record
    symtab += name_bytes(".text") + struct.pack("<IhHBB", 0, 1, 0, 3, 1)
    aux = bytearray(18)
    struct.pack_into("<I", aux, 0, len(body))       # Length
    struct.pack_into("<H", aux, 4, len(relocs))     # NumberOfRelocations
    aux[14] = 1                                     # Selection: ANY
    symtab += aux
    index = 2                                       # entries used so far
    entry_of = []
    for _off, sym in relocs:
        for name, section in (("__imp_" + sym, 0), (sym, 1)):
            entry_of.append((name, section, index))
            symtab += name_bytes(name) + struct.pack("<IhHBB", 0, section, 0x20, 2, 0)
            index += 1

    blob = bytes(body) + b"".join(
        struct.pack("<IIH", va, entry_of[i * 2][2], 0x06)
        for i, (va, _s) in enumerate(relocs))

    sec = bytearray(40)
    sec[0:8] = b".text\0\0\0"
    struct.pack_into("<I", sec, 8, len(body))
    struct.pack_into("<I", sec, 16, len(body))
    struct.pack_into("<I", sec, 20, 20 + 40)
    struct.pack_into("<I", sec, 24, 20 + 40 + len(body))
    struct.pack_into("<H", sec, 32, len(relocs))
    struct.pack_into("<I", sec, 36, 0x60501020)

    struct.pack_into("<I", strtab, 0, len(strtab))
    header = struct.pack("<HHIIIHH", 0x14C, 1, 0, 20 + 40 + len(blob),
                         index, 0, 0)
    return bytes(header) + bytes(sec) + blob + bytes(symtab) + bytes(strtab)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--target-bin", required=True)
    ap.add_argument("--out", required=True)
    args = ap.parse_args()

    data = (ROOT / args.target_bin).read_bytes()
    out = ROOT / args.out
    out.mkdir(parents=True, exist_ok=True)
    thunks = []
    for iat, sym in sorted(THUNKS.items(), key=lambda kv: -kv[0]):
        code = text_at(data, iat - 0x10, 8)   # cheap sanity read, not used
        del code
        thunks.append((sym, None, iat))
    # read the real six bytes at the thunk VA by searching for `ff 25 <iat>`
    for i, (sym, _c, iat) in enumerate(thunks):
        pat = b"\xff\x25" + struct.pack("<I", iat)
        pos = data.find(pat)
        if pos < 0:
            raise SystemExit(f"no thunk for {sym} ({iat:#x})")
        thunks[i] = (sym, pat, iat)
    (out / "import_thunks.obj").write_bytes(build_object(thunks))
    (out / "index.json").write_text(json.dumps(
        [{"symbol": s, "iat": iat} for s, _c, iat in thunks], indent=1))
    print(f"wrote {len(thunks)} thunks to {out / 'import_thunks.obj'}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
