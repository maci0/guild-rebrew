#!/bin/bash
# gate.sh — the checks a change must pass before it is committed.
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
#   toolchain alignment   each target's configured compiler profile matches the
#                         code generator actually in its binary (Processor Pack
#                         vs plain, read from game-code x87 compares)
#
# Usage: scripts/gate.sh
# Exit status: 0 when all pass, 1 otherwise.

set -uo pipefail
cd "$(cd "$(dirname "$0")/.." && pwd)"
mkdir -p .scratch

# `rebrew verify` counts game EXACT + RELOC as passed (library-attributed rows are
# reported separately); PROVEN is not a byte match
# and fails like any other difference.
BASELINE=${BASELINE:-261}
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
RESIDUE_BASELINE=${RESIDUE_BASELINE:-4}
# Raw-link .data divergence baseline (16,415: CrashDump blob split, split_link sizes its
# tail blob from the map).  The goal is a build that is
# byte-identical WITHOUT postlink, but postlink blits .data wholesale from the
# layout package, so the shipped file shows `.data differing 0x0` no matter what
# the link produced -- and this gate, guarding .text alone, could not see .data
# move at all.  Three rounds of data work were invisible to it.  Guard the raw
# link's own .data so progress there is measured and regressions there caught.
# 15,787: server.c block 0x1002956c..0x10029ac0 defined in reference order.
# 7,807: aemter tables, alchemy tables, command speed pair and dispatch table.
# 5,309: command, loadsave and lobby strings as literals in first-use order.
# 2,920: plant tables, spiel.c named block (spiel_data.c) and spiel literals.
# 2,370: fold literals in .data$zz, after the library .data instead of inside it.
# 2,012: library string literals placed in .rdata by split_blob, not folded.
# 1,253: the tail blob held the reference bytes up to where .data$zz starts.
# 0: library .data through ___lc_time_c is linked from objects. The gap blob
# starts at 0xd30c, past the historical tail 0xd274, and [0, 0xd30c) matches
# without that blob covering it.
# Raised from 0 to 13 in round 182, with the user's agreement, to bank the
# base-relative pool placement (scripts/emit_base_relative.py).  That change moves
# pool symbols to their reference addresses, and the linker rewrites the 13 `.data`
# words that are relocation targets naming them -- all 13 are relocation targets in
# the reference (round 180), so the 13 bytes are `.data` agreeing with the improved
# placement, not corruption of it.  Before: gap 41,619, .data 0.  After: gap 39,381,
# .data 13.  The trade was put to the user explicitly rather than assumed.
DATA_BASELINE=${DATA_BASELINE:-0}
# The raw-link gap, reported every run as OBJECTIVE GAP.  Round 122 described this
# as added with the baseline line; it was not -- the only references were
# `${OBJECTIVE_BASELINE:-999999999}` at the comparison, so the "above the baseline"
# note could never fire and the number it was meant to qualify went unqualified
# for ninety rounds.  Defined here in round 217, at the value the gate measures.
# It is a progress meter, not a pass/fail line: the objective is met when the two
# raws match, so crossing it prints a note rather than failing the run.
#
# Raised 41,619 -> 41,620 in round 216 when scripts/emit_thunks.py was fixed: its
# COFF symbols all carried Value 0, so the linker could place only one of the seven
# socket stubs.  Giving each its real offset put all seven at the reference's
# spacing and moved the gap by ONE byte, because the thunk bytes still name our
# IAT slots rather than the reference's.  A 1-byte regression from a correctness
# fix is recorded, not hidden.
# Lowered 41,620 -> 41,565 in round 225, the first genuine improvement: the
# WS2_32 IAT slot order now matches the reference exactly, which fixes `.rdata`
# (1,268 -> 1,238 differing) and `.text` (4,419 -> 4,395) with it.  See
# src/crt_region/crt_imports.c for how the /include order was derived.
OBJECTIVE_BASELINE=${OBJECTIVE_BASELINE:-41565}
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

echo "== build (compile errors only)"
# The exit status, not a string match.  Round 183: this step grepped for
# `error C<n>` / `error LNK` and so reported "compile/link errors: 0" for a build
# that had actually FAILED -- rebrew postlink's message is `error: postlink
# failed: ...`, which matches neither pattern, and the failure DELETES
# build/server.dll.  The later residue step then recreated the deliverable from
# the reference, so the gate went green with the build broken and nothing naming
# it.  A build step that does not check its own exit status is not a check.
# Delete the deliverable first so this step must PRODUCE it.  Without that the
# check is state-dependent and therefore meaningless: the failing link deletes
# build/server.dll, the residue step later recreates it from the reference, and the
# NEXT run finds the target up to date, never invokes postlink, and reports a clean
# exit.  Measured three runs in a row: FAIL, pass, pass -- on an unchanged tree.
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
    echo "  A non-zero exit with zero 'error C/LNK' lines is usually rebrew postlink"
    echo "  refusing the build; its message reads 'error: postlink failed: ...'."
    rc=1
