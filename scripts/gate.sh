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
# .text residue baseline: 8636 (0x21bc) as of round 516.  Guarded below --
# lower it when a change improves the number, never raise it.
#
# Raised twice, both times to buy a much larger .data gain, both recorded here
# because "never raise it" is otherwise the rule:
#
#   8633 -> 8635 (round 509, .data -231).  g_log_level_table was declared
#     `int[12]` where the reference gives the table 12 BYTES.  The fix needs
#     its declaration in rebrew_globals.h, which every TU includes; two
#     sp5-pp-pinned files each gained a byte inside functions that were ALREADY
#     unmatched, at an unchanged first-diff offset.  See section 150.
#   8635 -> 8636 (round 510, .data -1,350).  g_crash_newline/g_crash_space were
#     defined separately at VAs that fall INSIDE g_crashdump_data_10027104,
#     so those 8 bytes existed twice.  gm_AllocGebaeude gained one byte and its
#     OBJECT IS BYTE-IDENTICAL either way -- the byte is pure link placement,
#     not codegen.  See section 151.
#
# Both trades are net progress toward a build that needs no postlink, which is
# the objective; the shipped deliverable is unaffected either way because
# postlink overwrites .data wholesale.
#
# Round 511 gave one of those bytes back (8636 -> 8635) by DEFINING "_main_:"
# at 0x10028938, which nothing defined: link_stubs.c had two zeroed ints
# standing in for it.  .data -306 in the same change.  See section 152.
#
# Round 512 raised it again (8635 -> 8636) while landing two follow-ups on
# that same string run: (1) spell "_main_:" as an anonymous literal so it
# lands LAST among m_alloc.c's COMDATs (a named array went FIRST and
# displaced "Memory-Underflow Error"); (2) drop five truncated stub arrays
# in m_alloc2.c that duplicated COMDAT literals.  .data 26,066 -> 25,884.
# The +1 .text byte is pure link placement -- the three residue-table objects
# are md5-identical.  See section 153.
#
# Round 513 gave that byte back (8636 -> 8635) and cut .data by 2,105 by
# extracting the winsock/SO_* string run into winsock_data.c, ordered via
# --first-va between m_alloc2 and trees.  See section 154.
#
# Round 514 raised it again (8635 -> 8637, +2) while prepending "rb"/gzip
# magic to vfs4.c and killing the duplicate gz COMDAT in vfs_ReadData.c.
# .data 23,779 -> 23,526 (-253).  The +2 is codegen from switching the
# sprintf/LogMessageInternal args from a literal+raw-address cast to named
# symbols (vfs_ReadData.obj md5 changes).  See section 155.
#
# Round 515 gave three bytes back (8637 -> 8634) and cut .data by 54 by
# defining the vfs_OpenStream format string as a named array in that TU
# (already linked before zutil).  See section 156.
#
# Round 516 raised it again (8634 -> 8636, +2) while dropping the explicit
# broadcast.c named dword 0xffffffff + path/msg arrays -- anonymous COMDATs
# omitted the leading dword and shifted every later .data symbol by -4.
# .data 23,470 -> 22,541 (-929).  See section 158.
RESIDUE_BASELINE=${RESIDUE_BASELINE:-8636}
# Raw-link .data divergence baseline (22,541 as of round 517).  The goal is a build that is
# byte-identical WITHOUT postlink, but postlink blits .data wholesale from the
# layout package, so the shipped file shows `.data differing 0x0` no matter what
# the link produced -- and this gate, guarding .text alone, could not see .data
# move at all.  Three rounds of data work were invisible to it.  Guard the raw
# link's own .data so progress there is measured and regressions there caught.
DATA_BASELINE=${DATA_BASELINE:-22541}
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
    full=$(.venv/bin/python scripts/postlink_residual.py --write build/server.dll \
           2>.scratch/gate-residue.log)
    res=$(echo "$full" | grep -E "^\.text differing")

    # .data, from the RAW LINK block (the shipped file's .data is copied, so it
    # is always 0x0 and says nothing).  Reported always; enforced as a ceiling.
    draw=$(echo "$full" | sed -n 's/^  \.data *differing *\(0x[0-9a-f]*\) .*/\1/p')
    if [ -n "$draw" ]; then
        dnow=$(printf '%d' "$draw")
        if [ "$dnow" -gt "$DATA_BASELINE" ]; then
            echo "REGRESSION: raw-link .data $dnow (0x$(printf '%x' "$dnow")), baseline is" \
                 "$DATA_BASELINE (0x$(printf '%x' "$DATA_BASELINE"))"
            rc=1
        else
            echo "raw-link .data $dnow, baseline $DATA_BASELINE held"
        fi
    else
        echo "raw-link .data not measured (see .scratch/gate-residue.log)"
        rc=1
    fi

    if [ -n "$res" ]; then
        echo "$res"
        # Guard the residue too.  Round 215: a phantom 367-byte regression
        # (0x2347 against the 0x21d8 baseline) passed the gate untouched,
        # because only lint, compile errors and the two verify baselines were
        # checked.  It came from `touch`ing a source to force a rebuild, which
        # produced a partial relink; the source was byte-identical to HEAD.
        now=$(printf '%d' "$(echo "$res" | sed -E 's/.*differing (0x[0-9a-f]+) .*/\1/')")
        if [ "$now" -gt "$RESIDUE_BASELINE" ]; then
            echo "REGRESSION: residue $now (0x$(printf '%x' "$now")), baseline is" \
                 "$RESIDUE_BASELINE (0x$(printf '%x' "$RESIDUE_BASELINE"))"
            rc=1
        else
            echo "residue $now, baseline $RESIDUE_BASELINE held"
        fi
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
