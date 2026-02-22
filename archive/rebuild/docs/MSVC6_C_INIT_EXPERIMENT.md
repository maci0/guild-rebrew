# MSVC6 C Init Rebuild Process

## Goal
Reproduce `Init` (`VA 0x10009320`, 48 bytes) from C with MSVC6, then rebuild a checksum-identical `server.dll` using the compiled function bytes.

## Environment
- Compiler: `tools/MSVC600/VC98/Bin/CL.EXE` (run via Wine)
- Rebuild assembler: NASM
- Working folder: `rebuild/c`

## Header Requirement (`windows.h`)

`windows.h` is **not required**, but it **can** still produce a 1:1 match with the right source shape.

- Exact pure-C match without headers (archived): `rebuild/experiments/msvc6_purec/final_sources/init_pure_exact.c`
- Exact pure-C match with headers (final): `rebuild/c/init.c`
- For header-based builds, compile with include path:

```bash
wine tools/MSVC600/VC98/Bin/CL.EXE /nologo /c /O2 /MT /Gd \
  /I"tools/MSVC600/VC98/Include" \
  /Fo"rebuild/c/init.obj" \
  "rebuild/c/init.c"
```

## 1) Extract original Init bytes

`Init` is at file offset `0x9320` (RVA `0x9320`, image base `0x10000000`).

```bash
dd if=original/Server/server.dll of=rebuild/experiments/msvc6_purec/slices/init_original_48.bin bs=1 skip=$((0x9320)) count=48
```

## 2) Disassemble/reference target behavior

Reference disassembly is documented in `rebuild/docs/functions/Init.md` and corresponds to this 48-byte window.

## 3) Re-implement in C

Final sources:

1. `windows.h` exact-match (final): `rebuild/c/init.c`
2. No-header exact-match (archived): `rebuild/experiments/msvc6_purec/final_sources/init_pure_exact.c`

## 4) Compile with MSVC6

Compile the final `windows.h` implementation:

```bash
wine tools/MSVC600/VC98/Bin/CL.EXE /nologo /c /O2 /MT /Gd \
  /I"tools/MSVC600/VC98/Include" \
  /Fo"rebuild/c/init.obj" \
  "rebuild/c/init.c"
```

Compile the archived no-header implementation:

```bash
wine tools/MSVC600/VC98/Bin/CL.EXE /nologo /c /O2 /MT /Gd \
  /Fo"rebuild/c/init_pure_exact.obj" \
  "rebuild/experiments/msvc6_purec/final_sources/init_pure_exact.c"
```

## 5) Extract compiled bytes and compare

```bash
objcopy -O binary --only-section=.text rebuild/c/init.obj rebuild/c/init_text.bin
dd if=rebuild/c/init_text.bin of=rebuild/c/init_48.bin bs=1 count=48
cmp -s rebuild/c/init_48.bin rebuild/experiments/msvc6_purec/slices/init_original_48.bin
```

Expected: no output and success exit code (exact match).

## 6) Replace Init in `.text` section and reassemble DLL

Patch `text_raw.bin` copy at section offset `0x8320` (because `.text` starts at file `0x1000`).

```bash
cp rebuild/sections/text_raw.bin rebuild/sections/text_cl_init.bin
dd if=rebuild/c/init_48.bin of=rebuild/sections/text_cl_init.bin bs=1 seek=$((0x8320)) conv=notrunc
```

Assemble the patched full DLL with:

`rebuild/asm/server_cl_init.asm`

```nasm
BITS 32
incbin "rebuild/sections/header.bin"
incbin "rebuild/sections/text_cl_init.bin"
incbin "rebuild/sections/rdata_raw.bin"
incbin "rebuild/sections/data_raw.bin"
incbin "rebuild/sections/reloc_raw.bin"
```

```bash
nasm -f bin -o rebuild/Server/server_cl_init.dll rebuild/asm/server_cl_init.asm
```

## 7) Verify final checksums

