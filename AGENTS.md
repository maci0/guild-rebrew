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

1. `rebrew triage --json` -- assess the binary
2. `rebrew todo --json` -- get highest ROI action items
3. `rebrew skeleton 0x<VA>` -- generate `.c` skeleton
4. Write C89 source matching Ghidra decompilation
5. `rebrew test src/server.dll/<file>.c --json` -- compile and compare
6. `rebrew match -d src/server.dll/<file>.c --json` -- inspect diffs
7. Iterate until RELOC or EXACT match
8. `rebrew promote src/server.dll/<file>.c --json` -- test + update STATUS

## CLI Tools

Use `--json` for structured output (preferred for agents). All tools read `rebrew-project.toml` for compiler paths, target binary, and flags. Global flags: `-v` (verbose), `-q` (quiet) apply to all subcommands.

| Command | Use |
|---------|-----|
| `rebrew triage --json` | Combined overview: coverage, near-misses, recommendations |
| `rebrew doctor` | Check toolchain and project health |
| `rebrew todo --json` | Prioritized action items (compile errors, near misses, new functions) |
| `rebrew next --json` | Find next function to reverse (sorted by similarity) |
| `rebrew next --improving --json` | List MATCHING functions sorted by byte delta |
| `rebrew skeleton 0x<VA>` | Generate C skeleton from address |
| `rebrew test <file> --json` | Compile and byte-compare against target |
| `rebrew match --diff-only <file> --json` | Structured byte diff (`-d`) |
| `rebrew match --flag-sweep-only <file>` | Find best compiler flags for a single function (`-S`) |
| `rebrew match <file> --json` | Run GA matching engine |
| `rebrew ga --flag-sweep --json` | Batch flag sweep on all MATCHING functions |
| `rebrew ga --near-miss --threshold 5` | Batch GA on MATCHING functions with small deltas |
| `rebrew promote <file> --json` | Test + atomically update STATUS |
| `rebrew rename <old> <new>` | Rename function and update cross-references |
| `rebrew status --json` | Coverage progress |
| `rebrew verify --json` | Bulk verify all reversed files |
| `rebrew lint --json` | Validate annotations |
| `rebrew lint --fix <file>` | Auto-fix annotation format |
| `rebrew data --json` | Inventory globals in .data/.rdata/.bss |
| `rebrew graph --format summary` | Dependency graph stats and blockers |
| `rebrew catalog --json` | Generate coverage catalog |
| `rebrew flirt --json` | FLIRT scan for known library functions |
| `rebrew extract --json` | Batch extract and disassemble functions |
| `rebrew asm 0x<VA> --size 128 --json` | Quick offline disassembly |
| `rebrew sync --push` | Push annotations to Ghidra |
| `rebrew sync --summary --json` | Preview what would be synced |
| `clang-format -i --style=file <file>` | Format C source (pre-commit hook runs this automatically) |


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

One function per file. The `.c` file contains only the `// FUNCTION:` marker and
the C source — all volatile metadata lives in `rebrew-functions.toml`:

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

`rebrew-functions.toml` (in the same directory, managed by CLI tools):

```toml
["SERVER.0x10003da0"]
size = 160
status = "RELOC"
```

The function name and symbol are derived automatically from the C function
definition (e.g. `alloc_game_object` → symbol `_alloc_game_object`).
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

### In `rebrew-functions.toml` (sidecar — managed by CLI tools)

> [!CAUTION]
> Never manually edit `rebrew-functions.toml`. It is managed by `rebrew promote`,
> `rebrew match`, `rebrew sync`, etc. Manual edits will be lost.

**Required sidecar fields**: `status`, `size`

**Optional sidecar fields**: `cflags`, `blocker`, `blocker_delta`, `ghidra`, `analysis`, `note`, `source`

**`status` values**:

| Status | Meaning |
|--------|---------|
| `EXACT` | Byte-for-byte identical to target |
| `RELOC` | Identical after masking relocations (typical best) |
| `MATCHING` | Close but structural diffs remain |
| `MATCHING_RELOC` | Very close, 1-5 byte diffs |
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

`rebrew match --diff-only` markers: `==` identical, `~~` relocation diff only,
`**` structural mismatch. Use `--mm` to show only `**` lines.

## Key Directories

| Path | Contents |
|------|----------|
| `src/server.dll/` | Reversed C89 source files |
| `src/server.dll/rebrew-functions.toml` | Function metadata (status, size, blocker, …) — shared by all subdirs |
| `src/server.dll/rebrew-data.toml` | Data/global metadata (size, section, note) — shared by all subdirs |
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
