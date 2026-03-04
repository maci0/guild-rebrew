# AGENTS.md — guild-rebrew

## Overview

Workspace for reversing Europa 1400: The Guild `server.dll` using the `rebrew`
toolchain. Contains original binaries, ~330 reversed C89 source files in
`src/server.dll/`, MSVC6 toolchain under Wine, and project config in `rebrew-project.toml`.

**Not a Python package.** Install tooling from sibling dirs:

```bash
uv pip install -e ../rebrew && uv pip install -e ../recoverage
```

## Build / Test / Lint Commands

Always use `--json` when running these commands as an agent to receive structured, machine-readable output.

```bash
# Test a single reversed file (primary workflow command)
rebrew test src/server.dll/<file>.c --json

# Diff against target binary (side-by-side disassembly)
rebrew match -d src/server.dll/<file>.c --json
rebrew match -d --mm src/server.dll/<file>.c --json   # mismatches only

# Flag sweep (find best compiler flags)
rebrew match -S src/server.dll/<file>.c --json

# GA matching engine (find best flag/code combination)
rebrew match src/server.dll/<file>.c -g 200 -p 64 -j 16 --json

# Batch verify all reversed files
rebrew verify --json

# Lint annotations (checks E001-E017, W001-W015)
rebrew lint src/server.dll/<file>.c --json
rebrew lint --fix src/server.dll/<file>.c    # auto-fix annotation format

# Format C source (pre-commit hook runs this automatically)
clang-format -i --style=file src/server.dll/<file>.c

# Progress / next function to reverse
rebrew next --stats --json
rebrew next --origin GAME --json

# Generate skeleton, update catalog
rebrew skeleton 0x<VA>
rebrew catalog --json
```

All tools read `rebrew-project.toml` for compiler paths, target binary, and flags.
Most tools support `--json` for machine-readable output.
Global flags: `-v` (verbose), `-q` (quiet) apply to all subcommands.

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

One function per file. Annotation header, then externs, then the function:

```c
// FUNCTION: SERVER 0x10003da0
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 160
// CFLAGS: /O2 /Gd
// SYMBOL: _alloc_game_object

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

### Types and Imports

- Primitives: `int`, `char *`, `unsigned int`, `unsigned short`, `unsigned char`
- Local `typedef` per file (no shared headers): `uint32_t`, `uint16_t`, etc.
- Struct definitions are local to each file
- Win32 imports: `__declspec(dllimport)` with `__stdcall`
- Use `#pragma intrinsic(memset)` when compiler must emit inline `rep stosd`

### Inline Assembly

CRT functions that can't compile from C use `__declspec(naked)` with `__asm {}`:

```c
void __declspec(naked) __cdecl local_unwind2(void)
{
    __asm {
        push ebx
        /* ... */
        ret
    }
}
```

## Annotation Reference

**Markers**: `FUNCTION` (game code), `LIBRARY` (CRT/zlib), `STUB` (incomplete)

**Required fields**: `STATUS`, `ORIGIN`, `SIZE`, `CFLAGS`, `SYMBOL` (leading `_` for `__cdecl`)

**STATUS values**:

| Status | Meaning |
|--------|---------|
| `EXACT` | Byte-for-byte identical to target |
| `RELOC` | Identical after masking relocations (typical best) |
| `MATCHING` | Close but structural diffs remain (add `BLOCKER` line) |
| `MATCHING_RELOC` | Very close, 1-5 byte diffs |
| `STUB` | Far off or placeholder |

When STATUS is `MATCHING`, add `// BLOCKER:` explaining the remaining diff:
```c
// BLOCKER: register allocation - target uses ebx/esi/edi, compiler picks differently
```

**Compiler flags by origin** (base `/nologo /c /MT` always prepended):

| Origin | CFLAGS | Notes |
|--------|--------|-------|
| GAME | `/O2 /Gd` | Full optimization, cdecl default |
| MSVCRT | `/O1` | Size optimization |
| ZLIB | `/O2` | Full optimization |

## Diff Output

`rebrew match --diff-only` markers: `==` identical, `~~` relocation diff only,
`**` structural mismatch. Use `--mm` to show only `**` lines.

## Key Directories

| Path | Contents |
|------|----------|
| `src/server.dll/*.c` | Reversed C89 source files (one function each) |
| `original/Server/server.dll` | Target binary (DO NOT MODIFY) |
| `tools/MSVC600/VC98/` | MSVC6 compiler toolchain (via Wine) |
| `references/zlib-1.1.3/` | Exact zlib version used in server.dll |
| `rebrew-project.toml` | Single source of truth for all tool config |

## Common Workflow

1. `rebrew next --origin GAME --json` -- pick a function
2. `rebrew skeleton 0x<VA>` -- generate skeleton `.c` file
3. Write C89 source matching Ghidra decompilation
4. `rebrew test src/server.dll/<file>.c --json` -- compile and compare
5. `rebrew match -d src/server.dll/<file>.c --json` -- inspect diffs
6. Iterate until RELOC or EXACT match
7. `rebrew promote src/server.dll/<file>.c --json` -- test + update STATUS
8. `rebrew catalog --json` -- update catalog

## Knowledge Memory (Cognee MCP)

A local Cognee MCP server is available for persistent project knowledge. Use
the `cognee` tools to store and retrieve discoveries made during reversing.

**When to store** (`cognify` / `save_interaction`):
- Identified purpose of a global variable (e.g. `g_10030b6c` is the connection pool)
- Discovered struct layouts or calling conventions
- Mapped relationships between functions
- Noted patterns in compiler output or flag behavior

**When to search** (`search`):
- Before reversing a new function, check if related globals/structs are documented
- When encountering an unknown global or function reference
- To recall prior analysis of similar code patterns

**Start the server** (separate terminal): `./scripts/cognee-start.sh`
