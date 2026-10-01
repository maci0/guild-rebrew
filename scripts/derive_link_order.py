#!/usr/bin/env python3
"""Derive the link order the original build used, from the reference alone.

Why this exists (round 69).  `rebrew postlink --layout` validates 65% of the
7,463 layout-map code spans and needs 90%, and the reason is not 281 wrong
function bodies.  Probing each `LIBCMT:*` symbol's first bytes against the
reference showed shifts of -4065, +25126, -7704, ... with no constant and no
progression, and showed `___ld12mul` belonging at 0x10009789 -- deep in the
game band -- while our link places every LIBCMT object after the game objects.
The reference **interleaves** library code with game code, and the interleaving
is what .text layout is made of.

So the original link line is recoverable without reversing anything:

  1. take every function in the reference's .text, in VA order;
  2. for each, find the function in OUR link that carries the same bytes;
  3. read off the object that supplies that function;
  4. sort by *reference* address, not by our address.

Step 4 is the answer.  Our order is what we produced; the reference order is
what the original produced; the difference is the defect.

Usage:
    python3 scripts/derive_link_order.py --map build/raw.map \\
        --built build/raw.dll --out build/split_poc/link_order.txt
        [--json] [--min-match 16]
"""
from __future__ import annotations

import argparse
import json
import re
import struct
import sys
from collections import Counter, defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
IMAGE_BASE = 0x10000000

#: " 0001:00008310       _DllMain@12                10009310 f   server.c.obj"
MAP_RE = re.compile(
    r"^\s*0001:([0-9a-f]{8})\s+(\S+)\s+([0-9a-f]{8}) f\s+(\S+)")


def text_section(path: Path) -> tuple[bytes, int]:
    """Return (.text bytes, its VA) for a PE image."""
    d = path.read_bytes()
    pe = struct.unpack_from("<I", d, 0x3C)[0]
    n = struct.unpack_from("<H", d, pe + 6)[0]
    opt = struct.unpack_from("<H", d, pe + 20)[0]
    o = pe + 24 + opt
    for i in range(n):
        s = o + i * 40
        if d[s:s + 8].rstrip(b"\0") == b".text":
            vs, va, rs, rp = struct.unpack_from("<IIII", d, s + 8)
            return d[rp:rp + rs], IMAGE_BASE + va
    raise SystemExit(f"{path}: no .text")


def map_entries(path: Path) -> list[tuple[int, str, str]]:
    """(va, symbol, supplying object) for every public .text symbol."""
    out = []
    for line in path.read_text(errors="replace").splitlines():
        m = MAP_RE.match(line)
        if m:
            out.append((int(m.group(3), 16), m.group(2), m.group(4)))
    out.sort()
    return out


def build_probe_index(blob: bytes, base: int, entries, min_len: int):
    """Map first-N-bytes -> [(va, symbol, object)] for our own link."""
    idx: dict[bytes, list[tuple[int, str, str]]] = defaultdict(list)
    for va, sym, obj in entries:
        off = va - base
        if off < 0 or off + min_len > len(blob):
            continue
        idx[blob[off:off + min_len]].append((va, sym, obj))
    return idx


def main() -> int:
    ap = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--map", default="build/raw.map",
                    help="LINK /MAP of our own link (supplies object names)")
    ap.add_argument("--built", default="build/raw.dll")
    ap.add_argument("--reference", default="original/Server/server.dll")
    ap.add_argument("--inventory", default="db/inventory-server.dll.json")
    ap.add_argument("--out", default=None,
                    help="write the derived object order, one per line")
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--min-match", type=int, default=16)
    ap.add_argument("--top", type=int, default=20)
    args = ap.parse_args()

    ref_blob, ref_base = text_section(ROOT / args.reference)
    our_blob, our_base = text_section(ROOT / args.built)
    entries = map_entries(ROOT / args.map)
    inv = json.loads((ROOT / args.inventory).read_text())

    our_index = build_probe_index(our_blob, our_base, entries, args.min_match)

    # 1+2. every reference function, in reference order, matched into our link
    rows = []
    matched = ambiguous = unmatched = 0
    for f in sorted(inv, key=lambda x: x["va"]):
        off = f["va"] - ref_base
        if off < 0 or off + args.min_match > len(ref_blob):
            continue
        probe = ref_blob[off:off + args.min_match]
        cands = our_index.get(probe, [])
        if len(cands) == 1:
            va, sym, obj = cands[0]
            rows.append({"reference_va": f["va"], "reference_name": f["name"],
                         "our_va": va, "symbol": sym, "object": obj})
            matched += 1
        elif cands:
            ambiguous += 1
        else:
            unmatched += 1

    # 3+4. the answer: objects in the order the reference places them
    order: list[str] = []
    seen = set()
    for r in rows:
        if r["object"] not in seen:
            seen.add(r["object"])
            order.append(r["object"])

    # where our own order puts the same objects, for the delta
    our_order = []
    seen = set()
    for va, sym, obj in entries:
        if obj not in seen:
            seen.add(obj)
            our_order.append(obj)
    ours_pos = {o: i for i, o in enumerate(our_order)}
    inversions = sum(1 for i in range(len(order))
                     for j in range(i + 1, len(order))
                     if ours_pos.get(order[j], 1 << 30) < ours_pos.get(order[i], -1))

    if args.json:
        print(json.dumps({
            "reference_functions": len(inv),
            "matched_uniquely": matched,
            "ambiguous": ambiguous,
            "unmatched": unmatched,
            "distinct_objects": len(order),
            "order_inversions_vs_our_link": inversions,
            "order": order,
        }, indent=2))
        return 0

    print(f"reference functions        : {len(inv)}")
    print(f"  matched uniquely         : {matched}")
    print(f"  ambiguous probe          : {ambiguous}")
    print(f"  no match in our link     : {unmatched}")
    print(f"distinct objects in order  : {len(order)}")
    print(f"order inversions vs ours   : {inversions}")
    kinds = Counter("library" if r["object"].startswith("LIBCMT:")
                    else "split" if r["object"][0].isdigit()
                    else "game" for r in rows)
    print("  by kind                  : " +
          ", ".join(f"{k} {v}" for k, v in sorted(kinds.items())))

    if args.out:
        out = ROOT / args.out
        out.parent.mkdir(parents=True, exist_ok=True)
        out.write_text("\n".join(order) + "\n")
        print(f"wrote {args.out} ({len(order)} objects)")

    print(f"\nfirst {args.top} objects in the reference's order:")
    for i, o in enumerate(order[:args.top], 1):
        at = ours_pos.get(o)
        print(f"  {i:3d}. {o:<44} ours: {'absent' if at is None else at}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
