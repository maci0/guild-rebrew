# Source layout

The intended result is one shared C tree following the original developers'
`Develop` layout. A source match does not establish its original compilation unit.
Keep that distinction when placing and merging files.

| Location | Evidence and current use |
| --- | --- |
| `src/Develop/DieGildeAddOn/game` | Attested game units, including `spiel.c` and `sim.c`; client counterparts live alongside them until safe merging is established. |
| `src/Develop/DieGildeAddOn/command` | Attested command and lobby units. Client addresses previously given unrelated server command names require correction before grouping. |
| `src/Develop/DieGildeAddOn/auxillary` | Attested plant subsystem. |
| `src/Develop/DieGildeAddOn/loadsave` | Attested save/load unit. |
| `src/Develop/DieGildeAddOnServer` | Attested server unit and reconstructed shared declarations. |
| `src/Develop/Units` | Attested reusable units: Error, allocation, VFS, network and renderer modules. |
| `src` directly | Unassigned recovered functions and shared headers whose original module is still unknown. This is a reconstruction backlog, not the intended final layout. |

The 2026-10-11 organization pass moves these existing sources without merging
their bodies or changing their compiler flags:

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

Keep target-specific bodies separate when they differ. Merge only with evidence of
shared compilation-unit ownership and verification of all affected target variants.
Headers declare globals; moving a declaration does not establish a storage owner.

Rebrew's `source rehome --from OLD --to NEW` updates every affected function and
data row across targets through the managed writers. Preview it after preparing the
destination, then apply it and remove the old file. Check includes, build lists and
callers, compare complete COFF bodies and typed relocation bindings, and refresh the
affected verification and coverage records.

The automatic TL compilation-unit map currently groups 6,335 functions into only
three clusters. Those broad clusters are insufficient evidence for bulk placement.
Unassigned functions need native path/log evidence, established counterpart units,
or stronger call/global ownership evidence. Address proximity alone is insufficient.

Organization receipts and the remaining root-file inventory are in
`.scratch/goal20/source-organization/`; historical match receipts retain the paths
that were valid when they were recorded.

The next pass scans the native binaries for complete source-path strings and direct
instruction operands referring to them. It finds 37 functions across the clients.
This evidence is stronger than address clustering; the scan clips known matched
bodies to their verified extents. Evidence is in
`.scratch/goal20/native-unit-map/direct-path-evidence.json`.

Thirteen MSX channel functions were grouped under `Develop/Units/Msx` using their
common critical section, channel state and calls. TL420840 and GOLD4244b0 directly
reference the original `Units/Msx/msx.c` path. Eleven functions now share the
reconstructed `msx.c`: fade state (TL420700/GOLD424370), channel stop
(TL420120/GOLD423df0), ambient stop (TL420840/GOLD4244b0), named-track lookup
(TL4205e0/GOLD424250), free-slot selection (TL420690/GOLD424300), active-track selection
(TL420650/GOLD4242c0), ordinary acquisition (TL41fd70/GOLD423a90), and ambient
acquisition (TL420780/GOLD4243f0), start/queue state (TL41fe10/GOLD423b30),
volume updates (TL41fc10/GOLD423930), and path assignment (TL420760/GOLD4243d0). Helper
placement follows subsystem evidence; exact original units and function spellings
remain unproven. `FindTrackByName` and `FindFreeTrack` are inferred names. The fade helper's former `game/GOLDTL.sim.c`
placement was incorrect.

The module header reuses the canonical 296-byte track view and SDK critical-section
declarations. Two game callers now use track pointers and the fade helper takes a
scalar mode. Two older module callers now pass strings to the lookup and use SDK
locking declarations in place of absolute addresses. The table helpers reuse the
same record view; the duplicate `g_6b71b0.h` is retired, and the existing active-track
selector is placed in the module directory with its code preserved. The volume
helper and all its callers now use the canonical track-pointer signature.

