#!/bin/bash
# split_link.sh - reproduce the split-set PoC link end to end.
#
#   LIBCMT is never reversed: scripts/map_libcmt.py says which stock member
#   body the reference has at each VA, scripts/locate_sections.py completes
#   that map with the member sections the catalog mapping cannot reach,
#   scripts/split_coff.py turns each mapped section into a command-line object,
#   scripts/emit_commons.py defines the members' commons, scripts/emit_thunks.py
#   restores the socket IAT thunks, scripts/emit_defs.py defines whatever is
#   still undefined, and scripts/make_split_rsp.py assembles the response file.
#
# Requires a configured and built CMake tree (build/CMakeFiles/server_dll.dir/
# objects1.rsp).  Usage:
#
#   scripts/split_link.sh [workdir]        # default build/split_poc
#
# Prints the built .text VirtualSize against the reference's 0x22846 and the
# per-object placement audit.
set -euo pipefail
cd "$(dirname "$0")/.."

WORK=${1:-build/split_poc}
# These five stock archives live in gitignored .scratch/, so a clean checkout
# (or a scratch cleanup -- round 172) will not have them.  Re-extract with:
#   for p in sp6:6.0-sp6-win32:msvc6.0-sp6 sp5:6.0-sp5-win32:msvc6.0-sp5 \
#            sp4:6.0-sp4-win32:msvc6.0-sp4 base:6.0-win32:msvc6.0; do
#     n=${p%%:*}; r=${p#*:}; cid=$(docker create "rebrew/msvc:${r%%:*}")
#     docker cp "$cid:/opt/${r#*:}/VC98/Lib/LIBCMT.LIB" ".scratch/libcmt/LIBCMT.$n.LIB"
#     docker rm -f "$cid"
#   done
# (sp4's path is lowercase `lib/libcmt.lib`; vc7 comes from
#  rebrew/msvc:7.0-win32 at /opt/msvc7.0/Vc7/lib/libcmt.lib.)
LIBS=(
  --lib .scratch/libcmt/LIBCMT.sp6.LIB
  --lib .scratch/libcmt/LIBCMT.sp5.LIB
  --lib .scratch/libcmt/LIBCMT.base.LIB
  --lib .scratch/libcmt/LIBCMT.vc7.LIB
  --lib .scratch/libcmt/LIBCMT.sp4.LIB
)
OBJ_RSP=build/CMakeFiles/server_dll.dir/objects1.rsp
MAP=.scratch/libcmt_map_u.json

mkdir -p "$WORK"
echo "== map"
python3 scripts/map_libcmt.py "${LIBS[@]}" --json > "$MAP"

echo "== map completion (locate member sections the catalog mapping missed)"
python3 scripts/locate_sections.py --members "${LIBS[@]}" --map "$MAP" --json \
    > "$WORK/extra.json"
python3 - "$MAP" "$WORK/extra.json" "$WORK/map_full.json" <<'PY'
import json, sys
base, extra, out = sys.argv[1], sys.argv[2], sys.argv[3]
m = json.load(open(base))
x = json.load(open(extra))["matched"]
have_va = {int(e["va"], 16) for e in m["matched"]}
have_ms = {(e["member"], e.get("section")) for e in m["matched"]}
add = [e for e in x
       if int(e["va"], 16) not in have_va and (e["member"], e.get("section")) not in have_ms]
m["matched"] = sorted(m["matched"] + add, key=lambda e: int(e["va"], 16))
json.dump(m, open(out, "w"), indent=1)
print(f"{len(add)} extra sections merged")
PY
MAP="$WORK/map_full.json"

echo "== split (member data, trimmed to the reference function's size)"
rm -rf "$WORK/split"
# `--split-rdata` puts each member's `.rdata` sections in their own objects so
# they can be ordered independently (the split blob); it also lets them fold on
# their own, which is worth 0xa0 of the prefix surplus with the prefix bytes
# still byte-identical.  `--promote-statics` makes a split member's own data
# statics external so its functions still resolve them; without it `/FORCE`
# leaves those references at RVA 0 and ~74 layout-map entries fail with a built
# value of exactly image_base (docs/TODO.md round 137).  See rounds 129-138.
python3 scripts/split_coff.py "${LIBS[@]}" --map "$MAP" \
    --out "$WORK/split" --with-data --trim --split-rdata --promote-statics

echo "== import thunks"
rm -rf "$WORK/thunks"
python3 scripts/emit_thunks.py --target-bin original/Server/server.dll \
    --out "$WORK/thunks"

echo "== commons"
rm -rf "$WORK/commons"
python3 scripts/emit_commons.py "${LIBS[@]}" --map "$MAP" --out "$WORK/commons"

echo "== response file (pass 1, so emit_defs can see the real object set)"
python3 scripts/make_split_rsp.py --split "$WORK/split" --objects "$OBJ_RSP" \
    --thunks "$WORK/thunks" --commons "$WORK/commons" --out "$WORK/rsp1.rsp"

echo "== definitions (iterated to a fixed point)"
rm -rf "$WORK/defs"
python3 scripts/emit_defs.py "${LIBS[@]}" --rsp "$WORK/rsp1.rsp" --out "$WORK/defs"

