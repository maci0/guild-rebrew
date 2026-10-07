#!/usr/bin/env python3
"""Place `.data` by explicit emit, instead of leaving it to the COMMON pool.

Round 92 measured what this is worth: 4,419 -> 4,058 differing `.text` bytes,
with the small-COMMON group landing within a single 0x827 shift of the
reference.  The mechanism, in three parts:

  1. **Sections.**  `emit_data_sections.py` locates each game `.data`/`.bss`
     section in the reference by content (98.8% of them) and emits it as its own
     object, carrying the section's symbol table.
  2. **COMMON symbols.**  Each COMMON symbol with a reference address in the
     metadata becomes its own object too, emitted into `.bss` (uninitialised),
     because that is what a pooled COMMON symbol is -- emitting them as
     initialised `.data` adds their bytes to the file.
  3. **Order.**  The emitted objects are merged into the link line by reference
     `.data` address against the objects that have one, and their originals are
     stripped so the game objects contribute no `.data` of their own.

Ordering is a stable merge, not a sort: an object with no known address keeps
the slot it already has.  A plain sort sends every unkeyed object to the end and
costs 26x the difference (round 89).

Usage:
    python3 scripts/apply_data_emit.py --link
"""
from __future__ import annotations

import argparse
import json
import re
import subprocess
import sys
import tomllib
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "scripts"))

from split_coff import Coff  # noqa: E402
from emit_data_symbols import build_data_object, strip_data_sections  # noqa: E402
from emit_data_sections import build_section_object  # noqa: E402

MAP_RE = re.compile(r"^\s*\d{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{8})\s+[fF]?\s*(\S+)\s*$")
DATA_LO, DATA_HI = 0x10027000, 0x11767600
#: Only COMMON symbols the reference places at or beyond this belong in the
#: emit.  Below it, `.data` is already byte-exact (round 57: 247 of 249 tracked
#: symbols have the right bytes at the right address), and emitting those six
#: measured worse -- 4,572 against round 92's 4,058.
BSS_LO = 0x10035000
#: above this a "size" is a manifest artefact, not an object (see below)
MAX_EMIT_SIZE = 0x10000
#: The sparse placeholders.  `link_stubs.c` sizes these "to fit the .data VS"
#: -- the real bytes come from the restore gap -- so their declared extent is
#: 8x (g_connections) or 79x (g_bss_tail) too small, and a derived or
#: manifest size makes them look like small objects.  Packing one gives it a
#: slot a few hundred bytes long and the real array is lost: 101 LNK2001 for
#: `_g_connections` alone.  Never emit or pack these; leave the pool to them.
SPARSE_PLACEHOLDERS = {"g_connections", "g_bss_tail", "g_player_slot_overflow_pad"}
#: the emitted blocks go in here, which is inside the game's data region and
#: before the CRT band that must stay last (round 32/34).
ANCHOR = "rdata_restore.c.obj"


