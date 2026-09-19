# Workflow traps — agents, concurrency, tooling, past mistakes

Process failures and the errors made along the way. Codegen walls live in
`codegen-walls.md`, measurement traps in `measure-traps.md` (start at §1:
only the linked residue decides). Constraint cost of the C-only / no-asm
rule is walls §6b.

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


## 6. A header records a true observation about a compilation that no longer exists (rounds 940, 955-957)

Three separate instances in three rounds, each found by checking a header claim against the **current**
object rather than trusting the note:

| round | file | the claim | what the binary says now |
|---|---|---|---|
| 940 | `gm_AllocGebaeude.c` | lists `switch (s.type_id)` and the in-loop `gm_AllocRaum` among **rejected** probes | both were later **adopted**; line 309 reads `switch (s.type_id)` and `0x1001771b` is byte-identical |
| 955-956 | `ServerMainThread.c`, `srv_LoadBuf.c` | describe the target's `lea` "against our `add`" | `ServerMainThread`: the direction was **backwards** (target has the `lea`); `srv_LoadBuf`: we emit **no `add` at all**, both sides have the identical `lea` |
| 957 | `ahm_ExAllocAlchemist.c` | "our baseline emits `d905b8560210 fld [0x100256b8]`" | that byte sequence **does not occur anywhere in the build**; both sides now emit the reference's order |

**The class.** Headers here are meticulous about *what was measured* — compile counts, scores, byte
sequences — and that is exactly why a stale one is dangerous: it reads as evidence. But an entry is a
snapshot of one compilation, and the source moves underneath it. Round 952's own file states the
principle for rejections ("a rejection is only valid for the compilation it was measured on"); the same
applies to **every** claim, including direction, baseline bytes, and which of two spellings is shipped.

**The guard, and it is cheap:**

1. Grep the carrier for verifiable claims — hex byte runs, `where we emit` / `against our`, `rejected`,
   `not adopted`.
2. **Decode each image from its own entry point** (decoding the reference at our VA yields garbage and
   coincidental matches — this produced a false `lea`/`add` "match" in round 955).
3. Compare against the current object. Where they disagree, **the binary wins**, and the note gets an
   inline STALE marker with the address and the measurement.

**Do not blanket-retract.** In round 957 the stale sub-item sat in the same paragraph as a root-cause
claim that re-verified exactly (`dec1 faddp st(1)` vs `d8c1 fadd st(1)` at `0x1000c034`). Annotate the
part that moved; keep the part that did not.


## 7. A sweep that rewrites a tracked file must be killable and self-restoring (round 966)

The permutation sweep from round 964 works by **rewriting `cm_ExSellObjekt.c` once per candidate** and
compiling it. That is a reasonable design — 0.85 s per point instead of minutes — but it has two hazards
that both materialised in round 966:

- **The file is dirty for the whole run.** `git status` shows the carrier modified, and anything reading
  the tree during the sweep (or a crash) sees a candidate, not the shipped source. The harness restores
  the original in a `finally:`/trailing write — keep that, and verify with `git status` afterwards.
- **Killing the job can orphan a compiler.** Cancelling the background job did not stop the running
  `rebrew-cmake-cl`; a follow-up `pkill -9 -f rebrew-cmake-cl` then **matched the killing shell itself**
  (the pattern appears in its own command line) and SIGKILLed the tool call. Use a pid file, or match on
  something the harness does not contain, and check `pgrep -af` before and after.

**Costs, measured, for planning a sweep:** single TU compile **0.85 s**; a best-improvement hill-climb pass
over 9 items is 36 candidates per sweep, ~28 accepted moves, so **~15 minutes per restart**. Budget the
search, not just the compile.

**Always end a mutating sweep by restoring the source and re-running the gate** — a sweep that leaves a
candidate in the tree, or a stale object in `build/`, produces a residue reading that has nothing to do
with what is committed.

## 8. Probe history lives in TWO places; `whathas.py` indexes only one (round 978)

`scripts/whathas.py` searches the four codegen docs, `naming_conventions.md` and `TODO.md` — all under
`docs/`. But a carrier's probe history is also, and often *only*, in the **header comment of its own `.c`
file**: the instruction pair, the probe variants, and the score each one produced. `whathas.py` cannot see
any of that, and neither can a `grep` of `docs/`.

**Measured on `ahm_ExAllocAlchemist`.** `whathas.py 0x1000bebc --window 48` reports *"no documented probe
in 6 docs"*, which reads as an untouched carrier. The divergence is in fact fully documented in the file
header, `src/server.dll/DieGildeAddOn/game/alchemy_logic_c/ahm_ExAllocAlchemist.c:63-70`, including the
exact instruction pair (`lea edx,[eax+eax*8]` against `lea eax,[eax+eax*8]`) and the exact probe that
tests it, measured at **109** against a shipped **452**.

**Two carriers' whole histories are like this**, and both are small — which is why they were missed: a
small function's probe history fits in its header comment, so it never earned a `docs/` entry.
`cm_ProcessCommandQueue` (18 rounds of history, `cm_ProcessCommandQueue.c:100-320`) and `srv_LoadBuf`
(round 956) are the same shape.

