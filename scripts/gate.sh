#!/bin/bash
# gate.sh - the checks a change must pass before it is committed.
#
#   rebrew lint           annotation and corpus consistency
#   cmake --build         builds the raw server.dll with stock libraries
#   rebrew verify --full  byte comparison plus linked EXACT from the raw DLL
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
BASELINE=${BASELINE:-261}
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
# Round 907: this check printed lint's output but never tested it, so it could
# not fail the gate.  Proven inert: a deliberately broken FUNCTION identity
# header produced "1 warnings" here and the gate still reported pass on every
# other axis.  The objective is explicit that "zero warnings is the only
# acceptable state", so the count is now read and enforced.  Lint exits 0 even
# with warnings, so the exit code alone is not enough -- parse the summary.
lint_out=$(rebrew lint 2>&1 | tail -1)
echo "$lint_out"
lint_bad=$(echo "$lint_out" | sed -n 's/.*: [0-9]* passed, \([0-9]*\) errors, \([0-9]*\) warnings.*/\1 \2/p')
if [ -z "$lint_bad" ]; then
    echo "could not read the lint summary"
    rc=1
else
    lint_errs=${lint_bad% *}
    lint_warns=${lint_bad#* }
    if [ "$lint_errs" -ne 0 ] || [ "$lint_warns" -ne 0 ]; then
        echo "REGRESSION: lint $lint_errs errors, $lint_warns warnings (both must be 0)"
        rc=1
    else
        echo "lint clean: 0 errors, 0 warnings"
    fi
fi

echo "== build raw server.dll"
# Delete the output so this run must link it; check the build exit status too.
rm -f build/server.dll
build_rc=0
cmake --build build -j8 > .scratch/gate-build.log 2>&1 || build_rc=$?
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
# The rebrew checkout is editable, so the venv imports whatever commit it is on --
# and something outside this project moved it off `main` mid-session (round 247).
# The symptom was NOT "wrong commit": it was `rebrew build residue` dying with
# `ImportError: cannot import name 'map_coverage'`, the deliverable silently not being
# rebuilt, and six downstream rows failing for one missing symbol.  Check the symbols
# the project's own scripts import, by name, before anything depends on them.
echo "== rebrew checkout"
reb_py="${REBREW_PY:-.venv/bin/python}"
if reb_head=$(git -C /home/maci/Desktop/Projects/relumea/rebrew rev-parse --short HEAD 2>/dev/null); then
    echo "rebrew HEAD: $reb_head"
    reb_dirty=$(git -C /home/maci/Desktop/Projects/relumea/rebrew status --porcelain 2>/dev/null | wc -l)
    if [ "$reb_dirty" -gt 0 ]; then
        echo "  ($reb_dirty uncommitted file(s) in the checkout)"
        # A patch of those edits lives here so a `git checkout` cannot erase the
        # work a second time.  Verified to apply to a clean tree in round 250.
        if [ -s .scratch/rebrew-session-fixes.patch ]; then
            echo "  recovery patch: .scratch/rebrew-session-fixes.patch"
        fi
    fi
fi
sym_out=$("$reb_py" - <<'PYEOF' 2>&1
import sys
sys.path.insert(0, "/home/maci/Desktop/Projects/relumea/rebrew/src")
need = [
    ("rebrew.postlink", "binary_info_from_bytes"),
    ("rebrew.postlink", "map_coverage"),
    ("rebrew.postlink", "FIXERS"),
    ("rebrew.binary_loader", "decode_binary_name"),
]
missing = []
for mod, name in need:
    try:
        m = __import__(mod, fromlist=[name])
        getattr(m, name)
    except Exception as exc:
        missing.append("%s.%s (%s)" % (mod, name, type(exc).__name__))
print("MISSING " + ", ".join(missing) if missing else "OK")
PYEOF
)
case "$sym_out" in
    "OK") echo "required rebrew symbols import" ;;
    *) echo "REGRESSION: the editable rebrew checkout is unusable -- $sym_out"
       echo "  The project does NOT build against this checkout.  Check"
       echo "  \`git -C /home/maci/Desktop/Projects/relumea/rebrew rev-parse HEAD\`:"
       echo "  a moved HEAD is the cause, not a regression in this tree."
       rc=1 ;;
