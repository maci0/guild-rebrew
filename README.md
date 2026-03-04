# ☕ Guild Rebrew — Europa 1400 Decompilation

Byte-identical C89 source reconstruction of **Europa 1400: The Guild** (`server.dll`).

Uses the [rebrew](../rebrew/) toolchain for compiler-in-the-loop decompilation matching with MSVC6 under Wine.

## Quick Start

```bash
# Install dependencies (pulls in rebrew tooling package)
uv sync

# All rebrew CLI tools work from this directory:
rebrew next --stats              # overall progress
rebrew next --origin GAME -n 10  # next GAME functions to tackle
```

## Decompilation Workflow

```bash
# 1. Find a function to work on
rebrew next --origin GAME -n 10

# 2. Generate a skeleton .c file
rebrew skeleton 0x10003DA0

# 3. Write C89 source (see AGENTS.md for rules)
#    - Declare ALL variables at block top
#    - No for(int i=...) — declare int i; separately
#    - No // comments (use /* */)

# 4. Test your implementation
rebrew test src/server.dll/my_func.c

# 5. If near-miss, check the diff and try the GA
rebrew match -d src/server.dll/my_func.c     # byte diff
rebrew match src/server.dll/my_func.c -g 200 -p 64 -j 16  # GA search

# 6. Promote: test + auto-update STATUS annotation
rebrew promote src/server.dll/my_func.c
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
├── src/server.dll/       # Reversed C source files (~147 functions)
├── original/             # Target binaries (gitignored)
├── references/           # Reference source (zlib 1.1.3)
├── tools/                # Vendored MSVC6 compiler toolchain
│   ├── MSVC600/          # CL.EXE, headers, libs
│   └── VC/               # Additional VC headers/libs
├── db/                   # Coverage data (coverage.db, JSONs)
├── docs/                 # User stories & workflow docs
├── archive/              # Old experiments
├── rebrew-project.toml           # Project configuration
├── reccmp-project.yml    # reccmp configuration
└── AGENTS.md             # Full project reference
```

## Documentation

| Document | Description |
|----------|-------------|
| [AGENTS.md](AGENTS.md) | Full project reference for AI agents and contributors |
| [docs/USER_STORIES.md](docs/USER_STORIES.md) | Workspace-specific user stories with workflow diagrams |
| [handoff.md](handoff.md) | Session handoff context and pending tasks |

## Targets

| Target | Binary | Status |
|--------|--------|--------|
| `server_dll` | `original/Server/server.dll` | Active (~400 functions reversed) |
| `Europa1400Gold` | `original/Europa1400Gold.exe` | Future |
| `Europa1400Gold_TL` | `original/Europa1400Gold_TL.exe` | Future |

## License

MIT
