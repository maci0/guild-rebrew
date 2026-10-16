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

The full goal remains ACTIVE and incomplete. Latest user priority is the1213
TL no-source functions. Parallel work is explicitly authorized: commands own
TL4c9a10/4c9e20 family, actions own55ffe0/512b40, networking owns4210a0/494ed0.
Their candidates and reports are isolated in .scratch/parallel-no-source; only
reviewed source/operand/provider evidence may be integrated. Root owns managed
writes and final checks. Preserve source sharing and all prior strong matches.

Goal65 adds inferred SaveBMP8 at TL401d10: complete441 executable bytes, all
eight operands, exact wbn literal, thirteen rejecting controls and seven NOPs
pass. The448-byte inventory span remains. Eight native and compiled cases each
agree with independently packed BMP header/palette/row bytes, including odd
width without padding, null/custom palettes, zero/negative heights, open failure
and ignored write failures. The private fill0 reuses the independently attested
original aligned-fill macro; fresh native sites and stock-archive exclusions
support managed helper provenance. Its name and source placement are inferred.
SDK BMP types introduce no new project type or storage. New TL game bytes441;
Gold0. Broader legacy VFS global/prototype/provider contracts remain open.

SaveBMP24 TL401ed0 / Gold401b90 is paired439 code bytes plus9 NOPs. Its447-byte
scratch body passes twelve bounded output checks, including exact44-byte info
blocks and BGR conversion; it remains unadopted and unmatched. Do not resume its
bounded header/indexed-loop shape trials without new evidence. Receipts live
in .scratch/goal65/indexed and bmp24. Lint/data are clean for every target; a
fresh server gate passes with all 286720 raw bytes identical, matching data,
imports, relocations and layout, and successful Wine load/export checks.

Goal64 committed0e32efdc adds one shared485-byte quad sampler in both clients
and the79-byte Gold projection counterpart, with complete operand/literal proof
and rejecting controls. All eight earlier affected strong contexts pass and one
weak102-byte context retains its exact prior output. client_scene_transform.h
holds the narrowed object/float access contract; broader455350/scene contracts
remain open. Preserve native double0.9 sampling bias and distinct plane sentinels.

Goal63's65 native-only mappings cover55 TL functions/150636 inventory bytes
plus ten large Gold counterparts. They do not earn source providers or byte
verdicts. Reuse saved7.1M FLIRT results and diagnostic/Kuna/native dossiers rather
than repeating scans. Prefix fortify/check-fail hits were rejected; DirectX
attribution still needs whole-body operands and raw-map provider evidence.

Continue tractable mapped no-source bodies. rd_AllBauplatzToSupermap remains
scratch-only260/123matching; record/array,Op/O1,G3/G6 probes do not justify new
flags. Its wrapper needs enum pointer/count repair: fourteen native callers
consume count despite existing void providers. Preserve null holes. Gold callback
58f780's250+6 extent is a review lead only. Do not resume exhausted court/queue/
office/camera/timer/runner families without new evidence; retain OWN-before-OTHER
stateful query order. Both full client raw-file/data proofs and linked providers
remain open. Every goal completion criterion above still applies.

## History

[Archived checkpoints](docs/goal-history.md) preserve the previous goal file in
full. They are historical evidence, not current status or instructions. Keep this
file concise: replace the current continuation when it changes; write detailed
chronology to `docs/TODO.md` and evidence to its owning document.
