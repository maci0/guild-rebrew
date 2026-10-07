#!/usr/bin/env python3
"""Move whole `.data`/`.bss` sections to their reference addresses.

Why a section emitter rather than the per-symbol one (round 85).

`scripts/emit_data_symbols.py` emits one object per *symbol*, and
`strip_data_sections` refuses to drop a section unless the fragment supplies
every symbol in it.  Measured in round 84: the fragment covered **136 of 870**
data symbols, so **all 343** sections were kept and nothing could move.  Closing
that needs 734 more symbols named in the manifest -- a reversing task.

A section needs none of that.  A `.data`/`.bss` section is a contiguous byte
range, so placing one needs its reference *start* and its size, not a name per
symbol.  And the reference's `.data` is byte-identical to ours at the same file
offsets (round 55: 26 bytes differ out of 57,344, best constant shift 0), so a
section's start is findable by content.

Placement, in increasing cost:
  1. a unique match for any 32/24/16-byte window at the section's front,
     middle, quarter or tail -- **probe several windows, not one**: a section
     beginning `00 00 00 00` matches a hundred places while the same section's
     middle usually matches exactly one;
  2. the same search confined to the window after the previously located
     section, for sections that repeat;
  3. chaining: try each surviving candidate and keep the one that lets the
     *next* section match contiguously.

Usage:
    python3 scripts/emit_data_sections.py --out build/data_sections \\
        --rsp build/split_poc/rsp.rsp
"""
from __future__ import annotations

import argparse
import json
import struct
import sys
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "scripts"))

from split_coff import Coff  # noqa: E402

IMAGE_BASE = 0x10000000
#: the on-disk part of `.data`: past it the section is uninitialised and has no
#: bytes to match against.
DATA_RVA = 0x27000
DATA_ONDISK = 0xE000


def sections_of(objects, build: Path):
    """(built_offset, bytes, object, section_name) for every game data section."""
    out = []
    for rel in objects:
        p = build / rel
        if not p.exists() or "CMakeFiles" not in rel:
            continue
        try:
            c = Coff(p.read_bytes())
        except Exception:
            continue
        for i, s in enumerate(c.sections):
            if s["name"].rstrip(b"\0") not in (b".data", b".bss") or not s["raw_size"]:
                continue
            if s["raw_ptr"] + s["raw_size"] > DATA_ONDISK:
                continue          # runs past the initialised part: nothing to match
            out.append((c.data[s["raw_ptr"]:s["raw_ptr"] + s["raw_size"]],
                        p.name, s["name"].rstrip(b"\0").decode(), i))
    return out


def section_symbols(objs, build: Path):
    """(object, section index) -> [(symbol name, in-section offset)].

    A relocated section must bring its symbols with it.  An emitted object that
    carries only a section symbol leaves every reference to `g_log_format_table`
    and its siblings unresolved -- 435 of them on the first attempt, and the link
    stops before it can be judged.
    """
    out: dict[tuple[str, int], list[tuple[str, int]]] = {}
    for rel in objs:
        p = build / rel
        if not p.exists() or "CMakeFiles" not in rel:
            continue
        try:
            c = Coff(p.read_bytes())
        except Exception:
            continue
        names: dict[int, list[tuple[str, int]]] = {}
        for sym in c.symbols:
            if not sym or sym["storage_class"] not in (2, 3) or sym["section"] < 1:
                continue
            idx = sym["section"] - 1
            n = sym["name"]
            if not isinstance(n, str):
                continue
            names.setdefault(idx, []).append((n, sym["value"]))
        for idx, syms in names.items():
            out[(p.name, idx)] = syms
    return out


def walk_build_order(sections, built: bytes):
    """Order sections by where they actually sit in OUR .data.

    Content search, forward-only first, because two sections can share bytes.
    A section that cannot be found from the cursor falls back to a global search.
    """
    placed = []
    cur = 0
    for blob, name, sec, secidx in sections:
        j = built.find(blob, cur)
        if j < 0:
            j = built.find(blob)
        if j < 0:
            continue
        placed.append((j, blob, name, sec, secidx))
        cur = j + len(blob)
    placed.sort()
    return placed