```bash
md5sum rebuild/Server/server_cl_init.dll original/Server/server.dll
sha256sum rebuild/Server/server_cl_init.dll original/Server/server.dll
cmp -s rebuild/Server/server_cl_init.dll original/Server/server.dll
```

Expected values:
- MD5: `43279c2f9e9fd4d7bbc3889fd02ea4ea`
- SHA256: `c7ac331f44292657c1fa613608ffd84c9d8ee778e3e7696c7782b37dd6d40ee5`

## Outcome
- The final `windows.h` implementation (`rebuild/c/init.c`) compiles to a 1:1 match for the 48-byte `Init` function.
- Injecting the compiled bytes into `.text` and rebuilding yields a bit-identical full `server.dll`.

## Notes

Earlier non-matching pure-C candidates were removed during experiment cleanup to keep `rebuild/c/` minimal.
The exact-match sources and brute-force scripts/outputs are preserved under `rebuild/experiments/msvc6_purec/`.

## Brute-Force Search (Pure C, Exhaustive Matrix)

An exhaustive pure-C search was added and executed:

- Script: `rebuild/experiments/msvc6_purec/scripts/bruteforce_init_purec_v2.sh`
- Outputs:
  - `rebuild/experiments/msvc6_purec/outputs/bruteforce_v2_results.tsv`
  - `rebuild/experiments/msvc6_purec/outputs/bruteforce_v2_best.tsv`

Search dimensions:
- 96 source-shape variants (`variants_v2/v*.c`)
- 22 compiler flag sets
- Total combinations: 2,112

Result:
- Found multiple exact pure-C matches (diff `0`, text size `48`), including variant `v0004.c` with `/O2 /MT /Gd`.

Winning minimal pure-C source (archived):
- `rebuild/experiments/msvc6_purec/final_sources/init_pure_exact.c`

Verification:
```bash
wine tools/MSVC600/VC98/Bin/CL.EXE /nologo /c /O2 /MT /Gd \
  /Fo"rebuild/c/init_pure_exact2.obj" \
  "rebuild/experiments/msvc6_purec/final_sources/init_pure_exact.c"

objcopy -O binary --only-section=.text rebuild/c/init_pure_exact2.obj rebuild/c/init_pure_exact2_text.bin
dd if=rebuild/c/init_pure_exact2_text.bin of=rebuild/c/init_pure_exact2_48.bin bs=1 count=48
cmp -s rebuild/c/init_pure_exact2_48.bin rebuild/experiments/msvc6_purec/slices/init_original_48.bin
```

This now confirms pure C can produce a 1:1 bit-identical `Init` sequence under the right source shape and options.

## Brute-Force Search (`windows.h` Variants)

An additional exhaustive matrix was run for `windows.h`-based sources:

- Script: `rebuild/experiments/msvc6_purec/scripts/bruteforce_init_windowsh.sh`
- Outputs:
  - `rebuild/experiments/msvc6_purec/outputs/bruteforce_winh_results.tsv`
  - `rebuild/experiments/msvc6_purec/outputs/bruteforce_winh_best.tsv`

Result:
- Multiple exact matches (`diff=0`, `text_size=48`) were found, including `v0000.c` with `/O2 /MT /Gd`.
- Canonical windows.h exact source: `rebuild/c/init.c`.

## Most Readable `windows.h` 1:1 Source

Preferred readable exact-match source:

- `rebuild/c/init.c`

Compile and verify:

```bash
wine tools/MSVC600/VC98/Bin/CL.EXE /nologo /c /O2 /MT /Gd \
  /I"tools/MSVC600/VC98/Include" \
  /Fo"rebuild/c/init.obj" \
  "rebuild/c/init.c"

objcopy -O binary --only-section=.text rebuild/c/init.obj rebuild/c/init_text.bin
dd if=rebuild/c/init_text.bin of=rebuild/c/init_48.bin bs=1 count=48
cmp -s rebuild/c/init_48.bin rebuild/experiments/msvc6_purec/slices/init_original_48.bin
```

This keeps `windows.h` and remains bit-identical for the 48-byte `Init` body.
