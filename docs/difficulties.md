# Difficulties — why the last 6.5% of `server.dll` resists

A record of what was actually hard, what was measured, and what a future attempt should not
re-derive. Every claim here is tied to a function, an address, or a number that came from a
compilation or a link. Where a statement is a judgement rather than a measurement, it says so.

Companion reading: `docs/msvc6-c-shapes.md` (front-end shapes), `docs/msvc6-allocator.md`
(register allocation and slot maps), `docs/TODO.md` (round-by-round history and the CURRENT
STATE block at the top), `docs/behavioral-verdicts.md` (per-function behavior verdicts).

---

## 1. What is actually left

At the end of the last working session the deliverable was `build/server.dll`, **286,720 bytes**,
with **9,209 differing bytes in `.text`** (6.51% of 0x22846). Everything else in the PE is
**byte-identical**: `.data`, `.rdata`, `.reloc` and the headers differ by 0, and the import
table is 100 entries matching the reference in set *and* in order. There is no `.idata`
section — imports live inside the already-matching `.rdata`/`.data`.

So 100% of the remaining work is **`.text` code generation**, spread over 18 functions. The
distribution is extremely top-heavy:

```
gm_AllocSpieler                    2861   31%
CrashDumpUnhandledExceptionFilter  1597
cm_ExSellObjekt                    1404
ls_LoadBuildingEntityState          728
cm_ExCopyEntityData                 462
gv_ExAllocGraveyardWorker           456
ServerMainThread                    367
gm_AllocGebaeude                    327
... 10 more, none above 250, plus 7 bytes outside every function
```

Session progress was 9,533 -> 9,209 (−324). That figure is the honest shape of the problem:
**hundreds of compile-and-measure cycles per tens of bytes**, because the remaining difference
is not missing code or wrong logic but the compiler's internal choices.

---

## 2. Compiler-level walls — the main obstacle class

These are not "hard to find" problems. They are places where the C language has no expression
that reaches the reference's encoding, and that was established by exhausting the spellings
rather than by giving up.

### 2.1 Register allocation and scheduling are not steerable from C

The single largest class. `msvc6` picks which local lives in which slot and which
callee-saved register by its own colouring, and the source has almost no influence.

- **Declaration order is inert.** Ten declaration/type permutations on
  `CrashDumpUnhandledExceptionFilter` are byte-identical (`int`/`unsigned` for `i`, `excCode`,
  `key`, `frameInfo`; `char`/`unsigned char szLine`; `space`/`fCanContinue` order; `int*
  pDwords`; `szSep[0x1c]`); only `char szLine[8]` moves anything, and that moves the frame.
- **Statement order is inert** for the two prologue zero-inits on `gm_CheckInventoryCapacity`
  (four orders plus declaration-initializer forms, normal and reversed — all inert; the
  scheduler hoists a list store into the slot the reference uses).
- **A slot *transposition* is a colourer tie, not a source property.** On `cm_ExSellObjekt` the
  reference and our object assign `[esp+0x14]`/`[esp+0x18]` and `[esp+0x1c]`/`[esp+0x20]` to
  opposite variables, with *identical per-slot access counts* and every block reading the same
  logical value. Declaration swap, all eleven rotations of the `= 0` initializer block,
  renaming, deleting a local, changing a pointee type — all byte-identical. Read the slot map
  with a **sentinel-initial probe** (allocator Finding 60) rather than guessing.
- **A whole function's residue can be one register rename.** `gm_ObjectsAvailble`'s entire
  28 bytes is `mov edi,esi` where the reference has `mov ebx,esi` (0x10016090), cascading to
  the row/inner pair. `ahm_ExAllocAlchemist` keeps its 0x300-stride counter in `edi` and the
  matrix address in `ebp`; the reference is exactly reversed, and nothing flips it.
- **`volatile` on a local is a per-variable fixed point**, not a dial (allocator Finding 61).
  On `cm_ExSellObjekt` the committed qualification is a local optimum on `matched`, object size
  *and* instruction count simultaneously; qualifying a neighbour instead pushes the object to
  2080, an upward bucket crossing. On `vfs_ReadCompressed`, one qualifier is a lever (−1
  linked) and its neighbour in the same five lines is load-bearing: making the whole tail plain
  collapses the frame (object 496 -> 480, matched 447 -> 21).
