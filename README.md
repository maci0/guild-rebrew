# ☕ Guild Rebrew: Europa 1400 Decompilation

Byte-identical C89 source reconstruction of **Europa 1400: The Guild** (`server.dll`).

Uses the [rebrew](../rebrew/) toolchain for compiler-in-the-loop decompilation matching with MSVC6 under Wine.

<!-- progress:start -->
<p align="center">
  <img src="docs/progress.svg" width="715" alt="Decompilation progress. One block per discovered function, in address order. server.dll 509 of 543 functions. Europa1400Gold_TL.exe 823 of 5012 game functions. Europa1400Gold.exe 350 of 4638 functions.">
</p>
<!-- progress:end -->

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
#    - No for(int i=...): declare int i; separately
#    - No // comments (use /* */)

# 4. Test your implementation (auto-updates STATUS)
rebrew test src/Develop/<path>/my_func.c

# 5. If near-miss, check the diff and try the GA
rebrew diff src/Develop/<path>/my_func.c -m   # structural diffs only
rebrew match src/Develop/<path>/my_func.c --generations 200 --pop-size 64 -j 16  # GA search

# 6. Single-file flag sweep
rebrew match src/Develop/<path>/my_func.c --flag-sweep-only
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
├── src/Develop/          # Reversed C, mirrors the original D:\Develop tree (all targets)
├── src/GOLD*.fcn_*.c     # Client-only functions with no shared source yet
├── original/             # Target binaries (gitignored)
├── references/zlib/      # Reference source (zlib 1.1.3, submodule)
├── db/                   # Function inventories (tracked), coverage data (ignored)
├── docs/                 # Codegen notes, traps, naming, TODO (map: docs/README.md)
├── layout/server.dll/    # Link layout package
├── rebrew-project.toml   # Project configuration
└── AGENTS.md             # Full project reference
```

The MSVC6 compiler is not vendored: every CL.EXE/LINK.EXE call runs through
a docker image: `rebrew/msvc:6.0-sp5-win32` for the server, `rebrew/msvc:6.0-sp5-pp-win32`
for both clients (see `cmake/toolchain-msvc-6.0-sp5-docker.cmake`).

## Documentation

| Document | Description |
|----------|-------------|
| [AGENTS.md](AGENTS.md) | Full project reference for AI agents and contributors |
| [docs/README.md](docs/README.md) | Which doc answers which question |
| [docs/msvc6-c-shapes.md](docs/msvc6-c-shapes.md) | C spellings that compile to the target's exact bytes, indexed by diff symptom |
| [docs/msvc6-allocator.md](docs/msvc6-allocator.md) | Register allocation notes |
| [docs/codegen-walls.md](docs/codegen-walls.md) | Encodings no C spelling reaches |
| [docs/measure-traps.md](docs/measure-traps.md) | Rulers and tools that gave wrong readings |
| [docs/msvc6-link-layout.md](docs/msvc6-link-layout.md) | Linker and PE layout outside `.text` |
| [docs/general-knowledge.md](docs/general-knowledge.md) | Facts about the original build and toolchain |
| [docs/naming_conventions.md](docs/naming_conventions.md) | Original developer naming conventions |
| [docs/TODO.md](docs/TODO.md) | Open work and the .text link shortfall |

## Targets

| Target | Binary | Role |
|--------|--------|------|
| `server.dll` | `original/Server/server.dll` | Default |
| `Europa1400Gold_TL.exe` | `original/Europa1400Gold_TL.exe` | Active focus |
| `Europa1400Gold.exe` | `original/Europa1400Gold.exe` | Validation |

Game knowledge: [docs/game-compendium.md](docs/game-compendium.md): canonical
compendium (game, binaries, tree, network, community ecosystem).

## License

MIT
