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

The full goal remains ACTIVE and incomplete. Goal66 completes the first parallel
no-source integration batch. New shared bodies am_RegisterMethod579,
cm_ExCreateCutsceneEntry111 and cm_ExAddCutsceneParticipant70 add760 matched game
bytes to EACH client, with complete operands/literals and rejecting controls.
All6057 prior strong statuses are unchanged. Nineteen affected contexts pass
fresh verification; independent preservation covers all15 old contexts, including
all72 original Gold assembly-macro sites. No assembly was added.

TL no-source is now1212 /1207266bytes, from1213 /1208039. Two previously hidden
entries were added to each native inventory while gaining source;13 bytes formerly
inside a384-byte span are now correctly separate padding. Count/catalog repairs
are distinct from the760 newly matched executable bytes. TL accounted text45.0%
still includes libraries/padding; full client raw links are not established.

The old client cutscene384-byte spans are independently dispatched190/111/70-byte
functions with2/1/10 NOPs. Diagnostic reuse does not prove unique names: the first
entry pairs with SERVER cm_ExAllocCutscene at command index0x27; SERVER0x28/0x29
are cm_ChainNoop. Keep the two new names inferred and separate from SERVER. The
old190-byte name remains a provisional counterpart association, with Goal63's
nearest-diagnostic attribution explicitly superseded. Incoming g_aed340 is an
incomplete bytebuffer, separate from outgoing g_aed32c; no owner/full extent or
allocation is invented. The pointer-return allocator repair preserves46bytes.

The method header records inferred AM_EFFECT/AM_METHOD layouts and native strides
8/0x94, not allocations. Preserve the unsigned-byte/full-width-1 comparison,
profile-mode-only second argument and opaque callback slots. The narrow inferred
pragma function(memcpy), with default flags, retains the evidenced explicit32-byte
copy before the37-DWORD registry assignment. All four old caller definitions and
four existing Gold assembly-provenance records are current. Registry/filename/
flag storage owners, complete extents and linked providers remain unresolved.

All-target lint has zero errors/warnings and data zero conflicts/duplicate owners.
A fresh server gate passes: all286720 raw bytes identical, matching data, imports,
relocations and layout, with Wine load/export checks. Upstream diagnostic bug fix
e1230fc7 is committed/pushed,12392 tests pass/48 skip and mandatory push gates
pass; canonical checkout is clean and the isolated fix worktree removed.

Parallel unmatched action/network/crime candidates remain scratch-only. Do not
restart exhausted warehouse/init_Betrieb/gfx/nt_Recv/crime shapes without new
evidence; preserve discarded server inputs. Reports and replay proofs are in
.scratch/parallel-no-source and .scratch/goal66; detailed findings/next leads live
in docs/TODO.md and docs/naming_conventions.md. Reuse Goal63's65 native-only
mappings,7.1M FLIRT results and Kuna/native dossiers rather than repeating scans.
DirectX attribution still requires complete native/provider proof.

Continue tractable mapped no-source bodies, prioritizing larger executable byte
gains. Goal65 SaveBMP8 adds441TL bytes; paired SaveBMP24 remains unmatched439/447
with bounded output checks. Do not resume exhausted court/queue/office/camera/
timer/runner families without new evidence; keep OWN-before-OTHER query order.
Both clients' full raw-file/data/provider proofs and broader source contracts
remain open. Every completion criterion above still applies.

## History

[Archived checkpoints](docs/goal-history.md) preserve the previous goal file in
full. They are historical evidence, not current status or instructions. Keep this
file concise: replace the current continuation when it changes; write detailed
chronology to `docs/TODO.md` and evidence to its owning document.
