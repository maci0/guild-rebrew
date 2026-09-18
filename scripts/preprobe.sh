#!/bin/bash
# preprobe.sh - answer "has this already been measured?" BEFORE a probe runs.
#
# Why (round 981): rounds 976-981 each opened by probing a carrier or axis whose
# result was already recorded -- srv_LoadBuf order (+574) and m_AllocTracked
# guards (+539) in 976, ServerMainThread's packet block (+0/+0/+861) in 979,
# /Os on gm_AllocSpieler (+0xbfae) in 981.  Every one of those results was in
# docs/ OR in the carrier's own .c header, and every round read neither first.
# The two rules already existed (workflow-traps sections 8 and 9); what was
# missing was a step in the opening that forces the lookup.  This is that step.
#
#   scripts/preprobe.sh <carrier.c> [fault-address]
#   scripts/preprobe.sh src/server.dll/.../gm_AllocSpieler.c
#   scripts/preprobe.sh src/server.dll/.../gm_AllocSpieler.c 0x100188fa
set -uo pipefail
cd "$(dirname "$0")/.."

f=${1:?usage: preprobe.sh <carrier.c> [fault-address]}
[ -f "$f" ] || { echo "no such file: $f" >&2; exit 2; }

echo "== 1. docs/ lookup (whathas.py)"
if [ $# -ge 2 ]; then
    python3 scripts/whathas.py "$2" --window 48 || true
else
    va=$(grep -m1 '^// FUNCTION: SERVER' "$f" | awk '{print $4}')
    if [ -n "${va:-}" ]; then
        python3 scripts/whathas.py "$va" --window 48 || true
    else
        echo "  (no FUNCTION header found; pass a fault address explicitly)"
    fi
fi

echo
echo "== 2. the carrier's OWN HEADER -- whathas.py does NOT index this (workflow-traps 8)"
echo "   reading $f lines 1-140:"
sed -n '1,140p' "$f" | grep -nE '^[0-9]+:.*' | \
    grep -iE 'revert|inert|worse|measured|closed|do not|dead end|probed|dead-end|dead end|section [0-9]|shapes' | \
    sed 's/^/   /' | head -40
echo
echo "   ^ if any line above names the change you are about to make, DO NOT PROBE IT."
echo "     Grep the whole header when in doubt:  grep -niE 'inert|revert|worse' \"$f\""

echo
echo "== 3. fault vs symptom (workflow-traps 9)"
echo "   scripts/fault_address.py prints both columns for all 19 carriers."
echo "   Look up the FAULT, not the lowest differing byte."
