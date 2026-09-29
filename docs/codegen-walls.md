# Codegen walls: where C cannot reach the reference encoding

Places where the C language has no expression that reaches the reference's
encoding, established by exhausting the spellings rather than by giving up.

Companion reading: `msvc6-c-shapes.md` (front-end shapes that do work),
`msvc6-allocator.md` (register allocation and slot maps), `measure-traps.md`
(method traps that fake codegen signal), `TODO.md` (round-by-round history).

---

## 1. Register allocation and scheduling are not steerable from C

This is the default for **homes** (which callee-saved register, equal-count
slot transpositions). Statement and definition *order* can still move which
value is computed where (`msvc6-c-shapes.md` §84). Do not read this section
as "order never matters."

The single largest class. `msvc6` picks which local lives in which slot and which
callee-saved register by its own colouring, and the source has almost no influence.

- **Declaration order is inert.** Ten declaration/type permutations on
  `CrashDumpUnhandledExceptionFilter` are byte-identical (`int`/`unsigned` for `i`, `excCode`,
  `key`, `frameInfo`; `char`/`unsigned char szLine`; `space`/`fCanContinue` order; `int*
  pDwords`; `szSep[0x1c]`); only `char szLine[8]` moves anything, and that moves the frame.
- **Statement order is inert** for the two prologue zero-inits on `gm_CheckInventoryCapacity`
  (four orders plus declaration-initializer forms, normal and reversed, all inert; the
  scheduler hoists a list store into the slot the reference uses).
- **A slot *transposition* is a colourer tie, not a source property.** On `cm_ExSellObjekt` the
  reference and our object assign `[esp+0x14]`/`[esp+0x18]` and `[esp+0x1c]`/`[esp+0x20]` to
  opposite variables, with *identical per-slot access counts* and every block reading the same
  logical value. Declaration swap, all eleven rotations of the `= 0` initializer block,
  renaming, deleting a local, changing a pointee type: all byte-identical. Read the slot map
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
- **Typing a record is byte-neutral only when no index goes dead (rounds 897-898).**
  Replacing `char* p; p += 0xa9; *p == 0` with `EntityQueryRecord* p; p++; p->type == 0` landed
  **+0 linked** on `spiel5.c`'s `gm_SearchStruct` (39/39 before and after). The *same*
  transformation on `spiel6.c`'s `gm_SearchTable67` took it **obj 62 → 38, match 62 → 8**. The
  reference at `0x10017a70` keeps **both** the index (`inc eax; cmp eax,0x100`) and the pointer
  (`add ecx,0xa9`) and computes its return as `g_entity_ptr + i*0xa9` through a strength-reduced
  `lea` chain (`lea ecx,[eax*8]; add esi,eax; sub ecx,eax; lea ecx,[ecx+ecx*2];
  lea eax,[esi+ecx*8]`). Rewriting the return to the pointer directly makes `i` **dead**, so msvc6
  deletes the loop shape and 24 bytes with it.
  **The trigger is deadness, not the presence of index algebra**: round 897 first stated this as
  "an index used in the return expression", and round 898 measured a counterexample on itself:
  `spiel.c`'s `gm_ResetAllEntities` uses `i` in its address computation
  (`g_entity_ptr + i * 0xa9` → `(EntityQueryRecord*) g_entity_ptr + i`) and still lands at **+0**,
  because `i` also bounds the loop and therefore stays live. Three sites, one variable:
  no index (`gm_SearchStruct`) +0; index used and still bounding the loop (`gm_ResetAllEntities`)
  +0; index rendered dead (`gm_SearchTable67`) −24 bytes of code. **A type change is a codegen
  edit: measure every site with `linktest.sh`, never batch them.**

**Why this is a wall and not a puzzle:** these are choices made after the C front end, over
information (live ranges, use counts) that the source cannot address. Every measured attempt
either did nothing or moved a different decision instead. `msvc6-c-shapes.md` §§52-61 and
`msvc6-allocator.md` Findings 52-61 catalogue the specific attempts.

### 2. `msvc6` merges byte-identical early-return epilogues unconditionally

> **Superseded (round 1145):** the merge follows a `return` inside a loop; without one each guard keeps its own epilogue. See `msvc6-c-shapes.md` section 200.


The reference **does not merge**. On `gm_FindNextFilteredEntity` (0x10016f80) it keeps **five
`ret` sites**: three byte-identical short epilogues (`xor eax,eax; pop esi; ret` at `+0x17`,
`+0x27`, `+0x75`) and two byte-identical long ones (`+0x141`, `+0x155`). Each short one is
reached by a **2-byte** conditional jumping *over* an inline fall-through return. Our `/O2`
object keeps **two** `ret` sites with five `rel32` branches into one shared block.

The cross-jump is therefore **not** downstream of any difference between the exits: they are
byte-identical in the reference and it still does not merge them. Proof that it is not a shape
problem: a 352-byte standalone TU carrying the target's exact guard/loop structure reproduces
the reference's *prologue byte-for-byte* and still folds all three exits. `/O1`, `/O2 /Os`,
`/O2 /Og-` and `/O2 /Ot /Oy-` all fold too.

**Eight return spellings have been compiled across two passes and all are inert.** This is the
wall behind the recurring "the reference keeps N epilogues and we keep one" note in this
project's file headers (`msvc6-c-shapes.md` §74).

**A third instance, and the cleanest one, from round 970.** `gv_ExAllocGraveyardWorker`'s entry-search
loop is **instruction-for-instruction identical** between the two images across indices 99-118 --
except that **three branches target different addresses for the same code**:

| index | reference target | ours |
|---|---|---|
| 103 (`jle`) | `0x10011d77` | `0x10011cdb` |
| 116 (`je`) | `0x10011d77` | `0x10011cdb` |
| 118 (`jne`) | `0x10011d77` | `0x10011cdb` |

Both targets are the **byte-identical epilogue**
`pop edi; pop esi; pop ebp; mov eax,0xffff; pop ebx; add esp,0x10; ret` -- the reference keeps **two
copies** of it (`0x10011cdb` and `0x10011d77`, 0x9c apart) and routes the loop's three exits to the later
one; we emit **one** and fold all three into it. The folding is this section's mechanism, and it is
invisible to every positional ruler because **the instruction stream matches at every index** -- only the
`rel8` operands differ.

**This is also why the carrier's own header mis-diagnosed the row.** It records the residual as *"an
ecx<->edx role exchange … the loop is otherwise instruction-for-instruction identical, so this is a
register-naming difference, not a shape difference"*. The registers are in fact identical at every index;
what differs is **which copy of the epilogue three branches reach**. A stream diff that compares mnemonics
and operands cannot see it either -- it compares `jle` to `jle` -- so the check that finds it is
comparing **branch targets**, not instructions.

### 3. The `volatile` idiom has a direction, and a per-site wall

`volatile` on a 16-bit load selects `mov r16,[mem]; and r,0xffff`; a plain load selects
`xor r,r; mov r16,[mem]` (`msvc6-c-shapes.md` §52). **The direction is easy to get backwards**:
one pass was briefed with it inverted and spent 14 probes refuting the brief, not the mechanism.

Where the reference's form is the *masked* one, the lever is to remove the qualifier, and that
can be impossible, because the qualifier is often what holds the loop's register allocation.
On `gm_AllocSpieler` dropping it at the sympathy-loop reads produces exactly the reference's
local form and costs **362 matched bytes** (736 -> 374). Sweeping the qualifier *in* is worse
still: 736 -> 488/408/365 at 1/8/17 sites, and the full sets exceed the composition band.

Corollary that invalidated an earlier inventory: `and r,0xffff` site counts are **not** a length
signal. On that function both sides' real code is already exactly 3689 bytes, the gap curve
oscillates ±48 and returns to 0, and all four reference `xor`s are present: the "6 extra `and`,
4 missing `xor`" figure three passes worked from was a fixed-offset artefact.

### 4. Address folding and strength reduction

> **Superseded (round 1145):** a `volatile` load defeats the `[reg+reg]` fold, and counted index loops reproduce the reference's strength reduction. See `msvc6-c-shapes.md` section 200.


- **`base + idx` always folds to one `[reg+reg]` operand.** Nineteen spellings on
  `gm_AllocGebaeude`: pointer cast, array subscript, two-step pointer, `idx << 6`, `(unsigned)`
  cast, `int*`-scaled, `&arr[..]`, named intermediates, split across two statements, all emit
  `mov cl,[eax+ebx]` (shapes §73). Confirmed at a **second** site on
  `gm_CheckInventoryCapacity`. Materialisation can be forced by giving the address a second
  read, but that flips `entity_index`/`in_list` (edi->esi, ->edi), moves `push edi` by 0x27 bytes
  and adds 7 instructions: one decision, not two.
- **`add R,R` where the reference has `lea R,[R+R]`** (4 sites on `gm_AllocSpieler`, 1 byte
  each): strength reduction follows the value's *uses*, not the spelling (Finding 54).
- **FPU operand forms**: the reference emits `fsubr qword [const]` directly where we emit
  `fld qword [const]` then `fsub st(1)`, plus an extra `fstp st(0)`. On `gm_AllocSpieler` the
  two largest hunks (+160, +144) sit here, alongside a hoisted `slot+0x124`/`slot+0x128` FPU
  block that our object computes *before* the 14-iteration loop where the reference computes it
  after: ~8 instructions moved across the whole loop.
- **A constant-0 register CSE** on `CrashDump`: the reference emits `push 0` 49 times (2 bytes);
  we emit `xor edi,edi` once plus 31 extra `push edi` (1 byte), −26 bytes of push encoding.
  Spelling the zero as `(LPOVERLAPPED)0`, `NULL`, `(void*)0`, `(DWORD)0` is byte-identical: a
  register-allocator value choice, not reachable from C.

### 5. Flags are not a general lever

`#pragma optimize("a", on)` is a real lever at *specific* aliasing sites (shapes §44) but it
does not generalise: on `ahm_ExAllocAlchemist` it collapses the function (matched 714 -> 480,
object 1008 -> **1024**, past the admissible band) and `"w"` regresses (475); on
`cm_ExProdObjekt` it collapses 888 -> 279 and `"w"` regresses 871 with 22 diffs; on
`vfs_OpenStream` `"a"` gives 390 -> **83** with the object at 720 (tables moved). In every case
it also leaves the composition band, so it fails on layout as well as score.
`/Ot /Oa /Os /Og- /G6 /Oi /Ob1 /G5 /Ow` have been swept repeatedly on the large functions with
no win (`/G6` crashes to 135 at object 1056).

### 6. The largest measured win was forbidden by the constraints

> **Superseded (round 1145):** the barrier's effect is reachable from C with a `volatile` load (gm_AllocGebaeude 328 -> 19). See `msvc6-c-shapes.md` section 200.


On `gm_AllocGebaeude`, `__asm { nop nop nop }` used as a scheduling barrier measured
**matched 683 -> 830** and `matched-reloc` 823 -> 970 at an unchanged object size, because it
moved a global load across two instructions, flipping a forward branch rel8 -> rel32 and
realigning a 129-byte loop. The objective allows C only (except hand-written assembly the
*original* contained), so it was reverted. Measured cost of honouring the constraint: removing
just the barrier gives matched **377** (worse than HEAD) and a COMDAT of **1072** instead of
1088, which moves the jump table and breaks the composition. **The entire +147 rested on the
barrier** (shapes §69). The same class of lever is unavailable everywhere.

---

## 6b. The inline-asm zero-fill/memcpy prelude: measured cost of the constraint

Six sites in the tree (`server4.c`, `gm_AllocGebaeude.c`, `m_AllocTracked.c`, `m_alloc.c`,
`m_alloc2.c`, `vfs_ReadData.c`) carry the same hand-written align-up block-fill:

```
lea ecx,[edi+edi*2] ; and ecx,3 ; sub ebx,ecx ; jle L
rep stosb ; mov ecx,ebx ; and ebx,3 ; shr ecx,2 ; rep stosd ; L: add ecx,ebx ; rep stosb
```

**The shape is confirmed unreachable from C, re-derived 2026-09-17 rather than cited.** Compiling
the exact call shape under `/O2`, `/Oi`, `/O2 /Oi`, `/Ox`, `/O2 /Ow`, `/O2 /Oa` and `/O1` gives
`shr ecx,2; rep stosd; and ecx,3; rep stosb` in every case: never the align-up prelude. The
reference at `0x1000b040` contains the prelude verbatim.

**Measured cost of removing them, through `gate.sh` (round 889):**

| metric | with asm (shipped) | asm removed |
|---|---|---|
| verify passed | 281/283 | 277/283 |
| byte-matched | 264 | 260 |
| residue | 8,634 | **116,814** (+108,180) |
| raw-link `.data` | 21,836 | 21,842 |

**108,180 bytes is 12.5x the entire remaining residue.** Three functions go SIZE_MISMATCH (short):
`srv_InitBuildingTypeTable` 372 to 358, `m_init` 162 to 143, `m_PoolAlloc` 270 to 248.

**Judgement, marked as judgement.** The objective's asm clause permits asm "only when certain the
original game source used raw asm at the same site," with "a code shape no MSVC6 C output can
produce" as the example of positive evidence. That condition is satisfied here: measured, not
assumed. But the *writer* was almost certainly the compiler vendor, not the game: the same 24-byte
idiom at six independent call sites is a CRT `memset` expansion, and the enclosing function is not
library code (`rebrew lib-match --stock-lib LIBCMT.LIB --va 0x1000b040` reports "Safe to reverse").
So the strict reading of the clause and the byte objective pull apart, and the cost of choosing the
strict reading is 108,180 bytes.

**DECIDED (round 984, by the user): keep the asm.** The clause's "a code shape no MSVC6 C output can
produce" is treated as sufficient positive evidence on its own, without requiring that the *original
author* hand-wrote it. Recorded so this is not re-litigated: the six sites stay, the residue baseline
stays at 8,628, and no round should re-open the question of removing them to satisfy a strict reading
of "the game wrote asm".

> **Correction (round 984).** The sentence above says "the same 24-byte idiom at six independent call
> sites is a CRT `memset` expansion". **That is wrong on the mechanism, and the conclusion survives it.**
> The VC6 CRT source is in the local cache and readable:
> `rebrew/.cache/gh-org/msvc600_sp3/VC98/crt/src/platform/memset.asm`. Its align-up code is
> `neg ecx` / `and ecx,3` / a **byte loop** (`adjust_loop: mov [edi],al / inc edi / dec ecx / jnz`),
> then `shr ecx,2` / `rep stosd`. The reference's prelude is different:
>
> ```
> 0x1000b057  lea ecx,[edi+edi*2]   <- edi*3, not `neg`
> 0x1000b05a  and ecx,3
> 0x1000b05d  sub ebx,ecx
> 0x1000b05f  jle ...
> 0x1000b061  rep stosb             <- string op for the alignment bytes, not a byte loop
> ```
>
> `(edi*3)&3 == (-edi)&3` for every `edi` (verified 0..8), so it *is* an alignment computation, just
> written as a ×3 multiply, which msvc6 strength-reduces into `lea`. §6b's CRT attribution is
> therefore unsupported: **the idiom is not the CRT `memset`, and it is not a `memset` intrinsic
> expansion either** (three fresh probes this round under `/O2`, with the function's own
> `#pragma optimize("y", off)`, and with runtime `dest`/`size`, all emit `shr ecx,2; rep stosd;
> and ecx,3; rep stosb`).
>
> It is still unreachable from C, re-confirmed: spelling the alignment as `(-(int) d) & 3` emits
> `neg ecx; and ecx,3`, and spelling it as `(unsigned) d * 3u & 3u` is **canonicalised back to `neg`**
> by msvc6. So the prelude's `lea`-based form has no C source, and the 108,180-byte cost of removing
> the asm stands. §6b's *decision* is unaffected; its *evidence* was wrong, and the distinction
> matters because "a CRT expansion" would imply the game never wrote asm while "an unreachable
> strength-reduction" does not.

---

## 7. What would actually move the needle

Ordered by what the evidence says is most likely to pay.

1. **A way to steer the allocator.** This is the dominant obstacle (§1). Nothing in C has been
   found that controls which slot or callee-saved register a live range receives, yet a
   majority of the remaining bytes are exactly that choice. If a technique exists (a
   compiler extension, a source idiom, or a post-pass), it would close many functions at once.
   **The "source idiom" half is now measured empty**: see §8.
2. **The original build's exact compiler or flag set.** ~~suggests our `/O2 /Gd` is not
   precisely what produced the reference. `msvc6` SP6 is what is installed; the reference may
   have been built with a different service pack or a different `/O` combination per file.~~
   **CLOSED (rounds 458/163/503/842).** SP6 is confirmed (`rebrew toolchain detect`: profile
   `msvc-6.0-sp6`, aligned true, and its "pre-6.0 constant-hoist" signal is a documented false
   positive: 4 of the 5 sites reproduce under our own SP6 build and 3 are in zlib). The flag
   axis is flat on 12 axes / ~120 compilations. The SP5/SP5++ per-file axis was swept over all
   18 carrier rows with the population enumerated: **3 pins landed, 16 of 16 unpinned rows
   worse**. No fourth pin. Do not re-open.
3. **`CrashDumpUnhandledExceptionFilter`'s frame plus exact tables *together*.** ~~No candidate
   achieved both...~~ **Re-measured (rounds 835/840): the register homes are a *consequence* of
   the frame, not a lever on it.** The frame is the first divergence (byte 2), and the file
   header records 8 declaration permutations, 11 flag combinations and two named lanes already
   exhausted. Only 10 of its 595 mismatching instructions differ solely by `[esp+N]`; the other
   585 are scheduling. Do not reopen as a register problem.
4. **`gm_AllocSpieler`'s two live leads** (2,824 bytes, 33%). ~~the `add R,R` versus
   `lea R,[R+R]` sites need a change in the *uses* of the value, and the 0xc slot-map
   assignment itself.~~ **Both probed and closed.** The FPU-spill loop (the longest single
   residue run, 189 bytes at `0x10018be0`) collapses under either `volatile` form:
   `match` 1004 -> 570 and -> 553 (round 841). Its frame is confirmed correct
   (`sub esp,0x41c`, prologue byte-identical for 48 bytes), so it is not a frame problem;
   do not re-open it as one.

## 8. The measured floor of this constraint set

> **Correction (2026-09-25): 8,634 was not a floor.** The linked residue fell from 11,735 to
> 5,404 without touching a single codegen wall. Three causes, none a C-spelling issue: seven files
> defined functions out of VA order after the `src/Develop` reshuffle, and the linker places a
> translation unit's functions in source order (-2,945, plus -137 for m_alloc2.c's
> `#pragma optimize` pair); stale per-function flag pins (`gm_AllocSpieler` compiled `/Oa /Ow` while
> tuned at `/O2 /Gd`, -2,804; `m_AllocTracked` `/G6 /Oy-`, -69); and a CMake `COMPILE_OPTIONS`
> pin whose path the reshuffle broke, so `gv_ExAllocGraveyardWorker` silently lost its `/Ow` (-5).
> Every remaining byte is inside a carrier's own body. The section below is kept as the record of
> what rounds 833-843 measured; read its conclusions as "under the composition of that time".

