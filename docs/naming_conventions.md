### Shared solar-effect stop (2026-10-14)

The inferred `StopSonnenstrahlen` covers TL0x4186d0 and Gold0x417150,
31 bytes each. It belongs beside the existing creation/reset bodies in the
shared solar-effect unit. The weather caller supplies an object pointer and
phase1; the native helper ignores the first argument and stores the second,
sets active state to-1 and resets the clock. The Gold one-argument stub is
retired. No original spelling or filename is attested. Fresh CLI discovery
supplies the missing TL inventory entry; all prior inventory rows are preserved.
The shared header declares the two-argument interface. Both weather callers
retain their complete380-byte COFF bodies and35 typed operands after binding
and declaration repairs. All six solar-effect bodies and32 rejecting symbol
controls are verified in `.scratch/goal22/reconstruction/solar-stop-native-proofs.json`.
No storage, flags or assembly are added; client raw links remain unverified.

### Shared Sonnenstrahlen creation and reset (2026-10-14)

The newly inferred `CreateSonnenstrahlen` covers TL0x418710 and GOLD0x417190,
211 native bytes each. `StartSonnenstrahlen` replaces TLfcn_004186f0 and
GOLDfcn_00417170 at0x4186f0/0x417170,31 bytes each. Both live once in the
inferred `Develop/DieGildeAddOn/game/sonnenstrahlen.c` unit. No original
function spelling or unit path is attested: resource literals `pLicht` and
`sonnenstrahlen`, the shared scene creation calls and the existing weather
caller establish purpose and affinity. No new module prefix is invented.

`SonnenstrahlenAktiv`, `SonnenstrahlenStartZeit` and `SonnenstrahlenPhase`
are inferred scalar access names. Their rows and the existing object-pointer
spelling describe declaration views; backing allocations, complete extents
and storage owners remain unresolved. No storage is allocated. The constructors
share logic with verified per-client flag offsets and masks. Their literal
rows record complete compiler-owned strings and provide no linked data verdict.
The canonical interface returns the constructed scene object; the reset accepts
an unused object argument, matching the native constructor's push. Both old
reset copies retire. Complete bodies, every typed operand and rejecting bindings
are checked in `.scratch/goal22/reconstruction/production-native-proofs.json`;
the existing weather caller's complete body and operand graph are preserved
in both clients by `caller-preservation.json` in that directory.

# Original Developer Naming Conventions

Reconstructed from debug strings, error messages, and binary analysis of
`server.dll` and `Europa1400Gold_TL.exe`. Developer: 4HEAD Studios (German).

### Shared tracked allocator and attested spelling (2026-10-11)

SERVER0x10006580 (658 bytes), GOLDTL0x41db70 and GOLD0x4223c0
(544 bytes each) share the canonical memory-allocation implementation in
`Develop/Units/m_alloc/m_alloc.c`. The unit path is attested by SERVER's
`__FILE__` strings; common native grouping, tracking and literal bytes support
client placement in that unit. SERVER alone contains the three fatal diagnostics.
No new storage or assembly is introduced. Scoped client aliases describe the
existing tracker state; they do not establish global storage owners.

The pre-initialization diagnostic explicitly spells `m_alloc()`. That attests
the original allocator spelling. The previous reconstruction name
`m_AllocTracked` is retired: the definition, three target rows,84 source/header
files and server link anchor now use `m_alloc`. Existing
`GroupNode`, field labels and numeric global spellings remain inferred or
unresolved. Both complete client bodies, literals and all25 operands match;
all185 checked caller operands independently retain their native destination.
The private40-byte group and16-byte allocation-record layouts are unchanged.
Receipts: `.scratch/goal21/shared-tracked-alloc`.

### Shared allocator shutdown (2026-10-12)

The inferred `m_ShutdownAllocator` name now covers SERVER0x10006c00,
TL0x41e0c0 and GOLD0x422910 in the shared m_alloc unit. Its original spelling
remains unproven. The clients retain the same leak-reporting literals, tracking
slot cleanup and linked-list traversal; SERVER alone logs the formatted pointer
leak. The native bodies are 283/262/262 bytes. Client aliases describe existing
storage without allocating it or establishing an owner; the numeric global and
callback names remain unresolved. The group next pointer remains at offset36,
and tracked records remain16 bytes. Complete native operands and literal bytes
agree with the old client implementation and existing allocator/report bindings.
The TL shutdown caller retains its native call destination. Evidence:
`.scratch/goal21/shared-allocator-shutdown`.

## Shared tracker reporting and group layout (2026-10-11)

The existing inferred `m_ReportGroupInfo` name now covers SERVER0x10006990,
TL0x41df00 and GOLD0x422750 in the shared m_alloc unit. The SERVER source
path is attested by its native logging calls; client placement follows the
identical group traversal, formatting literals and shutdown callers. SERVER
logs the formatted output; the clients retain the formatting but omit those
six calls. Its original spelling remains unproven.

`GroupNode` is the single40-byte allocation-group layout for all targets;
`MemPool` was another name for the same layout. Canonical `size_total`,
`count_total`, `size_max`, `count_max`, `count` correspond to the former
`used`, `used_blocks`, `max`, `max_blocks`, `calls` at offsets16/20/24/28/32.
The names are reconstructed. Name storage is16 bytes and next is at36;
tracked `MemBlock` records remain16 bytes with group/tag/pointer/size at0/4/8/12.
Compiler assertions and native bodies establish layout, not original spelling
or storage ownership. Client stat/global spellings are private scoped aliases
without allocations. Evidence: `.scratch/goal21/shared-pool-report`.

### Shared pool deallocation (2026-10-11)

`m_pool_free` is attested by the SERVER fatal diagnostic at0x10006e30.
The corresponding TL0x41e2e0/GOLD0x422b30 names and unit placement remain
inferred from the same16-byte pool-block layout, slot/bounds/unlink logic and
calls to the shared tracking deallocator. One canonical definition now serves
all three targets; only SERVER reports invalid entries. The complete112-byte
client bodies retain both native call operands, while the137-byte server body
and every caller remain unchanged. The duplicate client `Chunk` definition is
retired with its source. Existing `M_POOL_BLOCK` field names and global owners
remain provisional. Evidence: `.scratch/goal21/shared-pool-free`.

### Native MSX and D3 unit placement (2026-10-11)

TL420840 directly references the attested `D:\develop\units\Msx\msx.c` path.
Thirteen channel functions share the same native critical section; their placement
under `Develop/Units/Msx` is inferred from this subsystem affinity. Their original
function spellings and the other functions' exact original units remain unknown.
Both TL420840 and GOLD4244b0 also attest `hTrack->bAmbient`. The canonical 296-byte
`Chan_14cc460` view now uses the attested `bAmbient` spelling at offset0x106.
Its type name and the other field spellings remain provisional. Eleven verified MSX bodies now share
`msx.c`; helper placement is inferred from their channel calls and state. Their
address-based function names and the complete allocation owners remain unresolved.
Evidence: `.scratch/goal20/msx-shared-unit/scope-final.json`.
`FindTrackByName` (TL4205e0/GOLD424250) and `FindFreeTrack`
(TL420690/GOLD424300) are inferred descriptive names. No MSX function prefix is
attested, so these names remain unprefixed. Their shared ten-record table is an
accessed view; its original global name and allocation owner are unknown.
Evidence: `.scratch/goal20/msx-track-table/scope-final.json` and
`.scratch/goal20/msx-track-type/scope-final.json`.
`SetTrackPath` (TL420760/GOLD4243d0) is also inferred and unprefixed. Its former
GOLD478860 pairing was false: that function copies into a separate game buffer.
The unassigned `g_f8aae0` keeps a provisional VA label until its original role/name
is established; it does not name the MSX path buffer. Evidence:
`.scratch/goal20/msx-start-volume/scope-final.json`.
GOLD438780 directly references `D:\develop\Units\d3\d3_d3d.c` and the expression
`d3d_Device->lpVtbl->EndScene(d3d_Device)`. `d3d_Device` is therefore attested;
`d3d_LastResult` is inferred. The interface's complete type and the accessed views'
allocation owners remain unresolved. The original function name is unknown.
Evidence: `.scratch/goal20/native-unit-map/direct-path-evidence.json` and
`.scratch/goal20/native-unit-batch/native-msx-affinity.json`.

### Shared worker-housing action (2026-10-11)

`RunBuergermeister` is inferred from the native `Buergermeister` run registration
at TL49d640/GOLD49dc00. The action name is attested; the original function and unit
spelling are unknown. `client_actions.h` declares the recovered three-argument ABI
and existing helper's returned filtered pointer. Calendar scalars remain accessed
views; complete backing allocation and cross-TU declaration consolidation are pending.
Evidence: `.scratch/goal20/mayor-worker-housing/scope-final.json`.

### Shared GUI image update (2026-10-11)

`d2_SetElementImage` at TL466330/GOLD469240 and the `d2_gui.c` unit are inferred.
The attested `d2_` UI prefix, indexed GUI records, release/load/acquire callbacks,
signed resource dimensions and GUI callers establish the role, not original spelling.
The false client `cm_ExAllocThemaPredigt` binding is removed; the SERVER handler stays
unchanged. Shared C preserves TL756-byte/32-bit fields and GOLD748-byte/16-bit fields,
including GOLD's unchanged-resource guard. `bild_offset` names the proven integer
view at TL+88/GOLD+78; inherited legacy GuiEnt field names remain unresolved. The
ten global aliases reuse existing C spellings as declaration-only accessed views:
original names, allocation identity, complete backing extents and owners remain
unproven. `d2_gui.h` is a reconstructed declaration home. No storage is allocated.
The TL routing caller is independent70-byte4bfbc0, outside the matched dialog body.
Evidence: `.scratch/goal20/ui-resource-bind/scope-final.json`.

### Shared floor-water region fill (2026-10-11)

`d3_FillWaterRegion` at TL43bf60/GOLD440170 is inferred. The attested `d3_`
renderer prefix and the caller's `d3_fl:Water` allocation labels support its
module/role; original spelling and `d3_floor.c` unit placement remain unproven.
The unrelated client `cm_ExAllocRaum` binding is removed; that attested SERVER
handler stays unchanged. The268-byte helper operates on square byte grids and
retains all six full-width arguments, interpreting region values by low byte.
The original valid-coordinate/distinct-color preconditions remain unchanged.
Evidence: `.scratch/goal20/grid-flood-fill/scope-final.json`.

### Shared motion completion identity (2026-10-11)

`ch_FinishAni` at TL404410/GOLD403c10 is inferred from the native motion
cleanup and morph continuation flow; original name/unit remain unproven.
The neighboring `ch_CheckAniMorph` logs belong to TL4045c0. The false client
`cm_ExClearLagerslot` binding is removed; the attested SERVER handler remains.
The shared options view preserves native partial initialization, with a
continuation field at TL+0x318 / GOLD+0x10. `ch_MorphFrameValue` is inferred
for the accessed4-byte value written to animation+0x3c. Its two alias rows
allocate no storage and establish neither complete backing objects nor owners.
Evidence: `.scratch/goal20/character-motion-clear/scope-final.json`.

