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
6. Refresh coverage through `rebrew coverage build`; never maintain a second
   progress store. Record only current evidence and concise next steps here.

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
recovery of discarded server inputs remain open. Historical byte matches do
not establish original source or complete client images.

The fresh pinned gate (`REBREW_DEBUG_INFO=OFF uv run --frozen scripts/gate.sh`)
passes: all286720 raw server bytes equal the reference,316 game functions and652
data comparisons pass, with import, relocation, toolchain and Wine checks.
The plain server and Processor Pack client images are present. All-target lint
is0/0; all three data inventories have zero conflicts and duplicate definitions.

Scene destruction and unlinking remain shared: both wrappers are32 bytes and
both unlink helpers are unmasked EXACT154. Draw-data cleanup TL439d80/Gold43cd80
now shares one C89 d3_CleanupObjectDrawData definition using the canonical types
and allocator header. Both full137-byte bodies and all six operands agree;
four shifted-callee controls reject. Keep the counted loop, unconditional
part-three cleanup, pointer/count reloads across calls and final context clear.
The source follows native VA order. Name and unit placement remain inferred;
draw-part providers439c90/43cc90 remain separate and Gold43cc90 is unsourced.
The two unowned standalone cleanup sources are retired through reviewed rehome.

All129 affected comparisons preserve byte results and prior binding proofs;
Gold cleanup gains a tracked-free binding. All6022 previous strong statuses and
the identity set remain. Six D3 compiler-backed sizes, extents and offsets are
unchanged. Receipts: .scratch/goal41/cleanup/{production-native-proof,
object-native-proof,scope-preservation,preservation}.json,gate-pinned.log,
lint-final.json,data-*-final.json andtype receipts in .scratch/goal41/.

Upstreamf2dbe476 fixes missing mov-to-memory immediate references in section,
function and reachable-code scans. Two regression cases fail before;112 focused
and12032 full-suite tests pass afterward. Native xrefs now find callback stores
TL5108f7->5107f0 and Gold50d457->50d350. Required commit checks pass. Feature gaps
remain in upstream docs/IDEAS-GUILD.md; bugs must be fixed directly upstream.
Receipts: .scratch/goal41/upstream/.

Next: finish the remaining evidenced D3 helper twins and reconcile their
contracts/providers before integrating d3_DisposeObject. The attested disposal
name has a void(D3_OBJECT*) contract; its placement is inferred. Scratch bodies
match full450/637 bytes but are not adopted: their three separate Gold globals
contradict native evidence for one fb9900 record. Use an extern prefix view with
no allocation or complete-extent claim; full owner/extent remain unknown.
Gold draw-data+968 caches kontext and is pointer-valued. Constructor, assignment
and callback evidence supports draw-data offset0 as a nullable one-object void
callback, and a cleanup bit immediately below darstellungsflag. Preserve total
bit widths and all existing layouts. Reconcile assignment/caller declarations
and prove all native operands before adoption. Reviews and exact evidence are
saved in .scratch/goal41/committee-*.md andHANDOFF.md.

Preserve prior chain, building destructor, lighting, display-counter and inventory
repairs; detailed checkpoints are in docs/goal-history.md anddocs/TODO.md. Do not
repeat exhausted animation/production probes without new evidence. Keep the
attested cm_ExProdObjekt unit: its earlier split changed30085 raw bytes and32
data rows. Continue native source-unit/type/data/provider work and both raw
client builds; the server gate alone cannot complete this goal.

## History

[Archived checkpoints](docs/goal-history.md) preserve the previous goal file in
full. They are historical evidence, not current status or instructions. Keep this
file concise: replace the current continuation when it changes; write detailed
chronology to `docs/TODO.md` and evidence to its owning document.
