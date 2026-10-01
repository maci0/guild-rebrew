#!/usr/bin/env python3
"""Report where every tracked data symbol actually landed, against the reference.

Why (round 19).  Rounds 11-18 chased the `.text` overshoot and established that
the real blocker is `.data` placement: neither the shipped `/OPT:NOREF` link nor
`/OPT:REF` puts the game's data at the reference's addresses, and postlink hides
that by rewriting operands and blitting `.data`.  Round 19 also ruled out the
obvious fix -- reordering the per-TU `.data` sections -- because the reference's
layout is not a permutation of them (`link_stubs.c.obj`'s symbols alone span
0x100241a0..0x114ffe24, and ordering by reference address yields 13 overlapping
ranges).

None of that was measurable.  `scripts/data_extent_check.py` checks that a
symbol's *size* does not run into its neighbour, and `postlink_residual.py`
reports `.data` as a byte count; neither says *where* a symbol went.  This does,
and it is the standing ruler for the remaining work.

Usage:
    python3 scripts/data_placement.py --map build/split_poc.map
    python3 scripts/data_placement.py --map build/split_poc.map --json
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
IMAGE_BASE = 0x10000000
MAPLINE = re.compile(r"^\s*(\d{4}):([0-9a-f]{8})\s+(\S+)\s+([0-9a-f]{8})(?:\s+\S+)?\s+(\S+)\s*$")
#: map section number -> PE section; 0003 is .data, 0002 is .rdata/IAT.
SECTIONS = {"0002": ".rdata", "0003": ".data"}


def reference_data() -> tuple[dict[str, int], dict[str, int]]:
    """(name -> reference VA, name -> size) from src/rebrew-data.toml.

    The sizes matter as much as the addresses: they say how much of the
    reference section the tracked symbols account for.  On server.dll that is
    16% -- the rest is the unnamed BSS tail and inter-TU padding, so "re-emit
    every tracked symbol at its reference offset" cannot tile the section on its
    own, and the manifest a full re-emit needs is not yet complete.
    """
    out: dict[str, int] = {}
    sizes: dict[str, int] = {}
    cur: int | None = None
    name: str | None = None
    for line in (ROOT / "src" / "rebrew-data.toml").read_text(errors="ignore").splitlines():
        m = re.match(r'\["SERVER\.(0x[0-9a-fA-F]+)"\]', line)
        if m:
            cur = int(m.group(1), 16)
            name = None
            continue
        if cur is None:
            continue
        m = re.match(r'name\s*=\s*"([^"]+)"', line)
        if m:
            name = m.group(1)
            out.setdefault(name, cur)
            continue
        m = re.match(r'size\s*=\s*(\d+)', line)
        if m and name:
            sizes[name] = int(m.group(1))
    return out, sizes


def built_data(mapfile: Path, section: str) -> dict[str, int]:
    """name -> built VA, for the symbols the map places in `section`."""
    out: dict[str, int] = {}
    with open(mapfile, errors="replace") as fh:
        for line in fh:
            m = MAPLINE.match(line)
            if not m:
                continue
            if SECTIONS.get(m.group(1)) != section:
                continue
            out.setdefault(m.group(3).lstrip("_"), int(m.group(4), 16))
    return out


def manifest_gaps(ref: dict[str, int], sizes: dict[str, int],
                  lo: int, hi: int) -> list[tuple[int, int, str]]:
    """Uncovered runs in [lo, hi) as (address, length, next symbol name).

    Round 21: the initialised part of `.data` is 100% covered by 249 sized
    symbols bar 292 bytes in 22 runs, and those runs are real objects -- a
    `__server.log` name table, an `{index, pointer}` table, small string
    constants, and a few symbols whose declared size is a few bytes short
    (0x1002c5a0 holds a pointer to `cm_ChainNoop` immediately before
    `g_chain_handler_table`).  Naming them is what completes the manifest a
    reference-ordered `.data` emit would need, so the gaps need a ruler too.
    """
    sized = sorted(((va, sizes[name], name) for name, va in ref.items()
                    if name in sizes and lo <= va < hi), key=lambda t: t[0])
    gaps: list[tuple[int, int, str]] = []
    at = lo
    for va, size, name in sized:
        if va > at:
            gaps.append((at, va - at, name))
        at = max(at, va + size)
    if at < hi:
        gaps.append((at, hi - at, "<end>"))
    return gaps


def locate_sections(built: bytes, ref: bytes, base: int, on_disk: int,
                    objects, rsp) -> dict:
    """Reference address of every game `.data`/`.bss` section, by content.

    Why this works (round 55).  `.data` carries no relocations, its VA equals its
    file offset, and the built `.data` is already the reference's byte for byte
    at the SAME offsets (26 bytes differ out of 57,344, best constant shift 0).
    So a section's reference address is simply where its own bytes appear in the
    reference -- no metadata needed.

    Sections are walked in *built* order and the search is confined to the window
    after the previously located section, which turns most of the ambiguous
    content matches (repeated small ints) into unique ones.
    """
    import sys as _sys
    _sys.path.insert(0, str(ROOT / "scripts"))
    from split_coff import Coff

    bdata = built[base:base + on_disk]
    rdata = ref[base:base + on_disk]

    # 1. where each section sits in OUR build, in link order
    placed = []
    cursor = 0
    for rel in objects:
        p = Path(rel)
        if not p.exists():
            p = ROOT / "build" / rel
        if not p.exists():
            continue
        try:
            c = Coff(p.read_bytes())
        except Exception:
            continue
        for sec in c.sections:
            if sec["name"].rstrip(b"\0") not in (b".data", b".bss") or not sec["raw_size"]:
                continue
            blob = c.data[sec["raw_ptr"]:sec["raw_ptr"] + sec["raw_size"]]
            hit = None
            for j in range(cursor, max(cursor, len(bdata) - len(blob) + 1)):
                if bdata[j:j + len(blob)] == blob:
                    hit = j
                    break
            if hit is not None:
                placed.append((hit, blob, p.name))
                cursor = hit + len(blob)

    # 2. where each of those sits in the REFERENCE
    out = {"placed_in_build": len(placed), "located": 0, "windowed": 0,
           "ambiguous": 0, "no_match": 0, "zero_body": 0, "sections": []}
    last = 0
    for boff, blob, name in placed:
        rec = {"object": name, "built_offset": hex(base + boff),
               "size": len(blob), "reference": None, "how": None}
        if not any(blob):
            out["zero_body"] += 1
            rec["how"] = "zero-body"
            out["sections"].append(rec)
            continue
        hit = None
        for ln in (32, 24, 16, 12, 8):
            pat = blob[:ln]
            if not any(pat):
                continue
            hs = [j for j in range(0, len(rdata) - ln + 1) if rdata[j:j + ln] == pat]
            if len(hs) == 1:
                hit, how = hs[0], "unique"
                break
            if hs:
                hit, how = None, "ambiguous"
                break
        if hit is None:
            for ln in (24, 16, 12, 8):
                pat = blob[:ln]
                if not any(pat):
                    continue
                hs = [j for j in range(last, min(len(rdata) - ln, last + 0x4000))
                      if rdata[j:j + ln] == pat]
                if len(hs) == 1:
                    hit, how = hs[0], "windowed"
                    break
            else:
                how = "ambiguous" if how == "ambiguous" else (how or "no-match")
        key = {"unique": "located"}.get(how, how)
        if hit is None:
            out[key if key in out else "no_match"] += 1
        else:
            out[key] += 1
            rec["reference"] = hex(IMAGE_BASE + base + hit)  # base is a file offset
            last = hit + len(blob)
        out["sections"].append(rec)
    out["coverage_pct"] = round(100.0 * (out["located"] + out["windowed"])
                                / max(1, out["placed_in_build"]), 1)
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--map", required=True)
    ap.add_argument("--section", default=".data", choices=sorted(SECTIONS.values()))
    ap.add_argument("--top", type=int, default=15)
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--locate", action="store_true",
                    help="locate every game .data/.bss section in the reference "
                         "by content matching (round 55)")
    ap.add_argument("--built", default="build/split_poc.dll")
    ap.add_argument("--rsp", default="build/split_poc/rsp.rsp")
    ap.add_argument("--section-base", default="0x27000", type=lambda s: int(s, 0))
    ap.add_argument("--on-disk", default="0xe000", type=lambda s: int(s, 0))
    ap.add_argument("--gaps", action="store_true",
                    help="list the manifest gaps in the on-disk (initialised) part")
    args = ap.parse_args()

    ref, ref_sizes = reference_data()

    if args.locate:
        res = locate_sections(
            (ROOT / args.built).read_bytes(),
            (ROOT / "original" / "Server" / "server.dll").read_bytes(),
            args.section_base, args.on_disk,
            [o for o in (ROOT / args.rsp).read_text().split() if o.endswith(".obj")],
            args.rsp)
        if args.json:
            print(json.dumps(res, indent=2))
            return 0
        print(f"game .data/.bss sections placed in the build: {res['placed_in_build']}")
        print(f"  located by unique content : {res['located']}")
        print(f"  located inside a window  : {res['windowed']}")
        print(f"  ambiguous / no match / zero: {res['ambiguous']} / "
              f"{res['no_match']} / {res['zero_body']}")
        print(f"  coverage {res['coverage_pct']}%")
        return 0

    if args.gaps:
        lo, hi = args.section_base, args.section_base + args.on_disk
        binary = (ROOT / "original" / "Server" / "server.dll").read_bytes()
        gaps = manifest_gaps(ref, ref_sizes, lo, hi)
        total = sum(g[1] for g in gaps)
        print(f"manifest gaps in {lo:#x}..{hi:#x} ({hi - lo} B on disk): "
              f"{len(gaps)} run(s), {total} B uncovered")
        for at, n, nxt in gaps:
            off = at - 0x10000000
            blob = binary[off:off + min(n, 24)]
            txt = "".join(chr(c) if 32 <= c < 127 else "." for c in blob)
            print(f"  {at:#010x} {n:5d} B  before {nxt:28} {blob.hex(' ')}  {txt}")
        return 0

    built = built_data(Path(args.map), args.section)
    accounted = sum(ref_sizes.values())

    matched = [n for n in built if n in ref]
    off = [(built[n] - ref[n], n, ref[n], built[n]) for n in matched if built[n] != ref[n]]
    rows = {
        "section": args.section,
        "reference_symbols": len(ref),
        "built_symbols": len(built),
        "matched": len(matched),
        "exact": len(matched) - len(off),
        "misplaced": len(off),
        "misplaced_pct": round(100.0 * len(off) / len(matched), 1) if matched else 0.0,
        "sized_symbols": len(ref_sizes),
        "bytes_accounted": accounted,
    }

    if args.json:
        rows["worst"] = [
            {"name": n, "delta": d, "reference": hex(r), "built": hex(b)}
            for d, n, r, b in sorted(off, key=lambda t: abs(t[0]))[:args.top]
        ]
        print(json.dumps(rows, indent=2))
        return 0

    print(f"{args.section}: {rows['matched']} tracked symbols matched by name "
          f"({rows['exact']} exact, {rows['misplaced']} misplaced, "
          f"{rows['misplaced_pct']}%)")
    if not off:
        print("  every tracked symbol is at its reference address")
        return 0
    hist = Counter(d for d, _n, _r, _b in off)
    print("  delta histogram:", ", ".join(f"{d:+#x}x{c}" for d, c in hist.most_common(6)))
    print(f"  manifest coverage: {len(ref_sizes)} sized symbols account for "
          f"{accounted} bytes; a re-emit plan cannot tile the section on those alone")
    print(f"  {args.top} largest:")
    for d, n, r, b in sorted(off, key=lambda t: abs(t[0]))[:args.top]:
        print(f"    {d:+10d}  {n:34} ref {r:#010x} built {b:#010x}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
