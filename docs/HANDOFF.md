# Handoff

Read [current work](TODO.md), [the objective](../goal.md), then the
[reference map](README.md#reference-map). Use metadata and fresh checks for live
counts. The project default target is GoldTL; name `server.dll` for the server.
Historical commands and measurements are in [goal history](goal-history.md).

## Current status snapshot (2026-10-21 16:24 UTC)

All three build images exist. The server remains byte-identical:
`3cc2ce9049e41ab6d0eea042df4966fbf57e5e27c67fb923e81709d2683609d1`.
Its fresh data/image verification again passes all 652 compared symbols and the
complete PE check. Both client CMake targets link successfully with same-build
maps and comparison-only placeholders (2871 Gold, 4138 TL). They are not
playable or byte-identical games.

Data comparisons now run directly with `uv run rebrew verify --data` (TL) or
`--target Europa1400Gold.exe`. Gold reports 83 matching / 30 differing / 49
missing symbols; TL reports 100 / 51 / 40. Respect the non-comparable BSS/file
limits and displaced placements; no client EXACT data placement was earned.

Project tests: 34 passed plus 3 subtests. Lint: zero errors; server and Gold
have no warnings, TL has two unsupported-inline-assembly warnings. Compiler
warnings and the incomplete source/ABI/storage contracts remain. The full gate
was not rerun. Rebrew's generator fix is on upstream main at
[8bd102e6](https://github.com/maci0/rebrew/commit/8bd102e6), with 13074 tests passing.
The [build guide](../stubs/README.md) covers regeneration's version requirement.

The [README charts](../README.md#reconstruction-status) and
[tracker](TODO.md#status-snapshot-2026-10-21-1202-utc) show this checkpoint. Earlier
pause/resume notes below are historical. Receipts:
`.scratch/linkable-clients-20261021/`.

## Paused state before the 2026-10-19 resume

The user requested that delegated work finish and reconstruction stop. All
owned tasks are terminal; no owned compiler or emulation process remains.
At that checkpoint, source, inventory and managed metadata changes for the
shared `d2_ShowTxt` integration were uncommitted. The integration above
supersedes that Git state.

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

The creator checkpoint used Rebrew 5.2.0 plus an explicit development checkout
for guarded integration commands. The conditional-typedef audit note was later
merged upstream; that documents the gap rather than resolving the audit.

On October 20, Guild upgraded to released Rebrew 5.4.0 and applied the import-API
recipe migration. The venv changed only Rebrew; dependency checks, optional
imports, 22 selected project tests and exact import-response parity pass.
All six upstream release CI jobs passed. Native rebuilds and final raw-image
validation remain separate work. Release evidence is in
`.scratch/rebrew-release-5.4.0-logs/`; see [tooling notes](tooling-upstream.md#import-table-api-extraction-2026-10-20).
