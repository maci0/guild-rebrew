# ☕ Guild Rebrew — Europa 1400 Decompilation

Byte-identical C89 source reconstruction of **Europa 1400: The Guild** (`server.dll`).

Uses the [rebrew](../rebrew/) toolchain for compiler-in-the-loop decompilation matching with MSVC6 under Wine.

## Quick Start

```bash
# Install dependencies (pulls in rebrew tooling package)
uv sync

# All rebrew CLI tools work from this directory:
rebrew-next --stats              # overall progress
rebrew-next --origin GAME -n 10  # next GAME functions to tackle
```

## Decompilation Workflow

```bash
# 1. Find a function to work on
rebrew-next --origin GAME -n 10

# 2. Generate a skeleton .c file
rebrew-skeleton 0x10003DA0

# 3. Write C89 source (see AGENTS.md for rules)
#    - Declare ALL variables at block top
#    - No for(int i=...) — declare int i; separately
#    - No // comments (use /* */)

# 4. Test your implementation
rebrew-test src/server_dll/my_func.c --update

# 5. If near-miss, run the GA to auto-search
rebrew-match \
  --cl "wine tools/MSVC600/VC98/Bin/CL.EXE" \
  --inc "tools/MSVC600/VC98/Include" \
  --cflags "/nologo /c /O2 /MT /Gd" \
  --target-exe original/Server/server.dll \
  --target-va 0x10003DA0 --target-size 160 \
  --symbol "_my_func" \
  --seed-c src/server_dll/my_func.c \
  --out-dir run_out --generations 200 --pop 64 -j 16

# 6. Update STATUS in the annotation header based on result
#    EXACT | RELOC | MATCHING | STUB
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
├── src/server_dll/       # Reversed C source files (~400 functions)
├── original/             # Target binaries (gitignored)
├── references/           # Reference source (zlib 1.1.3)
├── tools/                # Vendored MSVC6 compiler toolchain
│   ├── MSVC600/          # CL.EXE, headers, libs
│   └── VC/               # Additional VC headers/libs
├── recoverage/           # Coverage web dashboard
├── archive/              # Old experiments
├── rebrew.toml           # Project configuration
├── reccmp-project.yml    # reccmp configuration
├── CMakeLists.txt        # CMake build for native compilation
└── AGENTS.md             # Full project reference
```

## Targets

| Target | Binary | Status |
|--------|--------|--------|
| `server_dll` | `original/Server/server.dll` | Active (~400 functions reversed) |
| `Europa1400Gold` | `original/Europa1400Gold.exe` | Future |
| `Europa1400Gold_TL` | `original/Europa1400Gold_TL.exe` | Future |

## License

MIT
