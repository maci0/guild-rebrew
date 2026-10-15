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

## Current continuation — 2026-10-15

The full goal remains ACTIVE and incomplete. Both raw client images, complete
client data verification/ownership, source contracts, unresolved code and faithful
discarded server inputs remain open. Preserve all prior native identities/matches.
Checkpoint815573c6 is pushed; Goal50's allocator source is retained and corrected.

Goal51 reconstructs the attested `ch_CreateMesh` in shared game/character.c:

- TL 0x403880 matches all 777 bytes and Gold 0x403070 all 787 bytes. Complete COFF
  relocation application covers all 61 operand sites, 45 wrong-symbol controls
  reject, and compiler literals pass. Unresolved native bases remain comparison
  hypotheses; this does not establish raw-link providers or literal placement.
- One ordinary C89 body preserves string parsing, scene creation, model state,
  animal handling, animation calls and optional low-poly updates. Gold's extra
  scene call and moved flag masks follow native evidence. Character-unit placement
  and local/byte-view spellings remain inferred; the function name is attested.
- Native word loads support the model flags’ 16-bit access view at +0x8c. Updating
  that word with 0x1000 emits the exact native byte OR; a signed-char update does
  not. No padding, assembly, flag or identifier/declaration sweep is added.
- Factory/caller declarations now use resource char* and float* positions through
  ch_motion.h. Repaired the argument-dropping forwarding prototype and the scalar
  component wrapper's integer float transport. Related private object views remain
  private. Other renderer/camera contracts and SDK/include contexts remain open.
- Reviewed native extents 777/787 exclude seven/thirteen external NOPs, with old
  784/800 extents retained in inventory history. No executable bytes are discarded.

The previous allocator integration incorrectly copied TL scene masks into Gold.
Gold needs flags2 at+212 masked with~8/4 and bit1 of+211 cleared; TL needs+216
masked with~2/1 and bit7 of+214 cleared. Corrected C matches both complete 38-byte
native flag windows; the old Gold object rejects. The allocator stays NEAR_MATCHING
(TL 1771/2003, Gold 1782/2003) with the separate LOD ADD/TEST/code-placement gap.
Do not reinterpret the old score or archive's only-LOD wording as semantic proof.

Final validation preserves all 8,385 prior identities and 6,032 strong statuses,
adds two constructor matches, and checks 184 affected target bindings with current
inputs (63 server pass, 58 TL pass/7 weak, 50 Gold pass/6 weak). All-target lint,
data conflict/duplicate-owner inventories and type bindings are clean. The fresh
server gate passes all 286,720 raw bytes, imports/relocations/data and Wine checks.
Named contract audits have zero findings and current hashes, but exit1 for the
existing 122/904/614 SDK/include-context unknowns; no whole-project closure claim.

TL gains 777 matched game bytes: 692,752 total. Libraries remain 390,163 bytes;
padding 33,587; accounted text 1,116,502/2,491,370 (44.8%). Gold gains 787 game bytes;
accounted text 410,907/2,006,532 (20.4%). Padding gains 7/13 are separate from game
progress. Neither client has a verified raw image. Receipts/replays: .scratch/goal51.

Upstream 744ec69f records bounded FLIRT progress output in IDEAS-GUILD.md and is
pushed after mandatory full tests. Existing two-stage switch, native-entry and
SDK/include-context gaps remain recorded. No upstream runtime bug is worked around.
Docker/toolchain images remain usable; only main worktrees and no loose files.

Next: inspect TL 0x404b60’s 305-byte model service, already a constructor callee,
using library/native/Kuna evidence before implementation. Keep the constructor's
unresolved providers explicit. Continue renderer contracts and the allocator LOD
shape from saved evidence; do not repeat exhausted byte/declaration probes.
The office pair 0x4eba60/0x4e9ce0 remains 2148 bytes with 17 nonoperand differences in
its saved candidate. Queue loader 0x5252d0/0x520340 remains 733/735. Camera/list/position/
rotation/disposal work is partial; Gold 0xfb9900 extent/owner remains unresolved.
The full three-target source and raw-file objective continues.

## History

[Archived checkpoints](docs/goal-history.md) preserve the previous goal file in
full. They are historical evidence, not current status or instructions. Keep this
file concise: replace the current continuation when it changes; write detailed
chronology to `docs/TODO.md` and evidence to its owning document.
