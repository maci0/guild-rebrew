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

The full goal remains ACTIVE and incomplete. Latest user priority is the TL
no-source inventory: map evidenced roles/names/counterparts and reconstruct real
shared C bodies. A parallel native-mapping/reconstruction pass was explicitly
authorized. Prefer new source bodies over repeated exhausted shape searches.

Goal64 adds inferred rd_FillSupermapQuad at TL4be000 / Gold4bd760: one ordinary
C89 definition matches all485 native executable bytes per client, all ten
operands and four literal uses. Thirteen rejecting controls per target pass.
The native sampling bias is double0.9; complete literal auditing rejected an
initial0.5 draft despite masked instruction agreement. Eleven following NOPs
remain alignment. Byte255 and integer255 independently skip their respective
planes; original unchecked sampling and write order remain. Source placement
and role name are inferred, backing-map ownership unproven. No new storage or
speculative map/vector type is created.

Gold4bd710 now shares the existing TL4bdfb0 projection body, with four evidenced
map offsets guarded for Gold. Complete67/79-byte bodies and callee operands
match; wrong-callee controls reject. client_scene_transform.h reconciles its
object/float-vector access contracts across the provider and current C callers.
All eight old strong contexts pass; the existing weak102-byte context retains
identical code, fixups and literals. Broader455350/scene contracts remain open.
Newly matched game bytes are TL485 and Gold564. Earlier native-only mappings,
libraries and alignment are separate from that gain.

Goal63's65 native-only name/size/note identities remain:55 TL functions covering
150636 inventory bytes and ten large Gold counterparts. None claims a source
provider or byte verdict. The7.1M-signature FLIRT scan remains inspection-only;
selected fortify/check-fail prefix hits are rejected, and DirectX/provider
attribution still requires whole-body/operand/raw-map evidence. See the Goal63
naming table and saved dossiers rather than repeating the scan.

Next: continue tractable mapped no-source bodies. rd_AllBauplatzToSupermap's
260-byte shared algorithm remains scratch-only at123 matching bytes; array/
record shapes, Op/O1 and G3/G6 probes do not justify production flags. Its direct
wrapper needs pointer/count contracts first: both existing enum providers are
void, while all fourteen native callers consume their count. Preserve the
returned slot count including null holes. Gold callback58f780 ends after250
code bytes plus6 NOPs; stored256 is only a future selected-extent review lead.
Do not promote it from counterpart evidence alone. Full review is under
.scratch/goal64/review; compiled proofs under quad/production-proof.json and
projection-proof.json. Main-body failed probes are retained for bounded reuse.

All-target lint has zero errors/warnings and data has zero conflicts/multiple
definitions. The fresh server gate passes: all286720 raw bytes are identical,
imports/data/relocations/layout and Wine load/exports pass, and code generators
remain aligned. All8478 earlier identities/extents and6053 strong statuses are
preserved. Current accounted TL text is1121839/2491370 bytes; native game-byte
gain is485 and TL no-source count is1214. Both complete client raw-file/data proofs
and linked helper providers remain open. No upstream tooling defect was
established in Goal64. Actual bugs still require upstream fixes and regression
checks; missing capabilities belong in upstream docs/IDEAS-GUILD.md.

Do not resume exhausted Goal58/59 court arithmetic/cursor, queue/office/camera,
timer-loop or Goal62 runner searches without new evidence. Preserve OWN-before-
OTHER stateful query order. Prior packet-pointer checkpoint2eaccc18, timer and
mapping evidence remain in docs/TODO.md and their scratch receipts. Every goal
completion criterion above still applies.

## History

[Archived checkpoints](docs/goal-history.md) preserve the previous goal file in
full. They are historical evidence, not current status or instructions. Keep this
file concise: replace the current continuation when it changes; write detailed
chronology to `docs/TODO.md` and evidence to its owning document.