Established 2026-09-17 after rounds 833-843, by exhaustion with the population stated at each
step rather than by assertion. **Under C89, MSVC6 SP6, `/O2 /Gd`, no asm, no naked, no `_emit`:
the whole-tree `.text` residue floor for this binary is 8,634 bytes**, all inside 18 functions.
(Round 924 lowered the *actual* residue to **8,633** and the raw-link `.data` differing count
from 21,836 to **21,481**. See §10. The 8,634 floor above remains the figure rounds 833-843
measured and is what those rounds' evidence supports; it is not re-derived here.)

The shape of that floor (round 840, whole tree): **610 contiguous differing runs, median 5,
mean 14.2, longest 189, 254 of them exactly one byte**, with the nine largest carriers holding
7,880 (91%) and the top two 4,407 (51%). Fragmented in position, concentrated in cause.

Every axis that could move it has been measured shut:

| axis | verdict | evidence |
|---|---|---|
| source spelling (operand form, declaration type, loop shape, guard form) | inert | shapes §84 and throughout; lands once, as a *statement order* change |
| statement/definition ORDER | the only lever that has ever landed | TODO rounds 254-431; round 841 |
| flags | flat, now enumerated per-file | 12 axes, ~120 compilations, 1 distinct score (round 458); **per-file audit round 943**: `/Ow` pays on 3 of 12 carriers (best -5 linked, worst **+485**), `/Oy` inert on the one second carrier tested, and the remaining axes have a ~96-combination sweep with zero hits |
| `#pragma optimize` per function | inert | 7 forms byte-identical on the largest carrier, with a working control (round 843) |
| service pack (sp5-pp per file) | closed | 18 rows enumerated, 3 pins, 16/16 unpinned worse (rounds 503/842) |
| compiler build | SP6, by elimination within the MSVC6 family | `rebrew toolchain detect` gives a **hedged** answer (its own `version_hint` reads "may be MSVC 4.x/5.0" and it reports 5 pre-6.0 constant-hoist sites), so the citation is weaker than "confirmed" implies. What actually settles it is round 502: `msvc-6.0`, `-sp1`..`-sp5` and `-win9x` produce **byte-identical objects** on a shared row (1149/2057 obj 2056), i.e. **the nine images are three generators**, and the project sits on the one that matches. Round 837's zlib cross-check is the corroboration. The residual risk is that the original was MSVC 4.x/5.0, which no image here provides |
| size gaps | net-negative to close | shapes §89 (5 bytes recovered, ~178 lost); §69 (4 bytes worth 327 matched) |
| `.text` content post-pass | contradicts the objective | link-layout §6: postlink's `.text` content "is largely ours"; copying it makes the bytes copied, not compiled |

The two mechanisms that *would* move it are both excluded by the constraints, not by effort:
a **scheduling barrier** (`__asm`, shapes §69, measured at +147 matched and off-limits by the
C-only rule) and a **backend cross-jump / instruction-selection control** (the
`cm_ExCopyEntityData` epilogue finding: 2 epilogues against the reference's 3, six probe
passes and ~20 spellings all leaving it at 2).

**Rounds 916-921 closed the four axes that remained open on the *method* side**, each by counting
rather than by impression, so none needs re-probing:

| axis | verdict | evidence |
|---|---|---|
| composition budget | **no object is over its span** | rounds 916: all 25 `LONG` objects re-measured; 23 exactly at span, 2 under, 0 over. The `LONG` label compares against the wrong baseline |
| per-file flags | **carrier-specific, nearly closed** | rounds 919-920: `/Ow` +511 on `gm_AllocSpieler`, +3 on `cm_ExSellObjekt`, **0** on `CrashDump` and on `ls_LoadBuildingEntityState` (the largest flag-free carrier, tested through CMake because `--cflags` drops the toolchain pin) |
| duplicated declarations | **15 symbols lifted, 0 bytes moved** | rounds 909-918; population measured at ~7 remaining, and lifting is provably inert |
| `volatile` zero-extend excess | **3 sites, located, both tested ones closed** | round 921: image-wide census `and r,0xffff` 16 vs 19 and `xor r,r` 556 vs 550; the sites are `0x10011f26`, `0x100190fb`, `0x1001934a` |

**The census trick generalises and is worth reusing:** counting an idiom image-wide on both sides
converts "the residue is 6% of `.text`" into "three instructions differ in form", which is a claim
that can be closed. `and`/`xor` was the first try; the same treatment is available for any idiom pair
the shapes doc names.

**Counted, round 922**: six pairs, three closed outright and one newly explained:

| idiom | REF | BLD | verdict |
|---|---|---|---|
| `lea r,[r+r]` | 7 | 7 | exact |
| `fsubr qword` | 26 | 26 | exact |
| `and r,0xffff` | 16 | 19 | 3 extra, all located (round 921) |
| `xor r,r` | 556 | 550 | the same 3, from the other side |
| `fmulp st(1)` | 4 | 7 | 3 extra, **placement not spelling** |
| `add r,r` | 583 | 593 | 10 extra; the idiom is too common in library code for a count to attribute |

The `fmulp` three are the instructive case. All four of the reference's sites appear at the same VAs
in my object; `gm_AllocSpieler` adds three at `0x10018f1f`, `0x10018f5d`, `0x10018f65`. Disassembling
both images shows why: at `0x10018f1b` both sides emit `fild [esp+0x10]`, then the **reference jumps**
while mine inserts `fmulp st(1)`: the reference performs the multiply later, as
`fmul dword ptr [0x100256b0]` at `0x10018f5e`. **A folded multiply, not a different form.** Shapes
§8a's documented `volatile`-alias remedy scores **606/3689** here and does not reach it. Recorded as
placement; do not re-spell it.

### 11. The residue's shape, quantified: and why the small carriers are not a shortcut (round 939)

The natural instinct when the big carriers are walled is to work the tail. Measured, that is a dead end,
and the population makes it obvious:

| band | carriers | bytes | share |
|---|---|---|---|
| top 5 (`gm_AllocSpieler` 2,823 · `CrashDump` 1,583 · `cm_ExSellObjekt` 966 · `ls_LoadBuildingEntityState` 671 · `cm_ExCopyEntityData` 462) | 5 | **6,505** | **75%** |
| the other 14 carriers | 14 | 2,128 | 25% |
| of which the 8 smallest (<=100 bytes each) | 8 | **327** | **3.8%** |

**Every one of the eight small carriers has a file header that already names its residual with a
mechanism and a probe history**: checked individually this round:

- `gm_CalculateProductionValue` (5 B): an adjacent `fxch st(1)` / `cmp [esi],0x17` pair swap, **closed
  at round 196** after ~330 compiles, with the four reachable classes enumerated: the x87-stack
  allocator picks the `fxch` fixup position from the *type* of the scaled operand, and that same choice
  decides whether the compare folds (3 B) or unfolds (4 B).
- `gm_CheckInventoryCapacity` (97) · `m_AllocTracked` (92) · `srv_LoadBuf` (49) · `gm_ObjectsAvailble` (25)
  · `vfs_ReadCompressed` (23) · `cm_ExProdObjekt` (21) · `cm_ProcessCommandQueue` (15): each header
  states its residual cluster and the variants rejected.

**So the tail is not unexplored; it is explored and closed, one file at a time, by rounds that wrote
the result down.** Re-walking it costs a round per carrier to re-derive a known answer, and the whole
band is worth 327 bytes. The only carriers worth a round are the top five, and each of those has a
measured wall: §81/§1 for `CrashDump` and `gm_AllocSpieler`, allocator Finding 63 for `cm_ExSellObjekt`,
shapes §122 for `ls_LoadBuildingEntityState`.

### 12. Only one residue carrier has room to grow (round 950)

Section 11 mapped the residue by function; `object_span_check.py` maps it by *budget*. Cross-referencing
the two gives the constraint that decides which edits are even admissible:

| object | span | text | slack | residue it carries |
|---|---|---|---|---|
| `vfs_OpenStream.c.obj` | 752 | 704 | **-48** | **238** |
| `srv_SeedRandom.c.obj` | 58 | 16 | -42 | 0 |
| `vfs2.c.obj` | 688 | 400 | -288 | 0 |
| `initterm.c.obj` | 418 | 71 | -347 | 0 |
| `sbh_pool.c.obj` | 7146 | 4556 | -2590 | 0 |
| `m_alloc2.c.obj` | 6080 | 704 | -5376 | 0 |
| *(all other carriers)* | n/a | n/a | **exactly at span** | 8,390 of 8,628 |

**Exactly one residue carrier -- `vfs_OpenStream` -- has headroom; the other five under-span objects carry
no residue at all.** Every other carrier sits precisely at its span, so *any* edit that grows it moves
every later symbol and fails the composition check. That is not a hypothesis: it is why `/Ow` on
`gm_AllocGebaeude` costs **+485** and on `vfs_OpenStream` collapses outright, while the same flag on
`gv_ExAllocGraveyardWorker` (at span, but net-shrinking) pays −5.

**Two consequences for targeting.**

1. **A carrier at its span can only be improved by a change that is size-neutral or size-reducing.** This
   is a hard filter that has been rediscovered by measurement several times (`gm_AllocGebaeude` +485,
   `vfs_OpenStream` collapse); apply it *before* probing, not after.
2. **`vfs_OpenStream` is the one carrier where a size-increasing change is affordable** -- and its
   header already records that every such variant was tried and is worse (the 701-byte size-correct form
   scores 277 against the shipped 450, and "`/G3`..`/G4` with `/Gd /Oy /Op` … so there is no CFLAGS
   lever"). So the headroom exists and is deliberately unused.

### 12b. Every one of the 19 carriers' divergence sites is already documented (round 978)

The round-975 first-divergence table made it possible to ask a question earlier rounds could not: **is any
carrier's actual divergence site undocumented?** Round 978 checked all 19 with
`scripts/whathas.py <va> --window 48`. Result: **none are new**. The one apparent exception was instructive.

| carrier | bytes | first divergence | documented at |
|---|---|---|---|
| `gm_AllocSpieler` | 2823 | `+0xaa` store sink across `rep stosd` | shapes §109: 17-variant sweep, closed |
| `CrashDumpUnhandledExceptionFilter` | 1583 | `+0x2` frame `0x280` vs `0x284` | shapes §81 frame rule |
| `cm_ExSellObjekt` | 966 | `+0x2c` slot displacement | allocator Finding 61 |
| `ls_LoadBuildingEntityState` | 671 | `+0x3c` branch target | §13 block placement |
| `cm_ExCopyEntityData` | 462 | `+0x30` branch target | shapes §124 |
| `gv_ExAllocGraveyardWorker` | 451 | `+0x107` branch target | §2 epilogue merge |
| `ServerMainThread` | 367 | `+0x3c7` branch target | §13 block placement |
| `gm_AllocGebaeude` | 327 | `+0x60` operand | §13 |
| `vfs_OpenStream` | 238 | `+0x36` `cmp [eax],0` vs `mov al,t` | §13 |
| `gm_FindNextFilteredEntity` | 215 | `+0x6` xor/test | §13 |
| `ahm_ExAllocAlchemist` | 198 | `+0xcc` `lea` accumulator | **the file's own header, lines 63-70** |
| `gm_CheckInventoryCapacity` | 97 | `+0x13` store order | TODO round 974 |
| `m_AllocTracked` | 92 | `+0x11` callee-save vs compare | allocator Finding 51 |
| `srv_LoadBuf` | 49 | `+0x50` store/arg order | in-source, round 956 |
| `gm_ObjectsAvailble` | 25 | `+0x10d` `ebx`/`edi` | §1 of this file |
| `vfs_ReadCompressed` | 23 | `+0x9a` clamp order | shapes §85, round 187 |
| `cm_ExProdObjekt` | 21 | `+0xcd` load hoist | §13 |
| `cm_ProcessCommandQueue` | 15 | `+0x37` arm order | in-source, 18 rounds |
| `gm_CalculateProductionValue` | 5 | `+0xe4` `fxch`/`cmp` swap | TODO: "CLOSED at its floor", 4 classes |

**The instructive exception: `ahm_ExAllocAlchemist`.** `whathas.py` reported *"no documented probe in 6
docs"* at `0x1000bebc`, which reads as an unworked carrier. It is not: the divergence is documented at
**`ahm_ExAllocAlchemist.c:63-70`**, in the file's own header comment rather than in `docs/`. The comment
names the exact instruction pair and the exact probe:

```
 * That fold and the `lea edx,[eax+eax*8]` vs `lea eax,[eax+eax*8]` split at
 * index 66 are both register-pressure consequences: in isolation a named
 * offset local, a base-pointer local and a regrouped `i*0x87*4` all emit the
 * candidate's form, so neither is steerable from the expression alone.
 * ... a `slot_off = slot_index * 0x21c` local shared by the guard, both
 * memsets and the two -1 stores, to force the target's single edx stride at
 * 0x1000bebb, 109;
```

So a per-file header comment is a **second store of probe history that `whathas.py` does not index**: the
tool searches `docs/` only. A carrier whose history lives in its `.c` header reads as fresh work, and an
agent that trusts the tool will re-run a probe already measured at 109 against a shipped 452.

**The check, before treating a carrier as unworked:**

```bash
python3 scripts/whathas.py 0x<va> --window 48     # searches docs/ only
sed -n '1,120p' <the carrier's .c>                # the per-file header is the other half
```

Small carriers resist this best: their whole history fits in a header comment, so it never needed a
`docs/` entry. Round 976 lost budget to exactly this: it probed `srv_LoadBuf` (`+0x50`) and
`m_AllocTracked`'s guard order, both already in-source, and measured +574 and +539.

### 13. The residue is fully attributed and classified (round 973)

Three questions have now been answered by measurement rather than by argument: *where* the residue is,
*whether* it is inside the functions it is attributed to, and *what kind* each carrier's divergence is.

**Where.** All 8,628 differing bytes, attributed per function:

```
0x21b4 of 0x21b4 differing bytes are inside the 19 functions `rebrew verify`
reports as not byte-matched; 0x0 are not
```

**Nothing spills outside the unmatched functions**: no pad, no inter-function gap, no table. And the
shipped `.data`, `.rdata`, `.reloc` and headers differ by `0x0` (section 9b).

**What kind**, by the round-971 branch-target census (`scripts/branch_census.py`):

| class | carriers | evidence |
|---|---|---|
| **block placement** | `gm_AllocSpieler` (21 target-differing branches), `ServerMainThread` (14), `cm_ExSellObjekt` (7), `CrashDump` (7), `cm_ExCopyEntityData` (8), `gm_AllocGebaeude` (4), `gm_FindNextFilteredEntity` (3), `ls_LoadBuildingEntityState` (2), `cm_ProcessCommandQueue` (2), `gm_CheckInventoryCapacity` (1) | a branch whose mnemonic matches but whose destination does not |
| **epilogue merge** | `gv_ExAllocGraveyardWorker` (3 branches to a duplicate epilogue 0x9c away) | §2 |
| **register-role rotation** | `vfs_OpenStream`, `ahm_ExAllocAlchemist`, `m_AllocTracked`, `srv_LoadBuf`, `gm_ObjectsAvailble`, `vfs_ReadCompressed`, `cm_ExProdObjekt`, `gm_CalculateProductionValue`: **zero** target-differing branches | Findings 62/63; verified on `gm_ObjectsAvailble` (a consistent `ebx`/`edi` exchange, 235 instructions both sides) |
| **statement order** | `gm_CheckInventoryCapacity` (1 target-differing branch, but that is *downstream*) | round 974: its actual first divergence is `list[2] = 0x12` placed differently; see below |

**Round 974 corrected one entry and it matters for how the census is read.** The table above was
assembled from each carrier's *first branch whose target differs*, which is not necessarily its first
divergence. `gm_CheckInventoryCapacity` has one such branch, so it was filed under block placement, but
its real first divergence is at `0x10019ee3`:

```
reference  xor ebp, ebp                     (in_list = 0)
ours       mov dword ptr [esp+0x18], 0x12   (list[2] = 0x12)
```

The source has `list[2] = 0x12;` early, between `base = ...` and `entity = ...`; the reference emits it
elsewhere. Moving it to the end of the initialiser block was probed and measures **8,628 -> 8,641 (+13)**,
so the shipped position stays.

**Round 975 replaced the proxy with the real signal.** Instead of the first target-differing branch, each
carrier's **first differing byte** is located and the instruction covering it is read from each side:

| carrier | first byte | reference | ours | kind |
|---|---|---|---|---|
| `_gm_AllocSpieler` | +0xaa | `lea edx,[edx+0x100358fc]` | `mov [ebp],bx` | different mnemonic |
| `CrashDump` | +0x2 | `sub esp,0x280` | `sub esp,0x284` | operand |
| `cm_ExSellObjekt` | +0x2c | `mov [esp+0x14],edi` | `mov [esp+0x24],edi` | operand |
| `ls_LoadBuildingEntityState` | +0x3c | `jle 0x10012dea` | `jle 0x10012de8` | branch target |
| `cm_ExCopyEntityData` | +0x30 | `jne 0x1000ed8e` | `jne 0x1000ed8c` | branch target |
| `gv_ExAllocGraveyardWorker` | +0x107 | `jle 0x10011d77` | `jle 0x10011cdb` | branch target |
| `ServerMainThread` | +0x3c7 | `je 0x10009827` | `je 0x1000982a` | branch target |
| `gm_AllocGebaeude` | +0x60 | `mov edx,[0x10030b6c]` | `mov [ebp-0xc],eax` | operand |
| `vfs_OpenStream` | +0x36 | `cmp byte [eax],0` | `mov al,[eax]` | different mnemonic |
| `gm_FindNextFilteredEntity` | +0x6 | `xor cl,cl` | `test eax,eax` | different mnemonic |
| `ahm_ExAllocAlchemist` | +0xcc | `lea edx,[eax+eax*8]` | `lea eax,[eax+eax*8]` | operand (register) |
| `gm_CheckInventoryCapacity` | +0x13 | `xor ebp,ebp` | `mov [esp+0x18],0x12` | different mnemonic |
| `m_AllocTracked` | +0x11 | `push esi` | `cmp eax,ebx` | **two instructions swapped** |
| `srv_LoadBuf` | +0x50 | `push eax` | `mov [ebp+0x2c],ecx` | different mnemonic |
| `gm_ObjectsAvailble` | +0x10d | `test ebx,ebx` | `test edi,edi` | operand (register) |
| `vfs_ReadCompressed` | +0x9a | `mov edi,eax` | `test eax,eax` | different mnemonic |
| `cm_ExProdObjekt` | +0xcd | `mov edx,[0x101de450]` | `mov ebx,[ebp+0x16]` | operand |
| `cm_ProcessCommandQueue` | +0x37 | `jne 0x1000ab08` | `jne 0x1000ab04` | branch target |
| `gm_CalculateProductionValue` | +0xe4 | `fxch st(1)` | `cmp [esi],0x17` | **adjacent pair swap** |

**This is the table to work from**, not the branch census: eight carriers diverge on something other than
a branch target, and three (`m_AllocTracked`, `gm_CalculateProductionValue`, and `gm_CheckInventoryCapacity`)
on something the branch census could not see at all.

**And `m_AllocTracked` is the sharpest example of the proxy's failure.** It has **zero** target-differing
branches, so round 973 filed it under register-role rotation, but its first differing byte is two
instructions **swapped in the prologue** (`push esi` before `cmp eax,ebx` in the reference, after it in
ours), which is *scheduling*, not register naming. Hoisting `g_alloc_counter++;` above the guard to
reproduce it was probed and measures **8,628 -> 8,699 (+71)**, so the shipped order stays; the file's own
header already lists the neighbouring spellings as inert.

**So the census classifies by the *first target-differing branch*, which is a proxy, not by the first
divergence.** That is still useful for partitioning the set (a carrier with zero such branches cannot be a
placement story) but it must not be used to order *work*: for a carrier with one or two target-differing
branches, read the actual first divergence: it may be a statement-order or instruction-form difference
that the branch census cannot see.

**Every class is walled, and each has a named mechanism rather than an exhaustion argument:** block
placement is the backend layout pass (§17 of the shapes doc; and `cm_ProcessCommandQueue` is closed by
proof: the target's join test is provably-true dead code); epilogue merge is §2; register rotation is
allocator Findings 62-65, whose sweep showed no source-level naming reaches the choice.

**Consequence.** A future round should not re-derive the map. The open question is not *which* carrier or
*what kind*, but whether any lever exists for a class whose every member has been measured, and for three
independent classes the answer so far is no.

**Read this as a limit of the toolchain-plus-constraints, not of the source.** Every function
compiles, links at the reference's exact VA, and the deliverable is byte-identical outside
`.text` (8,634 of 8,634 differing bytes are inside `.text`; `.data`, `.rdata`, `.reloc`,
headers all `differing 0x0`). Reaching zero needs a lever this constraint set forbids.

### 9. The residue is not a code-shape deficit anywhere (round 923)

The census of section 8 counted idiom *pairs*. Round 923 counted **every mnemonic** over the
whole image, which answers a different and prior question: is any function missing code?
No.

The instrument is `scripts/opcode_census.py`. Two things make it honest, and both were
learned by getting them wrong first:

- **Decode the object, not the linked image.** The linked build is position-aligned at
  *function* granularity, so decoding a function's `size` from the reference's VA reads the
  wrong bytes whenever our object placed that body at a different internal offset. Decoding
  `gm_AllocSpieler` out of `build/server.dll` this way reported 1,014 instructions and 52
  calls; the object holds **55** calls: the reference's own number. Alignment comes from
  `build/split_poc.map`, which is exact and regenerated every link.
- **Cut each body at its last `ret`.** A COFF `.text` section ends in jump-table and padding
  bytes that decode as plausible instructions: the reference's `0x09` filler reads as
  `or dword ptr [ecx], ecx` (50 of them after `CrashDumpUnhandledExceptionFilter`'s tables)
  and `gm_AllocGebaeude`'s tail reads as `adc ch, dh`. Counting those gave "-51 `or`,
  -43 `adc`, +108 `add`" image-wide. **All three were filler.** Filtering on a fully-decoded
  span is not enough to catch it: garbage also "decodes" end to end.

Measured, over the 102 functions both sides decode as real `push`-prologue bodies:

| metric | value |
|---|---|
| instructions, reference | 8,986 |
| instructions, our build | 8,989 |
| total difference | **+3** |
| Σ \|mnemonic count difference\| over all mnemonics | **13** |
| functions with any instruction-count difference | **1** |

The one function is `gm_AllocGebaeude` (0x100174d0), +3 instructions in 295.

**Consequence, and the reason this closes a vein rather than opening one.** 8,634 residue
bytes against a +3 instruction deficit means the residue is *not* unassembled or missing
source anywhere. It is encoding length, register choice and scheduling inside bodies whose
instruction counts already match, which is exactly the class sections 1-7 record as walled.
The remaining hypothesis that a large carrier is simply incomplete is now **measured false**,
so "this function is missing its tail" is retired as a lead. The file-local claim in
`gm_AllocSpieler.c`'s header ("no region is missing: the call sequences agree 55/55") is
correct after all; shapes §104's table stands.

**Reuse:** this script is the cheap whole-image audit. Run it after any change that could
alter codegen globally, and treat any function appearing in its final table as the only place
a code-shape story can still be true.

### 9b. "Byte-identical outside `.text`" is true of the *shipped file*, not of what the build produces (round 936)

The headline result reads "`.data`, `.rdata`, `.reloc` and headers all `differing 0x0`". That sentence
is correct about `build/server.dll` and **misleading about the build**, and the difference decides how
to read the whole objective. Measured on the current tree, the same command reports both numbers:

| section | shipped file | **raw link, pre-fixer** |
|---|---|---|
| `.data` | differing `0x0` | differing **21,481** (`0x53e9` of `0xe000`) |
| `.rdata` | differing `0x0` | differing **1,268** (`0x4f4`) |
| `.reloc` | differing `0x0` | differing **7,107** (`0x1bc3`) |
| `headers` | differing `0x0` | differing **267** (`0x10b`) |
| `.text` | differing `0x21b9` | differing `0x3810` |

**`rebrew postlink` writes those four sections from the layout package.** They are copied, not
compiled; the raw link produces 30,123 bytes the fixers overwrite. So the objective's "every data byte
matching" is satisfied **by construction**, and no measurement of the data sections can ever be
evidence about codegen. This is not a defect and it is not hidden (`measure-traps` §6h and the
`rebrew verify --data` warning both say it), but it belongs in this section too, because "the
deliverable is byte-identical outside `.text`" is the claim a reader arrives with.

**What it means for the objective's other clauses.** "Residue at zero" is a `.text` claim and is
unaffected. "Every data byte matching" is trivially met and should not be quoted as progress. The
honest single-number summary of this project is: **the deliverable matches the reference except for
8,633 bytes, all of them inside `.text`, and `.text` is the only section the build has to get right.**

### 10. A function-argument that was an undefined stub, found by reading the emitted operand (round 924)

The first residue movement since round 901, and it came from the section-9 instrument: decoding
*mnemonics* does not see it, but decoding **operands** does.

At `0x1000e12a` in `cm_ExSellObjekt` the reference emits `push 0x1002cc8c` (`68 8c cc 02 10`):
a relocated reference to the message string `"cm_ExSellObjekt(): Ziel-Besitzer ist kein
Gebaeude"`. Our build emitted `push 0x11766604` (`68 04 66 76 11`): a nonsense immediate.
The source line was

```c
LogMessageInternal("D:\\...\\command.c", 0x2e45, g_error_msg_sell_failed, 8);
```

and **`g_error_msg_sell_failed` is declared `extern char[]` at the top of the file but never
defined and never present in `src/rebrew-data.toml`.** An undeclared-in-practice array decays to
an address the compiler cannot relocate, so the push became an immediate. The other 11
`LogMessageInternal` sites in the same file pass **string literals**, which is what produces the
reference's relocated `push`.

Substituting the reference's own message as a literal:

| metric | before | after |
|---|---|---|
| linked `.text` residue | 8,634 | **8,633** |
| raw-link `.data` differing bytes | 21,836 | **21,481** |

Both improved, so both baselines were lowered. The `.data` gain is 355 bytes (much larger than
the `.text` gain) because the literal now participates in the merged string pool instead of
leaving a hole.

**Two lessons, both general:**

- **An `extern` declaration that has no definition is a silent operand bug.** `lint` passes (the
  header is well-formed), the compile passes (a warning at most), the object size is unchanged
  (`0x810` both ways), and only the *operand bytes* are wrong. **Grep every `extern char[]` in a
  file and check each one is either defined in the tree or in `rebrew-data.toml`.** This file
  alone carries 9 such declarations for strings at `0x1002cdxx`-`0x1002cexx`; the one that was
  *used* was the broken one, which is why it went unnoticed.
- **`.data` residue is invisible to a `.text`-only objective check.** The gate could not see this
  half of the win until round 863 added the raw-link `.data` ceiling. When a source change alters
  a literal's placement, measure both sections.

### 14. The `.data` axis is closed: the shipped file's non-`.text` bytes already match exactly (round 977)

The round brief routes work to `.data`/`.rdata`/`.bss`, types and structs. Measured this round, that vein
is **already empty in the deliverable**, and the round-977 numbers say so independently of `rebrew`:

```
$ cmp -l original/Server/server.dll build/server.dll | wc -l
8628
```

All 8,628 differing bytes are inside `.text`. Every non-`.text` byte already matches: confirmed three ways
that share no code:

| check | result |
|---|---|
| `postlink_residual.py`, shipped file | `.data` differing `0x0`, `.rdata` `0x0`, `.reloc` `0x0`, headers `0x0` |
| `cmp` over the whole file (above) | 8,628, i.e. exactly the `.text` residue 0x21b4 |
| `cmp` over `.data`+`.bss` alone (from `0x22846` to `0x174059c`) | **0** differing bytes |

**Why the round brief's `.data` framing is now a dead end.** `rebrew postlink`'s data fixer *copies* the
reference's `.data` wholesale: the baseline log records `0x7806` non-`.text` bytes overwritten per link.
So the raw-link `.data` figure the gate enforces as a ceiling (`21,481`) measures the **build's**
placement, not the deliverable's content. The objective's "every data byte matching" clause is satisfied
in the shipped file today; the raw-link number can only be driven to 0 by reconstructing the original's
`.data` COMDAT order, which is linker-hash-driven (documented at `CMakeLists.txt:443-448`) and not
reachable from C.

**Consequence for the remaining work.** The objective's only unmet clause is `residue at zero`, and the
residue is 100% `.text` inside 19 functions across the three walled classes in §13. `.data`, types and
structs cannot move it. A round that spends its budget on `rebrew todo`'s `start-data` list is spending it
on a vein that is already mined out.

**The `start-data` list itself.** `rebrew todo -c start-data -n 300` returns 207 items: 84 are `__imp_*`
IAT slots at the head of `.rdata` (`0x10024000`+), which are linker-supplied and not reversible; the other
123 are `extern`-only declarations whose addresses are already correct in `src/rebrew-data.toml`. Both
kinds show `status: "UNCHECKED"` and ROI 10.0 regardless of difficulty, so the list's ordering carries no
signal. See measure-traps §19.

### 12c. The fault-versus-symptom split, and the tool that makes it mechanical (round 979)

Section 12b said all 19 carriers are documented. It is worth making that claim *reproducible*, because it is
easy to reproduce wrongly: **looking up the symptom address instead of the fault address makes a closed
carrier read as open work.**

- **Symptom**: the lowest differing **byte**. On this tree it is usually a branch displacement or a
  displaced operand, i.e. downstream of the real fault. Its address frequently has no `docs/` entry, or only
  residue-table mentions.
- **Fault**: the first instruction whose `(mnemonic, op_str, size)` actually disagrees when both streams are
  walked from the function entry. That is the address to look up.

`scripts/fault_address.py` prints both columns for all 19 carriers, so the split is mechanical:

```
carrier                                symptom      FAULT        fault instruction
_gm_AllocSpieler                       0x100188fa   0x100188fa   lea edx, [edx + 0x100358fc]
_CrashDumpUnhandledExceptionFilter@4   0x10002772   0x10002770   sub esp, 0x280
_cm_ExProdObjekt                       0x1000e20d   0x1000e20c   mov edx, [0x101de450]
_vfs_ReadCompressed                    0x10008b2a   0x10008b2a   mov edi, eax
...
```

The two addresses usually coincide; they separate exactly where the fault is a size change that displaces
everything after it. Every fault address carries documentation:

| fault address | doc hits | | fault address | doc hits |
|---|---|---|---|---|
| `gm_AllocSpieler` `0x100188fa` | 7 | | `ahm_ExAllocAlchemist` `0x1000bebb` | 4 |
| `CrashDump` `0x10002770` | 33 | | `gm_CheckInventoryCapacity` `0x10019ee3` | 7 |
| `cm_ExSellObjekt` `0x1000d959` | 4 | | `m_AllocTracked` `0x10006591` | 18 |
| `ls_LoadBuildingEntityState` `0x1001292a` | 3 | | `srv_LoadBuf` `0x1000a5c0` | 2 |
| `cm_ExCopyEntityData` `0x1000ec2e` | 2 | | `gm_ObjectsAvailble` `0x1001607c` | 3 |
| `gv_ExAllocGraveyardWorker` `0x10011cf6` | 14 | | `vfs_ReadCompressed` `0x10008b2a` | 2 |
| `gm_AllocGebaeude` `0x10017530` | 3 | | `cm_ExProdObjekt` `0x1000e20c` | 1 |
| `vfs_OpenStream` `0x10009056` | 4 | | `cm_ProcessCommandQueue` `0x1000aaf6` | 6 |
| `gm_FindNextFilteredEntity` `0x10016f86` | 20 | | `gm_CalculateProductionValue` `0x10019804` | 5 |

**The two low-hit rows were checked by hand and both are covered**, in their own file headers rather than by
a standalone `docs/` section:

- `vfs_ReadCompressed` `0x10008b2a`: the clamp order, shapes §85 plus the round-187 closure in the file
  header ("three walls and nothing else; do not re-probe without a new allocator finding").
- `cm_ExProdObjekt` `0x1000e20c`, `src/Develop/DieGildeAddOn/command/command_c/cm_ExProdObjekt.c:147-160`:
  *"the dead store goes through a cast volatile pointer, which msvc6 treats as aliasing every global, so the
  global load is pinned below it"*, with ~50 measured variants all landing on the identical mismatch set
  (205-218, 223-224, 410). §91's sp5-pp screening independently calls this "the +204 global-load lane is
  scheduler-bound and retires".

So §12b's conclusion holds and is now checkable two ways rather than asserted.

### 12d. The 12b/12c coverage table partly counted itself (round 982)

Sections 12b and 12c tabulated "doc hits" per carrier fault address to argue that all 19 are documented.
**That count included the tables themselves**: `whathas.py` finds §12b/§12c because those sections list the
same addresses, so eight carriers' scores were inflated by the very tables making the claim.

Re-scored with `12b.`/`12c.`/`Round 97x`/`Round 98x` excluded, and cross-checked against each carrier's
**own `.c` header** (which `whathas.py` does not index, workflow-traps §8):

| carrier | fault | real doc hits | header probe-history markers |
|---|---|---|---|
| `_CrashDumpUnhandledExceptionFilter@4` | `0x10002770` | 34 | n/a |
| `_cm_ExSellObjekt` | `0x1000d959` | 32 | n/a |
| `_cm_ExCopyEntityData` | `0x1000ec2e` | 21 | n/a |
| `_gm_FindNextFilteredEntity` | `0x10016f86` | 19 | n/a |
| `_m_AllocTracked` | `0x10006591` | 18 | n/a |
| `_gm_AllocSpieler` | `0x100188fa` | 11 | n/a |
| `_gv_ExAllocGraveyardWorker` | `0x10011cf6` | 9 | n/a |
| `_vfs_OpenStream` | `0x10009056` | 6 | n/a |
| `_gm_CheckInventoryCapacity` | `0x10019ee3` | 6 | n/a |
| `_cm_ProcessCommandQueue` | `0x1000aaf6` | 5 | n/a |
| `_gm_CalculateProductionValue` | `0x10019804` | 5 | n/a |
| `_ls_LoadBuildingEntityState` | `0x1001292a` | 3 | **1** |
| `_gm_AllocGebaeude` | `0x10017530` | 3 | 10 |
| `_gm_ObjectsAvailble` | `0x1001607c` | 2 | 69 |
| `_ahm_ExAllocAlchemist` | `0x1000bebb` | 1 | 15+ |
| `_vfs_ReadCompressed` | `0x10008b2a` | 1 | 15+ |
| `_ServerMainThread@4` | `0x100096a8` | **0** | 8 |
| `_srv_LoadBuf` | `0x1000a5c0` | **0** | **16 passes** |
| `_cm_ExProdObjekt` | `0x1000e20c` | **0** | 15 |

**The three zero-hit carriers all have substantial in-header history**, and `srv_LoadBuf`'s header documents
**sixteen passes** of probes with the score of each. So the conclusion of §12b survives, but the *evidence*
for it was partly circular, and the corrected table shows that for 8 of 19 carriers the `docs/` count is
not the evidence at all.

**The practical reading: `docs/` hits under-count on this tree, and the under-count is largest exactly where
the work was hardest.** A carrier with a long header and a short `docs/` presence (small function, many
probes, no standalone section) is the normal shape for thoroughly-worked rows, not an unexplored one.
`scripts/preprobe.sh` prints both counts for this reason.

### 2 addendum: a fourth instance, with branch counts: `cm_ExCopyEntityData` (round 995)

§2 had three instances (`gm_FindNextFilteredEntity` five `ret` sites, `gv_ExAllocGraveyardWorker` two
byte-identical copies, and the recurring "reference keeps N epilogues" note). Round 995 found a fourth, and
this one is the clearest because the two epilogues are **not** byte-identical: they differ only in the
return value:

```
reference A @ 0x1000eda8   5f 5e 5d b8 01 00 00 00 5b 83 c4 0c c3
  pop edi; pop esi; pop ebp; mov eax,1;  pop ebx; add esp,0xc; ret

reference B @ 0x1000ef7b   5f 5e 5d 31 c0 5b 83 c4 0c c3
  pop edi; pop esi; pop ebp; xor eax,eax; pop ebx; add esp,0xc; ret
```

Everything after the return-value materialisation is identical, so msvc6 merges them; the reference keeps
both. **Branch counts in the reference: 4 branches reach A (return 1), 1 reaches B (return 0).** Our object
has **2 `ret` sites** where the reference has **3** (`0x1000edb4`, `0x1000ee48`, `0x1000ef84`).

Our surviving epilogue is byte-identical to reference B: it is not wrong code, it is a *missing copy*. That
is why this instance adds something the others did not: the earlier three involve byte-identical epilogues,
so a reader can suspect the difference is in the exits themselves. Here the exits provably differ by five
bytes and the compiler still folds them.

**No new lever.** §2 is closed with eight return spellings compiled across two passes, all inert, and a
352-byte standalone TU reproducing the reference's guard/loop structure that still folds all three exits.
This instance was found *by* `scripts/instr_diff.py` reporting `ref-only x4: pop R`, which is a cheap screen
for the class: **a carrier with `ref-only` `pop`/`ret` counts is an epilogue-merge instance, not an operand
problem.** Worth running before probing any carrier.

### 5 addendum: the `#pragma optimize` axis, swept on `ls_LoadBuildingEntityState` (round 996)

§5 records that flags are not a general lever, and the `#pragma optimize` letter axis has landed once
(`cm_ExCopyEntityData` pass 5: `"a", on` took 512 → 523, because **`/Oa` is not part of `/O2` or `/Ox`** and
the toml cflags apply per translation unit, so the pragma is the only way to reach it). Because that lever
*did* pay once, it is worth knowing whether it pays on the other carriers. Round 996 tested it on
`ls_LoadBuildingEntityState`, the carrier with the highest aligned-match rate of the four mid-size rows
(87.8%, 17 of 33 hunks same-kind) and, until now, **no `#pragma optimize` anywhere in the file**.

| pragma | residue | delta |
|---|---|---|
| none (baseline) | 8,628 | n/a |
| `#pragma optimize("a", on)` | 8,749 | **+121** |
| `#pragma optimize("y", off)` | 9,366 | **+738** |

Both reverted. `"y", off` is the letter that reproduced `server4.c`'s `[ebp-4]` slot and it is catastrophic
here; `"a", on` is the letter that landed on `cm_ExCopyEntityData` and costs 121 here.

**This is consistent with §5 and worth recording as a per-carrier fact rather than a general one.** The
`#pragma optimize` letter axis is not a lever that transfers: each letter's effect depends on the function's
own shape, and on these two carriers both of the letters that have paid elsewhere are large regressions.
Combined with the existing sweeps (`srv_LoadBuf`: `"a", on` → 180; `server4.c`: `"y", off` already applied;
`ServerMainThread`: `optimize("", off)` → 847), the axis now has a measured, mostly-negative answer on five
carriers.

**Do not sweep this axis again without a new reason.** The one case where it paid
(`cm_ExCopyEntityData`, /Oa) is documented and already in the source.

### 15. The asm clause has no applicant among the 19 carriers (round 999)

The user clarified the asm carve-out: raw asm is permitted where C cannot reach the shape: padding, single
instructions, the six memset preludes, never whole-function asm. That is a **narrower** permission than
"write the function in asm", and it is worth testing what it actually closes.

**It closes nothing among the residue.** The six existing asm sites are inside `srv_InitBuildingTypeTable`,
`gm_AllocGebaeude`, `m_AllocTracked`, `m_alloc`, `m_alloc2` and `vfs_ReadData`, and the functions that
*contain* those sites are already byte-exact. The 8,628 residual bytes live in 19 different functions, and
none of them is an instruction-shape problem:

| carrier class | count | is a single instruction unreachable from C? |
|---|---|---|
| register-role rotation | 8 | no: the instructions are all C-producible; the *register* differs |
| block placement / branch target | 10 | no: same instructions, different addresses |
| epilogue merge | 1 | no: same epilogue bytes, one copy folded away |
| **total with an asm-eligible shape** | **0** | |

The test for eligibility is not "is the byte wrong" but "**could a C compiler emit this instruction at this
site at all, in any spelling**". Every differing instruction in the 19 carriers is emitted by msvc6
*somewhere* in the same function: that is what the register-role and epilogue classes mean. An asm block
would be a whole-function escape, which the carve-out excludes.

**Screened by hunk count rather than file size, which is the efficient order.** The two closest to a
single-instruction fix are `cm_ExProdObjekt` (`0x1000e140`, 348/354 aligned, 3 hunks, `ref-only 0 /
built-only 0`) and `ls_LoadBuildingEntityState` (`0x100128f0`, 438/499, 33 hunks but only **1
different-kind**). Both probed this round, both **+0**:

- `cm_ExProdObjekt`: the three-instruction ordering hunk. Header records a *complete* enumeration: "all 112
  topological orderings of the seven statements … none beats 976". Genuine closure.
- `ls_LoadBuildingEntityState`: the `lea esi,[edx+ecx]` vs `[ecx+edx]` operand swaps are **`msvc6-c-shapes.md`
  §70**'s inert class ("operand order in a commutative address expression is inert"; the section number lives
  in the shapes doc, not here; codegen-walls has no §70, so a bare "§70" in this file reads as a dangling
  reference), and naming the `esi + 0x34` argument pointer to match the reference's `mov ecx,ebx; add ecx,edx`
  form is **byte-identical**: shapes §70's "this site was already at its optimum" reproduces. Re-confirmed
  round 1077: the swap sits at `0x10012944`, paired with the `jle 0x10012dea` / `0x10012de8` branch-target
  divergence at `0x1001292a` already carried in §33. Both are accounted for; the function yields no new lever.

**Conclusion.** The asm permission is a constraint clarification, not a lever. No carrier among the 19 has a
site where asm would be both permitted and useful.

### 16. The residue quantified by lever availability: 67.5% register-role, 32.5% placement (round 1003)

Section 13 classifies the 19 carriers; this assigns the **byte counts** to each class, which is what decides
whether any remaining work is worth doing. Total must equal 8,628.

| class | bytes | share | carriers |
|---|---|---|---|
| **register-role** | **5,825** | **67.5%** | `gm_AllocSpieler` 2823, `CrashDump` 1583, `ls_LoadBuildingEntityState` 671, `vfs_OpenStream` 238, `ahm_ExAllocAlchemist` 198, `gm_CheckInventoryCapacity` 97, `m_AllocTracked` 92, `srv_LoadBuf` 49, `gm_ObjectsAvailble` 25, `vfs_ReadCompressed` 23, `cm_ExProdObjekt` 21, `gm_CalculateProductionValue` 5 |
| **block placement** | **1,675** | **19.4%** | `cm_ExSellObjekt` 966, `ServerMainThread` 367, `gm_AllocGebaeude` 327, `cm_ProcessCommandQueue` 15 |
| **epilogue merge** | **1,128** | **13.1%** | `cm_ExCopyEntityData` 462, `gv_ExAllocGraveyardWorker` 451, `gm_FindNextFilteredEntity` 215 |

**Both major classes are compiler decisions taken after the C front end**: register colouring and the
backend cross-jump pass. Neither is addressed by any C spelling: §1 records that for register-role across many
carriers, and §2 for the epilogue merge across four instances and eight return spellings.

**The list is worth reading as a budget, not a work queue.** 67.5% of the residue sits in the class with the
most thoroughly-probed negative result in the project; the remaining 32.5% is split between two backend passes.
There is no third class.

**Two probes this round, both +0**, on carriers whose classification the byte split makes most attractive:

| probe | carrier | result |
|---|---|---|
| `volatile char` local for the compare operand | `gm_CalculateProductionValue` (5 bytes, 99.2% aligned) | **+16 object**, composition collapse |
| force the separate `add` via an `unsigned int` intermediate (`eoff = base; eoff += idx;`) to defeat the fold the recorded blocker names | `gm_CheckInventoryCapacity` (97 bytes) | **+0**, byte-identical: msvc6 strength-reduces it back, confirming the blocker's claim by direct measurement rather than citation |

The second is the useful one: blockers in this project's docs are normally left as assertions, and this one
("Writing `ent = base + idx*0x40; ent += idx;` is strength-reduced right back") was re-derived independently
and **held**.

### 17. Several of the 13 "differing CFG" carriers differ only by branch POLARITY (round 1009)

`cfg_compare.py` (rounds 1006-1008) reports **13 carriers whose control-flow graph is not isomorphic** to the
reference's. That verdict is built on a canonical form that deliberately **collapses conditional polarity**
(`je` and `jne` reaching the same two successors are one shape), so a DIFFERS verdict means the graphs differ
in *topology*, not merely in encoding. This round checked the smallest case and found the distinction is
narrower than the count suggests.

**`gm_CheckInventoryCapacity`: the one carrier whose block counts match exactly (25 vs 25), 97 bytes.**
Its entire CFG difference is the first list-scan loop's tail:

```
reference                        ours
0x10019f4f  cmp eax, edx         0x10019f4f  cmp eax, edx
0x10019f51  je  0x10019f5f       0x10019f4c  je  0x10019f5f
0x10019f53  mov eax,[ecx+4]      0x10019f52  mov eax,[ecx+4]     (approximately)
0x10019f56  add ecx,4            ...
0x10019f59  cmp eax, ebp         0x10019f59  cmp eax, ebp
0x10019f5b  jne 0x10019f4f       0x10019f5d  jne 0x10019f52
0x10019f5d  jmp 0x10019f64       0x10019f59  je  0x10019f64
```

**CORRECTION (round 1010): the difference is NOT polarity: it is statement order plus arity, and the
first draft of this section said otherwise.** Decoding both tails in full:

```
reference                          ours
0x10019f4f  cmp eax, edx           0x10019f52  mov eax, [ecx]
0x10019f51  je  0x10019f5f         0x10019f54  add ecx, 4
0x10019f53  mov eax, [ecx+4]       0x10019f57  cmp eax, ebp
0x10019f56  add ecx, 4             0x10019f59  je  0x10019f64
0x10019f59  cmp eax, ebp           0x10019f5b  cmp eax, edx
0x10019f5b  jne 0x10019f4f         0x10019f5d  jne 0x10019f52
0x10019f5d  jmp 0x10019f64         0x10019f5f  mov esi, 1
0x10019f5f  mov esi, 1             0x10019f64  ...
```

The reference runs the **sentinel test (`cmp eax,edx`) first**, then the hit test; ours runs the **hit test
(`cmp eax,ebp`) first**. So the loop's two tests are swapped in the source, and the swap changes each node's
**arity**: the reference's exit edge is an unconditional `jmp` (out-degree 1), ours is a second `jcc`
(out-degree 2). Measured out-degree histograms over the same 25 blocks:

| | out-degree 2 | out-degree 1 | out-degree 0 |
|---|---|---|---|
| reference | 19 | **1** | 5 |
| ours | **20** | **0** | 5 |

That is why the graphs are non-isomorphic: not a polarity swap on one node, but a `jcc` where the reference
has a `jmp`. The `cfg_compare.py` kind collapses polarity but still records `jmp` vs `branch2`, and this node
is the latter.

**The two probes stand** (+0 for the polarity-inverted spelling, +228 for bump-then-read), but the +0 is now
explained differently: inverting the *sentinel test's* polarity lands the same bytes because the test ORDER is
unchanged. Reordering the tests is the lever, and that is §84's statement-order class.

**Two probes, both reverted:**

| probe | result |
|---|---|
| `if (elem != 0) continue; break;` (polarity inverted) | **+0, byte-identical**: msvc6 normalises it |
| `list_cursor++; elem = *list_cursor;` (bump-then-read) | **+228** (residue 8,628 → 8,857) |

The second matches the file header's account exactly: *"the bump as `list_cursor++; elem = *list_cursor;` … the
bottom-compare form is structurally closer (one byte), but the entry compare is load-bearing for correctness"*,
with recorded scores of 291-292 for the `do/while` family.

**What to take from it.** A `cfg_compare.py` DIFFERS verdict is a **necessary** condition for a real
topological difference, not proof of one: the canonical form collapses polarity but a polarity swap still
changes which node is a `jmp` versus a `jcc`, and that is enough to separate the graphs. Before treating any of
the 13 as topological, check whether its difference reduces to a polarity swap on the same destination pair:
`gm_CheckInventoryCapacity` does, and its two available C spellings are +0 and +228.

### 18. All 13 non-isomorphic carriers differ in ARITY or MERGE, never in polarity alone (round 1011)

Round 1009 claimed one carrier's CFG difference was branch polarity; round 1010 showed it was arity. Round 1011
measured the **out-degree histogram** and the **undirected edge count** for all 13 carriers `cfg_compare.py`
reports as non-isomorphic, which classifies them without guessing.

| carrier | ref out-degree {0,1,2} | ours | undirected ref/bld | class |
|---|---|---|---|---|
| `gm_AllocSpieler` | {0:8, 1:26, 2:136} | {0:9, 1:27, 2:134} | 295/290 | **arity** |
| `CrashDumpUnhandledExceptionFilter` | {2, 21, 49} | {2, 21, 50} | 117/119 | **arity** |
| `cm_ExSellObjekt` | {8, 23, 96} | {8, 23, 98} | 215/219 | **arity** |
| `ls_LoadBuildingEntityState` | {3, 6, 65} | {3, 6, 64} | 136/134 | **arity** |
| `cm_ExCopyEntityData` | {4, 19, 56} | {4, 17, 60} | 126/132 | **arity** |
| `gv_ExAllocGraveyardWorker` | {10, 1, 35} | {9, 1, 35} | 67/67 | **arity** (ret/blocks differ) |
| `ServerMainThread` | {4, 18, 131} | {4, 18, 131} | 257/257 | **merge** |
| `gm_AllocGebaeude` | {4, 5, 28} | {4, 4, 30} | 60/63 | **arity** |
| `vfs_OpenStream` | {4, 8, 19} | {4, 6, 20} | 45/45 | **arity** |
| `gm_FindNextFilteredEntity` | {6, 2, 33} | {4, 2, 33} | 65/65 | **arity** (ret count differs) |
| `ahm_ExAllocAlchemist` | {4, 2, 22} | {4, 3, 22} | 44/44 | **arity** |
| `gm_CheckInventoryCapacity` | {5, 1, 19} | {5, 0, 20} | 36/37 | **arity** |
| `cm_ProcessCommandQueue` | {2, 5, 32} | {2, 5, 30} | 67/63 | **arity** |

**Twelve of the thirteen change an out-degree count**: a `jcc` where the reference has a `jmp` (or the
reverse), i.e. the *shape* of a branch differs, not its polarity. That is §84's statement-order class at the
branch level, and it is why the successor-set canonical form separates them despite collapsing polarity.

**`ServerMainThread` is the one exception, and round 1012 showed the "merge" reading here was an artifact.**

> **CORRECTION (round 1012).** The neighbourhood-profile table below was read as a *merge-point* difference.
> It is not. Comparing the two graphs under a **block correspondence by instruction ordinal** (rather than by
> address) shows **278 of 280 successor pairs match**. The two that differ are the pair already hand-verified in
> round 1005 at `0x100098e3` / `0x100098e9`:
>
> ```
> reference  0x100098e3  je  0x100097c5   then  0x100098e9  jmp 0x10009919
> ours       0x100098e5  jne 0x1000991a   then  0x100098e7  jmp 0x100097c5
> ```
>
> Same two destinations, swapped polarity. So `ServerMainThread` is **polarity-only**, exactly as round 1005
> concluded. The exact-isomorphism test rejects it because the reference reaches `0x100097c5` by a taken branch
> where we reach it by a fallthrough, and the two blocks sit at *different instruction ordinals* as a result:
> an address-level difference that is downstream of an encoding choice, not of topology.
>
> **The lesson, which is the same one rounds 1009-1011 kept relearning:** an exact isomorphism test on
> *addresses* answers "are these the same graph at the same addresses", not "is the control flow the same". The
> correspondence has to be established first (by ordinal or by canonical role), and only then compared. The
> neighbourhood table below is real data but was over-read.

**The original neighbourhood-profile reading (superseded, kept for the record):**

| neighbourhood (kind, successor kinds, predecessor kinds) | ref | ours |
|---|---|---|
| `(b2, (b2,b2), (b2,))` | 37 | 36 |
| `(b2, (b2,b2), (b2,b2,b2))` | 11 | 12 |
| `(b2, (b2,b2), (b2,b2,jmp))` | 2 | 1 |
| `(b2, (b2,b2), (jmp,))` | 2 | 3 |

So the difference is a **merge point**: one block has one predecessor where the reference gives it three, and
another has three where the reference gives it one. Nodes and edges are conserved; their *wiring* is not. That
is a real structural difference in the `place` class and the only carrier of its kind in the tree.

**Practical consequence.** "Non-isomorphic CFG" is not one phenomenon: twelve carriers differ by a branch's
arity (candidate: statement order, §84) and one by a merge point's fan-in. Before probing any of them, read the
out-degree histogram; it separates the two classes in one command:

```python
Counter(sum(1 for k in ('taken','fall') if edges[a].get(k) in blocks) for a in blocks)
```

Identical histograms but non-isomorphic means the carrier is in the merge class; a differing histogram means a
branch's shape is wrong.

### 19. Loop-condition polarity follows the loop FORM, not the condition's spelling (solved)

**Superseded.** The polarity below is reachable: written as `phase_complete = 0; while
(phase_complete == 0) { ... }` (a top-tested loop entered with a known-false test) the tail
compiles to the reference's `je top; jmp exit`. Every `do`/`while` or `for (;;)` spelling gives
the mirror image. `ServerMainThread` is byte-exact with that form (`msvc6-c-shapes.md` 196). The
measurements below stand; the conclusion drawn from them does not.


Round 1013 isolated `ServerMainThread`'s entire control-flow difference to **2 of 280 edges**, a polarity swap
on the same two destinations. The reference tails a loop with

```
0x100098e1  test esi, esi
0x100098e3  je   0x100097c5     <- taken edge CONTINUES the loop
0x100098e9  jmp  0x10009919     <- fallthrough EXITS
```

and we emit the mirror image:

```
0x100098e3  test esi, esi
0x100098e5  jne  0x1000991a     <- taken edge EXITS
0x100098e7  jmp  0x100097c5     <- fallthrough CONTINUES
```

Both encode the same two edges. Four source spellings were compiled to try to reach the reference's form:

| spelling of the tail | link delta |
|---|---|
| `} while (phase_complete == 0);` (shipped) | n/a |
| `} while (!(phase_complete != 0));` | **+0**, byte-identical |
| `if (phase_complete) break; } while (1);` | **+0**, byte-identical |
| inner scan inverted: `for (;;) { if (phase_complete == 0) break; ... }` | **+0**, byte-identical |
| outer `if (phase_complete != 0) { break; } } for (;;) {` | compile error (malformed); not a valid probe |

All three that compiled are byte-identical, so **msvc6 canonicalises loop-condition polarity**: it picks which
edge to encode as the taken branch from the loop's shape, not from how the C condition is written. This is the
same class as §50 (branch polarity) but specific to *loop back-edges*; the loop form (see the note above) is
what reaches the other encoding.


### 20. The whole raw-link `.data` divergence is postlink-supplied: so no `.data` content is missing (round 1016)

Rounds 977, 980 and 1015 each re-derived part of this section from a different angle. This round settles it with
the two numbers side by side, which none of the earlier passes printed together:

| file | `.data` differing vs reference |
|---|---|
| `build/split_poc.dll` (the raw link) | **21,481 of 57,344** (37.5%) |
| `build/server.dll` (the shipped file) | **0 of 57,344** |

So **every byte** of the raw-link `.data` divergence is rewritten by postlink's data fixer, and the deliverable's
`.data` is exact. The objective's "every data byte matching" clause is satisfied, and the gate's
`DATA_BASELINE` ceiling of 21,481 is a *build-placement* metric, not a measure of missing content.

**Why earlier passes kept re-opening it.** The divergence is not concentrated in the generated shims: attributing
it by owning object puts 643 bytes in `cm_ExSellObjekt.c.obj` and more in `cm_ExAllocSpieler.c.obj`, and the bytes
themselves differ in *kind*, not just position:

```
0x10029d00  reference:  a structured record table  {f64 2048.0, 14, 4, 5, 2500}, stride 0x18
            build:      a run of error strings   "gm_AllocSpieler() failed", "cm_ExChangePlayerIdentity() failed"
```

A game TU emitting strings where the reference has a record table reads as a content defect. It is not: the
shipped file is byte-identical at that address, because postlink copies `.data` wholesale from the layout
package.

**The record table is real and unmodelled.** At `0x10029cf0`, stride `0x18`, the reference holds
`{int, int, int, float}` records reading `5 / 2500`, `6 / 3000`, `4 / 2000`: a production cost table. It has no
source reference and no `rebrew-data.toml` entry; the layout package supplies it. Modelling it would be a
*source-fidelity* improvement (the C would name the table) but would not change a single shipped byte, because
postlink overwrites the section either way.

**Practical consequence for the objective.** The `.data` axis cannot move the residue: the shipped bytes are
already exact and the raw-link number is a ceiling the gate enforces correctly. The only route to changing
raw-link `.data` would be reproducing the original's `.data` COMDAT order, which is linker-hash-driven
(`CMakeLists.txt:443-448`) and unreachable from C.

### 21. `gm_FindNextFilteredEntity`'s entry order moves the fault instruction but scores +6 (round 1027)

`gm_FindNextFilteredEntity` (`0x10016f80`, 352 B, 215 residue) opens with a guarded prologue. The two
streams disagree at the **third** instruction:

```
ref  mov eax, [0x1014d8c0]     ; g_entity_ptr
     push esi
     xor cl, cl                ; match = 0
     lea esi, [eax + 0xa900]   ; end
     mov eax, [0x100a8c30]     ; g_entity_type_table
     test eax, eax
bld  mov eax, [0x1014d8c0]
     push esi
     test eax, eax             ; <-- table guard hoisted above match = 0
     je 0x100170d6
     lea esi, [eax + 0xa900]
     mov eax, [0x100a8c30]
```

The reference forms `end` before testing the table; ours tests the table first. Three spellings were
measured **at the link**, all reverted:

| variant | result |
|---|---|
| `match = 0; end = ...; if (table == 0) return 0;` | **+6** |
| `end = ...; if (table == 0) return 0; ...; match = 0;` | **+6** |
| `end` split into a braced block with its own `entity_base` temp | **+6** |

**Why this is not an ordinary canonicalisation.** Variant 1 *did* change the emitted order: it moved
`lea esi,[eax+0xa900]` from instruction 5 to instruction 2, which is where the reference has it. The
streams got **closer** at the fault and the link score still moved by exactly +6, identically for all
three spellings. So the +6 is not "the reorder failed"; it is a downstream cost that the reorder does not
touch, and it is larger than the local gain.

**The reading.** `xor cl, cl` is placed by the scheduler on data dependence (shapes §60), so its position
relative to the guard is not expressible in C, but the *guard's* position is, and moving it reproduces the
reference's own instruction order while making the function 6 bytes worse. **A carrier can have a fault
whose removal is not a win.** Score at the link before concluding that a fault-match is progress; the
fault-instruction identity is a diagnostic, not a target.

**Judgement:** with the entry order reproduced and still worse, and the remaining divergence being the
scheduler's placement of a single `xor`, this row has no C-expressible lever at its fault. Not re-probed
without new evidence.

### 22. `m_AllocTracked`'s prologue is a pure 2-instruction swap, and both source levers cost (round 1028)

`m_AllocTracked` (`0x10006580`, 92 residue) carries the most isolated divergence on the tree: an **adjacent
swap of exactly two instructions** at prologue index 6-7, with everything else in the first 12 instructions
identical.

```
ref  ... mov eax,[0x10034640]; push ebx; xor ebx,ebx; push esi; cmp eax,ebx; push edi; jne ...
bld  ... mov eax,[0x10034640]; push ebx; xor ebx,ebx; cmp eax,ebx; push esi; push edi; jne ...
```

`ref[6] == bld[7]` and `ref[7] == bld[6]`: verified by decoding both streams. The reference saves `esi`
before the `g_array_ptr == 0` test; we test first.

Two source-order spellings of the entry were measured **at the link**, both reverted:

| variant | link delta |
|---|---|
| swap the two entry guards (`if (size == 0)` before `if (g_array_ptr == 0)`) | **+539** |
| hoist `node = (struct GraphNode*) &g_alloc_root_name;` above both guards | **+61** |

Both are worse, and the second is worse by an amount that tracks nothing local. `push esi` is a callee-save
whose **position** is chosen by the scheduler from liveness; the `cmp` is a guard whose position is chosen
from the source, but moving the guard moves every dependent block with it. **The 2-instruction swap is not
a 2-byte edit to source: it is a scheduling difference whose local form cannot be reproduced without
re-laying the function.**

This is shapes §60's rule ("the scheduler places a store by its dependence, not by where the statement
sits") in its *prologue* form: a callee-save's placement is a liveness decision, and no C spelling names it.
The header's existing "these 2 remaining target-only items are allocator" verdict is **confirmed
independently**, and both spellings are now retired rather than untried.

**Generalisation, after two measured cases (this and §21).** A carrier whose fault is a *reorder* is not
automatically the best target, even when the swapped instructions are adjacent and the rest of the
prologue is byte-identical. The reorder is a symptom of a liveness/scheduling decision; reproducing it from
source requires moving a statement that other blocks depend on, and the dependent cost exceeds the local
gain in both cases measured.

### 23. The 18 carriers fail individually, not from a shared cause: file-mates are byte-identical (round 1040)

An untested hypothesis this session never falsified: that the residue has a **common cause**: a shared
header, a preamble spelling, a flag, or a codegen state introduced once and propagating. If true, one fix
would close all 18 carriers, and the per-carrier wall documentation would be a red herring.

**Falsified. Carriers fail independently of their translation unit.**

**Test 1: carriers are spread across 11 directories.** `spiel_c` 3, `command_c` 3, `server_c` 3, `game` 2,
and one each in `Error_c`, `loadsave_c`, `friedhof_logic_c`, `vfs_c`, `alchemistry_logic_c`, `m_alloc_c`,
plus `spiel_dumpD.c`. No single TU, module or header set is common to them.

**Test 2: file-mates of carriers are byte-identical.** Across all 30 multi-function files,
**130 of 137 functions (94.9%)** are byte-identical. The decisive cases are the two files that hold a
carrier *and* other functions:

| file | carriers | file-mates, all residue 0 |
|---|---|---|
| `spiel622.c` | `gm_CalculateProductionValue` `0x10019720`, `gm_CheckInventoryCapacity` `0x10019ed0` | `0x100196c0`, `0x100198b0`, `0x10019a20`, `0x10019a70`, `0x10019ae0`, `0x10019b40`, `0x10019b80`, `0x10019be0`, `0x10019c60`, `0x10019cd0`, `0x10019d00`, `0x10019d30`, `0x1001a060`, `0x1001a0d0`: **14 functions** |
| `spiel_dumpD.c` | `gm_FindNextFilteredEntity` `0x10016f80` | `0x10016cd0`, `0x10016de0`, `0x10016ea0`: **3 functions** |

Same translation unit, same headers, same compiler flags, same object file, and in `spiel622.c`
**14 functions are byte-identical while two are not.**

**What this rules out.** Any explanation of the residue that is a property of the *environment* (a header,
an include order, a `#pragma`, a flag, a toolchain state, a shared type or struct layout) because those are
common to every function in the TU, including the 94.9% that match. **The residue is a property of each
carrier's own code**, which is what the per-carrier class map (`codegen-walls` §13) and the allocator
findings already describe, and it is why 18 separate walls is the correct model rather than one.

**What it does not rule out.** That two carriers can share a *mechanism*: §13's four classes are exactly
that, and register-role rotation is one mechanism across eight carriers. The claim falsified here is a shared
**cause** reachable by a single edit, not a shared **class**.

**Method note.** This is the cheapest high-value test run this session (two `grep`s and a byte compare per
file) and it closes the last structural hypothesis about the residue's shape. Worth running whenever a
residue is described as having "a" cause.

### 24. `gm_AllocSpieler`'s +0xaa fault: three further spellings, none lands (round 1044)

Shapes §109 closed this row's first divergence (at `+0xaa`: the reference emits
`lea edx,[edx+0x100358fc]` where we emit `mov word ptr [ebp],bx` + `xor ebx,ebx` first, then
`lea edi,...`) and measured two reorderings that lose 371 matched bytes and grow the object by 5. Three
further spellings were measured **at the link** this round, all reverted:

| spelling | link delta | verdict |
|---|---|---|
| `memset` hoisted above the two zero-stores (`*(int*)(slot+0x170)`, `*(int*)(slot+0x16c)`) | **+361** | worst: 5.4x §109's recorded loss |
| explicit `int scaled = idx * 0x21c;` local, used for the `-1` fill | **+5** | worse |
| explicit `char* fill = (char*)0x100358a4 + idx*0x21c;` for the `-1` fill | **+0** | inert |

**The first row is the important one.** §109 moved the `memset` call and measured 633/3694 (371 matched
bytes lost). Moving the **two zero-stores instead** (leaving the `memset` where it is) is the same
transposition from the other direction, and at the link it costs **+361**, seven times the local gain
available and far worse than the reorder §109 tried. Both directions are now measured and both lose.

**The `+0` row is the converse datum:** naming the scaled index explicitly is *inert*, so the register the
reference keeps live in `edx` is not reachable by giving it a name. Consistent with §109's conclusion that
the ordering is a scheduler decision downstream of register pressure.

**The mechanism, restated with the new measurement.** Sinking a 16-bit store past a block fill is what msvc6
does; forcing either side of the transposition from C costs more than the transposition is worth, in both
directions, by margins of 5 to 361 bytes. **Eighteen rounds have now probed this row or its siblings from
every angle and the row has moved zero bytes.**

**The complete cost map for this one transposition (round 1045 closes it).** Every spelling that perturbs
the `id store / two zero-stores / memset` group, measured at the link:

| spelling | link delta |
|---|---|
| `*(slot+0x16c) = 0;` moved below the `memset` (only that one store) | **+3** |
| `*(slot+0x170) = 0;` moved below the `memset` (only that one store) | **+3** |
| both zero-stores moved below the `memset` | **+361** |
| `memset` hoisted above the id store and both zero-stores | **+368** |
| `memset` hoisted above the two zero-stores only | **+361** |
| explicit `int scaled = idx * 0x21c;` local | **+5** |
| explicit `char* fill = (char*)0x100358a4 + idx*0x21c;` | **+0** (inert) |

**Two structural facts fall out of the table.**

1. **The two single-store moves give the *identical* delta (+3).** Different edits, same number, is the
   collapse signature recorded in `workflow-traps` §18: msvc6 canonicalised both into one schedule, so
   *which* zero-store you move is not a degree of freedom: only *how many* are moved is.
2. **Hoisting the `memset` costs ~365 whichever side it lands on** (+361, +368), while moving zero-stores
   costs `3n`-ish for n = 1 (3) and n = 2 (361). The two halves of the transposition are not symmetric: the
   `memset` is the expensive operand because hoisting it forces the scaled index to be rematerialised across
   the call, exactly as §109 states.

**So the transposition is fully enumerated and every point on it loses.** The cheapest perturbation is +3,
the dearest +368, and the only inert spelling is the one that does not touch the schedule at all.

**Judgement:** with §109's two reorderings, these three, and the whole-carrier probes of rounds 1025-1031,
`gm_AllocSpieler` has no C-expressible lever at its fault. The 2,823 bytes behind it are that
scheduling decision's displacement wake (measured in measure-traps §38 as a multi-run profile, 4 distinct
displacement values across 7 runs). Not re-probed without a new allocator finding.

### 25. `gm_AllocSpieler`'s 2,823 bytes are FOUR clusters, and they are not displaced code (round 1046)

The row is described as "132 distributed schedule steps, no cliff" (`rebrew todo`) and its residue as a
"scheduling decision's displacement wake" (shapes §109). Both readings suggest many small scattered
differences. Measured, the residue is **highly concentrated and not displaced at all**.

**Cluster structure** (17 clusters at gap ≤ 8):

| cluster | size | share |
|---|---|---|
| `+0x1a4..+0x5f6` | **1,107** | **39.2%** |
| `+0xa0d..+0xd72` | **870** | **30.8%** |
| `+0x6cf..+0x8db` | **525** | **18.6%** |
| `+0x607..+0x6c6` | 192 | 6.8% |
| `+0xaa..+0x125`, `+0x130..+0x177` | 124, 72 | 4.4%, 2.6% |
| `+0xdd0..+0xe33` | 100 | 3.5% |
| eight singletons + `+0x8e7`, `+0x9ff`, `+0xd8c` | 5-27 each | 2.0% |

**Four clusters hold 90% of the residue.** Not 132 scattered steps.

**Rigid-displacement test on the big clusters**: for each, the best single offset `delta` maximising
byte-match between our cluster and the reference:

| cluster | best rigid delta | bytes matching |
|---|---|---|
| `+0x1a4..+0x5f6` (1,107 B) | +5 | **17.0%** |
| `+0x6cf..+0x8db` (525 B) | −13 | **13.9%** |
| `+0x607..+0x6c6` (192 B) | −8 | 18.3% |
| `+0xaa..+0x125` (124 B) | −16 | 20.3% |

**No cluster is a displaced copy.** A genuinely shifted region would match near 100% at its own delta; these
peak at 14-20% under their best offset, which is chance level for x86 byte comparison. So the large clusters
are **genuinely different code**, not our code at a shifted address, and the "displacement wake" description
does not hold for them.

**Reconciling with the other measurements.** Measure-traps §38 profiled this carrier as 4 distinct
displacement values across 7 runs, and §39 corrected the reading by showing the carrier's context-match rate
is only 34.1%. This section is that correction made concrete: the 34% of our stream that *is* findable in the
reference sits mostly in the small clusters, and the 66% that is not is the four large ones. **§109's
mechanism for the fault at `+0xaa` stands** (it is separately measured, and round 1045 enumerated its whole
perturbation space), but its extrapolation to the remaining 2,823 bytes does not: they are four independent
regions of different code, not one decision's wake.

**CORRECTION (round 1047): the "not displaced code" conclusion above is WRONG: the test was byte-level and
the clusters are displaced at the INSTRUCTION level.**

Re-measured by comparing instruction streams (mnemonic + operand with every `0x...` normalised to `A`, so
branch and data displacements do not count as differences):

| cluster | bytes | ref insns | our insns | delta | equal modulo address |
|---|---|---|---|---|---|
| `+0x1a4..+0x5f6` | 1,107 | 323 | 322 | −1 | **251/322 = 78.0%** |
| `+0xa0d..+0xd72` | 870 | 248 | 247 | −1 | **177/247 = 71.7%** |
| `+0x6cf..+0x8db` | 525 | 157 | 157 | 0 | 79/157 = 50.3% |
| `+0x607..+0x6c6` | 192 | 1* | 52 | n/a | *decode artefact, see below |
| `+0xaa..+0x125` | 124 | 30 | 31 | +1 | 12/30 = 40.0% |
| `+0x130..+0x177` | 72 | 15 | 13 | −2 | 3/13 = 23.1% |
| `+0xdd0..+0xe33` | 100 | 27 | 10 | −17 | 5/10 = 50.0% |

**The two large clusters are mostly displacement, not different code.** `+0x1a4` is 323 vs 322 instructions
with 78% equal modulo address; `+0xa0d` is 248 vs 247 with 72%. The best rigid *byte* delta matched only
17% because **every differing branch displacement breaks byte-window matching**: a 16-byte window spanning a
`jne rel32` cannot match at any offset once the target changes, even though the instruction stream is aligned.

**Why the byte test failed.** Byte-level autocorrelation answers "is this region a shifted copy", which is
false as soon as *any* embedded displacement differs. Instruction-level comparison with address
normalisation answers "is this the same code with different constants", which is the question that matters
for deciding whether a region is displacement or new code. **§38's local-context method has the same
limitation**: it searches for byte contexts, so it under-reports alignment exactly where branch targets
differ, and its "match rate" (34.1% for this carrier) is a byte-level statistic that must not be read as
"66% of this function is different code".

**Re-classification of the row:** clusters `+0x1a4` (39.2%) and `+0xa0d` (30.8%) are **displacement**;
`+0x6cf` (18.6%) is mixed; the small clusters are genuinely different. `+0x607` is the one outlier where we
have 51 more instructions than the reference in a 192-byte window (1 vs 52), which is a real structural
difference worth a probe.

**The `+0x607` row is a decoding artefact, not a finding.** Capstone reports 1 reference instruction there
because the cluster's first two bytes are `24 83` (`and al,0x83`), after which the decoder desynchronises and
stops emitting valid instructions: the reference's raw bytes at that offset are ordinary code
(`24 83 c6 0c db 44 24 24 ...`), and ours (`20 8b 44 24 14 db 44 24 20 ...`) is a different but equally real
stream. **A cluster whose instruction count comes out near zero is a desync, not a 51-instruction surplus.**
Verify the first bytes decode plausibly before reading any count from a narrow window.

**Judgement, revised:** the row's two largest clusters are **displacement** (78.0% and 71.7% equal modulo
address, instruction counts within 1); the first cluster's perturbation space is fully enumerated and losing
(§24); `+0x6cf` (18.6%) is mixed at 50.3%; and the small clusters are genuinely different. **No cluster on
this row has an unprobed lever with a clear signal.** The row is displacement plus small local differences,
which is what §109 said, and the six spellings targeting the first cluster's neighbourhood are all measured
and all lose. All six spellings that target the first cluster's neighbourhood are
measured and lose (§24), and the other three clusters have no probe on record. This is where a future round
would start if it takes this row up again, but the ordering is by cluster size, not by fault address, and
the first cluster at 39.2% is the one with a fully enumerated and fully losing perturbation space.