- **A callee-saved sentinel and a CSE can be one mechanism.** On
  `ls_LoadBuildingEntityState` the `ebp`-cached `-1` and the read loop's CSE vanish together:
  matched 645 -> 79. The 2-instruction form being chased is the *cheap* half of a decision.

**Why this is a wall and not a puzzle:** these are choices made after the C front end, over
information (live ranges, use counts) that the source cannot address. Every measured attempt
either did nothing or moved a different decision instead. `msvc6-c-shapes.md` §§52-61 and
`msvc6-allocator.md` Findings 52-61 catalogue the specific attempts.

### 2.2 `msvc6` merges byte-identical early-return epilogues unconditionally

The reference **does not merge**. On `gm_FindNextFilteredEntity` (0x10016f80) it keeps **five
`ret` sites**: three byte-identical short epilogues (`xor eax,eax; pop esi; ret` at `+0x17`,
`+0x27`, `+0x75`) and two byte-identical long ones (`+0x141`, `+0x155`). Each short one is
reached by a **2-byte** conditional jumping *over* an inline fall-through return. Our `/O2`
object keeps **two** `ret` sites with five `rel32` branches into one shared block.

The cross-jump is therefore **not** downstream of any difference between the exits — they are
byte-identical in the reference and it still does not merge them. Proof that it is not a shape
problem: a 352-byte standalone TU carrying the target's exact guard/loop structure reproduces
the reference's *prologue byte-for-byte* and still folds all three exits. `/O1`, `/O2 /Os`,
`/O2 /Og-` and `/O2 /Ot /Oy-` all fold too.

**Eight return spellings have been compiled across two passes and all are inert.** This is the
wall behind the recurring "the reference keeps N epilogues and we keep one" note in this
project's file headers (`msvc6-c-shapes.md` §74).

### 2.3 The `volatile` idiom has a direction, and a per-site wall

`volatile` on a 16-bit load selects `mov r16,[mem]; and r,0xffff`; a plain load selects
`xor r,r; mov r16,[mem]` (`msvc6-c-shapes.md` §52). **The direction is easy to get backwards** —
one pass was briefed with it inverted and spent 14 probes refuting the brief, not the mechanism.

Where the reference's form is the *masked* one, the lever is to remove the qualifier — and that
can be impossible, because the qualifier is often what holds the loop's register allocation.
On `gm_AllocSpieler` dropping it at the sympathy-loop reads produces exactly the reference's
local form and costs **362 matched bytes** (736 -> 374). Sweeping the qualifier *in* is worse
still: 736 -> 488/408/365 at 1/8/17 sites, and the full sets exceed the composition band.

Corollary that invalidated an earlier inventory: `and r,0xffff` site counts are **not** a length
signal. On that function both sides' real code is already exactly 3689 bytes, the gap curve
oscillates ±48 and returns to 0, and all four reference `xor`s are present — the "6 extra `and`,
4 missing `xor`" figure three passes worked from was a fixed-offset artefact.

### 2.4 Relocation accounting makes the object metrics lie about what is left

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

### 2.5 Address folding and strength reduction

- **`base + idx` always folds to one `[reg+reg]` operand.** Nineteen spellings on
  `gm_AllocGebaeude` — pointer cast, array subscript, two-step pointer, `idx << 6`, `(unsigned)`
  cast, `int*`-scaled, `&arr[..]`, named intermediates, split across two statements — all emit
  `mov cl,[eax+ebx]` (shapes §73). Confirmed at a **second** site on
  `gm_CheckInventoryCapacity`. Materialisation can be forced by giving the address a second
  read, but that flips `entity_index`/`in_list` (edi->esi, ->edi), moves `push edi` by 0x27 bytes
  and adds 7 instructions: one decision, not two.
- **`add R,R` where the reference has `lea R,[R+R]`** (4 sites on `gm_AllocSpieler`, 1 byte
  each) — strength reduction follows the value's *uses*, not the spelling (Finding 54).
