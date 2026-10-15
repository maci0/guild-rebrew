# Measure traps: the method's own failure modes

These cost as much as the codegen walls, and most of them were learned by being burned.
For what the compiler itself blocks, see `codegen-walls.md`. Live residue /
verify / `.data` numbers are `scripts/gate.sh` defaults, not a figure later
in this file.

Companion reading: `msvc6-c-shapes.md` (front-end shapes), `msvc6-allocator.md`
(register allocation and slot maps), `TODO.md` (round-by-round history).

### Diagnostic compilers can change floating-point observations (2026-10-14)

The shared production callback candidate was compared with the original x86
callback using identical, modeled external helpers. Both native bodies have
1,151 code instructions and 66 helper-call sites. The fixtures compare every
byte of the event snapshot, the ordered helper-call trace and complete
notification strings; they
do not mask floating-point fields or verify the external helpers themselves.

Clang's x87 diagnostic build retained an intermediate across repeated
replenishment, differing by one float ULP at offsets 0xb4/0xb8 in case31.
GCC with standard assignment precision fixed that observation, but its extended
evaluation of `1.3f` differed in case92. The native TL instruction at0x5722ef
multiplies by the four-byte pool value at0x66419c, bits0x3fa66666. Native
replenishment adds the unsigned recipe amount to the stored float, writes both
progress fields, then reloads the stored float for the loop condition.

The project C was not changed to satisfy those diagnostic compilers. A separate
ignored test copy spells its float literals as their exact float32 values and
uses standard assignment precision to model the observed literal/store widths.
Its192 runs (96 fixtures per client) agree on event bytes and call traces,
covering all66 native call sites. Controls that reinterpret the unsigned recipe
as a float, discard the returned queue ID, or copy12 rather than14 time bytes
are rejected in both clients. These are bounded observations under the stated
helper/precision model, not exhaustive semantic proof or MSVC byte agreement.
Do not add volatile fields or change game flags solely to fix another compiler's
observations. Actual MSVC tests and caller binding are still required.

Receipts: `.scratch/goal25/production/precision-model.json`,
`fixture-precision-model-v1-results.json`, `rejecting-controls.json`, and
`fixture-input-hashes.json`. The failed direct and unnormalized diagnostic
attempts remain recorded alongside the successful model.

### A literal-value change can retain function RELOC (2026-10-14)

A rejecting source control changes Gold0x004b6b10's increment from1.0 to2.0.
The current CLI still reports RELOC216/216: the COFF __real@ relocation remains
unresolved and masks the changed pool address. Independent literal-byte checking
rejects object0000000000000040 against native000000000000f03f at0x005eb8a8.
Function-byte agreement does not establish the values of referenced data, even
when the data is a compiler literal. Preserve this distinction in progress and
source-sharing decisions. Inspect every differing native constant before grouping
same-shaped bodies under one C definition. The repaired transfer variants have
24 literal checks across11 complete bodies, not new raw-link data verdicts.

The reusable content/trust capability is recorded in upstream IDEAS-GUILD.md.
Replay evidence: `.scratch/goal26/production/wrong-transfer-literal-test.json`,
`wrong-transfer-literal-rejected.json` and `repaired-operands.json`.

### Actual compiler fixtures need input and boundary controls (2026-10-14)

Once Docker access returned, the actual pinned MSVC callback object replaced the
host-compiler diagnostic candidate in the bounded fixtures. LIEF loads the COFF
sections and Rebrew applies typed relocations to reviewed native helper/global
bindings. Constant sections come from the actual object. External helper entry
points still use models, so this is neither a raw game link nor an exhaustive
proof. Independently compiled TL and Gold callback bytes, typed relocations and
constant sections agree. All 456 runs reach the same 66 native call sites per
client and agree on event bytes, complete strings and ordered helper traces.

The previous 192 fixtures missed two source errors. Letting the notification
helper mutate the building owner exposed stale owner reads; reaching exactly zero
production progress exposed `<0` where native x87 tests C0/C3 with mask0x41 and
uses `<=0`. Each pair of new cases rejects the earlier MSVC object in both
clients. The source now reloads the owner and preserves inclusive thresholds.
The current full compile is still SIZE_MISMATCH, 4016 versus3816 bytes. Do not
infer exhaustive equivalence from the expanded fixture count or describe its
modeled helpers as verified original callees.

Receipts: `.scratch/goal26/production/paired-msvc-objects.json`,
`msvc-v1-owner-mutation-red.json`, `msvc-fixture-bindings.json`, and the actual
MSVC fixture result files under `.scratch/goal25/production/`.

- A discovery region can include alignment beyond the actual function.
  TL0x41e1d0/GOLD0x422a20 m_PoolAlloc is261 bytes,103 reachable instructions
  and two returns, followed by11 NOPs. Complete CFG and fully bound operands
  prove the extent; a chosen prefix length or first return does not.
  `rebrew test --size 261` measures and persists the corrected extent through
  the locked writer. Catalog rows retain the272-byte discovery region and
  hash its code without padding; status counts261 body bytes plus11 padding
  bytes. Keep those scopes distinct. Evidence:
  `.scratch/goal21/pool-alloc-upstream/native-proof.json` and `status.json`.

- Verify the ruler's reported VA, symbol and extent before accepting its score.
  A positional `diagnose probe 0x499a50` formerly resolved a shared source but
  selected its first annotation47ddf0, giving a misleading66/66. Upstream
  9a2f9bb0 fixes the shared probe/gap/qualifier selector and rejects absent
  explicit VAs before compilation or source edits. The corrected499a50 probe
  exposes the unrelated body (10/128); all three canonical dispatcher probes
  remain130/130. Receipts `.scratch/goal20/probe-selection-*`.

---

## 1. Only the linked residue decides