**The cost is concrete.** Round 976 opened by probing two carriers that were already closed in-source —
`srv_LoadBuf`'s `header[0xb]`/`header[0xc]` order (documented in its own header) and `m_AllocTracked`'s
guard order (bisected in its header, allocator Finding 51). Both probes ran, both were reverted, and
neither could have landed: **+574** and **+539**.

**The rule.** Before probing a carrier, read both stores:

```bash
python3 scripts/whathas.py 0x<va> --window 48    # docs/ only — necessary, not sufficient
sed -n '1,120p' ""<carrier>.c                    # the per-file header, always
```

Treat "no documented probe" from `whathas.py` as *"no `docs/` entry"*, never as *"unworked"*. The round
brief's own wording — read the file header before probing, since "no documented probe" is not proof of
novelty — already says this; round 976 is what happens when only the tool is consulted.

## 9. The round-978 rule was written and then broken in the same session (round 979)

Round 978 established: *"no documented probe" from `whathas.py` means "no `docs/` entry", never
"unworked" — read the carrier's `.c` header too* (workflow-traps §8). Round 979 read the tool, skipped the
header, and spent its budget re-deriving three already-recorded results.

**What happened.** Working `ServerMainThread` (classified source-bound by the sp5-pp oracle, §91), the
first-divergence table gave `+0x3c7`, and byte analysis narrowed the real fault to `+0x454`: the reference
emits `mov ecx,[0x101deac0]` (6B) where we emit `mov eax,[0x101deac0]` (5B), desyncing the downstream
block by 3. Three probes followed, all reverted:

| probe | link delta |
|---|---|
| named `unsigned char* qbuf` alias for `cmd_buffer_primary` across the stores | **+0** (byte-identical — msvc6 folds the alias) |
| the same alias assigned *before* the `total_size` load | **+0** (byte-identical) |
| `total_size` load moved below the first four stores | **+861** |

