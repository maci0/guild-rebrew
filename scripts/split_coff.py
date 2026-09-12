#!/usr/bin/env python3
"""Split static-library members into one COFF object per COMDAT section.

Why: MSVC LINK appends every archive member after every command-line object, so
`LIBCMT.lib` leaves all CRT code at the end of `.text`, while the reference
interleaves members with game/CRT objects.  Putting whole members on the
command line fixes the order but over-includes: the 99 members
`scripts/map_libcmt.py` selects carry 40,896 B of `.text` against the
reference region's 34,550 B.

LIBCMT is built with `/Gy`, so every function is its own COMDAT `.text`
section.  Extracting just the sections the reference uses gives per-*function*
selection with ordinary command-line objects, which is what the link needs.

Output: one `.obj` per section, named `<va>_<symbol>.obj`, each a valid COFF
object with the section, its relocations remapped onto a reconstructed symbol
table, and the string table rebuilt.

Usage:
    python3 scripts/split_coff.py --lib .scratch/libcmt/LIBCMT.sp6.LIB \\
        --map .scratch/libcmt_map.json --out build/libcmt_split
"""

from __future__ import annotations

import argparse
import json
import struct
import sys
from pathlib import Path


# ---------------------------------------------------------------------------
# COFF parsing
# ---------------------------------------------------------------------------


def ar_members(data: bytes):
    if data[:8] != b"!<arch>\n":
        return []
    pos, out = 8, []
    while pos + 60 <= len(data):
        header = data[pos : pos + 60]
        if len(header) < 60:
            break
        name = header[0:16].decode("ascii", "replace").strip()
        try:
            size = int(header[48:58].decode().strip())
        except ValueError:
            break
        out.append((name, data[pos + 60 : pos + 60 + size]))
        pos += 60 + size + (size & 1)
    return out


def name_resolver(members):
    longnames = next((b for n, b in members if n.startswith("//")), None)

    def resolve(name: str) -> str:
        if name.startswith("/") and name[1:].isdigit() and longnames is not None:
            off = int(name[1:])
            return longnames[off : longnames.find(b"\0", off)].decode()
        return name.rstrip("/")

    return resolve


class Coff:
    def __init__(self, data: bytes):
        self.data = data
        (
            self.machine,
            self.nsections,
            self.timestamp,
            self.symptr,
            self.nsyms,
            self.opt_size,
            self.characteristics,
        ) = struct.unpack_from("<HHIIIHH", data, 0)
        self.sections = []
        for i in range(self.nsections):
            off = 20 + i * 40
            self.sections.append(
                {
                    "off": off,
                    "name": data[off : off + 8],
                    "raw_size": struct.unpack_from("<I", data, off + 16)[0],
                    "raw_ptr": struct.unpack_from("<I", data, off + 20)[0],
                    "reloc_ptr": struct.unpack_from("<I", data, off + 24)[0],
                    "lineno_ptr": struct.unpack_from("<I", data, off + 28)[0],
                    "nreloc": struct.unpack_from("<H", data, off + 32)[0],
                    "nlineno": struct.unpack_from("<H", data, off + 34)[0],
                    "chars": struct.unpack_from("<I", data, off + 36)[0],
                }
            )
        self.strtab_off = self.symptr + self.nsyms * 18 if self.symptr else 0
        self.symbols = []
        i = 0
        while i < self.nsyms:
            off = self.symptr + i * 18
            entry = data[off : off + 18]
            raw = entry[0:8]
            if raw[0:4] == b"\0\0\0\0":
                stroff = struct.unpack_from("<I", raw, 4)[0]
                end = data.find(b"\0", self.strtab_off + stroff)
                name = data[self.strtab_off + stroff : end].decode("ascii", "replace")
            else:
                name = raw.rstrip(b"\0").decode("ascii", "replace")
            self.symbols.append(
                {
                    "raw_name": raw,
                    "name": name,
                    "value": struct.unpack_from("<I", entry, 8)[0],
                    "section": struct.unpack_from("<h", entry, 12)[0],
                    "type": struct.unpack_from("<H", entry, 14)[0],
                    "storage_class": entry[16],
                    "naux": entry[17],
                    "aux": data[off + 18 : off + 18 + entry[17] * 18],
                }
            )
            i += 1 + entry[17]

    def section_body(self, index: int) -> bytes:
        s = self.sections[index]
        return self.data[s["raw_ptr"] : s["raw_ptr"] + s["raw_size"]]

    def section_relocs(self, index: int):
        s = self.sections[index]
        out = []
        for i in range(s["nreloc"]):
            off = s["reloc_ptr"] + i * 10
            va, symidx, typ = struct.unpack_from("<IIH", self.data, off)
            out.append((va, symidx, typ))
        return out


