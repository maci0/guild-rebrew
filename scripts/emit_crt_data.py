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
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from split_coff import Coff, ar_members, build_object, name_resolver  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent

# (member, .data ordinal among that member's .data sections, tag)
# charmax is the last bytes of crt0msg's table, not a separate contribution.
# Preserve the archive section alignments; placement differences remain visible.
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
    ("lconv.obj", 0, "lconv"),
    ("constpow.obj", 0, "constpow"),
]

def member_object(lib: Path, stem: str) -> bytes:
    raw_ar = ar_members(lib.read_bytes())
    resolve = name_resolver(raw_ar)
    for raw, obj in raw_ar:
        name = resolve(raw).replace("\\", "/").split("/")[-1].lower()
        if name == stem:
            return obj
    raise SystemExit(f"{stem} not in {lib}")


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
    for n, (stem, ordinal, tag) in enumerate(ORDER):
        coff = Coff(member_object(lib, stem))
        sections = data_sections(coff)
        if ordinal >= len(sections):
            raise SystemExit(f"{stem} has no .data ordinal {ordinal}")
        index = sections[ordinal]
        path = out / f"crt_{n:02d}_{tag}.obj"
        extra = {
            sym["section"] - 1
            for sym in coff.symbols
            if sym is not None and sym["name"] == "___lconv_static_null"
            and sym["section"] > 0
        } if tag == "lconv" else None
        blob = bytearray(
            build_object(
                coff, index, tag, set(), set(), False, None, extra, False, None, 0, True
            )
        )
        if tag == "lc_time_c":
            native = ROOT / "build/CMakeFiles/server_dll.dir/src/crt_region/locale_time_table.c.obj"
            blob = bytearray(native.read_bytes())
        path.write_bytes(blob)
        for sym in coff.symbols:
            if sym is None or sym["section"] != index + 1:
                continue
            if sym["name"].startswith(".") or sym["name"].startswith("$"):
                continue
            if sym["storage_class"] in (2, 3):
                skip.append(sym["name"])
        print(f"wrote {path.name} from {stem} .data[{ordinal}]")
    native_strings = ROOT / "build/CMakeFiles/server_dll.dir/src/crt_region/locale_time_strings.c.obj"
    locale_dir = out / "locale_rdata"
    locale_dir.mkdir(exist_ok=True)
    (locale_dir / "locale_time_strings.obj").write_bytes(native_strings.read_bytes())
    native_constants = ROOT / "build/CMakeFiles/server_dll.dir/src/crt_region/game_float_constants.c.obj"
    (locale_dir / "game_float_constants.obj").write_bytes(native_constants.read_bytes())
    (out / "crt_99_lc_time_strs.obj").unlink(missing_ok=True)
    (out / "skip.txt").write_text("".join(s + "\n" for s in skip))
    print(f"{len(skip)} symbols for emit_defs --skip")
    return 0


if __name__ == "__main__":
    sys.exit(main())
