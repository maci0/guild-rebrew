#!/usr/bin/env python3
"""Extract each tracked `.data` symbol into its own object, ordered by reference VA.

Why (round 40).  `server.dll`'s `.data` has to come out of the linker laid out
as the reference has it, and nothing else achieves that: `make_split_rsp.py`
routes `data_globals.c.obj` and `link_stubs.c.obj` into fixed buckets near the
end of the link line (round 38), so their data lands wherever those buckets
fall.  Adding correctly-sized objects to the tree makes the file *worse*
(rounds 26, 33, 37) because a correct object inside a wrongly-ordered section
still has the wrong absolute address.

The enabling fact is that `.data` carries **zero relocations** (round 39): the
data holds the reference's addresses as *literal constants*, so a symbol can be
lifted out of its translation unit as a plain byte copy, with nothing to fix
up.  Each symbol then becomes its own command-line object, and the objects are
ordered by the reference address the metadata already records.

This script does step 1 and 2 -- extract, and emit an ordered response-file
fragment.  Step 3 (stripping the original `.data`/`.bss` out of the game objects
so only the extracted copies contribute) is `--strip`, and is a byte-level COFF
edit of the kind `flatten_comdat.py` already performs for a different section.

Usage:
    python3 scripts/emit_data_symbols.py --out-dir build/data_split \\
        --out-rsp build/split_poc/rsp_data.rsp --report
"""

from __future__ import annotations

import argparse
import json
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from split_coff import Coff  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
COMDAT = 0x1000
#: .data is initialised, read/write data on the 32-bit target.
DATA_CHARS = 0xC0300040


def tracked_data() -> dict[str, tuple[int, int]]:
    """name -> (reference VA, size), for `.data` entries that carry a size."""
    import tomllib
    with open(ROOT / "src" / "rebrew-data.toml", "rb") as fh:
        meta = tomllib.load(fh)
    out: dict[str, tuple[int, int]] = {}
    for key, val in meta.items():
        if not isinstance(val, dict) or val.get("section") != ".data":
            continue
        name, size = val.get("name"), val.get("size")
        if not name or not isinstance(size, int) or size <= 0:
            continue
        _, sep, addr = str(key).rpartition(".")
        if not sep:
            continue
        try:
            out[name] = (int(addr, 16), size)
        except ValueError:
            continue
    return out


#: bytes per element for the declarator types the tree uses.  Anything else
#: (a struct, a function pointer typedef) falls back to the in-object bound.
ELEM_SIZE = {"char": 1, "signed char": 1, "unsigned char": 1,
             "short": 2, "unsigned short": 2, "int": 4, "unsigned int": 4,
             "long": 4, "unsigned long": 4, "float": 4, "double": 8,
             "void*": 4, "DWORD": 4, "BOOL": 4, "LPVOID": 4, "BYTE": 1, "WORD": 2}

# The type may be a function-pointer declarator -- `int(__cdecl* name[106])(...)`
# -- so parentheses have to be allowed, not just identifiers, spaces and `*`.
_DECL = re.compile(
    r"(?m)^\s*(?!extern\b)(?P<type>[A-Za-z_][\w ()\*]*?)\b(?P<name>[A-Za-z_]\w*)"
    r"\s*\[(?P<n>0x[0-9a-fA-F]+|\d+)\]")


def declared_sizes() -> dict[str, int]:
    """name -> declared byte size, from the array bounds in the sources.

    This is the ground truth for what CL emitted, and the only model that gets
    every case right: the metadata says `g_dispatch_table` is 4 bytes and the
    object implies 4, while `int g_dispatch_table[106]` says 424 -- the real
    extent.  `_DECL` opens with `(?!extern\\b)`, so an extern declaration can
    never supply a size: only a definition has storage.  (This docstring once
    claimed link_stubs.c declares `g_connections[0x1321320]`; it declares
    `0x264264`, and the claim was wrong for five rounds.)
    """
    out: dict[str, int] = {}
    for p in (ROOT / "src").rglob("*.c"):
        try:
            t = p.read_text(errors="ignore")
        except OSError:
            continue
        for line in t.splitlines():
            if line.split("//")[0].strip().endswith("{") and "=" not in line:
                continue
            m = _DECL.match(line.split("//")[0].strip())
            if not m:
                continue
            raw_type = m.group("type").strip()
            base = raw_type.rstrip("*").strip()
            elem = ELEM_SIZE.get(base)
            if elem is None and ("(*" in raw_type or base.endswith("*")
                                 or "__cdecl" in raw_type or "__stdcall" in raw_type):
                elem = 4          # callback / function-pointer slot
            if elem is None:
                continue
            try:
                n = int(m.group("n"), 0)
            except ValueError:
                continue
            out.setdefault(m.group("name"), n * elem)
    return out


