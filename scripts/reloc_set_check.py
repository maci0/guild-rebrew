#!/usr/bin/env python3
"""Compare the raw link's relocation RECORDS against the reference's.

Why this exists (round 170).  A relocation record changes no byte of the file:
it tells the loader to add the image base to the word at that RVA.  So a build
missing 590 of them is byte-identical in the region they describe and invisible
to `cmp`, to the per-section table, and to the residue report -- all of which
guild-rebrew's gate uses.  Round 169 measured exactly that: 590 missing, of which
**260 point into `.data`**, a section the gate reports as perfect.

On this DLL the practical effect is nil -- preferred base 0x10000000, it loads
there, every fixup is the identity -- but a loader forced to rebase would produce
a different image from ours with the gate still green.

Reports the entry sets, not the bytes, and exits non-zero only when a baseline is
exceeded, so it is a regression guard rather than a gate on an unfinished number.

Usage:
    python3 scripts/reloc_set_check.py [--built build/split_poc.dll] \\
        [--reference original/Server/server.dll] [--json]
"""
from __future__ import annotations

import argparse
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

#: measured on the split link at round 169; a regression is a new missing record
MISSING_BASELINE = 590
EXTRA_BASELINE = 96


def entries(path: Path) -> set[tuple[int, int]]:
    d = path.read_bytes()
    pe = struct.unpack_from("<I", d, 0x3C)[0]
    n = struct.unpack_from("<H", d, pe + 6)[0]
    oh = struct.unpack_from("<H", d, pe + 20)[0]
    o = pe + 24 + oh
    for i in range(n):
        s = o + i * 40
        if d[s:s + 8].rstrip(b"\0") != b".reloc":
            continue
        vs, _va, _rs, rp = struct.unpack_from("<IIII", d, s + 8)
        blk = d[rp:rp + vs]
        break
    else:
        return set()
    out: set[tuple[int, int]] = set()
    i = 0
    while i + 8 <= len(blk):
        page, size = struct.unpack_from("<II", blk, i)
        if size < 8:
            break
        j = i + 8
        while j + 2 <= i + size:
            f = struct.unpack_from("<H", blk, j)[0]
            out.add((page + (f & 0x0FFF), f >> 12))
            j += 2
        i += size
    return out


def band(rva: int) -> str:
    if rva < 0x24000:
        return ".text"
    if rva < 0x27000:
        return ".rdata"
    if rva < 0x35000:
        return ".data"
    return "other"


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--built", default="build/split_poc.dll")
    ap.add_argument("--reference", default="original/Server/server.dll")
    ap.add_argument("--json", action="store_true")
    args = ap.parse_args()

    ref = entries(ROOT / args.reference)
    got = entries(ROOT / args.built)
    missing = sorted(ref - got)
    extra = sorted(got - ref)
    by_band: dict[str, int] = {}
    for rva, _t in missing:
        by_band[band(rva)] = by_band.get(band(rva), 0) + 1

    result = {
        "reference_entries": len(ref),
        "built_entries": len(got),
        "missing": len(missing),
        "extra": len(extra),
        "shared": len(ref & got),
        "missing_by_section": by_band,
    }
    if args.json:
        print(json.dumps(result, indent=2))
    else:
        print("reference relocation records: %d" % len(ref))
        print("built                        : %d" % len(got))
        print("  shared  : %d" % len(ref & got))
        print("  missing : %d  %s" % (len(missing), by_band))
        print("  extra   : %d" % len(extra))

    bad = len(missing) > MISSING_BASELINE or len(extra) > EXTRA_BASELINE
    if bad:
        print("REGRESSION: relocation records missing %d (baseline %d) / extra %d (baseline %d)"
              % (len(missing), MISSING_BASELINE, len(extra), EXTRA_BASELINE), file=sys.stderr)
        return 1
    print("missing %d, extra %d -- baseline %d/%d held"
          % (len(missing), len(extra), MISSING_BASELINE, EXTRA_BASELINE))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
