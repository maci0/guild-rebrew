#!/bin/bash
# Run the GA to match entry0 (_DllMainCRTStartup@12).
# Usage: cd challenge && bash run.sh [mode]
#   mode: ga (default), obj, sweep, diff
set -e

REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
TOOLS="$REPO_ROOT/tools/MSVC600/VC98"
CHALLENGE_DIR="$(cd "$(dirname "$0")" && pwd)"

CL="wine $TOOLS/Bin/CL.EXE"
LINK="wine $TOOLS/Bin/LINK.EXE"
INC="$TOOLS/Include"
LIB="$TOOLS/Lib"
CFLAGS="/nologo /c /O1 /Oy- /MT /Gd"
LDFLAGS="/nologo /SUBSYSTEM:CONSOLE"
SYMBOL="_DllMainCRTStartup@12"
TARGET_BIN="$CHALLENGE_DIR/target/_DllMainCRTStartup@12.bin"

MODE="${1:-ga}"

case "$MODE" in
  obj)
    # OBJ-level comparison (no linking, ~2x faster)
    python3 "$REPO_ROOT/matcher.py" \
        --cl "$CL" --inc "$INC" \
        --cflags "$CFLAGS" \
        --compare-obj \
        --target-bin "$TARGET_BIN" \
        --symbol "$SYMBOL" \
        --seed-c "$CHALLENGE_DIR/entry0.c" \
        --out-dir "$CHALLENGE_DIR/run_out" \
        --generations 200 --pop 64 --elite 12 \
        --stagnation-limit 20 --timeout-min 30 \
        --checkpoint-every 5 \
        --verbose -j 16
    ;;
  sweep)
    # Flag sweep only (find best compiler flags)
    python3 "$REPO_ROOT/matcher.py" \
        --cl "$CL" --inc "$INC" \
        --cflags "/nologo /c /MT" \
        --flag-sweep-only \
        --target-bin "$TARGET_BIN" \
        --symbol "$SYMBOL" \
        --seed-c "$CHALLENGE_DIR/entry0.c" \
        --out-dir "$CHALLENGE_DIR/run_out" \
        --verbose -j 16
    ;;
  diff)
    # Diff-only mode (compare seed against target)
    python3 "$REPO_ROOT/matcher.py" \
        --cl "$CL" --inc "$INC" \
        --cflags "$CFLAGS" \
        --diff-only "$CHALLENGE_DIR/entry0.c" \
        --target-bin "$TARGET_BIN" \
        --symbol "$SYMBOL" \
        --seed-c "$CHALLENGE_DIR/entry0.c" \
        --out-dir "$CHALLENGE_DIR/run_out"
    ;;
  ga|*)
    # Original GA mode (full build+link)
    python3 "$REPO_ROOT/matcher.py" \
        --cl "$CL" --link "$LINK" --inc "$INC" --lib "$LIB" \
        --cflags "$CFLAGS" --ldflags "$LDFLAGS" \
        --target-bin "$TARGET_BIN" \
        --symbol "$SYMBOL" \
        --seed-c "$CHALLENGE_DIR/entry0.c" \
        --extra-sources "$CHALLENGE_DIR/stubs.c" "$CHALLENGE_DIR/main.c" \
        --out-dir "$CHALLENGE_DIR/run_out" \
        --generations 200 --pop 64 --elite 12 \
        --stagnation-limit 20 --timeout-min 30 \
        --checkpoint-every 5 --diff \
        --verbose
    ;;
esac
