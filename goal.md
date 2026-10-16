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

The full goal remains ACTIVE and incomplete. Goal61 adds the shared cutscene clock
TL `4e4a60` / Gold `4e3210`, RELOC 31 each. Its signed pre-increment comparison
sets the flag, then increments the counter. `game/cutscene_clock.h` centralizes
three existing scalar views without allocating storage or claiming an owner.
Both inventories formerly folded the callback and one NOP into the already
matched 336-byte predecessor; digest-guarded repairs preserve that body and admit
the separate callback. The prior 23-byte `fcn_00525e90` provider survives; its
incorrect data identity is retired through the locked writer.

The periodic timer controls and every existing caller now share the inferred
`client_timer.h`. `TIMER_CALLBACK` is void cdecl(void); the canonical 12-byte slot
has `funktion`, unsigned `periode` and integer `pausiert` at 0/4/8. Stable type ID
`client.timer_callback_slot` is compiler-checked for both clients. The 32-slot,
384-byte table is a declaration view with unresolved storage owner. Preserve
native full-table overwrite, null callback and zero-period behavior. These are
game semantics, not Rebrew defects to repair.

Four controls (88/49/49/49) and the new clock match complete native bytes with
all 20 operand sites per target resolved; 18 wrong-binding controls reject.
Fifty bounded VEX cases pass. Dispatcher preserves its previous 262 object bytes
and all 28 fixups per target; older unresolved operands/IAT policy remain separate.
All 28 prior strong selected contexts and both new matches pass. All 8411 prior
identities/6051 strong statuses survive; totals are 8413/6053. Earlier Goal60
texture, first-phase, refresh and buffer evidence remains in docs/TODO.md and
`.scratch/goal60`; no earlier source/ownership claim was silently completed.

Fresh Docker server gate passes: all 286720 raw bytes identical, 316 functions,
652 data records, imports/exports/resources/relocations/layout/load checks. SHA
3cc2ce9049e41ab6d0eea042df4966fbf57e5e27c67fb923e81709d2683609d1.
All-target lint has zero errors/warnings; data has no type conflicts/duplicate
owners; all three type checks have 1018 structs and no findings. Eleven selected
contracts are clean and all 3992 audit input hashes are current. Broader findings/
unknowns remain server 258/305, TL 1473/4093 and Gold 964/2613. Seventeen unknowns
are the auditor's intentionally unsupported anonymous slot typedef, not type
conflicts. Compiler layout and native bytes are independent evidence. The precise
feature gap/replay/proposal is recorded upstream in docs/IDEAS-GUILD.md, commit
23b81d46; no invented source tag or local auditor workaround was introduced.
The previous non-record typedef binding gap (4d52a5b4) also remains unimplemented.

Actual new game byte matches: TL +31 / Gold +31; totals 697576/383581. Library
390163/9732 and padding 33615/23499 are unchanged. Accounted text is
1121354/2491370 (45.0%) and 416812/2006532 (20.7%); no-function 102878/75338.
Display rounding hides the small gains. Both client raw builds and initialized-
data verification remain open; library accounting and source cleanup are separate
from newly matched game bytes.

Continue the larger runner TL `4e5a00` / Gold `4e4060`, native 2033/2063.
Unadopted `.scratch/goal61/runner.c` uses the canonical timer/clock headers and
still emits 2023/2054. Native uses a 0x248-byte EBP frame; the default TL candidate
omits the frame pointer and reserves 0x240. This is not a local ten-byte patch.
The previous /Oy- diagnostics do not recover original TU options or justify a
production pragma. Keep service contracts/native source evidence ahead of shape
search. Packet-base `4c4510`/Gold `4c3ba0` has 90-byte matched bodies but transports
pointers through integers, including a resolver output over its ID argument.
Review its complete caller surface and canonical resolver before repairing it.
Resource identifiers, lighting and missing providers remain separate open roots.
Misaligned-size operand-conflict counts are not callee-identity proof.

Preserve both participant scans, stateful calls, Gold signed viewport words and
GUI stride/count 0x2ec/768 versus TL 0x2f4/1024. Keep Goal58 OWN-before-OTHER
sequencing and Goal59 reset behavior. Do not repeat exhausted arithmetic/cursor,
queue/office/camera or timer-loop probes without new native/TU evidence.

Current receipts/replays are in `.scratch/goal61`: timer-proof.py/json, guarded
inventory/data plans, current type bindings, verify-scope.py/scope-promote.json,
contracts/data/lint/status/types, runner measurements and server-gate-current.log.
The interrupted contract audit correctly refused changing inputs; failed source
probes remain visible. No upstream bug was established. Client data/storage,
broad source contracts and faithful discarded server inputs remain open. Every
completion criterion above still applies.

## History

[Archived checkpoints](docs/goal-history.md) preserve the previous goal file in
full. They are historical evidence, not current status or instructions. Keep this
file concise: replace the current continuation when it changes; write detailed
chronology to `docs/TODO.md` and evidence to its owning document.