### 26. Three per-file toolchain pins to `msvc-6.0-sp5-pp` are load-bearing and uniquely optimal (round 1051)

`src/rebrew-functions.toml` carries per-function `toolchain` keys, and `rebrew cmake-flags` turns them into
`/REBREW_TOOLCHAIN:<name>` on the compile line. Three files carry one:

| file | carriers it holds |
|---|---|
| `ls_LoadBuildingEntityState.c` | `ls_LoadBuildingEntityState` (671 residue) |
| `alchemistry_logic_c/ahm_ExAllocAlchemist.c` | `ahm_ExAllocAlchemist` (198) |
| `spiel_dumpD.c` | `gm_FindNextFilteredEntity` (215) |

**Measured across all nine available msvc6 images, at the link:**

| pin | `ls_LoadBuildingEntityState` | `ahm_ExAllocAlchemist` | `gm_FindNextFilteredEntity` | total |
|---|---|---|---|---|
| **`msvc-6.0-sp5-pp`** (shipped) | **671** | **198** | **215** | **8628** |
| `msvc-6.0-sp6` | 675 | 201 | 226 | 8646 (**+18**) |
| `msvc-6.0-sp5` | 675 | 201 | 226 | 8646 (**+18**) |
| `msvc-6.0-sp4` | 675 | 201 | 226 | 8646 (**+18**) |
| `msvc-6.0-sp3` | 675 | 201 | 226 | 8646 (**+18**) |
| `msvc-6.0` (base) | 675 | 201 | 226 | 8646 (**+18**) |
| unpinned (falls back to sp6) | 675 | 201 | 226 | 8646 (**+18**) |

