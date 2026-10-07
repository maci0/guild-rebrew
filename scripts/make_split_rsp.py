#!/usr/bin/env python3
"""Build the LINK response file for the split-set experiment.

The split set is: every game object the CMake build compiles, minus the eight
`crt_region/*.obj` hand-reversed LIBCMT bodies, plus the per-section objects
`scripts/split_coff.py` extracted from the mapped LIBCMT members, ordered by
the reference VA encoded in each object's filename.

Ordering matters and was wrong before round 27: `split_coff` writes
`index.json` in the order the map matched members, which is **not** sorted by
reference VA (four descents in the 235-entry list).  Feeding it straight to
LINK, as the old `/tmp/mkrsp.py` did, put the 821-byte `memmove` body next to
its identical `memmove2` twin instead of 0x38b0 later, i.e. 13.5 KB out of
place.  Sorting by VA drops the worst placement error from -0x3640 to -0x260
and shrinks `.text` from 0x246f6 to 0x246e6.

Usage:
    python3 scripts/make_split_rsp.py --split build/libcmt_split \\
        --objects build/CMakeFiles/server_dll.dir/objects1.rsp \\
        --out build/split_sorted.rsp
"""

from __future__ import annotations

import argparse
import json
import re
import shlex
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

#: the hand-reversed LIBCMT bodies the split objects replace
DROP = (
    "Develop/DieGildeAddOn/game/game_float_constants.c.obj",
    "crt_region/locale_time_strings.c.obj", "crt_region/locale_time_table.c.obj",
    "crt_region/initterm.c.obj", "crt_region/dllmain.c.obj",
    "crt_region/mlock.c.obj", "crt_region/sbh_pool.c.obj",
    "crt_region/sbh_aliases.c.obj", "crt_region/crt_heap.c.obj",
    "crt_region/amsg_exit.c.obj", "crt_region/sbh_globals.c.obj",
)


#: Where the two restore blobs go, by the running `.data` total of the objects
#: before them.  `rdata_restore.c`'s blob carries `// DATA: SERVER 0x1002a000`,
#: i.e. reference `.data` offset 0x3000, and `.data` is placed in response-file
#: order, so the blobs belong near the point where the game objects' own
#: `.data` adds up to that.  The landscape is jagged -- one object either way
#: costs thousands of bytes -- so the constant is measured, not derived; see
#: the round-60 and round-62 tables in docs/TODO.md.  If an object's `.data`
#: size changes, re-sweep rather than trusting this number.
_BLOB_AT_DATA = 0x3400


def _section_bytes(path: str, prefix: str) -> int:
    """Total size of the object's sections whose name starts with `prefix`."""
    try:
        data = (ROOT / "build" / path).read_bytes()
    except OSError:
        return 0
    try:
        count = struct.unpack_from("<H", data, 2)[0]
    except struct.error:
        return 0
    total = 0
    for i in range(count):
        off = 20 + i * 40
        name = data[off : off + 8].rstrip(b"\0").decode("ascii", "replace")
        if name.startswith(prefix):
            total += struct.unpack_from("<I", data, off + 16)[0]
    return total


def _only_crt_sections(path) -> bool:
    """True when every non-empty section of an object is a `.CRT$` one."""
    try:
        data = path.read_bytes()
    except OSError:
        return False
    try:
        count = struct.unpack_from("<H", data, 2)[0]
        opt = struct.unpack_from("<H", data, 16)[0]
    except struct.error:
        return False
    seen = False
    for i in range(count):
        off = 20 + opt + i * 40
        name = data[off : off + 8].rstrip(b"\0").decode("ascii", "replace")
        if struct.unpack_from("<I", data, off + 16)[0] == 0:
            continue
        if not name.startswith(".CRT$"):
            return False
        seen = True
    return seen


