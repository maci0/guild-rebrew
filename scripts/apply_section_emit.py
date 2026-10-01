#!/usr/bin/env python3
"""Apply the section emit: strip what the emit owns, link it in reference order.

The per-symbol emit could not be applied (round 84): its fragment covered 136 of
870 data symbols, so `strip_data_sections` kept all 343 sections and the link
died on 292 duplicate symbols.  The section emit (round 86) places 248 sections
at distinct reference addresses, and this script does the rest:

  1. read the manifest (`emit_data_sections.py --manifest`) -- object, section
     index, reference offset;
  2. rewrite each game object without the sections the emit owns, so they
     contribute no `.data` of their own;
  3. build a response file that **keeps the original object order** and inserts
     the emitted sections in reference order.  Order is not a detail: the link
     runs `/FORCE:MULTIPLE`, where the first definition wins, and round 53 lost
     the zlib symbols to a reordering.

Nothing here reads the reference binary for *content*; it is applied to a build
that has already been shown (round 57) to be 99.2% byte-exact at the reference
addresses.  What it removes is the need for the fixers to move the rest.

Usage:
    python3 scripts/apply_section_emit.py --link
"""
from __future__ import annotations

import argparse
import json
import subprocess
import sys
import tomllib
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "scripts"))

from emit_data_symbols import strip_data_sections  # noqa: E402

GAME = "CMakeFiles/server_dll.dir"
#: the data-bearing TUs sit at these two spots on the link line (round 38); the
#: emitted sections go where they are, so the game's own data objects still
#: precede the data region and the CRT band still follows it.
BUCKETS = ("data_globals.c.obj", "link_stubs.c.obj")


_REF_DATA: dict[str, int] | None = None


def ref_data_of(object_name: str) -> int | None:
    """The reference `.data` address of this object, from the metadata.

    Only 34 of the 545 objects on the link line have one, which is why the
    emit's own sections are needed as anchors too.
    """
    global _REF_DATA
    if _REF_DATA is None:
        import tomllib
        _REF_DATA = {}
        data = tomllib.loads((ROOT / "src" / "rebrew-data.toml").read_text())
        for k, v in data.items():
            if not isinstance(v, dict) or not isinstance(v.get("name"), str):
                continue
            t, _, a = str(k).rpartition(".")
            if t != "SERVER":
                continue
            try:
                _REF_DATA.setdefault(v["name"], int(a, 16))
            except ValueError:
                pass
    # the map is consulted by the caller through a global set up in main
    return _OBJ_DATA.get(object_name)