All three were already recorded. The fault is `docs/msvc6-c-shapes.md` **§126** ("`ServerMainThread`'s +3
window: a rematerialised constant the reference carries in a register"), which names the exact site
(`0x100097fb  mov [esp+0x1c],eax` against our 8-byte `mov [esp+0x14],0xffffffff`), explains the mechanism,
and already carries the `volatile` probe table that settles it (store `volatile` load-bearing, +4 if
dropped; read `volatile` inert, +0). The alias-fold result is the same one `ahm_ExAllocAlchemist.c:63-70`
records. And the file's own header at `ServerMainThread.c:122-129` states the mechanism verbatim: *"msvc6
propagates the compared constant into the cmd+4 store … Moving the comparison off `sent_bytes` removes the
propagation but also hoists the cmd+0x10 store ahead of the argument pushes, so neither spelling matches
yet."*

`whathas.py 0x100097f4` **does** return a hit — shapes §126. The tool was not at fault this time; it was
consulted on `0x10009767` (the branch-displacement symptom) rather than on `0x100097f4` (the fault), and
the symptom's four `TODO.md` hits read as "known, unprobed".

**The refined rule.** On this tree the *first differing byte* is usually a **symptom**, and a symptom whose
target is displaced will not be documented. Find the fault — the lowest byte where the two **instruction
streams** stop agreeing, not where the first byte differs — and look *that* address up before probing:

```bash
python3 scripts/first_divergence.py <symbol>        # symptom: lowest differing byte
# then decode both sides and find the first STRUCTURALLY different instruction
python3 scripts/whathas.py <that fault address> --window 48
sed -n '1,140p' <carrier>.c                          # §8's second store
```

On `ServerMainThread` the symptom address had 6 hits and the fault address had 3, one of them the
dedicated section. Looking up the symptom instead of the fault is what made a fully-closed carrier read as
open.

## 10. Four wasted rounds share one cause: no opening step forced the lookup (round 981)

Rounds 976-981 each spent their budget probing a carrier or axis whose result was **already recorded**:

| round | probe | result | where it was already written |
|---|---|---|---|
| 976 | `srv_LoadBuf` assignment order | +574 | `srv_LoadBuf.c` header (round 956) |
| 976 | `m_AllocTracked` guard order | +539 | `m_AllocTracked.c` header, allocator Finding 51 |
| 979 | `ServerMainThread` packet block (three spellings) | +0, +0, +861 | `ServerMainThread.c:122-129`, shapes §126 |
| 981 | `/Os` on `gm_AllocSpieler` | **+0xbfae** | shapes §3639-3640, §1966, codegen-walls §77 |

Every result was in `docs/` **or** in the carrier's own `.c` header. Both rules existed before the failures —
workflow-traps §8 ("read the file header too") and §9 ("look up the fault address, not the symptom"). They
were written and then not followed, four times.

**So the defect is procedural, not informational.** Writing a fifth rule changes nothing; what was missing is
a step in the round's *opening* that cannot be skipped. `scripts/preprobe.sh <carrier.c> [fault-addr]` is that
step — it runs the `docs/` lookup, then greps the carrier's own header for the words that mark a closed lane
(`revert`, `inert`, `worse`, `measured`, `closed`, `do not`, `dead end`, `section N`), and prints the
fault-vs-symptom reminder:

```
$ bash scripts/preprobe.sh src/server.dll/.../gm_AllocSpieler.c
== 1. docs/ lookup (whathas.py)
0x10018850: 30 documented mention(s) (window 48)
  [49. A CFLAGS sweep on one function: inert, negative, and one near miss]
  [58. `/Ox` versus `/O2` is per-file and load-bearing]
  [109. gm_AllocSpieler's first fault is a scheduler sink, not a statement order]
...
== 2. the carrier's OWN HEADER -- whathas.py does NOT index this (workflow-traps 8)
```

Run it as the **first command** of any round that names a carrier. It costs seconds; the four probes above
cost most of four rounds. A round that has not run it has not established that its probe is novel.

**A generalisation worth keeping.** This tree has accumulated enough probe history that *most plausible moves
are already measured*. The expected value of a probe now depends far more on checking the record than on the
probe's design — the opposite of the position in the early rounds, where the record was thin and probing was
cheap. Rounds should budget for that shift explicitly rather than treating the lookup as an optional courtesy.

## 11. A stale in-source note can describe a state the source no longer has (round 982)

`ls_LoadBuildingEntityState.c:38` records:

```
 * 2026-09-13 (round 130): `current_index = 0;` hoisted ABOVE the
 * aux-count read (was after realloc) — matches reference order
 * (xor-zero, count read, realloc, re-read, test/jle): ... linked 728 -> 675 (-53)
```

**The source does not contain that hoist.** The assignment sits *below* the count read, and it appears
**twice** (lines 80 and 82, separated by a blank line) — a stray duplicate left behind when the hoist was
reverted. Both were measured this round:

| probe | link delta |
|---|---|
| delete the duplicate assignment (keep one, below the read) | **+0** (byte-identical — msvc6 folds it) |
| apply round 130's documented hoist (one assignment, above the read) | **+505** |

So the note's `-53` describes a configuration the file no longer has, and re-applying it is a large
regression. The `-53` was presumably real against the round-130 baseline (which the same header records as
"linked 728"); the tree has since moved to 6xx, and the hoist is no longer a win.

**This is workflow-traps §6's class** ("a header records a true observation about a compilation that no
longer exists") with a sharper edge: §6 was about a *stale claim in a header*, this is a stale claim whose
suggested action is now a −505 regression. A reader who trusted the note and applied it would lose half a
round and 505 bytes.

**Two rules follow.**

1. **Never apply a recorded fix from a note without re-measuring it.** The note records what was true when
   written, against the baseline of that round. Numbers in headers are history, not instructions.
2. **A duplicated statement is a revert artifact, not an optimisation.** `current_index = 0;` twice in a row
   is dead source that should be cleaned — it is byte-neutral here (measured **+0**), so cleaning it is free,
   but it must never be mistaken for a deliberate shape. Grep for adjacent duplicate assignments when reading
   a header that mentions an ordering change.

**Also useful:** the accidental no-op proved a tool works. The first attempt at the hoist had a malformed
match string and silently did not apply; `linktest.sh` printed its round-127 guard
(`NOTE: identical to HEAD, so any delta below is the BASELINE, not a result`) and reported `+0`. That is
exactly the failure §127 built the guard for, caught in the wild.

## 12. 32 dangling `extern` array declarations are latent hazards; all 7 with scalar stubs are currently inert (round 983)

Workflow-traps §3b found one undefined `extern char[]` producing a silently wrong operand (round 924, worth
−355 raw-link `.data`). Round 983 swept the whole class to see whether more remained. **52 `extern ...[]`
declarations in `src/server.dll/` have no definition anywhere in the tree; 32 of those are actually
referenced.** Seven of the 32 resolve to a **scalar** definition in `src/link_stubs.c`, which is the shape
that produces a wrong operand:

| symbol | declared | stub | used as |
|---|---|---|---|
| `g_log_message_buffer` | `char[]` | `char g_log_message_buffer = 0` | `sprintf` destination, `MessageBoxA` text |
| `g_office_role_templates` | `COPY24[]` | `int g_office_role_templates = 0` | array indexed by 24-byte elements |
| `g_field_worker_count_wt0..3` | `int[]` | `int g_... = 0` | indexed limit table |
| `g_error_msg_sell_no_source` | `char[]` | `int g_... = 0` | `LogMessageInternal` message pointer |
| `g_error_msg_sell_no_dest` | `char[]` | `int g_... = 0` | `LogMessageInternal` message pointer |

**All seven are inert today, and the reason is worth recording:** the operand a wrong-type stub produces is
an *address*, and address operands are exactly what the postlink fixer rewrites. Measured on
`g_log_message_buffer`: five `.text` dwords hold `0x117640e0`, and every enclosing function is **RELOC**
(byte-matched) — the stub's address is a relocation slot, not a byte the comparison sees. Only a stub that
changes the *shape* (a size, an instruction form, a displacement) would be visible, and these do not.

So the class is a **latent hazard, not an active defect**: it becomes a real bug the moment such a symbol is
used where the type changes codegen — a `sizeof`, a pointer arithmetic stride, an array index scaling. Two
of the seven are already in that position textually (`g_office_role_templates` indexes with a 24-byte
stride; `g_field_worker_count_wt0` scales by 20), and they are inert only because the enclosing functions
happen to compile correctly anyway.

**The check, cheap enough to keep:**

```bash
# declarations with no definition and a scalar stub -- the round-924 shape
grep -rn 'extern char \w*\[\]' src/server.dll --include=*.c
grep -nE '^\s*(int|char|short)\s+\w+\s*=\s*0;' src/link_stubs.c
```

Treat each hit as a finding to *verify*, not to fix blind: confirm the enclosing function's status first.
If it is RELOC/EXACT the address is a relocation slot and the type is cosmetic; if it is unmatched, the type
may be part of why.

**Also recorded: a `cm_ExSellObjekt` false alarm, self-caught.** Two dangling `extern char[]` at
`cm_ExSellObjekt.c:431,479` looked like extra `LogMessageInternal` calls the reference does not have. Both
sides emit **exactly three** `LogMessageInternal` calls and **exactly six** line-number pushes
(`0x2c05, 0x2c2f, 0x2c53, 0x2c75, 0x2c97, 0x2cdd`) — identical. The sites are dead branches in both. The
initial "our build has 2, reference has 3" reading was a **truncated disassembly window**, the same
off-by-one class as measure-traps §18.

## 13. `cl /FAs` writes its listing to the CWD, not next to `/Fo` (round 984)

The probe rule is "probes go in `.scratch/`, never in the tree." Round 984 broke it without noticing: six
throwaway compilations were run as

```bash
rebrew-cmake-cl /nologo /c /O2 /Gd /MT /FAs /Fo.scratch/align.obj .scratch/align.c
```

which put the object in `.scratch/` **and the assembly listing in the repository root** as `align.asm`,
`align2.asm`, `mstest.asm`, `mstest4.asm`, `mstest5.asm`, `mstest6.asm`. `/FAs` takes no directory: it
writes `<basename>.asm` relative to the **current working directory**, regardless of where `/Fo` points.

`git status` caught them at commit time, six untracked files in the root. Nothing was committed, but a
round that ran `git add -A` without reading `git status --short` would have committed all six.

**The check, before any `git add`:**

```bash
git status --short          # untracked probe artifacts show up here
git add -A docs/ scripts/   # scope the add to what the round actually changed
```

The second line is the one that matters for this project: `git add -A` is how the leak would reach a commit,
and every round here commits only docs (plus the occasional script), so scoping the add costs nothing and
closes the hole.

**Fix for probes:** pass an explicit listing path, `-Fa.scratch/<name>.asm`, or run with
`cd .scratch && rebrew-cmake-cl ... <file>`. Verified locally that `/Fa` with a path does redirect.

## 14. A header's "bankable once N bytes are recovered" can itself be stale (round 986)

`gm_AllocSpieler.c:391-399` records a fix as **costing 11 bytes and being bankable once those bytes are
recovered elsewhere in the citizen path**:

```
 * But it costs 11 bytes (real body 3689 -> 3678), which
 * desyncs the whole tail: matched 766 -> 485, aligned
 * 662 -> 637, rebrew test 1004 -> 648, status STUB ->
 * SIZE_MISMATCH.  Bankable only once those 11 bytes are
 * recovered elsewhere in the citizen path.
```

Round 986 applied exactly that edit (`n = *(int*) 0x1003542c;` then the two stores through `n`) and measured
it at the link:

| metric | claimed by the header | measured (round 986) |
|---|---|---|
| object span | — | **3696, still exactly at span** |
| `.text` residue delta | "costs 11 bytes", i.e. expected ≈ +11 | **+343** |

So the edit is **31x worse than recorded**, and the "recover 11 bytes elsewhere" plan it invites would not
have helped even if the 11 bytes had been found. The header's numbers date from an earlier tree state; the
carrier has since been reshaped (round 941's `/Ow`, the round-178/179 tail fixes), and the same edit now
lands differently.

**This is the third instance of the same class**, and the pattern is now unambiguous:

| round | stale claim | claimed | measured |
|---|---|---|---|
| 982 | `ls_LoadBuildingEntityState` hoist | −53 | **+505** |
| 985 | `gm_AllocSpieler` +16 fix | "bankable" | span still overflowed |
| 986 | `gm_AllocSpieler` 11-byte fix | 11 bytes | **+343** |

**The rule, stated so it stops being relearned:** in this tree, *any* number in a header comment — including
one that describes the cost of a fix rather than the fix itself — is a historical measurement against a
baseline that no longer exists. Treat every recorded delta as a **hypothesis to re-measure**, never as a
budget to plan against. A round that budgets work from a header's byte figure is planning on noise.

`scripts/linktest.sh` makes the re-measurement cost one command; there is no excuse for planning on the
number instead.

## 15. `rebrew test --json` PERSISTS state — including a per-function toolchain pin (round 997)

`rebrew test <file>` reads like a measurement command. It is not: it writes back to
`src/rebrew-functions.toml`. Round 997 ran it with an explicit `--toolchain msvc-6.0-sp5-pp` to test whether a
different backend avoids the epilogue merge (§2), and the tool **persisted the pin into the metadata**:

```
$ rebrew test src/server.dll/.../cm_ExCopyEntityData.c --toolchain msvc-6.0-sp5-pp --json
SIZE persisted → 912
TOOLCHAIN persisted → msvc-6.0-sp5-pp
```

leaving a new line in the tool-owned file:

```diff
 ["SERVER.0x1000ec00"]
 size = 912
 status = "PROVEN"
 blocker = "..."
 blocker_delta = 481
+toolchain = "msvc-6.0-sp5-pp"
```

**Why this matters more than an ordinary stray write.** A per-*function* toolchain pin contradicts this
project's rule that the toolchain is chosen per *translation unit* (`CMakeLists.txt` pins whole files via
`COMPILE_OPTIONS`, and §142 requires every function in the file to survive the switch). `rebrew cmake-flags`
**fails the configure** when one TU's functions resolve to different flags, so committing this line would
have broken the build for a reason with no connection to the change that caused it — and the diff is one line
in a 3,000-line generated file, which is exactly the kind of thing that rides along in a `git add -A`.

Caught by reading the tool's banner output rather than only the JSON, and reverted with
`git checkout -- src/rebrew-functions.toml`.

**The rule.** `rebrew test`, `rebrew match` and `rebrew diff` are **writers**. Before any probe batch:

```bash
git status --short src/rebrew-functions.toml src/rebrew-data.toml   # must be clean before
# ... run probes ...
git diff src/rebrew-functions.toml src/rebrew-data.toml            # must be UNCHANGED after
```

The second check is the one that matters, and it is not covered by `gate.sh` — the gate runs `lint` and
`verify`, neither of which flags a syntactically valid extra metadata key. A probe batch that leaves the
metadata dirty is a probe batch whose measurements may also have been taken under a different backend than
the one the build uses.

**Related:** this is why `rebrew verify --full` is safe to run freely and `rebrew test --toolchain` is not —
`verify` reads, `test` writes.

## 16. A header's "unused slack" figure was CORRECT — the check that "disproved" it was tautological (rounds 998, 1017, 1018)

Workflow-traps §14 established that a header's recorded **delta** is a historical measurement, not a budget.
Round 998 extended that to a recorded **headroom** figure and concluded `cm_ExProdObjekt.c:341-343`'s
"15 bytes of unused slack" was stale, because the object's `.text` raw size equalled the span.

**That conclusion is wrong, and the check that produced it measures nothing.** msvc6 pads a COMDAT to the
span with trailing `nop`s, so `object .text raw == span` holds **by construction** for every function in
its own COMDAT. The comparison cannot distinguish "our code fills the span" from "our code is short and
msvc6 padded it".

Round 1017 repeated the same check on two decoders and confirmed "slack 0" a second time — still
tautological. Round 1018 measured the right quantity, the end of the last non-`nop` instruction:

| carrier | reference code | our code | span | real headroom |
|---|---|---|---|---|
| `cm_ExProdObjekt` | 1008 | **993** | 1008 | **15** |
| `ServerMainThread` | 2434 | 2434 | 2448 | 14 |
| `ls_LoadBuildingEntityState` | 1463 | 1460 | 1472 | 12 |
| `CrashDump`, `cm_ExSellObjekt` | 2115, 2057 | 2120, 2056 | 2128, 2064 | 8 |
| `gm_AllocSpieler` | 3689 | 3689 | 3696 | 7 |
| `srv_LoadBuf` | 750 | 750 | 752 | 2 |

**So the header's 15 bytes were right and three rounds of "correction" were wrong.** The rule that
survives is the opposite of round 998's:

- A recorded **delta** is historical; re-measure it.
- A recorded **headroom** is checkable, but only against the *code end* (`last non-nop end - span`), never
  against the COMDAT's raw size, which is msvc6's padding target and therefore always equal to the span.
- Three methods gave three answers here; only the artefact-based code-end measure is sound
  (measure-traps §34).

**Headroom is capacity, not affordance.** Round 1019 spent `cm_ExProdObjekt`'s 15 bytes on the one
size-neutral variant the header records and it link-tested at **+13**. Having room to grow does not mean a
profitable edit exists. (Round 1020 then closed the aliasing lever on the same row at **+658**.)


## 17. A stale inventory is not a coverage gap — check the annotations before claiming missing functions (rounds 1021-1024, corrected round 1037)

`rebrew verify --full` reports 13 functions whose annotation SIZE differs from the binary-derived size.
Twelve are `command_c/*.c`. Rounds 1021-1024 read this as **missing functions**: first 51, then 10, "hidden
inside over-wide discovery symbols", and built a root-cause story on it (`discover.py`'s `>= 3` padding
threshold) plus a proposed tool fix.

