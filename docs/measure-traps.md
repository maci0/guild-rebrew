# Measure traps — the method's own failure modes

These cost as much as the codegen walls, and most of them were learned by being burned.
For what the compiler itself blocks, see `codegen-walls.md`.

Companion reading: `msvc6-c-shapes.md` (front-end shapes), `msvc6-allocator.md`
(register allocation and slot maps), `TODO.md` (round-by-round history).

---

## 1. Only the linked residue decides

Object metrics are proxies and have pointed the wrong way repeatedly — at least six
recorded instances, including one where the *positional* metric (`aligned`) picked the
losing candidate by 3 linked bytes, and one where `matched` rose by 6 while the link fell
by 1. But they are not useless: on `CrashDump`'s V2 the object metric was much worse *and
so was the link* (+131), because the mechanism — a 59-byte shortfall displacing the
function's own jump tables — was understood. **The rule that survives: neither accept nor
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
`gm_AllocSpieler`'s ceiling is ~3115 of 3689 — the distance from 736 was never reachable.

A recognition that some residue is unreachable by any code edit — the one-sided
relocation bytes (`cm_ExProdObjekt` 92, `cm_ProcessCommandQueue` 40, `gm_AllocSpieler`
~574). Byte-identity in the *linked image* is what the objective measures, and those bytes
already match there; the metric simply cannot see them.

## 4. A residue number is not the size of the error

It is the distance from the first divergence to the end of the function. `gm_AllocSpieler`
is 2,861 differing bytes over a 3,689-byte function *with a two-instruction deficit*; one
early encoding of a different length shifts everything after it. But the ratio does not tell
you *which* of three causes you have: a length cascade, a frame **value** difference (which
changes every `esp`-relative operand and no length at all — `sub esp,0x28c` vs `0x280` are
both 6 bytes), or genuinely distributed differences. `scripts/gaptrace.py`'s **curve shape**
discriminates; the ratio does not.

A high residue was once read as "one early encoding shifts the tail", sent to two agents as
a mission brief, and both refuted it with measurements — `CrashDump`'s first differing byte
is a frame *value*, and `gm_AllocSpieler`'s gap returns to 0 repeatedly across 168 hunks. Two
agent budgets were spent at a cliff that was not there.

**The run-length histogram is the cheap discriminator (round 839, whole tree).** Count the
contiguous differing runs between built and reference `.text` and look at their lengths.
Measured on the current tree: **610 runs over 8,634 bytes, median 5, mean 14.2, longest
189, and 254 of them exactly one byte.** That shape rules *out* a single early length
cascade — a cascade produces one long run from its start to the next realignment, not 254
scattered singletons — and rules *out* "one frame value per function", because a frame
value changes every `esp`-relative operand in that function at once.

**Do not infer the cause from the most common short-run context.** The top of that list is
dominated by `mov eax,[esp+0x20]` vs `[esp+0x18]`, which reads as a frame-offset cascade.
Measured directly, the bytes attributable to an `[esp+disp8]` slot offset are **54 of
8,634** (0.6%). The frequent pattern was the most *visible* one, not the bulk — the same
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
  first instruction — the header lines eat the budget; use `head -12`.)
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
  shipped DLL measures **215/346** at that VA, and compiling with the pin gives `obj 346` —
  the reference's exact size — at `match` 171/346. The whole-tree residue is safe because
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
  `rebrew lint 2>&1 | tail -1` and echoed the line, with **no `rc=1` anywhere near it** — so it could
  never fail the gate, on an objective whose stated rule is "zero warnings is the only acceptable
  state". Two further traps in the same spot:
  - **`rebrew lint` exits 0 even when it reports warnings**, so testing `$?` would not have fixed it.
    The `N passed, E errors, W warnings` summary must be parsed.
  - **A failing lint can look like a different failure.** Injecting a broken `FUNCTION:` VA did make
    the gate fail — with `REGRESSION: 263 byte-matched`, because the bogus VA also demoted a function.
    The gate went red for the wrong reason, and a warning that perturbed nothing would have passed
    silently. **When a guard fires, confirm it fired for the reason you intended.**
  **Rule: falsify every guard against a state where it must fire, and check the attribution, not just
  the exit code.**
- **A probe that fails to fire is not evidence the guard is broken — check the probe first
  (round 908).** Three successive attempts to falsify one new check all "passed", and all three were
  the *probe's* fault: the entry was still inside the section, the TOML had a duplicate key so it
  never loaded, and a `str.replace` matched a different entry than intended. The guard was correct
  every time. **Before concluding a check is dead, confirm the input actually reaches it** — print
  the parsed row, not just the exit code. This is the mirror of round 907's finding (a real dead
  guard, where the *gate* was wrong); the two look identical from the outside and are separated only
  by inspecting the input.
