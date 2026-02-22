# AGENTS.md - Rebrew Project Guidelines

## AI Agent Quick Start

If you are an AI agent continuing work on this project, follow these steps:

**1. See what needs work:**
```bash
rebrew-next --stats          # overall progress
rebrew-next --origin GAME     # next GAME functions to tackle
rebrew-next --improving       # MATCHING functions to improve
```

**2. Generate a skeleton .c file:**
```bash
rebrew-skeleton 0x<VA>         # single function
rebrew-skeleton --batch 5 --origin GAME  # batch of 5
```

**3. Get decompilation** (if Ghidra MCP available):
```
get-decompilation programPath="/server.dll" functionNameOrAddress="0x<VA>"
```

**4. Write C89 source**, replacing the skeleton TODO. Key rules:
- Declare ALL variables at block top (before any statements)
- No `for(int i=...)` — declare `int i;` separately
- No `//` comments in function body (use `/* */`)
- Use `__cdecl` for game functions, `__stdcall` for Win32 API

**5. Test:**
```bash
rebrew-test src/server_dll/<file>.c <symbol> \
    --va 0x<VA> --size <SIZE> --cflags "/O2 /Gd"
```

**6. Update STATUS** in the annotation header based on result:
- `EXACT` = byte-for-byte match
- `RELOC` = match after masking relocations
- `MATCHING` = near-miss (add `BLOCKER` line explaining diff)

**Compiler flags:** GAME=`/O2 /Gd`, MSVCRT=`/O1`, ZLIB=`/O2`.

**Full workflow details:** See `docs/WORKFLOW.md`.

---

## Project Overview

**Rebrew** is a compiler-in-the-loop genetic algorithm that searches C source code permutations to match a target function's compiled bytes. Given a target binary function (extracted from an executable or `.bin` file), it mutates C source code and compiles each variant with MSVC6 under Wine, scoring candidates by byte similarity to the target.

The primary use case is **binary matching** — reconstructing the exact C source that produced a given compiled function, targeting the MSVC6 (Visual C++ 6.0) compiler specifically.

**Dependencies:**
```bash
pip install pefile capstone pygad pycparser
# or: uv add pefile capstone pygad pycparser
```

**Toolchain:** MSVC6 at `tools/MSVC600/VC98/` running under Wine.

---

## Project Structure

```
rebrew/
├── original/                       # Original game binaries (do not modify)
│   ├── Server/server.dll           # Target DLL (PE32, ~141K .text)
│   ├── Europa1400Gold.exe          # Main game EXE (~2MB .text)
│   └── Europa1400Gold_TL.exe       # TL edition EXE (~2.4MB .text)
├── src/                            # Decompilation source (per-target subdirs)
│   ├── server_dll/                 # server.dll decompilation
│   │   ├── *.c                     # ~330 reversed C source files
│   │   ├── CATALOG.md              # Auto-generated function catalog
│   │   ├── ghidra_functions.json   # Cached Ghidra function list
│   │   └── r2_functions.json/txt   # radare2 function databases
│   ├── Europa1400Gold/             # Europa1400Gold.exe decompilation (future)
│   └── Europa1400Gold_TL/          # Europa1400Gold_TL.exe decompilation (future)
├── bin/                            # Extracted target bytes (gitignored)
│   └── server_dll/                 # .bin files extracted from original DLLs
├── tools/                          # All tooling (MSVC6 + custom scripts)
│   ├── MSVC600/VC98/               # MSVC6 toolchain (CL.EXE, LINK.EXE, headers, libs)
│   │   ├── Bin/                    # CL.EXE, LINK.EXE, LIB.EXE
│   │   ├── Include/                # C headers
│   │   ├── Lib/                    # Static libraries (LIBCMT.LIB, etc.)
│   │   └── CRT/SRC/               # Partial CRT source (subset only)
│   ├── reccmp/                     # isledecomp/reccmp toolchain (git clone)
│   ├── matcher/                  # Modular GA logic package
│   │   ├── compiler.py             # Wine execution, flag sweeping
│   │   ├── core.py                 # Persistent caching (SQLite), data classes
│   │   ├── mutator.py              # Mutation engine and crossover
│   │   ├── parsers.py              # COFF and PE extraction
│   │   └── scoring.py              # Byte/mnemonic comparison
│   ├── matcher.py                  # CLI frontend for PyGAD GA
│   ├── train_mutation_model.py     # Train ML model for mutations
│   ├── catalog.py                  # Core pipeline: annotations, catalog, JSON, CSV
│   ├── verify.py                   # Verification pipeline: compile and verify bytes
│   ├── test_func.py                # Quick compile-and-compare harness
│   ├── gen_skeleton.py             # Auto-generate .c skeleton from VA
│   ├── next_work.py                # Show uncovered functions + progress stats
│   ├── ga_batch.py                 # Batch GA runner for STUB functions
│   ├── batch_extract.py            # Batch extract and disassemble functions
│   ├── batch_test.sh               # Batch test all reversed functions
│   ├── nasm_extract.py             # NASM extraction with round-trip verify
│   ├── lint_annotations.py         # Annotation linter (E001-E010, W001-W007)
│   ├── ghidra_sync.py              # Ghidra label/comment/bookmark sync
│   ├── extract_target.py           # Helper to compile+extract target bytes
│   └── disasm_candidates.py        # Quick disassembly helper
├── docker/                         # Docker build environment
│   ├── Dockerfile                  # Debian + Wine + MSVC6 + Python
│   └── entrypoint.sh               # verify/test/diff/lint/stats/skeleton
├── output/                         # Generated tool output (gitignored)
│   ├── ga_runs/                    # GA batch results (best.c per function)
│   └── nasm/                       # Extracted NASM disassembly
├── references/                     # Reference source code for matching
│   └── zlib-1.1.3/                 # Complete zlib 1.1.3 source
├── tests/                          # pytest tests
├── docs/                           # TOOLS.md, WORKFLOW.md
│   ├── TOOLS.md                    # Installed RE tools reference
│   └── WORKFLOW.md                 # Step-by-step decomp guide
├── recoverage/                     # Web coverage dashboard
│   ├── open.sh                     # Launch dashboard + open browser
│   ├── dev_server.py               # Dev server with regen support
│   ├── potato.py                   # "Potato Mode" static HTML renderer
│   ├── index.html / app.js / style.css
│   └── data.json                   # Auto-generated by catalog.py
├── reccmp-project.yml              # Multi-target config (reccmp-compatible)
├── AGENTS.md                       # This file
└── archive/                        # Old challenges, examples, experiments
```

