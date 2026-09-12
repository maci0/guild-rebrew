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


def build_object(coff: Coff, index: int, out_name: str, separate: set[int] | None = None, claimed: set[int] | None = None, closure: bool = False) -> bytes:
    """COFF object for `coff.sections[index]` plus its same-member closure.

    `separate` holds the section indices that are themselves emitted as their
    own object (the member's mapped functions); the closure stops there so the
    sections are not duplicated and stay at their own reference VAs.
    """
    separate = separate or set()
    claimed = claimed if claimed is not None else set()
    # Section closure: every .text section reachable from this one through a
    # relocation to a symbol defined in ANOTHER section of the same member.
    # MSVC splits a member's shared tails into separate COMDATs (memmove's
    # LeadUp*/UnwindUp*/TrailUp* family), and leaving them out makes the linker
    # re-pull the whole member and append it after the region.
    need = {index}
    work = [index] if closure else []
    while work:
        i = work.pop()
        for _va, symidx, _typ in coff.section_relocs(i):
            if symidx >= len(coff.symbols):
                continue
            sec = coff.symbols[symidx]["section"]
            if sec > 0:
                j = sec - 1
                if (
                    j not in need
                    and j not in separate
                    and j not in claimed
                    and coff.sections[j]["name"].startswith(b".text")
                ):
                    need.add(j)
                    work.append(j)
    secs = sorted(need)
    claimed.update(secs)
    new_secnum = {old: k + 1 for k, old in enumerate(secs)}

    # Symbols to keep: every definition in the emitted sections and every
    # symbol referenced by their relocations.
    keep = []
    seen = set()

    def add(i: int):
        if i not in seen:
            seen.add(i)
            keep.append(i)

    for i, sym in enumerate(coff.symbols):
        if sym["section"] > 0 and (sym["section"] - 1) in new_secnum:
            add(i)

    # A relocation may name a *section* symbol (class 3, ".text") of a COMDAT
    # that is not part of this object.  Leaving that as an external named
    # ".text" leaves LINK with an unresolvable reference, so retarget it at the
    # external function symbol defined in that section.
    first_ext: dict[int, int] = {}
    for i, sym in enumerate(coff.symbols):
        if sym["section"] > 0 and sym["storage_class"] == 2:
            j = sym["section"] - 1
            if j not in first_ext or sym["value"] < coff.symbols[first_ext[j]]["value"]:
                first_ext[j] = i

    def resolve_ref(symidx: int) -> int:
        if symidx >= len(coff.symbols):
            return symidx
        sym = coff.symbols[symidx]
        if sym["storage_class"] == 3 and sym["name"].startswith(".") and sym["section"] > 0:
            j = sym["section"] - 1
            if j not in new_secnum and j in first_ext:
                return first_ext[j]
        return symidx

    for i in secs:
        for _va, symidx, _typ in coff.section_relocs(i):
            if symidx < len(coff.symbols):
                add(resolve_ref(symidx))

    # Symbol table, renumbered onto the emitted sections.
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
        section_number = new_secnum.get(sym["section"] - 1, 0) if sym["section"] > 0 else sym["section"]
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

    # Layout: header, section headers, then (body, relocations) per section,
    # then symbols and the string table.
    hdr_size = 20
    sec_size = 40
    cur = hdr_size + sec_size * len(secs)
    headers = bytearray()
    blobs = bytearray()
    for old in secs:
        body = coff.section_body(old)
        relocs = coff.section_relocs(old)
        body_off = cur
        cur += len(body)
        cur += (-cur) % 4
        if relocs:
            reloc_off = cur
            blob = b"".join(
                struct.pack("<IIH", va, remap.get(resolve_ref(symidx), 0), typ)
                for va, symidx, typ in relocs
            )
            cur += len(blob)
        else:
            reloc_off = 0
            blob = b""
        sec = bytearray(coff.data[coff.sections[old]["off"] : coff.sections[old]["off"] + 40])
        struct.pack_into("<I", sec, 16, len(body))
        struct.pack_into("<I", sec, 20, body_off)
        struct.pack_into("<I", sec, 24, reloc_off)
        struct.pack_into("<I", sec, 28, 0)
        struct.pack_into("<H", sec, 32, len(relocs))
        struct.pack_into("<H", sec, 34, 0)
        headers += sec
        blobs += body + b"\0" * ((-(body_off + len(body))) % 4) + blob

    sym_off = cur
    header = struct.pack(
        "<HHIIIHH",
        coff.machine,
        len(secs),
        coff.timestamp,
        sym_off,
        entry_count,
        0,
        coff.characteristics,
    )
    struct.pack_into("<I", strtab, 0, len(strtab))
    return bytes(header) + bytes(headers) + bytes(blobs) + bytes(new_symbols) + bytes(strtab)


