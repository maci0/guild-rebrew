# Europa 1400: The Guild — Knowledge Compendium

Canonical game facts, binary inventory, and community ecosystem. Binary-derived
claims cite VA / string / doc. Community and press claims cite URLs. Speculative
entries marked as such. Link health swept round 19: all URLs 200 except the
private MCP repo (404 for non-members) and the wiki (502).

## 1. Game identity

- Title: Europa 1400: The Guild (German: Die Gilde). First of The Guild series.
  Spiritual successor to Die Fugger II. Genre per German wiki: economic sim
  ([de](https://de.wikipedia.org/wiki/Die_Gilde)).
- German-base cities: Augsburg, Berlin, Dresden, Hannover, Köln (vs international
  London/Madrid/Milan/Nuremberg/Paris set — editions differ; both lists cited).
- Developer: 4HEAD Studios, Hannover. Publisher: JoWooD Productions.
- Concept from 1997 (Lars Martensen), dev start autumn 1997, team 2 → 10 by
  spring 2002 ([Wikipedia](https://en.wikipedia.org/wiki/Europa_1400:_The_Guild),
  citing Gamespy interview 12-2002).
- Ratings/media: USK 0, PEGI 3+. Languages: German + English. Media:
  CD-ROM/DVD-ROM/download. Controls: keyboard + mouse. Entry at MobyGames
  (bot-walled, 403 on fetch — search "Europa 1400: The Guild" there).
  Official sites (archived): [diegilde.de](https://web.archive.org/web/20161018162253/http://www.diegilde.de/),
  [theguildgame.com](https://web.archive.org/web/20240229175511/https://theguildgame.com/de/).
  Per [de wiki](https://de.wikipedia.org/wiki/Die_Gilde).
- Design: Lars Martensen. Code: Tobias Severin. Art: Thomas Bömelt.
- Music: Gerhard Ottmer, Christoph Isermann, Lars Martensen (~2h09m, 46 tracks).
- Release: UK 2002-10-18, US 2002-10-30, Windows. Genre: life simulation (en wiki)
  / economic sim (de wiki: Wirtschaftssimulation) — sources differ, both cited.
- Expansion (2003): Trade, Greediness and Intrigue (de: Gaukler, Gruften und
  Geschütze) — adds Nuremberg + tailor/jester/gravedigger professions + imperial
  politics level. Gold Edition (2005-11): base + expansion.
- Sequels: The Guild 2 (2006-09) + Pirates of the European Seas (2007) + Venice
  (2008) + Renaissance (2010, ex-fan-mod); Gilde 1400 browser (Gameforge,
  2009–2012); Die Gilde DS (2009-04, turn-based not realtime); The Guild 3
  (2022-06-14, GolemLabs→Purple Lamp). Reboot: Die Gilde – Europa 1410
  (Ashborne Games, announced 2026). Per [de wiki](https://de.wikipedia.org/wiki/Die_Gilde).
- Multiplayer at release "unreif": bugs blocked internet play, JoWooD dropped
  support months after the addon (de wiki) — matches the netcode findings in §7.
- Reception: GameRankings 78.83%, Metacritic 82% ("generally favorable"). IGN
  Editors' Choice ("fascinatingly different, complex and addictive"), PC Action
  Gold Award. Gamespot 2nd-best PC game Jan 2003. Electric Playground 2002 Best
  Sim nominee (lost to MechWarrior 4: Mercenaries). 100,000 copies shipped
  first week (not sold-through).
- Sources: [Wikipedia](https://en.wikipedia.org/wiki/Europa_1400:_The_Guild),
  [Worthplaying facts](https://worthplaying.com/article/2002/10/17/news/6404-europa-1400the-guild-facts-features/).

## 2. Gameplay (press-attested)

- Life sim + realtime + role-play + nonlinear. Full 3D engine, bird's-eye
  camera, zoom, interiors enterable. Left-click select, right-click deselect.
- Self-created protagonist, 12 professions / career paths
  ([Wikipedia](https://en.wikipedia.org/wiki/Europa_1400:_The_Guild); server.dll has no
  profession list — zero hits for smith/tailor/mason/priest/tavern/thief;
  only `alchemistry_logic`/`ahm_ExAllocAlchemist` strings), missions or
  open-ended sim.
- Dynasty to power/wealth in historic European cities. Multiplayer up to 8 players
  ([Wikipedia](https://en.wikipedia.org/wiki/Europa_1400:_The_Guild), citing Gamespot E3 preshow;
  server binary defaults `g_max_players` 2, lobby enforces the passed-in value).
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
| `original/Europa1400Gold_TL.exe` | T&L client, shared game logic | Active focus, 6335 discovered, 174 annotated |
| `original/Europa1400Gold.exe` | Base client | Validation target, 4638 discovered, 330 annotated |

`server.dll` exports: `Init` (0x10009320), `Exit` (0x10009350). Image base
0x10000000. Exactly 100 imports, 4 DLLs (KERNEL32, USER32, WS2_32, WINMM),
no `.idata` (IAT at `.rdata` head). `.text` VirtualSize 0x22846.
Round-10 independent PE re-parse confirms: 4 sections (.text/.rdata/.data/.reloc),
100 imports, base, both exports. CRT static LIBCMT, zlib 1.1.3 vendored
(community origins:
[zlib_functions.md](https://github.com/europa1400-community/europa1400-decompilation/blob/main/zlib_functions.md) —
never reverse, links as stock). Compiler MSVC6 (`/O2 /Gd` project-wide;
SP6 confirmed, three per-file `-sp5-pp` pins; nine local images collapse to
three real stops: base group, `-sp5-pp`, `-sp6`).
Evidence: `docs/general-knowledge.md`, `rebrew-project.toml`.

## 5. Original source tree (attested)

Root `D:\Develop\` (case varies). 14 `__FILE__` paths embedded in server.dll
are authority (`docs/naming_conventions.md` round 937). The attested-name table
there holds ~50 entries (VA + standing: renamed vs already-correct), each verified
by confirmed literal push, not RevEng attribution alone:

```
DieGildeAddOn\auxillary\plant.c, command\command.c, command\lobbycommands.c
DieGildeAddOn\game\aemter.c, alchemistry_logic.c, friedhof_logic.c, sim.c, spiel.c
DieGildeAddOn\loadsave\loadsave.c
DieGildeAddOnServer\server.c
Units\net\broadcast.c, Error\Error.c, m_alloc\m_alloc.c, vfs\vfs.c
```

Client build uses `DieGildeAddOnVc\` (TL.exe embeds exactly 3 `D:\develop\`
paths, verified by regex scan: `DieGildeAddOnVc\Release\Europa1400Exp_TL.pdb`
via NB10 debug header, `units\Msx\msx.c`, `units\net\net.c`). GOLD.exe embeds
10 paths (verified same way): `Units\d2.v`, `Units\d3\d3_d3d.c`,
`Units\d3\d3_engine.c`, `Units\d3\d3_interface.c`, `Units\d3\d3_sky.c`,
`Units\d3\ts_texture.c`, `Units\d3_tools\d3_tools.c`,
`Units\dd_vesa\Dd_vesa.c`, `units\Msx\msx.c`, `units\net\net.c`.
(`d2.v1\GFX.C` per naming doc reads as the truncated `Units\d2.v` hit.)
This repo's `_c` directory suffixes are NOT attested (split-TU artefact).

## 6. Architecture

- server.dll: `Init` spawns thread `ServerMainThread` (0x100093a0); reads game.ini;
  `srv_Init` (0x10009d30); loop: accept clients, broadcast status ~3s,
  process commands, send queued, timeouts, sim tick; `Exit` flags shutdown.
  (Community
  [server.dll.md](https://github.com/europa1400-community/europa1400-decompilation/blob/main/server.dll.md)
  uses different names — `srv_GameLoop`, `srv_InitServer` — unverified here;
  tree names above are what `src/server.dll` annotates.)
- Two-phase commands: `cm_Chk*` validate, `cm_Ex*` execute; handlers return int
  (0 OK, 1 reject/fail), typically `(cmd, result)` pointer pairs — exact
  parameter spellings vary per TU in the tree.
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
- Seasons `GM_*`, events `HE_SIM_*`, objects `ob_*`, commands `cmdt_*` —
  speculative working names from `docs/naming_conventions.md`; only `ob_` /
  `cmdt_` / `pef_` have string hits in server.dll (`ob_MARKTSTAND`,
  `cmdt_ALLOC`, `pef_GELIEBTE`); `GM_WINTER`, `HE_SIM`, `EINWANDERUNG` have
  zero hits. Errors via `LogMessageInternal(__FILE__, line,
  "<func>(): msg", severity)` — log prefix is strongest name evidence.

## 7. Network

- TCP Winsock, non-blocking socket, `bind` + `listen` backlog 5. LAN discovery:
  UDP broadcast 255.255.255.255 (`SendBroadcastPacket`, 0x10001130).
  Host = slot with flag 0x400 (`host_slot_found` scan in `ServerMainThread.c`),
  not "first connected" — community `server.dll.md` says first-connected,
  unverified here.
- Original code assumes clean delivery; packet loss / `WSAEWOULDBLOCK` /
  partial send cause "out of sync" / disconnect.
- Fixes: [networkfix](https://github.com/maci0/europa1400-networkfix) (recv→0-byte,
  send retry, `TCP_NODELAY`, reset `ctx[0xE]` in game stream reader, Sleep(30)→1ms
  clamp) and prior
  [HookDLLs](https://github.com/europa1400-community/europa1400-hooks).
- Packet IDs: tree-verified server→client emissions in `ServerMainThread.c`:
  0x04 + 0x20 (start commands), 0x08 (transfer total) + 0x09 (128-byte chunks),
  0x1E (clock sync struct). Community
  [network.md](https://github.com/europa1400-community/europa1400-decompilation/blob/main/network.md)
  adds client→server IDs and names, unverified here.
- Root-cause detail (per
  [problem-analysis](https://github.com/maci0/europa1400-networkfix/blob/main/docs/problem-analysis.md)):
  packet validator at server.dll RVA 0x3720 sets persistent `ctx[0xE]` error
  flags (-3 checksum, -1 stream) with no recovery; `GetTickCount` sync assumes
  LAN timing; town-data transfer throttled by `Sleep(30)` pump
  (`NETWORKFIX_FASTSYNC` clamps to 1 ms).
- Config: server.dll itself reads `game.ini` keys `General`/`GamePath` and
  `Config`/`Port` beside the module path (`GetPrivateProfileIntA/StringA` in
  `ServerMainThread.c`); `g_max_players` defaults 2, overridable from the
  startup block. The `[Network]` `ServerPath` key + port 2303 belong to the
  networkfix plugin's
  [configuration](https://github.com/maci0/europa1400-networkfix/blob/main/docs/configuration.md),
  not the game binary. Env toggles: `NETWORKFIX_NODELAY`,
  `NETWORKFIX_FASTSYNC`. Version table (SHA256 + hook RVAs) in
  [server-dll-versions](https://github.com/maci0/europa1400-networkfix/blob/main/docs/server-dll-versions.md).

## 8. Community ecosystem

| Repo | What |
|---|---|
| [europa1400-database](https://github.com/europa1400-community/europa1400-database) | Editions/versions/patches/executables YAML + mkdocs |
| [europa1400-decompilation](https://github.com/europa1400-community/europa1400-decompilation) | server.dll outline, function table (243 VAs), network.md (confidence-scored, partly renamed); full `server.dll.c` pseudo-C dump (~1 MB). VA reconciliation round 21–22: 127/243 overlap our tree; 59 named-zlib (stock, correctly absent here); ~8 loadsave sub-VAs (0x10012d00–0x100145c0 `handleLoad*Data`) sit inside our wider annotated spans (same inventory artefact as `docs/general-knowledge.md` `command_c` entry); remainder are CRT/IAT-side VAs — candidate import list, names unverified |
| [fuse_file_access_monitor](https://github.com/europa1400-community/fuse_file_access_monitor) | FUSE file-access monitor prototype (fusers+iced), supports asset research |
| [Europa1400.Tools](https://github.com/europa1400-community/Europa1400.Tools) | .NET asset tools; structs cover Ageb (buildings/coords), Bgf (faces/polygons/skeleton/models), Gfx (graphics/shapebanks), Sbf (soundbanks), Aobj, Vector3 |
| [europa1400-tools](https://github.com/europa1400-community/europa1400-tools) | Python asset decode/convert/export: formats ageb aobj baf bgf ed3 gfx ogr sbf txs; converters incl. bgf→gltf/wavefront |
| [europa1400-imhex](https://github.com/europa1400-community/europa1400-imhex) | ImHex patterns: ageb aobj baf bgf cty ed3 form gfx ogr res sbf scr txs |
| [europa1400-hooks](https://github.com/europa1400-community/europa1400-hooks) | HookDLL netfix predecessor (MinHook, Zig) |
| [europa1400-manager](https://github.com/europa1400-community/europa1400-manager) | Manager/launcher (Python+GUI): modules config/info/license/overview/patch; patch types archive/simple; consumes europa1400-database YAMLs |
| [europa1400-docker](https://github.com/europa1400-community/europa1400-docker) | Docker run env (empty repo) |
| [europa1400-network-bridge](https://github.com/europa1400-community/europa1400-network-bridge) | Asyncio TCP proxy bridge (server/client port-forward roles, GUI+config) |
| [europa1400-memory-editor](https://github.com/europa1400-community/europa1400-memory-editor) | Memory editor (x86 C++ DLL injected via LordPE/Cheat Engine) |
| [europa1400-ghidra-mcp](https://github.com/europa1400-community/europa1400-ghidra-mcp) | Ghidra MCP (private — link 404s for non-members) |
| [die-gulde](https://github.com/europa1400-community/die-gulde) | Unity (6000.0.43f1) remake homage, early development, not yet playable |
| [networkfix](https://github.com/maci0/europa1400-networkfix) | Supported netfix .asi, 15 game-years VPN-stable; headless harness (2 Wine containers, xdotool-driven, A/B baseline via `NETWORKFIX_DISABLE=1`); docs: architecture, problem-analysis, server-dll-versions, configuration |
| [europa1400-lua](https://github.com/maci0/europa1400-lua) | In-process LuaJIT RE console: 51 modules (memory/code/PE/domain/workflow); catalog candidates all `status="candidate"`, none with verified address; console is OEM code page (German needles = Latin-1 escapes); docs: API, USAGE, EXAMPLES, TROUBLESHOOTING |
| [rebrew](https://github.com/maci0/rebrew) | This repo's decomp toolchain (MSVC6-in-Docker matching) |
| [rebrew-toolchains](https://github.com/maci0/rebrew-toolchains) | Standalone legacy-compiler Docker images (MSVC 1.0–11.0, Borland, Watcom, Delphi); MSVC6 image is what `rebrew-cmake-cl` runs through |
| [recoverage](https://github.com/maci0/recoverage) | Coverage dashboard for binary-matching decomp (per-byte .text/.data/.bss grid) |
| [resembl](https://github.com/maci0/resembl) | Assembly similarity search |
| [ghidra-cli](https://github.com/maci0/ghidra-cli) | Headless Ghidra automation (functions/symbols/strings/xrefs) for RE agents |
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
