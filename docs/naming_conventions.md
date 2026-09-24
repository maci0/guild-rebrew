# Original Developer Naming Conventions

Reconstructed from debug strings, error messages, and binary analysis of
`server.dll` and `Europa1400Gold_TL.exe`. Developer: 4HEAD Studios (German).

## Source Tree Layout

Reconstructed from `__FILE__` debug strings and PDB references embedded in
the three shipped binaries. All paths are on `D:\Develop\` (case varies).

### server.dll

```
D:\Develop\
  DieGildeAddOn\
    auxillary\
      plant.c              -- plant/vegetation system
    command\
      command.c            -- all cm_* functions (~15k bytes, 0x1000cb20..0x10010526)
      lobbycommands.c      -- all lb_* functions
    game\
      spiel.c              -- core game logic (gm_* functions)
      aemter.c             -- office/election system
      alchemistry_logic.c  -- alchemy subsystem (ahm_* functions)
      friedhof_logic.c     -- graveyard subsystem (gv_* functions)
      sim.c                -- simulation / citizen logic (sim_* functions)
    loadsave\
      loadsave.c           -- save/load serialization
  DieGildeAddOnServer\
    server.c               -- main loop, dispatch table, cm_ProcessCommandQueue
  Units\                   -- shared library units (linked into multiple binaries)
    Error\Error.c          -- error handling
    m_alloc\m_alloc.c      -- memory allocator
    net\broadcast.c        -- network broadcast
    vfs\vfs.c              -- virtual file system
```

### Europa1400Gold.exe (main game client)

```
D:\develop\
  Units\
    d2.v1\GFX.C           -- 2D graphics
    d3\
      d3_d3d.c             -- Direct3D renderer
      d3_engine.c          -- 3D engine core
      d3_interface.c       -- 3D interface layer
      d3_sky.c             -- sky rendering
      ts_texture.c         -- texture system
    d3_tools\d3_tools.c    -- 3D tool utilities
    dd_vesa\Dd_vesa.c      -- DirectDraw / VESA fallback
    Msx\msx.c              -- music/sound (MSX)
    net\net.c              -- network layer
```

### Europa1400Gold_TL.exe (Transform & Lighting GPU pipeline)

```
D:\develop\
  DieGildeAddOnVc\         -- game logic (VC = Visual C++ project)
    Release\Europa1400Exp_TL.pdb   -- PDB debug symbols (!)
  d2_test\textures\        -- 2D test textures
  units\
    Msx\msx.c              -- music/sound (shared)
    net\net.c              -- network layer (shared)
```

Note: TL.exe shares the same game logic as server.dll (the `cm_*`, `gm_*`
functions appear in both) but is built from `DieGildeAddOnVc\` instead of
`DieGildeAddOn\`. The `Units\` directory is shared across all three binaries.

### Attested original source paths (round 937)

The `__FILE__` strings the compiler embedded give the original tree directly: **14 paths**, extracted
with:

```sh
python3 - <<'PY'
import re, collections
d = open('original/Server/server.dll','rb').read()
c = collections.Counter()
for m in re.finditer(rb'D:\\Develop\\[ -~]{4,90}', d):
    c[m.group(0).decode('latin1')] += 1
for k, v in c.most_common():
    print(v, k)
