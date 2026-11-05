# Naming conventions

Attested diagnostic/path spellings win, including original errors such as
`gm_ObjectsAvailble` and German nouns such as `Objekt`. A semantic role or a
community label does not establish the original name. Mark inferred names.

## Module prefix system

Use an evidenced module prefix. Do not invent one for a unit that lacks it.
Error and broadcast helpers retain unprefixed descriptive names where no original
prefix is attested. A `fio_` infix identifies module file I/O, as in
`amt_fio_LoadAemter`.

| Prefixes | Subsystems |
| --- | --- |
| cm_, gm_, lb_ | Commands, game/entities, lobby |
| ahm_, gv_, sim_, amt_, ls_, plt_ | Alchemy, graveyards, simulation, offices, persistence, plants |
| m_, vfs_, srv_ | Allocation, virtual files, server |
| ch_, ai_, he_, cut_ | Characters, AI, events, cutscenes |
| d2_, d3_, txt_, lc_, rd_ | UI, renderer, text, location, records |
| sv_, io_, init_, main_, nt_, ob_, gs_, am_ | Client state, I/O, startup, main loop, network, objects, court, method registry |

Asset/config prefixes are not automatically function prefixes.

## Function naming

Use `prefix_VerbNoun` for inferred function names, with the original module style.
Keep English verbs and German game nouns where the binary uses them.
`cm_Chk*` usually validates and `cm_Ex*` executes, but recover each actual contract;
the names do not prove its signature or return values.

Use CRT headers for library functions. A private runtime helper's identity does
not make it a game routine or prove a selected archive provider.

## Variable naming

- Preserve attested globals such as `lpGebaeudePROT`, `lpObjekteINST`,
  `gm_ObjektNr2MinimalHersteller` and `cm_LastSyncCount` exactly.
- Inferred module globals use `<module>_CamelCase`. Heap table pointers use `lp`
  plus a German noun and PROT/INST where supported; typed pointers use `tp_`.
- Actual file statics use `s_`. Packet/struct fields use German snake_case.
- Compiler literals have no C source identifier. Their metadata rows use
  `str_<content>`, `flt_<value>` or `dbl_<value>`.
- Keep unresolved address labels and layout-span names until evidence supports a
  name, backing object and owner. Do not create new global `g_` naming conventions.
- Local names are inferred descriptions. Renaming one can still affect compilation
  context, so preserve compiler-sensitive forms until measured.

## Struct naming

Use UPPER_CASE for inferred types. Unknown fields retain offset/unknown labels;
access width or a stride does not prove a complete original type or allocation.

## Enum / constant naming

Follow the attested `prefix_UPPER_SNAKE` style, for example `cmdt_ALLOC_SPIELER`,
`ob_MARKTSTAND` or `HE_SIM_KRANKHEITEN`. Preserve exceptions such as `GM_WINTER`.

## Rename safely

Use `rebrew source rename` with the target-qualified MODULE.0xVA identity where
spelling is ambiguous. Preview scope, providers, callers and linker anchors;
apply the reviewed digest, then verify affected targets. Naming does not earn a
byte verdict. [Source layout](source-layout.md) owns placement guidance.

The index below locates historical attestations and inference limits. Recheck the
current managed binding before using a recorded name or address.


## Archived findings

<details>
<summary>Historical sections and address lookup</summary>

The [November 5 archive](archive/2026-11-05-documentation.tar.xz) preserves the full
`docs/naming_conventions.md` notebook, including corrections and receipt paths. Entries below locate
historical claims, not current instructions or verdicts. Hex values include
code/data addresses and constants.

```sh
tar -xOf docs/archive/2026-11-05-documentation.tar.xz docs/naming_conventions.md | less
```

