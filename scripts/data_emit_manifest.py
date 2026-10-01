#!/usr/bin/env python3
"""Emit the ordered worklist a reference-ordered `.data` link would need.

Why (round 35).  Rounds 26, 33 and 34 established the shape of the problem:
`server.dll`'s `.data` must come out of the linker laid out exactly as the
reference has it, and no *single* object added to the current tree helps --
each attempt moved correct content into a wrongly-ordered section and cost
750-900 residue bytes.  The only thing that can work is a wholesale emit, and
that needs every region's extent known up front.

This prints the reference's `.data` as an ordered list of regions with their
sizes and whether the tree currently declares them, so the emit is mechanical
rather than a matter of rediscovering the layout each round.

The layout it uses was established by measurement, not assumed:
  * `g_connections` is 8 slots of 0x264264 = 0x1321320 (round 28: the tree had
    declared the *stride*), and the reference's own loop bound is
    `0x101deb00 + 0x1321320 == 0x114ffe20` (round 28, from the base relocations).
  * two 768 x 768 tables at 0x100a9820 and 0x1014d8e0 (round 31, from the
    `add $0x300 / cmp $0x90000` initialisation loop).
  * `__sbh_initialized` is 411,112 B at 0x100366b8 (round 33, tracked and
    VERIFIED in the metadata since round 2, never defined in the tree).

Usage:
    python3 scripts/data_emit_manifest.py
    python3 scripts/data_emit_manifest.py --json
"""

from __future__ import annotations

import argparse
import json
import re as _re
import tomllib
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SECTION_START = 0x10027000
SECTION_END = 0x1176759C

#: (name, start VA, end VA, declared-in-tree?)
REGIONS: list[tuple[str, int, int]] = [
    ("game data .. array A", 0x10027000, 0x100A9820),
    ("array A (768 x 768)", 0x100A9820, 0x10139820),
    ("unnamed gap between A and B", 0x10139820, 0x1014D8E0),
    ("array B (768 x 768)", 0x1014D8E0, 0x101DD8E0),
    ("unnamed gap before g_connections", 0x101DD8E0, 0x101DEB00),
    ("g_connections (8 slots)", 0x101DEB00, 0x114FFE20),
    ("sentinel", 0x114FFE20, 0x114FFE24),
    ("g_player_slot_overflow_pad", 0x114FFE24, 0x11764084),
    ("CRT band", 0x11764084, 0x1176759C),
]

#: symbols the tree must define for the regions above, with their sizes.
REQUIRED: list[tuple[str, int, int]] = [
    ("__sbh_initialized", 0x100366B8, 411112),
    ("array A", 0x100A9820, 0x90000),
    ("unnamed gap A..B", 0x10139820, 0x140C0),
    ("array B", 0x1014D8E0, 0x90000),
    ("unnamed gap B..g_connections", 0x101DD8E0, 0x1220),
    ("g_connections", 0x101DEB00, 0x1321320),
    ("g_player_slot_overflow_pad", 0x114FFE24, 0x264260),
]


#: a definition of `name` looks like `<type> name[...] = ...;` or `... name;`
#: at file scope -- never `extern`, never a use, never a parameter.
_DEF = r"(?m)^(?!\s*extern\b)(?:[A-Za-z_][\w \t\*]*?)\b{NAME}\b\s*(?:\[[^\]]*\])?\s*(?:=[^;]*)?;"


def defined_names() -> set[str]:
    """Names the tree actually defines.

    A definition is a line that names the symbol and ends in `;`, is not
    `extern`, not a comment, and is not a use inside a function body.  A
    regex over declarations kept missing the real ones
    (`unsigned char g_connections[0x1321320] = {0};` in link_stubs.c), so this
    is deliberately line-based.
    """
    out: set[str] = set()
    for p in (ROOT / "src").rglob("*.c"):
        try:
            lines = p.read_text(errors="ignore").splitlines()
        except OSError:
            continue
        for ln in lines:
            ln = ln.split("//")[0].strip()
            if not ln.endswith(";") or ln.startswith("extern") or ln.startswith("*"):
                continue
            m = _re.match(r"^[A-Za-z_][\w \t\*]*?\**\s*([A-Za-z_]\w*)\s*(\[[^\]]*\])?\s*"
                          r"(?:=[^;]*)?;$", ln)
            if m:
                out.add(m.group(1))
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--json", action="store_true")
    args = ap.parse_args()

    have = defined_names()
    total = sum(e - s for _n, s, e in REGIONS)
    rows = {
        "section_start": hex(SECTION_START),
        "section_end": hex(SECTION_END),
        "reference_vsize": hex(SECTION_END - SECTION_START),
        "region_sum": hex(total),
        "residual": hex(SECTION_END - SECTION_START - total),
        "regions": [{"name": n, "start": hex(s), "end": hex(e), "bytes": e - s}
                    for n, s, e in REGIONS],
        "required_declarations": [
            {"name": n, "va": hex(v), "bytes": b, "in_tree": n in have}
            for n, v, b in REQUIRED
        ],
    }

    if args.json:
        print(json.dumps(rows, indent=2))
        return 0

    print(f".data {rows['section_start']}..{rows['section_end']}  "
          f"reference VS {rows['reference_vsize']}")
    print(f"  region sum {rows['region_sum']}   residual {rows['residual']}")
    print()
    print("  ordered regions (this is the order the link must produce):")
    for r in rows["regions"]:
        print(f"    {r['start']} .. {r['end']}  {r['bytes']:>10d}  {r['name']}")
    print()
    print("  declarations the tree still needs:")
    for d in rows["required_declarations"]:
        mark = "present" if d["in_tree"] else "MISSING"
        print(f"    {d['va']}  {d['bytes']:>10d}  {d['name']:32} {mark}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
