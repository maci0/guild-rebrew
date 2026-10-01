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
        # Indexed by COFF symbol-table ENTRY index, not by position: a
        # relocation's symbol index counts the AUX records too, so a compacted
        # list makes every index past an AUX record wrong, and
        # `remap.get(symidx, 0)` then silently emits symbol 0 -- the object's
        # own section symbol -- so the call jumps to its own start.
        # (fclose.obj sec 3's four relocations name entries 13..16 while a
        # compacted list held 14 symbols.)
        self.symbols = [None] * self.nsyms
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
            self.symbols[i] = {
                "raw_name": raw,
                "name": name,
                "value": struct.unpack_from("<I", entry, 8)[0],
                "section": struct.unpack_from("<h", entry, 12)[0],
                "type": struct.unpack_from("<H", entry, 14)[0],
                "storage_class": entry[16],
                "naux": entry[17],
                "aux": data[off + 18 : off + 18 + entry[17] * 18],
            }
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


def masked_body(obj: bytes, sec: dict) -> bytes:
    """Section body with every relocation field zeroed."""
    body = bytearray(obj[sec["raw_ptr"] : sec["raw_ptr"] + sec["raw_size"]])
    for i in range(sec["nreloc"]):
        off = sec["reloc_ptr"] + i * 10
        if off + 10 > len(obj):
            break
        addr = struct.unpack_from("<I", obj, off)[0]
        for k in range(4):
            if addr + k < len(body):
                body[addr + k] = 0
    return bytes(body)


