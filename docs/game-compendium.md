# Game and binary reference

Addresses on this page refer to the reference `server.dll`. Verify community
findings against the exact game build before adopting names or types.
[Reference inputs](build.md#reference-inputs) · [Compiler evidence](general-knowledge.md)

## Subsystems

Shared sources under `src/Develop/DieGildeAddOn/` cover commands, game logic
and persistence. `src/Develop/Units/` contains engine and runtime interfaces.
The [naming guide](naming_conventions.md) owns module prefixes.
[Source layout](source-layout.md) owns placement.

## Server flow

`Init` (0x10009320) starts `ServerMainThread` (0x100093a0). The thread accepts
clients, processes commands, sends queues, handles timeouts and advances
simulation. When a thread exists, `Exit` (0x10009350) sets the shutdown flag
and waits for it to clear before terminating the thread and closing its handle.
All three are in `src/Develop/DieGildeAddOnServer/server.c`.

`lb_ExLobbyServerCommand` (0x10014db0) reads the integer at `msg + 0x10`.
See `src/Develop/DieGildeAddOn/command/lobbycommands.c`.

| Value | Call |
| --- | --- |
| 0 | `lb_ExPlayerlist` |
| 1 | `lb_ExPlayerReadyStatus` |
| 2 | `lb_ExPlayerHasJoined` |
| 3 | `lb_BroadcastStateChange` |
| 4 | `lb_ExPlayerRecordBroadcast` |
| 5 | `lb_HandleEntitySync` |
| 6 | `cm_RouteCommand` |

See [command naming](naming_conventions.md#function-naming) for the `cm_Chk*`
and `cm_Ex*` conventions.

## Network and persistence

The listen socket is nonblocking TCP. `FIONBIO` is `0x8004667e` and the listen
backlog is 5, both in `srv_Init` in `server.c`. UDP discovery is
sent to `255.255.255.255` by `SendBroadcastPacket` in
`src/Develop/Units/net/broadcast.c`. Announcements use `timeGetTime` and
sync uses `GetTickCount`. The lobby loop sleeps 30 ms (`Sleep(0x1e)`). Host
selection uses player flag `0x400`, not connection order.

The server reads `Config/Port` (default `0x1d6b`) and `General/GamePath` from
`game.ini` beside the host executable. `ServerMainThread` builds that path
with `GetModuleFileNameA(0, module_path, 0x104)`. Community networkfix settings
belong to that separate plugin. Its fixes for partial delivery and would-block
handling must not alter a faithful reconstruction.

`ls_LoadSavegameHeader` at `0x10012470` calls `ls_ReadVfsDataChecked` at
`0x10012440`. Both are in `src/Develop/DieGildeAddOn/loadsave/loadsave.c`.
The client definitions have different addresses. Logging and allocation labels are native witnesses. Game-guide
behavior still needs separate confirmation.

## Assets and research links

| Resource | Research use |
| --- | --- |
| [Edition database](https://github.com/europa1400-community/europa1400-database) | Build and version metadata |
| `europa1400-community/europa1400-decompilation` (HTTP 404 on 2026-11-13) | Historical analysis; [local review](community-research.md) |
| [.NET tools](https://github.com/europa1400-community/Europa1400.Tools) | Asset structures and decoders |
| [Python tools](https://github.com/europa1400-community/europa1400-tools) | Asset conversion |
| [ImHex patterns](https://github.com/europa1400-community/europa1400-imhex) | Binary formats |
| [networkfix](https://github.com/maci0/europa1400-networkfix) | Separate runtime and network work |
| [Lua tools](https://github.com/maci0/europa1400-lua) | In-process analysis |
| [OpenMiles](https://github.com/maci0/openmiles) | Separate audio implementation |

The [archived write-up](goal-history.md#full-notebooks) under this filename
keeps older native paths, packet cases and surveys.
