# Current work

The [three-binary objective](../goal.md) is incomplete. This checkpoint records
Goal110 checks on **2026-10-18**, completed client builds on **2026-10-19**,
the later, interrupted GUI text-creator integration, and the resumed delegated
reconstruction waves on **2026-10-19**.
Both clients remain comparison scaffolds. Historical checkpoints are in
[goal history](goal-history.md).

Guild now pins released **Rebrew 5.4.0**. The installed release includes the
upstream fixes discussed below; references to installed 5.2.0 describe the
earlier measurement checkpoint. The import recipe now uses Rebrew's API and
preserves its complete response file. This tooling upgrade adds no native
verification or recovered-byte credit. See [tooling notes](tooling-upstream.md#import-table-api-extraction-2026-10-20).

## Delegated reconstruction waves, 2026-10-19

Work resumed on the goal. Waves of ten subagents, ten isolated per-function
STUB files each, ran against the default target `Europa1400Gold_TL.exe`.
Local receipts are under `.scratch/wave2/` and `.scratch/wave3/`.

Wave 2 attempted 100 targets and the lead reproduced every non-STUB verdict
with a fresh official `rebrew test` (`.scratch/wave2/verify-changed.json`):
**14 RELOC**, 2 NEAR_MATCHING, 10 SIZE_MISMATCH, 3 EXTRACT_ERROR, 71 still
STUB. Twelve of the RELOC bodies are game code; they are byte-identical after
relocation masking with their operands validated. This is object progress, not
linked EXACT: the raw link has not been rebuilt.

The wave-2 selector did not read the target's `external_ranges`, so 53 of 100
assigned files were statically linked D3DX8 bodies (`0x5e0000..0x64ffff`,
declared external in `rebrew-project.toml`). Those are not game source and
their `__thiscall`/C++ ABIs cannot be emitted by C89. The same batch measured
many inventory over-merges (one stored extent covering two to six adjacent
functions or alignment padding), which C cannot close; they need reviewed
`rebrew binary repair-extents` work.

Wave 3 ran on the validated-extent game queue with the library band excluded.
The lead reproduced the 29 promoted verdicts with a fresh official `rebrew
test` (`.scratch/wave3/verify-changed.json`): **23 RELOC** (all
byte-identical after relocation masking, operand bindings validated where
recorded) and **6 NEAR_MATCHING**. The other attempted rows keep faithful
partial bodies whose measured SIZE_MISMATCH is not promoted to STATUS by the
default policy; their reports record extent-repair specs and unresolved
operand/data-row gaps. Inline `__asm { int 3 }` for evidenced debug-break
traps is an accepted lead decision (`.scratch/wave2/DECISIONS.md`).

Wave 4 ran on the remaining validated game extents (larger bodies, 135-625
bytes). The lead reproduced its promoted verdicts
(`.scratch/wave4/verify-changed.json`): **1 RELOC** and **3 NEAR_MATCHING**;
the rest are faithful bodies recorded as forced SIZE_MISMATCH (61 rows), which
now persists through `--force-status`. Larger bodies mostly stop at
register/scheduling or x87-choreography walls, and several need operand rows
that do not exist yet (`.scratch/wave2/DATA-GAPS.md`).

A reviewed extent-repair batch then ran: 36 game rows passed the byte-level
spec verifier and were applied with `rebrew binary repair-extents` under its
input digest, then re-measured with the corrected stored SIZE. That converted
`0x0042f4d0` (356/356) and `0x004e8c00` (173/173) to RELOC and five more rows
to NEAR_MATCHING. Three further rows now measure exactly against the repaired
size but remain STUB-classified because their bytes still differ. The separate
merge case `0x45a3a0`+`0x45a7f9`, two code+table rows, and two missing-entry
additions are still open. Do not use `rebrew coverage catalog --fix-sizes`; it
grew 22 already-verified rows from the stale inventory and had to be undone
(details in `.scratch/wave2/DECISIONS.md`).

Wave 5 ran on 100 remaining validated extents (354-889 bytes) plus a second
repair batch of three verified rows (`0x4aa240`->748, `0x524fc0`->498,
`0x5252d0`->735). Five promoted rows were lead-verified as RELOC (425, 480,
489, 478, 559 bytes) and three more as NEAR_MATCHING; `0x524fc0` became
NEAR_MATCHING 454/498 after its repair. Six wave-5 agents did not deliver a
report; the written sources remain, all their promoted rows are verified, and
the rest are recorded partial SIZE_MISMATCH bodies. Larger bodies are now the
pool, so most new output is faithful partial C rather than RELOC.

Wave 6 ran on 43 shared-TU STUB rows (each in a distinct file) plus the 57
smallest remaining validated extents. Shared-row agents edit only their own
function and measure with `--va` so resident EXACT/RELOC rows are not
re-promoted. The lead reproduced its promoted verdicts
(`.scratch/wave6/verify-changed.json`): **3 RELOC** (`0x4d1ad0` 539/539,
`0x512b40` 478/478 after extent repair, `0x546720` 181/181) and **2
NEAR_MATCHING**. The rest are faithful partial bodies (28 forced
SIZE_MISMATCH) or untouched large rows. The wave also found a third invalid
metadata row (`0x5294c4`, a switch-case arm inside the enclosing function) and
confirmed the `rebrew_globals.h` gap: it is server-only, so GOLDTL bodies keep
local externs and operand validation stays blocked on missing data rows.

A systematic trailing-pad audit then ran: 514 game extents have padding after
their last real terminator; 73 single-function SIZE_MISMATCH/NEAR bodies were
repaired in the inventory with one digest-guarded batch. Feeding the corrected
SIZE back through `rebrew test --va --size --force-status` is converting some
of them to RELOC (first batch: `0x445760` 309/309; a mid-wave scan error left
six rows to retry). The remaining repair classes (code+table, merges, invalid
rows) are queued in `.scratch/wave2/EXTENT-QUEUE.md`.

Wave 7 currently runs on the next 100 validated game extents (637-1817 bytes),
with wave-8 groups precomputed for replacement agents so ten subagents stay
running. A closure pipeline is prepared at
`.scratch/closure/run_closure.py`: resume the paused client build, then data,
whole-image, lint and server-gate checks; it must not run while wave agents are
compiling.

Classification of the remaining TL STUB rows (`.scratch/wave2/classify.py`):
204 declared library band, 14 CRT/runtime tail, 604 game rows whose extent the
fresh discovery pass validates (296 left after waves 3-5), 409 game rows with
merged or padded extents, 43 rows in shared TUs. The reviewed extent-repair
queue (splits, merges, padding) is `.scratch/wave2/EXTENT-QUEUE.md`. Findings,
classify output and next-wave plan are in `.scratch/wave2/FINDINGS.md` and
`.scratch/wave2/PLAN-next.md`.

## Paused checkpoint, 2026-10-19

This checkpoint records the pause that preceded the resumed waves above. At that
pause all delegated tasks had finished and no
owned compiler or emulation process remained. The current creator source,
inventory and metadata changes are **uncommitted and unpushed**.

Scoped verification finished: **98 of 102 contexts pass**, with four existing
size mismatches and no compile failures. The subsequent full client rebuild
stopped at **59%**, exit **143** after the requested SIGTERM; its log contains
zero compiler-error lines through that point. Neither client was relinked.
The existing PEs/maps, server gate, data results and README graphics describe
earlier checkpoints, not validation of the current working tree. Final raw-link
checks, fresh lint and the server gate remain pending.

See [handoff](HANDOFF.md) for prepared work and resume steps. Stop evidence is
`.scratch/gui-text-creator-integration/STOPPED.json`; detailed receipts are in
that directory. No further build or reconstruction starts without a resume request.

## Current integration

- The inferred `d2_ShowTxt` now shares Gold `0x473640` and TL `0x46fac0`
  in `Develop/Units/d2.v1/`. Gold uses signed word coordinates; TL uses
  dwords. The canonical header preserves that difference. Gold's complete
  525-byte C body passes all 31 applied operands and 65 rejecting controls;
  TL retains its 518-byte object. The three NOPs following Gold's return are
  a separately reviewed inventory-boundary correction, not C padding.
  All 28 caller TUs use the shared contract. Gold's eleven misrouted creator
  calls and four misrouted receiver calls select their evidenced providers;
  the unrelated Gold `0x46fac0` stays separate. Creator results and receiver
  IDs are integers. Twenty-seven caller objects preserve nondebug sections
  and reviewed operands. TL `0x4d6170` changes four register-color bytes in
  an existing nonmatching body; its size and relocations stay unchanged.
  Fresh verification passes 98 of 102 selected contexts, with four existing
  size mismatches and no compile failures. Gold `0x5bcb10` now earns RELOC
  after the provider repair. Two private TL views pass their sizeof and all
  24 offsetof assertions; neither view claims storage ownership.
  The source-contract audit still reports conditional-coordinate typedef
  uncertainty; actual target compiles resolve it, but it is not a clean audit.
  The full rebuild stopped at 59%; final raw-link checks remain pending. Receipts:
  `.scratch/gui-text-creator-integration/`.
- The inferred `d2_SetElementValue` now shares the TL `0x472380` and Gold
  `0x475ca0` setters with a variadic contract: widget kind and flags select
  string, integer or unused payloads. All selected callers use the canonical
  header. Three timer conversions and the file selector's pointer payloads
  retain their native calling behavior. Gold now uses the existing shared
  step helper at `0x475be0`, replacing its obsolete zero-return scaffold.
  Both setters officially measure RELOC (389/389 and 390/390); pool and helper
  operands validate, while `_itoa` remains unresolved in catalog evidence.
  All 75 rebuilt object contexts preserve nondebug sections and operands apart
  from the reviewed names. Complete mapped setter/helper bytes agree, with
  18 rejecting controls across the setters. Both placements remain displaced.
  Imports are unchanged, and all 106 changed data-pointer slots per client
  retain their mapped symbol or bounded CRT offset. Gold loses the 16-byte
  helper stub; TL's section sizes stay unchanged. No storage owner or original
  TU boundary was inferred. The external file-selector form is unavailable,
  so its string-widget subtype remains an explicit input precondition.
  That checkpoint exposed two wrong text-creator bindings in Gold `0x5bcb10`
  and demoted it to NEAR_MATCHING. The later creator integration above repairs
  those providers and records the fresh verdict.
  Receipts: `.scratch/gui-setter-integration/` and
  `.scratch/gui-text-creator-provider-review/`.
- Three more client bodies now share C definitions: the six-record GUI cleanup
  (TL `0x4d0ec0`, Gold `0x4cfe70`, 50 bytes), recipe-key lookup
  (TL `0x4ec960`, Gold `0x4eabe0`, 59 bytes), and 14-byte calendar-copy callback
  (TL `0x55a820`, Gold `0x552730`, 60 bytes). All six official object checks
  are RELOC with every operand VALIDATED. The five-byte lookup wrappers and
  77-byte bonus callers remain RELOC; the latter retain three unresolved
  global operands per target. Reviewed Gold inventory splits separate the
  newly bound entries from their preceding functions and alignment bytes.
  Two GUI-table rows identify addresses without claiming an extent or owner;
  the scaffolds' 48-dword buffers are comparison capacity only.
  All eight rebuilt contributions, including the forwarding wrappers, match
  their complete native bodies after applying the reviewed operands and match
  their mapped raw-link bytes. All eight placements are displaced; none earns
  linked EXACT. Eleven saved-object comparisons preserve every other nondebug
  section and operand target, including the GUI initializer. Import identities
  are unchanged across all three images. The initializer remains RELOC 581/581,
  with five unresolved operands. Existing alchemistry nonmatches remain open.
  Receipts: `.scratch/client-small-bodies-integration/`.
- Gold `0x418030` now reuses the existing TL `0x4195f0` C cleanup. Both
  official comparisons are RELOC 76/76 with all 11 operands VALIDATED.
  The duplicate Gold assembly body and its assembly marker are removed.
  Six data identities bind the existing pointer slots without allocating storage
  or claiming their owners. Complete applied-byte proof, rejecting controls
  and 16 null/callee-mutation cases are in `.scratch/gold-cleanup-c/`.
  Both fresh raw links contain the applied compiled body at displaced addresses;
  neither earns linked EXACT. The TL object's non-CodeView sections are unchanged.
- The shared GUI forwarding wrapper now passes its slot argument to the
  correct target provider: Gold `0x46e700`, TL `0x46b2b0`. Both five-byte
  wrappers remeasure RELOC with their callee operands VALIDATED. The Gold
  caller remains RELOC 45/45 with unchanged non-CodeView sections. Both
  destructors remain explicit, unrecovered `void(int)` stubs; observed calls
  discard their result, which does not prove the original return declaration.
  Another 19 Gold calls in four shared TUs now select the same Gold provider;
  all eight official target contexts remain RELOC, with those calls VALIDATED.
  Unrelated global operands remain unresolved.
  All four TL objects and the complete TL image are unchanged by that correction.
  The obsolete Gold scaffold provider is removed. Its 16-byte contribution shifts
  later Gold code; all 106 changed data-pointer slots retain the same mapped
  symbol or bounded CRT function offset. Imports are unchanged.
  Receipts: `.scratch/gui-forwarding-contract/` and `.scratch/gui-provider-audit/`.
- The sound-control declaration repair removes the conflicting zlib declaration
  and uses the existing shared callee's pointer argument. Both official wrappers
  remain RELOC 44/44, and both complete non-CodeView objects are unchanged.
  Receipts: `.scratch/vfs-warning-triage/`.
- Gold `0x423a50` is C: official RELOC 59/59, five validated operands and two
  IAT-policy slots. Independent application validates all seven operands and
  13 rejecting controls. Its rebuilt raw contribution agrees with the compiled
  object at that checkpoint's displaced address `0x424720`; this is not linked EXACT.
  The old assembly marker/blocker are removed. No storage was added.
  Receipts: `.scratch/gold-msx-lock/`.
- Gold `0x4790d0` is C: official object checks are RELOC 53/53, with its two
  callers at 49/49 and 91/91. Current source hashes match those receipts. This
  replaces already-accounted assembly; it adds no accounted text.
- Four TL callbacks (`0x40cfb0`, `0x551010`, `0x55af10`, `0x586bd0`) now have C
  implementations with fresh RELOC verdicts at 51, 61, 38 and 61 bytes.
  All eight operands are VALIDATED. Independent applied-byte comparisons and
  wrong-target/site/window controls pass on the final sources. These are
  object results; client raw-link validation remains due.
- Gold `0x4c6a50` now binds the existing `cm_MarkAndReturn` in `command.c`,
  whose selected Gold object matches all 14 native bytes. Its old 64-byte
  inventory extent was split into the 14-byte function and a separate 37-byte
  entry at `0x4c6a60`. The replacement binding now measures EXACT 14/14;
  the new entry remains unreconstructed.
- TL `g_774a1c` has an identity-only data row. Six native dword references and
  both operands of the cached `0x586bd0` object agree. No extent, storage owner
  or C allocation was inferred.
- The attested `d3_LoadAnimStream` name now covers its shared client definition
  in `Develop/Units/d3`; both targets remeasure RELOC 207/207, with seven
  unresolved operands each. The corrected `cm_TestCommandResult` filename
  remeasures EXACT 23/23. All 28 affected client compile contexts preserve
  non-CodeView sections and operands apart from the animation symbol rename.
  Both animation-options bindings have fresh sizeof/offsetof checks after the
  declaration rename; the 12-byte type and offsets are unchanged.
  Exact original filenames/TU boundaries and raw-link placement remain unproved.

All 20 reconstruction and organization reports are in `.scratch/dsh-wave1/results/`.
Parent review and fresh official comparisons are in `.scratch/dsh-wave1/review/`;
naming/move preservation checks are in `.scratch/dsh-wave1/naming-review/`.
Compilation works through the pinned unshare runner. Both client source lists
were regenerated, and the broad two-job rebuild completed successfully:
`.scratch/dsh-wave1/naming-review/clients-build.log`. Gold then relinked after
the audio-wrapper replacement. Both raw-image comparisons still fail; object
results do not establish native placement.

The updated [community review](community-research.md#exe-branch-follow-up-2026-10-19)
records original-name and algorithm leads. It establishes no new original TU
or local byte verdict. The upstream fixture-isolation fix passed 12,715 tests
(48 skipped) and merged in [Rebrew #35](https://github.com/maci0/rebrew/pull/35).
The last completed lint is `.scratch/gui-setter-integration/lint-final.json`:
36 E023 errors and zero warnings per target. The official blocker backfill
documented 1,848 Gold and 1,284 TL unmatched rows without changing their verdicts;
this clears missing-explanation warnings, not the recovery work. Rebrew 5.2.0
also removes the obsolete-template W033 warning. No type-staleness warning
remains in that receipt. Lint was not rerun after the creator integration.
The temporary layout-probe failure under unshare was reproduced
and repaired in [Rebrew #36](https://github.com/maci0/rebrew/pull/36);
the native replay passes in both clients. Both upstream fixes are on `main`.
The later [Rebrew #37](https://github.com/maci0/rebrew/pull/37) removes size-only
import-thunk claims from blocker backfill; its full suite passed 12,820 tests
(37 skipped). That fix is on upstream `main`, outside the pinned 5.2.0 release.
None of this checkpoint's backfilled rows took the short-body heuristic.
[Rebrew #38](https://github.com/maci0/rebrew/pull/38) also merged: function tests
skip a redundant SIZE transaction while retaining missing/changed size writes.
Its local suite and all six CI jobs passed; it is not yet in the pinned release.
[Rebrew #39](https://github.com/maci0/rebrew/pull/39) merged with all CI checks
passing: indexed table references are explicit candidates rather than inferred
effective addresses, and reference-binding rename previews carry guarded input
digests. Its full suite passed 12,837 tests (48 skipped). These repairs are also
outside the pinned 5.2.0 release.
[Rebrew #40](https://github.com/maci0/rebrew/pull/40) merged with all six CI jobs
passing: conservative unshare CL caching, target-isolated verification results
and comparison baselines (including #41), corrected nested-header lookup, and
the preserved startup optimization. The final full suite passed 13,007 tests
(36 skipped); seven real compiler dispatches preserve complete cold/hot control
objects and diagnostics. Rejected cache candidates are validated privately
before atomic publication. These changes are not in the installed 5.2.0 release.
See [performance limits](verify-performance.md#runner-and-caches).
[Rebrew #42](https://github.com/maci0/rebrew/pull/42) fixes guarded binding of
valid typed `va_arg` expressions without weakening malformed-source rejection.
[Rebrew #43](https://github.com/maci0/rebrew/pull/43) removes discarded row
copies from metadata writer validation. Both fixes passed their full local
suites and all six CI jobs, and are merged outside installed 5.2.0.
Parser and writer receipts are in `.scratch/upstream-va-arg-evidence/` and
`.scratch/upstream-writer-evidence/`; the profile's limits are in
[verification performance](verify-performance.md#causes-and-fixes).
[Rebrew #44](https://github.com/maci0/rebrew/pull/44) also passed its full local
suite and all six CI jobs before merging: read-only developer preflights now
honor `UV_PROJECT_ENVIRONMENT` without creating a local `.venv`. Evidence is in
`.scratch/upstream-preflight-evidence/`; installed 5.2.0 remains unchanged.

## GoldTL data audit, 2026-10-19

At the last completed setter-integration checkpoint, both rebuilt scaffolds
have **0 exact data placements**. Those raw-image checks report:

| Target | Displaced / absent from map | Byte-equal / different / missing | Compared / total |
| --- | --- | --- | --- |
| Gold | 306 / 14 | 83 / 30 / 49 | 162 / 320 |
| GoldTL | 336 / 22 | 93 / 51 / 42 | 186 / 358 |

Gold has 158 non-comparable symbols; TL has 172. These include zero-fill tails
and addresses outside file-backed data. Byte equality at a reference address
does not establish the displaced symbol's identity there. Both whole-file
checks fail as expected for comparison scaffolds. Last completed receipts and hashes:
`.scratch/gui-setter-integration/image-{gold,tl}.json`.
The two unsized GUI-table identities add one non-comparable row per target;
they do not increase compared bytes or establish storage ownership.
The earlier TL snapshot below had 330 displaced symbols and 24 absent.

The logging tables/newline/default name and both Sonnenstrahlen strings have
correct file bytes at their mapped addresses. Before this rebuild, the scaffold's
`ch_MorphFrameValue` and `SonnenstrahlenStartZeit` contain zero where the
reference initializes them to -1; `g_6752a4` also has a zero placeholder for
native value 1. Both clients' stub-generator overrides now preserve those values.
Both regenerated stub objects compile without warnings. Both new raw images
contain the three expected values at their mapped addresses. Original owners
and native placement remain unresolved.
The critical-section slots already have import metadata and KERNEL32 providers;
their placement differs.

Complete COFF/native literal audits identify TL's `dbl_1_0`, Gold's distinct
`dbl_2_0`, and each image's `flt_0_3`. Their metadata now names the emitted
compiler symbols; no new C storage was added. On that checkpoint's TL map this
reduced absent symbols from 24 to 22 (332 displaced). These are content and
symbol-binding checks, not native placement or original TU ownership proof.

Receipts: `.scratch/dsh-wave1/review/data-diagnosis-tl.json` and
`data-linked-location-samples.json`. The original audit changed only 22 GoldTL
comparison records. The four later literal bindings above are separate changes.
Correcting displaced initializers does not fix native placement.
Literal/initializer receipts and that TL comparison are in
`.scratch/data-initializers/`; the earlier Gold comparison is
`.scratch/gold-msx-lock/gold-rebuilt-image.json`. Use the final receipts above
for the last completed images; no creator-integration image check has run.

## Verified checkpoint

These completed checks precede the paused creator integration. The server gate
has not been rerun for the current working tree; the interrupted build is
recorded in the paused checkpoint above.

| Area | Result | Receipt |
| --- | --- | --- |
| Server raw image | All 286,720 bytes equal the untouched reference. Fresh function checks 316/316; data checks 652/652. Whole-image checks, Wine loading and toolchain alignment pass. The gate fails only on the 36 E023 findings. | `.scratch/gui-setter-integration/server-gate.log`, `gate-verify.json` |
| Client builds | The 9,305-entry two-job rebuild exited 0, producing both PEs/maps under `build/`. It emitted 310 compiler-warning lines, with no compiler errors or linker diagnostics. Both images remain scaffolds and differ from their references. | `.scratch/gui-setter-integration/clients-build.log`, `build-diagnostics.json`, `post-build-proof.json` |
| Gold getter | `0x4364f0` is C, RELOC25/25, with its DIR32 validated. Gold subsequently relinked. The new pointer slot is comparison storage, not a recovered owner. | `.scratch/goal110-full-runs/getter-official.json`, `gold-rebuild.log` |
| Experimental runner | Verification and CMake CL/LINK/LIB use configured unshare. Wine-prefix initialization, private font cache and extracted mtimes are repaired upstream. Complete Gold/TL probe objects equal Docker controls. | `.scratch/goal110-full-runs/compile-equivalence.json`, `seed-isolation.json` |
| Upstream tests | 12,586 passed, 36 skipped; mypy checked 392 files. These are the upstream suite, not raw-image or client proof, and not a verdict on later edits. | `.scratch/goal110-full-runs/upstream-suite-final.log`, `upstream-mypy-final.log` |

The first client passes emitted 457 compiler-warning lines across 128 files.
Those logs are not warning-free builds. The first warning batch preserves
complete non-CodeView sections and relocations in 18 contexts. Later edits need
independent review, official comparison and relinking. See
`.scratch/goal110-full-runs/compiler-warnings.json` and `warning-batch/`.

Assembly lint stayed open after that gate.
`.scratch/publication/guild-final51-lint.json` (2026-10-18 16:23) reports 39
E023 errors and 0 warnings in each target summary. The gate's 41 errors are the
earlier log. Run `rebrew lint` again after further edits.

## Next actions

Work resumed on 2026-10-19; the delegated waves above run on the game STUB
queue while closure stays pending. First finish the interrupted build and its
prepared raw-link checks, then obtain fresh lint and server-gate results before
committing the current integration.

1. **Continue the validated-extent game queue.** Wave 3 covers the first 100 of
   the 604 rows whose stored extent the fresh discovery pass validates; keep
   the `external_ranges` band and CRT/runtime tail out of reconstruction.
   Review each wave's extent-defect and ABI reports.
2. **Repair reviewed inventory extents.** Apply a reviewed
   `rebrew binary repair-extents` batch for the 409 merged/padded game rows
   plus the sibling entries fresh discovery found, then reconstruct them.
3. **Finish warning repairs and rerun both clients.** Review numeric conversions,
   pointer/callee contracts, packing and return paths against native evidence.
   Preserve every selected target context. Do not suppress diagnostics, add
   arbitrary initializers or replace recovered behavior with stubs.
4. **Recover unsupported assembly as C.** The Goal110 getter left 40 outstanding
   Gold-audit entries at that checkpoint. That denominator is the audit list,
   not the later 39 E023 lint receipt. Query the live list. Old EXACT/RELOC
   assembly verdicts are not C-recovery credit. Fourteen TL comparison stubs
   also need native ABI/provider recovery.
   [Assembly policy and receipts](assembly-audit.md) define the allowed exceptions.
5. **Close client providers and storage.** Resolve duplicate native identities,
   comparison placeholders, omitted TUs and unproven global owners. Keep stock
   libraries linked and distinguish import slots from game storage. Do not add
   the server BSS owners to a client to satisfy names. The shared GUI text
   creator still depends on scaffolded index allocation and text measurement,
   plus Gold's scaffolded list insertion. Recover those providers and their
   caller contracts; TL's recovered insertion body can guide a shared version.
   A complete creator body does not establish the helper implementations.
6. **Continue scene, terrain and savegame contracts.** Prioritize the building/
   placement family, opaque stream callers, resource constructors and renderer
   dependencies. Native counterpart mappings and bounded behavior checks do not
   establish compiled bodies or original source ownership.
7. **Verify final inputs and raw images.** Rebuild after the last source/header
   edit, compare placement/imports/data/whole files, and rerun the server gate.
   Preserve server raw identity while closing lint and source-fidelity debt.

## Commands

```sh
uv run rebrew todo --json
uv run rebrew status --all-targets --json
uv run rebrew lint --all-targets --json
uv run rebrew verify --data --target Europa1400Gold.exe --json
uv run rebrew verify --data --target Europa1400Gold_TL.exe --json
uv run scripts/gate.sh
```

`todo --json` uses the default target, GoldTL. `verify --data` can record data
verdicts for the configured raw link, and compiles functions only when asked.
Bare `verify` checks functions. `--no-cache` skips saved verification results;
a matching compiler-object cache entry can still supply the object. Under
unshare, Rebrew 5.2 directs RELOC `todo` rows to raw-image verification
([runner limits](verify-performance.md#runner-and-caches)). Check current CLI
help before reusing an old command. Client build recipes and scaffold limits
are in [stubs/README.md](../stubs/README.md).

## CURRENT STATE

Server-only table generated from the last completed gate, before the current
creator integration. A zero raw-image gap does
not imply a passing gate, recovered client code or verified source ownership.

<!-- CURRENT-STATE:BEGIN -->
<!-- generated by scripts/update_state_table.py -- do not hand-edit -->

| Quantity | Value | Source |
|---|---|---|
| verify `passed` | **316/316** | gate's `BASELINE` |
| `.text` residue | **0** | raw-link file identity |
| raw-link `.data` divergence | **0** | raw-link file identity |
| relocation records missing / extra | **0 / 0** | `rebrew verify --whole-binary` |
| raw-link import table | **matches** | gate, round 210 |
| OBJECTIVE GAP (raw link vs reference) | **0** | raw-link file identity |
| ...of which | **0 differing bytes in the common prefix, 0 bytes of size shortfall** | gate's decomposition |
| annotations shorter than the binary | **?** | `rebrew verify --json` |
| `cmake --build` exit | **0** | gate's build step |

<!-- CURRENT-STATE:END -->

## Evidence and handoff

- Paused creator integration and stop record: `.scratch/gui-text-creator-integration/`.
- Prepared helper candidates and native-only checks: [handoff](HANDOFF.md#prepared-helper-work).
- Goal110 build, runner and warning receipts: `.scratch/goal110-full-runs/`.
- Earlier client source/provider cutover: `.scratch/goal106-client-cutover/`.
- Text-placement repair: `.scratch/goal107-text-placement/`.
- Scoped assembly review: `.scratch/goal108-assembly-provenance/`.
- Full pre-cleanup queue: [2026-10-18 archive](goal-history.md#full-notebooks).

Replace this checkpoint when evidence changes. Keep experiment details in their
technical reference or scratch receipt; query metadata for live counts.
