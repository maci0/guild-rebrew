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

# Fail before measuring stale inputs, including shared header dependencies.
rebrew build-check --objects

# ---- staleness guard (round 145) -------------------------------------------
# This script RE-LINKS; it does not compile.  A source edited after its object
# was built is therefore invisible: the run measures the old object and reports
# a result that has nothing to do with the edit.  That cost round 145 an
# experiment.  Two conditions are checked, and they are different in kind:
#
#   * source newer than object  -> the object is stale, the run is meaningless;
#   * object newer than NOW     -> its timestamp is in the FUTURE (objects here
#     have been written 1h12m ahead of the host clock), so mtime comparison
#     cannot be trusted for that file at all and `make` may skip it.
#
# Neither is fatal for a pure re-link (which is what most rounds do), so this
# warns rather than exits -- but it warns loudly, and deletes nothing.
if [ "${SPLIT_LINK_SKIP_STALE_CHECK:-0}" != "1" ]; then
    now=$(date +%s)
    stale=0
    future=0
    while IFS= read -r src; do
        obj="build/CMakeFiles/server_dll.dir/${src}.obj"
        [ -f "$obj" ] || continue
        smt=$(stat -c %Y "$src" 2>/dev/null || echo 0)
        omt=$(stat -c %Y "$obj" 2>/dev/null || echo 0)
        if [ "$smt" -gt "$omt" ]; then
            echo "WARNING: $src is newer than its object; this link will use the STALE object" >&2
            echo "  run: cmake --build build --target server_dll   (or rm '$obj')" >&2
            stale=$((stale + 1))
        fi
        [ "$omt" -gt "$now" ] && future=$((future + 1))
    done < <(find src -name '*.c' 2>/dev/null)
    if [ "$future" -gt 0 ]; then
        echo "WARNING: $future object(s) carry a timestamp in the FUTURE; mtime staleness cannot be trusted" >&2
        echo "  delete the specific .obj when testing a source change" >&2
    fi
    [ "$stale" -eq 0 ] && [ "$future" -eq 0 ] && echo "staleness check: clean"
fi
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
    --out "$WORK/split" --with-data --trim --split-rdata --promote-statics \
    --drop-data crt0msg.obj --drop-data tzset.obj --drop-data intrncvt.obj \
    --drop-data mbctype.obj

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

echo "== CRT .data band (library sections, reference order, before the tail)"
rm -rf "$WORK/crt_data"
python3 scripts/emit_crt_data.py --lib .scratch/libcmt/LIBCMT.sp6.LIB \
    --out "$WORK/crt_data"
CRT_SKIP=()
while IFS= read -r sym; do
    [ -n "$sym" ] && CRT_SKIP+=(--skip "$sym")
done < "$WORK/crt_data/skip.txt"

echo "== definitions (iterated to a fixed point)"
rm -rf "$WORK/defs"
python3 scripts/emit_defs.py "${LIBS[@]}" "${CRT_SKIP[@]}" --rsp "$WORK/rsp1.rsp" \
    --out "$WORK/defs"

echo "== response file (final) and link"
python3 scripts/make_split_rsp.py --split "$WORK/split" --objects "$OBJ_RSP" \
    --thunks "$WORK/thunks" --commons "$WORK/commons" --defs "$WORK/defs" \
    --out "$WORK/rsp.rsp"

if [ "${REBREW_SKIP_SPLIT_BLOB:-0}" != "1" ]; then
echo "== split blob (member .rdata sections at their reference offsets)"
# The member .rdata sections the link keeps (string literals, ___lookuptable,
# the unnamed pointer tables, the __real@8@ constants, ___dnames/___mnames)
# have reference offsets *inside* rdata_restore.c's range, which one array
# cannot express: cut it into pieces around them.  Verified: zero mismatching
# bytes in [0x1a0, 0x2608), .text placement and all four raw sizes unchanged.
# Only the all-zero literals ("", L"\0") cannot be placed unambiguously;
# Matched CRT code references locate those zero literals.
uv run --frozen python scripts/split_blob.py --rsp "$WORK/rsp.rsp" --split "$WORK/split" \
    --defs "$WORK/defs" --defs "$WORK/crt_data/locale_rdata" --work "$WORK" --byte-align \
    --blob crt_region/rdata_restore.c.obj
fi

mkdir -p "$WORK/abs"
python3 scripts/emit_absolute_obj.py --name _z_errmsg_empty --value 0x10034620 \
    --out "$WORK/abs/abs__z_errmsg_empty.obj"
echo "wrote absolute _z_errmsg_empty"
# The rsp is rebuilt below; this object is added with the other absolutes.

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
# z_errmsg empty-string anchor. The CMake link already carries the same
# absolute object; appending a second copy is a duplicate symbol.
if ! grep -q 'abs__z_errmsg_empty\.obj' "$WORK/rsp.rsp"; then
  printf ' %s' "${WORK#build/}/abs/abs__z_errmsg_empty.obj" >> "$WORK/rsp.rsp"
fi
# LIBCMT .data for the band before the historical tail. After every other
# contribution and before the gap blob, so the blob cannot cover 0xcbb0.
python3 - "$WORK/rsp.rsp" "$WORK/crt_data" <<'PY'
import sys
from pathlib import Path
rsp, folder = Path(sys.argv[1]), Path(sys.argv[2])
objs = sorted(folder.glob("crt_*.obj"))
if not objs:
    raise SystemExit("no CRT .data objects")
text = rsp.read_text().rstrip()
extra = " ".join(p.relative_to(Path("build")).as_posix() for p in objs)
rsp.write_text(text + " " + extra + "\n")
print(f"appended {len(objs)} CRT .data objects ahead of the gap blob")
PY

echo "== drop the reference .data splice"
# data_restore.c.obj is a copy of reference .data. lconv and constpow now
# come from LIBCMT (emit_crt_data.py), and the bytes after constpow through
# the file-alignment boundary are zeros, so the section still rounds to
# raw 0xe000 without pasting the reference.
python3 - "$WORK/rsp.rsp" <<'RSP'
import shlex, sys
from pathlib import Path
rsp = Path(sys.argv[1])
tokens = shlex.split(rsp.read_text())
kept = [t for t in tokens if not t.endswith("/crt_region/data_restore.c.obj")
        and not t.endswith("/data_restore_split.obj")]
rsp.write_text(" ".join(kept) + "\n")
print(f"dropped the reference .data splice ({len(tokens) - len(kept)} object(s))")
RSP

LINK_RSP="${WORK#build/}/rsp.rsp"

cmd=$(sed "s#@CMakeFiles/server_dll.dir/objects1.rsp#@${LINK_RSP#build/}#;
           s#/out:server.dll#/out:split_poc.dll /MAP:split_poc.map#;
           s#/implib:server.lib#/implib:split_poc.lib#;
           s# /pdb:[^ ]*##" build/CMakeFiles/server_dll.dir/link.txt)
( cd build && eval "$cmd" >/dev/null 2>&1 )
if grep -q '_g_data_restore_gap' build/split_poc.map; then
    echo "g_data_restore_gap is still in build/split_poc.map; the reference .data splice is linked" >&2
    exit 1
fi
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
# head closes the pipe after four lines. Under pipefail that SIGPIPE is a
# failure even when the link and the audit both succeeded.
set +o pipefail
python3 scripts/split_audit.py build/split_poc.map | head -4
set -o pipefail
