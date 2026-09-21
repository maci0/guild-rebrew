# Europa 1400: The Guild — Knowledge Compendium

Canonical game facts, binary inventory, and community ecosystem. Binary-derived
claims cite VA / string / doc. Community and press claims cite URLs. Speculative
entries marked as such. Link health swept round 19, re-swept round 57: all URLs
200 except the private MCP repo (404 for non-members) and the wiki (502,
still down).

## 1. Game identity

- Title: Europa 1400: The Guild (German: Die Gilde). First of The Guild series.
  Spiritual successor to Die Fugger II. Genre per German wiki: economic sim
  ([de](https://de.wikipedia.org/wiki/Die_Gilde)).
- Cities: German-base set per de wiki (Augsburg, Berlin, Dresden, Hannover,
  Köln); international set per C.O.R.E. guide (London/Berlin/Madrid/Nuremberg/
  Paris/Milan). Binaries carry no city list — GOLD.exe holds only `Augsburg`
  (config default `STADT=`) and `_STADTWAPPEN_BERLIN` (crest asset); city data
  ships in game data files, not the exes.
- Developer: 4HEAD Studios, Hannover (later Cranberry Production lineage per
  [lld wiki](https://lld.wikipedia.org/wiki/Europa_1400:_The_Guild)/[Wikidata Q1213047](https://www.wikidata.org/wiki/Q1213047)).
  Publisher: JoWooD Productions. Release-date variants: UK 18 Oct / US 30 Oct /
  25 Oct (uk/en-wikidata/lld) / EU 18 Oct (pl) / domestic Feb 2002 (vi).
- Concept from 1997 (Lars Martensen), dev start autumn 1997, team 2 → 10 by
  spring 2002 ([Wikipedia](https://en.wikipedia.org/wiki/Europa_1400:_The_Guild),
  citing Gamespy interview 12-2002). Founders: Severin + Martensen, autumn 1997;
  late-medieval setting (Reformation, Hundred Years' War; limited historic maps;
  historian/archive consults). €100,000 loan; demo after 1 year; Infogrames deal
  collapsed after FR-office "chaos"; JoWooD signed winter 2001. RU publisher:
  Руссобит-М. Per [ru wiki](https://ru.wikipedia.org/wiki/Europa_1400:_The_Guild).
- Ratings/media: USK 0, PEGI 3+. Languages: German + English. Media:
  CD-ROM/DVD-ROM/download. Controls: keyboard + mouse. Entry at MobyGames
  (bot-walled, 403 on fetch — search "Europa 1400: The Guild" there).
  Official sites (archived): [diegilde.de](https://web.archive.org/web/20161018162253/http://www.diegilde.de/),
  [theguildgame.com](https://web.archive.org/web/20240229175511/https://theguildgame.com/de/).
  Per [de wiki](https://de.wikipedia.org/wiki/Die_Gilde).
- Design: Lars Martensen. Code: Tobias Severin. Art: Thomas Bömelt.
- Music: Gerhard Ottmer, Christoph Isermann, Lars Martensen (~2h09m, 46 tracks).
- Release: UK 2002-10-18, US 2002-10-30, Windows (pl wiki: EU 18 Oct 2002).
  Genre: life simulation (en wiki) / economic sim (de wiki) / strategy+RPG (pl wiki)
  — sources differ, all cited.
- Expansion (2003): Trade, Greediness and Intrigue (de: Gaukler, Gruften und
  Geschütze) — adds Nuremberg + tailor/jester/gravedigger professions + imperial
  politics level. Gold Edition (2005-11): base + expansion.
- Sequels: The Guild 2 (2006-09) + Pirates of the European Seas (2007) + Venice
  (2008) + Renaissance (2010, ex-fan-mod); Gilde 1400 browser (Gameforge,
  2009–2012); Die Gilde DS (2009-04, turn-based not realtime); The Guild 3
  (2022-06-14, GolemLabs→Purple Lamp). Reboot: Die Gilde – Europa 1410
  (Ashborne Games) — official site [theguild.thqnordic.com](https://theguild.thqnordic.com)
  live, Early Access on Steam, Discord active. Per [de wiki](https://de.wikipedia.org/wiki/Die_Gilde)
  + site fetch round 33.
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
- Self-created protagonist, 12 professions / career paths per en wiki
  (fr wiki lists 12 by name; cs wiki counts 8 base + 3 addon = 11 playable,
  C.O.R.E. guide notes 11 creatable of 15 with 4 exclusive via career change;
  server.dll has no profession list — zero hits for smith/tailor/mason/priest/
  tavern/thief; only `alchemistry_logic`/`ahm_ExAllocAlchemist` strings),
  missions or open-ended sim.
- Dynasty to power/wealth in historic European cities. Multiplayer up to 8 players
  ([Wikipedia](https://en.wikipedia.org/wiki/Europa_1400:_The_Guild), citing Gamespot E3 preshow;
  server binary defaults `g_max_players` 2, lobby enforces the passed-in value).
- Playable cities: London (easiest), Berlin, Madrid, Nuremberg, Paris, Milan
  (hardest). Game ends ~1800–1815 (end of feudal era framing).
- Professions in three groups (per [C.O.R.E. guide](https://core-rpg.net/articles/the-guild-guide)):
  crafts (alchemy, carpentry, smithing, perfumery, tailoring, masonry), crafts
  with twists (priesthood, taverns, long-distance trade, moneylending,
  vagrancy), rogues/niche (necromancy, thievery, robbery, law service).
  French wiki names 12 explicitly ([fr](https://fr.wikipedia.org/wiki/Europa_1400_:_Les_Marchands_du_Moyen_%C3%82ge)):
  blacksmith, carpenter, mason, alchemist, perfumer, tavern-keeper, thief, cleric,
  usurer, merchant, brigand, guard — 6 mastery levels each, 3 enterprise tiers
  (e.g. church→abbey→cathedral).
- Noble ranks: serf → citizen → patrician → noble → baron → count (fr wiki).
  Offices (treasurer, judge…) pay monthly wage + perks (bodyguard, tax breaks).
- French city order by difficulty: London, Berlin, Paris, Milan, Madrid (fr wiki
  omits Nuremberg — pre-addon list).
- Launch state: "tout simplement injouable" for 10–20 min sessions until patches
  weeks later; latest known = beta-3 patch, never final (fr wiki) — consistent
  with de wiki's multiplayer verdict and §7 netcode.
- Attributes (0–6 stars): Negotiation, Handicraft, Stealth/Guile, Combat,
  Rhetoric. Heir takes over at death (age 12+); childless death = game over.
  Per [uk wiki](https://uk.wikipedia.org/wiki/Europa_1400:_The_Guild): exactly ONE heir;
  school at 8 (profession), university at 12 (stats); market = supply/demand +
  random events; low Handicraft → hire master (profit drops); titles unlock
  residences/palaces/castles; mastery upgrade every 4 years. Cities (uk, 6):
  Berlin, London, Madrid, Milan, Nuremberg, Paris. Release (uk): 25 Oct 2002.
  Per [vi wiki](https://vi.wikipedia.org/wiki/Europa_1400:_The_Guild): domestic Feb 2002,
  international later; span 1400–1815.
  Time: one game day ages character one year (ru wiki). RU reviews: Igromania
  9.0/10, PlayGround 9.5/10, Absolute Games 75%, Strana Igr 7.0/10; MobyRank 77.
- Action points ([cs wiki](https://cs.wikipedia.org/wiki/Europa_1400:_The_Guild)):
  4/round base, raisable via items, house upgrades, 6th mastery level; spent on
  mastery study, skill training, office powers, firefighting, confession.
  6th skill point costs 12 AB; each skill trains in a house room (study free,
  others must be built, only one fits the starter house). Mastery: 6 levels at
  4 AB each; enterprise upgrade at 3rd and 5th; career switch costs 8 AB.
- Career ([cs wiki](https://cs.wikipedia.org/wiki/Europa_1400:_The_Guild)): starts at
  10,000 gold fortune + 500 gold citizen rights; offices pay yearly income;
  top post sovereign (addon: pope/emperor appointments).
- Platforms per cs wiki: Win 98/ME/2000/XP. Rating ESRB Teen (vs USK 0/PEGI 3).
  Cities per cs wiki: 6 with traits (London short herb distance, Nuremberg
  double area addon-only); professions 8 base + 3 addon (gravedigger, tailor,
  itinerant entertainer) = 11.
- Note: guide-level claims above are press/community, not binary-derived.

## 3. Editions, versions, executables, patches

From [europa1400-database](https://github.com/europa1400-community/europa1400-database):

- Editions: Standard, Gold. Languages: en, de, ru. Distributions: Steam, GOG, retail.
- Steam: [app 39520](https://store.steampowered.com/app/39520/The_Guild_Gold_Edition/),
  publisher now THQ Nordic, release 18 Nov 2002, EN+DE full audio, tags
  Simulation/Strategy, single+multiplayer + Family Sharing, Mostly Positive
  (555 reviews, 73%). Community hub: 249 discussion topics, active (graphics
  mods, T&L fix, multiplayer stability threads). Guides: 12 total incl.
  multiplayer netfix guides, window-mode (`game.ini Bildmodus=DIRECTWINDOW`,
  `show_intro=0` — both keys verified present in GOLD.exe strings round 60),
  thief/smith occupation guides, RU fix collection.
  GOG: [Gold Edition](https://www.gog.com/en/game/the_guild_gold_edition)
  (sku 1207658720, listed 2014-12-19, 4.2/5 over 793 ratings). Humble Store
  also listed (fr wiki).
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
| `original/Server/server.dll` (286,720 bytes) | Dedicated server, game logic | Active reversing target, 283 annotated (of 543 discovered); verify round 55: 281 passed, 264 byte-matched (31 EXACT + 233 RELOC), 2 failed; deliverable residue 8628 bytes, all in `.text` (round 56) |
| `original/Europa1400Gold_TL.exe` (2,850,888 bytes) | T&L client, shared game logic | Active focus, 6335 discovered, 174 annotated |
| `original/Europa1400Gold.exe` (2,301,952 bytes) | Base client | Validation target, 4638 discovered, 330 annotated |

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
are authority (`docs/naming_conventions.md` round 937; re-verified by regex
scan round 52 — exactly 14 distinct hits). The attested-name table
there holds 52 entries (VA + standing: renamed vs already-correct; recount
round 53), each verified
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
  parameter spellings vary per TU in the tree. 69 `cm_` handlers annotated in
  `command_c/`: lifecycle (AllocSpieler/Free/KillSpieler/KillTransporter/
  CreateCitizen/AllocCharacter), property (AllocObjekt/MoveObjekt/SellObjekt/
  ProdObjekt/ClearLagerslot/TransferCurrency), buildings (CreateGeb/
  AllocRaum/DestroyBuilding/SetGebBesitzer/SetGebUpgrade/SetWohnsitz),
  staff (EmployWorker), politics (AssignOffice/ExecuteOffice/JoinLeaveElection/
  ElectionOrTrade), character (ChangeDesire/ChangeAttribute/ChangeBits/
  ChangeFloat/ModifyHealth/ModifyStamina/ModifyStat), system (SimCommand,
  WarEvent, ThemaPredigt, Cutscene, CopyEntityData, SetSyncFlags).
- Subsystems (all in `src/server.dll/DieGildeAddOn/`): `sim_` citizen sim
  (`sim_AdvanceGameClock`, `sim_SetSyncParams`, `sim_PriorityUpdate`;
  `sim_CreateCitizen` 0x10015500); `amt_` offices/elections
  (`amt_ValidateOfficeCandidate`, `amt_ValidateAndAssignOffice`,
  `amt_SwapOfficeHolders`, `amt_fio_LoadAemter/SaveAemter`); `ahm_` alchemy
  (`ahm_ExAllocAlchemist`, `ahm_AllocAhmInfo`); `gv_` graveyard
  (`gv_ExAllocGraveyardWorker`, `gv_AllocGraveyardField`,
  `gv_SpawnEntities`, filter `gv_eval_SlotFrei`); `plt_` plant/zones
  (`plt_SetPlantMap`, `plt_FindRecord`, `plt_CheckZoneAvailability`).
- Game core `gm_` (`spiel.c`, largest module): entity lifecycle
  (`gm_AllocSpieler`, `gm_KillSpieler`, `gm_ChangePlayerIdentityImpl`),
  buildings (`gm_AllocGebaeude`, `gm_AllocRaum`, `gm_CleanupBuildingEntity`,
  `gm_GetBuildingTypeCategory`), objects (`gm_AllocObjekt`, `gm_AddObjekt`,
  `gm_SubObjekt`, `gm_AllocateObjectSlot`, `gm_FreeObjectListRecursive`,
  `gm_ObjectsAvailble`), queries (`gm_FindSlotById`, `gm_FindEntityByOwner`,
  `gm_CheckEntityType`, `gm_CheckInventoryCapacity`, `gm_eval_SlotVoll`,
  `gm_ff_Objekt`), random (`gm_RandomFloat01`, `gm_RandomQuadratic`,
  `gm_RandomStatModifier`).
- Shared types (`src/server.dll/game_structs.h`, sizes compiler-verified):
  `PlayerSlot` (0x264264: flags + id + data), `LinkedNode` (0x43 packed:
  type + entity_id + children + next), `OFFICE_SLOT` (0x18),
  `OFFICE_ROLE_TEMPLATE` (0x18), `EntityQueryRecord` (0xa9 packed, 0x100-entry
  table at `g_entity_ptr`) — distinct from `EntityStruct` (0x21c stride at
  `g_slot_table`). Key globals: `g_current_year` (0x10035880) + clock words,
  `g_file_version` (0x1002D4EC, savegame gate), `g_office_slots` (0x101DE5A0),
  `g_max_players` (0x11764084), `g_tick_rate`, player slots at 0x101DEB00
  (stride 0x264264). Data state round 54: 460 metadata symbols, 250 matched,
  0 mismatched, 210 not-comparable (BSS/imports).
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

## 8. Persistence (save/load)

- Chain in `src/server.dll/DieGildeAddOn/loadsave/`: `ls_LoadSavegameHeader`
  (0x10012470) → `ls_ReadVfsDataChecked` (0x10012440) → `ls_LoadExistingEntities`
  (0x100127d0) → `ls_LoadBuildingEntityState` (0x100128f0) →
  `ls_LoadDynamicEntities` (0x10012eb0) → `ls_LoadEntities` (0x10013230) →
  `ls_LoadTownData` (0x10013b10); pointer fixup `ls_ID2Ptr` (0x10014070);
  network receive `srv_RecvGame` (0x10014260, also logs `LoadGame():`).
- Savegame carries version-gated conditional blocks (community `handleLoad*Data`
  notes); quicksave slot 0 auto-writes daily 6:00, key Q (C.O.R.E. guide).

## 9. Diagnostics (error/logging)

- Unit `Units/Error/Error.c`: `LogMessageInternal(module, line, msg, severity)`,
  `ReportFatalError`, `ReportMessage`, `DispatchLogOutput`,
  `InitializeLogAndErrorHandler`, `ShutdownLogAndErrorHandler`,
  `CrashDumpUnhandledExceptionFilter`, `EmitCrashModuleLine`,
  `GetDebugRecordByIndex`, `AnalyzeInstruction`, `check_memory_protection`.
- Every game function logs via `LogMessageInternal(__FILE__, line,
  "<func>(): msg", severity)` — the log prefix is the strongest name evidence
  (see §6). Crash dumps walk the stack with the Analyzer helpers.

## 10. Memory (m_alloc)

- Unit `Units/m_alloc/m_alloc.c`, snake_case (not `m_VerbNoun`): `m_init(n)`
  sets slot count + table; `m_AllocTracked(size, file:line)` is the tracked
  implementation behind the `m_alloc` macro; `m_FreeTracked`, `m_PoolAlloc`,
  `m_pool_free`, `m_ReportGroupInfo`, `m_ShutdownAllocator`.
- `m_alloc` refuses before `m_init`. Shutdown anomaly string:
  `"[*] Memory-Shutdown-Anomaly: [*]\nUsed %i blocks in %i bytes.\n\n%i"`.
  `m_alloc_debug` is a block-group name (sprintf), not a symbol.

## 11. Files (vfs)

- Unit `Units/vfs/vfs.c`: `vfs_OpenStream`, `vfs_CloseStream`,
  `vfs_FlushAndClose`, `vfs_ReadData`, `vfs_ReadCompressed`, `vfs_GetByte`,
  `vfs_ReadUint32BE`, `vfs_CleanupObject`, `vfs_DestroyEntity`; zlib gzio
  wrappers (`gzread`, `check_header`); shared `gz_stream` (0x64) header lifted
  to `Units/vfs/gz_stream.h`.

## 12. Assets and engine

- Formats (ImHex patterns + Python construct parsers agree): ageb, aobj, baf,
  bgf, cty, ed3, form, gfx, ogr, res, sbf, scr, txs.
- Game data layout (per europa1400-tools `const.py`): `Data/` (`A_Geb.dat`,
  `A_Obj.dat`, `character_names.dat`), `gfx/` (+`Bmp/`, `GroundPlans/`,
  `Maps/`, `Gilde_add_on_german.gfx`), `Resources/` (`animations.bin`,
  `groups.bin`, `objects.bin`, `scenes.bin`, `scripts.bin`,
  `textbin_german.bin`), `Movie/`, `msx/`.
- Renderer: Direct3D 8 (GOLD links d3dx8 statically — 907 `LIBRARY: D3DX8`
  markers in `library_d3dx8.h`, count re-verified round 39; DX8.1 SDK).
  Import census round 40: GOLD.exe 212 imports / 10 DLLs (adds ADVAPI32, DDRAW,
  DINPUT, GDI32, ole32 to server's 4); TL.exe 275 imports / 11 DLLs (DINPUT→
  DINPUT8, adds d3d8). TL has 5 sections (extra D3DX), others 4.
  Audio: Miles (mss32 `_AIL_stream_*`; ASI scan only when audio init succeeds
  per netfix harness). 2D fallback: DirectDraw/VESA (`dd_vesa`).

## 13. Community ecosystem

| Repo | What |
|---|---|
| [europa1400-database](https://github.com/europa1400-community/europa1400-database) | Editions/versions/patches/executables YAML + mkdocs sources (site URL 404 on fetch round 36 — see repo); Discord `discord.gg/jB9HYY8DpT` |
| [europa1400-decompilation](https://github.com/europa1400-community/europa1400-decompilation) | server.dll outline, function table (243 VAs), network.md (confidence-scored, partly renamed); full `server.dll.c` pseudo-C dump (~1 MB). VA reconciliation round 21–22: 127/243 overlap our tree; 59 named-zlib (stock, correctly absent here); ~8 loadsave sub-VAs (0x10012d00–0x100145c0 `handleLoad*Data`) sit inside our wider annotated spans (same inventory artefact as `docs/general-knowledge.md` `command_c` entry); remainder are CRT/IAT-side VAs — candidate import list, names unverified |
| [fuse_file_access_monitor](https://github.com/europa1400-community/fuse_file_access_monitor) | FUSE file-access monitor prototype (fusers+iced), supports asset research |
| [Europa1400.Tools](https://github.com/europa1400-community/Europa1400.Tools) | .NET asset tools (active Sep 2026: async+progress pipeline); asset classes Ageb/Aobj/Baf/BafIni/Bgf/Gfx/Sbf/Texture/Txs; structs cover Ageb (buildings/coords), Bgf (faces/polygons/skeleton/models), Gfx (graphics/shapebanks), Sbf (soundbanks), Aobj, Vector3 |
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

## 14. Repo doc map (this checkout)

- `docs/general-knowledge.md` build/game facts. `docs/naming_conventions.md`
  source tree + attested names. `docs/msvc6-c-shapes.md` C→bytes.
  `docs/msvc6-allocator.md` registers. `docs/codegen-walls.md` dead ends.
  `docs/measure-traps.md` metric lies. `docs/workflow-traps.md` process traps.
  `docs/behavioral-verdicts.md` behavior. `docs/msvc6-link-layout.md` layout.
  `docs/TODO.md` session log. `goal.md` durable objective.
- Community tables use own names/confidence; do not import names without
  confirmed-push string check (`rebrew asm` + literal push).
- Maintenance: annotated counts drift with reversing churn — re-verify with
  `grep -r "FUNCTION: <MARKER>" src/<target> --include="*.c" | wc -l` before
  citing. Link health last swept round 19 (re-sweep when touching URLs).