All 994 bytes in the shared unit and 130 bytes in the corrected callers match their
complete native bodies, with 72 actual relocation operands and isolated wrong-target
controls. All 23 previous function bodies retain their instruction bytes: 21 COFF
bodies directly, and the two corrected callers after applying their relocations.
404 C89 sanitizer cases check the table primitives and caller lock ordering.
GOLD's lookup/free-slot spans included 6/10 trailing NOPs; native returns and branch
targets establish the complete 106/102-byte bodies. Their shared code now verifies
in both clients, with alignment kept separate from function bytes.
The assertion attests `hTrack->bAmbient`; that spelling now replaces the old
`b106` in the canonical296-byte view. Its previously opaque tail is expanded through
the self-pointer at0x124, including the unsigned volume value at0x118. The two local
full-track duplicates are removed. All558 source files in the conservative include
and use closure were baselined before the header change:884 successful builds.
The final878 builds preserve928 complete baseline function bodies. The valid indexed
selector retains its49 native bytes; a chained assignment corrects two formerly
crossed native pointer-slot bindings in a game caller. The five observed game pointer
slots have canonical declaration-only views, with no invented allocation owner.
The eight-function checkpoint reproduces1766 complete native bytes across both
clients with112 strict relocation operands and isolated wrong-target controls.
8704 C89 32-bit ASan/UBSan cases check full layout, self-pointers, all flag byte values
and selector priority. GOLD acquisition extents exclude9/6 trailing NOPs, proven by
native returns and every direct branch; their complete151/186-byte bodies match.
The updater is now placed under MSX and retains its793-byte compiled body; its
previous791-byte mismatch remains unresolved. The start helper and volume API now share the unit. Track names, backing allocation and original storage
owners remain unresolved. No new global storage or data byte verdict is created.
Receipt: `.scratch/goal20/msx-track-type/scope-final.json`.

The following start/volume pass expands the unit to11 functions/22 client bindings.
GOLD423b30 shares the699-byte TL start helper through verified cross-import; its
old704-byte inventory span includes5 NOPs, independently checked at the return
and every direct branch. The98-byte volume helper uses the canonical track fields
and pointer API, preserving lock/callback ordering. No CRT implementation is copied;
the formatter is attributed against the stock archive.

Native checking also corrects an older false twin: TL420760 music-path assignment
belongs with GOLD4243d0, which writes14611a0. GOLD478860 writes the separatef8aae0
game buffer and keeps its unchanged22-byte native body under a separate declaration.
The canonical MSX path view is TL14cc360/GOLD14611a0. Its complete allocation extent
and owner remain unproven; the new declaration allocates no storage. Both callers
use inferred SetTrackPath. The former raw-address GOLD path copier is retired.

All3404 shared native bytes and206 actual relocation operands pass strict checks and
isolated wrong-target controls. Twenty baseline builds and15 final builds preserve
33 complete COFF bodies; the formerly mismatched path copier now matches its22 native
bytes.1083 volume/lock and1785 path-copy cases pass under32-bit C89 ASan/UBSan;
the path test buffer is a fixture and does not establish the binary allocation size.
33 affected matches freshly verify with no losses. The TL updater remains793 bytes
against791: six instruction widths differ because the loop anchors at track+110
instead of+118. Tested C/type/context forms and the quick flag sweep did not solve
it; the exact blocker and probes are recorded for the next matching attempt.
Upstream's existing generous DIR32 masking hid the false buffer pairing; a known-
binding hardening proposal is recorded in Rebrew's IDEAS-GUILD.md, without changing
that documented agreement-only behavior. Receipt:
`.scratch/goal20/msx-start-volume/scope-final.json`.

GOLD438780 now lives in the attested `Develop/Units/d3/d3_d3d.c`. Its diagnostic
attests `d3d_Device->lpVtbl->EndScene(d3d_Device)`. The prior source incorrectly
indexed vtable entry40, dereferenced the function pointer again, and logged a zero
result. The native call uses byte offset0x28 (entry10) and logs nonzero results.
The repaired complete44-byte function and all5 actual operands match; six C89
sanitizer cases check the method, this pointer, result and diagnostic arguments.
The device name is attested; `d3d_LastResult` and the interface type remain inferred.
The header declares native views; it allocates no storage or complete backing object.

