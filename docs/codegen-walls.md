# Codegen walls — where C cannot reach the reference encoding

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
- **Typing a record is byte-neutral only when no index goes dead (rounds 897-898).**
  Replacing `char* p; p += 0xa9; *p == 0` with `EntityQueryRecord* p; p++; p->type == 0` landed
  **+0 linked** on `spiel5.c`'s `gm_SearchStruct` (39/39 before and after). The *same*
  transformation on `spiel6.c`'s `gm_SearchTable67` took it **obj 62 → 38, match 62 → 8**. The
  reference at `0x10017a70` keeps **both** the index (`inc eax; cmp eax,0x100`) and the pointer
  (`add ecx,0xa9`) and computes its return as `g_entity_ptr + i*0xa9` through a strength-reduced
  `lea` chain (`lea ecx,[eax*8]; add esi,eax; sub ecx,eax; lea ecx,[ecx+ecx*2];
  lea eax,[esi+ecx*8]`). Rewriting the return to the pointer directly makes `i` **dead**, so msvc6
  deletes the loop shape and 24 bytes with it.
  **The trigger is deadness, not the presence of index algebra** — round 897 first stated this as
  "an index used in the return expression", and round 898 measured a counterexample on itself:
  `spiel.c`'s `gm_ResetAllEntities` uses `i` in its address computation
  (`g_entity_ptr + i * 0xa9` → `(EntityQueryRecord*) g_entity_ptr + i`) and still lands at **+0**,
  because `i` also bounds the loop and therefore stays live. Three sites, one variable:
  no index (`gm_SearchStruct`) +0; index used and still bounding the loop (`gm_ResetAllEntities`)
  +0; index rendered dead (`gm_SearchTable67`) −24 bytes of code. **A type change is a codegen
  edit — measure every site with `linktest.sh`, never batch them.**

**Why this is a wall and not a puzzle:** these are choices made after the C front end, over
information (live ranges, use counts) that the source cannot address. Every measured attempt
either did nothing or moved a different decision instead. `msvc6-c-shapes.md` §§52-61 and
`msvc6-allocator.md` Findings 52-61 catalogue the specific attempts.

### 2. `msvc6` merges byte-identical early-return epilogues unconditionally

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

### 4. Address folding and strength reduction

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

On `gm_AllocGebaeude`, `__asm { nop nop nop }` used as a scheduling barrier measured
**matched 683 -> 830** and `matched-reloc` 823 -> 970 at an unchanged object size — because it
moved a global load across two instructions, flipping a forward branch rel8 -> rel32 and
realigning a 129-byte loop. The objective allows C only (except hand-written assembly the
*original* contained), so it was reverted. Measured cost of honouring the constraint: removing
just the barrier gives matched **377** (worse than HEAD) and a COMDAT of **1072** instead of
1088 — which moves the jump table and breaks the composition. **The entire +147 rested on the
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
`shr ecx,2; rep stosd; and ecx,3; rep stosb` in every case — never the align-up prelude. The
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
produce" as the example of positive evidence. That condition is satisfied here — measured, not
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
> `(edi*3)&3 == (-edi)&3` for every `edi` (verified 0..8), so it *is* an alignment computation — just
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
   majority of the remaining bytes are exactly that choice. If a technique exists — a
   compiler extension, a source idiom, or a post-pass — it would unlock many functions at once.
   **The "source idiom" half is now measured empty**: see §8.
2. **The original build's exact compiler or flag set.** ~~suggests our `/O2 /Gd` is not
   precisely what produced the reference. `msvc6` SP6 is what is installed; the reference may
   have been built with a different service pack or a different `/O` combination per file.~~
   **CLOSED (rounds 458/163/503/842).** SP6 is confirmed (`rebrew toolchain detect`: profile
   `msvc-6.0-sp6`, aligned true, and its "pre-6.0 constant-hoist" signal is a documented false
   positive — 4 of the 5 sites reproduce under our own SP6 build and 3 are in zlib). The flag
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
   residue run, 189 bytes at `0x10018be0`) collapses under either `volatile` form —
   `match` 1004 -> 570 and -> 553 (round 841). Its frame is confirmed correct
   (`sub esp,0x41c`, prologue byte-identical for 48 bytes), so it is not a frame problem —
   do not re-open it as one.

