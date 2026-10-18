# Guild Rebrew

**Status: work in progress.** The server has a byte-identical raw build;
**Gold and GoldTL are comparison scaffolds, not playable games.** Source
recovery, unsupported assembly and provider/storage work remain.

A faithful C89 reconstruction of **Europa 1400: The Guild**, targeting the
original MSVC6 toolchains. The [objective](goal.md) is one shared source tree
that produces all three binaries byte for byte.

[Current work](docs/TODO.md) · [Build and compare](stubs/README.md) ·
[Documentation](docs/README.md) · [Reconstruction rules](AGENTS.md)

<!-- progress:start -->
<p align="center">
  <img src="docs/progress.svg" width="715" alt="Reconstruction status: stored C function matches, assembly matches and raw-image agreement for all three targets.">
</p>
<!-- progress:end -->

The chart is a dated snapshot of stored verdicts, not a fresh verification run.
Function matches do not imply whole-image completion. The
[last full server checkpoint](docs/TODO.md#verified-checkpoint) passed byte
comparison but failed assembly lint; later edits require fresh checks.

## Get started

Requires Python 3.13+, `uv` and a local [Rebrew checkout](https://github.com/maci0/rebrew)
at `../relumea/repos/rebrew`, relative to this project root. `uv sync` installs
that checkout as an editable dependency; create it before running the commands.

Supply your own game reference binaries under ignored `original/` at the paths
below. The clone does not include the pinned MSVC toolchain images or Miles archive.
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

| Target | Reference path | Build status |
| --- | --- | --- |
| Server | `original/Server/server.dll` | Raw file matches; source-fidelity work remains |
| GoldTL | `original/Europa1400Gold_TL.exe` | Links with placeholders; differs from reference |
| Gold | `original/Europa1400Gold.exe` | Links with placeholders; differs from reference |

## Build and compare

Follow the [client build recipe](stubs/README.md#build) to produce both PEs and
maps under `build/`. These builds support reconstruction and comparison only.
The [server gate](docs/project-principles.md) checks the raw server build,
source consistency and binary agreement.

CL/LINK/LIB use the configured **unshare** runner with pinned image filesystems:
`rebrew/msvc:6.0-sp5-win32` for server and
`rebrew/msvc:6.0-sp5-pp-win32` for clients. Gold uses `/ML`/LIBC;
server and TL use `/MT`/LIBCMT. Effective settings live in `rebrew-project.toml`;
[runner and cache behavior](docs/verify-performance.md) explains execution.

Once built, compare client data without recompiling functions:

```sh
uv run --frozen rebrew verify --data --target Europa1400Gold_TL.exe
uv run --frozen rebrew verify --data --target Europa1400Gold.exe
```

Client comparisons currently report differences. A successful link is not a
passing reconstruction verdict.

## Project map

| Path | Contents |
| --- | --- |
| `src/Develop/` | Shared reconstruction following attested original paths |
| `src/GOLD*.fcn_*.c` | Client bodies awaiting placement or consolidation |
| `stubs/` | Explicit client comparison placeholders and their limits |
| `references/` | Vendor sources, patches and dependency provenance |
| `db/inventory-*.json` | Tracked native function inventories |
| `layout/server.dll/` | Server link ordering, retention inputs and layout metadata |
| `rebrew-*.toml` | Managed reconstruction identities, evidence and configuration |
| `docs/` | Current work, technical references and archived experiments |

Use [existing tooling](docs/tooling-upstream.md) before adding scripts, and
[vendoring rules](docs/vendoring.md) before editing libraries. Rebrew and
Recoverage read canonical project inputs; exported coverage is a snapshot.

<details>
<summary><strong>Server reference provenance</strong></summary>


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

</details>

<details>
<summary><strong>Refresh the status graphic</strong></summary>

The renderer consumes the canonical CLI report; it keeps no separate coverage database.

```sh
uv run --frozen rebrew status --all-targets --json | python3 scripts/progress_svg.py > docs/progress.svg
```

</details>

## License

MIT for project code. Third-party sources retain their own license notices.
