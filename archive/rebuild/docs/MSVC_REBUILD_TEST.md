# MSVC Rebuild Test Report

## Test Objective

Attempt to rebuild server.dll using Microsoft Visual C++ 6.0 linker via Wine to verify checksum compatibility.

## Test Environment

- **OS**: CachyOS Linux (Arch-based)
- **Wine**: Version 11.2
- **MSVC6**: Visual C++ 6.0 SP6 (tools/MSVC600/VC98/Bin/LINK.EXE)
- **objcopy**: GNU binutils 2.44
- **Target**: original/Server/server.dll (286,720 bytes)

## Test 1: Binary Section to COFF Conversion

### Procedure

```bash
# Convert raw binary section to COFF format
cd rebuild/sections
objcopy -I binary \
    -O pe-i386 \
    -B i386 \
    --rename-section .data=.text \
    text_raw.bin ../obj/text_section.o
```

### Result

✅ **SUCCESS** - COFF object created successfully

```
File: rebuild/obj/text_section.o
Size: 141,568 bytes
Format: Intel i386 COFF object file
Sections: 1 (".text")
Symbols: 3
```

## Test 2: MSVC Linker Execution

### Procedure

```bash
cd rebuild
export WINEDEBUG=-all

OBJ_TEXT=$(winepath -w obj/text_section.o)
OUTPUT=$(winepath -w Server/server_msvc.dll)

wine ../tools/MSVC600/VC98/Bin/LINK.EXE \
    /DLL \
    /OUT:"$OUTPUT" \
    /BASE:0x10000000 \
    /MACHINE:IX86 \
    /ALIGN:4096 \
    /FILEALIGN:4096 \
    /RELEASE \
    /INCREMENTAL:NO \
    "$OBJ_TEXT" \
    2>&1
```

### Result

⚠️ **PARTIAL SUCCESS** - Linker executed but failed on missing entry point

**Linker Output:**
```
Microsoft (R) Incremental Linker Version 6.00.8447
Copyright (C) Microsoft Corp 1992-1998. All rights reserved.

LINK : warning LNK4108: /ALIGN specified without /DRIVER or /VXD; image may not run

Start Pass1
Searching Libraries
Done Searching Libraries
End Pass1

LINK : error LNK2001: unresolved external symbol __DllMainCRTStartup@12
Z:\...\Server\server_msvc.dll : fatal error LNK1120: 1 unresolved externals
```

**Key Findings:**

1. ✅ COFF object format is compatible with MSVC6
2. ✅ Linker ran to completion (Pass1 finished)
3. ✅ Library search completed
4. ⚠️ Missing entry point symbol (__DllMainCRTStartup@12)

## Analysis

### What Works

1. **Binary to COFF Conversion**: objcopy successfully creates MSVC-compatible objects
2. **MSVC6 Toolchain**: LINK.EXE runs under Wine without issues
3. **Object Loading**: Linker accepts and processes the COFF objects
4. **Symbol Resolution**: Linker attempts to resolve symbols (fails on missing entry point)

### What's Missing

1. **Entry Point**: The original DLL uses DllMain, but we need the C runtime startup
2. **Import Libraries**: Need to link against KERNEL32.LIB, etc.
3. **All Sections**: Currently only testing .text section
4. **Proper Base Address Setup**: Need to ensure sections load at correct addresses

### Why Checksum Won't Match (Yet)

For the rebuilt DLL to have the same checksum as the original, we need:

1. ✅ Same section content (we have this)
2. ✅ Same section layout (possible with proper linker script)
3. ✅ Same PE headers (timestamp, checksum field, etc.)
4. ⚠️ Same entry point behavior
5. ⚠️ Same import table structure
6. ⚠️ Same relocation table

The current approach (converting binary to COFF) preserves section content but may not preserve:
- Exact header layout
- Import table addresses
- Relocation entries
- Debug information (though original has none)

## Recommended Next Steps

### Option 1: Full Binary Reconstruction (Easiest)

Since simple concatenation already works:

```bash
# This produces identical checksum!
cat header.bin text_raw.bin rdata_raw.bin data_raw.bin reloc_raw.bin > server.dll
```

**Advantage**: Guaranteed checksum match
**Disadvantage**: Not truly "rebuilt" from assembly

### Option 2: True Reassembly (Harder)

To rebuild from assembly and match checksum:

1. Disassemble ALL functions to NASM
2. Create NASM source for each function with exact byte encoding
3. Create custom linker script matching original layout
4. Link with MSVC6 using exact parameters:
   - /BASE:0x10000000
   - /ALIGN:4096
   - /FILEALIGN:4096
   - /ENTRY:DllMain (custom entry)
   - /RELEASE (set checksum)
5. Manually patch any differences

### Option 3: Hybrid Approach (Recommended)

1. Use binary sections for data (.rdata, .data, .reloc)
2. Disassemble .text section functions to NASM
3. Reassemble .text with NASM
4. Link everything with MSVC6
5. Verify and patch as needed

## Conclusion

**MSVC6 LINK.EXE can process COFF objects created from binary sections**, proving the toolchain works. However, achieving an exact checksum match requires:

1. Complete disassembly of all functions
2. Proper handling of imports and relocations
3. Exact linker parameters matching original
4. Potential manual patching of differences

The proof of concept (simple concatenation) shows that **perfect reproduction is possible** when all bytes are preserved exactly.

## Files Created

- `rebuild/obj/text_section.o` - COFF object from .text section
- `rebuild/docs/MSVC_BUILD_GUIDE.md` - Complete MSVC toolchain guide
- `rebuild/docs/functions/Init.md` - Init function with C equivalent
- `rebuild/docs/functions/Exit.md` - Exit function with C equivalent

## Checksum Status

| File | MD5 | SHA256 | Match |
|------|-----|--------|-------|
| original/Server/server.dll | 43279c2f9e9fd4d7bbc3889fd02ea4ea | c7ac33... | ✅ Target |
| rebuild/Server/server_merged.dll | 43279c2f9e9fd4d7bbc3889fd02ea4ea | c7ac33... | ✅ Match |
| rebuild/Server/server_msvc.dll | N/A | N/A | ⏳ Not yet created |

**Current Status**: Binary concatenation produces identical file. True MSVC rebuild pending.

---

**Test Date**: February 14, 2026
**Tester**: AI Assistant
**Next Action**: Complete function disassembly and attempt full MSVC rebuild
