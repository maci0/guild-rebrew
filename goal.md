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

The full goal remains ACTIVE and incomplete. Both raw client images, complete
client data verification/ownership, remaining source contracts and faithful
discarded server inputs remain open. Checkpoint 8cd1c29d is pushed; preserve its
constructor and corrected Gold allocator flags.

Goal52 reconciles animation name/result pointers and the byte loop/force flags
through the canonical d3_animation.h. Native TL `0x44e309` copies the loop argument's
low byte into animation `+0x169`; Kuna agrees. A full-width wrapper load/push was not
an int contract. The char declaration restores both complete 342-byte preloaders
and preserves the 207/108-byte wrappers. No pointer transport through integers.

The existing 207-byte loader at TL `0x44c620` also matches Gold `0x44e4a0` from one C body:
eight operand sites and seven rejecting symbol controls per target. Gold gains
207 matched game bytes. Known lookup bindings validate; other native bases remain
comparison hypotheses without raw-link provider proof. Reviewed inventory repairs
retain history: TL 800 / Gold 208 become 207 executable bytes, followed by one NOP.
The TL discovery extent had swallowed later code; no executable byte is padding.

All 8,387 previous identities and their histories remain. Fresh verification,
started in another session before these C edits, correctly demotes TL `0x5392a0`’s 221
bytes: `_gm_ResetAllEntities` is ambiguous between independent TL `0x4297c0` and `0x5012b0`
providers. Native `0x5392a0` calls `0x5012b0`. Both walkers retain their byte matches and
sources. Preserve the rejected caller verdict until the naming ambiguity is
repaired; do not reinstate a historical RELOC just to recover the count.

Upstream repairs are direct, with reproducing tests: a2b40b43 pins generated
CMake CL/LINK/LIB profiles while permitting later file overrides; 627b68e9 preserves
typed matcher relocations and makes diff reject invalid bindings with XX / exit 1;
257398f1 checks generated compiler arguments against CMake's active record while
retaining altered/appended-pin detection. The real `0x5392a0` diff now agrees with
test/verify. The public import removal has its required Breaking changelog entry.
All three repairs and the ownership feature gap are pushed through 257398f1;
the mandatory full suite and contributor checks pass.

The interactive default remains TL. Server CMake flags, final verification and
the gate now explicitly select server.dll. Regenerated toolchain files and fresh
main/isolated Docker builds retain all 286,720 raw bytes. The server gate passes
316 function checks, 652 data checks, imports/relocations/layout and Wine loading.
All-target lint is 0/0, each type check covers 1,021 definitions with no findings,
and data inventories report no type conflicts or duplicate storage definitions.
The 39 affected bindings have 38 matches and one existing TL low-poly mismatch;
all 37 prior strong matches in that source surface survive. All four selected
contract audits have zero findings and current hashes; SDK/include unknowns remain
122 server / 904 TL / 615 Gold, including the new Gold loader context. This is not
whole-project contract closure.

TL matched game bytes are 692,531: minus 221 newly rejected ambiguous-call bytes,
with no new TL byte gain this checkpoint. Libraries 390,163 and padding 33,587 are
separate; accounted text is 1,116,281/2,491,370 (44.8%). Gold gains 207 game bytes:
377,902 total, libraries 9,742, padding 23,471; accounted 411,115/2,006,532 (20.4%).
Both clients still have 0 verified initialized-data bytes and no verified raw image.
No library or cleanup work is reported as game reversing progress.

TL `0x404b60` / Gold `0x404360` remain a shared 305-byte native algorithm. Kuna, native bodies
and the 7,102,296-pattern library miss are saved. Ordinary-C candidates stall around
option initialization/lookup scheduling (304/306/307 emitted bytes); none is
adopted or promoted. Do not manufacture types, padding or assembly to match it.
Source receipts and replays are in .scratch/goal52; declarations and prior matches
are current independently of this unaccepted candidate.

The selected-definition rename safely refuses same-target ambiguous references.
Its missing reviewed reference-ownership capability is submitted upstream in
IDEAS-GUILD.md with the concrete replay. Next repair that ownership with native
call evidence; retain both algorithms and unrelated declarations. Continue larger
unmatched client bodies through todo rather than repeating exhausted probes.
The allocator LOD gap, office pair’s 17-byte residue, queue 733/735, camera/list/
disposal contracts and Gold `0xfb9900` owner/extent remain open from prior checkpoints.
Docker images work; the crun prototype stays ignored and production remains Docker.
Guild has only main and no loose files; retained scratch is evidence. Upstream
experimental-unshare has live edits/tests in another session and is preserved;
it has no completed commits to merge. The earlier release-review PID 16748 is gone.

## History

[Archived checkpoints](docs/goal-history.md) preserve the previous goal file in
full. They are historical evidence, not current status or instructions. Keep this
file concise: replace the current continuation when it changes; write detailed
chronology to `docs/TODO.md` and evidence to its owning document.