**There are no missing functions.** Every annotated VA inside those twelve spans is implemented and
**byte-identical** — 25 annotated functions, 24 with zero residue, and the only residue is
`cm_ExSellObjekt`'s 966 bytes, a carrier already in the residue table. The ten VAs the earlier rounds named
(`0x1000d340`, `0x1000d730`, `0x1000d930`, `0x1000e750`, `0x1000e9c0`, `0x1000f480`, `0x1000f590`,
`0x1000fad0`, `0x10010080`, `0x10010140`) all have annotations — `cm_RejectCommand`, `cm_ExFree`,
`cm_ExSellObjekt`, `cm_ExAllocObjekt`, `cm_ExSetWohnsitz`, `cm_ExSimCommand` and four more.

**What the size divergence actually is.** `src/server.dll/function_structure.json` holds **543 entries**
against **283 annotated functions** — it is a *coarser* partition, and its entries' sizes are the gap to the
next *inventory* entry, not to the next function. `0x1000d8a0` is one 2008-byte inventory entry while the
tree annotates two functions inside it (`cm_ExTransferCurrencyNoKill` 144 bytes, byte-identical, and
`cm_ExSellObjekt`). So `binary_size > annotation_size` is expected whenever the discoverer merged functions
the annotations already separate.

**The rule.** `function_structure.json` is a **discovery** artefact and is allowed to be coarser than the
annotations; it is not the list of what exists in the reconstruction. Before concluding that a function is
missing, grep the annotations:

