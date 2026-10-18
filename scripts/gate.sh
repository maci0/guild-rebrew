#!/bin/bash
# gate.sh - the checks a change must pass before it is committed.
#
#   rebrew lint           annotation and corpus consistency
#   cmake --build         builds the raw server.dll with stock libraries
#   rebrew verify --no-cache  byte comparison plus linked EXACT from the raw DLL
#   rebrew verify --data  data bytes and symbol placement in the raw link
#   file identity         the raw DLL equals the reference without postlink
#
#   toolchain alignment   each target's configured compiler profile matches the
#                         code generator actually in its binary (Processor Pack
#                         vs plain, read from game-code x87 compares)
#
# Usage: scripts/gate.sh
# Exit status: 0 when all pass, 1 otherwise.

set -uo pipefail
cd "$(dirname "$0")/.." || exit 1
mkdir -p .scratch

# `rebrew verify` counts game EXACT + RELOC as passed (library-attributed rows are
# reported separately); PROVEN is not a byte match
# and fails like any other difference.
BASELINE=${BASELINE:-316}
rc=0

# Build-tree integrity.  build/ is gitignored, so no other check here can see it:
# a hand-edited build.make leaves git status clean, lint clean, verify unchanged,
# and `cmake --build` still "succeeding" -- while every measurement taken from the
# tree describes a build no fresh clone reproduces.  Round 1051 hit this sweeping
# toolchain pins: 58% residue and a 290,816-byte deliverable vs 286,720 / 8628.
# The check lives in rebrew (round 1055 moved it there from a project script) so
# every rebrew project gets it; `rebrew build check` exits 1 on drift.
echo "== build-tree integrity"
if [ -f build/CMakeFiles/server_dll.dir/flags.make ]; then
    if ! bc=$(rebrew build check 2>&1); then
        echo "$bc"
        echo "REGRESSION: build.make has been hand-edited -- the tree no longer"
        echo "  describes a reproducible build.  Restore with:"
        echo "    rm -rf build && cmake -B build -S . \\"
        echo "      --toolchain cmake/toolchain-msvc-6.0-sp5-docker.cmake \\"
        echo "      -DCMAKE_BUILD_TYPE=Release -DREBREW_DEBUG_INFO=OFF"
        rc=1
    else
        echo "$bc"
    fi
else
    echo "(not configured -- skipped)"
fi

echo "== rebrew lint"
# Warnings are fatal for this project; lint's ordinary exit contract covers errors.
if ! rebrew lint --json --target server.dll > .scratch/gate-lint.json; then
    rc=1
fi
if ! python3 - .scratch/gate-lint.json <<'PYEOF'
import json, sys
with open(sys.argv[1]) as handle:
    report = json.load(handle)
print("lint: %d passed, %d errors, %d warnings" %
      (report["passed"], report["errors"], report["warnings"]))
raise SystemExit(bool(report["errors"] or report["warnings"]))
PYEOF
then
    echo "REGRESSION: lint errors or warnings (both must be 0)"
    rc=1
fi

echo "== build raw server.dll"
# Delete the output so this run must link it; check the build exit status too.
rm -f build/server.dll
build_rc=0
cmake --build build --parallel 2 > .scratch/gate-build.log 2>&1 || build_rc=$?
errs=$(grep -cE "error C[0-9]+|error LNK" .scratch/gate-build.log)
echo "compile/link errors: $errs   cmake exit: $build_rc  (full log: .scratch/gate-build.log)"
if [ "$errs" -ne 0 ]; then
    rc=1
fi
if [ "$build_rc" -ne 0 ]; then
    echo "REGRESSION: cmake --build failed (exit $build_rc) while matching $errs compiler/linker errors"
    grep -E "error|Error [0-9]" .scratch/gate-build.log | head -3
    rc=1
fi
echo "== toolchain images"
# Check the pinned server image before interpreting compile failures.
if ! docker image inspect rebrew/msvc:6.0-sp5-win32 >/dev/null 2>&1; then
    echo "REGRESSION: toolchain image missing: rebrew/msvc:6.0-sp5-win32"
    echo "  rebuild: rebrew toolchain build msvc-6.0-sp5"
    echo "  Every function will report COMPILE_ERROR until then; that is not a"
    echo "  source break.  Not running verify, because its result would be noise."
    rc=1
    echo "GATE: FAIL"
    exit "$rc"
fi
echo "toolchain images present"

echo "== rebrew function, data and whole-binary verification"
# One upstream report supplies function/data verdicts and all structural checks.
# Whole-file equality also checks the physical order of import slots and names.
if ! rebrew verify --no-cache --functions --jobs 2 --text --raw-link --data --whole-binary \
        --built build/server.dll --json --target server.dll > .scratch/gate-verify.json; then
    echo "REGRESSION: upstream verification failed (see .scratch/gate-verify.json)"
    rc=1
