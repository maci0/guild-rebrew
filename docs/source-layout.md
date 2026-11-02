# Source layout

Use one shared C tree under `src/Develop/`, following attested `D:\Develop`
paths. A byte match establishes code agreement; original TU ownership still
needs path, diagnostic, counterpart or dependency evidence. Label inferred
placement. Address-named files in `Unassigned` remain a consolidation backlog.

| Location | Evidence and current use |
| --- | --- |
| `src/Develop/DieGildeAddOn/game` | Attested game units, including `spiel.c` and `sim.c`; client counterparts live alongside them until safe merging is established. |
| `src/Develop/DieGildeAddOn/command` | Attested command and lobby units. Client addresses previously given unrelated server command names require correction before grouping. |
| `src/Develop/DieGildeAddOn/auxillary` | Attested plant subsystem. |
| `src/Develop/DieGildeAddOn/loadsave` | Attested save/load unit. |
| `src/Develop/DieGildeAddOnServer` | Attested server unit and reconstructed shared declarations. |
| `src/Develop/Units` | Attested reusable units: Error, allocation, VFS, network and renderer modules. |
| `src/Develop/Unassigned` | Recovered functions whose original module/TU is unresolved; inferred placement is not original path evidence. |
| `src` directly | Shared reconstruction headers and remaining support files; move them only with ownership evidence. |

## Moving sources

Review all-target providers, original TU context, storage instances and native
order with `rebrew source organize review` before merging or splitting. Preserve
raw baselines, includes, compiler flags and declaration order; compare complete
COFF bodies/operands and rebuilt images with `rebrew source organize check` afterward.
Move managed identities through Rebrew's writers. Headers declare objects; source definitions or selected library members allocate storage.

The October 19 review moved the attested `d3_LoadAnimStream` definition into
the existing D3 directory and corrected the stale `cm_TestCommandResult`
filename. Neither move establishes an original TU boundary. The texture family
has stronger unit evidence: Gold `0x45f6c0` references
`D:\develop\Units\d3\ts_texture.c`; the TL counterparts share its allocation
labels and call graph, but retain different record layouts and bodies.

Further consolidation must preserve native definition order. In particular,
the two TL savegame readers interleave four definitions currently emitted by
`loadsave.c`. Moving them into separate files beside that unit would not
reconstruct its TU order. Review a single client loadsave unit and target-scoped
providers before merging; keep the distinct server bodies. Reports and current
object-preservation checks are in `.scratch/dsh-wave1/results/17/`,
`results/20/` and `.scratch/dsh-wave1/naming-review/`. Raw-link checks remain due.

The October 11 placement pass used these witnesses:

| Source | New directory | Placement evidence |
| --- | --- | --- |
| `GOLD.vfs_CloseStream.c` | `Develop/Units/vfs` | Existing VFS twin and stream close behavior; VFS unit path is attested. |
| `GOLDTL.fcn_004208a0.c` | `Develop/Units/net` | The function logs the literal original path `D:\develop\units\net\net.c`. |
| `GOLD.fcn_00503f30.c` | `Develop/DieGildeAddOn/game` | Shared `gm_IsInRange` counterpart is defined in existing `spiel.c`. |
| `GOLDTL.fcn_0050e000.c` | `Develop/DieGildeAddOn/game` | `gm_eval_SlotVoll` counterpart is in `spiel.c`, with the original unit path in its log. |
| `GOLD.fcn_0047cec0.c` | `Develop/DieGildeAddOn/game` | Its TL `sim_SetSyncParams` definition has an existing `sim.c` counterpart. The other GOLD body in this file has no independently established original unit; the grouping remains provisional. |
| `d2_gui.c`, `d2_gui.h` | `Develop/Units/d2.v1` | Attested d2 unit directory and GUI role. The reconstructed `d2_gui` filename and exact original unit are inferred. |
| `d3_floor.c`, `d3_floor.h` | `Develop/Units/d3` | Attested d3 renderer directory and native `d3_fl:Water` allocation labels. Exact original unit and reconstructed filename are inferred. |
| `GOLDTL.d3_LoadObjectAnim.c` | `Develop/Units/d3` | Existing inferred d3 identity; still an incomplete stub, not a recovered original unit. |

Automatic address clustering was insufficient: 6,335 TL functions collapsed into
three groups. Direct path references supplied 37 stronger client witnesses.
Receipts: `.scratch/goal20/source-organization/` and
`native-unit-map/direct-path-evidence.json`.

## MSX and D3 placement, October 11

Native TL `0x420840` / Gold `0x4244b0` reference `Units/Msx/msx.c`.
The reconstructed shared unit contains eleven functions; individual names and
exact original helper units remain inferred where no diagnostic attests them.

| Role | TL | Gold |
| --- | --- | --- |
| Fade state | `0x420700` | `0x424370` |
| Channel stop | `0x420120` | `0x423df0` |
| Ambient stop | `0x420840` | `0x4244b0` |
| Named-track lookup | `0x4205e0` | `0x424250` |
| Free-slot selection | `0x420690` | `0x424300` |
| Active-track selection | `0x420650` | `0x4242c0` |
| Ordinary acquisition | `0x41fd70` | `0x423a90` |
| Ambient acquisition | `0x420780` | `0x4243f0` |
| Start/queue | `0x41fe10` | `0x423b30` |
| Volume | `0x41fc10` | `0x423930` |
| Track path | `0x420760` | `0x4243d0` |

The canonical track view is 296 bytes. `hTrack->bAmbient` is attested;
volume at `+0x118` and self-pointer at `+0x124` have native access evidence.
The path view is TL `0x14cc360` / Gold `0x14611a0`; Gold `0x478860` writes a
separate `0xf8aae0` buffer and is not its twin. Storage owners/extents remain
unresolved. The updater remains 793 compiled versus 791 native bytes; loop
anchors `+0x110`/`+0x118` explain six instruction-width differences.

