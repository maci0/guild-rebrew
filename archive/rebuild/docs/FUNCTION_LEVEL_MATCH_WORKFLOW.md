# Function-Level 1:1 Workflow (Extract -> Disasm -> Rebuild -> Reinsert)

This is the general process we use to reproduce individual functions and keep a bit-identical `server.dll`.

## 0) Concepts

- **VA**: virtual address in memory (e.g. `0x10009320`)
- **Image base**: `0x10000000` for this DLL
- **RVA**: `VA - image_base`
- **File offset**: byte offset in the file
- **Section raw offset**: where the section starts in the file
- **Section RVA**: where the section maps in memory

For functions in `.text` in this DLL, `.text` has raw offset `0x1000` and RVA `0x1000`, so:

- `file_offset = RVA` (for `.text` only)

## 1) Find function boundaries

Pick one:

```bash
# Radare2: list functions
r2 -A -q -c 'afl' original/Server/server.dll
```

or if you already have start/end:

```bash
objdump -d -M intel --start-address=0xSTART --stop-address=0xEND original/Server/server.dll
```

## 2) Compute offsets

General formula:

```
RVA = VA - 0x10000000
file_offset = section_raw_offset + (RVA - section_rva)
```

For `.text` in this project:

```
file_offset = VA - 0x10000000
text_bin_offset = file_offset - 0x1000
```

## 3) Extract original bytes

```bash
dd if=original/Server/server.dll of=/tmp/f.bin bs=1 skip=$((FILE_OFFSET)) count=$SIZE
```

## 4) Disassemble (reference)

```bash
objdump -d -M intel --start-address=0xSTART --stop-address=0xEND original/Server/server.dll
```

## 5) Recreate function bytes

We currently use two approaches:

### A) NASM exact bytes

- Useful for documenting and rebuilding without a compiler
- Use when you want full byte control

### B) MSVC6 pure-C exact bytes

- Useful when you want a C source that still compiles to the exact original bytes
- This requires brute-forcing the *source shape* and sometimes compiler flags

See `rebuild/docs/MSVC6_PURE_C_WORKFLOW.md`.

## Annotations

We use reccmp-style annotations to keep a durable mapping between source and original addresses:

- Spec: https://github.com/isledecomp/reccmp/blob/master/docs/annotations.md
- Target alias: `SERVER`

Examples:

```c
// FUNCTION: SERVER 0x10009320
```

```asm
; FUNCTION: SERVER 0x10009320
```

See `rebuild/docs/C_REBUILT_FUNCTIONS.md` for the current list of functions rebuilt in pure C.

## 6) Reinsert into `.text` and rebuild DLL

Patch a copy of `rebuild/sections/text_raw.bin`:

```bash
cp rebuild/sections/text_raw.bin rebuild/sections/text_patched.bin
dd if=/tmp/f.bin of=rebuild/sections/text_patched.bin bs=1 seek=$((TEXT_BIN_OFFSET)) conv=notrunc
```

Reassemble DLL:

```bash
cat > rebuild/asm/server_patched.asm <<'EOF'
BITS 32
incbin "rebuild/sections/header.bin"
incbin "rebuild/sections/text_patched.bin"
incbin "rebuild/sections/rdata_raw.bin"
incbin "rebuild/sections/data_raw.bin"
incbin "rebuild/sections/reloc_raw.bin"
EOF

nasm -f bin -o rebuild/Server/server_patched.dll rebuild/asm/server_patched.asm
```

Verify:

```bash
md5sum rebuild/Server/server_patched.dll original/Server/server.dll
sha256sum rebuild/Server/server_patched.dll original/Server/server.dll
cmp -s rebuild/Server/server_patched.dll original/Server/server.dll
```
