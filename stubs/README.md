# Client comparison builds

Gold and GoldTL link as raw PE32 executables with MSVC maps:

- `build/Europa1400Gold.exe` and `build/Europa1400Gold.map`
- `build/Europa1400Gold_TL.exe` and `build/Europa1400Gold_TL.map`

These are comparison scaffolds, **not playable or byte-identical games**. They
combine recovered sources with explicit placeholder functions and storage.
Placeholder sizes and types do not establish native allocations, layouts or
ownership. The build uses no postlink reference-byte copying or forced
unresolved/duplicate-symbol link.

## Build

The [last full checkpoint](../docs/TODO.md#verified-checkpoint) linked both
clients under unshare and reported compiler warnings. Gold then relinked after
the getter C replacement; later source edits require fresh builds. See
[current work](../docs/TODO.md) for logs and pending checks.

Complete the root [setup steps](../README.md#get-started), then run from the
project root. Supply both client references as
`original/Europa1400Gold.exe` and `original/Europa1400Gold_TL.exe`, and download
the pinned [Miles archive](../references/mss-6.1c/README.md) to
`references/mss-6.1c/mss32.lib`; check its documented SHA-256. These inputs are
ignored by Git. Also build the Processor Pack image using the toolchain
checkout and environment variables from the root setup:

```sh
uv run rebrew toolchain build msvc-6.0-sp5-pp
```

The configured `unshare` backend also applies to CMake's
CL/LINK/LIB commands. Toolchain filenames retain the `-docker.cmake` suffix;
their driver uses the configured backend.

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

Each target has its own `unresolved.txt` input and generated `symbol_stubs.c`.
Gold removes three obsolete video-list placeholders, preserves comparison-only
capacity for six color writes, and includes a generated vertex-buffer pointer
slot. Refresh manifests from current maps before quoting counts. Placeholders
link only into their client and remain outside recovered `src/` and its metadata
accounting.

```sh
uv run rebrew build symbol-stubs --source-dir src \
  --log stubs/gold/unresolved.txt --footer stubs/SCAFFOLD.txt \
  --specials stubs/gold/specials.toml \
  --output stubs/gold/symbol_stubs.c
uv run rebrew build symbol-stubs --source-dir src \
  --log stubs/goldtl/unresolved.txt --footer stubs/SCAFFOLD.txt \
  --specials stubs/goldtl/specials.toml \
  --output stubs/goldtl/symbol_stubs.c
```

The generator uses declarations where available and fallback types otherwise.
For example, `g_slot_table` is a two-byte placeholder, not a recovered client
slot allocation. Named configured library/import providers are excluded;
unbound numeric aliases of library functions can still be placeholders.

When a real provider becomes available, remove its placeholder and regenerate.
Do not link the server's BSS ownership files into these client scaffolds.

Gold also has five generated source-closure placeholders listed in
`gold/source-closure.json`. Four came from the selected MSX fade function; the
vertex-buffer pointer slot came from the recovered getter. These are actual
COFF references absent from the saved unresolved-link log. They do not claim
native storage ownership. After the base command above, append those closure
symbols with the public generator. `g_10405e0[6]` is `specials.g_10405e0`, not
a closure symbol, and the current file places it after the closure marker.
`generate_stubs` emits a special only when that name is also unresolved, so a
marker split that keeps only the prefix drops the six-int capacity. Keep every
non-empty special implementation that the new fragment does not already contain.

```sh
uv run python - <<'PY'
import json, tomllib
from pathlib import Path
from rebrew.gen_stubs import collect_extern_info, generate_stubs
root = Path('stubs/gold')
stub = root / 'symbol_stubs.c'
closure = json.loads((root / 'source-closure.json').read_text())
specials = tomllib.loads((root / 'specials.toml').read_text())
generated = generate_stubs(closure['symbols'], collect_extern_info(Path('src')))
fragment = generated.split('#include <time.h>\n\n', 1)[1].split('/* Function stubs */', 1)[0]
marker = '/* Generated source-closure placeholders; see source-closure.json. */'
head = stub.read_text().split(marker, 1)[0].rstrip()
kept = []
for name, spec in specials.get('specials', {}).items():
    impl = (spec.get('impl') or '').strip()
    if impl and impl not in head and impl not in fragment:
        kept.append(impl)
tail = marker + '\n' + fragment.strip() + '\n'
if kept:
    tail += '\n' + '\n\n'.join(kept) + '\n'
stub.write_text(head + '\n\n' + tail)
PY
```

`gold/symbols.json` is a map snapshot; refresh it with
[`linked_manifest.py`](linked_manifest.py) after a successful link.
Both `specials.toml` files omit an obsolete sound-control function placeholder.
Gold's also omits the three shared video-list functions and preserves the
comparison-only color-array capacity. Empty implementations emit no replacement
function. Keep historical unresolved logs intact and regenerate manifests from each
successful link.

`omitted-sources.cmake` separately lists single-function TUs with colliding C
names: 26 Gold and 5 TL choices. These comparison choices do not prove that
the independent native bodies are equivalent. Their permanent name/provider
repairs remain open. The zlib sample program `minigzip` is also omitted.

Client scaffold builds add no recovered-byte or ownership credit. The separate
[server checkpoint](../docs/TODO.md#verified-checkpoint) passed byte comparison
but failed assembly lint; later edits require a fresh gate.
