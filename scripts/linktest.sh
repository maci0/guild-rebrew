#!/bin/bash
# linktest.sh - measure candidate source changes at the LINK level.
#
# The object-level scores are proxies, and round 173 caught them pointing the
# wrong way four times (two of them the coordinator's): a change that raises
# `matched` or `aligned` in probe_function.py can still grow the composed
# image's residue, because the residue is a *positional* byte compare over the
# whole .text and a size change in one object moves everything after it.  So a
# candidate is only ever kept after this cycle.
#
#   scripts/linktest.sh <src.c> [<src.c> ...]        # recompile, relink, diff
#   scripts/linktest.sh --new-base <src.c> ...       # also adopt the result as the baseline
#
# Recompiles each file with the exact command build.make records for it (the
# same one `cmake --build` runs, so the flags cannot drift), relinks the
# per-reference-offset composition, applies postlink, and diffs the per-function
# residue table against .scratch/residue_base.log.
#
# Re-snapshot the baseline with:
#   .venv/bin/python scripts/postlink_residual.py --write build/server.dll > .scratch/residue_base.log
set -uo pipefail
cd "$(dirname "$0")/.."

BASE=.scratch/residue_base.log
NEW_BASE=0
if [ "${1:-}" = "--new-base" ]; then NEW_BASE=1; shift; fi
[ $# -gt 0 ] || { sed -n '2,20p' "$0"; exit 2; }

for f in "$@"; do
    rel=${f#./}
    # build.make writes its targets relative to the build directory
    rule="CMakeFiles/server_dll.dir/$rel.obj"
    line=$(grep -A4 "$rule:" build/CMakeFiles/server_dll.dir/build.make \
           | grep rebrew-cmake-cl | grep -v /FAs | head -1)
    if [ -z "$line" ]; then
        echo "no compile rule for $rel -- is the tree configured?" >&2
        exit 1
    fi
    cmd=$(echo "$line" \
        | sed -e 's|$(C_DEFINES)|-DREBREW_ALLOW_NAKED=1 -Dserver_dll_EXPORTS|' \
              -e "s|\$(C_INCLUDES)|-I$PWD/src/server.dll -I$PWD/references/zlib-1.1.3|" \
              -e 's|$(C_FLAGS)|/W3 /D "WIN32" /D "_WINDOWS" /D "_WIN32_WINNT=0x0400" /D "NDEBUG" -MT /W3|')
    if ! (cd build && eval "$cmd" >/dev/null 2>&1); then
        echo "compile FAILED: $rel" >&2
        exit 1
    fi
    echo "recompiled $rel"
done

if ! bash scripts/split_link.sh > .scratch/linktest-link.log 2>&1; then
    echo "link FAILED -- tail of .scratch/linktest-link.log:" >&2
    tail -12 .scratch/linktest-link.log >&2
    exit 1
fi
.venv/bin/python -u scripts/postlink_residual.py --write build/server.dll \
    > .scratch/linktest-residue.log 2>&1
grep -E "^\.text differing" .scratch/linktest-residue.log

if [ "$NEW_BASE" = 1 ]; then
    cp .scratch/linktest-residue.log "$BASE"
    echo "baseline replaced ($BASE)"
else
    .venv/bin/python scripts/residue_diff.py "$BASE" .scratch/linktest-residue.log
fi
