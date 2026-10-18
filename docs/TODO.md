# Current work

The [three-binary objective](../goal.md) is incomplete. This checkpoint records
Goal110 checks on **2026-10-18** and fresh client builds on **2026-10-19**.
Both clients remain comparison scaffolds. Historical checkpoints are in
[goal history](goal-history.md).

## Current integration

- Gold `0x423a50` is C: official RELOC 59/59, five validated operands and two
  IAT-policy slots. Independent application validates all seven operands and
  13 rejecting controls. Its rebuilt raw contribution agrees with the compiled
  object at the displaced address `0x424720`; this is not linked EXACT.
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
Latest lint is `.scratch/dsh-wave1/review/lint-refreshed-types.json`: 38 E023
errors and one W033 warning per target. W033 is the installed 5.1.0 template's
obsolete metadata-format wording; the correction is upstream. No type-staleness
warning remains. The temporary layout-probe failure under unshare was reproduced
and repaired in [Rebrew #36](https://github.com/maci0/rebrew/pull/36);
the native replay passes in both clients. Both upstream fixes are on `main`.

## GoldTL data audit, 2026-10-19

The existing scaffold has **0 exact placements, 330 displaced symbols and
24 absent from the map**. At reference addresses, 186/354 symbols are
comparable: 93 byte-equal, 51 different and 42 missing. Byte equality at a
reference address does not establish the displaced symbol's identity there.

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
compiler symbols; no new C storage was added. On the existing TL map this
reduces absent symbols from 24 to 22 (332 displaced). These are content and
symbol-binding checks, not native placement or original TU ownership proof.

Receipts: `.scratch/dsh-wave1/review/data-diagnosis-tl.json` and
`data-linked-location-samples.json`. The original audit changed only 22 GoldTL
comparison records. The four later literal bindings above are separate changes.
The new TL image still has 0 exact placements, 332 displaced symbols and 22
absent from the map. Reference-address comparison remains 93 equal, 51 different
and 42 missing; correcting displaced initializers does not fix native placement.
Literal/initializer receipts and the fresh TL comparison are in
`.scratch/data-initializers/`; the final Gold comparison is
`.scratch/gold-msx-lock/gold-rebuilt-image.json`. Image hashes are in those receipts.

## Verified checkpoint

| Area | Result | Receipt |
| --- | --- | --- |
| Server raw image | All 286,720 bytes equal the untouched reference. Function checks 316/316; data checks 652/652. That gate log records 41 lint errors, all E023, so the gate still fails. | `.scratch/goal110-full-runs/server-gate-retry.log`, `.scratch/gate-lint.json` |
| Client builds | Both complete build passes exited 0 and produced PEs/maps under `build/`. They contain explicit scaffolds and differ from their references. | `.scratch/goal110-full-runs/{gold-build,goldtl-build}.log` |
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

1. **Finish warning repairs and rerun both clients.** Review numeric conversions,
   pointer/callee contracts, packing and return paths against native evidence.
   Preserve every selected target context. Do not suppress diagnostics, add
   arbitrary initializers or replace recovered behavior with stubs.
2. **Recover unsupported assembly as C.** The Goal110 getter left 40 outstanding
   Gold-audit entries at that checkpoint. That denominator is the audit list,
   not the later 39 E023 lint receipt. Query the live list. Old EXACT/RELOC
   assembly verdicts are not C-recovery credit. Fourteen TL comparison stubs
   also need native ABI/provider recovery.
   [Assembly policy and receipts](assembly-audit.md) define the allowed exceptions.
3. **Close client providers and storage.** Resolve duplicate native identities,
   comparison placeholders, omitted TUs and unproven global owners. Keep stock
   libraries linked and distinguish import slots from game storage. Do not add
   the server BSS owners to a client to satisfy names.
4. **Continue scene, terrain and savegame contracts.** Prioritize the building/
   placement family, opaque stream callers, resource constructors and renderer
   dependencies. Native counterpart mappings and bounded behavior checks do not
   establish compiled bodies or original source ownership.
5. **Verify final inputs and raw images.** Rebuild after the last source/header
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
a matching compiler-object cache entry can still supply the object. A RELOC
`todo` row may print `rebrew test --linked`, which unshare refuses
([runner limits](verify-performance.md#runner-and-caches)). Check current CLI
help before reusing an old command. Client build recipes and scaffold limits
are in [stubs/README.md](../stubs/README.md).

## CURRENT STATE

Server-only table generated from the last gate log. A zero raw-image gap does
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

- Goal110 build, runner and warning receipts: `.scratch/goal110-full-runs/`.
- Earlier client source/provider cutover: `.scratch/goal106-client-cutover/`.
- Text-placement repair: `.scratch/goal107-text-placement/`.
- Scoped assembly review: `.scratch/goal108-assembly-provenance/`.
- Full pre-cleanup queue: [2026-10-18 archive](goal-history.md#full-notebooks).

Replace this checkpoint when evidence changes. Keep experiment details in their
technical reference or scratch receipt; query metadata for live counts.
