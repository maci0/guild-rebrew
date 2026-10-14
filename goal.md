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
   the complete image. Run `scripts/gate.sh` before every commit. Client changes
   also require client-specific validation. Keep failed checks visible.
6. Refresh coverage through `rebrew coverage build`; never maintain a second
   progress store. Record only current evidence and concise next steps here.

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

The full source-fidelity/three-image objective is unfinished. Both client raw
links, complete data ownership/verification, unknown code ranges and faithful
reconstruction of discarded server inputs remain open. Existing inferred server
link inputs do not establish original source merely because the raw DLL matches.

Guild checkpoints e24b9311 (Rebrew 3 migration), 86560789 (raw server/provider
repairs), 14b5140d (CLI guidance) and de00f948 (shared lighting) are committed
and pushed. The migration audit
preserves all 8,376 identities/bindings/extents and non-comment tokens in 3,836
C/header files. cm_ExProdObjekt is restored to its attested command.c position:
its isolated object matched, but splitting it changed 30,085 raw bytes and drifted
32 data rows. Do not split an attested TU merely to quiet conflicting target order.
Six acyclic units have reviewed definition orders and retain their tested bodies.

The complete frozen baseline corpus is terminal with zero game compiler errors,
clearing the earlier 27 timeouts. Byte matches: server 316/316, TL 3597/3693 and
Gold 2098/2540. No checkpoint EXACT/RELOC identity is lost, and all 3,973 source/
configuration inputs stay unchanged during that run. Receipts:
.scratch/goal29/corpus-current.json and .scratch/goal31/terminal-corpus-audit.json.
All three coverage documents were regenerated before the new helper integration.
Gold compiled libraries were 14/15; the incorrect 5e3a71 C copy is now retired.
Function/object comparisons do not establish client raw-file or data identity.

The shared UpdateSceneLighting integration now uses one C89 definition for
TL450a00/Gold453890, with only Gold's evidenced flag-dependent branches. Its
original spelling, prefix and unit remain unattested; client_lighting.h is an
inferred canonical interface. Fresh complete native proof retains all 38/128
bytes and twenty operands; fourteen wrong bindings reject. Seventeen current
target/source comparisons pass, including all changed helper users, the reset
and the sound caller. All thirteen named helper transfers validate their native
targets. The byte-width interface retains the TL implementation's ignored flag.
Receipts: .scratch/goal31/integrated-helper-native-proof.json,
lighting-users-test-summary.json and integrated-caller-bindings.json.

Seven locked declaration-view updates describe four-byte or one-byte accesses
in zero-filled .data tails. They allocate no storage; backing extents and owners
remain unknown. The existing signed-byte flag is retained. Both scalar/header
registration and shared-definition renaming use Rebrew's managed writers/CLI.
The obsolete TL setter include override is removed; inherited flags are unchanged.
Three audited, unbound Gold duplicates are retired after canonical-provider tests;
backups/receipts remain under .scratch/goal31/retired-duplicate-sources/.
Conflict-filtered data scans had no type conflicts (664/293/260 rows); they did
not prove definition ownership clean. The current full TL scan reports six
existing multiple-definition cases requiring target/provider/scope triage.
Current lint has zero errors and 31 W030 findings in command.c,
alchemistry_logic.c, friedhof_logic.c, spiel.c and loadsave.c. Native source-unit
and ordering evidence is required; keep the attested server composition intact.

The new server gate found the documented upstream CLI migration in the local
CMake call: order-sources --marker is now --module, with an explicit server target.
That call is repaired. The raw rebuild has zero compiler/linker errors and again
equals all 286,720 reference bytes. The fresh full gate is terminal: all 316
functions, 652 data comparisons, raw structure/file identity and Wine checks pass.
Only the 31 known order warnings fail. Receipt:
.scratch/goal31/gate-lighting-restored.log. Coverage is regenerated for the
integrated tree (.scratch/goal31/coverage-lighting-{server,tl,gold}.json).