- **Editing a file to change nothing is not a no-op (round 908).** A docstring-only edit to
  `data_extent_check.py` collapsed a line and produced
  `end = cur["va"] + cur["size"]        if end <= nxt["va"]:`. `ast.parse` caught it in one command;
  without that check it would have failed at runtime in the gate, where the symptom (`could not read`
  / non-zero exit) points at the tree rather than the tool.
- **A metadata size that crosses the next tracked symbol is wrong by construction — and the check is
  one command (round 905).** Sorting the sized `.data`/`.rdata` entries by VA and asking whether
  `va + size > next_va` found **exactly two** defects in the whole tree, both real, both invisible to
  three rounds of *type-conflict* analysis (902-904) because an entry can be internally wrong while
  agreeing with every other TU:  - `g_dynasty_field_48` typed `int`/size 4 at `0x10035448`, overlapping `g_dynasty_field_49` at
    `0x10035449`. The reference does `mov dl, byte ptr [0x10035448]` (`0x1001700f`) and
    `mov byte ptr [0x10035448], dl` (`0x10017130`) — **one byte**.
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
  - treating a *fully contained* symbol as benign — misses both round-905 defects, because a 4-byte
    `int` size swallowing a 1-byte neighbour is geometrically identical to a blob swallowing a view;
  - treating `extern` as evidence of a view — misses `g_entity_type_bytes`, because
    `g_stat_b_array` is `extern unsigned char g_stat_b_array[]`, a *separate object* that merely sits
    next door. **An `extern` declaration is not evidence of anything about ownership.**
  The working rule requires **positive** evidence of a view (a `#define` naming an offset) plus a
  verified allowlist of the gap blobs. **Lesson: a guard must be tested against a state where it
  should fire.** This one was written twice while the tree was already fixed, and both early versions
  would have shipped silently passing.
- **Metadata-only width corrections are byte-neutral; composition-budget changes are not
  (rounds 904-905).** Four such fixes have now landed — `locktable` 256→192, `g_dynasty_field_48`
  4→1, `g_entity_type_bytes` 4→1, plus round 900's type corrections — every one with residue and
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
  (round 904).** The same array's extent was needed twice — once misread by disassembly (above), and
  again a round later to justify a metadata fix. The second time it was cross-checked by scanning
  `.text` for immediates of the form `base + 0x10k`, which needs no control-flow reasoning at all:
  only `+0x0`, `+0x0c0` (the bound) and `+0x0d0` (the next object) appear, and **no `+0x100`**, which
  is what the old metadata claimed. **The check cost one command and would have caught round 903's
  error before it was written up.** When a fix depends on "how big is this object", get the number
  two ways.
- **A conflict report cannot express "two objects, one name, two consumers" (round 903).**
  `rebrew data` flagged `locktable` as `CRITICAL_SECTION*[0x40]` vs `CRITICAL_SECTION**`. Both are
  intentional: `data_globals.c` defines the array the binary's own cleanup loop walks, and
  `mlock.c` defines `CRITICAL_SECTION** locktable = __locktable` because **LIBCMT's `tidtable.obj`**
  (pulled in via `_getptd`) references `_locktable` as a `CRITICAL_SECTION**`. `_locktable` is
  verified present in `LIBCMT.LIB`. Third case this session where "fixing" a reported type conflict
  would have broken the link.
