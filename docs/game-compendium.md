# Europa 1400: The Guild

Game and binary context. Native observations are distinguished from community
claims; this is not a live store, version or project-status directory. Detailed
historical surveys and source links remain in the
[archive](goal-history.md#full-notebooks).

## 1. Game identity

4HEAD Studios developed this Windows economic/life simulation for JoWooD.
The 2003 expansion is *Trade, Greediness and Intrigue* (*Gaukler, Gruften und
Geschütze*); Gold combines the base game and expansion. Historical background:
[Wikipedia](https://en.wikipedia.org/wiki/Europa_1400:_The_Guild) and
[release features](https://worthplaying.com/article/2002/10/17/news/6404-europa-1400the-guild-facts-features/).

## 2. Gameplay (press-attested)

Guide/press descriptions cover professions, commerce, dynasties, offices,
elections and inheritance in real-time 3D cities, with up to eight players.
Profession counts and city lists vary by edition/source; they are not native
layout evidence. The [C.O.R.E. guide](https://core-rpg.net/articles/the-guild-guide)
provides gameplay detail. Native server default player count is two, overridden
by startup configuration.

## 3. Editions, versions, executables, patches

Standard/Gold editions use localized executable names: `Gilde[Gold][_TL].exe`
in German and `Europa1400[Gold][_TL].exe` in English. The TL variant uses a
hardware transform-and-lighting renderer. Edition/version records belong to
[europa1400-database](https://github.com/europa1400-community/europa1400-database).
Historical store ratings, review totals and link-health checks are archived.

Community compatibility work includes DDrawCompat, DXVK, DxWrapper and
networkfix. Their behavior is separate from the original game being reconstructed.

## 4. Binaries in this repo

| Reference | Role |
| --- | --- |
| `original/Server/server.dll` | Dedicated server; 286,720 bytes |
| `original/Europa1400Gold_TL.exe` | Primary client reconstruction |
| `original/Europa1400Gold.exe` | Shared-source validation and unique client logic |

The server has image base `0x10000000`, four sections, 100 imports across
KERNEL32/USER32/WS2_32/WINMM, `.text` VirtualSize `0x22846`, `Init` at
`0x10009320` and `Exit` at `0x10009350`. The IAT starts `.rdata`; there is no
`.idata`. Reference provenance is in [README.md](../README.md). Compiler/runtime
evidence is in [build facts](general-knowledge.md); current progress in [TODO.md](TODO.md).

## 5. Original source tree (attested)

Embedded paths attest `D:\Develop`, game `DieGildeAddOn`, client
`DieGildeAddOnVc`, dedicated `DieGildeAddOnServer` and shared `Units`.
The server's fourteen path strings cover plant, command/lobby, aemter,
alchemistry, friedhof, sim, spiel, loadsave, server, broadcast, Error,
m_alloc and vfs. Clients additionally attest MSX, net, d2, d3, d3_tools and
dd_vesa. Exact paths and inferred placements belong in
[naming conventions](naming_conventions.md) and [source layout](source-layout.md).
One shared body can have a managed identity per target; old `_c` split names
are reconstruction names.

## 6. Architecture

- `Init` starts `ServerMainThread` (`0x100093a0`): configure, accept clients,
  announce status, process commands, send queues, handle timeouts and tick sim.
  `Exit` signals shutdown.
- `cm_Chk*` validates commands; `cm_Ex*` executes. Typical results are 0 success,
  1 reject/fail, but recover each actual signature and consumer.
- Subsystems: `gm_` game/entities, `sim_` simulation, `amt_` offices/elections,
  `ahm_` alchemy, `gv_` graveyards, `plt_` plants, `ls_` persistence, `lb_` lobby,
  `vfs_` files and `m_` allocation. Error/broadcast lack an attested prefix.
- Lobby `lb_ExLobbyServerCommand` (`0x10014db0`) dispatches message `+0x10`
  values 0–6: player list, configuration, join, state, player record, entity sync,
  then game-command routing.
- Native type extents include player stride `0x264264`, entity stride `0x21c`,
  query stride `0xa9` and 24-byte office slots/templates. Extents and access views
  do not establish ownership. Use canonical headers and stable type bindings.

## 7. Network

Native code uses nonblocking TCP Winsock (`FIONBIO = 0x8004667e`, listen backlog
5), with UDP discovery to `255.255.255.255`. `timeGetTime` gates three-second
announcements; `GetTickCount` drives sync. The loop sleeps 30 ms, with a two-second
pre-start wait. Host is selected by slot flag `0x400`, not connection order.
Player storage starts `0x101deb00`, stride `0x264264`, with admin at `0x114ffe20`.

Server emissions include IDs `0x04`/`0x20` start commands, `0x08` transfer total,
`0x09` 128-byte chunks and `0x1e` clock sync. Community client-packet names require
independent native confirmation. Original send/receive assumptions mishandle
partial delivery and would-block conditions; see the separate
[networkfix analysis](https://github.com/maci0/europa1400-networkfix/blob/main/docs/problem-analysis.md).
Do not import its fixes into a faithful byte reconstruction.

The server reads `game.ini` `General/GamePath` and `Config/Port` beside its module.
`Network/ServerPath`, port 2303 and `NETWORKFIX_*` toggles belong to the plugin's
[configuration](https://github.com/maci0/europa1400-networkfix/blob/main/docs/configuration.md).
Build-specific hook RVAs live in its
[version table](https://github.com/maci0/europa1400-networkfix/blob/main/docs/server-dll-versions.md).

## 8. Persistence (save/load)

Native load chain: `ls_LoadSavegameHeader` `0x10012470` → checked VFS reader
`0x10012440` → existing entities `0x100127d0` → building state `0x100128f0` →
dynamic entities `0x10012eb0` → entities `0x10013230` → town `0x10013b10`.
`ls_ID2Ptr` is `0x10014070`; network receive `srv_RecvGame` is `0x10014260`.
Version-gated blocks and community guide behavior need separate evidence.

## 9. Diagnostics (error/logging)

`Units/Error/Error.c` supplies logging, fatal/report handling and crash analysis.
A confirmed native push of `name(): …` attests a function spelling; an embedded
path attests a unit. Imported decompiler/community names alone do neither.
Retain original line numbers, literal contents and call order.

## 10. Memory (m_alloc)

`Units/m_alloc/m_alloc.c` supplies initialization, tracked allocation/free,
pools, reports and shutdown. Native diagnostics attest snake_case `m_alloc`;
`m_AllocTracked` was an earlier reconstruction name. The allocator requires
initialization. Allocation labels support role/extent evidence but do not always
name a source function.

## 11. Files (vfs)

`Units/vfs/vfs.c` owns stream/file operations; client-only directory-tree work
may be discarded in the server. zlib gzip and minizip are library code. Use
[canonical vendor providers](vendoring.md), not copied CRT/gzip bodies or
historical reconstructed private headers.

## 12. Assets and engine

Known asset formats: ageb, aobj, baf, bgf, cty, ed3, form, gfx, ogr, res, sbf,
scr, txs. Data commonly resides in `Data/`, `gfx/`, `Resources/`, `Movie/` and
`msx/`. Python/.NET tools and ImHex patterns below provide independent decoders.
Clients use Direct3D 8/D3DX8, DirectDraw fallback and Miles audio; input differs
between Gold DirectInput7 and TL DirectInput8. Complete GUID/native-call evidence
belongs in [build facts](general-knowledge.md#native-findings).

## 13. Community ecosystem

Historical research links, without a current availability or completeness claim:

| Resource | Use |
| --- | --- |
| [Database](https://github.com/europa1400-community/europa1400-database) | Edition/version metadata |
| [Decompilation](https://github.com/europa1400-community/europa1400-decompilation) | Independent server outline, pseudo-C and network notes; names/VAs need confirmation |
| [Europa1400.Tools](https://github.com/europa1400-community/Europa1400.Tools) | .NET asset structures and decoders |
| [Python tools](https://github.com/europa1400-community/europa1400-tools) | Asset conversion, including BGF export |
| [ImHex patterns](https://github.com/europa1400-community/europa1400-imhex) | Binary format descriptions |
| [Network bridge](https://github.com/europa1400-community/europa1400-network-bridge) | TCP forwarding experiments |
| [networkfix](https://github.com/maci0/europa1400-networkfix) | Separate runtime compatibility fixes and harness |
| [Lua console](https://github.com/maci0/europa1400-lua) | In-process RE tools; candidate catalog names are not verified addresses |
| [OpenMiles](https://github.com/maci0/openmiles) | Separate Miles-compatible audio project |
| [Rebrew](https://github.com/maci0/rebrew) / [Recoverage](https://github.com/maci0/recoverage) | Reconstruction tooling and coverage views |

The full project/store/community census is archived; counts, ratings and service
health are dated observations, not reconstruction evidence.

## 14. Repo doc map (this checkout)

Use [the documentation map](README.md). Query canonical metadata for live counts;
legacy `FUNCTION:` marker greps are obsolete. Keep native evidence, community
claims, compiler matches and complete image verification distinct.