PY
```

```
Units\net\broadcast.c              Units\Error\Error.c
Units\m_alloc\m_alloc.c            Units\vfs\vfs.c
DieGildeAddOnServer\server.c       DieGildeAddOn\auxillary\plant.c
DieGildeAddOn\command\command.c    DieGildeAddOn\command\lobbycommands.c
DieGildeAddOn\game\aemter.c        DieGildeAddOn\game\alchemistry_logic.c
DieGildeAddOn\game\friedhof_logic.c
DieGildeAddOn\game\sim.c           DieGildeAddOn\game\spiel.c
DieGildeAddOn\loadsave\loadsave.c
```

(all under the `D:\Develop\` root the binary spells out). Every entry of the merged tree below is
attested by one of these. **This list is the authority**; the tree is not speculation where it agrees
with it.

**The `_c` directory suffixes in this repository's working tree are NOT attested.** Our files live
under `game/spiel_c/`, `command/command_c/`, `loadsave/loadsave_c/` and so on, but no `__FILE__` string
contains `_c\`: the originals were `spiel.c`, `command.c`, `loadsave.c` in the plain directories shown
above. The suffixes are a decompiler-era artefact of splitting one original translation unit into many
files, kept because moving ~140 files would churn every path in the metadata for no gain. They should
not be read as evidence about the original layout, and a future round that reorganises the tree should
target the attested names. Recorded so the difference reads as deliberate rather than as attestation.

### Merged Source Tree (speculative)

Combining all three binaries into a single view of the original development
tree. Entries marked with which binary references them.

```
D:\Develop\
  DieGildeAddOn\                         -- game logic (server-side build)
    auxillary\
      plant.c                            [server.dll]
    command\
      command.c                          [server.dll]
      lobbycommands.c                    [server.dll]
    game\
      aemter.c                           [server.dll]
      alchemistry_logic.c               [server.dll]
      friedhof_logic.c                   [server.dll]
      sim.c                              [server.dll]
      spiel.c                            [server.dll]
    loadsave\
      loadsave.c                         [server.dll]
  DieGildeAddOnServer\                   -- dedicated server entry point
    server.c                             [server.dll]
  DieGildeAddOnVc\                       -- game logic (client-side build, T&L)
    Release\
      Europa1400Exp_TL.pdb               [TL.exe] PDB symbols
  Units\                                 -- shared engine / infrastructure
    d2.v1\
      GFX.C                              [Gold.exe] 2D graphics
    d2_test\
      textures\                          [TL.exe] test textures
    d3\
      d3_d3d.c                           [Gold.exe] Direct3D renderer
      d3_engine.c                        [Gold.exe] 3D engine core
      d3_interface.c                     [Gold.exe] 3D interface layer
      d3_sky.c                           [Gold.exe] sky rendering
      ts_texture.c                       [Gold.exe] texture system
    d3_tools\
      d3_tools.c                         [Gold.exe] 3D tool utilities
    dd_vesa\
      Dd_vesa.c                          [Gold.exe] DirectDraw / VESA fallback
    Error\
      Error.c                            [server.dll] error handling
    m_alloc\
      m_alloc.c                          [server.dll] memory allocator
    Msx\
      msx.c                              [Gold.exe, TL.exe] music/sound
    net\
      broadcast.c                        [server.dll] network broadcast
      net.c                              [Gold.exe, TL.exe] network layer
    vfs\
      vfs.c                              [server.dll] virtual file system
