# Workflow traps — agents, concurrency, tooling, past mistakes

Process failures and the errors made along the way. Codegen walls live in
`codegen-walls.md`, measurement traps in `measure-traps.md`.

---

## 1. Agent concurrency

- **File ownership collisions.** Two rounds were broken by launching a fan-out without checking
  which files the running agents held. The protocol is now: call `list_agents`, diff the
  `running` set's file assignments against the new ones, and only then launch.
- **Agents wrote scratch files into `src/`.** `CMakeLists.txt` uses `file(GLOB_RECURSE)`, so a
  probe file dropped there is compiled and linked as an extra object and moves every symbol
  after it. One appeared mid-link-test (it was transient and never reached the link, so the
  measurement held). The glob now excludes a leading `_`.
- **`git add -A` swept an unmeasured agent edit into a commit** once. Commit named paths only.
- **The instruments lived in gitignored `.scratch/`** while being the tools every agent was
  told to use — they would not survive a clean checkout. `ndiff`, `cdiff`, `gaptrace` and
  `reallen2` were promoted to `scripts/`, with the two that assumed the repo root as cwd fixed.
- **Read the doc before writing the brief.** A mission brief inverted a documented mechanism
  (told an agent to *add* `volatile` to get the reference's `xor`/`mov` form; shapes §52 says
  the opposite). Fourteen probes refuted the brief, not the mechanism.
- **Never measure while agents write.** Two full-rebuild rounds returned 0/319 and 37%
  differing because several writers were active; the mechanism was misdiagnosed twice as
  compiler flags and a response-file difference before the real cause was found.
- **Agents cannot link-test** (link measurement is serialized), so they rank candidates on the
  object metrics that mispredict. Every delivery needs a coordinator link test — the bottleneck
  is measurement, not agent count.

## 2. Scope constraints that closed options

- **C only, no `__asm`** except where the original had hand-written assembly. Directly forbade
  the largest measured lever (codegen-walls §6). One pre-existing `__asm` block-fill is
  admissible because the original contains a 24-byte hand-written fill prelude there.
- **Do not reverse zlib or LIBCMT** — they are linked in. (`rebrew lib-match` is the check;
  FLIRT finds only 9 of the 68 functions that turned out to be stock LIBCMT.)
- **Library code and the CRT region are out of scope**, so the crt-region objects' "LONG"
  reports and the split-symbol drift are not the objective.
- **Correctness versus the metric.** One real bug (swapped `AnalyzeInstruction` arguments on
  `CrashDump`, which made the callee dereference `nInstr - 5`) was fixed at a **deliberate cost
  of 1 linked byte**, because byte-identity bought with semantically wrong C is a false match.
  Conversely a `volatile` byte-fitting change was accepted despite a pass recommending against
  it, because `volatile` changes no observable behaviour — the line is semantics, not style.

## 3. Errors made during this work, kept on the record

Each cost real budget and each is the kind of mistake the next attempt would repeat.

- **A wrong size rule was enforced for many rounds.** "The real body must equal the reference's"
  discarded admissible candidates; the true constraint is the padded COMDAT (measure-traps
  §7). Correcting it retracted recorded rejections.
- **A cascade framing was inferred from a ratio and was wrong.** High residue was read as "one
  early encoding shifts the tail", sent to two agents as a mission brief, and both refuted it
  with measurements — `CrashDump`'s first differing byte is a frame *value*, and
  `gm_AllocSpieler`'s gap returns to 0 repeatedly across 168 hunks. Two agent budgets were spent
  at a cliff that was not there.
- **A tool was blamed for what was my own invocation.** A `gaptrace` run with the metadata size
  produced "37 bytes too long, 20 extra instructions", reported as a finding before being
  recognised as an artefact of the truncated window.
- **The same refactor was attempted three times before its real blocker was identified
  (rounds 909-911).** The goal was to lift duplicated `extern` declarations into a shared header —
  plainly right by the mandate, and **byte-neutral when probed on one TU (`linktest.sh` +0)**. It
  failed at 27 symbols, then at one symbol, and the failures were blamed first on the pinned
  toolchains and then on include plumbing. **The actual cause surfaced only on the third attempt:
  the target header is not inert.** `entity.h` declared `gm_ResetAllEntities` returning `int` while
  the defining TU had `void`, so *including* the header converted a silent disagreement into
  `C2371: redefinition; different basic types`. Nothing had ever compared them, because no TU that
  defines the function includes the header.
  **Two lessons.** (1) Before widening a header's use, grep its declared names against the tree and
  check they agree with every definition that will newly see it — one command, and it would have
  replaced three rounds. (2) A `+0` probe on a single TU certifies only the axis it measured: an
  `extern` line cannot move `.text`, so the probe said nothing about whether the header *compiles*
  against the TUs it was entering.
  The blocker is now stated precisely rather than worked around: make the header agree with every
  TU first, per declaration, then widen its use.
  **Resolved in round 912.** The check — every `extern` function declaration in every header against
  every definition tree-wide — returned **0 disagreements**, and with that the lift landed: 9 symbols,
  20 files, 84 declarations removed, **byte-neutral at the gate**. So the sequence is: *check the
  header against the tree first, then move declarations in measured batches.* The check is one grep
  and would have replaced three rounds.