```bash
grep -rn "FUNCTION: SERVER 0x<VA>" src/server.dll     # does it exist?
python3 -c "import json;d=json.load(open('src/server.dll/function_structure.json'));print(len(d))"
```

If the VA has an annotation, it is implemented and `rebrew verify` is already scoring it — the size
divergence is an inventory-coarseness fact, and it is not work. **This trap cost four rounds** (1021-1024),
including a proposed upstream tool fix for a defect that does not exist.

**Second-order lesson.** Both rounds that "found" missing functions measured their evidence without ever
asking `rebrew verify`'s own population — the annotation list — for the same VAs. A claim of the form "X is
missing" needs a check against the authoritative list of X, not against a proxy that is known to be coarser.

## 19. `rebrew todo`'s 20 items are 2 real carriers and 18 false positives — verified again (rounds 955, 1038)

`rebrew todo --json` returns 20 `improve-match` / `start-data` items. Round 955 recorded that 18 of them
are `__imp__*` IAT slots and false positives. Round 1038 re-verified that against the binary rather than
trusting the note:

**The 18 `start-data` items are IAT slots at `0x10024000..0x10024044`, and all 18 are already
byte-identical in the shipped file** — read directly, 18 of 18 matching. They appear as "UNCHECKED" because
the dispatcher rewrite installs the reference's IAT, not because anything is undone.