```

`DieGildeAddOn\` and `DieGildeAddOnVc\` likely contain the same game logic
source files, compiled with different project settings. The server build
(`DieGildeAddOn\`) produces `server.dll`. The client T&L build
(`DieGildeAddOnVc\`) produces `Europa1400Gold_TL.exe`. The base client
(`Europa1400Gold.exe`) links only the engine `Units\`: game logic may be
compiled directly into it or loaded from a separate DLL not captured here.

### File Naming Patterns

- A shared domain type spelled identically in two TUs leaves the `.c` files
  (rebrew_types.h holds globals support types, game_structs.h domain types).
  Lifts on record:
  - `LinkedNode` (0x43, packed, round 1103): `spiel_c/gm_RemoveLinkedNodeById.c`
    and `spiel_c/gm_RemoveObjectByType.c`. Both local copies invented names;
    the CALLERS fix the evidence: +0x00 word = `type` (16-bit object types
    passed to `gm_RemoveObjectByType` by cm_ExClearLagerslot / cm_ExProdObjekt /
    ahm_ExAllocAlchemist), +0x02 int = `entity_id` (`*(int*)(entity + 2)` at
    `gm_RemoveObjectWrapper`); removal clears the type word.
  - `gm_CurrentHumanFamilyCount` (round 1107): attested by the confirmed-push
    overflow log in gm_AllocSpieler; renamed from `g_dynasty_generation_counter`.
  - `OFFICE_SLOT` (0x18, round 1103): `game/aemter.c` (`a/b/c/type/d`) and
    `game/aemter_c/amt_fio_LoadAemter.c` (read-order names). The latter's
    names kept. Neither list is attested by a string; both descriptive.
  - `gz_stream` (0x64, round 1104): `Units/vfs/vfs_c/check_header.c` and
    `Units/vfs/vfs_c/gzread.c` byte-identical zlib-gzio copies -> header
    `Units/vfs/gz_stream.h` next to its users.
  - round 1105-1106 collapsed the last two 0x43-byte node spellings
    (`EntitySlot` in `gm_FreeObjectListRecursive.c`, anonymous `Record` in
    `spiel.c`) onto the lifted `LinkedNode`; one layout, one name.
- German nouns for gameplay concepts: `spiel` (game), `aemter` (offices),
  `friedhof` (graveyard)
- English for technical/infrastructure: `server`, `lobbycommands`, `loadsave`
- Subsystem logic files get a `_logic` suffix: `alchemistry_logic`,
  `friedhof_logic`
- Shared library code lives under `Units\` with short module names:
  `d3`, `net`, `vfs`, `Msx`, `m_alloc`

## Module Prefix System

Every exported/named function carries a **module prefix** identifying its
subsystem:

### Game Logic Modules

| Prefix | Module       | Source File              | Domain                          |
|--------|--------------|--------------------------|---------------------------------|
| `cm_`  | Command      | `command.c`              | Command validation & execution  |
| `gm_`  | Game         | `spiel.c`                | Entity/object/building mgmt     |
| `lb_`  | Lobby        | `lobbycommands.c`        | Network lobby layer             |
| `ahm_` | Alchemy      | `alchemistry_logic.c`    | Alchemy subsystem               |
| `gv_`  | Graveyard    | `friedhof_logic.c`       | Graveyard subsystem             |
| `sim_` | Simulation   | `sim.c`                  | Citizen simulation              |
| `amt_` | Offices      | `aemter.c`               | Office / election system        |
| `ls_`  | LoadSave     | `loadsave.c`             | Save/load serialization         |
| `plt_` | Plant        | `plant.c`                | Zone/record lookup, vegetation  |

### Infrastructure Modules (`Units/`)

| Prefix | Module       | Source File              | Domain                          |
|--------|--------------|--------------------------|---------------------------------|
| `m_`   | Memory       | `m_alloc.c`              | Tracked heap alloc, pool alloc  |
| `vfs_` | VFS          | `vfs.c`                  | Virtual file system, streams    |
| `srv_` | Server       | `server.c`               | Server lifecycle, main loop     |

Two units have **no attested prefix**: `Units/Error/Error.c` and
`Units/net/broadcast.c`. The debug strings and the binary's own names for
them are not recovered, so their functions keep descriptive unprefixed names
(`LogMessageInternal`, `ReportFatalError`, `SendBroadcastPacket`) rather than
an invented `err_`/`net_`. The string corpus confirms this: the only
module-prefixed identifiers near `Error.c` (`0x10027144`) and `broadcast.c`
(`0x10001130`) are asset names, and neither unit logs with a `err_*():` or
`net_*():` prefix. Add a row here only when the original name is attested.

File-scoped save/load helpers inside a module take a `fio_` (file I/O) infix:
`amt_fio_LoadAemter`, `amt_fio_SaveAemter`. The prefix chain is
`<module>_<role>_<VerbNoun>`, so `amt_fio_LoadAemter` is the `aemter.c`
file-I/O loader.

### Client-Only Modules (`Europa1400Gold*.exe`)

The client binaries share the game logic (`cm_`, `gm_`, `amt_`, `ls_`, `gv_`,
`ahm_`) but add engine subsystems that never appear in `server.dll`. These
prefixes are attested by log strings in `Europa1400Gold_TL.exe` and
`Europa1400Gold.exe` and are **out of scope for this repo's decompilation
target**; they are recorded so names are not invented twice.

| Prefix  | Module            | Domain                                   |
|---------|-------------------|------------------------------------------|
| `ch_`   | Character         | Character/mesh/animation runtime         |
| `ai_`   | AI                | Meister (master) AI decision routines    |
| `he_`   | Handlungsereignis | Game events                              |
| `cut_`  | Cutscene          | Cutscene control                         |
| `d2_`   | Direct2D layer    | 2D UI/interface layer (`d2.v1`)          |
| `d3_`   | Direct3D layer    | 3D renderer (`d3/`)                      |
| `txt_`  | Text              | Text file parse/format                   |
| `lc_`   | Location          | Building placement / jail queries        |
| `rd_`   | Record            | Record / supermap lookup                 |
| `sv_`   | Server view       | Client-side state sync                   |
| `io_`   | I/O               | Generic file I/O                         |
| `init_` | Init              | Startup / scene init                     |
| `main_` | Main              | Client main loop / menus                 |
| `nt_`   | Network           | Client network layer                     |
| `ob_`   | Object            | Object behaviour on the client           |
| `gs_`   | Court (Gericht)   | Evidence / trial system                  |
| `am_`   | Method registry   | Engine method registration (`am_RegisterMethod`) |

Assets, script commands, and config keys in the client also use `prefix_`
spellings (`bau_`, `bk_`, `sp_`, `ub_`, `upgr_`, `riss_`, `prva_`, `snd_`,
`sbs_`, …). Those are data identifiers, not function names; do not map them
onto C symbols.

### Standard Library Functions

Standard CRT functions (`fopen`, `fread`, `putc`, `srand`, `rand`, etc.)
are used directly with proper `#include` headers: no `extern` declarations
needed.

