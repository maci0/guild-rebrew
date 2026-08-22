#!/bin/bash
# Shared helpers for the MSVC 6.0 docker wrapper scripts (CMake toolchain).
#
# The MSVC 6.0 command-line tools (CL.EXE / LINK.EXE / LIB.EXE) run inside
# the rebrew docker image rebrew/msvc:6.0-win32 (wine inside the image);
# the host never calls them directly.  The project root is same-path mounted
# into the container, so absolute host paths in the arguments (sources,
# /I dirs, build outputs) resolve identically inside the container, and
# wine's Z: drive maps them the same way the old host-wine wrapper did.
set -euo pipefail

_MSVC_COMMON_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
MSVC_PROJECT_ROOT="$(cd "$_MSVC_COMMON_DIR/.." && pwd)"
MSVC_IMAGE="rebrew/msvc:6.0-win32"
MSVC_TOOL_ROOT="/opt/msvc6.0/VC98/Bin"
MSVC_WINEPREFIX="${REBREW_WINEPREFIX:-$HOME/.cache/rebrew-msvc6-wineprefix}"

# Windows-style path for wine inside the container (Z: = container root; the
# project root is same-path mounted, so Z:\<abs> resolves to the host path).
msvc_to_w() {
    local p="$1"
    if [[ "$p" == /* ]]; then echo "Z:${p//\//\\}"; else echo "$p"; fi
}

# Initialize the shared wineprefix exactly once.  A fresh prefix races under
# a parallel build (8 concurrent wine processes creating it → most fail), so
# the first invocation runs `wineboot` under a flock and everyone else reuses
# the result.  Marker: .update-timestamp (modern wine has no system.reg).
msvc_ensure_wineprefix() {
    if [[ -f "$MSVC_WINEPREFIX/.update-timestamp" ]]; then return 0; fi
    mkdir -p "$MSVC_WINEPREFIX"
    (
        flock -x 9
        if [[ ! -f "$MSVC_WINEPREFIX/.update-timestamp" ]]; then
            docker run --rm \
                --user "$(id -u):$(id -g)" \
                -e WINEPREFIX="$MSVC_WINEPREFIX" \
                -v "$MSVC_WINEPREFIX:$MSVC_WINEPREFIX" \
                --entrypoint /usr/bin/wine \
                "$MSVC_IMAGE" wineboot -u >/dev/null 2>&1 || true
        fi
    ) 9>"$MSVC_WINEPREFIX/.init.lock"
}

# Run an MSVC tool (CL.EXE / LINK.EXE / LIB.EXE) with the given args through
# the docker image.  Strips CR from wine's output (CMake parses it).
#
# Runs under an exclusive lock on the wineprefix: concurrent wine processes
# on ONE prefix are not safe — each docker run has its own wineserver, and
# parallel wineservers updating the same prefix corrupt it (CL.EXE then dies
# with C1900 "Il mismatch" or C1083 on its transient a000XX intermediate
# files).  Serializing the runs makes the build deterministic; the warm
# prefix keeps each compile ~0.6s.
msvc_docker_run() {
    local tool="$1"
    shift
    msvc_ensure_wineprefix
    (
        flock -x 8
        docker run --rm \
            --user "$(id -u):$(id -g)" \
            -e WINEPREFIX="$MSVC_WINEPREFIX" \
            -e XDG_CACHE_HOME="$MSVC_WINEPREFIX/xdg-cache" \
            -e "LIB=Z:${MSVC_PROJECT_ROOT//\//\\}\\tools\\MSVC600\\VC98\\Lib" \
            -v "$MSVC_PROJECT_ROOT:$MSVC_PROJECT_ROOT" \
            -v "$MSVC_WINEPREFIX:$MSVC_WINEPREFIX" \
            -w "$PWD" \
            --entrypoint /usr/bin/wine \
            "$MSVC_IMAGE" "$MSVC_TOOL_ROOT/$tool" "$@" 2>&1 | tr -d '\r'
        exit "${PIPESTATUS[0]}"
    ) 8>"$MSVC_WINEPREFIX/.run.lock"
}
