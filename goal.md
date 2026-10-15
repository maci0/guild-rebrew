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

The full goal is ACTIVE and incomplete. Both raw client images, complete client
initialized-data verification/ownership, source contracts, unresolved code ranges
and faithful discarded server inputs remain open. Preserve every prior match.

Checkpoint4917aafe is pushed. Its skill-contract and master-binding repairs retain
all 6,030 previous strong statuses and add 872 Gold game bytes. TL stays691,975
matched game bytes. Detailed Goal49 receipts are in TODO and the archived goal.

Goal50 reconstructs the client cart-rendering path in the existing shared
`gm_AllocObjekt` definition in game/spiel.c:

- SERVER 0x10016760 retains its 1,379-byte match. TL 0x502fe0 and Gold 0x500190 each have
  a 2,003-byte native body, including two dispatch tables and their selector maps.
  Thirteen external NOPs follow each body. Digest-guarded inventory repairs
  preserve the old 2,016-byte extents in history; no executable bytes are discarded.
- Native evidence supplies the renderer calls and both switch arms omitted by
  Kuna. Shared hierarchy, slot initialization, parent walking, recursive child
  creation and return remain one algorithm. Guards reflect native server logging
  and client rendering differences. No assembly, padding or flag overrides added.
- Client source is NEAR_MATCHING: TL 1,771/2,003 and Gold 1,777/2,003 under strict
  known-binding checks. The remaining LOD byte ADD/TEST shape emits one fewer
  instruction byte, shifting late code; table alignment keeps symbol size equal.
  This is no new matched game coverage. Unresolved operands/providers and
  renderer declaration contracts remain explicit; matching literals prove contents,
  not placement or ownership. See .scratch/goal50 and docs/msvc6-c-shapes.md.
- Nine former fcn_00502fe0 callers now use gm_AllocObjekt through the supported
  reference-binding writer. Their declarations consistently return char*. Existing
  pointer-through-integer wrapper returns and broader renderer contracts still
  need native review; this checkpoint does not claim their complete repair.

The final current-input server gate passes all 286,720 raw bytes and required
checks. All 8,383 prior identities and 6,032 strong statuses remain unchanged;
228 affected bindings have current source hashes. Both new client identities
remain NEAR_MATCHING. All-target lint, data conflicts/duplicate definitions and
type-binding checks are clean. The allocator-name audit has zero findings but
retains the existing 122/904/614 unknown SDK/include contexts, so it does not
prove complete source-contract closure. See docs/TODO.md.
No toolchain rebuild is needed: Docker access, pinned images and the plain-SP5 and Processor Pack
compiler smokes pass. Only main worktrees remain; no untracked cleanup candidates.
Keep ignored native receipts as evidence.

The upstream switch command currently exposes physical jump-table slots without
recovering the preceding bounded byte selector/bias. The concrete two-stage
switch feature gap is recorded in upstream IDEAS-GUILD.md at f94f3866, pushed after
mandatory full tests. It is not a runtime bug or a project-local parser replacement.
The earlier native-entry insertion and SDK/include-context gaps remain recorded.

Next: reconcile the allocator's renderer declarations/providers, complete operand
proof and close the measured LOD source shape without changing semantics or
sweeping declarations. Start from the full spiel.c context; isolated probes lose
native register/global-cache behavior. Do not repeat the exhausted byte-assignment
or promotion probes without new evidence. Keep the remaining client raw links and
initialized data/ownership work in scope. Large unmatched native bodies remain
necessary for material TL byte gains; library/padding accounting stays separate.

The office pair TL 0x4eba60/Gold 0x4e9ce0 remains unadopted: 2,148 native bytes and17
nonoperand differences in the saved candidate. Queue loader 0x5252d0/0x520340 remains
733/735 bytes. Camera/list/position/rotation/disposal work is partial; Gold 0xfb9900
has unresolved extent/owner. Retain prior native evidence and exhausted probes.

## History

[Archived checkpoints](docs/goal-history.md) preserve the previous goal file in
full. They are historical evidence, not current status or instructions. Keep this
file concise: replace the current continuation when it changes; write detailed
chronology to `docs/TODO.md` and evidence to its owning document.