- **FPU operand forms**: the reference emits `fsubr qword [const]` directly where we emit
  `fld qword [const]` then `fsub st(1)`, plus an extra `fstp st(0)`. On `gm_AllocSpieler` the
  two largest hunks (+160, +144) sit here, alongside a hoisted `slot+0x124`/`slot+0x128` FPU
  block that our object computes *before* the 14-iteration loop where the reference computes it
  after — ~8 instructions moved across the whole loop.
- **A constant-0 register CSE** on `CrashDump`: the reference emits `push 0` 49 times (2 bytes);
  we emit `xor edi,edi` once plus 31 extra `push edi` (1 byte), −26 bytes of push encoding.
  Spelling the zero as `(LPOVERLAPPED)0`, `NULL`, `(void*)0`, `(DWORD)0` is byte-identical — a
  register-allocator value choice, not reachable from C.

### 2.6 Flags are not a general lever

`#pragma optimize("a", on)` is a real lever at *specific* aliasing sites (shapes §44) but it
does not generalise: on `ahm_ExAllocAlchemist` it collapses the function (matched 714 -> 480,
object 1008 -> **1024**, past the admissible band) and `"w"` regresses (475); on
`cm_ExProdObjekt` it collapses 888 -> 279 and `"w"` regresses 871 with 22 diffs; on
`vfs_OpenStream` `"a"` gives 390 -> **83** with the object at 720 (tables moved). In every case
it also leaves the composition band, so it fails on layout as well as score.
`/Ot /Oa /Os /Og- /G6 /Oi /Ob1 /G5 /Ow` have been swept repeatedly on the large functions with
no win (`/G6` crashes to 135 at object 1056).

### 2.7 The largest measured win was forbidden by the constraints

On `gm_AllocGebaeude`, `__asm { nop nop nop }` used as a scheduling barrier measured
**matched 683 -> 830** and `matched-reloc` 823 -> 970 at an unchanged object size — because it
moved a global load across two instructions, flipping a forward branch rel8 -> rel32 and
realigning a 129-byte loop. The objective allows C only (except hand-written assembly the
*original* contained), so it was reverted. Measured cost of honouring the constraint: removing
just the barrier gives matched **377** (worse than HEAD) and a COMDAT of **1072** instead of
1088 — which moves the jump table and breaks the composition. **The entire +147 rested on the
barrier** (shapes §69). The same class of lever is unavailable everywhere.

---

## 3. Measurement difficulties — the method's own failure modes

These cost as much as the codegen walls, and most of them were learned by being burned.

1. **Only the linked residue decides.** Object metrics are proxies and have pointed the wrong
   way repeatedly — at least six recorded instances, including one where the *positional*
   metric (`aligned`) picked the losing candidate by 3 linked bytes, and one where `matched`
   rose by 6 while the link fell by 1. But they are not useless: on `CrashDump`'s V2 the object
   metric was much worse *and so was the link* (+131), because the mechanism — a 59-byte
   shortfall displacing the function's own jump tables — was understood. **The rule that
   survives: neither accept nor reject on a metric alone.**
2. **One candidate, one full rebuild, one number.** A batch attributes nothing. Two rounds of
   "wins" were later found to be layout shifts from *other* objects (a committed "−58"
   re-measured at +56).
3. **Never measure while agents write.** Two full-rebuild rounds returned 0/319 and 37%
   differing because several writers were active; the mechanism was misdiagnosed twice as
   compiler flags and a response-file difference before the real cause was found.
4. **A residue number is not the size of the error.** It is the distance from the first
   divergence to the end of the function. `gm_AllocSpieler` is 2,861 differing bytes over a
   3,689-byte function *with a two-instruction deficit*; one early encoding of a different
   length shifts everything after it. But the ratio does not tell you *which* of three causes
   you have: a length cascade, a frame **value** difference (which changes every `esp`-relative
   operand and no length at all — `sub esp,0x28c` vs `0x280` are both 6 bytes), or genuinely
   distributed differences. `scripts/gaptrace.py`'s **curve shape** discriminates; the ratio
   does not.
