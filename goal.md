# Goal: one faithful source tree, three byte-identical binaries

Reconstruct the shared C source tree the original developers most likely used,
and build `server.dll`, `Europa1400Gold_TL.exe` and `Europa1400Gold.exe` with
100% raw-file byte identity to their references. Both source fidelity and binary
identity are required. A matching binary assembled from fabricated source does
not complete this goal.

This is the durable objective for `goal-dd7dd2dd-8cde-4e14-a043-8674d4ec5631`.
If session goal state is lost, restore the objective from this file. Read
[AGENTS.md](AGENTS.md) for project rules and the relevant Rebrew skill before work.

## Priority and scope

1. Preserve and complete `server.dll`, including faithful reconstruction of
   discarded original source that affects link inputs and relocation reservations.
2. Reverse `Europa1400Gold_TL.exe` as the primary client workstream.
3. Validate `Europa1400Gold.exe` from the same source tree and verified related
   imports. Reverse unique Gold code when needed; do not reconstruct shared logic twice.

Keep one definition of shared game logic, with one managed identity per target.
Use target-specific code only where native evidence supports a difference.
Source placement and headers follow attested `__FILE__` paths, module conventions
and actual cross-TU use. Mark inferred names, layouts and organization explicitly.

## Completion criteria

All criteria must hold against current source, headers, compiler inputs and images:

- All three targets build reproducibly from the unified tree using their pinned
  toolchains. The raw linked files equal their references byte for byte, including
  headers, sections, imports, exports, resources and relocations. Postlink repairs
  cannot substitute for raw-link identity.
- Every reconstructed game function is EXACT in its object or verified as linked
  EXACT in the raw image. Library code/provider evidence is accounted separately.
  Every data byte and symbol placement is verified; unresolved owners stay explicit.
- The server passes `scripts/gate.sh`, including raw-file identity, linked EXACT,
  data/import placement and Wine load/export checks for `Init` and `Exit`.
  Its `.text` VirtualSize is `0x22846` and its import table matches all 100 entries.
- Both clients pass equivalent full-image checks against their own references.
  The current server gate alone does not establish client completion.
- Shared logic has no drifting duplicate bodies. Types, declarations, storage
  owners and native operands are reconciled across targets. No fabricated logs,
  placeholder calls, padding or fixups remain to manufacture agreement.
- All-target lint has zero errors and warnings, required checks pass, and the
  naming, native evidence and continuation documents are current.

Object RELOC, NEAR_MATCHING, PROVEN, bounded fixtures, coverage percentages and
historical green builds do not establish completion. Report file agreement,
accounted text, game reversing progress and stored data verification separately.

## Non-negotiable constraints

- C89 under MSVC6. No naked functions, `_emit` or inline assembly unless positive
  native evidence establishes original assembly at that site. A difficult match
  is insufficient evidence. Preserve reviewed assembly provenance where applicable.
- Run CL/LINK/LIB inside the configured Docker images: plain SP5 for the server,
  Processor Pack SP5 for both clients. Use the project's pinned environment;
  set `REBREW_DEBUG_INFO=OFF` for link checks. No host Wine/compiler fallback.
- Check library attribution before implementing a function. Reuse linked stock
  CRT and available library sources/providers; do not reimplement stock library
  code as game progress or patch third-party archives to force a match. Any
  evidenced original vendor changes must be pinned and reproducible.
- Preserve one storage owner per global and canonical subsystem declarations.
  Interior views, compiler literals, layout spans and imports are distinct facts.
  Never infer allocation ownership from an extern, address proximity or coverage row.
- Follow [naming_conventions.md](docs/naming_conventions.md). Attested spelling
  wins, including original errors. Use established module prefixes and record
  inferred names. Rename through `rebrew source rename`.
- Keep shared types in their owning headers; preserve byte-sensitive declaration
  order. Bind stable type IDs through `rebrew types bind`, separating C layout
  from evidenced allocation/stride extent. Resolve duplicate-symbol findings.
