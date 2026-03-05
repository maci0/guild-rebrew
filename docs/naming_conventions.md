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
(`Europa1400Gold.exe`) links only the engine `Units\` — game logic may be
compiled directly into it or loaded from a separate DLL not captured here.

### File Naming Patterns

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

| Prefix | Module       | Source File              | Domain                          |
|--------|--------------|--------------------------|---------------------------------|
| `cm_`  | Command      | `command.c`              | Command validation & execution  |
| `gm_`  | Game         | `spiel.c`                | Entity/object/building mgmt     |
| `lb_`  | Lobby        | `lobbycommands.c`        | Network lobby layer             |
| `ahm_` | Alchemy      | `alchemistry_logic.c`    | Alchemy subsystem               |
| `gv_`  | Graveyard    | `friedhof_logic.c`       | Graveyard subsystem             |
| `sim_` | Simulation   | `sim.c`                  | Citizen simulation              |

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
extern int g_timestamp_0b6c;              /* known purpose, partial name */
extern char g_player_slot_0[];            /* known: player slot array */
extern char g_static_entity_table_358a0[];/* known: static entity table */
extern int g_entity_type_table;           /* known: entity type lookup */
extern int g_10030b6c;                    /* unknown: address-only name */
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
