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
RESIDUE_BASELINE=${RESIDUE_BASELINE:-8628}
# Raw-link .data divergence baseline (22,266 as of round 519).  The goal is a build that is
# byte-identical WITHOUT postlink, but postlink blits .data wholesale from the
# layout package, so the shipped file shows `.data differing 0x0` no matter what
# the link produced -- and this gate, guarding .text alone, could not see .data
# move at all.  Three rounds of data work were invisible to it.  Guard the raw
# link's own .data so progress there is measured and regressions there caught.
DATA_BASELINE=${DATA_BASELINE:-21481}
rc=0

# Build-tree integrity.  build/ is gitignored, so no other check here can see it:
# a hand-edited build.make leaves git status clean, lint clean, verify unchanged,
# and `cmake --build` still "succeeding" -- while every measurement taken from the
# tree describes a build no fresh clone reproduces.  Round 1051 hit this sweeping
# toolchain pins: 58% residue and a 290,816-byte deliverable vs 286,720 / 8628.
# The check lives in rebrew (round 1055 moved it there from a project script) so
# every rebrew project gets it; `rebrew build-check` exits 1 on drift.
echo "== build-tree integrity"
if [ -f build/CMakeFiles/server_dll.dir/flags.make ]; then
    if ! bc=$(rebrew build-check 2>&1); then
        echo "$bc"
        echo "REGRESSION: build.make has been hand-edited -- the tree no longer"
        echo "  describes a reproducible build.  Restore with:"
        echo "    rm -rf build && cmake -B build -S . \\"
        echo "      --toolchain cmake/toolchain-msvc-6.0-sp6-docker.cmake \\"
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
    # emit_defs fixed-point guard.  The definition cascade MUST iterate: emitting
    # __CRT_INIT@12 introduces a reference to _DllMain@12, so one pass leaves
    # symbols behind.  Round 1055 put the iteration's guard clause in the wrong
    # place and silently dedented the emit code OUT of the loop -- definitions
    # were then emitted once, .rdata grew 0x40, and postlink refused the build
    # with a message about /debug.  Every other check passed; only this one sees
    # it.  Two passes is the steady state (73 missing, then 0).
    epasses=$(grep -cE "^pass [0-9]+: " .scratch/gate-link.log || true)
    if [ "${epasses:-0}" -lt 2 ]; then
        echo "REGRESSION: split_link's definition cascade ran $epasses pass(es);"
        echo "  it must iterate (2 is the steady state).  A single pass means the"
        echo "  emit code has fallen out of emit_defs.py's fixed-point loop, which"
        echo "  silently grows .rdata and makes postlink refuse the build."
        rc=1
    fi
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

# Data extents that cross the next tracked symbol.  Added round 906: two real
# width defects (a 4-byte `size` on a byte-wide field) sat in the metadata while
# residue, verify and lint all stayed green, because an entry can be internally
# wrong while agreeing with every other TU.  The check needs no disassembly, so
# it costs a second and belongs here rather than in a periodic audit.
# See docs/measure-traps.md section 6.
echo "== data extents"
if [ -f src/rebrew-data.toml ]; then
    if EXT=$("${REBREW_PY:-.venv/bin/python}" scripts/data_extent_check.py 2>&1); then
        echo "$EXT" | head -1
    else
        echo "REGRESSION: metadata extent claims bytes another symbol owns:"
        echo "$EXT" | sed -n '/BUGS/,$p' | head -20
        rc=1
    fi
fi

# Import table against the reference.  Was a done-criterion with nothing
# enforcing it until round 881: an extra import means a library object came in
# the original did not have, a missing one means the opposite, and neither shows
# up in the residue.  The reference has exactly 100 over four descriptors.
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
        "OK 100") echo "imports match the reference (100)" ;;
        *) echo "REGRESSION: import table differs -- $IMP"; rc=1 ;;
    esac
else
    echo "imports not measured (build/server.dll missing)"
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
    lm=$(rebrew lib-match --lib references/dxsdk8/lib/d3dx8.lib --target Europa1400Gold_TL.exe --json 2>&1)
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
        echo "REGRESSION: rebrew lib-match d3dx8 failed on GOLDTL"
        echo "$lm" | head -40
        rc=1
    fi
else
    echo "d3dx8 lib not vendored -- skipped"
fi

[ "$rc" -eq 0 ] && echo "GATE: pass" || echo "GATE: FAIL"
exit "$rc"
