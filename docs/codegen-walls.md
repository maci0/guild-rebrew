# Codegen walls — where C cannot reach the reference encoding

Places where the C language has no expression that reaches the reference's
encoding, established by exhausting the spellings rather than by giving up.

Companion reading: `msvc6-c-shapes.md` (front-end shapes that do work),
`msvc6-allocator.md` (register allocation and slot maps), `measure-traps.md`
(method traps that fake codegen signal), `TODO.md` (round-by-round history).

---

## 1. Register allocation and scheduling are not steerable from C

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
strict reading is 108,180 bytes. Left in place pending the user's decision; both numbers recorded.

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