fi
# rebrew postlink prints how much of the layout map validates, and that ratio is
# the objective's own progress meter for "produced by the toolchain" -- the floor
# is 90% and it is unreachable while `.text` is not byte-identical.  It used to
# appear only inside the failure blob above, where it reads as part of an error
# rather than as a number to move.  Extracted and named (round 234).
cov=$(grep -oE "only [0-9]+/[0-9]+ layout-map entries validate \([0-9.]+%" \
      .scratch/gate-build.log 2>/dev/null | head -1)
if [ -n "$cov" ]; then
    echo "postlink layout-map coverage: ${cov#only }"
    echo "  (the floor is 90%; it is code, not placement -- see OBJECTIVE GAP)"
fi

# The rebrew checkout is editable, so the venv imports whatever commit it is on --
# and something outside this project moved it off `main` mid-session (round 247).
# The symptom was NOT "wrong commit": it was `scripts/postlink_residual.py` dying with
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
missing_images=""
for img in rebrew/msvc:6.0-sp5-win32; do
    docker image inspect "$img" >/dev/null 2>&1 || missing_images="$missing_images $img"
done
if [ -n "$missing_images" ]; then
    echo "REGRESSION: toolchain image(s) missing:$missing_images"
    for img in $missing_images; do
        echo "  rebuild: rebrew toolchain build $(echo "$img" | sed 's#rebrew/msvc:##; s#-win32##')"
    done
    echo "  Every function will report COMPILE_ERROR until then; that is not a"
    echo "  source break.  Not running verify, because its result would be noise."
    rc=1
    echo "GATE: FAIL"
    exit "$rc"
fi
echo "toolchain images present"