5. **Tool traps that produced wrong readings.**
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
   - `instr_diff` decoded without `skipdata` and halted on a stray byte, understating alignment
     for the rest of a function (one function went 618 -> 646 once fixed).
6. **The size rule has two branches, and mixing them discards good work.** `cl` pads each COMDAT
   to 16 bytes, so for an object with **no** relocated data after its code any real body at or
   below `16*ceil(size/16)` is composition-neutral, with **no lower bound**. If the object
   *does* carry a jump table or case map after its code, the **real** length binds and padding
   cannot protect it (`vfs_OpenStream`'s 8-byte shortfall was worth −36 linked). An earlier
   rule — "the real body must equal the reference's" — was strictly stronger than the
   composition requires and had been silently discarding admissible candidates.
7. **`cmake --build build` fails by design at the post-link layout step** with no
   `error C####`/`LNK####`, and `make` then **deletes `build/server.dll`**. The deliverable must
   be regenerated with `scripts/split_link.sh` + `postlink_residual.py --write`. Leaving the tree
   after a bare build means the artifact is simply gone.
8. **`rebrew verify --full` rewrites `src/rebrew-functions.toml`** (it demotes `SIZE_MISMATCH` to
   `STUB`) and the file is mode 444, so restoring it needs `chmod u+w` first.

---

## 4. Process difficulties — agents, concurrency, tooling

- **File ownership collisions.** Two rounds were broken by launching a fan-out without checking
  which files the running agents held. The protocol is now: call `list_agents`, diff the
  `running` set's file assignments against the new ones, and only then launch.
- **Agents cannot link-test** (link measurement is serialized), so they rank candidates on the
  object metrics that mispredict. Every delivery needs a coordinator link test — the bottleneck
  is measurement, not agent count.
- **Agents wrote scratch files into `src/`.** `CMakeLists.txt` uses `file(GLOB_RECURSE)`, so a
  probe file dropped there is compiled and linked as an extra object and moves every symbol
  after it. One appeared mid-link-test (it was transient and never reached the link, so the
  measurement held). The glob now excludes a leading `_`.
- **`git add -A` swept an unmeasured agent edit into a commit** once. Commit named paths only.
- **The instruments lived in gitignored `.scratch/`** while being the tools every agent was
  told to use — they would not survive a clean checkout. `ndiff`, `cdiff`, `gaptrace` and
  `reallen2` were promoted to `scripts/`, with the two that assumed the repo root as cwd fixed.

---

## 5. Errors made during this work, kept on the record

Recording these because each cost real budget and each is the kind of mistake the next attempt
would repeat.

- **A wrong size rule was enforced for many rounds.** "The real body must equal the reference's"
  discarded admissible candidates; the true constraint is the padded COMDAT. Correcting it
  retracted recorded rejections.
- **A cascade framing was inferred from a ratio and was wrong.** High residue was read as "one
  early encoding shifts the tail". It was then sent to two agents as a mission brief, and both
  refuted it with measurements — `CrashDump`'s first differing byte is a frame *value*, and
  `gm_AllocSpieler`'s gap returns to 0 repeatedly across 168 hunks. Two agent budgets were spent
  at a cliff that was not there. The three-cause table in §3.4 is the correction.
- **A mission brief inverted a documented mechanism.** An agent was told to *add* `volatile` to
  get the reference's `xor`/`mov` form; `msvc6-c-shapes.md` §52 says the opposite, and it is
  right. Fourteen probes refuted the brief. Read the doc before writing the brief.
- **A tool was blamed for what was my own invocation.** A `gaptrace` run with the metadata size
  produced "37 bytes too long, 20 extra instructions", which was reported as a finding before
  being recognised as an artefact of the truncated window.
- **An "instrument is broken" conclusion from one agent was itself wrong** — it accused
  `gaptrace` of comparing instruction offsets rather than bytes, and rebuilt it; the tool
  compares masked bytes and decodes both streams at the same base. The real defect was the size
  argument. Verify a tool complaint before acting on it.

---

## 6. Constraints that closed otherwise-promising options

- **C only, no `__asm`** except where the original had hand-written assembly. This directly
  forbade the largest measured lever found (§2.7, +147). One pre-existing `__asm` block-fill is
  admissible because the original contains a 24-byte hand-written fill prelude there.
- **Do not reverse zlib or LIBCMT** — they are linked in. (`rebrew lib-match` is the check;
  FLIRT finds only 9 of the 68 functions that turned out to be stock LIBCMT.)
- **Library code and the CRT region are out of scope**, so the crt-region objects' "LONG"
  reports and the split-symbol drift (73 of 319 split symbols were not at their reference VA
  when measured, up to +0x31c) are not the objective, and the drift costs little: the residue
  outside the 19 functions is **7 bytes** today (it was 20 before a pad-fill fix landed).
- **Correctness versus the metric.** One real bug (swapped `AnalyzeInstruction` arguments on
  `CrashDump`, which made the callee dereference `nInstr - 5`) was fixed at a **deliberate cost
  of 1 linked byte**, because byte-identity bought with semantically wrong C is a false match.
  Its companion (a dead stack-walk cursor) is documented with the faithful fix. Conversely a
  `volatile` byte-fitting change was accepted despite a pass recommending against it, because
  `volatile` changes no observable behaviour — the line is semantics, not style.

---

## 7. What would actually move the needle

Ordered by what the evidence says is most likely to pay.

1. **A way to steer the allocator.** This is the dominant obstacle (§2.1). Nothing in C has been
   found that controls which slot or callee-saved register a live range receives, yet a
   majority of the remaining bytes are exactly that choice. If a technique exists — a
   compiler extension, a source idiom, or a post-pass — it would unlock many functions at once.
2. **The original build's exact compiler or flag set.** The residual pattern (unconditional
   epilogue merge, the constant-0 CSE, strength reduction choices) suggests our `/O2 /Gd` is not
   precisely what produced the reference. `msvc6` SP6 is what is installed; the reference may
   have been built with a different service pack or a different `/O` combination per file.