The compiler intrinsic `__ftol` (float-to-long) is statically linked and
requires a forward declaration where used.

Small static helpers within a module may omit the prefix (they were `static`
in the original source and not visible across translation units).

## Function Naming

### Pattern: `prefix_VerbNoun`

```
cm_ExSellObjekt        -- cm  = command module
                       -- Ex  = execute (action verb)
                       -- Sell = English verb
                       -- Objekt = German noun (object)

cm_ChkMoveCredits      -- Chk = check / validate
gm_AllocBuildingDefaults
lb_ExPlayerlist
ahm_ExAllocAlchemist
gv_ExAllocGraveyardWorker
sim_CreateCitizen
```

### Command Module Sub-Prefixes

The `cm_` module uses a two-phase check-then-execute architecture.
Each command type has up to two handler functions:

| Sub-prefix    | Role        | Return semantics                     |
|---------------|-------------|--------------------------------------|
| `cm_Chk*`     | Validate    | `0` = OK, `1` = invalid (reject)    |
| `cm_Ex*`      | Execute     | `0` = OK, `1` = failed              |

Both share the signature `int __cdecl func(void* cmd, void* result)`.

Additional patterns seen in the binary:

| Pattern           | Role                                          |
|-------------------|-----------------------------------------------|
| `cm_Request*`     | Client-side command request (TL.exe only)     |
| `cm_Dispatch*`    | Routes to a sub-handler                       |
| `cm_Chain*`       | Linked command chain handler                  |
| `cm_Init*`        | Initialization / default setup                |
| `cm_Assign*`      | Assigns IDs or counters                       |
| `cm_Get*`         | Read-only query                               |
| `cm_Set*`         | Write a flag or field                         |
| `Cmd*`            | Likely the compiled name for some cm_Ex       |

### Lobby command dispatch

`lb_ExLobbyServerCommand` (`0x10014db0`) is a **7-way switch on the lobby command id**, read as
`*(int*)(msg + 0x10)`. It is the single best anchor for the `lb_` module's vocabulary: every case is a
sibling handler, and the numbering is fixed by the binary rather than guessed. Recovered in round 1080 by
reading the jump table at `0x10014ebc` against the case bodies. The dispatcher bounds the id first
(`cmp eax,6` / `ja 0x10014eae`) and each case ends in its own `pop esi` / `add esp,0x80` / `ret`, so the
order below is the table order, not an inference from the C source:

| id | handler | address | role |
|---|---|---|---|
| 0 | `lb_ExPlayerlist` | `0x100145e0` | send the player list |
| 1 | `lb_SendLobbyConfig` | `0x100146c0` | send lobby configuration |
| 2 | `lb_ExPlayerHasJoined` | `0x100147b0` | a player joined |
| 3 | `lb_BroadcastStateChange` | `0x10014a50` | broadcast a state change |
| 4 | `lb_ExPlayerRecordBroadcast` | `0x10014af0` | distribute one player's record to the others |
| 5 | `lb_HandleEntitySync` | `0x10014bf0` | entity synchronisation |
| 6 | `cm_RouteCommand` | `0x10014ca0` | hand off to the `cm_` layer |