def build_object(coff: Coff, index: int, out_name: str) -> bytes:
    """One-section COFF object for `coff.sections[index]`."""
    s = coff.sections[index]
    relocs = coff.section_relocs(index)
    body = coff.section_body(index)

    # Symbols to keep: definitions in this section, the section symbol, and
    # every symbol referenced by a relocation.
    keep = []
    seen = set()

    def add(i: int):
        if i not in seen:
            seen.add(i)
            keep.append(i)

    for i, sym in enumerate(coff.symbols):
        if sym["section"] == index + 1:
            add(i)
    for _va, symidx, _typ in relocs:
        if symidx < len(coff.symbols):
            add(symidx)
    # Sections referenced by relocations are emitted as IMAGE_REL_I386_DIR32
    # against the section symbol's replacement, so no extra sections needed.

    # New string table + symbol table.  SectionNumber is 1 for everything that
    # lived in the extracted section; absolute/undefined keep their original.
    strtab = bytearray(b"\0\0\0\0")
    new_symbols = bytearray()
    remap = {}
    entry_count = 0
    for old_i in keep:
        sym = coff.symbols[old_i]
        remap[old_i] = entry_count
        entry_count += 1 + sym["naux"]
        raw = sym["raw_name"]
        if raw[0:4] == b"\0\0\0\0":
            off = len(strtab)
            strtab += sym["name"].encode("ascii", "replace") + b"\0"
            raw = b"\0\0\0\0" + struct.pack("<I", off)
        section_number = sym["section"]
        if section_number == index + 1:
            section_number = 1
        elif section_number > 0:
            # The defining section is not part of this object, so the linker
            # has to resolve the symbol from wherever it is emitted.
            section_number = 0
        new_symbols += (
            raw
            + struct.pack(
                "<IhHBB",
                sym["value"],
                section_number,
                sym["type"],
                sym["storage_class"],
                sym["naux"],
            )
            + sym["aux"]
        )

    # Relocations, remapped.
    new_relocs = bytearray()
    for va, symidx, typ in relocs:
        new_relocs += struct.pack("<IIH", va, remap.get(symidx, 0), typ)

    # Layout: header, section header, body, relocs, symbols, string table.
    hdr_size = 20
    sec_size = 40
    body_off = hdr_size + sec_size
    reloc_off = body_off + len(body)
    if not relocs:
        reloc_off = 0
    sym_off = body_off + len(body) + len(new_relocs)
    str_off = sym_off + len(new_symbols)

    sec = bytearray(coff.data[s["off"] : s["off"] + 40])
    struct.pack_into("<I", sec, 16, len(body))  # SizeOfRawData
    struct.pack_into("<I", sec, 20, body_off)  # PointerToRawData
    struct.pack_into("<I", sec, 24, reloc_off)  # PointerToRelocations
    struct.pack_into("<I", sec, 28, 0)  # PointerToLinenumbers
    struct.pack_into("<H", sec, 32, len(relocs))  # NumberOfRelocations
    struct.pack_into("<H", sec, 34, 0)  # NumberOfLinenumbers

    header = struct.pack(
        "<HHIIIHH",
        coff.machine,
        1,
        coff.timestamp,
        sym_off,
        entry_count,
        0,
        coff.characteristics,
    )
    struct.pack_into("<I", strtab, 0, len(strtab))
    return bytes(header) + bytes(sec) + body + bytes(new_relocs) + bytes(new_symbols) + bytes(strtab)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--lib", required=True)
    ap.add_argument("--map", required=True, help="JSON from scripts/map_libcmt.py --json")
    ap.add_argument("--out", required=True)
    ap.add_argument("--from-va", default="0x1001a150")
    args = ap.parse_args()

    root = Path(__file__).resolve().parent.parent
    lib = Path(args.lib)
    if not lib.is_absolute():
        lib = root / lib
    outdir = Path(args.out)
    if not outdir.is_absolute():
        outdir = root / outdir
    outdir.mkdir(parents=True, exist_ok=True)

    mapping = json.loads(Path(args.map).read_text())
    floor = int(args.from_va, 16)
    want = {}
    for e in mapping["matched"]:
        va = int(e["va"], 16)
        if va >= floor:
            want.setdefault(e["member"], []).append((va, e["symbol"]))

    members = ar_members(lib.read_bytes())
    resolve = name_resolver(members)
    by_name = {resolve(raw): obj for raw, obj in members}

    written, index = [], {}
    for member, funcs in want.items():
        obj = by_name.get(member)
        if obj is None:
            print(f"  missing member {member}", file=sys.stderr)
            continue
        coff = Coff(obj)
        for va, symbol in funcs:
            # find the section that defines `symbol`
            hit = None
            for i, sym in enumerate(coff.symbols):
                if sym["name"] == symbol and sym["section"] > 0:
                    hit = i
                    break
            if hit is None:
                print(f"  no section for {symbol} in {member}", file=sys.stderr)
                continue
            data = build_object(coff, coff.symbols[hit]["section"] - 1, symbol)
            safe = "".join(c if c.isalnum() or c in "._" else "_" for c in symbol)
            name = f"{va:08x}_{safe}.obj"
            (outdir / name).write_bytes(data)
            written.append((va, str(outdir / name), symbol))

    written.sort()
    print(f"wrote {len(written)} objects to {outdir}")
    (outdir / "index.json").write_text(
        json.dumps([{"va": f"0x{v:x}", "obj": o, "symbol": s} for v, o, s in written], indent=1)
    )
    return 0


if __name__ == "__main__":
    sys.exit(main())