def build_object(coff: Coff, index: int, out_name: str, separate: set[int] | None = None, claimed: set[int] | None = None, closure: bool = False, aliases: set[str] | None = None, extra: set[int] | None = None, emit_commons: bool = False, trim: int | None = None, start: int = 0, promote_statics: bool = False) -> bytes:
    """COFF object for `coff.sections[index]` plus its same-member closure.

    `separate` holds the section indices that are themselves emitted as their
    own object (the member's mapped functions); the closure stops there so the
    sections are not duplicated and stay at their own reference VAs.
    """
    separate = separate or set()
    claimed = claimed if claimed is not None else set()
    # `trim` cuts the ROOT section to the reference function's size.  A member
    # section can be longer than the reference function it was matched to — the
    # 238-byte exsup section carries six reference functions of 34..216 bytes —
    # and emitting all of it for each of them multiplies the over-inclusion.
    if trim is not None:
        trim = min(trim, max(0, coff.sections[index]["raw_size"] - start))
    # Section closure: every .text section reachable from this one through a
    # relocation to a symbol defined in ANOTHER section of the same member.
    # MSVC splits a member's shared tails into separate COMDATs (memmove's
    # LeadUp*/UnwindUp*/TrailUp* family), and leaving them out makes the linker
    # re-pull the whole member and append it after the region.
    need = {index} | set(extra or ())
    # Walk relocations to same-member .text sections.  With --closure the root
    # .text section is a root; a carried data section is *always* a root,
    # because its initialisers name code in the same member (the iob array
    # points at ___endstdio) and leaving that out turns a definition into an
    # undefined reference that re-pulls the whole member from the archive.
    work = list(need) if closure else list(extra or ())
    while work:
        i = work.pop()
        for _va, symidx, _typ in coff.section_relocs(i):
            if symidx >= len(coff.symbols) or coff.symbols[symidx] is None:
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

    # Common symbols (storage class 2, section 0, value = size, e.g.
    # __mbctype:0x101) are allocated by the linker, so no member section
    # defines them and LINK goes to the archive for the whole member.  With
    # --with-data we emit one synthetic .bss holding every common the member
    # declares, each symbol at its aligned offset.
    commons: list[tuple[int, int, int]] = []
    synth_total = 0
    synth_sec = 0
    if emit_commons:
        # Not `extra and emit_commons`: a blob with no sections of its own to
        # emit still declares COMMON symbols, and leaving them at section 0 put
        # a second definition of the same symbol on the link next to the blob
        # that does place it in a synthetic .bss.  LINK resolved the pair
        # first-wins and reported 34 LNK4006, which looked like a placement
        # defect and was not.
        off = 0
        for i, sym in enumerate(coff.symbols):
            if sym is None:
                continue
            if sym["storage_class"] == 2 and sym["section"] == 0 and sym["value"] > 0:
                align = 8 if sym["value"] >= 8 else 4
                off = (off + align - 1) & ~(align - 1)
                commons.append((i, off, sym["value"]))
                off += sym["value"]
        if off:
            synth_total = (off + 3) & ~3
            synth_sec = len(secs) + 1

    # Symbols to keep: every definition in the emitted sections and every
    # symbol referenced by their relocations.
    keep = []
    seen = set()

    def add(i: int):
        if i not in seen:
            seen.add(i)
            keep.append(i)

    for i, sym in enumerate(coff.symbols):
        if sym is None:
            continue
        if sym["section"] > 0 and (sym["section"] - 1) in new_secnum:
            # Never drop the root COMDAT's section symbol: LINK reports a
            # COMDAT without one as "no symbol for comdat section".
            is_sec_sym = sym["storage_class"] == 3 and sym["name"].startswith(".")
            if sym["section"] - 1 == index and start and not is_sec_sym and (
                sym["value"] < start
                or (trim is not None and sym["value"] >= start + trim)
            ):
                continue
            if (
                not start
                and trim is not None
                and sym["section"] - 1 == index
                and sym["value"] >= trim
            ):
                continue
            add(i)

    # A relocation may name a *section* symbol (class 3, ".text") of a COMDAT
    # that is not part of this object.  Leaving that as an external named
    # ".text" leaves LINK with an unresolvable reference, so retarget it at the
    # external function symbol defined in that section.
    first_ext: dict[int, int] = {}
    for i, sym in enumerate(coff.symbols):
        if sym is None:
            continue
        if sym["section"] > 0 and sym["storage_class"] == 2:
            j = sym["section"] - 1
            if j not in first_ext or sym["value"] < coff.symbols[first_ext[j]]["value"]:
                first_ext[j] = i

    def resolve_ref(symidx: int) -> int:
        if symidx >= len(coff.symbols):
            return symidx
        sym = coff.symbols[symidx]
        if sym is None:
            return symidx
        if sym["storage_class"] == 3 and sym["name"].startswith(".") and sym["section"] > 0:
            j = sym["section"] - 1
            if j not in new_secnum and j in first_ext:
                return first_ext[j]
        return symidx

    for i, _off, _sz in commons:
        add(i)

    for i in secs:
        for _va, symidx, _typ in coff.section_relocs(i):
            if i == index and start and (
                _va < start or (trim is not None and _va >= start + trim)
            ):
                continue
            if trim is not None and i == index and _va >= trim:
                continue
            if symidx < len(coff.symbols):
                add(resolve_ref(symidx))

    # Symbol table, renumbered onto the emitted sections.
    common_off = {i: off for i, off, _sz in commons}
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
        value = sym["value"]
        if start and sym["section"] - 1 == index and value >= start:
            value -= start
        if old_i in common_off:
            section_number = synth_sec
            value = common_off[old_i]
        aux = bytearray(sym["aux"])
        # A section-definition AUX record carries the section NUMBER it is
        # associated with (bytes 12..13) when its COMDAT selection is
        # ASSOCIATIVE (5).  Splitting renumbers the sections, and a stale
        # number makes LINK fail its COMDAT pass: "Internal error during
        # ReadSymbolTable" under /OPT:REF.  Remap it, and if the associated
        # section was not emitted, drop back to SELECT_ANY.
        for k in range(sym["naux"]):
            base_aux = k * 18
            if len(aux) < base_aux + 18:
                break
            if aux[base_aux + 14] == 5:
                assoc = aux[base_aux + 12] | (aux[base_aux + 13] << 8)
                newno = new_secnum.get(assoc - 1) if assoc else None
                if newno:
                    aux[base_aux + 12] = newno & 0xFF
                    aux[base_aux + 13] = (newno >> 8) & 0xFF
                else:
                    aux[base_aux + 12] = 0
                    aux[base_aux + 13] = 0
                    aux[base_aux + 14] = 2
        # A member's own statics are file-local, and splitting the member
        # across objects breaks their linkage: `10020943_.text.obj` references
        # `_dststart`/`_dstend`/`_tzapiused` as undefined externals while the
        # object carrying them defines them as class 3, so `/FORCE` resolves
        # the references to RVA 0 and every operand entry through them fails
        # (docs/TODO.md round 137).  Promote the data statics to external so
        # they resolve across the split objects, as the original single object
        # did.  `$`-labels and section symbols stay local.
        storage_class = sym["storage_class"]
        if (
            promote_statics
            and storage_class == 3
            and sym["section"] > 0
            and sym["name"].startswith("_")
            and not sym["name"].startswith("$")
            and not sym["name"].startswith(".")
        ):
            storage_class = 2
        new_symbols += (
            raw
            + struct.pack(
                "<IhHBB",
                value,
                section_number,
                sym["type"],
                storage_class,
                sym["naux"],
            )
            + bytes(aux)
        )

    # Aliases: other CRT members whose section body is byte-identical to this
    # one (_lseek and __write are the same 101 bytes in different members).
    # Exporting all of their names here stops the linker pulling the sibling
    # member just to resolve the other spelling.
    for alias in sorted(aliases or ()):
        off = len(strtab)
        strtab += alias.encode("ascii", "replace") + b"\0"
        new_symbols += (
            b"\0\0\0\0"
            + struct.pack("<I", off)
            + struct.pack("<IhHBB", 0, 1, 0x20, 2, 0)
        )
        entry_count += 1

    # Layout: header, section headers, then (body, relocations) per section,
    # then symbols and the string table.
    hdr_size = 20
    sec_size = 40
    cur = hdr_size + sec_size * (len(secs) + (1 if synth_sec else 0))
    headers = bytearray()
    blobs = bytearray()
    for old in secs:
        sec_old = coff.sections[old]
        # A .bss-style section has PointerToRawData 0 and no bytes in the file:
        # keep its size but emit nothing and do not advance the file cursor.
        uninit = sec_old["raw_ptr"] == 0
        body = b"" if uninit else coff.section_body(old)
        if old == index and (trim is not None or start):
            body = body[start:start + trim] if trim is not None else body[start:]
        size = sec_old["raw_size"] if uninit else len(body)
        relocs = [r for r in coff.section_relocs(old)
                  if not (old == index and (
                      (trim is not None and r[0] >= trim)
                      or (start and (r[0] < start
                                     or (trim is not None and r[0] >= start + trim)))))]
        if uninit:
            body_off = 0
            pad = b""
        else:
            body_off = cur
            cur += len(body)
            pad = b"\0" * ((-cur) % 4)
            cur += len(pad)
        if relocs:
            reloc_off = cur
            blob = b"".join(
                struct.pack(
                    "<IIH",
                    va - start if old == index and start else va,
                    remap.get(resolve_ref(symidx), 0),
                    typ,
                )
                for va, symidx, typ in relocs
            )
            cur += len(blob)
        else:
            reloc_off = 0
            blob = b""
        sec = bytearray(coff.data[coff.sections[old]["off"] : coff.sections[old]["off"] + 40])
        struct.pack_into("<I", sec, 16, size)
        struct.pack_into("<I", sec, 20, body_off)
        struct.pack_into("<I", sec, 24, reloc_off)
        struct.pack_into("<I", sec, 28, 0)
        struct.pack_into("<H", sec, 32, len(relocs))
        struct.pack_into("<H", sec, 34, 0)
        headers += sec
        blobs += body + pad + blob

    if synth_sec:
        synth = bytearray(40)
        synth[0:8] = b".bss\0\0\0\0"
        struct.pack_into("<I", synth, 8, synth_total)
        struct.pack_into("<I", synth, 16, synth_total)
        struct.pack_into("<I", synth, 20, 0)
        struct.pack_into("<I", synth, 24, 0)
        struct.pack_into("<I", synth, 28, 0)
        struct.pack_into("<H", synth, 32, 0)
        struct.pack_into("<H", synth, 34, 0)
        struct.pack_into("<I", synth, 36, 0xC0300080)
        headers += synth

    sym_off = cur
    header = struct.pack(
        "<HHIIIHH",
        coff.machine,
        len(secs) + (1 if synth_sec else 0),
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
            if symidx >= len(coff.symbols) or coff.symbols[symidx] is None:
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
        "--with-data",
        action="store_true",
        help="also carry each member's non-.text sections (.data/.bss/.rdata/"
        ".CRT$*) on the object for its lowest-VA mapped function, so the "
        "member's data symbols have a command-line definition and LINK stops "
        "loading the whole member from the archive",
    )
    ap.add_argument(
        "--drop-data",
        action="append",
        default=[],
        help="member basename whose plain .data is not carried. The split "
        "link's gap blob copies those reference bytes; carrying the section "
        "on the function object places it at the .text order instead",
    )
    ap.add_argument(
        "--trim",
        action="store_true",
        help="cut each emitted section to the reference function's size (the map "
        "records it), so a member section longer than the function it was "
        "matched to stops multiplying the over-inclusion",
    )
    ap.add_argument(
        "--promote-statics",
        action="store_true",
        help="emit `_`-named data statics as external symbols, so a member split "
        "across objects still resolves its own statics (docs/TODO.md round 137)",
    )
    ap.add_argument(
        "--split-rdata",
        action="store_true",
        help="emit a member's `.rdata` sections as their own per-section objects "
        "(same VA, so the index order and the link are unchanged) while keeping "
        ".data/.bss/.CRT$* bundled with the function object.  Separate plain "
        "objects are what the split blob needs: a section whose bytes sit inside "
        "rdata_restore.c's range has to land at its own reference offset, "
        "between two pieces of the blob.  Splitting ALL the data sections "
        "instead perturbs symbol resolution (crt0.obj gets pulled, `_main` "
        "unresolved) - see docs/TODO.md round 130",
    )
    ap.add_argument(
        "--with-commons",
        action="store_true",
        help="(experimental) also emit the member's common symbols as a "
        "synthetic .bss.  The objects this produces are rejected by LINK "
        "today - see docs/TODO.md round 29",
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
    # Grouped by (member, library), not by member alone.  Service packs
    # disagree about individual sections -- sbheap.obj section 34 is
    # `3b c6 72 55` in sp5 and `3b f0 77 55` in sp6 -- so a member can be
    # matched in one pack for one VA and another pack for the next.  Keying by
    # member dropped the per-entry library and emitted whichever pack came
    # first, which is one byte wrong at 0x1001e638.
    want: dict[tuple[str, str], list] = {}
    for e in mapping["matched"]:
        va = int(e["va"], 16)
        if va >= floor:
            want.setdefault((e["member"], e.get("lib") or ""), []).append(
                (va, e["symbol"], e.get("section"), int(e.get("offset", 0)))
            )

    by_name: dict[str, bytes] = {}
    # (library basename, member) -> object, so a map entry that names the
    # library it matched in gets THAT copy.  The service packs disagree on
    # section numbering: popen.obj sec 6 is a 965-byte .text in vc7 and not code
    # at all in 6.0-sp6, and taking the first library's copy emitted nothing.
    by_lib_name: dict[tuple[str, str], bytes] = {}
    alias_index: dict[bytes, set[str]] = {}
    for lp in libs:
        members = ar_members(lp.read_bytes())
        resolve = name_resolver(members)
        key_lib = Path(lp).name
        for raw, obj in members:
            by_name.setdefault(resolve(raw), obj)
            by_lib_name.setdefault((key_lib, resolve(raw)), obj)
            if len(obj) < 20:
                continue
            try:
                coff_tmp = Coff(obj)
            except (struct.error, IndexError):
                continue
            for i, sec in enumerate(coff_tmp.sections):
                if not sec["name"].startswith(b".text") or sec["raw_size"] == 0:
                    continue
                ext = {
                    sym["name"]
                    for sym in coff_tmp.symbols
                    if sym is not None
                    and sym["section"] == i + 1
                    and sym["storage_class"] == 2
                    and not sym["name"].startswith(".")
                }
                if ext:
                    alias_index.setdefault(masked_body(obj, sec), set()).update(ext)

    # Entries whose VA falls inside a section another entry already emits must
    # not be emitted again.  The reference overlaps functions freely: popen's
    # `$L21349` fragment at 0x1001a89c is interior to malloc.obj's 252-byte
    # __malloc, and wpopen's at 0x1001a8fb likewise, while crt0dat's `exit` pair
    # are two separate 17-byte sections that really do tile.  The test uses the
    # EMITTED extent, not the catalog size, or the crt0dat pair would be
    # collapsed.
    map_size = {}
    for e in mapping["matched"]:
        map_size[(e["member"], int(e["va"], 16))] = e.get("size")
    flat = sorted(
        (va, member, lib, symbol, section, offset)
        for (member, lib), funcs in want.items()
        for (va, symbol, section, offset) in funcs
    )
    interior = set()
    frontier = -1
    for va, member, lib, _symbol, section, offset in flat:
        if va < frontier:
            interior.add((member, va))
            continue
        obj_i = by_name.get(member)
        if lib:
            obj_i = by_lib_name.get((lib, member), obj_i)
        end = va
        if obj_i is not None and section:
            try:
                sec_i = Coff(obj_i).sections[section - 1]
                avail = sec_i["raw_size"]
                if (
                    offset
                    and sec_i["name"].startswith(b".text")
                    and offset < avail
                ):
                    avail -= offset
                want_n = map_size.get((member, va))
                end = va + (min(want_n, avail) if want_n else avail)
            except (struct.error, IndexError):
                end = va
        frontier = max(frontier, end)

    written: list[tuple[int | None, str, str]] = []

    def member_external_names(member_name, lib_name, funcs_list):
        """External names defined by this member's mapped sections."""
        obj_i = by_name.get(member_name)
        if lib_name:
            obj_i = by_lib_name.get((lib_name, member_name), obj_i)
        if obj_i is None:
            return set()
        try:
            coff_i = Coff(obj_i)
        except (struct.error, IndexError):
            return set()
        names = set()
        for _va, symbol_i, section_i, _off_i in funcs_list:
            sec_i = resolve_section(coff_i, symbol_i, section_i)
            if sec_i is None:
                continue
            for sym in coff_i.symbols:
                if sym is not None and (
                    sym["section"] == sec_i + 1
                    and sym["storage_class"] == 2
                    and not sym["name"].startswith(".")
                ):
                    names.add(sym["name"])
        return names

    def resolve_section(coff_i, symbol_i, section_i):
        """Which section of THIS copy holds `symbol_i`.

        The map's index is authoritative only for the copy it was matched in.
        The same member in another service pack can number its sections
        differently (and crt0dat.mbctype.obj really does), so fall back to a
        name lookup when the recorded index does not hold that symbol.
        """
        if section_i and 0 < section_i <= len(coff_i.sections) and any(
            s is not None and s["name"] == symbol_i and s["section"] == section_i
            for s in coff_i.symbols
        ):
            return section_i - 1
        for sym in coff_i.symbols:
            if sym is not None and sym["name"] == symbol_i and sym["section"] > 0:
                return sym["section"] - 1
        if section_i and 0 < section_i <= len(coff_i.sections):
            return section_i - 1
        return None

    all_mapped_names = set()
    all_by_member: dict[str, list] = {}
    for (_member, _lib), _funcs in want.items():
        all_mapped_names |= member_external_names(_member, _lib, _funcs)
        all_by_member.setdefault(_member, []).extend(_funcs)

    data_done: set[str] = set()
    for (member, lib), funcs in want.items():
        obj = by_name.get(member)
        if lib:
            obj = by_lib_name.get((lib, member), obj)
        if obj is None:
            print(f"  missing member {member}", file=sys.stderr)
            continue
        coff = Coff(obj)

        def find_section(symbol, section):
            return resolve_section(coff, symbol, section)

        # Every section ANY copy of this member emits, resolved into this copy.
        # A member whose entries were matched in two service packs is emitted as
        # two object groups, and a group that only knew its own sections made
        # the closure pass re-emit the other pack's sections: the sp5 mbctype
        # object carried sp5's `___initmbctable` to 0x10021ec0, displacing the
        # sp6 crtGetACP that belongs there.
        mapped = set()
        for _va, symbol, section, _off in all_by_member[member]:
            sec = find_section(symbol, section)
            if sec is not None:
                mapped.add(sec)
        claimed: set[int] = set()
        data_secs: set[int] = set()
        member_base = member.replace("\\", "/").split("/")[-1].lower()
        drop_data = member_base in {n.lower() for n in args.drop_data}
        if args.with_data:
            for i, sec in enumerate(coff.sections):
                nm = sec["name"].rstrip(b"\0").decode("ascii", "replace")
                # Plain .data of a dropped member is supplied by the gap blob.
                # .bss/.rdata/.CRT$* still have to travel with the function or
                # LINK pulls the whole archive member back in.
                if drop_data and nm.split("$", 1)[0] == ".data":
                    continue
                if nm.startswith((".data", ".bss", ".rdata", ".CRT$")):
                    data_secs.add(i)
        funcs_sorted = sorted(funcs, key=lambda f: f[0])
        sizes = {}
        for e in mapping["matched"]:
            # Keyed by VA, not by (member, lib): the map never lists a VA twice,
            # and an entry with no library recorded still has to contribute its
            # size to whichever pack's group it landed in.
            if e["member"] == member:
                sizes[int(e["va"], 16)] = e["size"]
        # External names defined by the mapped sections of ANY member.  They must
        # not be exported as aliases.  Several CRT bodies are byte-identical
        # across members — lseek.obj, read.obj and write.obj all carry the same
        # 101 bytes, and crt0dat.obj §14/§16 the same 9 — so the alias index
        # lists every spelling for each.  Exporting them all makes several of our
        # objects define the same symbol set, and LINK then keeps one and drops
        # the rest, which is what left the CRT region short at 0x1001e8b4 (101
        # bytes), 0x1001eec1 (101) and elsewhere.
        member_names = all_mapped_names

        for n, (va, symbol, section, offset) in enumerate(funcs_sorted):
            if (member, va) in interior:
                continue
            entry_size = sizes.get(va)
            root_sec = find_section(symbol, section)
            if root_sec is None:
                print(f"  no section for {symbol} in {member}", file=sys.stderr)
                continue
            safe = "".join(c if c.isalnum() or c in "._" else "_" for c in symbol)
            name = f"{va:08x}_{safe}.obj"
            # Slice from the matched symbol's offset only when that makes sense
            # for the section split_coff actually loaded: the map records the
            # section of the FIRST library that matched, and a popen.obj offset
            # valid in vc7's 21-section copy can point past the end of the
            # 9-section 6.0 one.
            root_sec_info = coff.sections[root_sec]
            start = (
                offset
                if (
                    args.trim
                    and offset
                    and root_sec_info["name"].startswith(b".text")
                    and offset < root_sec_info["raw_size"]
                )
                else 0
            )
            if start:
                # A slice carries only the names physically inside it.  The
                # alias index lists every spelling of the WHOLE section, and
                # exporting those from each slice puts the same symbols on
                # several objects, which makes LINK keep one and drop the rest.
                aliases = set()
            else:
                aliases = alias_index.get(
                    masked_body(coff.data, coff.sections[root_sec]), set()
                ) - {symbol} - member_names
            carry = data_secs if n == 0 and member not in data_done else None
            rdata_only = set()
            if carry and args.split_rdata:
                rdata_only = {
                    i
                    for i in carry
                    if coff.sections[i]["name"].startswith(b".rdata")
                }
            (outdir / name).write_bytes(
                build_object(
                    coff, root_sec, symbol, mapped, claimed, False, aliases,
                    # Once per member, not once per (member, library) group:
                    # the packs' data sections hold the same symbols, and a
                    # second copy is a duplicate definition.
                    extra=(set(carry or ()) - rdata_only) or None,
                    emit_commons=args.with_commons,
                    trim=entry_size if args.trim else None,
                    start=start,
                    promote_statics=args.promote_statics,
                )
            )
            for k, i in enumerate(sorted(rdata_only)):
                # Own object, same VA as the function object so the index sort
                # keeps it right behind it and the default link is unchanged.
                # `extra={i}` keeps the closure walk running from the section,
                # which is what pulls the same-member .text its initialisers
                # name (docs/TODO.md round 130).
                dname = f"{va:08x}_{safe}_r{k}.obj"
                (outdir / dname).write_bytes(
                    build_object(
                        coff, i, dname, mapped, claimed, False, set(),
                        extra={i},
                        emit_commons=args.with_commons,
                        promote_statics=args.promote_statics,
                    )
                )
                written.append((va, str(outdir / dname), f"{symbol}_r{k}"))
            if n == 0:
                data_done.add(member)
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
                        if s is not None
                        and s["section"] - 1 == helper
                        and s["storage_class"] == 2
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
