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

The full goal remains ACTIVE and incomplete. Goal62 repairs the packet-base
contract at TL `4c4510` / Gold `4c3ba0`: a byte-pointer base, integer entity ID
and three typed resolver outputs. Both complete 90-byte bodies and all six
operands match; eight wrong-binding controls reject. MSVC6 reuses the dead ID
argument slot for the output local itself. No pointer is written through an
integer's address in source.

The inferred `client_packet_builder.h` reaches all 42 provider/caller source files
plus the additional base-pointer consumer. Existing private object views convert
to byte access; relative offsets retain their narrowing. The global's integer
aliases and incompatible declaration are removed. Both existing `g_aed32c` rows
move their declaration home through the guarded writer, preserving names, VAs,
types and unresolved owner. No storage, data verdict or native inventory is added.
The pointer-valued `fcn_004ce740` consumer retains all 366 old object bytes and
fixups per target. Its four native calls per client have source-less callers.

Sixteen bounded native/compiled cases pass, including failures, resolver output
writes, full-width results and side effects. Clearing/reset precede resolution;
success stores the original supplied base, not a returned object pointer. All
68 previously strong selected contexts pass. Six existing weak contexts preserve
their exact old compiled bytes/fixups/literals and weak verdicts. All 8413 prior
identities/6053 strong statuses survive unchanged. Earlier timer, texture, event
phase, court and reset evidence remains in docs/TODO.md and prior scratch receipts.

Fresh Docker server gate passes all 286720 raw bytes, 316 functions/652 data
records, imports/exports/resources/relocations/layout/Wine/DirectX checks. SHA
3cc2ce9049e41ab6d0eea042df4966fbf57e5e27c67fb923e81709d2683609d1.
All-target lint has zero errors/warnings; data has no type conflicts/duplicate
owners; all three type checks have 1018 structs and no findings. Selected packet
provider/consumer/global contracts are clean and all 3993 audit input hashes are
current. Broad findings/unknowns remain server 258/305, TL 1471/4085, Gold 963/2609.
Anonymous slot-typedef audit support and non-record typedef binding remain the
upstream feature gaps recorded in docs/IDEAS-GUILD.md (23b81d46/4d52a5b4). No new
Rebrew bug or feature gap was established; active upstream work remains untouched.

This turn adds no matched game bytes. TL remains 697576, Gold 383581. Library
390163/9732, padding 33615/23499 and no-function 102878/75338 are unchanged.
Accounted text remains 1121354/2491370 (45.0%) and 416812/2006532 (20.7%). This
contract repair advances source fidelity, not reversing-byte coverage. Both client
raw builds and initialized-data verification remain open.

Prioritize the TL no-source inventory next, per the latest user direction: map
evidenced roles, names and counterpart functions, check library attribution, then
add real shared C bodies where justified. Track mapped native bytes separately
from newly matched source bytes. A parallel mapping agent is authorized.

Preserve the larger runner TL `4e5a00` / Gold `4e4060`, native 2033/2063, for later.
Unadopted `.scratch/goal62/runner.c` uses the canonical packet, timer and clock
headers and still emits 2023/2054. Resource identifiers (`4730c0` and callees),
lighting (`6b8300`) and missing provider contracts remain open. Native uses an
EBP frame of 0x248; the default TL candidate omits it and reserves 0x240. This
is not a ten-byte local patch. Previous /Oy- diagnostics do not recover original
TU options or justify a production pragma. Keep actual native operands and
source/TU evidence ahead of shape search; misaligned-size binding conflicts are
not callee-identity proof.

Preserve both participant scans, stateful calls, native redundant tests, Gold
signed viewport words and GUI stride/count 0x2ec/768 versus TL 0x2f4/1024.
Preserve Goal58 OWN-before-OTHER sequencing and Goal59 reset behavior. Do not
repeat exhausted arithmetic/cursor, queue/office/camera or timer-loop probes
without new native/TU evidence. Original identifiers, allocation owners and source
placements remain inferred wherever the evidence has not established them.

Current receipts/replays are under `.scratch/goal62`: packet-proof.py/json,
weak-preservation.py/json, verify-scope.py/scope-promote.json, current lint/data/
contracts/types/status, native xrefs, guarded data plans, runner measurements and
server-gate-current.log. The canonical writer's refusal of incomplete include
contexts is retained, without a local tooling workaround. Client data/storage,
broad source contracts and faithful discarded server inputs remain open. Every
completion criterion above still applies.

## History

[Archived checkpoints](docs/goal-history.md) preserve the previous goal file in
full. They are historical evidence, not current status or instructions. Keep this
file concise: replace the current continuation when it changes; write detailed
chronology to `docs/TODO.md` and evidence to its owning document.
