#!/usr/bin/env python3
"""Emit the LIBCMT .data sections that sit in the reference before the tail.

The split link's gap blob copies reference .data from wherever
g_data_restore_gap lands. That is the answer key when the blob starts in
the LIBCMT band (before the historical tail at 0xd274). These sections
match that band; linking them, in reference order, is what fills it.

Usage:
    python3 scripts/emit_crt_data.py --lib .scratch/libcmt/LIBCMT.sp6.LIB \\
        --out build/split_poc/crt_data
"""

from __future__ import annotations

import argparse
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from split_coff import Coff, ar_members, build_object, name_resolver  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent

# (member, .data ordinal among that member's .data sections, tag)
# charmax is the last bytes of crt0msg's table, not a separate contribution.
# The 8 bytes between winxfltr and intrncvt are alignment: intrncvt's library
# section is only 8-aligned, so the emitted object is raised to 16 and lands
# on 0xd130. mbctype then ends at 0xd258. lc_time_c ends at 0xd30c; lconv and
# constpow are the same kind of 8-aligned library section, raised to 16 so
# they land at 0xd310 and 0xd350. Their bytes replace the reference tail.
ORDER = [
    ("cmiscdat.obj", 0, "cmiscdat"),
    ("setlocal.obj", 0, "setlocal"),
    ("ctype.obj", 0, "ctype"),
    ("nlsdata1.obj", 0, "nlsdata1"),
    ("crt0msg.obj", 0, "crt0msg"),
    ("timeset.obj", 0, "timeset"),
    ("tzset.obj", 0, "tzset"),
    ("days.obj", 0, "days"),
    ("winxfltr.obj", 0, "winxfltr"),
    ("intrncvt.obj", 0, "intrncvt"),
    ("mbctype.obj", 0, "mbctype"),
    # ___lc_time_curr is a 4-byte pointer at ___lc_time_c. The table is
    # ALIGN_8, so it has to follow the pointer: 0xd258 + 4 pads to 0xd260.
    ("strftime.obj", 0, "lc_time_curr"),
    ("strftime.obj", 1, "lc_time_c"),
    # 0xd30c is 4 bytes short of a 16-byte boundary; 0xd34c is the same for
    # the next one. ALIGN_16 on these two sections is what produces the pad.
    ("lconv.obj", 0, "lconv"),
    ("constpow.obj", 0, "constpow"),
]

# Library sections whose IMAGE_SCN_ALIGN is 8, placed by the reference on a
# 16-byte boundary. Raised in the emitted object; the bytes are unchanged.
_ALIGN_16 = {"intrncvt", "lconv", "constpow"}

IMAGE_BASE = 0x10000000


def member_object(lib: Path, stem: str) -> bytes:
    raw_ar = ar_members(lib.read_bytes())
    resolve = name_resolver(raw_ar)
    for raw, obj in raw_ar:
        name = resolve(raw).replace("\\", "/").split("/")[-1].lower()
        if name == stem:
            return obj
    raise SystemExit(f"{stem} not in {lib}")


def _reference_rdata() -> tuple[int, bytes]:
    ref = (ROOT / "original/Server/server.dll").read_bytes()
    pe = struct.unpack_from("<I", ref, 0x3C)[0]
    nsec = struct.unpack_from("<H", ref, pe + 6)[0]
    opt = struct.unpack_from("<H", ref, pe + 20)[0]
    off = pe + 24 + opt
    for _ in range(nsec):
        if ref[off:off + 6] == b".rdata":
            va = struct.unpack_from("<I", ref, off + 12)[0]
            rs, rp = struct.unpack_from("<II", ref, off + 16)
            return va, ref[rp:rp + rs]
        off += 40
    raise SystemExit("reference has no .rdata")


def _string_vas(pairs: list[tuple[str, bytes]]) -> list[tuple[str, int]]:
    """VA of each locale string already resident in reference .rdata.

    The split link's .rdata blob holds these bytes. Defining the COMDAT
    names as absolutes lets ___lc_time_c's relocs resolve onto them. Leaving
    the names undefined pulls strftime.obj, and with it the member's .text.
    "Sat" and "Dec" also occur earlier in .rdata; the locale table is the
    span covered by the strings that occur once.
    """
    rva, blob = _reference_rdata()
    located: dict[str, list[int]] = {}
    for name, body in pairs:
        if name in located:
            continue
        hits: list[int] = []
        start = 0
        while True:
            found = blob.find(body, start)
            if found < 0:
                break
            hits.append(found)
            start = found + 1
        if not hits:
            raise SystemExit(f"{name} ({body!r}) is not in reference .rdata")
        located[name] = hits
    unique = [hits[0] for hits in located.values() if len(hits) == 1]
    if not unique:
        raise SystemExit("no unique locale string in reference .rdata")
    lo, hi = min(unique), max(unique)
    out: list[tuple[str, int]] = []
    for name, hits in located.items():
        if len(hits) == 1:
            chosen = hits[0]
        else:
            inside = [h for h in hits if lo <= h <= hi]
            if len(inside) != 1:
                raise SystemExit(
                    f"{name} hits {[hex(h) for h in hits]} "
                    f"against locale span {lo:#x}-{hi:#x}"
                )
            chosen = inside[0]
        out.append((name, IMAGE_BASE + rva + chosen))
    return out


