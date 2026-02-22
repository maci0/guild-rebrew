#!/bin/bash
# Build script using MSVC6 LINK.EXE via Wine

set -e

WINE="wine"
MSVC="tools/MSVC600/VC98/Bin"
REBUILD="rebuild"

echo "=== MSVC6 DLL Build Script ==="

# Convert paths for Wine
REBUILD_WIN=$(winepath -w "$REBUILD")
echo "Rebuild directory (Windows): $REBUILD_WIN"

# Create object list
OBJ_LIST=""
for obj in "$REBUILD"/obj/*.obj; do
    if [ -f "$obj" ]; then
        OBJ_WIN=$(winepath -w "$obj")
        OBJ_LIST="$OBJ_LIST $OBJ_WIN"
    fi
done

echo "Object files: $OBJ_LIST"

# Run linker
# Note: For now, we're not linking because we need all sections
# This is just to show the command structure

echo ""
echo "=== Linker Command ==="
echo "$WINE $MSVC/LINK.EXE \\"
echo "    /DLL \\"
echo "    /OUT:$REBUILD_WIN/Server/server.dll \\"
echo "    /BASE:0x10000000 \\"
echo "    /ENTRY:DllMain \\"
echo "    /MACHINE:IX86 \\"
echo "    /ALIGN:4096 \\"
echo "    /FILEALIGN:4096 \\"
echo "    /RELEASE \\"
echo "    /INCREMENTAL:NO \\"
echo "    /DEF:$REBUILD_WIN/server.def \\"
echo "    $OBJ_LIST"

