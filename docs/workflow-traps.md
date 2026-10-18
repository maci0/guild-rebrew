# Workflow traps

Process findings, keyed by their original section numbers. Historical command
names and counts are evidence, not current instructions; `--no-cache` replaces
the old `verify --full` spelling. Use [AGENTS.md](../AGENTS.md),
[the tooling map](tooling-upstream.md) and current CLI help. Full experiments
remain in the [archive](goal-history.md#full-notebooks).

## Index

| Question | Sections |
| --- | --- |
| Parallel work, scope, and looking up the existing finding first | 1, 2, 3, 9, 10 |
| Declarations, operands, slack, and stale notes | 3b, 3c, 6, 11, 12, 14, 16, 17 |
| A completion check has to reject a bad input | 4 |
| Isolated sweeps, stale objects, and explicit targets | 7, 13, 15, 20, 23, 24, 25, 28 |
| Same-target names and contract audits | the two 2026-10-16 notes |
| Retired command named in the old heading | 5, 8, 19, 21, 22, 26, 27 |

## 1. Agent concurrency

When parallel work is authorized, assign disjoint files and serialize linked
measurements. Do not measure while inputs change. Keep probes outside `src/`
(build globs may compile them), stage named paths, and verify coordinator-side
linked results. Read the existing finding before writing a probe brief.

## 2. Scope constraints that closed options

Use the current [project rules](../AGENTS.md) and [objective](../goal.md).
Assembly requires positive original-assembly evidence; library attribution and
provider evidence are separate. Earlier split-link exclusions are historical,
not current scope restrictions. A score improvement cannot justify incorrect C.

## 3. Errors made during this work, kept on the record

Check header declarations against every affected definition before widening
includes. A single-TU byte-neutral probe cannot establish all callers compile.
Native code extent and padded COMDAT capacity are separate; use the right ruler.
When a local tooling edit breaks a build, test that edit first. Historical recovery
recipes and old proxy counts are in the [archive](goal-history.md#full-notebooks).

## 3b. A declaration is not a definition: sweep for undefined `extern` operands (round 924)

A compile, lint pass and unchanged object size can hide an undefined or wrong
operand. Check definitions, selected providers and native relocation targets.
`gm_Open` pushes the same `0x10031004` string at eleven sites: it needed the shared
symbol's definition, whereas `cm_ExSellObjekt` needed a per-site literal.
Do not replace a shared symbol with literals without reading native pushes.

## 3c. `rebrew data list`'s type-conflict list is a signal, not a work queue (round 925)

Triage type conflicts by ownership and native width, not count. The historical
`loadsave3.c` correction matched the scalar layout at `0x10030b84` but regressed
linked bytes; preserve both observations. Differing declaration views do not
establish duplicate storage. An owning C89 array definition needs an explicit
extent; use `extern` for declarations.

## 4. An objective criterion with no check will silently stay unverified (round 934)

Map every completion criterion to a deciding check and prove the check rejects
bad input. The original gate omitted DLL loading; a truncated 4,096-byte control
then failed while the real image resolved both `Init` and `Exit`. Green tests
cannot certify a criterion they never inspect.

## 5. `rebrew library match` without `--allow` is not a finding (round 947)

Historical library scans lacked the then-configured displacement allowlist and
misreported twenty known local providers. Read selected archives, callers and
recorded reasons before deleting source. Old allowlist paths/options are retired;
current CLI help and raw-map evidence decide provider attribution.

## 6. A header records a true observation about a compilation that no longer exists (rounds 940, 955-957)

Source-header notes describe their measured inputs. Recheck current code and
bytes before using an old rejected variant, opcode description or score. Retract
only the stale claim: the same paragraph can retain valid root-cause evidence.
Examples: `gm_AllocGebaeude`, `ServerMainThread`, `srv_LoadBuf` and
`ahm_ExAllocAlchemist`, rounds 940/955–957.

## 7. A sweep that rewrites a tracked file must be killable and self-restoring (round 966)

Run mutating sweeps in isolated scratch. Preserve/restore inputs on failure,
track owned process IDs and avoid broad kill patterns that match their own shell.
Restore/rebuild production objects before linked measurement. A candidate left in
the tree or a stale object invalidates the reported delta.

## 8. Probe history lives in TWO places; `whathas.py` indexes only one (round 978)

The retired `whathas.py` searched docs, missing source-header experiments.
Use `rebrew source findings` and inspect the function's own notes, metadata and
scratch receipts. No search hit means no indexed hit, not unworked code.
`ahm_ExAllocAlchemist` at `0x1000bebc` was the measured counterexample.

## 9. The round-978 rule was written and then broken in the same session (round 979)

Look up the first structural fault and its surrounding window, not only the
first shifted symptom. Round 979 repeated three recorded `ServerMainThread`
probes after skipping its source header; symptom `+0x3c7` followed the real fault
at `+0x454` (different encoding width for the `0x101deac0` load).

## 10. Four wasted rounds share one cause: no opening step forced the lookup (round 981)

Read address findings and the source header, then compare the current
instructions, before probing. Rounds 976–981 repeated documented assignment,
guard, packet-order, and `/Os` failures. Reopen an exhausted axis only with new
evidence or changed inputs.

## 11. A stale in-source note can describe a state the source no longer has (round 982)

Verify the current source actually contains an old optimization and that a
proposed edit changes it. `ls_LoadBuildingEntityState`'s recorded count-read hoist
had been undone; another attempted hoist was a no-op. Distinguish a restored
optimization from a novel mechanism, and report the actual before/after inputs.

## 12. 32 dangling `extern` array declarations are latent hazards; all 7 with scalar stubs are currently inert (round 983)

The round-983 census found dangling extern arrays, including seven scalar-stub
cases that emitted no references in their bound bodies. An unused declaration
is a latent contract hazard, not evidence of current byte corruption. Audit actual
operands, then reconcile canonical declarations without inventing backing storage.

## 13. `cl /FAs` writes its listing to the CWD, not next to `/Fo` (round 984)

VC6 `/FAs` writes its listing into the current working directory, independently
of `/Fo`. Run listing probes in ignored scratch and avoid clobbering another
probe's listing.

## 14. A header's "bankable once N bytes are recovered" can itself be stale (round 986)

A header's “bankable once N bytes are recovered” delta is historical. Measure
current executable length and the linked result before budgeting an edit.
Capacity and profitable changes are separate; see §16.

## 15. `rebrew test --json` PERSISTS state: including a per-function toolchain pin (round 997)

JSON does not imply read-only. `test` and `verify` can persist comparison
results; experimental toolchain/flag overrides may alter managed inputs.
Read current help and use supported `--no-promote`/preview modes for probes.
Never restore managed stores by hand. The old “verify only reads” conclusion
was incorrect for current Rebrew.

## 16. A header's "unused slack" figure was CORRECT: the check that "disproved" it was tautological (rounds 998, 1017, 1018)

COMDAT raw size can equal the native span because of trailing NOPs, hiding
unused capacity. Measure the real return, reachable branches and padding.
`cm_ExProdObjekt` genuinely had fifteen bytes of slack, yet its tested edit
worsened linked residue by thirteen. Headroom alone establishes no win.

## 17. A stale inventory is not a coverage gap: check the annotations before claiming missing functions (rounds 1021-1024, corrected round 1037)

Compare authoritative source bindings with inventory spans before declaring
missing functions. The twelve coarse command spans already contained 25 bound
functions; only known `cm_ExSellObjekt` had residue. See the corrected census in
[build facts](general-knowledge.md). A proxy partition cannot prove source absence.

## 19. `rebrew todo`'s 20 items are 2 real carriers and 18 false positives: verified again (rounds 955, 1038)

Round 1038's todo listed eighteen IAT slots at `0x10024000..0x10024044` that
were already equal in the postlinked image. That queue and its counts are
obsolete. Linker-owned imports, postlink-supplied bytes, and native
reconstruction are different facts. Current accounting is [TODO.md](TODO.md).

## 20. `build/` is gitignored, so a hand-edited `build.make` is invisible to every check (round 1051)

Ignored `build.make` is generated input, not an authoritative configuration.
A hand edit can change compiler behavior while Git and source checks remain
clean. Regenerate from tracked CMake/toolchain inputs and compare the actual
compile command before interpreting a regression.

## 21. A misleading error message is a defect: postlink's `.rdata` prefix check named one cause and hid the measurement (round 1053)

Diagnostics must report measured values and the failing invariant. The retired
postlink prefix error blamed `/DEBUG` when the observed problem was simply a
prefix-length mismatch. Preserve alternate causes; do not turn one hypothesis
into the error message.

## 22. Inserting a `for ... else` mid-body dedents the rest of the loop, and no other check sees it (round 1055)

A misplaced Python `for ... else` can move work outside a loop while remaining
syntactically valid. In the retired `emit_defs.py` experiment it broke the
definition fixed point. Check the connected control flow and add a regression
that exercises multiple iterations, not just parser/lint success.

## 23. A read-only metadata file is rebrew's WRITE-LOCK, not a bug: the CLI is meant to write it (round 1060, corrected round 1061)

Read-only managed TOML is intentional: locked atomic writers replace it and
restore mode `0444`. CLI writes are not a permission bug. Use Rebrew's managed
writers exclusively; the historical chmod-and-hand-edit recovery advice is
superseded by current project rules. Function identity is format 3
`rebrew-functions.toml`, including `[source.definitions]` and `[source.files]`.
Data rows stay format 2 `rebrew-data.toml`. The separate source store is retired.

## 24. Some source experiments need a full object rebuild to recover from, and `linktest.sh` cannot tell you (round 1064)

A source experiment can pull a different library member into the link and
invalidate the whole composition. The historical out-of-line memset control for
`gm_AllocSpieler` failed before any comparable residue existed. Restore all
inputs and rebuild affected objects before treating subsequent numbers as a baseline.

## 25. `rebrew source rename` leaves the CMake tree stale, and both guards miss it (round 1080)

Renaming source does not update a cached object graph by itself. Reconfigure
CMake from tracked inputs, then rebuild and verify every affected target.
The configured backend is unshare over the pinned toolchain image filesystem;
CMake and `verify` both use it. Retired split-link exit codes and SP6 configure
recipes are historical. Keep `REBREW_DEBUG_INFO=OFF` for link checks.

<a id="26-cmake---build-build---target-final-needed-two-passes-after-a-clean-configure-and-reported-a-fake-residue-of-86676-round-1102"></a>

## 26. The retired `final` target hid a failed first build (round 1102)

The retired nested `final` target swallowed an early parallel-build failure
and linked an incomplete object set, fabricating an 86,676-byte residue. Require
successful prerequisite builds and a complete input inventory before measuring.
A second pass succeeding does not excuse a broken first-build dependency graph.

## 27. The GOLDTL client statically links D3DX8: run `lib-match` against `d3dx8.lib`, not just LIBCMT (round 1143)

Check every plausible static library, not only LIBCMT. Use
`rebrew library match` ([tooling map](tooling-upstream.md)); the heading's
`lib-match` name is historical. The historical D3DX8
scan found the TL band `0x5e0000..0x64ffff` plus stubs at `0x45fa70` and
`0x460a40`. Whole-body and short-prefix/template evidence are different strengths;
resolve native operands/callees before assigning identity, and selected providers
through the raw map. Imports alone cannot reveal statically linked code.

## 28. Pin both the CMake toolchain and the verification target (2026-10-15)

A generated toolchain used to advertise the requested profile but invoke bare
`rebrew build driver` commands. The driver then selected the environment or root
compiler profile instead. Upstream a2b40b43 pins all three generated tool commands;
a later per-file pin overrides the generated default, and neither marker reaches
CL/LINK/LIB. Make/Ninja integration tests and driver precedence tests reproduce the
old failures. Regenerate the toolchain files and configure with `cmake --fresh`:
CMake's existing `CMakeCCompiler.cmake` can retain the old compiler arguments after
an ordinary reconfigure.

The project default target is independent. With TL selected, the server's old
`cmake-flags` call resolved client rows and rejected mixed flags; the server gate
and `final` target also implicitly selected TL for a server DLL. The recorded
fix selects `server.dll` explicitly. Changing the interactive default must not change
server build inputs or select a different reference for its verification.

### Same-target names need reviewed reference ownership (2026-10-16)

Two independent definitions can share a C name even within one target. Select
the definition by MODULE.0xVA and preview `source rename --shared-definition`
with a `--reference-owner FILE=MODULE.0xVA` for every ambiguous reference file.
Review the exact inputs and apply with `--expected-digest`; a file with mixed
ownership remains unsupported. Whole-file ownership is a source claim, not
native call proof. Decode actual target destinations and reverify all bound
contexts; never recover a rejected verdict by suppressing known-binding checks.
Goal53 retains both algorithms and all four logical-reset reference files,
recovering TL 0x5392a0 only after its actual 0x5012b0 callee is unambiguous.

### Run contract audits after metadata writes finish (2026-10-16)

Goal54's contract audit refuses when concurrent verification changes its
managed-store inputs. Keep that failed receipt. Finish verification, then rerun
against stable inputs and check every recorded input hash. At that checkpoint,
five focused audits had zero findings and still listed SDK/include unknowns
(server 122, TL 904, Gold 616). Those counts are not current project status, and
they are not complete contract verification. The checkpoint recorded an open
upstream SDK-context gap. Do not weaken the exact-input guard to skip it.