**The two real items are both documented walls, with quantified blockers:**

| VA | name | status | match | recorded blocker |
|---|---|---|---|---|
| `0x10018850` | `_gm_AllocSpieler` | STUB | 27.2% | "132 distributed schedule steps, no cliff; in-hunk clusters are parent-wins 344B, refs-scan 220B, no-parent trait 181B, record-header 140B; ndiff 731/1056 in 171 hunks, cdiff 808/1056 in 156" |
| `0x100093a0` | `_ServerMainThread@4` | NEAR_MATCHING | 85.3% | "already in reference order (16/16 log landmarks byte-identical, zero block reorderings); residual is 3 intra-block scheduling sites + register pairs; ndiff 592/627 in 25 hunks, cdiff 614/627 in 15" |

**The rule.** `rebrew todo`'s ROI ordering carries no signal on this tree — its top-scoring items are IAT
slots that are already correct. Filter to the annotated carriers before reading the list as work, and
re-check the IAT claim against the binary rather than inheriting it: **the 18 are byte-identical, measured,
not assumed.** With that filter the queue is empty except for the two carriers whose walls are recorded
above, both in the same 18-carrier residue set this project has already characterised.

This is workflow-traps §10's "no opening step forced the lookup" in its tooling form: a work queue that is
90% noise will keep generating rounds unless the filter is applied before the queue is read.

## 20. `build/` is gitignored, so a hand-edited `build.make` is invisible to every check (round 1051)

**The trap.** `scripts/linktest.sh` recompiles with the exact command `build.make` records — that is what
makes its deltas comparable to the real build — and `scripts/split_link.sh` consumes the objects that
command produced. Both treat `build.make` as **ground truth**. But `build.make` lives in `build/`, which is
gitignored:

```
.gitignore:20  build/
```

So a round that hand-edits it changes what every later measurement **means**, while:

- `git status` stays clean,
- `rebrew lint` stays clean,
- `rebrew verify --full` is unchanged (it compiles from source, not from `build/`),
- and `cmake --build build` still nominally succeeds.

