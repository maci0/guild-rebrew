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
