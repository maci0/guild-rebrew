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
and state exchange, then game-command routing. See
[command naming](naming_conventions.md#function-naming) for the `cm_Chk*` and
`cm_Ex*` conventions.

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
| `europa1400-community/europa1400-decompilation` (HTTP 404 on 2026-11-13) | Historical analysis; see our [review](community-research.md) |
| [.NET tools](https://github.com/europa1400-community/Europa1400.Tools) | Asset structures/decoders |
| [Python tools](https://github.com/europa1400-community/europa1400-tools) | Asset conversion |
| [ImHex patterns](https://github.com/europa1400-community/europa1400-imhex) | Binary formats |
| [networkfix](https://github.com/maci0/europa1400-networkfix) | Separate runtime/network work |
| [Lua tools](https://github.com/maci0/europa1400-lua) | In-process analysis |
| [OpenMiles](https://github.com/maci0/openmiles) | Separate audio implementation |

The [archived write-up](goal-history.md#full-notebooks) under this filename
retains detailed native paths, packet cases and older surveys.