Nothing in the project could see it. Round 1051 did exactly this while sweeping per-file toolchain pins,
substituting `/REBREW_TOOLCHAIN:<name>` in `build.make` to test the nine msvc6 images. After restoring, the
tree was left measuring **58% residue and a 290,816-byte deliverable**, against the correct **286,720 bytes
and 8628**. The cause was a stale `build/split_poc` plus objects compiled under the swept flags; the fix was
a full `rm -rf build` and reconfigure.

**The fix, now in the tree.** `scripts/build_tree_check.py` compares CMake's own record of each object's
flags against the compile line `build.make` carries:

- CMake regenerates `flags.make` beside `build.make` and records per-object flags there as
  `# Custom flags: <obj>_FLAGS = ...` and `# Custom options: <obj>_OPTIONS = ...`.
- Any codegen flag token (`/` + uppercase) in the compile line that the corresponding Custom comment does
  not list was hand-added.

It is wired into **`gate.sh`** (`== build-tree integrity`, whole tree, fails the gate) and into
**`linktest.sh`** (refuses to measure, exit 4). Verified both directions: silent on the clean tree —
**198 objects compared** — and firing on a single injected `/Ob1` in one object's rule.

**A second bug found while writing the checker, worth recording because it produced a silent pass.**
`parse_recorded` used `re.compile(r"...$")` with **no `re.M` flag**. Without multiline, `$` anchors to
end-of-*string*, so on a `flags.make` containing **202** `Custom` comments it matched **zero** objects — and
the checker then printed "agrees" while comparing nothing. A guard that silently checks nothing is worse than
no guard. The tell was the summary line reading `0 object(s) with recorded flags`; the summary now reports
the count it actually compared, so a zero is visible.

**Also worth keeping:** the composition guard in `linktest.sh` (rounds 232/1051) caught the collapse and
said so, and `cmake --build` failing at POST_BUILD postlink is by design (measure-traps §17) — neither is
the problem. The problem is that no check looked at the *inputs* to those steps.

## 21. A misleading error message is a defect: postlink's `.rdata` prefix check named one cause and hid the measurement (round 1053)

`rebrew.postlink._fix_imports` guards the `.rdata` prefix between the IAT and the import directory
against the layout package's recorded prefix length. When the lengths disagree it raised:

```
built .rdata prefix size does not match the reference — check the debug directory:
builds with /debug carry an extra 0x1c-byte directory that shifts everything
```

**It reports a hypothesis and withholds the numbers.** In guild-rebrew's tree this round the actual
discrepancy was **+64 bytes**, and `DataDirectory[6]` was **0 in both the reference and the built image** —
there was no debug directory at all. The message sent the reader after `/debug` while the real fault was a
different `.rdata` length.

**Fixed in the rebrew checkout** (`src/rebrew/postlink.py`): the error now reports the measured sizes and
distinguishes the two cases:

- **exactly `0x1c` short** → that IS the `/debug` directory, and the original advice applies;
- **any other value** → the built `.rdata` is itself a different length, and the message says to compare
  VirtualSize against the reference and find what added or dropped the bytes.

Measured after the fix, same tree:

```
built 9384 byte(s) between the IAT (0x24000, size 0x1a0) and the import directory (0x26648);
the reference has 9320.
```

**The general point.** A guard's error text is part of its interface. One that names a single hypothesis
and omits the measurement converts a five-minute diagnosis into a wrong lead — and this one is reached by
every round that touches the composition, so the cost recurs. Prefer: *what was measured*, *what was
expected*, and *the distinguishing test between the candidate causes*.

**Companion to workflow-traps §19.** That one is about a work queue that is 90% noise; this is about an
error message that is 100% one hypothesis. Both are cases where the tooling's *reporting* costs more than
its *computation*.

## 22. Inserting a `for ... else` mid-body dedents the rest of the loop — and no other check sees it (round 1055)

**What happened.** Round 1053 added a convergence guard to `scripts/emit_defs.py`, whose definition cascade
loops to a fixed point:

```python
for _round in range(6):
    defined, undefined = scan(...)
    missing = sorted(...)
    print(f"pass {_round}: ...")
    if not missing:
        break
    done.update(missing)

    defs = ...          # the emit work -- part of the loop body
    ...
```

The guard was written as `for ... else`, which must follow the **whole** loop. Inserted right after the
`break`, it terminated the loop body there — the emit code below was silently **dedented out of the loop**.
Python accepts this: no syntax error, no lint warning, no test failure.

**The symptom was two steps removed from the cause.** Definitions were emitted from a single pass instead of
iterating, which grew `.rdata` by `0x40`. `postlink` then refused the build with the `/debug` message
(workflow-traps §21). Round 1054 spent a full round diagnosing that as a "pre-existing composition failure"
— it was this, and it was self-inflicted.

**Why nothing caught it.** The `.rdata` overshoot is only visible at the *end* of the link pipeline, and the
guard that would have reported "did not converge" was the very clause that broke the loop.

**The fixes, both permanent:**

