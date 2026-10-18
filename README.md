# Guild Rebrew

**Status: unfinished.** The server was raw byte-identical at the recorded
[Goal110 checkpoint](docs/TODO.md#verified-checkpoint); later edits need fresh
checks. Both clients are comparison scaffolds, not playable or byte-identical.
Source recovery, unsupported assembly and provider/storage work remain.

Reconstruct Europa 1400: The Guild as one faithful C89 source tree producing
three byte-identical binaries. See [the objective](goal.md) and
[current work](docs/TODO.md).

<!-- progress:start -->
<p align="center">
  <img src="docs/progress.svg" width="715" alt="Historical function-status snapshot; query rebrew status for current progress.">
</p>
<!-- progress:end -->

## Start

Requires Python 3.13+, `uv` and a local [Rebrew checkout](https://github.com/maci0/rebrew)
at `../relumea/repos/rebrew`, relative to this project root. `uv sync` installs
that checkout as an editable dependency; create it before running the commands.

Supply the game reference binaries under ignored `original/` at the paths below.
The clone does not include the pinned MSVC toolchain images or Miles archive.
See [toolchain setup](https://github.com/maci0/rebrew/blob/main/docs/TOOLCHAIN.md),
[runner requirements](docs/verify-performance.md#runner-and-caches) and the
[Miles input and checksum](references/mss-6.1c/README.md).

```sh
uv sync
uv run --frozen rebrew todo --json
uv run --frozen rebrew status --all-targets --json
```

Check libraries before implementing a function, then use `rebrew skeleton`,
`test` and `diff`. [AGENTS.md](AGENTS.md) and the shipped skills cover the full
workflow. Commands run through the project's pinned environment.

| Target | Reference | Role |
| --- | --- | --- |
| `server.dll` | `original/Server/server.dll` | Server preservation and source fidelity |
| `Europa1400Gold_TL.exe` | `original/Europa1400Gold_TL.exe` | Primary client reconstruction |
| `Europa1400Gold.exe` | `original/Europa1400Gold.exe` | Shared-source validation and unique code |

CL/LINK/LIB use the configured **unshare** runner with pinned image filesystems:
`rebrew/msvc:6.0-sp5-win32` for server and
`rebrew/msvc:6.0-sp5-pp-win32` for clients. Gold uses `/ML`/LIBC;
server and TL use `/MT`/LIBCMT. Effective settings live in `rebrew-project.toml`;
[runner and cache behavior](docs/verify-performance.md) explains execution.

Both client PEs/maps exist for comparison; they contain scaffolds and are not
playable or byte-identical. See [build and compare](stubs/README.md).
The graphic above is a historical snapshot, not live coverage.

## Reference provenance

The authoritative server reference is the untouched GOG Gold DLL, read-only
(`0444`), 286,720 bytes. On 2026-10-02 it was compared directly with
`app/Server/server.dll` from `setup_the_guild_gold_2.0.0.5.exe` and the Steam
Gold v2.06 English international DLL: all three were identical. The GOG-labelled
`gilde-binaries/` directory is a Redump DVD symlink; the installer supplied the
independent provenance check.

```sh
sha256sum --check <<'HASH'
3cc2ce9049e41ab6d0eea042df4966fbf57e5e27c67fb923e81709d2683609d1  original/Server/server.dll
HASH
```

## Layout

| Path | Contents |
| --- | --- |
| `src/Develop/` | Shared reconstruction following attested original paths |
| `src/GOLD*.fcn_*.c` | Client bodies awaiting placement or consolidation |
| `original/` | Reference binaries, ignored |
| `references/` | Pristine vendor releases, patches and generated sources |
| `db/` | Tracked function inventories; optional ignored coverage artifacts |
| `layout/server.dll/` | Native link layout package |
| `docs/` | [Reference map](docs/README.md), current queue and archived history |

Rebrew and Recoverage read canonical project inputs; optional coverage exports
are snapshots. Use [existing tooling](docs/tooling-upstream.md) before adding
scripts, and [vendoring rules](docs/vendoring.md) before editing libraries.

## License

MIT