def closure_sections(coff: Coff, root: int, skip: set[int]) -> list[int]:
    """Same-member .text sections reachable from `root`, excluding `skip`."""
    out: list[int] = []
    seen = {root}
    work = [root]
    while work:
        i = work.pop(0)
        for _va, symidx, _typ in coff.section_relocs(i):
            if symidx >= len(coff.symbols):
                continue
            sec = coff.symbols[symidx]["section"]
            if sec <= 0:
                continue
            j = sec - 1
            if j in seen or j in skip or not coff.sections[j]["name"].startswith(b".text"):
                continue
            seen.add(j)
            out.append(j)
            work.append(j)
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--lib", action="append", required=True,
                    help="static library (repeatable); members are looked up in order")
    ap.add_argument("--map", required=True, help="JSON from scripts/map_libcmt.py --json")
    ap.add_argument("--out", required=True)
    ap.add_argument("--from-va", default="0x1001a150")
    ap.add_argument(
        "--skip-helper",
        action="append",
        default=["__CRT_INIT@12"],
        help="helper symbol to leave to LIBCMT (repeatable).  Default "
        "__CRT_INIT@12: when our objects supply it LIBCMT's dllcrt0.obj is not "
        "pulled and LINK stops resolving /ENTRY:_DllMainCRTStartup@12",
    )
    ap.add_argument(
        "--closure",
        action="store_true",
        help="also pull same-member .text sections the mapped function references "
        "(memmove's LeadUp*/UnwindUp* COMDATs); the PoC link with this on did not "
        "resolve /ENTRY:_DllMainCRTStartup@12, so it is off by default",
    )
    args = ap.parse_args()

    root = Path(__file__).resolve().parent.parent
    libs = []
    for spec_ in args.lib:
        lp = Path(spec_)
        if not lp.is_absolute():
            lp = root / lp
        libs.append(lp)
    lib = libs[0]
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
            want.setdefault(e["member"], []).append((va, e["symbol"], e.get("section")))

    by_name: dict[str, bytes] = {}
    for lp in libs:
        members = ar_members(lp.read_bytes())
        resolve = name_resolver(members)
        for raw, obj in members:
            by_name.setdefault(resolve(raw), obj)

    written: list[tuple[int | None, str, str]] = []
    for member, funcs in want.items():
        obj = by_name.get(member)
        if obj is None:
            print(f"  missing member {member}", file=sys.stderr)
            continue
        coff = Coff(obj)
        def find_section(symbol, section):
            """The map records the matched COFF section; .text symbols repeat."""
            if section:
                return section - 1
            for sym in coff.symbols:
                if sym["name"] == symbol and sym["section"] > 0:
                    return sym["section"] - 1
            return None

        mapped = set()
        for _va, symbol, section in funcs:
            sec = find_section(symbol, section)
            if sec is not None:
                mapped.add(sec)
        claimed: set[int] = set()
        for va, symbol, section in sorted(funcs, key=lambda f: f[0]):
            root_sec = find_section(symbol, section)
            if root_sec is None:
                print(f"  no section for {symbol} in {member}", file=sys.stderr)
                continue
            safe = "".join(c if c.isalnum() or c in "._" else "_" for c in symbol)
            name = f"{va:08x}_{safe}.obj"
            (outdir / name).write_bytes(build_object(coff, root_sec, symbol, mapped, claimed))
            written.append((va, str(outdir / name), symbol))
            if not args.closure:
                continue
            # Same-member helpers the function branches to.  They are emitted as
            # their own SINGLE-section objects, placed immediately after this
            # one, rather than folded into it: a multi-section object makes LINK
            # lose /ENTRY resolution (see docs/TODO.md).
            claimed.add(root_sec)
            for helper in closure_sections(coff, root_sec, mapped | claimed):
                claimed.add(helper)
                hsym = next(
                    (
                        s["name"]
                        for s in coff.symbols
                        if s["section"] - 1 == helper and s["storage_class"] == 2
                    ),
                    f"helper_{helper}",
                )
                if hsym in args.skip_helper:
                    continue
                hsafe = "".join(c if c.isalnum() or c in "._" else "_" for c in hsym)
                hname = f"{va:08x}_h{helper}_{hsafe}.obj"
                (outdir / hname).write_bytes(build_object(coff, helper, hsym, set(), set()))
                written.append((None, str(outdir / hname), hsym))

    print(f"wrote {len(written)} objects to {outdir}")
    (outdir / "index.json").write_text(
        json.dumps(
            [
                {"va": (f"0x{v:x}" if v is not None else None), "obj": o, "symbol": s}
                for v, o, s in written
            ],
            indent=1,
        )
    )
    return 0


if __name__ == "__main__":
    sys.exit(main())
