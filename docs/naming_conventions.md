# Original Developer Naming Conventions

Attested diagnostic/path spellings win, including original errors. Otherwise
use an evidenced module prefix and VerbNoun; units without a prefix stay
unprefixed. Globals follow original module/German pointer conventions, not a
new `g_` scheme. Mark inferred names and keep compiler literals separate from
named source storage. Rename through Rebrew, then verify affected targets.

Rules: [prefixes](#module-prefix-system), [functions](#function-naming),
[variables](#variable-naming), [types](#struct-naming),
[constants](#enum--constant-naming). The ledger below preserves native addresses,
attestation limits and receipts; a descriptive role is not automatically an
original identifier. Implementation and debt statements describe each entry's
checkpoint; query metadata and [current work](TODO.md) before continuing it.
[Source layout](source-layout.md) owns placement guidance.

## Recent findings

### Five attested names settled against their counterparts (2026-10-27)

`rd_GetBKSize`, `amt_fio_LoadAemter`, `cm_ExSetHE`, `cm_ExSysMessage` and
`gm_AddObjekt` were refused earlier because a different definition already used
the name. Each has a single attested owner now:

| TL VA | Attested name | What changed |
| --- | --- | --- |
| `0x4bdf40` | `rd_GetBKSize` | The unclaimed duplicate in `plant.c:314` became `plt_LookupBauplatzBox` (inferred helper name); it has no row and never pushed the diagnostic. |
| `0x4ec520` | `amt_fio_LoadAemter` | Renamed onto the TL row; `aemter.c` carries the server body and `src/Develop/DieGildeAddOn/game` is not part of the client build, so no duplicate symbol exists. |
| `0x4c9340` | `cm_ExSetHE` | `command.c` keeps the server body behind `#if defined(REBREW_SERVER) \|\| defined(REBREW_GOLD)`; the client body is `0x4c9340`. |
| `0x4c9550` | `cm_ExSysMessage` | Same split as `cm_ExSetHE`. |
| `0x5037c0` | `gm_AddObjekt` | `spiel.c:2251` keeps the server body behind the same guard; the client body is `0x5037c0`. Server.dll attests the name too, so both builds legitimately carry it. |

`--shared-definition` now accepts a name that another target's row owns in the
same file (upstream `cf53a9dd`): one tree holds each target's guarded body, and
the caller acknowledged the counterpart. Same-module rows are still refused.


### Animation loader name and command filename (2026-10-19)

`d3_LoadAnimStream` is attested by its own diagnostic at TL `0x44c688`
(literal `0x67b04c`) and Gold `0x44e508` (literal `0x5fc278`). The shared
definition is TL `0x44c620` / Gold `0x44e4a0`. Its declaration remains in
`d3_animation.h`; `Develop/Units/d3/d3_LoadAnimStream.c` is an inferred source
filename, not an attested original TU. All affected callers use the same name.

The TL `0x4959f0` definition already named `cm_TestCommandResult` now has the
matching filename. It is distinct from the 14-byte `cm_MarkAndReturn` in
`command.c`. The two moves preserve all non-CodeView sections and relocation
operands in 28 client compile contexts, allowing only the animation symbol
rename. This is object preservation, not raw-link placement evidence.
Receipts: `.scratch/dsh-wave1/naming-review/`.

### Scene loading declarations (Goal80, 2026-10-17)

`ecmd_LoadScene` remains attested by the complete original diagnostic. Its
`char** filename` parameter is an inferred first-pointer-slot access view, not
a recovered full command record. `client_scene_loader.h`, `SCENE_PROGRESS` and
`client_script_runtime.h` are inferred declaration names/homes. Loader names
remain `fcn_00448360` / `fcn_0044be60`; no original identifier is established.
The one-byte Boolean result, stream pointer and three full-width callback inputs
follow native evidence, without claiming original char signedness or typedef text.

The script error function retains `fcn_00425bf0`, with its existing provider's
`char*`, unsigned position and constant message contract. Reuse `g_6b7e98`
from its current canonical declaration in `ch_motion.h`; neither including it
nor the new script header establishes allocation or original module ownership.
No globals or storage were added. At Goal80 the T&L embedded-scene bridge accepted
`void* stream`, while its receiver still carried a legacy integer stream.
Goal82's opaque-pointer cutover superseded that debt statement; see
[stream contracts](data-ownership.md#stream-contracts-do-not-create-storage-owners-goal82-2026-10-17).
Receipts: `.scratch/goal80-scene/{proof.json,stream-boundary.json}`.

### D2 image argument slot (Goal79, 2026-10-17)

`d2_BildArgument2` is inferred, using the attested `d2_` prefix. It names the
second argument stored by Gold `0x475f30` / T&L `0x472770`, indexed through the
GUI image-offset field with stride 0x160. It does not assign an unproven meaning
to the stored value. The function names remain address-based. Their non-owning
views start at Gold `0xfa6038` / T&L `0x102d158`; four bytes describe only the
first accessed slot, not complete array bounds, a backing object or an owner.
Both addresses are in the actual PE `.data` zero-filled virtual tail. Existing
`d2_gui.h` supplies the canonical extern, with no storage or new original-unit
claim. Gold `0x475e30` / T&L `0x472640` are paired by complete native behavior;
the two Boolean-cell meanings beyond existing field views remain unproven.
Receipts: `.scratch/goal79-gui/{proof.json,data-commands.json}`.

### Cursor and dialog access views (Goal78, 2026-10-17)

`client_cursor.h` and `client_d3_dialog.h` are inferred declaration homes,
not attested original source units. The functions retain their address names.
`CursorOsBypass` names the observed nonzero predicate that skips `SetCursorPos`;
`CursorX1`/`CursorY1` and `CursorX2`/`CursorY2` number pairs by native write order,
without assigning unproven UI roles. Existing `g_01467380`/`g_01467382` names
are retained, not a pattern for new globals. `DialogArgument1`, `DialogArgument4`
and `DialogArgument5` describe the wrapper's observed argument slots only.

All ten names identify non-owning scalar access views. Their original spellings,
module prefixes, backing extents and storage owners remain unknown. Nine are in
Gold's zero-filled `.data` tail; the four-byte cursor bypass view has native
initial value one. Section placement and initialization do not establish owners.
Complete cursor/dialog C and operand evidence:
`.scratch/goal78-assembly/{proof.py,proof.json}`.

### Native CRT rand and scene-name collector (Goal77, 2026-10-17)

Gold `0x5de784` is the stock `_rand` identity, not a game routine named
`fcn_005de784`. Pristine Processor Pack `LIBC` reproduces all 30 bytes with
both seed operands bound to `0x62e108`. The copied assembly is retired through
binding history; `library_msvcrt.h` records the library identity, and the sole
30-byte caller uses SDK `rand` without changing its native code or destination.
The resolver's strict native review still rejects unresolved private `_holdrand`.
No public seed declaration, complete backing allocation or selected raw-link
archive provider is claimed. Receipts: `.scratch/goal76-assembly/rand-proof.json`
and `.scratch/goal77-assembly/{rand-caller-proof.json,rand-native-review.json}`.

Gold `0x4d2650` retains its address name: `sp_CONQUER` identifies the scene-name
prefix it collects, not an original function spelling or module prefix. Its C
callback takes `char*` and an unused `void*` context, matching the actual Gold
iterator at `0x438d40`. All 47 code bytes, both operands and the full 11-byte
literal match with rejecting controls. The count cell at `0x6f0d60` and pointer
table at `0x930380` remain access views without invented names, allocations or
owners. No additional accounted text is credited for replacing already-counted
assembly. Replay: `.scratch/goal77-assembly/collector-proof.py`.

### Object-transform animation wrapper (2026-10-15)

`StartObjectTransformAnimation` is inferred for TL 0x00412d30. No original spelling,
prefix, source unit or Gold counterpart is established. Its private source unit
and `D3_OBJ_ANIM_FLAGS`/`D3_OBJ_ANIM_FRAME` names are inferred. Native allocation
labels attest the called service's `d3_int:CreateObjAnim` and frame-data purpose.
The frame stride is 88 bytes; options occupy12 bytes by value. Unknown fields and
bits retain `unbekannt_*`/bit-position names and are not given invented meanings.
The numeric global spellings predate this reconstruction and are retained as
declaration views. Their storage owners remain unknown. The helper is a near
match with bounded call-input evidence, not a byte match or original-unit proof.

### Private CRT input helper (2026-10-15)

Gold 0x005e3a71 is the attested private `_un_inc` (`__un_inc` in COFF),
not an inferred game function. Pristine Processor Pack `input.obj` has STATIC
linkage and reproduces all 23 bytes with its `__ungetc_lk` operand bound to
0x005e899f; a wrong-callee control rejects. Its managed LIBRARY identity lives
in `library_msvcrt.h` without a public declaration. The incorrect copied body
is retired. No client raw-link provider is claimed by this identification.

### Shared scene lighting refresh (2026-10-15)

`UpdateSceneLighting` is an inferred name for TL 0x450a00 and Gold 0x453890.
Neither its original spelling nor a function prefix or enclosing source unit is
attested. The shared definition retains both clients' counter/terrain work;
Gold alone has the native byte-flag branches that clear node caches or rebuild
mesh lighting. The inferred `client_lighting.h` owns the canonical declaration,
not storage. TL ignores the argument; Gold reads its low byte and compares it
unsigned. Original parameter spelling remains unknown.

`LightingUpdateCount` and `LightingUpdatePending` are inferred access names.
Existing numeric global spellings and the existing signed-byte flag declaration
are preserved. Seven managed declaration views describe four-byte or one-byte
accesses in the PE's zero-filled `.data` tails. Backing allocations and storage
owners remain unresolved; no globals, padding or initialized data are emitted.
The complete 38/128-byte native bodies and twenty operands pass with fourteen
rejecting bindings in `.scratch/goal31/integrated-helper-native-proof.json`.
These results do not establish client raw-link providers or image identity.

### Shared solar-effect stop (2026-10-14)

The inferred `StopSonnenstrahlen` covers TL 0x4186d0 and Gold 0x417150,
31 bytes each. It belongs beside the existing creation/reset bodies in the
shared solar-effect unit. The weather caller supplies an object pointer and
phase1; the native helper ignores the first argument and stores the second,
sets active state to-1 and resets the clock. The Gold one-argument stub is
retired. No original spelling or filename is attested. Fresh CLI discovery
supplies the missing TL inventory entry; all prior inventory rows are preserved.
The shared header declares the two-argument interface. Both weather callers
retain their complete 380-byte COFF bodies and 35 typed operands after binding
and declaration repairs. All six solar-effect bodies and 32 rejecting symbol
controls are verified in `.scratch/goal22/reconstruction/solar-stop-native-proofs.json`.
No storage, flags or assembly are added; client raw links remain unverified.

### Shared Sonnenstrahlen creation and reset (2026-10-14)

The newly inferred `CreateSonnenstrahlen` covers TL 0x418710 and GOLD 0x417190,
211 native bytes each. `StartSonnenstrahlen` replaces TLfcn_004186f0 and
GOLDfcn_00417170 at 0x4186f0/0x417170,31 bytes each. Both live once in the
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

### Shared tracked allocator and attested spelling (2026-10-11)

SERVER 0x10006580 (658 bytes), GOLDTL 0x41db70 and GOLD 0x4223c0
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
unresolved. Both complete client bodies, literals and all 25 operands match;
all 185 checked caller operands independently retain their native destination.
The private40-byte group and 16-byte allocation-record layouts are unchanged.
Receipts: `.scratch/goal21/shared-tracked-alloc`.

### Shared allocator shutdown (2026-10-12)

The inferred `m_ShutdownAllocator` name now covers SERVER 0x10006c00,
TL 0x41e0c0 and GOLD 0x422910 in the shared m_alloc unit. Its original spelling
remains unproven. The clients retain the same leak-reporting literals, tracking
slot cleanup and linked-list traversal; SERVER alone logs the formatted pointer
leak. The native bodies are 283/262/262 bytes. Client aliases describe existing
storage without allocating it or establishing an owner; the numeric global and
callback names remain unresolved. The group next pointer remains at offset 36,
and tracked records remain 16 bytes. Complete native operands and literal bytes
agree with the old client implementation and existing allocator/report bindings.
The TL shutdown caller retains its native call destination. Evidence:
`.scratch/goal21/shared-allocator-shutdown`.

## Shared tracker reporting and group layout (2026-10-11)

The existing inferred `m_ReportGroupInfo` name now covers SERVER 0x10006990,
TL 0x41df00 and GOLD 0x422750 in the shared m_alloc unit. The SERVER source
path is attested by its native logging calls; client placement follows the
identical group traversal, formatting literals and shutdown callers. SERVER
logs the formatted output; the clients retain the formatting but omit those
six calls. Its original spelling remains unproven.

`GroupNode` is the single40-byte allocation-group layout for all targets;
`MemPool` was another name for the same layout. Canonical `size_total`,
`count_total`, `size_max`, `count_max`, `count` correspond to the former
`used`, `used_blocks`, `max`, `max_blocks`, `calls` at offsets 16/20/24/28/32.
The names are reconstructed. Name storage is 16 bytes and next is at 36;
tracked `MemBlock` records remain 16 bytes with group/tag/pointer/size at 0/4/8/12.
Compiler assertions and native bodies establish layout, not original spelling
or storage ownership. Client stat/global spellings are private scoped aliases
without allocations. Evidence: `.scratch/goal21/shared-pool-report`.

### Shared pool deallocation (2026-10-11)

`m_pool_free` is attested by the SERVER fatal diagnostic at 0x10006e30.
The corresponding TL 0x41e2e0/GOLD 0x422b30 names and unit placement remain
inferred from the same 16-byte pool-block layout, slot/bounds/unlink logic and
calls to the shared tracking deallocator. One canonical definition now serves
all three targets; only SERVER reports invalid entries. The complete 112-byte
client bodies retain both native call operands, while the 137-byte server body
and every caller remain unchanged. The duplicate client `Chunk` definition is
retired with its source. Existing `M_POOL_BLOCK` field names and global owners
remain provisional. Evidence: `.scratch/goal21/shared-pool-free`.

### Native MSX and D3 unit placement (2026-10-11)

TL420840 directly references the attested `D:\develop\units\Msx\msx.c` path.
Thirteen channel functions share the same native critical section; their placement
under `Develop/Units/Msx` is inferred from this subsystem affinity. Their original
function spellings and the other functions' exact original units remain unknown.
Both TL420840 and GOLD4244b0 also attest `hTrack->bAmbient`. The canonical 296-byte
`Chan_14cc460` view now uses the attested `bAmbient` spelling at offset 0x106.
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
The TL routing caller is independent70-byte 4bfbc0, outside the matched dialog body.
Evidence: `.scratch/goal20/ui-resource-bind/scope-final.json`.

### Shared floor-water region fill (2026-10-11)

`d3_FillWaterRegion` at TL43bf60/GOLD440170 is inferred. The attested `d3_`
renderer prefix and the caller's `d3_fl:Water` allocation labels support its
module/role; original spelling and `d3_floor.c` unit placement remain unproven.
The unrelated client `cm_ExAllocRaum` binding is removed; that attested SERVER
handler stays unchanged. The 268-byte helper operates on square byte grids and
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
motion-loader file owns the reconstructed283-byte helper and 12-byte options
view. Its two absolute 0x34 reads are native, with no direct callers or absolute
function-pointer references found. No storage owner or GOLD counterpart inferred.
Evidence: `.scratch/goal20/alloc-spieler-client/scope-final.json`.

### Recovered character queries and sound constructor (2026-10-11)

`CharacterSitting` TL40df00 and `CharacterSitsDown` TL40e110 retain their
attested spellings and saved implementations; their shared bit query remains
unmatched. `fcn_004050c0`, `fcn_00405540` and `fcn_00418c80` remain unnamed
pending original-module and naming evidence. This recovery restores their
exact previously verified source versions, including the constructor's
existing SOUND_SOURCE view; it establishes no new names or storage owners.
The TL constructor again matches 150 bytes with all 6 operands independently
bound. Its stock CRT call is strncpy64d530. GOLD's constructor field offset
difference remains unbound; do not import the TL constructor unchanged.
Evidence: `.scratch/goal20/missing-character-bindings/scope-final.json`.

### Parent resolver and getter extents (2026-10-11)

`gm_ResolveParentEntity` (SERVER10019ae0/TL50d490/GOLD50a050) and
`gm_GetEntityType` (SERVER10019b40/TL50d530/GOLD50a0b0) retain inherited
inferred names. Complete client extents are82 and 62 bytes, excluding 14
and 2 external NOPs. The resolver uses the id at input+0x0a, returns its
static record if present, otherwise follows dynamic+0x27 into g_slot_table;
missing records or link 0xffff return null. The getter returns the static
record's first word, otherwise dynamic+0x27, otherwise 0xffff. A domain
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
codes return zero. Its complete 291 bytes include both compiler tables; the
retired client clone's304-byte extent also included13 external NOPs.
The table-entry helper selects a172-byte record for kinds5/6/7 with flag 0x8000
and low-four-bit index0..15. Both client implementations remain near matches
with 11 register/scheduling differences. Canonical prototypes and caller casts
preserve the existing reconstructed views; original domain types remain open.
Client `g_entity_type_bytes` is a declaration-only view at `g_slot_table+0x164`.
Client `g_entity_base` describes the accessed2752-byte table view. These inherit
server analysis names and allocate no storage; complete backing objects and
storage owners remain unresolved. VC6 requires the owning spiel.c's early
prototype order; its header omits repeat stat declarations in that TU.
Evidence: `.scratch/goal20/stat-level-extent/scope-final.json`.

### Filtered iterator identity correction (2026-10-11)

`gm_FindNextFilteredEntity` is the existing inferred shared name for the
iterator at SERVER10016f80, GOLDTL503e80 and GOLD501030. The client body is 341
bytes plus 11 layout NOPs; all 20 relocation sites and all other bytes match
the existing spiel.c definition in both clients. GOLDTL503e80's former
`gm_AddObjekt` binding named a different shared function and is disproven.
The true server `gm_AddObjekt` name remains attested and unchanged. Evidence:
`.scratch/goal20/stat-shared-iterator-audit.json`. Upstream0fbab4fb fixes the
shared importer, and the verified replay corrects both client names, symbols,
flags and 341-byte reference hashes through the managed writer. Evidence:
`.scratch/goal20/stat-iterator-replay.json`.

### Entity-class embedded switch extents (2026-10-11)

The existing shared `gm_EntityClassCheck` retains its name and C definition.
GOLDTL506e20 and GOLD503f50 have70-byte complete extents:34 bytes of reachable
code,2 internal alignment bytes, an8-byte branch table, and a26-byte case map.
The following 10 NOPs are external alignment. Compiler-generated table labels
are private views inside the owning function; the extent repair creates no
named global or storage owner. All 26 cases/default and 8 local DIR32 targets
are validated through upstream strict operand proof. Evidence:
`.scratch/goal20/entity-class-extent/scope-final.json`.

### Shared object resource cleanup (2026-10-11)

`gm_ClearObjektResources` is inferred, not attested. The existing spiel.c now
owns SERVER10016670 (one-byte empty body), GOLDTL502ec0 and GOLD500080
(client54-byte body). The clients inspect the object prototype category 0x1d,
release the pointer chain at node+0x29 via fcn_004be280, and clear that field.
The recursive list helper at SERVER10016710, GOLDTL502f80 and GOLD500140 calls
the correct edition body. Clients have66-byte recursion plus 14 alignment NOPs.
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

The `__FILE__` strings the compiler embedded give the original tree directly:
**14 paths**. Current inventory is `rebrew source units --json`. The default
target is `Europa1400Gold_TL.exe`, so name the binary:

```sh
uv run rebrew source units --target server.dll --json
uv run rebrew source units --target Europa1400Gold_TL.exe --json
uv run rebrew source units --target Europa1400Gold.exe --json
```

Confirm a referencing instruction with `rebrew binary asm show` on that same
target. The old ad hoc scan of `original/Server/server.dll` is retired.

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

(all under the `D:\Develop\` root). These paths attest those units, not every
reconstructed header, helper name or proposed file boundary. The table below
records the measured mapping; inferred placements remain labeled.

**The `_c` directory suffixes are not attested.** No `__FILE__` string contains `_c\`.
The server per-function split is retired. The table is the recorded server TU
map, 260 functions in these runs. It is not a fresh census. Whole-file server
identity is a separate fact: the current raw server file equals the reference.
Remaining `*_c` directories hold client `GOLDTL` files (`command_c`,
`friedhof_logic_c`, `spiel_c`, `loadsave_c`, `vfs_c`, `Error_c`), not that
retired server split.

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
| `0x1000bd50`-`0x1000c710` | `DieGildeAddOn/game/alchemistry_logic.c` | 14 |
| `0x1000ca00`-`0x100104a0` | `DieGildeAddOn/command/command.c` | 70 |
| `0x10010530`-`0x10011bf0` | `DieGildeAddOn/game/friedhof_logic.c` | 17 |
| `0x10012000`-`0x10014260` | `DieGildeAddOn/loadsave/loadsave.c` | 11 |
| `0x100145e0`-`0x10014db0` | `DieGildeAddOn/command/lobbycommands.c` | 8 |
| `0x10014ee0`-`0x100151b0` | `DieGildeAddOn/auxillary/plant.c` | 6 |
| `0x100151e0`-`0x10015690` | `DieGildeAddOn/game/sim.c` | 6 |
| `0x100156c0`-`0x1001a110` | `DieGildeAddOn/game/spiel.c` | 66 |

The chain dispatcher at SERVER `0x1000ca00` / TL `0x4c4d30` / Gold `0x4c43c0`
now precedes `gm_GetFieldByType` in `command.c`. Its placement is inferred from
native ordering, the caller and the command-owned dispatch table; the body has
no direct `__FILE__` reference. `ahm_ProcessEntityChain` remains an inferred name.
Complete comparisons and the unchanged raw server validate the move without
establishing original spelling or proving all client unit boundaries.

In the measured units, `LogMessageInternal` line values rise with native VA,
supporting the recorded definition order. This does not locate unlogged helpers
or prove every original TU boundary. Divergent client twins may remain separate
`GOLDTL.<name>.c` definitions until organization is verified across targets.

### Merged Source Tree (speculative)

Server paths are the attested list above. Client-only paths are the Gold
and TL trees above this section. One further entry is speculative:
`Units/net/net.h` is a reconstructed statistics header from multi-TU client
evidence, not an attested `__FILE__` path.

`DieGildeAddOn\` and `DieGildeAddOnVc\` likely contain the same game logic
source files, compiled with different project settings. The server build
(`DieGildeAddOn\`) produces `server.dll`. The client T&L build
(`DieGildeAddOnVc\`) produces `Europa1400Gold_TL.exe`. The base client
(`Europa1400Gold.exe`) links only the engine `Units\`: game logic may be
compiled directly into it or loaded from a separate DLL not captured here.

### File Naming Patterns

- A shared domain type spelled identically in two TUs leaves the `.c` files.
  `src/Develop/rebrew_types.h` holds support types.
  `src/Develop/game_structs.h` holds domain types. The round 1103-1106 paths
  below are the files those lifts came from. Those paths are gone.
  - `LinkedNode` (0x43, packed, round 1103) was spelled in
    `spiel_c/gm_RemoveLinkedNodeById.c` and `spiel_c/gm_RemoveObjectByType.c`.
    Both local copies invented names. Callers fix the evidence: +0x00 word =
    `type` (16-bit object types passed to `gm_RemoveObjectByType` by
    cm_ExClearLagerslot / cm_ExProdObjekt / ahm_ExAllocAlchemist), +0x02 int =
    `entity_id` (`*(int*)(entity + 2)` at `gm_RemoveObjectWrapper`); removal
    clears the type word. The canonical typedef is `src/Develop/game_structs.h`.
    `src/GOLDTL.fcn_00502e30.c` and `src/GOLDTL.fcn_00502f00.c` still carry a
    local typedef with the same field list. Those copies do not allocate storage.
  - `gm_CurrentHumanFamilyCount` (round 1107): attested by the confirmed-push
    overflow log in gm_AllocSpieler; renamed from `g_dynasty_generation_counter`.
  - `OFFICE_SLOT` (0x18, round 1103) was spelled in `game/aemter.c`
    (`a/b/c/type/d`) and `game/aemter_c/amt_fio_LoadAemter.c` (read-order names).
    The read-order names were kept. Neither list is attested by a string.
    `aemter_c/` is gone. The typedef is `src/Develop/game_structs.h`.
    `src/Develop/DieGildeAddOn/game/office_slot.h` defines a separate
    `OfficeSlot` with different field names. It is not this spelling.
  - `gz_stream` (0x64, round 1104) was copied from
    `Units/vfs/vfs_c/check_header.c` and `Units/vfs/vfs_c/gzread.c` into
    `Units/vfs/gz_stream.h`. That header is gone. The struct lives in vendored
    `references/zlib/gzio.c`. See [vendoring](vendoring.md).
  - Rounds 1105-1106 collapsed the last two 0x43-byte node spellings
    (`EntitySlot` in `gm_FreeObjectListRecursive.c`, anonymous `Record` in
    `spiel.c`) onto `LinkedNode`.
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

Prefer the toolchain CRT headers for `fopen`, `fread`, `putc`, `srand` and
`rand`. Add a local declaration only when that header does not provide the
symbol. The statically linked `__ftol` intrinsic still needs a declaration
where it is used.

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

A common reconstructed shape is `int __cdecl func(void* cmd, void* result)`.
Recover the actual signature and consumer for each handler. The 0/1 results
are the usual pattern, not a proof that every body uses them.

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

A direct-call search misses these: the catalogue name was `fcn.10010700`, and
a header comment asserted "It has no caller" for many rounds. Before treating
a small unnamed function as dead, use `rebrew binary xrefs 0x<VA>`. Give a
proven predicate the `_eval_` name and record the callee's callback signature.

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

`__cdecl` object symbols have a leading underscore. The managed row's
`symbol` field records it. A `// SYMBOL:` comment is retired; do not add one.

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

A string shaped `"<name>(): ..."` or `"<name>: ..."` names a function only
when that function pushes the literal. List candidates with
`rebrew binary strings --xref --filter` and confirm the push with
`rebrew binary asm show`. An external string catalog is not authority: one
wrongly attached `_main_:` to `0x100068e0`.

Every name below was checked that way: the function at the stated VA pushes
the literal.

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

### Client production callback (2026-10-14)

| TL VA | Gold VA | Attested name | Standing |
| --- | --- | --- | --- |
| `0x00571870` | `0x005694b0` | `he_RunProduktion` | Shared C89 candidate in `src/he_RunProduktion.c`; byte verification was not established by this naming receipt |

Both bodies push `"he_RunProduktion(): geb:%G"`: TL instruction
`0x005718b1` references literal `0x006a7c78`, and Gold instruction
`0x005694f1` references `0x00628c28`. Their shared initializer places each
entry in the same production callback slot. The complete native extent is
3,816 bytes per client, including the five-entry switch table and excluding
following NOPs. This does not establish a source file, header, storage owner
or byte-match verdict. Existing numeric callback declarations remain until
implementation and verified name binding. Native receipts:
`.scratch/goal23/production-callback/{name-proof,extent-proof}.json`.

The reconstructed file path, locals and field meanings are inferred. The
original event type and complete allocation remain unresolved; the C currently
uses explicit byte-offset views. Only the function name is attested. Numeric
initializer references have a reviewed rename preview but remain unchanged
until both client compilations can be checked. Bounded behavior fixtures do
not establish original prototypes or a byte-match verdict. Current receipts:
`.scratch/goal25/production/`.

### Module case: `m_alloc` is snake_case

The `Units/m_alloc` unit does not use the `m_VerbNoun` CamelCase of the game
modules. Its recovered names are lower snake case:

- `m_alloc`: attested by `m_alloc() called without prior call to m_init()`.
  The earlier reconstruction name `m_AllocTracked` is retired. The definition
  in `Develop/Units/m_alloc/m_alloc.c` is `m_alloc`. The tracked call still
  receives a `__FILE__`/`__LINE__` tag; that does not restore the retired name.
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

Both clients are reconstruction targets. Their log prefixes are under
Client-Only Modules above. Counts from an old external catalog (5128 and
4956 strings) are not a live inventory; use `rebrew binary strings` on each
image. A string constrains a name only when the function pushes it.

## Struct Naming

Structs use `UPPER_CASE` names, often abbreviated:

```c
typedef struct DISPATCH_OBJ { ... } DISPATCH_OBJ;
typedef struct SRC { ... } SRC;
typedef struct TGT { ... } TGT;
```

Field naming appears to use lowercase with occasional camelCase. Where no
original shared header is attested, treat the struct as TU-local.
Reconstructed headers such as `d3_object.h` are current declaration homes,
not attested original headers.

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

- Inferred shared type `VECTOR3` replaces address-derived `Vec3_67bbdc`: three floats,12-byte view with offsets 0/4/8, reused by seven client sources. TL67bbdc/Gold5fcc78 includes ambient RGB use; TL6b86c4 semantics remain unresolved. No original-name or source-path attestation. Evidence `.scratch/goal-material-colors/field-alias-bindings.json`; original allocation ownership remains unresolved.

### Shared random helper consolidation (2026-10-04)

| Image | VA | Current name | Standing |
|-------|----|--------------|----------|
| server.dll | `0x1001a0d0` | `gm_RandomMod` | Existing reconstructed server name retained. The round's path `game/spiel_c/gm_RandomMod.c` is gone. The definition is `DieGildeAddOn/game/zufall.c`. See the 2026-10-11 reconciliation. |
| Europa1400Gold_TL.exe | `0x0042e410` | `gm_RandomMod` | Numeric caller alias fcn_0042e410 renamed; newly recovered32-byte identity shares the server body. |
| Europa1400Gold.exe | `0x0042ec00` | `gm_RandomMod` | Renamed from fcn_0042ec00; duplicate body retired for the shared definition. |

This is a semantic shared-name choice anchored in the existing server reconstruction, not an original-symbol or log-string attestation. The existing `int __cdecl gm_RandomMod(unsigned short n)` C form produces all 32 native bytes in each image, including a typed call to that image's stock `rand`. It does not prove unique original signedness or parameter spelling. Caller prototype narrowing remains unresolved; the rename preserves caller declaration types. Evidence: .scratch/goal-random-helper/consolidation/native-shared-body-audit.json and consolidation-scope-check.json. Full-tree verification63165 is accepted: all existing matches retained and the TL helper added. Five prior mismatches have stricter deltas under the newly bound call catalog; before/after compiled bytes are identical.


### Shared scene-object destruction (2026-10-15)

`d3_UnlinkObject` is inferred from the native parent/sibling updates and flag
clear at TL `0x43a0a0` and Gold `0x43d0e0`. One typed definition now uses the
verified D3 object layout for both clients; the header supplies each target's
field offsets. It preserves the original store order and introduces no null
guard. The old `Ent` type in caller TL `0x4458e0` remains a partial view; the
call casts it to the canonical object type without changing its byte accesses.
The name and placement in `d3_object.c` remain inferred.

Both complete unlink bodies are unmasked EXACT for154 bytes. Opposite object
layouts reject, and both 32-byte destruction wrappers retain their complete
native bodies and call destinations. The unlink provider is now source-owned
for both targets, including the previously unsourced Gold leaf. Inner disposal
still differs and remains separate. Evidence:
`.scratch/goal40/native-proof.json` and `scope-preservation.json`.

`d3_DestroyObject` is inferred from the wrapper's unlink/dispose behavior and
the existing D3 object layout evidence. It names TL `0x442be0` and Gold
`0x447190`; neither native body contains a name or source-path string. The
`d3_object.c` placement is inferred beside the existing object header. The
callee's `d3_DisposeObject(): invalid universe by object %s` string attests
the inner disposal helper, not the wrapper name.

One C89 definition returns a byte and takes `D3_OBJECT*`, with a single header
declaration reused by every reconstructed caller. Native TL calls `43a0a0` /
`4398d0`; Gold calls `43d0e0` / `43c7a0`. Unlink now has a shared typed provider;
the disposal providers remain separate:
TL disposal is 450 bytes and Gold disposal637. The caller byte proof does not
establish their provider implementations or original parameter spelling.

Both complete 32-byte wrappers and their call operands agree; four shifted-call
controls reject. Across31 target/source contexts, the other115 comparisons
preserve their byte results and existing binding proofs; nine Gold call sites
gain a native address proof. All six D3 layouts retain their evidenced sizes,
extents and offsets after compiler rechecks. Receipts:
`.scratch/goal39/wrapper-native-proof.json`, `scope-audit-current.json`,
`d3-types-before.json` and `type-*.json`.

### Shared building destruction (2026-10-15)

`cm_ExDestroyBuilding` is an inferred command-handler name, shared by SERVER
`0x1000f680`, GOLDTL `0x4cbc90` and GOLD `0x4cb100`. Native command tables
select these handlers at index `0x3b`; the client handlers previously used the
numeric name `fcn_004cbc90`. The server diagnostic names `cm_ExSetGebUpgrade`
instead, an apparent native copy-paste error preserved literally with line
`0x4c32`. It does not attest the reconstructed destructor name.

The common definition in `command.c` shares building lookup, child traversal,
clearing the `+0x16c` field of 768 records at stride `0x21c`, and the reply tail.
Client guards preserve rendering and handle teardown; the server keeps its
missing-building log. The field view uses the existing `g_slot_table` backing
object in all targets and introduces no storage definition. `saved_mode` and
the other descriptive locals are inferred.

Client query, child-removal and cleanup helpers keep their existing numeric
bindings because their definitions are not yet unified with the server helpers.
Resource destruction now uses shared `d3_DestroyObject`, whose Gold identity
is `0x447190` (formerly `fcn_00447190`). Full client
caller bodies and independently reviewed operands agree, but this does not
verify the helper providers or complete client images. Receipts:
`.scratch/goal38/destroy-native-proof.json` and `comparison-preservation.json`.

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

The reconstructed client code of rounds 16-19 (msvc6-link-layout 5f) added the names below.
The check was every `ident():` / `ident:` string in the three images, a verbatim
search of each name, and the strings each ported TL function addresses.
`.scratch/measure/attest.py` is retired. Repeat a search with
`rebrew binary strings --xref --filter` on each target. The historical
classification is [client-only sweep](client-only-sweep.md).

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
- **Layout rows:** `g_gap_10035410` (28 bytes) and `g_gap_10034684` (3460 bytes)
  are generated definitions in `src/bss_layout/bss_head2.c`. The names are
  inventory, not attested identifiers. That definition supplies reconstructed
  bytes and does not prove an original owner. `gm_GetSlotBase` reads the first
  dword of `g_gap_10035410` as a float scale. `sim_NextServiceBuilding` reads
  the dword at +0x18. Client copies of `g_gap_10035410` in the comparison
  scaffolds are placeholders, not a second owner. The round-19 note that
  `g_gap_10034684` appeared only in docs is superseded.

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
now identify the shared 34-byte server.c bodies. Their original names/source
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
for the 37-byte compiler literal, not a source identifier. The existing C
spelling `g_current_year` binds Gold's native scalar view at 770ae0; the
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
without an invented module prefix. Both complete 38-byte native functions are
identical and use the existing TL C body in `src/FindTableEntryIndex.c`.
The original function/unit names, table domain and unused original parameters
remain unproven; the two used arguments are the target value and a caller-supplied
row table. The loop advances12 bytes per row, examines at most64 rows, stops at
0x28, and returns 0x27 when missing. It checks equality before the terminator,
so a target value 0x28 can return that row's index. No storage owner or array
allocation is inferred. The malformed GOLD placeholder's absolute-address
assumption and discarded first argument were false. Managed identity, the
verified shared import and both complete objects establish EXACT bytes.
Evidence: `.scratch/goal20/table-search-repair/scope-final.json`.

### Alchemy flag helper ownership (2026-10-11)

`ahm_CheckFlag` remains an inferred name. SERVER1000bda0, TL4ec850 and
GOLD4eaad0 share the unchanged `DieGildeAddOn/game/alchemistry_logic.c`
definition; the misleading TL `ahm_ResetEntityState.c` clone is retired.
The real reset helpers remain distinct. Both native client bodies are70 bytes
plus 10 alignment NOPs. Clone/owner bytes and the typed table operand agree
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
for the scene object in both clients, TL 0x1640/GOLD 0x970 for draw data.
Four draw slots have TL 0x4a4/GOLD 0x198 stride. `teile`, `teile_anzahl`,
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
model referenced through character offset 0x124, its orientation and terrain
height, then caches the main model position. Its second argument is read as an
unsigned byte. The native x87 comparison accepts unordered height differences;
the C condition preserves that behavior. The zero-initialized float is an
existing global read, not a new constant or storage definition. The complete
bodies, all 17 typed operands,14 rejecting binding controls and all 24 literal
bytes agree in each client. The 10 previous surrounding bodies remain unchanged.
Declarations are canonical in `ch_motion.h`; native callee spellings, field
names and storage ownership remain unresolved. Receipts:
`.scratch/goal21/character-pending-positions/attachment/`.

### Low-polygon character updates and animation options (2026-10-12)

The native TL diagnostic attests the exact spelling `ch_Updatelowpoly()` at
TL4033e0. Its partial C reconstruction now lives in shared `game/character.c`,
and four callers use the canonical declaration in `ch_motion.h`. The native
body is 1156 bytes; the inventory's1168-byte span includes 12 alignment bytes.
The current default-flags object emits1150 bytes and remains SIZE_MISMATCH.
Detailed/low-polygon block ordering and pointer reuse still need matching; no
complete byte-match, proof, Gold counterpart binding or new data verdict is
claimed. The stock CRT supplies strstr/sprintf.

The two identical private animation-option definitions are replaced by one
inferred `D3_ANIMATION_OPTIONS` in `Units/d3/d3_animation.h`. Both client
compilers check sizeof12 and offsets mode0/layer1/pad2=2/pad8=9; native calls
pass three DWORDs by value. All eight old animation bodies and typed operands,
and all 24 surrounding bodies across 12 contexts, are unchanged. The type and
field spellings remain inferred; this argument layout allocates no global
storage. Receipts: `.scratch/goal21/character-lowpoly/`.

Broader checks also confirm that Gold40cba0/40cf10 already matched their full
55/183-byte bodies: both catalog sizes included nine trailing alignment NOPs.
All 13 typed operands and rejecting bindings agree. Corrected size metadata
removes those pre-existing SIZE_MISMATCH verdicts without changing their C or
introducing a new function identity.


### Person tooltip callback identity collision (2026-10-14)

Gold 0x00589390 now uses inferred `ShowPersonTooltip`, from its native
`ToolTip\\ToolTip_Personen` key and person-statistic rendering. Neither the
function spelling nor original source path is attested. The separate
Gold 0x00580d10/TL 0x00589390 function retains its own definition. A shared
placeholder name had redirected the tooltip self callback to that function.
The private `RandomMoneyTransfer` inline helper in GOLDTL.fcn_004b6f00.c is
also inferred organization; its five native entries/coefficient variants are
recorded in TODO.md and independently checked. No original helper identity is
claimed, and no out-of-line helper is emitted.

### Scene-object draw-data cleanup (2026-10-15)

`d3_CleanupObjectDrawData` is an inferred name for TL439d80 / Gold43cd80.
The native bodies clean the counted draw parts, always clean part three, free
the draw-data allocation and clear the object's context. Neither the spelling
nor placement in `Units/d3/d3_object.c` is attested. Both identities select one
definition and the canonical object/draw-data types. Their draw-part cleanup
callees remain separately named native providers; Gold43cc90 is unsourced.
No shared callee identity or storage owner is inferred from this consolidation.

### Scene-object auxiliary records and cleanup (2026-10-15)

`d3_CleanupObjectAuxSlots` is inferred for TL456b80 / Gold45ccc0; placement
in d3_object.c is also inferred. One definition walks the four auxiliary records
inside draw data. `D3_OBJECT_AUX_SLOT`, `zusatz` and `zusatz_flag` are inferred
names for the evidenced stride views and controlling bit. Unknown word fields
remain access views, without claims about their original semantic types.
The `objekt` pointer is compared with the disposal object's callback context.
Per-record cleanup remains separately identified at TL456b10 / Gold45cc80;
Gold's63-byte body is unsourced, and TL's112-byte body has additional COM cleanup.

### Camera slot and scene-list removal (2026-10-15)

`g_6b8014` remains a provisional identifier for the pointer at TL6b8014 /
Goldfc2dec. Native selection and camera positioning establish its camera role,
but not an original global name, storage owner or complete allocation extent.
The inferred d3_camera.h supplies one `char*` byte-access declaration and the
selector prototype; it allocates no storage. The native diagnostic is
`SetCameraToDummy(): Could not find Cameradummy '%s'!` in both clients.

`d3_RemoveObjectFromList` is inferred for TL439b30 / Gold43cab0. Placement in
d3_object.c is inferred. Both 112-byte native bodies remove the object's list
links, clear the selected camera for kind3 and clear flags 0 bit1. This is a
different operation from the established hierarchy unlink helper.


### Master-evaluation eligibility (2026-10-15)

`gm_CanEvaluateMaster` is inferred for TL0047dd60 / Gold0047e8a0. Its 137-byte
body checks entity kinds1/2, nonzero +164, a home pointer at+16c and its valid
slot, excludes home kind7, then applies the evidenced global scheduling filter.
TL0047de50 calls it at 0047de7e before the native master-evaluation diagnostics
(`Evaluation von Meister %s in %s beginnt...`). The original identifier and
translation-unit home are unproved; the existing standalone source file stays.

This is distinct from the 32-byte kind2/3/4/5 predicate at TL0047d220 /
Gold0047dd60, which retains its provisional `fcn_0047dd60` spelling. The old
shared spelling caused an ambiguous native binding; it did not establish that
the two algorithms were one function. Rename and reference binding use the
managed CLI after direct native destination review. Goal49/master-proof.json
records complete object/operand/literal checks.


### Character mesh constructor (2026-10-15)

`ch_CreateMesh` at TL 0x403880/Gold 0x403070 is attested by the native
`ch_CreateMesh(): Could not load 3D-Character: %s` diagnostic. Complete ordinary-C
bodies match 777/787 bytes. Its existing character.c placement and local names are
inferred; char* model/resource and float* position are reconstructed access
contracts, not recovered original typedef spellings. The allocation factory and
conditional forwarder retain their provisional fcn names. Native word consumer
40342a independently supports a 16-bit model flag view at+8c.

### Active-context processing (2026-10-16)

`ProcessActiveContexts` is inferred for TL `0x4297c0` / Gold `0x42aef0`.
Both 59-byte bodies walk 128 records at stride `0xc98`, process records whose
byte `+0x124` has bit 0 set, and clear the current-context pointer afterwards.
The processing callee saves/restores execution and rendering context and runs
the context's operation loop; it does not reset the game's entity table. Kuna
and native receipts are retained in `.scratch/goal53`. No original module prefix
or source-unit path is attested, so the unprefixed name and existing placement
in `game/GOLDTL.spiel.c` remain inferred.

The independent logical reset retains `gm_ResetAllEntities` at SERVER
`0x10015cb0`, TL `0x5012b0` and Gold `0x4fe7f0`. Native calls from the two bound
server callers and TL `0x5392a0` reach that definition. The shared header and
all three physical caller files keep their reset declarations/calls unchanged.
Reviewed file-level ownership authorizes the selected-definition rename; it
does not establish providers for unbound contexts or client raw-link identity.

### Character action insertion and queue access (2026-10-16)

`ch_InsertAction` at TL `0x4051d0` / Gold `0x4048b0` and
`ch_GetFreeQueueEntry` at TL `0x405080` / Gold `0x404760` are attested by
the native `ch_InsertAction(): Could not ch_GetFreeQueueEntry()` diagnostic.
One ordinary-C insertion body matches 461/456 executable bytes; native callers
establish three fixed arguments followed by integer varargs. Kuna's fourth
fixed parameter is not supported. The insertion's character.c placement and
the new ch_queue.h declaration home remain inferred from subsystem use.

`CH_QUEUE_SLOT` is an inferred occupancy-word view with opaque remaining bytes,
not the recovered complete action type. Native allocation/iteration establishes
2,000 slots at stride 0x194. Existing `Entry_14d0c40` models the 0x4c dispatch
stride and observed offsets; its handler remains an opaque DWORD, without a
reconciled callback contract. TL `0x14d0c40` / Gold `0x1469700` are 64-entry,
0x1300-byte tables in the zero-filled virtual .data tail. Their canonical extern
declaration establishes no storage owner or raw-link provider.

The provisional message name `fcn_0041d9e0` now also identifies Gold `0x4222b0`;
both 119-byte bodies agree. error_message.h is an inferred narrow declaration
home. `const char*` expresses the observed read-only message contract, not an
attested original qualifier. The wider Error API and helper names remain open.
Complete native/object, literal and operand receipts are in .scratch/goal54.

### Scene dummy selection callback (2026-10-16)

TL `0x406ee0` / Gold `0x406340` retain the provisional `fcn_00406ee0` name:
no original identifier or source-unit path is attested. One shared definition
is retained beside the existing TL selection caller in GOLDTL.fcn_00407330.c;
that source-unit home is inferred. Each complete 1,102-byte body initializes a
15-by-64 local name filter, appends the first matching object pointer to the
caller's result and returns the signed count comparison with 32.

`CH_DUMMY_PICKS` is an inferred private result view, renamed from Picks through
the type writer. The callers' 0x84-byte stack frames, callback stores at
base+4*count and count at +0x80 support 32 pointer slots plus an integer count.
Both target layouts are compiler-checked under stable ID ch.dummy_picks.
The native concatenated `dummy_AUSGANGdummy_LAUFEN1` filter is preserved as one
entry; a missing comma in the original source is plausible, not established.
Receipts: .scratch/goal55/native-proof.json and the native/Kuna caller bodies.

### Character script registration and adapters (2026-10-16)

`ch_RegisterScriptCommands` is an inferred name for TL `0x40e1a0` / Gold
`0x40d270`. The 41 native registration names and argument recipes correspond;
the new `game/ch_script.c` and `ch_script.h` homes follow subsystem use, not an
attested original source path. Existing provider names stay unchanged. Native
registration strings do not automatically attest the C callback identifiers.

`WalkToDummy` (TL `0x40cae0`, Gold `0x40bbc0`) and `MoveCharacterCamera`
(TL `0x40d980`, Gold `0x40ca60`) are attested by their native diagnostics.
The three-byte TL `0x40dac0` retains its provisional name: its registration
attests the command `PreloadSitMesh`, not a unique original C identifier or
formal signature. One unused object-pointer argument is inferred from its VM
recipe. Gold's recipe points to `0x49dee0`, already attributed to Lua's
`default_panic`; identical three-byte bodies do not establish folding, shared
source identity or the linked provider. That LIBRARY row is preserved.

`ch_script.h` holds canonical declarations for the participating callbacks;
`ch_motion.h` retains object-byte-view/float-vector camera adapters. The narrow
`m_alloc_checks.h` declaration home is inferred and exposes the existing
`int m_is_tracked(void*)` provider contract without claiming a pointee layout.
No new storage or native type allocation is inferred. Full native/object and
operand/literal evidence is in `.scratch/goal56/native-proof.json`.


### Event validators and master checking (2026-10-16)

TL `0x4dc7d0` / Gold `0x4daf80` retain provisional `fcn_004dc7d0`:
registration and the actual indirect consumer establish their validator role,
but no original identifier or source path is attested. One shared ordinary-C
body serves both clients. The standalone source home and narrow
`game/event_callbacks.h` declaration home are inferred.

`cut_CheckMaster` is attested by both native diagnostics inside TL `0x4e63e0`
/ Gold `0x4e4a50`, including `cut_CheckMaster(): invalid master for id %i`.
The managed shared rename preserves the existing filename and both 241-byte
bodies. Original TU ownership remains unestablished. Complete strings, native
references and the supported rename preview are retained in `.scratch/goal57`.

`EVENT_CHECK` is an inferred `int (__cdecl*)(char*)` access contract: native
code passes one event pointer and tests full EAX. Eight fourth-slot callbacks,
the setter and their actual consumer share it. The first three registry slots
currently expose address storage only; their callable signatures remain open.
The event helpers retain their established word or unsigned-byte access views,
with explicit reviewed conversions from private event views at callers.

The existing provisional `g_9b0840` identifies TL `0x9b0840` / Gold `0x92c500`.
The consumer's former unbound `g_9b0850` spelling was a base+16 field view,
not a separate allocation. Its private `Kind` view is bound under stable ID
`event.validator_view`: 20-byte stride, callback at offset zero, sixteen bytes
opaque. Native registry entries begin sixteen bytes before that view. The
canonical header declares the backing bytes without defining storage or
claiming their full extent or owner. Proof: `.scratch/goal57/native-proof.json`.


### Court decision callback (2026-10-16)

TL `0x4df1b0` / Gold `0x4dd960` retain provisional `fcn_004df1b0` and one
shared definition in the inferred standalone source home. The registry's second
slot and its actual dispatcher establish two arguments: a participant-context
byte view and a word-access action view. Original identifiers, record names and
TU ownership are unproved. The native asset strings `cutscenes\prozess` and
`cutscenes\folterwahl` name resources, not the original C function or file.

The canonical declaration is in existing `game/event_callbacks.h`. Other phase
callbacks still need contract reconciliation. Private `cut_SECOND_CHOICE` and
`cut_WINDOW_WIDTH` are inferred expressions for two measured target differences:
Gold's alternate choice is 0 versus TL's 2; Gold reads a signed word at window+8
versus TL's dword at +12. The window remains a byte-access view with no invented
layout or allocation owner. Native boundaries, dispatch/operand evidence and
bounded execution inputs are retained in `.scratch/goal58`.


### Goal59: inferred participant-reset callback

`fcn_004e4f10` is the existing provisional label for TL `4e4f10`, paired with
Gold `4e36a0` by complete native bodies and direct callers. Its standalone file,
local names and word/byte access views are inferred. The native registrar passes
NULL; the runner passes an event pointer. Both paths support the canonical
nullable `int*` declaration in `event_callbacks.h`, without recovering an original
record typedef or C identifier.

The declaration of `g_9b0e20` remains the existing `char[]` view. Native strides,
field offsets and 16 outer reset iterations do not establish a storage owner or
the full allocation extent. No inferred interior alias or new allocation is
created to match the compiler's cursor choice. Receipts are in `.scratch/goal59`.


### Goal60: texture precaching and the first event phase

The name `d3d_PrecacheBuffer` is attested in Gold's native DrawPrimitive
expression. Its declaration belongs in the reconstructed `d3_d3d.h`; the native
source path is `D:\develop\Units\d3\d3_d3d.c`. The buffer's vertex type,
complete allocation extent and storage owner remain unproved. Its unsized extern
and alias row do not allocate storage or verify bytes.

`d3d_PrecacheTexture` is an inferred function name for Gold `4360e0`, chosen from
the attested buffer name and its SetTexture/DrawPrimitive behavior. The supported
writer renamed its earlier `fcn_004360e0` spelling everywhere. Parameter `t`
appears in the native SetTexture diagnostic. The source unit is attested; neither
the inferred function identifier nor the original opaque interface spelling is.

`fcn_00443270` remains a provisional name/home for TL `443270` / Gold `447800`.
One loop processes object-context texture entries, with native-supported offsets,
flag bits and backend calls. Private `d3_*_OFFSET`/`d3_FLAG_BIT` expressions and
byte-access context views are inferred, without claiming complete record types.
The existing canonical `D3_OBJECT` supplies the evidenced `kontext` member.

`EVENT_RUN` is an inferred first-phase call contract, void cdecl with one event
byte pointer. The native runner and two existing providers support it; source-less
providers and original typedef names remain open. Canonical declarations live in
`event_callbacks.h`; second and third phase slots retain their separate open
contracts. Evidence and compiler-width assertions are in `.scratch/goal60`.

### Goal61: periodic timer and cutscene clock contracts

`client_timer.h`, `TIMER_CALLBACK` and `TIMER_CALLBACK_SLOT` are inferred names
and organization. Native TL `42dcd0` / Gold `42e7b0` invoke a no-argument cdecl
callback, ignore its result, divide the unsigned tick count by the slot's period,
and skip paused slots. The German member names `funktion`, `periode` and
`pausiert` describe offsets 0/4/8; their original spelling is unknown. Compiler
checks bind the 12-byte stride under stable ID `client.timer_callback_slot`.
The existing provisional `g_1052c60` denotes a 32-slot declaration view, not a
new allocation or an established storage owner.

The separate native cutscene clock callback TL `4e4a60` / Gold `4e3210` retains
provisional `fcn_004e4a60` and its standalone source home. Its original identifier
and unit are unproved. `game/cutscene_clock.h` is an inferred declaration home;
the existing numeric globals retain their scalar access names. Native signed
comparison precedes the counter increment. No complete backing allocation or
storage owner is inferred from the three adjacent scalar accesses.

Former `g_525e90` was a mistaken data identity at executable TL `525e90`.
Registration now passes the existing `void fcn_00525e90(void)` provider. Its
23-byte function identity survives; the false `.rdata` row is retired through
the locked data writer. Receipts and the old row are in `.scratch/goal61`.

### Goal62: packet-base byte-access contract

`client_packet_builder.h` is an inferred declaration home, not an attested original
header or storage owner. The existing provisional `fcn_004c4510` names TL `4c4510`
and Gold `4c3ba0`; its base argument and `g_aed32c` use a byte-pointer access view.
The function initializes a packet for an integer entity ID and retains that base
when the canonical resolver succeeds. Neither the function spelling nor the
original pointee typedef is recovered. Existing private record views are retained
at callers with explicit conversions to byte access, without integer transport.

The numeric global label and target addresses are unchanged. Its two data rows
now point to the canonical extern; complete allocation ownership and client raw
data remain unverified. `fcn_004ce740` also has a pointer-valued incoming argument,
as established by its native dereferences. Its four native call sites per client
have no reconstructed source providers yet; changing the definition does not
complete those callers. Receipts and the 43-file existing source scope are in
`.scratch/goal62`.


## No-source native mapping (Goal63, 2026-10-16)

This batch maps 55 previously source-less TL inventory bodies (150636 inventory bytes), including ten large-body Gold counterparts. These are native identity and role notes, with no source definitions or new comparison verdicts. Inventory spans may contain tables and alignment; these totals are not newly matched or executable bytes. All existing 8413 metadata rows remain unchanged.

Names below are adopted only when a local diagnostic and Kuna/native behavior agree. `unresolved` retains an address label. Reused diagnostics are not unique names: the three `io_Text` bodies, two `ai_MeisterTradeFernEinkauf` bodies, generic `MASTER`/`he_fn_Handlung` messages, the copied guard-master failure and mixed building-upgrade diagnostics remain explicit. The chapter3 initializer is not named from its inconsistent chapter2 allocation label.

The large-body Gold pairings have complete native/Kuna role review and resource/diagnostic anchors; main-pass Gold entries below are diagnostic candidates only. Neither establishes a compiled shared body, all operands or a linked provider. No server counterpart is claimed.

| TL VA | Inventory span | Attested name | Native role | Gold counterpart/candidate | Native anchor |
|---|---:|---|---|---|---|
| `0x00401d10` | 448 | `unresolved` | Writes an 8-bit indexed BMP: BM header, 256 BGR0 palette entries (grayscale when palette is null), bottom-up rows; does not add row padding. | unresolved | Complete native disassembly and Kuna: .scratch/goal63/00401d10-{asm,kuna}.json |
| `0x00401ed0` | 448 | `unresolved` | SaveBMP24 is an inferred function name from the temp-row allocation label; an original function identifier is not independently attested. Writes a 24-bit BMP, swapping RGB to BGR in a temporary row, bottom-up. Native writes a 44-byte info block and uses pixel offset 0x3a; do not silently replace it with a standard 40-byte header. | unresolved | Complete native disassembly and Kuna: .scratch/goal63/00401ed0-{asm,kuna}.json |
| `0x004045c0` | 1088 | `ch_CheckAniMorph` | Checks and completes character animation morph transitions. | 0x00403dc0 | 0x4049da -> 0x675548: ch_CheckAniMorph(): Could not attach CurrentAnimStream: %s; 0x40486f -> 0x675598: ch_CheckAniMorph(): huston we got a problem... |
| `0x00404dc0` | 416 | `ch_AttachAni` | Builds character animation resource/name strings, loads if absent, attaches a stream and sets frame state. Empty-name path reads an uninitialized native stack local; preserve that finding during reconstruction. | 0x004044a0 | 0x404ef7 -> 0x6755c8: ch_AttachAni(): Could not attach ani: %s |
| `0x00405760` | 362 | `unresolved` | Updates a pending target displacement from character +0x114 and model position/offset; normalizes/scales the step, decrements the +0x110 byte, then clears state at tolerance0.4. | unresolved | Complete native disassembly and Kuna: .scratch/goal63/00405760-{asm,kuna}.json |
| `0x0040a200` | 1024 | `ch_WalkOnPathRotation` | Updates path-following rotation and checks its arrival threshold. | 0x004093d0 | 0x40a5db -> 0x675b18: ch_WalkOnPathRotation(): Have missed my treshhold... %s [%f %f] |
| `0x0040a600` | 4400 | `ch_WalkOnPath` | Advances character path-following, animation and arrival/action state. | 0x004097d0 | 0x40b633 -> 0x675b58: ch_WalkOnPath(): Have missed my treshhold... %s [%f %f] |
| `0x0040eff0` | 464 | `AttachAnimLooped` | Script adapter loads and attaches a named animation with loop options. | 0x0040e0e0 | 0x40f17e -> 0x6768ec: AttachAnimLooped(): Could not find animation-file... |
| `0x004210a0` | 496 | `nt_Recv` | Accumulates socket packet fragments, checks command/sync counts and dispatches complete packets. | 0x00424c80 | 0x421236 -> 0x678b18: nt_Recv(): Lost a Command, cmd->Count is %li, nt_LastRequCount is %li; 0x421218 -> 0x678b60: nt_Recv(): Received Sync, cmd->Count is %li, LastRequCnt is %li |
| `0x0042bf20` | 5840 | `txt_OpenText` | Localized text resource compiler/loader | GOLD.0x0042cbc0 | 0x42d039 -> txt_OpenText(): %s compiled! |
| `0x0043c640` | 5419 | `unresolved` | Terrain material/blend mesh construction | unresolved | 0x43d474 -> d3fl:BlendAttributes |
| `0x0044e1e0` | 3840 | `d3_LoadBinaryAnimStream` | Loads chunked binary animation streams, including vertices, UV faces and frame terminators. | 0x0044f8b0 | 0x44e93e -> 0x67b8e8: Expected EXP_EOCHUNK in d3_LoadBinaryAnimStream(): EndOfFrameLoop; 0x44e76f -> 0x67b92c: Expected EXP_DONE in d3_LoadBinaryAnimStream(): ReadUVFaces |
| `0x0046c5a0` | 6080 | `unresolved` | GUI text-box markup layout/render pass | GOLD.0x0046fb90 | 0x46d525 -> Unknown textparameter: %%%c |
| `0x00480330` | 2352 | `ai_CalcMeisterWache` | Updates guard-master patrol and subordinate actions. | 0x00480e60,0x00482ef0 | 0x480ad0 -> 0x67dd1c: ai_CalcMeisterWache(): Meister %s patroulliert im Umland; 0x480a08 -> 0x67dd58: ai_CalcMeisterWache() : gm_GetGebaeudeHauptraum() failed !!! |
| `0x00480c60` | 1872 | `ai_CalcAngriff` | Selects and schedules attack or espionage actions. | 0x00481790 | 0x481380 -> 0x67dec0: ai_CalcAngriff(): Meister %s hat schon eine Spionage bei '%s' laufen; 0x481370 -> 0x67df08: ai_CalcAngriff(): Meister %s hat aber noch eine Spionage bei '%s' nicht beendet |
| `0x004813b0` | 4112 | `ai_CalcMeisterDiebe` | Updates thief-master burglary and espionage actions. | 0x00481ee0 | 0x482272 -> 0x67dfe8: ai_CalcMeisterDiebe(): Meister %s m; 0x4820ea -> 0x67e020: ai_CalcMeisterDiebe(): Meister %s entf |
| `0x004823c0` | 1952 | `unresolved` | AI action routine reuses an ai_CalcMeisterWache failure diagnostic. That copied string does not establish its own name. | unresolved | 0x48293b -> 0x67dd58: ai_CalcMeisterWache() : gm_GetGebaeudeHauptraum() failed !!! |
| `0x00489250` | 1744 | `ai_MeisterCollectTrans` | Collects and redirects transporters, with once-per-check state. | 0x00489ca0 | 0x489661 -> 0x67e3a8: ai_MeisterCollectTrans(): Um %li:%li Uhr zus; 0x489762 -> 0x67e3a8: ai_MeisterCollectTrans(): Um %li:%li Uhr zus |
| `0x00489a70` | 6064 | `ai_MeisterTrade` | Master-worker inventory trading | GOLD.0x0048a4c0 | 0x48a24f -> ai_MeisterTrade(): Von Auto in "%s" %li Einheiten %s entladen |
| `0x0048b220` | 4993 | `ai_MeisterTradeAllgemein` | General master trade/unload decisions. Its own diagnostics distinguish it from ai_MeisterTrade despite one reused message. | 0x0048bc70 | 0x48c1df -> 0x67e4e8: ai_MeisterTrade(): Fake-Verkauf in "%s" von %li Einheiten %s, weil kein Marktlager; 0x48bd1e -> 0x67e750: ai_MeisterTradeAllgemein(): Fake-Verkauf aus Auto in "%s" von %li Einheiten %s |
| `0x0048c5b0` | 2048 | `unresolved` | Long-distance trading branch sharing ai_MeisterTradeFernEinkauf diagnostics with 0x48cdb0. Individual original name unresolved. | unresolved | 0x48c81c -> 0x67e8c0: ai_MeisterTradeFernEinkauf(): Fake-Verkauf aus Auto in "%s" von %li Einheiten %s; 0x48c7b6 -> 0x67e918: ai_MeisterTradeFernEinkauf(): Von Auto in "%s" %li Einheiten %s entladen |
| `0x0048cdb0` | 2144 | `unresolved` | Second long-distance trading branch sharing ai_MeisterTradeFernEinkauf diagnostics with 0x48c5b0. Individual original name unresolved. | unresolved | 0x48d014 -> 0x67e8c0: ai_MeisterTradeFernEinkauf(): Fake-Verkauf aus Auto in "%s" von %li Einheiten %s; 0x48cfae -> 0x67e918: ai_MeisterTradeFernEinkauf(): Von Auto in "%s" %li Einheiten %s entladen |
| `0x00494ed0` | 579 | `am_RegisterMethod` | Loads and registers an action method and its effects from profile fields. | 0x00495510 | 0x495099 -> 0x67ea30: am_RegisterMethod(): Methode '%s' hat keinerlei Auswirkungen!!! |
| `0x004a4d90` | 544 | `amt_ExecGebaeudeBauen` | Executes a building-construction action using the building prototype/model group. | 0x004a5320 | 0x4a4f96 -> 0x67f074: amt_ExecGebaeudeBauen(): Keine Group f |
| `0x004bdda0` | 272 | `rd_AllBauplatzToSupermap` | Projects the four building-site corners into supermap coordinates. | 0x004bd500 | 0x4bddbd -> 0x681674: rd_AllBauplatzToSupermap(): Unbekannter Bauplatz '%s' |
| `0x004c9a10` | 544 | `cm_ExAddStraftat` | Allocates and fills a crime record, assigns its counter and reports the result. | 0x004c8e70 | 0x4c9a9b -> 0x68afc8: cm_ExAddStraftat(): Executed---- st_id = %i, taeter = %i, opfer = %i |
| `0x004c9e20` | 190 | `cm_ExAllocCutscene` (inferred counterpart) | Goal66: original 384-byte span split into three entries; diagnostic belongs to next111-byte entry. Dispatch index 0x27 pairs with SERVER named handler; unique client identifier unresolved. | 0x004c9280 | Goal63 nearest-diagnostic association superseded; see Goal66 below. |
| `0x004ca970` | 2784 | `cm_ExChrGotoBuilding` | Moves a character into a building/room/universe, with explicit invalid-room diagnostics. | 0x004c9dc0 | 0x4cb094 -> 0x68b108: cm_ExChrGotoBuilding(): Could not find universe...; 0x4cb044 -> 0x68b13c: cm_ExChrGotoBuilding(): invalid room-id (raum==NULL) |
| `0x004cb7f0` | 1184 | `unresolved` | Building upgrade command. Both cm_ExGebUpgrade and cm_ExSetGebUpgrade occur in its diagnostics; exact original name unresolved. | unresolved | 0x4cba31 -> 0x68b240: cm_ExGebUpgrade(): Could not load 3D-Object-Group '%s'...; 0x4cb869 -> 0x68b2ac: cm_ExSetGebUpgrade(): already highest level |
| `0x004cc820` | 848 | `cm_ExCreateGeb` | Creates a building instance and its 3D model group, replacing prior scene objects. | 0x004cbca0 | 0x4ccb14 -> 0x68b304: cm_ExCreateGeb(): could not lc_GetGebaeudeBauplatz()...; 0x4ccaee -> 0x68b33c: cm_ExCreateGeb(): killing objectname: %s |
| `0x004da690` | 7057 | `unresolved` | Council election/removal session cutscene controller | GOLD.0x004d8e20 | 0x4dac50 -> cutscenes\sitzung_main |
| `0x004e0620` | 3344 | `cut_MainDuell` | Duel cutscene state and character creation/update. | 0x004ded10 | 0x4e130f -> 0x68cc70: cut_MainDuell(): Could not create character |
| `0x004eab40` | 1184 | `amt_calc_zuenfte` | Computes guild/office candidates for the selected office type; preserve the attested lowercase spelling. | 0x004e8dc0 | 0x4eaeaf -> 0x68de2c: amt_calc_zuenfte(): could not find a free place... |
| `0x00512b40` | 480 | `init_Betrieb` | Initializes business stock/cost state; emits the zero-cost diagnostic. | 0x0050f570 | 0x512d11 -> 0x6a1cf0: init_Betrieb(): costs are zero |
| `0x00519190` | 7536 | `unresolved` | io_Text-family GUI text expansion and append | GOLD.0x00515990 | 0x519ce3 -> io_Text(): too many icons before redraw! |
| `0x0051af00` | 6464 | `unresolved` | io_Text-family buffer expansion | GOLD.0x00517700 | 0x51c68a -> io_Text(): Missing Random-Text (e.g. {r1})... |
| `0x0051c840` | 6048 | `unresolved` | io_Text-family player-name/template text append | unresolved | 0x51d2a3 -> io_Text(): too many icons before redraw! |
| `0x005238c0` | 1920 | `ls_LoadCharacter` | Loads character tables and converts persisted action/stock identifiers back to pointers. | 0x0051e930 | 0x523fbf -> 0x6a23e0: ls_LoadCharacter(): invalid next or prev-action pointer for action-type:%i; 0x523f0a -> 0x6a2430: ls_LoadCharacter(): invalid stockptr for action-type:%i (character perhaps created by script!) |
| `0x005305d0` | 1069 | `sv_HandleObjects` | Updates scene-view selection and quick-jump contact objects. | 0x0052aea0 | 0x5306ac -> 0x6a301c: sv_HandleObjects(): Could not find QuickJump.ContactName: %s; 0x530722 -> 0x6a301c: sv_HandleObjects(): Could not find QuickJump.ContactName: %s |
| `0x005373e0` | 3200 | `unresolved` | UI master registration/dispatch routine. Generic MASTER diagnostic alone does not establish a unique original identifier. | unresolved | 0x537542 -> 0x6a33f4: MASTER(): Function already registrated! |
| `0x0053fc80` | 916 | `main_RundenBeginn` | Starts a new round and updates participating entities and notifications. | 0x005383a0 | 0x53fcb8 -> 0x6a42d0: main_RundenBeginn(): init round no %i |
| `0x005462a0` | 256 | `unresolved` | Iterates action records with type/owner filtering. he_fn_Handlung diagnostic retained as evidence, not adopted as a proven function name. | unresolved | 0x5462d4 -> 0x6a5784: he_fn_Handlung(): invalid Handlungen_LAST |
| `0x00546720` | 181 | `he_CreateGfxInfo` | Allocates a graphics-info slot, creates its parent resource and restores rendering mode. | 0x0053e9e0 | 0x546789 -> 0x6a57b0: he_CreateGfxInfo(): invalid parent :%s |
| `0x00547770` | 5600 | `unresolved` | Building-mix driven economic command selection | GOLD.0x0053f910 | complete native/Kuna state and command-flow review |
| `0x0055d0d0` | 1296 | `he_AllocTransport` | Initializes a transport action, endpoints, routing and optional escort selection. | 0x00554f00 | 0x55d520 -> 0x6a62a8: he_AllocTransport(): master choose eskorte type %i; 0x55d3f2 -> 0x6a62dc: he_AllocTransport(): Start and goal are the same! |
| `0x0055df80` | 1312 | `he_TransportStadtStadt` | Advances a transport between cities and issues character travel actions. | 0x00555db0 | 0x55e45c -> 0x6a6380: he_TransportStadtStadt(): character-action not attached but target should be reached : %s |
| `0x0055ffe0` | 512 | `he_RunLagerErweitern` | Timed warehouse-expansion action updates storage size and sends completion notification. | 0x00557dc0 | 0x5601a8 -> 0x6a64e0: he_RunLagerErweitern():Wrong LagerID... |
| `0x00564b90` | 1024 | `he_RunKredit` | Advances a credit/loan action and its repayment/default notifications. | 0x0055c950 | 0x564df3 -> 0x6a6620: he_RunKredit(): Could not find GebaeudeId '%i' |
| `0x00568060` | 3472 | `he_RunMarktSupervisor` | Runs market supervision and goods/warehouse balancing. | 0x0055fd80 | 0x5681e9 -> 0x6a6920: he_RunMarktSupervisor(): Could not find markt-lager:%s |
| `0x00581e20` | 5392 | `unresolved` | Tutorial chapter3 task-graph construction | GOLD.0x00579830 | 0x581e90 -> CHAPTER_3_INTRO |
| `0x005988b0` | 2720 | `lc_GebaeudeAusrichten` | Chooses, loads and orients a 3D group for a building site. | 0x0058ffe0 | 0x59926a -> 0x6aa1e8: lc_GebaeudeAusrichten(): Could not load 3D-Object-Group '%s'...; 0x598b0e -> 0x6aa240: lc_GebaeudeAusrichten(): Could not find any 3D-Object-Group fitting this building... |
| `0x005b6300` | 9648 | `unresolved` | Personnel/mercenary book controller | GOLD.0x005aacd0 | 0x5b63c1 -> Buch\Personalbuch_1_Diebesgilde |
| `0x005ba0e0` | 1648 | `ob_TransportFromLager` | Initializes warehouse-origin transport UI/action using the selected storage ID. | 0x005aeaf0 | 0x5ba143 -> 0x6ac37c: ob_TransportFromLager(): Could not find lager by id... |
| `0x005ba910` | 11948 | `unresolved` | Trade/transport inventory panel controller | GOLD.0x005af320 | 0x5baa7b -> panel\infopanel_marktstand |
| `0x005c5310` | 1664 | `ob_HandleBepflanzung` | Handles planting UI/state and loads planting scene groups. | 0x005b9880 | 0x5c58c8 -> 0x6ac6c4: ob_HandleBepflanzung(): Could not load 3D-Objekt-roup '%s'... |

The full FLIRT scan loaded 7102296 signatures and reported 1967 candidates (4679 ambiguous sites skipped). None of the selected bodies earns library attribution from that scan: the five selected `___chk_fail`/`___fortify_fail` hits cover only prefixes of game-specific bodies. All twelve large bodies and the four initial main-pass bodies also reject stock LIBCMT whole-body matches with callee resolution. Misses do not exclude other archives.

BMP native details matter for future source: TL `401d10` writes indexed/grayscale BGR0 palette data and bottom-up rows without row padding. TL `401ed0` / Gold `401b90` carry the `!bmp:SaveBMP24(temp_row)` label; TL writes a 44-byte info block and pixel offset `0x3a`. `SaveBMP24` is a label-derived inferred function name. Goal69 registers the independently reviewed Gold pair as native-only; this creates no source or matched-byte claim. TL `404dc0` / Gold `4044a0` attest `ch_AttachAni`; the empty-name native branch consumes an uninitialized stack slot. Do not silently initialize it while claiming source fidelity.

Receipts and replay inputs are under `.scratch/goal63`: `main-map-plan.json`, `reviewed-map-rows.json`, `mapping-preservation.json`, per-VA native/Kuna dossiers, diagnostic strings with xrefs, and `map-no-source/report.md` plus `mapping-report.json`. Replay with the target named explicitly. The default target is `Europa1400Gold_TL.exe`:

```sh
uv run rebrew binary function 0x<VA> --target Europa1400Gold_TL.exe --json
uv run rebrew binary asm show 0x<VA> --size <inventory-span> --target Europa1400Gold_TL.exe --json
uv run rebrew decompile 0x<VA> --decompiler kuna --target Europa1400Gold_TL.exe --json
uv run rebrew binary strings --filter '<regex>' --xref --target Europa1400Gold_TL.exe --json
uv run rebrew library match --stock-lib LIBCMT.LIB --va 0x<VA> --resolve-callees --target Europa1400Gold_TL.exe --json
```

A miss from that library match does not prove the body is game code. Managed name, size and note rows at this checkpoint were written through the internal `record_function_rows` helper, not a shell command. No source files, type or data stores, or inventory extents changed.

### Goal64: shared supermap sampling

`rd_FillSupermapQuad` at TL `0x004be000` / Gold `0x004bd760` is an
**inferred** role name, following the adjacent attested
`rd_AllBauplatzToSupermap` caller. Its provisional standalone source placement
does not establish an original TU. One C89 body samples a projected quadrilateral
into independently selected byte and 28-byte record planes. Both complete
485-byte bodies match, including all ten address operands, the native double
`0.9` sampling bias and float `1.0` normalization constant. Eleven following NOPs
are alignment. Low-byte `0xff` skips byte writes; full-width integer `255` skips
record writes. No clipping or allocation ownership is inferred.

Projection TL `0x004bdfb0` / Gold `0x004bd710` retains its provisional identifier
and now shares the existing body with four observed map-field offsets guarded
for Gold (`50/60/58/78` versus `90/a0/98/b8`). Executable extents are 67/79;
13/1 following NOPs remain alignment. The inferred declaration home
`src/client_scene_transform.h` reconciles its object/vector pointer contract
with the shared transform provider and all current C callers. No original
vector typedef, backing-map allocation extent or client linked provider is claimed.

Native/compiled operand receipts and rejecting controls are in
`.scratch/goal64/quad/production-proof.json` and `projection-proof.json`.

### Goal65: indexed BMP output

`SaveBMP8` at TL `0x00401d10` is an **inferred** sibling name to the label-derived
`SaveBMP24`, not a recovered identifier. Its standalone source filename is also
provisional. The complete 441-byte writer is matched with all eight address
operands and the `wbn` mode literal; seven following NOPs are alignment within
its retained448-byte inventory span. It writes a14-byte BITMAPFILEHEADER,
40-byte BITMAPINFOHEADER,256 BGR0 entries and bottom-up unpadded rows. A null
palette selects grayscale. Write failures are ignored as in the native body.

The two26-byte zero-fill preludes are the original operand-homed handwritten
macro documented in docs/msvc6-allocator.md. Reuse is justified by that independent
compiler/provenance evidence and fresh native-site/stock-archive exclusions,
not by a difficult C match. The private `fill0` name is inferred; target-scoped
managed source evidence records its definition. Stock Windows SDK BMP types are
used without inventing local layouts or storage. VFS backing ownership/provider
and broader legacy VFS declarations remain open. A fixed-prefix miss in Gold
is not evidence that no differently compiled counterpart exists.

Production replay: `.scratch/goal65/indexed/proof.py`, `production-proof.json`,
`assembly-proof.json` and `effects.py/json`. Eight bounded native/compiled cases
verify exact headers, grayscale/custom palettes, odd widths without padding,
zero/negative heights, open failure and ignored write failure against independently
packed bytes. Real VFS execution and arbitrary-input safety are not established.

## Method registry and cutscene entries (Goal66, 2026-10-16)

`am_RegisterMethod` is attested by its native diagnostic at TL495099 and Gold
4956d9. One shared 579-byte body covers TL494ed0 and Gold495510. Inferred
`AM_EFFECT`/`AM_METHOD` names, fields and `client_method_registry.h` organization
describe native 8-byte effects and 0x94-byte method strides, not allocation sizes.
Callback slots retain opaque address views; their invocation contracts are open.
The unsigned effect kind compared with full-width-1 is native behavior. Profile
reads use the global filename; the second argument is only a profile-mode test.
An explicit memcpy copies32 bytes, followed by a37-DWORD registry assignment.
`#pragma function(memcpy)` is inferred source spelling for that evidenced call.
No storage definitions or complete registry/filename allocation claims are added.

The old384-byte inventory span at TL4c9e20 / Gold4c9280 actually contains
three separately dispatched functions:

| Command index | TL / Gold | Executable bytes | Following NOPs | Name evidence |
|---|---|---:|---:|---|
|0x27|4c9e20 /4c9280|190|2|Existing cm_ExAllocCutscene remains an inferred family/counterpart association, not directly attested at this entry.|
|0x28|4c9ee0 /4c9340|111|1|cm_ExCreateCutsceneEntry is inferred. Its cm_ExAllocCutscene diagnostic may reuse family text.|
|0x29|4c9f50 /4c93b0|70|10|cm_ExAddCutsceneParticipant is inferred from lookup, append and optional success reply.|

The three native pointer sites are TL68aa7c/80/84 and Gold60be14/18/1c.
SERVER1002c494 points at existing named cm_ExAllocCutscene1000f0a0; its
next two entries point at cm_ChainNoop1000f3a0. The 111-byte client body must
therefore not be merged into the SERVER definition based on reused diagnostic
text. Its allocation helper returns a pointer consumed by both native client
callers; the repaired shared helper preserves all 46 bytes in both clients.

`g_aed340` is an incomplete incoming bytebuffer view, separate from outgoing
`g_aed32c`. Reassembly and 248/276/860-byte consumers do not establish its
complete allocation, owner or a backing relationship. Existing byte flag views
likewise do not prove the complete wider flag allocation. All new data rows
remain declarations.

Complete native operands, literals and rejecting controls are in
`.scratch/goal66/method-production-proof.json`, `commands-production-proof.json`
and the independent parallel reports. These object proofs do not establish
client raw-link provider selection, placement or full-image identity.

## AttachAnimLooped (Goal67, 2026-10-16)

The script diagnostic attests `AttachAnimLooped` at TL40eff0 / Gold40e0e0.
The shared C89 body has 454 executable bytes followed by ten alignment NOPs;
its 464-byte native inventory spans are retained. The source filename and
placement with the other character script callbacks are inferred.

Arguments are a character-pointer slot, animation-name-pointer slot and full
integer kind pointer. The resumed path reads the object before any null-object
check, then tests three nullable draw-data pointer cells at stride 0x7c. Their
first offsets are TL 0x484 / Gold 0x178; these measured byte views do not claim
complete slot records, backing allocations or a universal context layout.
A nonempty cell reschedules this callback; null draw or three empty cells return0.

The fresh path appends `.baf`, copies the path to a name buffer and runs existing
401040 on that name. Its returned basename is copied into an otherwise unused
third buffer. Preserve this copy and the helper's first-separator/first-dot
behavior. Lookup uses the mutated name, loading uses the original path,
and attachment uses object+0x1cc. A loader failure does not suppress attachment.
Attachment failure invokes the original script diagnostic; no new logger is added.

Existing `D3_ANIMATION_OPTIONS` remains twelve bytes passed by value. Native sets
mode to low8(kind), layer to 16 only when the FULL integer kind equals1, loop to 1,
reverse to 0 and queue to 1; all remaining bits/padding are zero. Canonical helper
434970 / Gold435550 consumes context,name and those three DWORDs and returns a
slot pointer. Its prototype is now in d3_animation.h, replacing three identical
local declarations. That native ABI proof does not create a source/link provider.
The existing stable type ID was rebound without changing its layout.

Complete two-target native proofs cover fifteen operands, three literal uses and
25 rejecting controls per target. Independent preservation checks cover all 41 old
contexts across fifteen existing files, including the weak TL ch_Updatelowpoly;
all compiled code, fixups, literals and function-definition hashes stay unchanged.
Receipts: `.scratch/goal67/attach-loop/{proof.json,effects.json}` and
`.scratch/goal67/animation-preservation/preservation.json`. No storage, assembly,
compiler override or raw client-link identity is claimed.

## Object-universe mapping helper (Goal68, 2026-10-16)

TL515540 / Gold511df0 is a separate 151/146-byte helper, provisionally named
`fcn_00515540`. Original identifier and source placement remain inferred. It maps
an object's unsigned-short type through a signed-byte table, initializes a
selected object or allocates a free universe index, then marks the row used and
copies the prototype name. Preserve the signed final reload, including after
the selected-object initializer changes object type or mapping. Allocation -1
returns immediately without mutation; no bounds, rollback or new failure
behavior has been invented.

Private `D3_UNIVERSE_VIEW` records only inferred row strides3dcTL/3e0Gold and
used byte+3d5. Its opaque prefix is not a recovered string capacity; neither
that view nor the shared game_data.h prototype-table extern claims allocation
or storage ownership. Stable type ID is d3.universe-view. Initializer510c90 /
50d7f0 has no adopted C/raw-link provider.

The old496-byte discovery spans at 5153f0 /511ca0 split into 336+160 through
reviewed inventory repair. Existing331-byte source extents and historical
reference hashes remain intact, with five NOPs before the admitted helper.
Trailing9TL/14Gold NOPs stay separate from its executable source extent. Complete
proofs and bounded effects: .scratch/goal68/helper-proof.

## init_LoadObjektScene (native identification, Goal69)

Original diagnostic `init_LoadObjektScene:Could not find a free universe...`
attests the initializer at TL510c90 /Gold50d7f0. The native-only rows record that
name and complete 940/938-byte extents; they create no C source, linker provider,
comparison status or recovered original signature. All twelve known direct
callers discard EAX; void(int) is a supported future contract, not uniquely
recovered source spelling. Source-unit ownership remains unknown.

Both bodies have32correspondingCFG blocks and 80pairedaddress sites. Gold adds
call46e980 and signed-short loading coordinates. Preserve allocation-1 continuing
through the diagnostic, scene-load failure without universe restoration, live
mapping/resource reloads and conditional timer restoration. The 768slot objects
are character/controller views, distinct from scene D3_OBJECT nodes. Hidden
caller entries4e4230 /4e2910 are separate from existing 165-byte matches.

Evidence:.scratch/goal68/init-scene/REPORT.md and native-dossier.json;
registration:.scratch/goal69/native-initializer-registration.json. Library misses
are inconclusive alone; the diagnostic and universe/character operations establish
application provenance. Native naming is separate from reconstructed game bytes.

### SaveBMP24 native mapping correction (Goal69)

TL401ed0 /Gold401b90 have complete 439-byte bodies plus 9alignment NOPs in
unchanged448-byte inventory spans. Both native-only rows now use the inferred
name SaveBMP24, derived from !bmp:SaveBMP24(temp_row). Direct label PUSH sites
401fbb /401c7b and the full BMP algorithm support the role; the allocation label
does not independently attest the original function identifier. This supersedes
earlier attested-name wording, including the sibling discussion above.

The pair agrees at 399fixed bytes and ten corresponding address operands. Gold's
direct caller 589f34 confirms its actual entry. Preserve the 14-byte file header,
44-byte info block,pixel offset 0x3a,RGB-to-BGR temp-row conversion and bottom-up
writes. No C symbol, source, status, selected provider or extent changed.
Evidence:.scratch/goal69/native-names/{manifest.json,review.md,registration.json}.

## Native role mapping and Gold action identities (Goal70)

Retain address names for six newly mapped TL entries: personnel book `0x5b88b0`,
progress renderer `0x467920`, family tree `0x5d0660`, universe selection
`0x4432d0`, scene loader `0x448360` and scene-map rebuild `0x45b290`.
These roles are inferred from complete native behavior and resource references;
no original function identifier, source path or provider is established.

Gold diagnostics independently attest `he_AllocTransport` at `0x554f00`,
`he_TransportStadtStadt` at `0x555db0`, `he_RunKredit` at `0x55c950`,
`he_RunMarktSupervisor` at `0x55fd80` and `main_RundenBeginn` at `0x5383a0`.
Their TL names were already mapped in Goal63. Across all five pairs, 7,973
executable bytes agree after substituting 339 corresponding address fields;
231 internal edges retain their offsets. This is native correspondence, not
compiled-source or callee-provider verification. All eleven admitted rows remain
without source, symbol, status or verification claims.

Boundary repairs separately expose TL `0x5c1490`, `0x5c18e0`, `0x5c23b0`,
`0x5b9980` and Gold `0x5ae390`. Their original names remain unknown. The repaired
spans preserve every prior byte and do not affect an existing source/status row.
Receipts: `.scratch/goal70/no-source-{large,resources,actions}/REPORT.md` and
`preservation.json`. FLIRT misses remain inconclusive; no library classification
is assigned from a miss or a partial failure-helper signature.

## Separated UI entries and ecmd_LoadScene (Goal71)

TL `0x5c1110` is the pamphlet noticeboard with four action rows; poem/audio
resources belong to separate `0x5c1490`. TL `0x5c18e0` handles residence feast
configuration/invitations, `0x5c23b0` confirms building sales and `0x5b9980`
acquires transport carts. Keep address names: these roles do not attest original
C identifiers. Gold counterparts are respectively `0x5b57e0`, `0x5b5b70`,
`0x5b5fd0`, `0x5b6aa0` and `0x5ae390`. Complete per-body resources, callers,
extents and counterpart limits are in `.scratch/goal71/boundary-ui/REPORT.md`.

The exact `ecmd_LoadScene: Could not find scene on disk...` diagnostic and
single-purpose native behavior attest `ecmd_LoadScene` at TL `0x40ed00` and
Gold `0x40ddf0`. Each 55-byte entry follows a separate 64-byte matched function;
its nine trailing NOPs are alignment. It reads the filename from its argument,
calls the loader with NULL stream/callback, tests AL, diagnoses failure and
returns full-width one. C argument spelling, TU placement and providers remain
unresolved. Native-only rows earn no source or match verdict. Evidence:
`.scratch/goal71/scene-loader/boundary-review.json` and `REPORT.md`.

Sale-loop source must retain the same-iteration confirmation after setting exit
state for invalidity. Its lookup uses cached entry ID, but packet construction
reloads live building `+1`. `_ftol` consumes implicit x87 values; Kuna's apparent
integer arguments are wrong. Full native suffix controls and limits are in
`.scratch/goal71/sale/loop-effects.json`; this is not a compiled-source proof.

## Large functions and scene/credit dependencies (Goal72)

Keep address names for combat results TL `0x4d6170` / Gold `0x4d4d70`, combat
task progression `0x4d8d00` / `0x4d76a0`, and round/day refresh `0x540020` /
`0x538740`. Complete native behavior, resources and callers support these roles
and pairings, without original names, source placement or provider claims.
TL `0x432410` is a 111-byte name lookup; independent callback `0x432480` is
4,850 bytes. Their original names remain unknown.

The direct unknown-type diagnostic and recursive scene-reader behavior attest
`rd_object` at TL `0x447110` / Gold `0x44abb0`. Terrain readers TL `0x447e30` /
Gold `0x44b920` retain address names: `d3_int_io:FloorWaterRegions` is an
allocation label, not a function identifier. Both readers borrow their streams.
Gold `0x401380` corresponds to TL `0x401500`; TL's same address is unrelated.

Credit recovery TL `0x5c4ec0` / Gold `0x5b9430` retains address names; module
ownership and the original identifier are unproven. Gold `0x501190` inherits
the canonical descriptive name `gm_StartFilteredEntitySearch` from its complete
native TL `0x503fe0` counterpart. This is native identity mapping, not adoption
of spiel.c's emitted candidate definition or an attested original spelling.

Retain both `fcn_0051af00` formatter names. TL siblings `0x519190`, `0x51af00`
and `0x51c840` reference the same `io_Text` diagnostic; the output-buffer role
does not uniquely establish the bare function name. Complete formatter extent
is 6,455 bytes, retaining 6,282 code bytes, two alignment bytes, an 88-byte
jump table and an 83-byte selector table. Shared diagnostics and masked FLIRT
prefixes do not establish unique identities or selected library providers.

Evidence: `.scratch/goal72/{large,credit-deps,scene-deps}/REPORT.md`, native
manifests, caller matrices and replay proofs. All admissions are native-only;
no source, symbol, match verdict or provider is earned by mapping.


## VFS closer declarations and entity call binding (Goal81, 2026-10-17)

TL `CloseVfsStream` (`0x430580`) reuses existing inferred address names
`g_6b7fe4` and `g_6b7fec`, with private logical macros `g_stream_pool` and
`g_stream_count`. No original spelling or storage owner is newly asserted.
The receiver's `fcn_00522e30` references are bound to the existing managed
`GOLDTL.0x00522e30` / `ls_LoadEntities` identity, not a newly invented function.
The disabled copied definition in `GOLDTL.loadsave2.c` remains physical source;
it is not a second compiled provider. The upstream reference-binding guard now
excludes proven literal-zero branches and still rejects unknown/live alternatives.
The destination identity, source and verdict do not change. Receipts:
`.scratch/goal81-vfs/{entity-name-apply.json,receiver-after.json,close-proof.json}`.

## Opaque stream formals (Goal82, 2026-10-17)

`stream` and `stream_ctx` describe inferred opaque VFS parameters; they are not
attested source spellings or a newly established struct. The former
`ahm_AllocAhmInfo` formal `cmd_payload` was a savegame stream. Existing loader,
allocator and storage identities retain their names. The recovered TL building
reader still uses its existing `fcn_00522510` identity pending a reviewed
canonical name binding; its completed body does not attest an original name.

The Gold dialog's `dd_` prefix is attested by diagnostics from
`D:\develop\Units\dd_vesa\Dd_vesa.c`, including `dd_Guid` and `dd_BitPlanes`.
The new declaration spellings such as `dd_DriverCombo` and `dd_DeviceCount`
are inferred and recorded as such; operand agreement does not attest those
exact names. TL version and auxiliary slots retain their existing legacy
declaration names pending a canonical naming review. Literal inventory labels
`str_f3g_PlantMap` / `str_AHM_INFO` are inferred labels for compiler pools,
not invented C identifiers or storage owners.
`str_STADTAUSWAHL_s_INFO_0` likewise labels the complete format literal;
the existing inferred global names `g_85ab80` / `g_14a5320` identify native
bases without asserting original names, allocation bounds or owners.

## Scene callbacks and resource views (Goal83, 2026-10-17)

`SCENE_PROGRESS`, `SCENE_PROGRESS_CONTEXT` and `SCENE_RESOURCE` are inferred
access contracts in the client scene headers. Native progress calls pass three
full integers and discard EAX. Gold resource selectors remain full integers even
where code tests their low byte. The TL callback context has a 20-byte stride;
the Gold resource record has a 128-byte stride. Gold offsets must not be applied
to the TL resource record, whose stride is 112 bytes.

The Gold declaration spellings `g_104049c`, `g_10404a0` and `g_6b8af0` reuse
existing inferred TL correspondence names at separate native addresses. They
describe pointer/count/clear slots, without new storage or ownership. The TL
scene scalar and indexed-base identities retain their existing provisional
address names. `str_rb`, `str_boden` and `str_Scene_too_old_Sorry` are literal
inventory labels, not original C identifiers or defining translation units.

The Gold clone-list helper retains `fcn_0043ca20`; its native contract consumes
one object pointer and no return value. Combined caller cleanup includes an
earlier clone-constructor argument and does not attest a second parameter.
Evidence and unresolved pointer views are in
`.scratch/goal83-gold-scene/contracts-followup/` and `contracts-root/`.

Gold `g_fc2700` and `g_fc28f4` retain unattested address names. The latter is
the former's list-head pointer at offset `0x1f4`, matching `voriges` in the
existing D3 layout. This relationship names an accessed view; it establishes
neither the sentinel's full static extent nor its storage owner.

`ReadVfsFourDwords` is an inferred descriptive name for the shared TL `0x4012b0` / Gold `0x401270` reader. It separates that definition from Gold `0x4012b0`, which writes three dwords. The placeholder collision did not establish common behavior or a shared provider.
