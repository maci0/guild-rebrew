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
- **Do not re-derive the CMake configure command — read `scripts/build-win.sh` (round 917).**
  Recovering from a failed experiment I ran
  `rm -rf build && cmake -S . -B build -DREBREW_DEBUG_INFO=OFF`, **omitting `--toolchain
  cmake/toolchain-msvc-6.0-sp6-docker.cmake`**. CMake silently configured for the *host* compiler and
  the whole tree failed with `windows.h: No such file or directory` — 27 build errors that look like
  a source catastrophe and are nothing of the sort. The correct invocation is in `build-win.sh`
  lines 59-62. **`build/` is a derived directory with non-obvious required flags; delete it only via
  that script.** Recovery cost three gate runs on top of the mistake, because a fresh configure also
  surfaces the known `C1001` — `C1083` transients before a serial rebuild clears them.
- **Before lifting a duplicated `extern`, find its *defining* TU, and stop if that TU is the
  BSS-commons block (round 917).** Lifting `g_current_season` — declared in 16 TUs, so a perfect
  candidate by every other test — took residue from **8,634 to 91,327** and demoted a function. Its
  definition lives in `gm_NextEntityQueryMatch.c:185`, inside the block commented *"Round-558:
  same-size majority types that still emit BSS commons. Incomplete `[]` does not emit; sized arrays
  broke .text layout."* That TU **cannot include a header** without changing what it emits, so moving
  the declaration left the definition unattached. **The check is one grep:**
  `grep -rn '^[a-z].* g_<name>;' src/server.dll/`. Neither the `LONG` label (round 916) nor
  "zero slack" predicts this — only the definition's location does.
- **Three pre-checks for a declaration lift, and where each came from.** All three are needed; the
  first two cost a reverted batch apiece to learn:
  1. **one identical spelling** across every declaring TU — otherwise the TUs disagree and it is a
     type-conflict question, not a lift;
  2. **the defining TU is not the BSS-commons block** (`gm_NextEntityQueryMatch.c`, the "Round-558"
     comment) — moving the declaration leaves the definition unattached and the link reshuffles
     (round 917: residue 8,634 → 91,327);
  3. **the header agrees with every TU that will newly see it** (round 911: `C2371`).
  **And a warning about the filter itself:** the candidate scan that applies these has been wrong
  twice — a regex missed `int x = 0;` and reported 17 symbols as undefined, then placed a definition
  in the wrong TU. **Use it to order candidates, not to decide.** The decision is lift → build →
  gate.
- **Check the *size* of a work-vein before spending rounds in it (round 918).** Five rounds
  (909-913) went into a declaration-lift refactor before anyone counted the population: of 44
  candidate symbols, **6 are blocked, 31 have a single declaration site** (not a dedup), leaving ~7.
  Fifteen symbols were lifted at zero byte cost. **One `rebrew data --json` query would have shown
  the vein was nearly empty before the third failed batch.** When a vein's payoff is "provably
  byte-neutral", that is a signal it is not on the critical path — measure the population first.

## 3b. A declaration is not a definition: sweep for undefined `extern` operands (round 924)

Two `gate.sh` checks and `rebrew lint` can all be green while a translation unit references a symbol
that **does not exist anywhere**. `extern char name[];` at the top of a file, never defined in the
tree and never named in `src/rebrew-data.toml` — and then *used* — decays to an operand the compiler
cannot relocate. The emitted bytes are wrong, and nothing reports it:

- `rebrew lint` passes: the identity header and marker contract are about the function, not its operands.
- the compile passes: at worst a warning, and `C4013` for a missing *function*.
- **the object size is unchanged** — measured on `cm_ExSellObjekt`, `.text` was `0x810` both with the
  broken operand and with the fix. So every size-based ruler is blind to it.
- only the `.text` residue moves (and, when the operand was a string, the raw-link `.data` too).

**Run this before believing a file is finished:**

```
python3 - <<'PY'
import re, glob
defined=set()
for p in glob.glob('src/**/*.c')+glob.glob('src/**/*.h'):
    t=open(p,errors='replace').read()
    for m in re.finditer(r'^\s*(?!extern\b|static\b)[A-Za-z_][\w \t\*]*\b(\w+)\s*(\[[^\]]*\]|=[^;]*)\s*;',t,re.M):
        defined.add(m.group(1))
meta=set(re.findall(r'name\s*=\s*"(\w+)"',open('src/rebrew-data.toml').read()))
for p in glob.glob('src/**/*.c'):
    code=re.sub(r'//[^\n]*','',re.sub(r'/\*.*?\*/','',open(p,errors='replace').read(),flags=re.S))
    for n in set(re.findall(r'^\s*extern\s+[^;]*?\b(\w+)\s*\[',code,re.M)):
        if n not in defined and n not in meta:
            uses=len(re.findall(r'\b%s\b'%n,code))-len(re.findall(r'extern\s+[^;]*\b%s\b'%n,code))
            if uses: print(uses, n, p)
PY
```

Measured round 924: **37 live uses in the `server.dll` tree** (plus 4 data globals — a separate
sub-class worth checking the same way). Strip comments first, or every symbol merely *named in a
docstring* counts as a use and the list is four times too long.

