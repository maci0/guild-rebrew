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

The full goal remains ACTIVE and incomplete. Preserve all earlier character,
animation, loader, allocator, logical-reset and action-insertion work. Both raw
client images, initialized-data verification/ownership, broader source contracts
and faithful discarded-server inputs remain open.

Goal55 adds one shared ordinary-C dummy-selection callback, provisional
fcn_00406ee0: TL406ee0 and Gold406340 each earn RELOC1102. Its original identifier
and unit remain unproved; the definition stays beside its existing selection
caller. Native/Kuna evidence establishes a local 15*64 matrix, fourteen literal
filters and an implicit zero final row. Preserve the combined
`dummy_AUSGANGdummy_LAUFEN1` entry. An explicit empty fifteenth string emits1117
bytes; implicit initialization matches all1102 without flags, assembly or padding.
The private inferred CH_DUMMY_PICKS result view replaces Picks through the type
writer; stable ch.dummy_picks bindings check the 0x84 allocation and count+80 in
both targets. The old TL wrapper stays RELOC96. The native Gold wrapper matches
in scratch but is unadopted until its scene-service/provider contracts reconcile.

Three complete production objects cover2300 bytes and122 operand sites, with34
rejecting controls. All58 literal sites per callback validate the full fourteen
strings. Supporting stock-object proof checks both clients' strstr128 and
strchr188, including the +6 internal entry and two wrong-entry controls. It does
not grant strict resolver trust or actual raw-map/archive provider attribution.
Upstream cdc0a00f records explicit internal-entry review in docs/IDEAS-GUILD.md;
its mandatory full-suite push hook passes, and it is merged/pushed to main.
Existing fail-closed behavior stays intact. The completed documentation worktree
is removed; both repositories retain only main. All23 unrelated upstream accounting
edits remain unstaged and untouched; do not commit or discard them.

Reviewed inventory repairs change only TL4079d0 from960 to30, ending at its RET
before two NOPs/new prologue, and Gold strstr5de800 from138 to128, excluding a
separate ten-byte stub. Retain subsequent bytes as unassigned native code, never
invented padding or new game progress. Library metadata and statuses are unchanged.
All8392 previous identities and6038 strong verdicts survive; totals are8394/6040.
Data and source/config stores are unchanged, all old type bindings survive, and
both new type bindings are compiler-checked. The source organization review is
retained; complete client PE placement comparisons remain unavailable.

New matched game bytes are1102 per client: TL694315, Gold379579. Library bytes
are390163/9732 (Gold-10 from the corrected extent), padding33605/23492.
Accounted text is TL1118083/2491370=44.8782%, Gold412803/2006532=20.5730%;
the CLI truncates these to44.8/20.5. Both clients still have zero verified
initialized-data bytes and no verified raw image. All-target lint is0/0, data
conflict/duplicate-definition counts are zero, and all three type checks report
1020 structs with zero findings. The focused callback contract audit has zero
findings and3981 current input hashes, with122/904/617 SDK/include unknowns.
The broader traversal/callback API is explicitly unreconciled.

The final server gate passes316 function/652 data checks and every286720 raw
reference byte (SHA-256 3cc2ce9049e41ab6d0eea042df4966fbf57e5e27c67fb923e81709d2683609d1),
plus import/export/relocation/layout and Wine loading/export checks. Docker-only
compilation works; compiler/config inputs and reference images are unchanged.
Receipts and replays: .scratch/goal55/native-proof, supporting CRT proof,
preservation, contract-summary, final lint/data/type/status, guarded extent/type
writer results, native/Kuna/library inputs and server-gate.log. Failed measurements
remain separate. Keep the stock CRT members unmodified and library work distinct
from game reversing gains.

Next select larger unmatched client bodies through todo/native/library evidence.
The corrected4079d0 extent exposes unassigned follow-on code: Kuna4079f0 and the
old complete960-byte disassembly are saved for recon; no new implementation was
started. Do not repeat exhausted low-poly motion/allocator LOD, office17-byte or
queue733/735 probes without new evidence. Camera/list/disposal contracts, Gold
fb9900 ownership/extent, client raw builds and discarded server inputs remain open.

## History

[Archived checkpoints](docs/goal-history.md) preserve the previous goal file in
full. They are historical evidence, not current status or instructions. Keep this
file concise: replace the current continuation when it changes; write detailed
chronology to `docs/TODO.md` and evidence to its owning document.
