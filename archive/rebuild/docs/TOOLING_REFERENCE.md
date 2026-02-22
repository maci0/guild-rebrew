# Tooling Reference Guide

## Available Tools Overview

### 1. Binary Analysis Tools

#### objdump (GNU binutils)
```bash
# Display headers
objdump -x original/Server/server.dll

# Display section headers
objdump -h original/Server/server.dll

# Disassemble with Intel syntax
objdump -d -M intel original/Server/server.dll

# Display relocations
objdump -R original/Server/server.dll

# Display private headers
objdump -p original/Server/server.dll
```

#### objcopy (GNU binutils)
```bash
# Extract a section to file
objcopy --dump-section .text=text_raw.bin original/Server/server.dll

# Add section to binary
objcopy --add-section .new=data_raw.bin input.dll output.dll

# Strip symbols
objcopy --strip-all input.dll output.dll
```

#### llvm-readobj (LLVM)
```bash
# Read COFF file headers
llvm-readobj -h original/Server/server.dll

# Read all sections
llvm-readobj --sections original/Server/server.dll

# Read imports/exports
llvm-readobj --coff-imports --coff-exports original/Server/server.dll

# Read relocations
llvm-readobj --coff-basereloc original/Server/server.dll
```

#### llvm-objdump (LLVM)
```bash
# Disassemble
llvm-objdump -d original/Server/server.dll

# Show section contents
llvm-objdump -s original/Server/server.dll
```

### 2. Disassembly Tools

#### Capstone (Python library)

Capstone is available for scripted disassembly when you want something lighter than `objdump`/`radare2`, or when you want to disassemble raw byte slices (e.g. extracted function bytes).

```python
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

md = Cs(CS_ARCH_X86, CS_MODE_32)

# Example: disassemble a function slice at a known VA
va = 0x10009320
code = open("rebuild/c/build/init_patch.bin", "rb").read()
for insn in md.disasm(code, va):
    print(f"0x{insn.address:08x}:\t{insn.mnemonic}\t{insn.op_str}")
```

Notes:
- Use `CS_MODE_32` for this DLL (x86, PE32).
- If you disassemble bytes cut from `original/Server/server.dll` by file offset, pass the corresponding VA so addresses match docs.

#### objconv (Agner Fog)
**Location:** `/usr/bin/objconv`
**Version:** 2.56

```bash
# Disassemble to NASM format
objconv -fnasm input.bin output.asm

# Disassemble to MASM format
objconv -fmasm input.bin output.asm

# Disassemble to GAS format
objconv -fgasm input.bin output.asm

# Dump file information
objconv -df input.bin    # File header
objconv -dh input.bin    # Section headers
objconv -ds input.bin    # Symbol table
objconv -dr input.bin    # Relocations
```

**Key Features:**
- Supports PE, COFF, ELF, OMF, Mach-O
- Converts between object formats
- Disassembles to multiple syntaxes
- Handles x86 and x86-64

#### NASM (Netwide Assembler)
**Location:** `/usr/bin/nasm`
**Version:** 3.01

```bash
# Assemble to win32 COFF format
nasm -f win32 -o output.obj input.asm

# Disable optimizations
nasm -f win32 -O0 -o output.obj input.asm

# List supported formats
nasm -hf
```

**Supported Output Formats:**
- `bin` - Flat raw binary
- `coff` - COFF (i386)
- `obj` - Intel/Microsoft OMF
- `win32` - Microsoft extended COFF for Win32 (i386)
- `win64` - Microsoft extended COFF for Win64 (x86-64)
- `elf32` - ELF32 (i386)
- `elf64` - ELF64 (x86-64)

### 3. Microsoft Visual C++ 6.0 Tools

**Location:** `tools/MSVC600/VC98/Bin/`

#### LINK.EXE (MSVC6 Linker)
**Size:** 462,901 bytes
**Version:** 6.00

```bash
# Run via Wine
wine tools/MSVC600/VC98/Bin/LINK.EXE /HELP

# Create DLL
wine tools/MSVC600/VC98/Bin/LINK.EXE \
    /DLL \
    /OUT:output.dll \
    /BASE:0x10000000 \
    /MACHINE:IX86 \
    input.obj
```

**Key Options:**
- `/DLL` - Build DLL
- `/OUT:file` - Output filename
- `/BASE:addr` - Image base address
- `/ENTRY:symbol` - Entry point
- `/MACHINE:IX86` - Target x86
- `/SECTION:name,attrs` - Section attributes
- `/ALIGN:n` - Section alignment
- `/FILEALIGN:n` - File alignment
- `/RELEASE` - Set checksum in header
- `/INCREMENTAL:NO` - Disable incremental linking
- `/MAP` - Generate map file
- `/IMPLIB:file` - Generate import library
- `/DEF:file` - Module definition file

#### LIB.EXE (Library Manager)
```bash
wine tools/MSVC600/VC98/Bin/LIB.EXE /HELP
```