def reference_addresses() -> dict[str, int]:
    data = tomllib.loads((ROOT / "src" / "rebrew-data.toml").read_text())
    out = {}
    for k, v in data.items():
        if not isinstance(v, dict) or not isinstance(v.get("name"), str):
            continue
        t, _, a = str(k).rpartition(".")
        if t != "SERVER":
            continue
        try:
            out[v["name"]] = int(a, 16)
        except ValueError:
            pass
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--rsp", default="build/split_poc/rsp.rsp")
    ap.add_argument("--map", default="build/split_poc.map")
    ap.add_argument("--sections", default="build/data_sections")
    ap.add_argument("--common", default="build/common_split")
    ap.add_argument("--addresses", default="build/common_addresses.json",
                    help="locate_common.py output: name -> reference address")
    ap.add_argument("--stripped", default="build/data_stripped")
    ap.add_argument("--out-rsp", default="build/split_poc/rsp_emit_all.rsp")
    ap.add_argument("--link", action="store_true")
    ap.add_argument("--pack-data", action="store_true",
                    help="emit packed runs as initialised .data instead of .bss")
    ap.add_argument("--pack-limit", type=int, default=0,
                    help="emit at most this many packed runs (0 = all)")
    ap.add_argument("--pack", action="store_true",
                    help="pack relocated symbols into contiguous runs, one "
                         ".bss section per run.  Off by default: measured to "
                         "break the link at every gap size tried (0/4/16/0x40), "
                         "including with only 120 objects against the 143 that "
                         "link.  The mechanism is right -- LINK's ceiling is on "
                         "section count -- but the packed section itself is "
                         "rejected; see docs/TODO.md round 111")
    ap.add_argument("--pack-gap", type=int, default=0x40,
                    help="maximum zero gap to bridge when packing relocated "
                         "symbols into one .bss object")
    ap.add_argument("--emit-size", type=int, default=0,
                    help="force every relocated object to this many bytes "
                         "(0 = use the real size); used to tell LINK's "
                         "SetupPhase ceiling of sections apart from VirtualSize")
    ap.add_argument("--max-emit", type=int, default=61,
                    help="cap the relocated objects.  61 is the highest value "
                         "that links REPEATEDLY (4,197 differing bytes, 0 link "
                         "differing bytes).  155 objects once measured 4,116 and "
                         "then failed LINK's SetupPhase (C00000FD) on four of "
                         "four runs, so it is not reproducible and is not "
                         "adopted -- see docs/TODO.md round 109")
    ap.add_argument("--relocate-all", action="store_true",
                    help="also relocate every symbol the locator places "
                         "elsewhere, not just the COMMON ones.  Off by default: "
                         "it strips symbols whose copies it then cannot supply "
                         "(the manifest's sizes are unreliable, so a skipped "
                         "large object strands everything after it and the link "
                         "dies), and the measured state without it is 4,407")
    ap.add_argument("--with-sections", action="store_true",
                    help="also place the located .data/.bss sections.  Off by "
                         "default: measured as a net loss (round 90, 9,295 vs "
                         "4,419) because the sections duplicate content the link "
                         "already places correctly, while the COMMON emit alone "
                         "is a win (round 92, 4,058)")
    args = ap.parse_args()

    build = (ROOT / args.rsp).parent.parent
    rsp = [o.strip('"').replace("\\", "/")
           for o in (ROOT / args.rsp).read_text().split() if o.endswith(".obj")]
    ref = reference_addresses()

    # --- 1+2. the emitted blocks ------------------------------------------
    sec_man = json.loads((ROOT / args.sections / "manifest.json").read_text())
    sec_obj = {}
    if args.with_sections:
        for f in sorted((ROOT / args.sections).glob("*.obj")):
            sec_obj[int(f.name[:8], 16) + 0x10000000] = f

    # Reference addresses come from locate_common.py where they exist (it places
    # 103 of the pool's 135 by pairing .text offsets), and from the manifest
    # otherwise.  The manifest is not the only source any more.
    located = json.loads((ROOT / args.addresses).read_text()) if (ROOT / args.addresses).exists() else {}
    addr = dict(located)
    for k, v in ref.items():
        if v >= BSS_LO:
            addr.setdefault(k, v)
    meta_size: dict[str, int] = {}
    for k, v in tomllib.loads((ROOT / "src" / "rebrew-data.toml").read_text()).items():
        if isinstance(v, dict) and isinstance(v.get("name"), str) and isinstance(v.get("size"), int):
            meta_size[v["name"]] = v["size"]
    map_built: dict[str, int] = {}
    for l in (ROOT / args.map).read_text(errors="replace").splitlines():
        m = MAP_RE.match(l)
        if m:
            map_built.setdefault(m.group(1).lstrip("_"), int(m.group(2), 16))

    com_dir = ROOT / args.common
    for f in com_dir.glob("*.obj"):
        f.unlink()
    com_dir.mkdir(parents=True, exist_ok=True)
    com_obj = {}
    com_names: set[bytes] = set()
    seen = set()
    for rel in rsp:
        p = build / rel
        if not p.exists():
            continue
        try:
            c = Coff(p.read_bytes())
        except Exception:
            continue
        for s in c.symbols:
            if not s or s["section"] != 0 or s["storage_class"] not in (2, 3) or not s["value"]:
                continue
            n = s["name"]
            if isinstance(n, bytes):
                n = n.decode("ascii", "replace")
            n = n.lstrip("_")
            if n in seen or n not in addr or addr[n] < BSS_LO:
                continue
            if (s["value"] or 0) > MAX_EMIT_SIZE:
                continue          # g_bss_tail is 19 MB; emitting it overflows LINK
            seen.add(n)
            va, size = addr[n], s["value"]
            f = com_dir / ("%08x_%s.obj" % (va - 0x10000000, n))
            f.write_bytes(build_data_object("_" + n, b"\0" * size))
            com_obj[va] = f
            com_names.add(("_" + n).encode())
    # The general rule, which subsumes the COMMON pass and the movers:
    # **emit a symbol iff the locator says it is somewhere else.**  A symbol
    # already at its reference address is left alone -- that is the difference
    # from the section emit of rounds 86-90, which moved sections whose content
    # was already correct and lost 9,295 against 4,419.
    moved = 0
    pending: list[tuple[int, str, int]] = []
    order_hint: list[int] = []
    for rel in (rsp if args.relocate_all else []):
        p = build / rel
        if not p.exists():
            continue
        try:
            c = Coff(p.read_bytes())
        except Exception:
            continue
        for s in c.symbols:
            if not s or s["storage_class"] not in (2, 3):
                continue
            n = s["name"]
            if isinstance(n, bytes):
                n = n.decode("ascii", "replace")
            if not isinstance(n, str):
                continue
            n = n.lstrip("_")
            r = addr.get(n)
            b = map_built.get(n)
            if r is None or b is None or r < BSS_LO or r == b:
                continue
            if n in SPARSE_PLACEHOLDERS:
                continue          # see SPARSE_PLACEHOLDERS
            if n in seen or r in com_obj:
                continue
            # A COMMON symbol carries its own size in `value`; a section
            # symbol does not, and guessing 4 truncates every buffer
            # (g_log_message_buffer and friends) and strands the symbols after
            # it.  The manifest's recorded size is the next best source.
            if s["section"] == 0 and s["value"]:
                size = s["value"]
            else:
                ent = meta_size.get(n)
                size = ent if isinstance(ent, int) and ent > 0 else 4
            # The manifest's sizes are unreliable for the large sparse objects
            # (g_connections reads 1, the arrays read 1) and where a size IS
            # large it can be the 20 MB the restore gap provides, not this
            # symbol.  Emitting `b"\0" * 20058912` per symbol is what made LINK
            # die with a stack overflow (C00000FD).  CRT data objects are
            # kilobytes at most.
            if size > MAX_EMIT_SIZE:
                continue
            if args.emit_size:
                size = args.emit_size
            seen.add(n)
            # Only a COMMON symbol's size is authoritative: COFF stores it in
            # `value`.  A section symbol's size comes from the manifest, which
            # reads 1 for `g_connections` and for the sparse arrays, so packing
            # one on a guessed size absorbed it into a neighbour's run (at 1
            # byte) and the real 2.5 MB object was stripped and never replaced --
            # the whole `LNK2001: unresolved external symbol _g_connections`
            # cascade.  Unknown-size symbols are emitted one-per-object instead.
            known = s["section"] == 0 and bool(s["value"])
            pending.append((r, n, size if known else 0))
            order_hint.append(r)
    # Pack the relocated symbols into CONTIGUOUS runs: one .bss object per run
    # rather than one per symbol.  LINK's SetupPhase ceiling is on the count of
    # emitted sections (measured: 61 links, 62 does not), and the 145 candidates
    # fall into 25 runs, so packing places every one of them well under it.
    pending.sort()
    # A section symbol has no size of its own, but the LOCATOR gives every
    # uniquely-placed address, so consecutive addresses bound it: size =
    # next_address - this one.  That is the same extent model the per-symbol
    # emitter settled on in rounds 43-47, and it is a measurement rather than a
    # guess.  Sizes beyond MAX_EMIT_SIZE are left unset, which keeps the sparse
    # placeholders out of packing exactly as round 115 required.
    # NOT derived, and the reason is worth keeping: `next_address - this one`
    # is only the size when every address in between is accounted for.  It is
    # not -- the locator places 636 of them and the rest are unknown, so a gap
    # routinely covers symbols that packing then overwrites with zeros while the
    # strip has already made them undefined.  Measured: 101 LNK2001 for
    # `g_connections`, then 89 for `g_entity_type_table` once that one was
    # excluded.  A section symbol's size stays unknown, and the manifest cannot
    # supply it (round 106: `g_connections` reads 1).  So packing can only ever
    # carry symbols whose size COFF states, and the ceiling stands.
    runs: list[list[tuple[int, str, int]]] = []
    for item in pending:
        if item[2] == 0:
            continue          # no trustworthy size: it goes out on its own
        if runs and 0 <= item[0] - (runs[-1][-1][0] + runs[-1][-1][2]) <= args.pack_gap:
            runs[-1].append(item)
        else:
            runs.append([item])
    if args.pack_limit:
        runs = runs[:args.pack_limit]
    loose = [it for it in pending if it[2] == 0]
    if args.pack:
        for r, n, _sz in loose:
            f = com_dir / ("%08x_%s.obj" % (r - 0x10000000, n))
            f.write_bytes(build_data_object("_" + n, b"\0" * 4))
            com_obj[r] = f
            com_names.add(("_" + n).encode())
    for run in (runs if args.pack else []):
        lo, hi = run[0][0], max(a + sz for a, _n, sz in run)
        if hi - lo > MAX_EMIT_SIZE:
            continue
        stem = "%08x_pack%d" % (lo - 0x10000000, len(run))
        # each symbol at its offset inside the one section, or it is not defined
        # at all: a packed object that only names itself strands the run
        syms = [(n, a - lo) for a, n, _sz in run]
        (com_dir / (stem + ".obj")).write_bytes(
            build_section_object("_" + stem, b"\0" * (hi - lo), syms, bss=not args.pack_data))
        for _a, n, _sz in run:
            com_names.add(("_" + n).encode())
        moved += len(run)
    print("emitted: %d sections, %d COMMON symbols, %d relocated in %d packed runs"
          % (len(sec_obj), len(com_obj) - sum(len(r) for r in runs), moved, len(runs)))
    print("PLACEHOLDER emitted: %d sections, %d COMMON symbols, %d relocated"
          % (len(sec_obj), len(com_obj) - moved, moved))

    # --- 3. anchors and the strip -----------------------------------------
    key: dict[str, int] = {}
    for e in sorted(sec_man, key=lambda x: x["reference"]):
        n = e["object"]
        if n not in key or e["reference"] < key[n]:
            key[n] = e["reference"]
    for l in (ROOT / args.map).read_text(errors="replace").splitlines():
        m = MAP_RE.match(l)
        if not m:
            continue
        r = ref.get(m.group(1).lstrip("_"))
        if r is None or not (DATA_LO <= r < DATA_HI):
            continue
        n = Path(m.group(3)).name
        if n not in key or r < key[n]:
            key[n] = r
    print("objects with a reference .data address: %d" % len(key))

    # Symbols the reference places in BSS but we place in initialised `.data`:
    # they must MOVE, which is different from the sections of rounds 86-90 (those
    # duplicated content already in the right place).  Emitted into `.bss` at the
    # manifest's address, with their originals stripped.
    movers = {}
    map_built = {}
    for l in (ROOT / args.map).read_text(errors="replace").splitlines():
        m = MAP_RE.match(l)
        if m: map_built.setdefault(m.group(1).lstrip("_"), int(m.group(2), 16))
    for n, r in ref.items():
        b = map_built.get(n)
        if b is not None and b < BSS_LO <= r:
            movers[n] = r
    sec_names = {}
    for rel in rsp:
        p2 = build / rel
        if not p2.exists():
            continue
        try:
            c = Coff(p2.read_bytes())
        except Exception:
            continue
        for i, sc in enumerate(c.sections):
            nm = sc["name"].rstrip(b"\0")
            if nm not in (b".data", b".bss"):
                continue
            for s2 in c.symbols:
                if s2 and s2["section"] == i + 1 and s2["storage_class"] in (2, 3):
                    x = s2["name"]
                    if isinstance(x, bytes):
                        x = x.decode("ascii", "replace")
                    if x.lstrip("_") in movers:
                        sec_names.setdefault(p2.name, set()).add(x.lstrip("_"))
    for n, r in sorted(movers.items(), key=lambda kv: kv[1]):
        if n not in sec_names and not any(n in v for v in sec_names.values()):
            continue
        f = com_dir / ("%08x_%s.obj" % (r - 0x10000000, n))
        f.write_bytes(build_data_object("_" + n, b"\0" * 4))
        com_obj[r] = f
        com_names.add(("_" + n).encode())
    print("movers emitted: %d" % sum(1 for r in com_obj if r in movers.values()))

    sd = ROOT / args.stripped
    for f in sd.glob("*.obj"):
        f.unlink()
    sd.mkdir(parents=True, exist_ok=True)
    sec_by_obj: dict[str, set[int]] = defaultdict(set)
    for e in sec_man:
        sec_by_obj[e["object"]].add(e["section_index"])
    for rel in rsp:
        p = build / rel
        if not p.exists():
            continue
        raw = p.read_bytes()
        try:
            c = Coff(raw)
        except Exception:
            continue
        drop = sec_by_obj.get(p.name, set()) if args.with_sections else set()
        has_common = any(s and s["section"] == 0 and s["storage_class"] in (2, 3)
                         and s["value"] for s in c.symbols)
        # an object that owns a mover must be rewritten too, even when it has
        # no dropped section and no COMMON: otherwise it still defines the
        # symbol and the emitted copy is the LNK4006 "second definition"
        # An object must be rewritten if it carries ANY symbol the emit supplies,
        # wherever that symbol lives in it.  A split blob can hold `_tzinfo` in
        # `.text` with no COMMON of its own, so a "has COMMON" test skips it and
        # the emitted copy then loses the LNK4006.
        # An object must be rewritten if it carries ANY symbol the emit
        # supplies, wherever that symbol sits in it.  A split blob can hold
        # `_tzinfo` in `.text` with no COMMON of its own, so a "has COMMON"
        # test skips it and the emitted copy then loses the LNK4006.
        names_here = set()
        for s in c.symbols:
            if not s or s["storage_class"] not in (2, 3):
                continue
            n = s["name"]
            if isinstance(n, bytes):
                n = n.decode("ascii", "replace")
            if isinstance(n, str):
                names_here.add(("_" + n.lstrip("_")).encode())
        # Only the COMMON copy is cleared.  A split blob carries the same
        # symbol in `.text` AND in COMMON (10020915_.text.obj holds `_tzinfo`
        # in both); undefining the `.text` one too removes 8 bytes of real data
        # and measures worse (4,416 against 4,407), so the section copy stays
        # and the duplicate is a property of the split set, not of the strip.
        carries = {n for n in names_here & com_names
                   if any(s and s["section"] == 0 for s in c.symbols)}
        if not drop and not has_common and not sec_names.get(p.name) and not carries:
            continue
        # Only the COMMON symbols we emitted become undefined.  Removing all of
        # them orphans the 86 CRT commons the library owns (`_g_const_0_001`,
        # `_g_game_speed_table`, ... LNK2001).
        # Undefine the emitted symbol wherever this object carries it.  The
        # split blobs define several of them TWICE -- once COMMON and once in
        # `.text` (10020915_.text.obj holds `_tzinfo` in both) -- so clearing
        # only the COMMON copy leaves the section copy to win the LNK4006.
        extra = set(com_names) | {("_" + n).encode()
                                  for n in sec_names.get(p.name, ())}
        (sd / p.name).write_bytes(
            strip_data_sections(raw, None, drop, True, com_names or None,
                                extra or None))
    print("objects rewritten: %d" % len(list(sd.glob('*.obj'))))

    # --- 4. the merged link line ------------------------------------------
    pending = sorted([(va, str(f)) for va, f in com_obj.items()]
                     + [(va, str(f)) for va, f in sec_obj.items()])
    out = []
    placed = 0
    for rel in rsp:
        n = Path(rel).name
        here = key.get(n)
        if here is not None:
            for va, f in pending:
                if va < here:
                    out.append(Path(f).relative_to(ROOT / "build").as_posix())
                    placed += 1
            pending = [(v, f) for v, f in pending if v >= here]
        st = sd / n
        out.append(st.relative_to(ROOT / "build").as_posix() if st.exists() else rel)
    for va, f in pending:
        out.append(Path(f).relative_to(ROOT / "build").as_posix())
        placed += 1
    (ROOT / args.out_rsp).write_text("\n".join(out) + "\n")
    print("rsp: %d tokens, %d emitted objects placed" % (len(out), placed))

    if args.link:
        link = (build / "CMakeFiles" / "server_dll.dir" / "link.txt").read_text()
        cmd = (link
               .replace("@CMakeFiles/server_dll.dir/objects1.rsp",
                        "@split_poc/rsp_emit_all.rsp")
               .replace("/out:server.dll", "/out:emit_all.dll /MAP:emit_all.map")
               .replace("/implib:server.lib", "/implib:emit_all.lib"))
        cmd = re.sub(r" /pdb:[^ ]*", "", cmd)
        r = subprocess.run(cmd, shell=True, cwd=build, capture_output=True, text=True)
        txt = r.stdout + r.stderr
        errs = [l for l in txt.splitlines() if "error" in l.lower()]
        print("link: %d LNK4006, %d error line(s)"
              % (txt.count("LNK4006"), len(errs)))
        for l in errs[:5]:
            print("   " + l)
        dll = build / "emit_all.dll"
        if dll.exists():
            print("output: emit_all.dll (%d bytes)" % dll.stat().st_size)
        return 1 if errs else 0
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