- Never hand-edit managed function, data, type or source-evidence stores. Use
  Rebrew CLI/locked APIs. Preserve unrelated changes and prior verified matches.
- Never weaken a gate, baseline, extent or binding policy to hide a regression.
  Do not restore invented logging calls or relocation reservations to recover bytes.

## Work loop

1. Read `rebrew todo --json` for the selected target and address-keyed findings
   before repeating experiments. Check existing CLI help/tools before writing helpers.
2. Check libraries, native bodies, callees and operands. Compare available
   decompiler seeds, including Kuna, against native evidence; then write real C.
3. Test/diff after source changes. Verify related imports against each destination
   before promotion. Use matching searches only after ordinary edits stall.
4. Reverify affected callers and all target contexts after shared-header, type,
   ownership or declaration changes. Known-binding checks remain enabled.
5. When matching measures disagree, compile an isolated raw native link and measure
   the complete image. Run `uv run --frozen scripts/gate.sh` before every commit. Client changes
   also require client-specific validation. Keep failed checks visible.
6. Read current coverage through `rebrew status` and the live coverage view.
   Use `rebrew coverage export` for an explicit offline snapshot; never maintain
   a second progress store. Record current evidence and concise next steps here.

Use the existing evidence homes: names in `docs/naming_conventions.md`; C shapes,
allocation and exhausted levers in their respective codegen documents; measurement
and process traps in `docs/measure-traps.md` and `docs/workflow-traps.md`; session
attempts and receipts in `docs/TODO.md`. Probes belong in ignored `.scratch/`.
Do not rerun exhausted probes without new evidence.

Fix Rebrew bugs in `/home/maci/Desktop/Projects/relumea/repos/rebrew` with a
reproducing regression test and a passing upstream suite before returning to
reversing. Record every missing capability immediately in that checkout's
`docs/IDEAS-GUILD.md` with the problem, proposed capability and replay evidence.
Keep binary-specific evidence in this project. Publishing and live sync require
explicit authorization; this file does not grant it.

## Current continuation — 2026-10-15

The full source-fidelity/three-image goal remains unfinished. Both raw client
images, complete data ownership/verification, unknown code ranges and faithful
recovery of discarded server inputs remain open. The next coverage work should
prioritize newly matched TL bytes and proven library gaps; source consolidation
and validation must be reported separately from coverage gains.

The fresh pinned server gate passes (.scratch/goal43/gate-refreshed.log): all
286720 raw bytes equal the reference, with316 game/652 data comparisons, imports,
relocations, toolchain and Wine checks. Both required compiler images are present.
All-target lint is0/0. All three data inventories report zero type conflicts and
duplicate definitions. Earlier gate failures from generated skill drift remain
recorded; refreshed instructions pass without weakening the gate.

TL439b30 / Gold43cab0 now share one inferred d3_RemoveObjectFromList definition
before draw-data cleanup in d3_object.c. Both complete112-byte bodies and all12
operand sites agree; ten wrong-binding controls reject. The two standalone
providers are retired after locked rehome and owner checks. Existing133-byte
auxiliary cleanup,137-byte draw cleanup,154-byte hierarchy unlink and32-byte
destruction helpers retain their full native proofs and rejecting controls.
Their names/placement remain inferred; separate callees/providers stay explicit.

A narrow inferred d3_camera.h now supplies the canonical pointer declaration for
TL6b8014 / Goldfc2dec and the selector. No storage owner or complete allocation
is inferred. Integer slot declarations, slot punning and four raw loads are
removed. Selector42/motion54 match completely in both clients with operand and
negative checks. The motion inputs carry floats, and the actual service's integer
return remains. Both native camera diagnostics match all53 bytes including NUL.
The embedded position wrapper4526d0 forwards its missing second argument and
retains its full23-byte RELOC result.