def symbol_owners(objs: list[str], build: Path) -> dict[str, str]:
    """symbol name -> the object that defines it."""
    out: dict[str, str] = {}
    for rel in objs:
        p = build / rel
        if not p.exists():
            p = ROOT / rel
        if not p.exists():
            continue
        try:
            coff = Coff(p.read_bytes())
        except Exception:
            continue
        for s in coff.symbols:
            if s and s["storage_class"] in (2, 3):
                out.setdefault(s["name"].lstrip("_"), Path(rel).name)
    return out


def defined_everywhere(objs: list[str], build: Path) -> set[str]:
    """Every symbol name the listed objects actually define.

    The metadata tracks 203 `.data` entries for objects the tree deleted long
    ago (round 41/42) -- they survive only as `extern char x[1];` in
    rebrew_globals.h.  They must not act as extent boundaries, or they split
    two real objects and the extraction swallows the gap between them.  The
    metadata is tool-owned, so filtering here is the fix that needs no upstream
    change.
    """
    names: set[str] = set()
    for rel in objs:
        p = build / rel
        if not p.exists():
            p = ROOT / rel
        if not p.exists():
            continue
        try:
            coff = Coff(p.read_bytes())
        except Exception:
            continue
        for s in coff.symbols:
            if s and s["storage_class"] in (2, 3):
                names.add(s["name"].lstrip("_"))
    return names


def section_bytes(coff: Coff, index: int) -> bytes:
    s = coff.sections[index]
    return coff.data[s["raw_ptr"]:s["raw_ptr"] + s["raw_size"]]


def build_data_object(name: str, body: bytes) -> bytes:
    """A one-symbol, non-COMDAT `.data` object.  No relocations: the data holds
    literal addresses (round 39), so the bytes are already final."""
    strtab = bytearray(b"\0\0\0\0")

    def name_bytes(n: str) -> bytes:
        if len(n) <= 8:
            return n.encode("ascii").ljust(8, b"\0")
        o = len(strtab)
        strtab.extend(n.encode("ascii") + b"\0")
        return b"\0\0\0\0" + struct.pack("<I", o)

    # An all-zero body belongs in .bss, not .data.  These objects stand in for
    # COMMON symbols, which the linker pools UNINITIALISED: emitting them as
    # initialised `.data` adds their bytes to the file, and the first attempt at
    # the COMMON emit produced a 5.2 MB DLL against a 286,720 B reference.
    is_bss = not any(body)
    secname = b".bss\0\0\0\0" if is_bss else b".data\0\0\0"
    # The raw bytes are in the object either way, so every offset below is
    # 20 + 40 + len(body); only the characteristics say whether the section
    # counts as uninitialised.  Mixing the two conventions gives a symbol table
    # that starts in the middle of the body, which LINK rejects.
    symtab = bytearray()
    symtab += name_bytes(secname.rstrip(b"\0").decode()) + struct.pack("<IHHBB", 0, 1, 0, 3, 0)
    symtab += name_bytes(name) + struct.pack("<IHHBB", 0, 1, 0, 2, 0)
    sec = bytearray(40)
    sec[0:8] = secname
    struct.pack_into("<I", sec, 8, len(body))          # VirtualSize
    struct.pack_into("<I", sec, 16, len(body))         # SizeOfRawData
    struct.pack_into("<I", sec, 20, 20 + 40)           # PointerToRawData
    struct.pack_into("<I", sec, 24, 20 + 40 + len(body))
    # Uninitialized sections keep their bytes in the object -- LINK seeks the
    # section's VirtualSize on disk and fails LNK1106 "cannot seek" when
    # SizeOfRawData is 0, and MSVC's own .bss sections behave the same.  The
    # uninitialized flag is what keeps them out of the image.
    struct.pack_into("<I", sec, 36, 0xC0000080 if is_bss else DATA_CHARS & ~COMDAT)
    struct.pack_into("<I", strtab, 0, len(strtab))
    header = struct.pack("<HHIIIHH", 0x14C, 1, 0, 20 + 40 + len(body), 2, 0, 0)
    return header + bytes(sec) + body + bytes(symtab) + bytes(strtab)


