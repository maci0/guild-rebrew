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
client data verification/ownership, source contracts and faithful discarded
server inputs remain open. Preserve checkpoint 5700a116's character/animation
contracts, shared Gold loader and corrected Gold allocator flags.

Goal53 resolves two independent definitions formerly named gm_ResetAllEntities.
TL `0x4297c0` / Gold `0x42aef0` become the inferred ProcessActiveContexts; their
complete 59-byte bodies and all four operands per target are unchanged. Native
and Kuna evidence shows active execution-context processing, not entity reset.
Original name/module and existing game/GOLDTL.spiel.c placement remain inferred.
The logical reset keeps SERVER `0x10015cb0`, TL `0x5012b0` and Gold `0x4fe7f0`.
Its header and all three physical caller files are unchanged. The two bound
server callers and TL `0x5392a0` have direct native call proof to that reset.

A guarded, reviewed rename changes one definition and two identities. All 8,388
previous identities/history and 6,034 previous strong verdicts survive. The TL
caller earns a fresh RELOC221 with the now-unambiguous reset operand. Complete
before/after comparisons cover 339 bytes and reject the wrong context-walker
callee; other unresolved caller operands remain explicit comparison hypotheses,
not client raw-link/provider proof. No new game body is reconstructed here.
TL recovers 221 previously rejected matched bytes: 692,752 game bytes; libraries
390,163 and padding 33,587 stay separate. Accounted text is 1,116,502/2,491,370
(44.8%). Gold stays at 377,902 game bytes and 20.4% accounted text. Both clients
still have zero verified initialized-data bytes and no verified raw image.

Upstream c8ee8d12 adds reviewed file-level reference owners and an exact-input
preview/apply digest; unresolved mixed-owner files and ambiguous linker symbols
still refuse. The feature gap and remaining finer-grained scope are recorded in
upstream docs/IDEAS-GUILD.md. Two encountered bugs are fixed directly upstream
with failing-then-passing regressions: 712ad9e0 makes refresh --dry-run read-only;
43802a3b makes scaffold lint use the configured default, matching refresh. Focused
checks pass 429 tests plus one skip; the final mandatory full suite and contributor
gates pass. These commits are merged and pushed to upstream main. All 23 files
of another session's uncommitted accounting work remain unstaged and preserved;
its documentation additions survive the merge. Do not commit or discard that work.

The final server gate passes 316 function and 652 data checks, all 286,720 raw
reference bytes, imports/exports/relocations/layout and Wine load/export checks.
All-target lint is 0 errors/0 warnings. Each type check covers 1,021 definitions
with no findings; data inventories have no type conflicts or duplicate storage
definitions. Function/data/type/source history remains intact. Refreshed generated
guidance follows the configured TL default; custom project rules are preserved
exactly. Config/compiler flags and all four retained reference files are unchanged.
Both Docker images work; no rebuild or production backend change was needed.

Receipts/replays are in .scratch/goal53: native-proof-{before,after}, reference-
ownership-proof, guarded rename previews/apply, preservation, final lint/data/type/
status reports and server-gate-final.log. Upstream .scratch/goal53-upstream keeps
regression/push logs and the preserved-work merge receipts. The completed feature
worktree is removed; retained ignored scratch is native/tooling evidence. An empty
old .gauntlet/scratch-l4 toolchain-directory tree was removed without deleting files.

Next use todo for larger unmatched client bodies, checking libraries and Kuna/native
operands first. Keep the 305-byte low-poly motion candidate unadopted; saved
304/306/307-byte probes do not justify padding, assembly or fabricated types.
Allocator LOD, office pair's 17-byte residue, queue 733/735, camera/list/disposal
contracts and Gold 0xfb9900 ownership/extent remain open. Do not repeat exhausted
probes without new evidence. Library attribution and cleanup are not game progress.

## History

[Archived checkpoints](docs/goal-history.md) preserve the previous goal file in
full. They are historical evidence, not current status or instructions. Keep this
file concise: replace the current continuation when it changes; write detailed
chronology to `docs/TODO.md` and evidence to its owning document.
