# MSVC6 Pure-C 1:1 Workflow (Function-Level)

This describes how to create a C implementation of a function, compile it with MSVC6 (`cl.exe`), and verify that the resulting machine code matches the original function bytes 1:1.

## Folder Layout

- Final (kept): `rebuild/c/`
  - `init.c`
  - `exit.c`
  - `fcn_10003140.c`

- Reusable brute-force tooling (archived): `rebuild/experiments/msvc6_purec/`
  - `scripts/` brute-force scripts
  - `outputs/` TSV results
  - `variants/` generated source-shape variants

## Canonical Compiler

- `tools/MSVC600/VC98/Bin/CL.EXE` (run via Wine)
- Typical options used here: `/O2 /MT /Gd`
- For `windows.h`: include path `/I"tools/MSVC600/VC98/Include"`

## Step-by-Step (Per Function)

## Annotations (reccmp-compatible)

We annotate function implementations so external tooling can map source back to original addresses.

- Spec reference: https://github.com/isledecomp/reccmp/blob/master/docs/annotations.md
- Target alias used in this repo: `SERVER`

For C files, place this comment immediately above the function implementation:

```c
// FUNCTION: SERVER 0x10003140
```

For asm files, we use the same payload but with NASM comment syntax:

```asm
; FUNCTION: SERVER 0x10003140
```

Note: reccmp expects functions within a compilation unit to be ordered by address ascending. In our setup we generally keep one function per `.c` file, which satisfies this trivially.

### 1) Find function boundaries

Use `r2` or `objdump`:

```bash
r2 -A -q -c 'afl' original/Server/server.dll
objdump -d -M intel --start-address=0xSTART --stop-address=0xEND original/Server/server.dll
```

### 2) Identify offsets and extract original bytes

Example: Init

- VA: `0x10009320`
- Size: `48`
- File offset: `0x9320`

```bash
dd if=original/Server/server.dll of=rebuild/experiments/msvc6_purec/slices/init_original_48.bin bs=1 skip=$((0x9320)) count=48
```

Example: Exit

- VA: `0x10009350`
- Size: `68`
- File offset: `0x9350`

```bash
dd if=original/Server/server.dll of=rebuild/experiments/msvc6_purec/slices/exit_original_68.bin bs=1 skip=$((0x9350)) count=68
```

### 3) Implement function in C (final source)

Rules of thumb for 1:1 matching:

- Keep the source shape simple.
- Prefer direct fixed-address loads/calls instead of helper locals when you see MSVC reorder.
- Use the same calling convention as the original exports (`__cdecl` here).
- Keep boolean returns as `return result != NULL;` when the original uses `test/setne`.

### 4) Compile with MSVC6 and emit listing

```bash
wine tools/MSVC600/VC98/Bin/CL.EXE /nologo /c /O2 /MT /Gd \
  /Fo"rebuild/c/func.obj" \
  /Fa"rebuild/c/func.asm" \
  "rebuild/c/func.c"
```

With `windows.h`:

```bash
wine tools/MSVC600/VC98/Bin/CL.EXE /nologo /c /O2 /MT /Gd \
  /I"tools/MSVC600/VC98/Include" \
  /Fo"rebuild/c/func.obj" \
  /Fa"rebuild/c/func.asm" \
  "rebuild/c/func.c"
```

### 5) Extract `.text` and compare bytes

```bash
objcopy -O binary --only-section=.text rebuild/c/func.obj rebuild/c/func_text.bin
dd if=rebuild/c/func_text.bin of=rebuild/c/func_slice.bin bs=1 count=$SIZE
cmp -s rebuild/c/func_slice.bin rebuild/c/original_slice.bin
```

### 6) Patch `.text` section and rebuild full DLL

`.text` raw starts at file offset `0x1000`, so the offset inside `text_raw.bin` is:

`text_offset = file_offset - 0x1000`

Init example:

```bash
cp rebuild/sections/text_raw.bin rebuild/sections/text_patched.bin
dd if=rebuild/c/init_pure_bytes.bin of=rebuild/sections/text_patched.bin bs=1 seek=$((0x8320)) conv=notrunc

cat > rebuild/asm/server_patched.asm <<'EOF'
BITS 32
incbin "rebuild/sections/header.bin"
incbin "rebuild/sections/text_patched.bin"
incbin "rebuild/sections/rdata_raw.bin"
incbin "rebuild/sections/data_raw.bin"
incbin "rebuild/sections/reloc_raw.bin"
EOF

nasm -f bin -o rebuild/Server/server_patched.dll rebuild/asm/server_patched.asm
md5sum rebuild/Server/server_patched.dll original/Server/server.dll
sha256sum rebuild/Server/server_patched.dll original/Server/server.dll
cmp -s rebuild/Server/server_patched.dll original/Server/server.dll
```

## Final Files (Current)

- Init (pure C, with windows.h, exact): `rebuild/c/init.c`
- Exit (pure C): `rebuild/c/exit.c`
- fcn_10003140 (pure C, with windows.h, exact): `rebuild/c/fcn_10003140.c`

Tracker:
- `rebuild/docs/C_REBUILT_FUNCTIONS.md`

Archived alternate Init sources:
- `rebuild/experiments/msvc6_purec/final_sources/init_pure_exact.c` (no headers)
- `rebuild/experiments/msvc6_purec/final_sources/init_pure_windows_readable_exact.c` (windows.h + typedef)

## Brute-Force Extension

To extend the approach to other functions, reuse the brute-force scripts archived under:

- `rebuild/experiments/msvc6_purec/scripts/`

## Makefile (Init + Exit + fcn_10003140)

For the current finalized `Init` + `Exit` + `fcn_10003140` C sources, you can build a bit-identical DLL with:

```bash
make -C rebuild/c
```

See also: `rebuild/docs/FUNCTION_LEVEL_MATCH_WORKFLOW.md`.

Outputs:
- `rebuild/Server/server_from_c.dll`
- `rebuild/sections/text_from_c.bin`

and create new variant generators for the target function.