### TL model-motion preloader identity (2026-10-11)

`ch_PreloadModelMotions` at TL404ca0 is inferred from the existing attested
character module prefix and native model-name/motion loop. Its original spelling
and compilation-unit path remain unproven. The former `cm_ExAllocSpieler` binding
was unrelated; that attested SERVER handler remains unchanged. The existing
motion-loader file owns the reconstructed283-byte helper and12-byte options
view. Its two absolute0x34 reads are native, with no direct callers or absolute
function-pointer references found. No storage owner or GOLD counterpart inferred.
Evidence: `.scratch/goal20/alloc-spieler-client/scope-final.json`.

### Recovered character queries and sound constructor (2026-10-11)

`CharacterSitting` TL40df00 and `CharacterSitsDown` TL40e110 retain their
attested spellings and saved implementations; their shared bit query remains
unmatched. `fcn_004050c0`, `fcn_00405540` and `fcn_00418c80` remain unnamed
pending original-module and naming evidence. This recovery restores their
exact previously verified source versions, including the constructor's
existing SOUND_SOURCE view; it establishes no new names or storage owners.
The TL constructor again matches150 bytes with all6 operands independently
bound. Its stock CRT call is strncpy64d530. GOLD's constructor field offset
difference remains unbound; do not import the TL constructor unchanged.
Evidence: `.scratch/goal20/missing-character-bindings/scope-final.json`.

### Parent resolver and getter extents (2026-10-11)

`gm_ResolveParentEntity` (SERVER10019ae0/TL50d490/GOLD50a050) and
`gm_GetEntityType` (SERVER10019b40/TL50d530/GOLD50a0b0) retain inherited
inferred names. Complete client extents are82 and62 bytes, excluding14
and2 external NOPs. The resolver uses the id at input+0x0a, returns its
static record if present, otherwise follows dynamic+0x27 into g_slot_table;
missing records or link0xffff return null. The getter returns the static
record's first word, otherwise dynamic+0x27, otherwise0xffff. A domain
claim of type/class is unproven; canonical entity_index naming does not
establish this helper's original name. No new storage was introduced.
Evidence: `.scratch/goal20/parent-type-extents/scope-final.json`.

### Shared stat/group and table-entry helpers (2026-10-11)

`gm_CheckStatLevel`, `gm_MapEntityStatRange` and `gm_GetEntityTableEntry`
retain their inherited inferred names. This work establishes shared identities,
not their original spellings: SERVER100181a0/TL5074e0/GOLD5044b0;
SERVER10018200/TL507b00/GOLD504ad0; SERVER100184e0/TL509570/GOLD506430.
The first returns the occupation code when its group equals the requested
stat id, otherwise a byte at table-entry+0x74+id, or zero for no entry. It does
not test a threshold. The mapper groups codes0..94; code82 and out-of-range
codes return zero. Its complete291 bytes include both compiler tables; the
retired client clone's304-byte extent also included13 external NOPs.
The table-entry helper selects a172-byte record for kinds5/6/7 with flag0x8000
and low-four-bit index0..15. Both client implementations remain near matches
with11 register/scheduling differences. Canonical prototypes and caller casts
preserve the existing reconstructed views; original domain types remain open.
Client `g_entity_type_bytes` is a declaration-only view at `g_slot_table+0x164`.
Client `g_entity_base` describes the accessed2752-byte table view. These inherit
server analysis names and allocate no storage; complete backing objects and
storage owners remain unresolved. VC6 requires the owning spiel.c's early
prototype order; its header omits repeat stat declarations in that TU.
Evidence: `.scratch/goal20/stat-level-extent/scope-final.json`.

### Filtered iterator identity correction (2026-10-11)

`gm_FindNextFilteredEntity` is the existing inferred shared name for the
iterator at SERVER10016f80, GOLDTL503e80 and GOLD501030. The client body is341
bytes plus11 layout NOPs; all20 relocation sites and all other bytes match
the existing spiel.c definition in both clients. GOLDTL503e80's former
`gm_AddObjekt` binding named a different shared function and is disproven.
The true server `gm_AddObjekt` name remains attested and unchanged. Evidence:
`.scratch/goal20/stat-shared-iterator-audit.json`. Upstream0fbab4fb fixes the
shared importer, and the verified replay corrects both client names, symbols,
flags and341-byte reference hashes through the managed writer. Evidence:
`.scratch/goal20/stat-iterator-replay.json`.

### Entity-class embedded switch extents (2026-10-11)

The existing shared `gm_EntityClassCheck` retains its name and C definition.
GOLDTL506e20 and GOLD503f50 have70-byte complete extents:34 bytes of reachable
code,2 internal alignment bytes, an8-byte branch table, and a26-byte case map.
The following10 NOPs are external alignment. Compiler-generated table labels
are private views inside the owning function; the extent repair creates no
named global or storage owner. All26 cases/default and8 local DIR32 targets
are validated through upstream strict operand proof. Evidence:
`.scratch/goal20/entity-class-extent/scope-final.json`.

### Shared object resource cleanup (2026-10-11)

`gm_ClearObjektResources` is inferred, not attested. The existing spiel.c now
owns SERVER10016670 (one-byte empty body), GOLDTL502ec0 and GOLD500080
(client54-byte body). The clients inspect the object prototype category0x1d,
release the pointer chain at node+0x29 via fcn_004be280, and clear that field.
The recursive list helper at SERVER10016710, GOLDTL502f80 and GOLD500140 calls
the correct edition body. Clients have66-byte recursion plus14 alignment NOPs.
The existing g_99ec10 declaration and client resource-chain callee remain
aliases/users; this consolidation creates no data allocation or owner claim.
The helper's original unit/name and domain types remain unproven. The canonical
spiel.h declaration uses the existing reconstructed LinkedNode; VC6 requires
its early recursive declaration and the expanded header after gm_Open in the
shared unit. Evidence: `.scratch/goal20/recursive-object-list/scope-final.json`.

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

**The `_c` directory suffixes are not attested.** No `__FILE__` string contains `_c\`; the decompiler-era
split of one translation unit into one file per function is gone for the server. The server tree now has
one file per original translation unit, in the order the linker lays them out (verified: every one of the
260 server game functions links at its reference VA):

| Reference VA run | File | Functions |
|---|---|---|
| `0x10001130` | `Units/net/broadcast.c` | 1 |
| `0x10002640`-`0x10003640` | `Units/Error/Error.c` | 11 |
| `0x100036d0`-`0x10003cf0` | `references/zlib/gzio.c` | 8 (zlib 1.1.3 `gzio.c`, vendored per `vendoring.md`; vfs.c calls its `gzread` and `gzclose`) |
| `0x10006580`-`0x10006e30` | `Units/m_alloc/m_alloc.c` | 7 |
| `0x10008a50`-`0x10008c80` | `references/minizip/unzip.c` | 3 (minizip 0.15 from zlib 1.1.3 contrib, vendored per `vendoring.md`; library code, so outside `src/Develop`; no `__FILE__` string names it) |
| `0x10008d10`-`0x10009020` | `Units/vfs/vfs.c` | 3 |
| `0x10009310`-`0x1000b040` | `DieGildeAddOnServer/server.c` | 19 |
| `0x1000b1c0`-`0x1000baf0` | `DieGildeAddOn/game/aemter.c` | 10 |
| `0x1000bd50`-`0x1000ca90` | `DieGildeAddOn/game/alchemistry_logic.c` | 16 |
| `0x1000cb20`-`0x100104a0` | `DieGildeAddOn/command/command.c` | 68 |
| `0x10010530`-`0x10011bf0` | `DieGildeAddOn/game/friedhof_logic.c` | 17 |
| `0x10012000`-`0x10014260` | `DieGildeAddOn/loadsave/loadsave.c` | 11 |
| `0x100145e0`-`0x10014db0` | `DieGildeAddOn/command/lobbycommands.c` | 8 |
| `0x10014ee0`-`0x100151b0` | `DieGildeAddOn/auxillary/plant.c` | 6 |
| `0x100151e0`-`0x10015690` | `DieGildeAddOn/game/sim.c` | 6 |
| `0x100156c0`-`0x1001a110` | `DieGildeAddOn/game/spiel.c` | 66 |

The `__LINE__` values the code passes to `LogMessageInternal` rise with the VA inside each file, so the
linked order is the source order. The client targets still keep divergent twins as `GOLDTL.<name>.c`
beside these files.

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
      net.h                              [Gold.exe, TL.exe] reconstructed statistics header (speculative; multi-TU native evidence)
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
`Europa1400Gold.exe`. Both clients are targets of the current reconstruction;
shared client subsystems should use one source tree and these original prefixes.

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
| 1 | `lb_ExPlayerReadyStatus` | `0x100146c0` | store a player's ready status (player+0x264210, flag 0x800) |
| 2 | `lb_ExPlayerHasJoined` | `0x100147b0` | a player joined |
| 3 | `lb_BroadcastStateChange` | `0x10014a50` | broadcast a state change |
| 4 | `lb_ExPlayerRecordBroadcast` | `0x10014af0` | distribute one player's record to the others |
| 5 | `lb_HandleEntitySync` | `0x10014bf0` | entity synchronisation |
| 6 | `cm_RouteCommand` | `0x10014ca0` | hand off to the `cm_` layer |

The ids and handler addresses come from the jump table; the names do not. `lb_ExPlayerlist`,
`lb_ExPlayerReadyStatus`, `lb_ExPlayerHasJoined` and the dispatcher `lb_ExLobbyServerCommand` are attested
by their own log strings (`"Got lb_ExPlayerReadyStatus"` is pushed at `0x1001478a`, the `Got <own name>` form
`lb_ExPlayerlist` uses); the other three names are inferred. `lb_` and `cm_` are **one dispatch chain**, not
independent modules: case 6 crosses into `cm_`, so a `cm_` rename can reach lobby code. All seven handlers
are defined in `command/lobbycommands.c`.

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
| Prepare  | Validate and fill an action's initial state (inferred `PrepareBuergerrecht`) |
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

Use the original developers' style, as accepted in `AGENTS.md`, rather than
adding a project-wide `g_` prefix. An attested name wins exactly: for example
`lpGebaeudePROT`, `lpObjekteINST`, `gm_ObjektNr2MinimalHersteller` and
`cm_LastSyncCount`. Allocation labels and log strings establish spelling;
physical section placement alone does not establish a name or owner.

For inferred names, use the owning module's `<module>_CamelCase` style. Heap
table pointers use `lp` + German noun, with `PROT`/`INST` where appropriate;
file statics use `s_`, typed pointers `tp_`, and struct fields German snake_case.
Record that an unattested name is inferred. Do not invent module prefixes.
Existing address-only labels remain unresolved until evidence supports a name.
Layout spans retain `g_gap_*` and `g_before_*` until their backing objects and
owners are proven; those labels are inventory, not original identifiers.

### String Constants

Compiler literals have no source identifier. Their inventory rows use
`str_<content>`, with `flt_`/`dbl_<value>` for floating pools. `s_` is reserved
for an actual file-static source object, not a compiler literal.

Older Ghidra-derived labels used `s_<truncated_content>_<address>`, for example:

```c
extern char s_cm_ChkMoveCredits____Invalid__qu_1002c7a4[];
extern char s_D__Develop_DieGildeAddOn_command_1002c748[];
```

Those historical labels still reveal original function names:
`s_cm_ChkMoveCredits____...` means the string literal starts with
`"cm_ChkMoveCredits(): ..."`. Rename surviving inventory labels through
`rebrew source rename --data`; preserve compiler-sensitive declaration order
and verify affected functions and the raw link before integrating.

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
`_main_:` to `0x100068e0`).

Reproduce:

```bash
# list every string a function references; "(): " prefixes name the owner
curl -s -H "Authorization: Bearer $REVENG_API_KEY" \
  "https://api.reveng.ai/v2/analyses/1468081/functions/strings?page_size=2000" \
  | jq -r '.data.strings[] | select(.value|test("^[A-Za-z_]+\\(\\):")) | "\(.functions[0].function_vaddr)\t\(.value)"'