## 8. The measured floor of this constraint set

Established 2026-09-17 after rounds 833-843, by exhaustion with the population stated at each
step rather than by assertion. **Under C89, MSVC6 SP6, `/O2 /Gd`, no asm, no naked, no `_emit`:
the whole-tree `.text` residue floor for this binary is 8,634 bytes**, all inside 18 functions.
(Round 924 lowered the *actual* residue to **8,633** and the raw-link `.data` differing count
from 21,836 to **21,481** — see §10. The 8,634 floor above remains the figure rounds 833-843
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
a **scheduling barrier** (`__asm`, shapes §69 — measured at +147 matched and off-limits by the
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

**Counted, round 922** — six pairs, three closed outright and one newly explained:

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
while mine inserts `fmulp st(1)` — the reference performs the multiply later, as
`fmul dword ptr [0x100256b0]` at `0x10018f5e`. **A folded multiply, not a different form.** Shapes
§8a's documented `volatile`-alias remedy scores **606/3689** here and does not reach it. Recorded as
placement; do not re-spell it.

### 11. The residue's shape, quantified — and why the small carriers are not a shortcut (round 939)

The natural instinct when the big carriers are walled is to work the tail. Measured, that is a dead end,
and the population makes it obvious:

| band | carriers | bytes | share |
|---|---|---|---|
| top 5 (`gm_AllocSpieler` 2,823 · `CrashDump` 1,583 · `cm_ExSellObjekt` 966 · `ls_LoadBuildingEntityState` 671 · `cm_ExCopyEntityData` 462) | 5 | **6,505** | **75%** |
| the other 14 carriers | 14 | 2,128 | 25% |
| of which the 8 smallest (<=100 bytes each) | 8 | **327** | **3.8%** |

**Every one of the eight small carriers has a file header that already names its residual with a
mechanism and a probe history** — checked individually this round:

- `gm_CalculateProductionValue` (5 B) — an adjacent `fxch st(1)` / `cmp [esi],0x17` pair swap, **closed
  at round 196** after ~330 compiles, with the four reachable classes enumerated: the x87-stack
  allocator picks the `fxch` fixup position from the *type* of the scaled operand, and that same choice
  decides whether the compare folds (3 B) or unfolds (4 B).
- `gm_CheckInventoryCapacity` (97) · `m_AllocTracked` (92) · `srv_LoadBuf` (49) · `gm_ObjectsAvailble` (25)
  · `vfs_ReadCompressed` (23) · `cm_ExProdObjekt` (21) · `cm_ProcessCommandQueue` (15) — each header
  states its residual cluster and the variants rejected.

**So the tail is not unexplored — it is explored and closed, one file at a time, by rounds that wrote
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
| *(all other carriers)* | — | — | **exactly at span** | 8,390 of 8,628 |

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
docs"* at `0x1000bebc`, which reads as an unworked carrier. It is not — the divergence is documented at
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

So a per-file header comment is a **second store of probe history that `whathas.py` does not index** — the
tool searches `docs/` only. A carrier whose history lives in its `.c` header reads as fresh work, and an
agent that trusts the tool will re-run a probe already measured at 109 against a shipped 452.

**The check, before treating a carrier as unworked:**

```bash
python3 scripts/whathas.py 0x<va> --window 48     # searches docs/ only
sed -n '1,120p' <the carrier's .c>                # the per-file header is the other half
```

Small carriers resist this best — their whole history fits in a header comment, so it never needed a
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

**Nothing spills outside the unmatched functions** — no pad, no inter-function gap, no table. And the
shipped `.data`, `.rdata`, `.reloc` and headers differ by `0x0` (section 9b).

**What kind**, by the round-971 branch-target census (`scripts/branch_census.py`):

| class | carriers | evidence |
|---|---|---|
| **block placement** | `gm_AllocSpieler` (21 target-differing branches), `ServerMainThread` (14), `cm_ExSellObjekt` (7), `CrashDump` (7), `cm_ExCopyEntityData` (8), `gm_AllocGebaeude` (4), `gm_FindNextFilteredEntity` (3), `ls_LoadBuildingEntityState` (2), `cm_ProcessCommandQueue` (2), `gm_CheckInventoryCapacity` (1) | a branch whose mnemonic matches but whose destination does not |
| **epilogue merge** | `gv_ExAllocGraveyardWorker` (3 branches to a duplicate epilogue 0x9c away) | §2 |
| **register-role rotation** | `vfs_OpenStream`, `ahm_ExAllocAlchemist`, `m_AllocTracked`, `srv_LoadBuf`, `gm_ObjectsAvailble`, `vfs_ReadCompressed`, `cm_ExProdObjekt`, `gm_CalculateProductionValue` — **zero** target-differing branches | Findings 62/63; verified on `gm_ObjectsAvailble` (a consistent `ebx`/`edi` exchange, 235 instructions both sides) |
| **statement order** | `gm_CheckInventoryCapacity` (1 target-differing branch, but that is *downstream*) | round 974: its actual first divergence is `list[2] = 0x12` placed differently — see below |

**Round 974 corrected one entry and it matters for how the census is read.** The table above was
assembled from each carrier's *first branch whose target differs*, which is not necessarily its first
divergence. `gm_CheckInventoryCapacity` has one such branch, so it was filed under block placement — but
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
branches, so round 973 filed it under register-role rotation — but its first differing byte is two
instructions **swapped in the prologue** (`push esi` before `cmp eax,ebx` in the reference, after it in
ours), which is *scheduling*, not register naming. Hoisting `g_alloc_counter++;` above the guard to
reproduce it was probed and measures **8,628 -> 8,699 (+71)**, so the shipped order stays; the file's own
header already lists the neighbouring spellings as inert.

**So the census classifies by the *first target-differing branch*, which is a proxy, not by the first
divergence.** That is still useful for partitioning the set (a carrier with zero such branches cannot be a
placement story) but it must not be used to order *work*: for a carrier with one or two target-differing
branches, read the actual first divergence — it may be a statement-order or instruction-form difference
that the branch census cannot see.

**Every class is walled, and each has a named mechanism rather than an exhaustion argument:** block
placement is the backend layout pass (§17 of the shapes doc; and `cm_ProcessCommandQueue` is closed by
proof — the target's join test is provably-true dead code); epilogue merge is §2; register rotation is
allocator Findings 62-65, whose sweep showed no source-level naming reaches the choice.

**Consequence.** A future round should not re-derive the map. The open question is not *which* carrier or
*what kind*, but whether any lever exists for a class whose every member has been measured — and for three
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
  calls; the object holds **55** calls — the reference's own number. Alignment comes from
  `build/split_poc.map`, which is exact and regenerated every link.
- **Cut each body at its last `ret`.** A COFF `.text` section ends in jump-table and padding
  bytes that decode as plausible instructions: the reference's `0x09` filler reads as
  `or dword ptr [ecx], ecx` (50 of them after `CrashDumpUnhandledExceptionFilter`'s tables)
  and `gm_AllocGebaeude`'s tail reads as `adc ch, dh`. Counting those gave "-51 `or`,
  -43 `adc`, +108 `add`" image-wide. **All three were filler.** Filtering on a fully-decoded
  span is not enough to catch it — garbage also "decodes" end to end.

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
instruction counts already match — which is exactly the class sections 1-7 record as walled.
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
evidence about codegen. This is not a defect and it is not hidden — `measure-traps` §6h and the
`rebrew verify --data` warning both say it — but it belongs in this section too, because "the
deliverable is byte-identical outside `.text`" is the claim a reader arrives with.

**What it means for the objective's other clauses.** "Residue at zero" is a `.text` claim and is
unaffected. "Every data byte matching" is trivially met and should not be quoted as progress. The
honest single-number summary of this project is: **the deliverable matches the reference except for
8,633 bytes, all of them inside `.text`, and `.text` is the only section the build has to get right.**

### 10. A function-argument that was an undefined stub, found by reading the emitted operand (round 924)

The first residue movement since round 901, and it came from the section-9 instrument: decoding
*mnemonics* does not see it, but decoding **operands** does.

At `0x1000e12a` in `cm_ExSellObjekt` the reference emits `push 0x1002cc8c` (`68 8c cc 02 10`) —
a relocated reference to the message string `"cm_ExSellObjekt(): Ziel-Besitzer ist kein
Gebaeude"`. Our build emitted `push 0x11766604` (`68 04 66 76 11`) — a nonsense immediate.
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

Both improved, so both baselines were lowered. The `.data` gain is 355 bytes — much larger than
the `.text` gain — because the literal now participates in the merged string pool instead of
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

All 8,628 differing bytes are inside `.text`. Every non-`.text` byte already matches — confirmed three ways
that share no code:

| check | result |
|---|---|
| `postlink_residual.py`, shipped file | `.data` differing `0x0`, `.rdata` `0x0`, `.reloc` `0x0`, headers `0x0` |
| `cmp` over the whole file (above) | 8,628, i.e. exactly the `.text` residue 0x21b4 |
| `cmp` over `.data`+`.bss` alone (from `0x22846` to `0x174059c`) | **0** differing bytes |

**Why the round brief's `.data` framing is now a dead end.** `rebrew postlink`'s data fixer *copies* the
reference's `.data` wholesale — the baseline log records `0x7806` non-`.text` bytes overwritten per link.
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
signal — see measure-traps §19.

### 12c. The fault-versus-symptom split, and the tool that makes it mechanical (round 979)

Section 12b said all 19 carriers are documented. It is worth making that claim *reproducible*, because it is
easy to reproduce wrongly: **looking up the symptom address instead of the fault address makes a closed
carrier read as open work.**

- **Symptom** — the lowest differing **byte**. On this tree it is usually a branch displacement or a
  displaced operand, i.e. downstream of the real fault. Its address frequently has no `docs/` entry, or only
  residue-table mentions.
- **Fault** — the first instruction whose `(mnemonic, op_str, size)` actually disagrees when both streams are
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

- `vfs_ReadCompressed` `0x10008b2a` — the clamp order, shapes §85 plus the round-187 closure in the file
  header ("three walls and nothing else; do not re-probe without a new allocator finding").
- `cm_ExProdObjekt` `0x1000e20c` — `src/server.dll/DieGildeAddOn/command/command_c/cm_ExProdObjekt.c:147-160`:
  *"the dead store goes through a cast volatile pointer, which msvc6 treats as aliasing every global, so the
  global load is pinned below it"*, with ~50 measured variants all landing on the identical mismatch set
  (205-218, 223-224, 410). §91's sp5-pp screening independently calls this "the +204 global-load lane is
  scheduler-bound and retires".

So §12b's conclusion holds and is now checkable two ways rather than asserted.

### 12d. The 12b/12c coverage table partly counted itself (round 982)

Sections 12b and 12c tabulated "doc hits" per carrier fault address to argue that all 19 are documented.
**That count included the tables themselves** — `whathas.py` finds §12b/§12c because those sections list the
same addresses, so eight carriers' scores were inflated by the very tables making the claim.

Re-scored with `12b.`/`12c.`/`Round 97x`/`Round 98x` excluded, and cross-checked against each carrier's
**own `.c` header** (which `whathas.py` does not index — workflow-traps §8):

| carrier | fault | real doc hits | header probe-history markers |
|---|---|---|---|
| `_CrashDumpUnhandledExceptionFilter@4` | `0x10002770` | 34 | — |
| `_cm_ExSellObjekt` | `0x1000d959` | 32 | — |
| `_cm_ExCopyEntityData` | `0x1000ec2e` | 21 | — |
| `_gm_FindNextFilteredEntity` | `0x10016f86` | 19 | — |
| `_m_AllocTracked` | `0x10006591` | 18 | — |
| `_gm_AllocSpieler` | `0x100188fa` | 11 | — |
| `_gv_ExAllocGraveyardWorker` | `0x10011cf6` | 9 | — |
| `_vfs_OpenStream` | `0x10009056` | 6 | — |
| `_gm_CheckInventoryCapacity` | `0x10019ee3` | 6 | — |
| `_cm_ProcessCommandQueue` | `0x1000aaf6` | 5 | — |
| `_gm_CalculateProductionValue` | `0x10019804` | 5 | — |
| `_ls_LoadBuildingEntityState` | `0x1001292a` | 3 | **1** |
| `_gm_AllocGebaeude` | `0x10017530` | 3 | 10 |
| `_gm_ObjectsAvailble` | `0x1001607c` | 2 | 69 |
| `_ahm_ExAllocAlchemist` | `0x1000bebb` | 1 | 15+ |
| `_vfs_ReadCompressed` | `0x10008b2a` | 1 | 15+ |
| `_ServerMainThread@4` | `0x100096a8` | **0** | 8 |
| `_srv_LoadBuf` | `0x1000a5c0` | **0** | **16 passes** |
| `_cm_ExProdObjekt` | `0x1000e20c` | **0** | 15 |

**The three zero-hit carriers all have substantial in-header history**, and `srv_LoadBuf`'s header documents
**sixteen passes** of probes with the score of each. So the conclusion of §12b survives — but the *evidence*
for it was partly circular, and the corrected table shows that for 8 of 19 carriers the `docs/` count is
not the evidence at all.

**The practical reading: `docs/` hits under-count on this tree, and the under-count is largest exactly where
the work was hardest.** A carrier with a long header and a short `docs/` presence (small function, many
probes, no standalone section) is the normal shape for thoroughly-worked rows, not an unexplored one.
`scripts/preprobe.sh` prints both counts for this reason.

### 2 addendum — a fourth instance, with branch counts: `cm_ExCopyEntityData` (round 995)

§2 had three instances (`gm_FindNextFilteredEntity` five `ret` sites, `gv_ExAllocGraveyardWorker` two
byte-identical copies, and the recurring "reference keeps N epilogues" note). Round 995 found a fourth, and
this one is the clearest because the two epilogues are **not** byte-identical — they differ only in the
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

Our surviving epilogue is byte-identical to reference B — it is not wrong code, it is a *missing copy*. That
is why this instance adds something the others did not: the earlier three involve byte-identical epilogues,
so a reader can suspect the difference is in the exits themselves. Here the exits provably differ by five
bytes and the compiler still folds them.

**No new lever.** §2 is closed with eight return spellings compiled across two passes, all inert, and a
352-byte standalone TU reproducing the reference's guard/loop structure that still folds all three exits.
This instance was found *by* `scripts/instr_diff.py` reporting `ref-only x4: pop R`, which is a cheap screen
for the class: **a carrier with `ref-only` `pop`/`ret` counts is an epilogue-merge instance, not an operand
problem.** Worth running before probing any carrier.

### 5 addendum — the `#pragma optimize` axis, swept on `ls_LoadBuildingEntityState` (round 996)

§5 records that flags are not a general lever, and the `#pragma optimize` letter axis has landed once
(`cm_ExCopyEntityData` pass 5: `"a", on` took 512 → 523, because **`/Oa` is not part of `/O2` or `/Ox`** and
the toml cflags apply per translation unit, so the pragma is the only way to reach it). Because that lever
*did* pay once, it is worth knowing whether it pays on the other carriers. Round 996 tested it on
`ls_LoadBuildingEntityState` — the carrier with the highest aligned-match rate of the four mid-size rows
(87.8%, 17 of 33 hunks same-kind) and, until now, **no `#pragma optimize` anywhere in the file**.

| pragma | residue | delta |
|---|---|---|
| none (baseline) | 8,628 | — |
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

The user clarified the asm carve-out: raw asm is permitted where C cannot reach the shape — padding, single
instructions, the six memset preludes — never whole-function asm. That is a **narrower** permission than
"write the function in asm", and it is worth testing what it actually unlocks.

**It unlocks nothing among the residue.** The six existing asm sites are inside `srv_InitBuildingTypeTable`,
`gm_AllocGebaeude`, `m_AllocTracked`, `m_alloc`, `m_alloc2` and `vfs_ReadData` — and the functions that
*contain* those sites are already byte-exact. The 8,628 residual bytes live in 19 different functions, and
none of them is an instruction-shape problem:

| carrier class | count | is a single instruction unreachable from C? |
|---|---|---|
| register-role rotation | 8 | no — the instructions are all C-producible; the *register* differs |
| block placement / branch target | 10 | no — same instructions, different addresses |
| epilogue merge | 1 | no — same epilogue bytes, one copy folded away |
| **total with an asm-eligible shape** | **0** | |

The test for eligibility is not "is the byte wrong" but "**could a C compiler emit this instruction at this
site at all, in any spelling**". Every differing instruction in the 19 carriers is emitted by msvc6
*somewhere* in the same function — that is what the register-role and epilogue classes mean. An asm block
would be a whole-function escape, which the carve-out excludes.

**Screened by hunk count rather than file size, which is the efficient order.** The two closest to a
single-instruction fix are `cm_ExProdObjekt` (`0x1000e140`, 348/354 aligned, 3 hunks, `ref-only 0 /
built-only 0`) and `ls_LoadBuildingEntityState` (`0x100128f0`, 438/499, 33 hunks but only **1
different-kind**). Both probed this round, both **+0**:

- `cm_ExProdObjekt`: the three-instruction ordering hunk. Header records a *complete* enumeration — "all 112
  topological orderings of the seven statements … none beats 976". Genuine closure.
- `ls_LoadBuildingEntityState`: the `lea esi,[edx+ecx]` vs `[ecx+edx]` operand swaps are §70's inert class
  ("operand order in a commutative address expression is inert"), and naming the `esi + 0x34` argument pointer
  to match the reference's `mov ecx,ebx; add ecx,edx` form is **byte-identical** — §70's "this site was
  already at its optimum" reproduces.

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

**Both major classes are compiler decisions taken after the C front end** — register colouring and the
backend cross-jump pass. Neither is addressed by any C spelling: §1 records that for register-role across many
carriers, and §2 for the epilogue merge across four instances and eight return spellings.

**The list is worth reading as a budget, not a work queue.** 67.5% of the residue sits in the class with the
most thoroughly-probed negative result in the project; the remaining 32.5% is split between two backend passes.
There is no third class.

**Two probes this round, both +0**, on carriers whose classification the byte split makes most attractive:

| probe | carrier | result |
|---|---|---|
| `volatile char` local for the compare operand | `gm_CalculateProductionValue` (5 bytes, 99.2% aligned) | **+16 object**, composition collapse |
| force the separate `add` via an `unsigned int` intermediate (`eoff = base; eoff += idx;`) to defeat the fold the recorded blocker names | `gm_CheckInventoryCapacity` (97 bytes) | **+0**, byte-identical — msvc6 strength-reduces it back, confirming the blocker's claim by direct measurement rather than citation |

The second is the useful one: blockers in this project's docs are normally left as assertions, and this one
("Writing `ent = base + idx*0x40; ent += idx;` is strength-reduced right back") was re-derived independently
and **held**.

### 17. Several of the 13 "differing CFG" carriers differ only by branch POLARITY (round 1009)

`cfg_compare.py` (rounds 1006-1008) reports **13 carriers whose control-flow graph is not isomorphic** to the
reference's. That verdict is built on a canonical form that deliberately **collapses conditional polarity**
(`je` and `jne` reaching the same two successors are one shape), so a DIFFERS verdict means the graphs differ
in *topology*, not merely in encoding. This round checked the smallest case and found the distinction is
narrower than the count suggests.

**`gm_CheckInventoryCapacity` — the one carrier whose block counts match exactly (25 vs 25), 97 bytes.**
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

**CORRECTION (round 1010): the difference is NOT polarity — it is statement order plus arity, and the
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
**arity** — the reference's exit edge is an unconditional `jmp` (out-degree 1), ours is a second `jcc`
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
| `if (elem != 0) continue; break;` (polarity inverted) | **+0, byte-identical** — msvc6 normalises it |
| `list_cursor++; elem = *list_cursor;` (bump-then-read) | **+228** (residue 8,628 → 8,857) |

The second matches the file header's account exactly: *"the bump as `list_cursor++; elem = *list_cursor;` … the
bottom-compare form is structurally closer (one byte), but the entry compare is load-bearing for correctness"*,
with recorded scores of 291-292 for the `do/while` family.

**What to take from it.** A `cfg_compare.py` DIFFERS verdict is a **necessary** condition for a real
topological difference, not proof of one: the canonical form collapses polarity but a polarity swap still
changes which node is a `jmp` versus a `jcc`, and that is enough to separate the graphs. Before treating any of
the 13 as topological, check whether its difference reduces to a polarity swap on the same destination pair —
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

**`ServerMainThread` is the one exception — and round 1012 showed the "merge" reading here was an artifact.**

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
> where we reach it by a fallthrough, and the two blocks sit at *different instruction ordinals* as a result —
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
out-degree histogram — it separates the two classes in one command:

```python
Counter(sum(1 for k in ('taken','fall') if edges[a].get(k) in blocks) for a in blocks)
```

Identical histograms but non-isomorphic means the carrier is in the merge class; a differing histogram means a
branch's shape is wrong.

### 19. Loop-condition POLARITY is not steerable — four spellings, all byte-identical (round 1014)

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
| `} while (phase_complete == 0);` (shipped) | — |
| `} while (!(phase_complete != 0));` | **+0**, byte-identical |
| `if (phase_complete) break; } while (1);` | **+0**, byte-identical |
| inner scan inverted: `for (;;) { if (phase_complete == 0) break; ... }` | **+0**, byte-identical |
| outer `if (phase_complete != 0) { break; } } for (;;) {` | compile error (malformed); not a valid probe |

All three that compiled are byte-identical, so **msvc6 canonicalises loop-condition polarity**: it picks which
edge to encode as the taken branch from the loop's shape, not from how the C condition is written. This is the
same class as §50 (branch polarity) but specific to *loop back-edges*, and it is the reason `ServerMainThread`'s
last 2 edges are unreachable from source.

**This closes `ServerMainThread`'s control-flow lane.** The carrier's 367 residual bytes are not a structural
problem: its CFG differs from the reference's in exactly 2 branch *encodings* out of 280 edges, both polarity,
and the polarity is not addressable from C89. Its remaining residue is the block-placement and register-role
work already documented for it.

### 20. The whole raw-link `.data` divergence is postlink-supplied — so no `.data` content is missing (round 1016)

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
themselves differ in *kind*, not just position —

```
0x10029d00  reference:  a structured record table  {f64 2048.0, 14, 4, 5, 2500}, stride 0x18
            build:      a run of error strings   "gm_AllocSpieler() failed", "cm_ExChangePlayerIdentity() failed"
```

A game TU emitting strings where the reference has a record table reads as a content defect. It is not: the
shipped file is byte-identical at that address, because postlink copies `.data` wholesale from the layout
package.

**The record table is real and unmodelled.** At `0x10029cf0`, stride `0x18`, the reference holds
`{int, int, int, float}` records reading `5 / 2500`, `6 / 3000`, `4 / 2000` — a production cost table. It has no
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

**Why this is not an ordinary canonicalisation.** Variant 1 *did* change the emitted order — it moved
`lea esi,[eax+0xa900]` from instruction 5 to instruction 2, which is where the reference has it. The
streams got **closer** at the fault and the link score still moved by exactly +6, identically for all
three spellings. So the +6 is not "the reorder failed"; it is a downstream cost that the reorder does not
touch, and it is larger than the local gain.

**The reading.** `xor cl, cl` is placed by the scheduler on data dependence (shapes §60), so its position
relative to the guard is not expressible in C — but the *guard's* position is, and moving it reproduces the
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

`ref[6] == bld[7]` and `ref[7] == bld[6]` — verified by decoding both streams. The reference saves `esi`
before the `g_array_ptr == 0` test; we test first.

Two source-order spellings of the entry were measured **at the link**, both reverted:

| variant | link delta |
|---|---|
| swap the two entry guards (`if (size == 0)` before `if (g_array_ptr == 0)`) | **+539** |
| hoist `node = (struct GraphNode*) &g_alloc_root_name;` above both guards | **+61** |

Both are worse, and the second is worse by an amount that tracks nothing local. `push esi` is a callee-save
whose **position** is chosen by the scheduler from liveness; the `cmp` is a guard whose position is chosen
from the source, but moving the guard moves every dependent block with it. **The 2-instruction swap is not
a 2-byte edit to source — it is a scheduling difference whose local form cannot be reproduced without
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

### 23. The 18 carriers fail individually, not from a shared cause — file-mates are byte-identical (round 1040)

An untested hypothesis this session never falsified: that the residue has a **common cause** — a shared
header, a preamble spelling, a flag, or a codegen state introduced once and propagating. If true, one fix
would close all 18 carriers, and the per-carrier wall documentation would be a red herring.

**Falsified. Carriers fail independently of their translation unit.**

**Test 1 — carriers are spread across 11 directories.** `spiel_c` 3, `command_c` 3, `server_c` 3, `game` 2,
and one each in `Error_c`, `loadsave_c`, `friedhof_logic_c`, `vfs_c`, `alchemistry_logic_c`, `m_alloc_c`,
plus `spiel_dumpD.c`. No single TU, module or header set is common to them.

**Test 2 — file-mates of carriers are byte-identical.** Across all 30 multi-function files,
**130 of 137 functions (94.9%)** are byte-identical. The decisive cases are the two files that hold a
carrier *and* other functions:

| file | carriers | file-mates, all residue 0 |
|---|---|---|
| `spiel622.c` | `gm_CalculateProductionValue` `0x10019720`, `gm_CheckInventoryCapacity` `0x10019ed0` | `0x100196c0`, `0x100198b0`, `0x10019a20`, `0x10019a70`, `0x10019ae0`, `0x10019b40`, `0x10019b80`, `0x10019be0`, `0x10019c60`, `0x10019cd0`, `0x10019d00`, `0x10019d30`, `0x1001a060`, `0x1001a0d0` — **14 functions** |
| `spiel_dumpD.c` | `gm_FindNextFilteredEntity` `0x10016f80` | `0x10016cd0`, `0x10016de0`, `0x10016ea0` — **3 functions** |

Same translation unit, same headers, same compiler flags, same object file — and in `spiel622.c`
**14 functions are byte-identical while two are not.**

**What this rules out.** Any explanation of the residue that is a property of the *environment* — a header,
an include order, a `#pragma`, a flag, a toolchain state, a shared type or struct layout — because those are
common to every function in the TU, including the 94.9% that match. **The residue is a property of each
carrier's own code**, which is what the per-carrier class map (`codegen-walls` §13) and the allocator
findings already describe, and it is why 18 separate walls is the correct model rather than one.

**What it does not rule out.** That two carriers can share a *mechanism* — §13's four classes are exactly
that, and register-role rotation is one mechanism across eight carriers. The claim falsified here is a shared
**cause** reachable by a single edit, not a shared **class**.

**Method note.** This is the cheapest high-value test run this session — two `grep`s and a byte compare per
file — and it closes the last structural hypothesis about the residue's shape. Worth running whenever a
residue is described as having "a" cause.

### 24. `gm_AllocSpieler`'s +0xaa fault: three further spellings, none lands (round 1044)

Shapes §109 closed this row's first divergence (at `+0xaa`: the reference emits
`lea edx,[edx+0x100358fc]` where we emit `mov word ptr [ebp],bx` + `xor ebx,ebx` first, then
`lea edi,...`) and measured two reorderings that lose 371 matched bytes and grow the object by 5. Three
further spellings were measured **at the link** this round, all reverted:

| spelling | link delta | verdict |
|---|---|---|
| `memset` hoisted above the two zero-stores (`*(int*)(slot+0x170)`, `*(int*)(slot+0x16c)`) | **+361** | worst — 5.4x §109's recorded loss |
| explicit `int scaled = idx * 0x21c;` local, used for the `-1` fill | **+5** | worse |
| explicit `char* fill = (char*)0x100358a4 + idx*0x21c;` for the `-1` fill | **+0** | inert |

**The first row is the important one.** §109 moved the `memset` call and measured 633/3694 (371 matched
bytes lost). Moving the **two zero-stores instead** — leaving the `memset` where it is — is the same
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
   *which* zero-store you move is not a degree of freedom — only *how many* are moved is.
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