DROP_SECTIONS = (b".data", b".bss")


def strip_data_sections(obj: bytes, provided: set[bytes] | None = None,
                        drop_sections: set[int] | None = None,
                        drop_common: bool = True,
                        common_names: set[bytes] | None = None,
                        extra_names: set[bytes] | None = None) -> bytes:
    """Return `obj` without its .data/.bss, their symbols now undefined.

    Step 2 of the emit (round 48).  A data symbol that stays defined in its
    translation unit would still contribute to the section, so the extracted
    one-symbol objects could not take over.  Symbols that lived in a dropped
    section -- and every COMMON one, which the linker allocates itself -- are
    rewritten as undefined externals of the same name, so the extracted object
    becomes the only definition.

    The file is rebuilt rather than patched: dropping a section renumbers every
    later one and moves their raw data, and a symbol's section index has to
    follow, so a byte-level edit is not enough.
    """
    nsec = struct.unpack_from("<H", obj, 2)[0]
    optsz = struct.unpack_from("<H", obj, 16)[0]
    sec_off = 20 + optsz
    sym_ptr = struct.unpack_from("<I", obj, 8)[0]
    sym_cnt = struct.unpack_from("<I", obj, 12)[0]

    secs = []
    for i in range(nsec):
        h = obj[sec_off + i * 40: sec_off + (i + 1) * 40]
        name = h[:8].rstrip(b"\0")
        vsz, va, rsz, rptr, rlp, llp, nrel, nln, chars = struct.unpack_from("<IIIIIIHHI", h, 8)
        secs.append([name, vsz, va, rsz, rptr, rlp, llp, nrel, nln, chars])

    # A data section may only be dropped when the extracted fragment supplies
    # every symbol in it.  The zlib objects are built by the same CMake target as
    # the game, so they were being stripped too -- and their `.data`
    # (`?my_version`, a `??_C@` string) is not a tracked global, so those symbols
    # vanished and the link reported them unresolved.  `provided` is the
    # fragment's symbol set; pass None to strip unconditionally.
    droppable = {i for i, sc in enumerate(secs) if sc[0] in DROP_SECTIONS}
    if drop_sections is not None:
        # Explicit set, 0-based section indices from the section emitter's
        # manifest.  This is the section-level route (round 86): it drops the
        # sections the emit actually owns, so the per-symbol coverage rule below
        # -- which the 172-object fragment could not satisfy -- never applies.
        droppable = {i for i in drop_sections if i < len(secs)}
    if provided is not None and drop_sections is None:
        body_ = Coff(obj)
        for i in sorted(droppable):
            owned = {(s["name"].encode() if isinstance(s["name"], str) else s["name"])
                     for s in body_.symbols
                     if s and s["storage_class"] in (2, 3) and s["section"] == i + 1}
            if owned - provided:
                droppable.discard(i)          # fragment does not cover it
    keep = [i for i in range(len(secs)) if i not in droppable]
    # The section table stores names with their NUL padding stripped while
    # `sym_name` returns the raw 8-byte field, so both sides are rstripped
    # before comparing.  Without this the comparison never matched and every
    # dropped section symbol survived as an undefined external literally named
    # ".data"/".bss" -- which LINK reported as LNK2001 unresolved externals and
    # then as an internal ReadSymbolTable error.
    all_secnames = {sc[0].rstrip(b"\0") for sc in secs}
    # old 1-based section number -> new 1-based, or 0 for a dropped section
    remap = {}
    for new_i, old_i in enumerate(keep):
        remap[old_i + 1] = new_i + 1
    dropped = {old_i + 1 for old_i in droppable}

    old_strtab = sym_ptr + sym_cnt * 18

    def sym_name(raw: bytes) -> bytes:
        """Resolve a symbol's name to plain bytes.

        A long name is stored as four NUL bytes plus an offset into the
        *object's own* string table.  Copying that 8-byte field verbatim into
        the rewritten object (it is exactly 8 bytes, so the writer treated it as
        a short name) produced a symbol table full of one-character names.
        """
        if raw[:4] == b"\0\0\0\0":
            off = struct.unpack_from("<I", raw, 4)[0]
            end = obj.index(b"\0", old_strtab + off)
            return obj[old_strtab + off:end]
        return raw

    # walk the symbol table, honouring aux records
    syms = []
    i = 0
    while i < sym_cnt:
        off = sym_ptr + i * 18
        raw = obj[off:off + 18]
        naux = raw[17]
        sec = struct.unpack_from("<H", raw, 12)[0]
        val = struct.unpack_from("<I", raw, 8)[0]
        cls = raw[16]
        nm_ = sym_name(raw[:8])
        # `common_names` makes the COMMON removal selective: only the named
        # symbols go, so the 86 untracked CRT commons (_g_const_0_001 and the
        # rest) keep their definitions instead of becoming LNK2001.
        if sec == 0 and drop_common:
            if common_names is not None and nm_ not in common_names:
                syms.append((nm_, val, 0, raw[14], cls, b"", 0))
                i += 1 + naux
                continue
        if sec in dropped or (drop_common and sec == 0):
            # A section symbol for a dropped section has no meaning left, and a
            # COMMON symbol is one the linker would allocate itself.  Both go
            # away: the data is supplied by the extracted one-symbol objects.
            # A *section* symbol, identified by its name matching a section
            # name -- NOT by storage class 3, which is also how a file-scope
            # `static` is stored.  Using the class dropped every `static char
            # s_foo[]` in the tree instead of making it undefined, which the
            # verifier caught as ~20 genuinely lost symbols.
            if nm_.rstrip(b"\0") in all_secnames:
                i += 1 + naux
                continue
            syms.append((nm_, 0, 0, 0, 2, b"", 0))   # undefined external
        elif extra_names and nm_ in extra_names:
            # A symbol the emit relocates: its section stays (other symbols in it
            # are fine where they are) but this one is now supplied by the
            # emitted object, so it becomes undefined here.  Without this the
            # original wins and the emitted copy is the LNK4006 "second
            # definition ignored".
            syms.append((nm_, 0, 0, 0, 2, b"", 0))
        else:
            # A COMDAT section's symbol MUST carry one aux record; dropping
            # it makes LINK fail with LKN1162 "expected aux symbol for comdat
            # section", so the original aux bytes are copied verbatim.
            # ALL of a symbol's aux records, not just the first: `.file` is
            # storage class FILE with six of them, and the object file name
            # spans all six.  Declaring naux=1 while writing one record leaves
            # the name truncated mid-string, which is a plausible source of
            # LINK's "Internal error during ReadSymbolTable".
            aux = b""
            if naux:
                aux = obj[sym_ptr + (i + 1) * 18: sym_ptr + (i + 1 + naux) * 18]
            syms.append((nm_, val, remap.get(sec, sec), raw[14], cls, aux, naux))
        i += 1 + naux

    # Lay the kept sections out consecutively -- raw data AND relocation
    # records.  Dropping the relocations is not a detail: every `.text` section
    # here carries 5-18 of them, and a section that still has its code but no
    # relocations links with zero operands (and LINK aborts with "Internal
    # error during ReadSymbolTable").  The round-50 failure was this.
    body = bytearray()
    new_secs = []
    for old_i in keep:
        _, vsz, va, rsz, rptr, rlp, llp, nrel, nln, chars = secs[old_i]
        data = obj[rptr:rptr + rsz] if rsz else b""
        new_secs.append((secs[old_i][0], vsz, va, len(data),
                         20 + 40 * len(keep) + len(body),
                         0, 0, 0, 0, chars))
        body += data
        if nrel:
            rstart = len(body)
            body += obj[rlp:rlp + nrel * 10]
            row = list(new_secs[-1])
            # PointerToRelocations is a FILE offset, not a body-relative one:
            # a body-relative value points into the section headers and LINK
            # then reads a bogus fixup (LNK1190 "invalid fixup found").
            row[5] = 20 + 40 * len(keep) + rstart
            row[7] = nrel                          # NumberOfRelocations
            new_secs[-1] = tuple(row)

    strtab = bytearray(b"\0\0\0\0")

    def nm(n: bytes) -> bytes:
        if len(n) <= 8:
            return n.ljust(8, b"\0")
        o = len(strtab)
        strtab.extend(n + b"\0")
        return b"\0\0\0\0" + struct.pack("<I", o)

    symtab = bytearray()
    # No separate loop for section symbols here: the walk above already emits
    # them (it does not skip storage class 3), and adding them a second time
    # duplicated every one of them, which is what garbled the table.
    nsym_out = 0
    for name, val, sec, typ, cls, aux, aux_len in syms:
        naux_out = aux_len
        symtab += nm(name) + struct.pack("<IHHBB", val, sec, typ, cls, naux_out)
        if naux_out:
            symtab += aux
        nsym_out += 1 + naux_out
    struct.pack_into("<I", strtab, 0, len(strtab))

    hdr = struct.pack("<HHIIIHH", 0x14C, len(new_secs), 0,
                      20 + 40 * len(new_secs) + len(body), nsym_out, 0, 0)
    sec_bytes = b"".join(
        sc[0].ljust(8, b"\0") + struct.pack("<IIIIIIHHI", *sc[1:]) for sc in new_secs)
    return hdr + sec_bytes + bytes(body) + bytes(symtab) + bytes(strtab)


