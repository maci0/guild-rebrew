# Source layout

Use one shared C tree under `src/Develop/`, following attested `D:\Develop`
paths. A byte match establishes code agreement; original TU ownership still
needs path, diagnostic, counterpart or dependency evidence. Label inferred
placement. Root address-named files remain a consolidation backlog.

| Location | Evidence and current use |
| --- | --- |
| `src/Develop/DieGildeAddOn/game` | Attested game units, including `spiel.c` and `sim.c`; client counterparts live alongside them until safe merging is established. |
| `src/Develop/DieGildeAddOn/command` | Attested command and lobby units. Client addresses previously given unrelated server command names require correction before grouping. |
| `src/Develop/DieGildeAddOn/auxillary` | Attested plant subsystem. |
| `src/Develop/DieGildeAddOn/loadsave` | Attested save/load unit. |
| `src/Develop/DieGildeAddOnServer` | Attested server unit and reconstructed shared declarations. |
| `src/Develop/Units` | Attested reusable units: Error, allocation, VFS, network and renderer modules. |
| `src` directly | Unassigned recovered functions and shared headers whose original module is still unknown. This is a reconstruction backlog, not the intended final layout. |

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
