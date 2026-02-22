#!/bin/bash
# Run the sum_array example end-to-end.
# Usage: cd examples/sum_array && bash run.sh
set -e

REPO_ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
TOOLS="$REPO_ROOT/tools/MSVC600/VC98"
EXAMPLE_DIR="$(cd "$(dirname "$0")" && pwd)"

CL="wine $TOOLS/Bin/CL.EXE"
LINK="wine $TOOLS/Bin/LINK.EXE"
INC="$TOOLS/Include"
LIB="$TOOLS/Lib"
CFLAGS="/nologo /c /O2 /MT /Gd"
LDFLAGS="/nologo /SUBSYSTEM:CONSOLE"
SYMBOL="_sum"

# Step 1: Extract target bytes
python3 "$REPO_ROOT/extract_target.py" \
    --cl "$CL" --link "$LINK" --inc "$INC" --lib "$LIB" \
    --cflags "$CFLAGS" --ldflags "$LDFLAGS" \
    --source "$EXAMPLE_DIR/target.c" \
    --symbol "$SYMBOL" \
    --out-dir "$EXAMPLE_DIR/target"

# Step 2: Run the GA
python3 "$REPO_ROOT/matcher.py" \
    --cl "$CL" --link "$LINK" --inc "$INC" --lib "$LIB" \
    --cflags "$CFLAGS" --ldflags "$LDFLAGS" \
    --target-exe "$EXAMPLE_DIR/target/target.exe" \
    --target-map "$EXAMPLE_DIR/target/target.map" \
    --symbol "$SYMBOL" \
    --seed-c "$EXAMPLE_DIR/seed.c" \
    --out-dir "$EXAMPLE_DIR/run_out" \
    --generations 50 --pop 16 --elite 4 --timeout-min 5 \
    --verbose
