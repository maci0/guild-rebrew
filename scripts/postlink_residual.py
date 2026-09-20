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

#: How far either side of a reference operand slot the symbol pass may look for a
#: shifted copy of it.  A compile difference moves an instruction by a byte or
#: two, rarely more; the bound keeps the search inside the instruction.
_SYM_WINDOW = 16

#: The reference's `.data` VA range.  `.rdata`/IAT slots below it belong to the
#: imports fixer and must not be re-pointed here.
_DATA_LO = 0x10027000
_DATA_HI = 0x1176759C

import argparse
import contextlib
import json
import re
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

    # The check above compares sources against the LINK OUTPUT, which misses the
    # step in between: `split_link.sh` consumes CMake's prebuilt objects, so
    # editing a source and re-linking without re-compiling relinks the STALE
    # object and the figure does not move.  Round 201 lost a measurement to
    # exactly that -- a `.data` probe read as a false null until `cmake --build`
    # was run first.  Compare each source against its own object too.
    objdir = ROOT / "build/CMakeFiles/server_dll.dir/src"
    if objdir.exists():
        stale_objs = []
        for src in (ROOT / "src").rglob("*.c"):
            obj = objdir / src.relative_to(ROOT / "src")
            obj = obj.with_name(obj.name + ".obj")
            if obj.exists() and obj.stat().st_mtime_ns < src.stat().st_mtime_ns:
                stale_objs.append(src.name)
        if stale_objs:
            sample = ", ".join(stale_objs[:3])
            sys.exit(
                f"postlink_residual: {len(stale_objs)} object(s) are older than "
                f"their source ({sample}{'...' if len(stale_objs) > 3 else ''}).  "
                f"split_link.sh reuses CMake's objects, so it would relink the "
                f"stale ones: run `cmake --build build` before measuring."
            )


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--built", default="build/split_poc.dll")
    ap.add_argument("--reference", default="original/Server/server.dll")
    ap.add_argument("--symbol-pass", action="store_true",
                    help="re-point stale .data operands by linker-map symbol instead of "
                         "by offset.  Default OFF: measured residue 8,628 -> 8,629 "
                         "(net +1), so it is a correctness fix, not a residue win "
                         "-- see docs/codegen-walls.md section 47")
    ap.add_argument("--link-map", default="build/split_poc.map",
                    help="linker map naming the symbol at each raw-link address; "
                         "lets the symbol pass recover operands the offset-based "
                         "fixers cannot reach")
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

    # ---- symbol-addressed operands the offset-based fixers cannot reach ----
    # `_fix_data` and the locality pass above both work by reference OFFSET, so
    # both miss an operand whose instruction has shifted.  That happens whenever
    # a function's codegen differs by a byte or two: the reference's operand slot
    # and ours are at different addresses, the rewrite lands on the neighbour,
    # and the value stays at its RAW-LINK address.  Measured on gm_AllocSpieler:
    # the reference's `mov edi,[0x10035434]` (g_citizen_count) appears in the
    # deliverable as `mov edi,[0x117665e4]`.
    #
    # This is a correctness defect, not only residue.  `_fix_data` copies the
    # reference's `.data` over ours, so a raw-link address now points at whatever
    # the REFERENCE holds there -- a different global.  The shipped DLL reads the
    # wrong variable.
    #
    # The linker map is the way out: it records the symbol each raw-link address
    # belongs to, and the data metadata gives that symbol's reference address, so
    # the rewrite does not need position at all.
    sym_recovered: list[tuple[int, int, int, str]] = []
    map_path = ROOT / args.link_map
    if args.symbol_pass and map_path.exists():
        raw_to_sym: dict[int, str] = {}
        _sym_re = re.compile(
            r"^\s+[0-9a-f]{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{8})\s+(\S+)"
        )
        for line in map_path.read_text(errors="replace").splitlines():
            m = _sym_re.match(line)
            if m:
                raw_to_sym[int(m.group(2), 16)] = m.group(1).lstrip("_")
        name_to_ref: dict[str, int] = {}
        _meta_path = ROOT / "src/rebrew-data.toml"
        if _meta_path.exists():
            for _key, _body in re.findall(
                r'\["SERVER\.(0x[0-9a-f]+)"\]\n((?:[^\[]*))', _meta_path.read_text()
            ):
                _n = re.search(r'name = "([^"]+)"', _body)
                if _n:
                    name_to_ref[_n.group(1).lstrip("_")] = int(_key, 16)
        if raw_to_sym and name_to_ref:
            tb = bytearray(pat)
            _tva2, _tvs2, _tptr2, _traw2 = sections(pat)[".text"]
            # Only positions in the neighbourhood of a REFERENCE operand slot are
            # eligible.  A blind sweep of `.text` also walks jump tables, and a
            # table entry that happens to equal a raw-link symbol address gets
            # rewritten into nonsense -- measured: a blind sweep rewrote 88 values
            # and took the residue UP by 29 bytes.  `meta.operands` holds only real
            # operand slots, so a window around them is the safe search space.
            eligible = {
                _tptr2 + off + d
                for off in meta.operands
                for d in range(-_SYM_WINDOW, _SYM_WINDOW + 1)
                if 0 <= off + d < _traw2 - 4
            }
            for i in sorted(eligible):
                cur = struct.unpack_from("<I", tb, i)[0]
                sym = raw_to_sym.get(cur)
                if not sym:
                    continue
                ref_va = name_to_ref.get(sym)
                if ref_va is None or ref_va == cur:
                    continue
                # `.rdata`/IAT slots belong to `_fix_imports`, which already
                # rewrites them correctly; our map's symbol ordering there does
                # NOT reproduce the reference's IAT layout, so re-pointing them
                # from this pass undoes that fixer's work (measured: it takes the
                # residue UP).  Only `.data`-resident symbols are ours.
                if ref_va < _DATA_LO or ref_va >= _DATA_HI:
                    continue
                if not (_DATA_LO <= cur < _DATA_HI):
                    continue
                struct.pack_into("<I", tb, i, ref_va)
                sym_recovered.append((i - _tptr2, cur, ref_va, sym))
            if sym_recovered:
                pat = bytes(tb)
                print(f"symbols     recovered {len(sym_recovered)} stale operand(s) "
                      f"by linker map, e.g. "
                      + ", ".join(
                          f".text+{o:#x} {c:#x}->{v:#x} ({s})"
                          for o, c, v, s in sym_recovered[:4]
                      ))

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
        # Guard the guard.  This block only means anything when `built_path` is
        # the RAW link.  `--write` rewrites its output in place, and the CMake
        # POST_BUILD step does the same to build/server.dll, so pointing
        # `--built` at an already-postlinked image makes every line below read
        # 0.0% -- restoring precisely the self-certification this block was
        # added (round 450) to prevent.  `.data` is blitted wholesale from the
        # layout package, so a raw link matching it exactly is not a triumph,
        # it is the tell that we are measuring the answer key.
        _dr, _dvs, d_rp, d_rr = sr[".data"]
        _sr2, _svs, d_sp, d_sr = ss[".data"]
        if d_rr == d_sr and ref[d_rp : d_rp + d_rr] == pre[d_sp : d_sp + d_sr]:
            print("  !! .data is byte-identical to the reference, which the raw link"
                  " cannot produce.", file=sys.stderr)
            print(f"  !! {built_path} looks ALREADY POSTLINKED, so the percentages"
                  " below are meaningless.", file=sys.stderr)
            print("  !! Pass the raw link instead (build/split_poc.dll), or run with"
                  " no --built.", file=sys.stderr)
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
    hidden = 0
    for name, count in sorted(counts.items(), key=lambda kv: -kv[1]):
        if args.verbose or count > 8 or name.startswith("<"):
            print(f"{name[:40]:40s} {count:6d} {first[name] + t_rva + IMAGE_BASE:#10x}")
        else:
            hidden += 1
    # A row that is filtered out is still residue.  Round 1073: the default view
    # hid every carrier at or below 8 bytes -- `gm_CalculateProductionValue` (5) --
    # so the table read 18 rows summing to 8623 while the summary line below said
    # all 8628 were inside the 19 functions.  Nothing was wrong with the
    # measurement, but the table could not be reconciled with it, and a reader who
    # summed the rows would conclude the tool was broken.  Say how many rows are
    # suppressed and what they total, so the column always reconciles.
    if hidden:
        hid = sum(c for n, c in counts.items() if c <= 8 and not n.startswith("<"))
        print(f"{'(' + str(hidden) + ' more carrier(s) <= 8 bytes, hidden':40s} "
              f"{hid:6d} {'':>10s}")
    print(f"{'total':40s} {sum(counts.values()):6d}")
    outside = counts.get("<outside the non-matching functions>", 0)
    print(f"\n{len(diffs) - outside:#x} of {len(diffs):#x} differing bytes are inside the "
          f"{len(bad)} functions `rebrew verify` reports as not byte-matched; "
          f"{outside:#x} are not")
    return 0


if __name__ == "__main__":
    sys.exit(main())
