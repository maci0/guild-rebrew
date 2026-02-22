#!/bin/bash
# Run a rebrew example by name.
# Usage: bash examples/run_example.sh simple_add
#        bash examples/run_example.sh max_func
#        bash examples/run_example.sh sum_array
set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
EXAMPLE_NAME="${1:?Usage: $0 <example_name> (simple_add|max_func|sum_array)}"
EXAMPLE_DIR="$SCRIPT_DIR/$EXAMPLE_NAME"

if [ ! -d "$EXAMPLE_DIR" ]; then
    echo "Error: example '$EXAMPLE_NAME' not found in $SCRIPT_DIR"
    echo "Available examples:"
    ls -d "$SCRIPT_DIR"/*/run.sh 2>/dev/null | while read f; do
        basename "$(dirname "$f")"
    done
    exit 1
fi

if [ ! -f "$EXAMPLE_DIR/run.sh" ]; then
    echo "Error: $EXAMPLE_DIR/run.sh not found"
    exit 1
fi

echo "=== Running example: $EXAMPLE_NAME ==="
cd "$EXAMPLE_DIR"
bash run.sh