Placement receipts are in `.scratch/goal20/native-unit-batch/`; the verified shared
MSX unit is recorded in `.scratch/goal20/msx-shared-unit/scope-final.json`, with the
table extension in `.scratch/goal20/msx-track-table/scope-final.json`. The remaining
root backlog is 3,854 C files. Further placement needs native evidence; the remaining
MSX functions still need safe type and compilation-unit consolidation.

This merge exposed an upstream Rebrew bug: legacy marker files with managed rows
were deleted without moving those rows. Upstream `42e0a8c0` fixes the shared writer
path, guards against dropping bound definitions, and rolls back failed updates.
The fixed CLI moved all four existing rows; two independently verified GOLD twins
complete the six bindings to this one C file.


## Character subsystem placement (2026-10-11)

Seventeen existing character sources and the canonical `ch_motion.h` now live in
`Develop/DieGildeAddOn/game`. Sixteen sources came from the unassigned root; the
shared `CreateAnimationEvent.c` came from the command-handler split directory.
Its animation-task allocation and callback are unrelated to the server health
command that supplied its former identity and placement.

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

This is inferred game-subsystem placement, not an attested original character
filename or proof that every fragment belonged to one translation unit. Twenty-seven
of the 33 affected native identities directly reference character diagnostics or
resource paths. The native callback/dependency evidence supplies the other helper
roles. The existing `ch_FinishAni` / preloader proofs remain valid historical
receipts. Address-based function names still need evidence-backed renaming.

Seven of these shared definitions now carry their attested diagnostic names:
`ch_AttachMotion`, `ch_TakingObject`, `ch_DroppingObject`,
`CreateCharacterAtDummy`, `PlayCharacterAniScript`, `PlayCharacterAniScriptInt`
and `SetCharacterCamera`. The public rename writer updates their fourteen
client identities and all declaration/caller/self-reference sites in thirteen
sources. Existing address-based filenames remain provisional; a diagnostic
function name does not establish its original compilation-unit filename.
Native witnesses and complete before/after COFF comparisons are in
`.scratch/goal21/continuation/`.

The scene-transfer variants differ in their scene-node render flag positions
(TL `+0x215`, bit 1; GOLD `+0x211`, bit 3). The take-object variants differ in
TL `+0x40c` / GOLD `+0x104` dummy-name pointer offsets. These differences now live
in partial build-specific views in shared `character.c`, with every actual native
operand and both complete byte sequences verified. Relocation masking alone did
not justify this consolidation; the strict full-body checks below establish it.

The public rehome writer moved all 33 function identities and nine existing data
rows with their files. Only four include spellings changed. Twenty-eight baseline
and 28 final builds preserve 34 complete COFF bodies, typed relocation bindings and
compiler literals, including the unbound GOLD preloader body. The two existing
unmatched sitting queries are preserved. No storage, identity or data verdict was
added. Native evidence, previews, full-body comparisons and remaining root inventory
are in `.scratch/goal20/character-placement/`; old receipts retain historical paths.


## Shared character scene and script helpers (2026-10-11)

`game/character.c` now defines the attested `ch_MoveCharacter2Universe`
(TL403bc0/GOLD4033c0) and `TakeObjectScript` (TL40d410/GOLD40c4f0) once each.
Four old client files are retired through public migration and managed identity
writers. `character.c` is a reconstructed unit name, not an original path attestation.
The canonical `ch_motion.h` supplies their recovered prototypes and six provisional
game declarations; two existing declaration sites now consume it.

The universe argument is a pointer view. The full native D3 byte layouts now
live in `Develop/Units/d3/d3_object.h`, bound by stable IDs in managed
`rebrew-types.toml`. `D3_OBJECT` spans 0x228 in both clients;
`D3_OBJECT_DRAW_DATA` spans TL0x1640/GOLD0x970, with four `D3_DRAW_PART`
slots at +0xf4 and TL0x4a4/GOLD0x198 stride. The resource context at +0x1cc
is `kontext`; the actual tree parent `eltern` is TL+0x1fc/GOLD+0x1f8.
The old partial character views were replaced. Native allocation/init/tree
instructions prove these extents and offsets; target MSVC6 assertions check
sizeof/offsetof. Type/file/field names remain inferred, and unknown semantic
fields are explicit byte regions. Compiler size does not itself prove a native
allocation. The old `lit` label was unproven: another recovered settings
view calls that same TL bit `mirror`. The neutral `darstellungsflag` describes the
observed flag without claiming either renderer role. Remaining helper identities
that lack one shared provider retain their native build names through local aliases.

