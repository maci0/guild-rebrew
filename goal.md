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

The full goal remains ACTIVE and incomplete. Latest user priority is the TL
no-source inventory: map evidenced roles/names/counterparts and then reconstruct
real shared C bodies. Do not resume exhausted contract/shape searches merely to
keep busy. A parallel native-mapping pass was explicitly authorized and completed.

Goal63 maps 55 previously source-less TL functions covering 150636 native inventory
bytes, with ten large-body Gold counterpart identities. Public locked
`record_function_rows` added 65 name/size/note-only rows. No file/symbol/provider,
STATUS, data storage or native extent was invented. All 8413 previous rows were
unchanged by publication; all earlier strong verdicts remain. Original identifiers
are retained only where native diagnostics and Kuna/native behavior agree.
Copied/ambiguous diagnostics retain provisional address names and explicit notes.
See docs/naming_conventions.md (Goal63) for every selected address and anchor.

Large mapped bodies include the trade/transport and personnel panels, three
localized text expansions, GUI markup rendering, council elections, master
trading, localized resource compilation, economic command selection, terrain
blend construction and tutorial chapter3 initialization. The other pass maps
character animation/path behavior, command handlers, AI roles, loading, transport,
credit, market supervision and building placement. Gold diagnostic candidates
outside the ten reviewed large-body pairings remain candidates. No server pairing
is claimed. No new matched source bytes are earned by this mapping.

The complete FLIRT scan loaded 7102296 signatures; 1967 candidates and 4679 skipped
ambiguous sites are inspection results. Five selected fortify/check-fail prefix
hits are rejected, not promoted to library origin. Stock LIBCMT whole-body checks
reject the twelve largest selected bodies and the four initial main-pass bodies;
a miss does not exclude other archives. DirectX/provider attribution still needs
whole-body/operand and raw-map evidence.

Prior source checkpoint 2eaccc18 repairs the packet-base pointer contracts across
43 files: both 90-byte providers and all six operands match; 68 old strong target
contexts pass, six old weak contexts preserve their exact prior compiled output,
and bounded resolver/native cases pass. It adds zero matched bytes. Timer, texture,
court and reset evidence remains in docs/TODO.md and earlier scratch receipts.

Continue from the mapped no-source bodies. Prefer a tractable real shared body
with bounded native operands and clean caller contracts; inspect complete native
instructions and Kuna before adoption. ch_AttachAni at TL404dc0 / Gold4044a0 has
an uninitialized empty-name native path. BMP24 TL401ed0 writes a 44-byte info block
and uses pixel offset0x3a. Preserve those findings; do not silently substitute a
cleaner algorithm and call it faithful. Original TU/headers/owners remain inferred
unless independently established.

The older runner TL4e5a00 / Gold4e4060 remains unadopted at 2023/2054 against native
2033/2063. Resource, lighting and provider contracts remain open. Preserve its
participant scans, stateful calls, Gold signed viewport words and GUI strides;
previous /Oy- diagnostics do not justify production flags. Preserve Goal58
OWN-before-OTHER sequencing and Goal59 reset behavior. Do not repeat exhausted
arithmetic/cursor, queue/office/camera or timer-loop probes without new evidence.

Goal63 receipts are under `.scratch/goal63`: main-map-plan.json,
reviewed-map-rows.json, mapping-preservation.json, full diagnostic string/xref and
Kuna/native dossiers, map-no-source/report.md and mapping-report.json, plus current
lint/data/status/server-gate results. Both client raw-file/data verification,
broad source contracts and discarded original server inputs remain open.
Upstream anonymous-record/typedef audit gaps are already recorded in
`docs/IDEAS-GUILD.md`. Goal63 also reproduces and fixes the upstream dossier bug
that hid native-only metadata names/notes; the regression retains target scoping
and no source-status claim. Its upstream full suite and push must pass before
returning to reconstruction. Preserve foreign upstream work. Every completion criterion above still applies.

## History

[Archived checkpoints](docs/goal-history.md) preserve the previous goal file in
full. They are historical evidence, not current status or instructions. Keep this
file concise: replace the current continuation when it changes; write detailed
chronology to `docs/TODO.md` and evidence to its owning document.