- The guard is now a plain `if missing: raise` **after** the loop, with a comment naming the exact mistake.
- `scripts/gate.sh` gained an **emit_defs fixed-point guard**: `split_link.sh` must report at least 2
  `pass N:` lines, because the cascade genuinely needs iteration (73 missing, then 0). One pass means the
  emit code fell out of the loop. Verified by simulating a pass-less log.

**The rule.** A `for ... else` clause is part of the loop's *structure*, not its body — adding one, or
converting `break`/`else` logic near the end of a loop, is a **control-flow edit to everything after the
insertion point**, not a local addition. When a fixed-point or accumulator loop is edited, check what else
was in the body, and add a check that the loop still *iterates* — not just that it terminates.

**And the honest part:** two rounds were spent reporting this as pre-existing and diagnosing the wrong
layer. A self-inflicted regression is the first hypothesis to test when the tree breaks immediately after
your own tooling edit, and the evidence was available from the start — stashing the edit restored `.rdata`.

## 23. A read-only metadata file is rebrew's WRITE-LOCK, not a bug — the CLI is meant to write it (round 1060, corrected round 1061)

`src/rebrew-functions.toml` and `src/rebrew-data.toml` are mode `0444` in this checkout, and
`rebrew test <file> --cflags "<set>"` writes one of them anyway. Round 1060 recorded that as a bug — a
read-only guard being bypassed. **That was wrong.** It is the designed write-lock discipline
(metadata-review F1), implemented in `rebrew.utils.atomic_write_locked`:

```python
os.chmod(filepath, 0o644)     # chmod before touching the file
try:
    atomic_write_text(filepath, text)      # sibling temp + os.replace
except BaseException:
    os.chmod(filepath, 0o444)              # re-lock on failure
    raise
os.chmod(filepath, 0o444)     # re-lock — direct edits now fail
```

- **A hand edit fails** (`Permission denied`) — the mode stops editors and shell redirects, which is the point.
- **The CLI succeeds by design**: it unlocks, writes, re-locks. The chmod-before is *also* required on Windows,
  where `os.replace` over a read-only target fails, so it is load-bearing for atomicity and not just a policy.
- `os.replace` needing only *directory* write permission (which round 1060 verified directly) is exactly why
  the explicit chmod-before exists.

**So: nothing to fix, and nothing to work around.** Metadata is tool-owned and rebrew is the tool.

**What remains true and useful from round 1060:** `rebrew test --cflags` **persists** a per-function flag pin
as a side effect of measuring (workflow-traps §15), and that pin silently changes the flags the whole tree
resolves for that function — so every later `linktest.sh`/`gate.sh` measurement inherits it. Snapshot
`src/rebrew-functions.toml` before any `--cflags` probe and diff afterwards. The mode is not what protects
you here; the discipline is.

**Re-locking after a manual fix.** If a round needs to undo something in the metadata by hand, it must
`chmod u+w`, edit, then `chmod u-w` to restore `0444` — round 1060 did exactly that and the file's
`git diff` is empty.

## 24. Some source experiments need a full object rebuild to recover from, and `linktest.sh` cannot tell you (round 1064)

**The experiment.** `gm_AllocSpieler` (the largest carrier, 2,823 of 8,628 residue bytes) declares:

```c
#pragma intrinsic(memcpy, memset, strlen, strcpy)
```

Its header repeatedly calls this "the memset call", and §109's mechanism turns on hoisting that call past a
block fill. No round had tried the opposite pragma — forcing a real out-of-line call:

```c
#pragma function(memset)
```

**Both the experiment and its aftermath are the finding.**

- With `#pragma function(memset)`: `linktest.sh` reports **`COMPOSITION COLLAPSED: only 0 symbols landed at
  their reference VA`** (the round-232 guard, working).
- **Reverting the source is not enough.** With the file restored and `git diff` clean, the composition still
  collapsed — repeatedly, across a fresh `rm -rf build/split_poc && split_link.sh`. The cause is the **stale
  object**: `build/CMakeFiles/.../gm_AllocSpieler.c.obj` still contained the version-compiled under the other
  pragma, and `split_link.sh` links those objects, not the source.
- **Recovery is a full `cmake --build build`** (objects recompiled), then `rm -rf build/split_poc && bash
  scripts/split_link.sh`. That restored `exactly at their reference VA: 246` and residue **8628**.

**Why `linktest.sh` cannot warn you.** Its stale-object guard compares source mtime against object mtime and
warns when the *source is newer*. Here the source and object timestamps end up consistent after a revert
(`git checkout` rewrites the source, then a later build updates the object), so no warning fires — the
object holds the experiment's code while every signal says the tree is clean.

**The rule.** After any experiment that changes a **pragma, an inline/intrinsic choice, or a codegen flag**,
treat the object as poisoned: revert the source **and** run `cmake --build build` before measuring anything
else. A collapsed composition that survives a clean `split_link.sh` is the tell — and the fix is the full
build, not another `split_link.sh`.

**Measured outcome:** `#pragma function(memset)` on `gm_AllocSpieler` is not a lead — it cannot be measured
at all on this tree, because the out-of-line call breaks the composition before any residue number exists.
That is a stronger statement than "it measured worse".