fi
if ! python3 - .scratch/gate-verify.json "$BASELINE" <<'PYEOF'
import json, sys
with open(sys.argv[1]) as handle:
    report = json.load(handle)
summary = report["summary"]
print("Verification: %d/%d passed" % (summary["passed"], summary["total"]))
print("baseline %s: %d passed" % (sys.argv[2], summary["passed"]))
data = report["data"]
print("data: %d/%d matched" % (data["matched"], data["compared"]))
whole = report["whole_binary"]
for name in ("file", "sections", "exports", "imports", "relocations", "rsrc", "headers", "layout"):
    print("whole-binary %s: %s" % (name, whole[name]["match"]))
print("missing %d, extra %d -- baseline 0/0" %
      (len(whole["relocations"]["missing"]), len(whole["relocations"]["added"])))
if whole["file"]["match"] and whole["imports"]["match"]:
    print("raw link imports match the reference (whole-file bytes identical)")
raise SystemExit(not (report.get("functions_checked") is True
                     and summary["passed"] >= int(sys.argv[2])
                     and summary["failed"] == 0
                     and not data["mismatched"] and not data["missing"]
                     and whole["match"] and whole["layout"]["match"]))
PYEOF
then
    echo "REGRESSION: verification report does not meet project criteria"
    rc=1
fi

# Round 934: the objective's last criterion -- "Wine load + exports (Init, Exit)
# resolve" -- had no check anywhere.  lint/compile/verify/residue all pass on a
# DLL that cannot be loaded, and "it linked" is not "it loads" when postlink
# rewrites operands and blits sections.  The check is skipped (not failed) when
# wine or the cross-compiler is absent, so the gate stays usable off this host.
echo "== wine load + exports"
if bash scripts/wine_load_check.sh build/server.dll > .scratch/gate-wine.log 2>&1; then
    tail -1 .scratch/gate-wine.log
else
    echo "REGRESSION: wine load check failed --"
    cat .scratch/gate-wine.log
    rc=1
fi

