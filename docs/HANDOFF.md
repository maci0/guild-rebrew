# Handoff

Read [current work](TODO.md), [the objective](../goal.md), then the
[reference map](README.md#reference-map). Use metadata and fresh checks for live
counts. The project default target is GoldTL; name `server.dll` for the server.
Historical commands and measurements are in [goal history](goal-history.md).

## Paused state before the 2026-10-19 resume

The user requested that delegated work finish and reconstruction stop. All
owned tasks are terminal; no owned compiler or emulation process remains.
Source, inventory and managed metadata changes for the shared `d2_ShowTxt`
integration remain uncommitted and unpushed. Documentation housekeeping does
not resume the objective.

The Gold/TL creators measure RELOC at 525/518 bytes. Scoped verification passes
98 of 102 contexts; the other four retain existing size mismatches, with no
compile failures. Caller preservation covers 27 of 28 TUs. TL `0x4d6170`
changes four register-color bytes in an existing nonmatch. The conditional
coordinate typedef still produces source-contract audit uncertainty.

The full client rebuild stopped at 59%, exit 143 after the requested SIGTERM.
There were no compiler-error lines through the stop, but neither client was
relinked. Existing `build/` PEs/maps, data comparisons, server gate and README
graphics belong to earlier checkpoints. Final raw-link validation, fresh lint
and the server gate have not run for this integration.

Local receipts: `.scratch/gui-text-creator-integration/`, especially
`STOPPED.json`, `official-closure-{gold,tl}.json`,
`caller-preservation-summary.json` and `provider-gold-proof.json`.
Scratch receipts are local and ignored by Git; the checkpoint in
[current work](TODO.md#paused-checkpoint-2026-10-19) preserves the public summary.

## Prepared helper work

These are preparation packages, not newly integrated or byte-matched C bodies.
Each path is a local scratch directory containing `REPORT.md`.

| Package | State / limits | Receipt directory |
| --- | --- | --- |
| Index allocators, Gold `0x46c9e0` / TL `0x469890` | Candidate uncompiled; wrappers not admitted to inventory/catalog. Existing scanners stay unchanged. | `.scratch/gui-index-allocator-prep/` |
| Native allocator checks | 18 finite cases pass; two negative controls reject. Executes original wrapper and scanner. No C-equivalence or storage-capacity claim. | `.scratch/gui-index-allocator-emulation/` |
| Text width, Gold `0x46ea00` / TL `0x46b520` | Candidate uncompiled; both production providers remain stubs. | `.scratch/gui-text-width-prep/` |
| Insertion, Gold `0x4730d0` / TL `0x46f650` | Candidate uncompiled; Gold remains a stub, TL already has recovered RELOC C. | `.scratch/gui-element-insertion-prep/` |
| Native insertion checks | 26 fixtures pass: 24 returning cases and two expected invalid-read paths; 24 wrong-output controls reject. Copy/error callees are explicit models, not provider proof. | `.scratch/gui-element-insertion-native/` |
| Creator data identities | 13 proposals, none applied; extent and ownership remain unresolved. | `.scratch/gui-creator-data-identities/` |
| Glyph contract | Gold consumes the low word; TL consumes a full signed index. Keep existing EXACT providers; no universal narrowing is justified. | `.scratch/gui-glyph-lookup-contract/` |

The extra harness slots used to observe LAST+1 accesses establish no native
allocation capacity or storage owner.

## Resume steps (work resumed 2026-10-19)

The three-binary goal resumed on 2026-10-19 with delegated reconstruction
waves ([current work](TODO.md#delegated-reconstruction-waves-2026-10-19)).
Closure still starts here: review the working-tree diff and the stop record.
Resume the existing
build with `cmake --build build/clients --parallel 2`; keep the compiler cap at
two. After a successful link, review and run the prepared `post-build.py`,
`image-checks.py` and `check-data-pointer-shifts-tl.py` in the integration
directory. Their syntax was checked, but their final raw-image checks have
not run. Then obtain fresh lint and server-gate results before committing.
Do not reuse earlier scaffold images as evidence for the new source.

Guild remains on released Rebrew 5.2.0. Guarded integration commands used an
explicit development checkout at `.scratch/publication/release-validation/rebrew`;
the venv was not upgraded. That checkout also has an unpushed docs-only commit
`bb2ea476` on `docs/guild-conditional-coordinate-audit`, recording the conditional
typedef audit gap. Its pre-commit checks passed; the full upstream suite and
publication were not run for that commit. Publishing or tooling changes remain
outside this paused handoff.
