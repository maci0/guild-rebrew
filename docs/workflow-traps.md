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
