# Client comparison builds

Gold and GoldTL recipes compile recovered C with explicit placeholder functions
and storage. They are **comparison scaffolds, not playable or byte-identical
games**. Placeholder sizes and types do not establish native allocations,
layouts or ownership. No postlink reference-byte copying is used.

## Build

As of 2026-10-31, GoldTL links with **no duplicate or unresolved-symbol
diagnostics**, without `/FORCE:MULTIPLE`. Its imports match the reference;
its configured image and map are under `build-goldtl-audit/`. Gold's latest
full build compiled but failed to link on 283 unresolved symbols, with no
duplicate-symbol diagnostics;
its older `build/Europa1400Gold.exe` and map are historical. Later isolated
provider probes are not a successful full link. See
[current work](../docs/TODO.md#working-checkpoint-2026-10-31) for hashes,
comparison evidence and outstanding blockers. Neither build is an acceptance
result for the [objective](../goal.md).

Complete the root [setup steps](../README.md#get-started), then run from the
project root. Use this checkout's `.venv` (`uv sync`). No sibling Rebrew
checkout is required. Supply both client references as
`original/Europa1400Gold.exe` and `original/Europa1400Gold_TL.exe`, and download
the pinned [Miles archive](../references/mss-6.1c/README.md) to
`references/mss-6.1c/mss32.lib`; check its documented SHA-256. These inputs are
ignored by Git. Client profiles are `msvc-6.0-sp5-pp`. Build that image from
the public toolchain checkout and environment variables in the root setup.

GoldTL also needs the local DirectX SDK libraries and supplementary objects
selected in `CMakeLists.txt`. Its image-loader member comes from the pristine
XP SP1 archive supplied at `references/dxsdk8/lib/d3dx8-xpsp1.lib`:

| Input | SHA-256 |
| --- | --- |
| XP SP1 archive | `c02e4fedf3e2e0964a1eed98ca02b28d68a0a7ac184594b04212216253bfbd9d` |
| Extracted `obj\i386\cd3dximage.obj` | `d0c91f1bf7550ae39709f738416a48710e75aba61749203d8c7b03d5a07fe592` |
| Extracted `obj\i386\jerror.obj` | `e1203fbdc8cb43231d4952b24843030fdd4f332c51e858807bdaf6cbda0516ba` |

Configure checks these hashes and extracts the members with `llvm-ar`. The archive
is a required local input and stays ignored; it is never patched or committed.
Native JPEG/PNG call destinations support this selection over the competing SDK
image loader. A matching archive member alone does not establish raw-link identity.
The error member supplies the loader's `_jpeg_std_error` dependency.

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

The commands above create a separate build tree and write its images/maps to
`build/`. Verification uses each target's configured `raw_link`; TL currently
points elsewhere. Pass `--built` with the image you just produced when comparing
a different tree. Keep older incremental trees separate from frozen baselines.

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
The game `WinMain` definitions remain comparison stubs; Gold's current reviewed
native extent is 1,849 bytes. The CRT supplies the PE startup code.
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

The generated C files are checked in. Installed Rebrew 6.9.0 includes the
[fastcall fix](https://github.com/maci0/rebrew/commit/8bd102e6); the old 5.4.0
regeneration restriction is retired. A newer, unreleased fix rejects ambiguous
conditional callable aliases instead of emitting guessed data. Until released,
review every generated signature and conditional alias against the active
target and provide an explicit ABI-reviewed special; generation is not ABI proof.
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

The checked-in logs include the previously separate Gold source-closure symbols.
They are historical input, not the latest failed Gold link; use a new diagnostic
log before regenerating the complete scaffold. The
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
