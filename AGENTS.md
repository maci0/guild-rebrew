# AGENTS.md — guild-rebrew

## Overview

Workspace for reversing Europa 1400: The Guild `server.dll` using the `rebrew`
toolchain. Contains original binaries, ~330 reversed C89 source files in
`src/server.dll/`, MSVC6 toolchain under Wine, and project config in `rebrew-project.toml`.

**Not a Python package.** Install tooling from sibling dirs:

```bash
uv pip install -e ../rebrew && uv pip install -e ../recoverage
```

## Quick Start

1. `rebrew todo --json` — pick highest ROI action item
2. `rebrew skeleton 0x<VA>` — generate `.c` skeleton
3. Write C89 source matching Ghidra decompilation
4. `rebrew test src/server.dll/<file>.c` — compile and compare (auto-updates STATUS)
5. `rebrew diff src/server.dll/<file>.c --json` — inspect byte diffs
6. Iterate until RELOC or EXACT — `rebrew test` promotes automatically

## CLI Tools

Use `--json` for structured output (preferred for agents). All tools read `rebrew-project.toml`.

| Command | Use |
|---------|-----|
| `rebrew todo --json` | Prioritized action items (compile errors, near misses, new functions) |
| `rebrew doctor` | Check toolchain and project health |
| `rebrew skeleton 0x<VA>` | Generate C skeleton from address |
| `rebrew test <file>` | Compile + byte-compare; auto-updates STATUS in sidecar |
| `rebrew test <file> --no-promote` | Compile + compare without updating STATUS |
| `rebrew diff <file> --json` | Structured byte diff (`--mm` for structural diffs only) |
| `rebrew diff <file> --fix-blocker` | Auto-write BLOCKER to sidecar from diff |
| `rebrew match <file> --json` | Run GA matching engine |
| `rebrew match --all --near-miss --threshold 5` | Batch GA on near-miss functions |
| `rebrew rename <old> <new>` | Rename function and update cross-references |
| `rebrew verify --json` | Bulk verify all reversed files |
| `rebrew verify --compare --json` | Compare against last saved report, detect regressions |
| `rebrew lint --json` | Validate annotations |
| `rebrew lint --fix` | Auto-fix annotation format |
| `rebrew data --json` | Inventory globals in .data/.rdata/.bss |
| `rebrew graph --format summary` | Dependency graph stats and blockers |
| `rebrew graph --cu-map --json` | Infer compilation unit boundaries |
| `rebrew catalog --data-json` | Write `db/data_<target>.json` (input for build-db) |
| `rebrew catalog --json` | Print catalog summary to stdout |
| `rebrew flirt --json` | FLIRT scan for known library functions |
| `rebrew extract --json` | Batch extract and disassemble functions |
| `rebrew asm 0x<VA> --size 128` | Quick offline disassembly (hex dump) |
| `rebrew asm 0x<VA> --format nasm` | NASM-reassembleable source |
| `rebrew prove <file>` | Prove MATCHING function is semantically equivalent (optional angr dep) |
| `rebrew binsync-export ./out` | Export annotations to BinSync state directory |
| `rebrew sync --push` | Push annotations to Ghidra |
| `rebrew sync --summary --json` | Preview what would be synced |
| `clang-format -i --style=file <file>` | Format C source (pre-commit hook runs automatically) |


## C Source Style (src/server.dll/*.c)

### Language: Strict C89 (MSVC6)

- **No C99+**: no `//` line comments, no `for(int i=...)`, no mixed declarations
- **Variables at block top**: all declarations before any statements in each `{}`
- **Comments**: use `/* */` only
- **Inner-block declarations allowed**: new `{}` blocks can declare new variables

### Formatting (.clang-format)