# then confirm the owner pushes the literal
rebrew binary asm show 0x<VA> --size <size>| grep 'push 0x100[23]'
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
| `0x1000f980` | `cm_ExAllocCharacter` | renamed from `cm_ExCreateCitizen`; the body logs `"cm_ExAllocCharacter():gm_AllocSpieler() failed"` (`0x1002d364`) and `"Invalid 'GI_Id' for cmdt_ALLOC_CHARACTER"`, and no other function holds the name |
| `0x1000fad0` | `cm_ExKillTransporter` | already correct (round 1108) |
| `0x1000fb30` | `cm_ExCreateGeb` | already correct |
| `0x10010700` | `gv_eval_SlotFrei` | renamed from `fcn_10010700`; a `FindSlotEntryFiltered` filter callback (address taken by 3 callers, so no `call` reaches it); true when the entry's owner id at +4 is -1 |
| `0x100109d0` | `gv_AllocGraveyardField` | renamed from `gv_AllocField` |
| `0x10011bf0` | `gv_ExAllocGraveyardWorker` | already correct |
| `0x10014070` | `ls_ID2Ptr` | already correct |
| `0x10014260` | `srv_RecvGame` | already correct; the same body also logs `LoadGame():` and `ls_RecvGame():` |
| `0x100146c0` | `lb_ExPlayerReadyStatus` | renamed from `lb_SendLobbyConfig`; pushes `"Got lb_ExPlayerReadyStatus"` (`0x1002d758`) at `0x1001478a` |
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
| `0x10028b04` | `s_Memory_Shutdown_Anomaly_10028b04` | historical rename from `g_str_10028b04`; literal `"[*] Memory-Shutdown-Anomaly: [*]\nUsed %i blocks in %i bytes.\n\n%i"` read from the reference. Compiler-literal inventory now uses `str_`; this spelling awaits the verified naming batch. |
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
- `m_FreeTracked`: our inferred implementation name, now shared by SERVER,
  TL and Gold. Its 188-byte server and 117-byte client bodies differ in native
  error reporting; the original function spelling is not attested.
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


### Client sound setter corrected from a legacy VFS misnomer

`vfs_WriteUint32LE` at TL `0x00419390` / GOLD `0x00417dd0` stores its second
argument at object offset `0x50`, calling TL `0x004192b0` / GOLD `0x00417cf0`
first when that argument is nonzero. The callee's shared C emits the
`3dSound-Handle is attached to %s` diagnostic. TL callers `0x004c39b0` and
`0x004c3a10` use this setter when creating and destroying a sound handle.
The client setter therefore does not serialize a little-endian word. Its exact
control-field meaning and original symbol/module name remain unestablished.
The client symbol is now `SetSoundControlValue` (descriptive, without an
invented module prefix); CLI rename updates the shared body and two TL callers.
`Units/vfs/GOLDTL.vfs2.c` placement remains a legacy reconstruction label,
not attested original organization. The server function with
that same name at `0x10003cf0` really writes four bytes with `fputc`; the target-aware
CLI rename preserves that independent server function and its callers.
The clients now share one verified setter body with two markers. Evidence:
`.scratch/goal-client-loop/asm-{gold-417dd0,tl-419390}.json`,
`src/GOLDTL.fcn_004192b0.c`, and the two sound-handle caller files.


### Animation task builder: inferred CreateAnimationEvent

TL `0x00406510` creates an animation task through `0x0040c0a0`, installs callback
`0x00406410`, copies its name at `+0xf0`, and returns the task pointer. Caller
`0x0040d7f7` tests that pointer and sets its `+0x18c` flag. The callback loads
and starts an animation; this body is unrelated to the server command handler
also named `cm_ExModifyHealth`. The pointer return and full 75-byte body are
recovered. The prior matched body was restored and freshly measured RELOC 75/75
on 2026-10-10. `CreateAnimationEvent` is an inferred descriptive name, without
an invented module prefix. The CLI renamed only the TL identity and its file;
the independent server health handler and its callers retain `cm_ExModifyHealth`.
The former command-directory placement was a legacy reconstruction label.
The shared builder now lives in `Develop/DieGildeAddOn/game/CreateAnimationEvent.c`,
with the other character task sources. That placement follows native task affinity;
its exact original compilation unit remains unknown.

Two callers used the unbound source name `fcn_00406510`. Rebrew's new explicit
`source rename fcn_00406510 GOLDTL.0x00406510` binds those declarations and calls
to the renamed definition, without changing any identity or verification row.
Their name arguments are now declared as string pointers. The earlier ordinary
rename rejection remains valid evidence of independent symbols; its duplicate
checks were not bypassed or relaxed.

The shared GOLD caller at `0x0040c870` calls GOLD `0x00405970`. Original assembly
there has the same 75-byte body with the allocator/callback relocations changed,
then five NOPs. Its discovered 80-byte span scores 94.393546 against the TL donor,
versus 100 for the actual body. That preview declined before the upstream extent
repair. After Rebrew 2613fa04, the reviewed pair imported through the existing
`--source-va` selector and the shared source verifies GOLD RELOC 75/75; the
inferred name now also owns GOLD `0x00405970`. Its callback's shared source uses
an inferred build selector for the native GOLD+0x84 / TL+0x390 blocking-word
offsets and verifies 248 bytes in each client. No original macro or full member
layout is attested. The existing shared GOLD caller now verifies RELOC 152/152,
with its eight following NOPs retained as layout facts. Automatic score/gap
guards and full compiled-body verification remain unchanged.
Evidence: `.scratch/goal-builder/xrefs.json`,
`.scratch/goal20/animation-builder-original-evidence.json`,
`animation-rename-applied.json`, `animation-binding-applied.json`, and
`src/Develop/DieGildeAddOn/game/CreateAnimationEvent.c`.


### Attested character sitting queries (2026-10-04)

| TL VA | Attested name | Evidence | Standing |
|---|---|---|---|
| `0x0040df00` | `CharacterSitting` | Direct push of `0x006762d4`: `CharacterSitting(): invalid character` | CLI renamed from `fcn_0040df00`; first-pass C, SIZE_MISMATCH |
| `0x0040e110` | `CharacterSitsDown` | Direct push of `0x0067635c`: `CharacterSitsDown(): invalid character` | CLI renamed from `fcn_0040e110`; first-pass C, SIZE_MISMATCH |

Both functions dereference their first argument, log a null character through
`0x00425bf0`, and return bit 4 of the byte at character offset `0x8c`.
The two reference bodies are each 56 bytes followed by eight NOPs; their
separate diagnostics attest two distinct API symbols despite identical flag
queries. Keep the recovered spelling without an invented module prefix.
No original file/module path is established; the bodies remain beside their
existing neighboring wrappers. Evidence: `.scratch/goal-next-asm-{df00,e110}.json`,
`.scratch/goal-character/rename-{sitting,sitsdown}.json`; original string bytes
were read directly at the pushed VAs.


### Inferred display-counter names (2026-10-04)

ResetDisplayCounters (TL4737c0/Gold476c60) and CountDisplayCounters
(TL4737e0/Gold476c80) are inferred descriptive names. The shared 12-byte
DISPLAY_COUNTER record follows the six-slot native renderer/update table:
key/ID at offset 0, value at 4 and four uninterpreted bytes at 8. DisplayCounters
is the inferred table name; its storage owner remains unresolved. These are
not recovered original names or source-path attestations. Existing client_types.h
remains the canonical home because the original subsystem/header is unproved.

On 2026-10-14 the actual legacy C is repaired to agree with its already-named
managed identities. Both clients now use ordinary typed six-element loops;
separate Gold copies retire. Stable client.display_counter bindings verify
12-byte size/stride and offsets 0/4/8 in both compilers. Complete native helper
and caller proofs: .scratch/goal23/pool-unification/. Original semantic evidence:
.scratch/goal-display-counters/table-operands.json.

- Inferred shared type `VECTOR3` replaces address-derived `Vec3_67bbdc`: three floats,12-byte view with offsets0/4/8, reused by seven client sources. TL67bbdc/Gold5fcc78 includes ambient RGB use; TL6b86c4 semantics remain unresolved. No original-name or source-path attestation. Evidence `.scratch/goal-material-colors/field-alias-bindings.json`; original allocation ownership remains unresolved.

### Shared random helper consolidation (2026-10-04)

| Image | VA | Current name | Standing |
|-------|----|--------------|----------|
| server.dll | `0x1001a0d0` | `gm_RandomMod` | Existing reconstructed server name retained; body moved from spiel622.c to game/spiel_c/gm_RandomMod.c. |
| Europa1400Gold_TL.exe | `0x0042e410` | `gm_RandomMod` | Numeric caller alias fcn_0042e410 renamed; newly recovered32-byte identity shares the server body. |
| Europa1400Gold.exe | `0x0042ec00` | `gm_RandomMod` | Renamed from fcn_0042ec00; duplicate body retired for the shared definition. |

This is a semantic shared-name choice anchored in the existing server reconstruction, not an original-symbol or log-string attestation. The existing `int __cdecl gm_RandomMod(unsigned short n)` C form produces all32 native bytes in each image, including a typed call to that image's stock `rand`. It does not prove unique original signedness or parameter spelling. Caller prototype narrowing remains unresolved; the rename preserves caller declaration types. Evidence: .scratch/goal-random-helper/consolidation/native-shared-body-audit.json and consolidation-scope-check.json. Full-tree verification63165 is accepted: all existing matches retained and the TL helper added. Five prior mismatches have stricter deltas under the newly bound call catalog; before/after compiled bytes are identical.


