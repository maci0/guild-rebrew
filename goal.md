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

Docker works and both pinned compiler images pass smoke checks; no rebuild is
needed. Previous checkpoint91f7c87b is pushed. Current bounded work and final
validation are recorded in `.scratch/goal48` and docs/TODO.md.

The office-slot repair uses the existing OFFICE_SLOT in game_structs.h and the
canonical game/aemter.h list-helper declaration. Twelve existing providers/callers
now share the 24-byte slot view. Role-template records remain distinct; their
DWORD at +16 must not become the slot's byte status. Removed two unsupported
volatile ID views without changing their 381-byte bodies. Storage definitions,
original identities and translation-unit organization are unchanged. The existing
unbound amt_ListSlotsOfGroup duplicate cannot be merged until source-organize
preflight and client raw baselines are resolved.

Stable type ID amt.office_slot has three compiler-checked target bindings:
size/stride24 and field offsets0/4/8/12/16/20. This proves a record stride,
not a table allocation or owner. A wrong +9 role offset fails compilation;
uncompiled dry-run previews alone are not rejecting evidence.

Six Gold source matches had padded native extents. Reviewed executable sizes are
4a0240:450,4aad30:446,4e8c20:414,4ea5c0:200,5ce940:337,5ceaa0:1021.
Their remaining44 bytes are separately accounted alignment NOPs. Preserve
inventory extent_history and status history. Complete body/operand checks and
wrong-symbol controls are in gold-boundary-proof.json/padded-cases-proof.json;
unbound native bases are comparison inputs, never accepted provider identities.
Literal audits additionally exposed a real reconstruction error: shared score
helper004aae50 used approximately -206 billion instead of the native -10.0f in
both clients. The one-line correction passes both literal audits. Instruction
RELOC alone had hidden the error; it never verified literal data or placement.

TL remains691,975 matched game bytes,390,163 library bytes/1,468 library
functions, and1,115,705/2,491,370 accounted text bytes (44.7%). Gold boundary
corrections recognize2,868 existing game bytes and44 padding bytes; they add no
new TL bytes. The completed7,102,296-signature audit and prior D3DX/CRT evidence
are in the history/TODO; do not repeat without new inputs. Actual client
raw-link providers remain explicit where unresolved.

The complete SDK/include-context audit and all-target type-check CLI remain
upstream feature gaps. Upstream e79dba09 records the latter and is pushed after
mandatory hooks/full tests. Do not bypass reconciliation guards or describe
zero selected-name findings as whole-project contract closure. SDK contexts
remain unknown, including32 TL/27 Gold selected OFFICE_SLOT typedef contexts;
the static contract command exits1 despite zero reported contradictions. All
input hashes are current. Compiler comparisons cover all59 selected bindings:
32 TL and27 Gold pass. All8,381 identities and6,024 prior strong statuses remain;
six reviewed Gold bodies add RELOC. Existing data/source stores and old type
bindings are unchanged. All-target lint passes3,879 files each with zero errors
and warnings; data inventories have zero conflicts/duplicate definitions. The
fresh gate-final.log passes all286,720 raw server bytes and required checks.
Full client data, layout and ownership are still unverified.

The large office-action pair TL4eba60/Gold4e9ce0 remains unadopted:2,148 native
bytes,87 operands, and a2,131-byte match with17 nonoperand differences. The
proper OFFICE_SLOT/canonical-header probe leaves the same17 differences.
Remaining skill-helper contracts and four office callers need reconciliation.
Preserve the algorithm and exhausted trials; no padding, assembly, declaration
sweeps or invented target divergence.

Queue loader5252d0/520340 remains a733/735-byte source-shape gap. Camera/list/
position/rotation/disposal work remains partial; Goldfb9900 has one record with
unresolved extent/owner. Earlier chain/building/allocation evidence is in TODO.
Next: continue remaining office contracts and byte-focused TL reconstruction.
The full original scope continues.

## History

[Archived checkpoints](docs/goal-history.md) preserve the previous goal file in
full. They are historical evidence, not current status or instructions. Keep this
file concise: replace the current continuation when it changes; write detailed
chronology to `docs/TODO.md` and evidence to its owning document.
