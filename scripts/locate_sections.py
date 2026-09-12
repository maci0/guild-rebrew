#!/usr/bin/env python3
"""Locate the reference VA of a section taken from a LIBCMT member.

`scripts/map_libcmt.py` goes one way: for each *reference catalog function*,
which member section supplies it.  This goes the other way, for the sections
that mapping misses — a member's unmapped `.text` sections (the closure helpers
`memcpy.obj`'s `LeadUp*` family, and the sections `scripts/emit_defs.py` has to
emit because nothing defines their symbols).  Those are appended at the end of
the split-set region today, which both adds bytes the reference does not have
*there* and shifts everything after them.

The matcher masks the candidate's relocation slots and the four bytes after
every `E8`/`E9` (intra-image relative calls carry no relocation entry in the
reference, so they cannot be masked from the relocation table), then looks for
a position in the reference's `.text` where every unmasked byte agrees.  A
16-byte run free of both is used as the `bytes.find` pre-filter.

Usage:
    python3 scripts/locate_sections.py build/split_poc/defs build/split_poc/split
    python3 scripts/locate_sections.py --json ...
"""

from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from map_libcmt import IMAGE_BASE, Reference  # noqa: E402
from split_coff import Coff  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
MIN_FIXED = 0.3
MIN_RUN = 8
MAX_FULL_SCAN = 4096


def candidate_mask(coff: Coff, index: int) -> tuple[bytes, list[bool]]:
    sec = coff.sections[index]
    body = bytearray(coff.section_body(index))
    mask = [False] * len(body)
    for rva, _sym, _typ in coff.section_relocs(index):
        for k in range(4):
            if rva + k < len(body):
                mask[rva + k] = True
    i = 0
    while i < len(body):
        if body[i] in (0xE8, 0xE9):
            for k in range(1, 5):
                if i + k < len(body):
                    mask[i + k] = True
            i += 5
            continue
        i += 1
    return bytes(body), mask


def longest_fixed_run(body: bytes, mask: list[bool]) -> tuple[int, int]:
    best = (0, 0)
    start = 0
    for i in range(len(body) + 1):
        if i == len(body) or mask[i]:
            if i - start > best[1] - best[0]:
                best = (start, i)
            start = i + 1
    return best


def locate(ref: Reference, body: bytes, mask: list[bool]) -> int | None:
    fixed = sum(1 for m in mask if not m)
    if fixed < MIN_FIXED * len(body) or len(body) < 8:
        return None
    a, b = longest_fixed_run(body, mask)
    for name, va, vs, rp in ref.sections:
        if name != ".text":
            continue
        blob = ref.img[rp:rp + vs]
        starts = []
        if b - a >= MIN_RUN:
            pos = blob.find(body[a:b])
            while pos >= 0:
                starts.append(pos - a)
                pos = blob.find(body[a:b], pos + 1)
        elif len(body) <= MAX_FULL_SCAN:
            # Heavily relocated code (the thunk block is 14 fixed bytes in 42)
            # has no long run to pre-filter on; scan every position.
            starts = range(0, len(blob) - len(body) + 1)
        for start in starts:
            if not 0 <= start <= len(blob) - len(body):
                continue
            ok = True
            for k in range(len(body)):
                if not mask[k] and blob[start + k] != body[k]:
                    ok = False
                    break
            if ok:
                return IMAGE_BASE + va + start
    return None


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("dirs", nargs="*", default=[], help="directories of COFF objects")
    ap.add_argument("--members", action="store_true",
                    help="instead of object directories, scan every .text section "
                         "of every member of --lib and emit map entries")
    ap.add_argument("--lib", action="append", default=[])
    ap.add_argument("--map", help="existing map JSON; its member+section pairs are skipped")
    ap.add_argument("--from-va", default="0x1001a140")
    ap.add_argument("--target-bin", default="original/Server/server.dll")
    ap.add_argument("--json", action="store_true")
    args = ap.parse_args()

    ref = Reference(ROOT / args.target_bin)

    if args.members:
        from split_coff import ar_members, name_resolver
        known = set()
        if args.map:
            for e in json.loads((ROOT / args.map).read_text())["matched"]:
                known.add((e["member"], e.get("section")))
        floor = int(args.from_va, 16)
        by_name: dict[str, bytes] = {}
        for spec in args.lib:
            lp = Path(spec)
            lp = lp if lp.is_absolute() else ROOT / lp
            ar = ar_members(lp.read_bytes())
            resolve = name_resolver(ar)
            for raw, obj in ar:
                by_name.setdefault(resolve(raw), obj)
        out = []
        for member, obj in sorted(by_name.items()):
            try:
                coff = Coff(obj)
            except Exception:
                continue
            for i, sec in enumerate(coff.sections):
                if not sec["name"].startswith(b".text") or sec["raw_size"] < 8:
                    continue
                if (member, i + 1) in known:
                    continue
                sym = next((x["name"] for x in coff.symbols
                            if x is not None
                            and x["section"] == i + 1
                            and x["storage_class"] == 2),
                           ".text")
                body, mask = candidate_mask(coff, i)
                va = locate(ref, body, mask)
                if va and va >= floor:
                    out.append({"va": hex(va), "name": sym, "size": len(body),
                                "member": member, "symbol": sym, "section": i + 1})
        out.sort(key=lambda e: int(e["va"], 16))
        print(json.dumps({"matched": out}, indent=1))
        return 0

    rows = []
    for d in args.dirs:
        for f in sorted((ROOT / d).glob("*.obj")):
            try:
                coff = Coff(f.read_bytes())
            except Exception:
                continue
            for i, sec in enumerate(coff.sections):
                if not sec["name"].startswith(b".text") or sec["raw_size"] < 8:
                    continue
                body, mask = candidate_mask(coff, i)
                va = locate(ref, body, mask)
                rows.append((f.name, i, len(body), va))
    rows.sort(key=lambda r: (r[3] is None, r[3] or 0))
    if args.json:
        print(json.dumps([{"obj": o, "section": s, "size": n,
                           "va": (hex(v) if v else None)}
                          for o, s, n, v in rows], indent=1))
        return 0
    found = sum(1 for r in rows if r[3])
    print(f"{found} of {len(rows)} sections located in the reference's .text")
    for name, sec, size, va in rows:
        print(f"  {name:34} sec{sec} {size:5} B  "
              f"{hex(va) if va else 'NOT FOUND'}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