### Existing resolver name shared across builds (2026-10-04)

The existing descriptive SERVER name `gm_ResolveEntityById` now identifies the
same complete 211-byte function in both clients. This is structural and native
byte evidence, with five independently bound globals; it is not original-name
string attestation.

| Build | VA | Standing |
|-------|----|----------|
| SERVER | 0x10015e90 | Existing descriptive canonical name |
| GOLDTL | 0x005015e0 | Renamed from fcn_005015e0; shared SERVER body |
| GOLD | 0x004fea50 | Renamed from fcn_005015e0; shared SERVER body |

All three identities select the existing spiel.c definition. Client global views
reuse the SERVER names g_item_def_table, g_slot_table, g_query_limit and
 g_query_base at independently established per-build addresses. No new module
prefix or storage owner is inferred. Evidence:
`.scratch/goal-resolver-consolidation/{identity-consolidation,resolver-native-proof,
binding-actions}.json`; allocation and physical-view evidence:
`.scratch/goal-tl-callee-identities/resolver-native-witness.json`.

### Names added in rounds 16-19 (2026-10-08)

The reconstructed client code of rounds 16-19 (msvc6-link-layout 5f) added the names below. Checked against
every `ident():` / `ident:` string in `Europa1400Gold_TL.exe`, `Europa1400Gold.exe` and `server.dll`
(`.scratch/measure/attest.py --corpus`), a verbatim search of each name in the three images, and the strings
each ported TL function addresses (`attest.py docs/client-only-sweep.md original/Europa1400Gold_TL.exe`).

- **Attested, already correct:** `vfs_Tfopen`, `vfs_init` (their own `sprintf` messages), `vfs_fseek`
  (`Unsupported vfs_fseek(inzip,SEEK_CUR)`), `nt_Recv`, `rd_GetBKSize`, `amt_fio_SaveAemter` (client log
  strings), the net.c globals `nt_LastRequCount` and `cm_LastSyncCount` (named inside `nt_Recv`'s messages),
  and the file `Units/net/net.c` (`D:\develop\units\net\net.c` in both clients).
- **Prefixes:** `srv_` is attested in server.dll (`srv_RecvGame(): Can't load Counter`; `srv_LoadBuf` is also in
  the image), so the server.c helpers keep it. `nt_` and `rd_` are the clients' attested prefixes of net.c and
  plant.c's building-site code, the TUs these ports come from. No `tb_` name remains (the timer unit is not
  built). The vfs strings `vfs:AddFile`, `vfs:FinishedFiles`, `vfs:IGetSubDir` and `vfs:Open` are `m_alloc`
  block labels, not function names: `vfs_Tfopen` allocates under `vfs:Open`.
- **Renamed:** `ls_SaveBuildings` to `ls_SaveBuildingEntityState`, the writer of `ls_LoadBuildingEntityState`
  like the other `ls_Save*`/`ls_Load*` pairs (no row, so an identifier edit: `rebrew source rename` finds no
  function); local types `OfficePick`, `sim_finddata`, `TownRec`, `Town` to `OFFICE_PICK`, `SIM_FINDDATA`,
  `TOWN_REC`, `TOWN`.
- **`zufall.c` (file name inferred).** No `__FILE__` string names the random-helper TU. The original links
  objects in file-name order (server.c, aemter.c, ... sim.c, spiel.c) and this object links after spiel.c,
  so its name sorts after `spiel.c`; `zufall.c` (German "chance") meets that and nothing more. The TU has no
  attested prefix, so by the rule above its functions should be unprefixed (`RandomMod`, `SeedRandom`, ...),
  but `rebrew source rename` refuses `gm_RandomFloat01`, `gm_RandomQuadratic` and `srv_SeedRandomWithTime`
  (ambiguous references to independent client symbols in spiel.c, friedhof_logic.c and
  alchemistry_logic.c) and finds no row for `gm_RandomRange` and `gm_RandomFloat01Squared`, so the set keeps
  its names until the client symbols are separated: `gm_RandomMod`, `gm_RandomRange`, `gm_RandomFloat01`,
  `gm_RandomQuadratic`, `gm_RandomFloat01Squared`, `srv_SeedRandomWithTime`, `srv_SeedRandom`, all inferred.
- **Stand-ins:** `g_gap_10035410` is a 28-byte layout span with no proven owner; `gm_GetSlotBase` reads its
  first dword (a float scale) and `sim_NextServiceBuilding` its dword at +0x18 (a scan cursor). The two
  objects keep the span's name until their allocation and extent are known (Global ownership in AGENTS.md).
  `g_gap_10034684` (5f) is referenced only by docs.

Every other name the rounds added is inferred: module prefix of the TU it sits in plus `VerbNoun`, or the
unit's own style (`m_` snake case in m_alloc.c, `nt_` globals in net.c, unprefixed in Error.c and
broadcast.c). TL VA from the sweep table or the definition's comment.

