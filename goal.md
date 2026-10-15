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

The full goal remains ACTIVE and incomplete. Goal58 reconstructs one shared
court decision callback TL4df1b0/Gold4dd960, covering seven native action cases.
Its two-argument declaration is canonical in event_callbacks.h. Native name/TU
ownership remain unproved. Correct source explicitly sequences OWN query before
OTHER. Gold preserves its two measured differences: alternate choice0 versus TL2,
and signed16-bit window width at+8 versus TL32-bit +12.

The production byte compare remains STUB (TL2536) / SIZE_MISMATCH
(Gold2532/native2528), with blockers retained. All372 bounded native/C x86/VEX
service-trace cases pass, including default tags, participant gates, selectors,
timeouts and buttons. This is not universal equivalence, PROVEN or raw-link
proof. The byte-near scratch2531/2536 and2523/2528 expressions are rejected:
they reverse stateful query calls. Physical case order and six scheduling bytes
are resolved. The remaining two-byte ECX copy is not fixed by the measured
arithmetic/temporary forms or final comma-expression control. Stop that family
without new native/TU evidence; never restore the incorrectly ordered expression.

Two native entries are admitted at2536/2528 through reviewed digests. Native
code, seven-entry switch tables, next prologues and all branch destinations are
checked independently. All8404 old identities/6048 strong statuses survive;
totals8406/6048. All26 old strong affected contexts pass, and the old TL transfer
callback remains799/native801 with identical compiled bytes/fixups. Two existing
validator-field type bindings are refreshed with unchanged20-byte layout.
No storage, type layouts, compiler flags, assembly or filler is introduced.

There are ZERO new matched game bytes in this checkpoint: TL697456,
Gold383347. Libraries390163/9732 stay unchanged. Padding33615/23499 includes
1/2 newly classified existing alignment bytes. Accounted text1121234/2491370
(CLI45.0%) and416578/2006532 (CLI20.7%); no-function103160/75531.
Keep source/discovery work separate from game byte gains. All-target lint0/0,
data0conflicts/duplicate owners and type checks1020structs/0findings hold.
Selected15 contracts are clean; broader findings258/1479/968 and unknowns
305/4082/2607 remain across server/TL/Gold. Both client raw images and
initialized-data verification remain open.

Fresh Docker server gate preserves316function/652data matches, imports/exports/
resources/relocations/layout/Wine and all286720 identical raw bytes, SHA-256
3cc2ce9049e41ab6d0eea042df4966fbf57e5e27c67fb923e81709d2683609d1.
Current receipts/replays are .scratch/goal58/{decision-boundaries,decision-traces,
query-order-control,preservation,contracts-focused,contracts-final-all,
scope-promote,lint-final,data-final,status-final,types-*}.json and server-gate.log.
Read docs/TODO.md Goal58 and C-shape notes before retrying. No upstream change
this turn; upstream8e897442 remains pushed. Preserve all23 foreign upstream WIP.

Next inspect larger unmatched client bodies through todo/native/library evidence;
the unreconstructed event runner4e5a00 has saved native/Kuna inputs. Existing
TL364-byte third-slot provider4dfba0 has Gold counterpart4de340, but helper twins,
global binding and prototype/provider contracts need reconciliation before import.
Keep Goal57 validators and Goal56 character work intact. Do not repeat exhausted
camera221/218, separation720/745-vs744, office17-byte, queue733/735 or low-poly
LOD probes without new evidence. Broader callback/D3 contracts, Goldfb9900
ownership, client raw builds and faithful discarded server inputs remain open.

## History

[Archived checkpoints](docs/goal-history.md) preserve the previous goal file in
full. They are historical evidence, not current status or instructions. Keep this
file concise: replace the current continuation when it changes; write detailed
chronology to `docs/TODO.md` and evidence to its owning document.
