#!/usr/bin/env python3
"""Audit where the split-set link placed each per-section LIBCMT object.

The CRT half of the goal is "link LIBCMT in, don't reverse it".  `scripts/
map_libcmt.py` says which member body the reference has at each VA and
`scripts/split_coff.py` turns each mapped section into a command-line object,
but nothing so far measured where LINK actually put them.  This does, from the
linker's own `/MAP` output.

Run it on a map produced by relinking with `/MAP:<file>`:

    cd build
    cmd=$(sed 's#@CMakeFiles/server_dll.dir/objects1.rsp#@split.rsp#;
               s#/out:server.dll#/out:server_split.dll /MAP:server_split.map#;
               s#/implib:server.lib#/implib:server_split.lib#;
               s# /pdb:[^ ]*##' CMakeFiles/server_dll.dir/link.txt)
    eval "$cmd"
    python3 ../scripts/split_audit.py server_split.map

Each split object is named `<reference-va>_<section>.obj`, so the object's own
name carries the VA the reference has it at; the deltas below are
`built - reference`.  A delta of 0 for every object is the CRT half of byte
identity.

Measured 2026-09-13 (round 26) on the 259-object split set: 340 placed symbols,
**0 at delta 0**.  The mapped objects start uniformly at -0xaa (the first CRT
function, `_fclose` 0x1001a18a, is placed at 0x1001a0e0) and the drift grows
monotonically to +0x5c0 by the tail (`__strdup` 0x10023812 at 0x10023dd2).
The -0xaa is the ~170 bytes of CRT code the reference has before `_fclose`
that the split set never emits — the nine functions no library carries plus
the eight `crt_region` objects the split rsp drops; the positive drift is the
split objects' COMDAT padding accumulating over ~300 objects.
`--closure` helpers are the extreme outliers (`memcpy.obj`'s `LeadUp1` lands
0x3640 *below* its reference VA, `__STRINGTOLD`'s helper 0xa5c above), so they
should be excluded when reading the drift.

**Corrected round 5.**  The conclusion of that paragraph is wrong, and it is why
this script read as "the drift is everywhere" for a long time.  Walking the
split objects in link order, only TWO of the 228 move the running delta at all:
`1001e7d4_.text.obj` (`__except_handler3`) emits 8 bytes too many, and the next
object, `1001e8b4_.text.obj`, emits 8 too few.  The split set therefore **nets
to exactly zero drift** and is position-exact.  The `delta range` line is
dominated by the `--closure` helpers, which all share their object's reference
VA and so report enormous deltas that mean nothing about layout.

The real 642-byte `.text` overshoot is **trailing content**, which a per-symbol
delta table can never show, because those symbols have no reference VA in their
object name.  It is now reported explicitly at the end of the run: past the
reference's `.text` end 0x10023846 sit a `DllMain@12` stub (6 B), 4 `link_stubs`
(70 B) and the import thunks (566 B) that the reference does not have — the
reference calls imports directly and has 11 thunks; ours has 103.

**What causes the thunks** (round 8, after two wrong answers in rounds 6 and 7 —
both from bad measurements, see docs/TODO.md; the cause is neither plain-name
references nor the `/INCLUDE:__imp__X` directives):

* Our `call dword ptr [IAT]` count is **211, the same as the reference's**, so
  the tree's call sites already match; the thunks are pure linker overhead.
  `scripts/import_thunk_census.py` measures all of this.
* The link line carries **`/OPT:NOREF`**, which tells LINK to keep unreferenced
  sections — and an MSVC6 import library holds each function's
  `jmp dword ptr [IAT]` thunk in the member's `.text`.  Relinking the identical
  object set with `/OPT:REF` drops the thunks from **103 to 10** against the
  reference's 11.
* `/OPT:REF` alone is NOT the fix.  Diffing the two maps, it drops 266 symbols:
  89 are the import thunks we want gone (80 KERNEL32 + 9 WS2_32) but **177 are
  real code the reference has** — `_CrashDumpUnhandledExceptionFilter@4`,
  `_EmitCrashModuleLine` and 175 more.  Pruning is transitive: drop a section
  and whatever reached only through it goes too.  `/OPT:NOREF` is load-bearing.
* `.def` `IMPORTS` cannot substitute for the import libraries: MSVC6 accepts the
  syntax but emits `LNK4017 ... not supported for the target platform` for
  stdcall names, and 99 of the 100 imports here are stdcall.
* So the fix must keep NOREF and synthesise the import descriptors (an object
  carrying `.idata`, with `__imp__X` absolute into it) instead of letting the
  import libraries supply a `.text` full of thunks.  Not implemented.
  **Superseded by round 11/12:** the working answer is `/OPT:REF` plus a derived
  `/INCLUDE` set — `scripts/ref_include_set.py` computes it.  With that link the
  thunks land on the reference's 11, the import table on 100 and `call [abs]`
  on 211, leaving 42 bytes of `.text`.  The synthesised-`.idata` emitter
  (`scripts/emit_idata.py`) is kept only as the evidence for the round-10 probe:
  LINK accepts such an object but never points IMAGE_DIRECTORY_ENTRY_IMPORT at
  it, so it cannot be used.
"""

from __future__ import annotations

import argparse
import collections
import re
import sys
from pathlib import Path

