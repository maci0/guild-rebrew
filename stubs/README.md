# Client comparison builds

Gold and GoldTL build recipes produce raw PE32 executables with MSVC maps:

- `build/Europa1400Gold.exe` and `build/Europa1400Gold.map`
- `build/Europa1400Gold_TL.exe` and `build/Europa1400Gold_TL.map`

These are comparison scaffolds, **not playable or byte-identical games**. They
combine recovered sources with explicit placeholder functions and storage.
Placeholder sizes and types do not establish native allocations, layouts or
ownership. The build uses no postlink reference-byte copying or forced
unresolved/duplicate-symbol link.

## Build

Both clients link successfully as of 2026-10-22. The current raw executables
and same-build maps support data and image comparisons. They remain broken
comparison scaffolds: Gold has 2871 placeholder symbols and GoldTL has 4138
(including seven additional calling-convention variants). No unresolved symbols
or duplicate-provider warnings are forced through the linker. Compiler warnings
and unsupported assembly remain open. See the [status snapshot](../README.md#reconstruction-status)
and [current work](../docs/TODO.md).

Complete the root [setup steps](../README.md#get-started), then run from the
project root. Use this checkout's `.venv` (`uv sync`). No sibling Rebrew
checkout is required. Supply both client references as
`original/Europa1400Gold.exe` and `original/Europa1400Gold_TL.exe`, and download
the pinned [Miles archive](../references/mss-6.1c/README.md) to
`references/mss-6.1c/mss32.lib`; check its documented SHA-256. These inputs are
ignored by Git. Client profiles are `msvc-6.0-sp5-pp`. Build that image from
the public toolchain checkout and environment variables in the root setup.

```sh
uv run rebrew toolchain build msvc-6.0-sp5-pp
```

Docker prepares the image; the configured `unshare` backend executes CMake's
CL/LINK/LIB commands inside its filesystem. No host Wine is used. Generated
toolchain files retain the historical `-docker.cmake` suffix.

```sh
uv run cmake -S . -B build/clients \
  -DCMAKE_TOOLCHAIN_FILE="$PWD/cmake/toolchain-msvc-6.0-sp5-docker.cmake" \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_RUNTIME_OUTPUT_DIRECTORY="$PWD/build" \
  -DREBREW_BUILD_SERVER=OFF \
  -DREBREW_BUILD_GOLD=ON -DREBREW_BUILD_GOLDTL=ON \
  -DREBREW_DEBUG_INFO=OFF
uv run cmake --build build/clients --parallel 2
```

Gold uses Processor Pack `/ML` and `LIBC`; GoldTL uses Processor Pack `/MT`
and `LIBCMT`. The server configuration remains separate. Client `/OPT:NOREF`
retains code and data while the entrypoints are stubs. Remove that temporary
retention setting when the real entrypoint references are recovered.

Older incremental object trees remain under
`.scratch/goal83-gold-build-baseline/build` and
`.scratch/goal83-tl-build-baseline/build`. They have been reconfigured since
Goal83 and are not frozen baselines. The commands above create a separate
build tree.

## Compare

The default target is GoldTL. Name Gold explicitly:

```sh
uv run rebrew verify --data
uv run rebrew verify --data --target Europa1400Gold.exe
```

`verify --data` checks the existing image without a function compile batch.
Add `--functions` for combined source verification, or pass a particular source
file to verify that file alongside the data. Image-only comparisons:

```sh
uv run rebrew verify \
  --target Europa1400Gold.exe --data --whole-binary --raw-link --dry-run --json
uv run rebrew verify \
  --target Europa1400Gold_TL.exe --data --whole-binary --raw-link --dry-run --json
```

Exit 1 reports the scaffolds' expected differences; it is not a passing verdict.
The game `WinMain` definitions remain stubs rather than the native 1,856-byte
bodies; the CRT still supplies the PE startup code.
Use maps from the same build as each image when checking placement.
Data-only verification preserves the function result cache and comparison
baseline; image-only checks do not initialize the compiler runner.

## Regenerate placeholders

Each target has its own `unresolved.txt` and generated `symbol_stubs.c`.
The normalized logs contain one actual diagnostic per unresolved symbol from
a link without placeholder objects. Stock library/import providers remain on
that diagnostic link, so their symbols do not become placeholders. When new
providers are recovered, regenerate from a fresh diagnostic link rather than
appending the new misses to an old stub list.

The generated C files are checked in; ordinary builds work with the project’s
pinned Rebrew. **Regeneration requires the fastcall generator fix on Rebrew
[main fix](https://github.com/maci0/rebrew/commit/8bd102e6).** Rebrew 5.4.0 can emit the wrong calling convention for `@Name@N`.
Conflicting decorations for one C name cannot share a C translation unit:
GoldTL keeps the additional seven signatures in `abi_stubs.c`, generated from
`abi-variants.txt`. These placeholders satisfy link contracts, not native ABI
or implementation evidence.

```sh
uv run rebrew build symbol-stubs --source-dir src \
  --log stubs/gold/unresolved.txt --footer stubs/SCAFFOLD.txt \
  --specials stubs/gold/specials.toml \
  --output stubs/gold/symbol_stubs.c
uv run rebrew build symbol-stubs --source-dir src \
  --log stubs/goldtl/unresolved.txt --footer stubs/SCAFFOLD.txt \
  --specials stubs/goldtl/specials.toml \
  --output stubs/goldtl/symbol_stubs.c
uv run rebrew build symbol-stubs --source-dir src \
  --log stubs/goldtl/abi-variants.txt \
  --output stubs/goldtl/abi_stubs.c
```

The generator uses declarations where available and fallback types otherwise.
Both targets preserve three native initial values in `specials.toml`:
`SonnenstrahlenStartZeit` and `ch_MorphFrameValue` are `-1`; `g_6752a4` is `1`.
These remain comparison placeholders with unresolved original storage owners.
For example, `g_slot_table` is a two-byte placeholder, not a recovered client
slot allocation. Named configured library/import providers are excluded;
unbound numeric aliases of library functions can still be placeholders.

When a real provider becomes available, remove its placeholder and regenerate.
Do not link the server's BSS ownership files into these client scaffolds.

The fresh logs include the previously separate Gold source-closure symbols,
so regeneration no longer needs the old fragment-append recipe. The
`source-closure.json` file remains historical evidence. Specials preserve the
comparison-only six-color and six-record GUI capacities without claiming native
storage ownership.

`gold/symbols.json` is a map snapshot; refresh it with
[`linked_manifest.py`](linked_manifest.py) after a successful link.
Both `specials.toml` files omit an obsolete sound-control function placeholder.
Gold's also omits the three shared video-list functions and the target-mismatched
GUI destructor spelling, and preserves the comparison-only color-array capacity.
Both clients reserve 192 placeholder bytes for the declared six-record GUI view;
this is capacity for the scaffold, not a recovered native allocation or owner.
The recipe lookup now uses its existing shared C provider, so Gold omits its old
numeric placeholder.
Empty implementations emit no replacement
function. Keep historical unresolved logs intact and regenerate manifests from each
successful link.

`omitted-sources.cmake` separately lists single-function TUs with colliding C
names: 26 Gold and 6 TL choices. These comparison choices do not prove that
the independent native bodies are equivalent. Their permanent name/provider
repairs remain open. The zlib sample program `minigzip` is also omitted.

Client scaffold builds add no recovered-byte or ownership credit. The separate
[server checkpoint](../docs/TODO.md#verified-checkpoint) passed byte comparison
but failed assembly lint; later edits require a fresh gate.