The call sites carry the symbol names directly (`call 0x100146c0  ; lb_SendLobbyConfig`), so this table is
attested rather than reconstructed. Two consequences worth keeping: `lb_` and `cm_` are **one dispatch
chain**, not independent modules: case 6 crosses into `cm_`, so a `cm_` rename can reach lobby code. And
`lb_SendLobbyConfig` has no `.c` of its own; it shares `lb_ExPlayerlist.c`. The dispatcher's own log string
(`0x1002d858`, `"lb_ExLobbyServerCommand: %i"`) confirms the name it prints is the real symbol, which is why
that row in the attested table reads "already correct".

### Verb Vocabulary

Verbs are English. Nouns are German when they name game concepts:

| Verb     | Meaning                                           |
|----------|---------------------------------------------------|
| Alloc    | Allocate / create a new entity                    |
| Free     | Deallocate / destroy                              |
| Kill     | Destroy with side effects (player death, etc.)    |
| Change   | Modify a numeric field (additive)                 |
| Set      | Write a field (absolute)                          |
| Move     | Transfer between containers                       |
| Sell     | Trade transaction                                 |
| Create   | Instantiate (buildings, objects)                  |
| Employ   | Assign a worker to a building                     |
| Prod     | Produce (manufacturing)                           |
| Clear    | Reset / empty a slot                              |
| Swap     | Exchange two values                               |
| Validate | Check preconditions                               |
| Dispatch | Route to sub-handler                              |
| Remove   | Unlink / detach                                   |
| eval     | Evaluate a predicate, no mutation (`gm_eval_SlotVoll`, `gm_eval_ObjektBesitzer`) |
| Load     | Read from file/stream (`amt_fio_LoadAemter`, `ls_LoadCharacter`) |
| Save     | Write to file/stream (`amt_fio_SaveAemter`)       |

### Filter callbacks

A function the reference never `call`s directly is still reachable: its **address** is passed as an argument
and the callee invokes it indirectly. `FindSlotEntryFiltered` (`0x10010710`) takes one as its fourth
parameter and calls it as

```c
if (((int (__cdecl*) (void*, void*)) filter)(filter_arg, cursor)) { ... }
```

so the callback contract is `filter(arg, entry)`, non-zero meaning *accept*. Three functions pass an address
there (`gv_SpawnEntities.c:41`, `gv_HireProductionWorker.c:55`, `gv_MoveSlotEntry.c:121`).

**This is a naming trap worth knowing.** `grep` for `call` finds none of them, the catalogue carries no name
for them (`fcn.10010700`), and a header comment can end up asserting "It has no caller": which is what
happened here and stood for many rounds. Before concluding a tiny unnamed function is dead code, grep for its
**address** in the tree, not just for a call. Give it the `_eval_` predicate name and record the callee's
callback signature in the header.

### German Noun Vocabulary

| German          | Abbreviation | English          | Example                    |
|-----------------|-------------|------------------|----------------------------|
| Spieler         |             | Player           | `cm_ExAllocSpieler`        |
| Objekt          |             | Object           | `cm_ExSellObjekt`          |
| Gebaeude        | Geb         | Building         | `cm_ExCreateGeb`           |
| Raum            |             | Room             | `cm_ExAllocRaum`           |
| Lagerslot       |             | Storage slot     | `cm_ExClearLagerslot`      |
| Wohnsitz        |             | Residence        | `cm_ExSetWohnsitz`         |
| Besitzer        |             | Owner            | `cm_ExSetGebBesitzer`      |
| Predigt         |             | Sermon           | `cm_ExAllocThemaPredigt`   |
| Thema           |             | Theme/topic      | `cm_ExAllocThemaPredigt`   |
| Aemter          |             | Offices/roles    | `aemter.c`                 |
| Friedhof        |             | Graveyard        | `friedhof_logic.c`         |
| Rohstoff        |             | Raw material     | error: "Rohstoff verschwunden" |
| Karren          |             | Cart             | error: "Karren in Spieler" |
| Straftat        |             | Crime            | `cm_ExAddStraftat` (TL)    |
| Handlungsereignis | HE        | Game event       | `cm_ExSetHE` (TL)          |
| Bauplatz        |             | Building plot    | `cm_ExCreateGeb` (TL)      |

## Variable Naming

### Globals