def candidates(blob: bytes, ref: bytes, lo: int, hi: int) -> list[int]:
    """Reference offsets where this section's bytes appear, best window first.

    The windows are tried in order and the FIRST one with exactly one hit wins;
    positions are never unioned across windows.  Unioning is much stricter and
    costs half the yield: a section that matches 3 places on its front and 1
    place on its middle is uniquely placed by the middle, and a union would
    report 3 and reject it.
    """
    fallback: set[int] = set()
    # Short sections need short probes: 34 of the 36 that stayed unlocated are
    # 1-10 bytes, and a 16-byte window never fits inside them.  The whole section
    # is used as the pattern when it is smaller than the shortest window.
    if len(blob) < 16:
        pat = blob
        if not any(pat):
            return []
        hits = {j for j in range(max(0, lo), hi - len(pat) + 1)
                if ref[j:j + len(pat)] == pat}
        return sorted(hits)
    for ln in (32, 24, 16):
        for off in (0, len(blob) // 4, len(blob) // 2, max(0, len(blob) - ln)):
            if off + ln > len(blob):
                continue
            pat = blob[off:off + ln]
            if not any(pat):
                continue
            hits = {j - off for j in range(max(0, lo - off), hi - ln + 1)
                    if ref[j:j + ln] == pat}
            if len(hits) == 1:
                return list(hits)
            fallback |= hits
    return sorted(fallback)


def locate(placed, ref: bytes, report):
    """Assign each section a reference offset, left to right.

    Offsets already claimed are excluded from later searches.  Without this, 30
    distinct sections all matched 0x2c748: a run of identical bytes (usually
    zeros) matches wherever that pattern occurs, so they collapsed onto one
    address instead of being told apart.
    """
    last = 0
    used: set[int] = set()
    result = [None] * len(placed)
    # Locate the BIG sections first.  A greedy left-to-right walk lets one wrong
    # small-section match claim an offset and block the section that really
    # belongs there; the large sections are unambiguous, so they establish the
    # map first and the small ones fill in around them.  Emission order is
    # restored afterwards, so the response file still goes by reference address.
    order = sorted(range(len(placed)), key=lambda i: -len(placed[i][1]))
    for i in order:
        boff, blob, name, sec, secidx = placed[i]
        rec = {"object": name, "section": sec, "built_offset": boff,
               "size": len(blob), "reference": None, "how": None,
               "section_index": secidx}
        if not any(blob):
            rec["how"] = "zero-body"
            report["zero_body"] += 1
            result[i] = rec
            continue
        cands = [c for c in candidates(blob, ref, 0, len(ref)) if c not in used]
        if len(cands) == 1:
            hit, how = cands[0], "unique"
        else:
            # constrain to just after the previous section, then re-ask
            narrow = [c for c in candidates(blob, ref, last, min(len(ref), last + 0x8000))
                      if c not in used]
            if len(narrow) == 1:
                hit, how = narrow[0], "windowed"
            elif len(narrow) > 1:
                # chaining: prefer the candidate that abuts the previous one
                adj = [c for c in narrow if last <= c < last + 0x40]
                if len(adj) == 1:
                    hit, how = adj[0], "chained"
                else:
                    hit, how = None, "ambiguous"
            else:
                hit, how = (narrow[0], "ambiguous") if narrow else (None, "no-match")
        if hit is None:
            report[how] += 1
        else:
            report[how] += 1
            rec["reference"] = IMAGE_BASE + DATA_RVA + hit
            rec["how"] = how
            used.add(hit)
            last = max(last, hit + len(blob))
        result[i] = rec

    # --- chaining pass -------------------------------------------------
    # Walk the sections in BUILD order and fit the leftovers into the gaps
    # between the ones already placed.  In the build a section sits directly
    # after its predecessor, so if the predecessor is placed and the successor
    # is placed, the leftover's reference start is pinned: it must begin where
    # the predecessor ends (or at the successor's start minus its own size).
    # This needs no metadata and no candidate search.
    # Each placement creates anchors for its neighbours, so one sweep is not
    # enough: a single pass placed 1 of 73, and iterating to a fixed point
    # places the rest, because the gaps close inwards from both ends.
    changed = True
    rounds = 0
    while changed and rounds < len(placed):
        changed = False
        rounds += 1
        for i in range(len(placed)):
            if result[i] is not None and result[i]["reference"] is not None:
                continue
            blob = placed[i][1]
            if not any(blob):
                continue
            prev_end = None
            for j in range(i - 1, -1, -1):
                if result[j] is not None and result[j]["reference"] is not None:
                    prev_end = (result[j]["reference"] - IMAGE_BASE - DATA_RVA) + len(placed[j][1])
                    break
            next_start = None
            for j in range(i + 1, len(placed)):
                if result[j] is not None and result[j]["reference"] is not None:
                    next_start = result[j]["reference"] - IMAGE_BASE - DATA_RVA
                    break
            tries = []
            if prev_end is not None:
                tries.append(prev_end)
            if next_start is not None:
                tries.append(next_start - len(blob))
            for cand in tries:
                if cand < 0 or cand + len(blob) > len(ref):
                    continue
                if ref[cand:cand + len(blob)] == blob and cand not in used:
                    result[i]["reference"] = IMAGE_BASE + DATA_RVA + cand
                    result[i]["how"] = "chained"
                    used.add(cand)
                    report["chained"] += 1
                    report["no-match"] = max(0, report["no-match"] - 1)
                    changed = True
                    break
    return result


def build_section_object(name: str, body: bytes,
                         symbols: list[tuple[str, int]] | None = None,
                         bss: bool = False) -> bytes:
    """A one-section object holding exactly one section, no relocations.

    `.data` carries no relocations (round 39): the bytes hold literal reference
    addresses, so the content is already final and only the placement is at issue.
    """
    strtab = bytearray(b"\0\0\0\0")

    def name_bytes(n: str) -> bytes:
        b = n.encode("ascii")
        if len(b) <= 8:
            return b.ljust(8, b"\0")
        o = len(strtab)
        strtab.extend(b + b"\0")
        return b"\0\0\0\0" + struct.pack("<I", o)

    symtab = bytearray()
    symtab += name_bytes(".bss" if (bss or not any(body)) else ".data") + struct.pack("<IHHBB", 0, 1, 0, 3, 0)
    symtab += name_bytes(name) + struct.pack("<IHHBB", 0, 1, 0, 2, 0)
    # the section's own symbols, at their in-section offsets: without them every
    # reference to a data global it used to define is unresolved
    for sym_name_, off in symbols:
        if off > len(body) or sym_name_ in (".data", ".bss", name):
            continue
        symtab += name_bytes(sym_name_) + struct.pack("<IHHBB", off, 1, 0, 2, 0)
    sec = bytearray(40)
    # A body of zeros destined for the uninitialised region must be .bss: as
    # .data its bytes are initialised content and they grow the image (and, at
    # this size, break the link).  LINK seeks SizeOfRawData, so the zeros stay
    # in the object; the uninitialized flag is what keeps them out of the image.
    is_bss = bss or not any(body)
    sec[0:8] = b".bss\0\0\0\0" if is_bss else b".data\0\0\0"
    struct.pack_into("<I", sec, 8, len(body))
    struct.pack_into("<I", sec, 16, len(body))
    struct.pack_into("<I", sec, 20, 20 + 40)
    struct.pack_into("<I", sec, 24, 20 + 40 + len(body))
    # IMAGE_SCN_CNT_INITIALIZED_DATA | MEM_READ | MEM_WRITE, no COMDAT
    struct.pack_into("<I", sec, 36, 0xC0000080 if is_bss else 0xC0000040)
    struct.pack_into("<I", strtab, 0, len(strtab))
    symbols = symbols or []
    n = 2 + len([1 for s_, o_ in symbols
                 if o_ <= len(body) and s_ not in (".data", name)])
    header = struct.pack("<HHIIIHH", 0x14C, 1, 0, 20 + 40 + len(body), n, 0, 0)
    return header + bytes(sec) + body + bytes(symtab) + bytes(strtab)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--rsp", default="build/split_poc/rsp.rsp")
    ap.add_argument("--built", default="build/split_poc.dll")
    ap.add_argument("--reference", default="original/Server/server.dll")
    ap.add_argument("--out", default="build/data_sections")
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--manifest", default=None,
                    help="write (object, section index) -> reference offset, so the "
                         "stripper knows exactly which sections the emit owns")
    args = ap.parse_args()

    build = (ROOT / args.rsp).parent.parent
    objects = [o.strip('"').replace("\\", "/")
               for o in (ROOT / args.rsp).read_text().split() if o.endswith(".obj")]
    ref = (ROOT / args.reference).read_bytes()[DATA_RVA:DATA_RVA + DATA_ONDISK]
    built = (ROOT / args.built).read_bytes()[DATA_RVA:DATA_RVA + DATA_ONDISK]

    secs = sections_of(objects, build)
    symtab_by_section = section_symbols(objects, build)
    placed = walk_build_order(secs, built)
    report = Counter()
    located = locate(placed, ref, report)

    out_dir = ROOT / args.out
    out_dir.mkdir(parents=True, exist_ok=True)
    for stale in out_dir.glob("*.obj"):
        stale.unlink()
    emitted = []
    for (boff, blob, name, sec, secidx), rec in zip(placed, located):
        if rec is None or rec["reference"] is None:
            continue
        stem = "%08x_%s_%s" % (rec["reference"] - IMAGE_BASE, name, sec.lstrip("."))
        (out_dir / (stem + ".obj")).write_bytes(
            build_section_object("_" + stem, blob,
                                 symtab_by_section.get((name, secidx), [])))
        emitted.append(rec)
    # the response file must go by REFERENCE address, not by the order the
    # locator happened to walk
    emitted.sort(key=lambda r: r["reference"])

    if args.manifest:
        (ROOT / args.manifest).write_text(json.dumps(
            [{"object": r["object"], "section_index": r["section_index"],
              "reference": r["reference"], "size": r["size"]}
             for r in located if r and r["reference"] is not None], indent=1))
        print(f"manifest written to                 : {args.manifest}")

    placed_n = len(placed)
    good = sum(1 for r in located if r["reference"] is not None)
    summary = {
        "sections_seen": len(secs),
        "placed_in_build": placed_n,
        "located": good,
        "coverage_pct": round(100.0 * good / max(1, placed_n), 1),
        "by_method": dict(report),
        "bytes": sum(r["size"] for r in located if r["reference"] is not None),
    }
    if args.json:
        print(json.dumps({"summary": summary, "sections": located}, indent=2))
        return 0
    print(f"game .data/.bss sections seen   : {summary['sections_seen']}")
    print(f"placed in our build             : {placed_n}")
    for k in ("unique", "windowed", "chained", "ambiguous", "no-match", "zero-body"):
        if report.get(k):
            print(f"  {k:<12}: {report[k]}")
    print(f"located                        : {good} ({summary['coverage_pct']}%)")
    print(f"bytes emitted                  : {summary['bytes']}")
    print(f"written to                     : {args.out}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
