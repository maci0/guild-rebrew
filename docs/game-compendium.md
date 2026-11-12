# Game and binary reference

This page covers game context and native architecture. [Build facts](general-knowledge.md)
own compiler evidence; [build instructions](build.md) own reference inputs.
Community descriptions are background, not naming, type or storage evidence.

## Subsystems

Shared sources under `src/Develop/DieGildeAddOn/` cover commands, game logic
and persistence. `src/Develop/Units/` contains engine and runtime interfaces.
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

The server reads `game.ini` sections `General/GamePath` and `Config/Port` beside
the host executable. `ServerMainThread` obtains that path with
`GetModuleFileNameA(0, module_path, 0x104)` in `src/Develop/DieGildeAddOnServer/server.c`.
Community networkfix settings belong to that separate plugin. Its fixes for
partial delivery and would-block handling must not alter a faithful reconstruction.

`ls_LoadSavegameHeader` at 0x10012470 calls the checked VFS reader
`ls_ReadVfsDataChecked` at 0x10012440. Both are in
`src/Develop/DieGildeAddOn/loadsave/loadsave.c`. Logging and allocation labels
are native witnesses; game-guide behavior still needs separate confirmation.

## Assets and research links

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
Detailed native paths, packet cases and older surveys remain in the archive.

## Archived techniques

Original notebook: `docs/game-compendium.md` in the [documentation archive](goal-history.md#full-notebooks).

- Europa 1400: The Guild
- 1. Game identity
- 2. Gameplay (press-attested)
- 3. Editions, versions, executables, patches
- 4. Binaries in this repo (`0x10000000`, `0x10009320`, `0x10009350`)
- 5. Original source tree (attested)
- 6. Architecture (`0x00264264`, `0x100093a0`, `0x10014db0`)
- 7. Network (`0x00264264`, `0x101deb00`, `0x114ffe20`, `0x8004667e`)
- 8. Persistence (save/load) (`0x10012440`, `0x10012470`, `0x100127d0`, `0x100128f0`, `0x10012eb0`, `0x10013230`, `0x10013b10`, `0x10014070`, `0x10014260`)
- 9. Diagnostics (error/logging)
- 10. Memory (m_alloc)
- 11. Files (vfs)
- 12. Assets and engine
- 13. Community ecosystem
- 14. Repo doc map (this checkout)