**Every other toolchain gives the identical +18, and the pin gives 0.** The five non-pinned images produce
byte-identical results to each other, so the axis is genuinely two-valued here: sp5-pp, or not-sp5-pp. The
pin is not a tolerance or a legacy artefact: it is the uniquely correct choice for these three files, and
removing it regresses all three carriers at once.

**Why this is worth recording despite moving nothing.** It is the first measurement in 26 rounds that
*changes the residue* rather than confirming a wall, and it does so in the informative direction: it
demonstrates that the toolchain axis is **closed by measurement, not by assumption**, for the only three
files where the axis is expressible. The global toolchain is fixed by
`cmake/toolchain-msvc-6.0-sp6-docker.cmake`, so a per-file pin is the only route, and it is already taken.

**Method note.** `scripts/linktest.sh` compiles with the exact `build.make` line, so it honours
`/REBREW_TOOLCHAIN`: the pins are live in both the build and in every delta this session has measured. The
sweep was run by substituting the token in `build.make` (backed up and restored; `build.make` is generated,
not tracked).

**Judgement:** no unexplored toolchain lever remains on this tree. The three pinned files are optimal, the
other 16 carriers have no expressible toolchain axis, and the five non-pp images are mutually identical.

### 27. The residue does not correlate with x87 density, branch count, or call count (round 1063)