| Name | File | TL VA |
|---|---|---|
| `ahm_CalcTraitBonus` | `DieGildeAddOn/game/alchemistry_logic.c` | 0x4f0eb0 |
| `ahm_CalcTraitLimits` | `DieGildeAddOn/game/alchemistry_logic.c` | 0x4f0f60 |
| `ahm_CanAffordUpgrade` | `DieGildeAddOn/game/alchemistry_logic.c` | 0x4f0ff0 |
| `ahm_CompareBestWorkers` | `DieGildeAddOn/game/alchemistry_logic.c` | 0x4f14c0 |
| `ahm_CountBusyWorkers` | `DieGildeAddOn/game/alchemistry_logic.c` | 0x4f13a0 |
| `ahm_CountUnusedAvatars` | `DieGildeAddOn/game/alchemistry_logic.c` | see source |
| `ahm_FindAvatar` | `DieGildeAddOn/game/alchemistry_logic.c` | 0x4eefe0 |
| `ahm_FindRecipeSlot` | `DieGildeAddOn/game/alchemistry_logic.c` | 0x4f0930 |
| `ahm_FindRecipeSlotImpl` | `DieGildeAddOn/game/alchemistry_logic.c` | 0x4ec950 |
| `ahm_fio_LoadAvatars` | `DieGildeAddOn/game/alchemistry_logic.c` | 0x4ef0d0 |
| `ahm_fio_SaveAhmInfo` | `DieGildeAddOn/game/alchemistry_logic.c` | 0x4eed10 |
| `ahm_fio_SaveAvatars` | `DieGildeAddOn/game/alchemistry_logic.c` | 0x4ef040 |
| `ahm_GetBrewTime` | `DieGildeAddOn/game/alchemistry_logic.c` | 0x4eccd0 |
| `ahm_GetBrewTimeTenth` | `DieGildeAddOn/game/alchemistry_logic.c` | see source |
| `ahm_GetBrewYield` | `DieGildeAddOn/game/alchemistry_logic.c` | 0x4ecd20 |
| `ahm_GetLabRisk` | `DieGildeAddOn/game/alchemistry_logic.c` | 0x4f11c0 |
| `ahm_GetLabUpgrades` | `DieGildeAddOn/game/alchemistry_logic.c` | 0x4f10d0 |
| `ahm_GetLabYieldFactor` | `DieGildeAddOn/game/alchemistry_logic.c` | 0x4f1290 |
| `ahm_GetQualityShare` | `DieGildeAddOn/game/alchemistry_logic.c` | 0x4ece30 |
| `ahm_GetRecipeBonus` | `DieGildeAddOn/game/alchemistry_logic.c` | 0x4eceb0 |
| `ahm_GetRecipeQuality` | `DieGildeAddOn/game/alchemistry_logic.c` | 0x4ec8a0 |
| `ahm_HasFreeRecipeSeat` | `DieGildeAddOn/game/alchemistry_logic.c` | 0x4ec9a0 |
| `ahm_PickBestWorker` | `DieGildeAddOn/game/alchemistry_logic.c` | 0x4f1450 |
| `amt_CanUpgradeBuildingTier1` | `DieGildeAddOn/game/aemter.c` | 0x4eb220 |
| `amt_CanUpgradeBuildingTier2` | `DieGildeAddOn/game/aemter.c` | 0x4eb260 |
| `amt_CanUpgradeBuildingTier3` | `DieGildeAddOn/game/aemter.c` | 0x4eb320 |
| `amt_CountTownHallSeats` | `DieGildeAddOn/game/aemter.c` | 0x4ec810 |
| `amt_ExpandSlots` | `DieGildeAddOn/game/aemter.c` | 0x4e9500 |
| `amt_FindVacantRoleBelow` | `DieGildeAddOn/game/aemter.c` | 0x4e9530 |
| `amt_GetGroupVacancyFlags` | `DieGildeAddOn/game/aemter.c` | 0x4ea130 |
| `amt_GetOfficeAffinity` | `DieGildeAddOnServer/server.c` | 0x4e7c70 |
| `amt_GetRankLimits` | `DieGildeAddOn/game/aemter.c` | 0x4e9580 |
| `amt_GetRoleGroup` | `DieGildeAddOn/game/aemter.c` | 0x4e8ad0 |
| `amt_GetRoleHolder` | `DieGildeAddOn/game/aemter.c` | 0x4e90d0 |
| `amt_GetRoleLevel` | `DieGildeAddOn/game/aemter.c` | 0x4e99c0 |
| `amt_GetRoleTemplate` | `DieGildeAddOn/game/aemter.c` | 0x4e8b40 |
| `amt_GetSlotByRole` | `DieGildeAddOn/game/aemter.c` | 0x4e8a80 |
| `amt_GetSlotByType` | `DieGildeAddOn/game/aemter.c` | 0x4e8af0 |
| `amt_GetSuperiorHolder` | `DieGildeAddOn/game/aemter.c` | 0x4e9110 |
| `amt_GetTownHallHolder` | `DieGildeAddOn/game/aemter.c` | 0x4ec7d0 |
| `amt_HasCouncilHolder` | `DieGildeAddOn/game/aemter.c` | 0x4ea460 |
| `amt_HasIdleSuperior` | `DieGildeAddOn/game/aemter.c` | 0x4e9270 |
| `amt_IsNextRoleStep` | `DieGildeAddOn/game/aemter.c` | 0x4e9180 |
| `amt_IsPendingAssignment` | `DieGildeAddOn/game/aemter.c` | 0x4ea2b0 |
| `amt_ListCouncilSlots` | `DieGildeAddOn/game/aemter.c` | 0x4e8cb0 |
| `amt_ListHeldSlotsOfGroup` | `DieGildeAddOn/game/aemter.c` | 0x4e8c00 |
| `amt_ListPromotionRoles` | `DieGildeAddOn/game/aemter.c` | 0x4e93d0 |
| `amt_ListRolesOfLevel` | `DieGildeAddOn/game/aemter.c` | 0x4e9950 |
| `amt_ListSlotsOfGroup` | `DieGildeAddOn/game/aemter.c` | 0x4e8b80 |
| `amt_ListSuperiors` | `DieGildeAddOn/game/aemter.c` | 0x4e9310 |
| `amt_RankAllOffices` | `DieGildeAddOn/game/aemter.c` | 0x4e8ee0 |
| `amt_RankOpenOffices` | `DieGildeAddOn/game/aemter.c` | 0x4e8d10 |
| `CloseBroadcastSocket` | `Units/net/broadcast.c` | 0x402320 |
| `gm_AdvanceGameTime` | `DieGildeAddOn/game/spiel.c` | 0x500de0 |
| `gm_AmountToUnits` | `DieGildeAddOn/game/spiel.c` | 0x50b710 |
| `gm_AmountToUnitsById` | `DieGildeAddOn/game/spiel.c` | 0x50b7a0 |
| `gm_BlendWeights` | `DieGildeAddOn/game/spiel.c` | 0x507ed0 |
| `gm_CalcFortuneTax` | `DieGildeAddOn/game/spiel.c` | 0x50ddf0 |
| `gm_CanMarry` | `DieGildeAddOn/game/spiel.c` | 0x509480 |
| `gm_CollectBuildingResidents` | `DieGildeAddOn/game/spiel.c` | 0x505d00 |
| `gm_CompareGameTime` | `DieGildeAddOn/game/spiel.c` | 0x500cb0 |
| `gm_CountChildren` | `DieGildeAddOn/game/spiel.c` | 0x5095d0 |
| `gm_CountHouseUpgradesA` | `DieGildeAddOn/game/spiel.c` | 0x510400 |
| `gm_CountHouseUpgradesB` | `DieGildeAddOn/game/spiel.c` | 0x510470 |
| `gm_CountHouseUpgradesC` | `DieGildeAddOn/game/spiel.c` | 0x510500 |
| `gm_CountHouseUpgradesD` | `DieGildeAddOn/game/spiel.c` | 0x510550 |
| `gm_DaytimeMinutesBetween` | `DieGildeAddOn/game/spiel.c` | 0x50cad0 |
| `gm_EntityHasOffice` | `DieGildeAddOn/game/spiel.c` | 0x506e70 |
| `gm_EntityHasProfession` | `DieGildeAddOn/game/spiel.c` | see source |
| `gm_FindBuildingStore` | `DieGildeAddOn/game/spiel.c` | 0x5049a0 |
| `gm_FindBuildingTypeByName` | `DieGildeAddOn/game/spiel.c` | 0x504eb0 |
| `gm_FindItemTypeByName` | `DieGildeAddOn/game/spiel.c` | 0x501490 |
| `gm_FindKind47ByOwner` | `DieGildeAddOn/game/spiel.c` | 0x503e50 |
| `gm_FindNearestOfKind` | `DieGildeAddOn/game/spiel.c` | 0x504db0 |
| `gm_FindTavernServing` | `DieGildeAddOn/game/spiel.c` | 0x503d10 |
| `gm_FormatPrice` | `DieGildeAddOn/game/spiel.c` | 0x50bc10 |
| `gm_GameTimeMinutesBetween` | `DieGildeAddOn/game/spiel.c` | 0x500d20 |
| `gm_GetBirthday` | `DieGildeAddOn/game/spiel.c` | 0x509120 |
| `gm_GetBuildingFoodStock` | `DieGildeAddOn/game/spiel.c` | 0x50ce20 |
| `gm_GetBuildingLevel` | `DieGildeAddOn/game/spiel.c` | 0x50c4e0 |
| `gm_GetBuildingStock` | `DieGildeAddOn/game/spiel.c` | 0x50cce0 |
| `gm_GetBuildingWorth` | `DieGildeAddOn/game/spiel.c` | 0x50c5d0 |
| `gm_GetCouncilRank` | `DieGildeAddOn/game/spiel.c` | 0x508f80 |
| `gm_GetEntityAge` | `DieGildeAddOn/game/spiel.c` | 0x508e80 |
| `gm_GetEntityDate` | `DieGildeAddOn/game/spiel.c` | 0x509050 |
| `gm_GetEntityMood` | `DieGildeAddOn/game/spiel.c` | 0x50bfe0 |
| `gm_GetGameTime` | `DieGildeAddOn/game/spiel.c` | 0x500c80 |
| `gm_GetGuildBuildingKind` | `DieGildeAddOn/game/spiel.c` | 0x506f70 |
| `gm_GetGuildHall` | `DieGildeAddOn/game/spiel.c` | 0x50e4a0 |
| `gm_GetHappinessFactor` | `DieGildeAddOn/game/spiel.c` | 0x50bbb0 |
| `gm_GetItemCategory` | `DieGildeAddOn/game/spiel.c` | 0x5013c0 |
| `gm_GetItemGuild` | `DieGildeAddOn/game/spiel.c` | 0x507380 |
| `gm_GetKindRecord` | `DieGildeAddOn/game/spiel.c` | 0x508220 |
| `gm_GetKindStatRange` | `DieGildeAddOn/game/spiel.c` | 0x507910 |
| `gm_GetManufacturerRating` | `DieGildeAddOn/game/spiel.c` | 0x50b840 |
| `gm_GetObjektPrice` | `DieGildeAddOn/game/spiel.c` | 0x502780 |
| `gm_GetOfficeRank` | `DieGildeAddOn/game/spiel.c` | 0x508eb0 |
| `gm_GetPackedSeason` | `DieGildeAddOn/game/spiel.c` | 0x500e00 |
| `gm_GetRangeBuildingKind` | `DieGildeAddOn/game/spiel.c` | 0x507080 |
| `gm_GetRangeStatId` | `DieGildeAddOn/game/spiel.c` | 0x507400 |
| `gm_GetRelationship` | `DieGildeAddOn/game/spiel.c` | 0x50f950 |
| `gm_GetRichestFive` | `DieGildeAddOn/game/spiel.c` | 0x50e670 |
| `gm_GetSeason` | `DieGildeAddOn/game/spiel.c` | 0x500e20 |
| `gm_GetSeasonPrice` | `DieGildeAddOn/game/spiel.c` | 0x50bb50 |
| `gm_GetSeasonTreasury` | `DieGildeAddOn/game/spiel.c` | 0x50d320 |
| `gm_GetSkillPair` | `DieGildeAddOn/game/spiel.c` | 0x507130 |
| `gm_GetSlotBase` | `DieGildeAddOn/game/spiel.c` | 0x502450 |
| `gm_GetSlotPrice` | `DieGildeAddOn/game/spiel.c` | 0x5025a0 |
| `gm_GetSlotProduction` | `DieGildeAddOn/game/spiel.c` | 0x5024e0 |
| `gm_GetStatBuildingKind` | `DieGildeAddOn/game/spiel.c` | 0x506fd0 |
| `gm_GetStatFirstItem` | `DieGildeAddOn/game/spiel.c` | 0x5072c0 |
| `gm_GetStatRecord` | `DieGildeAddOn/game/spiel.c` | 0x506d50 |
| `gm_GetStoreItemField` | `DieGildeAddOn/game/spiel.c` | 0x50dfa0 |
| `gm_GetStoreRoom` | `DieGildeAddOn/game/spiel.c` | 0x50e170 |
| `gm_GetTileDistance` | `DieGildeAddOn/game/spiel.c` | 0x502820 |
| `gm_GetTypeGuild` | `DieGildeAddOn/game/spiel.c` | 0x50e520 |
| `gm_GetTypeProductValue` | `DieGildeAddOn/game/spiel.c` | 0x50d170 |
| `gm_GetWealthRank` | `DieGildeAddOn/game/spiel.c` | 0x50e600 |
| `gm_GetWorkshopStock` | `DieGildeAddOn/game/spiel.c` | 0x50de80 |
| `gm_HasGuildHall` | `DieGildeAddOn/game/spiel.c` | 0x5079f0 |
| `gm_HasLevelFor` | `DieGildeAddOn/game/spiel.c` | 0x50c550 |
| `gm_HasNoGuildHouse` | `DieGildeAddOn/game/spiel.c` | 0x510170 |
| `gm_IsRawItem` | `DieGildeAddOn/game/spiel.c` | 0x5014d0 |
| `gm_IsWarehouse` | `DieGildeAddOn/game/spiel.c` | 0x505340 |
| `gm_ListBuildingStores` | `DieGildeAddOn/game/spiel.c` | 0x50be50 |
| `gm_ListGuildHouses` | `DieGildeAddOn/game/spiel.c` | 0x50c490 |
| `gm_ListProducts` | `DieGildeAddOn/game/spiel.c` | 0x50bec0 |
| `gm_ListProductsAfter` | `DieGildeAddOn/game/spiel.c` | 0x50bf30 |
| `gm_ListTypesOfKind` | `DieGildeAddOn/game/spiel.c` | 0x504ef0 |
| `gm_MapItemPairRange` | `DieGildeAddOn/game/spiel.c` | 0x507c30 |
| `gm_NextQueryItemMatch` | `DieGildeAddOn/game/spiel.c` | 0x502a20 |
| `gm_PackGameTime` | `DieGildeAddOn/game/spiel.c` | 0x500d60 |
| `gm_RandomFloat01Squared` | `DieGildeAddOn/game/zufall.c` | see source |
| `gm_RandomRange` | `DieGildeAddOn/game/zufall.c` | see source |
| `gm_RefreshSeasonSlots` | `DieGildeAddOn/game/spiel.c` | 0x5016f0 |
| `gm_ResolveEntityRecord` | `DieGildeAddOn/game/spiel.c` | 0x50d430 |
| `gm_ResolveEntitySlot` | `DieGildeAddOn/game/spiel.c` | 0x50d4f0 |
| `gm_RingGuildHallBell` | `DieGildeAddOn/game/spiel.c` | 0x507ab0 |
| `gm_ShuffleBytes` | `DieGildeAddOn/game/spiel.c` | 0x508c30 |
| `gm_SlotKindIsOneOf` | `DieGildeAddOn/game/spiel.c` | 0x506ee0 |
| `gm_SumProductPoints` | `DieGildeAddOn/game/spiel.c` | 0x50c710 |
| `gm_SumSlotTreasury` | `DieGildeAddOn/game/spiel.c` | 0x50d360 |
| `gm_SumStoreCount` | `DieGildeAddOn/game/spiel.c` | 0x50b810 |
| `gm_SumTreasury` | `DieGildeAddOn/game/spiel.c` | 0x50d2f0 |
| `gm_SumTypePoints` | `DieGildeAddOn/game/spiel.c` | 0x50c7d0 |
| `gm_UnitsToAmount` | `DieGildeAddOn/game/spiel.c` | see source |
| `gm_UnitsToAmountById` | `DieGildeAddOn/game/spiel.c` | 0x50b780 |
| `gm_UnpackGameTime` | `DieGildeAddOn/game/spiel.c` | 0x500db0 |
| `gv_eval_HasWorker` | `DieGildeAddOn/game/friedhof_logic.c` | 0x4f1840 |
| `gv_eval_HasWorkerId` | `DieGildeAddOn/game/friedhof_logic.c` | 0x4f1890 |
| `gv_eval_SameField` | `DieGildeAddOn/game/friedhof_logic.c` | 0x4f17f0 |
| `gv_eval_SameOwner` | `DieGildeAddOn/game/friedhof_logic.c` | 0x4f1820 |
| `gv_eval_SlotBelegt` | `DieGildeAddOn/game/friedhof_logic.c` | see source |
| `gv_FindWorkerSlot` | `DieGildeAddOn/game/friedhof_logic.c` | 0x4f1a10 |
| `gv_fio_SaveGraveyardData` | `DieGildeAddOn/loadsave/loadsave.c` | 0x4f3900 |
| `gv_GetSlotEntryIndex` | `DieGildeAddOn/game/friedhof_logic.c` | 0x4f1790 |
| `gv_GetUpgradeBonus` | `DieGildeAddOn/game/friedhof_logic.c` | 0x4f3800 |
| `gv_HasGravediggerRoom` | `DieGildeAddOn/game/friedhof_logic.c` | 0x4f3e60 |
| `LogMessage` | `Units/Error/Error.c` | 0x41daf0 |
| `ls_LoadRelationships` | `DieGildeAddOn/loadsave/loadsave.c` | 0x524610 |
| `ls_SaveDynamicEntities` | `DieGildeAddOn/loadsave/loadsave.c` | 0x51f170 |
| `ls_SaveEntities` | `DieGildeAddOn/loadsave/loadsave.c` | 0x51f480 |
| `ls_SaveObjects` | `DieGildeAddOn/loadsave/loadsave.c` | 0x51ebc0 |
| `ls_SaveRelationships` | `DieGildeAddOn/loadsave/loadsave.c` | 0x520860 |
| `ls_SaveTownData` | `DieGildeAddOn/loadsave/loadsave.c` | 0x520310 |
| `m_is_tracked` | `Units/m_alloc/m_alloc.c` | 0x41dd90 |
| `m_pool_clear` | `Units/m_alloc/m_alloc.c` | 0x41e440 |
| `m_pool_first` | `Units/m_alloc/m_alloc.c` | 0x41e3e0 |
| `m_pool_free_all` | `Units/m_alloc/m_alloc.c` | 0x41e410 |
| `m_pool_info` | `Units/m_alloc/m_alloc.c` | 0x41e490 |
| `m_pool_next` | `Units/m_alloc/m_alloc.c` | 0x41e350 |
| `m_pool_stats` | `Units/m_alloc/m_alloc.c` | 0x41e4d0 |
| `nt_Connect` | `Units/net/net.c` | 0x420db0 |
| `nt_CountCmd` | `Units/net/net.c` | 0x420ba0 |
| `nt_Disconnect` | `Units/net/net.c` | 0x421050 |
| `nt_FormatStats` | `Units/net/net.c` | 0x420bf0 |
| `nt_GetLocalIp` | `Units/net/net.c` | 0x420d20 |
| `nt_LogWinsockError` | `Units/net/net.c` | 0x4208a0 |
| `nt_ResetStats` | `Units/net/net.c` | 0x420b70 |
| `nt_Send` | `Units/net/net.c` | 0x421290 |
| `plt_FindRecordById` | `DieGildeAddOn/auxillary/plant.c` | 0x4bcc50 |
| `plt_FindRecordByOwner` | `DieGildeAddOn/auxillary/plant.c` | 0x4bcc20 |
| `rd_AddBKBox` | `DieGildeAddOn/auxillary/plant.c` | 0x4bd1e0 |
| `ReportError` | `Units/Error/Error.c` | 0x41d950 |
| `sim_ClaimResident` | `DieGildeAddOn/game/sim.c` | 0x500240 |
| `sim_IsUnderage` | `DieGildeAddOn/game/sim.c` | 0x4fffb0 |
| `sim_IsUnrelated` | `DieGildeAddOn/game/sim.c` | 0x4ff860 |
| `sim_NextServiceBuilding` | `DieGildeAddOn/game/sim.c` | 0x500480 |
| `sim_WalkDirectory` | `DieGildeAddOn/game/sim.c` | 0x500660 |
| `srv_FormatStatAttributes` | `DieGildeAddOnServer/server.c` | 0x4e7490 |
| `srv_FormatStatDumpBegin` | `DieGildeAddOnServer/server.c` | 0x4e73c0 |
| `srv_FormatStatDumpEnd` | `DieGildeAddOnServer/server.c` | 0x4e77e0 |
| `srv_FormatStatSkills` | `DieGildeAddOnServer/server.c` | 0x4e7550 |
| `srv_GetEntityCouncilSlot` | `DieGildeAddOnServer/server.c` | 0x4e7bf0 |
| `srv_GetEntityOfficeSlot` | `DieGildeAddOnServer/server.c` | 0x4e7b70 |
| `vfs_AddFile` | `Units/vfs/vfs.c` | see source |
| `vfs_AddPath` | `Units/vfs/vfs.c` | see source |
| `vfs_CompareFiles` | `Units/vfs/vfs.c` | see source |
| `vfs_CompareFilesNoCase` | `Units/vfs/vfs.c` | see source |
| `vfs_CompareKey` | `Units/vfs/vfs.c` | see source |
| `vfs_CompareKeyNoCase` | `Units/vfs/vfs.c` | see source |
| `vfs_CompareNames` | `Units/vfs/vfs.c` | see source |
| `vfs_exit` (inferred) | `Units/vfs/vfs.c` | TL 0x4310f0 / GOLD 0x431510 |
| `vfs_fgetc` | `Units/vfs/vfs.c` | 0x430870 |
| `vfs_fgets` | `Units/vfs/vfs.c` | 0x4308a0 |
| `vfs_FindDir` | `Units/vfs/vfs.c` | see source |
| `vfs_FindFile` | `Units/vfs/vfs.c` | see source |
| `vfs_FinishFiles` | `Units/vfs/vfs.c` | see source |
| `vfs_ForEachFile` | `Units/vfs/vfs.c` | 0x430f70 |
| `vfs_FreeDirs` (inferred) | `Units/vfs/vfs.c` | TL 0x42fc50 / GOLD 0x430260 |
| `vfs_ftell` | `Units/vfs/vfs.c` | 0x430c50 |
| `vfs_fwrite` (inferred) | `Units/vfs/vfs.c` | TL 0x430910 / GOLD 0x430e30 |
| `vfs_GetDirPath` | `Units/vfs/vfs.c` | see source |
| `vfs_GetDirPathOf` | `Units/vfs/vfs.c` | see source |
| `vfs_GetFilePath` | `Units/vfs/vfs.c` | see source |
| `vfs_GetFilePathOf` | `Units/vfs/vfs.c` | see source |
| `vfs_GetRelativePath` | `Units/vfs/vfs.c` | see source |
| `vfs_GetSubDir` | `Units/vfs/vfs.c` | see source |
| `vfs_LookupPath` | `Units/vfs/vfs.c` | see source |
| `vfs_MakeDirs` | `Units/vfs/vfs.c` | see source |
| `vfs_NormalizeCase` | `Units/vfs/vfs.c` | see source |
| `vfs_RemoveFile` | `Units/vfs/vfs.c` | see source |
| `vfs_ScanArchive` | `Units/vfs/vfs.c` | see source |
| `vfs_ScanDir` | `Units/vfs/vfs.c` | see source |
| `vfs_ToBackslashes` | `Units/vfs/vfs.c` | see source |
| `vfs_ToSlashes` | `Units/vfs/vfs.c` | see source |
| `ls_SaveBuildingEntityState` | `DieGildeAddOn/loadsave/loadsave.c` | 0x51ecf0 |
| globals `g_vfs_root`, `g_vfs_item_pool`, `g_vfs_case_sensitive` | `Units/vfs/vfs.c` | 0x6b7fdc, 0x6b7fe0, 0x6b7fe8 |
| globals `nt_WsaStarted`, `nt_LocalIp`, `nt_RecvBytes`, `nt_RecvPackets`, `nt_SendBytes`, `nt_SendPackets`, `nt_Socket`, `nt_RecvDone`, `nt_SendDone`, `nt_Closed`, `nt_CmdStats` | `Units/net/net.c` | see source |
| types `VFS_DIR`, `VFS_FILE`, `VFS_ITEM` | `Units/vfs/vfs.c` | |
| types `BK_BOX`, `BK_VERTEX`, `BK_GET_VERTICES` | `DieGildeAddOn/auxillary/plant.c` | |
| types `OFFICE_PICK`, `OFFICE_RANK_LIMITS` | `DieGildeAddOn/game/aemter.c` | |
| types `STOCK`, `STAT_REC`, `PACKED_TIME`, `KIND_REC`, `SLOT_COPY`; macro `gm_SEASON_TABLES` | `DieGildeAddOn/game/spiel.c` | |
| types `SIM_FINDDATA` | `DieGildeAddOn/game/sim.c` | |
| types `TOWN`, `TOWN_REC` | `DieGildeAddOn/loadsave/loadsave.c` | |
| macros `NT_CMD_LEN`, `NT_CMD_HEADER` | `Units/net/net.c` | |
| file `references/minizip/unzip.c` | minizip 0.15 plus the game's `unzGetFilePos`/`unzGoToFilePos` (`vendoring.md`) | |