#### DUMPBIN.EXE (Binary Dumper)
```bash
# Display exports
wine tools/MSVC600/VC98/Bin/DUMPBIN.EXE /EXPORTS server.dll

# Display headers
wine tools/MSVC600/VC98/Bin/DUMPBIN.EXE /HEADERS server.dll

# Display imports
wine tools/MSVC600/VC98/Bin/DUMPBIN.EXE /IMPORTS server.dll
```

#### CL.EXE (Compiler)
```bash
# Compile to object
wine tools/MSVC600/VC98/Bin/CL.EXE /c /Fooutput.obj input.c
```

**Environment Setup for Wine:**
```bash
export WINEPREFIX="$HOME/.wine_msvc6"
export INCLUDE="Z:\\path\\to\\MSVC600\\VC98\\Include"
export LIB="Z:\\path\\to\\MSVC600\\VC98\\Lib"
```

### 4. LLVM/Clang Tools

#### lld-link (LLVM Linker)
```bash
# Link DLL
lld-link /dll /out:output.dll input.obj

# Deterministic build
lld-link /dll /out:output.dll /brepro /timestamp:0 input.obj
```

**MSVC-compatible options:**
- `/dll` - Create DLL
- `/out:file` - Output file
- `/base:addr` - Base address
- `/align:n` - Alignment
- `/filealign:n` - File alignment
- `/brepro` - Deterministic mode
- `/timestamp:value` - Set timestamp

### 5. PE Analysis Tools

#### Python pefile
```python
import pefile

# Load PE file
pe = pefile.PE('server.dll')

# Print DOS header
print(pe.DOS_HEADER)

# Print NT headers
print(pe.NT_HEADERS)

# Print sections
for section in pe.sections:
    print(section.Name.decode(), hex(section.VirtualAddress))

# Print exports
if hasattr(pe, 'DIRECTORY_ENTRY_EXPORT'):
    for exp in pe.DIRECTORY_ENTRY_EXPORT.symbols:
        print(exp.name, hex(exp.address))

# Print imports
if hasattr(pe, 'DIRECTORY_ENTRY_IMPORT'):
    for entry in pe.DIRECTORY_ENTRY_IMPORT:
        print(entry.dll)
        for imp in entry.imports:
            print(imp.name, hex(imp.address))

# Verify checksum
print(pe.verify_checksum())

# Generate and set checksum
pe.OPTIONAL_HEADER.CheckSum = pe.generate_checksum()
pe.write('server_fixed.dll')
```

#### readpe (from pev package)
```bash
# Read PE headers
readpe -h server.dll

# Read optional header
readpe -o server.dll

# Read sections
readpe -s server.dll

# Read imports
readpe -i server.dll

# Read exports
readpe -e server.dll
```

### 6. Verification Tools

#### Checksum verification
```bash
# MD5
md5sum original/Server/server.dll rebuild/Server/server.dll

# SHA256
sha256sum original/Server/server.dll rebuild/Server/server.dll

# Compare
md5sum -c checksums.txt
```

#### Binary comparison
```bash
# Byte-level comparison
cmp -l file1.bin file2.bin

# Visual diff (if vbindiff installed)
vbindiff file1.bin file2.bin

# Hex dump and diff
hexdump -C file1.bin > file1.hex
hexdump -C file2.bin > file2.hex
diff file1.hex file2.hex
```

#### File information
```bash
# File type
file server.dll

# Detailed info
ls -la server.dll

# Size in bytes
wc -c server.dll
```

### 7. Wine Tools

#### Wine Configuration
```bash
# Initialize wine prefix
winecfg

# Set Windows version
# Via winecfg: Applications > Add Application > Windows Version

# Run Windows executable
wine program.exe

# Debug mode
WINEDEBUG=+all wine program.exe 2>&1 | less
```

#### Wine Path Conversion
```bash
# Linux to Windows path
winepath -w /home/user/project
# Output: Z:\home\user\project

# Windows to Linux path
winepath -u 'Z:\home\user\project'
# Output: /home/user/project
```

## Tool Comparison Matrix

| Task | Primary | Alternative 1 | Alternative 2 |
|------|---------|---------------|---------------|
| Disassemble | objconv | objdump | llvm-objdump |
| Assemble | nasm | yasm | ml (MASM) |
| Link DLL | MSVC LINK.EXE | lld-link | mingw-ld |
| Analyze PE | pefile | readpe | llvm-readobj |
| Extract sections | objcopy | dd | pefile |
| Verify checksum | md5sum | sha256sum | cmp |
| View headers | objdump -x | llvm-readobj | readpe |

## Workflow Recommendations

### For This Project

1. **Analysis:** Use `objdump -x` and `llvm-readobj` for initial PE analysis
2. **Extraction:** Use `objcopy` to extract raw sections
3. **Disassembly:** Use `objconv -fnasm` for NASM-compatible disassembly
4. **Assembly:** Use `nasm -f win32` to create COFF objects
5. **Linking:** Use MSVC6 `LINK.EXE` via Wine for authenticity
6. **Verification:** Use `md5sum` and `cmp` for checksum validation

## Common Issues & Solutions

