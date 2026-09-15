#!/usr/bin/env python3
"""Will shrinking/growing an object help `.data`, or hurt it?  Ask before editing.

Three rounds of the data pass produced three size reductions of almost identical
magnitude and wildly different outcomes:

    round 508   -37 bytes   .data   +236  WORSE
    round 509   -36 bytes   .data   -231  better
    round 510    -8 bytes   .data -1,350  better
    round 511    -8 bytes   .data +1,752  WORSE

Size is not the variable and neither is local correctness -- every one of those
edits was *right* about the bytes it changed.  What decides the sign is whether
the region of `.data` that sits AFTER the edit is currently at its best offset.
An object that emits D bytes too many moves everything after it by D; if that
downstream region already matches best at shift 0, then moving it by any D at
all can only lose, however wrong the object's own bytes are.

This measures that directly.  For a cut point (the end of the object you intend
to change) it reports, for each candidate shift, how many bytes of the
reference `.data` after that point the built `.data` reproduces:

    $ python3 scripts/data_shift_probe.py --cut 0x100273e0
    shift    +0   30729 matches   <-- current
    shift    -8   29327 matches   (-1402)
    shift    +8   29011 matches   (-1718)
    best shift: +0  -- an edit that changes this object's size can only lose

Read it as a veto, not a recommendation: `best shift: +0` means do not bother
editing the object's size.  A non-zero best shift says how many bytes the object
would have to gain or lose, and roughly what that is worth.

The numbers are byte counts of a positional compare, so they are directly
comparable with the `.data differing` figure `postlink_residual.py` prints.
"""

from __future__ import annotations

import argparse
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
IMAGE_BASE = 0x10000000

def data_section(path: Path) -> tuple[bytes, int]:
    """Raw `.data` bytes and the section's VA."""
    raw = path.read_bytes()
    pe = struct.unpack_from("<I", raw, 0x3C)[0]
    nsec = struct.unpack_from("<H", raw, pe + 6)[0]
    opt = struct.unpack_from("<H", raw, pe + 20)[0]
    for i in range(nsec):
        off = pe + 24 + opt + i * 40
        if raw[off : off + 8].rstrip(b"\0") == b".data":
            _vs, va, rsize, rptr = struct.unpack_from("<IIII", raw, off + 8)
            return raw[rptr : rptr + rsize], va
    raise ValueError(f"{path}: no .data section")

def matches_after(ref: bytes, built: bytes, cut: int, shift: int) -> int:
    """Bytes of ref[cut:] that built reproduces when built is moved by *shift*."""
    n = 0
    limit = min(len(ref), len(built))
    for i in range(cut, limit):
        j = i + shift
        if 0 <= j < len(built) and ref[i] == built[j]:
            n += 1
    return n

def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--cut", required=True,
                    help="VA (or raw .data offset) after which the edit shifts bytes")
    ap.add_argument("--built", default="build/split_poc.dll",
                    help="the RAW LINK, not the postlinked deliverable")
    ap.add_argument("--reference", default="original/Server/server.dll")
    ap.add_argument("--range", type=int, default=64,
                    help="widest shift to try, in bytes either way (default 64)")
    ap.add_argument("--step", type=int, default=4)
    args = ap.parse_args()

    ref, ref_va = data_section(ROOT / args.reference)
    built, _ = data_section(ROOT / args.built)

    cut = int(args.cut, 0)
    if cut >= IMAGE_BASE:  # a VA -- convert to a raw .data offset
        cut -= IMAGE_BASE + ref_va
    if not 0 <= cut < len(ref):
        sys.exit(f"cut {args.cut} is outside .data (0..{len(ref):#x})")

    base = matches_after(ref, built, cut, 0)
    rows = []
    for shift in range(-args.range, args.range + 1, args.step):
        rows.append((shift, matches_after(ref, built, cut, shift)))

    best = max(rows, key=lambda r: r[1])
    for shift, n in rows:
        tag = "  <-- current" if shift == 0 else f"  ({n - base:+d})"
        star = "  BEST" if (shift, n) == best else ""
        print(f"shift {shift:+5d}   {n} matches{tag}{star}")

    print()
    if best[0] == 0:
        print("best shift: +0 -- the region after this cut is ALREADY at its best "
              "offset, so an edit that changes this object's size can only lose, "
              "however wrong the object's own bytes are.")
        return 1
    print(f"best shift: {best[0]:+d} ({best[1] - base:+d} bytes) -- this object would "
          f"have to {'shrink' if best[0] < 0 else 'grow'} by {abs(best[0])} bytes.")
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