LINE = re.compile(
    r"\s+([0-9a-f]{4}):([0-9a-f]{8})\s+(\S+)\s+([0-9a-f]{8})\s+(\S+)\s+(\S+)")


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("mapfile")
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--content", action="append", default=[],
                    help="directory of objects whose .text is part of this region "
                         "(repeatable); with it the region span, its content and "
                         "the slack between them are printed")
    ap.add_argument("--reference-end", default="0x10023846",
                    help="VA the reference .text ends at (for the breakdown)")
    ap.add_argument("--text-end", help="VA the built .text ends at; overrides the "
                    "heuristic end used for the breakdown")
    args = ap.parse_args()

    rows = []
    for line in open(args.mapfile, errors="replace"):
        m = LINE.match(line)
        if not m:
            continue
        va = int(m.group(4), 16)
        obj = m.group(6)
        mm = re.match(r"([0-9a-f]{8})_", obj)
        if not mm:
            continue
        rows.append((int(mm.group(1), 16), va, m.group(3)))
    rows.sort()
    if not rows:
        print("no split objects found in " + args.mapfile, file=sys.stderr)
        return 1

    deltas = collections.Counter(va - ref for ref, va, _ in rows)
    if args.json:
        import json
        print(json.dumps({
            "placed": len(rows),
            "exact": deltas.get(0, 0),
            "delta_min": min(deltas),
            "delta_max": max(deltas),
            "deltas": {str(k): v for k, v in sorted(deltas.items())},
            "objects": [{"reference_va": hex(r), "built_va": hex(v), "symbol": n}
                        for r, v, n in rows],
        }, indent=1))
        return 0

    print(f"placed split symbols: {len(rows)}")
    print(f"exactly at their reference VA: {deltas.get(0, 0)}")
    print(f"delta range: {min(deltas):+#x} .. {max(deltas):+#x}")
    if args.content:
        def text_size(path):
            b = open(path, "rb").read()
            nsec = int.from_bytes(b[2:4], "little")
            optsz = int.from_bytes(b[16:18], "little")
            base = 20 + optsz
            total = 0
            for i in range(nsec):
                hdr = b[base + i * 40:base + (i + 1) * 40]
                if hdr[0:5] == b".text":
                    total += int.from_bytes(hdr[16:20], "little")
            return total

        content = 0
        for d in args.content:
            content += sum(text_size(str(f)) for f in Path(d).glob("*.obj"))
        region_start = min(va for _ref, va, _n in rows)
        end = (int(args.text_end, 16) if args.text_end
               else int(args.reference_end, 16) + max(va - ref for ref, va, _n in rows))
        span = end - region_start
        print()
        print(f"region built   {region_start:#x} .. {end:#x} = {span} bytes")
        print(f"emitted content{content:>28} bytes")
        print(f"slack (span - content){span - content:>17} bytes")
        print(f"reference span (end - first ref VA){end - min(ref for ref, _v, _n in rows):>8} bytes")
    print()
    print(f"{'symbol':34} {'reference':>11} {'built':>11} {'delta':>9}")
    for ref, va, name in rows[:10] + rows[-10:]:
        print(f"{name:34} {ref:#11x} {va:#11x} {va - ref:+#9x}")

    # ---- trailing content: what sits past the last reference-aligned symbol --
    # Round 5.  The split set itself is position-exact: walking the objects in
    # link order, only TWO of them move the running delta at all --
    # `1001e7d4_.text.obj` (__except_handler3) emits 8 bytes too many and the
    # very next object, `1001e8b4_.text.obj`, emits 8 too few, so the split set
    # NETS TO ZERO.  The 642-byte .text overshoot is entirely TRAILING: the
    # whole block above lives past the reference's .text end, and none of it
    # is drift.  Nothing reported that before -- the "delta range" line is
    # dominated by closure helpers (LeadUp/TrailDown/UnwindDown), which all
    # share their object's reference VA and so look like enormous misplacements
    # while saying nothing about layout.
    last_ref = max(ref for ref, _va, _n in rows if ref <= min(v for _r, v, _n in rows))
    aligned = [(ref, va, n) for ref, va, n in rows if va == ref]
    if aligned:
        boundary = max(va for _r, va, _n in aligned)
        # Everything in the MAP at or above the reference's .text end, not just
        # the split objects: the trailing block is DLL import thunks plus
        # def/commons/stub objects, none of which carry a reference VA in their
        # name, so filtering to split objects (as the delta table above does)
        # hides the whole cause of the overshoot.
        ref_end = int(args.reference_end, 16)
        tail = []
        for line in open(args.mapfile, errors="replace"):
            m = LINE.match(line)
            if not m:
                continue
            va = int(m.group(4), 16)
            if va >= ref_end:
                tail.append((va, m.group(3), m.group(6)))
        tail.sort()
        print()
        print(f"trailing content at or above the reference .text end {ref_end:#x}:")
        if not tail:
            print("  (none)")
        else:
            groups = {}
            for va, sym, obj in tail:
                groups.setdefault(obj, []).append((va, sym))
            for obj, items in sorted(groups.items(), key=lambda kv: min(v for v, _ in kv[1])):
                lo = min(v for v, _ in items)
                hi = max(v for v, _ in items)
                print(f"  {lo:#11x}..{hi + 6:#11x}  {hi + 6 - lo:5d} B  "
                      f"{len(items):3d} x {obj}")
            print(f"  {'total':>11}      {hi + 6 - min(v for v, _s, _o in tail):5d} B of "
                  f"{len(tail)} symbol(s) past the reference's .text")
    return 0


if __name__ == "__main__":
    sys.exit(main())