Globals use a `g_` prefix. When the original name is unknown, the convention
in this project is `g_<hex_address>`:

```c
extern int g_next_object_id;              /* known purpose, partial name */
extern char g_player_slot_0[];            /* known: player slot array */
extern char g_slot_table[];/* known: static entity table */
extern int g_entity_type_table;           /* known: entity type lookup */
extern int g_1009b764;                    /* unknown: address-only name */
```

### String Constants

Ghidra labels string constants as `s_<truncated_content>_<address>`:

```c
extern char s_cm_ChkMoveCredits____Invalid__qu_1002c7a4[];
extern char s_D__Develop_DieGildeAddOn_command_1002c748[];
```

The embedded content reveals original function names:
`s_cm_ChkMoveCredits____...` means the string literal starts with
`"cm_ChkMoveCredits(): ..."`.

### Locals

Original local variable names are lost. Ghidra assigns type-prefixed
temporaries (`iVar1`, `puVar2`, `pcVar3`). During decompilation we replace
these with descriptive names based on context:

```c
/* Ghidra output */
int iVar1;
ushort *puVar2;

/* Reversed */
int resolve_result;
unsigned short *building_entity;
```

## Calling Convention

| Code origin | Convention   | Default for             |
|-------------|-------------|-------------------------|
| GAME        | `__cdecl`    | All cm_, gm_ functions  |
| Win32 API   | `__stdcall`  | `__declspec(dllimport)` |
| CRT         | `__cdecl`    | Standard library        |

Symbol mangling: `__cdecl` functions get a leading underscore in the object
file. Annotation `// SYMBOL: _cm_ExFree` reflects this.

## Error Logging Convention

Every important function logs errors through a central logger:

```c
LogMessageInternal(
    s_D__Develop_DieGildeAddOn_command_1002c748,  /* __FILE__ */
    0x2a21,                                        /* __LINE__ (hex) */
    s_cm_ExFree____Can_t_free_Objects_1002cc3c,   /* message */
    1                                              /* severity */
);
```

The message string almost always starts with the function name:
`"cm_ExFree(): Can't free Objects"`. This is how we recover original names.

## Attested Names from Embedded Strings

The shipped binaries embed the full string corpus. RevEng.AI's
`GET /v2/analyses/{id}/functions/strings` returns every string with the
function VA that references it. A string shaped `"<name>(): ..."` or
`"<name>: ..."` names the owning function.

Every name below was then **verified against the code**: the function at the
stated VA is disassembled and confirmed to push the literal address of that
string. RevEng's attribution alone is not trusted (it wrongly attached
`_main_:` to `0x100068e0` and `lb_ExPlayerReadyStatus` to `0x100146c0`).

Reproduce:

```bash
# list every string a function references; "(): " prefixes name the owner
curl -s -H "Authorization: Bearer $REVENG_API_KEY" \
  "https://api.reveng.ai/v2/analyses/1468081/functions/strings?page_size=2000" \
  | jq -r '.data.strings[] | select(.value|test("^[A-Za-z_]+\\(\\):")) | "\(.functions[0].function_vaddr)\t\(.value)"'
# then confirm the owner pushes the literal
rebrew asm 0x<VA> --size <size> | grep 'push 0x100[23]'
```

### server.dll

