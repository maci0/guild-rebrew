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

Docker and Git access are restored after the session permission change. Both
pinned compiler images are present; rebuilding is unnecessary. The earlier
three-turn environment block is historical. The fresh server gate finishes
exit0/PASS in `gate-access-restored.log`:286,720 raw bytes identical,316/316 game
and652/652 data checks, imports, relocations, Wine and compiler alignment pass. Native
message-chain investigation is recorded below. Resolve the include closures,
reconcile the packet-wrapper/queue and message-helper contracts, verify all
affected client contexts and the server gate, then commit and push the reviewed
changes. The full objective remains unchanged and incomplete.

Latest resumed checks: `lint-resume-all.json` passes all3,879 files in each
target with zero errors/warnings; `data-conflicts-resume-all.json` reports zero
type conflicts and duplicate definitions in all three targets. Function contract
audits separately confirm incompatible office/helper declarations; lint and data
checks do not establish those contracts. Their source inventory and native message
helper receipt are in `.scratch/goal46`. Complete the reviewed canonical interfaces
and verify every affected target context before adopting the office body.

Message-chain native closure now covers129/36/79/71-byte pairs (630 bytes across
the clients). The wrappers preserve full-width ID/flag arguments; their helper
uses low bytes for lookup/packet fields. A further return/prototype mismatch in
the packet wrapper must be reconciled with existing `client_packet_queue.h`
before the helper contract is closed. The wrapper copies15 payload bytes while
the helper initializes11; preserve native behavior. The reconciliation preview
refuses unresolved include contexts without edits. Receipts and exact next scope
are in docs/TODO.md and `.scratch/goal46/office-message-native-contract.json`.

The interrupted `gate-office-evidence.log` has no terminal PASS and is historical.
The restored-access scope audit preserves all8,381 identities,6,024 strong
statuses and prior history. Only316 server verification records and275 associated
history/timestamp records refresh; data/type/source stores and production C are
unchanged. Both compiler smoke checks and fresh client71/129-byte baseline
comparisons pass. The full goal remains unfinished.

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
native boundary repairs. Data/type-store ownership and extents remain unchanged; the separately reviewed
client forwarding repair below changes three existing C bodies without new coverage.

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

The repaired upstream full suite is terminal PASS:12,250 passed/36 skipped
against d5d15c7c tree62250045bf93f12b92ce54d69f063c978f634092
(.scratch/goal45/upstream-full-suite-final.log). Both repairs are integrated as
f78478af/37637773; the changed product/test files equal the tested branch.
Current-main coverage-project, packaging and API checks also pass121/3 skip.
Both private upstream validation worktrees and branches were removed after
integration, direct file comparisons and process-use checks. Preserve the separate
active upstream release worktree/session.

Guild d31f0323 is committed and pushed. The subsequent upstream main push exited1:
all12,252 tests passed/36 skipped, but the pytest hook reported that files changed
during its run and blocked publication. This is a hook failure, not a failed test
or demonstrated transport error. The terminal evidence was sent to the upstream
session; do not start competing pushes. The upstream session subsequently published Rebrew4.1.0 and Recoverage8.0.0,
with both CI suites passing and release assets equal to CI artifacts. Rebrew
passed12,252 tests; Recoverage passed2,292 backend and24 browser tests. Both
projects are pushed to main; no PyPI publication. These supersede the earlier
publication-pending checkpoint.

New byte-focused TL triage is in.scratch/goal46. The intentionally capped
start-function lane returns only50 entries even with--limit3000; the complete-lane
feature gap is recorded in upstream docs/IDEAS-GUILD.md. Native extract inventory
provides larger candidates without maintaining a second coverage store.

TL4eba60 and Gold4e9ce0 are complete2,148-byte native counterparts:646
instructions,1,800 identical fixed bytes and87 corresponding address operands,
followed by12 alignment NOPs each (office-native-counterpart.json). A shared
ordinary-C office-action candidate is in ignored scratch only. Initial2,080-byte
output improved after preserving the cached second participant across both
relationship calls and the full-width255 flag argument. The frozen first candidate emits2,103 bytes against2,148; the later direct
membership-dispatch candidate below improves this without source adoption. Native
floating arithmetic and the six24-byte output records replace Kuna's omitted
FPU expression and artificial split stack arrays. Before adoption, reconcile
helper and caller contracts, resolve every operand/literal, and verify both
clients without changing prior matches. No new game bytes are claimed.

