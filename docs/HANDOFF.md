# Handoff

## Current committed snapshot (2026-10-29 02:40 UTC)

README, code/data bars and defrag map now describe the accumulated committed
source tree, using one CLI status report. Server code and stored data are 100%,
but its current raw file agrees at 74.4%; the byte-identical v1.6.1 build is
historical. GoldTL has 4,100/5,184 C matches (79.0%), 53.4% code accounting and
8.3% raw-file agreement. Gold has 1,881/4,426 C matches (42.4%), 21.0% accounting
and 1.1% raw-file agreement. No new native build or data verification ran.

All accumulated source, metadata, layout and build changes were committed; the
modified .lib archive was explicitly excluded. A stale cross-import fixture
path was corrected after its source moved. Tests: 39 passed plus 3 subtests.
All-target lint found zero errors; its only generated-guidance warning was
cleared by refresh, with project rules preserved and init --check passing.
Receipts: .scratch/readme-refresh-20261029/.


## Release 1.6.1 — server verification and charts (2026-10-27)

A fresh isolated build with published Rebrew 6.3.1 reproduces all 286,720 server
bytes (SHA-256 `3cc2ce9049e41ab6d0eea042df4966fbf57e5e27c67fb923e81709d2683609d1`).
Verification passes 316/316 functions (251 game, 65 source-built library) and
652/652 data records. Status reports 100% server code accounting, C matches,
raw-file agreement and all three data bars (547/547 records, 66,664 bytes).

Reviewed 76 server inventory extents end before 712 trailing NOPs. Those bytes
remain linker/compiler alignment; no source or image bytes were inserted.
Rebrew now supplies the native Microsoft-runtime toolchain profile, so the
obsolete duplicate project overlay and its CMake environment override are removed.

The README and all three graphics use one release-source status snapshot after
fresh data checks. GoldTL: 3,804/5,122 C matches, 47.8% code accounting; Gold:
2,466/4,592 C matches, 22.6%. Existing client raw images agree at 2.0% and 1.1%.
Neither client was rebuilt or made playable. Ongoing uncommitted client recovery
is preserved outside this release; its larger counts must not be mixed into the
release charts. Canonical server bindings accidentally retired by the client
library sweep were restored separately and their two TUs pass 80/80 checks.

Release tests: 39 passed and 3 subtests; all dependency extras resolve, `uv lock
--check` and `uv pip check` pass. Source-built library attribution and whole-file
identity remain separate claims. No full project gate or new gameplay test is
claimed. Local receipts: `.scratch/release-20261027/`.


Read [current work](TODO.md), [the objective](../goal.md), then the
[reference map](README.md#reference-map). Use metadata and fresh checks for live
counts. The project default target is GoldTL; name `server.dll` for the server.
Historical commands and measurements are in [goal history](goal-history.md).

## Server data placement fix (2026-10-24 19:24 UTC)

Rebrew 6.1.1 resolves private data through checked map-selected COFF sections,
interior aliases through bounded backing offsets, and layout intervals through
section coordinates. The server now has 547/547 EXACT data records in status
and 652/652 passing raw checks, with the complete DLL unchanged. One float-pool
identity was bound after a full native literal audit. No storage or symbols
were synthesized. Receipts: `.scratch/server-data-placement-20261025/`.
Client measurements and source counts below remain the earlier checkpoint.

## Current data/status snapshot (2026-10-24 18:38 UTC)

The existing server remains byte-identical, SHA-256
`3cc2ce9049e41ab6d0eea042df4966fbf57e5e27c67fb923e81709d2683609d1`.
Fresh data verification passes 652/652 and the complete PE comparison. Gold
again reports 83 content matches, 30 differences, 49 missing and 159 not
file-comparable. Neither client has an EXACT data placement.

The configured GoldTL audit EXE is unavailable and its map is empty during an
ongoing rebuild. The latest recorded link failed with 20 unresolved symbols.
The fresh image-only attempt exits 2 without updating verdicts. TL's stored
data result remains the 15:27 UTC check on 2026-10-24: 125 content matches,
51 differences, 15 missing and 172 not file-comparable, image SHA-256
`f43b0d5d76220fc99319cf657c3708a5364a507974fe496fcc73546b26cfb08b`.
No fallback image or partial link output is treated as a fresh TL data check.

The [README/charts](../README.md#reconstruction-status) share one status report:
server 247/251 C matches, TL 3,835/4,946 (77.5%), Gold 1,882/4,426 (42.5%),
plus one Gold whole-function assembly match. TL has one STUB, 1,024 size
mismatches, 81 near matches and five semantic-only PROVEN results. Four server
source claims remain unverified despite the identical existing image. These
are stored working-tree verdicts during source reorganization, not a new
function-verification batch. No rebuild or full gate was run by this refresh.

Current source work continues in [the tracker](TODO.md); earlier handoffs below
are historical. Receipts: `.scratch/data-readme-refresh-20261025/`.

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
