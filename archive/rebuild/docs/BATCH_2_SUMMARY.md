# Function Documentation Summary - Batch 2 (10 Functions)

## Overview

Documented 10 additional functions with both:
1. **Bit-identical NASM** (`_fcn_XXXX.asm`) - Uses `db` directives for exact byte match
2. **Readable NASM** (`fcn_XXXX_readable.asm`) - Actual instructions for reverse engineering

## Functions Documented

| # | Function | Address | Size | Description | Category |
|---|----------|---------|------|-------------|----------|
| 1 | fcn_10001130 | 0x10001130 | 179B | Network/socket initialization | Server |
| 2 | fcn_100011f0 | 0x100011f0 | 309B | CRC32 update function | zlib |
| 3 | fcn_10001330 | 0x10001330 | 505B | Deflate state initialization | zlib |
| 4 | fcn_100015b0 | 0x100015b0 | 685B | Deflate parameter processing | zlib |
| 5 | fcn_10001860 | 0x10001860 | 47B | Output byte write helper | zlib |
| 6 | fcn_10001890 | 0x10001890 | 114B | Flush pending output | zlib |
| 7 | fcn_10001910 | 0x10001910 | 170B | Deflate end/cleanup | zlib |
| 8 | fcn_10001bc0 | 0x10001bc0 | 290B | Slide hash window | zlib |
| 9 | fcn_10001cf0 | 0x10001cf0 | 113B | Read input data | zlib |
| 10 | fcn_100020a0 | 0x100020a0 | 367B | Longest match search | zlib |

## File Locations

### Assembly Sources

**Bit-identical versions** (for checksum verification):
- `rebuild/asm/_fcn_10001130.asm` through `_fcn_100020a0.asm`
- Extracted bytes as `db` directives
- Produces bit-identical output when assembled

**Readable versions** (for reverse engineering):
- `rebuild/asm/fcn_10001130_readable.asm` through `fcn_100020a0_readable.asm`
- Actual NASM instructions (`mov`, `push`, `call`, etc.)
- Functionally identical but may have minor encoding differences

### Documentation

- `rebuild/docs/functions/fcn_10001130.md` through `fcn_100020a0.md`
- Full analysis, C code equivalents, and cross-references

### New Documentation

- `rebuild/docs/NASM_ENCODING_DIFFERENCES.md`
  - Explains why readable NASM differs from original
  - Documents MOV instruction encoding differences
  - Provides solutions and recommendations

## NASM Encoding Issue

### The Problem

NASM and MSVC encode some instructions differently:

```
mov esi, eax
- NASM produces: 89 c6 (MOV r/m32, r32)
- MSVC produces: 8b f0 (MOV r32, r/m32)
```

Both execute identically but have different bytes.

### Impact

- **Functionality**: ✅ Identical
- **File size**: ✅ Same
- **Checksum**: ❌ Different

### Solutions Provided

1. **Use bit-identical versions** (`_fcn_XXXX.asm`) when checksum matters
2. **Use readable versions** (`fcn_XXXX_readable.asm`) for understanding/modifying code
3. **Both coexist** - you can switch between them as needed

## zlib Functions Identified

This batch confirmed extensive zlib deflate compression code:

### Core Deflate Functions
- `fcn_10001330` - deflate state initialization
- `fcn_100015b0` - deflate parameter processing
- `fcn_10001910` - deflate end/cleanup

### Compression Helpers
- `fcn_100011f0` - CRC32 calculation
- `fcn_10001860` - Output buffer management
- `fcn_10001890` - Flush output
- `fcn_10001bc0` - Slide hash window
- `fcn_10001cf0` - Read input
- `fcn_100020a0` - Longest match search

### Network Function
- `fcn_10001130` - Socket initialization (non-zlib)

## Verification Status

- ✅ All 10 bit-identical versions verified
- ✅ All readable versions assemble without errors
- ✅ Full DLL rebuild maintains checksum (with db versions)
- ✅ Documentation complete for all functions

## Total Progress

- **Total functions documented**: 18
- **Remaining**: ~82
- **Complete**: 18%

## Next Steps

Continue documenting functions. Recommend pattern:

1. Extract bytes with `dd`
2. Create bit-identical NASM with `db` directives
3. Create readable NASM with actual instructions
4. Write documentation with C equivalents
5. Update FUNCTION_LIST.md
6. Verify both versions assemble correctly

## Usage Recommendations

### For Bit-Identical Rebuild
```bash
# Use db versions
nasm -f bin -o rebuild/Server/server.dll rebuild/asm/server_native.asm
```

### For Reverse Engineering
```bash
# Use readable versions
nasm -f bin -o server_modified.dll asm/fcn_XXXX_readable.asm
# Inject and test behavior
```

### For Understanding
```bash
# Read documentation
cat rebuild/docs/functions/fcn_XXXX.md
# Read readable assembly
cat rebuild/asm/fcn_XXXX_readable.asm
```
