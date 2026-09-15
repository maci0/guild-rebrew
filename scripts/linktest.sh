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
    # Compile the live file.  A frozen copy under a dot-prefixed name was tried
    # to defeat the agents' sample-write sweeps and it collapses the composition
    # (`exactly at their reference VA: 0`, residue x12) -- something downstream
    # in split_link.sh/pad_short_functions.py keys off the object's source path.
    # The race is handled socially instead: a file is only measured after its
    # agent says "file frozen".
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

# Stale-object guard.  A source NEWER than its object means the object holds code
# that is not in the source -- which happens whenever a candidate is reverted (git
# checkout rewrites the source and bumps its mtime) without recompiling, and it
# silently poisons every number the run reports.  This is the round-195 case: the
# tree was clean but one object still held a reverted agent variant.
stale=$(cd build && for o in $(find CMakeFiles/server_dll.dir -name '*.obj'); do
    rel=${o#CMakeFiles/server_dll.dir/}; src="../${rel%.obj}"
    if [ -f "$src" ] && [ "$src" -nt "$o" ]; then echo "${rel%.obj}"; fi
done)
if [ -n "$stale" ]; then
    echo "WARNING: these sources are newer than their objects, so the objects hold" >&2
    echo "         code that is NOT in the source tree -- recompile them or run a" >&2
    echo "         full 'cmake --build' before trusting this run:" >&2
    echo "$stale" | sed 's/^/           /' >&2
fi

# Attribution guard.  postlink_residual attributes differing bytes by reference
# VA, and every symbol after a changed object moves, so a per-function delta is
# attribution ONLY when no other object changed.  Round 179 committed a "-58"
# that re-measured at "+56" for exactly this reason: another agent's source had
# been edited by a previous run and its stale object sat in the link.  A source
# that is modified in git but not named here is that contamination.
for dirty in $(git status --porcelain -- '*.c' | awk '{print $2}'); do
    case " $* " in
        *" $dirty "*) ;;
        *) echo "WARNING: $dirty is modified but not in this run -- the per-function" >&2
           echo "         delta below will mix its contribution with these files'" >&2
           echo "         (see docs/TODO.md round 179).  Name it too, or revert it." >&2 ;;
    esac
done

if ! bash scripts/split_link.sh > .scratch/linktest-link.log 2>&1; then
    echo "link FAILED -- tail of .scratch/linktest-link.log:" >&2
    tail -12 .scratch/linktest-link.log >&2
    exit 1
fi
# Composition guard.  The split link places each object at its reference VA; when
# that collapses, EVERY number below is meaningless but nothing else says so --
# the residue simply reads ten times too high and every other signal points at
# the source.  Round 232 lost most of a round to this: the source tree was clean
# and a full object rebuild did not help, because the stale artefact was
# build/split_poc itself (deleting the CMake objects orphans that workspace and
# it is not regenerated on its own).  The fix is `rm -rf build/split_poc`.
placed=$(grep -oE "exactly at their reference VA: [0-9]+" .scratch/linktest-link.log \
         | tail -1 | grep -oE "[0-9]+$")
if [ -n "$placed" ] && [ "$placed" -lt 100 ]; then
    echo "COMPOSITION COLLAPSED: only $placed symbols landed at their reference VA." >&2
    echo "         Every residue number below would be meaningless.  Fix with:" >&2
    echo "             rm -rf build/split_poc && bash scripts/split_link.sh" >&2
    echo "         (see docs/msvc6-c-shapes.md section 124)" >&2
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