- **`rebrew data`'s type-conflict count is a signal, not a work queue (round 902).** Eleven entries
  looked like eleven mismatches to fix. Chasing them found at least three different situations, and
  the "fix" was wrong in two of the three:
  - **a real layout impossibility** — `loadsave3.c` *defined* five filter globals as arrays summing
    to 53 bytes inside a 16-byte span. Correcting them to scalars cleared 5 conflicts and was
    byte-neutral through `linktest.sh` (**+0**), but cost **+236 `.data`** at the gate. The array
    forms are load-bearing for the raw `.data` size, and only the gate's raw-link number sees it.
  - **a deliberate defining-TU choice** — `gm_NextEntityQueryMatch.c` "mismatched" 13 TUs on three
    globals because it is the file that *defines* them, and its own comment says the scalar types
    were chosen so the TU **emits BSS commons** ("Incomplete `[]` does not emit; sized arrays broke
    .text layout"). Correcting the types produced **14 `LNK2001` unresolved externals**. The comment
    predicted the failure exactly; it had to be read before probing, not after.
  - **genuine mismatches** — the remainder, which are actually wrong.
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
  was always right and no byte ever differed — but the declared type was wrong, and no code could
  have used it as a real pointer. **Consequence:** a `g_<hex>` name is not merely cosmetic debt; it
  suppresses the compiler's ability to check the declaration at all. Expect renames of
  CRT-named globals to surface C2040s, and fix the type rather than the name.
  **But the hazard is not universal (round 901).** Restoring `__pioinfo`, `_nfile` and `__nstream`
  on three more CRT globals compiled **clean on the first try**. It bites only where MSVC6 also
  declares the same identifier itself (`__argv`, `_pgmptr`); for names it does not,
  the rename is safe and the risk is ordinary. Do not assume every placeholder hides a type error —
  test, and check the build log rather than reasoning about which is which.
- **A header edit can push a TU over its composition span, and the symptom is an unrelated
  `LNK2001` (round 914).** Adding an include to `gv_MoveSlotEntry.c` grew its object **688 → 1008
  bytes (+320)**, past the padded span the split-link can place, and the build failed with
  `LNK2001: unresolved external symbol _gv_MoveSlotEntry` — a symbol whose declaration was perfectly
  fine. §6d's composition-budget mechanism normally arrives from a *code* edit; it applies just as
  well to headers, and it is invisible until the link because the TU compiles cleanly.
  **Three symptoms now point at the same underlying budget:** `LNK2001` for a symbol you did not
  touch, a `LONG <file>.c.obj` line in the pad report, and a `split_link FAILED` with no `error C*`.
  **Check `grep '<file>.c.obj' .scratch/gate-link.log` *before* lifting into a file, not after** —
  and note the report only shows files that are *already* over, so a file 300 bytes under its span
  can still be tipped over by a header.
- **A `LNK2001` naming a symbol you did not edit is a declaration mismatch, not a missing definition
  (round 914).** Round 913 saw thirteen of them for `_s_ahm_AllocAhmInfo_1002a0f8`,
  `_ahm_QueryEntityBuildingType` and `_ahm_AllocateEntitySlot`, and recorded the cause as unknown.
  Each was a **return-type disagreement** between a caller's `extern` line and the defining TU —
  `int*` against `int`, `void` against `int` — and each was decidable from the reference rather than
  by preference (`0x1000c6a0` returns `ahm_LookupEntityInTable`'s `eax`, a pointer). **The diagnostic
  is cheap:** for each unresolved name, `grep` every declaration and the definition, and compare
  return types. This is round 911's `gm_ResetAllEntities` class, and it recurs wherever two TUs
  declare the same function independently — which is the norm in this tree, since the original kept
  declarations local.
- **A metadata note can be confidently wrong, so identify a symbol from its use sites (round 901).**
  `0x11766564` was noted as "tracked-block (stream) table ptr" and is in fact `__pioinfo`, the CRT
  per-handle file table — established from `mov eax,[__pioinfo]; mov eax,[eax + esi*4];
  test byte [eax+0xc],0x83` at `0x1001ad4b`, not from the note. `0x11766560` was noted as "current
  stream count" and is a handle **bound** (`cmp esi,[_nfile]; jae`, init `0x20`). Two of three notes
  were wrong about what the symbol *is*, while both were right that something was there.
  Disassemble the use site before naming; a note is a lead, not evidence.
- **A hand-rolled struct-size calculator reports garbage on this tree — use the compiler instead
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
  `gz_stream`'s check failed until `-I references/zlib` was added — the assertion never compiled,
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
  "is this a relocation?" heuristic only moved the count around (241 → 158 → 121 unexplained) —
  the clearest sign the *instrument* was wrong rather than the data. Checked with the tool:
  `rebrew verify` reports **0 entries with a nonzero delta**, and `rebrew test` on one of the
  "suspects" returns `match_count 179/179, mismatches []` with `reloc_count 12`. The metadata
  is consistent; the raw diff was not.
- **A field-offset histogram cannot type a struct, and merging two histograms invents a layout.**
  Round 893 collected every `slot + 0xNN` offset in the tree (98 distinct, `0x170` alone in 12
  files) and merged it with the field map written in `spiel62.c`'s header. The merge *collided* —
  `parent_index` (2 bytes at `0x27`) ran into `season_born` at `0x28` — and the tempting reading
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
  which struct they belong to — same-base offsets from different functions may not share a base;
  (2) when two field maps collide, disassemble the *producer* of the pointer (here, the call that
  fills `eax`) before deciding which map is wrong; (3) a half-remembered regex is not a negative
  result — `mov [r+0x28],r32` appeared absent because the pattern only matched the `disp8`
  encoding, and the store exists.
- **A type defined in a header is not a type in use.** `EntityStruct` (`game/entity.h`) is declared
  with `// SIZE 0x21c` and referenced **three times tree-wide — its own definition and two
  comments**. `entity.h` is included by 9+ TUs, but only for its `extern` globals. Do not count a
  header type as "the layout is defined"; grep for *instantiations and member accesses*, which is
  zero here. The same check applied to `PlayerSlot` gives 13 references and is real.
  **Use the tool's own masked comparison.** `rebrew test`/`verify` already implement "equal
  after masking relocations" — do not re-derive it by hand from a prelayout copy. If a raw
  comparison against `build/server.dll` is wanted instead, that file is the *post*-postlink
  output and its bytes are comparable; the prelayout copy is not.
  **The whole-`.text` total is also wrong from the prelayout copy: it reads 50,296 against the
  shipped file's 8,634** (round 863), because every unresolved relocation counts. So the
  prelayout copy is not an oracle for a per-function residue *or* for the tree total — only
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
(`0x10019720 + 400 == 0x100198b0`) — that is the ground truth, not either inventory.

## 6c. Object size can move toward the target while the link moves away (round 868)

`gm_FindNextFilteredEntity` (`0x10016f80`) is 4 bytes short of the reference: object **342**
against target **346**, and the deficit is a *missing block* — 8 instructions the reference has
and we do not (`jne` + a full epilogue: `xor eax,eax` / store / four pops / `ret`). The reference
reaches **one shared epilogue via a `cl`-flag jump**; we emit a private return at each early exit.

Routing the offending early `return 0;` through the shared tail (`match = 0; goto done;`) moves the
object **342 -> 347** — past the target by one, i.e. the size gap closes. At the link it is
**+114 worse** (`gm_FindNextFilteredEntity` 215 -> 329, `.text` 8,634 -> 8,748).

So "the object size now matches" is not evidence of progress, and on this function it is
positively misleading: the same edit that fixes the size adds 114 residue bytes, because the new
`goto` re-lays the block graph and the shared tail stops being reachable the way the reference
reaches it. **Measure at the link or do not claim a direction** — this is the concrete case behind
the AGENTS.md warning that the two object rulers disagree with each other and with the link.

## 6d. 28 objects are over the composition budget, and that is what makes source edits collapse (round 870)

> **CORRECTION (round 916): the `LONG` label does not mean "over the budget".** Measured against the
> objects' *actual reference spans* (next tracked VA minus this file's first VA), **zero of the 25
> checkable `LONG` objects are over** — 23 sit *exactly* at their span and two (`vfs2.c` −288,
> `vfs_OpenStream.c` −48) are **under** it, i.e. have room to spare. The pad report's `want` is the
> raw sum of metadata sizes, while the object is the **per-function-16-byte-padded** sum; for
> `spiel62.c` those are 1328 and 1408, so the report printed `+80 over` for a file that is exactly
> at its span. Verified on all 25: `per-func-pad == objtext` for every one. **Do not treat a `LONG`
> line as "this file cannot absorb a change"** — compute the span. See the new section below for the
> corrected test. The historical text is kept because the *mechanism* it describes is real; only the
> count and the inference are wrong.

`scripts/split_link.sh`'s pad step prints one line per object it cannot fit. On the current tree it
prints **28 `LONG` lines**:

```
spiel_dumpD.c.obj: 1040 > 1024 (+16 over the padded span; want 1015) -- not padded
ErrorModule2.c.obj: 528 > 496 (+32 over the padded span; want 494) -- not padded
trees.c.obj: 6464 > 1088 (+5376 over the padded span; want 1083) -- not padded
```

**But the total is 816 bytes, not 6,671 — three of the 28 lines are a reporting artifact
(round 871).** `want` is summed from the metadata's per-function sizes, and **zlib's sources carry
no `// FUNCTION:` markers at all** (0 markers in all 18 files under `references/zlib-1.1.3/`), so
for `trees.c`, `infblock.c` and `infcodes.c` the padding target collapses to whatever little the
metadata happens to know. `trees.c` reports `+5376 over` while its object is **exactly the span
between its own VAs** (`0x10008800 - 0x10006ec0 = 6464`), i.e. it is not over at all. The script's
own docstring warns about this at the `want` computation ("`want` is only as complete as the
metadata ... and then `want` understates the reference span").

Split correctly: **25 game files, 816 bytes of genuine overage**, against **3 zlib files, 5,680
bytes of phantom overage**. Read the game lines; ignore the zlib ones.

**Only SHORT objects can be padded** — `pad_short_functions.py`'s own docstring says a longer one
"cannot be cut without losing code". So for these 28 files the composition has *no slack*: any
edit that grows the object, and on a file already over budget even an edit that keeps its size,
moves the symbols after it.

That is the mechanism behind three rounds of failures. Round 869's `gm_FindNextFilteredEntity`
change took `spiel_dumpD.c.obj` from 1015 to 1024 bytes and the link reported "COMPOSITION
COLLAPSED: only 0 symbols landed at their reference VA" — because that file was **already 16 bytes
over**, so the composition had nothing left to absorb. The same applies to `LONG` file-mates in
`ErrorModule2.c`, `vfs.c`, `vfs2.c`, `infblock.c` and 23 others.

**Practical consequence, and the check to run first:** before reshaping any function, look up its
file in the pad report (`grep '<file>.obj' .scratch/gate-link.log`). A `LONG` line means that file
cannot absorb a size change at all and the only adoptable edits are ones that *shrink* it by at
least the stated overage. A file with no line either is within budget or was padded.

> **This inference is superseded by the round-916 correction above.** A `LONG` line does *not* mean
> the file is over budget — 23 of the 25 checkable `LONG` objects are exactly at their reference span
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

Rounds 868-870 were spent on `gm_FindNextFilteredEntity`, which is in `spiel_dumpD` — one of the
**three blocked** files. The right move was to work an unblocked carrier, and the check that would
have shown that costs one command. **Run it before choosing a function, not after a failed probe.**

## 6e. `cflags` in the metadata can crash the compiler on a CMake-flag-pinned file (round 877)

**Round 909 extension: the pins also make *header* changes unsafe, and a +0 single-symbol probe does
not generalise to them.** Lifting 27 duplicated globals into `entity.h` and deleting 145 local
`extern` lines was **+0 at the link on one TU** (`spiel62.c`), so it looked safe by the project's
usual standard. Scaled up it failed the gate: **`C1001: INTERNAL COMPILER ERROR`** as soon as
`ahm_ExAllocAlchemist.c` gained the include (the round-877 mechanism, on a *different* pinned file),
and **`LNK4006` duplicate definitions plus `LNK2001: unresolved _ls_LoadBuildingEntityState`** once
`ls_LoadBuildingEntityState.c` — the third pin — had its include graph widened. Restoring the two
pinned files individually did not help, because the damage is to *which objects define which
symbols*, not to either file alone.

**Rule:** the three sp5-pp-pinned files (`spiel_dumpD.c`, `ahm_ExAllocAlchemist.c`,
`ls_LoadBuildingEntityState.c`) should be excluded from any change that alters what a TU includes.
And note the shape of the mistake: `linktest.sh` measures `.text` residue, which an `extern` line
cannot move — so a passing probe says nothing about a build-graph change. **A +0 probe certifies the
axis it measured and no other.** See round 909 in `TODO.md`.

**Correction (round 878): the flags in this entry were misread.** `ls_LoadBuildingEntityState`
(`0x100128f0`) compiles with **`/O2 /Gd /REBREW_TOOLCHAIN:msvc-6.0-sp5-pp`** — the sp5-pp toolchain
pin only, **no `/Oa /Ow`**. Round 877 read a neighbouring file's flag tail. The mechanism this
section describes still holds (a CMake pin the metadata does not carry, and a `--cflags` write that
breaks the compile), but the specific flag pair does not belong to this file.

`os_LoadBuildingEntityState` (`0x100128f0`) compiles in the real build with
`/O2 /Gd /Oa /Ow /REBREW_TOOLCHAIN:msvc-6.0-sp5-pp`, set by `CMakeLists.txt` — it is one of the
three sp5-pp-pinned files. Its metadata carried **no `cflags` field**, and the docs record
`CMakeLists.txt` as the place where per-file flags live for exactly these files.

Persisting the same flags into the metadata with `rebrew test --cflags "/O2 /Gd /Oa /Ow"` — the
tool writes the field itself — makes `scripts/gate.sh` go **FAIL** with
**`fatal error C1001: INTERNAL COMPILER ERROR`** and a C1083. The identical flags appended to the
identical defaults work through the CMake path, so `/Oa /Ow` is not the problem: **the metadata
path and the CMake path do not construct the same command line, and only the CMake one compiles
this file.**

**Check `grep '<file>.c.obj:' -A40 build/CMakeFiles/server_dll.dir/build.make` before adding any
`cflags`**, and do not add a field that merely restates a CMake pin. Note also that
`rebrew-functions.toml` is mode 444 — reverting needs `chmod u+w` first.

**`rebrew test <file> --cflags <flags>` is a WRITE, not a measurement (round 919).** It persists the
flags into the tool-owned `src/rebrew-functions.toml` instead of testing in memory. Two sweeps left
the file dirty against `HEAD`, and because the CMake build consumes a separately generated table
(`build/rebrew-cflags.cmake`), the result *looked* like a real metadata/build divergence — `rebrew
data` reported `/Ox /Gd` for `gm_AllocSpieler` while the compile line carried `/O2 /Gd /Oa /Ow`. It
was my own probe. **After any `--cflags` sweep, `git diff src/rebrew-functions.toml` before drawing
any conclusion from a flag value**, and restore with `chmod u+w` first.

**`--cflags` also DROPS a per-file toolchain pin, so it cannot be used on the three sp5-pp files
(round 920).** On `ls_LoadBuildingEntityState.c` — whose CMake `COMPILE_OPTIONS` is
`/REBREW_TOOLCHAIN:msvc-6.0-sp5-pp` — the command printed `TOOLCHAIN persisted → msvc-6.0` and
proceeded to measure **a different compiler's output**. Every number from such a run is void, and
nothing in the output marks it as invalid. **The sound route for a pinned file is CMake:** append the
flag to that file's `COMPILE_OPTIONS` (`;`-separated — §6f), reconfigure, **grep the emitted
`build.make` line to confirm both the pin and the new flag survived**, then build and gate. That is
how `/Ow` was measured as inert on this carrier (residue 8,634 unchanged); the three `--cflags`
attempts that preceded it were measuring `msvc-6.0` and were discarded.

**A flag finding is per-carrier until measured otherwise (round 919).** `codegen-walls.md` §8 lists
`flags | flat | 12 axes, ~120 compilations`, and shapes §94 says `/Ow` is load-bearing on
`gm_AllocSpieler` while `/Oa` is inert. Both are true and neither generalises: re-measured,
`/O2 /Gd /Ow` and `/O2 /Gd /Oa /Ow` both score 1004/3689 while `/O2 /Gd` gives 493 — and the same
`/Ow` on `CrashDumpUnhandledExceptionFilter` scores **643/2115 either way, byte-identical**. So
"flags are flat" is a statement about *aggregate sweep results*, not a licence to skip a per-file
test.

**Round 913 correction: an sp5-pp pin does not make an *include* unsafe.** Round 909's
`C1001: INTERNAL COMPILER ERROR` appeared right after `ahm_ExAllocAlchemist.c` (a pinned file) gained
an include, and was recorded here as the pin interacting with header changes. It was not the pin.
Round 913 lifted `g_next_object_id` into that same file's include graph and built **clean, 0 errors**
— and round 911 then showed the real cause was a *wrong declaration* in `entity.h`
(`gm_ResetAllEntities` as `int` against a `void` definition). **The pin constrains the flags a file
compiles under; it says nothing about what it may include.** Do not exclude pinned files from
header work; fix the header instead.

## 6f. A dropped per-file flag produces a normal-looking measurement (rounds 879-880)
`set_source_files_properties(... COMPILE_OPTIONS "/A" "/B")` **silently drops `/B`** — CMake wants a
`;`-separated list. Configure succeeds, the build succeeds, `build.make` simply lacks the flag, and
any measurement taken is of a *different compile than the one intended*, with no error anywhere.
Round 45 nearly concluded "`/Oa` is inert" from exactly such a run.

**Check the generated command line, not the CMake source, before believing a flag experiment:**
`grep -A40 '<file>.c.obj:' build/CMakeFiles/server_dll.dir/build.make`.

The plumbing was audited afterwards and is otherwise sound: all three `COMPILE_OPTIONS` pins and
the zlib `COMPILE_FLAGS` reach their command lines, and of 57 files carrying metadata `cflags`, **0
real flags are missing** — the 48 apparent misses are all `/DREBREW_ALLOW_NAKED`, which
`C_DEFINES` supplies globally as `-DREBREW_ALLOW_NAKED=1`.

## 6f-bis. `COMPILE_OPTIONS` REPLACES a source's option list — adding a flag can silently drop a pin (round 942)

`set_source_files_properties(<src> PROPERTIES COMPILE_OPTIONS "/Ow")` **replaces** whatever
`COMPILE_OPTIONS` that source already had. It does not append. Three files in this tree carry a
per-file toolchain pin as `COMPILE_OPTIONS "/REBREW_TOOLCHAIN:msvc-6.0-sp5-pp"`, so adding a second
`set_source_files_properties` call for one of them **silently removes the pin** — the build succeeds,
the file compiles, and every measurement taken is of the wrong toolchain. Round 941's `/Ow` sweep did
exactly this to `spiel_dumpD.c` and `ahm_ExAllocAlchemist.c`, which is why part of that sweep's collapse
was not `/Ow` at all.

**To add a flag to a pinned file, put both in ONE list:**

```cmake
set_source_files_properties(
  "${PROJECT_SOURCE_DIR}/src/server.dll/.../file.c"
  PROPERTIES COMPILE_OPTIONS "/REBREW_TOOLCHAIN:msvc-6.0-sp5-pp;/Ow")
```

**And verify on the emitted command line, not in CMakeLists:**

```sh
awk '/<file>.c.obj: \/home/{f=1} f&&/rebrew-cmake-cl/{print; exit}' \
    build/CMakeFiles/server_dll.dir/build.make | tr ' ' '\n' | grep -E '^/(REBREW|Ow|O2|Gd)'
```

That must show **both** the old flag and the new one. A missing `/REBREW_TOOLCHAIN` is invisible to the
compiler — nothing warns, because the flag is consumed by `rebrew-cmake-cl` and stripped before the real
compile. Note also that `set_source_files_properties(PROPERTIES ...)` **with no source argument** is a
silent no-op; that is the shape that results if the source line is deleted from an existing pin while
trying to remove a duplicate.

## 6g. Two ways a whole-image instruction census lies, and both look like a finding (round 923)

A mnemonic census over both images is a good instrument — it converts "residue is 6% of `.text`"
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
  produced the image-wide figures **`or` -51**, **`adc` -43** and **`add` +108** — all filler, none
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
earlier rule — "the real body must equal the reference's" — was strictly stronger than the
composition requires and had been silently discarding admissible candidates.

## 8. probe-span vs test-real: two rulers, one truth

`probe_function` reports the padded COMDAT span as obj size (ExProdObjekt 1008, PCQ
640); `rebrew test` reports the real body (993, 639). Their match
counts differ accordingly (888 vs 976, 584 vs 624) — and test's
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
  "zero" on a tree that has six — and that log is exactly what the gate's compile check reads.
  **Rule: to count warnings, force a clean rebuild first; otherwise you are reading a cache.**
  Same family as the transient `C1083` below — a build log mistaken for a measurement.
- **A lone `C1083: Cannot open compiler intermediate file '<garbage>.tmp'` with no source location
  is the build harness, not the source (round 894).** It appeared in a `gate.sh` run immediately
  after a header change and read exactly like a compile-error regression introduced by that change.
  It is a **transient parallel-build temp-file collision**: re-running the build produced **0**
  errors and the gate then passed with all baselines held. The tell is the filename — `a00032gl`,
  not a path, and not a `.c` file — and the absence of any line/column. Before treating a C1083 as
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
  meaningless — round 889 measured **58,614** and then **116,814** from two such states, when the
  true value was 8,634. Worse, it is *sticky*: `git checkout` of the sources restores `verify`
  (281/283) but not the residue, so the tree looks reverted and still reports a false number. The
  recovery is to delete the split state and take a full gate pass:
  `rm -rf build/split_poc build/server.dll && bash scripts/gate.sh`.
  **The tell is `split_link.sh` printing `exactly at their reference VA: 0`** — the same
  composition-collapse signal `linktest.sh` refuses to measure through
  (`msvc6-c-shapes.md` §124). Treat any residue number taken without a fresh `postlink_residual.py`
  run after a source change as unmeasured, not as a regression.
- **A `cmake --build` also deletes the deliverable**, so a round that builds to test something and
  then compares residue is comparing a missing or stale artifact. Always rebuild the split state
  before reading residue; never carry a number across a bare build.
- **`rebrew verify --data` prints a `UserWarning` per `DATA` marker whose VA has no `name` in
  `src/rebrew-data.toml`, and the marker is then dropped from the inventory as `unknown`.** The
  warning text — "has no declaration on the following line and no name in the data metadata" —
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
  only, were skipped unconditionally, and all 20 turned out to be byte-identical — `matched` went
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
  compares zero against zero — a guaranteed match. Round 884 sized 57 `.data` symbols and
  `matched` rose 105 → 108, but **54 of the 57 are above `0x10035000`**: the rise is accounting,
  not verification. Before treating a data `matched` increase as evidence, check the symbol's VA
  against the section's raw extent. `.bss` and `.idata` entries are in the same category.
- **The built binary's `.text` / `.rdata` / `.reloc` VirtualSize already equal the reference's**
  (`0x22846` / `0x2e81` / `0x10374`). A size-mismatch hunt on this target is a dead end; the
  deliverable's remaining gap is *content* — 8,634 residue bytes inside `.text` — so measure with
  residue, not with section sizes.

---

## 10. How to check any claim in this document

- Residue and per-function numbers: `bash scripts/linktest.sh <one source>` against
  `.scratch/residue_base.log`, or regenerate with `scripts/split_link.sh` +
  `scripts/postlink_residual.py --write build/server.dll`.
- Frames, slot maps, prologues: disassemble `original/Server/server.dll` at the VA and compare
  with the built image (`instr_diff.py <va> --built build/server.dll`).
- Gap curves: `scripts/gaptrace.py <va> <source> _<symbol>` — **no size argument**.
- Slot maps: the sentinel-initial probe (`msvc6-allocator.md` Finding 60).
- Gate: `bash scripts/gate.sh` (lint + compile errors only + `verify --full` against a 281
  baseline). Expect the build's post-link step to fail; only `error C####`/`LNK####` count.

## 6h. An "undefined symbol" in this tree usually is not one — check `link_stubs.c` first (round 924)

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
externals**, among them a large `_s_..._1002xxxx` string family — e.g.
`_s_D__Develop_DieGildeAddOn_command_1002c748` is undefined in 12 places, and
`_s_amt_fio_LoadAemter____Can_t_load_10029f78` in one. That *looks* like the same bug repeated 20
times. It is not:

- **Those symbols are defined — in `src/link_stubs.c`, as 1-byte empty strings.**
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
authoritative answer was available the whole time and cost nothing — the link succeeds, `gate.sh`
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
`grep -rn '<symbol>' src/` and look for a non-`extern` line — `link_stubs.c` is where they live. A
symbol defined there as `[1] = ""` is finished work, not a defect; a symbol with *no* definition
anywhere is the bug. Distinguishing those two took most of this round, and the count difference is
the difference between a 1-item fix (done) and a 20-item vein (does not exist).

**One genuine residue remains in the neighbourhood:** `gm_Open.c` used the shared symbol at 11 sites,
and the reference does push one shared address (`0x10031004`) at every one of them — so the shape was
right and only the definition was missing. Rewritten to the `(char*) 0x10031004` cast the rest of the
tree uses for that string: **byte-neutral**, 11 undefined operands removed.


## 11. A stale operand can be a *consequence*, not a cause — read the fixer before chasing it (round 932)

Round 931 found an operand that read `[0x11766664]` (the stub region) where the reference reads
`[0x101de450]`, fixed the symbol name, and round 932 removed the duplicate definition that was
displacing it — and the operand **still** did not move. Disassembling `scripts/postlink_residual.py`
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
(`mov [esp+0x14],edi` vs `mov [esp+0x24],edi`). No missing code, no wrong instruction — different slot
numbers, which is allocator Finding 63's class.

**So: before treating a mismatched operand as the target, check whether the fixer would even accept a
rewrite there.** If the surrounding bytes differ, the operand is a readout of the divergence, not a
lever on it. The cheap test is the locality window itself — compare 12 bytes before and 16 after the
slot on both sides.


## 12. After a flag change, the CMake *objects* are stale even when `split_poc` is not (round 941)

`rm -rf build/split_poc` is the documented recovery for a collapsed composition, and it is **not
sufficient after a per-file flag change**. The objects themselves were compiled with the old flag, and
deleting only the split workspace leaves them in place. Measured: after reducing a `/Ow` sweep from seven
files back to one and deleting `build/split_poc`, the link still reported
`exactly at their reference VA: 0` and **"22 objects too long"** — because six objects still carried
`/Ow` from the previous build. Touching the sources did not help either; CMake rebuilt them, but other
objects from the swept set were untouched.

**The only reliable recovery is the full cycle:**

```sh
rm -rf build
cmake -B build --toolchain cmake/toolchain-msvc-6.0-sp6-docker.cmake \
      -DCMAKE_BUILD_TYPE=Release -DREBREW_DEBUG_INFO=OFF
rm -rf build/split_poc && bash scripts/split_link.sh
```

**The tell is the same as always** — `exactly at their reference VA: 0` and a residue above ~50% — and
the danger is that this state is *indistinguishable from a genuine composition failure*. If a flag
change appears to blow the budget, clean-rebuild before concluding anything about the flag.

**And two transient compiler errors to expect on a parallel rebuild:** `C1083: Cannot open compiler
intermediate file 'a00032xx'` and `C1001: INTERNAL COMPILER ERROR`. Both appeared on `-j4` and both
cleared on `-j1` / serial `TMPDIR=/tmp` rebuilds with no source change. Neither is a defect in the tree.