| VA | Attested name | Standing |
|----|---------------|----------|
| `0x100068e0` | `m_init` | renamed from `m_InitPacketPool` |
| `0x10006e30` | `m_pool_free` | renamed from `m_PoolFree` |
| `0x1000a570` | `srv_LoadBuf` | renamed from `srv_ProcessReceiveData` |
| `0x1000baf0` | `amt_fio_LoadAemter` | already correct |
| `0x1000bdf0` | `ahm_ExAllocAlchemist` | already correct |
| `0x1000c4d0` | `ahm_AllocAhmInfo` | already correct (mangled symbol `?ahm_AllocAhmInfo`) |
| `0x1000d260` | `cm_ChkCutsceneReady` | already correct |
| `0x1000f030` | `cm_ExKillSpieler` | already correct |
| `0x1000f2f0` | `cm_ExAllocThemaPredigt` | already correct (round 1108) |
| `0x1000f3b0` | `cm_ExSetGebBesitzer` | already correct (round 1108) |
| `0x1000f590` | `cm_ExSetGebUpgrade` | already correct (round 1108) |
| `0x1000f730` | `cm_ExEmployWorker` | already correct (round 1108) |
| `0x1000f980` | `cm_ExAllocCharacter` (log prefix only) | kept as `cm_ExCreateCitizen`; the body logs `"cm_ExAllocCharacter():gm_AllocSpieler() failed"` (`0x1002d364`): log-prefix-only attestation, same standing as `gm_AllocGebaeude` at `0x10017330` |
| `0x1000fad0` | `cm_ExKillTransporter` | already correct (round 1108) |
| `0x1000fb30` | `cm_ExCreateGeb` | already correct |
| `0x10010700` | `gv_eval_SlotFrei` | renamed from `fcn_10010700`; a `FindSlotEntryFiltered` filter callback (address taken by 3 callers, so no `call` reaches it); true when the entry's owner id at +4 is -1 |
| `0x100109d0` | `gv_AllocGraveyardField` | renamed from `gv_AllocField` |
| `0x10011bf0` | `gv_ExAllocGraveyardWorker` | already correct |
| `0x10014070` | `ls_ID2Ptr` | already correct |
| `0x10014260` | `srv_RecvGame` | already correct; the same body also logs `LoadGame():` and `ls_RecvGame():` |
| `0x100147b0` | `lb_ExPlayerHasJoined` | renamed from `lb_HandleLobbyCommands` |
| `0x10014af0` | `lb_ExPlayerRecordBroadcast` | renamed from `fcn_10014af0`; the site pushes `__FILE__` = `...\command\lobbycommands.c` and logs `"invalid client state"`; is `case 4` of the `lb_ExLobbyServerCommand` switch |
| `0x10014db0` | `lb_ExLobbyServerCommand` | already correct |
| `0x100150a0` | `plt_SetPlantMap` | already correct |
| `0x10015500` | `sim_CreateCitizen` | already correct |
| `0x100156c0` | `gm_InitObjektHersteller` | already correct |
| `0x10015950` | `gm_Open` | already correct |
| `0x10015f70` | `gm_ObjectsAvailble` | renamed from `gm_RefreshMarketAvailability` |
| `0x10016460` | `gm_ff_Objekt` | renamed from `gm_StartEntityQuery` |
| `0x10016760` | `gm_AllocObjekt` | already correct |
| `0x10016cd0` | `gm_AddObjekt` | renamed from `gm_AddOrAccumulateObject` |
| `0x10016de0` | `gm_SubObjekt` | already correct |
| `0x10016ea0` | `gm_SubObjectNoKill` | renamed from `gm_SubObjektNoKill` |
| `0x10017330` | `gm_AllocGebaeude` (log prefix only) | kept as `gm_AllocBuildingDefaults` |
| `0x100174d0` | `gm_AllocGebaeude` | already correct |
| `0x10017c40` | `gm_AllocRaum` | renamed from `gm_AllocBuildingContents` |
| `0x10017fb0` | `gm_KillSpieler` | renamed from `gm_DeallocEntity` |
| `0x10018850` | `gm_AllocSpieler` | renamed from `gm_CreateEntityFromParents` |
| `0x10019d30` | `gm_eval_SlotVoll` | renamed from `gm_KannObjektHergestellt` |
| `0x101de454` | `g_aux_entity_count` | renamed from the placeholder `g_101de454`; the name was already declared in `ls_LoadBuildingEntityState.c` and the metadata note said "auxiliary entity count (loadsave)" |
| `0x101de55c` | `g_aux_entity_buffer` | renamed from the placeholder `g_101de55c`; declared in the same TU, note "auxiliary entity buffer (realloc'd)" |
| `0x101de5a4` | `g_office_slots_00_entityId` | renamed from the misleading `g_aemter_table`; it is `g_office_slots + 4`, record 0's `entityId`, not a second table |
| `0x10028b04` | `s_Memory_Shutdown_Anomaly_10028b04` | renamed from `g_str_10028b04`; literal `"[*] Memory-Shutdown-Anomaly: [*]\nUsed %i blocks in %i bytes.\n\n%i"` read from the reference. Convention is `s_<content>_<addr>` for strings, not `g_str_` |
| `0x10028aec` | `s_Pointer_not_freed_10028aec` | renamed from `g_str_10028aec`; literal `"-> Pointer not freed:%s"` read from the reference |
| `0x100354c4` | `__argc` | renamed from `g_100354c4`; CRT name was in the metadata note. Present in LIBCMT but displaced by the `_CRT_REGION_KEEP` local definition, same as `__error_mode` |
| `0x100354c8` | `__argv` | renamed from `g_100354c8`; also fixed a latent **type** error: was declared `int`, MSVC6 requires `char**`. Renaming is what exposed it |
| `0x100354d0` | `__envp` | renamed from `g_100354d0`; `char**`, same fix |
| `0x100354e0` | `_pgmptr` | renamed from `g_100354e0`; `char*`, same fix |
| `0x10031b6c` | `__tlsindex` | renamed from `g_10031b6c`; CRT TLS index |
| `0x11766564` | `__pioinfo` | renamed from `g_11766564`; identified from the use site (`[__pioinfo][handle]`, flag byte at `+0xc`), NOT from the note, which called it a "tracked-block table" |
| `0x11766560` | `_nfile` | renamed from `g_11766560`; a handle bound (`cmp esi,[_nfile]; jae`, init 0x20), not the "current stream count" the note claimed |
| `0x11767580` | `__nstream` | renamed from `g_11767580`; guards the `__pioinfo` walk |