- Microsoft base style, 4-space indentation (tabs for continuation)
- Braces: **same line** for control statements, structs, enums, classes
- Pointer alignment: left (`int* p`), space after C-style cast: `(int) x`
- Insert braces on single-line if/else/for/while
- No bin-packing of arguments or parameters (one per line if they don't fit)

### Naming Conventions

- **Known functions**: `AllocGameObject`, `AcceptConnections` (descriptive)
- **Unknown functions**: `func_<VA>` — `func_10003e40`, `func_1000d570`
- **Globals**: `g_<address>` or `g_<name>` — `g_10030b6c`, `g_listen_socket`
- **Filenames**: `crt_` prefix for CRT (`crt_strcmp.c`), `zlib_` for zlib, `game_` for known game functions
- **Calling convention**: `__cdecl` for GAME code, `__stdcall` for Win32 imports

### File Structure

One function per file. The `.c` file contains **only** the `// FUNCTION:` marker and
the C source — all volatile metadata lives in `rebrew-function.toml`:

```c
/* Brief prose description of what the function does. */

// FUNCTION: SERVER 0x10003da0
// alloc_game_object

typedef unsigned int uint32_t;    /* local typedefs as needed */

extern int __cdecl some_func(int);
extern int g_some_global;

int __cdecl alloc_game_object(int param_1)
{
    int local_var;
    /* ... */
    return 0;
}
```

`rebrew-function.toml` (in the same directory, managed by CLI tools):

```toml
["SERVER.0x10003da0"]
size = 160
status = "RELOC"
```

The function name and symbol are derived automatically from the C function definition.
`CFLAGS` is optional — falls back to the target default from `rebrew-project.toml`.

### Types and Imports

- Primitives: `int`, `char *`, `unsigned int`, `unsigned short`, `unsigned char`
- Local `typedef` per file (no shared headers): `uint32_t`, `uint16_t`, etc.
- Struct definitions are local to each file
- Win32 imports: `__declspec(dllimport)` with `__stdcall`
- Use `#pragma intrinsic(memset)` when compiler must emit inline `rep stosd`

## Annotation Reference

### In the `.c` file

Only the `// FUNCTION:` marker line stays in `.c`:

```
// FUNCTION: SERVER 0xVA
```

**Markers**: `FUNCTION` (game code), `LIBRARY` (CRT/zlib), `STUB` (incomplete)

**Derived automatically**: Symbol (from C function def, e.g. `_alloc_game_object`), Prototype

### In `rebrew-function.toml` (sidecar — managed by CLI tools)

> [!CAUTION]
> Never manually edit `rebrew-function.toml`. It is managed by `rebrew test`,
> `rebrew match`, `rebrew sync`, etc. Manual edits will be lost.

**Required sidecar fields**: `status`, `size`

**Optional sidecar fields**: `cflags`, `blocker`, `blocker_delta`, `ghidra`, `analysis`, `note`, `source`

**`status` values**:

| Status | Meaning |
|--------|---------|
| `EXACT` | Byte-for-byte identical to target |
| `RELOC` | Identical after masking relocations (typical best) |
| `MATCHING` | Close but structural diffs remain |
| `STUB` | Far off or placeholder |

**Origin / compiler flags** — configured in `rebrew-project.toml`, not per-function annotations.
Default `cflags` presets (base `/nologo /c /MT` always prepended):

| Origin | CFLAGS | Notes |
|--------|--------|-------|
| GAME | `/O2 /Gd` | Full optimization, cdecl default |
| MSVCRT | `/O1` | Size optimization |
| ZLIB | `/O2` | Full optimization |

### Data / Global annotations

`.c` file retains only the marker and declaration:

```c
// DATA: SERVER 0xVA

extern int g_some_global;
```

Metadata lives in `rebrew-data.toml` (same directory, auto-managed):

```toml
["SERVER.0xVA"]
size    = 4
section = ".bss"
note    = "optional description"
```

> [!CAUTION]
> Never manually edit `rebrew-data.toml`. It is managed by `rebrew data`, `rebrew sync`, etc.

## Diff Output

`rebrew diff` markers: `==` identical, `~~` relocation diff only,
`**` structural mismatch. Use `--mm` to show only `**` lines.

## Key Directories

| Path | Contents |
|------|----------|
| `src/server.dll/` | Reversed C89 source files |
| `src/server.dll/rebrew-function.toml` | Function metadata (status, size, blocker, …) |
| `src/server.dll/rebrew-data.toml` | Data/global metadata (size, section, note) |
| `original/Server/server.dll` | Target binary (DO NOT MODIFY) |
| `tools/MSVC600/VC98/` | MSVC6 compiler toolchain (via Wine) |
| `references/zlib-1.1.3/` | Exact zlib version used in server.dll |
| `rebrew-project.toml` | Single source of truth for all tool config |

## Agent Skills

Detailed workflow instructions are in `.agents/skills/`:

| Skill | Use When |
|-------|----------|
| `rebrew-intake` | Onboarding a new binary, initial triage |
| `rebrew-workflow` | End-to-end function reversing workflow |
| `rebrew-matching` | Flag sweeping, GA engine, diff analysis |
| `rebrew-data-analysis` | Globals, dispatch tables, BSS debugging |
| `rebrew-ghidra-sync` | Ghidra push/pull sync via ReVa MCP |

## Knowledge Memory (MuninnDB MCP)

A local MuninnDB MCP server is available for persistent project knowledge. Use
the `muninn` tools to store and retrieve discoveries made during reversing.

**When to store** (`muninn_remember` / `muninn_remember_batch`):
- Identified purpose of a global variable (e.g. `g_10030b6c` is the connection pool)
- Discovered struct layouts or calling conventions
- Mapped relationships between functions
- Noted patterns in compiler output or flag behavior

**When to search** (`muninn_recall` / `muninn_find_by_entity`):
- Before reversing a new function, check if related globals/structs are documented
- When encountering an unknown global or function reference
- To recall prior analysis of similar code patterns