| Historical section | Referenced hex values |
| --- | --- |
| <a id="original-developer-naming-conventions"></a>Original Developer Naming Conventions | - |
| <a id="recent-findings"></a>Recent findings | - |
| <a id="five-attested-names-settled-against-their-counterparts-2026-10-27"></a>Five attested names settled against their counterparts (2026-10-27) | `0x4bdf40`, `0x4c9340`, `0x4c9550`, `0x4ec520`, `0x5037c0` |
| <a id="animation-loader-name-and-command-filename-2026-10-19"></a>Animation loader name and command filename (2026-10-19) | `0x44c620`, `0x44c688`, `0x44e4a0`, `0x44e508`, `0x4959f0`, `0x5fc278`, `0x67b04c` |
| <a id="scene-loading-declarations-goal80-2026-10-17"></a>Scene loading declarations (Goal80, 2026-10-17) | - |
| <a id="d2-image-argument-slot-goal79-2026-10-17"></a>D2 image argument slot (Goal79, 2026-10-17) | `0x472640`, `0x472770`, `0x475e30`, `0x475f30`, `0xfa6038`, `0x102d158` |
| <a id="cursor-and-dialog-access-views-goal78-2026-10-17"></a>Cursor and dialog access views (Goal78, 2026-10-17) | - |
| <a id="native-crt-rand-and-scene-name-collector-goal77-2026-10-17"></a>Native CRT rand and scene-name collector (Goal77, 2026-10-17) | `0x438d40`, `0x4d2650`, `0x5de784`, `0x62e108`, `0x6f0d60`, `0x930380` |
| <a id="object-transform-animation-wrapper-2026-10-15"></a>Object-transform animation wrapper (2026-10-15) | `0x00412d30` |
| <a id="private-crt-input-helper-2026-10-15"></a>Private CRT input helper (2026-10-15) | `0x005e3a71`, `0x005e899f` |
| <a id="shared-scene-lighting-refresh-2026-10-15"></a>Shared scene lighting refresh (2026-10-15) | `0x450a00`, `0x453890` |
| <a id="shared-solar-effect-stop-2026-10-14"></a>Shared solar-effect stop (2026-10-14) | `0x417150`, `0x4186d0` |
| <a id="shared-sonnenstrahlen-creation-and-reset-2026-10-14"></a>Shared Sonnenstrahlen creation and reset (2026-10-14) | `0x417170`, `0x417190`, `0x4186f0`, `0x418710` |
| <a id="shared-tracked-allocator-and-attested-spelling-2026-10-11"></a>Shared tracked allocator and attested spelling (2026-10-11) | `0x41db70`, `0x4223c0`, `0x10006580` |
| <a id="shared-allocator-shutdown-2026-10-12"></a>Shared allocator shutdown (2026-10-12) | `0x41e0c0`, `0x422910`, `0x10006c00` |
| <a id="shared-tracker-reporting-and-group-layout-2026-10-11"></a>Shared tracker reporting and group layout (2026-10-11) | `0x41df00`, `0x422750`, `0x10006990` |
| <a id="shared-pool-deallocation-2026-10-11"></a>Shared pool deallocation (2026-10-11) | `0x41e2e0`, `0x422b30`, `0x10006e30` |
| <a id="native-msx-and-d3-unit-placement-2026-10-11"></a>Native MSX and D3 unit placement (2026-10-11) | - |
| <a id="shared-worker-housing-action-2026-10-11"></a>Shared worker-housing action (2026-10-11) | - |
| <a id="shared-gui-image-update-2026-10-11"></a>Shared GUI image update (2026-10-11) | - |
| <a id="shared-floor-water-region-fill-2026-10-11"></a>Shared floor-water region fill (2026-10-11) | - |
| <a id="shared-motion-completion-identity-2026-10-11"></a>Shared motion completion identity (2026-10-11) | - |
| <a id="tl-model-motion-preloader-identity-2026-10-11"></a>TL model-motion preloader identity (2026-10-11) | - |
| <a id="recovered-character-queries-and-sound-constructor-2026-10-11"></a>Recovered character queries and sound constructor (2026-10-11) | - |
| <a id="parent-resolver-and-getter-extents-2026-10-11"></a>Parent resolver and getter extents (2026-10-11) | - |
| <a id="shared-statgroup-and-table-entry-helpers-2026-10-11"></a>Shared stat/group and table-entry helpers (2026-10-11) | - |
| <a id="filtered-iterator-identity-correction-2026-10-11"></a>Filtered iterator identity correction (2026-10-11) | - |
| <a id="entity-class-embedded-switch-extents-2026-10-11"></a>Entity-class embedded switch extents (2026-10-11) | - |
| <a id="shared-object-resource-cleanup-2026-10-11"></a>Shared object resource cleanup (2026-10-11) | - |
| <a id="source-tree-layout"></a>Source Tree Layout | - |
| <a id="serverdll"></a>server.dll | `0x1000cb20`, `0x10010526` |
| <a id="europa1400goldexe-main-game-client"></a>Europa1400Gold.exe (main game client) | - |
| <a id="europa1400gold_tlexe-transform--lighting-gpu-pipeline"></a>Europa1400Gold_TL.exe (Transform & Lighting GPU pipeline) | - |
| <a id="attested-original-source-paths-round-937"></a>Attested original source paths (round 937) | `0x4c43c0`, `0x4c4d30`, `0x10001130`, `0x10002640`, `0x10003640`, `0x100036d0`, `0x10003cf0`, `0x10006580`, `0x10006e30`, `0x10008a50`, `0x10008c80`, `0x10008d10`, `0x10009020`, `0x10009310`, `0x1000b040`, `0x1000b1c0`, `0x1000baf0`, `0x1000bd50`, `0x1000c710`, `0x1000ca00`, `0x100104a0`, `0x10010530`, `0x10011bf0`, `0x10012000`, `0x10014260`, `0x100145e0`, `0x10014db0`, `0x10014ee0`, `0x100151b0`, `0x100151e0`, `0x10015690`, `0x100156c0`, `0x1001a110` |
| <a id="merged-source-tree-speculative"></a>Merged Source Tree (speculative) | - |
| <a id="file-naming-patterns"></a>File Naming Patterns | - |
| Module Prefix System | - |
| <a id="game-logic-modules"></a>Game Logic Modules | - |
| <a id="infrastructure-modules-units"></a>Infrastructure Modules (`Units/`) | `0x10001130`, `0x10027144` |
| <a id="client-only-modules-europa1400goldexe"></a>Client-Only Modules (`Europa1400Gold*.exe`) | - |
| <a id="standard-library-functions"></a>Standard Library Functions | - |
| Function Naming | - |
| <a id="pattern-prefix_verbnoun"></a>Pattern: `prefix_VerbNoun` | - |
| <a id="command-module-sub-prefixes"></a>Command Module Sub-Prefixes | - |
| <a id="lobby-command-dispatch"></a>Lobby command dispatch | `0x264210`, `0x100145e0`, `0x100146c0`, `0x1001478a`, `0x100147b0`, `0x10014a50`, `0x10014af0`, `0x10014bf0`, `0x10014ca0`, `0x10014db0`, `0x10014eae`, `0x10014ebc` |
| <a id="verb-vocabulary"></a>Verb Vocabulary | - |
| <a id="filter-callbacks"></a>Filter callbacks | `0x10010710` |
| <a id="german-noun-vocabulary"></a>German Noun Vocabulary | - |
| Variable Naming | - |
| <a id="globals"></a>Globals | - |
| <a id="string-constants"></a>String Constants | - |
| <a id="locals"></a>Locals | - |
| <a id="calling-convention"></a>Calling Convention | - |
| <a id="error-logging-convention"></a>Error Logging Convention | - |
| <a id="attested-names-from-embedded-strings"></a>Attested Names from Embedded Strings | `0x100068e0` |
| <a id="serverdll-1"></a>server.dll | `0x100068e0`, `0x10006e30`, `0x1000a570`, `0x1000baf0`, `0x1000bdf0`, `0x1000c4d0`, `0x1000d260`, `0x1000f030`, `0x1000f2f0`, `0x1000f3b0`, `0x1000f590`, `0x1000f730`, `0x1000f980`, `0x1000fad0`, `0x1000fb30`, `0x10010700`, `0x100109d0`, `0x10011bf0`, `0x10014070`, `0x10014260`, `0x100146c0`, `0x1001478a`, `0x100147b0`, `0x10014af0`, `0x10014db0`, `0x100150a0`, `0x10015500`, `0x100156c0`, `0x10015950`, `0x10015f70`, `0x10016460`, `0x10016760`, `0x10016cd0`, `0x10016de0`, `0x10016ea0`, `0x10017330`, `0x100174d0`, `0x1001787f`, `0x10017c40`, `0x10017fb0`, `0x10018850`, `0x10019d30`, `0x10028aec`, `0x10028b04`, `0x1002d364`, `0x1002d758`, `0x10031b6c`, `0x100354c4`, `0x100354c8`, `0x100354d0`, `0x100354e0`, `0x101de454`, `0x101de55c`, `0x101de5a4`, `0x11766560`, `0x11766564`, `0x11767580` |
| <a id="client-production-callback-2026-10-14"></a>Client production callback (2026-10-14) | `0x005694b0`, `0x005694f1`, `0x00571870`, `0x005718b1`, `0x00628c28`, `0x006a7c78` |
| <a id="module-case-m_alloc-is-snake_case"></a>Module case: `m_alloc` is snake_case | - |
| <a id="original-spellings-to-preserve"></a>Original spellings to preserve | - |
| <a id="client-binaries"></a>Client binaries | - |
| Struct Naming | - |
| Enum / Constant Naming | - |
| <a id="client-sound-setter-corrected-from-a-legacy-vfs-misnomer"></a>Client sound setter corrected from a legacy VFS misnomer | `0x00417cf0`, `0x00417dd0`, `0x004192b0`, `0x00419390`, `0x004c39b0`, `0x004c3a10`, `0x10003cf0` |
| <a id="animation-task-builder-inferred-createanimationevent"></a>Animation task builder: inferred CreateAnimationEvent | `0x00405970`, `0x00406410`, `0x00406510`, `0x0040c0a0`, `0x0040c870`, `0x0040d7f7` |
| <a id="attested-character-sitting-queries-2026-10-04"></a>Attested character sitting queries (2026-10-04) | `0x0040df00`, `0x0040e110`, `0x00425bf0`, `0x006762d4`, `0x0067635c` |
| <a id="inferred-display-counter-names-2026-10-04"></a>Inferred display-counter names (2026-10-04) | - |
| <a id="shared-random-helper-consolidation-2026-10-04"></a>Shared random helper consolidation (2026-10-04) | `0x0042e410`, `0x0042ec00`, `0x1001a0d0` |
| <a id="shared-scene-object-destruction-2026-10-15"></a>Shared scene-object destruction (2026-10-15) | `0x43a0a0`, `0x43d0e0`, `0x442be0`, `0x4458e0`, `0x447190` |
| <a id="shared-building-destruction-2026-10-15"></a>Shared building destruction (2026-10-15) | `0x447190`, `0x4cb100`, `0x4cbc90`, `0x1000f680` |
| <a id="existing-resolver-name-shared-across-builds-2026-10-04"></a>Existing resolver name shared across builds (2026-10-04) | `0x004fea50`, `0x005015e0`, `0x10015e90` |
| <a id="names-added-in-rounds-16-19-2026-10-08"></a>Names added in rounds 16-19 (2026-10-08) | `0x402320`, `0x41d950`, `0x41daf0`, `0x41dd90`, `0x41e350`, `0x41e3e0`, `0x41e410`, `0x41e440`, `0x41e490`, `0x41e4d0`, `0x4208a0`, `0x420b70`, `0x420ba0`, `0x420bf0`, `0x420d20`, `0x420db0`, `0x421050`, `0x421290`, `0x42fc50`, `0x430260`, `0x430870`, `0x4308a0`, `0x430910`, `0x430c50`, `0x430e30`, `0x430f70`, `0x4310f0`, `0x431510`, `0x4bcc20`, `0x4bcc50`, `0x4bd1e0`, `0x4e73c0`, `0x4e7490`, `0x4e7550`, `0x4e77e0`, `0x4e7b70`, `0x4e7bf0`, `0x4e7c70`, `0x4e8a80`, `0x4e8ad0`, `0x4e8af0`, `0x4e8b40`, `0x4e8b80`, `0x4e8c00`, `0x4e8cb0`, `0x4e8d10`, `0x4e8ee0`, `0x4e90d0`, `0x4e9110`, `0x4e9180`, `0x4e9270`, `0x4e9310`, `0x4e93d0`, `0x4e9500`, `0x4e9530`, `0x4e9580`, `0x4e9950`, `0x4e99c0`, `0x4ea130`, `0x4ea2b0`, `0x4ea460`, `0x4eb220`, `0x4eb260`, `0x4eb320`, `0x4ec7d0`, `0x4ec810`, `0x4ec8a0`, `0x4ec950`, `0x4ec9a0`, `0x4eccd0`, `0x4ecd20`, `0x4ece30`, `0x4eceb0`, `0x4eed10`, `0x4eefe0`, `0x4ef040`, `0x4ef0d0`, `0x4f0930`, `0x4f0eb0`, `0x4f0f60`, `0x4f0ff0`, `0x4f10d0`, `0x4f11c0`, `0x4f1290`, `0x4f13a0`, `0x4f1450`, `0x4f14c0`, `0x4f1790`, `0x4f17f0`, `0x4f1820`, `0x4f1840`, `0x4f1890`, `0x4f1a10`, `0x4f3800`, `0x4f3900`, `0x4f3e60`, `0x4ff860`, `0x4fffb0`, `0x500240`, `0x500480`, `0x500660`, `0x500c80`, `0x500cb0`, `0x500d20`, `0x500d60`, `0x500db0`, `0x500de0`, `0x500e00`, `0x500e20`, `0x5013c0`, `0x501490`, `0x5014d0`, `0x5016f0`, `0x502450`, `0x5024e0`, `0x5025a0`, `0x502780`, `0x502820`, `0x502a20`, `0x503d10`, `0x503e50`, `0x5049a0`, `0x504db0`, `0x504eb0`, `0x504ef0`, `0x505340`, `0x505d00`, `0x506d50`, `0x506e70`, `0x506ee0`, `0x506f70`, `0x506fd0`, `0x507080`, `0x507130`, `0x5072c0`, `0x507380`, `0x507400`, `0x507910`, `0x5079f0`, `0x507ab0`, `0x507c30`, `0x507ed0`, `0x508220`, `0x508c30`, `0x508e80`, `0x508eb0`, `0x508f80`, `0x509050`, `0x509120`, `0x509480`, `0x5095d0`, `0x50b710`, `0x50b780`, `0x50b7a0`, `0x50b810`, `0x50b840`, `0x50bb50`, `0x50bbb0`, `0x50bc10`, `0x50be50`, `0x50bec0`, `0x50bf30`, `0x50bfe0`, `0x50c490`, `0x50c4e0`, `0x50c550`, `0x50c5d0`, `0x50c710`, `0x50c7d0`, `0x50cad0`, `0x50cce0`, `0x50ce20`, `0x50d170`, `0x50d2f0`, `0x50d320`, `0x50d360`, `0x50d430`, `0x50d4f0`, `0x50ddf0`, `0x50de80`, `0x50dfa0`, `0x50e170`, `0x50e4a0`, `0x50e520`, `0x50e600`, `0x50e670`, `0x50f950`, `0x510170`, `0x510400`, `0x510470`, `0x510500`, `0x510550`, `0x51ebc0`, `0x51ecf0`, `0x51f170`, `0x51f480`, `0x520310`, `0x520860`, `0x524610`, `0x6b7fdc`, `0x6b7fe0`, `0x6b7fe8` |
| <a id="renames-from-the-identifier-audit-2026-10-08"></a>Renames from the identifier audit (2026-10-08) | `0x00406560`, `0x0044c460`, `0x00499a50`, `0x00499ad0`, `0x004a1130`, `0x004c43c0`, `0x004c4d30`, `0x00503e80`, `0x00506cd0`, `0x0067edf8`, `0x1000a9a0`, `0x1000ca00`, `0x1000d7f0`, `0x1000ef90`, `0x1000efb0`, `0x1000f080`, `0x1000f0a0`, `0x1000f980`, `0x1000ff60`, `0x100146c0`, `0x100180d0`, `0x10019720`, `0x10022107` |
| <a id="random-unit-ownership-reconciliation-2026-10-11"></a>Random unit ownership reconciliation (2026-10-11) | - |
| <a id="alchemy-helper-declaration-reconciliation-2026-10-11"></a>Alchemy helper declaration reconciliation (2026-10-11) | - |
| <a id="client-animation-sound-identities-2026-10-11"></a>Client animation sound identities (2026-10-11) | - |
| <a id="shared-table-search-helper-2026-10-11"></a>Shared table-search helper (2026-10-11) | - |
| <a id="alchemy-flag-helper-ownership-2026-10-11"></a>Alchemy flag helper ownership (2026-10-11) | - |
| <a id="character-source-placement-2026-10-11"></a>Character source placement (2026-10-11) | - |
| <a id="shared-character-scene-and-script-identities-2026-10-11"></a>Shared character scene and script identities (2026-10-11) | - |
| <a id="attested-character-function-renames-2026-10-11"></a>Attested character function renames (2026-10-11) | `0x403950`, `0x404150`, `0x405d40`, `0x405fb0`, `0x4068e0`, `0x406b50`, `0x40ba90`, `0x40c0d0`, `0x40c210`, `0x40c9a0`, `0x40c9b0`, `0x40cff0`, `0x40d130`, `0x40d8c0` |
| <a id="native-d3-layout-identities-2026-10-11"></a>Native D3 layout identities (2026-10-11) | `0x41dd90`, `0x41e410`, `0x4225e0`, `0x422c60` |
| <a id="deferred-character-position-updates-2026-10-12"></a>Deferred character position updates (2026-10-12) | - |
| <a id="attached-character-model-positions-2026-10-12"></a>Attached character model positions (2026-10-12) | - |
| <a id="low-polygon-character-updates-and-animation-options-2026-10-12"></a>Low-polygon character updates and animation options (2026-10-12) | - |
| <a id="person-tooltip-callback-identity-collision-2026-10-14"></a>Person tooltip callback identity collision (2026-10-14) | `0x00580d10`, `0x00589390` |
| <a id="scene-object-draw-data-cleanup-2026-10-15"></a>Scene-object draw-data cleanup (2026-10-15) | - |
| <a id="scene-object-auxiliary-records-and-cleanup-2026-10-15"></a>Scene-object auxiliary records and cleanup (2026-10-15) | - |
| <a id="camera-slot-and-scene-list-removal-2026-10-15"></a>Camera slot and scene-list removal (2026-10-15) | - |
| <a id="master-evaluation-eligibility-2026-10-15"></a>Master-evaluation eligibility (2026-10-15) | - |
| <a id="character-mesh-constructor-2026-10-15"></a>Character mesh constructor (2026-10-15) | `0x403070`, `0x403880` |
| <a id="active-context-processing-2026-10-16"></a>Active-context processing (2026-10-16) | `0x4297c0`, `0x42aef0`, `0x4fe7f0`, `0x5012b0`, `0x5392a0`, `0x10015cb0` |
| <a id="character-action-insertion-and-queue-access-2026-10-16"></a>Character action insertion and queue access (2026-10-16) | `0x404760`, `0x4048b0`, `0x405080`, `0x4051d0`, `0x4222b0`, `0x1469700`, `0x14d0c40` |
| <a id="scene-dummy-selection-callback-2026-10-16"></a>Scene dummy selection callback (2026-10-16) | `0x406340`, `0x406ee0` |
| <a id="character-script-registration-and-adapters-2026-10-16"></a>Character script registration and adapters (2026-10-16) | `0x40bbc0`, `0x40ca60`, `0x40cae0`, `0x0040cba0`, `0x40d270`, `0x40d980`, `0x40dac0`, `0x0040dad0`, `0x40e1a0`, `0x49dee0` |
| <a id="event-validators-and-master-checking-2026-10-16"></a>Event validators and master checking (2026-10-16) | `0x4daf80`, `0x4dc7d0`, `0x4e4a50`, `0x4e63e0`, `0x92c500`, `0x9b0840` |
| <a id="court-decision-callback-2026-10-16"></a>Court decision callback (2026-10-16) | `0x4dd960`, `0x4df1b0` |
| <a id="goal59-inferred-participant-reset-callback"></a>Goal59: inferred participant-reset callback | - |
| <a id="goal60-texture-precaching-and-the-first-event-phase"></a>Goal60: texture precaching and the first event phase | - |
| <a id="goal61-periodic-timer-and-cutscene-clock-contracts"></a>Goal61: periodic timer and cutscene clock contracts | - |
| <a id="goal62-packet-base-byte-access-contract"></a>Goal62: packet-base byte-access contract | - |
| <a id="no-source-native-mapping-goal63-2026-10-16"></a>No-source native mapping (Goal63, 2026-10-16) | `0x00401d10`, `0x00401ed0`, `0x00403dc0`, `0x004044a0`, `0x004045c0`, `0x40486f`, `0x4049da`, `0x00404dc0`, `0x404ef7`, `0x00405760`, `0x004093d0`, `0x004097d0`, `0x0040a200`, `0x40a5db`, `0x0040a600`, `0x40b633`, `0x0040e0e0`, `0x0040eff0`, `0x40f17e`, `0x004210a0`, `0x421218`, `0x421236`, `0x00424c80`, `0x0042bf20`, `0x0042cbc0`, `0x42d039`, `0x0043c640`, `0x43d474`, `0x0044e1e0`, `0x44e76f`, `0x44e93e`, `0x0044f8b0`, `0x0046c5a0`, `0x46d525`, `0x0046fb90`, `0x00480330`, `0x480a08`, `0x480ad0`, `0x00480c60`, `0x00480e60`, `0x481370`, `0x481380`, `0x004813b0`, `0x00481790`, `0x00481ee0`, `0x4820ea`, `0x482272`, `0x004823c0`, `0x482550`, `0x482640`, `0x48288f`, `0x48293b`, `0x4829f7`, `0x00482ef0`, `0x00489250`, `0x489661`, `0x489762`, `0x00489a70`, `0x00489ca0`, `0x48a24f`, `0x0048a4c0`, `0x0048b220`, `0x0048bc70`, `0x48bd1e`, `0x48c1df`, `0x0048c5b0`, `0x48c5b0`, `0x48c7b6`, `0x48c81c`, `0x0048cdb0`, `0x48cdb0`, `0x48cfae`, `0x48d014`, `0x00494ed0`, `0x495099`, `0x00495510`, `0x004a4d90`, `0x4a4f96`, `0x004a5320`, `0x004bd500`, `0x004bdda0`, `0x4bddbd`, `0x004c8e70`, `0x004c9280`, `0x004c9a10`, `0x4c9a9b`, `0x004c9dc0`, `0x004c9e20`, `0x004ca970`, `0x4cb044`, `0x4cb094`, `0x004cb7f0`, `0x4cb869`, `0x4cba31`, `0x004cbca0`, `0x004cc820`, `0x4ccaee`, `0x4ccb14`, `0x004d8e20`, `0x004da690`, `0x4dac50`, `0x004ded10`, `0x004e0620`, `0x4e130f`, `0x004e8dc0`, `0x004eab40`, `0x4eaeaf`, `0x0050f570`, `0x00512b40`, `0x512d11`, `0x00515990`, `0x00517700`, `0x00519190`, `0x519ce3`, `0x0051af00`, `0x51c68a`, `0x0051c840`, `0x51d2a3`, `0x0051e930`, `0x005238c0`, `0x523f0a`, `0x523fbf`, `0x0052aea0`, `0x005305d0`, `0x5306ac`, `0x530722`, `0x005373e0`, `0x537542`, `0x005383a0`, `0x0053e9e0`, `0x0053f910`, `0x0053fc80`, `0x53fcb8`, `0x005462a0`, `0x5462d4`, `0x00546720`, `0x546789`, `0x00547770`, `0x00554f00`, `0x00555db0`, `0x00557dc0`, `0x0055c950`, `0x0055d0d0`, `0x55d3f2`, `0x55d520`, `0x0055df80`, `0x55e45c`, `0x0055fd80`, `0x0055ffe0`, `0x5601a8`, `0x00564b90`, `0x564df3`, `0x00568060`, `0x5681e9`, `0x00579830`, `0x00581e20`, `0x581e90`, `0x0058ffe0`, `0x005988b0`, `0x598b0e`, `0x59926a`, `0x005aacd0`, `0x005aeaf0`, `0x005af320`, `0x005b6300`, `0x5b63c1`, `0x005b9880`, `0x005ba0e0`, `0x5ba143`, `0x005ba910`, `0x5baa7b`, `0x005c5310`, `0x5c58c8`, `0x675548`, `0x675598`, `0x6755c8`, `0x675b18`, `0x675b58`, `0x6768ec`, `0x678b18`, `0x678b60`, `0x67b8e8`, `0x67b92c`, `0x67dd1c`, `0x67dd58`, `0x67dec0`, `0x67df08`, `0x67dfe8`, `0x67e020`, `0x67e218`, `0x67e25c`, `0x67e298`, `0x67e2d0`, `0x67e3a8`, `0x67e4e8`, `0x67e750`, `0x67e8c0`, `0x67e918`, `0x67ea30`, `0x67f074`, `0x681674`, `0x68afc8`, `0x68b108`, `0x68b13c`, `0x68b240`, `0x68b2ac`, `0x68b304`, `0x68b33c`, `0x68cc70`, `0x68de2c`, `0x6a1cf0`, `0x6a23e0`, `0x6a2430`, `0x6a301c`, `0x6a33f4`, `0x6a42d0`, `0x6a5784`, `0x6a57b0`, `0x6a62a8`, `0x6a62dc`, `0x6a6380`, `0x6a64e0`, `0x6a6620`, `0x6a6920`, `0x6aa1e8`, `0x6aa240`, `0x6ac37c`, `0x6ac6c4` |
| <a id="goal64-shared-supermap-sampling"></a>Goal64: shared supermap sampling | `0x004bd710`, `0x004bd760`, `0x004bdfb0`, `0x004be000` |
| <a id="goal65-indexed-bmp-output"></a>Goal65: indexed BMP output | `0x00401d10` |
| <a id="method-registry-and-cutscene-entries-goal66-2026-10-16"></a>Method registry and cutscene entries (Goal66, 2026-10-16) | - |
| <a id="attachanimlooped-goal67-2026-10-16"></a>AttachAnimLooped (Goal67, 2026-10-16) | - |
| <a id="object-universe-mapping-helper-goal68-2026-10-16"></a>Object-universe mapping helper (Goal68, 2026-10-16) | - |
| <a id="init_loadobjektscene-native-identification-goal69"></a>init_LoadObjektScene (native identification, Goal69) | - |
| <a id="savebmp24-native-mapping-correction-goal69"></a>SaveBMP24 native mapping correction (Goal69) | - |
| <a id="native-role-mapping-and-gold-action-identities-goal70"></a>Native role mapping and Gold action identities (Goal70) | `0x4432d0`, `0x448360`, `0x45b290`, `0x467920`, `0x5383a0`, `0x554f00`, `0x555db0`, `0x55c950`, `0x55fd80`, `0x5ae390`, `0x5b88b0`, `0x5b9980`, `0x5c1490`, `0x5c18e0`, `0x5c23b0`, `0x5d0660` |
| <a id="separated-ui-entries-and-ecmd_loadscene-goal71"></a>Separated UI entries and ecmd_LoadScene (Goal71) | `0x40ddf0`, `0x40ed00`, `0x5ae390`, `0x5b57e0`, `0x5b5b70`, `0x5b5fd0`, `0x5b6aa0`, `0x5b9980`, `0x5c1110`, `0x5c1490`, `0x5c18e0`, `0x5c23b0` |
| <a id="large-functions-and-scenecredit-dependencies-goal72"></a>Large functions and scene/credit dependencies (Goal72) | `0x401380`, `0x401500`, `0x432410`, `0x432480`, `0x447110`, `0x447e30`, `0x44abb0`, `0x44b920`, `0x4d4d70`, `0x4d6170`, `0x4d76a0`, `0x4d8d00`, `0x501190`, `0x503fe0`, `0x519190`, `0x51af00`, `0x51c840`, `0x538740`, `0x540020`, `0x5b9430`, `0x5c4ec0` |
| <a id="vfs-closer-declarations-and-entity-call-binding-goal81-2026-10-17"></a>VFS closer declarations and entity call binding (Goal81, 2026-10-17) | `0x430580`, `0x00522e30` |
| <a id="opaque-stream-formals-goal82-2026-10-17"></a>Opaque stream formals (Goal82, 2026-10-17) | - |
| <a id="scene-callbacks-and-resource-views-goal83-2026-10-17"></a>Scene callbacks and resource views (Goal83, 2026-10-17) | `0x401270`, `0x4012b0` |
| <a id="naming-review--2026-10-31"></a>Naming review — 2026-10-31 | `0x41d9e0`, `0x41f5f0`, `0x41f7f0`, `0x41f8f0`, `0x41f940`, `0x41f9b0`, `0x41f9d0`, `0x4222b0`, `0x423660`, `0x4236b0`, `0x459b80`, `0x466190`, `0x4722c0`, `0x473a90`, `0x475be0`, `0x475f60`, `0x4ce130`, `0x4cef30`, `0x504ec0`, `0x505df0`, `0x507f10`, `0x508e40`, `0x519190`, `0x51af00`, `0x60bd68`, `0x60bd6c`, `0x60bd70`, `0x68a9d0`, `0x68a9d4`, `0x68a9d8`, `0x92c4e0`, `0x9b0820`, `0x100184a0`, `0x41c64e6d` |
| <a id="character-queue-entry-removal-2026-11-02"></a>Character queue-entry removal (2026-11-02) | `0x004047a0`, `0x00404810`, `0x004050c0`, `0x00405130`, `0x00405610`, `0x00406120`, `0x00406560` |

</details>