### Renames from the identifier audit (2026-10-08)

Older docs (`TODO.md`, `codegen-walls.md`, the `msvc6-*.md` records) keep the names in use when they were
written. This table maps them to the current names. Evidence and grades are in the inferred-name table
below; `attested` entries are also in the attested table above.

| Image | VA | Old name | Current name | Grade |
|---|---|---|---|---|
| server.dll | `0x100146c0` | `lb_SendLobbyConfig` | `lb_ExPlayerReadyStatus` | attested |
| server.dll | `0x1000f980` | `cm_ExCreateCitizen` | `cm_ExAllocCharacter` | attested |
| server.dll | `0x10022107` | `crtLoadWinAPI` | `__crtMessageBoxA` | attested (LIBCMT exports `___crtMessageBoxA`; the `pfnMessageBoxA` rows are its function statics `?pfnMessageBoxA@?1??__crtMessageBoxA@@9@9`) |
| server.dll | `0x1000a9a0` | `cm_QueuePlayerCommand` | `srv_PutConnSCommand` | strong |
| server.dll, GOLD `0x00503e80`, TL `0x00506cd0` | `0x100180d0` | `gm_InitEntitySlots` | `gm_KillAllSpieler` | strong |
| server.dll | `0x10019720` | `gm_CalculateProductionValue` | `eval_ObjektPreis2Credits` | strong |
| server.dll | `0x1000ef90` | `cm_ChainAssignId` | `cm_ExSetHE` | strong |
| server.dll | `0x1000efb0` | `cm_ExSetSyncFlags` | `cm_ExSysMessage` | strong |
| server.dll | `0x1000f080` | `cm_AssignSequenceCounter` | `cm_ExAddStraftat` | strong |
| server.dll | `0x1000f0a0` | `cm_AssignEntityId` | `cm_ExAllocCutscene` | strong |
| server.dll | `0x1000d7f0` | `cm_ExTransferCurrency` | `cm_ExMoveCredits` | strong |
| server.dll | `0x1000ff60` | `cm_ExCutsceneUpdate` | `cm_ExCutsceneReady` | strong |
| TL | `0x0044c460` | `cm_ExCreateCitizen` (bound to the server body) | `d3_LoadObjectAnim` (own STUB file) | attested |
| TL | `0x00406560` | `cm_ExCutsceneUpdate` | `CharacterClearSitting` | weak |

