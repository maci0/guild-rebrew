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

The full goal remains ACTIVE and incomplete. Goal57 integrates one shared event
validator TL4dc7d0/Gold4daf80 (RELOC1920 each) and independently verifies the
Gold4e4cc0 event consumer (RELOC630; TL4e6650 retained). New game matches are
TL+1920 ->697456 and Gold+2550 ->383347. Libraries remain390163/9732; native
alignment is33614/23497. Accounted text: TL1121233/2491370 (CLI45.0%),
Gold416576/2006532 (CLI20.7%). Read docs/TODO.md Goal57 for detailed evidence.

The narrow inferred event_callbacks.h reconciles the eight fourth-slot validator
contracts, setter, consumer and connected event helper pointer views. Native
logging attests cut_CheckMaster (TL4e63e0/Gold4e4a50, RELOC241 each); supported
rename retains the existing filename and does not establish original TU ownership.
The private stable event.validator_view records a20-byte strided field view;
the backing table's full extent/owner and first three callback-slot contracts
remain unresolved. No new storage, flags, assembly or filler was introduced.

Two native discovery extents were repaired from13264/13616 to1920; subsequent
independent code remains unassigned, with only evidenced alignment counted.
All8401 previous identities/6045 strong verdicts survive, totals8404/6048.
All23 existing strong affected contexts survive. The TL transfer callback stays
799/native801 with all old compiled bytes/fixups preserved. Complete proof is
10bodies/6412bytes/306operands/148rejecting controls, including16 independently
bound local/table operands. Unbound externs remain comparison hypotheses.

Upstream8e897442 fixes function-pointer typedef contract resolution and named
record aliases retaining pointer/function declarators. Thirteen new regression
cases,186 focused tests and the full mandatory push suite pass. It is merged
and pushed; owned worktree/branch removed. Both repositories retain only main.
All23 unrelated upstream accounting edits remain unstaged and byte-preserved,
with reversible CHANGELOG merge receipts. Do not discard or commit that work.

Final all-target lint0/0, data0conflicts/duplicate owners, three type checks
1020structs/0findings. Selected14 contract names have zero findings/unknowns
with3986 current input hashes. Broad audit findings258/1479/968 and unknowns
305/4081/2606 remain across server/TL/Gold. No new finding names appear against
the Goal56 report, whose audit logic differs; this is not global contract closure.
Both clients still lack raw-image and initialized-data verification.

Fresh Docker server gate passes316function/652data checks, imports/exports/
relocations/layout/Wine and all286720 raw bytes, SHA-256
3cc2ce9049e41ab6d0eea042df4966fbf57e5e27c67fb923e81709d2683609d1.
Final source/header/tool fingerprints are remeasured after the upstream fix.
Receipts/replays are .scratch/goal57/{native-proof,preservation,contract-summary,
contracts-focused,scope-promote,lint-final,data-final,status-final,types-*}.json,
guarded inventory/data/type/rename plans, native/Kuna/library/formatter inputs,
transfer-preservation.json and server-gate.log. Scratch is ignored evidence,
not a second managed inventory.

Next select larger unmatched client bodies through todo/native/library evidence.
Check callback consumers before generalizing the first three event-slot signatures.
Preserve Goal56 character work and the unchanged MoveCharacterCamera221/218
blocker. Do not retry exhausted separation720/745-vs744, office17-byte, queue
733/735 or low-poly LOD probes without new evidence. Camera/list/disposal
contracts, Goldfb9900 ownership, client raw builds and discarded server inputs
remain open. Keep upstream bug fixes and feature-gap recording in AGENTS.md.

## History

[Archived checkpoints](docs/goal-history.md) preserve the previous goal file in
full. They are historical evidence, not current status or instructions. Keep this
file concise: replace the current continuation when it changes; write detailed
chronology to `docs/TODO.md` and evidence to its owning document.