Object metrics are proxies and have pointed the wrong way repeatedly: at least six
recorded instances, including one where the *positional* metric (`aligned`) picked the
losing candidate by 3 linked bytes, and one where `matched` rose by 6 while the link fell
by 1. But they are not useless: on `CrashDump`'s V2 the object metric was much worse *and
so was the link* (+131), because the mechanism (a 59-byte shortfall displacing the
function's own jump tables) was understood. **The rule that survives: neither accept nor
reject on a metric alone.**

## 2. One candidate, one full rebuild, one number

A batch attributes nothing. Two rounds of "wins" were later found to be layout shifts from
*other* objects (a committed "−58" re-measured at +56).

## 3. Relocation accounting makes the object metrics lie about what is left

`matched` credits a byte only when **both** sides relocate it or **neither** does. `msvc6`
relocates *memory operands* but not absolute immediates, and every local `call` carries a COFF
`REL32` that the linked reference does not relocate. So four bytes per call are permanently
uncountable, plus one-sided data slots (`msvc6-allocator.md` Finding 59 and its amendment).

Concrete ceilings, computed per window from the reference's HIGHLOW count:

| function | reference HIGHLOW | `matched` ceiling | HEAD `matched` / `matched-reloc` |
|---|---|---|---|
| `vfs_ReadCompressed` | 0 | 492 | 447 / 467 |
| `cm_ExProdObjekt` | 13 | 980 | 888 / **980** |
| `cm_ProcessCommandQueue` | 15 | 624 | 584 / **624** |

On the last two, `matched-reloc` **already equals the ceiling**: their entire remaining
`matched` shortfall is accounting, and **zero** of it is codegen work. A function can be
finished as far as any code edit can take it while its `matched` still looks far from its size.
`gm_AllocSpieler`'s ceiling is ~3115 of 3689: the distance from 736 was never reachable.

A recognition that some residue is unreachable by any code edit: the one-sided
relocation bytes (`cm_ExProdObjekt` 92, `cm_ProcessCommandQueue` 40, `gm_AllocSpieler`
~574). Byte-identity in the *linked image* is what the objective measures, and those bytes
already match there; the metric simply cannot see them.

## 4. A residue number is not the size of the error

It is the distance from the first divergence to the end of the function. `gm_AllocSpieler`
is 2,861 differing bytes over a 3,689-byte function *with a two-instruction deficit*; one
early encoding of a different length shifts everything after it. But the ratio does not tell
you *which* of three causes you have: a length cascade, a frame **value** difference (which
changes every `esp`-relative operand and no length at all: `sub esp,0x28c` vs `0x280` are
both 6 bytes), or genuinely distributed differences. `scripts/gaptrace.py`'s **curve shape**
discriminates; the ratio does not.

A high residue was once read as "one early encoding shifts the tail", sent to two agents as
a mission brief, and both refuted it with measurements: `CrashDump`'s first differing byte
is a frame *value*, and `gm_AllocSpieler`'s gap returns to 0 repeatedly across 168 hunks. Two
agent budgets were spent at a cliff that was not there.

**The run-length histogram is the cheap discriminator (round 839, whole tree).** Count the
contiguous differing runs between built and reference `.text` and look at their lengths.
Measured on the current tree: **610 runs over 8,634 bytes, median 5, mean 14.2, longest
189, and 254 of them exactly one byte.** That shape rules *out* a single early length
cascade (a cascade produces one long run from its start to the next realignment, not 254
scattered singletons) and rules *out* "one frame value per function", because a frame
value changes every `esp`-relative operand in that function at once.

**Do not infer the cause from the most common short-run context.** The top of that list is
dominated by `mov eax,[esp+0x20]` vs `[esp+0x18]`, which reads as a frame-offset cascade.
Measured directly, the bytes attributable to an `[esp+disp8]` slot offset are **54 of
8,634** (0.6%). The frequent pattern was the most *visible* one, not the bulk; the same
mistake §4 records, one level down. Classify by counting, never by the top of a frequency
list.

**Concentration is the other half.** The nine largest carriers hold **7,880 of 8,634 (91%)**
and the top two (`gm_AllocSpieler` 2,824, `CrashDump` 1,583) hold **4,407 (51%)**. So the
residue is simultaneously *fragmented in position* and *concentrated in cause*: many small
scattered differences, grouped into a handful of functions, each with its own documented
root. Any plan that treats the 610 runs as 610 problems is wrong; so is any plan that treats
the 8,634 as one cascade.

## 5. Tool traps that produced wrong readings

- `build/objtest/<name>.obj` is stale after `rebrew test`: disassembling it
  reads an earlier compile. The object a measurement actually wrote is the
  fresh `build/objtest/probe_*.obj` from `scripts/probe_function.py` (or the
  build tree object after a rebuild). One round nearly wrote up "the V2
  frame does not reproduce" from the stale file; the fresh object showed
  `sub esp,0x280`. (Also: `objdump -d file | head -6` truncates before the
  first instruction: the header lines eat the budget; use `head -12`.)
- `gaptrace`'s `size` argument must be the reference's *real body*, not the metadata size.
  `vfs_OpenStream` is 667 bytes of code inside a 701-byte real body inside a 704-byte window;
  the three choices read as "37 B long, 20 extra insns" / "3 B long" / aligned. The first
  invents instructions by decoding our own table bytes. It now derives the window itself.
- `gaptrace`'s instruction counts include cl's trailing alignment fill and read high; it now
  prints the real code end and labels the counts.
- **`rebrew test`/`verify` ignore the CMake per-file toolchain pin, so a pinned file's
  per-function numbers describe a compile that does not ship (round 842).**
  `CMakeLists.txt` pins three files to `/REBREW_TOOLCHAIN:msvc-6.0-sp5-pp` and the link
  honours it (visible in `build/CMakeFiles/server_dll.dir/build.make`), but `test`/`verify`
  compile with the project default sp6. Measured on `gm_FindNextFilteredEntity`
  (`spiel_dumpD.c`, pinned): verify reports `obj 342`, SIZE_MISMATCH, `delta 186`; the
  shipped DLL measures **215/346** at that VA, and compiling with the pin gives `obj 346` (
  the reference's exact size) at `match` 171/346. The whole-tree residue is safe because
  it is measured on the shipped bytes; **per-function claims about the three pinned files
  are not.** Check `CMakeLists.txt` before quoting a `verify` number for
  `spiel_dumpD.c`, `ahm_ExAllocAlchemist.c` or `ls_LoadBuildingEntityState.c`.
  Filed upstream in the rebrew ideas file.
- `instr_diff` decoded without `skipdata` and halted on a stray byte, understating alignment
  for the rest of a function (one function went 618 -> 646 once fixed).
- `gaptrace` was once accused of comparing instruction offsets rather than bytes, and rebuilt;
  the tool compares masked bytes and decodes both streams at the same base. The real defect
  was the size argument. Verify a tool complaint before acting on it.

## 6. Three audit shapes that generate only false positives

- **A check that only prints its result is not a check (round 907).** `gate.sh`'s lint step ran
  `rebrew lint 2>&1 | tail -1` and echoed the line, with **no `rc=1` anywhere near it**, so it could
  never fail the gate, on an objective whose stated rule is "zero warnings is the only acceptable
  state". Two further traps in the same spot:
  - **`rebrew lint` exits 0 even when it reports warnings**, so testing `$?` would not have fixed it.
    The `N passed, E errors, W warnings` summary must be parsed.
  - **A failing lint can look like a different failure.** Injecting a broken `FUNCTION:` VA did make
    the gate fail, with `REGRESSION: 263 byte-matched`, because the bogus VA also demoted a function.
    The gate went red for the wrong reason, and a warning that perturbed nothing would have passed
    silently. **When a guard fires, confirm it fired for the reason you intended.**
  **Rule: falsify every guard against a state where it must fire, and check the attribution, not just
  the exit code.**
- **A probe that fails to fire is not evidence the guard is broken: check the probe first
  (round 908).** Three successive attempts to falsify one new check all "passed", and all three were
  the *probe's* fault: the entry was still inside the section, the TOML had a duplicate key so it
  never loaded, and a `str.replace` matched a different entry than intended. The guard was correct
  every time. **Before concluding a check is dead, confirm the input actually reaches it**: print
  the parsed row, not just the exit code. This is the mirror of round 907's finding (a real dead
  guard, where the *gate* was wrong); the two look identical from the outside and are separated only
  by inspecting the input.
- **Editing a file to change nothing is not a no-op (round 908).** A docstring-only edit to
  `data_extent_check.py` collapsed a line and produced
  `end = cur["va"] + cur["size"]        if end <= nxt["va"]:`. `ast.parse` caught it in one command;
  without that check it would have failed at runtime in the gate, where the symptom (`could not read`
  / non-zero exit) points at the tree rather than the tool.
- **A metadata size that crosses the next tracked symbol is wrong by construction, and the check is
  one command (round 905).** Sorting the sized `.data`/`.rdata` entries by VA and asking whether
  `va + size > next_va` found **exactly two** defects in the whole tree, both real, both invisible to
  three rounds of *type-conflict* analysis (902-904) because an entry can be internally wrong while
  agreeing with every other TU:  - `g_dynasty_field_48` typed `int`/size 4 at `0x10035448`, overlapping `g_dynasty_field_49` at
    `0x10035449`. The reference does `mov dl, byte ptr [0x10035448]` (`0x1001700f`) and
    `mov byte ptr [0x10035448], dl` (`0x10017130`): **one byte**.
  - `g_entity_type_bytes` size 4 at `0x10035a04`, overlapping `g_stat_b_array` at `0x10035a05`, and
    typed empty. Reference: `mov byte ptr [ecx + 0x10035a04], dl` (`0x10015542`).
  **A declared extent that runs past the next known symbol cannot be right**, and unlike a byte diff
  or a size estimator this needs no disassembly and no assumptions. Run it after any metadata work.
  **Now automated:** `.venv/bin/python scripts/data_extent_check.py`, wired into `gate.sh` as the
  `== data extents` check (round 906).
- **Geometry alone cannot classify a crossing, and the naive discriminators each miss real bugs
  (round 906).** Two legitimate shapes look exactly like a wrong size:
  `g_data_restore_gap` (`+0x9a00`) contains `g_alchemy_entity_table` at `+0xa50`, and
  `g_crashdump_data_10027104` (`+568`) contains `g_crash_newline`, which is a `#define` offset. Both
  are views inside a blob that is *supposed* to cover those bytes. The two blind alleys, both caught
  only by running the check against the **pre-fix** tree:
  - treating a *fully contained* symbol as benign: misses both round-905 defects, because a 4-byte
    `int` size swallowing a 1-byte neighbour is geometrically identical to a blob swallowing a view;
  - treating `extern` as evidence of a view: misses `g_entity_type_bytes`, because
    `g_stat_b_array` is `extern unsigned char g_stat_b_array[]`, a *separate object* that merely sits
    next door. **An `extern` declaration is not evidence of anything about ownership.**
  The working rule requires **positive** evidence of a view (a `#define` naming an offset) plus a
  verified allowlist of the gap blobs. **Lesson: a guard must be tested against a state where it
  should fire.** This one was written twice while the tree was already fixed, and both early versions
  would have shipped silently passing.
- **Metadata-only width corrections are byte-neutral; composition-budget changes are not
  (rounds 904-905).** Four such fixes have now landed: `locktable` 256→192, `g_dynasty_field_48`
  4→1, `g_entity_type_bytes` 4→1, plus round 900's type corrections, every one with residue and
  raw-link `.data` **unchanged**. Contrast round 902, where changing objects the composition budget
  relies on cost **+236 `.data`** and **14 `LNK2001`**. The distinguishing question is not "is the
  metadata wrong" but **"does any code or layout decision depend on the value being wrong"**.
- **An unrolled loop presents its unrolled tail as if it were the termination condition
  (round 903).** Reading the reference cleanup loop at `0x1001cfd2`:
  ```
  mov  esi, 0x10031aac
  ...  cmp esi, 0x10031af0 ; je exit      <- four exit checks, 0x10 apart
  ...  cmp esi, 0x10031ae0 ; je exit
  ...  cmp esi, 0x10031ad0 ; je exit
  ...  cmp esi, 0x10031ab0 ; je exit
  ...  add esi, 4 ; cmp esi, 0x10031b6c ; jl loop
  ```
  The four `cmp … 0x10031aX0` are the **4-way-unrolled body's** per-iteration checks; the loop
  actually ends at `0x10031b6c`. Reading the first exit as the bound gives **68 entries**; the true
  array is **48** (`0xC0` bytes). **Read the `add`/`cmp`/`jl` tail, not the first `cmp` you meet.**
- **Confirm a size claim by a second, structurally different method before editing anything
  (round 904).** The same array's extent was needed twice: once misread by disassembly (above), and
  again a round later to justify a metadata fix. The second time it was cross-checked by scanning
  `.text` for immediates of the form `base + 0x10k`, which needs no control-flow reasoning at all:
  only `+0x0`, `+0x0c0` (the bound) and `+0x0d0` (the next object) appear, and **no `+0x100`**, which
  is what the old metadata claimed. **The check cost one command and would have caught round 903's
  error before it was written up.** When a fix depends on "how big is this object", get the number
  two ways.
- **A conflict report cannot express "two objects, one name, two consumers" (round 903).**
  `rebrew data list` flagged `locktable` as `CRITICAL_SECTION*[0x40]` vs `CRITICAL_SECTION**`. Both are
  intentional: `data_globals.c` defines the array the binary's own cleanup loop walks, and
  `mlock.c` defines `CRITICAL_SECTION** locktable = __locktable` because **LIBCMT's `tidtable.obj`**
  (pulled in via `_getptd`) references `_locktable` as a `CRITICAL_SECTION**`. `_locktable` is
  verified present in `LIBCMT.LIB`. Third case this session where "fixing" a reported type conflict
  would have broken the link.
- **`rebrew data list`'s type-conflict count is a signal, not a work queue (round 902).** Eleven entries
  looked like eleven mismatches to fix. Chasing them found at least three different situations, and
  the "fix" was wrong in two of the three:
  - **a real layout impossibility**: `loadsave3.c` *defined* five filter globals as arrays summing
    to 53 bytes inside a 16-byte span. Correcting them to scalars cleared 5 conflicts and was
    byte-neutral through `linktest.sh` (**+0**), but cost **+236 `.data`** at the gate. The array
    forms are load-bearing for the raw `.data` size, and only the gate's raw-link number sees it.
  - **a deliberate defining-TU choice**: `gm_NextEntityQueryMatch.c` "mismatched" 13 TUs on three
    globals because it is the file that *defines* them, and its own comment says the scalar types
    were chosen so the TU **emits BSS commons** ("Incomplete `[]` does not emit; sized arrays broke
    .text layout"). Correcting the types produced **14 `LNK2001` unresolved externals**. The comment
    predicted the failure exactly; it had to be read before probing, not after.
  - **genuine mismatches**: the remainder, which are actually wrong.
  **Rule:** open the defining TU and read its comment before touching a conflicted global. The
  report cannot distinguish "wrong type" from "the only definition, deliberately typed".
- **A placeholder name hides a type error the compiler would otherwise catch (round 900).**
  `data_globals.c` carried `int g_100354c8;` and `int g_100354e0;` compiled clean for as long as
  those globals were called by their placeholder names. Renaming them to their attested CRT names
  failed the build immediately:
  ```
  error C2040: '__argv' : 'int ' differs in levels of indirection from 'char ** '
  error C2040: '_pgmptr' : 'int ' differs in levels of indirection from 'char *'
  ```
  MSVC6 type-checks a declaration against its *own* CRT header only when the identifier matches, so
  the placeholder name made the conflict invisible. Both slots are 4 bytes on x86-32, so the layout
  was always right and no byte ever differed, but the declared type was wrong, and no code could
  have used it as a real pointer. **Consequence:** a `g_<hex>` name is not merely cosmetic debt; it
  suppresses the compiler's ability to check the declaration at all. Expect renames of
  CRT-named globals to surface C2040s, and fix the type rather than the name.
  **But the hazard is not universal (round 901).** Restoring `__pioinfo`, `_nfile` and `__nstream`
  on three more CRT globals compiled **clean on the first try**. It bites only where MSVC6 also
  declares the same identifier itself (`__argv`, `_pgmptr`); for names it does not,
  the rename is safe and the risk is ordinary. Do not assume every placeholder hides a type error:
  test, and check the build log rather than reasoning about which is which.
- **A header edit can push a TU over its composition span, and the symptom is an unrelated
  `LNK2001` (round 914).** Adding an include to `gv_MoveSlotEntry.c` grew its object **688 → 1008
  bytes (+320)**, past the padded span the split-link can place, and the build failed with
  `LNK2001: unresolved external symbol _gv_MoveSlotEntry`, a symbol whose declaration was perfectly
  fine. §6d's composition-budget mechanism normally arrives from a *code* edit; it applies just as
  well to headers, and it is invisible until the link because the TU compiles cleanly.
  **Three symptoms now point at the same underlying budget:** `LNK2001` for a symbol you did not
  touch, a `LONG <file>.c.obj` line in the pad report, and a `split_link FAILED` with no `error C*`.
  **Check `grep '<file>.c.obj' .scratch/gate-link.log` *before* lifting into a file, not after**,
  and note the report only shows files that are *already* over, so a file 300 bytes under its span
  can still be tipped over by a header.
- **A `LNK2001` naming a symbol you did not edit is a declaration mismatch, not a missing definition
  (round 914).** Round 913 saw thirteen of them for `_s_ahm_AllocAhmInfo_1002a0f8`,
  `_ahm_QueryEntityBuildingType` and `_ahm_AllocateEntitySlot`, and recorded the cause as unknown.
  Each was a **return-type disagreement** between a caller's `extern` line and the defining TU:
  `int*` against `int`, `void` against `int`, and each was decidable from the reference rather than
  by preference (`0x1000c6a0` returns `ahm_LookupEntityInTable`'s `eax`, a pointer). **The diagnostic
  is cheap:** for each unresolved name, `grep` every declaration and the definition, and compare
  return types. This is round 911's `gm_ResetAllEntities` class, and it recurs wherever two TUs
  declare the same function independently, which is the norm in this tree, since the original kept
  declarations local.
- **A metadata note can be confidently wrong, so identify a symbol from its use sites (round 901).**
  `0x11766564` was noted as "tracked-block (stream) table ptr" and is in fact `__pioinfo`, the CRT
  per-handle file table: established from `mov eax,[__pioinfo]; mov eax,[eax + esi*4];
  test byte [eax+0xc],0x83` at `0x1001ad4b`, not from the note. `0x11766560` was noted as "current
  stream count" and is a handle **bound** (`cmp esi,[_nfile]; jae`, init `0x20`). Two of three notes
  were wrong about what the symbol *is*, while both were right that something was there.
  Disassemble the use site before naming; a note is a lead, not evidence.
- **A hand-rolled struct-size calculator reports garbage on this tree: use the compiler instead
  (round 895).** Two successive versions of a Python `sizeof` estimator flagged **18 then 7**
  structs whose `// SIZE` comment disagreed with their declared extent. **All 25 were the
  instrument.** Three separate failure modes, each invisible in the output:
  - the first version double-counted array members (`PlayerList9 { int count; int ids[8]; }`
    computes 0x24; it said 0x80 = exactly 2x);
  - the second could not resolve a member whose *type is another struct*
    (`SbhRegion.grpHeadList[32]` of `SbhGroup` at 0x204: 0x144 + 32*0x204 = 0x41c4, which the
    header states correctly; the estimator assumed 4 bytes per element);
  - one-line bodies (`typedef struct { int count; int ids[8]; } PlayerList9;`) parsed as a single
    token pair.
  **The compiler cannot be fooled and costs one invocation per type.** Write
  `char chk[sizeof(T)==0xNN?1:-1];`, include the defining TU, and compile with
  `rebrew-cmake-cl`. Doing that for the flagged types returned **48 of 48 correct**, including
  `SbhRegion` 0x41c4, `SbhGroup` 0x204, `TGT` 0x3c and `gz_stream` 0x64. A regex over C is a
  hypothesis about C; `sizeof` is a fact about it.
- **A `C1083: cannot open include file` inside a size probe looks exactly like a size failure.**
  `gz_stream`'s check failed until `-I references/zlib` was added: the assertion never compiled,
  so "NOT 0x64" meant "did not build". Always separate *compile status* from *assertion result*
  before reporting a type as wrong.
- Naive same-mnemonic immediate comparison across a diff finds aligner
  crossover (both sides contain both values in different interleave:
  `cmp cl,2/6`, `shl 4/8`, push-constant runs). Without control-flow
  awareness it cannot distinguish a constant bug from a phase shift.
- Polarity-pair text comparison is void: `rebrew diff` prints branch
  targets as relative displacements, so equal strings are coincidence.
- Cross-image VA comparison is valid only for identical layouts. Byte-
  decoding branch targets on both sides and comparing numerically
  "found" three same-target polarity pairs; ground truth showed each
  side's VA holds different code. Never compare addresses across two
  differently-laid-out binaries.
- **Raw-byte diffing against `.scratch/server.dll.prelayout` invents mismatches in every
  relocated function (round 860).** That file is the *pre-postlink* link output, so its
  absolute `mov`/`call` operands hold the linker's own values, not the reference's. Comparing
  bytes directly made **241 of the 264 `RELOC`/`EXACT` entries look stale**, and tuning the
  "is this a relocation?" heuristic only moved the count around (241 → 158 → 121 unexplained):
  the clearest sign the *instrument* was wrong rather than the data. Checked with the tool:
  `rebrew verify` reports **0 entries with a nonzero delta**, and `rebrew test` on one of the
  "suspects" returns `match_count 179/179, mismatches []` with `reloc_count 12`. The metadata
  is consistent; the raw diff was not.
- **A field-offset histogram cannot type a struct, and merging two histograms invents a layout.**
  Round 893 collected every `slot + 0xNN` offset in the tree (98 distinct, `0x170` alone in 12
  files) and merged it with the field map written in `spiel62.c`'s header. The merge *collided*:
  `parent_index` (2 bytes at `0x27`) ran into `season_born` at `0x28`, and the tempting reading
  was "one of the two sources is wrong." **Neither is: they describe different records.**
  Disassembly settles it, and a histogram cannot. At `0x1000fe86`:
  ```
  0x1000fe76  call gm_StartFilteredEntitySearch   ; result in eax
  0x1000fe86  mov  cx, word ptr [eax + 0x27]      ; a SLOT INDEX, 2 bytes
  0x1000fe8a  cmp  cx, 0xffff
  0x1000fea0  lea  ecx, [ecx*4 + 0x100358a0]      ; scaled by 540 -> g_slot_table
  ```
  So the record `gm_StartFilteredEntitySearch` returns carries a slot index at `+0x27` and is
  **not** a `g_slot_table` element. The `g_slot_table` element separately has a 4-byte field at
  `+0x28` (`0x1000fc9c  mov [eax+0x28], ecx` after `dec ecx`, the season store). A word at `0x27`
  and a dword at `0x28` cannot coexist in one struct, so two types are in play.
  **Rules this yields:** (1) `offsetof`-style sweeps tell you which offsets are *used*, never
  which struct they belong to: same-base offsets from different functions may not share a base;
  (2) when two field maps collide, disassemble the *producer* of the pointer (here, the call that
  fills `eax`) before deciding which map is wrong; (3) a half-remembered regex is not a negative
  result: `mov [r+0x28],r32` appeared absent because the pattern only matched the `disp8`
  encoding, and the store exists.
- **A type defined in a header is not a type in use.** `EntityStruct` (`game/entity.h`) is declared
  with `// SIZE 0x21c` and referenced **three times tree-wide: its own definition and two
  comments**. `entity.h` is included by 9+ TUs, but only for its `extern` globals. Do not count a
  header type as "the layout is defined"; grep for *instantiations and member accesses*, which is
  zero here. The same check applied to `PlayerSlot` gives 13 references and is real.
  **Use the tool's own masked comparison.** `rebrew test`/`verify` already implement "equal
  after masking relocations"; do not re-derive it by hand from a prelayout copy. If a raw
  comparison against `build/server.dll` is wanted instead, that file is the *post*-postlink
  output and its bytes are comparable; the prelayout copy is not.
  **The whole-`.text` total is also wrong from the prelayout copy: it reads 50,296 against the
  shipped file's 8,634** (round 863), because every unresolved relocation counts. So the
  prelayout copy is not an oracle for a per-function residue *or* for the tree total, only
  `build/server.dll` (and `rebrew verify`) are.
  This is the second round this session (with 852) where a raw byte reading produced a
  confident false finding that the tool's own number refuted.

## 6b. `function_structure.json` sizes are 16-byte-padded; the toml's are real (round 866)

Comparing a function's recorded size across the two inventories looks like it finds defects and
does not. Across all 351 tracked entries, **163 disagree, always with the discovered size larger,
and 160 of those discovered sizes are an exact multiple of 16** while 157 of the toml sizes are
not. The discoverer rounds each extent up to a 16-byte boundary; `rebrew-functions.toml` records
the real function length.

Consequence: any by-size arithmetic over the discovered inventory silently over-runs into the
next function, which is what produced round 861's "54 unattributed residue bytes" and round 27's
"196-function gap" reading. Use the toml size for a function's real extent, and the discovered
inventory only for *finding* functions the toml does not list.

This is why `rebrew test --symbol <name>` can report a size the metadata never had:
`gm_CalculateProductionValue` came back as `ref 81` there while both inventories and
`rebrew verify` say 396/400. When a size looks wrong, check it against **the next tracked VA**
(`0x10019720 + 400 == 0x100198b0`): that is the ground truth, not either inventory.

## 6c. Object size can move toward the target while the link moves away (round 868)

`gm_FindNextFilteredEntity` (`0x10016f80`) is 4 bytes short of the reference: object **342**
against target **346**, and the deficit is a *missing block*: 8 instructions the reference has
and we do not (`jne` + a full epilogue: `xor eax,eax` / store / four pops / `ret`). The reference
reaches **one shared epilogue via a `cl`-flag jump**; we emit a private return at each early exit.

Routing the offending early `return 0;` through the shared tail (`match = 0; goto done;`) moves the
object **342 -> 347**, past the target by one, i.e. the size gap closes. At the link it is
**+114 worse** (`gm_FindNextFilteredEntity` 215 -> 329, `.text` 8,634 -> 8,748).

So "the object size now matches" is not evidence of progress, and on this function it is
positively misleading: the same edit that fixes the size adds 114 residue bytes, because the new
`goto` re-lays the block graph and the shared tail stops being reachable the way the reference
reaches it. **Measure at the link or do not claim a direction**: this is the concrete case behind
the AGENTS.md warning that the two object rulers disagree with each other and with the link.

## 6d. 28 objects are over the composition budget, and that is what makes source edits collapse (round 870)

> **CORRECTION (round 916): the `LONG` label does not mean "over the budget".** Measured against the
> objects' *actual reference spans* (next tracked VA minus this file's first VA), **zero of the 25
> checkable `LONG` objects are over**: 23 sit *exactly* at their span and two (`vfs2.c` −288,
> `vfs_OpenStream.c` −48) are **under** it, i.e. have room to spare. The pad report's `want` is the
> raw sum of metadata sizes, while the object is the **per-function-16-byte-padded** sum; for
> `spiel62.c` those are 1328 and 1408, so the report printed `+80 over` for a file that is exactly
> at its span. Verified on all 25: `per-func-pad == objtext` for every one. **Do not treat a `LONG`
> line as "this file cannot absorb a change"**: compute the span. See the new section below for the
> corrected test. The historical text is kept because the *mechanism* it describes is real; only the
> count and the inference are wrong.

`scripts/split_link.sh`'s pad step prints one line per object it cannot fit. On the current tree it
prints **28 `LONG` lines**:

```
spiel_dumpD.c.obj: 1040 > 1024 (+16 over the padded span; want 1015) -- not padded
ErrorModule2.c.obj: 528 > 496 (+32 over the padded span; want 494) -- not padded
trees.c.obj: 6464 > 1088 (+5376 over the padded span; want 1083) -- not padded
```

**But the total is 816 bytes, not 6,671: three of the 28 lines are a reporting artifact
(round 871).** `want` is summed from the metadata's per-function sizes, and **zlib's sources carry
no `// FUNCTION:` markers at all** (0 markers in all 18 files under `references/zlib-1.1.3/`), so
for `trees.c`, `infblock.c` and `infcodes.c` the padding target collapses to whatever little the
metadata happens to know. `trees.c` reports `+5376 over` while its object is **exactly the span
between its own VAs** (`0x10008800 - 0x10006ec0 = 6464`), i.e. it is not over at all. The script's
own docstring warns about this at the `want` computation ("`want` is only as complete as the
metadata ... and then `want` understates the reference span").

Split correctly: **25 game files, 816 bytes of genuine overage**, against **3 zlib files, 5,680
bytes of phantom overage**. Read the game lines; ignore the zlib ones.

**Only SHORT objects can be padded**: `pad_short_functions.py`'s own docstring says a longer one
"cannot be cut without losing code". So for these 28 files the composition has *no slack*: any
edit that grows the object, and on a file already over budget even an edit that keeps its size,
moves the symbols after it.

That is the mechanism behind three rounds of failures. Round 869's `gm_FindNextFilteredEntity`
change took `spiel_dumpD.c.obj` from 1015 to 1024 bytes and the link reported "COMPOSITION
COLLAPSED: only 0 symbols landed at their reference VA", because that file was **already 16 bytes
over**, so the composition had nothing left to absorb. The same applies to `LONG` file-mates in
`ErrorModule2.c`, `vfs.c`, `vfs2.c`, `infblock.c` and 23 others.

**Practical consequence, and the check to run first:** before reshaping any function, look up its
file in the pad report (`grep '<file>.obj' .scratch/gate-link.log`). A `LONG` line means that file
cannot absorb a size change at all and the only adoptable edits are ones that *shrink* it by at
least the stated overage. A file with no line either is within budget or was padded.

> **This inference is superseded by the round-916 correction above.** A `LONG` line does *not* mean
> the file is over budget: 23 of the 25 checkable `LONG` objects are exactly at their reference span
> and two are under it. The reliable test is the span comparison, which is what the round-916 section
> describes. Rounds 909-915 excluded files on the `LONG` label; that exclusion was unjustified, and
> **the real reason those lifts failed was a different check entirely** (a header declaration that
> disagreed with a definition, and a TU whose *object* grew past its span once an include was added).

**Applied to the 19 carriers (round 872): 16 are in files WITHIN budget and only 3 are blocked.**

```
blocked (LONG file)                 within budget
vfs_OpenStream        by  32        gm_AllocSpieler, CrashDump, cm_ExSellObjekt,
spiel_dumpD           by  16        ls_LoadBuildingEntityState, gv_ExAllocGraveyardWorker,
spiel622              by 112        cm_ExCopyEntityData, ServerMainThread, gm_AllocGebaeude,
                                    ahm_ExAllocAlchemist, m_AllocTracked, srv_LoadBuf,
                                    gm_ObjectsAvailble, vfs_ReadCompressed, cm_ExProdObjekt,
                                    cm_ProcessCommandQueue          (15 total)
```

Rounds 868-870 were spent on `gm_FindNextFilteredEntity`, which is in `spiel_dumpD`, one of the
**three blocked** files. The right move was to work an unblocked carrier, and the check that would
have shown that costs one command. **Run it before choosing a function, not after a failed probe.**

## 6e. `cflags` in the metadata can crash the compiler on a CMake-flag-pinned file (round 877)

**Round 909 extension: the pins also make *header* changes unsafe, and a +0 single-symbol probe does
not generalise to them.** Lifting 27 duplicated globals into `entity.h` and deleting 145 local
`extern` lines was **+0 at the link on one TU** (`spiel62.c`), so it looked safe by the project's
usual standard. Scaled up it failed the gate: **`C1001: INTERNAL COMPILER ERROR`** as soon as
`ahm_ExAllocAlchemist.c` gained the include (the round-877 mechanism, on a *different* pinned file),
and **`LNK4006` duplicate definitions plus `LNK2001: unresolved _ls_LoadBuildingEntityState`** once
`ls_LoadBuildingEntityState.c` (the third pin) had its include graph widened. Restoring the two
pinned files individually did not help, because the damage is to *which objects define which
symbols*, not to either file alone.

**Rule:** the three sp5-pp-pinned files (`spiel_dumpD.c`, `ahm_ExAllocAlchemist.c`,
`ls_LoadBuildingEntityState.c`) should be excluded from any change that alters what a TU includes.
And note the shape of the mistake: `linktest.sh` measures `.text` residue, which an `extern` line
cannot move, so a passing probe says nothing about a build-graph change. **A +0 probe certifies the
axis it measured and no other.** See round 909 in `TODO.md`.

**Correction (round 878): the flags in this entry were misread.** `ls_LoadBuildingEntityState`
(`0x100128f0`) compiles with **`/O2 /Gd /REBREW_TOOLCHAIN:msvc-6.0-sp5-pp`**: the sp5-pp toolchain
pin only, **no `/Oa /Ow`**. Round 877 read a neighbouring file's flag tail. The mechanism this
section describes still holds (a CMake pin the metadata does not carry, and a `--cflags` write that
breaks the compile), but the specific flag pair does not belong to this file.

`os_LoadBuildingEntityState` (`0x100128f0`) compiles in the real build with
`/O2 /Gd /Oa /Ow /REBREW_TOOLCHAIN:msvc-6.0-sp5-pp`, set by `CMakeLists.txt`: it is one of the
three sp5-pp-pinned files. Its metadata carried **no `cflags` field**, and the docs record
`CMakeLists.txt` as the place where per-file flags live for exactly these files.

Persisting the same flags into the metadata with `rebrew test --cflags "/O2 /Gd /Oa /Ow"` (the
tool writes the field itself) makes `scripts/gate.sh` go **FAIL** with
**`fatal error C1001: INTERNAL COMPILER ERROR`** and a C1083. The identical flags appended to the
identical defaults work through the CMake path, so `/Oa /Ow` is not the problem: **the metadata
path and the CMake path do not construct the same command line, and only the CMake one compiles
this file.**

**Check `grep '<file>.c.obj:' -A40 build/CMakeFiles/server_dll.dir/build.make` before adding any
`cflags`**, and do not add a field that merely restates a CMake pin. Note also that
`rebrew-functions.toml` is mode 444: reverting needs `chmod u+w` first.

**`rebrew test <file> --cflags <flags>` is a WRITE, not a measurement (round 919).** It persists the
flags into the tool-owned `src/rebrew-functions.toml` instead of testing in memory. Two sweeps left
the file dirty against `HEAD`, and because the CMake build consumes a separately generated table
(`build/rebrew-cflags.cmake`), the result *looked* like a real metadata/build divergence: `rebrew
data` reported `/Ox /Gd` for `gm_AllocSpieler` while the compile line carried `/O2 /Gd /Oa /Ow`. It
was my own probe. **After any `--cflags` sweep, `git diff src/rebrew-functions.toml` before drawing
any conclusion from a flag value**, and restore with `chmod u+w` first.

**`--cflags` also DROPS a per-file toolchain pin, so it cannot be used on the three sp5-pp files
(round 920).** On `ls_LoadBuildingEntityState.c` (whose CMake `COMPILE_OPTIONS` is
`/REBREW_TOOLCHAIN:msvc-6.0-sp5-pp`) the command printed `TOOLCHAIN persisted → msvc-6.0` and
proceeded to measure **a different compiler's output**. Every number from such a run is void, and
nothing in the output marks it as invalid. **The sound route for a pinned file is CMake:** append the
flag to that file's `COMPILE_OPTIONS` (`;`-separated, §6f), reconfigure, **grep the emitted
`build.make` line to confirm both the pin and the new flag survived**, then build and gate. That is
how `/Ow` was measured as inert on this carrier (residue 8,634 unchanged); the three `--cflags`
attempts that preceded it were measuring `msvc-6.0` and were discarded.

**A flag finding is per-carrier until measured otherwise (round 919).** `codegen-walls.md` §8 lists
`flags | flat | 12 axes, ~120 compilations`, and shapes §94 says `/Ow` is load-bearing on
`gm_AllocSpieler` while `/Oa` is inert. Both are true and neither generalises: re-measured,
`/O2 /Gd /Ow` and `/O2 /Gd /Oa /Ow` both score 1004/3689 while `/O2 /Gd` gives 493, and the same
`/Ow` on `CrashDumpUnhandledExceptionFilter` scores **643/2115 either way, byte-identical**. So
"flags are flat" is a statement about *aggregate sweep results*, not a licence to skip a per-file
test.

**Round 913 correction: an sp5-pp pin does not make an *include* unsafe.** Round 909's
`C1001: INTERNAL COMPILER ERROR` appeared right after `ahm_ExAllocAlchemist.c` (a pinned file) gained
an include, and was recorded here as the pin interacting with header changes. It was not the pin.
Round 913 lifted `g_next_object_id` into that same file's include graph and built **clean, 0 errors**
, and round 911 then showed the real cause was a *wrong declaration* in `entity.h`
(`gm_ResetAllEntities` as `int` against a `void` definition). **The pin constrains the flags a file
compiles under; it says nothing about what it may include.** Do not exclude pinned files from
header work; fix the header instead.

## 6f. A dropped per-file flag produces a normal-looking measurement (rounds 879-880)
`set_source_files_properties(... COMPILE_OPTIONS "/A" "/B")` **silently drops `/B`**: CMake wants a
`;`-separated list. Configure succeeds, the build succeeds, `build.make` simply lacks the flag, and
any measurement taken is of a *different compile than the one intended*, with no error anywhere.
Round 45 nearly concluded "`/Oa` is inert" from exactly such a run.

**Check the generated command line, not the CMake source, before believing a flag experiment:**
`grep -A40 '<file>.c.obj:' build/CMakeFiles/server_dll.dir/build.make`.

The plumbing was audited afterwards and is otherwise sound: all three `COMPILE_OPTIONS` pins and
the zlib `COMPILE_FLAGS` reach their command lines, and of 57 files carrying metadata `cflags`, **0
real flags are missing**: the 48 apparent misses are all `/DREBREW_ALLOW_NAKED`, which
`C_DEFINES` supplies globally as `-DREBREW_ALLOW_NAKED=1`.

## 6f-bis. `COMPILE_OPTIONS` REPLACES a source's option list: adding a flag can silently drop a pin (round 942)

`set_source_files_properties(<src> PROPERTIES COMPILE_OPTIONS "/Ow")` **replaces** whatever
`COMPILE_OPTIONS` that source already had. It does not append. Three files in this tree carry a
per-file toolchain pin as `COMPILE_OPTIONS "/REBREW_TOOLCHAIN:msvc-6.0-sp5-pp"`, so adding a second
`set_source_files_properties` call for one of them **silently removes the pin**: the build succeeds,
the file compiles, and every measurement taken is of the wrong toolchain. Round 941's `/Ow` sweep did
exactly this to `spiel_dumpD.c` and `ahm_ExAllocAlchemist.c`, which is why part of that sweep's collapse
was not `/Ow` at all.

**To add a flag to a pinned file, put both in ONE list:**

```cmake
set_source_files_properties(
  "${PROJECT_SOURCE_DIR}/src/Develop/.../file.c"
  PROPERTIES COMPILE_OPTIONS "/REBREW_TOOLCHAIN:msvc-6.0-sp5-pp;/Ow")
```

**And verify on the emitted command line, not in CMakeLists:**

```sh
awk '/<file>.c.obj: \/home/{f=1} f&&/rebrew-cmake-cl/{print; exit}' \
    build/CMakeFiles/server_dll.dir/build.make | tr ' ' '\n' | grep -E '^/(REBREW|Ow|O2|Gd)'
```

That must show **both** the old flag and the new one. A missing `/REBREW_TOOLCHAIN` is invisible to the
compiler: nothing warns, because the flag is consumed by `rebrew-cmake-cl` and stripped before the real
compile. Note also that `set_source_files_properties(PROPERTIES ...)` **with no source argument** is a
silent no-op; that is the shape that results if the source line is deleted from an existing pin while
trying to remove a duplicate.

## 6f-ter. `/Oy` is a prefix of `/Oy-`: a flag grep with plain substring matching reads the opposite (round 944)

Auditing per-file flags with `grep -oE '/Oy'` against the emitted command line reported `/Oy` for
`m_AllocTracked`, whose actual flags are `/O2 /Gd /G6 /Oy-`: the flag **disabled**. The substring
matches inside `/Oy-`. The same trap applies to every negated MSVC flag that is spelled as a suffix:
`/Og-`, `/Ot-`, `/Ob0`, and any `X` / `X-` pair.

**Match the flag with its terminator, not with a bare substring:**

```sh
# wrong: reads /Oy- as /Oy
grep -oE '/Oy' build/CMakeFiles/server_dll.dir/build.make

# right: require a non-word character (or end) after the flag
grep -oE '/Oy([^A-Za-z0-9]|$)'
```

Consequence when it bit: a table of per-file flags came out with one row reading "carries `/Oy`" when
the file carries `/Oy-`. Nothing downstream failed; it was caught only by printing the **whole**
command line next to the extracted flags. **Print the raw line when auditing, and use the extracted
list as a summary, never as the evidence.**

## 6f-quater. A real definition beats a COFF COMMON silently: the `LNK4006` rule cannot see it (round 945)

Two translation units defined `locktable`: one as a 192-byte
`CRITICAL_SECTION* locktable[0x30]`, one as `CRITICALSECTION** locktable = __locktable;` where the
second was referenced by nothing. The symbol tables looked like this:

```
mlock.c.obj:        _locktable  sec 2  val 0x0     <- a REAL definition
data_globals.c.obj: _locktable  sec 0  val 0xc0    <- a COFF COMMON (tentative definition)
```

**A real definition beats a COMMON**, so the unwanted 4-byte pointer silently won, the 192-byte table
was discarded, and **no `LNK4006` was emitted**, because resolving a COMMON against a definition is
legal, not a duplicate. AGENTS.md's rule ("a duplicate-symbol warning is a finding") is correct but
**cannot fire on this shape**. The tree links green, `verify` passes, and the symbol resolves to the
wrong storage.

**So symbol-duplication auditing needs a second check beyond the warning count:** for any global defined
in more than one TU, look at **which one the map picked**.

```sh
grep '_<symbol>' build/split_poc.map          # the winner and where it came from
objdump -t <obj> | grep -i '<symbol>'         # sec 0 = COMMON, sec N = real definition
```

A `sec 0` entry is a tentative definition whose size is in the value column; a `sec N` entry is a real
one. If the object with the *correct* layout has `sec 0` and another has `sec N`, the other one wins.

## 6f-quinquies. "Defined in two objects" is normal C, not a defect list (round 946)

Round 945 found a real bug with the COFF COMMON-vs-definition mechanism (§6f-quater) and round 946
tried to turn it into a tree-wide sweep. The sweep reported **419** symbols carrying both a real
definition and a COMMON. **Essentially all of them are ordinary C**, not defects:

```c
/* spiel622.c */   int gm_RandomMod(int);          /* declaration -> COMMON */
/* spiel622.c */   int gm_RandomMod(int n) { ... } /* definition  -> sec N */
/* sim.c */        extern int gm_RandomMod(int);   /* declaration -> COMMON */
```

Every cross-TU function call in the program has this shape. A function declared and defined produces
one real symbol and N COMMONs; the linker picks the real one, which is exactly right. Narrowing to data
objects still reported ~200 rows, because `link_stubs.c` deliberately defines ~176 placeholder globals
in one shared `.bss`, and the "size" column for those is the *remaining section length* (values like
24,314,872), not the object's size, so a size-based filter does not separate them either.

**The discriminator that worked in §6f-quater is not "does a COMMON clash exist" but "does the COMMON
have the CORRECT layout while a real definition has a different one".** That is a per-symbol question
requiring the metadata's recorded size and type, and there were exactly **one** such case in the tree
(`locktable`). A second sweep attempt with a "referenced nowhere else" filter produced 39 candidates and
**the first one checked was wrong** (`_g_stat_min_d` is referenced by `cm_ExChangeDesire.c`, the
detector had stripped comments after collecting rather than before).

**So: do not sweep for this class tree-wide.** Check the specific shape: a symbol whose metadata layout
disagrees with the definition that wins the link, and prefer the tooling's own view of the winner
(`build/split_poc.map`) over any grep-derived population.

## 6f-sexies. `object_span_check.py`'s one "OVER" result is an artifact of untracked functions (round 949)

`scripts/object_span_check.py` reports, out of 174 objects: 167 exactly at span, 6 under, and
**one over: `mlock.c.obj`, span 118, text 212, +94**. That reads as a real budget violation and is the
only one in the tree. It is not.

`mlock.c` defines **three** functions but marks only **two** with `// FUNCTION: SERVER`:

```
50:// FUNCTION: SERVER 0x1001d036     -> __lock     span 97
72:// FUNCTION: SERVER 0x1001d097     -> __unlock   span 21
   (and `_lockerr_exit`, defined at line 25, with no marker)
```

The object therefore carries **eight separate `.text` sections** (this build emits function-level
sections): `8, 15, 43, 97, 21, 14, 14, ...` summing to 212, while the *tracked* span is only
97 + 21 = 118. The 94-byte difference is `_lockerr_exit` and the other untracked helpers, which have no
reference VA to be measured against.

**And the split link confirms the artifact**: both tracked functions land at their reference VAs exactly
(`__lock 1001d036`, `__unlock 1001d097`), because `split_link.sh` places each function individually
rather than the object as a whole.

**So read `object_span_check.py`'s output as "objects whose tracked functions fit", and treat a single
outlier as a question about *untracked functions in that file*, not as a budget failure.** The check
cannot distinguish the two, because it sums every `.text` section in the object.

## 6g. Two ways a whole-image instruction census lies, and both look like a finding (round 923)

A mnemonic census over both images is a good instrument: it converts "residue is 6% of `.text`"
into a countable claim. It produced three large fake signals before it produced a real one.

- **Do not decode the linked image at the reference's VA.** The build is position-aligned at
  *function* granularity, not byte granularity. If our object placed a body at a different internal
  offset, decoding that function's `size` bytes from the reference's VA reads someone else's code.
  Measured: `gm_AllocSpieler` out of `build/server.dll` decoded to 1,014 instructions and **52
  calls**; its object holds **55** calls, which is the reference's number. The census's conclusion
  flipped from "three calls are missing" to "the ruler is reading the wrong bytes". **Take the
  symbol→VA alignment from `build/split_poc.map` and the body from the `.obj`.**
- **Trailing section bytes decode as instructions.** A COFF `.text` section ends in jump tables and
  padding, and both disassemble into plausible opcodes: the reference's `0x09` fill reads as
  `or dword ptr [ecx], ecx` (50 consecutive after `CrashDumpUnhandledExceptionFilter`'s tables),
  and `gm_AllocGebaeude`'s tail reads as `adc ch, dh` / `adc byte ptr [edx-0x3aeffe89], cl`. These
  produced the image-wide figures **`or` -51**, **`adc` -43** and **`add` +108**, all filler, none
  of it real. Requiring the span to decode end to end does **not** catch it, because garbage
  decodes end to end too. Cut every body at its **last `ret`**.

With both fixed, over the 102 functions both sides decode as real `push`-prologue bodies, the
whole-image difference is **+3 instructions** and **Σ|mnemonic delta| = 13**, with exactly **one**
function differing at all. `scripts/opcode_census.py` implements it; treat any function in its
final table as the only remaining place a code-shape claim can be true.

**General form:** when a census first reports a big, tempting number, the next question is not
"how do I fix it" but "what else could produce this number". Here the answer was padding, and the
size of the fake signal (-51) was larger than any real one the method found (+3).

The same caution applies to operands, and cost part of round 924: an operands-level census showed a
nonsense `push` immediate and a real bug behind it, but the "37 undefined symbols" population that
looked like the same bug 20 more times was mostly `link_stubs.c` placeholders. See §6h.

## 7. The size rule has two branches, and mixing them discards good work

`cl` pads each COMDAT to 16 bytes, so for an object with **no** relocated data after its code
any real body at or below `16*ceil(size/16)` is composition-neutral, with **no lower bound**.
If the object *does* carry a jump table or case map after its code, the **real** length binds
and padding cannot protect it (`vfs_OpenStream`'s 8-byte shortfall was worth −36 linked). An
earlier rule ("the real body must equal the reference's") was strictly stronger than the
composition requires and had been silently discarding admissible candidates.

## 8. probe-span vs test-real: two rulers, one truth

`probe_function` reports the padded COMDAT span as obj size (ExProdObjekt 1008, PCQ
640); `rebrew test` reports the real body (993, 639). Their match
counts differ accordingly (888 vs 976, 584 vs 624), and test's
match_count equals probe's matched-reloc bucket. Same object,
different rulers. Always state which ruler a number comes from
before comparing two figures.

## 9. Build and verify side effects that burn

- **A no-op `cmake --build` prints no linker warnings, so the build log is not a warning census
  (round 910).** `gate.sh` writes `.scratch/gate-build.log` on every run, and when nothing needs
  rebuilding that file contains one line: `[100%] Built target server_dll`. The shipped tree actually
  emits **six `LNK4006` warnings over three symbols** (`_putc`, `__amsg_exit`, `___app_type`, all
  `LIBCMT.lib(...)` against a local object), and they appear only after
  `cmake --build build --clean-first`. Grepping an incremental log for warnings therefore returns
  "zero" on a tree that has six, and that log is exactly what the gate's compile check reads.
  **Rule: to count warnings, force a clean rebuild first; otherwise you are reading a cache.**
  Same family as the transient `C1083` below: a build log mistaken for a measurement.
- **A lone `C1083: Cannot open compiler intermediate file '<garbage>.tmp'` with no source location
  is the build harness, not the source (round 894).** It appeared in a `gate.sh` run immediately
  after a header change and read exactly like a compile-error regression introduced by that change.
  It is a **transient parallel-build temp-file collision**: re-running the build produced **0**
  errors and the gate then passed with all baselines held. The tell is the filename: `a00032gl`,
  not a path, and not a `.c` file, and the absence of any line/column. Before treating a C1083 as
  a finding, check whether any `error C####` line names a *source* file; if none does, rebuild
  before touching the code. Setting `TMPDIR` or dropping to `-j4` avoids it.
- **`cmake --build build` fails by design at the post-link layout step** with no
  `error C####`/`LNK####`, and `make` then **deletes `build/server.dll`**. The deliverable must
  be regenerated with `scripts/split_link.sh` + `postlink_residual.py --write`. Leaving the tree
  after a bare build means the artifact is simply gone.
- **`rebrew verify --full` rewrites `src/rebrew-functions.toml`** (it demotes `SIZE_MISMATCH` to
  `STUB`) and the file is mode 444, so restoring it needs `chmod u+w` first.
- **`scripts/linktest.sh` measures `.text` only, and a data-type change can be `.text`-neutral
  while costing `.data`.** Round 521 replaced five overlapping array definitions in
  `loadsave3.c` with correctly-typed scalars: `linktest.sh` reported `8634 -> 8634 (+0)`, and the
  gate's `.data` ceiling caught **21,836 -> 22,072 (+236)** in the same change. `linktest.sh`
  reads `.text`; only `gate.sh` reads the raw-link `.data`, and it is the only ruler that saw it.
  Measure a data edit with `gate.sh`, not `linktest.sh`.
- **The `.scratch/residue_base.log` that `linktest.sh` diffs against is not regenerated
  automatically and can be many rounds stale.** A `+1` in that table is meaningless until the
  baseline is refreshed; `bash scripts/linktest.sh --new-base <file.c>` rewrites it (and prints no
  delta). Cross-check by reverting the edit and confirming the baseline reproduces.
- **`cmake --build build -j8` on its own leaves the tree in a state that reports garbage residue.**
  The post-link layout step fails by design and `make` then **deletes `build/server.dll`**, while
  `build/split_poc/` keeps the object set from the previous run. Residue read from that state is
  meaningless: round 889 measured **58,614** and then **116,814** from two such states, when the
  true value was 8,634. Worse, it is *sticky*: `git checkout` of the sources restores `verify`
  (281/283) but not the residue, so the tree looks reverted and still reports a false number. The
  recovery is to delete the split state and take a full gate pass:
  `rm -rf build/split_poc build/server.dll && bash scripts/gate.sh`.
  **The tell is `split_link.sh` printing `exactly at their reference VA: 0`**: the same
  composition-collapse signal `linktest.sh` refuses to measure through
  (`msvc6-c-shapes.md` §124). Treat any residue number taken without a fresh `postlink_residual.py`
  run after a source change as unmeasured, not as a regression.
- **A `cmake --build` also deletes the deliverable**, so a round that builds to test something and
  then compares residue is comparing a missing or stale artifact. Always rebuild the split state
  before reading residue; never carry a number across a bare build.
- **`rebrew verify --data` prints a `UserWarning` per `DATA` marker whose VA has no `name` in
  `src/rebrew-data.toml`, and the marker is then dropped from the inventory as `unknown`.** The
  warning text ("has no declaration on the following line and no name in the data metadata")
  reads like a *source* defect, but the marker can sit over a perfectly good definition; the
  missing field is the metadata. Round 882: `vfs4.c` `0x1002944c` (`s_rb_1002944c` and four
  siblings) and `vfs_OpenStream.c` `0x100294a4` (`s_0x_08X_length_100294a4`) both warned while
  the definitions were present and relocating correctly. A previous `lint --fix` had written
  **`section` only** into those two entries (TODO round 559, W016), and `scan_globals` needs
  `name`, not `section`, to attribute the marker. Writing `name`/`type`/`size` through
  `rebrew.data_metadata.set_data_field` (the same API `--fix` uses; run it from
  `~/.local/share/uv/tools/rebrew/bin/python`, the repo venv lacks `zstandard`) cleared both
  warnings and raised `verify --data` matched **83 -> 85**. A warning count here is not a
  `.text` or `.data` measure: the gate held 8,634 / 21,836 unchanged across the edit.
- **`rebrew verify --data` warnings go to stderr and are invisible to `--json` consumers that
  pipe stdout only.** `2>/dev/null` drops them; the `matched` count is the only surviving signal,
  and a silent drop lowers it rather than printing anything. Grep stderr when the count moves.
- **`verify --data` compares only symbols that carry a name *and* a resolvable size, and it drops
  the rest without saying so.** `data_verify.section_symbol_bytes` skips an entry with no `name`;
  with no `size` it falls back to `estimate_type_size(type)`, and skips again if that fails. So
  `matched` is a count of *attributable* symbols, not of `.data` symbols, and the number is not
  comparable between rounds where naming changed. Round 883: 20 `.data` entries had `section`
  only, were skipped unconditionally, and all 20 turned out to be byte-identical: `matched` went
  **85 → 105** with no output change whatsoever. Read `matched` as coverage, never as correctness;
  a `mismatched`/`missing` list is the only verdict here.
- **`rebrew todo`'s `start-data` lane and `verify --data` are not the same set, and the lane can
  never empty for link-produced data.** `start-data` is every metadata entry with a blank or
  `UNCHECKED` status (`todo.py` `_collect_start_data`). The 18 `__imp__*` IAT slots qualify and
  always will: they are linker output, not source definitions, so no source symbol can "verify"
  them. Their bytes were confirmed identical to the reference at `0x10024000..0x10024044` in round
  883. Treat a `start-data` item whose VA is in `.idata` as permanently unactionable rather than
  as pending work.
- **Most of this binary's "`.data`" is really BSS, so a `matched` tick on those symbols proves
  nothing.** `.data` carries `rawsize 0xe000` over a `vsize 0x174059c`, so only
  `0x10027000..0x10035000` has file bytes; every `.data` symbol above that is zero-fill.
  `rebrew verify --data` compares via `pefile`-style section reads, and on a zero-fill VA it
  compares zero against zero: a guaranteed match. Round 884 sized 57 `.data` symbols and
  `matched` rose 105 → 108, but **54 of the 57 are above `0x10035000`**: the rise is accounting,
  not verification. Before treating a data `matched` increase as evidence, check the symbol's VA
  against the section's raw extent. `.bss` and `.idata` entries are in the same category.
- **The built binary's `.text` / `.rdata` / `.reloc` VirtualSize already equal the reference's**
  (`0x22846` / `0x2e81` / `0x10374`). A size-mismatch hunt on this target is a dead end; the
  deliverable's remaining gap is *content* (8,634 residue bytes inside `.text`), so measure with
  residue, not with section sizes.

---

## 10. How to check any claim in this document

- Residue and per-function numbers: `bash scripts/linktest.sh <one source>` against
  `.scratch/residue_base.log`, or regenerate with `scripts/split_link.sh` +
  `scripts/postlink_residual.py --write build/server.dll`.
- Frames, slot maps, prologues: disassemble `original/Server/server.dll` at the VA and compare
  with the built image (`instr_diff.py <va> --built build/server.dll`).
- Gap curves: `scripts/gaptrace.py <va> <source> _<symbol>`: **no size argument**.
- Slot maps: the sentinel-initial probe (`msvc6-allocator.md` Finding 60).
- Gate: `bash scripts/gate.sh` (lint + compile errors only + `verify --full` against a 281
  baseline). Expect the build's post-link step to fail; only `error C####`/`LNK####` count.

## 6h. An "undefined symbol" in this tree usually is not one: check `link_stubs.c` first (round 924)

`src/link_stubs.c` no longer exists (2026-10-06): the game's zero-initialized data is generated by `scripts/gen_bss_layout.py` (docs/msvc6-link-layout.md 5d) and the placeholders below are gone. The rest of this section is history.

Round 924 found a real bug with a tempting generalisation attached, and the generalisation was
wrong. Recording both halves.

**The real bug.** `cm_ExSellObjekt.c` called

```c
LogMessageInternal("D:\\...\\command.c", 0x2e45, g_error_msg_sell_failed, 8);
```

where `g_error_msg_sell_failed` is declared `extern char[]` and has **no definition in the tree and
no entry in `rebrew-data.toml`**. It therefore never reaches the linker as a named reference at all;
the operand came out as a bare immediate (`push 0x11766604`) where the reference has a relocated
`push 0x1002cc8c`. Fixing it to a literal moved linked `.text` residue **8,634 -> 8,633** and
raw-link `.data` differing **21,836 -> 21,481**.

**The wrong generalisation.** Every COFF object in the build reports **587 distinct undefined
externals**, among them a large `_s_..._1002xxxx` string family: e.g.
`_s_D__Develop_DieGildeAddOn_command_1002c748` is undefined in 12 places, and
`_s_amt_fio_LoadAemter____Can_t_load_10029f78` in one. That *looks* like the same bug repeated 20
times. It is not:

- **Those symbols are defined: in `src/link_stubs.c`, as 1-byte empty strings.**
  `char s_D__Develop_DieGildeAddOn_command_1002c748[1] = "";` and 10 more like it. They are
  deliberate placeholders whose only job is to give the linker a symbol; their *content* is
  irrelevant because the shipped `.data` is blitted wholesale from the layout package.
- **Giving one its real content is a measured loss.** Replacing the 1-byte stub with the reference's
  actual 43-byte `"D:\Develop\DieGildeAddOn\command\command.c"` grew `.data` and pushed the common
  symbols past their span: **residue 8,633 -> 8,635 (+2)**. Reverted.
- `link_stubs.c`'s own header already says why: `.data`'s pad budget is compared against the
  reference's `.data` **VirtualSize**, so any stub that grows overshoots and every operand naming a
  common symbol fails (round 139).

**Four sweep detectors were written for this and all four were wrong**, which is itself the finding:

| detector | reported | why it was wrong |
|---|---|---|
| regex `extern` vs `defined` over `src/**` | 22 pairs | counted symbols merely *named in docstrings* until comments were stripped; then 5 |
| same, comments stripped | 37 pairs | treated the `(char*) 0x10031004` cast convention as a definition it had not seen |
| object COFF `*UND*` list, minus a `src/` definition scan | 60 | the scan missed `link_stubs.c`'s own declaration forms, so it re-flagged symbols that file defines |
| same, with `link_stubs.c` defs extracted | 160 | still flagged common symbols the **layout package** resolves (`g_entity_type_table`, 29 uses) that the linker is perfectly happy with |

The last one is the tell: when a detector reports 160 "missing" symbols in a tree whose link is green
and whose import table matches the reference exactly, **the detector is wrong, not the tree**. The
authoritative answer was available the whole time and cost nothing: the link succeeds, `gate.sh`
passes, and `link_stubs.c` documents its placeholder scheme in its own header. Prefer the toolchain's
verdict over any grep.

**And a fifth trap sat underneath all four: a COFF COMMON symbol looks undefined.**
`int x;` at file scope is a *tentative definition*; the compiler emits it with `SectionNumber = 0`
and `Value = size`, which is the same shape an undefined reference has. Every detector above counted
those as missing. Verified directly on the object that defines them
(`spiel_c/gm_NextEntityQueryMatch.c.obj`): `_g_slot_table`, `_g_entity_state_base` and
`_g_entity_type_bytes` all report `secn=0` **in the file that defines them.** They are correct C89 and
the linker allocates them. A detector built on "undefined in the object symbol table" cannot
distinguish a tentative definition from a missing one; the linker can, which is why the link is green.

**So the test is not "is this symbol undefined" but "does it have a definition *anywhere*".**
`grep -rn '<symbol>' src/` and look for a non-`extern` line: `link_stubs.c` is where they live. A
symbol defined there as `[1] = ""` is finished work, not a defect; a symbol with *no* definition
anywhere is the bug. Distinguishing those two took most of this round, and the count difference is
the difference between a 1-item fix (done) and a 20-item vein (does not exist).

**One genuine residue remains in the neighbourhood:** `gm_Open.c` used the shared symbol at 11 sites,
and the reference does push one shared address (`0x10031004`) at every one of them, so the shape was
right and only the definition was missing. Rewritten to the `(char*) 0x10031004` cast the rest of the
tree uses for that string: **byte-neutral**, 11 undefined operands removed.


## 11. A stale operand can be a *consequence*, not a cause: read the fixer before chasing it (round 932)

Round 931 found an operand that read `[0x11766664]` (the stub region) where the reference reads
`[0x101de450]`, fixed the symbol name, and round 932 removed the duplicate definition that was
displacing it, and the operand **still** did not move. Disassembling `scripts/postlink_residual.py`
explains it and saves the next round from the same chase:

```python
def _same(lo, hi):
    return all(ref[i] == text[i] for i in range(lo, hi) if i not in slots)
...
if not _same(i - 12, i) or not _same(i + 4, i + 16):
    continue          # do NOT rewrite this slot
struct.pack_into("<I", text, i, val)
```

The postlink operand fixer rewrites a slot **only when the 12 bytes before and 16 bytes after it already
match the reference**. At a site inside a function that has diverged, the neighbourhood does not match,
so the fixer correctly declines and the slot keeps whatever our link produced. **The stale operand is
downstream of the function's divergence; fixing the symbol changes nothing about placement.**

Measured on `cm_ExSellObjekt`: aligning the two instruction streams by mnemonic+operand shows **674
instructions on each side** with the first differences being stack-slot offsets
(`mov [esp+0x14],edi` vs `mov [esp+0x24],edi`). No missing code, no wrong instruction: different slot
numbers, which is allocator Finding 63's class.

**So: before treating a mismatched operand as the target, check whether the fixer would even accept a
rewrite there.** If the surrounding bytes differ, the operand is a readout of the divergence, not a
lever on it. The cheap test is the locality window itself: compare 12 bytes before and 16 after the
slot on both sides.


## 12. After a flag change, the CMake *objects* are stale even when `split_poc` is not (round 941)

`rm -rf build/split_poc` is the documented recovery for a collapsed composition, and it is **not
sufficient after a per-file flag change**. The objects themselves were compiled with the old flag, and
deleting only the split workspace leaves them in place. Measured: after reducing a `/Ow` sweep from seven
files back to one and deleting `build/split_poc`, the link still reported
`exactly at their reference VA: 0` and **"22 objects too long"**, because six objects still carried
`/Ow` from the previous build. Touching the sources did not help either; CMake rebuilt them, but other
objects from the swept set were untouched.

**The only reliable recovery is the full cycle:**

```sh
rm -rf build
cmake -B build --toolchain cmake/toolchain-msvc-6.0-sp6-docker.cmake \
      -DCMAKE_BUILD_TYPE=Release -DREBREW_DEBUG_INFO=OFF
rm -rf build/split_poc && bash scripts/split_link.sh
```

**The tell is the same as always** (`exactly at their reference VA: 0` and a residue above ~50%), and
the danger is that this state is *indistinguishable from a genuine composition failure*. If a flag
change appears to blow the budget, clean-rebuild before concluding anything about the flag.

**And two transient compiler errors to expect on a parallel rebuild:** `C1083: Cannot open compiler
intermediate file 'a00032xx'` and `C1001: INTERNAL COMPILER ERROR`. Both appeared on `-j4` and both
cleared on `-j1` / serial `TMPDIR=/tmp` rebuilds with no source change. Neither is a defect in the tree.


## 13. A positional comparator cannot classify a divergence (rounds 927, 955, 963)

Three times this session a script was written to *label* a divergence ("slot vs form", "first differing
instruction kind") by comparing the two instruction streams element by element. All three produced
garbage, and for the same reason: **the streams desynchronise at the first divergence**, so every index
after it pairs unrelated instructions.

Measured round 963: classifying all 19 residue carriers' first divergence as `SLOT` (same mnemonic,
operand differs only in a hex literal) or `form` labelled **every carrier `form`**, including ones whose
actual difference is a single rotated stack slot. Typical false pair:
`push ebp` against `push ebx`, or `test ebx,ebx` against a bare jump target.

**A label is a claim about aligned correspondence, so it needs alignment first.** The working methods in
this project all align on something that survives drift:

- **decode each image from its own function entry** (never the reference at our VA, that produced a
  coincidental `lea`/`add` "match" in round 955);
- **compare by source address** via `build/split_poc.map`, not by stream index;
- **or compare counts** over a whole function (round 961's slot-use histogram: reference `[esp+0x20]` 7 /
  `[esp+0x24]` 3 against our 5 / 4, which is what actually located the three-reference rotation).

**When a classifier answers "all of them are the same kind", suspect the classifier, not the data.**

## 14. An apparent missing instruction can be a compiler-proved-dead block (round 963)

`cm_ProcessCommandQueue` shows the reference emitting `test ebx,ebx; je <unlink>` before a `jmp`, where we
jump straight through, which reads as five bytes of missing code. It is not.

The header proves the target's join test is **provably-true dead code**: both predecessors enter with
`ebx != 0`, msvc6 constant-folds that, and deletes the block. **C cannot request a test whose operand the
compiler can prove nonzero**, so no spelling reaches those bytes. Corroborated by sp5-pp mismatching the
identical 15 offsets, and the fusion is invariant across every available MSVC6 generator and flag.

**Before treating absent instructions as missing source, check whether the compiler can prove the block
dead.** A redundant test in the reference is a *consequence* of how the original was written or built, not
a thing to spell.


## 15. `[esp+N]` is not comparable between two images without normalising esp depth (round 969)

A per-slot frequency table over a function ("how many instructions touch `[esp+0x34]` here versus there")
is a tempting way to find an extra or missing stack slot. Measured on `cm_ExSellObjekt`, it reports
`0x34` and `0x3c` used **only by our build** and `0x40` **only by the reference**, which reads as a frame
difference.

**It is an artefact: `esp` moves, so the same physical slot appears as different displacements on the two
sides.** The carrier's own header had already recorded this for the same two sites: *"tracking esp depth
through the pushes, the reference's `[esp+0x44]` and our `[esp+0x3c]` are both frame+0x468"*, and round
969 rediscovered it the expensive way.

**Every site that sits on a different push depth will show a phantom difference**, which is most of them:
the two `lea` sites at `0x1000d986`/`0x1000d993` are argument addresses whose displacements differ partly
because the pushes *between* them differ.

**So: normalise to the frame base before comparing slots, or compare only sites known to be at equal esp
depth.** A raw displacement table is not evidence about frame layout.


## 16. Compare branch TARGETS, not instructions, when a loop diverges (rounds 970-971)

A stream comparison of two images compares `jle` against `jle` and reports a match, so a divergence that
consists **only of where the branches go** is invisible to it, and invisible to `rebrew diff` too. Both
rulers agree the instructions are identical and the score stays high while the bytes differ.

Measured on `gv_ExAllocGraveyardWorker` (round 970): indices 99-118 match mnemonic-for-mnemonic and
operand-for-operand, but **three branches target different addresses**:

| index | reference | ours |
|---|---|---|
| 103 `jle` | `0x10011d77` | `0x10011cdb` |
| 116 `je` | `0x10011d77` | `0x10011cdb` |
| 118 `jne` | `0x10011d77` | `0x10011cdb` |

Both targets are the byte-identical 13-byte epilogue, 0x9c apart: the reference keeps two copies and
routes the loop's exits to the later one; we keep one. That is codegen-walls §2's mechanism, and it is
**only visible by comparing `op_str` of the jump instructions**.

**The check:**

```python
for x, y in zip(ref_insns, bld_insns):
    if x.mnemonic.startswith('j') and x.mnemonic == y.mnemonic and x.op_str != y.op_str:
        ...   # same branch, different destination
```

Round 971 ran it across all 19 residue carriers. **Eight have zero**: their residue is not branch-related
at all, while `gm_AllocSpieler` (21) and `ServerMainThread` (14) hold most of the branch-related
divergence. That partition is worth having before choosing a target: a carrier with many target-differing
branches is a block-placement story, one with none is an instruction-form story.

## 17. `cmake --build build` failing at postlink is the DESIGNED state, not a broken tree (round 976)

A clean `rm -rf build` + configure + `cmake --build build` fails:

```
error: postlink failed: built .text is not position-aligned with the reference: only
4847/7463 layout-map entries validate (64.9%, minimum 90%). .text VirtualSize built
0x221f6 vs reference 0x22846.
```

`.text` 0x221f6 is **0x650 short of the reference**, and every symptom reads like a real regression: the
linker deletes `server.dll`, `build/server.dll` does not exist, and the coverage gate refuses. Round 976
spent its opening on this and nearly bisected the source tree looking for the commit that broke it.

**Nothing is broken.** `CMakeLists.txt:442-468` attaches `rebrew build postlink --layout` as a POST_BUILD step of
the `server_dll` target, and that step is expected to fail until the tree is position-aligned: the
coverage gate exists precisely so a wrong-offset patch cannot be written silently. The plain CMake link
lays `.text` out in compile order, which is not the reference's order, so it can never pass.

**The deliverable is the `final` target, not `server_dll`:**

```
cmake --build build --target final
```

`final` (`CMakeLists.txt:566-578`) links `split_link.sh`'s per-reference-offset composition and then runs
`postlink_residual.py --write build/server.dll`. Only that path produces `build/server.dll`.

Two tells that the failure is the designed one, not a real break:

- The error names **position alignment**, not a compile or link error. No `error C####` / `error LNK####`
  appears anywhere in the build log.
- `git diff --stat` against `HEAD` is empty. A tree that compiles every object can still fail this step.

**Bisecting on this symptom is pure waste**: because the last source-touching commit is many rounds back
(round 958 at the time), a `git bisect` on "build fails" would report that commit and send the next round
hunting a source change that never happened. Confirm the *designed* failure first by checking for a compile
error and by diffing the tree, then build `--target final` and read the residue table.

## 18. A raw dword scan and a disassembler op_str scan disagree: neither alone is proof of absence (round 977)

Chasing whether `g_query_limit`'s recorded VA (`0x10035450`, `src/rebrew-data.toml:606`) was real, two scans
of the *same* reference gave opposite answers:

- A `capstone` scan of every `.text` instruction, testing `hex(0x10035450) in ins.op_str`, reported
  **zero** hits for `0x10035450` and two for `0x100a8c30`.
- A raw 4-byte little-endian scan of the whole file reported **15** hits for `0x10035450`.

The capstone result was taken as evidence that the toml carried a wrong address for the symbol, and that
`rebrew data list --json` had collided two symbols under one name. Both conclusions were wrong.

**The capstone scan was the broken one**, twice over:

1. It was handed `tdata = d[ptr:]` (a slice starting at the section's **file** offset) but disassembled at
   `tva` and then compared against `ins.op_str`. The scan loop iterated the slice from index 0 while the
   addresses it printed came from `tva`; every per-hit offset needed `tva + h`, not `h`. Hits were real but
   the printed addresses were shifted by the section VA, so they never matched the pattern being searched.
2. Independently, `mov eax, dword ptr [0x10035450]` **is** rendered by this capstone build as an absolute
   operand, so a correct scan *would* have found it: the failure was purely the indexing error above.

Decoding the raw hits directly settled it: `0x10035450` is a real `.bss` counter, and the reference touches
it 15 times (`mov eax,[0x10035450]` at `0x10014239` and `0x10015f2e`, `inc`/`dec` forms at `0x10015d82`
and `0x10015d89`, among others). The toml address is correct and `rebrew data list --json` is not lying.

**The check, before concluding a tool is wrong from an absence:** confirm the absence with a scan that
shares no code with the first one.

```bash
# raw dword scan: independent of any disassembler's operand formatting and of slicing bugs
python3 -c "d=open('original/Server/server.dll','rb').read(); \
  print(sum(1 for i in range(len(d)) if d[i:i+4]==(0x10035450).to_bytes(4,'little')))"
```

An "address is never referenced" result from a single disassembler scan is not evidence of absence: it is
evidence about that scan. This is the fourth self-inflicted measurement error recorded in this document,
and like the others it produced a plausible, confident, wrong finding (a claimed `rebrew` bug) that only a
second independent check dissolved.

## 19. `rebrew todo`'s ROI score is flat across `start-data`, so its ordering carries no signal (round 977)

`rebrew todo --json` is the objective's designated "pick highest-ROI item first" tool, and the round brief
routes work by its order. For the `start-data` category that order is **meaningless**: every one of the 207
items scores exactly `10.0`.

```
start-data roi_score histogram: {10.0: 207}
```

The top-20 page therefore reads as a ranked list while being an arbitrary sample, and this round's brief
pointed at it ("`rebrew todo` shows 246 start-data items and 34 data-drift"). Worked in that order, a round
starts on `__imp__GetLocalTime@4`, an **IAT slot at the head of `.rdata`** (`0x10024000`+) that the linker
supplies and no C source can affect. 84 of the 207 are `__imp_*` of this kind.

`improve-match` is not flat: `gm_AllocSpieler` scores 39.1 and `ServerMainThread` 15.9, both real. The
flatness is specific to `start-data`.

**The check.** Histogram the ROI column before trusting the order:

```bash
rebrew todo -c start-data -n 300 --json | \
  python3 -c "import json,sys,collections; \
  print(collections.Counter(i['roi_score'] for i in json.load(sys.stdin)['items']))"
```

A single-valued histogram means the ranking is not a ranking. Rank by measured residue instead
(`scripts/linktest.sh` / `scripts/first_divergence.py`), which is what the objective's own "judge candidates
at the link, not with object scores" rule already says.

## 20. Raw-link `.data` is a size-only filler and cannot reach zero: the ceiling is the right check (round 980)

Round 977 reported "all 8628 differing bytes are in `.text`" and concluded the `.data` axis was closed. That
is true of the **shipped** file but was stated without the mechanism, and the mechanism matters because it
says the *raw-link* number is not a target at all.

`scripts/split_link.sh:196-221` generates `data_restore_split.c`: a blob whose bytes are copied from the
reference's `.data` **tail**, and appends it to the link:

```
# The pad is a LENGTH-only filler (its bytes are the reference .data tail and
# postlink overwrites .data wholesale), but inserting it FIRST displaced every
# game .data symbol by +0x74a0 ...
GAP=0x74a0
```

So `data_restore_split.obj` exists to make the raw `.data` **size** land on the reference's `0xe000`, not to
reproduce its bytes. Attributing the raw-link `.data` diff by owning object makes that explicit:

| object | differing bytes | what it is |
|---|---|---|
| `data_restore_split.obj` | 6,207 | the length-only filler above |
| `fold_literals.obj` | 833 | `gen_fold_literals.py` shim |
| `deflate.c.obj` (stock zlib) | - | `ZLIB_VERSION "1.1.3"` COMDAT |

The 21,481 the gate enforces as `DATA_BASELINE` is therefore **mostly the filler's own bytes plus game
`.data` that the link places by COMDAT hash order** (`CMakeLists.txt:443-448`). It cannot be driven to zero
while a filler is present, and the filler is present because the raw size must be `0xe000`.

**The gate already models this correctly**: `scripts/gate.sh:160` fails on `-gt` and passes on `-le`, i.e. a
*ceiling*, not an equality. Reading it as a progress target is the error.

**One in-scope defect found and correctly left alone.** The first `.data` divergence is at `0x1002706c`, and
it is a genuine byte-level difference, not a filler artifact:

```
REF  0x10027058  "Sending Broadcast\0\0\0" "1.1.3\0\0\0" <ptr->0x1002706c> 01 00 00 00 02 ...
BLD  0x10027058  "Sending Broadcast\0\0\0" <ptr->0x10027070> "1.1.3\0\0\0" 01 00 00 00 02 ...
```

The string and its own pointer are **swapped**. Our `broadcast.c` span is correct (`s_Sending_Broadcast`
ends at `0x1002706c`, matching the reference); the swap is inside the `??_C@_05NLJN@1?41?43?$AA@` COMDAT and
the `zlib_version` pointer emitted by **`references/zlib-1.1.3/deflate.c`** (`zlib.h:40`
`#define ZLIB_VERSION "1.1.3"`). That is stock zlib, which the objective forbids reversing and which links
as a stock library. **In scope it is not**, and it is the one place in the section that could have been
mistaken for game-source work.

**Method point.** Sections 148-158 of `msvc6-c-shapes.md` are a full `.data` pass: eleven rounds that fixed
three `rebrew` tool defects, produced `int g_log_level_table[3]` (a 36-byte surplus costing 231), the
`g_log_format_table[96]` fix, and took raw-link `.data` from 27,953 downward. Round 977 declared the `.data`
vein "mined out" after reading only the shipped file's byte deltas and never reading that pass. **Check for
an existing section series on the round's assigned topic before declaring it exhausted**: the brief's
".data / types / structs" direction had a dedicated eleven-round history the round-977 work did not consult.

## 21. Disassembling `.text` from its start gives wrong instruction boundaries: every statistic built on it is junk (round 988)

`msvc6` pads between functions, and `.text` begins with bytes that are not a valid instruction stream at
offset 0. A linear sweep from section start therefore desynchronises within the first few hundred bytes and
**mis-classifies real instructions as data for the entire section**.

Measured this round. Attributing each of the 8,628 differing bytes to the instruction that contains it:

| decode origin | bytes "inside an instruction" | bytes "not covered" |
|---|---|---|
| `.text` start (linear sweep) | 2,565 (29.7%) | **6,063 (70.3%)** |
| each carrier's **own function entry** | 8,498 (98.5%) | 130 (1.5%) |

The first figure is not a finding about the residue; it is a finding about the sweep. It reads as a dramatic
result ("70% of the residue is not code at all"), and it is false. Decoding from the known entry points
shows the truth: **98.5% of the differing bytes are inside real instructions**, and the remaining 130 are
inter-function padding.

The tell was on screen and I nearly wrote it up anyway: the "uncovered" bytes printed as
`89 7c 24 10 89 7c 24 14 ...`, which is `mov [esp+0x10],edi` / `mov [esp+0x14],edi` repeated. Real code,
labelled DATA by a broken sweep.

**This is `first_divergence.py`'s documented rule, applied to a statistic instead of a diff.** That script
decodes each image from its own function entry and says so in its header; round 988 rebuilt an ad-hoc
analysis without reusing it, and paid for the omission.

**The check:** never disassemble `.text` from its start. Use the function inventory's entries, or
`scripts/first_divergence.py` / `scripts/fault_address.py`, which already do it correctly.

**The correct classification** (per-instruction, decoded from entries):

| reference instruction | differing bytes | share |
|---|---|---|
| `mov` | 2,971 | 34.4% |
| `push` | 827 | 9.6% |
| `lea` | 645 | 7.5% |
| `call` | 626 | 7.3% |
| `cmp` | 600 | 7.0% |
| `add` | 450 | 5.2% |
| `je` | 443 | 5.1% |
| `jmp` | 245 | 2.8% |
| `test` / `jne` / `xor` | 167 / 149 / 148 | ~1.8% each |
| `fmul` | 146 | 1.7% |
| inter-function padding | 130 | 1.5% |

**64 distinct mnemonics** are touched, with the top eight carrying 76%. A long tail across integer,
branch and x87 instructions is what the documented scheduler/register-role classification predicts; it is
**not** the shape of a single systemic cause, and no mnemonic dominates enough to be one.

## 22. `object_span_check.py` reads CMake's object, but `linktest.sh` recompiles elsewhere (round 989)

The span filter is applied *before* probing, and it is the check that stops a size-increasing edit from
collapsing the composition. Round 989 ran it on a live probe and it reported the carrier **exactly at its
span**, so the probe looked free, and the span filter passed it. The link then collapsed the composition,
and the carrier was in fact **+16 over span**, identical to the unprobed §159 measurement.

**Why.** `scripts/linktest.sh` recompiles the named file with the command `build.make` records, but writes
its object into its own work directory; it does **not** refresh
`build/CMakeFiles/server_dll.dir/<path>.c.obj`. `scripts/object_span_check.py` measures that CMake object.
So running the checker after `linktest.sh` measures the **previous** build:

```
src/.../gm_AllocSpieler.c          21:54:41   <- source reverted
build/.../gm_AllocSpieler.c.obj    21:53:36   <- object is 65s older
```

The stale object still held the pre-probe shape, so the checker said "exactly at span" about source that had
already grown +16.

**The rule.** `object_span_check.py` is only meaningful against objects CMake itself just built. Before
trusting it:

```bash
cmake --build build            # refresh CMake's objects FIRST
python3 scripts/object_span_check.py
```

Running it after a `linktest.sh` probe measures the wrong artefact. This is measure-traps §12's class
("after a flag change, the CMake objects are stale") generalised: **any tool that reads `build/` is telling
you about the last CMake build, not about your working tree.**

**Cost this round:** a probe that looked span-neutral was actually +16; catching it required a full rebuild
and a composition collapse to notice. The `linktest.sh` collapse message ("only 0 symbols landed at their
reference VA") is what surfaced it: that guard earned its place.

**Also confirmed:** the §159 probing result reproduces exactly. Caching **only** `slot+0x14` (rather than
both `slot+0x20` and `slot+0x14`) still measures **+16 obj / span overflow**, so the +16 is caused by the
single extra frame slot, not by the number of cached values. Any caching fix on that carrier must first free
16 bytes elsewhere in the same object.

## 23. Counting instructions from the shipped image measures postlink's output, not the object (round 990)

Round 990 set out to free the 16 bytes blocking `gm_AllocSpieler`'s caching fix, and began by asking where
our object is larger than the reference. Decoding both images from `0x10018850` gave:

```
REF insns 1056 (bytes 3689)   BLD insns 1014 (bytes 3577)
```

which reads as "our object is 112 bytes *shorter*, with 119 bytes of padding", and that is wrong. Both
numbers describe the **shipped** `build/server.dll`, which postlink has already rewritten; they are not the
object the linker lays out.

**The object, read directly from the COFF:**

```
.text raw 3696 bytes, 1061 instructions decoded, code ends at offset 0xe70 = 3696
trailing nop padding: 7 bytes (90909090909090), matching the reference span
```

**1061 instructions filling all 3696 bytes: zero headroom**, exactly as `object_span_check.py` says. The
"1014 instructions / 119 bytes of padding" figure was an artifact of the decode window: disassembling 3696
bytes from `0x10018850` in the *shipped* image stops early because postlink has rewritten bytes the stream
crosses.

**The reliable way to count**, which also resolves the discrepancy with §141:

| source | instructions | note |
|---|---|---|
| reference **image**, 3696-byte span, from the function entry | **1063** | truth for the reference |
| our **object** `.text`, decoded from its start | **1061** | truth for ours |
| our **shipped image**, same window | 1014 | postlink-rewritten; **not** a measure of code size |

Net difference: **2 instructions**, which agrees with §141's "15 net instructions across the eight heaviest
rows" in spirit, while §141's per-row `1054 vs 1056` figures came from the same shipped-image decode and
carry the same caveat.

**Two lessons.** (1) `build/server.dll` is postlink output; never count instructions in it and call the
number the object's. Read `build/CMakeFiles/server_dll.dir/<...>.c.obj` instead. (2) A disassembly window
that "ends early" is a signal that the stream desynchronised, not evidence about how much code exists:
§21 is the same failure one level up.

**Outcome for the round's actual goal:** the 16 bytes cannot be found by shrinking, because the object is
already exactly at its span and its code fills it. Any editing fix must be **size-neutral**, not merely
"small enough", which is why both caching probes measured +16 and the composition collapsed.

## 24. Instruction counts across two images are not comparable: the decoder's stop rule decides the answer (round 991)

Chasing whether any carrier is *missing code* rather than *reordered code*, round 991 compared instruction
counts between the reference and our build for all 19 carriers. **The answer changed with every truncation
rule**, which is the tell that the measurement is about the method, not the target:

| stop rule | `gm_AllocSpieler` ref / bld | total delta |
|---|---|---|
| full span, no truncation | 1063 / 1014 (−49) | −121 |
| truncate at last `ret`, drop trailing `nop` | 1056 / 1014 (−42) | −121 |
| truncate at last `ret` before padding | 1056 / 917 (−139) | −216 |
| `scripts/first_divergence.py` (decodes over the span) | 1063 / 1014 | - |

A −42 or a −139 for the same function is not a measurement; it is three different bugs. Every rule decodes
past the function's true end and then reports the garbage as code: in the reference that produced a bogus
`popal` at `0x10002e9c`, in ours a bogus `push 0xfe811004`.

**The desync-free measurement is the object's `.text` raw size**, read from the COFF, against the reference
span:

```
gm_AllocSpieler   span 3696   our object .text raw 3696   +0
CrashDump         span 2128   our object .text raw 2128   +0
cm_ExSellObjekt   span 2064   our object .text raw 2064   +0
```

Every carrier is **exactly at its span**. That is unambiguous (no decoding, no stop rule) and it confirms
§23 and round 990.

**The rule.** Do not compare instruction *counts* between two images. A count depends on where you stop, and
where you stop requires knowing the function's end, which is exactly what is in doubt. Compare **byte
lengths from the object**, which are declared, or compare instruction *streams* with an alignment-aware
tool. The mnemonics-multiset comparison used this round returned "differs by 87" for `gm_AllocSpieler`,
including 7 `nop`s and 2 extra `ret`s: all of them decoder garbage past the `ret` at `0x100196b8`.

**Third instance of this class** (§21 decoding from section start, §23 counting in postlink output, §24
counting across images). The common cause is that a disassembler always produces *something*; desynchronised
output is syntactically valid and reads like a finding.

## 25. `instr_diff.py`'s default `--built` reads the postlink composition, not the object (round 1000)

`scripts/instr_diff.py` defaults to `BUILT = build/split_poc.dll`. That is the per-reference-offset **composition**
(postlink's output), not the object the linker lays out. Round 990 found the same distinction for instruction
*counts* (measure-traps §23); this is the same trap one tool over, and this tool's default path is the wrong one.

Measured on four carriers, image vs `--obj`:

| carrier | image: ref / built | object: ref / built | image aligned | object aligned |
|---|---|---|---|---|
| `cm_ExProdObjekt` `0x1000e140` | 354 / 354 | 354 / **369** | 348/354 (98.3%) | **349/354 (98.6%)** |
| `ls_LoadBuildingEntityState` `0x100128f0` | 499 / 497 | 499 / **506** | 438/499 (87.8%) | **448/499 (89.8%)** |
| `cm_ProcessCommandQueue` `0x1000aac0` | 205 / 203 | 205 / **204** | 202/205 | 202/205 |
| `CrashDumpUnhandledExceptionFilter` `0x10002770` | 725 / 729 | 725 / **738** | 357/725 (49.2%) | **371/725 (51.2%)** |

The object consistently holds **more** built instructions than the image (369 vs 354, 506 vs 497, 738 vs 729)
and aligns **better** against the reference (up to +2 points). The composition has already been rewritten by
postlink, and bytes the object's decoder crosses are not the bytes postlink emits.

**Which is right depends on the question.** For "what does the compiler emit" (the reversing question), the
**object** is correct. For "what does the shipped DLL contain", the image is. Every ranking or alignment figure
in this project's docs that came from `instr_diff.py` without `--obj` is therefore the *shipped* view.

**What this does and does not change.** The round-999 ranking (which carriers have the fewest hunks) is
**stable** across both paths, and the key signal identities survive: `CrashDump`'s `ref-only x33: push ADDR` is
the same on both paths, and `cm_ExProdObjekt`'s three-instruction ordering hunk appears either way. So the
round-999 conclusions hold. What changes is the *magnitude*: a 49.2% alignment is really 51.2%, and a
"354 built instructions" is really 369.

**The rule.** Use `--obj build/CMakeFiles/server_dll.dir/<path>.c.obj` when the question is about codegen, and
remember to `cmake --build build` first (measure-traps §22, a stale object measures the previous edit).

## 26. `spiel622.c` holds 16 functions in one object: a per-function span reader must pick the right COMDAT (round 1001)

Round 1001 verified `gm_CalculateProductionValue`'s recorded **"+4 bytes of upward slack"** and found the
figure stale, but reaching that conclusion required noticing that the naive reader is wrong on this file,
which is worth recording separately because two of this project's scripts read objects that way.

`spiel622.c` contains **16 functions**, each its own COMDAT `.text` section in one object:

```
COMDAT .text[2] raw=96   [4] raw=400   [6] raw=368   [8] raw=80   [10] raw=112
[12] raw=96   [14] raw=64   [16] raw=96   [18] raw=128   [20] raw=112
[22] raw=48   [24] raw=48   [26] raw=416   [28] raw=400   [30] raw=112   [32] raw=32
```

A reader that sums or takes the **first** `.text` section gets 96, and a reader that loops without breaking
reports the last one. Both give a number unrelated to the function being asked about. The correct read is the
COMDAT whose size matches the function's placement:

```
gm_CalculateProductionValue  0x10019720 .. 0x100198b0  = 400 bytes  ->  COMDAT .text[4] raw=400
```

**Slack is 0, not +4.** The header at `spiel622.c:174-178` records:

```
 * Per shapes 88 the real body is 396 and the COMDAT span is 400 (4 pad bytes),
 * so the ceiling runs 396/397/398/400 -> 400 and only 401 -> 416: there is
 * **+4 bytes of upward slack** and 397 is SPAN-NEUTRAL.
```

The COMDAT is already **400**: it fills the span exactly, and the 4 trailing `nop`s are *inside* it, not spare
capacity. A 397-byte variant would fit in the 400-byte COMDAT only if it were padded back to 400; a 401-byte
one would push the COMDAT to 416 and displace every later function in the file. So the "upward slack" reading
inverts the geometry: there is no room to grow, and the recorded reason for the 397 variant being affordable
does not hold.

**The practical consequence on that carrier is nil**: the 397 shape was already recorded as losing on
*structure*, not size: *"unfolding the compare shifts every byte after 230 and takes the structural diffs from
2 to 53"*, re-measured at **255** aligned against the baseline's **122/123**. The row is retired at its 5-byte
floor for reasons that do not depend on the slack figure. But the figure itself is the **sixth stale header
quantity** found this session, and the first in a multi-function object, where it is easier to get wrong.

**The check.** Read the COMDAT whose raw size matches the function's placement, not the first or last `.text`:

```bash
python3 -c "
import struct,json
fs=json.load(open('db/inventory-server.dll.json'))
vas=sorted(f['va'] for f in fs); V=0x<VA>
span=next(v for v in vas if v>V)-V
d=open('build/CMakeFiles/server_dll.dir/src/Develop/<path>.c.obj','rb').read()
n=struct.unpack_from('<H',d,2)[0]; off=20+struct.unpack_from('<H',d,16)[0]
m=[struct.unpack_from('<I',d,off+i*40+12)[0] for i in range(n)
   if d[off+i*40:off+i*40+8].rstrip(b'\0')==b'.text']
print('span',span,'comdats',m,'matching',[x for x in m if x==span])"
```

If no COMDAT matches the span, the object is stale (measure-traps §22) or the metadata size is wrong: do not
read a slack figure from it.

## 27. `branch_census.py`'s "targetdiff" counts polarity swaps and ±1 drift as structural difference (round 1005)

`scripts/branch_census.py` aligns branch instructions by index and counts those whose target differs. Used as
a classifier (codegen-walls §13) and as a screen, it **overstates** structural difference in two ways, both
measured this round on `ServerMainThread` (106 branches, 14 reported target-differing).

**1. The deltas are mostly ±1..3, not different blocks.** The set of target deltas is
`{-1 x5, -2 x5, -3 x3, +340 x1}`. Nine of the fourteen are a one-to-three-byte displacement drift from a
locally shorter or longer block: the branch reaches the *same* block, one or three bytes off.

**2. The `+340` outlier is a PAIRING artifact, not a different target.** Aligning by index pairs the wrong
instructions once the streams desynchronise by one:

```
reference  0x100098e3  je  0x100097c5     (esi == 0 -> loop back)
           0x100098e9  jmp 0x10009919     (else      -> exit)
ours       0x100098e5  jne 0x1000991a     (esi != 0 -> exit)
           0x100098e7  jmp 0x100097c5     (else      -> loop back)
```

The index-aligned pairs are `je`/`jne` and `jmp`/`jmp`, which subtracts a taken-branch target from a
fallthrough target and yields 340. **Decoded properly, the control flow is identical**: both images send
`esi == 0` to `0x100097c5` and the other edge to the exit block: the reference via `je` + fallthrough, ours
via `jne` + fallthrough. That is §50's documented branch-polarity class, and the two exit targets differ by
exactly **1 byte** (`0x10009919` vs `0x1000991a`) because our block is one byte shorter locally.

**So `branch_census.py`'s count is an upper bound on structural difference, not a measurement of it.** The
round-971 table built from it (`gm_AllocSpieler` 21, `ServerMainThread` 14, `cm_ExSellObjekt` 7, …) should be
read as "branches whose *encoding* differs", which includes polarity and drift. The classifier's four classes
survive because the carriers with **zero** target-differing branches are genuinely zero
(`vfs_OpenStream`, `ahm_ExAllocAlchemist`, `m_AllocTracked`, `srv_LoadBuf`, `gm_ObjectsAvailble`,
`vfs_ReadCompressed`, `cm_ExProdObjekt`, `gm_CalculateProductionValue`), and the split at zero is what §13 uses.

**The check, before calling a branch target a structural difference:**

```python
# decode both streams from the function entry and compare CONTROL FLOW, not index:
# for each branch, resolve (condition, taken_dest, fallthrough_dest) and compare
# the destinations as *sets of basic blocks*, not as addresses.
```

A pair that differs by a few bytes reaches the same block. A pair where the *mnemonic polarity swapped* is
§50. Only a pair whose destinations resolve to different basic blocks is a placement finding.

## 28. How NOT to compare two control-flow graphs: five rejected formulations (round 1006)

`branch_census.py` counts branches whose encoding differs, which overstates structural difference (§27).
Replacing it needs a real CFG comparison, and getting there took **six attempts**, five of which were wrong in
ways that each looked plausible:

| # | formulation | why it failed | how it was caught |
|---|---|---|---|
| 1 | compare branch targets **by index** | polarity swaps, ±1..3 drift, and pairing artifacts all read as differences | hand-decoded ServerMainThread `0x100098e3` |
| 2 | compare successor **directions** (`fwd`/`back`) | direction FLIPS with polarity, so a polarity swap still differs | same case: reference `je`+back vs our `jne`+forward is one two-way branch |
| 3 | compare block **bodies** | a body differs for non-CFG reasons (register name, one extra insn): `gm_CalculateProductionValue` reported 6 different edges when its flow is identical | its known-good status |
| 4 | group **`jcc`+`jmp`** as one two-way branch | a `jmp` after a `jcc` often belongs to a *different* case; grouping corrupted alignment and regressed `ServerMainThread` from SAME to DIFFERS | re-measurement after the change |
| 5 | **BFS canonical labelling** + edge sets | **not canonical**: visiting a node's two successors in the other order changed 452 of the edge set on the SAME reference graph | explicit order-swap experiment |
| 6 | **order-independent signature** (block-kind multiset + degree profile + edge-kind multiset) | - | holds; see below |

**The generalisable trap is #5, because it is invisible without an explicit test.** A BFS labelling *looks*
canonical: it is deterministic, it is the standard recipe, and it gives identical output for identical input.
It only fails when two graphs differ slightly, and then it over-reports massively: `gm_AllocSpieler` showed
187-214 "differing edges" against a block-kind histogram that matched within 2 nodes.

**The test that catches it** (and that the tool now ships as `--self-test` plus this experiment):

```python
# canonical form must be invariant to iteration order on the SAME graph
a = canon(blocks, edges)
shuffled = dict(random.sample(list(blocks.items()), len(blocks)))
b = canon(shuffled, {k: edges[k] for k in shuffled})
assert a == b        # a BFS labelling FAILS this
```

A canonical form is only canonical if permuting the input does not change it. Check that property directly;
do not infer it from the algorithm's name.

**Also required: prove the tool is not always-zero.** A comparison that returns "SAME" for everything would
look like a clean result. `--self-test` redirects one branch in an in-memory copy of the build and asserts the
canonical form changes.

**The working formulation** (order-independent, no traversal): for each block, its **kind**
(`branch2` for any conditional, `jmp`, `ret`, `falloff`) and its **(in-degree, out-degree)**; then the sorted
multiset of (kind, indeg, outdeg) over blocks, plus the sorted multiset of (kind, kind) across edges. Condition
*polarity* is deliberately not part of the kind: `je` and `jne` to the same two successors are one shape.

**Results, with the two guards in place** (`nodeR`/`nodeB` are block counts):

| carrier | verdict | note |
|---|---|---|
| `ServerMainThread` | **SAME** | matches the hand decode; the tool's index-based predecessor called this 14 different |
| `m_AllocTracked` | **SAME** | kinds identical: `jcc 33, ret 6, jmp 3` both sides |
| `srv_LoadBuf`, `gm_ObjectsAvailble`, `vfs_ReadCompressed`, `cm_ExProdObjekt`, `gm_CalculateProductionValue` | **SAME** | all five known-near-exact carriers |
| `gm_CheckInventoryCapacity` | DIFFERS | hand-verified: reference `jcc 19, ret 5, jmp 1` vs ours `jcc 20, ret 5`: one `jmp` became a `jcc` |
| 11 others | DIFFERS | profile delta 1-2 blocks |

**12 of 19 carriers have a differing control-flow shape; 7 are identical.** That is a much larger structural
component than `branch_census.py`'s "upper bound" implied was *real*, and it is the first trustworthy number
this project has for the `place` class.

## 29. Round 1006's CFG verdict was wrong; the coarse canonical form could not see it (round 1007)

Round 1006 shipped `cfg_compare.py` with an **order-independent but coarse** canonical form (block-kind
multiset + degree profile + edge-kind multiset) and reported **7 carriers SAME**. Round 1007 stress-tested that
form and it is wrong.

**The coarse form is provably too blunt.** An exhaustive search over all CFGs of 3 nodes (2,197 graphs) found
**272,473 non-isomorphic pairs it reports as equal**. Example:

```
G: 3 branch2 nodes; edges 0->{0,0}, 1->{0,0}, 2->{0,1}
H: 3 branch2 nodes; edges 0->{0,0}, 1->{0,0}, 2->{0,0}
```

Same kinds, same degree profile, same edge-kind multiset, genuinely different graphs.

**Two further bugs were found while replacing it, both of which produced a confident wrong verdict:**

| bug | symptom | cause |
|---|---|---|
| comparing `_wl1` colour **IDs** across graphs | the unmutated build read as *non*-isomorphic to the reference for every carrier | `_wl1` interns signatures to dense ids **per call**; ids from two calls are unrelated. Fixed by comparing the id-independent class-size multiset, then deciding by backtracking |
| backtracking over colour classes with only an `a in mapping` test | `ServerMainThread` reported non-isomorphic despite identical WL-1 partitions | within one colour class the recursion re-tried nodes already placed by an outer call and mis-assigned them. Fixed by recursing over a flat (colour, node) slot list |

**The SAME verdicts were also wrong, and for a measurable reason.** `gm_AllocSpieler` and `ServerMainThread`
both read SAME under the coarse form; both are genuinely **DIFFERS**:

```
gm_AllocSpieler   block kinds  ref  jcc 136, jmp 26, ret 8
                               bld  jcc 134, jmp 28, ret 8      <- two jcc became jmp
ServerMainThread  block kinds  ref == bld (131/18/4), aggregate degrees identical
                  but WL-1 partitions match while exact backtracking and a
                  4-round refined colouring BOTH separate the graphs
```

`ServerMainThread` is the instructive one: every aggregate profile matches (kinds, out-degree histogram,
in-degree histogram, entry in-degree), and the graphs are still not isomorphic. **No summary statistic over
blocks is a substitute for a graph comparison.** Round 1005's hand-verification of a single branch
(`0x100098e3`) was correct for that branch and did not generalise to the function.

**What the tool does now.** Exact backtracking isomorphism, seeded by WL-1 colour classes as a pre-filter,
with two shipped guards:

* `--self-test` asserts a graph is isomorphic to **itself** and that a redirected branch is detected. The
  earlier version asserted the unmutated build was isomorphic to the reference, which assumes the answer
  being tested for, and failed for a carrier where the tool's DIFFERS is the finding, not a bug.
* the reflexive check catches the cross-graph colour-ID bug directly.

**Corrected verdicts (exact isomorphism):**

| verdict | carriers |
|---|---|
| **SAME** (6) | `m_AllocTracked`, `srv_LoadBuf`, `gm_ObjectsAvailble`, `vfs_ReadCompressed`, `cm_ExProdObjekt`, `gm_CalculateProductionValue` |
| **DIFFERS** (13) | the rest |

So the honest `place`-class number is **6 identical, 13 differing**, not 7/12, and unlike round 1006's, this
one survives an exhaustive small-graph correctness check plus a reflexive self-test.

## 30. Validating a CFG against the linear decode before trusting its verdicts (round 1008)

Round 1007 replaced `cfg_compare.py`'s canonical form and re-ran the guards, but never checked that the **CFG
construction itself** produces the right graph. A correct isomorphism test over a wrong graph still gives
wrong verdicts, so this round validated the construction three ways before accepting the 13/6 split.

**1. Blocks are non-empty and on real boundaries.** For `gm_AllocSpieler` (3,696-byte span): 170 blocks,
**0 zero-instruction blocks**, and **0 block entries off the linear-decode instruction boundaries**.

**2. Block count reconciles with the branch count.** The linear decode finds 1,063 instructions and 122
branches; the recursive descent finds 170 blocks. An independent count (entry, plus every branch target, plus
every fallthrough after a branch or terminator) gives **171**.

**3. The one-block difference is correct and symmetric.** The extra start is `0x100196b9`, a `nop` in the
trailing padding after the function's final `ret`. `build_cfg` never queues a fallthrough after a `ret`
(both successors are `None`), because code after a `ret` is unreachable. Crucially the **same block is dropped
on both sides**, so it cannot affect a comparison:

```
REF: independent 171, build_cfg 170, missing ['0x100196b9']
BLD: independent 171, build_cfg 170, missing ['0x196b9']
```

**The check, worth running after any change to `build_cfg`:**

```python
# block starts from a linear decode must match the recursive-descent blocks,
# up to unreachable code after a terminator
starts = {entry} | {branch targets} | {fallthroughs after branch/terminator}
assert set(build_cfg(...)) <= starts          # no invented blocks
assert starts - set(build_cfg(...)) == set()  # or explain each missing one
```

An invented block would add edges and could flip a SAME to DIFFERS; a dropped *reachable* block would do the
opposite. Both are silent without this check.

**Also confirmed:** `--self-test` passes both guards (reflexive isomorphism, redirected-branch detection) and
the 13-differ / 6-same split is reproducible run to run.

## 31. Exact isomorphism over ADDRESSES answers the wrong question: establish correspondence first (round 1012)

`cfg_compare.py` compared two CFGs by exact isomorphism over block **addresses**. That is not the question the
tool exists to answer. Two builds whose blocks sit at different addresses (because intervening code differs in
length) produce a non-isomorphic verdict for a purely encoding-level reason.

**Measured on `ServerMainThread`.** Under an exact address-based isomorphism the graphs are not isomorphic, and
round 1011 read that as a "merge-point" difference from the neighbourhood profiles. Comparing instead under a
**block correspondence by instruction ordinal** (the k-th instruction of the reference corresponds to the k-th of
ours):

```
successor pairs compared: 280
mismatches:                  2
```

**278 of 280 edges match.** The two that differ are the pair already hand-verified in round 1005:

```
reference  0x100098e3  je  0x100097c5   then  0x100098e9  jmp 0x10009919
ours       0x100098e5  jne 0x1000991a   then  0x100098e7  jmp 0x100097c5
```

Same two destinations, swapped polarity. So `ServerMainThread` is **polarity-only on 2 of 280 edges**: exactly
round 1005's conclusion, and rounds 1010/1011's "arity"/"merge" readings were both artifacts of comparing
addresses.

**The rule.** An isomorphism test must run on a **correspondence**, not on raw identities. Before comparing any
two compiled artifacts: establish which node corresponds to which (by ordinal, by canonical role, by matched
canonical form), *then* compare the induced edges. Comparing addresses compares layout, not structure.

**The tool now reports a graded verdict** (`mismatches / edges-checked` under ordinal correspondence) which is
far more informative than SAME/DIFFERS:

| carrier | differing edges by ordinal |
|---|---|
| `ServerMainThread` | **2 / 280 (0.7%)** |
| `ahm_ExAllocAlchemist` | 6 / 30 |
| `vfs_OpenStream` | 7 / 27 |
| `gm_CheckInventoryCapacity` | 9 / 10 |
| `gm_AllocSpieler` | 75 / 132 |
| (6 carriers) | **0: control flow identical** |

`ServerMainThread` is now visibly a near-miss, not a structural outlier, which is the opposite of what the
address-based verdict said.

**Three rounds, one root cause.** Rounds 1009, 1010 and 1011 each reached a different mechanism for the same
bytes (polarity → arity → merge) because each reasoned from a summary the previous round had computed wrongly.
The fix was not another inference: it was changing the *comparison primitive* so the correspondence is
established before anything is measured.

## 32. An ordinal correspondence is only valid when the two streams have equal length (round 1013)

Round 1012 replaced address-based isomorphism with a **block correspondence by instruction ordinal** and
reported `ServerMainThread` as a 2-of-280 near-miss. That specific result is correct and now independently
re-confirmed, but the method has a validity condition round 1012 did not state.

**A single global shift absorbs a constant offset; it cannot absorb progressive drift.** Ordinal pairing assumes
the k-th instruction of one function corresponds to the k-th of the other. When the two streams differ in length
they slip relative to each other, and the mismatch count measures the slip rather than the control flow.

**Measured: only 8 of 19 carriers have equal instruction counts.**

```
gm_AllocSpieler                1063 vs 1061   -2
CrashDumpUnhandledExceptionFilter 725 vs  729   +4
cm_ExSellObjekt                 667 vs  667    0   <- valid
ls_LoadBuildingEntityState      499 vs  497   -2
cm_ExCopyEntityData             260 vs  255   -5
gv_ExAllocGraveyardWorker       333 vs  332   -1
ServerMainThread                627 vs  627    0   <- valid
gm_AllocGebaeude                356 vs  359   +3
vfs_OpenStream                  210 vs  210    0   <- valid
gm_FindNextFilteredEntity       124 vs  120   -4
ahm_ExAllocAlchemist            286 vs  287   +1
gm_CheckInventoryCapacity       138 vs  137   -1
m_AllocTracked, srv_LoadBuf, gm_ObjectsAvailble, vfs_ReadCompressed,
cm_ExProdObjekt, gm_CalculateProductionValue      0   <- valid
cm_ProcessCommandQueue          206 vs  204   -2
```

`cfg_compare.py` now prints **`DRIFT-unreliable`** on any carrier whose counts differ. Three DIFFERS carriers are
drift-free and therefore trustworthy: `cm_ExSellObjekt` (85/99 edges), `ServerMainThread` (**2/280**),
`vfs_OpenStream` (7/27).

**A second trap in the shift search.** Selecting the shift by *fewest mismatches* alone overfits: it favours
alignments with a tiny denominator. Measured on `gm_CheckInventoryCapacity`, shift −2 scored **2/4** while
shift +1 covered **34 edges at 33 mismatches**. A 4-edge sample that happens to agree is not better evidence
than a 34-edge one that does not. The tool now selects on **coverage first, then mismatches**.

**The check, for any correspondence-based comparison:** state and test the validity condition. For ordinal
pairing it is `len(ref_instructions) == len(built_instructions)`; when it fails, report the figure as
indicative, not decisive.

## 33. A raw-link `.data` diff attributed to a GAME TU is still displacement, not wrong content (round 1015)

Round 980 attributed the raw-link `.data` divergence by owning object and found 28.9% of it in
`data_restore_split.obj` (the length-only filler). Round 1015 re-measured with the current tooling and found a
**game TU** contributing 643 bytes (`cm_ExSellObjekt.c.obj`) which looks like real missing content:

```
0x10029d9c  ref: 0500000005000000c409000000000000  <- integers 5, 5, 2500
            bld: 636d5f457853656c6c4f626a656b7428  <- "cm_ExSellObjekt("
```

and at `0x10029d00` the reference holds a **structured record table**
(`0.0, 5.0, 14, 4, 5, 2500, 0.0, 5.0, 15, 4, 6, 3000, …`) where the build holds a run of error **strings**
(`"gm_AllocSpieler() failed"`, `"cm_ExChangePlayerIdentity() failed"`, …). Different content, not a shift.

**It is still displacement.** Comparing the **shipped** file at the same address:

```
ref: 000000000000a0400e0000000400000005000000c4090000000000000000a0400f000000...
bld: 000000000000a0400e0000000400000005000000c4090000000000000000a0400f000000...
identical: True
```

and over the whole section, **shipped `.data` differs by 0 of 57,344 bytes.** The `.data` fixer copies the
section from the layout package, so raw-link divergence says nothing about whether content is missing.

**The rule.** Attributing a raw-link `.data` difference to a game object does **not** make it a content defect.
The check that separates the two is one command: compare the **shipped** file at the same address:

```bash
cmp <(dd if=build/server.dll bs=1 skip=$((0x27000+OFF)) count=N) \
    <(dd if=original/Server/server.dll bs=1 skip=$((0x27000+OFF)) count=N)
```

If identical, the divergence is placement. Only a difference in the *shipped* file is a content finding, and
`scripts/verify_objective.py` already reports that as a single number (currently 0 non-`.text` bytes).

**This is the third time this section has been re-derived** (rounds 977, 980, 1015), each from a slightly
different angle. The stable answer: shipped `.data` is exact; raw-link `.data` is a placement metric that the
gate correctly enforces as a *ceiling*, not a target.

## 34. Both decoders reaching the span end proves there is no hidden slack (round 1017)

Round 990 computed "119 bytes of padding" for `gm_AllocSpieler` from `span - sum(instruction sizes)` and
concluded the object had room. That arithmetic is unsound: a linear disassembly that stops early produces
exactly that kind of phantom gap.

**The sound test is whether both decoders reach the span end exactly.**

```
reference  1063 instructions, sizes summing to 3696   (span 3696)
built      1061 instructions, sizes summing to 3696   (span 3696)
```

Both consume the span with **zero remainder**, so there is no padding and no slack. Our stream has **two fewer
instructions** than the reference, offset by larger encodings: that difference, not a size deficit, is what the
2,823-byte residue consists of.

**Both tails are byte-identical**, which is the check that makes the count meaningful:

```
reference  0x100196b8  ret   then 7x nop   -> 0x100196c0
built      0x100196b8  ret   then 7x nop   -> 0x100196c0
```

**CORRECTION (round 1018): the COMDAT raw is the SPAN, not our code length, and there IS headroom.**

Round 1017 concluded "slack 0" by comparing the COMDAT *raw* against the span. That comparison is
self-fulfilling: msvc6 pads the COMDAT to the span with trailing `nop`s, so `raw == span` by construction and
says nothing about how much code we emit.

The number that matters is **our code up to and including the final `ret`**, and it is smaller:

| carrier | reference code | our code | span | real headroom |
|---|---|---|---|---|
| `cm_ExProdObjekt` | 1008 | **993** (its recorded `size`) | 1008 | **15** |
| `ServerMainThread` | 2434 | 2434 | 2448 | 14 |
| `ls_LoadBuildingEntityState` | 1463 | 1460 | 1472 | 12 |
| `CrashDump` | 2115 | 2120 | 2128 | 8 |
| `cm_ExSellObjekt` | 2057 | 2056 | 2064 | 8 |
| `gm_AllocSpieler` | 3689 | 3689 | 3696 | 7 |
| `srv_LoadBuf` | 750 | 750 | 752 | 2 |

Every carrier is padded with 2-15 trailing `nop`s. So **`cm_ExProdObjekt`'s header claim of "15 bytes of unused
slack" was correct**, and round 1016's dismissal of it as stale was wrong: the same mistake in the opposite
direction from round 990, which over-counted slack from a truncated decode.

Three answers from three methods, only the third sound:

| method | answer | verdict |
|---|---|---|
| `span - sum(sizes)` after an early-stopped decode (round 990) | 119 bytes | wrong, over-counts |
| COMDAT raw vs span (rounds 1001, 1017) | 0 | **self-fulfilling**, measures the pad |
| last non-`nop` instruction's end vs span (round 1018) | 2-15 bytes | **correct** |

**The rule.** A size budget must come from an artefact, never from arithmetic over a disassembly, but the
artefact must be the *code extent*, not the container's padded size. The container's raw size is what msvc6
pads **to**; `raw == span` is therefore a tautology and cannot be evidence about our code. The code's extent is
the end of the last non-`nop` instruction.

| claim | method | valid? |
|---|---|---|
| "119 bytes of slack" (round 990) | `span - sum(sizes)`, decoder stopped early | **no** |
| "slack 0" (rounds 1001, 1017) | COMDAT raw == span | **no**: tautological, measures the pad |
| "sum of sizes == span on both sides" (round 1017) | decode arithmetic | **no**: same tautology, and §24 shows the sum moves with the decoder's stop rule |
| "last non-`nop` end vs span" (round 1018) | object bytes | **yes** |

**Note on the earlier text above.** The round-1017 section still says the zero-remainder decode "proves there
is no padding and no slack". It proves the *decode* consumed the span; it does not bound our code, because the
trailing `nop`s are the pad. Both statements in that section that conclude "no slack" are superseded by the
table above.

This is the fifth time this session that a figure derived from disassembly arithmetic rather than from the
container has been wrong (§§21, 23, 24, 26), and the second time (§§26, 34) that the *container* figure was
wrong in the opposite direction because it measures a quantity msvc6 defines rather than one we control.

## 35. The shipped `.text` reads byte-perfect wherever postlink rewrote the operands (round 1022)

`postlink_residual.py` already warns that the non-`.text` zeros are **self-certifying**: the postlink
fixers blit reference bytes over `.data`/`.rdata`/`.reloc`, so "differing 0x0" there says nothing about
whether the build can produce those bytes. **The same trap exists inside `.text`, it is just smaller and
better hidden.**

`cm(MakeLists.txt:442-460)` documents the mechanism: `rebrew build postlink --layout` "rewrites the remaining
`.text` data operands / E8-E9 targets" from the layout package. So every `.text` byte that is an absolute
operand or a call target is restored to the reference's value regardless of what our objects emitted.

**Measured, same byte range, three artifacts:**

| artifact | what it is | `.text` differing |
|---|---|---|
| `.scratch/server.dll.prelayout` | plain CMake link | **50,285** |
| `build/split_poc.dll` | split-set composition (LIBCMT placed as stock objects at reference offsets) | **14,347** |
| `build/server.dll` | after `postlink_residual.py --write` | **8,628** |

The gate's `RESIDUE_BASELINE` is the third number, and that is **correct**: the objective's shipped
artefact is the postlinked one. The trap is using it to answer a different question.

**The concrete failure (round 1021).** Twelve `command_c` discovery symbols are blocks of contiguous
functions (see general-knowledge). Measuring those spans on `build/server.dll` gave **0 differing bytes**,
which I read as "our build emits these bytes correctly". It does not. Postlink had rewritten them. The raw
link differs in **694** of those bytes.

**The rule.** Any per-region `.text` claim of the form "our build emits this correctly" must be measured on
`build/split_poc.dll` or `.scratch/server.dll.prelayout`, never on `build/server.dll`. The shipped file is
the *deliverable* ruler; the split composition is the *capability* ruler. They answer different questions
and differ by 5,719 bytes.

This is the third distinct self-certification in this project, after `.data` (round 199) and the
`--built`-points-at-a-postlinked-image guard (round 450).

Verify with:

```
.venv/bin/python scripts/postlink_residual.py --write build/server.dll
# the "raw link vs reference" block is the capability number; the
# ".text differing" line at the top is the deliverable number
```

## 36. A carrier's VA is not guessable from its neighbours: resolve it from the annotation (round 1025)

Round 1025 set out to re-verify `codegen-walls.md` §13's recorded first-divergence offsets against the
current build, since the log is many rounds old and the code has moved. The first attempt reported
**13 of 13 mismatched**: every carrier wrong. All 13 mismatches were the check's own fault.

**Two independent errors, either of which alone produces a full table of false alarms:**

1. **The VAs were assumed, not resolved.** I took each carrier's start from memory and by rounding
   (`0x10011c00` for `gv_ExAllocGraveyardWorker`, `0x1000d8a0` for `cm_ExSellObjekt`, `0x10019e80` for
   `gm_CheckInventoryCapacity`). The real values are `0x10011bf0`, `0x1000d930`, `0x10019e60`: off by
   `0x10` to `0x100`. Every derived offset was then wrong by exactly that amount, and offsets are
   *relative*, so the error is invisible in the output: it looks like a stale table, not a bad baseline.
2. **The wrong artifact.** Two carriers (`m_AllocTracked`, `cm_ExCopyEntityData`) showed *no differing byte
   at all* in the image I measured, which is impossible for a carrier with non-zero residue. That should
   have been the tell; it is measure-traps §35's deliverable-vs-capability confusion arriving before §35
   was written.

**The correct method**: let the artefacts supply both endpoints:

```bash
# fault address, attributed per carrier, from the tool that computes the residue
.venv/bin/python scripts/postlink_residual.py --write build/server.dll | tail -22
# function start, from the annotation that lint already validates
grep -m1 'FUNCTION: SERVER' src/Develop/<path>/<carrier>.c
# offset = fault - start
```

With both resolved properly, **all 11 recorded §13 offsets reproduce exactly**: `0xaa`, `0x2`, `0x2c`,
`0x3c`, `0x30`, `0x107`, `0x3c7`, `0x60`, `0x36`, `0xcc`, `0x11`. Zero mismatches. The table is accurate
and current.

**The rule.** A fault address is a *VA*; an offset is a *difference*; a wrong start corrupts the second
while leaving the first plausible. Never carry a carrier VA in your head across rounds: resolve it from
the source annotation, which `rebrew lint` already keeps honest, and take the fault address from the tool
rather than from a `grep` of the docs (which are keyed by the fault, not the start, workflow-traps §8's
two-store problem).

This is also why the round's negative result was worth obtaining: the log's offsets being independently
reproducible is what earns the trust the next round will place in the class map built on top of them.

## 37. The graded residue and the raw-link residue form a clean partition: 8628 + 5081, zero overlap (round 1026)

Measure-traps §35 established that the shipped `.text` and the raw link answer different questions
(8,628 vs 14,347 differing). Round 1026 decomposed the two byte-for-byte over `.text`'s 0x22846 bytes,
comparing each offset across three artifacts:

| class | count | meaning |
|---|---|---|
| raw differs, shipped matches | **5,081** | **postlink supplied the reference byte** |
| raw differs, shipped differs | **8,628** | **the graded residue** |
| raw matches, shipped differs | **0** | postlink introduces nothing |

Two facts worth having:

- **The partition is exact and exhaustive.** `8628 + 5081 = 13,709`, which is the raw link's total
  divergence, and the shipped-only class is **empty**. So postlink is a pure repair step: it never
  corrupts a byte the build got right, and the graded residue is precisely the subset of the production
  gap it could not repair.
- **The 8,628 is a subset of the 13,709.** Every byte in the graded residue is also wrong in the raw
  link, which is why the two rulers agree on *which* carriers are failing even though they disagree on
  magnitude. A round may therefore use the raw link to study a carrier's divergence and the shipped file
  to score it, and the two will not contradict each other.

**Worked example: the 5,081 class, at `0x10015f80` (inside `gm_ObjectsAvailble`).** `gm_FindNextFilteredEntity` (annotation VA
`0x10016f80`; the real entry is `0x10015f80`, see below) opens:

```
REF      a1 c0 d8 14 10   mov eax, [0x1014d8c0]
SHIPPED  a1 c0 d8 14 10   mov eax, [0x1014d8c0]
RAW      a1 e8 6a 76 11   mov eax, [0x11766ae8]
```

`0x1014d8c0` is `g_entity_ptr` per `rebrew-data.toml` and `rebrew_globals.h:63`. Our raw link binds it to
the local stub `link_stubs.c:198` (`unsigned char* g_entity_ptr = 0;`), which the linker places at
`0x11766ae8`: inside `.data`'s BSS tail but 21 MB from the reference's address. Postlink's layout package
rewrites the operand back to the reference value, so the **shipped file is already correct here** and this
byte is not residue.

**The trap this exposes.** A round studying that offset on the raw link would see a wrong global operand and
reasonably chase it as a live bug: the address is plausible, the symbol is real, and the raw link is the
"capability" ruler §35 recommends. It is postlink-supplied and unfixable by editing the definition.
**Check the shipped image before treating any raw-link operand difference as work.**

**A note on `0x10016f80`.** `gm_FindNextFilteredEntity`'s annotation VA is `0x10016f80` and the
inventory agrees (`fcn.10016f80`, 352 bytes). The bytes at its entry are `c4 08 5e c3` followed by ten `90`s,
**identical in both images** (a shared epilogue tail left by the preceding function's layout) and the
function's own prologue begins at `0x10016f8a`. `fault_address.py` walks the streams from `0x10016f80` and
reports the first disagreement at `0x10016f86`; that is correct, and a first attempt to call this row
"the wrong span" was wrong. Decode the streams, do not read the bytes at the entry.

## 38. The residue's displacement profile is measurable, and most carriers ARE a single cliff (round 1031)

`msvc6-c-shapes.md` §109 closes `gm_AllocSpieler` (the largest carrier, 2,823 of 8,628 residue bytes)
with a framing that bounds expectations:

> the 2,824-byte residue behind it is that one scheduling decision's **displacement wake** rather
> than 2,824 bytes of wrong code

That claim changes what a future round should attempt: if the residue is one decision's displaced wake,
the lever is that decision; if it is many independent local shifts, no single lever reaches it. It is
therefore worth measuring rather than inheriting.

**Method.** For each sampled offset in the built image, search the reference within ±0x800 for the same
24-byte context. The distance at which it is found is the local displacement. A single cliff yields one or
two distinct values in one or two runs; many independent shifts yield many of both.

**Result: the profile differs sharply by carrier, and most are a single cliff:**

| carrier | sampled | matched | distinct values | runs |
|---|---|---|---|---|
| `gm_AllocSpieler` | 916 | 710 | **4** | **7** |
| `cm_ExSellObjekt` | 510 | 248 | 5 | 8 |
| `ServerMainThread` | 606 | 406 | 2 | 5 |
| `cm_ExCopyEntityData` | 109 | 96 | 2 | 3 |
| **`CrashDump`** | 526 | 501 | **1** | **1** |
| **`ls_LoadBuildingEntityState`** | 362 | 330 | **1** | **1** |
| **`gm_AllocGebaeude`** | 263 | 223 | **1** | **1** |
| **`vfs_OpenStream`** | 170 | 102 | **1** | **1** |
| **`gm_FindNextFilteredEntity`** | 82 | 75 | **1** | **1** |
| `gv_ExAllocGraveyardWorker` | 114 | 4 | 1 | 1 (only 4 matched, unresolved) |

**Six carriers show exactly one displacement value across the whole function.** For those, the residue
really is one local difference plus its wake: §109's framing is correct *for them*, and the single cliff
is the thing to attack. `gm_AllocSpieler` is **not** one of them (4 values, 7 runs), so §109's own carrier
is where the framing is weakest.

**A global-shift test fails outright on `gm_AllocSpieler`:** our bytes after the first divergence match the
reference at a constant offset in at best **310 of 3,519** cases (delta +5): chance level. So there is no
rigid displacement to find there either.

**A correction to this section's first draft.** It reported `gm_AllocSpieler` as 12 runs / 10 distinct
values. That came from slicing the image with the wrong origin. The numbers above use `ref[va - imagebase]`,
verified against a known function's bytes. **The first draft's headline reversed the conclusion**: it
claimed the wake framing does not reproduce, when in fact it reproduces for six carriers and fails only on
the largest. Recorded because the corrected version is more useful: the profile table is now a *triage
tool*: a carrier with one run is a §109-style single decision, a carrier with many runs is not.

**READ §39 BEFORE USING THIS TABLE.** The profile is only interpretable alongside its match rate: a
carrier whose code is genuinely different rather than shifted produces few matched samples, and a low
sample count can show as "one run" for the wrong reason. `gm_FindNextFilteredEntity`, listed here as a
single-run carrier, is 12.8% context-matched and has no profile to read.

**The rule.** "It is all downstream of fault X" is an attribution claim and needs the measurement any
other claim does. Sample the interior: one or two displacement values means a genuine single-cause wake;
many values means the fault explains the first run and nothing after it. And check your image origin
before believing a surprising table: the wrong slice produced a confident, wrong headline in this very
section.

## 39. "One displacement run" does not mean "one shifted byte": check context presence too (round 1032)

Measure-traps §38 introduced a displacement profile as a triage tool: sample our image, find the same
24-byte context in the reference nearby, and count the distinct distances. One value in one run was read as
"a single cliff, therefore a single local difference to attack".

**That reading is wrong for at least one carrier, and the reason is that a displacement match is only
possible where our bytes exist in the reference at all.** A carrier whose code is genuinely *different*
(not shifted) has few searchable contexts, and a small number of samples can easily land in one run purely
because so little matched.

**Second measurement: how much of our stream appears anywhere in the reference `.text`.** Sample every 4th
offset, take an 8-byte context, and search the whole reference:

| carrier | 8-byte contexts found in the reference | reading |
|---|---|---|
| `vfs_OpenStream` | **102/134 (76.1%)** | mostly displaced: §38's reading is right |
| `gm_AllocGebaeude` | 176/270 (65.2%) | mostly displaced |
| `ls_LoadBuildingEntityState` | 218/366 (59.6%) | mostly displaced |
| `gm_AllocSpieler` | 313/918 (34.1%) | mixed |
| `CrashDump` | 139/530 (26.2%) | mostly different code |
| **`gm_FindNextFilteredEntity`** | **11/86 (12.8%)** | **mostly different code** |

`gm_FindNextFilteredEntity` reported a single displacement run in §38 only because **only 4 of its 82
samples matched anything at all**: a sample count far too small to distinguish "one run" from "almost
nothing to measure". At 8-byte context it is 11/86, and a 24-byte context finds **nothing** in the entire
reference. Its 245 differing bytes are substantially new code, and the entry-order probe it motivated
(`codegen-walls` §21) returned +6 with the reorder genuinely applied.

**The rule.** A displacement profile is only interpretable alongside its **match rate**. Report both:

- **Match rate**: does our code exist in the reference at all? Low means the carrier needs *code* work, and
  no displacement profile describes it.
- **Distinct displacements and runs**, among the samples that *did* match: only this measures how many
  independent local shifts there are.

A carrier with a high match rate and one run is §38's clean case (`vfs_OpenStream`: 76.1%, one run, one
byte). A carrier with a low match rate has no profile to read, and a "1 run / 1 value" result on it is an
artefact of the sample being nearly empty. **Six of eight §38 rows were recomputed here; the two that were
not were `cm_ExSellObjekt` and `ServerMainThread`, both of which had 2-5 runs and are unaffected by this
correction.**

This is the same failure mode as measure-traps §24 ("instruction counts across two images are not
comparable: the decoder's stop rule decides the answer") arriving in a matching metric rather than a
counting one: **the denominator was doing the work, and it was not reported.**

## 40. A carrier has TWO first divergences: the raw link's and the shipped file's (round 1033)

Measure-traps §35 established that the raw link and the shipped file answer different questions, and §37
that the graded residue is a proper subset of the raw link's divergence. Neither says what happens to the
**first-divergence address**, which is the address every carrier's documentation is keyed by. It turns out
that address is ruler-dependent, and for most carriers the two do not agree.

**Measured, per carrier:** walk both the raw link and the shipped file against the reference from the
carrier's entry and record the first differing offset on each.

| carrier | raw first diff | shipped first diff | bytes postlink corrected between them |
|---|---|---|---|
| `gm_AllocSpieler` | `+0x6d` | `+0xaa` | 8 |
| `cm_ExSellObjekt` | `+0x7` | `+0x2c` | 3 |
| `gv_ExAllocGraveyardWorker` | `+0x6a` | `+0x107` | 10 |
| `ServerMainThread` | `+0x80` | `+0x3c7` | 4 |
| `gm_AllocGebaeude` | `+0xa` | `+0x60` | 8 |
| `gm_FindNextFilteredEntity` | `+0x1` | `+0x6` | 4 |
| `ahm_ExAllocAlchemist` | `+0x38` | `+0xcc` | 20 |
| `gm_CheckInventoryCapacity` | `+0x76` | `+0x83` | 3 |
| `m_AllocTracked` | `+0xa` | `+0x11` | 2 |
| `gm_ObjectsAvailble` | `+0x53` | `+0x10d` | 21 |
| `cm_ExProdObjekt` | `+0x4` | `+0xcd` | 21 |
| `gm_CalculateProductionValue` | `+0x6` | `+0xe4` | 23 |
| `CrashDump`, `ls_LoadBuildingEntityState`, `cm_ExCopyEntityData`, `vfs_OpenStream`, `srv_LoadBuf`, `vfs_ReadCompressed`, `cm_ProcessCommandQueue` | - | - | **agree** |

**Eleven of nineteen carriers disagree**, and in every case the raw link's divergence is *earlier* and is
a 2-23 byte window of data operands postlink restores.

**Worked example, `gm_AllocSpieler`.** At `+0x6d` the raw link has `e4 65 76 11` (`0x117665e4`, our
stub placement) where the reference has `34 54 03 10` (`0x10035434`). The shipped file has the reference's
`34 54 03 10`, and the two streams are byte-identical through `+0x90` across that whole window. So the
raw link reports a divergence at `+0x6d` that **the carrier does not have in the deliverable**.

**The rule.** `fault_address.py` measures the shipped file (correct, it is the deliverable), and every
carrier's header is keyed by the shipped file's fault. A round that studies a carrier on the raw link (
which §35 recommends, and which is the only way to see what the *build* produces) will land on a
**different, earlier, postlink-supplied address** and read it as the carrier's problem. Check which ruler
produced any fault address before looking it up.

**Concretely:** use the raw link for "does our build produce these bytes" (capability) and the shipped file
for "which byte is the carrier failing on" (deliverable). Do not carry a raw-link fault address into a doc
lookup; `whathas.py` is indexed by the shipped-file address.

This is measure-traps §35 and §36 in their address-level form: §35 said the two rulers differ in
*magnitude*, §36 said a carrier's VA must not be assumed, and this says they differ in *the address itself*
for 11 of 19 carriers.

## 41. A call-target multiset comparison inherits every desync, and a shifted stream invents wrong callees (round 1035)

Comparing the multiset of `call` targets between the reference and a built image looks like a cheap
"is any callee missing or wrong" check. **It is not:** after any size difference the streams desync, and
every instruction after the fault is decoded from the wrong offset, so the comparison reports phantom
missing calls and phantom wrong callees. Two measured examples, one for each direction.

**Direction 1: phantom *missing* calls (`gm_AllocSpieler`).** The multiset says the shipped file is missing
three calls (`0x1001a299`, `0x10003640`, `0x100122e0`) that the raw link has:

```
ref      1056 instructions, 55 calls
raw link 1054 instructions, 55 calls
shipped  1014 instructions, 52 calls
```

The raw link has 55 calls and the shipped file 52, but **the shipped stream decodes to 42 fewer
instructions**, so it is desynced and its multiset is not comparable. There is no missing call. This is
measure-traps §24 ("instruction counts across two images are not comparable") applied to call targets.

**Direction 2: phantom *wrong* callee (`vfs_OpenStream`).** Its multiset shows the reference calling
`0x1001b0c0` (`crt_toupper`, real code) where we call `0x1002387d` (`.rdata`, zeros), which reads as a
wrong symbol and would send a round hunting the C. It is the +1 displacement from §38's single-byte cliff:

```
ref  +0x5f  call 0x1001b0c0      (e8 5c 20 .. at +0x3f)
ship +0x5f  push eax             (50 at +0x3f)
ship +0x60  call 0x1002387d      (e8 18 .. at +0x40)
```

Our `call` is the reference's `call` **one byte later**, at the offset the shift puts it. The decoded target
is garbage because the decoder started the instruction one byte off. Nothing is wrong with the callee; the
earlier fault (`cmp byte [eax],0` vs `mov al,[eax]`, one byte shorter) is the whole difference.

**The rule.** Any comparison built on *decoded instructions* is only valid after establishing that the two
streams are aligned at the region being compared. For a per-carrier callee audit, compare **call counts
within a region known to be aligned**, or establish alignment first by the local-context method of §38;
never compare a whole-function multiset across a known divergence. Both directions of error here are the
§13/§24 family: the comparison silently measures the desync, not the code.

## 42. "Compare the data operands" gives 0, 707 or 9,855 depending on the offset filter (round 1036)

Round 1030 asked whether postlink's `.text` operand rewrite is complete and answered **0 mismatched of
4,398**. Round 1036 re-asked the same question a looser way and got **707** (or **9,855**), which looked like
a contradiction. It is not: the three numbers come from three different populations, and only one of them
is a set of operands.

**Method.** For every byte offset `i` in `.text`, read the little-endian dword at `i` in the reference and in
the shipped file, classify each as a data-range address (`0x10024000..0x11768000`), and count:

| population | rule | size | mismatched |
|---|---|---|---|
| **A: the operand set** | dword is a data address in **both** images | 4,398 | **0** |
| B: either image | dword is a data address in the reference **or** the shipped file | 5,105 | 707 |
| C: no filter | every offset where the two dwords differ | - | 9,855 |

**Population A is the only one that is a set of operands, and it is the one round 1030 used.** At a
genuinely operand-aligned offset the two images hold the same immediate, so both classify it as a data
address and it enters A. **Zero mismatches**: postlink's rewrite is complete, confirmed a second time.

**Populations B and C are dominated by dwords that straddle instruction boundaries.** A dword read at an
arbitrary offset is usually two halves of adjacent instructions; if the surrounding bytes differ (which they
do across the whole residue), the straddling dword differs too, while classifying as a data address only by
coincidence. Those entries are not operands and their "mismatch" is the residue showing through at a
misaligned window.

**The rule.** A byte-offset sweep is not an instruction sweep. Before counting anything from raw offsets,
say which offsets can be operands: either decode the instructions and test the operand fields, or use the
both-images classification as a cheap proxy, which works precisely *because* a real operand agrees in both
images. **When a looser re-measurement contradicts an earlier tight one, check whether the two are counting
the same population before believing either.**

This is measure-traps §21 ("disassembling `.text` from its start gives wrong instruction boundaries: every
statistic built on it is junk") applied to operand extraction rather than disassembly, and it is the second
time this session that a fixed instrument has been re-derived at a different threshold (§26's per-function
span reader is the first).

**Also verified this round:** postlink's `locality` pass reports **4 stale operands recovered** on every
run, deterministically: `.text+0xae64`, `+0xae85`, `+0x11378`, `+0x12209`, all 4-byte data addresses
inside `cmp reg,imm32`. Every one lands correctly in the shipped file (`0x1009aca0`, `0x1009aca2`,
`0x10139820`, `0x1009b762`). Note `0x1009aca2` is **odd-aligned**: a byte-level comparison against a
struct's second byte, which is why the generic 4-aligned sweep needs a second, locality-driven pass to
catch it. The pass is working as designed; the four are not defects.

## 43. A header records *history*, so a claim-extraction regex finds rejected variants, not current state (round 1042)

Round 1041 found one genuinely stale frame note by hand (`vfs_OpenStream`: "ours is 8" when ours is `0xc`).
Round 1042 tried to automate that audit: extract every `sub esp,0xNN` from each carrier's header and compare
it against the frame the binary actually emits. **The automation produced two false positives out of two
hits, and both were the same mistake.**

| file | regex found | binary | verdict |
|---|---|---|---|
| `cm_ExCopyEntityData.c:73` | `sub esp,0x10` | `0xc` | **not stale**: the line reads "one frame dword (`sub esp,0x10` -> `0xc`)", i.e. it *documents the change* |
| `cm_ExProdObjek.c:221` | `sub esp,0x14` | `0x10` | **not stale**: the line reads "the object at 993 but widens the frame to `sub esp,0x14` and moves every esp displacement, scoring 815", a *rejected probe* |

A carrier's header is a **probe history**: it records spells that were tried, values that were fixed, and
variants that lost. Quoting a number from it does not assert that number is current: often the opposite,
because the entry exists precisely to say it was wrong or rejected.

**The rule.** A header's numbers are **evidence about the past**, and an audit that extracts them must also
extract the surrounding verb: "is/was", "gives/scored", "->" (a change), "rejected/lost" (a retired probe).
Round 1041 succeeded by **reading the sentence**, not by matching the token. Any regex over these headers
needs to carry the polarity or it will report every documented change and every rejected probe as a stale
claim.

**Companion to workflow-traps §16 and §14.** Those say a header's headroom and delta figures are historical
measurements. This says the *reason* a number appears in a header is usually that it is historical, so the
default expectation for any extracted figure should be "not current" until the sentence says otherwise,
rather than "current until proven stale".

**Consequence:** the automated audit is withdrawn. One real stale note was found this session
(`vfs_OpenStream`, round 1041) and it was found by reading; the regex found none and invented two.

## 44. Byte-level displacement tests and instruction-level ones answer different questions (round 1047)

Measure-traps §38 introduced a byte-level "local-context displacement profile" as a triage tool, and §39
added the match rate as its denominator. Both remain useful, but round 1047 found their **limit**, by
comparing the two granularities on the same clusters of `gm_AllocSpieler`.

**Byte-level result:** the two largest clusters peak at 17.0% and 13.9% match under their best rigid offset
(chance level), which reads as "not displaced code, genuinely different code".

**Instruction-level result on the same clusters**, comparing mnemonic + operand with every `0x...` normalised
to `A`:

| cluster | bytes | ref insns | our insns | equal modulo address |
|---|---|---|---|---|
| `+0x1a4..+0x5f6` | 1,107 | 323 | 322 | **251/322 = 78.0%** |
| `+0xa0d..+0xd72` | 870 | 248 | 247 | **177/247 = 71.7%** |
| `+0x6cf..+0x8db` | 525 | 157 | 157 | 79/157 = 50.3% |

**The two large clusters are displaced code.** The byte test said otherwise because **every differing branch
displacement breaks byte-window matching**: a 16- or 24-byte window spanning a `jne rel32` cannot match at
any offset once the target differs, even though the surrounding instruction stream is aligned. Branch
displacements are dense in loop-heavy code, so the byte-level match rate collapses to chance on exactly the
regions that are most aligned.

**The rule.** Two questions, two tools:

- **"Is this region our code shifted?"** → compare **instruction streams with address normalisation**. This
  is the only version that survives differing embedded displacements, and it is what tells you whether a
  region is displacement or new code.
- **"How much of our byte stream exists in the reference?"** → the byte-level context search of §38. Keep it
  for that literal question and **do not** read its match rate as "N% of this function is different code":
  §39's correction said the rate needed reporting; this says what it must not be used to conclude.

**A second, arithmetic trap found in the same measurement.** One 192-byte cluster reported **1 reference
instruction against our 52**, which looks like a 51-instruction surplus and a strong probe candidate. It is a
**decoder desync**: the reference's first two bytes there are `24 83` (`and al,0x83`), after which capstone
stops emitting valid instructions and returns a single item. The raw bytes are ordinary code. **A cluster
whose instruction count is near zero is a desync, not a surplus**: check that the first few bytes decode
plausibly before reading any count from a narrow window.

Both traps share a shape with §24 ("instruction counts across two images are not comparable: the decoder's
stop rule decides the answer") and §42 ("check whether a looser measurement counts the same population").

## 45. `difflib.SequenceMatcher` reports 100% equal on streams that differ at instruction 21 (round 1048)

Round 1047 introduced instruction-level alignment (mnemonic + operand with `0x...` normalised) as the sound
instrument for "is this region displaced", replacing the byte-level test of §38/§44. It used
`difflib.SequenceMatcher` to count matching instructions. **That library call is not an alignment and its
"equal" count is not a measurement.**

**Measured, on `cm_ProcessCommandQueue` (`0x1000aac0`):**

```
SequenceMatcher equal count : 342 of 342  -> reported 100.0%
direct prefix walk          : first modulo-address difference at index 21
```

SequenceMatcher achieved 342/342 with **two** matching blocks and one delete, i.e. it found a long matching
block *after* the divergence, matched everything on both sides of a gap, and never reported the gap as a
difference at that granularity. The streams differ at instruction 21: the reference has
`test ebx,ebx; je 0x1000ab38` there (the shared `recheck` guard of shapes §61) and we go straight to
`jmp 0x1000ad08`.

**The sound instrument has two parts, and the second is the one that matters:**

1. **Direct prefix walk**: advance `k` while `norm(ref[k]) == norm(our[k])`. This cannot skip a divergence
   and gives the true first difference. It carries no alignment assumption at all.
2. **Resync scan after `k`**: for each instruction offset in a bounded window, count how much of the tail
   matches. This is what says *how much* of the rest is displaced, and at which offset.

Applied to `cm_ProcessCommandQueue`, part 2 finds **319/319 exact tail match at offset +2**: after the
2-instruction divergence our stream equals the reference's exactly, shifted by 2 instructions. So the
carrier's *entire* residue is those two instructions, and everything after is displacement. That is a far
sharper statement than the SequenceMatcher table's "100%".

**The rule.** Never read a `SequenceMatcher` ratio as an alignment result. A matching-blocks ratio is
**monotone in similarity, not in alignment**: it skips gaps by construction, which is exactly the quantity
being measured. Use a direct walk for "where do the streams first differ" and an explicit offset scan for
"how much of the tail is displaced". Block-matching libraries are for diff display, not for measuring
displacement.

This is measure-traps §31 ("exact isomorphism over ADDRESSES answers the wrong question: establish
correspondence first") in a new form: here the correspondence method itself silently suppressed the
difference it was meant to find.

## 46. The residue is 100.00% instruction-aligned: every differing byte lies inside a reference instruction (round 1072)

A property the project has never stated or checked: **is every residue byte covered by a reference
instruction?** If any differing byte sat in *padding* or in the gap between functions, the residue would
include something that is not a codegen difference at all, and the whole per-carrier analysis would be
incomplete.

**Measured over all 19 carriers**, decoding the reference from each entry and building the set of byte
offsets covered by its instructions, then intersecting with the residue:

| carrier | span | residue | on-instruction | |
|---|---|---|---|---|
| `gm_AllocSpieler` | 3696 | 2823 | 2823 | 100% |
| `CrashDump` | 2128 | 1583 | 1583 | 100% |
| `cm_ExSellObjekt` | 2064 | 966 | 966 | 100% |
| `ls_LoadBuildingEntityState` | 1472 | 671 | 671 | 100% |
| `cm_ExCopyEntityData` | 912 | 462 | 462 | 100% |
| `gv_ExAllocGraveyardWorker` | 1040 | 451 | 451 | 100% |
| `ServerMainThread` | 2448 | 367 | 367 | 100% |
| `gm_AllocGebaeude` | 1088 | 327 | 327 | 100% |
| `vfs_OpenStream` | 704 | 238 | 238 | 100% |
| `gm_FindNextFilteredEntity` | 352 | 215 | 215 | 100% |
| `ahm_ExAllocAlchemist` | 1008 | 198 | 198 | 100% |
| `gm_CheckInventoryCapacity` | 400 | 97 | 97 | 100% |
| `m_AllocTracked` | 672 | 92 | 92 | 100% |
| `srv_LoadBuf` | 752 | 49 | 49 | 100% |
| `gm_ObjectsAvailble` | 720 | 25 | 25 | 100% |
| `vfs_ReadCompressed` | 496 | 23 | 23 | 100% |
| `cm_ExProdObjekt` | 1008 | 21 | 21 | 100% |
| `cm_ProcessCommandQueue` | 640 | 15 | 15 | 100% |
| `gm_CalculateProductionValue` | 400 | 5 | 5 | 100% |
| **total** | | **8628** | **8628** | **100.00%** |

**Zero bytes in padding, zero in an inter-function gap, zero outside a function.** Every residue byte is a
difference *within* an instruction the reference actually emits: consistent with §13's attribution
(0x21b4 of 0x21b4 inside the 19 carriers) and now confirmed at instruction granularity rather than function
granularity.

**Why this closes a class of doubt.** If even a few bytes had landed off-instruction, the reading would be
"some residue is not codegen": a different problem with a different fix. It is not. The residue is 8,628
bytes of *instruction content*, which is exactly what the per-carrier sections describe.

**A method error caught while measuring, recorded because it nearly produced a false result.** The first run
used a hand-written size window per carrier (480 bytes for `gv_ExAllocGraveyardWorker`) instead of the real
span (1,040), which truncated that carrier's residue to 41 bytes and left 2 bytes apparently off-instruction.
The give-away was the total: **7,874 instead of 8,628**. The correct span comes from
`function_structure.json`'s next tracked VA, and with it the total is exactly 8,628 and the
off-instruction count is exactly 0. **Check that a per-carrier sum reproduces the known total before trusting
any per-carrier ratio.**

## 47. The residue table silently hid every carrier under 9 bytes: 18 rows summing to 8623 against a 8628 total (round 1073)

`scripts/postlink_residual.py` is the per-carrier ruler this project quotes in every round. Its default table
filtered rows:

```python
if args.verbose or count > 8 or name.startswith("<"):
    print(...)          # else: silently dropped
```

**So any carrier with 8 or fewer residue bytes was omitted.** Exactly one qualifies
(`gm_CalculateProductionValue`, 5 bytes), and the consequences were:

```
table rows printed : 18
sum of those rows  : 8623
summary line below : "0x21b4 of 0x21b4 differing bytes are inside the 19 functions"
0x21b4             : 8628
```

**The table could not be reconciled with its own summary.** Nothing was wrong with the *measurement*: the
summary is computed over the full set, but a reader who summed the printed rows would find a 5-byte gap and
no explanation for it. This project has used that table as a primary ruler for many rounds, and the carrier it
hid is one of the 19 named in §33.

**How it surfaced.** Round 1072's rule (*check that a per-carrier sum reproduces the known total*) was
applied to the tool's own output rather than to a hand-built table, and the sum came out 8623.

**Fixed:** the default view now prints the suppressed count and their byte total, and a `total` row:

```
cm_ProcessCommandQueue                       15 0x1000aaf7
(1 more carrier(s) <= 8 bytes, hidden         5
total                                      8628
```

`-v` always showed all 19; the fix is to the **default**, so the column reconciles without the flag.

**The rule, generalised.** A display filter is not a measurement, but it is what a reader measures. **Any
table that can drop rows must print the dropped count and their total, or state the total it is a subset of.**
This is the same failure shape as workflow-traps §22 (a check that cannot fail) and §23's message problem: the
tooling's *reporting* costing more than its computation.

Found by applying round 1072's own arithmetic cross-check to the tool rather than to a script written in the
same round, which is the first time this session that discipline caught a defect in shared tooling instead of
in my own ad-hoc code.

## 48. Audited every table and counter the project quotes against its own arithmetic: all reconcile (round 1074)

Round 1073 found the residue table hiding a carrier and failing to sum. This applies the same check to
**every other number the project treats as a ruler**, on the principle that one unreconcilable table implies
the possibility of others.

| source | figures | check | verdict |
|---|---|---|---|
| `postlink_residual.py` table | 18 rows / 8623 vs summary 8628 | sum vs reported total | **failed**: fixed round 1073 (`total` row + hidden-count line) |
| `rebrew verify --json` summary | `exact` 31, `reloc` 233, `proven` 17, `passed` 281, `total` 283, `byte_matched` 264 | 31+233 = 264 = `byte_matched`; 264+17 = 281 = `passed`; 281+2 = 283 = `total` | **exact** |
| `rebrew verify --full` warning | "13 function(s) have annotation SIZE differing" | `size_divergences` list length | **13 = 13** |
| `gate.sh` residue line | `residue 8628, baseline 8628 held` | `RESIDUE_BASELINE` | **held** |
| `gate.sh` byte-match line | `byte-matched 264 (EXACT+RELOC), baseline 264 held` | `BYTE_BASELINE`, and 31+233 | **held** |
| `gate.sh` raw-link `.data` | `21481, baseline 21481 held` | `DATA_BASELINE` | **held** |
| `gate.sh` imports | `(100)` | reference import count | **matches** |
| `gate.sh` data extents | `195 sized .data/.rdata entries` | - | reported, no independent total to check against |
| `build-check` | `198 object(s) checked` | objects with a `Custom` comment in `flags.make` | **198** |
| `fault_address.py` | 19 carrier rows | `codegen-walls` §33 table | **19, identical** |

**Only one failed, and it is fixed.** Everything else is internally consistent *and* reconciles against an
independent figure: the carrier tables agree between two tools, `verify`'s summary partitions exactly, and
each gate baseline is a named constant the report echoes.

**Why the audit was worth a round.** The residue table is the number every round quotes, so a subset silently
presented as a total is the highest-consequence display defect available here, and it had been there for many
rounds, invisible because nobody sums a table they trust. The other nine checks being clean is the useful
complement: it bounds the defect to the one place it was found.

**The rule.** A reported figure should either be checkable against another reported figure, or say what it is a
subset of. Apply the check to the tooling's output, not only to hand-built tables: that is how round 1073
found this one.

## 49. Auditing docs for "missing evidence" by regex measures word choice, not evidence (round 1075)

Round 1074's discipline was applied to the **claim** side: does every wall in the docs have a recorded
measurement behind it? A regex was written for "a number with a unit, an address, or an explicit round" and
run over three docs. It flagged eight sections as lacking evidence.

**All eight have evidence. The regex was the defect, exactly as in §§43, 44 and 46.**

| section | why the regex missed it | what is actually there |
|---|---|---|
| `codegen-walls` §4 | "**Nineteen** spellings": a word, not a digit | nineteen spellings enumerated, two named sites, per-site byte counts |
| `codegen-walls` §5 | scores written `714 -> 480`, `888 -> 279` | specific functions, scores, object sizes, and the composition-band consequence |
| `codegen-walls` §6 | title contains "measured" but body cites a constraint | a named constraint and the win it forbade |
| `measure-traps` §2 | the figure is a **re-measurement** (`"−58" re-measured at +56`) | the defect and its correction |
| `measure-traps` §3 | figures are in prose (`four bytes per call`) | a word-number, plus a named finding |
| `measure-traps` §8 | two score pairs on one line | four figures and the rule they justify |
| `measure-traps` §10 | it is a **procedure list**, so it contains commands not measurements | commands, which is the correct content for "how to check" |

**The finding is therefore negative and worth stating: every wall in `codegen-walls` (40 sections),
`measure-traps` (60) and `workflow-traps` (25) carries a numeric, address-based, or round-based
justification.** The documentation's evidence discipline holds across 125 sections.

**The method lesson: the fourth instance this session.** A regex over prose measures the *words used to
describe* evidence, not the presence of evidence. This is §§43 (header history), 44 (byte vs instruction
granularity), 46 (span windows) and now 49: **every attempt to automate "is this documented?" by keyword has
produced false positives, and in each case the correct instrument was reading the section.** The audit that
works here is a human-readable one, and this round performed it by hand after the regex flagged candidates.

**Practical rule.** Use a regex to *narrow* the set to inspect, never to conclude. State a keyword-based
audit's result as "N sections need eyeballing", not "N sections lack evidence".

## 50. The per-carrier table is stable across a full object rebuild, and the deliverable is bit-identical (round 1076)

Round 1039 verified that a clean rebuild reproduces the shipped `server.dll` byte-for-byte. What it did *not*
check is the stronger property every round actually depends on: **are the per-carrier numbers themselves
stable?** If a carrier's residue drifted between builds, the "floor" would not be a floor and every per-round
comparison would be against a moving target.

**Measured, three builds:**

| build | deliverable | per-carrier table |
|---|---|---|
| baseline | `md5 3febd2c4ca080a3749c12d4bf7452fbe` | reference table |
| full relink (`rm -rf build/split_poc` + `split_link.sh` + postlink) | - | **identical** (`diff` clean) |
| full **object** rebuild (`cmake --build build`) + relink + postlink | `md5 3febd2c4ca080a3749c12d4bf7452fbe` | **identical** (`diff` clean) |

So the 19 per-carrier figures (2823, 1583, 966, 671, 462, 451, 367, 327, 238, 215, 198, 97, 92, 49, 25, 23,
21, 15, 5) are **reproducible**, not a snapshot of one build's state. That is what makes
`RESIDUE_BASELINE` a meaningful floor: any per-round delta measured by `linktest.sh` is attributable to the
source edit, not to build noise.

**Why this is worth recording rather than assumed.** Round 1055 was a case where a source revert left a stale
object in the tree, and every downstream number described a build no clean checkout would produce. The
verification there was ad hoc. This is the systematic version: **compare the per-carrier table, not only the
file hash**: the table is what the rounds quote, and it is a strictly stronger check than the hash because it
localises any difference to a carrier.

**Method.** `postlink_residual.py`'s table after each of the three builds, diffed with `diff` (not summed,
the sum check is §47's job, and these two checks catch different failures).

**This closes the reproducibility question at the granularity the project measures at.**

## 51. A "0 mismatched" data verdict measured 37% of the metadata, and said nothing about it (round 1078)

`rebrew verify --data` printed:

```
data: 122 matched, 0 mismatched, 0 missing
```

Read as a whole-tree statement that is a full pass. It is not. `src/rebrew-data.toml` held **329**
symbols at the time; the check had compared **122** of them and reported no denominator, so nothing in the
output distinguished "every symbol verified" from "a third of them, chosen by a rule the reader cannot see".

**The rule is in `data_verify.section_symbol_bytes`, and it is deliberate.** It skips a symbol when

- its `section` is not in `(".data", ".rdata")`, or
- its extent runs past the section's `raw_size`: the zero-fill tail, which has no file bytes:

```python
if offset + size > sec.raw_size:
    continue  # zero-fill tail (BSS): no file bytes to read
```

A skipped VA never enters `ref_sizes`. `verify.py`'s write-back builds `matched_names` by iterating
`ref_sizes`, so a skipped symbol is never a candidate for `DATA_STATUS_VERIFIED` and stays `UNCHECKED`
**permanently**: no run of any command can move it. Those permanently-UNCHECKED entries are exactly what
`rebrew todo`'s `start-data` lane is built from, which is why that lane could never empty.

**Measured, guild-rebrew: 329 metadata symbols → 207 UNCHECKED → all 207 un-clearable.**

| group | count | why it cannot clear | independently confirmed correct |
|---|---|---|---|
| import slots (`__imp__…`, `section = ".idata"`) | 84 | linker output; the image has no `.idata` section | all 84 IAT dwords byte-identical |
| zero-fill tail (`0x10035000`+, incl. `section = ".bss"`) | 111 | past `.data`'s `raw_size = 0xE000`; no file bytes | zero-filled in both images by construction |
| sized with real file bytes | 5 | - (these *are* comparable) | byte-identical |
| no size and no usable type | 7 | nothing to compare | n/a |

Zero differences anywhere. **The data lane for this binary is complete**, and the 123 `todo` items that
claimed otherwise were an artefact of the ruler, not work.

**Fixed in rebrew (round 1079, commit `3f7cefea`).** The report now carries `total`, `compared`,
`not_comparable` and `coverage`, and the summary prints the denominator:

```
data: 122 matched, 0 mismatched, 0 missing (122 of 329 symbols compared, 37%)
  207 symbol(s) not comparable: no file bytes (zero-fill tail) or outside .data/.rdata:
  a zero above bounds only what was compared
```

The trap below is still worth knowing, because it generalises past this tool to every "0 differ" result:
the fix makes *this* denominator visible, not every future one.

**The transferable trap: a zero in a diff-shaped result is not a zero in coverage.** "0 mismatched" bounds
only the population the tool chose to look at. Before treating such a number as "this axis is done", find the
denominator: here it was absent from the output entirely and had to be reconstructed by calling
`section_symbol_bytes` directly on both images and counting `ref_sizes`. A cheap version of that check:
compare the result count against the metadata entry count; 122 against 329 is the tell.

**The trap bit for the whole project, not one round.** The lane's "123 start-data items" was quoted as
pending work in round briefs, and `start-data` was the largest category in `rebrew todo` for hundreds of
rounds. Every item in it was un-clearable. Round 1076's "the table is stable across rebuilds" is the correct
kind of check; this is its data-side counterpart: verify the *denominator*, not just the difference.

## 52. Decoding a function by its INVENTORY SPAN swallows inter-function padding and fabricates instructions (round 1084)

Disassembling a function by taking `function_structure.json`'s `(va, size)` and running a linear sweep over
that window is a measurement trap, because **the inventory span can extend past the function's real end into
`0x09` padding.** `09 09` decodes as `or dword ptr [ecx], ecx`, so the padding is not skipped: it becomes
instructions, and every derived count is wrong.

Measured on `CrashDumpUnhandledExceptionFilter` (`0x10002770`, inventory size 2128, so the span ends at
`0x10002fc0`):

| | |
|---|---|
| real code end (first run of `0x09` padding) | `0x10002f4c` |
| bytes of padding inside the inventory span | **116** |
| instructions counted over the full span | **724** |
| instructions counted to the real end | **673** |

**The fabricated instructions are not random noise: they cluster into a specific mnemonic.** Sweeping the
whole span made it appear that the reference contains **52 `or` instructions and only 1 `call`, against our
43 `call`s**, which reads as a completely different calling convention and sent this round chasing a
"register-argument-passing" hypothesis for a while. **All 50 of the surplus `or`s were the padding**: they
appear as one contiguous run at `0x10002f4e` upward, each with the identical text `or dword ptr [ecx], ecx`.
A quick test for exactly this:

```python
bad = [i for i in ins if i.mnemonic == "or" and i.op_str == "dword ptr [ecx], ecx"]
```

Any long run of those is `0x09` padding, not code. The tell in the byte dump is simpler still: look for a run
of `09` bytes.

**Corrected, the function is far less interesting than the artifact suggested.** 673 vs 656 instructions is an
18-instruction shortfall, and the largest divergence run is 131 instructions: the same *shape* §34/§35 found
in `gm_AllocSpieler`, not a calling-convention difference. The `sprintf`/`WriteFile` order at `0x10002aaf` is
the divergence, matching the "tail log/sprintf order" class already recorded for `gm_AllocSpieler`.

**The transferable trap: the unit of analysis has to be the function's real extent, which the inventory does
not give you.** Round 1040-1046 established that the inventory is *coarser* than the annotations (543 entries
against 283). This round adds the other direction: an inventory entry can also be **wider** than the function,
because sizes are gaps to the next entry. Before trusting any per-function instruction count, find the
padding: scan for runs of `0x09` (or `0xcc`) and stop there. Two other spellings of the same mistake were
already on record: `docs/measure-traps.md` §47 (residue ≠ error size) and §51 (a zero over an unstated
denominator). This is the third: **a count over an unstated boundary.**

**Corollary: measure the boundary before counting (round 1085).** Round 1084's correction is only useful if applied. Analysing the second carrier with the real extent (2012 bytes, stopping at the `0x09` padding) gives **673 reference instructions against our 656**, with the largest divergence run 131 instructions at `0x10002aaf`: the same shape §34/§35 found in `gm_AllocSpieler`. Counting over the padded inventory span instead gave 724 and made the run look like an 18-instruction shortfall plus a calling-convention difference. The corrected reading is: a `sprintf` argument-ordering difference, one instruction deep, cascading through the call's argument setup:

```
ref                                   ours
push 0x100272b4   (format)            mov edx, dword ptr [ecx + 0x18]
push eax                              push edx
call sprintf                          push 0x100272b4
add esp, 0xc                          push eax
lea ecx, [esp + 0x10]                 call sprintf
```

The reference pushes the format string first and loads the third argument after; we load it first. Everything downstream rotates from that.

## 53. The raw link is the wrong artifact for a `.data`-addressed operand comparison (round 1086)

The alignment technique of §34/§35 and the two rounds after it disassembles `build/split_poc.dll`: the raw
link, before postlink. That is correct **for `.text`**, which is what those rounds compare, because postlink
does not rewrite code. It is wrong the moment the comparison touches an operand that resolves into `.data`.

Measured, `cm_ExSellObjekt` (`0x1000d930`): the `LogMessageInternal` call site pushes the message pointer. In
the raw link and the reference that pointer is **the same immediate**, because it is an absolute VA baked into
the instruction, but the *string it points at* is at a different place:

| file | bytes at `0x1002cdac` | bytes at `0x10029e24` |
|---|---|---|
| reference | `"cm_ExSellObjekt() Lager voll"` | unrelated data |
| **deliverable** (`build/server.dll`) | `"cm_ExSellObjekt() Lager voll"` | unrelated data |
| raw link (`build/split_poc.dll`) | **zeros** | `"cm_ExSellObjekt() Lager voll"` |

The deliverable matches the reference **at both addresses**. Only the raw link has them swapped -- COMDAT
string material lands elsewhere before `rebrew build postlink` rewrites the `.data` operands (4398/4398 of them,
verified in an earlier round).

**Why this nearly became a false finding.** Reading the raw link's disassembly alongside the reference's, the
two call sites appear to pass *different string literals*: the reference pushes `0x1002cdac`, ours pushes
`0x10029e24`, which reads as a wrong literal in the source and sent this round to the source line. The source
was already correct (`cm_ExSellObjekt.c:396`), and so is the build.

**The rule.** `.text` residue must be measured on the raw link, because that is the only artifact where the
code has not had operands rewritten. Anything that dereferences a pointer into `.data` (string addresses,
table bases, global pointers) must be measured on the **deliverable**, after postlink. The two artifacts
answer different questions and this round asked the wrong one of the wrong file. Cross-check before reporting:
`docs/measure-traps.md` §20 already establishes that the whole raw-link `.data` divergence is
postlink-supplied, so a `.data`-addressed difference in the raw link is expected and carries no information.

## 54. A whole-section idiom census cannot use the raw link's `.text`, and cannot compare rates at all (round 1088)

§33's "census trick" (count an idiom image-wide on both sides to turn a byte residue into a small
instruction-level claim) is recorded as reusable. Reusing it on the **whole `.text`** does not work, and the
failure is silent.

**The raw link's `.text` is mostly not yet code.** A linear sweep of `.text` over its raw extent gives:

| file | `.text` VirtualSize | raw extent | instructions from a linear sweep |
|---|---|---|---|
| reference | `0x22846` | `0x23000` | **16,472** |
| raw link (`build/split_poc.dll`) | `0x22ac8` | `0x23000` | **2,916** |

The built image's region is largely unpopulated at the point the sweep passes through it: the composition
places objects at reference VAs, so the gaps are zeros, and decoding zeros yields long runs of `add [eax], al`
rather than nothing. The result is a 5.6x difference in "instruction count" that is entirely an artefact.

**Why that makes rate comparison meaningless, not merely noisy.** The obvious next step is to normalise
(`idiom occurrences / total instructions`) and compare the ratio, since absolute counts track the 10% of
`.text` that already differs. But the denominator is wrong by 5.6x on one side, so every ratio is wrong by a
factor that has nothing to do with the idiom. Measured, that produced a table reading "`and` ratio 1.50,
`xor` ratio 1.49, `push` ratio 1.25", which looks like four findings and is one artefact. The `call` and `cmp`
rows came out at 1.01 and 1.00, and `fs:`/`gs:` at 0.00/0.00, which is the tell: a real difference does not
produce three ratios of exactly 1.00.

**The rule.** The census works on a region both sides genuinely produce, which is why the recorded successes
were per-idiom counts over the whole *image* on matched functions (round 921's `and r,0xffff` 16 vs 19 and
`xor r,r` 556 vs 550), not over a section one side has not filled. Before using a census here, confirm the two
denominators are within a few percent; a large gap means the population includes undecoded padding, and the
trap is that it reads as a finding rather than as a broken measurement.

**This is the fifth instance of one family in this project**: the population is assumed while only the values
are checked: §47 (residue ≠ error size), §51 (a zero over an unstated denominator), §52 (a count over an
unstated boundary), §53 (the right number from the wrong artifact), §54 (a rate over a fabricated
denominator).

## 55. `postlink_residual.py` measures the raw link, so a stale composition reports a fake residue of 81,229 (round 1101)

`scripts/postlink_residual.py` defaults to `--built build/split_poc.dll` (the **raw link**, not the deliverable)
because that is the artifact where `.text` is unrewritten. That is correct for its purpose and it is also a
trap: `build/split_poc.dll` is regenerated only by `scripts/split_link.sh`, so after any object rebuild the file
on disk is whatever the last composition produced.

Measured this round: a `--clean-first` rebuild plus a probe left one object holding experimental code. The
composition then failed to place (0 of 319 symbols at reference VA, `.text` `0x22b08` against `0x22846`), and
`postlink_residual.py` reported **total 81,229** with `0x9401` differing bytes *outside* the 19 known carriers.

**Two independent checks said the tree was fine**, and both were right:

| check | reading |
|---|---|
| `build/server.dll` `.data` vs reference | **0 differing** → the deliverable *is* correctly postlinked |
| `.text` VirtualSize, imports, file size | `0x22846`, 100, 286,720: all correct |
| `rebrew build check` | clean |

So the 81,229 was entirely about a collapsed intermediate, not about the deliverable.

**The tell.** A residue total that is *an order of magnitude* above the baseline (81,229 against 8,628), and a
"differing bytes outside the 19 carriers" count that is large (`0x9401` against a baseline of `0x0`). The
baseline invariant is that **100% of residue lies inside the 19 carriers**; when that ratio breaks, the
intermediate is stale, not the code.

**Recovery, in order:** `rm -rf build/split_poc && bash scripts/split_link.sh`, which prints
`exactly at their reference VA: 246`. That count is the composition's own health check: **246/319 means good,
0/319 means collapsed**, and it appears before the residue number, so read it first.

**The distinct failure that caused it.** `linktest.sh`'s and the gate's stale-object guard both fired, and every
`rm -f <obj>` plus `cmake --build` is what eventually recovered it. This is the fourth round in this session
where a stale object cost time (workflow-traps §24, rounds 1082-1084). The reliable recipe is: after any probe,
`rm -f` the object explicitly, rebuild, then `rm -rf build/split_poc` and relink before reading **any** residue
number.

## 56. `verify --data --built <raw link>` rewrites VERIFIED statuses to DRIFT in the tool-owned toml (round 1102)

Pointing `--built` at `build/split_poc.dll` to get a non-tautological `.data` check is tempting, but the
comparison is the §20/§53 displacement artifact, and the tool **writes back**: every displaced symbol's
`status` in `src/rebrew-data.toml` moves `VERIFIED` → `DRIFT` (measured: `g_next_object_id`,
`g_producer_id_table`, `g_file_version`, the filter group, 30 in total against the round-698 steady state of
23). `git status -- src/rebrew-data.toml` went dirty from a read-shaped command.

**The rule.** `verify --data` is only meaningful on the deliverable (`build/server.dll`, postlinked). The
raw-link `.data` divergence is postlink-supplied by §20's own proof; running the check against the raw link
produces statuses that are wrong and persistent. Recovery: `git checkout src/rebrew-data.toml`, or re-run
`rebrew verify --data` (deliverable) which writes `VERIFIED` back to all displaceable symbols.

**All 30 mismatches were triaged to the displacement class**: spot-checked `g_file_version`'s bytes
(`5a 00 01 00 53 61 76 65 67 61 6d 65`): reference holds them at `0x2d4f0`, raw link holds them identical at
`0x2db30`; same content, different VA. `g_dispatch_table` is zeros in the raw link because `data_restore`/
postlink supplies it. Nothing was content-drift.

## 57. A relative include deeper than the tool's staging depth compiles unpacked, silently (round 1103)

`#include "../../../game_structs.h"` from `spiel_c/` is correct in the plain CMake build (`flags.make`
bind-mounts the tree at the same path, so the depth resolves exactly as on the host). Under `rebrew
test`/`rebrew diff`, the source is staged flat in a temp workdir; the depth-3 quoted include no longer
reaches the tree and the same bare-name include does, but the depth-3 spelling compiled anyway, because
the runner adds `src_parent` and the include dir as `/I` paths, and one of those resolutions (measured:
`target 0x3f got 0x41`, `8b7641` vs `8b763f`) returned a DIFFERENT body: pointer slots shifted +2 as if
`#pragma pack(1)` was absent, with `0 structural diffs` nowhere, a RELOC → NEAR_MATCHING demotion, and no
`error C####` anywhere in the log.

**The rule.** Project headers included from deep source files must be spelled as bare quoted names
(`#include "game_structs.h"`), resolved via `-I src/Develop`: the one spelling that is correct in the
CMake build, the flat workdir, and the remote recompile service. A depth-2 `../../include` spelling in
files at `game/` depth works today only because the staging depth happens to match; do not copy it deeper.
**Cross-check after any include-spelling change to a reversed TU:** `rebrew diff` must read `0 structural,
0 register`; a `target<R got got<R+2` pointer-slot pattern is the unpacked tell.

## 58. A lower byte count from a spelling that changes a stored value

A search over constant spellings in `gm_AllocSpieler` scored `*(unsigned short*) (slot + 0x50)
= 0x7fffffff;` at 10 differing bytes against the source's 17, with the edge-reload order at
0x10018c28 flipped to the reference's. The low 16 bits of `0x7fffffff` are `0xffff`: the
object stores `0xffff` where the reference stores `0x7fff`, one byte in the diff, and the
flip came from the `0x7fff` candidate disappearing. `rebrew match run` output has the same
failure mode: its best for this function (score 21000) swaps the `type` and `location`
parameters and adds padding locals. **The rule.** Read every differing byte of a candidate
(`rebrew diff <file> --json`) and check its semantics before keeping it; a smaller
count is not evidence of the same program.


### Pair-copy byte score hides an overlapping-buffer mismatch (2026-10-04)

TL `0x00407760` previously prefetched the final odd byte before writing the
final even byte. The original writes the even byte first, then reloads count
and source pointer to read the odd byte. These orders differ for overlapping
source/destination arrays; favoring the higher object score would keep incorrect
source behavior.

A concrete execution through angr's VEX engine compares the original 159-byte
function, the complete old 162-byte compiled function, and the complete corrected
163-byte canonical function. Inputs: count 3, fast-selector step 2, destination
at source-buffer offset 3, initial bytes `[10,20,30,40,50,60,70,80]`. All return
2. The reference and corrected C end with
`[10,20,30,30,40,40,40,80]`; the old C instead leaves `60` at offset 6.
The float-conversion branch is not entered and no external-call model is used.
This is one concrete counterexample and repair check, not a general proof.

Canonical repair removes the early odd-byte temporary and evaluates
`src->bytes[src->count * 2 - 1]` after the even store. Positional object score
falls from SIZE_MISMATCH 76/162 to 18/163 (159-byte reference); no byte-match or
linked-file gain is claimed. Retain the reference's observable read/write order
while solving register allocation. Receipt and reproducible script:
`.scratch/goal-sound-order/tail-alias-evidence.json` and `check-tail-alias.py`.
The script uses `CompareResult.full_obj_bytes` on size mismatch so execution
includes the complete compiled tail; the shorter comparison slice is insufficient.

### Explicit donor identity does not remove inventory-span noise (2026-10-04)

Related-import signature scoring sees managed42-byte TL device donors versus
Gold’s discovered48-byte spans (42-byte native body plus6 NOPs), giving85.935306.
The complete42-byte native patterns, unique GUID/CreateDevice outputs, and strict
wrong-global controls establish mouse/keyboard counterparts independently.
Use --source-va with a documented known-counterpart score allowance85, retain
normal verification, and let the verified-padding/merged-entry flow persist42.
Gap0 alone picks the same donor for both devices and is insufficient identity.
Receipts .scratch/goal-input-types/import-sizing-diagnostic.json, *known-preview.json,
*import.json, canonical-wrapper-bindings.json.

Rebrew deliberately masks IAT positions even when a supplied import name/VA
map disagrees. A wrong CloseHandle catalog binding therefore remainsRELOC; that
negative control does not prove an import-name match. The independent input audit
compiles once, uses public typed COFF records and smart_reloc_compare with
iat_region=None, requires every relocation symbol mapped, and supplies native
CloseHandle slots TL6620ec/Gold5eb0cc. Both107-byte cleanup bodies pass and reject
all8 wrong-binding controls each (including import); TL738-byte init passes with
all32 wrong-binding controls rejected. This audit is separate from CLI RELOC
status and is not a linked-file/import-table identity claim. Receipt
.scratch/goal-input-types/canonical-call-bindings.json and check-input-call-bindings.py.

### Indexed displacement can be a biased base in unrelated data (2026-10-04)

TL41a950 bounds its index to20..31 then loads [index*4+662ba8]. The displacement
662ba8 is inside pixel-format label strings (e.g.G5B5), not the start of an int
array. The accessed12-word span begins662bf8 (=662ba8+20*4) and contains
24,32,32,16,16,16,16,8,0,16,16,32. A canonical C reference should express the
actual table/view plus index-minus20 so COFF carries the real symbol with
addend-80; blindly declaring g662ba8 as an allocation would invent a false
owner over unrelated string bytes. Full backing allocation/provenance remains
unestablished; no definition or managed data owner created. Read-only evidence
.scratch/goal-input-drain/table-helper-native.json and
.scratch/goal-debug-record/pixel-neighbor-native.json.

### Stock-body membership does not select a unique CRT member

Whole-body relocation-masked probes for TL66080a andGold5eaad6 return library=true but symbol/object=null with __strlwr and__strupr candidates. The former matches MT LIBCMT objects, the latter ST LIBC objects. This establishes stock-body membership without selecting a unique member from the tie. Preserve the unresolved candidates; do not rename/reimplement a CRT routine based on the marker catalog name alone. The shared game wrapper42e520/Gold42ecf0 has separately verified char* ABI and native branch targets; native caller bindings and exact library-member attribution are different claims. Evidence .scratch/goal-net-stats/next-helper{,-gold}-library.json; lib_match.py documents masked-relocation candidate ambiguity.

### Comparison width resolves the case-conversion tie

The earlier TL66080a/Gold5eaad6 strlwr/strupr candidate tie was a32-byte prefix comparison: library match --va uses managed SIZE or PREFIX_BYTES32, and those library entries had no SIZE. Comparing complete native inventory spans308/158 through public index_library/match_bytes uniquely selects strupr.obj; strlwr has7/4 fixed mismatches. Earlier wording describing that tie as whole-body ambiguity is superseded by this evidence. Do not equate library=true or candidate ties with a complete native-body comparison when JSON omits its scope. Missing explicit-size/scope feature recorded upstreamIDEAS immediately. Evidence .scratch/goal-vfs-casefold/full-runtime-attribution.json.

### COFF zero-filled literal sections need semantic bytes

The scratch literal audit initially called nine correct empty-string operands different: LIEF section.content returned the header byte4c for an uninitialized COFF.bss COMDAT whose raw size is1 and raw pointer is0. Read the actual section header and the UNINITIALIZED_DATA characteristic; that symbol contains one zero byte, not byte4c from file offset0. The corrected scratch reader independently matches all five complete native bodies and rejects wrong-address controls. This is a scratch-reader assumption correction, not a Rebrew compiler/source change. Evidence `.scratch/goal-small-client-helpers/empty-string-reader-correction.json` and `empty-string-binding-audit.json`; initial diagnostic preserved as `deferred-literal-differences-attempt1.json`.

### Resolving an unknown callee changes mismatch scores without changing code (2026-10-04)

Adding the proven TL `gm_RandomMod` identity at42e410 makes REL32 validation bind calls previously treated as unresolved. Full comparison must review this catalog change even when source edits only rename identifiers. Five existing SIZE_MISMATCH rows acquired larger deltas:

| TL VA | Prior unbound delta | New bound delta |
|-------|--------------------|-----------------|
| 0044a120 | 288 | 318 |
| 0049a590 | 515 | 523 |
| 004ee290 | 849 | 864 |
| 004f3310 | 699 | 707 |
| 005d6030 | 357 | 364 |

The audit compiled the original backed-up source and current source with the same compiler/flags/header context, producing identical function bytes. Re-running the comparison with only gm_RandomMod/_gm_RandomMod absent from the symbol catalog reproduces all five old scores; restoring their verified42e410 address reproduces all fresh scores. Every row remains SIZE_MISMATCH, and no byte-matched row was lost. The higher deltas reveal a stricter comparison rather than changed executable bytes. Do not drop the binding to preserve a flattering score or ignore arbitrary regressions: accept only reviewed exact rows whose compiled-byte hashes and counterfactual comparison establish the cause. Evidence .scratch/goal-random-helper/consolidation/new-callee-binding-effects.json; full comparator retains exact checks for all other fields and rows.


## A trailing NOP can hide a wrong cross-target call binding

TL accessor `0x005b1eb0` compiled to31 bytes against a32-byte catalog extent,
with a100% common-prefix score. The excluded byte is a native trailing NOP,
but the old source called the Gold-derived `fcn_005a8690` symbol. Complete
REL32 decoding resolves the native TL callee to `0x005b1b10`. The existing
TL lookup body independently matches all31 bytes with its list-head pointer
at `0x00774a78`; the accessor reads the native default1.0f at `0x006628a0`.

Use the existing TL lookup declaration (`char*` return) and a pointer local.
The corrected accessor passes complete31-byte typed relocation comparison,
with IAT wildcard disabled. Wrong+4 call and list-head controls reject, as
does an explicit old Gold destination. Its whole body does not match stock
LIBCMT. Only then record31 as the function extent through the locked metadata
writer; retain the NOP as layout, without deleting or emitting padding.

Full all-target test20498 closed2 because other client failures remain.
Every-row comparison accepts exactly this SIZE_MISMATCH-to-RELOC promotion,
with no lost/added/removed rows or changed library providers. TL3558/3679;
server316/316 includes56 compiled library checks; Gold2041/2518 unchanged.
Fresh data89989 preserves all641 server verdicts, and raw serverff81a459
is unchanged. No whole-file byte gain is claimed. Evidence:
`.scratch/goal-tl-accessor/`. Scratch API attempt used the wrong update shape
and made no size change; the old-size batch46359 was explicitly terminated143,
and is not an accepted gate. Correct writer uses an update `fields` mapping.


## Undefined external string labels need complete payload proof

Three remaining TL extent candidates used undefined external string labels.
Restore five native compiler literals in their existing C sources: `buy dunkle
ecke` in TL4ab3e0, the two Friedhof paths and `sp_%u` in TL58d3f0, and `%1N3`
in TL5cc720. Compare each complete defined COFF literal, including NUL, with
the native operand payload before accepting the body. The full275/501/363-byte
bodies verify with64 typed relocations and rejected wrong+4 controls, with IAT
wildcard disabled. CFG and terminal checks exclude13/11/5 trailing NOP bytes;
those remain layout facts, without padding removal or emission. All three
complete game bodies miss the configured stock archive.

The first two sources also serve Gold4ab2c0/584e30. Their complete literal
payloads and all nonfixup bytes independently agree, but the Gold call/global
bindings remain incomplete. Do not borrow TL-address spellings as Gold VAs
or promote those Gold extents from the shared body. Native operand tracing
identifies actual destinations in deferred-gold-native-callees.json; presence
of a passing destination C row alone does not establish shared-call identity.

Locked metadata writer changes only the three TL sizes. Full85721 closed2
because other client failures remain; exact every-row comparison against20498
accepts only these three SIZE_MISMATCH->RELOC promotions, with no lost, added,
removed or other changed rows and identical library provider inventories.
TL3561/3679; server316/316 including56 compiled library checks and Gold2041/2518
unchanged. Freshdata22119 preserves all641 server verdicts; lint74986 has
zeroerrors and the exact prior warning set. Raw serverff81a459 is unchanged.

Evidence `.scratch/goal-tl-training/`: literal-audit.json, gold-literal-audit.json,
full-comparison.json, scope-receipt.json and data-lint-comparison.json. The first
scratch audit missed client_types.h after moving a source copy outside its
original directory; adding the original include directory to scratch flags
restored that context. Production flags and headers are unchanged.


### Compiler-local label counters are not relocation identity (2026-10-04)

The prospective slot declaration/type-view change leaves all276 bytes of TL504130 unchanged, but VC6 renumbers six switch-local labels (for example `$L589`→`$L594`). Comparing literal COFF label strings falsely rejects the unchanged body. Check relocation offset/kind and each referenced symbol's exact section bytes plus section offset; external symbol identities remain strict except the explicitly intended source rename. The six switch references agree under this check. Do not omit relocations or collapse all local labels into one wildcard. Evidence: `.scratch/goal-resolver-slot-types/{compiler-local-label-proof,all-user-attempt1}.json`; initial audit1381 CLOSED1 was retained, revised67654 is a separate measurement.


Resolver binding follow-up (2026-10-04): registering existing canonical globals/callee for TL makes five already SIZE_MISMATCH bodies lose4/2/11/3/4 formerly masked credits. Their Csource,headers,flags and generated bytes remain unchanged. The exact old/new name maps are reconstructed from the backed-up managed stores, and smart_reloc_compare independently reproduces both reported deltas with IATwildcards off. Do not report this as a code regression or a byte-match gain. Evidence: `.scratch/goal-resolver-consolidation/delta-effects.json`.

## Padding scores, donor gaps and the installed CLI (2026-10-10)

GOLD's animation builder 0x405970 contains a complete 75-byte body followed by
five NOPs. Comparing its 80-byte discovery span against TL 0x406510 lowers the
structural score from 100 to 94.393546. The bounded upstream signature repair
excludes only a real return's entirely padded suffix; it preserves reachable
NOPs and later return blocks. The original span still reaches full compiled-body
verification. No byte verdict follows from the structural score alone.

Correct extents do not remove the runner-up guard: unrelated histogram siblings
score 96.325483 for the builder and 96.275310 for its 152-byte caller. They have
different normalized instruction order. For the independently reviewed pairs,
use the existing `--source-va` with `--va`, retaining default score/gap checks on
the selected pool and full destination-byte verification. Automatic matching
must continue refusing its ambiguous pool. Evidence:
`.scratch/goal20/padded-signature-evidence.json` and paired import previews.

Check the editable installation when ordinary CLI results differ from a known
upstream checkout. This project's `.venv` pointed at the older
`rename-row-scope` worktree, so a default status query used stale library-identity
accounting. Its saved `.pth` and `direct_url.json` are in
`.scratch/goal20/project-rebrew-install-before.*`. Point the installation at
validated upstream main; a `PYTHONPATH` override alone does not update later
ordinary CLI invocations. The editable installation is now refreshed to
Rebrew 2613fa04, with no dependency changes.

The padding-fix suite run with the agent's `PYTHONDONTWRITEBYTECODE=1` passed
11,506 cases but failed the 0.8-CPU-second startup band at 0.877. Cold isolated
bytecache controls also put unchanged main over the band (1.326); subsequent
normal cached main/candidate imports use 0.18–0.27 seconds. Both thread caps and
heavy-import exclusion hold in every sample, and both isolated six-test startup
suites pass. The unchanged-source full rerun with normal caching passes
11,507 tests / 50 skips / zero failures. Keep the limit and do not call the first
full run green. Evidence:
`.scratch/goal20/padded-extents-startup-{no-write-comparison,comparison}.json`.

The callback's 98.087576 structural score also hides a real version difference:
its compiled TL displacement +0x390 differs from GOLD+0x84 by two bytes. The
first import correctly refuses without a row or verdict. An inferred per-target
build selector preserves one shared C body; both complete variants verify at
248 bytes, and the selector-omission control reproduces exactly those two
non-relocation differences. Never turn that field difference into padding or a
masked relocation. Layout evidence belongs in general-knowledge.md.

## A source rename can leave a live linker anchor (2026-10-11)

Renaming the shared plant lookup through Rebrew correctly changed its C
definition, callers and all three managed identities, but left the tracked
`layout/server.dll/game-includes.rsp` `/INCLUDE:_lb_SearchRecordTable` anchor.
The server gate failed with LNK2001 and LINK removed the previous output DLL.
A previous byte-identical DLL receipt does not establish the current build.
Repair the shared upstream rename plan, including target attribution, preview
and rollback, then use explicit reference binding for a linker-only stale name;
do not introduce a compatibility C alias. Upstream662d7132 now plans exact
native references in target-scoped INCLUDE/ALTERNATENAME/EXPORT options, preserving
public export names, decoration and paths. Five regressions failed first;
196 focused checks, all18 hooks and the corrected full suite11526pass/50skip pass.
The CLI linker-only repair changes one response line with no C/store changes.
The new gate passes all316 function checks,652 data comparisons and raw whole-file
identity. Keep both the failed and passing receipts: `.scratch/goal20/plant-server-gate.log`,
`plant-server-build-failed.log`, `plant-post-upstream-server-gate.log`.

## A shared import verdict can carry the wrong identity or inputs (2026-10-11)

The filtered iterator at TL503e80/GOLD501030 has a complete341-byte body and
11 following alignment NOPs. The original shared importer accepted the
341-byte retry but recorded reference_size352 and the rejected padded span's
hash. It also retained the former gm_AddObjekt name beside the correct
_gm_FindNextFilteredEntity symbol and selected another function's compiler
flags from spiel.c. A passing RELOC label alone did not prove that these
records described the measurement actually performed.

Use the selected source module and VA for flags; after verified retargeting,
replace the destination name and retain the successful body's comparison
inputs. A source-default flag choice must remove a stale destination override.
A rejected retarget between managed definitions in the same file must preserve
the entire previous row and verdict. Keep migration's protection of existing
names. These are shared upstream importer fixes, not reasons to edit managed
stores or modify the game body. Evidence: `.scratch/goal20/stat-iterator-tl-import.json`,
`stat-iterator-gold-import.json`, `stat-import-regressions-before-corrected.log`
and `stat-import-additional-before.log`.

The complete extent comes from bounded native branch traversal, all341 bytes,
all20 resolved operand sites, and wrong-binding controls. The conservative
linear extent reader stops at an internal jump after89 bytes; that result
does not establish the iterator's complete body. No instruction or match
threshold was changed to gain the client matches.

## Retire a shared source only after its last owner moves (2026-10-11)

The numeric slot-helper file carried both TL50dac0 and GOLD50a640 claims.
Rebrew's shared importer previously deleted the whole file after moving only
one claim. Upstream 2b46dab0 now considers managed function/data owners, live
legacy claims, other definitions and actual global storage before retirement.
It strips only the moved claim, preserves source lines and file-borne comments,
and backs up the final unowned single-body file. The game replay moves exactly
the two client rows; the first move preserves the other claim, and the second
retires the duplicate. Keep the generated backup as recovery evidence.

Source-in-workdir probes exposed a separate compiler wrapper bug: the original
parent include directory was omitted when source.parent equalled workdir.
The container's `/work` alias then broke parent-relative includes. Upstream
3214649a preserves the original authorized include path in that case; MSVC
fails before the fix and GCC provides a passing control. Both fixes pass their
focused checks, all 18 hooks and frozen full suites (11,553/11,555 passes,
50 skips respectively). Evidence: `.scratch/goal20/stat-helper-replay.json`,
`stat-helper-retirement-full-suite-policy.log` and
`compiler-source-in-workdir-full-suite.log`.

### Discovery overlap can hide an already-correct source extent (2026-10-15)

TL4186c0 had a47-byte inventory span but its source correctly compared the
complete five-byte tail jump. The next31-byte body was swallowed by the stale
span. TL571720 similarly retained4160 bytes despite a complete335-byte source,
covering the following production callback. Source verification alone does not
repair the discovery inventory; CU clustering correctly refuses such overlaps.
Use native control-flow/padding/next-entry evidence and the verified complete
body before curating a selected row. Preserve every unrelated identity and name.
A new7503-row discovery snapshot was not installed over the6337-row catalog.
Both selected repairs use the existing emitter utility and retain native
receipts under .scratch/goal37/. Neither early returns nor a near compiler
match justify truncating a function, switch region or callback.

### Immediate callback stores were missing from upstream xrefs (2026-10-15)

`binary xrefs` returned zero for callbacks TL5107f0 and Gold50d350 despite
native stores at5108f7/50d457. The shared instruction classifier handled
`mov reg, immediate` but omitted `mov [memory], immediate`, including absolute
store destinations. Upstreamf2dbe476 fixes section, function and reachable-code
scans to retain both operands when applicable. Native replay now finds both
assignments; two regression cases failed before,112 focused tests and12032
full-suite tests pass afterward. Scalar values outside the image are excluded.
An empty historical xref result at such a store is not absence evidence.

Replay through the pinned environment:
`uv run --frozen rebrew binary xrefs 0x5107f0 --json -t Europa1400Gold_TL.exe`
and the Gold counterpart at0x50d350. Receipts: `.scratch/goal41/upstream/`.

### A probe object name can be a Windows device name (2026-10-15)

The auxiliary-record probe requested `aux.obj` and VC6 returned C1083 while
opening its output. AUX is a reserved Windows device basename, including with
an extension. Changing the experiment's output to `auxslots.obj` succeeds;
no source, compiler flags or native extent changed. Earlier independent CLI
attempts timed out at60 seconds under host load. The isolated public-API proof
used a180-second execution budget and kept those failed receipts. Neither
failure was a measured byte mismatch or a reason to alter STATUS.
Receipts: .scratch/goal42/prove-reserved-name.log,candidate-*.json and
prove-candidate.log.
