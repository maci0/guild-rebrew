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

## 7. What would actually move the needle

Ordered by what the evidence says is most likely to pay.

1. **A way to steer the allocator.** This is the dominant obstacle (§1). Nothing in C has been
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
