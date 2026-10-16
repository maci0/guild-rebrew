# Guild Rebrew

Reconstruct Europa 1400: The Guild as one faithful C89 source tree producing
three byte-identical binaries. See [the objective](goal.md) and
[current work](docs/TODO.md); client whole-image verification remains open.

<!-- progress:start -->
<p align="center">
  <img src="docs/progress.svg" width="715" alt="Decompilation progress. One block per discovered function, in address order. server.dll 509 of 543 functions (exact 232, reloc 274, proven 3, near 2, stub 1, size 3, no size 8, unattempted 20). Europa1400Gold_TL.exe 823 of 5012 game functions (exact 226, reloc 597, near 5, stub 26, size 21, library 1323, unattempted 4137). Europa1400Gold.exe 350 of 4638 functions (exact 96, reloc 254, near 22, stub 78, size 1, error 3, unattempted 4184).">
</p>
<!-- progress:end -->

## Start

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

CL/LINK/LIB run in Docker: `rebrew/msvc:6.0-sp5-win32` for server and
`rebrew/msvc:6.0-sp5-pp-win32` for clients. Gold uses `/ML`/LIBC;
server and TL use `/MT`/LIBCMT. Effective per-target settings live in
`rebrew-project.toml`.

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