---

## Build & Run Commands

### Running the GA (Unified Engine)

The project now uses a unified GA engine powered by PyGAD and modularized in the `matcher` package. The `matcher.py` script serves as the main entry point to this engine.

```bash
# Basic usage (OBJ-only mode, fastest)
rebrew-match \
  --cl "wine tools/MSVC600/VC98/Bin/CL.EXE" \
  --inc "tools/MSVC600/VC98/Include" \
  --cflags "/nologo /c /O2 /MT /Gd" \
  --target-exe original/Server/server.dll --target-va 0x10003da0 --target-size 160 \
  --symbol "_alloc_game_object" \
  --seed-c src/server_dll/alloc_game_object.c \
  --out-dir run_out -j 16
```

### Full Link Mode

To perform full linking (slower, but useful for calling convention testing), use the `--full-link` flag:

```bash
rebrew-match \
  --full-link \
  --cl ... --link ... --inc ... --lib ... \
  --cflags "/nologo /c /O2 /MT /Gd" \
  --ldflags "/nologo /SUBSYSTEM:CONSOLE" \
  ...
```

### Flag Sweep (auto-find best compiler flags)

```bash
# Sweep only (no GA)
rebrew-match \
  --flag-sweep-only \
  --cl "wine tools/MSVC600/VC98/Bin/CL.EXE" \
  --inc "tools/MSVC600/VC98/Include" \
  --cflags "/nologo /c /MT" \
  --target-exe original/Server/server.dll --target-va 0x10003da0 --target-size 160 \
  --symbol "_alloc_game_object" \
  --seed-c src/server_dll/alloc_game_object.c -j 16
```

### Diff Mode (structural comparison)

```bash
# Diff a specific source against target (no GA)
rebrew-match \
  --cl "wine tools/MSVC600/VC98/Bin/CL.EXE" \
  --inc "tools/MSVC600/VC98/Include" \
  --cflags "/nologo /c /O2 /MT /Gd" \
  --compare-obj \
  --diff-only src/server_dll/alloc_game_object.c \
  --target-exe original/Server/server.dll --target-va 0x10003da0 --target-size 160 \
  --symbol "_alloc_game_object" --seed-c src/server_dll/alloc_game_object.c

# Show diff after GA run
rebrew-match ... --diff
```

Output uses markers: `==` (identical), `~~` (reloc-only diff), `**` (structural diff).

### Target Sources

```bash
--target-bin FILE          # Raw .bin file
--target-obj FILE          # COFF .obj (parsed with built-in COFF parser)
--target-exe FILE          # PE with --target-map or --target-va/--target-size
--target-lib FILE          # .LIB archive (needs --lib-obj)
  --lib-obj NAME           # Object member in .LIB
  --lib-exe CMD            # LIB.EXE command (auto-derived from --cl)
--target-va HEX            # VA in --target-exe
--target-size INT          # Byte size (with --target-va)
```

### Checkpoint / Resume

```bash
# GA run with checkpointing
rebrew-match ... --checkpoint-every 5

# Resume interrupted run
rebrew-match ... --resume

# Custom checkpoint path
rebrew-match ... --checkpoint /path/to/ckpt.json --resume
```

### Code Quality / Checkers

We use several tools to ensure code quality, formatting, and type safety:

```bash
# Code formatting
uv run black recoverage/

# Linting
uv run ruff check recoverage/

# Static type checking
uv run pyright recoverage/
uv run pyre check
```