esac

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

echo "== rebrew verify --full --text --raw-link"
if ! out=$(rebrew verify --full --text --raw-link --built build/server.dll 2>&1); then
    echo "$out"
    echo "REGRESSION: function verification failed"
    rc=1
fi
echo "$out" | grep -E "Verification:" || true
# An annotation SHORTER than the binary's function passes as EXACT/RELOC on a
# prefix, so it never shows up as a failure -- rebrew computes the divergence and
# puts it in --json, and until round 189 printed nothing.  Surface it here: it is
# the measure of what is not yet reversed.  Reported, not failed: the
# count is large today and a gate that fails on it would say nothing new.
short_line=$(echo "$out" | grep -E "SHORTER than the binary" | head -1)
if [ -n "$short_line" ]; then
    echo "  ${short_line#*warning: }"
fi
worst_line=$(echo "$out" | grep -E "^  worst:" | head -1)
[ -n "$worst_line" ] && echo "  ${worst_line#*worst: }"
# ...and how many of them are discovery merges rather than truncated code,
# because the two need opposite responses and only one is reversing work.
merge_line=$(echo "$out" | grep -oE "[0-9]+ of them open with a new function" | head -1)
[ -n "$merge_line" ] && echo "  ${merge_line} -- INVENTORY MERGES (the annotation is right; the inventory spans several functions)"
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

echo "== raw-link data verification"
if rebrew verify --data --built build/server.dll > .scratch/gate-data.log 2>&1; then
    tail -5 .scratch/gate-data.log
else
    cat .scratch/gate-data.log
    rc=1
fi

# Compare the imports of the raw CMake output, including their order.
echo "== import table"
if [ -f build/server.dll ]; then
    IMP=$("${REBREW_PY:-python3}" - <<'PYEOF'
import struct, sys
def imports(p):
    d = open(p, 'rb').read()
    pe = struct.unpack_from('<I', d, 0x3c)[0]
    n = struct.unpack_from('<H', d, pe + 6)[0]
    hs = struct.unpack_from('<H', d, pe + 20)[0]
    secs = []
    for i in range(n):
        o = pe + 24 + hs + i * 40
        vs, va, raw, ptr = struct.unpack_from('<IIII', d, o + 8)
        secs.append((va, vs, ptr, raw))
    def r2f(rva):
        for va, vs, ptr, raw in secs:
            if va <= rva < va + max(vs, raw):
                return ptr + (rva - va)
    opt = pe + 24
    irva, _ = struct.unpack_from('<II', d, opt + 96 + 8)
    k, out = irva, []
    while True:
        f = r2f(k)
        oft, ts, fc, nm, ft = struct.unpack_from('<IIIII', d, f)
        if not nm:
            break
        dll = d[r2f(nm):d.find(b'\0', r2f(nm))].decode()
        j, c = r2f(oft), 0
        while True:
            v = struct.unpack_from('<I', d, j + c * 4)[0]
            if v == 0:
                break
            out.append(dll + '!' + ('ord%d' % (v & 0xffff) if v & 0x80000000
                                    else d[r2f(v) + 2:d.find(b'\0', r2f(v) + 2)].decode()))
            c += 1
        k += 20
    return out
a = imports('original/Server/server.dll')
b = imports('build/server.dll')
if a == b:
    print("OK %d" % len(b))
else:
    print("DIFF ref=%d bld=%d" % (len(a), len(b)))
    for x, y in zip(a, b):
        if x != y:
            print("  first: ref %s bld %s" % (x, y))
            break
PYEOF
)
    case "$IMP" in
        "OK "*) echo "raw link imports match the reference (${IMP#OK })" ;;
        *) echo "REGRESSION: raw-link import table differs -- $IMP"; rc=1 ;;
    esac

else
    echo "imports not measured (build/server.dll missing)"
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
pins=$(grep -oE '/REBREW_TOOLCHAIN:[A-Za-z0-9._-]+' CMakeLists.txt | sort -u || true)
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