All262 scoped comparisons preserve byte results and prior bound operands; eight
sites gain resolved bindings. Final public-verifier batches refresh101 TL and51
Gold verdicts with the same statuses and operand evidence. All8376 pre-existing
identities, native extents and6022 prior EXACT/RELOC statuses remain. Ten reviewed
type bindings preserve established layouts after compiler checks. Receipts and
remaining contract details are in docs/TODO.md and.scratch/goal43/.

This checkpoint adds zero newly matched TL game bytes. The two user reports both
contained691740 matched game bytes/3567 functions; their seven-byte account
increase was padding. The library audit adds one target-scoped56-byte identity,
c_D3DXPlaneFromPointNormal at TL5edf50: its entire body equals stock D3DX8 without
masking, and altered-byte/shifted-start controls reject. Actual raw-link provider
selection remains unresolved. The full shared7102296-signature scan now finishes
in89.4 seconds after upstream32e846cc fixes quadratic name deduplication. Both
regression modes fail before;119 focused tests, real DirectX output preservation
and the required full upstream suite pass. The fix and signature discovery note
are pushed upstream, and their temporary worktrees are removed.

Full scan output has1967 ordinary hits and4679 ambiguous addresses, dominated by
weak cross-library patterns. Most focused DirectX hits already lie in credited
library spans; four additional complete D3DX matches retain unresolved template
aliases and are not assigned arbitrary names. Two missing CRT copy bodies at
TL64d740/658030 are each821 bytes. Both stock memcpy.obj and memmove.obj reproduce
each entire body with all46 internal fixups resolved and every wrong-binding
control rejected. Their CRT origin is recorded with provisional address-only
names; API aliases and raw-link providers remain unresolved. Internal labels and
tables are not extra functions. The existing caller retains its full184-byte
RELOC result; its unresolved API binding remains explicit.

The library audit adds1698 accounted bytes in total:1466 library functions and
390101 library bytes, with1115402/2491370 text bytes accounted (44.7706%). The CLI
truncates percentages to one decimal, so it still displays44.7%. No new matched
game bytes are claimed. All8376 original identities/extents and6022 strong
statuses remain; three new target-scoped library identities are added. Receipts
are in.scratch/goal43/. The shared/local signature discovery gap is recorded in
upstream docs/IDEAS-GUILD.md. Remaining source-backed zlib origin/provenance and
other weak signature candidates need review before any further reclassification.

The camera/client interface migration is deliberately unfinished. Reviewed
float-pointer position/rotation candidates match83/184 bytes in scratch; do not
mistake rotation's eight alignment NOPs for missing executable code. Scalar
wrappers, constructor/resource-name transports and connected declarations still
need measured reconciliation. Traversal and disposal integration remain open.
Do not describe byte agreement as complete C contract repair. Disposal's Gold
fb9900 state is one record with unknown full extent/owner, not three allocations.
Prior chain, building, lighting and inventory evidence remains in docs/TODO.md
anddocs/goal-history.md. Do not repeat exhausted probes without new evidence.

The next extent audit recovers the existing235-byte protection helper in both
clients: TL41d500 / Gold421f00 had included five trailing alignment NOPs in SIZE.
Supported tests now record RELOC; complete unmasked operand resolution and
rejecting controls independently pass. All8379 identities and6022 prior strong
statuses remain; strong statuses become6024. Newly matched game bytes are235
per client, with no new C implementation. TL game matches total691975 bytes;
accounted text becomes1115642/2491370 and still displays44.7%. Data/type stores
are unchanged. The larger735-byte TL5252d0 queue-loader experiment remains
unmatched, unregistered scratch work; its completed quick flag sweep finds no
exact result. Details and exhausted variants are in docs/TODO.md.
The fresh .scratch/goal44/gate-refreshed.log passes full server identity,
316/316 game and652/652 data checks. All-target lint is0/0 and all three data
inventories have no type conflicts or duplicate definitions.

## History

[Archived checkpoints](docs/goal-history.md) preserve the previous goal file in
full. They are historical evidence, not current status or instructions. Keep this
file concise: replace the current continuation when it changes; write detailed
chronology to `docs/TODO.md` and evidence to its owning document.