### Issue: NASM instruction encoding differs from original
**Solution:** Use `db`, `dw`, `dd` directives for exact byte control

### Issue: Wine can't find MSVC tools
**Solution:** Set proper WINEPREFIX and use full paths

### Issue: Relocations not applied correctly
**Solution:** Ensure linker base address matches original (0x10000000)

### Issue: Checksum doesn't match
**Solution:** Verify all padding, timestamps, and header fields match exactly

### Issue: objconv produces invalid NASM syntax
**Solution:** Manually fix or use objdump -M intel as reference


## Additional Reverse Engineering Tools

### 8. Radare2

**Location:** `/usr/bin/r2`
**Version:** Check with `r2 -v`

Radare2 is a complete reverse engineering framework with advanced analysis capabilities.

```bash
# Analyze and open PE file
r2 -A original/Server/server.dll

# Inside radare2:
[0x1001b9d4]> ii                    # Show imports
[0x1001b9d4]> iE                    # Show exports
[0x1001b9d4]> iS                    # Show sections
[0x1001b9d4]> px 64 @ 0x10001000   # Hex dump 64 bytes at address
[0x1001b9d4]> pd 20 @ 0x1001b9d4   # Disassemble 20 instructions
[0x1001b9d4]> afl                   # List all functions
[0x1001b9d4]> s 0x10009320          # Seek to Init function
[0x1001b9d4]> pdf                   # Print disassembly of current function
[0x1001b9d4]> agf                   # Show function call graph
[0x1001b9d4]> /c mnemonics          # Search for mnemonics
[0x1001b9d4]> ?                     # Help
[0x1001b9d4]> q                     # Quit
```

**Batch analysis:**
```bash
# List all functions in the binary
r2 -q -c 'afl' original/Server/server.dll

# Export disassembly to file
r2 -q -c 'pd > disasm.txt' original/Server/server.dll

# Get function information as JSON
r2 -q -c 'aflj' original/Server/server.dll | python3 -m json.tool

# Full analysis and export
r2 -A -q -c 'pd 1000 @ 0x1001b9d4' original/Server/server.dll > entry.asm
```

**Key commands for DLL analysis:**
- `i` - File information
- `ii` - Imports
- `iE` - Exports
- `iS` - Sections
- `ir` - Relocations
- `afl` - List functions
- `afn name @ addr` - Rename function
- `s addr` - Seek to address
- `pd n` - Disassemble n instructions
- `px n` - Hex dump n bytes
- `x @ addr` - Examine memory
- `V` - Visual mode
- `VV` - Visual graph mode

### 9. Zydis

**Description:** Fast and lightweight x86/x86-64 disassembler library

**Command-line tool:**
```bash
# Disassemble hex bytes
zydis-info -64 55 48 89 e5

# Disassemble from file at offset
echo -n -e '\x55\x48\x89\xe5' | zydis-info -64

# Format output
zydis-info -64 --formatter intel 55 48 89 e5
```

**Library usage (C):**
```c
#include <Zydis/Zydis.h>

ZydisDecoder decoder;
ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, 
                 ZYDIS_STACK_WIDTH_64);

ZydisFormattedInstruction instruction;
ZydisDecoderDecodeFull(&decoder, buffer, length, &instruction);
```

### 10. DiStorm

**Description:** Powerful disassembler for x86/AMD64 with streaming support

**Command-line tool:**
```bash
# Disassemble binary file
distorm3 file.bin

# Disassemble with specific offset and architecture
distorm3 -b 32 -o 0x1000 file.bin

# Output formats
# - -f intel (default)
# - -f att (AT&T syntax)
# - -f masm (MASM format)
```

**Library usage (C):**
```c
#include <distorm.h>

_DecodedInst instructions[MAX_INSTRUCTIONS];
unsigned int decodedCount;

distorm_decode(0, buffer, length, Decode32Bits, 
               instructions, MAX_INSTRUCTIONS, &decodedCount);
```

### Comparison of Disassemblers

| Tool | Speed | Accuracy | Syntax Support | Best For |
|------|-------|----------|----------------|----------|
| objconv | Medium | High | NASM, MASM, GAS | Exact reconstruction |
| objdump | Medium | High | Intel, AT&T | Quick analysis |
| radare2 | Medium | Very High | Intel, AT&T | Interactive RE |
| Capstone | Fast | High | Intel-style strings | Scripted disassembly |
| Zydis | Very Fast | Very High | Intel, AT&T, MASM | Library integration |
| DiStorm | Fast | Very High | Intel, AT&T, MASM | Streaming disassembly |

### Recommended Workflows

#### For Function Extraction (one file per function):
1. Use **radare2** to identify function boundaries
2. Use **objconv** to disassemble to NASM format
3. Manual cleanup of disassembly output
4. Assemble with **nasm**

#### For Quick Analysis:
1. **radare2 -A** for automated analysis
2. **r2 -c 'afl'** to list functions
3. **r2 -c 'pd @ addr'** for disassembly

#### For Library Integration:
1. **Zydis** for high-performance disassembly
2. **DiStorm** for streaming large files
