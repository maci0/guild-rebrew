# Native Toolchain Pipeline

## Overview

This document describes how to rebuild `original/Server/server.dll` using native tooling.

Project invariant: output must be bit-identical to the original. If bytes change, it's a failed build (we do not “fix up” checksums to make modified binaries look valid).

## Verified Approaches

### Approach 1: Pure NASM (Recommended)

**Result**: ✅ Produces identical checksum (MD5 match)

```bash

# Assemble with NASM
nasm -f bin -o rebuild/Server/server.dll rebuild/asm/server_native.asm

# Verify checksum match
md5sum rebuild/Server/server.dll original/Server/server.dll
# 43279c2f9e9fd4d7bbc3889fd02ea4ea (both files)
```

**How it works**:
- NASM outputs flat binary (`-f bin`)
- `incbin` directive includes raw section bytes at exact offsets
- PE headers are preserved from original
- No linker needed - direct byte output

### Approach 2: NASM + MSVC LINK (Experimental)

**Status**: ⚠️ Partial success - needs refinement

```bash
# Convert binary sections to COFF
objcopy -I binary -O pe-i386 -B i386 text_raw.bin text_coff.o

# Link with MSVC
wine tools/MSVC600/VC98/Bin/LINK.EXE \
    /DLL \
    /BASE:0x10000000 \
    /NOENTRY \
    text_coff.o rdata_coff.o data_coff.o reloc_coff.o
```

**Issues**:
- MSVC reorganizes sections
- Adds extra metadata
- File size differs (290816 vs 286720)
- Checksum doesn't match

## Complete Native Workflow

### Step 1: Extract Sections (one-time)

```bash
# Extract using dd for exact byte precision
dd if=original/Server/server.dll of=sections/header.bin bs=1 count=4096 skip=0
dd if=original/Server/server.dll of=sections/text_raw.bin bs=1 skip=4096 count=143360
dd if=original/Server/server.dll of=sections/rdata_raw.bin bs=1 skip=147456 count=12288
dd if=original/Server/server.dll of=sections/data_raw.bin bs=1 skip=159744 count=57344
dd if=original/Server/server.dll of=sections/reloc_raw.bin bs=1 skip=217088 count=69632
```

### Step 2: NASM Source

See `rebuild/asm/server_native.asm`.

### Step 3: Assemble

```bash
nasm -f bin -o rebuild/Server/server.dll rebuild/asm/server_native.asm
```

### Step 4: Verify

```bash

# Checksum
md5sum rebuild/Server/server.dll original/Server/server.dll


# Size
wc -c rebuild/Server/server.dll original/Server/server.dll


# Binary diff
cmp -l rebuild/Server/server.dll original/Server/server.dll
```

## Function-Level Work

For function byte-identical matching workflows, see:
- `rebuild/docs/FUNCTION_LEVEL_MATCH_WORKFLOW.md`
- `rebuild/docs/NASM_ENCODING_DIFFERENCES.md`

## Tool Comparison

| Tool | Purpose | Pros | Cons |
|------|---------|------|------|
| **NASM** | Assemble to binary | Exact byte control, no linker needed | Manual section management |
| **MSVC LINK** | Link COFF objects | Standard toolchain | Reorganizes sections, adds metadata |
| **objcopy** | Binary to COFF | Creates MSVC-compatible objects | Section alignment issues |
| **pefile** | Checksum correction | Automatic, accurate | Requires Python |

## File Structure for Native Build

```
rebuild/
├── asm/
│   ├── server_native.asm       # Main NASM source
│   ├── _init.asm               # Init function source
│   ├── _exit.asm               # Exit function source
│   └── [function].asm          # Other functions
├── sections/
│   ├── header.bin              # PE headers (4096 bytes)
│   ├── text_raw.bin            # Code section
│   ├── rdata_raw.bin           # Read-only data
│   ├── data_raw.bin            # Initialized data
│   └── reloc_raw.bin           # Relocations
├── obj/                        # COFF objects (if using MSVC)
├── Server/
│   └── server.dll              # Output
└── build_native.sh             # Build script
```

## Build Script Template

```bash
#!/bin/bash
# build_native.sh - Pure NASM build

set -e

INPUT_DIR="rebuild/sections"
OUTPUT="rebuild/Server/server_native.dll"
ASM_FILE="rebuild/asm/server_native.asm"

echo "=== Building DLL with NASM ==="

# Create NASM source
cat > "$ASM_FILE" << 'EOF'
BITS 32
incbin "rebuild/sections/header.bin"
incbin "rebuild/sections/text_raw.bin"
incbin "rebuild/sections/rdata_raw.bin"
incbin "rebuild/sections/data_raw.bin"
incbin "rebuild/sections/reloc_raw.bin"
EOF

# Assemble
nasm -f bin -o "$OUTPUT" "$ASM_FILE"

# Verify
echo ""
echo "=== Verification ==="
md5sum "$OUTPUT" original/Server/server.dll

echo ""
echo "Build complete: $OUTPUT"
```

## Verification Checklist

After building with native tools:

- [ ] File size matches (286,720 bytes)
- [ ] MD5 checksum matches (43279c2f9e9fd4d7bbc3889fd02ea4ea)
- [ ] SHA256 checksum matches
- [ ] Binary comparison shows no differences
- [ ] PE headers intact
- [ ] Sections at correct offsets
- [ ] Exports visible (dumpbin /exports)
- [ ] Imports visible (dumpbin /imports)

## Notes

- MSVC vs NASM encoding differences are common. When rebuilding functions in NASM, you may need explicit `db` bytes.
- For bit-identical output, prefer the canonical NASM flat binary build.

## Success Criteria

✅ **Native toolchain produces bit-identical DLL** when:
- All sections included at exact offsets
- PE headers preserved
- No modifications to code/data

⚠️ **Checksum differs** when:
- Any byte is modified
- Checksum not manually corrected

## References

- `rebuild/asm/server_native.asm` - Working example
- `rebuild/Server/server_nasm_native.dll` - Output (identical to original)
- `VERIFICATION_REPORT.md` - Detailed test results

---

**Last Updated**: February 14, 2026
**Status**: Pure NASM approach verified working