The final start/volume receipt checks 3,404 native bytes and 206 operands,
preserves 33 complete bodies and records bounded sanitizer checks. Receipts:
`.scratch/goal20/msx-{shared-unit,track-table,track-type,start-volume}/scope-final.json`.
The full pre-cleanup [archive](goal-history.md#full-notebooks) retains intermediate
counts and fixture limits.

Gold `0x438780` belongs in attested `Units/d3/d3_d3d.c`. Native EndScene uses
vtable byte offset `0x28` (entry 10), without another dereference, and logs
nonzero results. Its repaired 44-byte body/five operands match. Device spelling
is attested; result/interface names remain inferred. Receipt:
`.scratch/goal20/native-unit-batch/`.

## Character subsystem placement (2026-10-11)

Seventeen existing sources and `ch_motion.h` moved to the game subsystem using
character diagnostics, task/resource dependencies and callback evidence.
`CreateAnimationEvent` does not belong to the unrelated server health command.
Exact original character filenames/TUs remain inferred.

| Sources (old basenames) | Native placement evidence |
| --- | --- |
| `GOLD.fcn_004033c0.c`, `GOLDTL.fcn_00403bc0.c` | `ch_MoveCharacter2Universe()` diagnostic and character scene-node transfer. |
| `GOLDTL.fcn_00404150.c`, `GOLDTL.fcn_00404a00.c` | `ch_AttachMotion()` diagnostic, character motion resources, shared completion/preloader helpers. |
| `GOLDTL.fcn_004068e0.c`, `GOLDTL.fcn_00406b50.c` | `ch_TakingObject()` / `ch_DroppingObject()` diagnostics and character-task state. |
| `GOLDTL.fcn_0040c9b0.c`, `GOLDTL.fcn_0040cff0.c`, `GOLDTL.fcn_0040d130.c` | Character creation and animation-script diagnostics. |
| `GOLDTL.fcn_0040d410.c`, `GOLD.fcn_0040c4f0.c` | `TakeObjectScript()` diagnostics and dummy/animation/script task setup. |
| `GOLDTL.fcn_0040d8c0.c` | `SetCharacterCamera()` diagnostic and character camera choices. |
| `GOLDTL.fcn_0040df40.c`, `GOLDTL.fcn_0040e150.c` | Sitting queries and character subobject/name diagnostics. |
| `PlayEntitySound.c`, `PlayCharacterAniSound.c` | Attested animation-sound API and its native task callback. |
| `GOLDTL.CreateAnimationEvent.c` (now `CreateAnimationEvent.c`) | Existing shared animation-task builder and native callback/caller evidence. |
| `ch_motion.h` | Canonical completion/preloader declarations used by the moved motion source; two existing scalar alias views. |

The move preserved 34 complete COFF bodies and moved 33 function/nine data
identities through managed writers. Existing sitting-query mismatches remained.
Seven later diagnostic-based renames are recorded in the
[naming ledger](naming_conventions.md). Receipts:
`.scratch/goal20/character-placement/` and `.scratch/goal21/continuation/`.

## Shared character scene and script helpers (2026-10-11)

Shared `character.c` owns `ch_MoveCharacter2Universe` (TL `0x403bc0` / Gold
`0x4033c0`) and `TakeObjectScript` (TL `0x40d410` / Gold `0x40c4f0`).
`ch_motion.h` supplies canonical prototypes. Native layouts preserve TL
`+0x215` bit 1 versus Gold `+0x211` bit 3 and dummy-name offsets `+0x40c`/`+0x104`.
The neutral `darstellungsflag` avoids an unproved lighting/mirror interpretation.

Complete 1,181-byte/52-operand comparisons and rejecting controls pass; ten
consumer bodies are preserved. The 141,320 C89 sanitizer cases model helpers
under valid-input preconditions, not real helper execution or storage ownership.
Twelve declaration views allocate no storage. The existing 16-byte vector view
has only 12 scene-translation bytes observed here.

The native scene caller follows the matched 96-byte selector at TL `0x407330` /
Gold `0x406790`; it is a separate sibling. TL `0x402aa0` is one RET plus 15 NOPs,
below discovery's eight-byte minimum; Gold `0x402540` is nonempty.
Receipt: `.scratch/goal20/character-shared-pairs/`.

## D3 type identities and full byte extents (2026-10-11)

Owning header: `src/Develop/Units/d3/d3_object.h`. Bind stable IDs through
`rebrew types bind`; check both clients with `rebrew types check --compile`.

| Type / stable ID | TL | Gold |
| --- | --- | --- |
| `D3_OBJECT` / `d3.object` | `0x228` | `0x228` |
| `D3_OBJECT_DRAW_DATA` / `d3.object_draw_data` | `0x1640` | `0x970` |
| `D3_DRAW_PART` / `d3.draw_part` stride | `0x4a4` | `0x198` |

Four draw slots begin at `+0xf4`. Object resource `kontext` is at `+0x1cc`;
tree `eltern` is TL `+0x1fc` / Gold `+0x1f8`. Character `+0x34` points to the
object, object `+0x1ec` to draw data. Allocation/init/tree instructions establish
native extents; compiled assertions check C layout. Names remain inferred and
unknown fields stay byte regions. Receipt: `.scratch/goal20/type-identity-layouts/`.

## Shared client allocator helper checkpoint (2026-10-11)

The tracking check at `Units/m_alloc/GOLDTL.fcn_0041dd90.c` supplies both clients
(Gold 60 code bytes + four NOPs). `GOLDTL.fcn_0041e410.c` supplies the 43-byte
free-all body, retaining its null-head guard. Four managed scalar/pointer cells
are declaration views, without storage/data claims. This 2026-10-11 checkpoint
left the 117-byte client tracked-free body and the 188-byte server body
unmerged. That split is still not an attested single spelling and is not
permission to synthesize one body. Receipt: `.scratch/goal21/allocator-client-repair/`.

Upstream `42e0a8c0` repaired merge/rehome's loss of existing managed rows in
legacy-marker files, including rollback and bound-definition guards. That fix
is historical. Current readers reject legacy markers; format-3 function
metadata has no separate source store. Historical receipts keep their original
paths. Current state belongs in [TODO.md](TODO.md).

## Client placement views (Goal75, 2026-10-17)

Inferred declaration home `src/client_placement.h` owns `LC_GEBAEUDE_BAUPLATZ`
(84 bytes, stable ID `lc.gebaeude-bauplatz-result`) and `LC_OBJECT_LIST`
(132 bytes, stable ID `d3.object-selection-list32`). Both clients have compiler
size/offset checks. Native stack clears establish 21 and 33 DWORDs at
TL `0x4cc9da`/`0x4cca7c` and Gold `0x4cbe5a`/`0x4cbefc`. These are stack views,
not heap/global allocations. Result fields remain name+0, position+0x40,
unknown+0x4c, node+0x50; the list has 32 pointers and count+0x80.

The lookup provider, placement provider/callback, both collector providers and
existing consumers reuse the header. Fourteen client contexts retain 3,224
complete compiled bytes, all COFF operands and literals. The eight placement
contexts additionally pass complete native byte/operand proofs at TL
`0x5982d0`, `0x598330`, `0x598550`, `0x5985f0` and Gold `0x58fa00`, `0x58fa60`,
`0x58fc80`, `0x58fd20`. The numeric `0x442d50`/Gold `0x447300` argument contract
is preserved. Both iterator providers stay separate; client raw-link layout,
global owners and the larger universe contract remain open. Receipts and replays:
`.scratch/goal75-placement/{REPORT.md,preserve.py,preserve-extra.py,native-proof.py}`.


## Scene command declaration boundary (Goal80, 2026-10-17)

The two 55-byte `ecmd_LoadScene` commands remain in their existing target files.
`source organize review` reports unavailable client raw baselines and
`safe_to_reorganize=false`; no source move or merge was applied. Shared behavior
and matching objects do not establish original TU placement or complete PE agreement.

The inferred `client_scene_loader.h` supplies native byte-return/three-argument
loader declarations, the three-int callback and embedded-scene pointer bridge.
`client_script_runtime.h` shares the existing script-error provider's declaration
and reuses the current `ch_motion.h` global view. These headers allocate no storage.
Ten pre-existing client contexts preserve complete code, fixups and data sections.
At this Goal80 checkpoint the loaders were placeholders. Later scene-loader C
recovery does not establish a native byte match or original handle type; use
current metadata for implementation/verdict state. The recorded integer stream
transport at TL `0x525b40` was cutover debt. No SERVER-bound input changed. Evidence:
`.scratch/goal80-scene/{verification-scope.json,proof.json,stream-boundary.json}`
and `.scratch/goal80-organize-review.json`.

### Network local-address placement (2026-11-01)

T&L `nt_GetLocalIp` (`0x420d20`) lives in `Develop/Units/net` beside the network
routines. Its cached Winsock lookup and native position support this subsystem
placement; the reconstructed filename and exact original TU remain inferred.
The move preserves a separate compilation unit and adds no storage claim.

### Entity lookup and pricing placement (2026-11-01)

T&L `gm_LookupEntityRecordById` (`0x508e40`) and
`eval_ObjektPreis2Credits` (`0x50b980`) live in the game directory, each in its
own compilation unit. Their reviewed server counterparts reside in `spiel.c`;
the exact client TU boundaries remain inferred. The retired Gold lookup claim
stays retired, and the distinct server implementations remain canonical.

### Line renderer placement (2026-11-01)

T&L `dd_Line` and `dd_EndLines` share the inferred
`Develop/Units/d8_vesa/d8_vesa.c` translation unit. They are adjacent in the
native image and use the same line buffer. The `dd_Line` diagnostic references
`d8_vesa.c` for its line limit; it does not establish the original TU boundary.

### Gold DirectDraw dialog placement candidate (2026-11-01)

Gold `0x41c830`, currently in `Units/d3/GOLD.fcn_0041c830.c`, has three
bounded direct references to the native path `Units/dd_vesa/Dd_vesa.c`.
This supports reviewing it for the attested `dd_vesa` unit; that unit is
distinct from the inferred T&L `d8_vesa` line-renderer placement. The current
file also defines data and remains in place until its storage and linked
placement can be checked against a fresh Gold build.

### Shared client table search (2026-11-01)

Gold `0x4f36e0` and T&L `0x4f5810` use the same target-conditional definition
in `Unassigned/FindStraftatIndexById.c`. The name is inferred from the crime
table's use by `cm_ExAddStraftat`; the original name and subsystem remain
unproved. Both contexts tested EXACT after the rename (31 of 31 bytes each).

### Office-slot type review (2026-11-01)

`OfficeSlot` in `game/office_slot.h` and `OFFICE_SLOT` in `game_structs.h`
describe the same six field offsets in a 24-byte record. The former uses
signed `char` for its byte fields; the canonical server `OFFICE_SLOT` uses
`unsigned char`. `aemter.c` compares some `OfficeSlot` fields directly with
signed bytes, so simply substituting the canonical type would change integer
promotion for values above 127. Consolidation requires reviewing those uses
and preserving their native signedness before removing either declaration.
The managed `amt.office_slot` type already binds `OFFICE_SLOT` in all three
targets, with the 24-byte stride and field offsets supported by the evidence
recorded in that binding.
Server `amt_SwapOfficeHolders` (`0x1000b880`) compares the two slot ID bytes
directly at `0x1000b8be` and `0x1000b90a`; those equality instructions do not
establish a signed field type. Receipt:
`.scratch/sim-consolidation/office-swap-native.json`.

The two views were subsequently consolidated in `aemter.c` onto the managed
`OFFICE_SLOT`. Explicit signed casts retain the earlier comparisons. An
isolated compiler comparison found all 91 object sections and relocation
targets unchanged; the actual server rebuild and verification are pending.
The server rebuild subsequently succeeded and produced the same DLL bytes;
all ten source-bound office functions matched under relocation masking and
all 316 checked server functions passed raw-link verification as EXACT.

### Client crime counter (2026-11-01)

`CountMatchingStraftatEntries.c` stays in its existing command directory. Its name is inferred; the original TU remains unproved. The server readiness function remains separate.

### Client cutscene readiness (2026-11-01)

The Gold `0x4c69c0` / T&L `0x4c7550` shared client definition resides in `command/command_c/cm_ChkCutsceneReady.c`. Gold chain-dispatch entry 89 and native body identify it as the server readiness counterpart; the server body remains canonical and includes its own log. Original TU placement remains inferred.

T&L chain-dispatch entry 89 also points to `0x4c7550`; its primary dispatch
entry 89 points to execution handler `0x4cd590`.

### Client cutscene execution (2026-11-01)

Gold `0x4cca10` and T&L `0x4cd590` share `command/command_c/cm_ExCutsceneReady.c`. The server definition remains in `command.c` behind its target guard; the client body retains its additional slot and response updates. Original client TU placement remains inferred.

### Client cutscene record lookup (2026-11-01)

Gold `0x4e50a0` and T&L `0x4e6a30` use `game/cut_FindCutsceneById.c`. The name and exact TU are inferred from the active cutscene record table and attested `cut_` subsystem. Its data declarations do not establish storage ownership.

Gold `0x4e5120` and T&L `0x4e6ab0` use `game/cut_FindFreeCutscene.c`. The name and exact TU are inferred from the free-record sentinel and its caller.

Gold `0x4e5180` and T&L `0x4e6b10` use `game/cut_FreeCutscene.c`. The name and exact TU are inferred from the clearing operation and free-record sentinel.

### Gold queue-state lookup candidate (2026-11-01)

Gold `0x4c3ae0` has a 34-byte body ending at `0x4c3b02`, and the native
xref scan reports 335 direct calls. The existing shared
`GOLDTL.fcn_004c4450.c` compares RELOC 34/34 against it, but the Gold
`g_fb5760` operand at `0xf31160` is unresolved. Its comparison scaffold is
currently `int[32768]` (0x20000 bytes), while the function permits 32768
entries at a 10-byte stride, requiring a readable span of at least 0x4fff7
bytes. No source binding was restored: establish the native backing object,
complete extent, and link owner before relying on that scaffold. Receipts:
`.scratch/counter-contract/gold-queue-check{,-native,-xrefs}.json`.

Gold's `GOLD.fcn_00519ad0.c` independently indexes `g_f31161` at stride 10
for 0x8000 records. Its native address is one byte into the candidate base
`0xf31160`; its last referenced `ref` field ends at base + 0x50000. The current Gold
scaffold allocates `g_f31161` and `g_fb5760` separately as `int[32768]`, so it
neither represents the interior view nor the evidenced indexed span. PE section
metadata places the candidate range in the writable `.data` virtual tail;
that establishes mapped space, not an independent storage owner. Evidence:
`.scratch/counter-contract/gold-pe-info.json` and the two source definitions.

The Gold native remap loop confirms the view: `0x519b17` starts at
`0xf31166`, reads the type five bytes earlier, advances by 10, and stops at
`0xf81166`. Receipt: `.scratch/counter-contract/gold-queue-remap-native.json`.

Gold initialization at `0x4c350f` independently walks from `0xf31160` to
`0xf81160` in 10-byte steps, initializing each entry; `0xf81160` is also
accessed as a separate pointer-sized global. This establishes the table's
0x50000-byte native extent and its following boundary, but not its source
storage owner. Receipts: `.scratch/counter-contract/gold-queue-init-native.json`
and `gold-queue-data-xrefs-0.json` through `-3.json`.

The shared initializer `GOLDTL.fcn_004c3d50.c` is already bound to Gold
`0x4c3480` and declares `g_fb5760[0x8000]` as 10-byte entries. Thus the
undersized scaffold is a current Gold build limitation, independent of the
retired lookup binding. Correcting the scaffold and merging the interior view
requires a reviewed owner and raw-link layout check.

### Shared client cutscene-record candidate (2026-11-01)

The two 0x114-byte private record definitions in `GOLDTL.fcn_004e68d0.c` and
`GOLDTL.fcn_004e69e0.c` are identical. A scratch shared `CUTSCENE_RECORD`
checks `sizeof` and offsets 0x08, 0x14, 0x26, 0x30 and 0x34 with the pinned
compiler for both clients; the type/key lookup remains RELOC 76/76 with all
three recorded operands validated in both. The first lookup also remains
RELOC 64/64 in both in scratch. The shared header is not applied pending the
contract review and post-change target checks. Receipts:
`.scratch/counter-contract/cut-record-layout-assert-{gold,tl}.json` and
`cut-record-004e68d0-{gold,tl}.json`.

Gold `0x519ad0` calls the canonical `cut_FindCutsceneById` at native
`0x4e50a0`. A scratch caller with the pointer return declared correctly and
converted at its integer storage site compares RELOC 169/169, and the renamed
lookup operand validates. Other operands, including the queue-table view, remain
unresolved. No caller or scaffold was changed pending the guarded binding and
contract review. Receipt:
`.scratch/counter-contract/gold-cut-lookup-caller-candidate.json`.

The two-argument scene-comparison call in T&L
`GOLDTL.fcn_005ab3e0.c` is not supported by a direct call to `0x451840` in
the decoded 1063-byte native function extent. That source currently has a
SIZE_MISMATCH, so supplying a guessed third argument would not reconcile it.
Receipt: `.scratch/counter-contract/scene-epsilon-caller-5ab3e0-native.json`.

Gold `0x52ae70` and T&L `0x5305a0` use `game/sv_ClearObjectSelection.c`; its spelling and exact TU are inferred from its use by `sv_HandleObjects`.

Gold `0x453e70` and T&L `0x451840` use `Units/d3/CompareVector3WithinTolerance.c`. Name and exact TU are inferred from its three-component tolerance test; caller contract mismatches remain unresolved.

### Gold D3 camera-position candidate (2026-11-01)

Gold `0x43b790` has 91 native direct call references. The shared T&L source
`GOLDTL.fcn_00438b40.c` compares RELOC 83/83 in both clients. Gold validates
the camera and list globals, but four callable operands are unresolved; their
native targets are `0x43b6e0`, `0x43b6b0`, `0x45cdf0` (callback), and
`0x438e60`. Existing Gold comparison stubs provide those names but do not
establish runtime implementations. The Gold binding remains retired pending
provider and caller-contract review. Receipts:
`.scratch/counter-contract/{gold-camera-position-native,gold-camera-position-xrefs,camera-position-gold,camera-position-tl}.json`.

The Gold camera-position candidate calls `0x43b6b0` on its non-current-camera
branch. Its T&L counterpart `fcn_00438ac0` can share a conditional source:
Gold accesses `0x5fb5b0` and callback `0x43b670`, while T&L accesses
`0x67a370` and callback `0x438a80`. Scratch comparisons are RELOC 41/41 in
both targets; the Gold traversal callee at `0x438d40` remains unresolved.
Receipts: `.scratch/counter-contract/{gold-camera-helper-native,camera-helper-gold,camera-helper-tl}.json`.

The traversal at Gold `0x438d40` / T&L `0x4379a0` uses node offsets
`0x1fc/0x1f0/0x210` in Gold and `0x200/0x1f4/0x214` in T&L. A conditional
scratch body compares RELOC 288/288 in both. Gold's five unresolved data
operands resolve to native addresses `0xfc52f0`, `0xfc28f4`, `0xfb98f4`,
`0xfb9598`, and `0xfc2700`; the `0xfc2700` and `0xfc28f4` `d3_object.h` views have a
sentinel relationship whose full owner is unproved. Both targets still have
unresolved data operands, and Gold's nonrecursive callee is unresolved. No
traversal binding or storage was added. Receipts:
`.scratch/counter-contract/{gold-camera-traverse-native,camera-traverse-conditional-gold,camera-traverse-conditional-tl}.json`.

Gold `0x43b6e0` and T&L `0x438af0` share the D3 camera-reset operation,
with Gold-specific cleanup after the common traversal. A target-conditional
scratch body compares RELOC 171/171 for Gold and RELOC 74/74 for T&L. Gold's
traversal and cleanup callees remain unresolved; the cleanup name currently has
no Gold provider. The source and binding remain unchanged pending that provider.
Receipts: `.scratch/counter-contract/{gold-camera-reset-native,camera-reset-conditional-gold,camera-reset-conditional-tl}.json`.

The Gold cleanup callee `0x45d680` has a 358-byte native body ending at
`0x45d7e6`. The existing T&L `fcn_00459710` source compiles to 212 bytes for
Gold and does not match that extent. The Gold reset call passes zero as the
second argument, but that does not establish the callee's other paths; no
narrow substitute or shared binding was introduced. Receipts:
`.scratch/counter-contract/{camera-cleanup-gold,gold-camera-cleanup-native}.json`.

The client `cut_FindCutsceneById` definition returns a `char *`, while several
callers still declare an integer return. Two callers write that result into
integer reference fields: `fcn_0051ea70` and `fcn_00525670`. Scratch versions
using the pointer prototype and an explicit `(int)` conversion retain the
baseline comparison results: 169/169 RELOC for the former and the same existing
948-versus-893-byte SIZE_MISMATCH with identical reported mismatches for the
latter. These checks do not establish complete object-byte equality for the
latter. The canonical signature reconciliation is still pending a stable input
snapshot; no declaration was changed by this experiment. Evidence:
`.scratch/counter-contract/cutscene-caller-0051ea70-{baseline,candidate}.json`
and `.scratch/counter-contract/cutscene-caller-00525670-{baseline,candidate}.json`.

Gold startup at `0x00531c2c` directly calls `0x0042ea90` with argument `0x80`.
The current Gold inventory again contains a function starting at `0x0042ea90`,
although its source binding remains retired on the historical premise that the
address was no longer an inventory start. The old 293-byte binding pointed to
`GOLDTL.fcn_0042dfb0.c`; the current inventory extent is 304 bytes. That source
contains inline assembly, so the direct edge and historical masked match alone
do not establish that it satisfies the project's original-assembly policy.
The initializer remains unbound pending that review and extent reconciliation.
Evidence: `.scratch/counter-contract/gold-init-asm.json`, the inventory, and
the `GOLD.0x0042ea90` binding history.

The Gold initializer inventory extent was subsequently corrected to 293 bytes:
its last return is at `0x0042ebb4`, followed by 11 NOPs before the next entry.
This establishes the native boundary independently of source provenance; the
inline-assembly binding remains retired. Receipt:
`.scratch/counter-contract/gold-init-extent-apply.json`.

### VFS finish-files consolidation candidate (2026-11-02)

The client `fcn_0042ee50` duplicates `vfs_FinishFiles` in the canonical
`Units/vfs/vfs.c`: a scratch compilation of the canonical function compares
RELOC 436/436 against T&L. Gold's directory-mount function calls the matching
native entry `0x0042f620`; its historical source binding was retired. Native
T&L operands use pool `0x006b7fe0` and case flag `0x006b7fe8`, while the
canonical file's `g_vfs_item_pool` and `g_vfs_case_sensitive` are distinct
server-owned names and currently separate client scaffolds. The comparator
and recursive-call operands also need binding review. Consequently the byte
match alone is insufficient to replace the client implementation. Receipts:
`.scratch/counter-contract/vfs-finish-scratch-tl.json`,
`.scratch/counter-contract/vfs-finish-native-tl.json`, and
`.scratch/counter-contract/gold-vfs-mount-asm.json`.

The same canonical `vfs_FinishFiles` scratch body also compares RELOC 436/436
against Gold `0x0042f620`. Native Gold operands use the corresponding pool at
`0x00633400` and case flag at `0x00633408`; its qsort comparator targets are
`0x0042f600` and `0x0042f5c0`, while T&L uses `0x0042ee30` and `0x0042edf0`.
The comparison still leaves those operands unresolved. Receipts:
`.scratch/counter-contract/vfs-finish-scratch-gold.json` and
`.scratch/counter-contract/vfs-finish-native-gold.json`.

The canonical VFS comparators were independently compiled for both clients:
`vfs_CompareFiles` is EXACT 63/63 for Gold and T&L, and
`vfs_CompareFilesNoCase` is RELOC 25/25 for each. The latter's native tail
calls reach `strcmpi` library identities at Gold `0x005eab80` and T&L
`0x0065f220`; the T&L raw map identifies `_stricmp` and `__strcmpi` as aliases
in `LIBCMT:stricmp.obj`. The scratch comparison does not itself validate the
relocation. Receipts: `.scratch/counter-contract/vfs-comparator-{gold,tl}-{case,nocase}.json`,
`.scratch/counter-contract/gold-vfs-comparators-asm.json`, and the T&L build
map.

A scratch `vfs_FinishFiles` variant selecting the existing client symbols
`g_6b7fe0` and `g_6b7fe8` under `#ifndef REBREW_SERVER` also compares RELOC
436/436 for each client. The case-flag operand is validated in both, and Gold's
`vfs_CompareFiles` operand is now validated. The pool operand and other calls
remain unresolved; the existing pool scaffolds still need an extent/ownership
repair before using them as proof of a correct link. No production VFS source
was changed by this experiment. Receipts:
`.scratch/counter-contract/vfs-finish-client-globals-{gold,tl}.json`.

The post-correction T&L raw map exposes a real duplicate-storage problem:
`g_6b7fe0` and `g_vfs_item_pool` link at different addresses (`0x0087b3c0`
and `0x00b46741`), as do `g_6b7fe4` and `g_stream_pool` and the two case
flags. Both naming families are used by VFS source, but the native code uses
one pool head and one flag for each role. The earlier four-byte scaffold
repairs prevent undersized address-based heads; they do not reconcile these
separate linked symbols. Evidence:
`.scratch/counter-contract/tl-vfs-pool-alias-map.txt`,
`.scratch/counter-contract/tl-vfs-init-pool-asm.json`, and
`.scratch/counter-contract/tl-vfs-exit-asm.json`.

The locked all-target VFS organization review completed with two foreign
`fcn_0042ee50` findings (server and Gold) and 109 unknown contexts, including
incomplete system-header closures, parser failures in zlib headers, and
unbound functions in the existing multi-function TU. These findings describe
adding the donor definition to the canonical TU; the intended consolidation
instead replaces the donor with the existing `vfs_FinishFiles` definition.
They still require review along with target-specific globals and raw-link
checks. Gold's configured build artifact is not a fresh successful Gold raw
link: the latest Gold link failed. Receipt:
`.scratch/counter-contract/vfs-finish-organize-locked.json`.

The same T&L raw map also shows separate `g_6b7fdc`/`g_vfs_root` and
`g_6b7fec`/`g_stream_count` storage. `GOLDTL.vfs_OpenStream.c` increments the
canonical stream count, whereas `GOLDTL.vfs4.c` decrements the address-based
client count. A target-conditional alias experiment covering all five client
VFS globals is in scratch and under comparison; no source or storage owner was
changed by that experiment.

The VFS directory-mount caller was compared with both the old
`fcn_0042ee50` spelling and canonical `vfs_FinishFiles` spelling. Both versions
remain RELOC 1101/1101 for Gold and T&L. The old T&L call operand validates;
the canonical operand cannot validate until the shared finalizer is bound to
the corresponding target identities. Gold's native call to `0x0042f620` was
independently checked. Receipts:
`.scratch/counter-contract/vfs-mount-{prior,canonical}-{gold,tl}.json`.

The T&L finalizer and both comparator identities are now rebound to the
canonical VFS definitions, and their three T&L-only donor sources have been
removed. This supersedes the earlier pending-merge notes. The mount caller uses
the canonical finalizer. Fresh T&L function checks and a complete post-merge
raw-link comparison remain required; no object comparison by itself establishes
linked placement. Receipt:
`.scratch/counter-contract/vfs-tl-merge-locked-review.json`.

### VFS archive-scanner candidate (2026-11-02)

The canonical `vfs_ScanArchive` body compares RELOC 294/294 against T&L
`0x0042fb20` and Gold `0x00430130`. The mount caller with the canonical name
retains RELOC 1101/1101 in both, but its scanner operand remains unresolved
until a binding is recorded. Comparing relocation offsets with the existing
T&L donor identifies four native calls as its existing `fcn_0042e5a0`,
`fcn_0042e520`, `fcn_0042e540`, and `fcn_0042ed00` dependencies; all four
old donor operands validate. The corresponding canonical VFS bodies compare
RELOC 157/157, RELOC 19/19, EXACT 39/39, and RELOC 225/225 respectively
against T&L, though several of their own callees remain unresolved. The
remaining scanner operands, including minizip and CRT calls, also remain
unresolved. This is candidate evidence, not a completed merge. Receipts:
`.scratch/counter-contract/vfs-scanarchive-{tl,gold,donor-tl}.json`,
`.scratch/counter-contract/vfs-mount-scanarchive-{tl,gold}.json`, and
`.scratch/counter-contract/vfs-scan-dep-*-tl.json`.

The archive scanner's four corresponding canonical internal VFS bodies also
match the Gold functions in scratch: RELOC 157/157, RELOC 19/19, EXACT 39/39,
and RELOC 225/225. Gold's normalization and subdirectory inventory extents
were corrected to exclude native NOP padding. Some dependency calls remain
unresolved, so those comparisons do not establish linked provider identity.
Receipts: `.scratch/counter-contract/vfs-scan-dep-*-gold.json` and
`.scratch/counter-contract/gold-vfs-scan-deps-extent-apply.json`.

The archive-scanner donor also compares RELOC 294/294 against Gold, and all
four of its internal VFS call operands validate there as well. On T&L, the
five native minizip targets correspond to existing `LIBRARY` identities bound
to `references/minizip/unzip.c`; the scanner comparison itself still reports
those operands unresolved. This strengthens the correspondence but does not
validate the literal, CRT operands, or Gold minizip providers. Receipts:
`.scratch/counter-contract/vfs-scanarchive-donor-gold.json`,
`.scratch/counter-contract/{tl,gold}-vfs-scanarchive-asm.json`, and function
metadata for the native minizip targets.

A scratch build of the pinned `references/minizip/unzip.c` source compares
against the Gold scanner's four previously retired minizip entries at RELOC
398/398 (`unzOpen`), RELOC 51/51 (`unzGetCurrentFileInfo`), EXACT 64/64
(`unzGetFilePos`), and RELOC 115/115 (`unzGoToNextFile`). The Gold build
compiles this vendored source. The three relocation-masked bodies have
unresolved operands and are not yet established as Gold providers by these
comparisons alone. Receipts:
`.scratch/counter-contract/gold-minizip-{open,info,pos,next}-scratch.json`.

The T&L archive-scanner identity is now rebound to the existing canonical
`vfs_ScanArchive`, and the T&L-only donor source has been removed. This
supersedes the earlier pending-merge note. The Gold and T&L mount caller already
uses the canonical name. Fresh T&L function verdicts and post-merge raw PE
comparison remain required. Receipt:
`.scratch/counter-contract/vfs-scanner-tl-rebind.json`.

### Gold texture-wrapper candidate (2026-11-02)

Gold's sprite constructor calls `0x00448200`. A scratch conditional version
of the existing T&L `fcn_0047ce00` adds the two Gold device/flag guards and a
second argument to Gold's resource-release call; it compares RELOC 102/102
for Gold and retains RELOC 78/78 for T&L. The T&L operands validate, but both
Gold callee identities remain unresolved, and their Gold implementations are
not established by the masked match. The Gold-only global accesses also lack
complete ownership evidence. The candidate has not been applied or bound.
Receipts: `.scratch/counter-contract/gold-sprite-create-asm.json`,
`.scratch/counter-contract/gold-texture-load-asm.json`, and
`.scratch/counter-contract/texture-wrapper-v2-{gold,tl}.json`.

### VFS case-normalization contract (2026-11-02)

Gold `0x42ecf0` and T&L `0x42e520` have a case-normalization body
matching the existing `vfs_NormalizeCase` after relocation masking. Their
client callers currently declare the address-named function with differing
`void`, `int`, and pointer contracts, including an integer-cast argument in
`GOLDTL.fcn_0042f4d0.c`. Review those call sites against the canonical
`char *` argument and return before rebinding or removing the donor. The
cross-target contract audit and reconciliation preview both rejected changing
inputs during this review; no contract or source binding was changed. Gold
also needs a successful raw link for the required whole-PE comparison.

### Client image-name lookup candidate (2026-11-02)

Gold `0x0045db30` and T&L `0x0045a2e0` use the same image-name lookup
logic, with name arrays at image offsets `0x1a64` and `0x7e24`, respectively.
A target-conditional scratch body compares RELOC 177/177 in each client.
Gold's three data operands validate; T&L's data operands and both CRT call
operands remain unresolved by the comparator. All-target organization review
reports no order cycle or source-owned storage, but flags each original name
as foreign in the other target for a naive merge and cannot resolve the SDK
`string.h` include context. Gold also lacks a complete raw link. Keep the
original sources until the shared identity, include contexts, data operands,
and both raw-link comparisons can be reviewed. Evidence:
`.scratch/counter-contract/shared-image-helper-{gold,tl,organize}.json`.

The T&L table, cache, and cache-pointer data identities are now recorded; the
conditional helper still compares RELOC 177/177 and all three data operands
validate. The CRT call operands remain unresolved by the comparator. The T&L
native table contains initialized bytes, unlike the current zero-filled
scaffold; its original source owner and linked placement remain unproven.
Receipt: `.scratch/counter-contract/shared-image-helper-tl-data-bound.json`.

The native 135-byte name tables have identical 15-by-9 contents in Gold and
T&L, including the repeated `WEG` and `_ill*` entries and the final empty
entry. Gold stores its table in `.data`; T&L stores it in `.rdata`. The
current zero-filled definitions are in generated target scaffolds, while the
only source references are the two image helpers. No bounded T&L source-path
reference identifies the helper's original TU. Replacing the scaffolds with
a shared storage definition requires retaining one target-specific allocation,
establishing its source placement and checking linked data in both targets;
editing the generated stubs would not be durable. Evidence:
`.scratch/counter-contract/image-helper-tl-{names-xrefs,units,data}.json` and
`.scratch/counter-contract/image-helper-tl-data-lint.json`.

The helper has two direct native callers in each client, both within one
neighboring function: T&L `0x0045a3a0`, Gold `0x0045dbf0`. Neither caller's
native dossier contains a diagnostic string or source path. The reconstructed
T&L caller declares and calls the helper as `(char *, int, int)`, while the
helper's native entry dereferences its third argument as an image pointer and
its source contract is `(int, int, int *)`. The caller is currently a
SIZE_MISMATCH reconstruction; its arguments and loop behavior need native
review before changing the call order or consolidating the helper. Evidence:
`.scratch/counter-contract/image-helper-{tl,gold}-callers.json`,
`image-helper-{tl,gold}-caller-dossier.json`, and
`image-helper-tl-caller-asm.json`.

At T&L native `0x0045a521`, the caller pushes the image pointer first (the
callee's third argument), then the row and column loop registers. At
`0x0045a666`, it similarly pushes the image pointer followed by the two loop
coordinates. A scratch correction to `(int x, int y, int *img)` and the two
corresponding call orders remains SIZE_MISMATCH (1,304 compiled versus 1,388
native bytes, 25 reported matching bytes), the same measurement as the
baseline. This establishes the pointer argument order but does not validate
the caller's incomplete loops or the complete generated body. Receipts:
`.scratch/counter-contract/image-caller-{baseline,contract-candidate}.json`
and `image-helper-tl-caller-asm.json`.

### Client task-queue removal candidate (2026-11-02)

Gold `0x004047a0` and T&L `0x004050c0` have identical 110-byte native bodies.
The shared Gold/T&L caller at Gold `0x00406210` / T&L `0x00406db0` calls
them respectively. The T&L translation unit now uses a C-only queue-removal
body and records NEAR_MATCHING 98/110 in both scratch comparisons; its
neighboring T&L function remains RELOC 87/87. The Gold binding was previously
retired because the address had ceased to be an inventory start, but it is
again present with a 110-byte extent. Gold source binding and raw-link
verification remain open. The earlier inline assembly was justified by a
compiler-order mismatch, not positive evidence of original assembly.
Receipts: `.scratch/counter-contract/{gold,tl}-queue-remove-{native,c-only}.json`
and `tl-queue-c-only-production.json`.

The shared queue-removal implementation and its callers now use inferred
`ch_RemoveQueueEntry`; see `docs/naming_conventions.md` for the naming evidence.

Both clients' `g_fb5760` queue table extents are now recorded as 0x50000 bytes;
Gold `g_f31161` is an interior view at +1. A Gold scratch remap using that
backing remains RELOC 169/169 with its backing operands validated. The
comparison scaffolds still have insufficient capacity and Gold still has a
separate view allocation; correcting those generated files requires safe
selected-symbol regeneration and a raw-link placement review. Receipts:
`.scratch/counter-contract/{gold,tl}-queue-backing-apply.json` and
`gold-queue-remap-alias-data-bound.json`.

### Shared client game-matrix declarations (2026-11-02)

The `g_869480` and `g_90e0a0` 0x300-by-0x300 byte views are declared once
in `game/game_matrices.h` and included by their six client source users. The
header is an inferred declaration home, allocates no storage, and does not
establish the original TU or native owner. Existing explicit signed-byte
casts remain at arithmetic uses. All nine pre/post target objects preserve
code, data and relocation targets; debug records were excluded. The T&L
comparison scaffolds still allocate only one byte for each matrix. Receipt:
`.scratch/counter-contract/game-matrices-objects/compare.json`.

### Character action queue consolidation (2026-11-02)

`game/character.c` now owns the shared client queue removal, insertion, and
cancellation bodies. Gold `0x004048b0` and `0x00405610` were restored from
retired claims after the current inventory and target comparisons confirmed
their native extents; the Gold scaffold no longer supplies the cancellation
stub. The removal body remains NEAR_MATCHING 98/110 in both targets; insertion
and cancellation are RELOC at full extents. The T&L native inventory contains
other functions between these definitions, so their linked placement must be
checked and the remaining original-TU boundaries are not yet established.
Receipts: `.scratch/counter-contract/queue-move-verify.json` and
`queue-character-organize-current.json`.

Gold `0x00404810` and T&L `0x00405130` now share the inferred
`ch_ClearActionQueue` definition in `game/character.c`, after queue-entry
removal and before insertion. Both native inventories support that ordering,
and both object comparisons remain RELOC 78/78. The adjacent queue checker
remains separate pending evidence for its breakpoint implementation; complete
linked placement is still being checked. Receipt:
`.scratch/counter-contract/action-clear-organize.json`.

The subsequent T&L raw link places `ch_ClearActionQueue` at `0x00405130`, its
native address. Insertion is at `0x00405180` versus native `0x004051d0`, while
the separate checker remains later in the link. The raw clear body still differs
in two bytes. Gold remains blocked at link by 255 unresolved externals; these
placement observations do not establish a complete image match. Receipt:
`.scratch/action-clear/check-tl.json`.

The shared queue allocator `ch_GetFreeQueueEntry` now precedes removal in
`game/character.c`, matching the Gold and T&L native order. The server raw image
is unchanged. T&L's code and initialized sections remain byte-identical to the
previous raw link, and the allocator, removal and clear retain their native
addresses; the complete file differs in 148 bytes outside those sections.
Receipts: `.scratch/queue-free/check-{server,tl}.json` and `after-tl.map`.

The inferred 0x194-byte client action-record layout is shared through
`game/ch_action.h` instead of thirteen local full views. It retains two fields
at offsets 0x34 and 0x38 that had been opaque padding in some users; this does
not change their offsets or create storage. A separate partial `Task` view is
still unresolved. Full T&L and server raw links are unchanged; Gold still fails
at link with 255 unresolved externals. Receipts:
`.scratch/queue-type/{objects/compare.json,check-tl.json,check-server.json}`.

The former partial action view in the per-character executor now uses
`CH_ACTION` too. The inferred `ch_ExecuteAction` body remains in its existing
source file pending original-TU placement review; both client functions remain
EXACT. T&L and server full raw rebuilds are byte-identical to their baselines.
Receipt: `.scratch/queue-run/verify-definition.json` and
`.scratch/queue-run/check-{tl,server}.json`.

The character ground-placement routine and `ch_ExecuteAction` now follow action
insertion in `game/character.c`, in the common native order. T&L's raw link
places them at 0x00405350 and 0x00405460, respectively, versus native
0x004053a0 and 0x004054b0; previously they were at 0x00405400 and 0x00405510.
The full server image is unchanged. The T&L image differs in 618 `.text` bytes,
so linked placement remains incomplete. Gold has 254 unresolved externals,
down from 255, and cannot yet supply a raw image. Existing callers disagree on
the ground-placement return type and pointer view; the contract review remains
open. Receipts: `.scratch/queue-neighbors/{check-tl.json,check-server.json,contracts.json,after-gold-build.log}`.

The ground-placement contract now resides in `game/ch_ground.h` under the
inferred name `ch_PlaceOnGround`. Client declarations use its evidenced integer
return; the server declaration retains its previous void return under its target
guard. All 69 affected compiled contexts preserve code, data and relocations,
and complete T&L and server raw links are unchanged. Gold remains at 254
unresolved externals. The current source-contract audit does not preprocess
conditional declarations and reports both guarded returns in client contexts;
the target-aware audit feature gap is recorded upstream. Receipts:
`.scratch/ground-contract/{objects/compare.json,contracts.json,check-tl.json,check-server.json}`.

The inferred `ch_CancelActionQueueWithMotion` remains in the separate
`game/GOLDTL.ch_CancelActionQueueWithMotion.c` unit. A trial merge into
`character.c` shifted it over 0xc00 bytes early and changed 3,220 T&L text
bytes, so the merge was reversed. The named standalone rebuild restores its
prior 0x004061a0 placement and yields byte-identical complete T&L and server
raw images. Receipt: `.scratch/queue-extra/reversal-check-tl.json`.

The T&L sitting helper now lives in `game/GOLDTL.ch_ClearSitting.c` with an
inferred `ch_` name and a declaration in `ch_action.h`. It retains the seat
pointer across native 0x00402aa0, whose body is a single return instruction;
the former C incorrectly used an undefined function return. The corrected
object is 98 bytes versus native 87 and the former 89-byte object. The raw T&L
comparison consequently differs in 2,275,744 `.text`, 784 `.rdata` and 336
`.data` bytes, consistent with widespread subsequent placement changes; the
helper itself remains at its previous linked 0x00406580. The complete server
image is unchanged. Receipts: `.scratch/clear-sit/{native.json,empty-native.json,check-tl.json,check-server.json}`.

A subsequent C adjustment reloads the seat and entity views after the verified
empty helper call. The 93-byte corrected body remains larger than native 87 but
fits its old aligned link slot. T&L's raw image now differs from the
pre-correction baseline in 69 `.text` bytes, with compared data and resources
unchanged; the 16-case behavior harness passes. Receipt:
`.scratch/clear-sit-match/check-original.json`.