def strip_and_verify(objs: list[str], build: Path, out: Path, verify: bool,
                     provided: set[bytes] | None = None) -> list[str]:
    """Strip every rsp object's .data/.bss, and check the result against the original.

    A rewritten symbol table that "still links" is not evidence of correctness
    (round 14: four green numbers on a broken image), so the check is explicit:
    every original name must survive, every symbol that lived in a kept section
    must still live in the section that now carries it, and every dropped one
    must be undefined.
    """
    problems: list[str] = []
    for rel in objs:
        src = build / rel
        if not src.exists():
            src = ROOT / rel
        if not src.exists():
            continue
        raw = src.read_bytes()
        new = strip_data_sections(raw, provided)
        (out / Path(rel).name).write_bytes(new)
        if not verify:
            continue
        # The stream check round 50 needed and did not have: walking the
        # rewritten symbol table (honouring aux records) must land exactly on
        # the string table, whose first dword is its own size.  A count or aux
        # mismatch desynchronises the reader, and LINK reports it only as
        # "Internal error during ReadSymbolTable".
        sp = struct.unpack_from("<I", new, 8)[0]
        sc_ = struct.unpack_from("<I", new, 12)[0]
        j, seen = 0, 0
        while j < sc_:
            if sp + (j + 1) * 18 > len(new):
                problems.append(f"{Path(rel).name}: symbol table runs past EOF")
                break
            na = new[sp + j * 18 + 17]
            j += 1 + na
            seen += 1
        if sp + j * 18 > len(new):
            problems.append(f"{Path(rel).name}: aux chain desynchronised "
                            f"({j} records, file {len(new)} B)")
        else:
            size = struct.unpack_from("<I", new, sp + j * 18)[0]
            if size == 0 or sp + j * 18 + size > len(new) + 1:
                problems.append(f"{Path(rel).name}: string table misplaced "
                                f"(declared {size} B at {sp + j * 18:#x})")
        try:
            a, b = Coff(raw), Coff(new)
        except Exception as exc:                       # noqa: BLE001
            problems.append(f"{Path(rel).name}: unparsable after strip ({exc})")
            continue
        # Coff decodes symbol names to str but leaves section names as bytes,
        # so the "did this name survive" check has to compare like with like.
        secnames = {n.decode("ascii", "replace").rstrip("\0") for n in
                    (s["name"] for s in a.sections)}
        an = {s["name"]: s for s in a.symbols if s}
        bn = {s["name"]: s for s in b.symbols if s}
        # Section symbols for dropped sections are *meant* to disappear; any
        # other name is not.
        missing = sorted(nm_ for nm_ in set(an) - set(bn)
                         if nm_ not in secnames)
        if missing:
            problems.append(f"{Path(rel).name}: lost {missing[:4]}")
        a_secs = {i + 1: s["name"].decode("ascii", "replace").rstrip("\0")
                  for i, s in enumerate(a.sections)}
        b_secs = {i + 1: s["name"].decode("ascii", "replace").rstrip("\0")
                  for i, s in enumerate(b.sections)}
        for nm_, sy in an.items():
            if nm_ not in bn:
                continue
            was = a_secs.get(sy["section"]) if sy["section"] > 0 else None
            # normalise: the original name may carry the padding NULs
            now = b_secs.get(bn[nm_]["section"]) if bn[nm_]["section"] > 0 else None
            # A symbol either stays in the section it was in, or becomes
            # undefined because the extracted object now supplies it.  A section
            # the fragment does not fully cover is KEPT, so "still in .data" is
            # a correct outcome too; anything else is a relocation of the symbol
            # to a section it never belonged to.
            if now is not None and was is not None and was != now:
                problems.append(f"{Path(rel).name}: {nm_} moved {was!r}->{now!r}")
    return problems


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--rsp", default="build/split_poc/rsp.rsp")
    ap.add_argument("--out-dir", default="build/data_split")
    ap.add_argument("--out-rsp", default="build/split_poc/rsp_data.rsp")
    ap.add_argument("--report", action="store_true")
    ap.add_argument("--debug", action="store_true",
                    help="print why each tracked symbol was skipped")
    ap.add_argument("--strip", metavar="DIR",
                    help="write .data/.bss-stripped copies of the rsp's objects "
                         "into DIR and verify each against its original")
    ap.add_argument("--verify", action="store_true",
                    help="with --strip: re-parse every stripped object and check "
                         "that no name was lost, no kept symbol changed section "
                         "membership, and every dropped one is undefined")
    args = ap.parse_args()

    want_all = tracked_data()
    declared = declared_sizes()
    out_dir = ROOT / args.out_dir
    out_dir.mkdir(parents=True, exist_ok=True)
    rsp_path = ROOT / args.rsp
    rsp_objs = [o for o in rsp_path.read_text().split() if o.endswith(".obj")]
    # the response file is written relative to `build/`, which is also the
    # linker's working directory, so object paths resolve under build/.
    build = rsp_path.parent.parent
    defined = defined_everywhere(rsp_objs, build)
    want = {n: v for n, v in want_all.items() if n in defined}
    dropped = sorted(set(want_all) - set(want))

    objs = rsp_objs
    # Extent comes from the REFERENCE layout: a symbol runs to the next defined
    # symbol's reference address.  The in-object bound is wrong across a gap --
    # it made g_player_slot_overflow_pad swallow g_bss_tail and come out 1.7 MB
    # too large -- and the metadata's `size` is wrong for arrays.
    owner = symbol_owners(rsp_objs, build)
    by_va = sorted((v[0], n) for n, v in want.items() if n in owner)
    next_va: dict[str, int] = {}
    for i, (va, nm) in enumerate(by_va):
        # Cap: the next symbol in the reference that belongs to a DIFFERENT
        # object.  Bounding by the next symbol regardless of owner truncated
        # `g_connections` (20 MB) at `g_player_slot_field`, a field 20 bytes
        # inside it that shares link_stubs.c.
        cap = None
        for va2, nm2 in by_va[i + 1:]:
            if owner[nm2] != owner[nm]:
                cap = va2
                break
        if cap is not None:
            next_va[nm] = cap - va

    emitted: list[tuple[int, str]] = []
    emitted_spans: list[tuple[int, int]] = []
    missing: list[str] = []
    for rel in objs:
        p = build / rel
        if not p.exists():
            p = ROOT / rel
        if not p.exists():
            continue
        try:
            coff = Coff(p.read_bytes())
        except Exception:
            continue
        # COFF symbol records carry 1-based section numbers; `coff.sections` is
        # 0-based, so index with -1.  (Reading it 0-based silently matched
        # .text and extracted nothing.)
        data_syms = []
        for sym in coff.symbols:
            # 3 as well as 2: `static char s_fmt_player_id[] = "..."` and its
            # five siblings are file-scope statics (storage class 3), so a
            # class-2-only filter made every one of them invisible.
            if not sym or sym["storage_class"] not in (2, 3):
                continue
            idx = sym["section"] - 1
            if not (0 <= idx < len(coff.sections)):
                continue
            # CL puts explicitly-uninitialised globals in .bss (no raw bytes on
            # disk) and tentative definitions in COMMON; all three carry data
            # the section must contribute.
            if coff.sections[idx]["name"].rstrip(b"\0") not in (b".data", b".bss"):
                continue
            nm = sym["name"].lstrip("_")
            if nm in want:
                data_syms.append((sym["value"], nm, idx))
        # COMMON symbols have no section to slice, but COFF stores their size
        # in the symbol's value field, and their content is zeros (they are
        # uninitialised).  Most of the tree's data globals are COMMON, so
        # without this branch the extractor sees under half of them.
        for sym in coff.symbols:
            if not sym or sym["storage_class"] not in (2, 3) or sym["section"] != 0:
                continue
            nm = sym["name"].lstrip("_")
            if nm not in want or not sym["value"]:
                continue
            va = want[nm][0]
            # A common symbol's value is its declared size, which is right for a
            # scalar but can still overrun the next object in the reference, so
            # cap it exactly as the section path caps its fallback.
            # Same precedence as the section path: a source-declared array
            # bound is CL's own view and outranks the COMMON symbol's `value`.
            # Without this, removing `= {0}` moved g_connections from the
            # section path to this one, where the value (2,507,364) was capped
            # by next_va down to 20 bytes -- a silent 2.5 MB truncation.
            # A source-declared bound is CL's own view and is used UNCAPPED,
            # exactly as in the section path: `g_player_slot_field` at
            # 0x101deb14 is a *field* 20 bytes inside `g_connections` and lives
            # in a different TU, so next_va caps the 20 MB object at 20 bytes.
            # Only the fallback -- the COMMON symbol's own value -- is capped,
            # because there it is a guess.
            if nm in declared:
                span_c = declared[nm]
            else:
                span_c = sym["value"]
                if nm in next_va:
                    span_c = min(span_c, next_va[nm])
            if span_c <= 0 or any(lo <= va < lo + ln for lo, ln in emitted_spans):
                continue
            stem = f"{va:08x}_{nm}"
            (out_dir / f"{stem}.obj").write_bytes(
                build_data_object("_" + nm, b"\0" * span_c))
            emitted.append((va, f"{Path(args.out_dir).name}/{stem}.obj"))
            # `span`, not `span_c`: a stale name here recorded a leftover value
            # from the section path, and a 64-byte phantom span at
            # 0x10035439 was swallowing g_active_player_count, g_query_limit
            # and g_query_count three objects later.
            emitted_spans.append((va, span_c))
        data_syms.sort()
        # A symbol's extent runs to the next symbol in the same section.  The
        # metadata's `size` cannot be used: it records 4 for
        # `g_dispatch_table`, which is really 106 entries (424 bytes), so
        # trusting it would emit a truncated table.
        # Sorted by OFFSET, not by reference VA: the in-object neighbour is
        # data_syms[i+1][0], so reference order makes the computed span
        # negative for every symbol after a high-offset one (every scalar in
        # link_stubs.c silently vanished).  Offset order also naturally emits a
        # container before the fields it holds, which the span check relies on.
        data_syms.sort()
        for i, (off, nm, idx) in enumerate(data_syms):
            # Extent = the smaller of what the object implies and what the
            # reference allows.  The in-object bound alone lets
            # g_player_slot_overflow_pad swallow g_bss_tail and come out 1.7 MB
            # too big; the reference cap alone truncates g_connections.  A
            # symbol lying strictly inside an already-emitted extent is a field
            # of that object, not a separate one, so it is skipped.
            in_obj = (data_syms[i + 1][0] if i + 1 < len(data_syms)
                      else coff.sections[idx]["raw_size"]) - off
            # Precedence, strongest first:
            #   1. the array bound written in the source -- CL's own view, and
            #      exact for every real array (g_connections 0x1321320,
            #      g_dispatch_table 106, the overflow pad 0x264260);
            #   2. the metadata's size -- right for scalars, wrong for arrays,
            #      but every array is covered by (1), so it never wins there;
            #   3. the in-object bound -- last, because it over-runs badly: a
            #      scalar whose next in-object neighbour is far away swallows
            #      the symbol after it (g_current_season ate
            #      g_active_player_count).
            if nm in declared:
                span = declared[nm]
            elif want[nm][1] > 0:
                span = want[nm][1]
            else:
                span = in_obj
                if nm in next_va:
                    span = min(span, next_va[nm])
            va_here = want[nm][0]
            inside = [(lo, ln) for lo, ln in emitted_spans if lo <= va_here < lo + ln]
            if inside:
                if args.debug:
                    print(f"  skip {nm} @{va_here:#x}: inside span "
                          f"{inside[0][0]:#x}+{inside[0][1]}", file=sys.stderr)
                continue
            end = off + span
            if end > len(section_bytes(coff, idx)) and idx < len(coff.sections) \
                    and coff.sections[idx]["name"].rstrip(b"\0") == b".data":
                end = len(section_bytes(coff, idx))   # clamp to the section
            if coff.sections[idx]["name"].rstrip(b"\0") == b".bss":
                # .bss has no raw bytes on disk (raw_size is 0), so there is
                # nothing to slice: its extent is known, its content is zeros.
                body = b"\0" * (end - off)
            else:
                body = section_bytes(coff, idx)[off:end]
            if not body:
                if args.debug:
                    print(f"  skip {nm} @{want[nm][0]:#x}: empty body "
                          f"(off={off} span={span} sec={coff.sections[idx]['name']!r})",
                          file=sys.stderr)
                continue
            va = want[nm][0]
            stem = f"{va:08x}_{nm}"
            (out_dir / f"{stem}.obj").write_bytes(build_data_object("_" + nm, body))
            emitted.append((va, f"{Path(args.out_dir).name}/{stem}.obj"))
            # This append was missing entirely, so the field-skip list held only
            # the COMMON branch's entries.
            emitted_spans.append((va, span))
    if args.strip:
        provided = {n.encode() for n in want}
        out = ROOT / args.strip
        out.mkdir(parents=True, exist_ok=True)
        bad = strip_and_verify(objs, build, out, args.verify or True, provided)
        print(f"stripped {len(objs)} object(s) into {args.strip}: "
              f"{'all verified' if not bad else str(len(bad)) + ' MISMATCH(ES)'}",
              file=sys.stderr)
        if bad:
            for line in bad[:10]:
                print("   " + line, file=sys.stderr)
            return 1

    emitted = sorted(dict((v, o) for v, o in emitted).items())
    emitted = [(v, o) for v, o in emitted]
    (ROOT / args.out_rsp).write_text(
        "\n".join(o for _v, o in emitted) + ("\n" if emitted else ""))
    if args.report:
        print(f"tracked .data symbols: {len(want_all)}; defined in the link: "
              f"{len(want)}; ignored deleted-object placeholders: {len(dropped)}",
              file=sys.stderr)
        print(f"extracted: {len(emitted)}  -> {args.out_rsp}", file=sys.stderr)
        if missing:
            print(f"not found: {len(missing)}", file=sys.stderr)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