Steps 1-26 characterise each carrier individually. This asks whether any **structural property** predicts
residue size across the set, which no round has tabulated. Properties measured on the reference stream, per
carrier, against residue:

| carrier | x87 insns | calls | jcc | jmp | residue | residue/insn |
|---|---|---|---|---|---|---|
| `cm_ExCopyEntityData` | 0 | 2 | 20 | 8 | 462 | **3.85** |
| `gm_AllocSpieler` | **128** | 55 | 96 | 26 | 2823 | **2.67** |
| `gv_ExAllocGraveyardWorker` | 0 | 4 | 21 | 0 | 451 | 2.64 |
| `CrashDump` | 0 | 44 | 40 | 27 | 1583 | 2.16 |
| `gm_FindNextFilteredEntity` | 0 | 0 | 25 | 2 | 215 | 1.73 |
| `cm_ExSellObjekt` | 0 | 31 | 81 | 22 | 966 | 1.43 |
| `ls_LoadBuildingEntityState` | 0 | 45 | 59 | 6 | 671 | 1.32 |
| `vfs_OpenStream` | 0 | 7 | 17 | 9 | 238 | 1.14 |
| `ahm_ExAllocAlchemist` | 14 | 8 | 10 | 2 | 198 | 1.12 |
| `gm_AllocGebaeude` | 0 | 18 | 27 | 11 | 327 | 0.95 |
| `gm_CheckInventoryCapacity` | 0 | 5 | 16 | 1 | 97 | 0.70 |
| `ServerMainThread` | 0 | 55 | 88 | 18 | 367 | 0.57 |
| `m_AllocTracked` | 0 | 10 | 23 | 3 | 92 | 0.35 |
| `srv_LoadBuf` | 0 | 17 | 25 | 6 | 49 | 0.21 |
| `vfs_ReadCompressed` | 0 | 5 | 20 | 1 | 23 | 0.12 |
| `gm_ObjectsAvailble` | 0 | 15 | 24 | 1 | 25 | 0.11 |
| `cm_ExProdObjekt` | 1 | 21 | 31 | 3 | 21 | 0.06 |
| `cm_ProcessCommandQueue` | 0 | 23 | 26 | 6 | 15 | 0.04 |
| `gm_CalculateProductionValue` | **29** | 2 | 8 | 1 | 5 | **0.04** |

**Falsified: x87 density does not predict residue.** The two x87-heavy carriers sit at **opposite extremes**:
`gm_AllocSpieler` (128 x87 ops) at 2.67 residue/insn, `gm_CalculateProductionValue` (29) at **0.04**, the
lowest in the set. Mean density for x87-bearing carriers **0.97**, for the other fifteen **1.16**: no
separation.

**Falsified: call and branch counts do not predict it either.** The highest-density carrier has **2 calls**
(`cm_ExCopyEntityData`), and the two highest call counts (55, in `gm_AllocSpieler` and `ServerMainThread`) sit
at 2.67 and **0.57**: opposite ends. `gm_FindNextFilteredEntity` has **zero calls** and 1.73.

**What this rules out.** Any explanation of the residue that is a function of instruction *mix*: x87
content, call density, branch density, loop count. Combined with §23 (carriers fail individually, file-mates
are byte-identical at 130/137), the residue is not predictable from gross structure at all. It is a property
of **specific scheduling and allocation decisions** in each function, which is what the per-carrier sections
describe and why there is no shortcut to them.

**Value of a negative result here.** Six rounds have re-confirmed individual walls; this is the first that
tests whether the *set* has a shared predictor, and it does not. That is worth recording precisely because a
positive correlation would have been the cheapest possible lead.

### 28. `m_AllocTracked`'s inlined `strcpy` differs from the reference in TWO ways at 0x100066a0 (round 1066)

The row's header documents its `memset`/`rep stos` side exhaustively (`#pragma function(memset)` mandated,
three intrinsic spellings all regressed) and mentions `0x100066a0-0x100066b7` only as the *reason*
`#pragma function(memset, strcpy)` was rejected. Decoding that address in **the shipped form** shows a live
divergence the record does not describe: the reference and our build emit msvc6's inlined `strcpy`
differently:

```
reference                     ours
0x100066a0 cld                0x100066a0 not  ecx
0x100066a1 repne scasb        0x100066a2 sub  edi, ecx
0x100066a3 not   ecx          0x100066a4 mov  eax, ecx
0x100066a5 sub   edi, ecx     0x100066a6 shr  ecx, 2      <-- ours: here
0x100066a7 mov   eax, ecx     0x100066a9 mov  esi, edi
0x100066a9 mov   esi, edi     0x100066ab mov  edi, edx
0x100066ab mov   edi, edx     0x100066ad rep  movsd
0x100066ad shr   ecx, 2       0x100066af mov  ecx, eax     <-- ref: here
0x100066b0 rep   movsd        ...
```

**Two independent differences:**

1. **The reference has `cld; repne scasb` (4 bytes) at the head of the sequence; ours does not.**
2. **`shr ecx,2` is scheduled differently**: the reference emits it *after* `mov edi,edx`; we emit it *after*
   `mov eax,ecx`, i.e. two instructions earlier.

**21 of the 25 bytes at `0x100066a0..0x100066b9` differ.** The carrier's 92 residue bytes form **12 clusters**
across the function (`+0x11`, `+0x2e`, `+0xfa`, `+0x113..0x128`, `+0x12d..0x141`, `+0x147..0x14d`, `+0x179`,
`+0x19f`, `+0x1d5`, `+0x1fb`, `+0x22d`, `+0x252..0x265`), so this site is one cluster, not the whole row.

**Why this is worth recording rather than probing.** `cld` before `repne scasb` is *optional* (the ABI
guarantees DF=0 on entry), so its presence is a codegen choice, not a semantic requirement. The `shr ecx,2`
position is a scheduler decision. Both are the class this project has measured repeatedly as unreachable from
C (shapes §§60, 109; measure-traps §44). The row's header already establishes that the two available pragma
splits are mutually exclusive, and that the target's combination "was not built with the msvc6 SP6 codegen
this project has", which is the *evidence-based* claim this divergence independently supports: the
reference's `strcpy` expansion has a `cld` preamble our compiler does not emit there.

**Judgement:** record, do not probe. The divergence is a codegen difference in an intrinsic expansion, on a
row whose every reachable pragma/type spelling has been measured and the `memset` half is closed. What is new
is that the `strcpy` half is now precisely located and characterised, rather than cited.

`src/Develop/Units/m_alloc/m_alloc_c/m_AllocTracked.c`

