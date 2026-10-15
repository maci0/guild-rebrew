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

The full goal remains ACTIVE and incomplete. Preserve all previous character,
animation, loader, allocator and logical-reset work. Both raw client images,
complete client data/ownership, broader source contracts and faithful discarded
server inputs remain open.

Goal54 adds one shared ordinary-C ch_InsertAction: TL4051d0 RELOC461 and
Gold4048b0 RELOC456. The diagnostic attests both this name and the getter's
ch_GetFreeQueueEntry name; character.c/header placement remains inferred.
Native callers establish three fixed arguments and integer varargs, rejecting
Kuna's spurious fourth parameter. Handler/owner assignment and short-circuit
load order preserve complete native bytes; only the evidenced universe stride
varies. The existing universe allocation supplies its interior field views.

Queue declarations now share actual provider signatures, including pointer
transport formerly held as int in 40db50. The occupancy-only CH_QUEUE_SLOT and
existing dispatch-entry layout gain four compiler-checked stable bindings;
payload and callback contracts remain open. Two dispatch data rows describe
64*0x4c bytes in each client's zero-filled .data tail. Their header is extern-only:
no source storage owner or linked provider is established. The shared read-only
message provider also matches Gold4222b0 RELOC119; its narrow Error header
reconciles 49 declarations without claiming the broader Error API. Gold4047a0
is paired with TL's delete but remains NEAR_MATCHING98/110 and adds no matched
bytes. Six inventory repairs exclude only evidenced trailing alignment NOPs.

All 8,388 old identities and 6,035 strong statuses survive; current totals are
8,392/6,038. All old data/type bindings and history survive. Expanded verification
covers 162 target contexts: 147 pass, 15 remain weak. All 144 previous strong
contexts in that surface pass. Six complete production-object proofs cover
1,283 bytes and 60 operand sites; 40 rejecting controls fail as intended.
Literal extents and actual import names are checked. Unresolved supporting
operands remain explicit native comparison hypotheses, not client provider proof.

TL gains 461 matched game bytes to 693,213; Gold gains 575 to 378,477.
Libraries remain 390,163/9,742, padding 33,590/23,490. Accounted text is
TL1,116,966/2,491,370 (44.8%), Gold411,709/2,006,532 (20.5%). Both clients
still have zero verified initialized-data bytes and no verified raw image.
All-target lint is 0/0; data conflict/duplicate-definition counts are zero.
Type checks report 1,020 C-source structs with zero findings; moving a private
view to a bound header explains the count change. Five focused contract audits
have zero findings and current hashes, with 122/904/616 SDK/include unknowns.
The existing upstream SDK-context feature gap remains open; guards are preserved.

The final server gate passes 316 function/652 data checks and complete raw
286,720-byte identity (SHA-256 3cc2ce9049e41ab6d0eea042df4966fbf57e5e27c67fb923e81709d2683609d1),
plus imports/exports/relocations/layout and Wine load/export checks. Both Docker
images work. Initial transient container-start stalls also affected /bin/true;
a later 0.672s startup and actual client compiles pass. No image rebuild, daemon
change or host fallback. No upstream bug was identified in this package.

Receipts/replays live in .scratch/goal54: native-proof, preservation, scoped
verification, stable contract audits/summary, lint/data/type/status, reviewed
writer previews/digests, native/Kuna/library inputs and server-gate.log. Retain
failed measurements separately. Source organization review is recorded, but
client raw artifacts are still unavailable for complete placement/PE checks.
Both repositories have only main worktrees. Upstream remains at 43802a3b;
another session's 23 uncommitted accounting files remain unstaged and untouched.
Do not commit or discard them. Project rules already require bugs fixed directly
upstream and every feature gap recorded in its docs/IDEAS-GUILD.md.

Next use todo to select larger unmatched client bodies, checking libraries and
Kuna/native operands first. Avoid exhausted low-poly motion/allocator LOD probes,
office's 17-byte residue and queue733/735 experiments without new evidence.
Camera/list/disposal contracts, Gold0xfb9900 ownership/extent and the dispatch
callback contracts remain open. Cleanup, library attribution and validation are
not newly matched game bytes.

## History

[Archived checkpoints](docs/goal-history.md) preserve the previous goal file in
full. They are historical evidence, not current status or instructions. Keep this
file concise: replace the current continuation when it changes; write detailed
chronology to `docs/TODO.md` and evidence to its owning document.
