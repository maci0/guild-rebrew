#!/usr/bin/env python3
"""Emit the defining section of every symbol the split set still leaves undefined.

The split set is per-*function*, so a member's unmapped sections are missing
even when the member is mapped.  When a command-line object references a symbol
that only such a section defines (`__cinit` in `crt0dat.obj` section 2,
`__XcptActTab` in `winxfltr.obj` section 1, `__CRT_INIT@12` in `dllcrt0.obj`
section 3, `___xc_a` in `crt0init.obj` section 7, `_DllMain@12` in
`dllmain.obj`), LINK searches the archive, finds the member, and appends the
member's *whole* `.text` after the split-set region.  That is the last
1.6 KB of the CRT overshoot.

This script closes it from the symbol side: read the defined and undefined
externals of every object already on the response file, take the difference,
map each missing symbol to the section that defines it in one of the LIBCMT
variants, and emit that section as its own object (or, for an `ABSOLUTE`
symbol such as `__except_list`, a one-symbol object with section 0xFFFF).

Usage:
    python3 scripts/emit_defs.py --lib ... --rsp build/split_cd6.rsp \\
        --out build/libcmt_defs
then add the objects to the rsp (scripts/make_split_rsp.py --defs).
"""

from __future__ import annotations

import argparse
import json
import os
import re
import shlex
import struct
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from split_coff import Coff, ar_members, build_object, name_resolver  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent

SYM = re.compile(
    r"\[[ 0-9]+\]\(sec\s+(-?\d+)\).*\(scl\s+(\d+)\)\s*\(nx\s+\d+\)\s+\S+\s+(\S+)\s*$")


def object_symbols(path: str) -> tuple[set[str], set[str]]:
    """(defined externals, undefined externals) of one COFF object.

    objdump prints a COFF symbol as `(sec N)`: N > 0 is a definition in that
    section, N == 0 is an undefined external and N == -1 an ABSOLUTE symbol.
    """
    out = subprocess.run(["objdump", "-t", path], capture_output=True, text=True).stdout
    defined, undefined = set(), set()
    for line in out.splitlines():
        m = SYM.search(line)
        if not m or int(m.group(2)) != 2:
            continue
        section = int(m.group(1))
        if section > 0:
            defined.add(m.group(3))
        elif section == 0:
            undefined.add(m.group(3))
    return defined, undefined


def absolute_object(name: str, value: int) -> bytes:
    """A COFF object defining one ABSOLUTE symbol (section number 0xFFFF)."""
    strtab = bytearray(b"\0\0\0\0")
    if len(name) <= 8:
        raw = name.encode("ascii", "replace").ljust(8, b"\0")
    else:
        off = len(strtab)
        strtab += name.encode("ascii", "replace") + b"\0"
        raw = b"\0\0\0\0" + struct.pack("<I", off)
    symbols = raw + struct.pack("<IhHBB", value, -1, 0, 2, 0)
    header = struct.pack("<HHIIIHH", 0x14C, 0, 0, 20, 1, 0, 0)
    struct.pack_into("<I", strtab, 0, len(strtab))
    return bytes(header) + symbols + bytes(strtab)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--lib", action="append", required=True)
    ap.add_argument("--rsp", required=True, help="an rsp listing the objects already linked")
    ap.add_argument("--out", required=True)
    ap.add_argument("--skip", action="append", default=[],
                    help="symbol to leave to the archive (repeatable)")
    args = ap.parse_args()

    libs = []
    for spec in args.lib:
        lp = Path(spec)
        libs.append(lp if lp.is_absolute() else ROOT / lp)
    outdir = Path(args.out)
    outdir.mkdir(parents=True, exist_ok=True)

    rsp_objects = []
    for token in shlex.split((ROOT / args.rsp).read_text()):
        path = token if os.path.isabs(token) else str(ROOT / "build" / token)
        if os.path.exists(path):
            rsp_objects.append(path)

    def scan(paths):
        defined: set[str] = set()
        undefined: set[str] = set()
        for path in paths:
            d, u = object_symbols(path)
            defined |= d
            undefined |= u
        return defined, undefined

    # The definitions cascade: emitting __CRT_INIT@12 introduces a reference to
    # _DllMain@12, so a single pass leaves symbols behind.  Repeat until the
    # set of newly emitted objects adds nothing.
    emitted: list[str] = []
    index: list[dict] = []
    done: set[str] = set()
    for _round in range(6):
        defined, undefined = scan(rsp_objects + emitted)
        missing = sorted(
            s for s in undefined - defined
            # Only C++ string literals are skipped: `?_set_new_handler@@...`
            # is a real import-shaped symbol, and filtering every `?`-prefixed
            # name silently left handler.obj to the archive.
            if not s.startswith(("__imp_", "??_C@"))
            and s not in args.skip and s not in done
        )
        print(f"pass {_round}: {len(undefined)} undefined, {len(defined)} defined, "
              f"{len(missing)} new missing")
        if not missing:
            break
        done.update(missing)

        defs: dict[str, tuple[str, int]] = {}   # symbol -> (member name, section)
        absolutes: dict[str, int] = {}
        for lp in libs:
            ar = ar_members(lp.read_bytes())
            resolve = name_resolver(ar)
            for raw, obj in ar:
                name = resolve(raw)
                try:
                    coff = Coff(obj)
                except (struct.error, IndexError):
                    continue
                for sym in coff.symbols:
                    if (
                        sym is None
                        or sym["storage_class"] != 2
                        or sym["name"] not in missing
                    ):
                        continue
                    if sym["section"] == -1:
                        absolutes.setdefault(sym["name"], sym["value"])
                    elif sym["section"] > 0:
                        defs.setdefault(sym["name"], (name, sym["section"] - 1))

        # One object per (member, section): build_object emits every symbol the
        # section defines, so two symbols in the same section must not produce
        # two files with the same name (the second would overwrite the first).
        groups: dict[tuple[str, int], str] = {}
        for sym, key in sorted(defs.items()):
            groups.setdefault(key, sym)
        for (name, sec), sym in sorted(groups.items()):
            obj = None
            for lp in libs:
                ar = ar_members(lp.read_bytes())
                resolve = name_resolver(ar)
                for raw, data in ar:
                    if resolve(raw) == name:
                        obj = data
                        break
                if obj:
                    break
            if obj is None:
                continue
            coff = Coff(obj)
            safe = re.sub(r"[^A-Za-z0-9._]", "_", name.split("\\")[-1])
            fname = f"def_{safe}_s{sec}.obj"
            path = outdir / fname
            path.write_bytes(build_object(coff, sec, sym, set(), set(), False, None))
            emitted.append(str(path))
            index.append({"symbol": sym, "obj": str(path)})
        for sym, value in sorted(absolutes.items()):
            if sym in defs:
                continue
            fname = f"abs_{re.sub(r'[^A-Za-z0-9._]', '_', sym)}.obj"
            path = outdir / fname
            path.write_bytes(absolute_object(sym, value))
            emitted.append(str(path))
            index.append({"symbol": sym, "obj": str(path)})

    written = len(emitted)
    index = []
    (outdir / "index.json").write_text(json.dumps(index, indent=1))
    print(f"wrote {written} definition objects to {outdir}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