**Do not "fix" these by inlining literals without checking what the reference pushes.** `gm_Open.c`
passed one shared symbol at 11 sites; the reference pushes the **same address** `0x10031004` at every
one of them, so the shared-symbol shape was correct and only its missing definition was the defect.
Two failures in this class, two different correct answers: `cm_ExSellObjekt` needed a literal
(the reference relocates a per-site string), `gm_Open` needed a defined address. Read the reference's
pushes first.


## 3c. `rebrew data`'s type-conflict list is a signal, not a work queue (round 925)

The tool reports 11 conflicts over 342 globals. They are **not** 11 bugs, and triaging them by count
rather than by reading costs rounds in both directions:

- **Three were real wrong-width definitions**, all in the same file and all unused there:
  `char* g_slot_table` against 13 TUs' `unsigned char[]`, `char g_entity_state_base` against two TUs
  indexing it, `char g_entity_type_bytes` against three. All three fixed **byte-neutrally**.
- **One was fixed, measured, and reverted**: the `loadsave3.c` `g_query_filter_extra*` block. The
  scalars the other two TUs use are *provably* the right layout (the reference bytes at `0x10030b84`
  are `ff | ffffffff | ff7f | ff7f | ff`), but rewriting the definitions to match measured
  **+1 residue and +375 raw-link `.data`**. A semantically-correct change that emits *fewer* matching
  bytes is still a loss under this objective.
- **The rest are cosmetic**: `T[]` vs `T[N]` where element type and size agree, a string whose content
  was verified at its VA, and a CRITICAL_SECTION pointer-element vs pointer-to-pointer spelling.

**So sort the list by "do the types disagree on width or only on spelling" before doing anything.**
The cheap discriminator is the reference bytes at each symbol's VA plus a grep for whether the
definition is used in its own file.

**A C89 trap this hit:** `unsigned char g_slot_table[];` at file scope is an *incomplete* tentative
definition and emits **no symbol at all** — 11 `LNK2001`s, not a warning. A defining TU needs an
explicit size even when every declaring TU uses the unsized form.


## 4. An objective criterion with no check will silently stay unverified (round 934)

`gate.sh` had six checks and none of them loaded the DLL. The 100% objective's own done-criteria list
ends with **"Wine load + exports (Init, Exit) resolve"** — and for the whole of this session nothing
verified it. Every round could report "gate pass" while that criterion was untested, which is the
distinction between *green* and *verified*.

**Audit the objective's criteria as a set, not one at a time.** The cheap form: write the done-criteria
list out and mark, next to each, the exact command that decides it. Anything with no command is
unverified regardless of how long the suite has been green.

Two traps met while writing the missing check, both already documented separately and both hit anyway:

- **A check whose failure test is a grep for absence passes on a run that never happened.** v1 ran the
  loader under an unwritable `WINEPREFIX`, so Wine produced no output at all; `grep -q MISSING` found
  nothing and the script printed OK. **Test the exit code and require non-empty output.**
- **A harness limitation looks exactly like a finding.** The same v1 reported
  `LOAD FAILED err=193` (BAD_EXE_FORMAT) for our DLL — and for **the reference DLL too**. When a check
  fails, re-run it against the known-good artefact before believing it: that control cost one command
  and prevented a round being spent "fixing" a non-defect. Here the real cause was Wine's `Z:` path
  handling; copying to a short temp path loads all three DLLs correctly.

**Then prove the new check fails.** A truncated 4,096-byte copy gives exit 1; the real artefact gives
`Init resolved / Exit resolved` and exit 0.


## 5. `rebrew lib-match` without `--allow` is not a finding (round 947)

Run bare, the check reports **20 reversed functions whose bytes come from LIBCMT** and prints
"These do not need reversing: the linker supplies them. Delete the source...". That reads like a serious
scope violation — the exact anti-pattern AGENTS.md opens with. **It is not.** Every one of the 20 is
already recorded in `scripts/library_code_allowlist.txt` with a link-side reason (the `sbh_pool.c` /
`mlock.c` / `crt_heap.c` group, kept because the stock objects drag in imports the reference does not
have).

The allowlist is consumed by `.pre-commit-config.yaml`, which invokes the tool **with** the flag:

```
rebrew lib-match --stock-lib LIBCMT.LIB --allow scripts/library_code_allowlist.txt
```

Run that way the answer is `No reversed function matches a linked library.` — clean.

**So always run the check the way the hook runs it.** A bare invocation is not "the check failing"; it
is a different question being asked. Cross-check coverage directly when in doubt: extract the reported
VAs and confirm each appears in the allowlist (all 20 did, round 947).

```sh
rebrew lib-match --stock-lib LIBCMT.LIB --json > /tmp/lm.json
python3 -c "import json,re; d=json.load(open('/tmp/lm.json')); \
  a=set(m.lower() for m in re.findall(r'0x[0-9a-fA-F]+', open('scripts/library_code_allowlist.txt').read())); \
  print([x['va'] for x in d['findings'] if x['va'].lower() not in a])"
```
