# Game and binary reference

This page covers game context and native architecture. [Build facts](general-knowledge.md)
own compiler evidence; [build instructions](build.md) own reference inputs.
Community descriptions are background, not naming, type or storage evidence.

## Editions and subsystems

4HEAD Studios developed Europa 1400 for JoWooD. Gold combines the base game with
Trade, Greediness and Intrigue. English and German executable names differ; the TL
variant uses hardware transform and lighting.

The clients use Direct3D 8/D3DX8, a DirectDraw fallback and Miles audio. Gold uses
DirectInput 7; GoldTL uses DirectInput 8. Shared game modules cover entities,
commands, simulation, offices, alchemy, graveyards, plants and persistence.
The [naming guide](naming_conventions.md) owns module prefixes.

## Server flow

Init at 0x10009320 starts ServerMainThread at 0x100093a0. The thread configures the
server, accepts clients, processes commands, sends queues, handles timeouts and
ticks simulation. Exit at 0x10009350 signals shutdown.

The lobby dispatcher at 0x10014db0 reads message+0x10 values 0-6 for player/config
and state exchange, then game-command routing. `cm_Chk*` generally validates and
`cm_Ex*` executes; recover each function's actual result convention.

## Network and persistence

Native networking uses nonblocking TCP Winsock and UDP discovery. FIONBIO is
0x8004667e and listen backlog is 5. Discovery broadcasts to 255.255.255.255;
announcements use timeGetTime and sync uses GetTickCount. The main loop sleeps
30 ms. Host selection uses player flag 0x400, not connection order.

The server reads game.ini General/GamePath and Config/Port beside its module.
Community networkfix settings belong to that separate plugin. Its fixes for
partial delivery and would-block handling must not alter a faithful reconstruction.

The save/load chain starts at ls_LoadSavegameHeader 0x10012470, then the checked VFS
reader 0x10012440 and entity/building/town loaders. Logging and allocation labels
are native witnesses; game-guide behavior still needs separate confirmation.

## Assets and research links

Known formats include ageb, aobj, baf, bgf, cty, ed3, form, gfx, ogr, res, sbf,
scr and txs. Data paths include Data, gfx, Resources, Movie and msx.

| Resource | Research use |
| --- | --- |
| [Edition database](https://github.com/europa1400-community/europa1400-database) | Build/version metadata |
| [Community reconstruction](https://github.com/europa1400-community/europa1400-decompilation) | Independent analysis; see our [review](community-research.md) |
| [.NET tools](https://github.com/europa1400-community/Europa1400.Tools) | Asset structures/decoders |
| [Python tools](https://github.com/europa1400-community/europa1400-tools) | Asset conversion |
| [ImHex patterns](https://github.com/europa1400-community/europa1400-imhex) | Binary formats |
| [networkfix](https://github.com/maci0/europa1400-networkfix) | Separate runtime/network work |
| [Lua tools](https://github.com/maci0/europa1400-lua) | In-process analysis |
| [OpenMiles](https://github.com/maci0/openmiles) | Separate audio implementation |

These are research links, not claims about current service health or completeness.
Detailed native paths, packet cases and older surveys are indexed below.

## Archived findings

<details>
<summary>Historical sections and address lookup</summary>

The [November 5 archive](archive/2026-11-05-documentation.tar.xz) preserves the full
`docs/game-compendium.md` notebook, including corrections and receipt paths. Entries below locate
historical claims, not current instructions or verdicts. Hex values include
code/data addresses and constants.

```sh
tar -xOf docs/archive/2026-11-05-documentation.tar.xz docs/game-compendium.md | less
```

| Historical section | Referenced hex values |
| --- | --- |
| <a id="europa-1400-the-guild"></a>Europa 1400: The Guild | - |
| <a id="1-game-identity"></a>1. Game identity | - |
| <a id="2-gameplay-press-attested"></a>2. Gameplay (press-attested) | - |
| <a id="3-editions-versions-executables-patches"></a>3. Editions, versions, executables, patches | - |
| <a id="4-binaries-in-this-repo"></a>4. Binaries in this repo | `0x10000000`, `0x10009320`, `0x10009350` |
| <a id="5-original-source-tree-attested"></a>5. Original source tree (attested) | - |
| <a id="6-architecture"></a>6. Architecture | `0x264264`, `0x100093a0`, `0x10014db0` |
| <a id="7-network"></a>7. Network | `0x264264`, `0x101deb00`, `0x114ffe20`, `0x8004667e` |
| <a id="8-persistence-saveload"></a>8. Persistence (save/load) | `0x10012440`, `0x10012470`, `0x100127d0`, `0x100128f0`, `0x10012eb0`, `0x10013230`, `0x10013b10`, `0x10014070`, `0x10014260` |
| <a id="9-diagnostics-errorlogging"></a>9. Diagnostics (error/logging) | - |
| <a id="10-memory-m_alloc"></a>10. Memory (m_alloc) | - |
| <a id="11-files-vfs"></a>11. Files (vfs) | - |
| <a id="12-assets-and-engine"></a>12. Assets and engine | - |
| <a id="13-community-ecosystem"></a>13. Community ecosystem | - |
| <a id="14-repo-doc-map-this-checkout"></a>14. Repo doc map (this checkout) | - |

</details>
