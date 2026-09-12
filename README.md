# ☕ Guild Rebrew — Europa 1400 Decompilation

Byte-identical C89 source reconstruction of **Europa 1400: The Guild** (`server.dll`).

Uses the [rebrew](../rebrew/) toolchain for compiler-in-the-loop decompilation matching with MSVC6 under Wine.

## Quick Start

```bash
# Install dependencies (pulls in rebrew tooling package)
uv sync

# All rebrew CLI tools work from this directory:
rebrew todo --json               # prioritized action items
rebrew todo -c start-function --json  # only new functions to start
```

## Decompilation Workflow

```bash
# 1. Find a function to work on
rebrew todo --json

# 2. Generate a skeleton .c file
rebrew skeleton 0x10003DA0

# 3. Write C89 source (see AGENTS.md for rules)
#    - Declare ALL variables at block top
#    - No for(int i=...) — declare int i; separately
#    - No // comments (use /* */)

# 4. Test your implementation (auto-updates STATUS)
rebrew test src/server.dll/my_func.c

# 5. If near-miss, check the diff and try the GA
rebrew diff src/server.dll/my_func.c -m   # structural diffs only
rebrew match src/server.dll/my_func.c --generations 200 --pop-size 64 -j 16  # GA search

# 6. Single-file flag sweep
rebrew match src/server.dll/my_func.c --flag-sweep-only
```

## Compiler Flags by Origin

| Origin | CL flags | Notes |
|--------|----------|-------|
| **GAME** | `/nologo /c /O2 /MT /Gd` | Full optimization, cdecl |
| **MSVCRT/CRT** | `/nologo /c /O1 /MT /Gd` | Size optimization |
| **ZLIB** | `/nologo /c /O2 /MT /Gd` | Matches with /O2 |

## Project Structure

```
guild-rebrew/
├── src/server.dll/       # Reversed C source files (561 functions)
├── original/             # Target binaries (gitignored)
├── references/zlib/      # Reference source (zlib 1.1.3, submodule)
├── db/                   # Coverage data (gitignored)
├── docs/                 # Codegen notes, naming conventions, TODO
├── layout/server.dll/    # Link layout package
├── rebrew-project.toml   # Project configuration
├── reccmp-project.yml    # reccmp configuration
└── AGENTS.md             # Full project reference
```

The MSVC6 compiler is not vendored: every CL.EXE/LINK.EXE call runs through
the `rebrew/msvc:6.0-win32` docker image (see `cmake/toolchain-msvc6-docker.cmake`).

## Documentation

| Document | Description |
|----------|-------------|
| [AGENTS.md](AGENTS.md) | Full project reference for AI agents and contributors |
| [docs/msvc6-c-shapes.md](docs/msvc6-c-shapes.md) | C spellings that compile to the target's exact bytes |
| [docs/msvc6-allocator.md](docs/msvc6-allocator.md) | Register allocation notes |
| [docs/naming_conventions.md](docs/naming_conventions.md) | Original developer naming conventions |
| [docs/TODO.md](docs/TODO.md) | Open work and the .text link shortfall |

## Targets

| Target | Binary | Status |
|--------|--------|--------|
| `server.dll` | `original/Server/server.dll` | Active: 561 functions, 330 byte-exact, verify 278/280 |
| `Europa1400Gold_TL.exe` | `original/Europa1400Gold_TL.exe` | Onboarded: 6335 functions discovered, 10 skeletons, 0 matched |

`original/Europa1400Gold.exe` appears in `reccmp-project.yml` but is not a
rebrew target.

## License

MIT