echo "== response file (final) and link"
python3 scripts/make_split_rsp.py --split "$WORK/split" --objects "$OBJ_RSP" \
    --thunks "$WORK/thunks" --commons "$WORK/commons" --defs "$WORK/defs" \
    --out "$WORK/rsp.rsp"

echo "== fold literals (member string COMDATs the blob already carries)"
# msvc6 derives a `??_C@...` COMDAT name from the literal's contents and LINK
# folds COMDATs by name, so re-declaring every member string here makes the
# linker discard the members' copies: .rdata 0x33b1 -> 0x2fe1, raw 0x4000 ->
# 0x3000, the reference's.  The generated array lands in `.data`, which
# postlink overwrites wholesale.  See docs/msvc6-link-layout.md section 3.
python3 scripts/gen_fold_literals.py --split-dir "$WORK/split" > "$WORK/fold_literals.c"
rebrew-cmake-cl /nologo /c /O2 /Gd /MT /Fo"$WORK/fold_literals.obj" \
    "$WORK/fold_literals.c" >/dev/null
python3 - "$WORK/rsp.rsp" "${WORK#build/}/fold_literals.obj" <<'RSP'
import shlex, struct, sys
from pathlib import Path

rsp, obj = Path(sys.argv[1]), sys.argv[2]
tokens = shlex.split(rsp.read_text())


def defines_literal(token):
    """True if this *member* object defines a `??_C@` COMDAT of its own.

    Game objects are irrelevant to the boundary: if one of ours defines the
    literal first, the member's copy is discarded either way.  Only a member
    object winning the name ahead of us breaks the fold.
    """
    if not token.endswith(".obj"):
        return False
    if not ("split/" in token or "g_rdata_piece" in token or "rdata_restore" in token):
        return False
    try:
        d = (Path("build") / token).read_bytes()
        symoff = struct.unpack_from("<I", d, 8)[0]
        nsym = struct.unpack_from("<I", d, 12)[0]
        strtab = d[symoff + nsym * 18:]
        for i in range(nsym):
            e = d[symoff + i * 18:symoff + (i + 1) * 18]
            if e[:4] == b"\0\0\0\0":
                off = struct.unpack_from("<I", e, 4)[0]
                name = strtab[off:].split(b"\0")[0].decode("latin1")
            else:
                name = e.split(b"\0")[0].decode("latin1")
            _v, secno, _t, cls, _a = struct.unpack_from("<IhHBB", e, 8)
            if cls == 2 and secno > 0 and name.startswith("??_C@"):
                return True
    except (OSError, struct.error):
        pass
    return False


if obj not in tokens:
    # LINK keeps the FIRST COMDAT of a given name, so this object only has to
    # precede the first member object that defines a `??_C@` -- not the whole
    # link.  Everything before that point is game code whose `.data` our array
    # would otherwise displace: at token 1 it shifted every game symbol by
    # +0x488; here it shifts almost none (game `.data` is 0x3d4a of 0x3dbb
    # before the boundary).  Verified both ways -- see msvc6-c-shapes.md #102.
    pos = next((i for i, t in enumerate(tokens) if defines_literal(t)), 1)
    tokens.insert(pos, obj)
    print(f"fold object {obj} inserted at token {pos} (before the first member ??_C@)")
rsp.write_text(" ".join(tokens))
RSP

if [ "${REBREW_SKIP_SPLIT_BLOB:-0}" != "1" ]; then
echo "== split blob (member .rdata sections at their reference offsets)"
# The sections that cannot fold (___lookuptable, the unnamed pointer tables,
# the __real@8@ constants, ___dnames/___mnames) have reference offsets *inside*
# rdata_restore.c's range, which one array cannot express: cut it into pieces
# around them.  Verified: import directory 0x2778 -> 0x2610, zero mismatching
# bytes in [0x1a0, 0x2608), .text placement and all four raw sizes unchanged.
# The remaining 8 bytes of surplus are cvt.obj's `__real@8@0`, which the
# reference packs at an odd offset - see docs/TODO.md round 133.
python3 scripts/split_blob.py --rsp "$WORK/rsp.rsp" --split "$WORK/split" \
    --defs "$WORK/defs" --work "$WORK" --byte-align \
    --blob crt_region/rdata_restore.c.obj
fi

echo "== absolute definitions for the static labels the split leaves undefined"
# split_coff splits a member per section, so a relocation to a local label in
# another of its sections ($T17396, the LIBCMT SEH scopetable malloc's prologue
# pushes) survives as an undefined *static*.  LINK never reports those: it
# defines them as absolute 0, so the seven SEH prologues in the composition
# pushed 0x10000000 where the reference pushes the scopetable address (21 bytes
# and 7 of postlink's failing operand entries; every non-split build resolves
# all seven).  Statics are object-local, so the fix is in place: promote the
# symbol to an external ABSOLUTE definition at the address the reference's own
# link wrote.  No section bytes are added, so the geometry is untouched.
python3 scripts/resolve_static_labels.py --rsp "$WORK/rsp.rsp" \
    --reference original/Server/server.dll --out "$WORK/abs" --rewrite

