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

## Current continuation — 2026-10-16

The full goal remains ACTIVE and incomplete. Preserve earlier character,
loader, animation, allocator, action and logical-reset work. Both client raw
images/data ownership, broader contracts and faithful discarded-server inputs
remain open. Read docs/TODO.md Goal56 for the bounded integration and receipts.

Goal56 adds shared character-script registration (TL40e1a0/Gold40d270,
RELOC1033 each), WalkToDummy (TL40cae0/Gold40bbc0,RELOC185 each) and the TL
three-byte PreloadSitMesh callback40dac0 (EXACT3). One C89 definition per
logical function serves both clients. The registration home/name is inferred;
the walk and camera names are native diagnostics. MoveCharacterCamera remains
SIZE_MISMATCH at221/native218 in both clients; its blockers, failed source
shapes and read-only flag controls are preserved. No production flags changed.

Canonical script callback, camera adapter and allocator-membership declarations
are reconciled over the participating46 names. Full native proof covers five
strong production bodies,2439bytes,270 operand sites and180 rejecting controls.
The Gold PreloadSitMesh destination49dee0 remains Lua LIBRARY default_panic;
three-byte equality cannot establish folding/provider identity. Its unresolved
registrar operand is a comparison hypothesis, not a new managed game binding.
No fabricated storage, type layout, assembly or padding was introduced.

Upstream55b4f436 records that logical callback/address distinction in IDEAS.
843d70a2 adds explicit reviewed missing-function admission with atomic/digest
checks and regression tests;72a19318 repairs help/summary integration;
af9b30c2 documents the public-surface/digest change. Full upstream push gate
passes. Main contains those commits locally/remotely; completed owned worktrees
are removed. All23 unrelated upstream accounting edits remain unstaged and
preserved, including reversible merges of the overlapping docs. Do not discard
or commit that work. Project rules already require upstream fixes and IDEAS.

Six reviewed predecessor extent repairs admit five real native callbacks,
including the three-byte stub missed by default discovery. All8394 old source
identities and6040 strong statuses survive; current totals8401/6045. Data, types,
source/config stores and compiler inputs are unchanged. Native row order,
fields and history survive. Every affected target context is remeasured with
the final upstream tooling; the server gate restores linked EXACT afterward.

New matched game bytes: TL+1221 ->695536, Gold+1218 ->380797. Libraries
390163/9732 and padding33605/23492 are unchanged. Accounted text is
TL1119304/2491370 (CLI44.9%), Gold414021/2006532 (CLI20.6%). This is progress
in matched game bytes, separate from libraries, cleanup and validation.
All-target lint0/0, data0conflicts/duplicate owners, all three type checks
1020structs/0findings. Selected46 contracts have zero findings with current
input hashes; broader contracts retain258/1489/973 findings and304/4085/2600
unknowns across server/TL/Gold. That broader audit has no full before-baseline.
Both clients still have zero verified initialized-data bytes and no raw image.

The server gate passes316function/652data checks and all286720 raw bytes
(SHA-2563cc2ce9049e41ab6d0eea042df4966fbf57e5e27c67fb923e81709d2683609d1),
plus import/export/relocation/layout and Wine load/export checks. Actual Docker
compilation works; the initial allocator timeout is retained as failed evidence.
Current receipts/replays are .scratch/goal56/native-proof, preservation,
contract-summary/contracts-focused, final scope/lint/data/type/status, guarded
inventory plans, native/Kuna/library inputs and server-gate.log.

Next select larger unmatched client bodies through todo/native/library evidence.
TL402d00 separation probes720/745 versus native744 stay scratch; read the
address-keyed C-shape notes before retrying. Do not repeat exhausted camera
221/218, low-poly allocator LOD, office17-byte or queue733/735 probes without
new evidence. Camera/list/disposal contracts, Goldfb9900 ownership/extent,
client raw builds and discarded server inputs remain open.

## History

[Archived checkpoints](docs/goal-history.md) preserve the previous goal file in
full. They are historical evidence, not current status or instructions. Keep this
file concise: replace the current continuation when it changes; write detailed
chronology to `docs/TODO.md` and evidence to its owning document.
