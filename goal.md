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

The full goal remains ACTIVE and incomplete. Goal60 adds a shared texture callback
TL `443270` / Gold `447800`: EXACT 89 and RELOC 86. Its context/texture offsets,
processed bits and resource calls vary only where native evidence supports it.
The table entry is reloaded after a resource call before the processed bit is set.
Complete code/operand checks and 18 bounded cases include table replacement.

Gold's 117-byte `4360e0` provider is reconstructed in attested `d3_d3d.c` as
inferred `d3d_PrecacheTexture`, RELOC 117. Native HRESULT stores, both error logs,
device reload and draw arguments agree. Full code, all 11 operands and four
literal sites/three complete strings pass strict comparison and rejecting
controls. Eight bounded resource/error cases pass; the old EndScene retains its
44 bytes, fixups and literals. These checks do not verify a client raw link.

The name `d3d_PrecacheBuffer` is attested. Its new unsized header declaration and
alias row allocate no storage; complete extent, vertex type and owner remain open.
First registry callbacks now use inferred `EVENT_RUN(char*)`, void cdecl, with
canonical provider/registrar/setter declarations. Two actual providers retain
674/165-byte matches per target. Ten first-phase providers and both other phase
contracts remain open. TL's refresh declaration now accepts its native unused int
argument; Gold's different 113-byte implementation remains unadopted.

All 8408 previous identities/6048 strong statuses survive; totals 8411/6051.
All 38 old strong affected contexts pass, plus the three new matches. Two old
validator bindings retain their 20-byte layouts. The old transfer's 799 bytes/
fixups survive; all 372 court and 14 reset cases pass with the current event header.
All-target lint has no errors/warnings, data has no conflicts/duplicate owners,
and type checks have 1020 structs and no findings. Broader contracts still have
findings/unknowns server 258/305, TL 1476/4082 and Gold 966/2607. All 33 selected
contracts are clean and all 3989 audit input hashes are current.

New game byte gains are TL +89 / Gold +203; totals 697545/383550. Library bytes
390163/9732 and padding 33615/23499 are unchanged. Accounted text is
1121323/2491370 (45.0%) and 416781/2006532 (20.7%); no-function 102909/75369.
TL's merged inventory extent is repaired from 160 to its already matched 62,
with separate 89-byte callback and existing alignment. No source verdict is earned
from discovery. Both client raw builds and initialized-data verification remain open.

Fresh Docker server gate passes with all 286720 raw bytes identical, 316 function/
652 data matches, imports/exports/resources/relocations/layout/load checks. SHA-256
3cc2ce9049e41ab6d0eea042df4966fbf57e5e27c67fb923e81709d2683609d1.
Current receipts/replays are in `.scratch/goal60`: texture-proof.py/json,
precache-proof.py/json, event-abi.py/json, scope-promote.json, current contract/data/
lint/status/type reports, source-unit review and server-gate-current.log. Setup
errors and rejected drafts are retained separately. See docs/TODO.md Goal60 and
C-shape/naming notes before repeating work.

Upstream main/origin is 4d52a5b4, documenting the non-record typedef binding gap in
`docs/IDEAS-GUILD.md`. Its mandatory full suite passed in an isolated worktree,
which was merged and removed. All 23 unrelated upstream files preserve their
hashes. `types bind` still accepts only record definitions: target compiler width
assertions and source-contract audit do not create a managed callback identity.
Do not fabricate a wrapper struct or manually write one.

Continue the larger runner TL `4e5a00` / Gold `4e4060`, native 2033/2063.
The complete unadopted candidate `.scratch/goal60/runner.c` preserves both scans,
stateful effects and native target layouts. Default builds emit 2023/2054;
frame diagnostics 2007/2034. Those measurements do not justify adopting a pragma.
Service contracts remain incompatible/provisional, particularly packet bases,
callback registration and lighting. Reconcile them before adopting the body,
then remeasure full operands/literals and native behavior. Preserve Gold's signed
viewport words and GUI stride/count 0x2ec/768 versus TL 0x2f4/1024. Original source
spelling/TU options remain unproved; no new runner verdict was registered.

Preserve Goal58 OWN-before-OTHER sequencing and Goal59 reset behavior. Do not retry
exhausted arithmetic/cursor, queue/office/camera families without new native/TU
evidence. Client raw builds, data ownership/layout, broad source contracts and
faithful discarded server inputs remain open. Completion still requires every
criterion above, including reproducible raw-file identity for all three targets.

## History

[Archived checkpoints](docs/goal-history.md) preserve the previous goal file in
full. They are historical evidence, not current status or instructions. Keep this
file concise: replace the current continuation when it changes; write detailed
chronology to `docs/TODO.md` and evidence to its owning document.
