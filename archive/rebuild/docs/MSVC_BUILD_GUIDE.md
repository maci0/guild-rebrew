# MSVC Toolchain Build Guide

## Overview

This guide describes how to rebuild the server.dll using the Microsoft Visual C++ 6.0 toolchain via Wine.

## Tools Required

### Host Tools (Linux)
- NASM 3.01+ (Netwide Assembler)
- objconv 2.56+ (Object file converter)
- Wine 11.2+ (Windows compatibility layer)
- radare2 5.9.8+ (Reverse engineering framework)

### MSVC6 Tools (via Wine)
- LINK.EXE (MSVC6 Linker v6.00)
- LIB.EXE (Library Manager)
- DUMPBIN.EXE (Binary dumper)

## Build Workflow

### Phase 1: Disassembly

#### Method A: Using objconv (Recommended)

Extract and disassemble each function to NASM format:

```bash
# Extract a function from the .text section
# Init function at RVA 0x9320, size 0x30 (48 bytes)
# In text_raw.bin at offset 0x9320 - 0x1000 = 0x8320
dd if=rebuild/sections/text_raw.bin of=rebuild/asm/init_raw.bin bs=1 skip=37664 count=48 2>/dev/null

# Disassemble to NASM format
objconv -fnasm rebuild/asm/init_raw.bin rebuild/asm/init_disasm.asm

# Clean up the output for reassembly
# (Manual step to convert to proper NASM syntax)
```

#### Method B: Using objdump + Manual Cleanup

```bash
# Disassemble with Intel syntax
objdump -d -M intel --start-address=0x10009320 --stop-address=0x10009350 \
    original/Server/server.dll > rebuild/asm/init_disasm.txt

# Manually convert to NASM syntax
```

### Phase 2: Assembly Source Creation

Create assembly files with proper NASM structure:

```nasm
; rebuild/asm/_init.asm
; Function: Init
; Export ordinal: 2

section .text
    global _Init

_Init:
    ; Byte-exact instructions
    db 0x8b, 0x4c, 0x24, 0x04           ; mov ecx, [esp+4]
    db 0x8d, 0x44, 0x24, 0x04           ; lea eax, [esp+4]
    ; ... rest of function
    db 0xc3                             ; ret
```

### Phase 3: NASM Assembly

```bash
# Assemble all functions
for asm_file in rebuild/asm/*.asm; do
    obj_name=$(basename "$asm_file" .asm).obj
    nasm -f win32 -O0 -o "rebuild/obj/$obj_name" "$asm_file"
done
```

**NASM Options:**
- `-f win32` - Output Microsoft COFF format (32-bit)
- `-O0` - Disable optimizations (preserve exact encoding)
- `-o file` - Output filename

### Phase 4: MSVC Linking

#### Simple Link (All Objects)

```bash
# Set up Wine environment
export WINEDEBUG=-all

# Convert paths
OBJ_FILES=$(find rebuild/obj -name '*.obj' -exec winepath -w {} \; | tr '\n' ' ')
REBUILD_WIN=$(winepath -w rebuild)

echo "Object files: $OBJ_FILES"

# Run MSVC6 LINK.EXE
wine tools/MSVC600/VC98/Bin/LINK.EXE \
    /DLL \
    /OUT:"$REBUILD_WIN\\Server\\server.dll" \
    /BASE:0x10000000 \
    /ENTRY:DllMain \
    /MACHINE:IX86 \
    /ALIGN:4096 \
    /FILEALIGN:4096 \
    /RELEASE \
    /INCREMENTAL:NO \
    /DEF:"$REBUILD_WIN\\server.def" \
    $OBJ_FILES \
    kernel32.lib \
    user32.lib \
    ws2_32.lib \
    winmm.lib
```

#### Linker Options Reference

| Option | Description |
|--------|-------------|
| `/DLL` | Build DLL (not EXE) |
| `/OUT:file` | Output filename |
| `/BASE:addr` | Preferred load address |
| `/ENTRY:symbol` | Entry point function |
| `/MACHINE:IX86` | Target x86 architecture |
| `/ALIGN:n` | Section alignment in memory |
| `/FILEALIGN:n` | Section alignment in file |
| `/RELEASE` | Set checksum in PE header |
| `/INCREMENTAL:NO` | Disable incremental linking |
| `/DEF:file` | Module definition file |
| `/MAP` | Generate map file |
| `/IMPLIB:file` | Generate import library |

### Phase 5: Verification

```bash
# Checksum comparison
echo "Original:"
md5sum original/Server/server.dll
sha256sum original/Server/server.dll

echo ""
echo "Rebuilt:"
md5sum rebuild/Server/server.dll
sha256sum rebuild/Server/server.dll

# Binary comparison
cmp -l original/Server/server.dll rebuild/Server/server.dll | head -20
```

## Section-Based Approach

For exact reproduction, the simplest approach is:

1. **Extract sections** using dd/objcopy
2. **Keep sections as binary blobs** (don't disassemble)
3. **Create COFF object files** containing raw sections
4. **Link with proper section ordering**

### Creating COFF Objects from Raw Sections

```bash
# Use objcopy to convert binary to COFF
cd rebuild/sections

# .text section
objcopy -I binary \
    -O pe-i386 \
    -B i386 \
    --rename-section .data=.text \
    --change-section-address .data=0x10001000 \
text_raw.bin ../obj/text_section.obj

# Repeat for other sections...
```

### Alternative: Use NASM INCBIN

```nasm
; rebuild/asm/sections.asm
section .text align=4096
incbin "rebuild/sections/text_raw.bin"

section .rdata align=4096
incbin "rebuild/sections/rdata_raw.bin"

section .data align=4096
incbin "rebuild/sections/data_raw.bin"
```

Then assemble and link:

```bash
nasm -f win32 -o rebuild/obj/sections.obj rebuild/asm/sections.asm

wine tools/MSVC600/VC98/Bin/LINK.EXE \
    /DLL \
    /OUT:rebuild/Server/server.dll \
    rebuild/obj/sections.obj \
    /BASE:0x10000000 \
    /ENTRY:DllMain
```

## Troubleshooting

### Issue: Wine can't find MSVC tools

**Solution:** Use full paths or set up Wine environment

```bash
export WINEPREFIX="$HOME/.wine_msvc6"
winecfg  # Configure Windows version to Windows XP
```

### Issue: LINK.EXE reports "cannot find library"

**Solution:** Set LIB environment variable

```bash
export LIB="Z:\\path\\to\\MSVC600\\VC98\\Lib"
# Or use /LIBPATH option
wine LINK.EXE /LIBPATH:"Z:\\path\\to\\libs" ...
```

### Issue: Object format incompatible

**Solution:** Ensure NASM outputs win32 format, not coff or elf

```bash
nasm -f win32 ...  # Correct
nasm -f coff ...   # Wrong format for MSVC
nasm -f elf32 ...  # Wrong format for MSVC
```

### Issue: Checksum doesn't match

**Solution:** Verify:
1. All sections byte-identical
2. Same base address
3. Same alignment
4. Same entry point
5. Same exports
6. No debug info differences

Use cmp to find differences:
```bash
cmp -l original.dll rebuilt.dll
```

## Complete Build Script

```bash
#!/bin/bash
set -e

# Configuration
MSVC_ROOT="tools/MSVC600/VC98"
REBUILD_DIR="rebuild"
ORIGINAL_DLL="original/Server/server.dll"

echo "=== DLL Rebuild Script ==="

# Step 1: Extract sections (if not already done)
if [ ! -f "$REBUILD_DIR/sections/text_raw.bin" ]; then
    echo "Extracting sections..."
    python3 rebuild/tools/extract_sections.py "$ORIGINAL_DLL" "$REBUILD_DIR/sections"
fi

# Step 2: Create assembly files (one-time manual process)
# This step is manual - create .asm files for each function

echo ""
echo "=== Assembling with NASM ==="
mkdir -p "$REBUILD_DIR/obj"
for asm in "$REBUILD_DIR/asm/"*.asm; do
    if [ -f "$asm" ]; then
        obj_name=$(basename "$asm" .asm).obj
        echo "Assembling: $asm -> $obj_name"
        nasm -f win32 -O0 -o "$REBUILD_DIR/obj/$obj_name" "$asm"
    fi
done

echo ""
echo "=== Linking with MSVC6 ==="
OBJ_LIST=$(find "$REBUILD_DIR/obj" -name '*.obj' -exec winepath -w {} \; | tr '\n' ' ')
REBUILD_WIN=$(winepath -w "$REBUILD_DIR")

wine "$MSVC_ROOT/Bin/LINK.EXE" \
    /DLL \
    /OUT:"$REBUILD_WIN\\Server\\server.dll" \
    /BASE:0x10000000 \
    /ENTRY:DllMain \
    /MACHINE:IX86 \
    /ALIGN:4096 \
    /FILEALIGN:4096 \
    /RELEASE \
    /INCREMENTAL:NO \
    /DEF:"$REBUILD_WIN\\server.def" \
    $OBJ_LIST

echo ""
echo "=== Verification ==="
md5sum "$ORIGINAL_DLL" "$REBUILD_DIR/Server/server.dll"
sha256sum "$ORIGINAL_DLL" "$REBUILD_DIR/Server/server.dll"

echo ""
echo "Build complete!"
```

## References

- [MSVC6 LINK Options](https://docs.microsoft.com/en-us/cpp/build/reference/linker-options)
- [NASM Manual - win32 Format](https://www.nasm.us/doc/nasmdoc7.html#section-7.9)
- [Wine User Guide](https://www.winehq.org/docs/en/wineusr-guide.html)
