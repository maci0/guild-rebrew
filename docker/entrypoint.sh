#!/usr/bin/env bash
set -e

ACTION="${1:-verify}"

case "$ACTION" in
    verify)
        echo "=== Running verification pipeline ==="
        python3 tools/validate.py --verify
        ;;
    test)
        shift
        echo "=== Running test_func.py ==="
        python3 tools/test_func.py "$@"
        ;;
    diff)
        shift
        echo "=== Running matcher.py diff ==="
        python3 tools/matcher.py \
            --cl "wine tools/MSVC600/VC98/Bin/CL.EXE" \
            --inc "tools/MSVC600/VC98/Include" \
            --cflags "/nologo /c /O2 /MT /Gd" \
            --compare-obj \
            --diff-only "$@"
        ;;
    lint)
        echo "=== Running annotation linter ==="
        python3 tools/lint_annotations.py
        ;;
    stats)
        echo "=== Running next_work.py stats ==="
        python3 tools/next_work.py --stats
        ;;
    skeleton)
        shift
        echo "=== Generating skeleton ==="
        python3 tools/gen_skeleton.py "$@"
        ;;
    shell)
        exec /bin/bash
        ;;
    *)
        echo "Usage: docker run rebrew [verify|test|diff|lint|stats|skeleton|shell]"
        echo ""
        echo "  verify    - Compile all .c files and verify byte match against DLL"
        echo "  test      - Run test_func.py with given arguments"
        echo "  diff      - Run matcher.py diff-only with given arguments"
        echo "  lint      - Run annotation linter"
        echo "  stats     - Show RE progress statistics"
        echo "  skeleton  - Generate .c skeleton for a VA"
        echo "  shell     - Drop into bash shell"
        exit 1
        ;;
esac
