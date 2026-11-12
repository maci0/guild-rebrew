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
GoldTL also needs `llvm-ar` and these local DirectX inputs:

- `references/dxsdk8/lib/d3dx8.lib`
- `references/dxsdk8/lib/ddraw.lib`
- `references/dxsdk8/lib/dinput8.lib`
- `references/dxsdk8/lib/d3d8.lib`
- `references/dxsdk8/lib/d3dx8-xpsp1.lib`
- The JPEG/PNG objects under `references/dxsdk8/supp/`

See [SDK provenance](../references/dxsdk8/VENDOR.md). CMake extracts two
objects from the XP SP1 archive and checks these hashes during configuration:

| Input | SHA-256 |
| --- | --- |
| XP SP1 archive | `c02e4fedf3e2e0964a1eed98ca02b28d68a0a7ac184594b04212216253bfbd9d` |
| `obj\i386\cd3dximage.obj` | `d0c91f1bf7550ae39709f738416a48710e75aba61749203d8c7b03d5a07fe592` |
| `obj\i386\jerror.obj` | `e1203fbdc8cb43231d4952b24843030fdd4f332c51e858807bdaf6cbda0516ba` |

The pristine archive stays local and unpatched. Matching a member alone does not
establish original raw-link composition.

## Placeholder stubs

CMake selects `symbol_stubs.c` and `symbol_stubs_extra.c` for each client.
Gold also selects `symbol_stubs_adopted.c` and `symbol_stubs_adopted2.c`.
GoldTL adds `abi_stubs.c`, `data_scaffold.c`, `link_scaffold.c` and the C++
`ctl_locale_stubs.cpp` object. These supply comparison definitions, including
zero-filled globals and empty functions. Their declarations do not establish
native types or allocation sizes. Review all selected scaffold files when a
real provider becomes available.

## Build

```sh
uv run cmake -G "Unix Makefiles" -S . -B build/clients \
  -DCMAKE_TOOLCHAIN_FILE="$PWD/cmake/toolchain-msvc-6.0-sp5-docker.cmake" \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_RUNTIME_OUTPUT_DIRECTORY="$PWD/build" \
  -DREBREW_BUILD_SERVER=OFF \
  -DREBREW_BUILD_GOLD=ON -DREBREW_BUILD_GOLDTL=ON \
  -DREBREW_DEBUG_INFO=OFF
uv run cmake --build build/clients --parallel 2
```

Use a fresh build directory. This writes the EXEs and maps to `build/`, while
objects stay in `build/clients/`. It can replace earlier client images there.

Gold uses `/ML` with LIBC; GoldTL uses `/MT` with LIBCMT. The configured backend runs
CL/LINK/LIB in the pinned images. The historical toolchain filename does not
select Docker execution. GoldTL compiles its resources with a direct Docker
invocation, so that step still needs Docker with the `unshare` backend.

The scaffold's `/OPT:NOREF` retains selected contributions while WinMain is a stub.
It does not establish original retention, providers or successful gameplay.

## Compare

Use the image and map from that build. Pass `--built` because both configured
`raw_link` paths point to `build/consolidation-baseline-pp/`. Status uses those
configured images; these commands compare the images from this recipe.

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
against the target ABI before applying generator output. The commands below
preview the historical inputs without replacing current scaffolds:

```sh
uv run rebrew build symbol-stubs --source-dir src --module GOLD \
  --reference original/Europa1400Gold.exe \
  --log stubs/gold/unresolved.txt --footer stubs/SCAFFOLD.txt \
  --specials stubs/gold/specials.toml --output stubs/gold/symbol_stubs.c --dry-run --json
uv run rebrew build symbol-stubs --source-dir src --module GOLDTL \
  --reference original/Europa1400Gold_TL.exe \
  --log stubs/goldtl/unresolved.txt --footer stubs/SCAFFOLD.txt \
  --specials stubs/goldtl/specials.toml --output stubs/goldtl/symbol_stubs.c --dry-run --json
uv run rebrew build symbol-stubs --source-dir src --module GOLDTL \
  --reference original/Europa1400Gold_TL.exe \
  --log stubs/goldtl/abi-variants.txt --output stubs/goldtl/abi_stubs.c --dry-run --json
```

Checked-in unresolved logs are historical generator inputs, not a current census.
Use a fresh log for current regeneration; do not append misses to an old list.
Remove placeholders as real providers become available. Conflicting decorated
signatures may need separate TUs.

`specials.toml` records explicit comparison capacities/initial values, not recovered
allocations. `omitted-sources.cmake` records collision choices, not native identity.
Do not link server BSS-owner files into client scaffolds.

[linked_manifest.py](linked_manifest.py) reads a successful link map, but counts
only `symbol_stubs.c.obj` and `abi_stubs.c.obj` as scaffold objects. Its count
omits the other scaffold files listed above. Keep any output under ignored
`build/`; do not use that count as a complete scaffold inventory.
