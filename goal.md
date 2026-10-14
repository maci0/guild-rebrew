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

## Current continuation — 2026-10-15

The full source-fidelity/three-image objective is unfinished. Both raw clients,
complete data ownership/verification, unknown code ranges and faithful recovery
of discarded server inputs remain open. Inferred server inputs do not become
original source merely because the raw DLL matches.

The fresh server gate passes: all286720 raw bytes equal the reference,316 game
functions and652 data comparisons pass, and library/import/relocation/Wine
checks pass. The plain server and Processor Pack client images are present.
All-target lint now has zero errors and zero warnings. The single130-byte
ahm_ProcessEntityChain body and its packed private type now precede
gm_GetFieldByType in command.c; all three identities follow via CLI rehome.
The table keeps its storage position. Ownership and name remain inferred,
with no direct native source-path reference in the body.

All102 comparisons across command/alchemy and the three targets preserve
their results, including91 byte matches; only compiler-local labels renumber.
All three complete chain bodies agree after resolving their sole operand at+33
to SERVER1002c5a0,TL68ab88,Gold60bf20; shifted-table controls reject. This
verifies the operands, not full client linked data or its provider. Receipts:
.scratch/goal36/move-comparison-audit.json,chain-native-proof.json,
lint-chain-move.json andgate-chain-move.log. The server map preserves the
ca00/ca90 sequence with the chain now in command.c.obj; it is a reconstructed map.

Seven false TL source bindings are retired after native Kuna review:
57c7b0,5974e0,5d6030,4c35f0,4b0220,44a120,422150. Their native inventory,
extents and failed-comparison history remain. Actual client destruction
TL4cbc90/Gold4cb100 now shares the server command.c definition. Dynasty
initialization TL4adcd0 has a matched body but remains separate. Factory TL5043d0 is
identified without a source provider: the server seed emits1050 versus1488
native bytes. Its SERVER assembly is guarded; the client branch uses C memset.
Four stale SERVER failure rows outside the image and two retired-source flag
overrides are removed; all6020 prior strong claims remain and data is untouched.
Receipts: .scratch/goal34/identity-retirement.json andadditional-identity-retirement.json;
.scratch/goal35/cleanup-preservation.json andforeign-server-orphans-before.json.

Upstream provider/header/parser/dossier and mixed-target data-scope repairs are
committed and pushed. Latest6173db1d converts malformed remote compile URLs
to typed failures (12 failing-before cases,83 focused passes);7e82dbcd protects
VERIFIED data during orphan cleanup (two failing-before cases,324 focused
passes). Required commit checks and full push suites pass. Default project prune
protects all46 earned data rows and selects nothing. Both repos retain only main.
Upstream IDEAS-GUILD.md records safe identity retirement and source-unit audits.

Preserve earlier verified integrations and evidence: shared lighting with17
current comparisons and native operand controls (.scratch/goal31); pristine
stock __un_inc attribution and retirement of its incorrect C copy; unused year
COMMON removal with all three72/72/56-byte bodies intact, and corrected Gold
gm_FindSlotById extent72 (.scratch/goal33). The full frozen baseline corpus has
zero game compiler errors and no lost checkpoint matches; it is historical,
not proof of complete client images (.scratch/goal29/corpus-current.json).
TL412d30 StartObjectTransformAnimation remains NEAR230/280:96 bounded VEX
cases are not a byte/exhaustive proof, and its callee/original unit remain open
(.scratch/goal32). Shared he_RunProduktion remains4016/3816 in both clients;
its456 bounded runs and66 reached call sites do not establish byte identity.

The two unused dispatch typedefs and unused table declaration are removed from
alchemistry_logic.c. All25 current comparisons retain their results; a fresh
full server gate still passes. Two stale TL inventory extents are corrected:
4186c0 from47 to5 (external tail jump plus eleven padding NOPs), and571720
from4160 to335 (complete verified body ending immediately before the production
callback). All6337 inventory identities and6020 strong claims remain. Existing
5/335-byte source comparisons pass; their metadata sizes were already correct.
CU recommendations now run, but their largest groups contain thousands of
functions and do not establish ahm_ResetEntityState ownership. Do not apply
those bulk merge suggestions as native source evidence. Receipts:
.scratch/goal37/preservation.json,inventory-*-repair.json,recommend-summary.json
andgate-alchemy-cleanup.log. The selected inventory-edit CLI gap is recorded
as upstreamf03077b5; its required commit and full push checks pass, and it is pushed.

The building destructor now has one C89 body at SERVER1000f680,
TL4cbc90 and Gold4cb100, preserving native client renderer extras and server
logging. It uses the same backing-object field view in all three targets.
Both complete265-byte client bodies match with all34 operand sites resolved;
30 shifted-destination controls reject. All79 command comparisons retain
their byte results, including75 byte matches, and all6020 strong statuses stay.
The unowned numeric duplicate is removed. The final full server gate passes;
all-target lint is0/0 and all three data inventories have no type conflicts or
duplicate definitions. Client helper providers and full client data verification
remain open. Name and local spelling are inferred. Receipts:
.scratch/goal38/destroy-native-proof.json,comparison-preservation.json,
preservation.json andgate-destroy-final.log. Upstreamb1a5de80 records the
missing all-target data inventory command; its push checks are running.

Next: unify the evidenced query, child-removal and building-cleanup helpers,
repair the Gold resource destructor's byte return, and get direct native
unit/caller evidence for the distant ahm_ResetEntityState. Keep the attested cm_ExProdObjekt TU: its
previous split changed30085 raw bytes and drifted32 data rows. Recover genuine
discarded server inputs, finish source-unit/type/data/provider evidence and
client code, and build both raw clients. Keep the original goal active.

## History

[Archived checkpoints](docs/goal-history.md) preserve the previous goal file in
full. They are historical evidence, not current status or instructions. Keep this
file concise: replace the current continuation when it changes; write detailed
chronology to `docs/TODO.md` and evidence to its owning document.