echo "== data gap for this composition"
# `data_restore.c`'s blob is sized for the CMake composition (its own .data
# ends at 0xdf00 with a 0x9a00 blob).  The split objects carry more `.data`
# (the members' bundled sections), so the CMake blob overshoots the reference's
# 0xe000 raw size by 0x2460.  postlink overwrites `.data` wholesale, so only
# the blob's LENGTH matters (docs/msvc6-link-layout.md section 2) - emit a
# shorter one for this link and drop the CMake object.  Re-sweep the constant
# when the composition's own `.data` changes.
# GAP =0xe000 - (total .data of every object before the blob in rsp.rsp).
# The reorg'd src/Develop composition emits S=0x7736 before the blob (was0x6b60
# when GAP was0x74a0); the stale0x74a0 placed the ref-tail blob0xbd6 early ->
# .data 45% off.  Re-derive on every composition change: GAP=0xe000-S.
GAP=0x68ca
python3 - "$GAP" "$WORK/data_restore_split.c" <<'BLOB'
import struct, sys
from pathlib import Path
size = int(sys.argv[1], 0)
out = Path(sys.argv[2])
ref = Path("original/Server/server.dll").read_bytes()
pe = struct.unpack_from("<I", ref, 0x3C)[0]
count = struct.unpack_from("<H", ref, pe + 6)[0]
opt = pe + 24
for i in range(count):
    off = opt + struct.unpack_from("<H", ref, pe + 20)[0] + i * 40
    if ref[off : off + 8].rstrip(b"\0") == b".data":
        raw = struct.unpack_from("<I", ref, off + 16)[0]
        ptr = struct.unpack_from("<I", ref, off + 20)[0]
        break
blob = ref[ptr + raw - size : ptr + raw]
lines = [f"unsigned char g_data_restore_gap[0x{size:x}] = {{"]
for i in range(0, len(blob), 16):
    lines.append("\t" + ",".join(f"0x{b:02x}" for b in blob[i : i + 16]) + ",")
lines.append("};")
out.write_text("\n".join(lines) + "\n")
print(f"wrote {out} ({size:#x} bytes)")
BLOB
rebrew-cmake-cl /nologo /c /O2 /Gd /MT \
    /Fo"$WORK/data_restore_split.obj" "$WORK/data_restore_split.c" >/dev/null
python3 - "$WORK/rsp.rsp" "${WORK#build/}/data_restore_split.obj" <<'RSP'
import shlex, sys
from pathlib import Path
rsp, obj = Path(sys.argv[1]), sys.argv[2]
tokens = shlex.split(rsp.read_text())
tokens = [t for t in tokens if not t.endswith("/crt_region/data_restore.c.obj")]
# The pad is a LENGTH-only filler (its bytes are the reference .data tail and
# postlink overwrites .data wholesale), but inserting it FIRST displaced every
# game .data symbol by +0x74a0, which alone accounted for 0x1758 of the .data
# residue.  Appending it instead keeps the geometry (raw still 0xe000) and drops
# the uniform displacement to +0x488.  See docs/msvc6-c-shapes.md section 101.
tokens.append(obj)
rsp.write_text(" ".join(tokens))
print(f"swapped the CMake data blob for {obj}")
RSP

echo "== pad short functions (so the symbols after them keep their reference VAs)"
# `make_split_rsp.py` orders the link by reference VA, so an object whose .text
# comes out SHORT drags everything after it and the composition stops being
# position-aligned -- which makes a better-shaped but differently-sized function
# unusable.  A .text-only pad object is inserted after each short one; see
# scripts/pad_short_functions.py.
python3 scripts/pad_short_functions.py --rsp "$WORK/rsp.rsp" \
    --out-dir "$WORK/pad" --out-rsp "$WORK/rsp_pad.rsp"
RSP_PAD="${WORK#build/}/rsp_pad.rsp"

cmd=$(sed "s#@CMakeFiles/server_dll.dir/objects1.rsp#@${RSP_PAD#build/}#;
           s#/out:server.dll#/out:split_poc.dll /MAP:split_poc.map#;
           s#/implib:server.lib#/implib:split_poc.lib#;
           s# /pdb:[^ ]*##" build/CMakeFiles/server_dll.dir/link.txt)
( cd build && eval "$cmd" >/dev/null 2>&1 )
python3 - <<'PY'
import struct
def vsize(path):
    b = open(path, 'rb').read()
    e = struct.unpack_from('<I', b, 0x3c)[0]
    n = struct.unpack_from('<H', b, e + 6)[0]
    o = struct.unpack_from('<H', b, e + 20)[0]
    off = e + 24 + o
    for i in range(n):
        s = b[off + i * 40:off + (i + 1) * 40]
        if s[0:5] == b'.text':
            return struct.unpack_from('<I', s, 8)[0]
ref = vsize('original/Server/server.dll')
got = vsize('build/split_poc.dll')
print('reference .text %#x' % ref)
print('split-set .text %#x  (%+d)' % (got, got - ref))
PY
python3 scripts/split_audit.py build/split_poc.map | head -4
