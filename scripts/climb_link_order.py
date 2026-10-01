#!/usr/bin/env python3
"""Greedily add /INCLUDE: directives until the link order stops improving.

Round 70 showed the mechanism -- the linker's pull order is set by which
object first references a symbol, and `/INCLUDE:` moves that -- but also that a
*batch* of directives can make the order worse (277 -> 294) while a smaller one
made it better (339 -> 277).  So this walks one candidate at a time, links,
measures, and keeps a directive only when the inversion count drops.

The objective is the inversion count from `derive_link_order.py`: the number of
object pairs the reference orders differently from our link.  Lower is better.
`rebrew postlink --layout` coverage is reported alongside but is NOT the
optimised quantity -- order changes do not by themselves make function bodies
correct, and rounds 68-70 show the two numbers move independently.

It edits `build/CMakeFiles/server_dll.dir/link.txt` in place rather than
re-running cmake, because the directive order is all that matters and a
reconfigure per candidate costs more than the link does.

Usage:
    python3 scripts/climb_link_order.py --steps 8
"""
from __future__ import annotations

import argparse
import json
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "scripts"))

from derive_link_order import (  # noqa: E402
    build_probe_index, map_entries, text_section,
)

LINK_TXT = ROOT / "build" / "CMakeFiles" / "server_dll.dir" / "link.txt"
MAP = ROOT / "build" / "raw.map"
BUILT = ROOT / "build" / "raw.dll"


def link() -> bool:
    """Relink to raw.dll/raw.map, returning False on a link error."""
    txt = LINK_TXT.read_text()
    out = txt.replace("/out:server.dll", "/out:raw.dll /MAP:raw.map")
    out = out.replace("/implib:server.lib", "/implib:raw.lib")
    out = re.sub(r" /pdb:[^ ]*", "", out)
    r = subprocess.run(out, shell=True, cwd=ROOT / "build",
                       capture_output=True, text=True)
    if "error LNK" in r.stdout + r.stderr:
        line = next((x for x in (r.stdout + r.stderr).splitlines()
                     if "error LNK" in x), "link failed")
        print("    link error: " + line.strip()[:100])
        return False
    return True


def measure() -> dict:
    """Inversion count and coverage for the current link."""
    rb, rba = text_section(ROOT / "original" / "Server" / "server.dll")
    ob, oba = text_section(BUILT)
    entries = map_entries(MAP)
    idx = build_probe_index(ob, oba, entries, 16)
    inv = json.loads((ROOT / "db" / "inventory-server.dll.json").read_text())
    order, seen = [], set()
    for f in sorted(inv, key=lambda x: x["va"]):
        off = f["va"] - rba
        if off < 0 or off + 16 > len(rb):
            continue
        c = idx.get(rb[off:off + 16], [])
        if len(c) == 1 and c[0][2] not in seen:
            seen.add(c[0][2])
            order.append(c[0][2])
    ours, seen = [], set()
    for va, sym, obj in entries:
        if obj not in seen:
            seen.add(obj)
            ours.append(obj)
    pos = {o: i for i, o in enumerate(ours)}
    inv_count = sum(1 for i in range(len(order))
                    for j in range(i + 1, len(order))
                    if pos.get(order[j], 1 << 30) < pos.get(order[i], -1))
    return {"inversions": inv_count, "order": order, "pos": pos,
            "distinct": len(order)}


def candidates(state: dict) -> list[str]:
    """Symbols whose object the reference places earlier than we do.

    Only objects we actually link are considered, and only those the reference
    places before something we already place earlier -- i.e. the object that
    *should* be pulled in before the one we pull first.
    """
    out = []
    order, pos = state["order"], state["pos"]
    for i, obj in enumerate(order):
        if obj not in pos:
            continue
        for j in range(i + 1, min(i + 4, len(order))):
            later = order[j]
            if later in pos and pos[later] < pos[obj]:
                out.append(obj)
                break
    return out


def symbol_for(map_path: Path, obj: str) -> str | None:
    """The exported symbol of `obj`, for /INCLUDE: -- which takes a symbol."""
    for line in map_path.read_text(errors="replace").splitlines():
        m = re.match(r"^\s*0001:[0-9a-f]{8}\s+(\S+)\s+[0-9a-f]{8} f\s+(\S+)", line)
        if m and m.group(2) == obj:
            return m.group(1)
    return None


def insert(flag: str) -> bool:
    """Put /INCLUDE:<flag> at the very front of the directive list."""
    txt = LINK_TXT.read_text()
    if f"/INCLUDE:{flag} " in txt:
        return False
    # immediately after the linker name, which is where LINK reads them in order
    new, n = re.subn(r'(rebrew-cmake-link\.exe\s+)',
                     r'\1"/INCLUDE:' + flag + '" ', txt, count=1)
    if n == 0:
        return False
    LINK_TXT.write_text(new)
    return True


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--steps", type=int, default=8)
    ap.add_argument("--verbose", action="store_true")
    args = ap.parse_args()

    if not link():
        print("baseline link failed")
        return 1
    base = measure()
    best = base["inversions"]
    print(f"baseline: {best} inversions over {base['distinct']} objects")

    original = LINK_TXT.read_text()
    kept: list[str] = []
    try:
        for step in range(args.steps):
            state = measure()
            cands = candidates(state)
            if not cands:
                print("no candidates left")
                break
            improved = False
            for obj in cands[:6]:
                sym = symbol_for(MAP, obj)
                if not sym:
                    continue
                if not insert(sym):
                    continue
                if not link():
                    LINK_TXT.write_text(original if not kept else LINK_TXT.read_text()
                                        .replace(f'"/INCLUDE:{sym}" ', "", 1))
                    continue
                now = measure()
                if now["inversions"] < best:
                    drop = best - now["inversions"]
                    best = now["inversions"]
                    kept.append(sym)
                    print(f"  step {step + 1}: +{sym:<14} -> {best} "
                          f"({drop} better)")
                    improved = True
                    break
                LINK_TXT.write_text(
                    LINK_TXT.read_text().replace(f'"/INCLUDE:{sym}" ', "", 1))
                if args.verbose:
                    print(f"  step {step + 1}: {sym} no help ({now['inversions']})")
            if not improved:
                print("no single-symbol step improved the order")
                break
    finally:
        pass

    print(f"\nkept {len(kept)} directive(s): {' '.join(kept) if kept else '(none)'}")
    print(f"inversions: {base['inversions']} -> {best}")
    print("\nNow make the winning flags permanent in CMakeLists.txt; this run")
    print("only edited build/CMakeFiles/server_dll.dir/link.txt, which cmake")
    print("regenerates on the next configure.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
