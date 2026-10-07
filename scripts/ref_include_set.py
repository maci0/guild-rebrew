#!/usr/bin/env python3
"""Compute the `/INCLUDE` set that lets the split link run under `/OPT:REF`.

Why (round 11).  The link carries `/OPT:NOREF` to keep every section the
reference has, and that is what leaves 89 unreferenced import thunks
(`jmp dword ptr [IAT]`) in `.text` — 566 of the 642-byte overshoot.  Round 9
showed `/OPT:REF` drops the thunks but also 174 real symbols, so neither flag
alone is the answer.

Measured, on the shipped object set:

    /OPT:NOREF                      .text 0x22ac8   thunks 103   imports 100
    /OPT:REF                        .text 0x18a50   thunks  10   imports  98
    /OPT:REF + /INCLUDE <this set>  .text 0x22870   thunks  11   imports  98

So the thunks land on the reference's 11, `call [abs]` returns to 211 (the
reference's own count), and the overshoot falls 642 -> 42 bytes.

`/INCLUDE` is the only lever: it names a symbol, which forces the section that
defines it, so the dropped game and CRT code comes back while the import
thunks — which nothing references — stay discarded.  The set is not a guess;
it is exactly the symbols a `/OPT:REF` link drops relative to the shipped
`/OPT:NOREF` link, and this script derives it by linking twice and diffing the
two maps.  The import thunks are excluded on purpose: they are the 89 we want
gone.  That exclusion is also why two dead imports (AllocConsole, WS2_32
ord16) come out missing — the reference imports them but never calls them, and
with the thunk discarded `/INCLUDE:__imp_X` is not enough to keep the slot.

Usage:
    python3 scripts/ref_include_set.py --map build/split_poc.map \\
        --rsp build/split_poc/rsp.rsp --workdir build
    # prints one /INCLUDE:<symbol> per line
"""

from __future__ import annotations

import argparse
import os
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from import_thunk_census import imported_names  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
MAPLINE = re.compile(r"^\s*(\d{4}):([0-9a-f]{8})\s+(\S+)\s+([0-9a-f]{8})(?:\s+\S+)?\s+(\S+)\s*$")


def map_symbols(path: str) -> dict[str, str]:
    """symbol -> providing object, from a LINK /MAP file."""
    return {s: o for s, _sec, o in map_rows(path)}


def map_rows(path: str) -> list[tuple[str, str, str]]:
    """(symbol, section number, object) for every public in a LINK /MAP file.

    The section matters: a naive symbol diff over the whole map also yields
    `.rdata` string literals (`??_C@...`), and forcing those with /INCLUDE
    breaks the link with unresolved `??_C@` externals.  Only `.text`
    (section 1) symbols belong in the set.
    """
    rows: list[tuple[str, str, str]] = []
    with open(path, errors="replace") as fh:
        for line in fh:
            m = MAPLINE.match(line)
            if m:
                rows.append((m.group(3), m.group(1), m.group(5)))
    return rows


def probe_link(workdir: str, rsp: str, noref_map: str,
              out_stem: str = "refprobe", includes: list[str] | None = None) -> str:
    """Link the same object set with /OPT:REF and no /INCLUDE; return its map."""
    link_txt = Path(workdir) / "CMakeFiles" / "server_dll.dir" / "link.txt"
    cmd = link_txt.read_text()
    # the probe link runs with cwd=workdir, so the map name is relative to it
    out_map = out_stem + ".map"
    for a, b in (("@CMakeFiles/server_dll.dir/objects1.rsp", "@" + rsp),
                 ("/out:server.dll", f"/out:{out_stem}.dll /MAP:{out_map}"),
                 ("/implib:server.lib", f"/implib:{out_stem}.lib"),
                 ("/OPT:NOREF", "/OPT:REF")):
        cmd = cmd.replace(a, b)
    cmd = re.sub(r" /pdb:[^ ]*", "", cmd)
    if includes:
        cmd = cmd.replace('/OPT:REF', '/OPT:REF ' + ' '.join(includes), 1)
    proc = subprocess.run(cmd, shell=True, cwd=workdir, capture_output=True, text=True)
    if not os.path.exists(Path(workdir) / out_map):
        sys.exit("REF probe link failed:\n" + (proc.stdout + proc.stderr)[-2000:])
    return str(Path(workdir) / out_map)


def _imp_symbol(noreref: dict[str, str], imp: str) -> str | None:
    """`AllocConsole` -> the `__imp__AllocConsole@0` symbol the map knows."""
    for sym in noreref:
        if not sym.startswith("__imp__"):
            continue
        base = sym[len("__imp__"):].split("@")[0]
        if base == imp:
            return sym
    return None


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--map", required=True, help="the shipped /OPT:NOREF map")
    ap.add_argument("--rsp", required=True, help="response file the link uses")
    ap.add_argument("--workdir", default="build")
    ap.add_argument("--noref-binary", help="the /OPT:NOREF build, for import names")
    ap.add_argument("--ref-binary", help="the /OPT:REF probe build")
    ap.add_argument("--keep-import-thunks", action="store_true",
                    help="also force the import thunks (they are dropped by default)")
    args = ap.parse_args()

    noreref = map_symbols(args.map)
    noreref_text = {s for s, sec, _o in map_rows(args.map) if sec == "0001"}
    ref = map_symbols(probe_link(args.workdir, args.rsp, args.map))

    # (a) everything REF drops that is not an import thunk -- forcing these
    #     brings back the 174 real game/CRT symbols.
    dropped = [f"/INCLUDE:{s}" for s in sorted(noreref_text)
               if s not in ref and (args.keep_import_thunks or ".dll" not in noreref[s])]
    for line in dropped:
        print(line)

    # (b) the import slots REF still drops once (a) is applied.  The reference
    # imports a few functions it never calls (AllocConsole, WS2_32 ord16); with
    # their thunks discarded the descriptor entries go too and the import table
    # falls to 98.  Forcing the __imp_ symbol keeps the IAT slot *without*
    # re-adding the thunk, which is exactly the reference's shape.  Forcing the
    # plain name instead (_AllocConsole@0) drags the thunk back, 6 bytes apiece.
    # The comparison is made against a probe that already carries (a), or every
    # import whose caller was dropped would be reported here as well.
    slots: list[str] = []
    if args.noref_binary:
        withinc = probe_link(args.workdir, args.rsp, args.map,
                             out_stem="refwithinc", includes=dropped)
        have_ref = set(imported_names(Path(withinc.replace(".map", ".dll")).read_bytes()))
        have_noref = set(imported_names(Path(args.noref_binary).read_bytes()))
        for imp in sorted(have_noref - have_ref):
            sym = _imp_symbol(noreref, imp)
            if sym:
                slots.append(sym)
            else:
                print(f"# no __imp_ symbol found for dropped import {imp}",
                      file=sys.stderr)
    for s in slots:
        print(f"/INCLUDE:{s}")

    print(f"# {len(dropped)} symbol(s) + {len(slots)} import slot(s); "
          f"/OPT:REF keeps {len(ref)} of {len(noreref)}", file=sys.stderr)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
