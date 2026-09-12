#!/usr/bin/env python3
"""Audit where the split-set link placed each per-section LIBCMT object.

The CRT half of the goal is "link LIBCMT in, don't reverse it".  `scripts/
map_libcmt.py` says which member body the reference has at each VA and
`scripts/split_coff.py` turns each mapped section into a command-line object,
but nothing so far measured where LINK actually put them.  This does, from the
linker's own `/MAP` output.

Run it on a map produced by relinking with `/MAP:<file>`:

    cd build
    cmd=$(sed 's#@CMakeFiles/server_dll.dir/objects1.rsp#@split.rsp#;
               s#/out:server.dll#/out:server_split.dll /MAP:server_split.map#;
               s#/implib:server.lib#/implib:server_split.lib#;
               s# /pdb:[^ ]*##' CMakeFiles/server_dll.dir/link.txt)
    eval "$cmd"
    python3 ../scripts/split_audit.py server_split.map

Each split object is named `<reference-va>_<section>.obj`, so the object's own
name carries the VA the reference has it at; the deltas below are
`built - reference`.  A delta of 0 for every object is the CRT half of byte
identity.

Measured 2026-09-13 (round 26) on the 259-object split set: 340 placed symbols,
**0 at delta 0**.  The mapped objects start uniformly at -0xaa (the first CRT
function, `_fclose` 0x1001a18a, is placed at 0x1001a0e0) and the drift grows
monotonically to +0x5c0 by the tail (`__strdup` 0x10023812 at 0x10023dd2).
The -0xaa is the ~170 bytes of CRT code the reference has before `_fclose`
that the split set never emits — the nine functions no library carries plus
the eight `crt_region` objects the split rsp drops; the positive drift is the
split objects' COMDAT padding accumulating over ~300 objects.
`--closure` helpers are the extreme outliers (`memcpy.obj`'s `LeadUp1` lands
0x3640 *below* its reference VA, `__STRINGTOLD`'s helper 0xa5c above), so they
should be excluded when reading the drift.
"""

from __future__ import annotations

import argparse
import collections
import re
import sys
from pathlib import Path

LINE = re.compile(
    r"\s+([0-9a-f]{4}):([0-9a-f]{8})\s+(\S+)\s+([0-9a-f]{8})\s+(\S+)\s+(\S+)")


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("mapfile")
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--content", action="append", default=[],
                    help="directory of objects whose .text is part of this region "
                         "(repeatable); with it the region span, its content and "
                         "the slack between them are printed")
    ap.add_argument("--reference-end", default="0x10023846",
                    help="VA the reference .text ends at (for the breakdown)")
    ap.add_argument("--text-end", help="VA the built .text ends at; overrides the "
                    "heuristic end used for the breakdown")
    args = ap.parse_args()

    rows = []
    for line in open(args.mapfile, errors="replace"):
        m = LINE.match(line)
        if not m:
            continue
        va = int(m.group(4), 16)
        obj = m.group(6)
        mm = re.match(r"([0-9a-f]{8})_", obj)
        if not mm:
            continue
        rows.append((int(mm.group(1), 16), va, m.group(3)))
    rows.sort()
    if not rows:
        print("no split objects found in " + args.mapfile, file=sys.stderr)
        return 1

    deltas = collections.Counter(va - ref for ref, va, _ in rows)
    if args.json:
        import json
        print(json.dumps({
            "placed": len(rows),
            "exact": deltas.get(0, 0),
            "delta_min": min(deltas),
            "delta_max": max(deltas),
            "deltas": {str(k): v for k, v in sorted(deltas.items())},
            "objects": [{"reference_va": hex(r), "built_va": hex(v), "symbol": n}
                        for r, v, n in rows],
        }, indent=1))
        return 0

    print(f"placed split symbols: {len(rows)}")
    print(f"exactly at their reference VA: {deltas.get(0, 0)}")
    print(f"delta range: {min(deltas):+#x} .. {max(deltas):+#x}")
    if args.content:
        def text_size(path):
            b = open(path, "rb").read()
            nsec = int.from_bytes(b[2:4], "little")
            optsz = int.from_bytes(b[16:18], "little")
            base = 20 + optsz
            total = 0
            for i in range(nsec):
                hdr = b[base + i * 40:base + (i + 1) * 40]
                if hdr[0:5] == b".text":
                    total += int.from_bytes(hdr[16:20], "little")
            return total

        content = 0
        for d in args.content:
            content += sum(text_size(str(f)) for f in Path(d).glob("*.obj"))
        region_start = min(va for _ref, va, _n in rows)
        end = (int(args.text_end, 16) if args.text_end
               else int(args.reference_end, 16) + max(va - ref for ref, va, _n in rows))
        span = end - region_start
        print()
        print(f"region built   {region_start:#x} .. {end:#x} = {span} bytes")
        print(f"emitted content{content:>28} bytes")
        print(f"slack (span - content){span - content:>17} bytes")
        print(f"reference span (end - first ref VA){end - min(ref for ref, _v, _n in rows):>8} bytes")
    print()
    print(f"{'symbol':34} {'reference':>11} {'built':>11} {'delta':>9}")
    for ref, va, name in rows[:10] + rows[-10:]:
        print(f"{name:34} {ref:#11x} {va:#11x} {va - ref:+#9x}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
