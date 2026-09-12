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

echo "== split (member data; --closure is subsumed by the completed map)"
rm -rf "$WORK/split"
python3 scripts/split_coff.py "${LIBS[@]}" --map "$MAP" \
    --out "$WORK/split" --with-data

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
cmd=$(sed "s#@CMakeFiles/server_dll.dir/objects1.rsp#@${WORK#build/}/rsp.rsp#;
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