You can run all checkers at once using the provided script:
```bash
./test.sh
```

### Syntax Check / Tests

```bash
uv run python -m py_compile tools/matcher.py
uv run pytest tests/ -v
```

---

## MSVC6 Constraints

- **C89 only**: no `for(int i=...)`, no `//` comments in strict mode, declare all variables at block top
- **Symbol decoration**: `_funcname` for `__cdecl`, `_funcname@N` for `__stdcall`
- **Compiler ID**: comp.id = `000A2636` (can verify with `objconv` on `.obj` files)
- **No `__declspec(noinline)`** — not supported
- **No `/GS`** — buffer security checks don't exist
- Wine execution: all CL.EXE/LINK.EXE calls go through Wine

## Confirmed Compiler Flags by Origin

| Origin | CL flags | Notes |
|--------|----------|-------|
| **GAME code** | `/nologo /c /O2 /MT /Gd` | Confirmed by user. Full optimization, cdecl. |
| **MSVCRT/CRT** | `/nologo /c /O1 /MT /Gd` or `/O1 /Oy-` | Size optimization. Some functions need `/Oy-` for frame pointer. |
| **ZLIB 1.1.3** | `/nologo /c /O2 /MT /Gd` | Matches with `/O2`. Unknown whether zlib was built from source alongside game code or pre-built as a static library and linked in. Either way, the exact zlib 1.1.3 source at `references/zlib-1.1.3/` produces byte-identical matches with `/O2`. |

---

## Challenge: _DllMainCRTStartup@12

### Background

The target is a 157-byte `_DllMainCRTStartup@12` function from `server.dll`. This function is from the MSVC6 C Runtime Library (`dllcrt0.c` in LIBCMT.LIB), compiled with the same CL.EXE we have.

### Key Findings