### 29. The reference's inlined `strcpy` carries a `cld` our msvc6 never emits: positive evidence for the asm clause

§28 located the divergence at `m_AllocTracked`'s `0x100066a0`. This probes its **first cause**: the reference
begins the expansion with `cld; repne scasb`, and ours begins at `repne scasb`.

**Tested whether any C spelling produces the `cld`.** Three independent compiles under this file's own flags
(`/O2 /Gd /MT`), each isolating the expansion:

| spelling | expansion head emitted |
|---|---|
| `void f(void) { strcpy(dst, src); }` with `<string.h>` | `83 c9 ff 33 c0 **f2 ae** f7 d1 2b f9 8b c1 8b f7 ...` |
| same, plus `#pragma intrinsic(strcpy)` | identical |
| same, taking `dst`/`src` as parameters | identical shape |

**None emits `cld`.** All three go `... 33 c0` → `f2 ae`, with no `fc` between. The reference is
`fc f2 ae f7 d1 2b f9 8b c1 ...`: that is, **`cld` followed by a sequence that is byte-for-byte what all
three spellings produce.** Verified: `ref_head == b'\xfc' + our_head` is `True`.

**And the in-situ build agrees.** Searching our compiled `m_AllocTracked` around the site finds the expansion
starting `8d 7d e8 f2 ae f7 d1 ...`: no `cld` adjacent, in situ as well as isolated.

**Why `cld` here is a genuine codegen choice, not a requirement.** The x86 ABI guarantees DF=0 on function
entry, so a compiler emitting `repne scasb` has no need to clear it first, and an *inlined* `strcpy` at a
call site inherits that guarantee. msvc6's own `strcpy` expansion does not emit `cld` in any of the three
forms tested. The reference emits it anyway.

**A caveat about the isolated test, recorded because it nearly misled this round.** The isolated compiles
schedule `shr ecx,2` **after** `mov esi,edi` (`... 8b c1 8b f7 8b 3d ... c1 e9 02`), while the in-situ build
places it **before** that move (`... 8b c1 c1 e9 02 8b f7`). So the expansion's schedule is
**context-dependent**, and the isolated compiles are not a faithful stand-in for the in-situ one. They do
answer the `cld` question (all three agree on its absence) but they must not be used to reason about the
`shr` ordering, which §28 measured in situ.

**Judgement, and this is the first entry in this doc that supports the asm clause.** The objective permits
raw asm only on *"positive evidence (for example a code shape no MSVC6 C output can produce, or a
corroborating string/symbol), not a hunch from a hard match"*. **`cld` before `repne scasb` is exactly that
shape**: an optional prefix byte with no semantic effect under the ABI, absent from every C spelling tested,
present in the reference. It is **one byte**, on a carrier whose 92 residue bytes span 12 clusters, and the
surrounding schedule difference (`shr` placement) is a separate, context-dependent cause that no pragma
reaches. So it is not a lever worth spending: closing it would need `__asm { cld }` at that site *and* would
still leave the other eleven clusters.

Recorded as evidence, not as a probe target.

`src/Develop/Units/m_alloc/m_alloc_c/m_AllocTracked.c`

### 30. The `cld` at `0x100066a0` is a ONE-OFF in the reference: 1 of 18 `repne scasb` sites

§29 established that the reference's inlined `strcpy` at `m_AllocTracked` carries a `cld` our msvc6 never
emits. This measures whether that is a compiler habit or a single site.

**Scanned the whole reference `.text` for `f2 ae` (`repne scasb`): 18 sites.** Of those, the count preceded by
`fc` (`cld`) is **one**:

```
VA           prev  context
0x10002730   11 76
0x10002ad7   00 00
0x100066a1   fc 55     <-- the ONLY cld
0x10006a95   10 24
0x10009d70   20 24
0x10009d96   ff c9
0x10009da5   ff c9
0x100110f3   ff c9
0x1001111a   ff c9
0x10011eae   c0 33
0x10011ed5   ff c9
0x1001717e   c0 33
0x10018a6e   30 55
0x10018a91   ff c9
0x10018ab4   ff c9
0x1001a54c   ff c9
0x1001a556   fd 0c
0x10021214   c0 33
```

**Our build emits `cld; repne scasb` zero times.**

**Two readings, and the data supports the second.** Either (a) msvc6 emits `cld` before `repne scasb` only in
some context we have not reproduced, or (b) the reference's byte at that site was produced by something other
than this compiler's `strcpy` expansion. Reading (a) would predict the 17 other sites to show some variation
in prologue; they do not: **15 of 18 share the same `83 c9 ff 33 c0` idiom** (`ff c9` / `c0 33` in the
`prev`/`prev2` columns), and the one `cld` site is the only one whose preceding byte is `55` (a `push ebp`
from an unrelated instruction). So the `cld` is not a systematic codegen variant; it is **one site**.

**A correction to this section's first draft.** It reported "the 17 normal sites are byte-correct in our
build; only the `cld` site is not." **That is wrong: 6 of the 17 differ.** Those six sit inside residue
carriers, so their difference is expected displacement, not a `cld` question, but the sentence as written
overstated the evidence and is recorded here rather than quietly dropped.

**Net.** The `cld` remains genuine positive evidence for the asm clause (§29): no C spelling produced it, and
the reference has it once. What this section adds is its **scale**: one site out of eighteen `repne scasb`
expansions in the whole binary, on a carrier that still has eleven other residue clusters. It is evidence, not
a lever, and the arithmetic is now explicit.

### 31. The missing `cld` does NOT explain `m_AllocTracked`'s other eleven clusters (round 1069)

§29-30 established the `cld` at `0x100066a0` as positive evidence for the asm clause and measured its scale
(1 of 18 `repne scasb` sites). The obvious next question: **is it the cause of the carrier's other residue?**
If our stream is missing one byte there, everything after it would be displaced by one, and the remaining
clusters would be that displacement rather than independent differences. That is testable and it is **false**.

**Test.** The `cld` sits at function offset `+0x120` of 672. Correlate our byte stream after that offset
against the reference's at several shifts:

| shift | tail match (bytes `+0x120..0x29f`) |
|---|---|
| **0** | **316/383 = 82.5%** |
| +1 | 23/383 = 6.0% |
| −1 | 22/383 = 5.7% |

**Shift 0 wins by a wide margin; ±1 collapses to chance.** So the tail is *not* displaced by a missing byte:
the residue after `0x100066a0` is a set of **local differences**, not one insertion's ripple. Inserting the
`cld` would fix the byte at `+0x120` and change nothing else.

**This closes the lead with evidence rather than by assertion.** Combined with §30's scale measurement, the
`cld` is now known to be:

- genuine positive evidence for the objective's asm clause: no C spelling emits it, confirmed across three
  independent compiles (§29);
- a single site out of eighteen in the whole binary (§30);
- **not** the cause of the carrier's other eleven clusters, since those are not a ±1 displacement (§31).

So closing it would move **one byte of 8,628**, and would require `__asm { cld }` to do it. The lead is
exhausted in both directions: it cannot be reached from C, and reaching it from asm buys one byte.

`src/Develop/Units/m_alloc/m_alloc_c/m_AllocTracked.c`

### 32. `std` before a rep sequence appears 11 times and we match all 11: the `cld` miss is specific, not a prefix gap

§29-31 closed the `cld` at `m_AllocTracked`'s `0x100066a0` as positive asm-clause evidence worth one byte.
This round asks whether we have a **general** weakness with direction-flag prefixes, which would be a much
bigger and more interesting finding.

**Contrast measured.** Scanned the reference for a direction prefix immediately followed by a rep sequence:

| prefix | reference | ours | verdict |
|---|---|---|---|
| `std` (`fd`) + `f2`/`f3` | **11 sites** | **11 sites** | **all 11 byte-identical in our build** |
| `cld` (`fc`) + rep | **1 site** | **0 sites** | the §29 miss |

The eleven `std` sites and their neighbours match exactly:

```
0x10011dad  ref=c0 8b fd f3 ab 83 c8 ff   our=identical
0x100188e8  ref=c0 8b fd f3 ab 83 ce ff   our=identical
0x1001a555  ref=45 0c fd f2 ae 47 38 07   our=identical
0x1001b3b3 / 0x1001b40a / 0x1001b434 / 0x1001b466 (and 0x1001ec63 / ba / e4 / 0x1001ed16)
            ref=72 0d fd f3 a5 fc ff 24   our=identical
```

**So there is no general prefix gap.** Our msvc6 emits `std` before `rep stosd`/`rep movsd` exactly where the
reference does, eleven times out of eleven, and the *reference itself* emits `cld` before a rep sequence only
once in the whole binary (§30).

