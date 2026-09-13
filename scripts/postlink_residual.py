#!/usr/bin/env python3
"""How far is the build from byte identity, *after* postlink's fixers?

`rebrew postlink` refuses a build whose layout-map coverage is under 90%, which
is the safety check that makes its fixed-offset rewrites sound — so on the way to
100% there is no command that answers "how many bytes are left".  This applies
the three fixers anyway (`rebrew.postlink.FIXERS`, no `check_text_alignment`),
diffs the result against the reference section by section, and attributes the
`.text` bytes that remain to the functions `rebrew verify` reports as not
byte-matched.

Read the result as the *remaining work*: everything outside `.text` (headers,
`.rdata`, `.data`, `.reloc`, file size) is either produced by the link already or
copied from the layout package, so if those sections differ the pipeline has a
bug, and the `.text` residue is the code that still has to be made to match.

Usage:
    python3 scripts/postlink_residual.py                    # build/split_poc.dll
    python3 scripts/postlink_residual.py --built build/server_probe.dll -v
"""

from __future__ import annotations

import argparse
import contextlib
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT))

from rebrew.binary_loader import load_binary  # noqa: E402
from rebrew.layout_meta import load_package  # noqa: E402
from rebrew.postlink import FIXERS, FIXER_ORDER, _binary_info_from_bytes  # noqa: E402

IMAGE_BASE = 0x10000000


def sections(raw: bytes) -> dict[str, tuple[int, int, int, int]]:
    """name -> (va, vsize, raw_ptr, raw_size)."""
    pe = struct.unpack_from("<I", raw, 0x3C)[0]
    nsec = struct.unpack_from("<H", raw, pe + 6)[0]
    opt = struct.unpack_from("<H", raw, pe + 20)[0]
    out = {}
    for i in range(nsec):
        off = pe + 24 + opt + i * 40
        name = raw[off : off + 8].rstrip(b"\0").decode()
        vs, va, rs, rp = struct.unpack_from("<IIII", raw, off + 8)
        out[name] = (va, vs, rp, rs)
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--built", default="build/split_poc.dll")
    ap.add_argument("--reference", default="original/Server/server.dll")
    ap.add_argument("--layout", default="layout/server.dll")
    ap.add_argument("--results", default=".scratch/verify_full.json",
                    help="rebrew verify --full --json output, for attribution")
    ap.add_argument("-v", "--verbose", action="store_true")
    args = ap.parse_args()

    built_path = ROOT / args.built
    meta = load_package(ROOT / args.layout)
    info_b = load_binary(built_path)
    built = bytearray(info_b.data)
    for name in FIXER_ORDER:
        before = bytes(built)
        with contextlib.suppress(ValueError):
            info_b = _binary_info_from_bytes(bytes(built), built_path)
        report = FIXERS[name](built, meta, info_b)
        print(f"{name:11s} changed={before != bytes(built)} {report.stats}")

    ref = (ROOT / args.reference).read_bytes()
    pat = bytes(built)
    print(f"\nreference {len(ref)} bytes, patched {len(pat)} bytes, delta {len(pat) - len(ref):+d}")
    sr, sp = sections(ref), sections(pat)
    for name in sorted(set(sr) | set(sp)):
        if name not in sr or name not in sp:
            print(f"{name:9s} MISSING on one side")
            continue
        vr, v_r, pr_r, rs_r = sr[name]
        vp, v_p, pr_p, rs_p = sp[name]
        span = min(rs_r, rs_p)
        diff = sum(1 for i in range(span) if ref[pr_r + i] != pat[pr_p + i])
        print(f"{name:9s} raw {rs_r:#7x}/{rs_p:#7x}  vs {v_r:#9x}/{v_p:#9x}  differing {diff:#7x}")
    hdr = min(sr[".text"][2], sp[".text"][2])
    print(f"{'headers':9s} differing {sum(1 for i in range(hdr) if ref[i] != pat[i]):#x} of {hdr:#x}")

    # ---- attribution of the remaining .text bytes ----
    t_rva, t_vs, t_ptr, _ = sr[".text"]
    p_rva, p_vs, p_ptr, _ = sp[".text"]
    n = min(t_vs, p_vs)
    diffs = [i for i in range(n) if ref[t_ptr + i] != pat[p_ptr + i]]
    print(f"\n.text differing {len(diffs):#x} of {n:#x} ({100.0 * len(diffs) / n:.2f}%)")
    results = ROOT / args.results
    if not results.exists():
        return 0
    bad = [
        (int(r["va"], 16) - IMAGE_BASE - t_rva, r["size"], r["name"])
        for r in json.loads(results.read_text())["results"]
        if (r.get("delta") or 0) > 0 or r.get("status") in ("STUB", "SIZE_MISMATCH")
    ]
    if not bad:
        return 0

    def owner(off: int) -> str | None:
        for lo, size, name in bad:
            if lo <= off < lo + size:
                return name
        return None

    counts: dict[str, int] = {}
    first: dict[str, int] = {}
    for i in diffs:
        key = owner(i) or "<outside the non-matching functions>"
        counts[key] = counts.get(key, 0) + 1
        first.setdefault(key, i)
    print(f"{'function':40s} {'bytes':>6s} {'1st diff':>10s}")
    for name, count in sorted(counts.items(), key=lambda kv: -kv[1]):
        if args.verbose or count > 8 or name.startswith("<"):
            print(f"{name[:40]:40s} {count:6d} {first[name] + t_rva + IMAGE_BASE:#10x}")
    outside = counts.get("<outside the non-matching functions>", 0)
    print(f"\n{len(diffs) - outside:#x} of {len(diffs):#x} differing bytes are inside the "
          f"{len(bad)} functions `rebrew verify` reports as not byte-matched; "
          f"{outside:#x} are not")
    return 0


if __name__ == "__main__":
    sys.exit(main())