def va_of(entry: dict) -> int:
    v = entry.get("va")
    if isinstance(v, str):
        return int(v, 16)
    if isinstance(v, int):
        return v
    m = re.search(r"([0-9a-f]{8})_", entry["obj"])
    return int(m.group(1), 16) if m else 1 << 32


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--split", required=True, help="split_coff output directory")
    ap.add_argument("--objects", required=True, help="objects1.rsp from the CMake build")
    ap.add_argument("--out", required=True)
    ap.add_argument("--thunks", help="directory from scripts/emit_thunks.py; its "
                    "objects are inserted between the game objects and the CRT "
                    "objects, where the reference has its IAT thunks")
    ap.add_argument("--defs", help="directory from scripts/emit_defs.py; its objects "
                    "define the sections the split set leaves undefined")
    ap.add_argument("--commons", help="directory from scripts/emit_commons.py; its "
                    "objects define the mapped members' common symbols so LINK "
                    "stops loading whole members for them")
    ap.add_argument("--no-sort", action="store_true",
                    help="keep split_coff's index order (the pre-round-27 behaviour)")
    args = ap.parse_args()

    index = json.loads((ROOT / args.split / "index.json").read_text())
    if not args.no_sort:
        index = sorted(index, key=va_of)
    try:
        tokens = shlex.split((ROOT / args.objects).read_text())
    except FileNotFoundError:
        print(f"missing {args.objects}; configure the CMake build first", file=sys.stderr)
        return 1

    head, mid, data, rdata, tail = [], [], [], [], []
    for t in tokens:
        if any(d in t for d in DROP):
            continue
        # NB: match on "/<name>" -- "rdata_restore.c.obj".endswith(
        # "data_restore.c.obj") is True, so the bare basename sends the
        # rdata blob to `head` and its .rdata lands at offset 0x1a0 instead
        # of the reference's 0x12e8.
        if t.endswith("/crt_imports.c.obj"):
            head.append(t)
        elif t.endswith("/data_globals.c.obj"):
            data.append(t)
        elif t.endswith("/readonly_strings.c.obj") or t.endswith("/data_restore.c.obj"):
            # Both restore blobs reproduce reference section content that the
            # game objects' own contributions sit in front of, so they belong
            # after the CMake objects and before the split ones -- not in
            # `head`, which put the .rdata blob at offset 0x1a0 instead of
            # 0x12e8 and the .data blob a long way early as well.
            rdata.append(t)
        elif t.endswith("/link_stubs.c.obj"):
            tail.append(t)
        else:
            mid.append(t)
    extra_objs = []
    if args.defs:
        for f in sorted((ROOT / args.defs).glob("*.obj")):
            # A definition object whose sections are all `.CRT$` has to be left
            # out: LINK then emits a separate `.CRT` *output* section (raw
            # 0x1000) after `.data`, which moves `.reloc` off the reference's
            # file offset.  LIBCMT's own `crt0init.obj` supplies the same
            # symbols and merges into `.data` exactly as the reference has them
            # (section 3 offsets 0x0..0x30), so dropping these costs nothing -
            # measured: `.CRT` gone, `.data` 0xe000 at 0x27000 and `.reloc` back
            # at 0x35000.
            if _only_crt_sections(f):
                continue
            extra_objs.append(f.relative_to(ROOT / "build").as_posix())
    if args.commons:
        for f in sorted((ROOT / args.commons).glob("*.obj")):
            extra_objs.append(f.relative_to(ROOT / "build").as_posix())
    ordered = [e["obj"].replace(str(ROOT / "build") + "/", "") for e in index]
    thunk_objs, tail_thunks = [], []
    if args.thunks:
        for f in sorted((ROOT / args.thunks).glob("*.obj")):
            dest = tail_thunks if f.stem.endswith("_tail") else thunk_objs
            dest.append(f.relative_to(ROOT / "build").as_posix())
    # Split `mid` where the restore blobs belong, so their `.data`/`.rdata`
    # land at the reference's offsets instead of after every game object.
    cut = len(mid)
    acc = 0
    for i, t in enumerate(mid):
        acc += _section_bytes(t, ".data")
        if acc >= _BLOB_AT_DATA:
            cut = i + 1
            break
    (ROOT / args.out).write_text(
        " ".join(head + mid[:cut] + rdata + mid[cut:] + thunk_objs + ordered
                 + tail_thunks + extra_objs + data + tail))
    print(f"{len(ordered)} split objects + {len(thunk_objs)} thunk objects -> {args.out} "
          f"({len(head) + len(mid) + len(ordered) + len(data) + len(tail)} tokens)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
