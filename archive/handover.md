# Handover Document — Rebrew Reverse Engineering

## Standing Directive
"Continue, don't stop until you reversed all known functions 1:1; do not ask for permission for tool usage, you have it. Make sure to keep the catalog updated as you go along. Catalog should also hint if the function came from the game, msvcrt or zlib 1.1.3."

## Current Progress
- **~158 functions matched** out of ~471 total in `server.dll` (~34%)
- **CATALOG.md is STALE** — currently shows 146 functions but 12 more were matched in this session. Needs a full rebuild.

## New Matches This Session (12 functions, not yet in CATALOG.md)

| VA | Size | Name | Flags | Match | Origin |
|-----|------|------|-------|-------|--------|
| 0x10005720 | 66B | reset_subobject | /O2 | RELOC | GAME |
| 0x10005770 | 72B | cleanup_subobject | /O2 | RELOC | GAME |
| 0x100184A0 | 56B | find_entity_21c | /O2 | EXACT | GAME |
| 0x100151B0 | 41B | table_lookup | /O2 | EXACT | GAME |
| 0x1001C97A | 13B | stream_read_dword | /O1 | EXACT | MSVCRT |
| 0x1001C997 | 14B | stream_read_word | /O1 | EXACT | MSVCRT |
| 0x1001C987 | 16B | stream_read_qword | /O1 | EXACT | MSVCRT |
| 0x1001D097 | 21B | crt_unlock | /O1 /Oy- | RELOC | MSVCRT |
| 0x100212CD | 22B | clear_bit_call | /O1 | RELOC | MSVCRT |
| 0x1001B542 | 34B | crt_rand | /O1 | RELOC | MSVCRT |
| 0x1001BB60 | 47B | crt_lock_stream | /O1 | RELOC | MSVCRT |
| 0x1001BBB2 | 47B | crt_unlock_stream | /O1 | RELOC | MSVCRT |

## Priority Action Items

### 1. Update CATALOG.md (FIRST THING TO DO)
The catalog at `reversed/CATALOG.md` needs all 12 new functions added. Run a full rebuild by scanning all .c files in `reversed/` and regenerating. Total should be ~158 functions (31 exact, 127 reloc-normalized).

### 2. Near-Misses (Very Close but Not Matched)
These functions have only 1-5 byte differences and are worth revisiting:

| VA | Size | Name | Diff | Issue |
|-----|------|------|------|-------|
| 0x10007A70 | 111B | finalize_trees | 4B | Register alloc (edx vs ecx for lookup index) |
| 0x10015E90 | 211B | entity_find_3tables | 5B | Table 3 register alloc + loop tail ordering |
| 0x1000C6A0 | 102B | iterate_linked_entities | 7B | MSVC6 /O2 loop body duplication (109B vs 102B) |
| 0x10003820 | 114B | read_next_byte | 2B | Register alloc + code layout |
| 0x10015DC0 | 55B | search_table_43 | 5B | Return address computation differs |
| 0x10015690 | 41B | set_struct_fields | 5B | Store ordering / register selection |
| 0x10012440 | 37B | call_and_bool | 2B | `xor ecx;cmp` vs `neg` for bool conversion |
| 0x10020360 | 66B | crt_osfhnd | 3B+ | Register swap (eax/ecx for fd parameter) |
| 0x10016240 | 72B | search_slot | 9B+ | Multiply decomposition differs |

### 3. Untried Functions (328 remaining, sorted by size)
Best targets for next session (small, likely matchable):

**Tiny CRT (11-24B):**
- 0x1001B8A5 (11B) — `push 9; call unlock; pop; xor edi; ret` (problem: includes xor edi which is caller-context)
- 0x1001E7BA (24B) — exception context store
- 0x10020FF8 (24B) — format string parse start (part of larger function?)

**Small functions (34-56B):**
- 0x10018150 (34B) — switch on char type (0-25), returns 0 or 2
- 0x1001A540 (39B) — `strrchr` via `repne scasb` + `std; repne scasb`
- 0x10021F3D (41B) — zero large buffer via `rep stosd`
- 0x1002350A (43B) — `strnlen`-like function
- 0x10023812 (43B) — `strdup` wrapper (strlen + alloc + strcpy)
- 0x1001A809 (44B) — heap alloc retry loop
- 0x1001AC70 (47B) — `_alloca_probe` / `__chkstk` stack probe
- 0x1001A110 (48B) — random float range computation (FPU)
- 0x10021298 (53B) — FPU control word manipulation
- 0x1001C8DC (53B) — buffered char output (putc-like)

