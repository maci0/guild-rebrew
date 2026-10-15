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

The full goal remains unfinished: both raw client images, full initialized-data
verification and ownership, unresolved code ranges, shared source contracts and
faithful recovery of discarded server inputs remain open. Prioritize new TL
matched bytes and proven library gaps; report cleanup and validation separately.
The latest complete server gate, `.scratch/goal45/gate-post-upstream-fixtures.log`, passes all286720 raw
bytes,316/316 game and652/652 data comparisons, imports, relocations, toolchain
alignment and Wine. Both compiler images exist. All-target lint is0/0; fresh
three-target data inventories have no type conflicts or duplicate definitions.

TL currently has691975 matched game bytes,390163 library bytes/1468 library
functions and1115705/2491370 accounted text bytes (display44.7%). This turn adds
62 library bytes and one separately classified padding byte, with zero newly
matched game bytes. TL5f0e50/5f0eb0 each equal a complete31-byte stock D3DX8
createmesh.obj body without fixups; altered-byte and shifted-start controls reject.
Their two template aliases stay unresolved, with provisional address-only names
and no selected raw-link provider claim. Supported native extent repairs reduce
merged discovery entries96/41 to31/31 with boundary history. The remaining75
bytes are not library credit:74 stay unattributed and one is padding.

The previous full shared7102296-signature audit is complete; upstream32e846cc
fixes its quadratic deduplication. Earlier library gains total1698 bytes (56 D3DX
and two821-byte CRT copy bodies). Internal labels/tables are not functions;
memcpy/memmove aliases and actual client providers remain unresolved. Receipts
and complete prior continuation are archived in docs/goal-history.md.

Queue loader TL5252d0 has a native Gold counterpart at520340: both735-byte
bodies contain261 identical instruction/control-flow positions,575 fixed bytes
and40 mapped native operand sites. Every shifted operand control rejects. One
shared algorithm is supported, including the signed version threshold and the
same failure behavior. The best ordinary-C scratch candidate emits733 bytes;
573 bytes agree after complete operand resolution, with its first mismatch at
branch displacement offset345. Native loop failures join an early zero return;
the candidate merges later failures at a late return. Direct array access and
version orientation are settled; the bounded loop, continuation and failure-exit
variants do not fix placement. No new loader identity, padding, assembly or fake
semantic divergence is registered. Details/exhausted trials: docs/TODO.md and
.scratch/goal45/shape-summary.json.

The existing shared protection helper TL41d500/Gold421f00 retains RELOC235 in
both fresh client CLI tests. Its five trailing NOPs are alignment, not body.
All pre-existing8379 identities and6024 strong statuses must remain preserved;
this checkpoint adds only two origin-only library identities and two selected
native boundary repairs. No game C/header or data/type-store edits are intended.

The camera interface migration remains partial. Shared list removal112, selector42
and motion54 retain their bounded native proofs. Reviewed float position/rotation
candidates83/184, their scalar wrappers, disposal and connected declaration work
remain unfinished. Goldfb9900 is one record with unknown full extent/owner.
Prior chain/building/lighting/inventory evidence remains in docs/TODO.md; do not
repeat exhausted probes without new evidence.

Upstream319071e0 fixes a global catalog failure: unrelated comparisons proceed
while ambiguous native operands still fail closed. The original public-API
reproducer fails on43fe499a and passes the fix in both strict modes. Independent
same-named client definitions still need reviewed source/caller reconciliation;
the supported rename refuses ambiguous references without writes. The missing
explicit reference-ownership capability is recorded upstream in b1a24da3.
Source-root and assembly-artifact repairs ae85d71c/f7ef0a45 pass 241 focused
checks and all commit hooks; upstream main includes them as 94c9e0f9/07f17aaa.
The complete f7ef0a45 suite then finished with 62 failures, 12,118 passes and 36
skips. Remaining failures included obsolete root-aware mocks, strict binding/path
expectations, removed incidental imports and a real forced-merge rerun bug.

The isolated upstream branch is now based on fd044c32, with b1ef8377/d5d15c7c
repairing fixtures/API migration notes and merge validation. Forced reruns accept
retained input anchors only for the selected prior output and matching identity;
other-owner conflicts still reject before writes. All commit hooks pass, 588
focused tests pass with three skips, and all 73 merge tests pass. The unpatched-code
regression uses an explicit pytest source path: the default test configuration
otherwise silently imports the patched tree. The complete fresh suite is running
in.scratch/goal45/upstream-full-suite-final.log against committed tree
62250045bf93f12b92ce54d69f063c978f634092. Do not claim a green full suite or resume
game source promotion until its terminal result is checked. Both latest repairs are integrated into upstream main as f78478af/37637773;
publication remains pending. Their product and test files equal the tested branch.
Current-main coverage-project, packaging and API checks also pass: 121 tests,
three skips. The complete repaired-tree suite remains live and has passed its
previously failing groups through the public API check.

Guild checkpoint 44098478 is committed and pushed; it adds the two library origins
and native boundary repairs, with no new game bytes. The completed old validation
worktree was removed after integration and a process-use check. One private
upstream validation worktree remains active. Guild server validation remains
green; fresh all-target lint also passes with zero errors and warnings
(.scratch/goal45/lint-all-post-upstream.json). Full reconstruction is unfinished.

## History

[Archived checkpoints](docs/goal-history.md) preserve the previous goal file in
full. They are historical evidence, not current status or instructions. Keep this
file concise: replace the current continuation when it changes; write detailed
chronology to `docs/TODO.md` and evidence to its owning document.
