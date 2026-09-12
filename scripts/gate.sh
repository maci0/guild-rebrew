#!/bin/bash
# gate.sh — the three checks a change must pass before it is committed.
#
#   rebrew lint           annotation and corpus consistency
#   cmake --build         compiles every TU (the POST_BUILD postlink step is
#                         expected to fail: the tree is not position-aligned,
#                         see docs/TODO.md; only compile/link errors are fatal)
#   rebrew verify --full  byte comparison of every annotated function, which
#                         must stay at or above the recorded baseline
#
# Usage: scripts/gate.sh
# Exit status: 0 when all three pass, 1 otherwise.

set -uo pipefail
cd "$(cd "$(dirname "$0")/.." && pwd)"
mkdir -p .scratch

BASELINE=${BASELINE:-278}
rc=0

echo "== rebrew lint"
rebrew lint 2>&1 | tail -1

echo "== build (compile errors only)"
cmake --build build -j8 > .scratch/gate-build.log 2>&1
errs=$(grep -cE "error C[0-9]+|error LNK" .scratch/gate-build.log)
echo "compile/link errors: $errs  (full log: .scratch/gate-build.log)"
[ "$errs" -eq 0 ] || rc=1

echo "== rebrew verify --full"
out=$(rebrew verify --full 2>&1 | tail -3)
echo "$out" | grep -E "Verification:" || true
passed=$(echo "$out" | sed -n 's/.*Verification: \([0-9]*\)\/\([0-9]*\) passed.*/\1/p')
if [ -z "$passed" ]; then
    echo "could not read the verification summary"
    rc=1
elif [ "$passed" -lt "$BASELINE" ]; then
    echo "REGRESSION: $passed passed, baseline is $BASELINE"
    rc=1
else
    echo "baseline $BASELINE held"
fi

[ "$rc" -eq 0 ] && echo "GATE: pass" || echo "GATE: FAIL"
exit "$rc"
