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
from rebrew.postlink import (  # noqa: E402
    FIXERS, FIXER_ORDER, MIN_LAYOUT_MAP_COVERAGE, _binary_info_from_bytes, _map_coverage,
)

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


def _refuse_if_stale(built: Path) -> None:
    """Refuse to measure a link output older than the sources it should contain.

    Round 172: `split_link.sh` died in its first step (a deleted LIBCMT copy)
    while the caller chained it with `;`, so five rounds of "residue unchanged"
    were actually re-measuring a stale binary.  A residue number is only
    evidence if the thing measured was produced after the inputs changed.
    """
    if not built.exists():
        sys.exit(f"postlink_residual: {built} does not exist -- the link step "
                 f"did not produce it (check its exit status).")
    built_ns = built.stat().st_mtime_ns
    newer = [p for p in (ROOT / "src").rglob("*.c") if p.stat().st_mtime_ns > built_ns]
    if newer:
        sample = ", ".join(p.name for p in newer[:3])
        sys.exit(f"postlink_residual: {built.name} is older than {len(newer)} "
                 f"source file(s) ({sample}{'...' if len(newer) > 3 else ''}).  "
                 f"Re-run the build and link before measuring; a stale binary "
                 f"reports the previous round's residue.")


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--built", default="build/split_poc.dll")
    ap.add_argument("--reference", default="original/Server/server.dll")
    ap.add_argument("--layout", default="layout/server.dll")
    ap.add_argument("--results", default=".scratch/verify_full.json",
                    help="rebrew verify --full --json output, for attribution")
    ap.add_argument("--write", default=None,
                    help="write the patched bytes to this path (the fixers run "
                         "regardless of the coverage gate; the build refuses "
                         "below 90%% because a wrong-offset patch would be "
                         "silent, and this script is the measured way around "
                         "that refusal -- see docs/TODO.md round 148)")
    ap.add_argument("-v", "--verbose", action="store_true")
    args = ap.parse_args()

    built_path = ROOT / args.built
    _refuse_if_stale(built_path)
    meta = load_package(ROOT / args.layout)
    info_b = load_binary(built_path)
    op_ok, op_tot, call_ok, call_tot = _map_coverage(bytes(load_binary(built_path).data), meta, info_b)
    cover = (op_ok + call_ok) / max(1, op_tot + call_tot)
    if cover < MIN_LAYOUT_MAP_COVERAGE:
        print(f"WARNING: layout-map coverage {100 * cover:.2f}% is below the "
              f"{100 * MIN_LAYOUT_MAP_COVERAGE:.0f}% gate; the fixers rewrite "
              f"operands by fixed offset, so bytes inside the functions that do "
              f"not match may be patched at the wrong place.  The output is an "
              f"intermediate artifact, not a runnable build.", file=sys.stderr)
    built = bytearray(info_b.data)
    for name in FIXER_ORDER:
        before = bytes(built)
        with contextlib.suppress(ValueError):
            info_b = _binary_info_from_bytes(bytes(built), built_path)
        report = FIXERS[name](built, meta, info_b)
        print(f"{name:11s} changed={before != bytes(built)} {report.stats}")

    ref = (ROOT / args.reference).read_bytes()
    pat = bytes(built)

    # ---- operand slots whose instruction neighbourhood already matches ----
    # `_fix_data` only rewrites a slot when the built value already points into
    # the reference's `.rdata`/`.data`, which is how it avoids writing reference
    # operands into instructions whose boundaries differ (441 slots are left
    # alone that way, and patching all of them would "gain" 1,698 bytes of pure
    # byte-copying -- measured, see docs/TODO.md round 155).  A handful are
    # different: the instruction around the slot is byte-identical to the
    # reference and only the operand is stale (our `cmp eax, 0x117f65b4` against
    # the reference's `cmp eax, 0x10139820`, where the split layout put the
    # table's end past the reference's `.data`).  Those are the fixer's job, and
    # the locality test is what separates them from the 437: 12 bytes either
    # side must match outside the other operand slots.
    _tva, _tvs, _tptr, _traw = sections(ref)[".text"]
    _bva, _bvs, _bptr, _braw = sections(pat)[".text"]
    slots = {_tptr + off for off in meta.operands}
    text = bytearray(pat)
    recovered = []

    def _same(lo: int, hi: int) -> bool:
        return all(ref[i] == text[i] for i in range(lo, hi) if i not in slots)

    for off, val in meta.operands.items():
        i = _tptr + off
        cur = struct.unpack_from("<I", text, i)[0]
        if cur == val:
            continue
        if not _same(i - 12, i) or not _same(i + 4, i + 16):
            continue
        struct.pack_into("<I", text, i, val)
        recovered.append((off, cur, val))
    if recovered:
        pat = bytes(text)
        print(f"locality    recovered {len(recovered)} stale operand(s): "
              + ", ".join(f".text+{o:#x} {c:#x}->{v:#x}" for o, c, v in recovered))

    print(f"\nreference {len(ref)} bytes, patched {len(pat)} bytes, delta {len(pat) - len(ref):+d}")
    sr, sp = sections(ref), sections(pat)
    if args.write:
        # The reference's `.text` padding beyond VirtualSize is zeros, while the
        # vehicle's tail carries link thunks the original build dead-stripped;
        # `_fix_data` preserves that tail deliberately (it must, for a build that
        # already matches), so normalize it here instead.
        _tva, _tvs, _tptr, _traw = sr[".text"]
        _pva, _pvs, _pptr, _praw = sp[".text"]
        _pad = ref[_tptr + _tvs:_tptr + _traw]
        if (len(_pad) == _praw - _pvs and _pad.strip(b"\x00") == b""
                and pat[_pptr + _pvs:_pptr + _praw] != _pad):
            pat = pat[:_pptr + _pvs] + _pad + pat[_pptr + _praw:]
            print(f"normalized {len(_pad)} bytes of .text padding")
        out = ROOT / args.write
        out.write_bytes(pat)
        print(f"wrote {out} ({len(pat)} bytes)")
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

    # The non-.text zeros above are SELF-CERTIFYING: the postlink fixers blit
    # reference bytes shipped inside layout/server.dll/ over those regions
    # (data.hex and reloc.hex are verbatim reference slices -- verified byte for
    # byte in round 199).  So "differing 0x0" outside .text says nothing about
    # whether the build can PRODUCE those bytes.  Report the raw link's own
    # divergence too, measured before the fixers run, so the metric stops
    # grading its own answer key.
    # `pat` is the post-fixer image; built_path holds the raw link output.
    if built_path.exists():
        pre = built_path.read_bytes()
        ss = sections(pre)
        print("\nraw link vs reference (pre-fixer -- what the build actually produces):")
        total = 0
        for name in (".text", ".rdata", ".data", ".reloc"):
            if name not in sr or name not in ss:
                continue
            _vr, _v_r, pr_r, rs_r = sr[name]
            _vs, _v_s, pr_s, rs_s = ss[name]
            span = min(rs_r, rs_s)
            d = sum(1 for i in range(span) if ref[pr_r + i] != pre[pr_s + i])
            if name != ".text":
                total += d
            print(f"  {name:9s} differing {d:#7x} of {span:#7x}"
                  f" ({100.0 * d / span:.1f}%)")
        h = min(sr[".text"][2], ss[".text"][2])
        hd = sum(1 for i in range(h) if ref[i] != pre[i])
        total += hd
        print(f"  {'headers':9s} differing {hd:#7x} of {h:#7x} ({100.0 * hd / h:.1f}%)")
        print(f"  non-.text total the fixers overwrite: {total:#x} ({total} bytes)")

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

    # A function's recorded `size` is its BODY size, but msvc6 emits switch jump
    # tables and case-index maps AFTER the body inside the same COMDAT.  Attributing
    # strictly by [lo, lo+size) therefore files those trailing structures as
    # "outside", which under-reports the owner and invents a phantom category.
    # Round 186: vfs_OpenStream's five jump-table bytes at 0x100092bc read as
    # unattributed because its body ends at +0x82bb -- one nop short of the table.
    # Extend each extent to the next function start so a body's trailing tables are
    # credited to it, while still never crossing into another tracked function.
    starts = sorted(lo for lo, _size, _name in bad)
    extents = []
    for lo, size, name in bad:
        nxt = next((s for s in starts if s > lo), None)
        end = lo + size if nxt is None else min(max(lo + size, nxt), nxt)
        extents.append((lo, end, name))

    def owner(off: int) -> str | None:
        for lo, end, name in extents:
            if lo <= off < end:
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