1. **Source identified**: The function matches the VC98 CRT source from `dllcrt0.c` (copyright 1989-1997). The source was found via the [shihyu/learn_c](https://github.com/shihyu/learn_c/blob/master/vc_lib_src/src/dllcrt0.c) GitHub repository.

2. **Register allocation is the hard part**: MSVC6 assigns registers based on variable liveness. The target uses:
   - `ebx` = hDllHandle (1st param)
   - `esi` = dwReason (2nd param)
   - `edi` = lpreserved (3rd param)
   - `retcode` at `[ebp+0xc]` (reuses dwReason's stack slot)

3. **The retcode-accumulation pattern is critical**: The original CRT source uses:
   ```c
   BOOL retcode = TRUE;
   // ATTACH path:
   if ( _pRawDllMain )
       retcode = (*_pRawDllMain)(hDllHandle, dwReason, lpreserved);
   if ( retcode )
       retcode = _CRT_INIT(hDllHandle, dwReason, lpreserved);
   if ( !retcode )
       return FALSE;
   ```
   This extends retcode's live range from function entry, creating register pressure that forces the compiler to put all 3 params in registers and spill retcode to the stack. Using early returns (`if (!_pRawDllMain(...)) return FALSE;`) instead produces completely different register allocation (160 bytes, wrong registers).

4. **`BOOL retcode = TRUE;` initialization matters**: Without it, the compiler generates 165 bytes with wrong allocation. The initialization extends retcode's live range backwards.

5. **`volatile` is wrong**: Using `volatile BOOL retcode` forces correct stack allocation but produces 7 structural byte differences (store-before-compare ordering, MOV instead of AND for clearing retcode). The non-volatile VC98 source produces the exact match.

6. **Trimming bug**: `extract_candidate_symbol_bytes()` was stripping trailing `0x00` bytes, which ate the last byte of `ret 0xc` (`C2 0C 00`). Fixed to only trim `0xCC` (int3) and `0x90` (nop).

7. **Static vs extern doesn't matter**: Whether `__proc_attached` is `static` or `extern`, and whether `_pRawDllMain` is a common variable or `extern`, the compiler produces identical code.

8. **Extracted CRT object confirms same compiler**: `dllcrt0.obj` extracted from `LIBCMT.LIB` via `wine LIB.EXE /EXTRACT:...` has comp.id `000A2636`, identical to our CL.EXE.

### Current Status

The VC98 source in `archive/challenge/entry0.c` produces a **bit-perfect `.obj` match** against `dllcrt0.obj` extracted from LIBCMT.LIB:

```
sha256: 1c1efa6cc1eab6cfb75834b5dd49e7fa784fa1d258b61f7db4f5e46852538457
```

Compiled with `/O1 /Oy- /MT /Gd`. The source uses `#include <windows.h>` for type definitions (produces identical output to manual typedefs). Comparison is done at the `.obj` level (pre-linker) to avoid relocation address differences.

Compiler flags: `/nologo /c /O1 /Oy- /MT /Gd` — `/O2` produces completely different (189-byte) output.

---

## matcher.py — Unified GA Engine

### Overview

`matcher.py` is the unified entry point for the compiler-in-the-loop genetic algorithm. It delegates logic to the `matcher` package and uses the PyGAD library for robust optimization. It takes a seed C source file and a target binary function, then iteratively mutates the source, compiles each variant with MSVC6 under Wine, and scores the output by byte similarity to the target.

### Modular Architecture (matcher package)

The core logic is modularized for maintainability and reuse:

- **`matcher.core`**: Handles persistent state.
    - `BuildCache`: SQLite-backed persistent cache for compilation results. Prevents redundant Wine calls across GA runs.
    - `GACheckpoint`: Logic for saving and resuming GA progress.
- **`matcher.compiler`**: Manages the MSVC6 toolchain via Wine.
    - Handles relative path mapping for `CL.EXE` compatibility.
    - Implements flag sweeping to find optimal compiler settings.
- **`matcher.scoring`**: Multi-metric fitness calculation.
    - `_normalize_reloc_x86_32`: Masking of relocatable bytes (`call`, `jmp`, global references).
    - Mnemonics comparison via Capstone disassembly.
- **`matcher.parsers`**: COFF and PE extraction.
    - Extracts raw code bytes and relocation metadata from `.obj` and `.exe` files.
- **`matcher.mutator`**: Modular mutation engine.
    - Contains a catalog of 40+ C89-compatible mutation operators.
    - Supports AST-aware transformations (via `pycparser`).

### Operation Modes

There are four distinct modes of operation:

#### 1. Diff Mode (`--diff-only FILE`)

Compiles a single source file and shows a side-by-side disassembly comparison against the target. This is the primary mode for manual reversing.

```bash
rebrew-match \
  --cl "wine tools/MSVC600/VC98/Bin/CL.EXE" \
  --inc "tools/MSVC600/VC98/Include" \
  --cflags "/nologo /c /O2 /MT /Gd" \
  --diff-only src/server_dll/my_func.c \
  --target-exe original/Server/server.dll --target-va 0x10001000 --target-size 302 \
  --symbol "_my_func" --seed-c src/server_dll/my_func.c
```

#### 2. Flag Sweep Mode (`--flag-sweep-only`)

Tries all combinations of MSVC6 compiler flag axes against a single source to find which flags produce the closest match.

#### 3. OBJ-Only GA Mode (Default)

The recommended GA mode. Compiles candidates to `.obj` only (skipping `LINK.EXE`), providing bit-perfect comparison by avoiding relocation noise.

```bash
rebrew-match \
  --cl "wine tools/MSVC600/VC98/Bin/CL.EXE" \
  --inc "tools/MSVC600/VC98/Include" \
  --cflags "/nologo /c /O2 /MT /Gd" \
  --target-exe original/Server/server.dll --target-va 0x10001000 --target-size 302 \
  --symbol "_my_func" \
  --seed-c src/server_dll/my_func.c \
  --out-dir run_my_func \
  --generations 200 --pop 64 -j 16
```

#### 4. Full Link GA Mode (`--full-link`)

Compiles candidates to `.exe` via `CL.EXE` + `LINK.EXE`. Required only when testing calling conventions or linker-dependent behavior.

### Scoring System (lower = better)

| Component | Weight | What it measures |
|-----------|--------|------------------|
| Length penalty | 3.0 | `abs(candidate_size - target_size)` |
| Weighted byte similarity | 1000.0 | Position-weighted byte comparison; first 20 bytes (prologue) weighted 3x |
| Relocation-aware similarity | 500.0 | Byte comparison after masking relocatable fields |
| Mnemonic similarity | 200.0 | Instruction-level comparison via capstone disassembly |
| Prologue bonus | -100.0 | Bonus if first 20 bytes match exactly |

### Thread Safety & Caching

- **`BuildCache`**: Uses SQLite with file-level locking to allow multiple parallel GA runs to share the same compilation cache safely.
- **Parallel Compilation**: Uses `ThreadPoolExecutor` to saturate available CPU cores during the evaluation phase.
- **Workdirs**: Each candidate is compiled in a unique subdirectory to prevent file collisions.


### Checkpoint Format

`GACheckpoint` stores: generation number, best score, best source text, entire population (list of source strings), Python RNG state, stagnant generation count, cumulative elapsed time, and an args hash. Saved as JSON via atomic write (tmp file + rename). On `--resume`, the args hash is validated to prevent loading a checkpoint from a different run configuration.

---


## Reference Sources

### MSVC6 CRT Source (Partial — `tools/MSVC600/VC98/CRT/SRC/`)

We have 17 original CRT source files shipped with VC++ 6.0. These are the **authoritative** sources for heap-related CRT functions and can be compiled directly to produce byte-identical matches.

| File | Size | Key Functions |
|------|------|---------------|
| `MALLOC.C` | 8.8K | `_malloc_base()`, `_nh_malloc_base()`, `_heap_alloc_base()` |
| `FREE.C` | 4.8K | `_free_base()` — heap free with V5/V6/system heap dispatch |
| `REALLOC.C` | 23K | `_realloc_base()` — realloc with SBH support |
| `CALLOC.C` | 5.3K | `_calloc_base()` |
| `EXPAND.C` | 4.9K | `_expand_base()` |
| `MSIZE.C` | 3.5K | `_msize_base()` |
| `SBHEAP.C` | 105K | Small-block heap: `__sbh_alloc_block()`, `__sbh_free_block()`, `__sbh_find_block()`, `__sbh_resize_block()`, `__sbh_alloc_new_region()`, `__sbh_alloc_new_group()`, `__sbh_heap_check()`, plus V5 compat functions |
| `HEAPINIT.C` | 21K | `_heap_init()`, `__heap_select()`, `_GetLinkerVersion()` |
| `HEAPCHK.C` | 8.2K | `_heapchk()`, `_heapwalk()`, `_heapset()` |
| `HEAPMIN.C` | 13K | `_heapmin()`, `__sbh_heapmin()` |
| `OUTPUT.C` | 88K | `_output()` — printf core formatting engine |
| `STRFTIME.C` | 33K | `strftime()` implementation |
| `TZSET.C` | 30K | `_tzset()`, timezone handling |
| `DBGHEAP.C` | 61K | Debug heap (only used in debug builds, not in server.dll) |
| `WINHEAP.H` | 9.0K | All SBH struct definitions (`HEADER`, `REGION`, `GROUP`, `ENTRY`, `BITVEC`), constants (`_HEAP_MAXREQ`, `BYTES_PER_PAGE`, etc.), V5/V6/SYSTEM_HEAP selection |

**Important**: The CRT uses `#ifdef WINHEAP` — server.dll uses the `WINHEAP` path (Win32 HeapAlloc-based). The `#ifndef WINHEAP` paths can be ignored. server.dll also uses `#ifdef _MT` paths (multi-threaded CRT).

**Missing CRT sources** (not in our subset but needed): `dllcrt0.c`, `crt0.c`, `_flsbuf.c`, `_write.c`, `_read.c`, `input.c`, `dosmap.c`, `initterm.c`, `cinit.c`, `handler.c`, `amsg.c`, `mlock.c`, `tidtable.c`, `getptd.c`, `mbstring/*.c`. These can be found in the [shihyu/learn_c](https://github.com/shihyu/learn_c/tree/master/vc_lib_src/src) GitHub repository.

### zlib 1.1.3 Source (`references/zlib-1.1.3/`)

The **exact** zlib version statically linked into server.dll. Confirmed by version strings in the binary: `"deflate 1.1.3 Copyright 1995-1998 Jean-loup Gailly"` and `"inflate 1.1.3 Copyright 1995-1998 Mark Adler"`.

**Core source files and their functions:**

| File | Key Functions | Visibility |
|------|---------------|------------|
| `deflate.c` | `deflateInit_()`, `deflateInit2_()`, `deflate()`, `deflateEnd()`, `deflateReset()`, `deflateParams()`, `deflateCopy()`, `deflateSetDictionary()` | ZEXPORT (public) |
| `deflate.c` | `fill_window()`, `deflate_stored()`, `deflate_fast()`, `deflate_slow()`, `longest_match()`, `lm_init()`, `flush_pending()`, `read_buf()`, `putShortMSB()` | local (static) |
| `inflate.c` | `inflateInit_()`, `inflateInit2_()`, `inflate()`, `inflateEnd()`, `inflateReset()`, `inflateSync()`, `inflateSetDictionary()`, `inflateSyncPoint()` | ZEXPORT |
| `trees.c` | `_tr_init()`, `_tr_stored_block()`, `_tr_align()`, `_tr_flush_block()`, `_tr_tally()` | exported |
| `trees.c` | `tr_static_init()`, `init_block()`, `pqdownheap()`, `gen_bitlen()`, `gen_codes()`, `build_tree()`, `scan_tree()`, `send_tree()`, `build_bl_tree()`, `send_all_trees()`, `compress_block()`, `set_data_type()`, `bi_reverse()`, `bi_flush()`, `bi_windup()`, `copy_block()` | local |
| `adler32.c` | `adler32()` | ZEXPORT |
| `crc32.c` | `crc32()`, `get_crc_table()` | ZEXPORT |
| `compress.c` | `compress()`, `compress2()` | ZEXPORT |
| `uncompr.c` | `uncompress()` | ZEXPORT |
| `inftrees.c` | `inflate_trees_bits()`, `inflate_trees_dynamic()`, `inflate_trees_fixed()` | exported |
| `inftrees.c` | `huft_build()` | local |
| `infblock.c` | `inflate_blocks_reset()`, `inflate_blocks()`, `inflate_blocks_free()`, `inflate_set_dictionary()`, `inflate_blocks_sync_point()` | exported |
| `infcodes.c` | `inflate_codes_new()`, `inflate_codes()`, `inflate_codes_free()` | exported |
| `inffast.c` | `inflate_fast()` | exported |
| `infutil.c` | `inflate_flush()` | exported |
| `gzio.c` | `gzopen()`, `gzdopen()`, `gzread()`, `gzwrite()`, `gzclose()`, `gzflush()`, `gzseek()`, `gztell()`, `gzeof()`, `gzrewind()`, `gzgets()`, `gzputs()`, `gzputc()`, `gzgetc()`, `gzprintf()`, `gzsetparams()`, `gzerror()` | ZEXPORT |
| `zutil.c` | `zlibVersion()`, `zError()`, `z_error()`, `zcalloc()`, `zcfree()`, `zmemcpy()`, `zmemcmp()`, `zmemzero()` | mixed |

**Anchor strings** for identifying zlib functions in server.dll:

| String | Address | Referencing Function | Likely zlib Function |
|--------|---------|---------------------|---------------------|
| `"1.1.3"` | 0x1002706c | FUN_100057c0, FUN_10001330, FUN_10009020 | `inflateInit2_`, `deflateInit2_`, game wrapper |
| `"need dictionary"` | 0x10027538 | InflateStateMachine (0x100058d0) | `inflate()` |
| `"unknown compression method"` | 0x1002758c | InflateStateMachine | `inflate()` |
| `"invalid distance code"` | 0x10027504 | FUN_10005390, InflateFast (0x10004bc0) | `inflate_fast()`, `inflate_codes()` |
| `"incomplete dynamic bit lengths tree"` | 0x100286b0 | FUN_10005d00 | `inflate_trees_dynamic()` |
| `"incomplete literal/length tree"` | 0x100286fc | FUN_10006280 | `inflate_trees_dynamic()` |
| `"incomplete distance tree"` | 0x10028764 | FUN_10006280 | `inflate_trees_dynamic()` |
| `"buffer error"` | 0x10029514 | FUN_100015b0 | `inflate_blocks()` |
| `"stream error"` | 0x10029544 | FUN_100015b0 | `inflate_blocks()` |

**Identified zlib functions in server.dll** (from call graph + string analysis):

| server.dll VA | Size | Identified As | zlib Source File |
|---------------|------|---------------|-----------------|
| 0x100057c0 | 270B | `inflateInit2_` | inflate.c |
| 0x100058d0 | 1015B | `inflate` | inflate.c |
| 0x10004bc0 | 1919B | `inflate_codes` (InflateFast) | infcodes.c |
| 0x10005390 | 911B | `inflate_fast` | inffast.c |
| 0x100015b0 | 685B | `inflate_blocks` | infblock.c |
| 0x10005d00 | 163B | `inflate_trees_bits` | inftrees.c |
| 0x10005db0 | ?? | `huft_build` (shared callee) | inftrees.c |
| 0x10006280 | 393B | `inflate_trees_dynamic` | inftrees.c |
| 0x10001330 | 505B | `deflateInit2_` | deflate.c |
| 0x10001530 | 115B | `init_stream` (deflate helper) | deflate.c |
| 0x10001860 | 47B | `copy_fields` (already matched) | deflate.c |
| 0x10001890 | 114B | zlib inflate helper | infblock.c |
| 0x10001910 | 170B | `free_game_subobject` (already matched) | deflate.c |
| 0x100019c0 | ?? | deflate/inflate callee | |
| 0x10006ec0 | 108B | zlib tree helper | trees.c |
| 0x10006fb0 | ?? | inflate helper | infblock.c |
| 0x10007050 | ?? | inflate helper | infblock.c |
| 0x100092e0 | 19B | `zcalloc` (alloc_mul, already matched) | zutil.c |
| 0x10009300 | 12B | `zcfree` (free_wrap, already matched) | zutil.c |
| 0x10009020 | 667B | game VFS decompression wrapper | game code |

---

## Annotation Standard (reccmp-compatible + extensions)

Based on [reccmp annotations](https://github.com/isledecomp/reccmp/blob/master/docs/annotations.md)
and [reccmp recommendations](https://github.com/isledecomp/reccmp/blob/master/docs/recommendations.md),
with project-specific extensions.

### Function Header (required)

Every `src/server_dll/*.c` file MUST start with a function annotation block:

```c
// FUNCTION: SERVER 0x10003da0
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 160
// CFLAGS: /O2 /Gd
// SYMBOL: _alloc_game_object
// SOURCE: (original source file, if known)
// NOTE: (compiler behavior observations)
```

**Marker types** (first line):
- `FUNCTION` — Game-origin functions with complete implementation
- `LIBRARY` — Third-party library functions (ZLIB, MSVCRT)
- `STUB` — Incomplete/non-matching implementation

**Required fields** (errors if missing):

| Field | Description | Example |
|-------|-------------|---------|
| `STATUS` | Match status (see below) | `EXACT`, `RELOC`, `MATCHING`, `MATCHING_RELOC`, `STUB` |
| `ORIGIN` | Code origin | `GAME`, `MSVCRT`, `ZLIB` |
| `SIZE` | Target function size in bytes | `160` |
| `CFLAGS` | Compiler flags (excluding `/nologo /c /MT`) | `/O2 /Gd` |

**STATUS values explained:**

| Status | Meaning | What it tells you |
|--------|---------|-------------------|
| `EXACT` | Byte-for-byte identical to DLL | Every byte matches. Rare for functions with calls/globals since those encode link-time addresses. |
| `RELOC` | Identical after masking relocation bytes | The code structure, registers, and control flow all match. The only diffs are in `call`/`jmp` displacement bytes and global address references that the linker fills in. **This is the typical best result** for functions that reference other functions or globals. |
| `MATCHING` | Close but with structural byte differences | Compiled output differs in register choice, loop structure, comparison encoding, or code block ordering. Add a `BLOCKER` line explaining the specific difference. |
| `MATCHING_RELOC` | MATCHING but very close (1-5 byte diffs) | Like MATCHING but the diff is tiny — usually one wrong comparison operator or a register swap. Worth iterating on. |
| `STUB` | Far off or placeholder | Significantly wrong size, structure, or still has TODOs. Add a `BLOCKER` line. |

**What gets masked in RELOC comparison:**
- `call rel32` (`E8 xx xx xx xx`) — call target offsets
- `jmp rel32` (`E9 xx xx xx xx`) — jump displacements
- `mov eax/reg, [abs32]` — global variable addresses
- `cmp [abs32], imm` — globals in comparisons
- `push imm32` / `mov reg, imm32` — when value looks like an address (>0x10000000)

**Recommended fields** (warnings if missing):

| Field | Description | Example |
|-------|-------------|---------|
| `SYMBOL` | Decorated linker symbol | `_alloc_game_object`, `___sbh_heap_init` |
| `SOURCE` | Reference source file (for CRT/ZLIB) | `SBHEAP.C:195`, `deflate.c:fill_window` |
| `BLOCKER` | Why a STUB doesn't match (required for STUBs) | `loop-rotation`, `register-alloc` |

**Optional fields**:

| Field | Description | Example |
|-------|-------------|---------|
| `NOTE` | Compiler behavior observations | `store order controls param scheduling` |
| `GLOBALS` | Referenced global variables with addresses | `0x10031b78 __old_small_block_heap` |

### Global Variable Annotations

Following reccmp convention, annotate global variables inline where they're declared:

```c
// GLOBAL: SERVER 0x11766444
extern void *__sbh_pHeaderList;

// GLOBAL: SERVER 0x10031b78
extern __old_sbh_region_t __old_small_block_heap;
```

### Struct Annotations (reccmp recommendations)

**Size annotation**: Add `// SIZE 0xNN` comment above or beside struct definitions:

```c
// SIZE 0x14
typedef struct tagHeader {
    unsigned int bitvEntryHi;   // 0x00
    unsigned int bitvEntryLo;   // 0x04
    unsigned int bitvCommit;    // 0x08
    void *pHeapData;            // 0x0c
    void *pRegion;              // 0x10
} HEADER, *PHEADER;
```

**Member offset annotations**: Add `// 0xNN` comments on each field for structs with
known layout. This makes it easy to cross-reference with Ghidra decompilation.

**Size assertion** (C89-compatible):

```c
typedef char _check_header_size[sizeof(HEADER) == 0x14 ? 1 : -1];
```

### Unknown Type Aliases

Use `undefined` aliases (from reccmp) for unknown types to distinguish known from unknown:

```c
typedef unsigned char undefined;
typedef unsigned short undefined2;
typedef unsigned int undefined4;
```

### Naming Conventions

| Origin | File prefix | Function prefix | Example |
|--------|-------------|-----------------|---------|
| GAME | `game_` | varies (PascalCase for APIs, snake_case for helpers) | `game_set_sync_params.c` |
| MSVCRT | `crt_` | `crt_` or standard name | `crt_sbh_heap_init.c` |
| ZLIB | `zlib_` | zlib original name | `zlib_adler32.c` |

### Lint Rules Reference

Run `rebrew-lint` to check compliance.

| Code | Severity | Description |
|------|----------|-------------|
| E001 | Error | Missing FUNCTION/LIBRARY/STUB annotation |
| E002 | Error | VA outside server.dll .text range |
| E003 | Error | Missing STATUS |
| E004 | Error | Invalid STATUS value |
| E005 | Error | Missing ORIGIN |
| E006 | Error | Invalid ORIGIN value |
| E007 | Error | Missing SIZE |
| E008 | Error | Invalid SIZE value |
| E009 | Error | Missing CFLAGS |
| E010 | Error | Unknown annotation key |
| W001 | Warning | Missing SYMBOL (recommended) |
| W002 | Warning | Old-format header (run --fix) |
| W003 | Warning | No function implementation in file |
| W004 | Warning | Marker/ORIGIN mismatch |
| W005 | Warning | STUB missing BLOCKER |
| W006 | Warning | CRT/ZLIB missing SOURCE |
| W007 | Warning | Struct without SIZE annotation |

### reccmp CSV Export

`catalog.py --csv` generates `server_functions.csv` in reccmp-compatible pipe-delimited format:

```csv
address|name|symbol|type|size
0x10001000|adler32|_adler32|library|302
0x10001330|deflateInit2_|_deflateInit2_|library|505
0x10003da0|alloc_game_object|_alloc_game_object|function|160
```

This file covers ALL known functions (matched + unmatched) and can be imported by reccmp tools.

---

## Code Style Guidelines

### Formatting
- **4 spaces** for indentation (no tabs)
- Line length: aim for <100 characters
- Section headers: `# -----------\n# Section Name\n# -----------`

### Naming
| Element | Convention | Example |
|---------|------------|---------|
| Functions | snake_case | `mutate_code()`, `build_candidate()` |
| Variables | snake_case | `c_path`, `obj_path` |
| Classes | PascalCase | `Score`, `BuildCache` |
| Mutations | `mut_` prefix | `mut_swap_eq_operands()` |
| Private helpers | leading `_` | `_run()`, `_sub_once()` |

### Type Annotations
- Use type hints on all function signatures
- Use `Optional[T]` style (not `T | None`)
- Use `Tuple[T1, T2]` for multiple returns

### Adding a New Mutation

1. Define `def mut_xxx(source: str, rng: random.Random) -> Optional[str]:` in the Mutations section
2. Return `None` if mutation doesn't apply
3. Register in the `mutations` list inside `mutate_code()`
4. Protect the preamble (everything before the function body) from modification

### Testing

```bash
uv run pytest tests/ -v
```

### Command Execution
- **Command Execution**: NEVER use background/async commands. Always prefer synchronous execution with sufficient timeout.

---

## Available RE Tools

Full details in [`docs/TOOLS.md`](docs/TOOLS.md).

### Installed Tools Summary

| Tool | Version | Integration | Functions Found |
|------|---------|-------------|-----------------|
| **Ghidra** | 11.4 | ReVa MCP (live) | 496 |
| **Binary Ninja Free** | 5.2.8722 | GUI only (no headless API in free) | TBD |
| **IDA Free** | 9.2.0 | Headless via `idat` (not integrated) | TBD |
| **radare2** | 5.9.8 | CLI; prior analysis in `r2_functions.json` | 471 |
| **DUMPBIN.EXE** | MSVC6 6.00.8447 | Via Wine | exports only |
| **objconv** | 2.56 | CLI | comp.id verification |
| **objdump** | GNU 2.46 | CLI | no symbols (stripped PE) |
| **yara** | 4.5.5 | CLI | pattern matching |

### Python RE Libraries

| Library | Version | Use |
|---------|---------|-----|
| capstone | 5.0.7 | x86 disassembly (matcher.py scoring) |
| pefile | 2024.8.26 | PE parsing (matcher.py) |

### Cross-Tool Function Tracking

The `catalog.py` pipeline tracks which tools detected each function via the `detected_by` field. Each function in `recoverage/data.json` includes:
- `detected_by`: list of tools that found the function (e.g. `["ghidra", "r2"]`)
- `size_by_tool`: per-tool size measurements (e.g. `{"ghidra": 302, "r2": 302}`)
- `ghidra_name` / `r2_name`: tool-specific names

Ghidra function data is cached in `src/server_dll/ghidra_functions.json` (generated by `catalog.py --export-ghidra`).

### Known Tool Discrepancies

- Ghidra finds 25 more functions than r2
- r2 has 2 bogus size entries: `0x1000ad40` (r2: 1.1MB, Ghidra: 600B) and `0x10018200` (r2: 16.9MB, Ghidra: 123B)
- 7 WS2_32 + 1 KERNEL32 IAT thunks (6B `jmp [addr]` stubs) — not reversible C
- 2 single-byte "functions" (`0x10006f30`, `0x10016670`) — likely `ret` stubs or alignment

### Pipeline Scripts

| Script | Purpose | Usage |
|--------|---------|-------|
| `catalog.py` | Core pipeline: parse annotations, generate catalog + coverage JSON | `rebrew-catalog` |
| `verify.py` | Compile all .c files and verify byte match against DLL | `rebrew-verify` |
| `catalog.py --csv` | Generate reccmp-compatible `server_functions.csv` | `rebrew-catalog --csv` |
| `catalog.py --export-ghidra` | Cache Ghidra function list to `src/server_dll/ghidra_functions.json` | `rebrew-catalog --export-ghidra` |
| `lint_annotations.py` | Annotation linter (E001-E010 errors, W001-W007 warnings) | `rebrew-lint` |
| `lint_annotations.py --fix` | Auto-migrate old annotations to reccmp-style format | `rebrew-lint --fix` |
| `ghidra_sync.py` | Export annotations as Ghidra commands (labels, comments, bookmarks) | `rebrew-sync --export` |
| `batch_extract.py` | Batch extract and disassemble functions from server.dll | `rebrew-batch` |
| `batch_test.sh` | Batch test all reversed functions | `./tools/batch_test.sh` |