def _absolute_symbols(pairs: list[tuple[str, int]]) -> bytes:
    """One COFF object defining each (name, VA) as an external absolute."""
    strtab = bytearray(b"\0\0\0\0")
    symbols = bytearray()
    for name, value in pairs:
        if len(name) <= 8:
            raw = name.encode("ascii").ljust(8, b"\0")
        else:
            off = len(strtab)
            strtab += name.encode("ascii") + b"\0"
            raw = b"\0\0\0\0" + struct.pack("<I", off)
        symbols += raw + struct.pack("<IhHBB", value & 0xFFFFFFFF, -1, 0, 2, 0)
    struct.pack_into("<I", strtab, 0, len(strtab))
    header = struct.pack("<HHIIIHH", 0x14C, 0, 0, 20, len(pairs), 0, 0)
    return bytes(header) + bytes(symbols) + bytes(strtab)


def data_sections(coff: Coff) -> list[int]:
    out = []
    for i, sec in enumerate(coff.sections):
        name = sec["name"]
        if isinstance(name, bytes):
            name = name.split(b"\0", 1)[0].decode()
        if name == ".data":
            out.append(i)
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--lib", required=True)
    ap.add_argument("--out", required=True)
    args = ap.parse_args()
    lib = Path(args.lib)
    if not lib.is_absolute():
        lib = ROOT / lib
    out = Path(args.out)
    if not out.is_absolute():
        out = ROOT / out
    out.mkdir(parents=True, exist_ok=True)

    skip: list[str] = []
    locale_strings: list[tuple[str, bytes]] = []
    for n, (stem, ordinal, tag) in enumerate(ORDER):
        coff = Coff(member_object(lib, stem))
        sections = data_sections(coff)
        if ordinal >= len(sections):
            raise SystemExit(f"{stem} has no .data ordinal {ordinal}")
        index = sections[ordinal]
        path = out / f"crt_{n:02d}_{tag}.obj"
        blob = bytearray(
            build_object(
                coff, index, tag, set(), set(), False, None, None, False, None, 0, True
            )
        )
        if tag in _ALIGN_16:
            # IMAGE_SCN_ALIGN_16. The library section is only 8-aligned, so
            # the linker would start it 8 bytes early (intrncvt at 0xd128
            # instead of 0xd130, lconv at 0xd308, constpow at 0xd348).
            nsec = struct.unpack_from("<H", blob, 2)[0]
            for si in range(nsec):
                off = 20 + si * 40
                if blob[off:off + 5] == b".data":
                    chars = struct.unpack_from("<I", blob, off + 36)[0]
                    chars = (chars & ~0x00F00000) | 0x00500000
                    struct.pack_into("<I", blob, off + 36, chars)
                    break
        if tag == "lc_time_c":
            # The table's slots name strftime's day/month COMDATs. Those
            # bytes already sit in the .rdata blob. Remember the bodies so
            # the names can be defined as absolutes at those addresses.
            for _va, symidx, _typ in coff.section_relocs(index):
                sym = coff.symbols[symidx]
                if sym is None or sym["section"] <= 0:
                    continue
                locale_strings.append(
                    (sym["name"], coff.section_body(sym["section"] - 1))
                )
        path.write_bytes(blob)
        if tag == "lconv":
            # Defined in the ioinit commons span (split_link.sh), not here.
            # Leaving it for emit_defs would emit lconv's own 1-byte .bss at
            # the wrong address and pull the member's .text.
            skip.append("___lconv_static_null")
        for sym in coff.symbols:
            if sym is None or sym["section"] != index + 1:
                continue
            if sym["name"].startswith(".") or sym["name"].startswith("$"):
                continue
            if sym["storage_class"] in (2, 3):
                skip.append(sym["name"])
        print(f"wrote {path.name} from {stem} .data[{ordinal}]")
    if locale_strings:
        vas = _string_vas(locale_strings)
        abs_path = out / "crt_99_lc_time_strs.obj"
        abs_path.write_bytes(_absolute_symbols(vas))
        print(f"wrote {abs_path.name} ({len(vas)} locale string absolutes)")
    (out / "skip.txt").write_text("".join(s + "\n" for s in skip))
    print(f"{len(skip)} symbols for emit_defs --skip")
    return 0


if __name__ == "__main__":
    sys.exit(main())
