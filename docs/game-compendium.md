# Europa 1400: The Guild — Knowledge Compendium

Canonical game facts, binary inventory, and community ecosystem. Binary-derived
claims cite VA / string / doc. Community and press claims cite URLs. Speculative
entries marked as such.

## 1. Game identity

- Title: Europa 1400: The Guild (German: Die Gilde). First of The Guild series.
- Developer: 4HEAD Studios, Hannover. Publisher: JoWooD Productions.
- Design: Lars Martensen. Code: Tobias Severin. Art: Thomas Bömelt.
- Music: Gerhard Ottmer, Christoph Isermann, Lars Martensen (~2h09m, 46 tracks).
- Release: UK 2002-10-18, US 2002-10-30, Windows. Genre: life simulation.
- Expansion (2003-03): Trade, Greediness and Intrigue. Gold Edition (2005-11):
  base + expansion. Nintendo DS port (2009).
- Reception: GameRankings 78.83%, Metacritic 82%. IGN Editors' Choice, PC Action
  Gold Award. 100,000 copies shipped first week (not sold-through).
- Sources: [Wikipedia](https://en.wikipedia.org/wiki/Europa_1400:_The_Guild),
  [Worthplaying facts](https://worthplaying.com/article/2002/10/17/news/6404-europa-1400the-guild-facts-features/).

## 2. Gameplay (press-attested)

- Life sim + realtime + role-play + nonlinear. Full 3D engine, bird's-eye
  camera, zoom, interiors enterable. Left-click select, right-click deselect.
- Self-created protagonist, 12 professions, missions or open-ended sim.
- Dynasty to power/wealth in historic European cities. Multiplayer to 8 players.
- Playable cities: London (easiest), Berlin, Madrid, Nuremberg, Paris, Milan
  (hardest). Game ends ~1800–1815 (end of feudal era framing).
- Professions in three groups (per [C.O.R.E. guide](https://core-rpg.net/articles/the-guild-guide)):
  crafts (alchemy, carpentry, smithing, perfumery, tailoring, masonry), crafts
  with twists (priesthood, taverns, long-distance trade, moneylending,
  vagrancy), rogues/niche (necromancy, thievery, robbery, law service).
- Attributes (0–6 stars): Negotiation, Handicraft, Stealth/Guile, Combat,
  Rhetoric. Heir takes over at death (age 12+); childless death = game over.
- Note: guide-level claims above are press/community, not binary-derived.

## 3. Editions, versions, executables, patches

From [europa1400-database](https://github.com/europa1400-community/europa1400-database):

- Editions: Standard, Gold. Languages: en, de, ru. Distributions: Steam, GOG, retail.
- DRM: none, SecuROM, Steam.
- Versions: v1.01, v1.02, v1.03b, v1.04, v1.05b, v2.01–v2.06.
- Executables: Gilde.exe / Gilde_TL.exe (de standard), GildeGold.exe /
  GildeGold_TL.exe (de gold), Europa1400.exe / Europa1400_TL.exe (en standard),
  Europa1400Gold.exe / Europa1400Gold_TL.exe (en gold).
- Community patches: DDrawCompat (ddraw.dll), Network Fix (networkfix.asi),
  DXVK (d3d9.dll), DxWrapper (d3d8.dll + dxwrapper.dll + dxwrapper.ini,
  `SetPOW2Caps=1`).

## 4. Binaries in this repo

| Binary | Role | Status here |
|---|---|---|
| `original/Server/server.dll` | Dedicated server, game logic | Active reversing target, 283 annotated (of 543 discovered) |
| `original/Europa1400Gold_TL.exe` | T&L client, shared game logic | Active focus, 6335 discovered, 175 annotated |
| `original/Europa1400Gold.exe` | Base client | Validation target, 4638 discovered, 330 annotated |

`server.dll` exports: `Init` (0x10009320), `Exit` (0x10009350). Image base
0x10000000. Exactly 100 imports, 4 DLLs, no `.idata` (IAT at `.rdata` head).
`.text` VirtualSize 0x22846. CRT static LIBCMT, zlib 1.1.3 vendored
(community origins:
[zlib_functions.md](https://github.com/europa1400-community/europa1400-decompilation/blob/main/zlib_functions.md) —
never reverse, links as stock).
Evidence: `docs/general-knowledge.md`, `rebrew-project.toml`.

## 5. Original source tree (attested)

Root `D:\Develop\` (case varies). 14 `__FILE__` paths embedded in server.dll
are authority (`docs/naming_conventions.md` round 937):

```
DieGildeAddOn\auxillary\plant.c, command\command.c, command\lobbycommands.c
DieGildeAddOn\game\aemter.c, alchemistry_logic.c, friedhof_logic.c, sim.c, spiel.c
DieGildeAddOn\loadsave\loadsave.c
DieGildeAddOnServer\server.c
Units\net\broadcast.c, Error\Error.c, m_alloc\m_alloc.c, vfs\vfs.c
```

Client build uses `DieGildeAddOnVc\` (+ `Release\Europa1400Exp_TL.pdb` in TL.exe);
engine `Units\` shared: `d2.v1\GFX.C`, `d3\d3_d3d.c d3_engine.c d3_interface.c
d3_sky.c ts_texture.c`, `d3_tools\d3_tools.c`, `dd_vesa\Dd_vesa.c`, `Msx\msx.c`,
`net\net.c`. This repo's `_c` directory suffixes are NOT attested (split-TU
artefact).

## 6. Architecture

- server.dll: `Init` spawns thread `ServerMainThread` (0x100093a0); reads game.ini;
  `srv_Init` (0x10009d30); loop: accept clients, broadcast status ~3s,
  process commands, send queued, timeouts, sim tick; `Exit` flags shutdown.
  (Community
  [server.dll.md](https://github.com/europa1400-community/europa1400-decompilation/blob/main/server.dll.md)
  uses different names — `srv_GameLoop`, `srv_InitServer` — unverified here;
  tree names above are what `src/server.dll` annotates.)
- Two-phase commands: `cm_Chk*` validate, `cm_Ex*` execute, both
  `int __cdecl f(void* cmd, void* result)` (0 OK, 1 reject/fail).
- Lobby dispatch `lb_ExLobbyServerCommand` (0x10014db0): 7-way switch on
  `*(int*)(msg+0x10)`: 0 Playerlist, 1 LobbyConfig, 2 PlayerHasJoined,
  3 BroadcastStateChange, 4 PlayerRecordBroadcast, 5 EntitySync, 6 route to `cm_`.
- Modules: `cm_` command, `gm_` game/spiel, `lb_` lobby, `ahm_` alchemy,
  `gv_` graveyard, `sim_` citizen sim, `amt_` offices, `ls_` loadsave,
  `plt_` plant, `m_` memory, `vfs_` VFS, `srv_` server. `Error.c` and
  `broadcast.c` have no prefix. Client-only: `ch_ ai_ he_ cut_ d2_ d3_ txt_
  lc_ rd_ sv_ io_ init_ main_ nt_ ob_ gs_ am_`.
- Naming: verbs English, game nouns German (Spieler, Objekt, Gebaeude/Geb, Raum,
  Lagerslot, Wohnsitz, Aemter, Friedhof). Preserve misspellings
  (`gm_ObjectsAvailble`, `gm_SubObjectNoKill` vs `gm_SubObjekt`).
- Seasons `GM_WINTER/SPRING/SUMMER/AUTUMN`, events `HE_SIM_*`, objects
  `ob_*`, commands `cmdt_*` — speculative working names from
  `docs/naming_conventions.md`; no string literal found in server.dll
  (zero hits for `GM_WINTER`, `HE_SIM`, `EINWANDERUNG`). Errors via
  `LogMessageInternal(__FILE__, line,
  "<func>(): msg", severity)` — log prefix is strongest name evidence.

## 7. Network

- TCP Winsock, non-blocking socket, `bind` + `listen` backlog 5. LAN discovery:
  UDP broadcast 255.255.255.255 (`send_broadcast_message`, 0x10001130).
  First client = serving host.
- Original code assumes clean delivery; packet loss / `WSAEWOULDBLOCK` /
  partial send cause "out of sync" / disconnect.
- Fixes: [networkfix](https://github.com/maci0/europa1400-networkfix) (recv→0-byte,
  send retry, `TCP_NODELAY`, reset `ctx[0xE]` in game stream reader, Sleep(30)→1ms
  clamp) and prior
  [HookDLLs](https://github.com/europa1400-community/europa1400-hooks).
- Packet IDs (community
  [network.md](https://github.com/europa1400-community/europa1400-decompilation/blob/main/network.md),
  unverified here): server→client 0x02/0x04/0x08/0x09/0x1E/0x20;
  client→server 0x01/0x02/0x06/0x07/0x08/0x0D/0x0E/0x0F/0x11–0x13/0x1D/0x1E/0x5F–0x61.
- Root-cause detail (per
  [problem-analysis](https://github.com/maci0/europa1400-networkfix/blob/main/docs/problem-analysis.md)):
  packet validator at server.dll RVA 0x3720 sets persistent `ctx[0xE]` error
  flags (-3 checksum, -1 stream) with no recovery; `GetTickCount` sync assumes
  LAN timing; town-data transfer throttled by `Sleep(30)` pump
  (`NETWORKFIX_FASTSYNC` clamps to 1 ms).
- Config: `game.ini` `[Network]` `ServerPath` (fallback `Server\server.dll`),
  port default 2303. Env toggles: `NETWORKFIX_NODELAY`,
  `NETWORKFIX_FASTSYNC`. Version table (SHA256 + hook RVAs) in
  [server-dll-versions](https://github.com/maci0/europa1400-networkfix/blob/main/docs/server-dll-versions.md).

## 8. Community ecosystem

| Repo | What |
|---|---|
| [europa1400-database](https://github.com/europa1400-community/europa1400-database) | Editions/versions/patches/executables YAML + mkdocs |
| [europa1400-decompilation](https://github.com/europa1400-community/europa1400-decompilation) | server.dll outline, function table, network.md (confidence-scored, partly renamed) |
| [Europa1400.Tools](https://github.com/europa1400-community/Europa1400.Tools) | .NET asset tools; structs Ageb Aobj Bgf Gfx Sbf Vector3 |
| [europa1400-tools](https://github.com/europa1400-community/europa1400-tools) | Python asset decode/convert/export: formats ageb aobj baf bgf ed3 gfx ogr sbf txs; converters incl. bgf→gltf/wavefront |
| [europa1400-imhex](https://github.com/europa1400-community/europa1400-imhex) | ImHex patterns: ageb aobj baf bgf cty ed3 form gfx ogr res sbf scr txs |
| [europa1400-hooks](https://github.com/europa1400-community/europa1400-hooks) | HookDLL netfix predecessor (MinHook, Zig) |
| [europa1400-manager](https://github.com/europa1400-community/europa1400-manager) | Manager/launcher (Python project scaffold) |
| [europa1400-docker](https://github.com/europa1400-community/europa1400-docker) | Docker run env (empty repo) |
| [europa1400-network-bridge](https://github.com/europa1400-community/europa1400-network-bridge) | Network bridge (Python spec + package) |
| [europa1400-memory-editor](https://github.com/europa1400-community/europa1400-memory-editor) | Memory editor (x86 C++ DLL injected via LordPE/Cheat Engine) |
| [europa1400-ghidra-mcp](https://github.com/europa1400-community/europa1400-ghidra-mcp) | Ghidra MCP (private) |
| [die-gulde](https://github.com/europa1400-community/die-gulde) | Unity remake homage |
| [networkfix](https://github.com/maci0/europa1400-networkfix) | Supported netfix .asi, harness-tested 15 game-years; docs: architecture, problem-analysis, server-dll-versions, configuration |
| [europa1400-lua](https://github.com/maci0/europa1400-lua) | In-process LuaJIT RE console: 51 modules (memory/code/PE/domain/workflow); catalog candidates all `status="candidate"`, none with verified address; console is OEM code page (German needles = Latin-1 escapes); docs: API, USAGE, EXAMPLES, TROUBLESHOOTING |
| [rebrew](https://github.com/maci0/rebrew) | This repo's decomp toolchain (MSVC6-in-Docker matching) |
| Wiki | [europa1400-wiki.eulenet.io](https://europa1400-wiki.eulenet.io/) (down 2026-09-21, HTTP 502) |

## 9. Repo doc map (this checkout)

- `docs/general-knowledge.md` build/game facts. `docs/naming_conventions.md`
  source tree + attested names. `docs/msvc6-c-shapes.md` C→bytes.
  `docs/msvc6-allocator.md` registers. `docs/codegen-walls.md` dead ends.
  `docs/measure-traps.md` metric lies. `docs/workflow-traps.md` process traps.
  `docs/behavioral-verdicts.md` behavior. `docs/msvc6-link-layout.md` layout.
  `docs/TODO.md` session log. `goal.md` durable objective.
- Community tables use own names/confidence; do not import names without
  confirmed-push string check (`rebrew asm` + literal push).