Native action-name evidence (2026-10-10): TL initializer `0x004a1130`
registers literal `Buergerrecht` at `0x0067edf8` with starter `0x00499a50`
and run handler `0x00499ad0`. This attests the action name only; neither an
original C function name nor a module prefix/source path is established.
The disproven `ahm_ProcessEntityChain` binding at the starter VA was removed;
that shared dispatcher remains at TL `0x004c4d30`, GOLD `0x004c43c0` and
SERVER `0x1000ca00`. Evidence: `.scratch/goal20/citizenship-registration.json`
and `canonical-chain-measurements.json`.

Recovered as inferred `PrepareBuergerrecht`, an unprefixed English verb with
the attested German action noun. The one shared body lives provisionally at
`src/GOLDTL.PrepareBuergerrecht.c`; its original unit is unknown, so no source
path or module prefix is invented. Both TL499a50 and GOLD49a010 have125-byte
RELOC verdicts. GOLD initializer4a16f0 independently binds literal600190 to
the same action/starter. The initializer's reference and four-argument
declaration are updated; original function-name spelling remains unattested.

Shared plant lookup reconciliation (2026-10-11): `plt_FindPlantInfo` is an
inferred module/VerbNoun name replacing the unrelated `lb_SearchRecordTable`
label at SERVER10014ee0, TL4bcb80 and GOLD4bc5a0. The attested `plt_SetPlantMap`
log and `DieGildeAddOn\\auxillary\\plant.c` path establish the plant subsystem;
its `PlantInfo not found` wording supports the noun, not the exact helper name.
`plt_PlantInfo` is likewise an inferred module/CamelCase name for the initialized
four-record table at SERVER1002d878, TL6814a8 and GOLD602840. All three identities
bind the same existing definition in `plant.c`, including the zero-id terminator.
`plant.h` is a reconstructed canonical declaration home, not an attested header
path. Layout-span names remain inventory names, and the meanings of the table's
f42/f43/f44 fields remain unresolved. Evidence: `.scratch/goal20/plant-lookup-audit.json`.

Shared slot-helper reconciliation (2026-10-11): TL50dac0 and GOLD50a640 now
reuse the existing inferred `gm_WalkEntityChain` name and spiel.c definition
instead of the numeric `fcn_0050dac0` duplicate. Complete native/body evidence
proves the shared 124-byte helper, not an original-symbol spelling. The
unsigned-short formal is supported by both callee and formatter code.
`spiel.h` is a reconstructed declaration home; no original header path is
claimed. The 52 caller files retain their existing names and function bodies.
Evidence: `.scratch/goal20/stat-helper-replay.json` and
`stat-helper-after-final-prototype/`.

Shared statistic formatter reconciliation (2026-10-11): the inferred names
`srv_FormatStatAttributes` (TL4e7490/GOLD4e5980), `srv_FormatStatSkills`
(TL4e7550/GOLD4e5a40) and `srv_FormatStatTreasury` (TL4e7600/GOLD4e5af0)
identify three adjacent members of the client statistic family. Both clients
now use the same server.c bodies; exact original names and the client-only
source-unit placement remain inferred. `server_stats.h` is a reconstructed
canonical declaration home, not an attested original path. The treasury row
formerly called `srv_Init` was false; the independent SERVER10009d30 initializer
keeps its name and body. `str_i_tab_i_tab_i_tab_i_tab_i_tab` is a compiler-literal
content label for the complete 16-byte five-integer skills format at TL68d924,
not a source identifier or another allocation. Evidence:
`.scratch/goal20/stat-pair-gold-import.json`, `stat-treasury-identity-repair.json`
and `stat-skills-literal-repair.json`.

Office statistic recovery (2026-10-11): `srv_FormatStatAemter`
(TL4e75a0/GOLD4e5a90, 87 bytes) is inferred from its four office-role fields
and neighboring statistic formatters. It now shares the server_stats.c body and
server_stats.h prototype. `aemter.h` is a reconstructed declaration home for
the role-label pointers, not evidence of their original storage owner or an
attested header path. The unresolved table keeps its existing inventory label
`g_14a5c6c` until ownership/name evidence is recovered.
`str_s_tab_s_tab_s_tab_s_tab` labels the complete 13-byte compiler format at
TL68d934; it is not a source identifier. The separate client-only unit placement
is inferred: a direct server.c inclusion failed LINK because the table has no
verified server provider. This result does not establish its original source
unit or authorize a server allocation. Evidence:
`.scratch/goal20/stat-offices-probe/receipt.json` and
`stat-offices-gold-import.json`.

Statistic delimiter reconciliation (2026-10-11): the existing inferred names
`srv_FormatStatDumpBegin` (TL4e73c0) and `srv_FormatStatDumpEnd` (TL4e77e0)
now identify the shared34-byte server.c bodies. Their original names/source
placement remain inferred; no Gold counterpart is established. The complete
formats atTL68d870/68d968 use compiler-literal content labels
`str_begin_statistic_dump_round`/`str_end_statistic_dump_round`, not source
identifiers. The existing packed calendar analysis label `g_7f4c00` is retained:
its `_g_current_year` link spelling describes the first-four-byte scalar view
used by these bodies. That existing shared C spelling is inferred, not an
original symbol or a second allocation. The backing owner and complete extent
remain unresolved. Evidence: `.scratch/goal20/stat-delimiters-probe-final/receipt.json`
and `stat-delimiters-final-native.json`.

Office-query reconciliation (2026-10-11): existing inferred names
`srv_GetEntityOfficeSlot` (TL4e7b70/Gold4e6030),
`srv_GetEntityCouncilSlot` (TL4e7bf0 only), and `amt_GetOfficeAffinity`
(TL4e7c70/Gold4e60b0) identify one shared server.c body each. Neither the
names, original parameter domain types nor their original unit placement
are attested by these byte matches. `aemter.h` holds their canonical current
prototypes; the void* row outputs retain the reconstructed ABI pending type
recovery. Existing client declaration labels g_9a9220/g_68da68/g_68d9a0
remain analysis labels. Verified native link spellings bind the shared office
tables without creating allocation owners. No Gold council name/VA is invented.
Evidence: `.scratch/goal20/office-query-scope-final.json`.

Identity-statistic reconciliation (2026-10-11): `srv_FormatStatIdentity`
(TL4e73f0/Gold4e58e0,159 bytes) is inferred from the first statistic columns,
not an attested original symbol. Its shared body and prototype now live in
the reconstructed client-only server_stats.c/server_stats.h. The old numeric
single-body unit is retired after both target verifications. Existing class
and runtime-name declaration labels remain analysis names with unresolved
allocation owners/extents. `str_stat_identity_columns` is a content label
for the37-byte compiler literal, not a source identifier. The existing C
spelling `g_current_year` binds Gold's native scalar view at770ae0; the
broader `g_7f4c00` inventory is unchanged. No SERVER counterpart is claimed.
Evidence: `.scratch/goal20/stat-identity-shared-probe/receipt.json` and
`stat-identity-retirement.json`.

Pool helper reconciliation (2026-10-11): TL41e440/41e490/41e4d0 now use
the existing inferred names `m_pool_clear`, `m_pool_info`, `m_pool_stats`
and their single shared m_alloc.c definitions, replacing the corresponding
numeric-source owners. These are source/naming consolidations of existing
EXACT functions, not new original-symbol attestations. No caller or header
declaration needs changing: the superseded symbols had no source users.
Block layout/field names remain reconstructed; no Gold identity or allocation
owner is inferred. The first/free-all and iterator family retains its saved
native proof and blocker pending the wider declaration/caller reconciliation.
Evidence: `.scratch/goal20/pool-clear-info-stats-retirement.json`.

### Random unit ownership reconciliation (2026-10-11)

The earlier random-modulo consolidation's source bindings became stale after
later tree changes. SERVER1001a0d0, TL42e410 and Gold42ec00 now all name the
unchanged `DieGildeAddOn/game/zufall.c` definition. Seven TL and six Gold
helpers share that unit; eight duplicate sources are retired. The existing
gm_/srv_ spellings and `zufall.c` remain inferred, with no original-symbol or
file-name attestation. Canonical declarations and caller prototype narrowing
remain open; the caller bindings preserve existing types. No Gold range
counterpart is established, so no Gold range address is invented. TL42e430 has a complete
22-byte native range body, ten alignment NOPs and a verified call to TL42e410.
Evidence: `.scratch/goal20/random-consolidation/scope-final.json` and
`.scratch/goal20/random-unit-probe/native-proof-catalog-corrected.json`.

### Alchemy helper declaration reconciliation (2026-10-11)

`ahm_SlotClearMatch` retains its existing inferred name and shared definition.
The reconstructed `alchemistry_logic.h` supplies its canonical current
`int(char*, char*, char*)` prototype to that definition and command.c;
the original header name and domain parameter types are not attested.
All three native bodies return zero/one. Twelve compiler contexts and 642
body/typed-operand measurements preserve the existing bytes and callers.
The separate client sound wrapper's use of `ahm_AllocateEntitySlot` is a false
binding to a four-argument sound helper; the genuine SERVER three-argument
alchemy name must remain separate until the client identity is repaired.
Evidence: `.scratch/goal20/ahm-prototype-contexts/scope-final.json` and
`next-sound-binding-audit.json`.

### Client animation sound identities (2026-10-11)

`PlayCharacterAniSound` is attested by the diagnostic owned by the complete
206-byte native TL40cee0/GOLD40bfc0 function; the compiler literal bytes and
all relocated operands were verified. Its shared reconstructed file is
`src/PlayCharacterAniSound.c`; the original compilation-unit path is unproven.
The registered callback at TL40ce80/GOLD40bf60 is now inferred
`PlayEntitySound`, shared in the correspondingly named reconstructed file.
It creates a voice and starts a positional sound with range3000/1000 and
volume127. Its previous `cm_ChkSetGebBesitzer` name and copied SERVER validator
comment were false. Likewise its four-argument sound callee is the existing
`fcn_004193f0`, unrelated to SERVER's three-argument `ahm_AllocateEntitySlot`.
The genuine SERVER command names and dispatch table are preserved.
`client_sound.h` provides both canonical current prototypes. Native numeric
sound data views still lack proven original identifiers/storage owners; no
new allocations are inferred from the declaration-file move. The voice-start
callee remains source-unbound, and GOLD's pan helper has a distinct matrix
call ABI, so neither a complete shared pan alias nor full client link is claimed.
Evidence: `.scratch/goal20/sound-wrapper/scope-final.json`.

