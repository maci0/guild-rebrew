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
initialized-data verification and storage ownership, source contracts, unresolved
code ranges and faithful discarded server inputs remain open. Server byte
identity alone does not establish complete source fidelity or client completion.

Previous checkpoint07299374 is pushed. Docker works with both pinned images.
Goal48 repaired office-slot contracts, preserved all6,024 earlier strong statuses,
recognized2,868 existing Gold game bytes/44 padding bytes and corrected the
shared best-score literal to native -10.0f. Receipts/details are in docs/TODO.md.

Current Goal49 work repairs the skill-query API and its connected wrappers:

- Existing spiel.h owns reconstructed char-pointer/integer-index contracts;
  the query/paired wrapper return float and the scalar wrapper returns integer.
  Removed31 contradictory local declarations and integer pointer transport in
  connected wrappers/callers. Private record views remain private. Original
  spelling is unproved; equal x86 widths alone do not justify integer pointers.
- The native query is784 bytes in both clients, including its five-entry embedded
  switch table. Complete object/native comparison and17 literal occurrences per
  target pass, with40 wrong-symbol controls. Kuna's seed misreads the integer
  index and switch as floating values/indirect calls; native instructions win.
- Gold504ec0 now shares the existing507f10 source. Gold504e20 shares the existing
  507e70 paired wrapper,88 bytes. Five additional wrapper/caller bodies total321
  resolved bytes with18 wrong-symbol controls. The87-byte caller keeps its
  explicit double local while using the canonical float-return declaration.
- Gold discovery had merged two functions into504e00's120-byte entry. The first
  ends with a29-byte tail-call body, then three NOPs; the next starts504e20 and
  returns504e77. Digest-guarded repair preserves native extent history and the
  first source's existing29-byte match. Removed bytes are not all padding.
- Adding client declarations unconditionally to spiel.h perturbed four native
  server bytes in gm_ObjectsAvailble10015f70. The failed full gate is retained.
  The header's existing server/client declaration convention now excludes these
  client APIs from server contexts; the714-byte object matches again. The fresh
  full raw-image gate passes all286,720 bytes and all required checks. Broad
  preservation checks also pass for the final repaired state.

Baseline comparison covers196 source contexts and518 existing target bindings:
82 server matches,235 TL matches/12 old mismatches,160 Gold matches/29 old
mismatches. The final comparison preserves strong matches and explicitly records
the new Gold callee evidence. One already weak production body exposes three previously
masked conflicting bytes; the historical-map control reproduces the old score
without promoting it or weakening the actual binding policy.
The final combined scope adds the existing master helper and covers197 C files,
522 bindings:82 server pass,237 TL pass/11 weak,163 Gold pass/29 weak. Final
repository audit preserves all8,381 prior identities and6,030 strong statuses,
adds two Gold identities/872 bytes, and keeps data/type/source stores unchanged.
All522 source/reference hashes and stored statuses are current. All-target lint
passes3,879 files each with zero errors/warnings; data conflicts/duplicate
owners and type-binding findings are zero. Gold accounted text is410,094 bytes.

Final audit also repaired a pre-existing ambiguous fcn_0047dd60 spelling. The
sole master caller's native47de7e→47dd60 operand identifies the137-byte helper,
not the32-byte kind predicate. Supported rename/reference binding now calls the
inferred gm_CanEvaluateMaster; all three affected bodies pass928 resolved bytes
with35 rejecting controls and complete literals. Original source file and all
native identities remain. The654-byte caller's valid RELOC is freshly restored;
its earlier failing measurement is kept. See naming_conventions.md and TODO.

Receipts/scripts are in `.scratch/goal49`. Do not reinterpret temporary linked
EXACT invalidation after header changes as permanent completion or restore it
without fresh raw-link evidence.

TL remains691,975 matched game bytes,390,163 library bytes/1,468 library
functions, and1,115,705/2,491,370 accounted text bytes (44.7%). This contract and
Gold counterpart work adds no new TL algorithm. The7,102,296-signature audit and
prior D3DX/CRT evidence are in history/TODO; do not repeat without new inputs.
Actual client raw-link providers remain explicit where unresolved.

The large office-action pair TL4eba60/Gold4e9ce0 remains unadopted:2,148 native
bytes,87 operands, and a2,131-byte match with17 nonoperand differences. Slot and
skill API work closes parts of its source-contract problem; the formatter's
ID-or-pointer format word and four office callers still need native review.
Preserve the algorithm and exhausted trials; no padding, assembly, declaration
sweeps or invented target divergence. The native format parser is not a CRT printf.

Complete SDK/include-context and all-target type-check CLI support remain upstream
feature gaps (upstream e79dba09). Final named contract audits have zero selected
contradictions/unknowns and current hashes, but exit1 for122 server/904 TL/614
Gold other unknown SDK contexts. Do not bypass reconciliation guards or claim
whole-project closure. Queue loader5252d0/520340 remains a733/735-byte source-shape gap. Camera/list/position/
rotation/disposal work is partial; Goldfb9900 has unresolved record extent/owner.
Reviewed native-entry insertion is a separate upstream gap recorded in
IDEAS-GUILD at da4e8139; current tooling cannot add discovery start504e20.
The accepted source identity is retained; do not hand-edit native inventory.
Upstream da4e8139 is pushed after mandatory hooks/full tests. Next prioritize
the2,016-byte TL502fe0 object-allocation body. Prior native/Kuna/server comparison is in Goal46; recover
its real rendering additions and switch arms rather than repeat the failed
1,371-byte server-only seed or exhausted office-shape trials. Formatter and
remaining office contracts remain open. The full original objective continues.

## History

[Archived checkpoints](docs/goal-history.md) preserve the previous goal file in
full. They are historical evidence, not current status or instructions. Keep this
file concise: replace the current continuation when it changes; write detailed
chronology to `docs/TODO.md` and evidence to its owning document.
