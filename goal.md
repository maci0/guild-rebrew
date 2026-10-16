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

The full goal remains ACTIVE and incomplete. Goal67 adds shared AttachAnimLooped
at TL40eff0 / Gold40e0e0: 454 executable game bytes per client, followed by ten
alignment NOPs in each retained 464-byte native span. Complete proofs validate
all fifteen operands, three literal uses and 25 rejecting controls per target.
Eighteen bounded cases per client (72 native/compiled executions) assert exact
options, waiting slots, paths, service order, diagnostics and callback writes.
Real renderer execution and arbitrary input safety are not established.

The native callback reads three nullable draw-data pointer cells at stride0x7c,
first offset0x484 TL /0x178 Gold. Preserve the resumed-path null-object behavior,
the otherwise unused resolved-name copy, and full-kind==1 test before narrowing
mode. The existing D3_ANIMATION_OPTIONS layout remains twelve bytes by value;
its stable ID was rebound after moving the attachment-service prototype to
canonical d3_animation.h. All41 old contexts across fifteen files preserve full
code/fixups/literals, including the existing weak TL ch_Updatelowpoly. All6063
prior strong statuses retain their exact value. No assembly, storage or compiler
flags were added. Helper434970 /435550 source/link providers remain unresolved.

TL no-source is1211 /1206802bytes, down from1212 /1207266. Newly matched game
code is454 per client; ten additional accounted bytes are alignment. Accounted
TL text1123524/2491370 =45.096633...%; the deliberate floor-to-one-decimal display
remains45.0%. This includes libraries and padding, independently of game progress.
All-target lint is clean, data has zero conflicts/duplicate owners, and a fresh
server gate passes with all286720 raw bytes identical, matching data/imports/
relocations/layout and successful Wine load/export checks.

Larger parallel work remains distinct from adopted progress. cm_ExCreateGeb
TL4cc820 /Gold4cbca0 has a full838-byte scratch match with44operands, eight literals
and81 rejecting controls per target. Do not adopt it with contradictory factory
prototypes: command.c declares byte/ushort but spiel.c defines int/int and reuses
full argument slots in the independently attested macro. Compatible int/int
caller emits842; narrowing the factory unchanged fails its assembly operand.
Native low8/low16 consumption does not uniquely recover original formal spelling.
Resolve allocator, placement-result/callback/iterator contracts and Gold twins
before sharing the server's lookup/allocation/reply tail with client scene work.

amt_ExecGebaeudeBauen remains543native/527compiled after bounded trials;
ls_LoadCharacter remains1915native/1904compiled with strrchr last-underscore
semantics and pointer/layout debt. CHARACTER allocation0x244 differs from Figure's
0x228 accessed view and from the D3 allocation. Newly found helper515540 /Gold511df0
has151/146 executable bytes plus9/14 NOPs, currently swallowed by preceding
5153f0/511ca0 inventory spans496; preserve their existing331-byte matches when
reviewing admission. Initial helper source matches but needs full proof, canonical
global views and source/type/provider review before integration. Keep all scratch
results separate from STATUS; reports are in .scratch/goal67.

The first190-byte cutscene command has an allocator-zero path that reaches a read
at address8 in BOTH clients. Do not add a graceful failure return or conflate it
with the adjacent111-byte handler or SERVER37-byte ID/timestamp function. Prior
Goal66 adds760 bytes per client; Goal65 SaveBMP8 adds441 TL. All corresponding
proofs and earlier findings remain in docs/TODO.md and docs/naming_conventions.md.

Continue tractable no-source bodies and the new helper admission, reusing Goal63
mapping/FLIRT/Kuna/native evidence. Do not restart exhausted court/queue/office/
camera/timer/runner or recent bounded families without new evidence; preserve
OWN-before-OTHER query order and discarded server inputs. Both clients' complete
raw-file/data/provider proofs and broader source contracts remain open. Every
completion criterion above still applies.

## History

[Archived checkpoints](docs/goal-history.md) preserve the previous goal file in
full. They are historical evidence, not current status or instructions. Keep this
file concise: replace the current continuation when it changes; write detailed
chronology to `docs/TODO.md` and evidence to its owning document.
