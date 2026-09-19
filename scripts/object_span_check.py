#!/usr/bin/env python3
"""Measure each object against its ACTUAL reference span, not the pad report's `want`.

Why this exists (round 916): `scripts/split_link.sh`'s pad report compares an
object against `want`, the raw sum of the metadata's per-function sizes.  But an
object pads **each function** to a 16-byte boundary, so its `.text` is the
per-function-padded sum.  For `spiel62.c` those are 1328 and 1408, and the report
printed `+80 over the padded span` for a file that is exactly at its span.  All 25
checkable `LONG` objects were re-measured: **per-func-pad == objtext for every
one**, and against the real span **zero are over** -- 23 sit exactly at it and two
are under.

So `LONG` does not mean "over budget".  This script answers the question that
matters before editing a file: does the object fit between its first function's
reference VA and the next tracked VA?

**Re-measured round 1058: 1 object is over, not zero.**  `mlock.c.obj` reports
`span 118, text 212, +94`.  That is *correct and expected*: `mlock.c` is a local
LIBCMT replacement (the `_CRT_REGION_KEEP` pattern -- it exists so the linker
never pulls LIBCMT's `mlock.obj`, which imports `FatalAppExitA`/`IsBadWritePtr`),
so its object carries CRT support code the two annotated functions do not
describe.  The extra 43-byte section at `0x1001d0ac` is **byte-correct in the
deliverable** (0 differing bytes), so the overshoot does not move later symbols
and is not a defect.  The header's earlier "zero are over" was true of the 25
`LONG`-flagged objects at the time and is not true tree-wide.

Read `over > 0` on a *replacement* object as "this file also carries displaced
library code", not as a fault: check the bytes before acting.

    over > 0   the object does not fit -- edits that grow it will move later symbols
    over == 0  exactly at the span -- any growth moves later symbols
    over < 0   room to spare (this many bytes)

Usage:
    .venv/bin/python scripts/object_span_check.py [--json] [--obj <name>]
"""

import argparse
import json
import os
import re
import struct
import sys
import tomllib
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
BUILD = REPO / "build" / "CMakeFiles" / "server_dll.dir"
SRC = REPO / "src" / "server.dll"


def text_size(obj_path):
    """Total .text raw size across all COMDAT sections of a COFF object."""
    d = obj_path.read_bytes()
    nsec = struct.unpack_from("<H", d, 2)[0]
    opt = struct.unpack_from("<H", d, 16)[0]
    off = 20 + opt
    total = 0
    for _ in range(nsec):
        name = d[off : off + 8].rstrip(b"\x00").decode(errors="ignore")
        _vsz, _va, raw, _rp = struct.unpack_from("<IIII", d, off + 8)
        if name == ".text":
            total += raw
        off += 40
    return total


def track_map():
    """VA -> size, from rebrew-functions.toml."""
    with open(REPO / "src" / "rebrew-functions.toml", "rb") as fh:
        fn = tomllib.load(fh)
    out = {}
    for key, val in fn.items():
        if not isinstance(val, dict):
            continue
        _, sep, addr = str(key).rpartition(".")
        if not sep:
            continue
        try:
            out[int(addr, 16)] = int(val.get("size") or 0)
        except ValueError:
            continue
    return out


def file_vas(src_path):
    """Every `// FUNCTION: SERVER 0xNNN` VA in a source file, ascending."""
    try:
        txt = src_path.read_text(encoding="utf-8", errors="ignore")
    except OSError:
        return []
    vas = [int(m.group(1), 16) for m in re.finditer(r"// FUNCTION: SERVER (0x[0-9a-fA-F]+)", txt)]
    return sorted(vas)


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--obj", help="only this object basename, e.g. spiel62.c.obj")
    args = ap.parse_args()

    track = track_map()
    vas = sorted(track)
    longf = set()
    linklog = REPO / ".scratch" / "gate-link.log"
    if linklog.exists():
        for line in linklog.read_text(errors="ignore").splitlines():
            if line.startswith("LONG"):
                longf.add(line.split(":")[0].replace("LONG", "").strip())

    rows = []
    for root, _dirs, files in os.walk(BUILD):
        for f in files:
            if not f.endswith(".c.obj"):
                continue
            obj = Path(root) / f
            rel = obj.relative_to(BUILD)
            # strip the leading src/server.dll/ to find the .c it came from
            parts = list(rel.parts)
            if parts[0] != "src" or parts[1] != "server.dll":
                continue
            src = SRC.joinpath(*parts[2:])  # .../foo.c.obj -> .../foo.c
            src = src.with_suffix("")
            if not src.exists():
                continue
            fvas = file_vas(src)
            if not fvas:
                continue
            # The file's span runs from its FIRST function to the next TRACKED VA
            # after its LAST function.  Using the next VA after the first
            # function gives one function's size, not the file's -- that mistake
            # is why this script reported 24 objects over on its first run when
            # the correct answer is 0.
            lo = min(fvas)
            last = max(fvas)
            nxt = next((v for v in vas if v > last), None)
            if nxt is None:
                continue
            span = nxt - lo
            try:
                text = text_size(obj)
            except (OSError, struct.error):
                continue
            rows.append(
                {
                    "obj": f,
                    "span": span,
                    "text": text,
                    "over": text - span,
                    "long": f in longf,
                }
            )

    if args.obj:
        rows = [r for r in rows if r["obj"] == args.obj]
    rows.sort(key=lambda r: -r["over"])

    if args.json:
        print(json.dumps(rows, indent=2))
        return 1 if any(r["over"] > 0 for r in rows) else 0

    over = [r for r in rows if r["over"] > 0]
    print(f"measured {len(rows)} objects against their reference span")
    if over:
        print(f"\nOVER their span ({len(over)}):")
        for r in over:
            print(
                f"  {r['obj']:34s} span {r['span']:6d}  text {r['text']:6d}  +{r['over']}"
                f"{'  (LONG)' if r['long'] else ''}"
            )
    at = [r for r in rows if r["over"] == 0]
    print(f"exactly at their span: {len(at)}")
    slack = [r for r in rows if r["over"] < 0]
    print(f"under their span: {len(slack)}")
    for r in slack:
        print(f"  {r['obj']:34s} span {r['span']:6d}  text {r['text']:6d}  {r['over']}")

    flagged = [r for r in rows if r["long"]]
    print(
        f"\nLONG-flagged objects checked: {len(flagged)}; "
        f"of those, over their span: {sum(1 for r in flagged if r['over'] > 0)}"
    )
    return 1 if over else 0


if __name__ == "__main__":
    sys.exit(main())
