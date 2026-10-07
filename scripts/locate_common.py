#!/usr/bin/env python3
"""Reference address of every data symbol, by pairing `.text` offsets.

Why this exists (round 100).  The last unplaced thing in the binary is the
linker's placement of the COMMON pool: 135 symbols, 24,330,148 bytes, whose
order C cannot influence (round 91: CL emits COMMON in its own table order) and
whose content cannot identify them (round 96: a pooled symbol has no bytes).

But there is a third source.  Our link is **position-aligned**: its `.text` and
the reference's are the same length and the same addresses, so the operand at
`.text`+i holds *our* value in the built image and the *reference's* value in the
target.  Wherever a built operand names a symbol, the same offset in the
reference names the same object, at its reference address.

    for i in range(len(text) - 3):
        ours = u32(built_text, i)
        name = symbol_at.get(ours)
        if name: reference[name].add(u32(reference_text, i))

Validation: the method is not assumed.  Four addresses it produces -- `FPinit`
0x100317d8, `dstend` 0x10034028, `FloatFormat` 0x10034148, `rgcode_page_info`
0x10034168 -- were also derived independently in round 97 by content matching
plus anchor arithmetic, and all four agree.

A symbol with more than one distinct vote is ambiguous and is dropped: a small
integer's bit pattern can coincide with an address.  That is what `conflicts`
counts, and it is why the tool reports "unique" and not "found".

Usage:
    python3 scripts/locate_common.py --map build/split_poc.map --json
"""
from __future__ import annotations

import argparse
import json
import re
import struct
import sys
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "scripts"))

from split_coff import Coff  # noqa: E402

IMAGE_BASE = 0x10000000
MAP_RE = re.compile(r"^\s*\d{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{8})\s+[fF]?\s*(\S+)\s*$")


def text_section(path: Path) -> bytes:
    d = path.read_bytes()
    pe = struct.unpack_from("<I", d, 0x3C)[0]
    n = struct.unpack_from("<H", d, pe + 6)[0]
    oh = struct.unpack_from("<H", d, pe + 20)[0]
    o = pe + 24 + oh
    for i in range(n):
        s = o + i * 40
        if d[s:s + 8].rstrip(b"\0") == b".text":
            _vs, _va, rs, rp = struct.unpack_from("<IIII", d, s + 8)
            return d[rp:rp + rs]
    raise SystemExit(f"{path}: no .text")


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--map", default="build/split_poc.map")
    ap.add_argument("--built", default="build/split_poc.dll")
    ap.add_argument("--reference", default="original/Server/server.dll")
    ap.add_argument("--rsp", default="build/split_poc/rsp.rsp")
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--out", default=None, help="write name -> reference address")
    args = ap.parse_args()

    ours = text_section(ROOT / args.built)
    refs = text_section(ROOT / args.reference)
    if len(ours) != len(refs):
        print(f"warning: .text lengths differ ({len(ours)} vs {len(refs)}); "
              "offsets past the shorter one are skipped", file=sys.stderr)

    built = {}
    for line in (ROOT / args.map).read_text(errors="replace").splitlines():
        m = MAP_RE.match(line)
        if m:
            built.setdefault(m.group(1).lstrip("_"), int(m.group(2), 16))
    addr2sym = {v: k for k, v in built.items()}

    build = (ROOT / args.rsp).parent.parent
    common = set()
    for rel in [o.strip('"').replace("\\", "/")
                for o in (ROOT / args.rsp).read_text().split() if o.endswith(".obj")]:
        p = build / rel
        if not p.exists():
            continue
        try:
            c = Coff(p.read_bytes())
        except Exception:
            continue
        for s in c.symbols:
            if s and s["section"] == 0 and s["storage_class"] in (2, 3) and s["value"]:
                nm = s["name"]
                if isinstance(nm, bytes):
                    nm = nm.decode("ascii", "replace")
                common.add(nm.lstrip("_"))

    votes: dict[str, Counter] = {}
    n = min(len(ours), len(refs))
    for i in range(n - 3):
        s = addr2sym.get(struct.unpack_from("<I", ours, i)[0])
        if s is None:
            continue
        votes.setdefault(s, Counter())[struct.unpack_from("<I", refs, i)[0]] += 1

    unique = {s: c.most_common(1)[0][0] for s, c in votes.items() if len(c) == 1}
    ambig = {s: dict(c) for s, c in votes.items() if len(c) > 1}
    # EVERY uniquely-located symbol, not only the COMMON ones.  Filtering to
    # COMMON hid `_tzapiused` and `___setlc_active` (round 105), which round
    # 102's raw check had already given unique reference addresses: they are
    # section symbols in the split blobs, not COMMON, so they fell out of the
    # `common` set and were never written out -- and the emit then had no
    # address for them.
    common_unique = {s: v for s, v in unique.items() if s in common}
    all_unique = dict(unique)
    result = {
        "symbols_in_map": len(built),
        "symbols_with_votes": len(votes),
        "unique": len(unique),
        "ambiguous": len(ambig),
        "common_symbols": len(common),
        "common_unique": len(common_unique),
        "addresses": {k: v for k, v in sorted(all_unique.items(), key=lambda kv: kv[1])},
    }
    if args.json:
        print(json.dumps({k: v for k, v in result.items() if k != "addresses"}, indent=2))
        return 0
    print("symbols in the map        : %d" % result["symbols_in_map"])
    print("with at least one vote    : %d" % result["symbols_with_votes"])
    print("uniquely located          : %d" % result["unique"])
    print("ambiguous (2+ votes)      : %d" % result["ambiguous"])
    print("of which COMMON           : %d of %d located" % (result["common_unique"],
                                                            result["common_symbols"]))
    print("written (all unique)      : %d" % len(result["addresses"]))
    if args.out:
        (ROOT / args.out).write_text(json.dumps(result["addresses"], indent=1))
        print("written to %s" % args.out)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
