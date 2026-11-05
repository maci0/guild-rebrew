# Client comparison builds

These scaffolds link recovered C with explicit placeholders. They are not playable
or byte-identical clients. Placeholder types and sizes prove neither native ABI
nor storage ownership. [Current work](../docs/TODO.md) owns build status.

## Inputs

Complete the [host/toolchain setup](../docs/build.md) and supply both client
[reference binaries](../docs/build.md#reference-inputs).
The clients use the Processor Pack image:

```sh
uv run rebrew toolchain build msvc-6.0-sp5-pp
```

Supply the pinned [Miles 6.1c archive](../references/mss-6.1c/README.md).
GoldTL also needs the SDK libraries selected in `CMakeLists.txt`, `llvm-ar`, and
`references/dxsdk8/lib/d3dx8-xpsp1.lib`. Configure checks these SDK inputs:

| Input | SHA-256 |
| --- | --- |
| XP SP1 archive | `c02e4fedf3e2e0964a1eed98ca02b28d68a0a7ac184594b04212216253bfbd9d` |
| `obj\i386\cd3dximage.obj` | `d0c91f1bf7550ae39709f738416a48710e75aba61749203d8c7b03d5a07fe592` |
| `obj\i386\jerror.obj` | `e1203fbdc8cb43231d4952b24843030fdd4f332c51e858807bdaf6cbda0516ba` |

The pristine archive stays local and unpatched. Matching a member alone does not
establish original raw-link composition.

## Build

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

Gold uses `/ML` with LIBC; GoldTL uses `/MT` with LIBCMT. The configured backend runs
CL/LINK/LIB in the pinned images. The historical toolchain filename does not
select Docker execution.

The scaffold's `/OPT:NOREF` retains selected contributions while WinMain is a stub.
It does not establish original retention, providers or successful gameplay.

## Compare

Use the image and map from that build. Pass `--built` because the configured
GoldTL `raw_link` points to a different historical build directory.

```sh
uv run rebrew verify --target Europa1400Gold.exe \
  --built build/Europa1400Gold.exe --data --whole-binary --raw-link --dry-run --json
uv run rebrew verify --target Europa1400Gold_TL.exe \
  --built build/Europa1400Gold_TL.exe --data --whole-binary --raw-link --dry-run --json
```

These check existing images without a function compile pass or verdict writes.
Exit 1 reports differences. Add explicit function verification only when needed;
[verification](../docs/verify-performance.md) explains the check scopes.

## Regenerate placeholders

Create a fresh diagnostic link log without placeholder objects, leaving selected
library/import providers on the link. Review signatures and conditional aliases
against the target ABI before applying generator output.

```sh
uv run rebrew build symbol-stubs --source-dir src \
  --log stubs/gold/unresolved.txt --footer stubs/SCAFFOLD.txt \
  --specials stubs/gold/specials.toml --output stubs/gold/symbol_stubs.c
uv run rebrew build symbol-stubs --source-dir src \
  --log stubs/goldtl/unresolved.txt --footer stubs/SCAFFOLD.txt \
  --specials stubs/goldtl/specials.toml --output stubs/goldtl/symbol_stubs.c
uv run rebrew build symbol-stubs --source-dir src \
  --log stubs/goldtl/abi-variants.txt --output stubs/goldtl/abi_stubs.c
```

Checked-in unresolved logs are historical generator inputs, not a current census.
Do not append new misses to an old list. Remove placeholders as real providers
become available. Conflicting decorated signatures may need separate TUs.

`specials.toml` records explicit comparison capacities/initial values, not recovered
allocations. `omitted-sources.cmake` records collision choices, not native identity.
Do not link server BSS-owner files into client scaffolds. Generate link manifests
with [linked_manifest.py](linked_manifest.py) only after a successful link, writing
them under ignored `build/` rather than checking them into Git.
