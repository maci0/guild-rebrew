# Guild Rebrew

C89 reconstruction of Europa 1400: The Guild using the original MSVC6 toolchains.
The [objective](goal.md) is one shared source tree that reproduces the complete
server, GoldTL and Gold reference binaries.

The latest source release is [1.10.0](docs/releases/1.10.0.md). Its rebuilt server
matches all 286,720 reference bytes. Both clients remain incomplete, and the
full project gate still fails. See [current work](docs/TODO.md) for the checks,
limits and next actions.

## Start here

- [Build the server](docs/build.md), including prerequisites and reference input.
- [Build the client comparison scaffolds](stubs/README.md).
- [Find documentation](docs/README.md) or review the [project rules](AGENTS.md).
- [Contribute source or analysis](docs/collaboration.md).

Quick setup after installing the [build prerequisites](docs/build.md#prerequisites):

```sh
git clone https://github.com/maci0/guild-rebrew.git
cd guild-rebrew
uv python install 3.15.1
uv sync
uv run rebrew --version
```

Reference binaries and compiler inputs are local dependencies, not release assets.
Supply your own legally obtained game files. Build and comparison commands are in
[the build guide](docs/build.md).

## Work on a function

```sh
uv run rebrew todo --target Europa1400Gold_TL.exe --json
uv run rebrew source findings 0x<VA> --json
uv run rebrew test path/to/function.c --no-promote --json
```

Check library attribution and native evidence before implementation. GoldTL is
the default target; select `server.dll` or `Europa1400Gold.exe` explicitly.
Metadata stores hold identities and verdicts. Change them through Rebrew's locked
writers, never by hand.

## Project layout

| Path | Purpose |
| --- | --- |
| [src/Develop/](src/README.md) | Shared C reconstruction in attested or explicitly inferred source locations |
| `stubs/` | Client comparison placeholders |
| `references/` | Vendor sources, patches and dependency provenance |
| `db/inventory-*.json` | Native function inventories |
| `layout/` | Link-order and layout inputs |
| `rebrew-*.toml` | Project configuration and managed metadata |
| `docs/` | Build guides, current work and native research |

## Optional dashboard

```sh
uv sync --extra dashboard
uv run --extra dashboard recoverage serve
```

Open http://127.0.0.1:8001/ and stop the server with Ctrl+C. The dashboard reads
local sources, metadata and reference binaries. Stored verdicts may predate edits;
coverage is not gameplay completion or whole-image identity.

## License

Project code is MIT licensed. Third-party sources retain their own notices.

<!-- Section aliases retained for existing links. -->
<a id="1-install-and-check-build-dependencies"></a><a id="2-clone-and-create-the-python-environment"></a><a id="3-supply-the-original-server-dll"></a><a id="4-build-the-compiler-images"></a><a id="5-compile-serverdll-with-cmake"></a><a id="6-compare-the-result-with-the-original"></a><a id="build-and-compare"></a><a id="data-verification"></a><a id="get-started"></a><a id="optional-coverage-dashboard"></a><a id="project-map"></a><a id="reconstruction-status"></a><a id="reference-provenance"></a><a id="work-together"></a>