# DirectX lib-match: the GOLDTL client statically links d3dx8.lib (DX8.1 SDK).
# Its bodies sit in .text like game code; this check vetoes them so the
# linker-supplied bytes are not reversed by mistake (the 0x63e931 case: D3DX8
# _jpeg_calc_output_dimensions was reversed as m_AllocTracked before this).
# The 907 known matches are LIBRARY-marked in library_d3dx8.h, so this finds
# only NEW reversals that collide with d3dx8 bodies.  The lib is vendored under
# references/ so a fresh clone reproduces the check.
echo "== lib-match d3dx8 (GOLDTL)"
if [ -f references/dxsdk8/lib/d3dx8.lib ]; then
    lm=$(rebrew library match --lib references/dxsdk8/lib/d3dx8.lib --target Europa1400Gold_TL.exe --json 2>&1)
    lmrc=$?
    cnt=$(echo "$lm" | python3 -c 'import json,sys
try: print(len(json.load(sys.stdin).get("findings", [])))
except Exception: print("ERR")' 2>/dev/null)
    echo "d3dx8 lib-match findings: $cnt"
    if [ "$cnt" != "0" ] && [ "$cnt" != "ERR" ]; then
        echo "REGRESSION: $cnt GOLDTL function(s) are D3DX8 library code"
        echo "$lm" | head -40
        rc=1
    elif [ "$cnt" = "ERR" ] || [ "$lmrc" -ge 2 ]; then
        echo "REGRESSION: rebrew library match d3dx8 failed on GOLDTL"
        echo "$lm" | head -40
        rc=1
    fi
else
    echo "d3dx8 lib not vendored -- skipped"
fi

# Code-generator lock (round 1379): the three binaries share cl 12.00.8804 but
# not the code generator -- both clients are Processor-Pack builds, the server
# is a plain one -- and the difference is invisible to a compiler-version check
# because every VC6 profile carries the same cl version.  Configure the wrong
# family and every FP-comparing function silently stops matching; this check
# reads the x87 compare idiom from GAME code (library bands excluded) and
# refuses the mismatch.  Measured evidence: docs/general-knowledge.md.
echo "== toolchain alignment (code generator)"
for spec in "server.dll:original/Server/server.dll" \
            "Europa1400Gold_TL.exe:original/Europa1400Gold_TL.exe" \
            "Europa1400Gold.exe:original/Europa1400Gold.exe"; do
    tgt="${spec%%:*}"; bin="${spec#*:}"
    if [ ! -f "$bin" ]; then
        echo "$tgt: binary missing -- skipped"
        continue
    fi
    det=$(rebrew toolchain detect "$bin" --target "$tgt" --json 2>&1)
    line=$(echo "$det" | python3 -c '
import json, sys
try:
    d = json.load(sys.stdin)
except Exception:
    print("ERR"); raise SystemExit
print("%s|%s|%s" % (d.get("codegen") or "-", d.get("aligned"), (d.get("explanation") or "")[:120]))
' 2>/dev/null)
    if [ "$line" = "ERR" ] || [ -z "$line" ]; then
        echo "REGRESSION: toolchain detect failed for $tgt"
        echo "$det" | head -20
        rc=1
        continue
    fi
    codegen="${line%%|*}"; rest="${line#*|}"; aligned="${rest%%|*}"; why="${rest#*|}"
    echo "$tgt: code generator=$codegen aligned=$aligned"
    if [ "$codegen" = "mixed" ]; then
        echo "REGRESSION: $tgt shows BOTH x87 code generators in game code;"
        echo "  the profile cannot be locked -- see docs/general-knowledge.md"
        rc=1
    elif [ "$aligned" != "True" ]; then
        echo "REGRESSION: $tgt profile does not match its code generator -- $why"
        rc=1
    fi
done

# Single-toolchain convergence: no source file may be pinned to a compiler of a
# DIFFERENT code-generator family than the target it is built into.  The server
# is a plain-VC6 binary, so an msvc-6.0-sp5-pp pin there would be a
# wrong-compiler coincidence, not the original build (round 1379f removed
# three such pins).  Pins of the same family (e.g. sp5 on an sp6 target) are
# fine: their output is byte-identical here.
echo "== per-file toolchain pins"
pin_dir=build/CMakeFiles/server_dll.dir
pins=$(grep -h -oE '/REBREW_TOOLCHAIN:[A-Za-z0-9._-]+' \
    "$pin_dir/flags.make" "$pin_dir/build.make" "$pin_dir/link.txt" | sort -u || true)
if [ -z "$pins" ]; then
    echo "no per-file toolchain pins"
else
    srv_codegen=$(rebrew toolchain detect original/Server/server.dll --target server.dll --json 2>/dev/null |
        python3 -c 'import json,sys
try: print(json.load(sys.stdin).get("codegen") or "")
except Exception: print("")')
    while read -r pin; do
        [ -z "$pin" ] && continue
        prof="${pin#/REBREW_TOOLCHAIN:}"
        case "$prof" in
            *-pp) pin_family="processor-pack" ;;
            *)    pin_family="plain" ;;
        esac
        if [ "$srv_codegen" = "plain" ] && [ "$pin_family" = "processor-pack" ]; then
            echo "REGRESSION: $prof pin on the server target, whose code generator is plain"
            rc=1
        else
            echo "$prof pin: family=$pin_family, server codegen=$srv_codegen -- ok"
        fi
    done <<< "$pins"
fi

# Objective structural criteria (round 1392): the delivered binary is checked
# against the reference with NO project tooling -- file size, every section
# VirtualSize, imports, exports, entry point, and that every differing byte is
# inside .text.  The residue count is a baseline, not a verdict: this check is
# red only when the DELIVERABLE regresses structurally (round 1391 proved the
# three header/layout defects that used to hold it red).
echo "== deliverable vs reference, byte for byte"
# The strongest assertion available, and until round 166 the gate never made it.
# Every other check here is sectional or structural -- `.data` size, `.reloc` size,
# the import list, exports, the residue -- and round 119 found `.reloc` sitting
# unexamined for dozens of rounds precisely because it was a region nobody printed.
# A whole-file comparison cannot have that failure: it either matches or it does
# not, and it subsumes every sectional check in this script.
if cmp -s original/Server/server.dll build/server.dll; then
    echo "raw link is byte-identical to the reference ($(stat -c %s build/server.dll) bytes)"
    echo "residue 0, baseline 0 held"
    echo "raw-link .data 0, baseline 0 held"
    echo "OBJECTIVE GAP: 0 bytes between the raw link and the reference"
    echo "  of which: 0 differing bytes in the common prefix, 0 bytes of size shortfall"
else
    echo "REGRESSION: the deliverable differs from the reference"
    cmp original/Server/server.dll build/server.dll | head -3
    echo "  size: reference $(stat -c %s original/Server/server.dll), built $(stat -c %s build/server.dll)"
    rc=1
fi

echo "== objective raw-link file identity"
if timeout 900 python3 scripts/verify_objective.py > .scratch/gate-objective.log 2>&1; then
    tail -2 .scratch/gate-objective.log
else
    echo "OBJECTIVE NOT MET: raw-link file identity failed --"
    cat .scratch/gate-objective.log
    rc=1
fi

# Regenerate docs/TODO.md's CURRENT STATE table from this run.  That table has gone
# stale twice in one session (rounds 209 and 238) while claiming to hold the gate's
# live numbers; correcting it by hand fixes an instance, generating it fixes the
# class.  Best-effort: a documentation write must never decide the gate's verdict.
if [ -n "${GATE_LOG:-}" ] && [ -f "$GATE_LOG" ]; then
    python3 scripts/update_state_table.py < "$GATE_LOG" 2>/dev/null || true
fi

[ "$rc" -eq 0 ] && echo "GATE: pass" || echo "GATE: FAIL"
exit "$rc"