**What this rules out.** The plausible broader hypothesis ("this compiler handles the direction-flag prefixes
differently from the reference's, so any rep-sequence site is suspect") is **false**, and it is false by a
wide margin: 11/11 versus 0/1. The `cld` is a single site with a single-byte consequence, not the visible
edge of a systemic difference.

**This closes the prefix direction of the investigation.** Combined with §31 (the `cld` is not the cause of
the carrier's other clusters), the finding is now bounded on every side: one site, one byte, specific rather
than general, and not reachable from C.

**Measured with a byte-level scan, with the caveat that raw byte counts are not instruction counts**: `fc`,
`fd` and `f0` occur inside immediates and displacements, so a naive count of those bytes in the two images
disagrees (reference 467 `fc` vs our 465) for reasons unrelated to prefixes. The table above counts only the
meaningful pattern (direction prefix *immediately followed by* a rep opcode), which is why it is trustworthy
where the raw count is not.

### 33. All 19 first divergences in one table, independently reproduced (round 1071)

§13 and §12c state each carrier's divergence site; this consolidates **the first differing instruction** for
all nineteen in one place, re-derived from the current shipped file and **cross-checked against
`scripts/fault_address.py`**: a tool written at a different time from a different method. Both agree on every
instruction and every address.

| carrier | first diff | instruction (reference) |
|---|---|---|
| `gm_AllocSpieler` | `+0x00aa` | `lea edx, [edx + 0x100358fc]` |
| `CrashDump` | `+0x0002` | `sub esp, 0x280` |
| `cm_ExSellObjekt` | `+0x002c` | `mov dword ptr [esp + 0x14], edi` |
| `ls_LoadBuildingEntityState` | `+0x003c` | `jle 0x10012dea` |
| `cm_ExCopyEntityData` | `+0x0030` | `jne 0x1000ed8e` |
| `gv_ExAllocGraveyardWorker` | `+0x0107` | `jle 0x10011d77` |
| `ServerMainThread` | `+0x03c7` | `je 0x10009827` |
| `gm_AllocGebaeude` | `+0x0060` | `mov edx, dword ptr [0x10030b6c]` |
| `vfs_OpenStream` | `+0x0036` | `cmp byte ptr [eax], 0` |
| `gm_FindNextFilteredEntity` | `+0x0006` | `xor cl, cl` |
| `ahm_ExAllocAlchemist` | `+0x00cc` | `lea edx, [eax + eax*8]` |
| `gm_CheckInventoryCapacity` | `+0x0013` | `xor ebp, ebp` |
| `m_AllocTracked` | `+0x0011` | `push esi` |
| `srv_LoadBuf` | `+0x0050` | `push eax` |
| `gm_ObjectsAvailble` | `+0x010d` | `test ebx, ebx` |
| `vfs_ReadCompressed` | `+0x009a` | `mov edi, eax` |
| `cm_ExProdObjekt` | `+0x00cd` | `mov edx, dword ptr [0x101de450]` |
| `cm_ProcessCommandQueue` | `+0x0037` | `jne 0x1000ab08` |
| `gm_CalculateProductionValue` | `+0x00e4` | `fxch st(1)` |

**Classified by the instruction's kind:**

| kind | count | carriers |
|---|---|---|
| branch target (`jcc`) | 5 | `ls_LoadBuildingEntityState`, `cm_ExCopyEntityData`, `gv_ExAllocGraveyardWorker`, `ServerMainThread`, `cm_ProcessCommandQueue` |
| operand (`mov`/`lea`) | 6 | `cm_ExSellObjekt`, `gm_AllocGebaeude`, `ahm_ExAllocAlchemist`, `vfs_ReadCompressed`, `cm_ExProdObjekt`, `gm_AllocSpieler` |
| stack/frame | 3 | `CrashDump` (`sub esp`), `m_AllocTracked` (`push esi`), `srv_LoadBuf` (`push eax`) |
| compare/zero | 3 | `vfs_OpenStream` (`cmp [eax],0`), `gm_FindNextFilteredEntity` (`xor cl,cl`), `gm_CheckInventoryCapacity` (`xor ebp,ebp`) |
| register role | 1 | `gm_ObjectsAvailble` (`test ebx,ebx`) |
| x87 | 1 | `gm_CalculateProductionValue` (`fxch st(1)`) |

**Why the table is worth having in one place.** It is the most compact statement of what remains: nineteen
instructions, each already characterised in its own section, and **five of them are `jcc`**: the branch-target
class whose mechanism is the backend layout pass rather than anything in C. Any future round can read this
table instead of re-deriving the set.

**The cross-check is the point.** `fault_address.py` walks both instruction streams from each entry and reports
the first structural disagreement; the table above was built by a different method (byte compare for the first
differing offset, then the reference instruction covering it). Two independent methods, same nineteen answers.

### 34. `gm_AllocSpieler`'s 2,823 bytes are dominated by ONE 159-instruction run, and it is a register swap the `volatile` qualifier fixes in place (round 1082)

The 2,823-byte carrier had been described as "192 hunks of 1-2 instructions", i.e. an evenly distributed
divergence with no single wall, which is the reading that justified not attacking it. **That is wrong.**
Aligning the two instruction streams directly (capstone on the reference and on the raw-linked
`build/split_poc.dll`, matching on `(mnemonic, operand-string-with-registers-normalised)`, resyncing within a
6-instruction window) gives:

| | |
|---|---|
| reference instructions | 1,056 |
| ours | 1,054 |
| differing runs | **48** |
| largest run | **159 instructions** |
| run-size mean | 19.0 |

So 2 of 3 differing instructions sit in one contiguous block starting at **`0x1001910e`**. The function is not
uniformly rough; it has a large coherent divergence and a scatter of small ones.

**What the big run actually is: a two-register role swap.** The reference and our code are instruction-for-
instruction identical across it except that `edi` and `esi` exchange jobs:

```
ref    0x1001910e  mov byte ptr [edi + 0x1014d8e0], 0
our    0x10019113  mov byte ptr [esi + 0x100a9820], al
ref    0x10019115  mov byte ptr [edi + 0x100a9820], al
our    0x10019119  mov      ax, word ptr [ebp]
ref    0x1001911b  xor      eax, eax            <-- the tell
ref    0x1001911d  mov      ax, word ptr [ebp]  <-- zero-extend, no mask
our    0x1001911d  and      eax, 0xffff         <-- mask instead
ref    0x10019123  lea      edx, [eax + eax*2]
our    0x10019124  lea      esi, [eax + eax*2]
```

The reference zero-extends the `unsigned short` load with `xor eax,eax` + `mov ax,[ebp]`; ours masks with
`and eax,0xffff`. From that one difference everything downstream rotates: the cursor lands in `edi` in the
reference and `esi` in ours, and every address in the run follows. The C is the `colv`/`rowv` sympathy-matrix
loop at `gm_AllocSpieler.c:588`, where both operands are `*(volatile unsigned short*) slot`.

**Two levers probed, both measured, both negative. Do not re-probe:**

| probe | linked delta |
|---|---|
| drop `volatile` from both loads in the loop | **+426** |
| explicit `(int)` cast on the first load | **+0** (inert) |
| hoist `rowv` above the first `gm_RandomMod` call, matching the reference's order | **collapses the composition** (`.text` +658, 0/319 symbols at reference VA) |

The first is the important negative: `volatile` is **load-bearing here**, and removing it to chase the
reference's *cleaner* zero-extend makes the match far worse. The regression list already recorded volatile
reads as 627 (worse than 652) at `gm_AllocSpieler.c:169-172`; this is an independent confirmation from the
opposite direction. The third shows the reference's *order* is not reachable by moving that statement: the
hoist is not a local change, it re-schedules enough of the function to lose position alignment outright.

**Why the earlier "192 hunks" reading misled.** It came from `ndiff.py`, a normalised instruction comparison
that is no longer in the tree (`.scratch/ndiff.py` is absent). Its hunk count was taken as evidence of
distributed divergence, but counting runs depends on where the aligner resyncs; the resync window here is 6
instructions, which merges many neighbouring small hunks into the 159-instruction run. **Neither count is
wrong, but only the run-size distribution answers the question that matters**: is there one wall or many?
The 192-hunk figure was used to argue "many", and the wall is real.

### 35. The sympathy-loop wall is a mid-argument register choice; four type and structure spellings are measured and none lands (round 1083)

Section 34 located `gm_AllocSpieler`'s 159-instruction wall and identified its single upstream tell: the
reference zero-extends the `unsigned short` load with `xor eax,eax` + `mov ax,[ebp]`, we emit
`and eax,0xffff`. This round probed whether that zero-extend is reachable from C. **It is not, by any of the
four shapes tried.**

**What the wall actually is, precisely.** Both sympathy loops open with the same pattern, and comparing the
reference against the raw-linked build at the loop head (`0x10019342`, the no-parent path) makes the cause
exact:

```
reference                              ours
xor eax, eax                           mov si, word ptr [ebp]
push 0x40                              and esi, 0xffff
mov ax, word ptr [ebp]                 add esi, edi
lea edi, [eax + esi]                   push 0x40
call gm_RandomMod                      call gm_RandomMod
```

The reference **clears a register, pushes the `0x40` argument, and only then loads the word into it**; ours
loads into the low half of the register it will accumulate into (`si` in `esi`) and masks afterwards. That one
choice determines the whole register assignment for the loop body (`edi` becomes the reference's address
base and `esi` the stride accumulator, and ours has them the other way), which is why 159 consecutive
instructions differ while being otherwise instruction-for-instruction identical.

**Four probes, all measured at the link, all negative:**

| probe | linked delta |
|---|---|
| `volatile` dropped from both loads (§34) | **+426** |
| `colv`/`rowv` declared `unsigned short` | **+455** |
| bind the slot id into a local `int` once per iteration, both uses reading it | **+470** |
| `colv`/`rowv` declared `unsigned int` | **+0** (inert) |
| explicit `(int)` cast on the load (§34) | **+0** (inert) |

All reverted; tree byte-identical to HEAD, deliverable `md5` unchanged.

**The negatives are the finding.** The reference's shape needs the loaded value in a *different* register from
the accumulator, live across the `push` of the call argument. Every C spelling that widens or renames the
value (`unsigned short`, `unsigned int`, a cast, a bound local) either changes the width back to what we
already emit (**+0**) or forces msvc6 to keep the value in one register across the call, which costs far more
than the swap it was meant to fix (**+426/~+455/+470**). The `volatile` double-load is load-bearing: the
reference reloads `*slot` twice per iteration, and only a volatile read stops msvc6 hoisting it.

**Judgement, labelled as such:** this is a register-allocation decision taken after the front end, in the same
class as §16's "67.5% register-role" bucket. The wall is now located to a single instruction and its cause
named, but no C spelling reaches it: the remaining options are a post-pass over the emitted bytes (outside
the C-only constraint) or accepting the floor.

### 36. No carrier is one wall: the largest run holds 17-83% of a carrier's differing instructions, and 25% across all ten measured (round 1087)

Rounds 1082-1086 located a single dominant divergence in each carrier they examined, which invites the
conclusion that each carrier is "one wall" and a handful of levers would clear them all. **Measuring the run
distribution across ten carriers says otherwise.**

Method: capstone on the reference and on the raw-linked `build/split_poc.dll`, matching on
`(mnemonic, operand-string-with-registers-normalised)`, resyncing within 6 instructions, then sorting the
differing runs by length.

| carrier | differing instrs | runs | largest run | largest share | mean run |
|---|---|---|---|---|---|
| `gm_AllocSpieler` | 949 | 50 | 159 | 17% | 19.0 |
| `CrashDumpUnhandledExceptionFilter` | 500 | 52 | 131 | 26% | 9.6 |
| `cm_ExSellObjekt` | 344 | 31 | 113 | 33% | 11.1 |
| `ls_LoadBuildingEntityState` | 244 | 12 | 62 | 25% | 20.3 |
| `vfs_OpenStream` | 61 | 3 | 30 | 49% | 20.3 |
| `gm_FindNextFilteredEntity` | 42 | 4 | 16 | 38% | 10.5 |
| `cm_ExCopyEntityData` | 37 | 3 | 19 | 51% | 12.3 |
| `ServerMainThread` | 26 | 9 | 7 | 27% | 2.9 |
| `gm_AllocGebaeude` | 13 | 4 | 9 | 69% | 3.2 |
| `gv_ExAllocGraveyardWorker` | 12 | 3 | 10 | 83% | 4.0 |
| **total** | **2,228** | **171** | n/a | **25%** | n/a |

**The shapes differ, and that is the point.** The large carriers are *one big run plus a long tail*: in
`gm_AllocSpieler` the 159-instruction run holds 17% of the differences, and 10 of its 48 runs are 3
instructions or shorter. The small carriers are *almost entirely one run*
(`gv_ExAllocGraveyardWorker` 83%, `gm_AllocGebaeude` 69%), and those are exactly the ones already close to
byte-exact.

**What the tail runs are made of**, sampled from `gm_AllocSpieler`, is the same material as the big runs:

| site | reference | ours | class |
|---|---|---|---|
| `0x10019361` | `xor eax,eax` + `mov ax,[ebp]` | `mov ax,[ebp]` + `and eax,0xffff` | §34/§35 zero-extend |
| `0x10018ee6` | `mov [esp+0x28], …` | `mov [esp+0x20], …` | frame-slot offset |
| `0x10018fd9` | `mov eax, [esp+…]` | `mov ecx, [esp+…]` | register choice |
| `0x10018f29` | `mov dl, [edi]` | `mov cl, [ebx+edx]` | register + addressing |

So the tail is not a different kind of problem that a second lever addresses; it is the *same* register and
frame decisions repeated at smaller scale, each independently placed. Fixing the largest run in a carrier
leaves the other 75-83% of its differences untouched.

**The consequence for planning, stated as judgement:** no carrier is cleared by locating its dominant run, and
no lever found in one carrier transfers as a single edit to another. §16's 67.5% register-role bucket is the
same conclusion from the byte side, and §23's "the carriers fail individually, not from a shared cause" is the
same conclusion from the file-mate side. Three independent measurements now agree, which is why the remaining
work is not a matter of finding the last lever.

**Caveat on the method.** The sizes passed to the disassembler were windows, not always the true function
extent (rounds 1084-1085 established that inventory sizes can overrun into padding), so the absolute run
counts are window-dependent. The *share* column is robust to that, since it is a ratio within the same window,
and it is the share that carries the argument. A first pass at this table using guessed sizes produced one
entry with zero runs for a carrier with 671 residue bytes; the real size was 1463 rather than the 499 assumed.

### 37. A register-rename post-pass has a measured ceiling of ~16% of the residue, and the other 84% is structural (round 1090)

The standing question this project has carried is whether to authorise a **non-C post-pass** over the residue
carriers: rewriting operands after compilation. That departs from the C-only constraint, so it cannot be
self-authorised, but its **value can be bounded without authorising it**, and this round bounded it.

Method: for each carrier, index both disassemblies by **address** (not by position), keep the addresses present
in both, and split the those where the bytes differ into two classes:

- **operand-only**: same mnemonic, different encoding. A register rename or addressing-form rewrite can fix
  these without recompiling.
- **structure**: different mnemonic. Only a recompilation can produce these.

| carrier | differing (same addr) | operand-only | operand-only bytes | structure bytes |
|---|---|---|---|---|
| `gm_AllocSpieler` | 276 | 32% | 364 | 767 |
| `CrashDumpUnhandledExceptionFilter` | 204 | 45% | 296 | 440 |
| `cm_ExSellObjekt` | 146 | 56% | 317 | 222 |
| `ls_LoadBuildingEntityState` | 92 | 32% | 114 | 246 |
| `cm_ExCopyEntityData` | 19 | 53% | 37 | 41 |
| `gv_ExAllocGraveyardWorker` | 11 | 91% | 42 | 5 |
| `ServerMainThread` | 41 | 56% | 115 | 71 |
| `gm_AllocGebaeude` | 10 | 100% | 47 | 0 |
| `vfs_OpenStream` | 10 | 20% | 11 | 30 |
| `gm_FindNextFilteredEntity` | 21 | 14% | 17 | 72 |
| **total** | **930** | n/a | **1,360** | **1,894** |

**The ceiling is ~1,360 bytes, or 16% of the 8,628-byte residue**, and that is a *perfect* post-pass, one that
renames every register correctly with no alignment cost. The remaining ~84% differs in **mnemonic**, which is
not reachable by operand rewriting at all: those sites need the compiler to emit different instructions.

**Two caveats that make 16% an over-estimate, not an under-estimate:**

1. These are 10 of the 19 carriers, holding 8,103 of the 8,628 residue bytes. The other nine are smaller and
   were not decomposed here.
2. The table counts only addresses present in **both** streams. Where the two have different instruction
   counts the alignment shifts and those bytes are attributed to neither class: the operand + structure
   columns sum to 3,254, well under the 8,628 the residue ruler reports. So the measured 1,360 is a floor on
   what is *not* fixable by register rename and a ceiling on what is, taken from the subset both streams agree
   on spatially.

**Why this matters for the decision.** The post-pass was the one remaining option that could move the number
without new C. It is now bounded: **it cannot reach zero, and it cannot even reach half.** Combined with §16
(67.5% of residue bytes are register-role *by byte count*, a different, looser classification that counts
whole functions rather than same-address sites), the two measurements agree on the direction and differ only in
granularity: the post-pass buys roughly a sixth of the residue, and the objective's "residue at zero" clause
would still be unmet afterwards.

**Judgement, labelled as judgement:** authorising the post-pass would trade a constraint for ~16%, and the
remaining 84% would then need the recompilation work that the constraint was protecting. That is a bad trade,
and it is now a measured bad trade rather than an assumed one.

### 38. THE LEVER THAT WAS MISSING: the residue contains 109 instructions the reference has and we do not emit at all (round 1094)

Rounds 1082-1090 classified the residue by **byte counts** and by whether differing sites shared a mnemonic.
Both are order-sensitive measures taken at aligned *positions*, and neither answers the question that decides
what kind of problem this is:

> **Does the reference contain instructions that our build does not emit anywhere in the function?**

If the answer is yes, the difference is not a compiler decision: a compiler choosing differently still emits
*some* instruction at every point. An instruction present on one side and absent from the other means the two
programs are not the same program, and the gap is **missing or surplus SOURCE**.

**Measured (order-insensitive instruction multiset, reference vs raw link, per carrier):**

| carrier | shared (mnemonic) | ref-only | our-only | verdict |
|---|---|---|---|---|
| `gm_AllocSpieler` | 1,032 | **24** | 22 | different set |
| `CrashDumpUnhandledExceptionFilter` | 632 | **41** | 24 | different set |
| `cm_ExSellObjekt` | 663 | 4 | 4 | different set |
| `ls_LoadBuildingEntityState` | 492 | 7 | 5 | different set |
| `gm_FindNextFilteredEntity` | 97 | **13** | 6 | different set |
| `gv_ExAllocGraveyardWorker` | 175 | 0 | 1 | different set |
| **10 carriers total** | n/a | **109** | **79** | |

**What the missing instructions look like, and why each is a missing statement, not a codegen choice:**

| carrier | reference-only instructions | reading |
|---|---|---|
| `gm_FindNextFilteredEntity` | `pop` ×3, **`ret` ×3**, `xor` ×3 | **three epilogues where our C has one** |
| `cm_ExCopyEntityData` | `pop` ×4, `mov`, `add`, `jmp`, `jge` | same: extra exits folded away in our source |
| `CrashDump` | **`adc` ×10**, `push` ×8, `pop` ×6, `sub` ×6, `test` ×4 | a whole carry-chain block we never wrote |
| `gm_AllocSpieler` | `mov` ×9, `lea` ×7, `xor` ×4 | statements absent from our reconstruction |
| `cm_ExSellObjekt` | `mov` ×2, `add`, `jne` | one missing statement and its branch |

**`ret` ×3 is decisive.** A function whose reference has three return paths and whose C has one is not
experiencing a scheduling disagreement: our source is missing the branches that reach the other two.

**Nothing about this contradicts the toolchain.** 264 of 283 functions are byte-perfect under this exact
msvc6, which is proof the compiler reproduces this binary when the C is right. A compiler wall would produce
the same instruction *set* in a different order; it cannot produce a set that is missing three `ret`s. So the
residue is **source-recovery work**, and source recovery is the one thing the constraints fully permit.

**Why rounds 1082-1090 read it otherwise.** §16's 67.5% "register-role" figure, §36's run distribution and
§37's 16% post-pass bound all measure *aligned positions* and *byte counts*. Both are blind to an instruction
that exists on only one side: an `adc` chain is counted as "bytes that differ", never as "an instruction we do
not have". The correct first question for any carrier is the multiset question above, and it should have been
asked before the position-based analyses, not after them.

**The lever, stated plainly.** For each carrier: list the reference-only instructions, read the region they sit
in, and recover the source that produces them. Start with the epilogue carriers: `gm_FindNextFilteredEntity`
(3 `ret`s) and `cm_ExCopyEntityData` (4 `pop`s), because a missing early-return is a structural gap that is
identifiable from the disassembly alone, with no search.

### 39. `gm_FindNextFilteredEntity`: the three epilogues are NOT merged in the reference, and the merge is what shifts every later byte (round 1095)

Round 1094 found 13 reference-only instructions here, including **three `ret`s against our one**. Reading the
two streams side by side gives the exact mechanism.

**The reference keeps three inline epilogues; our build shares one.**

| | reference | ours |
|---|---|---|
| `pop esi` sites | **3**: `0x10016f99`, `0x10016fa9`, `0x10016ff7` | **1**: at the shared exit `0x100170d6` |
| first epilogue reached by | `test eax,eax` / **`jne` skip** / fall into `xor eax,eax; pop esi; ret` | `test eax,eax` / **`je` shared_exit** |
| `push ebx` | `0x10016ff9` | `0x10016ffd`: **4 bytes later** |

The reference's shape is `jne <carry on>` with the return *falling through*; ours is `je <shared exit>` with the
return *jumped to*. The reference therefore materialises `xor eax,eax; pop esi; ret` three times (3 bytes each,
6 bytes more than ours), and because those bytes sit ahead of the `push ebx`/`push ebp`/`push edi` prologue of
the second half, **every byte after the first guard is positionally shifted by 4**. That is what the file's
header recorded as "with every post-entry byte positionally shifted behind the three misplaced pushes, no byte
after offset 3 can match, which holds the score at 99/346 despite obj size being exactly right at 346."

So the *object size matches* (346 = 346) while the *internal layout* does not: we spend the same bytes on one
shared epilogue plus padding, where the reference spends them on three inline ones.

**The lever, precisely stated.** msvc6 merges three identical `return 0;` tails into one block. The reference
did not. Something in the original source made those three returns *not* interchangeable: a distinct statement
between them, a different expression reaching them, or a construct the compiler treats as a barrier. Matching
the object size proves we have the right statement *count*; the merge decision is downstream of source
structure we have not yet reproduced.

**Probed this round, all reverted:**

| probe | delta |
|---|---|
| reorder so `end` is computed before the guard (the reference's apparent order) | **+6** |
| duplicate the second guard's `return 0;` (test whether two returns stay separate) | **+0**: msvc6 folded the duplicate away, since both are the same test |
| `volatile` double-load of `g_entity_type_table` to force the reference's two loads | **+0**: the file header records volatile reads as already probed inert here (probes z1-z4, w2/w3/w6, v1-v5) |

The duplicate-guard probe is the informative one: **two identical guards collapse**, which is why the merge
happens. Reaching the reference's three epilogues needs the three sites to differ in a way msvc6 cannot
collapse: not merely to be written twice.

**Also re-confirmed:** the flag axis is closed for this file. `/Ox, /O1, /Oy-, /Ot /Og, /Gs, /Gf, /Gy, /Ob0`
and `/Og /Oi /Ot /Ob1` were all swept on it (file header, line 288), and it carries the `sp5-pp` pin.

### 40. The epilogue-merge class: three carriers, one mechanism, and it is the SAME mechanism in all three (round 1096)

Round 1094 found reference-only `ret`s and `pop`s. Rounds 1095-1096 established the mechanism is one thing,
present in three carriers, and it is worth stating once:

**The reference keeps early returns INLINE; our build merges them into one shared exit.**

| carrier | reference epilogue clusters | ours | missing exits |
|---|---|---|---|
| `gm_FindNextFilteredEntity` | 3: `0x10016f99`, `0x10016fa9`, `0x10016ff7` | 1: shared `0x100170d6` | 2 |
| `cm_ExCopyEntityData` | 3: `0x1000eda8`, `0x1000ee3c`, `0x1000ef7b` | 2: `0x1000ee46`, `0x1000ef7f` | 1 |
| `gv_ExAllocGraveyardWorker` | (same class, 451 bytes) | n/a | n/a |

**The mechanism, from `cm_ExCopyEntityData`.** Its source has three `return 1;` sites in a row
(`cm_ExCopyEntityData.c:449`, `452`, `455`). msvc6 folds all three into one epilogue block. The reference does
not: it emits `pop edi; pop esi; pop ebp; mov eax,1; pop ebx; add esp,0xc; ret` **inline at `0x1000eda8`**,
reached by falling out of the scan loop at line 448.

The cost is positional. In `gm_FindNextFilteredEntity` the reference's three inline epilogues occupy 6 more
bytes than our single shared one, ahead of the second half's `push ebx`/`push ebp`/`push edi`, so **every byte
after the first guard is shifted by 4**. That is the file header's "no byte after offset 3 can match, which
holds the score at 99/346 **despite obj size being exactly right at 346**": the statement count is correct and
the internal layout is not.

**Probed (rounds 1095-1096), all reverted:**

| probe | result |
|---|---|
| reorder so `end` is computed before the guard | **+6** |
| duplicate the second guard verbatim | **+0**: msvc6 folds two identical guards into one |
| `volatile` double-load of the guard global | **+0**: already recorded inert here (probes z1-z4, w2/w3/w6, v1-v5) |
| give one return a distinct value (`temp = 1; return temp;`) | object **905** vs target 912: **7 bytes short** |
| value-preserving expression (`return (int)(dst_slot == 0x300) \| 1;`) | object **956**: **44 bytes long** |

**What the probes establish.** Respelling the *value* changes codegen but never lands: the two attempts bracket
the target (905 and 956 around 912) without hitting it, and the duplicate-guard case proves two *identical*
returns collapse. So the merge is not breakable by how the value is written. Matching the reference requires the
three returns to differ **structurally** (a different statement between them, or a control-flow shape msvc6
treats as a barrier), which is a source-recovery question about what the original `cm_ExCopyEntityData` and
`gm_FindNextFilteredEntity` actually contained at those sites.

**This is the most tractable remaining lever**, because the gap is identifiable from the disassembly alone: for
each carrier, count the reference's `pop`/`ret` clusters, compare with ours, and the difference names the
number of missing exits. No search space is involved.

### 41. `cm_ExCopyEntityData`: the third epilogue is a *duplicated shared exit*, and two structural probes are both 905 vs 912 (round 1097)

Round 1096 counted the epilogues and left the mechanism as "msvc6 folds three returns into one; the reference
keeps them inline". Reading the branch targets shows that is **not quite right**, and the correction matters.

**The reference's exits are shared too: it just materialises one of them three times.** In the reference:

| site | instruction | target |
|---|---|---|
| `0x1000eda0` | `cmp edx, 0x1009aca4` / `jb 0x1000ed95` | loop back |
| `0x1000eda6` | falls through | `pop edi` at `0x1000eda8`: epilogue **#1** |
| `0x1000edbb` | `jae 0x1000eda8` | **jumps back to #1** |
| `0x1000ee3a` | `jb` loop back, then falls through to `pop edi` at `0x1000ee3c` | epilogue **#2** |
| `0x1000ef7b` | n/a | epilogue **#3** |

Our build has **two** epilogue blocks (`0x1000ee46`, `0x1000ef7f`) where the reference has three, and our first
loop exit emits `jae 0x1000ee46` (jumping *forward* to the shared exit), where the reference *falls through*
into its own copy. So the difference is not "merged vs inline": it is **how many copies of the same epilogue the
backend chose to materialise**, and which branch reaches which copy.

**Two structural probes, both reverted, both `905` against a target of `912`:**

| probe | result |
|---|---|
| route the loop-fallthrough exit to its own label (`goto scan_failed; … scan_failed: return 1;`) | obj **905** |
| give that return a distinct value (`temp = 1; return temp;`), round 1095 | obj **905** |
| value-preserving expression (`return (int)(dst_slot == 0x300) \| 1;`), round 1095 | obj **956** |

Two different structural spellings landing on the **same** 905 says the shortfall is not the shape of that one
statement: both remove the same 7 bytes, i.e. both collapse the same code. The target needs those 7 bytes spent
elsewhere, which is the layout question above: a third epilogue copy.

**What this means for the lever.** The epilogue count is fixed by the backend's block-placement pass over the
whole function, not by any local spelling at the return site. Reaching three copies means changing what the
backend sees *around* the returns (the surrounding block order), which is the same "statement/definition order
is the only lever that lands" conclusion this project reached for other carriers, applied at the function's
tail rather than its head.

**The tractable residue in this function is now separated from the intractable part.** The 5 stride sites and
the two epilogue clusters match instruction-for-instruction; the divergence is which of the two-or-three
epilogue copies each branch reaches. That is a countable difference (2 vs 3), and it is not a source edit
available at the return site.

**Build note.** `rebrew test` reports `SIZE_MISMATCH` (obj 905 vs target 912) for this file **at HEAD as well**,
with no source change present: the reported object size does not track what `cmake --build` produces for it. The
gate, which measures the real composition, is unaffected. Recorded so the tool's number is not read as a
regression.

### 42. Correcting §38/§40/§41: the missing-instruction counts were inflated by jump-table decoding, and the real exit-path gap is 4 (round 1098)

Rounds 1094-1097 reported "109 reference-only instructions", "10 `adc` the reference has and we do not", and
"3 epilogues vs our 1". Re-measuring with the **true function extents** cuts all three down, and the correction
matters more than the original claim.

**The inflation was jump tables decoded as code.** A linear sweep over an inventory span passes through
embedded jump tables, and table bytes decode into plausible-looking instructions:

| what §38/§40 claimed | what was really there |
|---|---|
| `CrashDump`: **`or` ×50** | a run of `0x09` padding: `09 09` is `or dword ptr [ecx], ecx` (measure-traps §52) |
| `CrashDump`: **`adc` ×10** | a **jump table** at `0x10002e9c`..`0x10002f1f`; `popal`/`sub eax,[eax]`/`adc [ecx+0x2b],dl` is table data, not code |
| `CrashDump` ref-only total: 41, then 91 | **24** with the extent corrected |

**And the exit-path gap is 4, not 5.** Counting `ret`/`retf`/`iret` per carrier at the inventory extent
(`function_structure.json`, which is authoritative here because it bounds the span at the next entry):

| carrier | reference `ret` sites | ours | delta |
|---|---|---|---|
| `CrashDumpUnhandledExceptionFilter` | 2 | 1 | −1 |
| `cm_ExCopyEntityData` | 3 | 2 | −1 |
| `gm_FindNextFilteredEntity` | 5 | 3 | −2 |
| **all 19 carriers** | **71** | **67** | **−4** |

So the reference has **four** more exit paths than our build across the whole residue, not one per carrier per
function as §40 implied. Four extra epilogues is on the order of 4 × 6 bytes = **~24 bytes of `.text`**, plus
whatever positional shift they cause: a real but *small* lever, and not the explanation for 8,628 bytes.

**The corrected reading of the whole residue.** Total reference-only instructions across the 19 carriers is
**122**, not 189, once the padding and table artifacts are removed (189 was measured with two bad extents over
the same set). 122 missing instructions cannot account for 8,628 differing bytes either: the rest is the
aligned-position differences that §34-§37 already characterised.

**What remains true from §38.** The multiset test is still the right *first* question, and it still shows the two
programs differ in instruction *set*, not merely in ordering, which is what makes this source-recovery work
rather than a compiler wall. What §38 got wrong was the magnitude, because it measured over spans containing
tables and padding.

**The method rule this adds to §52 and §53:** before counting anything per function, establish the extent from
`function_structure.json`'s *next entry*, not from a guessed size or from the first padding run: a span can
contain both padding **and** jump tables, and the first padding run does not mark the end.

### 43. The missing early exits resist three further spellings; the mechanism is backend block placement (round 1099)

§42 established the real gap is **4 missing exit paths** across the 19 carriers: small, but the one clearly
source-shaped difference left. This round tried three more spellings at the two smallest instances. All failed,
and the pattern of failures is now informative enough to stop probing blind.

**The instance, precisely.** `gm_FindNextFilteredEntity` (`0x10016f80`, 346 bytes): the reference has **five**
`ret` sites: `0x10016f9a`, `0x10016faa`, `0x10016ff8` (three early, each an inline
`xor eax,eax; pop esi; ret` reached by falling through its guard) plus `0x100170c5`, `0x100170d9`. Our build has
**three**: `0x100170c5`, `0x100170d5`, `0x100170d9`. All three of our early guards jump to a late exit.

**Probes, all measured, all reverted:**

| probe | result |
|---|---|
| reorder so `end` is computed before the guard (§39, round 1095) | **+6** |
| duplicate the second guard verbatim | **+0**: identical guards fold |
| `volatile` double-load of the guard global | **+0**: already inert here (probes z1-z4, w2/w3/w6, v1-v5) |
| **scoped `end`** (`{ unsigned char* end_tmp = …; if (guard) return 0; end = end_tmp; }`, so both guards precede its use) | **+6**, and the `ret` count stayed **3** |
| route a return to its own label (`goto scan_failed; … scan_failed: return 1;`, `cm_ExCopyEntityData`) | obj **905** vs target 912 |
| distinct return value (`temp = 1; return temp;`) | obj **905** |
| value-preserving expression (`return (int)(… == 0x300) \| 1;`) | obj **956** |

**What the failures have in common.** Every spelling that changes the *tail structure* costs +6 (a positional
shift with no structural gain), and every spelling that changes the *returned value's form* moves the object
size without reaching the target's block count. Two independent carriers now show the same thing, and in
`cm_ExCopyEntityData` two different spellings landed on the **identical** 905: meaning they removed the same
bytes rather than arranging them differently.

**The mechanism, stated as narrowly as the evidence supports.** The reference materialises more copies of the
same epilogue than we do. Which branches reach which copy, and how many copies exist, is decided by the
backend's block-placement pass over the whole function. No local spelling at a return site changes that count:
probes on two carriers and seven spellings confirm it. Changing it means changing the block structure the
backend sees *around* the returns, which is the "statement/definition ORDER is the only lever that lands" rule
this project established elsewhere, now located at the function tail.

**Judgement, labelled as judgement:** with 4 exits across 8,628 bytes, this lever is worth roughly 24 bytes plus
positional shift. It is real and it is source-shaped, but it is not the path to zero, and seven failed spellings
say the remaining work here is block-order search rather than statement recovery. Recording that so the next
round does not re-run these seven.

### 44. WHAT THE 8,628 BYTES ACTUALLY ARE: 938 differing instructions, 567 of them a different mnemonic (round 1100)

§42 left the question open: 122 missing instructions and 4 missing exits cannot account for 8,628 bytes. This
round measured the residue directly on the **deliverable**, not on the raw link, and decomposed every differing
instruction.

**First correction: about 10% of the earlier counts were relocation artifacts.** Comparing the twelve largest
carriers at the same address:

| artifact | same-address differing instructions |
|---|---|
| raw link (`build/split_poc.dll`) | **1,042** |
| deliverable (`build/server.dll`) | **938** |

`.data`/`.bss`-addressed operands sit at provisional addresses in the raw link, and `postlink` rewrites them. So
an operand like `dec dword ptr [0x117665e4]` in the raw link is `dec dword ptr [0x10035434]` in the deliverable:
**identical to the reference**. Six of the twelve carriers' *first* divergence were exactly this: identical
instructions, different symbol addresses. Everything in §34-§43 that counted differences positionally should be
read from the deliverable; §53 said this for `.data`-addressed operands and this confirms it applies to
`.text` operands that *reference* `.data` too.

**The decomposition of the shipped residue, twelve carriers covering 8,538 of the 8,628 bytes:**

| class | instructions | bytes | what it means |
|---|---|---|---|
| **mnemonic differs** | **567** | **2,152** | a genuinely different instruction is emitted |
| operand other | 138 | 540 | same mnemonic, different addressing form |
| register only | 128 | 386 | same mnemonic and form, other register |
| immediate only | 105 | 407 | same mnemonic and form, other displacement/constant |
| **total** | **938** | **3,485** | |

**Read the classes in order of how hard they are to reach, not by size:**

- **`register only` (386 bytes) and `immediate only` (407)** are the backend's allocation and frame decisions:
  §16's bucket, and the two classes this project has measured shut repeatedly (five negatives on
  `gm_AllocSpieler` alone, §34/§35).
- **`operand other` (540)** is the addressing-form choice, §70's "nesting steers, operand order is inert".
- **`mnemonic differs` (2,152) is the only class that is unambiguously source-shaped**, and it is the largest.
  567 sites where the reference executes a different *kind* of instruction: a `lea` where we emit a `mov`, a
  `cmp [mem]` where we emit `mov`+`test`, an inlined sequence where we call. Each is a statement the original
  wrote differently or a construct msvc6 inlined and we did not.

**The bytes-per-instruction arithmetic is the missing link.** 938 instructions differ and the residue is 8,628
bytes: that is 9.2 bytes per differing instruction, well above the ~3 bytes an instruction occupies. The gap is
**positional**: once an instruction differs in length, every later byte in that function is compared against the
wrong instruction, and the byte-level ruler counts the whole misaligned stretch. That is why 938 real
differences produce 8,628 counted bytes, and it is the same mechanism §34/§36 described as "runs" without
accounting for the byte inflation. **The lever count is 938 instructions, not 8,628 bytes**, and the actionable
subset is the 567 `mnemonic differs`.

**What this changes about the plan.** The earlier framing (find the missing instructions) was right in kind but
wrong in magnitude: only 122 instructions are *absent*, while 567 are *present but different*, and it is the
latter that dominates. So the work is not primarily "recover what we deleted" but "find the source spelling that
makes msvc6 choose the reference's instruction at these 567 sites", which is the `msvc6-c-shapes` problem, and
narrower than the whole function.

### 45. Most of the residual difference is PAIRS OF SWAPPED INSTRUCTIONS, not different code (round 1103, fresh-eyes survey)

Going carrier-by-carrier produced a misleading picture: each one looked like a different problem. Comparing all
nineteen **by address on the deliverable** shows one shape repeated everywhere: the same instructions in the
opposite order.

**`cm_ExProdObjekt` is the cleanest example: 2 differing instructions out of 349 shared addresses, 21 residue
bytes, and the entire difference is one schedule swap.**

```
reference                              ours
0x1000e20c mov edx,[g_item_def_table]  0x1000e20c mov ebx,[ebp+0x16]
0x1000e212 xor eax,eax                 0x1000e20f xor eax,eax
0x1000e214 mov ax,[ebp+0x14]           0x1000e211 mov ax,[ebp+0x14]
0x1000e218 mov ebx,[ebp+0x16]          0x1000e215 mov [esp+0x18],ebx
0x1000e21b mov ecx,eax                 0x1000e219 mov edx,[0x100367bc]
0x1000e21d mov [esp+0x18],ebx          0x1000e21f mov ecx,eax
```

The reference hoists the **table-pointer load to the top**; ours issues it fourth. Nothing is missing, nothing
is different in kind: one load is scheduled earlier.

**The same shape in the other carriers examined this session:**

| carrier | the swap |
|---|---|
| `cm_ExProdObjekt` | `mov edx,[global]` first vs fourth (2 of 349 differ) |
| `vfs_ReadCompressed` | `mov edi,eax; test edi,edi` vs `test eax,eax; mov edi,eax` |
| `srv_LoadBuf` | `push eax` at idx 26 vs idx 29 (its whole 49-byte residue) |
| `gm_AllocSpieler` | `rep stosd` before vs after the slot stores (round 212) |
| `CrashDump` | `push ebp` / `mov [ebp],ecx` order |
| `gm_ObjectsAvailble` | `ebx`/`edi` roles swapped across two pointers |

**Two consequences that change the plan.**

1. **The address-indexed `mnemonic differs` count of 567 (§44) overstates the semantic gap.** When two
   adjacent instructions swap, both addresses report a *different mnemonic*, so a one-instruction schedule
   change is counted twice and looks like two pieces of different code. The real count of genuinely different
   instruction *kinds* is smaller than 567.
2. **`cm_ExProdObjekt`'s operand `0x100367bc` is not a symbol**: it is absent from `rebrew-data.toml`, while the
   reference's `0x101de450` is `g_item_def_table`. That is not a wrong global in the source: `postlink`
   rewrites `.data` operands **by `.text`-relative offset**, so when a preceding instruction changes length the
   rewrite lands on the neighbouring instruction. **Fix the swap and the operand corrects itself.** Reading it
   as a wrong-global bug would send the search into the data declarations, which are already exact (0 differing).

**Probed this round, all reverted, all negative:**

| carrier | probe | result |
|---|---|---|
| `cm_ExProdObjekt` | hoist `g_item_def_table` into a block local before both msg loads, so the source reads it first | **+0**, and the instruction order was **unchanged**: the scheduler rescheduled it back |
| `vfs_ReadCompressed` | volatile use-site on the `i == 0` test, the file's own technique | object grew past the 512 span, composition collapsed |
| `CrashDump` | typed `(OVERLAPPED*) 0` at one `WriteFile` | (probe abandoned, reverted) |

**The conclusion this supports, stated as judgement:** the residual is dominated by msvc6's **scheduler**, not
by source content. The instructions are all present and semantically equivalent (17 of the 19 carriers are
PROVEN); what differs is the order the backend emits them in, and the order is set after the front end by
register pressure and the instruction scheduler. Five carriers, three rounds, and roughly a dozen spellings now
show the same thing: no C-level respelling moves a pinned schedule, because the schedule is not derived from
the spelling.

### 46. Per-difference attribution: the residue is split evenly across THREE mechanisms, and §45 overstated the scheduler (round 1104)

§45 concluded from a handful of carriers that "the residual is dominated by msvc6's scheduler". That was an
extrapolation from the carriers that happened to be examined. `scripts/attribution.py` now attributes **every**
difference across all nineteen carriers, and the conclusion changes.

**Method.** Both streams are disassembled from the deliverable and the reference, then aligned on instruction
*shape*: mnemonic plus operands with registers **and** immediates abstracted. Aligning on shape is what makes a
register swap and an immediate difference land as aligned pairs rather than as unrelated instructions. Aligned
pairs differing in bytes are classified by how much of the operand text differs; the leftovers are matched
across the two streams by shape, and a leftover whose shape exists on the other side is the same operation at a
different position: a schedule difference.

**Result, all 19 carriers (2,025 attributed sites):**

| class | sites | bytes~ | share | what it is |
|---|---|---|---|---|
| **schedule** | 488 | 1,742 | **24.7%** | same instruction, different position |
| **register** | 502 | 1,623 | **23.0%** | same instruction, different register |
| **immediate** | 359 | 1,494 | **21.2%** | same instruction, different displacement/constant |
| missing | 299 | 838 | 11.9% | reference instruction with no counterpart |
| encoding | 144 | 698 | 9.9% | identical operand text, different bytes |
| extra | 188 | 580 | 8.2% | our instruction with no counterpart |
| operand-order | 14 | 42 | 0.6% | commutative address order (§70) |
| epilogue | 31 | 33 | 0.5% | materialised exits |
| **total** | **2,025** | **7,050** | | vs the ruler's 8,628 |

**The three leaders are within four points of each other.** No mechanism owns the residue. §45's "dominated by
the scheduler" was wrong: the scheduler is the largest single class at a quarter, not a majority, and the
allocation classes (`register` + `immediate`) together are **44%**, larger than scheduling.

**The sum is 7,050 against the ruler's 8,628 (82%).** The gap is the positional inflation §44 described: this
counts one entry per differing instruction, while the byte ruler counts the whole misaligned stretch that a
length change produces. Both are correct answers to different questions.

**Two secondary results worth keeping:**

- **`operand-order` is 0.6%.** §70 recorded commutative operand order as inert on a handful of probes; this is
  the first whole-tree measurement of how much of the residue it accounts for, and it is negligible. The doc's
  judgement is quantitatively confirmed rather than merely asserted.
- **`encoding` is 9.9%**: identical operand *text*, different bytes. Those sites cannot be register, immediate
  or order differences by construction, so they are something else (relocation slots, prefix bytes). It was not
  a class anyone had looked for.

**Validated against known cases before use:** `cm_ExProdObjekt` attributes 5 sites / 20 bytes against the
ruler's 21, and `srv_LoadBuf` 14 sites / 42 against 49. Both are the carriers whose differences were traced by
hand in §45, and both agree. The script carries a `--self-test` covering the classifier's contract and the
shape-abstraction rule.

**What this means for effort allocation, stated as judgement:** there is no single lever left, and there was
never going to be one. Fixing the schedule class would leave 75% of the difference; fixing allocation would
leave 79%. The residue is the aggregate of three backend passes disagreeing at a few hundred sites each, which
is why every per-carrier probe this project has run (hundreds of them, documented across these docs) moved a
carrier by a few bytes at most or cost more than it recovered.

### 47. The four backend mechanisms, named and separated (round 1105)

> **Amended (round 1145):** block placement and tail merging are reachable from source (loop form, in-loop returns, duplicated arms); nine carriers closed that way. See `msvc6-c-shapes.md` section 200.


Earlier rounds used "the scheduler" as a catch-all. It hides four distinct passes, and they differ in whether
source can reach them. Naming them separately is what makes the attribution table in §46 readable.

| mechanism | what it decides | evidence it exists | reachable from source? |
|---|---|---|---|
| **instruction scheduling** | the order of instructions with no dependency between them, within one basic block | `cm_ExProdObjekt`: both streams hold the same instructions in one basic block (the nearest branch is `ret` before and `je` after), and only the order differs | weakly: expression *shape* moves it, statement order does not (shapes, round 1105) |
| **constant CSE / rematerialisation** | whether a constant gets a register or is re-materialised at each use | `CrashDump`: reference `push 0` × 49 / `push edi` × 3; ours × 18 / × 37. Note the reference emits the *larger* encoding (`push 0` is 2 bytes, `push edi` 1) | no known lever; a constant has no definition site to sink (shapes §85) |
| **register allocation** | which register each value gets | `gm_ObjectsAvailble`: 79% of its differences are register-only: same mnemonic, same operand shape, different register | only through liveness, and ~120 declaration permutations measured inert there |
| **block placement / tail merging** | how many copies of an epilogue exist and which branch reaches which | `cm_ExCopyEntityData`: reference materialises the same epilogue 3 times, ours 2, with ours branching forward to a shared copy where the reference falls through | no: a CFG-layout consequence, not a knob |

**Why the distinction matters.** Each fails differently. A scheduling difference is a permutation of the same
instructions; an allocation difference swaps registers; a CSE difference changes an encoding's *length*; a block
difference changes the *number* of instructions. Fixing one leaves the others, which is why no single lever has
ever moved more than a few bytes:

- fixing scheduling alone would leave ~75% of the attributed difference (§46)
- fixing allocation alone would leave ~79%

**What "the residual is the scheduler" actually meant.** It meant "a pass after the front end, working on a
representation that does not preserve my statement order", which is true of scheduling and block placement, and
false of CSE (value numbering) and allocation. The corrected statement is in §46: the difference splits roughly
evenly across scheduling, allocation and immediate/displacement, so no one pass owns it.

**The instrument.** `scripts/msvc6_probe.py` compiles a snippet with the project's own compiler and dumps the
resulting instructions, so a claim about any of these four can be tested against the compiler instead of argued.
What it showed on first use is in `msvc6-c-shapes.md` (round 1105): independent operations are canonicalised, so
their source order is inert, and an isolated probe cannot predict a large function's order.

### 48. The ObjektNr2 literal wall: `0x101dd8e0` is load-bearing at three sites (rounds 1108-1109, judgement)

The reference corpus string-attests `gm_ObjektNr2MinimalHersteller` (732 ints, zeroed to 0x58 by
`gm_InitObjektHersteller`; the log string `"...Initialisiere gm_ObjektNr2MinimalHersteller[Objekte_MAX]"`
names the array). Two probes named the symbol and replaced the raw VAs in the three use sites
(`gm_InitObjektHersteller.c` fill/scan/store loops, `spiel622.c` `gm_CalculateProductionValue`):

| spelling | object rulers | linked residue |
|---|---|---|
| literal `0x101dd8e0` (shipped) | clean | **8,628** |
| `(int) symbol` in address arithmetic (round 1108) | clean (0 structural, 0 register, RELOC held) | **9,235 (+607)** |
| array-decay addressing (round 1109) | clean (0 structural, 0 register) | **9,237 (+609)** |

Both named-symbol forms displace the walled `gm_CalculateProductionValue` carrier out of the
attribution table entirely: the +607/+609 is not new damage at those sites, it is everything
after spiel622.c moving.

**Judgement, marked as judgement:** every named-symbol access form probed (cast and decay) changes
what msvc6 materialises, so the literal stays until a spelling is found that folds the base into the
instruction displacement the way the literal does. The attested name remains in
`naming_conventions.md`; do not re-probe the two spellings above without new evidence.

### 49. `gm_AllocSpieler`: two ordering differences with identical instructions (17 linked bytes)

> **Resolved (round 1145), both sites, byte-exact.** `push 0xa`: rounding the father term to float
> (`(float) (g_dbl_const_7d8 - rnd01) * father_value`) makes the first `fmul` wait on the node c2
> inserts after `fsubr` (op 0x162, latency 3), so it is ready at cycle 6 and the push issues at cycle 4
> after `fsubr`. Edge reloads: reusing the dead parameter `location` in place of `n` at three sites
> gives it three more webs; parameter webs take ids from the free list, which moves `type` from
> first-pass id 61 to 30 and flips the split order. A parameter's web count sets its webs' ids.

After `msvc6-c-shapes.md` sections 197 and 198 the function differs in 17 linked bytes, in
two places where both sides emit the same instructions in a different order. Both
mechanisms were traced in c2 12.00.9782 (`msvc6-allocator.md`).

- **Edge reloads at 0x10018c28/0x10018c38** (9 bytes). The two blocks reload `type` (esi)
  and `arg6` (ebx) in the opposite order. The order follows the split pieces' node ids,
  which follow a second numbering pass over the parameters' first-pass ids
  (`msvc6-allocator.md`, "Node ids are recycled"). The first-pass ids come from the constant
  candidates freed just before the parameters are created; our set is
  `0xff, 0x7fff, 0x3e, 0x3c, -8, 0x2637, 0x27f0, 0x286c` at the top, all but `-8` emitted
  as immediates, so their ids are fixed by the layout. Measured flips, each with other
  code changes: dropping the `-8` candidate (`0x56 - (rnd < 4 ? 8 : 0)` emits
  `mov cl,0x56; sub cl,al`, 897 bytes) and dropping `0x7fff` (storing `0x7fffffff`, which
  stores `0xffff`). Adding the `-4` and `-0x86` candidates gives `type` the lower
  first-pass id and still does not flip it. Tried without effect or with other code
  changes: casts and zero-extending loads for both `& 0xff`, if/else, swapped conditions
  and base-plus-select arithmetic for every ternary (the arithmetic forms emit `add dl`
  where the reference has `add edx`), respelled constants (`0x3e`, `0x7f`, `0x7fff`,
  `0x8000`, `0xffff`, `0x300`, `0xf`) and byte stores, constants routed through a
  temporary (copy-propagated first), fresh counters for each loop (19 byte-neutral,
  55 pairs), `*&param` (c1 folds it), `volatile` parameters, a local copy of `type`, raw
  addresses for `g_dynasty_field_2c`, `g_next_object_id`, `g_trait_ranges` and the `0.x`
  float constants, a struct copy for the `0xa8` memcpy, dead stores, unreachable code, an
  old-style parameter list in another order. Every immediate in our code equals the
  reference's.
- **`push 0xa` in the parent 14-trait blend** (8 bytes). The scheduler (`0x10727977`)
  holds the push back at cycle 5 because the previous issue is opcode 95 and the next
  `fmul` is ready (`0x10727d01`); it issues at cycle 7 and lands after the second `fmul`.
  The reference has it after `fsubr`, which needs opcode 95 not to issue in cycle 4. In our
  trace the first `fmul` is ready at cycle 3 with priority 38 (units of 0x2000) against the
  push's 22, and wins every cycle both are ready; the push can only precede it in a cycle
  where that `fmul` is not yet ready. Every
  spelling of the blend (casts, operand order, temporaries, weight type and storage,
  pointer or index addressing) folds to the same IL.