3. **`CrashDumpUnhandledExceptionFilter`'s frame plus exact tables *together*.** No candidate
   achieved both: the exact tables at `0x72c`/`0x7ac` were reached by byte-fitting with
   `volatile` (frame 0x284), and the exact frame 0x280 came with a 59-byte-short body. If the
   allocator tie ever breaks the other way — an `esi`-homed `CreateFileA` cache and no zero
   register — both arrive together and `matched` should clear 600. Its per-segment lengths
   (315 / 343 / 653 / 522 / 3 = 1836) and the byte-accounting of the 59 are in `docs/TODO.md`.
4. **`gm_AllocSpieler`'s two live leads** (2,861 bytes, 31%): the `add R,R` versus
   `lea R,[R+R]` sites need a change in the *uses* of the value, and the 0xc slot-map
   assignment itself. Its frame is confirmed correct (`sub esp,0x41c`, prologue byte-identical
   for 48 bytes), so it is not a frame problem — do not re-open it as one.
5. **A recognition that some residue is unreachable by any code edit** — the one-sided
   relocation bytes (`cm_ExProdObjekt` 92, `cm_ProcessCommandQueue` 40, `gm_AllocSpieler`
   ~574). Byte-identity in the *linked image* is what the objective measures, and those bytes
   already match there; the metric simply cannot see them.

---

## 8. How to check any claim in this document

- Residue and per-function numbers: `bash scripts/linktest.sh <one source>` against
  `.scratch/residue_base.log`, or regenerate with `scripts/split_link.sh` +
  `scripts/postlink_residual.py --write build/server.dll`.
- Frames, slot maps, prologues: disassemble `original/Server/server.dll` at the VA and compare
  with the built image (`instr_diff.py <va> --built build/server.dll`).
- Gap curves: `scripts/gaptrace.py <va> <source> _<symbol>` — **no size argument**.
- Slot maps: the sentinel-initial probe (`msvc6-allocator.md` Finding 60).
- Gate: `bash scripts/gate.sh` (lint + compile errors only + `verify --full` against a 281
  baseline). Expect the build's post-link step to fail; only `error C####`/`LNK####` count.
