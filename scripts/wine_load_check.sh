#!/bin/bash
# wine_load_check.sh - load the deliverable under Wine and resolve its exports.
#
# The 100% objective lists "Wine load + exports (Init, Exit) resolve" as a done
# criterion, and round 934 found no script checked it: gate.sh covers lint,
# compile, verify and residue, but nothing ever loaded the built DLL.
#
# Why the copy-to-$TMPDIR dance: passing a deep path straight to Wine's Z: drive
# fails with error 193 (BAD_EXE_FORMAT) on this host even for the *reference*
# DLL, which is a harness artefact and not a property of the file.  Copying to a
# short temp path loads correctly, so the check copies.
#
# Usage: scripts/wine_load_check.sh [path/to/server.dll]
# Exit status: 0 when the DLL loads and both exports resolve, 1 otherwise.
set -uo pipefail
cd "$(dirname "$0")/.."

DLL=${1:-build/server.dll}
[ -f "$DLL" ] || { echo "no $DLL -- build first"; exit 1; }

command -v wine >/dev/null || { echo "wine not installed -- cannot check"; exit 1; }
command -v i686-w64-mingw32-gcc >/dev/null || { echo "no i686-w64-mingw32-gcc -- cannot build the loader"; exit 1; }
export WINEPREFIX=${WINEPREFIX:-$HOME/.wine-rebrew}
mkdir -p "$WINEPREFIX" || exit 1

tmp=$(mktemp -d); trap 'rm -rf "$tmp"' EXIT

cat > "$tmp/load.c" <<'C'
#include <windows.h>
#include <stdio.h>
int main(int argc, char** argv)
{
    int i, bad = 0;
    HMODULE h;
    if (argc < 3) { printf("usage: load <dll> <export>...\n"); return 2; }
    h = LoadLibraryA(argv[1]);
    if (!h) { printf("LOAD FAILED err=%lu\n", GetLastError()); return 1; }
    for (i = 2; i < argc; i++) {
        void* p = (void*) GetProcAddress(h, argv[i]);
        printf("  %-6s %s\n", argv[i], p ? "resolved" : "MISSING");
        if (!p) bad = 1;
    }
    return bad;
}
C

i686-w64-mingw32-gcc -o "$tmp/load.exe" "$tmp/load.c" 2>"$tmp/cc.log" \
    || { echo "loader build failed:"; tail -5 "$tmp/cc.log"; exit 1; }

cp "$DLL" "$tmp/target.dll"

# WINEDEBUG=-all silences Wine's noise; the loader's own output is what is read.
out=$(WINEDEBUG=-all wine "$tmp/load.exe" "Z:$tmp/target.dll" Init Exit 2>/dev/null)
rc=$?
echo "$out"

# The failure test is on the *program's* exit code and its words, not on a grep
# for absence: an empty output (Wine unable to start at all) must fail the check,
# which is the round-924 "a check that only prints is not a check" trap.
if [ $rc -ne 0 ] || [ -z "$out" ]; then
    echo "wine load check FAILED (rc=$rc)"
    exit 1
fi
echo "$out" | grep -q "resolved" || { echo "no export resolved"; exit 1; }
echo "$out" | grep -q "MISSING"  && { echo "an export is MISSING"; exit 1; }
echo "wine load + exports OK"
exit 0