All 1,181 complete native bytes match after resolving 52 actual typed operands;
52 isolated wrong-target controls fail as expected. Both complete native returns
and every direct branch are checked. Header/declaration changes preserve 10 complete
consumer bodies, and all 8 final builds reproduce 14 staged bodies and typed operands.
141,320 strict C89 32-bit ASan/UBSan cases cover flag masks, adjacent-bit preservation,
scene movement, optional nodes, callbacks, diagnostics, allocation failure, name
copying and input preservation under the original valid-input preconditions. The
fixtures model helper results; they do not establish those helpers' implementation
or allocation ownership. All 12 previously matched identities freshly verify; the
existing unmatched GOLD character query remains unchanged.

Twelve existing/native global declaration views now bind the canonical header,
four newly recorded for TL. They allocate no storage and earn no data verdict.
The vector retains its existing 16-byte declared view, also passed as `vec4` elsewhere;
scene translation reads its first 12 bytes. Backing allocation extents and source
owners remain unknown. No library source or archive changed.

The native scene caller is inside an unreversed sibling of TL407330/GOLD406790,
after the existing 96-byte selector, rather than inside the matched selector body.
The script helpers are registered by address in unreversed VM registration code.
No implemented C reference was left behind by the rename. TL402aa0 is a standalone
one-byte `RET` followed by 15 NOPs, omitted by discovery's documented 8-byte default
minimum. Its actual call destination is verified directly; GOLD402540 retains its
nonempty native helper. This inventory omission is not a new discovery defect.
Receipts and exact reference evidence: `.scratch/goal20/character-shared-pairs/`.

The recovered C-view sizes are measured with MSVC6, without inline `SIZE`
annotations. Function sizes and addresses remain in their managed TOML identities.
Upstream lint W007's obsolete file-level struct-size-comment requirement is retired;
partial views do not establish complete native object extents.


## D3 type identities and full byte extents (2026-10-11)

`d3.object`, `d3.object_draw_data`, and `d3.draw_part` each have a GOLDTL and
GOLD binding. Each binding records the owning header, C name, target size,
native allocation or array stride evidence, member offsets and input fingerprints.
Heap instances have allocation/use sites, not invented fixed addresses:
character +0x34 points to a D3 object, whose +0x1ec points to draw data;
TakeObjectScript reads the first draw slot's resource name prefix at
TL+0x40c/GOLD+0x104 in that allocation.

`rebrew types check --compile --json --target Europa1400Gold_TL.exe` checks the
TL binding; use the Gold target for its layout. Sources stay free of address
and SIZE markers. Stable IDs and extents are managed through `types bind`.
Native evidence and complete preserved character bodies:
`.scratch/goal20/type-identity-layouts/`.

## Shared client allocator helper checkpoint (2026-10-11)

`Develop/Units/m_alloc/GOLDTL.fcn_0041dd90.c` supplies the tracking check in
both clients. Gold's native body is 60 bytes; four following NOPs are alignment.
`Develop/Units/m_alloc/GOLDTL.fcn_0041e410.c` now supplies the 43-byte free-all
body in both clients, including the native null-head guard. The superseded
Gold-only source is retired. Module placement follows the common native allocator
span and neighbouring m_alloc diagnostics; the numeric declarations remain
compatibility names, not recovered original identifiers.

The four managed counter/pointer entries are existing extern declaration views
of four-byte native cells, not new definitions, heap extents or storage owners.
No allocation or data-verification claim is added. These helpers stay separate
until the actual 117-byte client tracked-free provider is reconciled with the
188-byte server provider in the shared allocator unit. All surviving complete
COFF bodies and caller operands are preserved, seven comparisons freshly pass,
and Gold gains two matches. Evidence: `.scratch/goal21/allocator-client-repair/`.