Upstream provider/split/header/parser repairs d37f4a07, 6e8dbd5e, 2468a895 and
4650b824 are pushed. Gap notes 4567bc35 and the CLI merge 7b0eb0e4 are integrated.
Dossier fixes bee8ada8/a705f40d retain known extents after early returns and exclude
internal jumps from callees while preserving recursion/external tail calls.
Focused suites 65/66 and required full commit/push hooks pass; canonical/remote
main contain a705f40d. Its completed checkout and the stale, clean 3babd2d4 baseline
checkout are removed after process/file-reference audits. Both repositories now
retain only main. New library-result and atomic-view-edit CLI gaps are committed
as 5f730512 in upstream docs/IDEAS-GUILD.md. Its required full-suite push hooks
pass and remote main contains the commit (.scratch/goal31/upstream-feedback-push.log).

The library mismatch is the static __un_inc helper in pristine input.obj; stock
body matching and the __ungetc_lk callee at 5e899f are supported. The project C copy
passes the wrong duplicated argument and has no project callers. It is retired;
the locked identity records attested _un_inc/__un_inc in library_msvcrt.h without
an extern. LIEF confirms STATIC linkage. Complete 23-byte native relocation proof
and a rejecting wrong-callee control pass. Historical comparison evidence and all
unrelated managed rows are preserved. No client raw map/provider is claimed.
Receipts: gold-un-inc-native-proof.json and
retired-duplicate-sources/gold-un-inc-retirement.json under .scratch/goal31/.
Provider audit selects 14 compiled Gold library sources and exactly one helper
header identity with provider unresolved. Fresh all-target lint retains zero
errors and 31 warnings. The terminal cleanup gate passes all 316 game functions,
65 compiled libraries, 652 data comparisons, complete raw-file identity and Wine
checks; only known lint warnings fail. Coverage is regenerated for all targets.
Receipts: .scratch/goal31/gold-un-inc-provider-audit.json,
lint-crt-retirement.json, gate-crt-retirement.log and coverage-crt-*.json.

Shared he_RunProduktion still emits 4,016 vs 3,816 bytes in both clients. Its 456
bounded runs reach all 66 call sites but do not prove exhaustive behavior or byte
identity. The two 450-byte initializer matches remain; native types/event extent
and original placement are unresolved. Preserve prior goal23–goal26 evidence.

TL412d30 now has a real inferred StartObjectTransformAnimation definition,
NEAR_MATCHING230/280 with its native 188-byte frame. Five data operands validate;
callee4339e0 and the Gold counterpart remain unresolved. Its two88-byte frames
and twelve by-value option bytes remain partly initialized. Current-source
angr/VEX comparison passes96 bounded cases including64 call paths and callee
player-pointer changes; wrong-position control rejects. This is no exhaustive
or byte proof. Private frame/flag type bindings and two initialized-data declaration
views are recorded through managed writers. Native owners/original unit are unknown.
Receipts: .scratch/goal32/integrated-transition-test.json, transition-trace-proof.json,
transition-extents.json and frame/flags-type-bind.json. The locked UEFI1.11 source
build repairs angr's import; pyproject.toml prevents the broken CPython3.10 wheel
from returning under3.13. Upstream ae530804 records the call-input proof gap;
its full-suite push check is running (session94348, upstream-call-gap-push.log).
All ten existing TL users pass fresh comparisons without lost byte matches.
The terminal new server gate passes316 functions,652 data comparisons, full
raw identity and Wine/library/profile checks; only the31 ordering warnings fail.
Receipts: .scratch/goal32/transition-users-audit.json and gate-transition.log.

Next: resolve the six full data definition reports, distinguish target-selected
definitions from genuine duplicate storage, and complete source-unit/type/data
evidence and raw-link providers;
recover genuine discarded server inputs and client code, and build both raw clients.
Keep the original completion criteria and the goal active.

## History

[Archived checkpoints](docs/goal-history.md) preserve the previous goal file in
full. They are historical evidence, not current status or instructions. Keep this
file concise: replace the current continuation when it changes; write detailed
chronology to `docs/TODO.md` and evidence to its owning document.
