#!/bin/bash
# Build server.dll using MSVC6 via Wine
#
# Usage: ./build-win.sh [options]
#   -j, --jobs N    Number of parallel jobs (default: 8)
#   -c, --clean     Clean build directory first
#   -d, --debug     Build with debug configuration

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR"

# Defaults
JOBS=8
CLEAN=false
BUILD_TYPE=Release

# Parse arguments
while [[ $# -gt 0 ]]; do
    case "$1" in
        -j|--jobs)
            JOBS="$2"
            shift 2
            ;;
        -c|--clean)
            CLEAN=true
            shift
            ;;
        -d|--debug)
            BUILD_TYPE=Debug
            shift
            ;;
        -h|--help)
            echo "Usage: $0 [options]"
            echo "  -j, --jobs N    Number of parallel jobs (default: 8)"
            echo "  -c, --clean    Clean build directory first"
            echo "  -d, --debug    Build with debug configuration"
            exit 0
            ;;
        *)
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
done

# Clean if requested
if [[ "$CLEAN" == true ]]; then
    echo "Cleaning build directory..."
    rm -rf build
fi

# Create build directory if needed
mkdir -p build

# Configure with MSVC6 toolchain
echo "Configuring with MSVC6 toolchain..."
cmake -B build \
    --toolchain cmake/toolchain-msvc6-wine.cmake \
    -DCMAKE_BUILD_TYPE="$BUILD_TYPE"

# Build
echo "Building (jobs=$JOBS)..."
cmake --build build -j"$JOBS"

echo "Build complete: build/server.dll"