`0x10017330` and `0x100174d0` both push an `"gm_AllocGebaeude(): ..."`
string. `0x100174d0` is the caller (`call 0x10017330` at `0x1001787f`), so it
keeps the name; `0x10017330` is its static defaults helper that reuses the
parent's log prefix.

### Module case: `m_alloc` is snake_case

The `Units/m_alloc` unit does not use the `m_VerbNoun` CamelCase of the game
modules. Its recovered names are lower snake case:

- `m_alloc`: the tracked allocator, called from every unit. In the original
  this is a macro: the tracked implementation receives an extra
  `__FILE__ ":" __LINE__` argument, so our `m_AllocTracked` stays as the
  implementation name and only the macro was `m_alloc`.
- `m_init`: sets the slot count and allocates the slot table;
  `m_alloc` refuses to run before it.
- `m_pool_free`: pool release.
- `m_alloc_debug`: not a function: a block group name written by `sprintf`,
  so it must not be turned into a symbol.

### Original spellings to preserve

Recovered names reproduce the original source exactly, including errors:

- `gm_ObjectsAvailble` (not `Available`)
- `gm_SubObjectNoKill` uses English `Object`, while `gm_SubObjekt` next to it
  uses German `Objekt`
- Umlauts are stripped in string literals: `Gebude` for `Gebäude`,
  `berschritten` for `überschritten`
- `erbaut`/`erhalb` fragments and similar truncated strings are continuations
  of literals that the linker split, not standalone names

### Client binaries

`Europa1400Gold_TL.exe` and `Europa1400Gold.exe` expose the same corpus via
the same endpoint (5128 and 4956 strings). Their function-name log prefixes
are listed under Client-Only Modules above. Neither binary is decompiled
here; the strings only constrain shared-code names and the prefix vocabulary.

## Struct Naming

Structs use `UPPER_CASE` names, often abbreviated:

```c
typedef struct DISPATCH_OBJ { ... } DISPATCH_OBJ;
typedef struct SRC { ... } SRC;
typedef struct TGT { ... } TGT;
```

Field naming appears to use lowercase with occasional camelCase. Struct
definitions are local per translation unit (no shared headers for game
structs in the decompiled code).

## Enum / Constant Naming

Constants seen in strings follow patterns:

- Object types: `ob_LAGERFLAECHE_ALLGEMEIN`, `ob_MARKTSTAND`, `ob_NULL`
- Command types: `cmdt_ALLOC_SPIELER`, `cmdt_ALLOC_OBJEKT`, `cmdt_FREE`
- Player flags: `pef_GELIEBTE`
- Seasons: `GM_WINTER`, `GM_SUMMER`, `GM_SPRING`, `GM_AUTUMN`
- Sim events: `HE_SIM_EINWANDERUNG`, `HE_SIM_KRANKHEITEN`, `HE_SIM_PERSONAL`

Pattern: `prefix_UPPER_SNAKE_CASE` where prefix is a short module/type tag.