_OBJ_DATA: dict[str, int] = {}


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--rsp", default="build/split_poc/rsp.rsp")
    ap.add_argument("--manifest", default="build/data_sections/manifest.json")
    ap.add_argument("--sections", default="build/data_sections")
    ap.add_argument("--out-objects", default="build/section_stripped")
    ap.add_argument("--out-rsp", default="build/split_poc/rsp_sections.rsp")
    ap.add_argument("--link", action="store_true",
                    help="link the result to build/section_emit.dll")
    ap.add_argument("--verify", action="store_true", default=True)
    args = ap.parse_args()

    # object -> the reference `.data` address of its lowest `.data` symbol.
    # The LINK map is the only place both halves are known at once: it names the
    # object, and the metadata names the reference address of the symbol.
    import re as _re
    _mpat = _re.compile(r"^\s*\d{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{8})\s+[fF]?\s*(\S+)\s*$")
    _meta = tomllib.loads((ROOT / "src" / "rebrew-data.toml").read_text())
    _refva = {}
    for k, v in _meta.items():
        if isinstance(v, dict) and isinstance(v.get("name"), str):
            t, _, a = str(k).rpartition(".")
            if t == "SERVER":
                try: _refva[v["name"]] = int(a, 16)
                except ValueError: pass
    _mapf = ROOT / "build" / "split_poc.map"
    if _mapf.exists():
        for line in _mapf.read_text(errors="replace").splitlines():
            mm = _mpat.match(line)
            if not mm: continue
            sym, obj = mm.group(1).lstrip("_"), Path(mm.group(3)).name
            r = _refva.get(sym)
            if r is None or not (0x10027000 <= r < 0x11767600): continue
            if obj not in _OBJ_DATA or r < _OBJ_DATA[obj]:
                _OBJ_DATA[obj] = r

    manifest = json.loads((ROOT / args.manifest).read_text())
    build = (ROOT / args.rsp).parent.parent
    objects = [o.strip('"').replace("\\", "/")
               for o in (ROOT / args.rsp).read_text().split() if o.endswith(".obj")]

    by_object: dict[str, set[int]] = defaultdict(set)
    for entry in manifest:
        by_object[entry["object"]].add(entry["section_index"])

    out_obj_dir = ROOT / args.out_objects
    out_obj_dir.mkdir(parents=True, exist_ok=True)
    for stale in out_obj_dir.glob("*.obj"):
        stale.unlink()

    stripped = 0
    dropped_sections = 0
    lost = []
    for rel in objects:
        if GAME not in rel:
            continue
        src = build / rel
        if not src.exists():
            continue
        drop = by_object.get(src.name)
        if not drop:
            continue
        raw = src.read_bytes()
        # COMMON symbols are pooled by the linker, not section-resident, so the
        # section emit must leave them defined: converting them to undefined
        # orphans every data global the section emit does not itself carry
        # (17 LNK2001 on the first attempt: g_list_head, g_download_slots, ...).
        new = strip_data_sections(raw, None, drop, drop_common=False)
        (out_obj_dir / src.name).write_bytes(new)
        stripped += 1
        dropped_sections += len(drop)
        if args.verify:
            from split_coff import Coff
            a, b = Coff(raw), Coff(new)
            a_secs = {i + 1 for i, s in enumerate(a.sections)
                      if s["name"].rstrip(b"\0") in (b".data", b".bss")}
            b_secs = {i + 1 for i, s in enumerate(b.sections)
                      if s["name"].rstrip(b"\0") in (b".data", b".bss")}
            if len(b_secs) > len(a_secs) - len(drop):
                lost.append(f"{src.name}: expected to drop {len(drop)}, "
                            f"{len(a_secs)}->{len(b_secs)}")

    emit_files = sorted((ROOT / args.sections).glob("*.obj"))
    # `.data` layout follows the order objects appear on the link line, so an
    # emitted section must be inserted where its REFERENCE address implies --
    # not at one bucket.  (Round 87 inserted all 248 at `data_globals.c.obj` and
    # 0 of them landed correctly.)
    #
    # Anchors come from two sources, both sound:
    #   * objects the metadata places in `.data` at a known reference address;
    #   * the objects the emit took sections FROM -- a section's reference
    #     address is a lower bound for its object's own data.
    anchors: list[tuple[int, int]] = []      # (reference address, rsp index)
    for i, rel in enumerate(objects):
        r = ref_data_of(Path(rel).name)
        if r is not None:
            anchors.append((r, i))
    for entry in manifest:
        try:
            i = [k for k, o in enumerate(objects) if Path(o).name == entry["object"]][0]
        except IndexError:
            continue
        anchors.append((entry["reference"], i))
    anchors.sort()
    # for each rsp position, the emitted sections whose address falls after the
    # last anchor at or before that position and before the next one
    buckets: dict[int, list] = defaultdict(list)
    files_by_va = {int(f.name[:8], 16): f for f in emit_files}
    for va in sorted(files_by_va):
        slot = 0
        for a, i in anchors:
            if a <= va:
                slot = i
            else:
                break
        buckets[slot].append(files_by_va[va])

    out = []
    inserted = 0
    for i, rel in enumerate(objects):
        name = Path(rel).name
        if GAME in rel:
            if buckets.get(i):
                out += [f"{Path(args.sections).name}/{f.name}" for f in buckets[i]]
                inserted += len(buckets[i])
            st = out_obj_dir / name
            out.append((out_obj_dir.name + "/" + name) if st.exists() else rel)
        else:
            out.append(rel)
        if i not in buckets and buckets and i == max(anchors, key=lambda t: t[1])[1]:
            pass
    if inserted < len(emit_files):
        rest = [f for f in emit_files if f not in
                {x for lst in buckets.values() for x in lst}]
        out += [f"{Path(args.sections).name}/{f.name}" for f in rest]
        inserted += len(rest)
    (ROOT / args.out_rsp).write_text("\n".join(out) + "\n")

    print(f"objects rewritten                : {stripped}")
    print(f"sections removed from them       : {dropped_sections}")
    print(f"emitted sections inserted        : {len(emit_files)}")
    print(f"response file                    : {args.out_rsp} ({len(out)} tokens)")
    if lost:
        print(f"VERIFY PROBLEMS ({len(lost)}):", file=sys.stderr)
        for line in lost[:8]:
            print("   " + line, file=sys.stderr)
        return 1

    if args.link:
        link_txt = (build / "CMakeFiles" / "server_dll.dir" / "link.txt").read_text()
        cmd = (link_txt
               .replace("@CMakeFiles/server_dll.dir/objects1.rsp",
                        "@split_poc/rsp_sections.rsp")
               .replace("/out:server.dll",
                        "/out:section_emit.dll /MAP:section_emit.map")
               .replace("/implib:server.lib", "/implib:section_emit.lib"))
        import re
        cmd = re.sub(r" /pdb:[^ ]*", "", cmd)
        r = subprocess.run(cmd, shell=True, cwd=build,
                           capture_output=True, text=True)
        out_text = r.stdout + r.stderr
        dupes = out_text.count("LNK4006")
        errs = [l for l in out_text.splitlines() if "error" in l.lower()]
        print(f"link: {dupes} LNK4006, {len(errs)} error line(s)")
        for l in errs[:6]:
            print("   " + l)
        dll = build / "section_emit.dll"
        if dll.exists():
            print(f"output                          : section_emit.dll "
                  f"({dll.stat().st_size} bytes)")
        return 1 if errs else 0
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