**Medium functions (55-100B):**
- 0x100184E0 (66B) — type_check_compute (5B diff from earlier)
- 0x10014EE0 (69B) — game function
- 0x1001D4CD (72B) — CRT function
- 0x10021538 (73B) — bitfield test
- 0x10017AB0 (74B) — game function
- 0x10014F30 (74B) — game function
- 0x10021EC0 (74B) — CRT function
- 0x10018450 (78B) — random generator with FPU
- 0x100180D0 (81B) — game function
- 0x100196C0 (81B) — game function

## Key Technical Insights (for the next agent)

### Tooling
- Use `uv run python` for all Python commands
- MSVC6 toolchain at `tools/MSVC600/VC98/` runs under Wine
- Test harness: `uv run python reversed/test_func.py <src.c> <symbol> --va 0xVA --size N --cflags "/O2"`
- Batch test pattern: write a Python script in `reversed/_tmp/batch*.py` with FUNCTIONS list

### C89 Constraints (MSVC6)
- No `for(int i=...)` — declare vars at block top
- No `//` comments — use `/* */`
- No mixed declarations and code

### Compilation Patterns (Confirmed Flags)
- **GAME functions**: `/nologo /c /O2 /MT /Gd` (confirmed by user — full optimization, cdecl)
- **MSVCRT/CRT functions**: `/O1` (size optimization), sometimes `/O1 /Oy-` (frame pointer)
- **ZLIB 1.1.3 functions**: `/nologo /c /O2 /MT /Gd` (matches with `/O2`; unclear if zlib was built from source alongside game code or pre-built as static lib and linked in — either way, `references/zlib-1.1.3/` source produces byte-identical matches with `/O2`)
- **Win32 API calls**: Use `__declspec(dllimport)` to get `ff 15` (IAT call) instead of `e8` (reloc call)
- **`cmp word [mem], 0xFFFF`**: Use `*(unsigned short *)p == 0xFFFF` to force 16-bit immediate (opcode `66 81`) instead of sign-extended 8-bit (opcode `66 83`)
- **Signed vs unsigned loop comparison**: `while ((int)p < (int)END)` generates `jl` (7C), `while (p < END)` generates `jb` (72)
- **Multiply decomposition**: MSVC6 decomposes `i * N` into LEA chains. E.g., `i * 540 = i*3*5*9*4` → `lea eax,[ecx+ecx*2]; lea eax,[eax+eax*4]; lea eax,[eax+eax*8]; lea eax,[eax*4+base]`
- **Running pointer vs index**: Keep both `p += stride` and `i++` as separate variables if the target uses both
- **`neg; sbb; and` pattern**: `val ? 7 : 0` compiles to `neg eax; sbb eax,eax; and eax,7`

### Register Allocation
- Variable declaration order can affect register assignment but is unreliable
- Some functions have persistent register allocation mismatches that are extremely hard to control from C source
- If target uses eax for param and your output uses ecx (or vice versa), try reordering declarations or changing the data flow

### Common Pitfalls
- **Don't strip trailing 0x00**: It's the last byte of `ret 0xc` (c2 0c 00)
- **Preamble protection**: Always split preamble (extern/typedef) from body before mutation
- **Loop body duplication**: MSVC6 /O2 can duplicate loop bodies for certain patterns, making output 7+ bytes larger. Very hard to prevent.
- **`__int64` return type**: Use for functions returning 64-bit values (edx:eax)

## File Layout
```
reversed/
├── CATALOG.md          — Master catalog (NEEDS UPDATE)
├── test_func.py        — Test harness for comparing compiled output vs target
├── *.c                 — 158 matched C source files
└── _tmp/
    ├── batch7_part*.py — Previous batch test scripts
    ├── batch8_part*.py — This session's batch test scripts
    └── *.c             — Temporary C files from batch testing
```

## Workflow
1. Get disassembly for candidate functions using r2: `r2 -q -e scr.color=false -c 'aaa; s VA; pD SIZE' server.dll`
2. Write C source that should compile to matching bytes
3. Test with: `uv run python reversed/test_func.py src.c _symbol --va 0xVA --size N --cflags "/O2"`
4. If match: write final .c file to `reversed/`, update CATALOG.md
5. If close miss: analyze byte diffs, try variants (register order, loop style, signed/unsigned, etc.)
6. Use batch scripts in `_tmp/` to test multiple variants efficiently