echo "== rebrew verify --full"
out=$(rebrew verify --full 2>&1)
echo "$out" | grep -E "Verification:" || true
# An annotation SHORTER than the binary's function passes as EXACT/RELOC on a
# prefix, so it never shows up as a failure -- rebrew computes the divergence and
# puts it in --json, and until round 189 printed nothing.  Surface it here: it is
# the measure of what is not yet reversed, and it is what keeps rebrew postlink
# from accepting the CMake build (rounds 183-188).  Reported, not failed: the
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
        if grep -q "splicing reference .data" .scratch/gate-residue.log; then
            echo "REGRESSION: g_data_restore_gap is splicing reference .data into the link"
            rc=1
        fi
        if grep -q "before the historical .data tail" .scratch/gate-residue.log; then
            echo "REGRESSION: g_data_restore_gap starts before the historical .data tail 0xd274"
            echo "  The gap blob is copying reference .data the link did not emit."
            rc=1
        fi
    else
        echo "raw-link .data not measured (see .scratch/gate-residue.log)"
        rc=1
    fi

    # The pre-fixer table, ALL of it.  Until round 119 this gate printed .text
    # and .data by name and nothing else, so `.reloc` (0x8b64 differing, eight
    # times the .text residue every round was chasing) and `.rdata` had no line
    # in the report and read as "no difference".  A measurement that is not
    # printed is not zero.
    pre=$(echo "$full" | sed -n '/^raw link vs reference/,/^$/p' | grep -E '^  (\.|headers)')
    if [ -n "$pre" ]; then
        echo "raw link vs reference (pre-fixer, the whole picture):"
        echo "$pre"
        # The objective's own number.  Everything the fixers overwrite is
        # difference the toolchain did not close, so the honest distance from
        # "100% straight out of the toolchain" is the sum of these rows -- and
        # until round 121 this gate reported a VERDICT about the POSTLINKED
        # artefact, which postlink builds by copying the reference's .reloc and
        # splicing its .data.  A copied section cannot pass as a produced one,
        # so the number is printed on every run even while it is large.
        gap=$(echo "$pre" | sed -E 's/.*differing +0x([0-9a-f]+) .*/\1/' \
              | while read -r h; do printf '%d\n' "0x$h"; done | paste -sd+ | bc)
        echo "OBJECTIVE GAP: $gap bytes between the raw link and the reference"
        # That number is a SUM of two different things and the gate never said so.
        # Round 167 reconciled it exactly against a whole-file comparison:
        #   differing bytes in the common prefix + size shortfall = gap
        #   12,947                              + 28,672          = 41,619
        # The second term is the raw link's `.reloc` being 0xa000 against the
        # reference's 0x11000 -- fewer relocation entries, less FileAlignment
        # padding, a shorter file.  Reporting them apart matters because a change
        # that fixes bytes and a change that only changes a section's size are
        # different work, and one number hides which happened.
        common=$(cmp -l original/Server/server.dll build/split_poc.dll 2>/dev/null | wc -l)
        refsz=$(stat -c %s original/Server/server.dll)
        bldsz=$(stat -c %s build/split_poc.dll)
        short=$((refsz - bldsz)); [ "$short" -lt 0 ] && short=0
        echo "  of which: $common differing bytes in the common prefix, $short bytes of size shortfall"
        if [ "$((common + short))" -ne "${gap:-0}" ]; then
            echo "  NOTE: the two components do not sum to the gap ($((common + short)) vs ${gap:-0});"
            echo "  the per-section table and the whole-file comparison disagree -- investigate."
        fi
        # Round 126: that number counts differing BYTES and cannot tell a
        # produced byte from a coincidental one.  A build with absolute symbols
        # scored 39,061 against 41,619 -- better -- while shipping an image that
        # does not load, because forcing an address at link time removes the
        # relocation that makes it an address.  So the raw link is load-checked
        # here, beside the number, every run: a gap that improves while this
        # goes red is not progress.
        if bash scripts/wine_load_check.sh build/split_poc.dll > .scratch/gate-rawload.log 2>&1; then
            echo "  raw link loads: $(tail -1 .scratch/gate-rawload.log)"
        else
            echo "REGRESSION: the raw link does not load ($(tail -1 .scratch/gate-rawload.log))"
            echo "  A byte gap can shrink while the image stops working -- check"
            echo "  .reloc entries before believing any improvement in the line above."
            rc=1
        fi
        # `:-999999999` is what made this line dead for ninety rounds (round 217):
        # an unset variable meant "compare against infinity", so the note could
        # never fire and nothing said so.  `:?` aborts instead -- a gate whose
        # threshold has gone missing should stop, not go quiet.
        if [ "${gap:-0}" -gt "${OBJECTIVE_BASELINE:?OBJECTIVE_BASELINE must be defined}" ]; then
            echo "  (above the ${OBJECTIVE_BASELINE} baseline; the raws must match for the"
            echo "   objective to be met, so this line is the real progress meter)"
        fi
    else
        echo "REGRESSION: the pre-fixer section table is missing from the residue report"
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
echo "== relocation records (raw link vs reference)"
# A relocation record changes no byte of the file: it tells the loader to add the
# image base to the word at that RVA.  So a build missing hundreds of them is
# byte-identical in the very region they describe -- invisible to `cmp`, to the
# per-section table and to the residue report, which is all this gate had.  Round
# 169 measured 590 missing, 260 of them pointing into `.data`, a section reported
# as perfect.  This check compares the RECORDS.
if python3 scripts/reloc_set_check.py --built build/split_poc.dll \
       > .scratch/gate-relocset.log 2>&1; then
    tail -1 .scratch/gate-relocset.log
else
    echo "REGRESSION: relocation records changed --"
    cat .scratch/gate-relocset.log
    rc=1
fi

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
    # ...but build/server.dll is the DELIVERABLE, and rebrew postlink builds it
    # from the reference.  So the check above compares the reference with a copy
    # of the reference and can never fail -- the same tautology rebrew's own
    # `verify --data` warns about (round 170).  Round 210: measure the RAW LINK,
    # which is the artefact the import table is actually a property of.
    if [ -f build/split_poc.dll ]; then
        IMPRAW=$("${REBREW_PY:-python3}" - <<'PYEOF'
import struct
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
b = imports('build/split_poc.dll')
if a == b:
    print("OK %d" % len(b))
else:
    print("DIFF ref=%d raw=%d" % (len(a), len(b)))
    for i, (x, y) in enumerate(zip(a, b)):
        if x != y:
            print("  first at %d: ref %s raw %s" % (i, x, y))
            break
PYEOF
)
        case "$IMPRAW" in
            "OK 100") echo "raw link imports match the reference (100) -- not tautological" ;;
            *) echo "REGRESSION: raw-link import table differs -- $IMPRAW"; rc=1 ;;
        esac
    fi
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
    echo "deliverable is byte-identical to the reference ($(stat -c %s build/server.dll) bytes)"
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
