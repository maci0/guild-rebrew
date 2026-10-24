# Handoff

Read [current work](TODO.md), [the objective](../goal.md), then the
[reference map](README.md#reference-map). Use metadata and fresh checks for live
counts. The project default target is GoldTL; name `server.dll` for the server.
Historical commands and measurements are in [goal history](goal-history.md).

## Current data/status snapshot (2026-10-24 15:29 UTC)

The existing server image remains byte-identical, SHA-256
`3cc2ce9049e41ab6d0eea042df4966fbf57e5e27c67fb923e81709d2683609d1`.
Fresh data verification passes 652/652 and the complete PE comparison.
Current source claims are a separate checkpoint: 247/251 C matches and 97.9%
code accounting, with four unverified claims during source reorganization.

Data checks at 15:27 UTC: Gold 83 matching / 30 differing / 49 missing,
159 not file-comparable; GoldTL 125 / 51 / 15, 172 not file-comparable.
Neither client earns an EXACT data placement. The stored data charts exclude
BSS and imports from initialized bytes; content matches are not placement proof.

Gold still uses `build/Europa1400Gold.exe`. GoldTL now selects
`build-goldtl-audit/Europa1400Gold_TL.exe`, measured with SHA-256
`f43b0d5d76220fc99319cf657c3708a5364a507974fe496fcc73546b26cfb08b`.
Concurrent build work removed that EXE after its data comparison. The later
status/chart correctly reports no current image score; it does not fall back
to the older file in `build/`. Rebuild before repeating the default TL check.

Stored C matches: GoldTL 3,833/4,948 (77.4%, 51.3% code accounting), Gold
1,882/4,426 (42.5%, 20.8% accounting), plus one Gold whole-function assembly
match. GoldTL has zero STUB, but 1,027 size mismatches, 83 near matches and five
semantic-only PROVEN results. Ongoing uncommitted source/binding reorganization
changes these counts; none is a fresh function-verification or gameplay result.

The [README and charts](../README.md#reconstruction-status) use one status
snapshot. This refresh rebuilds no binaries and runs no full gate. Current
source work remains in [the tracker](TODO.md); earlier handoffs below are
historical. Receipts: `.scratch/data-readme-refresh-20261024/`.

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
