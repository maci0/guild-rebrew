#!/bin/bash
# gate.sh — the three checks a change must pass before it is committed.
#
#   rebrew lint           annotation and corpus consistency
#   cmake --build         compiles every TU (the POST_BUILD postlink step is
#                         expected to fail: the tree is not position-aligned,
#                         see docs/TODO.md; only compile/link errors are fatal)
#   rebrew verify --full  byte comparison of every annotated function, which
#                         must stay at or above the recorded baseline
#   deliverable link       split_link + postlink actually run, so the residue
#                         reported each round is measured, not inherited
#
# Usage: scripts/gate.sh
# Exit status: 0 when all four pass, 1 otherwise.

set -uo pipefail
cd "$(cd "$(dirname "$0")/.." && pwd)"
mkdir -p .scratch

BASELINE=${BASELINE:-281}
# `passed` counts EXACT + RELOC + PROVEN, but AGENTS.md is explicit that PROVEN
# is NOT a byte match and ranks below RELOC.  Today that is 264 byte matches
# plus 17 PROVEN, so a RELOC -> PROVEN regression would leave `passed` at 281
# and this gate green while the deliverable lost bytes.  Guard the byte-match
# count separately (round 193).
BYTE_BASELINE=${BYTE_BASELINE:-264}
# .text residue baseline: 8665 (0x21d9) as of round 202.
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

# Byte-match guard: EXACT + RELOC only, never PROVEN.
bytes_now=$(rebrew verify --full --json 2>/dev/null \
    | python3 -c 'import json,sys; rs=json.load(sys.stdin)["results"]; print(sum(1 for r in rs if r.get("status") in ("EXACT","RELOC")))' 2>/dev/null)
if [ -z "$bytes_now" ]; then
    echo "could not count byte-matched functions"
    rc=1
elif [ "$bytes_now" -lt "$BYTE_BASELINE" ]; then
    echo "REGRESSION: $bytes_now byte-matched (EXACT+RELOC), baseline is $BYTE_BASELINE"
    rc=1
else
    echo "byte-matched $bytes_now (EXACT+RELOC), baseline $BYTE_BASELINE held"
fi

echo "== deliverable link + residue"
# Round 172: split_link.sh once died in its first step while the caller chained
# it with ';', and five rounds reported the previous binary's residue as if it
# were fresh.  Both steps are checked here, and postlink_residual.py refuses a
# build older than the sources.
if bash scripts/split_link.sh > .scratch/gate-link.log 2>&1; then
    res=$(.venv/bin/python scripts/postlink_residual.py --write build/server.dll \
          2>.scratch/gate-residue.log | grep -E "^\.text differing")
    if [ -n "$res" ]; then
        echo "$res"
    else
        echo "residue not measured (see .scratch/gate-residue.log)"
        rc=1
    fi
else
    echo "split_link FAILED (see .scratch/gate-link.log)"
    rc=1
fi

[ "$rc" -eq 0 ] && echo "GATE: pass" || echo "GATE: FAIL"
exit "$rc"
