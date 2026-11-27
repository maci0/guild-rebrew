# Build and compare

Build and verify `server.dll` against the original. See
[client comparison builds](../stubs/README.md) for the EXEs and
[current work](TODO.md) for the latest measurements.

## Prerequisites

These commands use Linux x86_64. Install Git, CMake 3.19+, Make, a C compiler,
Docker and util-linux. On Debian/Ubuntu:

```sh
sudo apt-get install git cmake make build-essential docker.io util-linux
```

Install [uv](https://docs.astral.sh/uv/), allow your user to run Docker, then check:

```sh
docker info
unshare --user --map-root-user true
```

The configured compiler backend is `unshare`. Docker prepares its immutable
toolchain filesystems. The runner also needs rootless overlayfs, `openat2`,
`pidfd_open` and `close_range`.
The namespace command alone does not test all requirements. See the
[toolchain guide](https://github.com/maci0/rebrew/blob/main/docs/TOOLCHAIN.md#experimental-unshare-backend).

## Project environment

Clone the repository and create its pinned environment:

```sh
git clone https://github.com/maci0/guild-rebrew.git
cd guild-rebrew
uv sync --frozen
uv run --frozen rebrew --version
```

Run the commands below from the checkout root. `.python-version` selects the
interpreter. `pyproject.toml` and `uv.lock` pin dependencies.

## Reference inputs

Supply your own game files at these ignored paths. These are the reference hashes:

| Path | Bytes | SHA-256 |
| --- | ---: | --- |
| `original/Server/server.dll` | 286,720 | `3cc2ce9049e41ab6d0eea042df4966fbf57e5e27c67fb923e81709d2683609d1` |
| `original/Europa1400Gold_TL.exe` | 2,850,888 | `6fe7a24c93192f6511bc8595eb82fd166db44f6cbeaf7c2f036838f3b6b4af45` |
| `original/Europa1400Gold.exe` | 2,301,952 | `7d1f178f6463ab41f90987451187a93056814293832a5d2c76444dbd087e3ae8` |

Only the DLL is needed for the server recipe. A different hash is a different
reference, even if the filename agrees.

## Prepare compiler images

Clone the toolchain recipes and point Rebrew at them:

```sh
git clone https://github.com/maci0/recompile-toolchains.git ../recompile-toolchains
export REBREW_TOOLCHAINS_DIR="$PWD/../recompile-toolchains"
```

Build the two server images:

```sh
uv run --frozen rebrew toolchain build msvc-6.0-sp5
uv run --frozen rebrew toolchain build msvc-6.0-sp5-crt
```

The server compiles with plain VC6 SP5, `/MT` and LIBCMT. Its link uses the
`msvc-6.0-sp5-crt` image. [Build facts](general-knowledge.md#configured-build)
cover the client compiler/runtime contexts.

The `-docker.cmake` toolchain filename is historical: the driver runs the
configured backend. Its header comment and the gate's recovery hint still say
Docker and use `--toolchain`, which needs CMake 3.21+. The commands below use the
[equivalent](https://cmake.org/cmake/help/latest/manual/cmake.1.html#cmdoption-cmake-toolchain)
`-DCMAKE_TOOLCHAIN_FILE=...`, which works on CMake 3.19.

## Build the server

Use a fresh build directory:

```sh
uv run --frozen cmake -G "Unix Makefiles" -S . -B build/server-example \
  -DCMAKE_TOOLCHAIN_FILE="$PWD/cmake/toolchain-msvc-6.0-sp5-docker.cmake" \
  -DCMAKE_BUILD_TYPE=Release \
  -DREBREW_BUILD_SERVER=ON \
  -DREBREW_BUILD_GOLD=OFF -DREBREW_BUILD_GOLDTL=OFF \
  -DREBREW_DEBUG_INFO=OFF
uv run --frozen cmake --build build/server-example --parallel "$(nproc)"
```

This produces `server.dll` and `server.map` in that directory. Keep each image
with its own map. CMake reads source selection and TU flags through Rebrew.
The server target currently selects `REBREW_LEGACY_SERVER_LAYOUT` through
`rebrew-project.toml`. Successful compilation does not establish byte identity.

## Compare the raw output

```sh
cmp original/Server/server.dll build/server-example/server.dll
sha256sum original/Server/server.dll build/server-example/server.dll
uv run --frozen rebrew verify --target server.dll \
  --built build/server-example/server.dll \
  --data --whole-binary --raw-link --dry-run --json
```

`cmp` exits 0 with no output for identical files. The Rebrew command checks the
existing image without a function compile pass or verdict writes; exit 1 reports
differences. Name the target explicitly because the project defaults to GoldTL.

## Run the server gate

Install the gate's host loader tools on Debian/Ubuntu. The loader
check fails if Wine or `i686-w64-mingw32-gcc` is absent:

```sh
sudo apt-get install wine gcc-mingw-w64-i686
```

The broader [server gate](../scripts/gate.sh) expects the conventional `build/`
tree and also checks functions, lint, toolchain alignment and Wine load/exports.
It also screens GoldTL functions against D3DX8 when that archive is present.
Configure that tree separately with the server options above, replacing
`build/server-example` with `build`. The gate records server verdicts in managed
metadata; run it only while sources are stable:

```sh
uv run --frozen bash scripts/gate.sh
```

A matching server file does not mean every gate check passed. Report the results
separately; see [measurement rules](measure-traps.md).