TL502fe0 also shares gm_AllocObjekt's server algorithm, but adds substantial
client rendering work and intersects the unfinished camera interfaces. Kuna
misses its indirect-switch bodies. The shared server seed emits1,371 bytes
against2,016 native bytes and is not a valid client provider. Keep that trial
separate; do not copy the incomplete seed or claim a client match.

The full goal remains unfinished. Client raw images, initialized-data bytes, shared
interfaces and source ownership remain incomplete. Checkpoint45d69dae passed
raw server identity, all-target lint0/0 and zero data conflicts/duplicate
allocations. Its audit preserved8,381 rows and6,024 strong statuses. A compiler
evidence refresh re-earned275 linked EXACT results without losing their history.

The prerequisite forwarding contract is repaired in three existing shared C files.
GOLDTL.fcn_005100f0.c explicitly forwards both integer arguments instead of
relying on an accidental tail jump from void(void). GOLDTL.fcn_0057dd40.c uses
the same void byte-pointer interface as its sole native caller, which discards
EAX. The old reconstructed return propagation did not establish a native return
contract. Other wrapper callers already use void(int,int). The50-byte destination
GOLDTL.fcn_004c6ae0.c now uses the existing canonical client_packet_queue.h
interface and a typed view of its packet buffer, replacing an incompatible local
queue declaration. These reconstructed access/return contracts are not attested
original spellings.

All three bodies retain complete5/33/50-byte matches in both clients. The full
operand-resolved proof covers176 bytes and eight wrong-callee controls reject
(forward-native-proof.json). The unchanged135-byte caller also retains both
matches. Named contract audits find no contradictions; the target-wide audits
exit1 for unresolved SDK/include closures and are not wholly green checks. Fresh
all-target lint is0/0. The fresh server gate passes in gate-forwarding.log, including raw286,720-byte
identity and all316 game/652 data checks. The forwarding scope audit preserves
all8,381 identities,6,024 strong statuses and prior history; only verification
evidence and the three selected source files change. Data/type stores and native identities remain unchanged. This repairs
source fidelity, with zero new matched game bytes.

The larger office candidate remains unadopted. Both independent reviews accounted
for the old 45-byte deficit: register lifetimes and folded notification/return
tails, with no missing gameplay operation. Directly dispatching a membership hit
from the search restores the native layout and all87 operand sites. The new best
scratch source is.scratch/goal46/office-direct-membership.c. Both client tests
report NEAR_MATCHING,2,131/2,148 bytes, with the same17 differing bytes. These are
six stack-slot displacements and instruction ordering in one outer-loop latch;
the comparison and control-flow edges match. No coverage is credited.

The explicit native-address proof resolves all87 operand sites/348 operand bytes
in each client;40 wrong-symbol controls introduce operand conflicts beyond those
17 nonoperand differences (office-near-operands.json). Both literal audits verify
all15 complete float/double occurrences. This is bounded object/native evidence,
not registered bindings, reconciled source contracts, linked providers or raw
client image identity. Stock CRT scans locate __ftol candidates in the expected
LIBCMT/LIBC archives; provider resolution remains explicitly unresolved.

Explicit notification returns do not improve the old2,103-byte shape. Moving the
outer increment to the body, a guarded do/while, and canonical record/action-view
probes leave the new17-byte residue unchanged. An explicit outer cursor regresses.
Keep the algorithms and their arithmetic intact; do not repeat these trials or
invent padding, assembly or volatile accesses. Remaining work is canonical
helper/caller contracts and evidence-led compiler/source-context work. The actual
three-file forwarding repair is committed and pushed as73cbbe63. Both clients
retain its matches; gate-forwarding.log and lint-forwarding-all.json pass.

## History

[Archived checkpoints](docs/goal-history.md) preserve the previous goal file in
full. They are historical evidence, not current status or instructions. Keep this
file concise: replace the current continuation when it changes; write detailed
chronology to `docs/TODO.md` and evidence to its owning document.