### Shared table-search helper (2026-10-11)

`FindTableEntryIndex` at TL44d7b0/GOLD44eeb0 is an inferred descriptive name
without an invented module prefix. Both complete38-byte native functions are
identical and use the existing TL C body in `src/FindTableEntryIndex.c`.
The original function/unit names, table domain and unused original parameters
remain unproven; the two used arguments are the target value and a caller-supplied
row table. The loop advances12 bytes per row, examines at most64 rows, stops at
0x28, and returns0x27 when missing. It checks equality before the terminator,
so a target value0x28 can return that row's index. No storage owner or array
allocation is inferred. The malformed GOLD placeholder's absolute-address
assumption and discarded first argument were false. Managed identity, the
verified shared import and both complete objects establish EXACT bytes.
Evidence: `.scratch/goal20/table-search-repair/scope-final.json`.

### Alchemy flag helper ownership (2026-10-11)

`ahm_CheckFlag` remains an inferred name. SERVER1000bda0, TL4ec850 and
GOLD4eaad0 share the unchanged `DieGildeAddOn/game/alchemistry_logic.c`
definition; the misleading TL `ahm_ResetEntityState.c` clone is retired.
The real reset helpers remain distinct. Both native client bodies are70 bytes
plus10 alignment NOPs. Clone/owner bytes and the typed table operand agree
in both client contexts, but11 native scheduling differences remain; this
consolidation does not establish client byte matching. Existing pointer/data
rows remain aliases/declarations with unresolved client backing storage;
no new allocation or original domain parameter type is inferred.
Evidence: `.scratch/goal20/ahm-flag-ownership/scope-final.json`.


### Character source placement (2026-10-11)

Seventeen existing character sources and the canonical `ch_motion.h` now live in
`Develop/DieGildeAddOn/game/`. Native character diagnostics, motion resource paths
and task callbacks support the subsystem grouping, not exact original filenames.
The attested `CharacterSitting` / `CharacterSitsDown` names and incomplete bodies
are preserved. `PlayCharacterAniSound` retains its attested spelling; inferred
helper names retain their recorded provenance. Several still-addressed functions
have directly attested diagnostic names and await a caller-aware rename pass.
Scene-transfer and take-object wrappers now use one shared body each in
`game/character.c`, preserving their different native field locations through
partial build-specific views. Evidence and 34-body preservation receipts:
`.scratch/goal20/character-placement/`.


### Shared character scene and script identities (2026-10-11)

`ch_MoveCharacter2Universe` (TL403bc0/GOLD4033c0) and `TakeObjectScript`
(TL40d410/GOLD40c4f0) are directly attested by diagnostic strings in both native
bodies. Their shared `character.c` compilation unit is inferred. The recovered
universe parameter is a pointer. The former `CHARACTER_SCENE_NODE_VIEW` and
`CHARACTER_DUMMY_VIEW` have been replaced by `D3_OBJECT`,
`D3_OBJECT_DRAW_DATA` and `D3_DRAW_PART` in the inferred `d3_object.h` header.
These names and their fields are inferred; complete native byte extents are
proven while unknown semantic fields remain byte regions. The former `eltern`
at +0x1cc was a mistaken parent interpretation and is now `kontext`.
`eltern` denotes the native tree parent at TL+0x1fc/GOLD+0x1f8.
`darstellungsflag` remains a neutral inferred bit name. The scene flag's exact renderer role is
unproven, so the former provisional `lit` label is replaced by a neutral name.
The six globals retain provisional legacy spellings in their canonical declaration
home; their original identifiers and allocation owners remain unknown. Conditional
helper aliases preserve independent native providers rather than inventing shared
identities. Strict full-body/operand and 141,320-case behavior evidence:
`.scratch/goal20/character-shared-pairs/`.

### Attested character function renames (2026-10-11)

These shared client definitions now use their original diagnostic spellings.
Each name has a direct native `push` of its diagnostic in both complete bodies;
the source declarations, callers and callback self-references were renamed together
through `rebrew source rename --all-modules`. Exact original compilation-unit
filenames, remaining local/type names and storage owners are still unresolved.

| Attested name | GOLDTL VA | GOLD VA | Standing |
| --- | --- | --- | --- |
| `ch_AttachMotion` | `0x404150` | `0x403950` | Renamed from `fcn_00404150`. |
| `ch_TakingObject` | `0x4068e0` | `0x405d40` | Renamed from `fcn_004068e0`. |
| `ch_DroppingObject` | `0x406b50` | `0x405fb0` | Renamed from `fcn_00406b50`. |
| `CreateCharacterAtDummy` | `0x40c9b0` | `0x40ba90` | Renamed from `fcn_0040c9b0`; preserve the unprefixed original. |
| `PlayCharacterAniScript` | `0x40cff0` | `0x40c0d0` | Renamed from `fcn_0040cff0`. |
| `PlayCharacterAniScriptInt` | `0x40d130` | `0x40c210` | Renamed from `fcn_0040d130`. |
| `SetCharacterCamera` | `0x40d8c0` | `0x40c9a0` | Renamed from `fcn_0040d8c0`. |

The integer script wrapper's own invalid-character diagnostic attests
`PlayCharacterAniScriptInt`; its other error message retains the original copied
`PlayCharacterAniScript` spelling. Neither diagnostic was edited. Instruction VAs,
literal VAs, complete native hashes and stock-library exclusions are recorded in
`.scratch/goal21/continuation/names-scope.json`. Compiler bodies and typed operands
are compared with only the seven symbol spellings normalized.


### Native D3 layout identities (2026-10-11)

Stable IDs `d3.object`, `d3.object_draw_data`, `d3.draw_part` live in managed
`rebrew-types.toml`; C type and header names follow the attested d3 subsystem
but their original spellings are unproven. Native allocation sizes are 0x228
for the scene object in both clients, TL0x1640/GOLD0x970 for draw data.
Four draw slots have TL0x4a4/GOLD0x198 stride. `teile`, `teile_anzahl`,
`zeichendaten`, `kontext`, `eltern`, `kinder`, `naechstes`, and `voriges`
are inferred German field spellings; unknown regions retain `unbekannt_*` names.
The `name` pointer is an accessed string prefix of a resource context, not a
claim that its backing allocation is a standalone C string.
Evidence: `.scratch/goal20/type-identity-layouts/native-evidence.json` and
`layout-bindings.json` (native extents plus target compiler sizeof/offsetof).

Allocator helper identity checkpoint (2026-10-11): the shared client tracking
check is TL 0x41dd90 / Gold 0x4225e0 (60 bytes); shared free-all is TL 0x41e410 /
Gold 0x422c60 (43 bytes). Both client providers now live under Units/m_alloc.
The existing inferred names m_is_tracked/m_pool_free_all in the table do not
attest original spellings. The four client identities and their callers now
bind to those canonical definitions in m_alloc.c through the public tools;
the two duplicate client helper files have been removed. The address-derived counter/pointer declarations are likewise
compatibility names. Native identity/operand evidence and metadata extent repair:
`.scratch/goal21/allocator-client-repair/baseline.json` and `scope-final.json`.


Shared allocator helper bindings (2026-10-11): m_TRACKED_SLOT_COUNT and
m_TRACKED_SLOTS are private build-time aliases for existing server/client
numeric declarations, not recovered developer names or additional globals.
One loop retains the native access order and register allocation in both
clients, the normal server build and a legacy-flag-off compile. Six shifted
native operand controls reject;
all four client helper bodies exactly retain 206 bytes. Names, declaration
ownership and removal of the compatibility bindings remain reconstruction
work. Evidence: `.scratch/goal21/shared-allocator-helpers/`.

### Deferred character position updates (2026-10-12)

`ch_UpdatePendingPositions` (TL403040/Gold402800) and `ch_SetPosition`
(TL402ab0/Gold4025c0) are inferred from their complete native bodies, not attested
strings. The update loop visits 768 character slots, checks the dirty position
bit and active universe, adds local offsets to the model position, respects the
task marker and clears the dirty bit. One shared loop matches all 149 bytes in
both clients. The setter takes a character, float vector and flag; Gold uses the
flag for two extra model updates, while TL ignores it. Those conditional calls
match the 118-byte Gold and 72-byte TL bodies. Both functions belong to the shared
`game/character.c`; declarations are canonical in `ch_motion.h`. The address-named
character table stays a declaration without a new storage-owner claim. Receipts:
`.scratch/goal21/character-pending-positions/`.

### Attached character model positions (2026-10-12)

`ch_UpdateAttachedModelPosition` is inferred from TL403e20/Gold403620, not
attested by a string. One shared 801-byte body in `game/character.c` updates the
model referenced through character offset0x124, its orientation and terrain
height, then caches the main model position. Its second argument is read as an
unsigned byte. The native x87 comparison accepts unordered height differences;
the C condition preserves that behavior. The zero-initialized float is an
existing global read, not a new constant or storage definition. The complete
bodies, all17 typed operands,14 rejecting binding controls and all24 literal
bytes agree in each client. The10 previous surrounding bodies remain unchanged.
Declarations are canonical in `ch_motion.h`; native callee spellings, field
names and storage ownership remain unresolved. Receipts:
`.scratch/goal21/character-pending-positions/attachment/`.

### Low-polygon character updates and animation options (2026-10-12)

The native TL diagnostic attests the exact spelling `ch_Updatelowpoly()` at
TL4033e0. Its partial C reconstruction now lives in shared `game/character.c`,
and four callers use the canonical declaration in `ch_motion.h`. The native
body is1156 bytes; the inventory's1168-byte span includes12 alignment bytes.
The current default-flags object emits1150 bytes and remains SIZE_MISMATCH.
Detailed/low-polygon block ordering and pointer reuse still need matching; no
complete byte-match, proof, Gold counterpart binding or new data verdict is
claimed. The stock CRT supplies strstr/sprintf.

The two identical private animation-option definitions are replaced by one
inferred `D3_ANIMATION_OPTIONS` in `Units/d3/d3_animation.h`. Both client
compilers check sizeof12 and offsets mode0/layer1/pad2=2/pad8=9; native calls
pass three DWORDs by value. All eight old animation bodies and typed operands,
and all24 surrounding bodies across12 contexts, are unchanged. The type and
field spellings remain inferred; this argument layout allocates no global
storage. Receipts: `.scratch/goal21/character-lowpoly/`.

Broader checks also confirm that Gold40cba0/40cf10 already matched their full
55/183-byte bodies: both catalog sizes included nine trailing alignment NOPs.
All13 typed operands and rejecting bindings agree. Corrected size metadata
removes those pre-existing SIZE_MISMATCH verdicts without changing their C or
introducing a new function identity.
