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
   the complete image. Run `scripts/gate.sh` before every commit. Client changes
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

## Current continuation — 2026-10-14

The full source-fidelity/three-image objective is unfinished. Client raw links,
complete data verification, unknown function ranges and faithful discarded-server
source remain open. The historical server layout still contains explicitly
inferred discarded inputs; raw equality alone does not prove original source.

Checkpoint e24b9311 is committed and pushed: Rebrew 3 metadata/source migration,
obsolete adapter removal, whitespace cleanup and the first reviewed order edits.
The pre-reorganization audit preserves all 8,376 function identities/bindings/
extents and every non-comment token in 3,836 migrated C/header files.

Extracting cm_ExProdObjekt preserved its complete 993-byte object match but broke
raw server layout: 30,085 file differences, 16 extra virtual text bytes and 32
DRIFT data rows. The identical body and both identities are restored to command.c
through the locked metadata API. The rebuilt raw file again equals all 286,720
reference bytes; all 316 functions and 652 data comparisons pass, with zero
relocation differences and Wine exports/load passing. The gate still fails lint.
Do not split an attested TU merely to remove a conflicting target-order warning.

Six acyclic units now have reviewed order changes: character.c, msx.c,
server_stats.c, sonnenstrahlen.c, GOLDTL.fcn_00404a00.c and server.c. The first three
retain 36 client matches and the existing lowpoly mismatch. The latter three
retain 45 complete function comparisons across their actual target contexts.
Source-body audits preserve every complete definition. A new full server gate
finishes after those changes: raw identity, 316 functions, 652 data rows and Wine
checks pass. Only lint fails (32 warnings: 31 order findings plus scaffold drift).
Receipt: .scratch/goal28/gate-final-current.log.

All five additional migration regressions are repaired. Two shared providers now
use canonical network declarations and the three-float view rather than TL raw
addresses; Gold validates all eight data operands. TL retains its two matches.
The ambiguous random-helper call and production dialog self/callback pointers
are explicitly bound to the correct identities. IsRandomSecondChoice and
ConfirmProductionSelection are inferred names; independent Boolean/Lua functions
are preserved. The random helper accepts the observed unused event argument and
retains its complete 18-byte match. Current helper/caller receipts are in
.scratch/goal28/. VECTOR3 restores the already documented canonical type name;
the DISPLAY_COUNTER stable ID is rechecked/rebound after header changes. These
are accessed views, not newly established storage owners.

Upstream d37f4a07 repairs provider selection and metadata-only lint locations;
6e8dbd5e repairs split dependencies/callback-table ownership; 2468a895 repairs
quoted-header rebasing. Upstream 4650b824 repairs conditional brace fragments that
swallowed following function definitions and corrupted scope inventories. Its
isolated full suite passes 11,800 tests with 36 skips, 332 focused tests and full
commit/push hooks. Remote main contains it. The canonical checkout has a separate
live CLI refactor; preserve its changes. The temporary rebrew-goal28-parser-check
worktree supplied frozen tooling while those measurements ran; all finished and
the checkout is removed. Both repositories again retain only main. New feature gaps and TU-regression evidence are recorded
in upstream docs/IDEAS-GUILD.md; that latest documentation edit is pending commit.

Current unresolved lint is concentrated in five units with conflicting target
orders: command.c, alchemistry_logic.c, friedhof_logic.c, spiel.c and loadsave.c.
Last frozen lint has 31 W030 findings plus one generated instruction drift
warning. The display-counter rebind clears its stale-evidence warning. Refresh instructions from the validated
upstream once the live CLI refactor is stable, preserving the local rules. Data
conflict scans finish with zero conflicts and duplicate definitions in all three
targets (664/293/256 managed data rows). Retry the earlier
27 compiler timeouts and reverify the header/type dependents before a clean
corpus claim. A passing object report is not a passing client raw link.

Independent operand reconstruction now reproduces three complete native bodies:
the two network reset implementations and TL's random-choice helper (92 bytes).
Every one of the eleven deliberately displaced bindings rejects equality.
Receipt: .scratch/goal29/bound-bodies/results.json. The float setter still has an
unresolved call and is excluded from that complete-operand claim. A fresh frozen
all-target corpus check is running with four compiler jobs; its 3,973 source and
configuration input hashes are unchanged. Do not describe it as finished until
.scratch/goal29/corpus-current.json contains its terminal report.

The complete shared he_RunProduktion candidate remains SIZE_MISMATCH (4,016 vs
3,816 bytes) in both clients. Its 456 bounded native/model runs reach all 66 call
sites but do not establish exhaustive equivalence or byte identity. Original
event allocation, types/prototypes and native source placement remain unresolved;
the two 450-byte initializer bodies retain RELOC. Preserve the prior evidence in
.scratch/goal23/ through goal26 and the respective codegen documents.

Next: verify all changed type/header
users and complete operand proofs with rejecting controls, and refresh coverage.
Resolve remaining native source-unit/order conflicts without changing attested
server composition. Then recover the production callback's native types/layout,
genuine discarded server inputs, client-only code and both full raw client links.
Keep the goal active until the original completion criteria all hold.

## History

[Archived checkpoints](docs/goal-history.md) preserve the previous goal file in
full. They are historical evidence, not current status or instructions. Keep this
file concise: replace the current continuation when it changes; write detailed
chronology to `docs/TODO.md` and evidence to its owning document.
