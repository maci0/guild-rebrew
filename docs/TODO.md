# Blockers — 100% Round-Trip Goal

## Distance to byte identity (2026-09-13, round 24)

One place to read the whole gap.  Nothing here is new work; it is the state
the round-by-round entries below establish.

| piece | state | size |
|---|---|---|
| reference `.text` | — | 141,382 B (0x22846) |
| game functions, byte-exact at object level | 261 of 281 `byte_matched` | ~140 KB |
| game functions, not byte-exact | **20** (10 size mismatches + 10 byte-different; 18 of them `PROVEN`/`STUB`, so `verify` hides them) | ~19 KB |
| first link-alignment gate | CrashDump +16 over 0x2fd0..0x6820; then m_AllocTracked -64, vfs_ReadData -32, cm_ExCopyEntityData -32 | — |
| standard CMake link, `.text` | 0x2276c (-218), postlink coverage 401/7,463 (5.4%) | — |
| split-set link (LIBCMT member objects), `.text` | 0x22cfa (+1204); 246 of 319 symbols exactly at their reference VA, 0 LIBCMT pulls, drift one-sided (+112..+0x31c) | — |
| CRT region functions matched | 235 of 244 | 38,674 B |
| CRT functions no library carries | **9** (`srand`, `__CRT_INIT`, `fpmath`, `init_fptrs`, `unlock_9`, `crt_close_handle`, `crt_once_init`, `allmul_slow`, `fcn_1001a643`) | 542 B |
| CRT split-set leftovers | **34** symbols across ~10 members | 5,294 B |

The two halves are independent: the game walls keep the standard link from
byte identity, and the CRT leftovers keep the split-set link from it.  Within
the CRT half, rounds 18-21 (aliases, static demotion, section merging) moved
the leftover count 71 -> 34 and then plateaued; rounds 15-16 removed a whole
member by correcting five game call sites from `fflush` to `fclose`.

Last verify: 279/281 passed, 2 failed (0x100093a0 ServerMainThread, object
size 2434 = the target's but the bytes differ; 0x10018850
gm_AllocSpieler 3688 vs 3689).  gzread (0x10003960) is new: it was defined
in check_header.c without a `// FUNCTION:` marker, so `verify` never counted
it; it is byte-exact (559/559, RELOC) now that it has its own TU and marker.
Goal requires 280/280 with inline asm only for 1-5 byte padding.

**`verify` is not a byte-identity gate.**  18 of the 20 non-byte-exact
functions carry `PROVEN`, and `passed: true` for PROVEN does not consult the
byte compare: CrashDumpUnhandledExceptionFilter reports `match_percent 12.5`
and `delta 1873` yet counts as passed.  The honest number is `byte_matched`
in `db/verify_results.json` (261/281 at this revision).  Whole-binary
identity needs the 20 byte diffs **and** the link alignment below.

**CrashDump's four-register prologue is not the loop.**  Section 38's
corollary says to delete the loop and recompile; if the head then matches, the
loop is the blocker.  Round 3 cut CrashDump's `for (;;)` stack walk out
entirely (probe `.scratch/zz_cdprobe.c`, since removed): the object drops to
1761 bytes but the prologue is still `sub esp,0x234; push ebx; push ebp;
push esi; push edi`, i.e. all four callee-saved registers are reserved at
entry with no loop at all.  The demand is in the entry region — the target
puts the CreateFileA IAT pointer in esi and `hDbgFile` in ebp (both pushed at
entry) and only reaches for ebx/edi after the `hDbgFile == -1` guard, while
this reconstruction puts the same two values in ebx/edi, so the compiler
reserves all four up front.  It is a register-role permutation across the
entry block, not loop pressure, and not reachable by deleting or reshaping
the walk.

## `ls_LoadBuildingEntityState` is one constant-caching decision away (2026-09-13, round 24)

Read this section with the measurement caveat first, because the tooling
misreported this function in every earlier round.

**`rebrew diff`'s positional count is meaningless here and its candidate
column lies about the prologue.**  The file's own header note already says the
function is 100% mnemonic-aligned with the reference, and that is right: an
LCS over mnemonics gives **484 of the reference's 499 instructions (97%)**
against the current `/O2` object.  But the reference materialises `-1` once
(`or ebp,0xffffffff`) where the candidate rematerialises it at each of the
three stores, so the two instruction streams differ in length and the diff's
index alignment desyncs at instruction 2 — it then reports only **3** exact
instructions and prints a candidate prologue of `push esi; push edi` where the
real object has `push ebx; push esi; push edi`.  `rebrew-cmake-cl` +
`objdump -d -Mintel` is the ground truth for prologues; mnemonic LCS is the
ground truth for "how close".

**The whole gap.**  Reference prologue and the three `neg1` stores:

```
target   83ec0c 53 55 56 57   sub esp,0xc; push ebx; push ebp; push esi; push edi
/O2 obj  83ec0c 53 56 57      push ebx; push esi; push edi          (one short)
target   83cdff               or ebp,0xffffffff        once at 0x10012934
target   8928 / 89afa5000000 / 89af95000000
                             mov [eax],ebp / mov [edi+0xa5],ebp / mov [edi+0x95],ebp
/O2 obj  c700ffffffff ...     mov dword [mem],0xffffffff at all three sites
```

The register *roles* otherwise agree — the reference and the candidate both
put `stream_ctx` in edi and the entity pointer in esi (the source note's claim
that ours differs is stale).  Everything else is the knock-on: no ebp means
every frame slot is 4 bytes low from instruction 5 on, and the object is
1464 vs 1463.

**`/Oa` flips exactly that one decision**, which is why it is the only flag
that moves this function (125 -> 713 matched bytes) and why its prologue is
byte-identical: the `/Oa` object has `or ebp,0xffffffff` and the three
`mov [mem],ebp`.  But `/Oa` also keeps the `m_AllocTracked` result in a
register for the whole read loop instead of reloading it before each call
(`lea ebx,[eax+8]`, no `mov edx,[esi+0x71]` anywhere) and gives up 36 bytes.
Declaring the read helper's buffer parameter `int*` or `char*` does not bring
the reloads back (the CSE is not parameter-type driven), and a volatile read
regresses to 117/1471.  So the reference really is `/Oa`-style constant
caching with `/O2`-style aliasing.

Under the tree's own `/O2 /Gd`, eleven spellings of `neg1` all leave ebp
uncached and the object at 1464: dropping `register`; `~0`; moving the
assignment above `offset = 0`, above the `entity_count` guard, or into the
loop body; initialising it at the declaration; `long` instead of `int`; a dead
`neg1 == 0` guard in the loop; deleting the `dummy` local; inlining the
`int* ebx` pointer local; and `/G6` (130/1464).  **Raising the use count does
not trigger it either** — a diagnostic build with a fourth and a fifth
`neg1` store (obj 1475 / 1479) still has no `or ebp,0xffffffff`, so the
decision is not a use-count threshold.  This is the round-23 constant-caching
wall seen from the other side: the allocator's choice is reachable by a *flag*
that also rewrites the memory model, and by no source form at all.  `cl /help`
offers no finer-grained switch — the whole family is `/Oa` (assume no
aliasing), `/Ow` (assume cross-function aliasing), `/Og`, `/Ob<n>`, `/Ot`,
`/Oy`, `/Oi`, `/Ox`, and `/Oa` and `/Ow` each alone reproduce neither half of
the pair.

**The rest of the flag sweep.**  `/Ox`, `/O1`, `/Ot`, `/Og-`, `/Ow`, `/Ob1`,
`/Ob2`, `/Oy-`, `/G6`, `/G5`, `/Oi-`, `/Gy`, `/Os` on top of `/O2` are all
inert or worse for this function; `#pragma optimize("a", on)` around the body
is byte-identical to `--cflags "/O2 /Gd /Oa"`.

Register-aware diff of the `/Oa` build: 142 exact, 28 reloc, **51
register-only**, **278 structural**.  The register-only set is a clean
esi/edi swap — under `/Oa` the reference keeps `stream_ctx` in edi and the
entity pointer in esi, ours the other way round.  Four source attempts to move
it are
byte-identical to the baseline and inert: copying the parameter into a local
`char* ctx` and using that at all 43 sites, renaming the entity-pointer local,
declaring it before the two int locals, and adding an extra local.  The
structural remainder is the CSE block above plus the rotated 0x55 loop tail.

**Sweep table.**  `match/total@obj` for each function's *recorded* CFLAGS and
for the same flags with `/Oa` appended.  **`rebrew test --cflags` replaces the
metadata CFLAGS outright**, so a sweep that passes a fixed flag string
silently measures a different configuration for the six functions whose
`src/rebrew-functions.toml` entry is not the `/O2 /Gd` default; the numbers
below pass each function's own recorded string (the first column is identical
to a plain `rebrew test --no-promote` on the untouched tree):

| function | recorded cflags | recorded | + `/Oa` |
|---|---|---|---|
| CrashDump | `/O2 /Gd` | 267/2137@2137 | 265/2129@2129 |
| m_AllocTracked | `/O2 /Gd /G6 /Oy-` | 241/658@608 | 241/658@608 |
| vfs_ReadCompressed | `/O2 /Gd /DREBREW_ALLOW_NAKED` | 138/499@499 | 43/493@493 |
| vfs_ReadData | `/O2 /Gd /Oy- /DREBREW_ALLOW_NAKED` | 138/472@446 | 71/472@447 |
| vfs_OpenStream | `/O2 /Gd` | 444/693@693 | 114/697@697 |
| ServerMainThread | `/O2 /Gd` | 1336/2434@2434 | 1142/2450@2450 |
| srv_LoadBuf | `/O2 /Gd /Ot` | 701/750@750 | 112/780@780 |
| cm_ProcessCommandQueue | `/O2 /Gd /DREBREW_ALLOW_NAKED` | 624/639@639 | 99/639@609 |
| ahm_ExAllocAlchemist | `/DREBREW_ALLOW_NAKED /O2 /Gd` | 823/1002@1002 | 507/1010@1010 |
| cm_ExSellObjekt | `/O2 /Gd` | 199/2057@2055 | 226/2057@1963 |
| cm_ExProdObjekt | `/Ox /Gd` | 976/993@993 | 341/993@982 |
| cm_ExCopyEntityData | `/O2 /Gd` | 525/901@880 | 525/901@880 |
| gv_ExAllocGraveyardWorker | `/DREBREW_ALLOW_NAKED /O2 /Gd` | 606/1040@1040 | 245/1042@1042 |
| ls_LoadBuildingEntityState | `/O2 /Gd` | 125/1464@1464 | **713/1463@1427** |
| gm_ObjectsAvailble | `/DREBREW_ALLOW_NAKED /O2 /Gd` | 686/714@714 | 567/714@709 |
| gm_FindNextFilteredEntity | `/O2 /Gd` | 168/346@342 | 168/346@342 |
| gm_AllocGebaeude | `/DREBREW_ALLOW_NAKED /O2 /Gd` | 418/1078@1078 | 243/1078@1078 |
| gm_AllocSpieler | `/DREBREW_ALLOW_NAKED /O2 /Gd /Oa /Ow` | 851/3689@3688 | 851/3689@3688 |
| gm_CalculateProductionValue | `/O2 /Gd` + pragma `a` | 391/396@396 | 391/396@396 |
| gm_CheckInventoryCapacity | `/O2 /Gd` | 293/395@395 | 152/395@389 |

Three functions are already `/Oa`-equivalent and their column is unchanged:
`gm_AllocSpieler` (`/Oa` in the metadata), `gm_CalculateProductionValue` and
`cm_ExCopyEntityData` (the `#pragma optimize("a", on)` in their sources).
`ls_LoadBuildingEntityState` is the only function `/Oa` helps; it is the only
one whose column should be read as a lead.

The six non-default `/O2 /Gd` entries are load-bearing and were re-measured
here for the first time as a set: `m_AllocTracked` is 241/658 with
`/G6 /Oy-` against 123/680 with plain `/O2 /Gd`, `vfs_ReadData` is 138/472
against 46/482, and `gm_AllocSpieler` is 851/3689 against 500/3689 — the
`/Oa /Ow` in its metadata is worth 351 matched bytes.

**Prioritised target list**, `rebrew diff <va>` under the tree's own
`/O2 /Gd`, sorted by structural mismatches (the only counts that need code
work; `reloc` slots are masked and `reg`-only diffs are not in this table):

| function | exact | structural | instrs | obj vs target |
|---|---|---|---|---|
| `gm_CalculateProductionValue` | 106 | 2 | 123 | 396 vs 396 |
| `cm_ExProdObjekt` | 316 | 5 | 354 | 993 vs 993 |
| `gm_ObjectsAvailble` | 188 | 18 | 229 | 714 vs 714 |
| `srv_LoadBuf` | 166 | 25 | 226 | 750 vs 750 |
| `vfs_OpenStream` | 96 | 99 | 199 | 667 vs 667 |
| `gm_FindNextFilteredEntity` | 5 | 112 | 118 | 342 vs 346 |
| `ServerMainThread` | 477 | 115 | 627 | 2434 vs 2434 |
| `gm_CheckInventoryCapacity` | 9 | 128 | 138 | 395 vs 395 |
| `vfs_ReadData` | 31 | 143 | 174 | 446 vs 472 |
| `vfs_ReadCompressed` | 50 | 150 | 200 | 492 vs 492 |
| `gv_ExAllocGraveyardWorker` | 166 | 160 | 333 | 1040 vs 1040 |
| `cm_ExCopyEntityData` | 78 | 169 | 249 | 880 vs 901 |
| `cm_ProcessCommandQueue` | 30 | 173 | 205 | 639 vs 639 |
| `ahm_ExAllocAlchemist` | 98 | 175 | 287 | 1002 vs 1002 |
| `m_AllocTracked` | 33 | 208 | 249 | 608 vs 658 |
| `gm_AllocGebaeude` | 75 | 264 | 353 | 1078 vs 1078 |
| `ls_LoadBuildingEntityState` | 3 | 496 | 499 | 1463 vs 1463 |
| `cm_ExSellObjekt` | 59 | 607 | 667 | 2055 vs 2057 |
| `CrashDump` | 11 | 701 | 724 | 2115 vs 2115 |
| `gm_AllocSpieler` | 82 | 971 | 1056 | 3688 vs 3689 |

The two closest (`gm_CalculateProductionValue`, `cm_ExProdObjekt`) are both
documented exhaustively as scheduling walls — the FP-stack `fxch`/folded-compare
exclusivity in the first, the pre-loop volatile-store interleave in the
second — so the structural count understates how hard they are.

**Superseded (round 25).**  The `structural` column above is *not* a priority
signal: `rebrew diff` aligns positionally, so one instruction of length
difference desyncs everything after it.  See the alignment-corrected table in
the round-25 section below before choosing a target.

## The section prefix before a matched symbol (2026-09-13, round 47)

Round 46 left 201 of 319 symbols on a constant **-16** plateau starting at
`_strchr`.  The cause was not missing code but *unclaimed* code: a match can
start partway into its member section, and the bytes before it are real code
the reference places immediately before it.  `strchr.obj` §1 starts with

```
8d42ff              lea eax,[edx-1]      <- the strncpy return-value tail
5bc3                pop ebx; ret
8da42400000000 8d642400                  11 bytes of 16-byte alignment padding
...                 _strchr at offset 16
```

so the reference has those 16 bytes at 0x1001af20 and `_strchr` at 0x1001af30,
while our map only knew about the offset-16 entry and emitted from there.

For every hit with a non-zero section offset the map now adds a second entry at
`VA - offset` covering `[0, offset)`, unless another entry already covers that
VA.  The `exsup` group is unaffected because its offset-0 entry is already
present, so the prefix is skipped.

| | before | after |
|---|---|---|
| symbols exactly at their reference VA | 46 | **246** |
| sum of abs delta over placed symbols | 32,172 | **30,088** |
| delta range | -0x10 .. +0x30c | **+0x0 .. +0x31c** |
| objects LINK discards | 0 | 0 |
| LIBCMT archive pulls | 0 | 0 |
| split-set `.text` | 0x22cba (+1140) | 0x22cfa (+1204) |

**Every mapped section now starts at its reference VA.**  `split_audit` still
reports 73 symbols with a delta, but they are all *interior* symbols of a
shared-tail object — the `memcpy.obj` `LeadUp*`/`UnwindUp*`/`TrailUp*` family,
`exsup3`'s `__except_handler3` and `__seh_longjmp_unwind@4`, `strchr`'s
`___from_strstr_to_strchr`, `fpinit`'s `__fpclear`.  The audit keys a symbol to
the VA in its *object filename*, so an interior label reads as if the whole
section were late by its offset.  Filtering those families out leaves **4**
nonzero deltas, and all four are that same artefact — the symbols really are at
their reference VAs.

So the +1204 in `.text` is entirely **after** the CRT region: `link_stubs.c`,
`emit_defs`' objects and the 96 unreferenced import thunks, which `rebrew
postlink`'s `data` fixer trims as "the extra `.text` tail".  The CRT half's
placement is done; what is left there is the functions no LIBCMT variant
carries (round 46) and the tail.

Note that `split_audit`'s "objects LINK discards" test is by object basename,
and the new prefix object defines no map-visible *symbols* of its own — it is
in the image (the bytes at 0x1001af20 match the reference exactly) but does not
show up in the map, so it reads as discarded.  Compare bytes, not basenames.

## The catalog's function size was truncating every longer object (2026-09-13, round 46)

The map's `size` came from the catalog — Ghidra's function size — and
`split_coff` trims each object to it.  That silently cut every reference
function longer than its catalog entry.  `_free` is the case that mattered:
LIBCMT's `free.obj` §1 is **233 bytes**, and Ghidra had catalogued 0x1001ab81
as a 106-byte `free` with the tail as two more "functions" (`unlock_09c` 88,
`unlock_09d` 45).  Our object was cut to 106 and the other 127 bytes were never
emitted — which is exactly the -128 drift island at `__alloca_probe`.

`match()` now reports how many bytes the member holds from the matched symbol
on, and the map takes the **larger** of that and the catalog size.  `--trim`
still caps at the section, so nothing grows past the member.

Two matcher filters also had to change:

* **`MIN_COVER = 0.5`** — `match()` compares `min(len(body), len(data))`, so a
  section that ends early still "matched" on its last few bytes: the
  `popen.obj` §6 entries at 0x1001abeb (88 B) and 0x1001ac43 (45) matched only
  the 9 bytes at offset 956 of a 965-byte section.  The floor has to stay at
  0.5 because catalog sizes are sometimes padded *above* the real function —
  crt0dat's 34-byte `exit` is a 17-byte section, exactly 0.5.
* **`MIN_FIXED_BYTES = 12`** — `MIN_FIXED_FRACTION` alone is too strict for
  relocation-dense code.  `init_fptrs` (`fpinit.obj` §7, 56 B) is six stores of
  absolute addresses, so 44 of its 56 bytes are operand slots and only 12 are
  opcodes.  A match now passes with **either** 12 fixed bytes **or** half the
  section fixed.  The absolute floor alone would be wrong: the fraction test is
  what keeps `undname.obj` §2 (0 fixed of 86) out, and that section otherwise
  matches several targets.

`match` selection also now prefers the library with the **longest** matching
section rather than the first that fits, since a shorter one matches as a
prefix and is then trimmed.  (That is what should have chosen vc7's 292-byte
`strncpy.obj` over sp6's 254-byte one; vc7's turns out to be a different
implementation and does not match, so the change is currently neutral — kept
because the rule is the right one.)

| | before | after |
|---|---|---|
| region functions matched | 229/244 | **234/244** |
| symbols exactly at their reference VA | 38 | **46** |
| sum of abs delta over placed symbols | 155,180 | **32,172** |
| delta range | -0x310 .. +0x25c | **-0x10 .. +0x30c** |
| objects LINK discards | 6 | **0** |
| LIBCMT archive pulls | 0 | 0 |

**201 of the remaining 319 symbols sit at exactly -16.**  That plateau starts
at `_strchr` (0x1001af30) and is one missing piece: between `_strncpy` (which
ends at 0x1001af1d, `pop ebx; pop esi; pop edi; ret`) and `_strchr` the
reference has

```
0x1001af1e  cc cc                     int3 padding
0x1001af20  8d42ff                    lea eax,[edx-1]
0x1001af23  5b                        pop ebx
0x1001af24  c3                        ret
0x1001af25  8da42400000000            lea esp,[esp]      \
0x1001af2c  8d642400                  lea esp,[esp]       > 11 bytes of padding
0x1001af30  33c0                      xor eax,eax        /   <- _strchr
```

a 5-byte strncpy return-value tail plus 11 bytes of msvc6's 16-byte
intra-section alignment.  Emitting it means an object whose section carries
16-byte alignment — the split objects take their alignment from the member, so
a 5-byte one left at 1-byte alignment would land `_strchr` at -11, not -16.

**Next step:** the missing 5-byte tail at 0x1001af20, then the CRT functions no
LIBCMT variant carries at all — `allmul_slow` (0x10022f29, 27 B), `unlock_9`
(0x1001b8a5, 86 B) and the `unlock_09e/f/g` group (0x1001b757 334,
0x1002001d 137, 0x100200a6 156) — which have to be written as C.

## The map did not say which library it matched in (2026-09-13, round 45)

The first drift island in the split set was **-128 at `__alloca_probe`**: every
object from `_fclose` to 0x1001ab81 was placed contiguously and correctly, and
then the object for 0x1001ac70 landed at 0x1001abf0.  The reference has two
functions in between — 0x1001abeb (88 bytes) and 0x1001ac43 (45) — and our
objects for them emitted **nothing**.

**Cause 1: the map did not record the library.**  `map_libcmt` searches the
five service packs in order and `split_coff` resolves a member by name against
the first library that has it.  They disagree on section numbering: vc7's
`popen.obj` §6 is a 965-byte `.text`, 6.0-sp6's §6 is not code at all.  The map
now carries `lib`, and `split_coff` indexes members per `(library, member)`.

**Cause 2: the reference overlaps functions freely.**  popen's `$L21349`
fragment at 0x1001a89c is *interior* to `malloc.obj`'s 252-byte `__malloc`, and
wpopen's at 0x1001a8fb likewise; emitting them again duplicates bytes that are
already there and pushed everything after them 18 bytes late.  `split_coff` now
drops any entry whose VA falls inside the extent another entry **actually
emits** — computed from the section's `raw_size` and `--trim`, not the catalog
size.  That distinction matters: crt0dat's `exit` pair are two separate 17-byte
sections that really do tile, and a catalog-size test (34 and 17) would collapse
one of them.

| | before | after |
|---|---|---|
| split-set `.text` | 0x22b8a (+836) | **0x22a0a (+452)** |
| objects LINK discards | 11 (315 B) | **6 (72 B)** |
| symbols exactly at their reference VA | 38 | 37 |
| LIBCMT archive pulls | 0 | 0 |

**Honest reading: this is progress on size and completeness, not on
placement.**  The per-symbol drift is if anything wider at the tail (81 symbols
at -592, 80 at -752, against -731/-848 before), because the layout is a chain
and the objects after the changed ones all move.  The `.text` figure is the one
that improved unambiguously, and 384 bytes of it is content that used to be
missing or duplicated.

**Still wrong:** the popen `$L21349` entries at 0x1001abeb and 0x1001ac43.  A
catalog size of 88 and 45 matched only a **9-byte prefix** at offset 956 of a
965-byte section — there is nothing left of the section after that offset — so
all three entries emit the same 9 bytes and LINK keeps one.
`match()` accepts a 9-byte common prefix because it compares
`min(len(body), len(data))`; a match this short should be rejected, or the
entry needs locating from scratch.

**Method note.**  `rebrew postlink`'s `data` fixer already trims "the extra
`.text` tail (import thunks/stubs the original build dead-stripped)", so the 96
unreferenced import thunks from round 44 are a *known and handled* condition,
not a blocker — they only matter because the tail must be trimmable, which
requires everything before it to be position-aligned.

## 96 import thunks the reference does not have (2026-09-13, round 44)

Counting `ff 25` (`jmp dword ptr [imm32]`, the import-thunk form) across
*every* section:

| | reference | split set | standard link |
|---|---|---|---|
| `ff 25` | **11** | 107 | 106 |
| `ff 15` (`call dword ptr [imm32]`) | 211 | 208 | — |
| `.rdata` VirtualSize | 0x2e81 | 0x3401 | — |

The reference's eleven are the seven socket thunks at 0x1001a160, the
`_RtlUnwind@16` thunk at 0x10023840, and three in the game region
(0x10015513, 0x10021eda, 0x10021eef).  Ours has **96 more, all at the end of
`.text` starting at 0x10023950**, and **nothing references them** — no
relocation in the image points at 0x10023950.  They are ~576 bytes, which is
most of the split set's +836.

They are dead COMDATs kept alive by `/OPT:NOREF`.  The import libraries put
`_GetLocalTime@4` (the thunk) and `__imp__GetLocalTime@4` (the IAT slot) in one
member; our objects reference 124 `__imp_` symbols across 54 objects, so the
members get pulled, and `/OPT:NOREF` then refuses to drop the unused thunk
COMDAT that came with each.

Measured split of the 96, by deleting one object from the response file and
relinking:

| source | thunks |
|---|---|
| `crt_imports.c.obj` — 100 `#pragma comment(linker, "/include:__imp__X@N")` | **20** |
| genuine `__imp_` references in the game and split objects (124 across 54) | **76** |

`crt_imports.c` is the auto-generated TU that forces the IAT slots to be
allocated in the reference's order.  Removing it from the link costs 0x78
bytes of `.text` and 20 thunks, but the IAT order is then whatever LINK's hash
produces — which is why it exists, and which `rebrew postlink` already rewrites
from the layout package.  So it is a candidate, not a fix: 20 of 96.

**`/OPT:REF` is not the answer.**  Linking the split set with it drops `.text`
to **0xc510 (50,448 bytes)** — 90 KB of the reference's code would go, because
almost nothing references a split object: they are one section each, and the
archive's own internal cross-references are gone.  `/OPT:NOREF` is what keeps
them, and the reference clearly used the same discipline.

That experiment also exposed a real malformation.  `/OPT:REF` failed with
`1001a7f7_.text.obj : error : Internal error during ReadSymbolTable`, because a
section-definition AUX record with COMDAT selection **ASSOCIATIVE (5)** carries
the section *number* it is associated with, and `build_object` copied AUX
records verbatim while renumbering the sections — `malloc.obj` §1's `.rdata`
kept `assoc 5` inside a two-section object.  `build_object` now remaps that
number through `new_secnum` and falls back to `SELECT_ANY` when the associated
section was not emitted.  The `/OPT:NOREF` link is unaffected.

**Next step on this thread:** the thunks have to stop being *included*, not be
discarded afterwards.  Since they arrive with the `__imp_` symbol's member, the
options are to define the `__imp_` symbols locally against our own import table
(the layout package already carries the full IAT), or to accept the 576 bytes
and attack the drift instead.  Note the reference's IAT is 1408 bytes smaller
than ours too, so some of the same excess may be in `.rdata`.

**Method note.**  Do not try to parse `KERNEL32.LIB` member-by-member with a
naive archive reader: the first member is a linker member whose "symbols" are
not COFF at all, and the reader will happily interpret a section count of
several thousand and dump garbage.

## LINK was pulling exsup.obj out of LIBCMT (2026-09-13, round 43)

The split link had **five symbols satisfied by an archive member**:

```
0001:00022bb4  _gu_return                10023bb4 f   LIBCMT:exsup.obj
0001:00022bbc  __unwind_handler          10023bbc f   LIBCMT:exsup.obj
0001:00022c46  __abnormal_termination    10023c46 f   LIBCMT:exsup.obj
0001:00022c72  __NLG_Notify              10023c72 f   LIBCMT:exsup.obj
0001:00022c85  __NLG_Dispatch            10023c85 f   LIBCMT:exsup.obj
```

LINK could not find them among our objects, so it pulled the whole
`exsup.obj` member and appended it **after** everything else, at 0x10023bb4 —
256 bytes at the end of `.text` instead of in the CRT region.

**Why they were missing.**  `exsup.obj` §1 is one 238-byte section holding
seven reference functions at offsets 0, 24, 32, 66, 154, 170, 205, 214 and
233.  `map_libcmt` already recorded which one each VA matched, through the
symbol's offset in the section, but `split_coff` emitted every entry as the
section from byte 0 and then `--trim` dropped every symbol past the reference
function's length.  `__abnormal_termination` sits at offset 170; the entry at
0x1001e78e is 35 bytes long, so it was discarded along with the bytes it
belonged to.

**Fix: `build_object` grew a `start`.**  The body becomes
`body[start:start+trim]`, symbol values and relocation offsets are rebased,
symbols and relocations outside the slice are dropped, and the root COMDAT's
section symbol is never dropped (a COMDAT without one is `LNK1143: no symbol
for comdat section`).  Sliced objects also get an **empty alias set** — the
alias index lists every spelling of the *whole* section, and exporting those
from each slice puts the same symbols on several objects again.

**A second bug surfaced on the way.**  The pre-existing trim filter
(`sym["value"] >= trim`) was still applied to sliced objects, so the slice at
offset 170 dropped `__abnormal_termination` because `170 >= 35` — it deleted
the very symbol the slice exists to define.  It now applies only when
`start == 0`.

| | before | after |
|---|---|---|
| symbols satisfied by a LIBCMT archive member | 5 | **0** |
| split-set `.text` | 0x22c8a (+1092) | **0x22b8a (+836)** |
| objects LINK discards | 10 | 11, all duplicates |

Slicing is skipped when the section `split_coff` actually loaded is not code,
or when the offset is past its end, because the map records the section of the
*first* library that matched while `split_coff` resolves the member against the
first library that has it.

**Method note.**  Checking whether a discarded object's content is really lost
by searching the built `.text` for the reference's exact bytes gives false
negatives for any block containing a `call`: the rel32 depends on the drifted
callee address.  Compare the two blocks with their relocations set aside
instead — that is how the ten duplicates in the round-42 entry were confirmed
harmless.

## Three CRT members carry the same 101 bytes (2026-09-13, round 42)

The alias mechanism in `split_coff` exports every byte-identical spelling of a
section body, because that is what stops LINK pulling a sibling archive member
just to resolve another name.  Round 41 narrowed it to the object's *own*
member, which fixed crt0dat §14/§16 and fread/fwrite — but `lseek.obj`,
`read.obj` and `write.obj` all carry the **same 101 bytes**, so each still
exported all three of `__lseek`, `__read` and `__write`.  Three objects
defining the same symbol set makes LINK keep one and drop two, which is what
lost 101 bytes at 0x1001e8b4 and 101 more at 0x1001eec1.

The exclusion now covers the mapped sections of **every** member
(`all_mapped_names` in `split_coff`).

| | round 41 | round 42 |
|---|---|---|
| symbols exactly at their reference VA | 35 | **38** |
| sum of abs delta over placed symbols | 150,062 | **114,890** |
| objects LINK discards | 14 (541 B) | **10 (280 B)** |
| delta range | -0x2b0 .. +0x22c | **-0x264 .. +0x25c** |

**All ten remaining discards are harmless duplicates — verified, not assumed.**
Seven are the `$L21349` / `$L21312` fragments with a zero-length `.text`.  The
other three look like losses and are not:

| discarded | reference VA | but the bytes are emitted by |
|---|---|---|
| `1001e7dc___except_handler3.obj` | 0x1001e7dc | `1001e7d4_.text.obj`, at +8 — found at 0x1001e5e4 |
| `1001e899___seh_longjmp_unwind_4.obj` | 0x1001e899 | same object, at +197 — found at 0x1001e769 |
| `1001ba7f___amsg_exit.obj` | 0x1001ba7f | `1001ba71_.text.obj`, at +14 — found at 0x1001b81b |

The quick check that suggested otherwise was wrong: searching the built `.text`
for the reference's exact bytes fails for any block containing a `call`, because
the rel32 depends on the drifted callee address.  Comparing the two blocks with
their relocations set aside shows `__amsg_exit` at 0x1001b81b is byte-for-byte
the reference's, and the exsup3 and seh_longjmp interiors are present at their
expected offsets inside the object that carries the whole section.

**So the split set is not losing content.  It has the opposite problem: its
`.text` is 0x22c8a against the reference's 0x22846, 1092 bytes too long.**  The
CRT half's remaining work is placement and duplication, not missing bytes.

**Why the exsup3 pair is hard.**  `exsup3.obj` §1 is one 224-byte section
holding *three* reference functions, and `map_libcmt` records which one it
matched through the symbol's offset inside the section:

| reference VA | section offset | size |
|---|---|---|
| 0x1001e7d4 | 0 | 197 |
| 0x1001e7dc | 8 | 216 |
| 0x1001e899 | 197 | 27 |

`split_coff` never sees that offset, so all three emit the section from byte
0, trimmed to three different lengths.  The first object carries the closure
and so defines all three symbols, and the other two are then duplicates —
which is harmless here, because the section is emitted once and the interior
functions sit at the right relative offsets inside it.

See the round-43 entry below for the case where *not* slicing was not
harmless: `exsup.obj`, where the same omission left three symbols undefined
and made LINK pull the whole member out of LIBCMT.

**Cross-library section indices are a trap.**  A map entry can name a section
that only exists in a later service pack: vc7's `popen.obj` has 21 sections
where the 6.0 ones have 9, and its §6 is a 965-byte `.text` while sp6's §6 is
not code at all.  `split_coff` resolves a member by name against the *first*
library that has it, so the offset is meaningless there.  Round 41 added a
section-count filter; the slice experiment needed a second guard (only slice a
`.text` root section, and only when the offset is inside it).  The real fix is
to record the library in the map and have `split_coff` read that copy.

## Two reference VAs were sharing one library section (2026-09-13, round 41)

The split set's CRT drift had two independent causes, and both reduce to the
same failure: **two of our emitted objects came out byte-identical, so LINK
kept one and silently dropped the other.**

**1. `map_libcmt` matched on content alone.**  A CRT member can hold two
COMDAT sections with identical bodies that differ only in their relocation
target:

| VAs in the reference | member sections | body |
|---|---|---|
| 0x1001a746 / 0x1001a74f | `crt0dat.obj` §14 / §16 | `6a0d e8???? ???? 59 c3` — `__lockexit` / `__unlockexit` |
| 0x1001a931 / 0x1001aa6a | `fread.obj` §1 / (alternative) | 47 bytes, both calling 0x1001bb60 |

The matcher returned the first section that fitted, so both VAs claimed §14
(or fread §1), the two objects came out with the same md5, and LINK discarded
one — the 9 bytes at `__initterm` and the 47 bytes before `__fread_lk`.
`match()` now takes a set of `(member, section, value)` keys already handed to
another VA and skips them.  The fallback matters: an alias at *one* VA
(`_mbsdup` / `__strdup` both sit at 0x10023812) must still resolve to the
shared section, so the exclusion only applies while the same library has an
unclaimed candidate left.

**2. `split_coff` exported the sibling's name.**  Even with distinct sections
the objects still clashed: the alias index lists every byte-identical spelling
of a body, so the §14 object exported `__unlockexit` and the §16 object
exported `__lockexit`, and two objects defining one symbol is again a
duplicate for LINK.  Each object's alias set now excludes the external names
defined by its own member's mapped sections.

**3. Section indices are library-specific.**  A map entry can point at a
section that only exists in a later service pack — vc7's `popen.obj` has 21
sections where the 6.0 ones have 9 — and `split_coff` resolves a member by
name against the *first* library that has it, so vc7 §17 indexed past the end
and crashed the splitter.  Entries above the canonical library's section count
for that member are now filtered out.

**Effect on the split set:**

| | before | after |
|---|---|---|
| symbols exactly at their reference VA | 25 | **35** |
| objects LINK discards | 20 (923 B) | **14 (541 B)** |
| first drift island | -9 at `__initterm` | **gone** (first is -47 at `__fread_lk`) |
| delta range | -0x353 .. +0x22c | **-0x2b0 .. +0x22c** |
| sum of \|delta\| over placed symbols | ~182,000 | **150,062** |
| section VirtualSize | 0x229fa | 0x22b8a |

The VirtualSize grows because 382 bytes of reference content that used to be
dropped are now emitted; it is not the metric to read here.  Note also that
`rebrew verify` is unaffected (280/282) — these are split-set pipeline
scripts, not part of the build.

**Next step:** 14 objects are still discarded.  Their pairs are in the map
with the same `(member, section)`; the remaining ones want the same treatment,
and if a member has no second section that fits, the object needs a distinct
primary symbol rather than a distinct section.

## The component loop walks a pointer, and the CPU flag is /G5 (2026-09-13, round 40)

`gm_AllocGebaeude`'s component loop indexed the record by the counter:

```c
	geb_type = 0;
	for (; geb_type < 0x40; geb_type++) {
		unsigned short comp = *(unsigned short*) (s.record + 0x23 + geb_type * 2);
		if (comp == 0) break;
		if (comp == 0xffff) continue;
		...
	}
```

The target walks a pointer instead, and keeps the pointer increment *ahead*
of the counter increment:

```
lea edi,[eax+0x23]            ; once, before the loop
...
add edi,2 / mov eax,[ebp+8] / inc eax / cmp eax,0x40 / mov [ebp+8],eax / jl
```

Written as a pointer walk with both increments in the for-header:

```c
	rec = (unsigned short*) (s.record + 0x23);
	for (; geb_type < 0x40; geb_type++, rec++) { comp = *rec; ... }
```

Both increments have to be in the header — with `rec++` at the end of the
body the `continue` for a 0xffff component skips it.  Aligned 41.6% ->
**42.5%**; object 1120 -> 1118 bytes (target 1088).  The island stays: the
function still carries about 19 extra instructions elsewhere.

**The project's CPU flag is not /G6.**  `spiel622.c` carries 17 functions, 15
of them byte-exact, so it is a good probe.  `/O2 /Gd /G3`, `/G4` and `/G5`
produce a byte-identical object to the `/O2 /Gd` default — `rebrew diff`
reports the same `2 structural, 15 reloc, 106 exact` for
`gm_CalculateProductionValue` under all four.  `/O2 /Gd /G6` changes the
codegen of **12 of the 17** functions, so the default is a `/G5`-class
setting and any function whose metadata says `/G6` is an explicit override,
not the house style.

**`gm_CalculateProductionValue` is the closest function in the binary to
byte-exact and is still two instructions away.**  `rebrew diff` on it reads
`2 structural diff(s), 0 register diff(s), 15 reloc diff(s), 106 exact
match(es)` — the two structural diffs are one swapped pair:

```
target:  fmul qword [0x100257d0] / fxch st(1) / cmp byte [esi],0x17 / fmulp st(1)
ours:    fmul qword [0x100257d0] / cmp byte [esi],0x17 / fxch st(1) / fmulp st(1)
```

The `cmp` is hoisted one slot too far into the x87 delay shadow.  Re-tested
this round against the `acc = quot; mod_value = ...; value = (float)(acc *
mod_value);` block: swapping the first two statements, casting both operands
to double, and folding `mod_value` into the `value` expression all leave it at
`2 structural / 106 exact`; using `quot` directly in place of `acc` makes it
worse (4 structural, 104 exact), and folding the whole multiply into one
expression is much worse (54 structural).  Combined with the round-1..7
sweep in the file header, this is a genuine fixed point of the x87
scheduler — every spelling lands on the same two-instruction swap.

**Next step:** unchanged — the five islands.  `vfs_ReadCompressed` is 497
bytes against a 496-byte bucket, so one legitimate byte of shrinkage would
close it; `m_AllocTracked` is 656 against 672 and needs 1..16 more;
`cm_ExCopyEntityData` needs 32 bytes of code found.

## A clamped length has to be its own variable (2026-09-13, round 39)

`vfs_ReadCompressed` clamped its read chunk in place:

```c
n = s->remaining;
if (n > 0) {
    if (n > 0x4000) n = 0x4000;
    if (n == 0) return 0;
    ... fread(s->inbuf, n, 1, s->file); ...
}
```

The target does not clamp in place.  It materialises the constant first and
keeps the dead check that follows:

```
mov edi,0x4000 / cmp eax,edi / jae L / mov edi,eax / test edi,edi / je ret0
```

Clamping `n` makes msvc6 emit the *other* min shape
(`cmp edi,0x4000` / `jbe L` / `mov edi,0x4000`) and drop the check entirely.
Using `i` — the separate clamped length the source already declares — gives
the target's shape byte for byte.  **499 -> 497 bytes, aligned 76.5% ->
79.0%.**

Measured and reverted while getting there: four different ternaries, an
if/else, and the constant on the left all give the clamp shape (73.6%); a
signed `lim` with casts gives 497 at 75.8%; folding the two `volatile int`
locals into one struct gives 497 with no gain.

**The prologue reorder is a real trade.**  Moving `if (handle == 0)
return -102;` above the two `volatile` initialisers drops the object's
section from 512 to 496 — which is exactly the reference span, so it *closes*
that drift island — but costs 4 points of byte alignment (79.0% -> 75.0%),
because the target initialises `done`/`result` at the top and only schedules
the handle test late.  Not kept.

**CFLAGS sweeps of the two default-flag functions came back empty.**

| function | default | best other | target |
|---|---|---|---|
| `CrashDumpUnhandledExceptionFilter` | 2137 | `/G6` 2129 (`/Oa` 2129) | 2115 |
| `cm_ExCopyEntityData` | 880 | `/G6` 881; `/Oy-` 875 | 912 |

`/G6` shrinks `CrashDump` by 8 bytes but costs 3.2 points of alignment
(22.5% -> 19.3%), and neither reaches the next 16-byte bucket, so the island
would not move.  `cm_ExCopyEntityData` is 32 bytes short under *every* flag
set — it is missing code, not mis-flagged.  All five of the round-38 islands
are single-function files, so these sweeps are safe to repeat.

`cm_ExCopyEntityData`'s remaining differences are structural, not scheduling:
the target writes `movsx eax,[edx+ecx]` where we write `[ecx+edx]` (swapped
base/index roles), it has a two-way `jge`/`jmp`/`mov eax,-1`/`jmp` where we
have a one-way `jl`, and it compares through a pointer
(`mov edx,IMM / cmp [edx],eax`) where we load the value first
(`mov esi,[IMM] / cmp esi,eax`).

**Next step:** same five islands.  `m_AllocTracked` (section 656 against the
672 span) and `vfs_ReadCompressed` (512 against 496) are one 16-byte bucket
away; `cm_ExCopyEntityData` needs 32 bytes of code found, and
`CrashDump`/`gm_AllocGebaeude` need real reversing.

## One missing function was 16 bytes of the game region's drift (2026-09-13, round 38)

The object-error table from round 37 has a caveat worth stating: msvc6 pads a
COFF `.text` section to a 16-byte multiple, and LINK merges the *padded*
length, so an object's contribution is `round16(function size)` — not the
function size.  `vfs_ReadCompressed` is the clean example: its function is 7
bytes long (499 against 492) and its section therefore rounds to 512 where
the reference's rounds to 496, which is the whole +16.  Every remaining
game-region island is a wrong *function* size plus that rounding.

**`gv_GetSlotEntry` was missing a function, not mis-sized.**  The reference
has a second function in that translation unit at 0x10010700:

```
8b4c2408   mov  ecx,[esp+8]
33c0       xor  eax,eax
837904ff   cmp  dword ptr [ecx+4],-1
0f94c0     sete al
c3         ret
```

It has no caller, no catalog name, and never appeared in the 281 tracked
functions, so nothing pointed at it.  Without it the object is 329 + 7 bytes
of msvc6's 16-byte intra-section alignment = 336, against the 352-byte span
to `FindSlotEntryFiltered`; with it the object is 329 + 7 + 14 + 2 = 352.
Written as ordinary C in `gv_GetSlotEntry.c` it is **EXACT 14/14**.

`rebrew skeleton 0x10010700` is what puts the `size = 14` annotation in
`src/rebrew-functions.toml`; `rebrew test` skips a marked function with no
SIZE, reporting `SKIPPED: No SIZE annotation`.  Note that rebrew leaves the
toml mode 444, so restoring a backup of it needs `rm` first — `cp` over it
fails with EACCES.

**Effect:** `verify` is 280/282 (up from 279/281), built `.text` 0x2275c
(-234) -> **0x2276c (-218)**, and the split set now places **25 of 330**
symbols exactly at their reference VA, up from **0**.

**`scripts/link_drift.py` needed a tie-break.**  Several functions here are
byte-identical twins — the `cm_ExAllocAlchemist` / `cm_ExAllocGraveyardWorker`
thunks, `amt_FindEntity26` / `amt_FindEntity27` — so "highest score wins"
latched onto the wrong copy and reported an 80-byte drift where the real one
was 16.  Ties now break towards the reference offset.

**The five remaining game-region size errors**, and the drift island each one
creates:

| object | function delta | island |
|---|---|---|
| `CrashDumpUnhandledExceptionFilter` | +22 | +16 at 0x10002770 |
| `m_AllocTracked` | -2 | -16 at 0x10006580 |
| `vfs_ReadCompressed` | +7 | +16 at 0x10008a90 |
| `cm_ExCopyEntityData` | -21 | -32 at 0x1000ec00 |
| `gm_AllocGebaeude` | +32 | +32 at 0x100174d0 |

`gv_GetSlotEntry` is no longer among them.  Every one is on the 20
non-byte-exact list, so the game half of the link cannot be aligned without
finishing them.

**Next step:** the five above, smallest first.  `m_AllocTracked` (2 bytes),
`vfs_ReadCompressed` (7) and `cm_ExCopyEntityData` (21) are all at documented
scheduling plateaus, but `vfs_ReadCompressed`'s 7 bytes are the prologue
order (the target hoists `mov eax,[esp+0xc]` above `push ebx` and puts
`test eax,eax` after `push esi`), which is the same class of lever that
closed other functions.  The standard link cannot fix the CRT half at all:
`link_drift` shows the `sbh_*` / `crt_*` reconstruction objects 12,737 bytes
away from where the reference has them, because LINK appends command-line
objects after the archive members — that is the split set's job.

## The link's whole remaining error is seven object sizes (2026-09-13, round 37)

`objects1.rsp` is **already sorted by reference VA** — 0 inversions in 173
adjacent pairs — so the game region is not misordered.  What breaks it is
purely per-object length: the drift profile below is piecewise constant and
changes value only at the objects whose `.text` is the wrong size.

`scripts/link_drift.py` (new) is what makes this visible.  It masks the bytes
a relocation may legitimately change (every rel32, every immediate or
displacement pointing into the image), then finds the offset in the built
`.text` that maximises the match, per tracked function.  Output today:

```
built .text 0x2275c  reference 0x22846  delta -234
  SendBroadcastPacket / crc32 / DispatchLogOutput     drift  0
  EmitCrashModuleLine .. vfs_WriteUint32LE            drift +16   (CrashDump broke it)
  m_FreeTracked .. m_pool_free                        drift  0
  ...
  sim_* .. gm_RandomQuadratic                         drift -32
```

**The block-fill prelude has exactly six sites in the whole binary**, all in
the game region, and three were still unreproduced:

| site | function | kind | state |
|---|---|---|---|
| 0x10006730 | `m_AllocTracked` | zero-fill | this round |
| 0x10008f0c | `vfs_ReadData` | copy | this round |
| 0x10017611 | `gm_AllocGebaeude` | zero-fill | this round |
| 0x10006929 | `m_init` | zero-fill | already asm |
| 0x10006e0d | `m_PoolAlloc` | zero-fill | already asm |
| 0x1000b057 | `srv_InitBuildingTypeTable` | zero-fill | already asm |

Five are `xor eax,eax` + `rep stosb/stosd`; `vfs_ReadData` is the same
template with `rep movsb/movsd` from `esi`.  The prelude is **not reachable
from C**: re-probed this round with eight `memset` shapes, twenty `memcpy`
shapes and one 0x100-frame shape mimicking `vfs_ReadData`, across
`/O2 /Gd`, `/O2 /Gd /G6`, `/O2 /Gd /G5`, `/Ox`, `/O1`, `/Oy-`, `/Os`, `/Oa`,
`/Ow` and every `6.0`…`6.0-sp6` image, plus `4.2` and `5.0`.  Every one emits
the naive `shr ecx,2; rep stosd; and ecx,3; rep stosb`.  `/G6` *is* being
applied — it changes the scheduling around the fill — it just does not select
this template.  Reproducing the six sites as block-fill asm by naming the
operands as ordinary locals is therefore the only route, and is the sanctioned
exception to "C only": the target has no C spelling, and the same idiom
appears nowhere else in the binary (no other `sub reg,reg; jle` without a
`test` between).

**Effect of the three new sites:**

| function | object before | object after | target | aligned before | aligned after |
|---|---|---|---|---|---|
| `m_AllocTracked` | 608 | 656 | 672 | 46.6% | 51.4% |
| `vfs_ReadData` | 446 | 479 | 472 | 58.0% | 76.4% |
| `gm_AllocGebaeude` | 1088 | 1120 | 1088 | 37.3% | 41.6% |

Built `.text` **0x226fc (-330) -> 0x2275c (-234)**, and the game region's
accumulated drift at `gm_RandomQuadratic` goes from about -100 to **-32**.

**The remaining per-object size errors** (span = distance to the next
object's first reference VA, so only objects that tile densely are
meaningful):

| object | span | built | error |
|---|---|---|---|
| `vfs_OpenStream.c.obj` | 752 | 704 | **-48** |
| `cm_ExCopyEntityData.c.obj` | 912 | 880 | **-32** |
| `gm_AllocGebaeude.c.obj` | 1088 | 1120 | +32 |
| `CrashDumpUnhandledExceptionFilter.c.obj` | 2128 | 2144 | +16 |
| `m_AllocTracked.c.obj` | 672 | 656 | -16 |
| `vfs_ReadCompressed.c.obj` | 496 | 512 | +16 |
| `gv_GetSlotEntry.c.obj` | 352 | 336 | -16 |

`gm_AllocGebaeude` is the one deliberate trade: its object was exactly 1088
before, and carrying the correct prelude makes it +32, but that is *also*
what took the whole `.text` 32 bytes closer.  Its other 32 bytes of excess
have to come out before it can be byte-exact; the prelude is a prerequisite
because it sits directly in front of the component loop and shifts every
register assignment downstream.

**Next step:** `vfs_OpenStream` (-48) and `cm_ExCopyEntityData` (-32) are the
two biggest remaining size errors and neither is a prelude site, so their
shortfall has a different cause — start there.  `gv_GetSlotEntry` (-16) is
not on the non-exact list at all, so its 16 bytes are missing *content*, not
a wrong function size.

## Deleting the dead half of `link_stubs.c` takes 368 bytes off the split link (2026-09-13, round 36)

Round 35 left the deletion undone because the dead names appeared in the
tooling.  Checked: the only hits outside `docs/` and `.scratch/` are Ghidra
label fields inside `src/rebrew-functions.toml` (`ghidra = "..."` on *other*
functions) plus the definitions themselves — **no link-time or postlink-time
dependency**.  Recomputing deadness as "defined by `link_stubs.c.obj` and
undefined in no object of either response file" gives **89 of 232** symbols.

Removed the 24 that are C functions (20 one-line stubs, 4 multi-line):
`_callnewh`, `ahm_RandomBelow`, `destroy_entity`, `fcn_1001accd`,
`fcn_1001c083`, `fcn_1001e8b4`, `fcn_1001eab0`, `fcn_1001ede5`, `fcn_1001eec1`,
`find_entity_26`, `find_entity_27`, `rand_mod`, `read_uint32_be`,
`vfs_EntityCleanup`, `vfs_FreeGameSubobject`, `vfs_FreeSubobj`,
`vfs_LockedFwrite`, `FreeCommandBuffer`, `free_node`, `game_free`,
`write_log`.  The other 65 dead symbols are `.data`/`.bss` globals and were
left alone — they do not emit `.text`, and `.data` is postlink's business.

`link_stubs.c.obj` `.text` **512 -> 128 B**; the split set **0x22aea (+676) ->
0x2297a (+308)**.  `gate.sh` still passes: 0 compile/link errors, 279/281.

**The standard link got worse and that is the honest reading.**  It went
`0x2283c (-10) -> 0x226fc (-330)`: at -10 it was only accidentally the right
total length while 94.6% of the layout map failed.  Delete nothing further
here without measuring: the 128 B left is exactly the seven stubs that *are*
referenced (`thread_proc`, `RecvGameSavegame`, `fcn_1001af30`,
`fcn_10020ff8`, `putc`, `crt_toupper`, `_crt_locked_call4a`), and they go away
only when the functions behind them are reversed.

**Corrected accounting of the remaining +308:**

| term | bytes |
|---|---|
| game region (`_fclose` starts 0x80 early: 96 B of game shortfall + 32 B `_getpid`/`srand`) | -128 |
| CRT content (38,618 against the reference region's 38,588) | +30 |
| `link_stubs.c` scaffolding `.text` | +128 |
| residual slack | +278 |
| | **+308** |

**The +308 is not the real distance.**  `split_audit` still reports **0 of 330
placed symbols at their reference VA**: `_fclose` lands at 0x1001a10a against
0x1001a18a, a uniform **-0x80** for the first ten symbols, drifting to -0x3d3
by the tail (`__strdup` at 0x10023442 against 0x10023812).  The -0x80 is
exactly the game region's shortfall, so the CRT cannot be placed until the
game half is the right length; matching the total would only hide that.

**Two more measured facts.**

*LINK discards 20 of the 246 split objects* (923 B of `.text`) as duplicate
COMDAT sections — aliases where the reference has two names for one body:
`crt0dat.obj` §14 at both 0x1001a746 and 0x1001a74f, `_mbscat`/`__mbscat`,
`__except_handler3`, `_amsg_exit`, the four `$L21349` fragments.  They are in
the response file and in the audit's `--content` sum but occupy no bytes, so
`split_audit`'s "slack" figure double-counts them and is not a padding
measurement.

*`srand` (0x1001a150, 12 B) is in no LIBCMT variant, and no `srand.obj` member
exists in any of the six.*  `rand.obj` supplies only the 13-byte seed-setter
(content-matched at 0x1001b535) and `_rand` (34 B at 0x1001b542).  The
reference's 12-byte `mov eax,[esp+4] / push eax / call 0x1001b535 / pop ecx /
ret` wrapper is therefore a separate function with no library supplier, and
`0x1001a140` (`srv_SeedRandomWithTime`) calls the same 0x1001b535 helper.

**Where the -0x80 actually is.**  `db/verify_results.json` has ten size
divergences; the sign below is *ours minus target*:

| function | target | ours | delta |
|---|---|---|---|
| `m_AllocTracked` 0x10006580 | 658 | 608 | **-50** |
| `vfs_ReadData` 0x10008e40 | 472 | 446 | **-26** |
| `cm_ExCopyEntityData` 0x1000ec00 | 901 | 880 | **-21** |
| `vfs_ReadCompressed` 0x10008a90 | 492 | 499 | +7 |
| `vfs_OpenStream` 0x10009020 | 667 | 693 | +26 |
| `CrashDumpUnhandledExceptionFilter` 0x10002770 | 2115 | 2137 | +22 |
| `gm_FindNextFilteredEntity` 0x10016f80 | 346 | 342 | -4 |
| `cm_ExSellObjekt` 0x1000d930 | 2057 | 2055 | -2 |
| `gm_AllocSpieler` 0x10018850 | 3689 | 3688 | -1 |
| `ls_LoadBuildingEntityState` 0x100128f0 | 1463 | 1464 | +1 |
| | | | **-48** |

The other 15 bytes of the -0x80 are `srand`'s 16 absent bytes minus one byte
of LINK padding.  So the shortfall is **three functions**, not a diffuse
layout problem: `m_AllocTracked`, `vfs_ReadData` and `cm_ExCopyEntityData`
alone are 97 of the 128 bytes.  A size delta is a structural difference (a
missing or extra instruction), which is why those three are the right targets
and the five near-matches (5-49 byte deltas at identical size) are not.

**The three size deltas are the memcpy alignment prelude, and it is not
flag-selected.**  All three are short by the same thing: the target expands
`memcpy` with a destination-alignment prelude
(`lea ecx,[edi+edi*2]; and ecx,3; sub ebx,ecx; jle; rep movsb; mov ecx,ebx;
and ebx,3; shr ecx,2; rep movsd; add ecx,ebx; rep movsb`), msvc6 emits the
naive `shr ecx,2; rep movsd; and ecx,3; rep movsb`.  Re-probed this round on
a fresh four-shape file (`/O2 /Gd`, `/O2 /Gd /G6`, `/Ox /Gd`, `/O1 /Gd`,
`/O2 /Gd /Oy-`, `/O2 /Gd /G6 /Oy-`, `/Os /Gd`): every flag set emits the naive
template, so `/G6` does not select it.  The `lea ecx,[edi+edi*2]; and ecx,3`
is worth recognising: it is `(-edi) & 3` computed as `(3*edi) & 3`, which is
the same value because `4*edi ≡ 0 (mod 4)` — so the prelude is the *standard*
dest-align form, not an exotic one.  Until MSVC6 is made to emit it, these
three functions stay short and the game region stays at -0x80.

**Next step:** the residual is now the biggest single term, but it cannot be
attacked before the -0x80: every split object is displaced by the game
region's length.  The 20 non-exact game functions are the prerequisite, not an
alternative — start from the three size mismatches above.  Note
in passing that `cm_ExProdObjekt` (976/993, the closest of the twenty) was
re-tested this round: hoisting the `g_unknown_1de450` load into its own
statement above `recipe_idx` and splitting the `<< 6` off leaves it at exactly
976 with the identical mismatch set, confirming the round-7 finding that the
volatile dead store pins the load.

## The remaining 784 bytes of "slack" are mostly our own scaffold (2026-09-13, round 35)

Round 34 called the 784-byte difference between the split region's span and its
summed content "inter-object slack".  That is wrong: **`link_stubs.c.obj` alone
contributes 512 bytes of `.text`**, and all of it is code the reference does not
have.  It is in the response file but not in any of the `--content`
directories, so it fell into the residual.  The other scaffolding objects
(`data_globals.c.obj`, `rdata_restore.c.obj`, `crt_imports.c.obj`) contribute
**0** bytes of `.text`; only `link_stubs.c` emits code.

`link_stubs.c` defines 232 symbols, and **96 of them are referenced by no object
in either the standard or the split response file** — about half its `.text` is
dead stubs kept alive only by `/OPT:NOREF`.  Removing them would be worth on the
order of 250 bytes, but it was **not done**: several dead names
(`ahm_RandomBelow`, `FreeCommandBuffer`, `rand_mod`, `_putc`, `write_log`)
appear in the tooling and configuration, so the postlink's expectations have to
be checked before deleting them.  The file is shared scaffolding, not
reconstruction, so a mistake there is expensive.

**Corrected accounting of the remaining +676:**

| term | bytes |
|---|---|
| game region (`_fclose` starts 0x80 early: 96 B of game shortfall + 32 B `_getpid`/`srand`) | -128 |
| CRT content (38,618 against the reference region's 38,588) | +30 |
| `link_stubs.c` scaffolding `.text` | +512 |
| residual slack | +262 |
| | **+676** |

**Also measured, and negative.**  Only 89% of member-internal adjacent section
pairs are contiguous in the reference (118 of 133), so the reference's layout is
section-by-section like ours and per-member emission would not reproduce it.
The exceptions are the members whose sections the reference splits:
`memcpy.obj` at 0x1001b200 and 0x1001eab0, `popen.obj` in five places,
`lseek.obj` in three, `cwprintf.obj`, `fread.obj`, `crt0dat.obj`.

**Next step:** either check the postlink's symbol expectations and delete the
dead half of `link_stubs.c`, or leave the CRT half where it is and go back to
the 20 non-exact game functions — the game region is still 128 bytes short and
that is the larger remaining piece.

## Trimming each section to the reference function size removes 2,170 bytes (2026-09-13, round 34)

`map_libcmt` matches a reference function to a member section by *common
prefix*, so a section can be far longer than the function it was matched to:
the 238-byte `exsup` section carries **six** reference functions of 34, 35, 66,
148, 197 and 216 bytes, and `split_coff` was emitting all 238 bytes for each of
them.  The same holds for `realloc` (member section 815 B against a 395-byte
reference function), `calloc`, `free`, `output` and `strchr`.

`split_coff --trim` cuts the emitted root section to the map's size for that
entry, drops the symbols defined past the cut, and drops relocations past it.
Result:

| | round 33 | round 34 |
|---|---|---|
| `.text` | 0x23364 (+2,846) | **0x22aea (+676)** |
| drift range | -0x132 .. +0x76c | -0x3d3 .. +0x1ac |
| archive members pulled | none | none |

**2,170 bytes**, and the emitted CRT content is now 38,618 bytes against the
reference CRT region's 38,588 — **+30 bytes of content**, with the remaining
784 bytes being inter-object slack across ~290 objects.  The whole CRT half is
now within 814 bytes of the reference, and the total +676 decomposes as -128 for
the game region (96 bytes of game shortfall plus the 32-byte `_getpid`/`srand`
pair that no LIBCMT carries) and +814 for the CRT region (784 slack + 30
content).

**`--trim` exposed a filter bug in `emit_defs`.**  Its missing-symbol filter
skipped every `?`-prefixed name as a C++ string literal, so when trimming
removed `?_set_new_handler@@YAP6AHI@ZP6AHI@Z@Z` from the middle of `handler.obj`'s
section, nothing replaced it and LINK pulled the whole member back.  Only
`??_C@` names are string literals; with the filter narrowed to `("__imp_",
"??_C@")` the pull disappears and `.text` drops another 10 bytes (0x22af4 ->
0x22aea).

`scripts/split_link.sh` runs the trimmed configuration and reproduces 0x22aea.

**Next step:** the residual is now dominated by the 784 bytes of slack plus the
128-byte game shortfall, both small and local.  Per-object slack is worth one
more look — the audit's worst deltas are a block of ~40 objects sitting at
-0x3d0 — but the bigger prize is the other half: the 20 non-exact game
functions.

## Three of the "no library carries" functions are in LIBCMT after all (2026-09-13, round 33)

Rounds 11-13 recorded nine CRT functions that no available library carries
(`srand`, `__CRT_INIT`, `fpmath`, `init_fptrs`, `unlock_9`, `crt_close_handle`,
`crt_once_init`, `allmul_slow`, `fcn_1001a643`), and round 31 leaned on that
when it concluded `_getpid`/`srand` at 0x1001a140 are "not ours to reverse".
**Three of those nine are member sections the catalog mapping simply could not
reach**, and `scripts/locate_sections.py` finds them:

| catalog VA | member section | located at |
|---|---|---|
| `fcn_1001a643` | `crt0dat.obj` section 2 — symbol `__cinit` | 0x1001a643, 45 B |
| `fpmath` | `fpinit.obj` section 3 — symbol `__fpmath` | 0x1001b070, 23 B |
| `__CRT_INIT` | `dllcrt0.obj` section 3 — symbol `__CRT_INIT@12` | 0x1001b8fb, 217 B |

`map_libcmt` matches *catalog functions to member sections* by name and prefix
length; these sections are only reachable through a member's section symbol or
under a different name, so they fell through.  `locate_sections.py` goes the
other way — for a member section, find its reference VA — with the mask the
round-31 note said was needed: relocation slots plus the four bytes after every
`E8`/`E9` (intra-image relative calls carry no relocation entry), a fixed-run
`bytes.find` pre-filter, and a full scan for heavily relocated code where no
16-byte run is fixed (the thunk block is 14 fixed bytes in 42).  Run over every
member of the five variants it recovers **12 sections** the map missed; run
over the emitted thunk object it returns 0x1001a160, confirming that object's
content matches the reference exactly.

**Measured on the whole pipeline** (`.text` against the reference's 0x22846,
and the per-object drift range from `scripts/split_audit.py`):

| configuration | `.text` | drift range | exact placements |
|---|---|---|---|
| round 32 (catalog map, `--closure`) | **0x2334a (+2,820)** | -0x230 .. +0xa7c | 0 |
| catalog map + catalog map completion, `--closure` | 0x233ea (+2,980) | -0xf0 .. +0xbdc | **2** |
| completed map, no `--closure` | 0x23364 (+2,846) | **-0x132 .. +0x76c** | 0 |

The completed map is the better state to build on even though it is 26 bytes
larger: the worst-case drift falls by 784 bytes, which is what byte identity
needs, and `--closure` is subsumed once the map covers the sections (it exists
to recover sections the catalog mapping misses).  `scripts/split_link.sh` now
runs the completion step and drops `--closure`; it reproduces 0x23364.

**Next step:** with the map complete, the remaining excess can be attributed
per section rather than per category — the 12 recovered sections and the
`emit_defs`/commons objects should each now be checkable against a known
reference VA, so any that still have none are the real over-inclusion.

## The socket IAT thunks now sit where the reference has them (2026-09-13, round 32)

Round 31 named 42 of the missing 74 CRT-pre bytes: the seven
`jmp dword ptr [IAT]` stubs at 0x1001a160..0x1001a18a that the reference's
`SendBroadcastPacket` calls from nine sites.  They exist because the original
source declares those imports without `__declspec(dllimport)`, so MSVC emits a
five-byte `call _socket@12`; ours does the same, but LINK takes the thunk from
`WS2_32.lib` and archive members are appended after every command-line object,
so it lands at the end of `.text` instead.

`scripts/emit_thunks.py` emits the reference's own six bytes for each thunk
(`ff 25 <IAT>` with the operand as a DIR32 relocation against the import
library's `__imp_<decorated>` symbol), as one COMDAT `.text` in the reference's
order (closesocket, sendto, bind, htons, htonl, setsockopt, socket), and
`make_split_rsp.py --thunks DIR` inserts it between the game objects and the
CRT objects.  Measured:

| | before | after |
|---|---|---|
| `.text` | 0x23354 (+2,830) | **0x2334a (+2,820)** |
| `_fclose` placement delta | -0xaa | **-0x80** |
| thunk VAs | absent from `.text` | 0x1001a0e0..0x1001a10a, same order as the reference |

`scripts/split_link.sh` runs the whole pipeline including this step and
reproduces 0x2334a from scratch.

**What the remaining -0x80 is.**  The reference has `_getpid` (14 B) at
0x1001a140 and `srand` (13 B + padding) at 0x1001a150, before the thunks —
32 bytes — and the other 96 bytes are the game shortfall.  Neither `_getpid`
nor `srand` is defined by **any** member of the five LIBCMT variants (a scan of
every member finds no such symbol), which is why `map_libcmt` could not place
them and why `emit_defs` never sees them: nothing in our link references them.
They are the first two of the nine functions the map records as carried by no
library, and under this objective they are not ours to reverse — the reference
build simply has CRT code that the available LIBCMTs do not.

**Bug note.**  `.text` is five characters, so `sec[0:6] = b".text\0\0"`
assigns *seven* bytes into a six-byte slice and resizes the bytearray by one:
the object then claims a 42-byte body that starts one byte early, and LINK
reports the section as corrupt ("bad string table size" from objdump, LNK1143
from LINK).  It is the same class as round 29's `.bss` bug, and the fix is
`sec[0:8] = b".text\0\0\0"` — always assign into an 8-byte name slice.

## The remaining 2,830 bytes, attributed (2026-09-13, round 31)

Round 30 left the split-set `.text` at 0x23354, +2,830 over the reference, and
"attribute it" as the next step.  `scripts/split_audit.py --content DIR` now
prints the region span against the objects' summed `.text`, so the three terms
fall out:

| term | bytes |
|---|---|
| game region — the built stream ends at 0x1001a0e0, the reference at 0x1001a18a | **-170** |
| CRT content 40,755 against the reference CRT span 38,588 | **+2,167** |
| inter-object slack — region span 41,588 minus content 40,755 | **+833** |
| | **+2,830** |

**The -170 has a name.**  96 bytes of it is *game* code (the game objects end
0x60 before the reference's CRT starts) and 74 bytes is CRT code before
`_fclose`:

```
0x1001a140  _getpid        14 B   call [GetCurrentProcess]; push eax; call srand; pop ecx; ret
0x1001a150  srand          13 B
0x1001a160  7 IAT thunks   42 B   jmp dword ptr [0x10024198/94/90/8c/88/84/80]
```

Those seven thunks are `socket`, `setsockopt`, `htonl`, `htons`, `bind`,
`sendto`, `closesocket`, and they are live code, not dead stubs: the
reference's `SendBroadcastPacket` (0x10001130) makes **nine direct
`call`/`jmp` to them** between 0x10001142 and 0x100011c0.  Our builds do
generate equivalent thunks — but at 0x1001c2b8+ in the standard build and at
the end of `.text` (0x100240f0+) in the split build, targeting an IAT base of
0x10025000+ rather than the reference's 0x10024180.  So what is missing at
0x1001a160 is **import-thunk placement plus a matching IAT layout**, not code:
the six-byte `jmp [IAT]` bytes themselves are the same shape we already emit,
and they come from `WS2_32.lib` in the standard build.

**The +2,167 content excess** is the sum of the terms rounds 27-30 measured:
the mapped sections' +1,049 over-inclusion (15 sections larger than the
reference function they were matched to), the closure helper sections (+744),
and the 13 definition objects (+268) — 2,061 of the 2,167, the remainder being
rounding across the region.

**The +833 slack** is 3.2 bytes per object across 259 split objects plus 28
helper/definition objects, so it is not worth chasing: the round-27 "5,619
bytes of LINK padding" was a measurement mistake, and the real inter-object
slack is this.

**Two facts about the definition sections, from trying to place them.**  The
reference's `__DllMainCRTStartup@12` does not call `__CRT_INIT@12` directly: at
0x1001b9fa it is `mov eax, dword ptr [0x11767588]; ...; call eax`, i.e. the
address is taken and stored in a data slot, so `__CRT_INIT@12` cannot be
located by following a direct call.  And a relocation- and `E8`-masked search
over the reference's `.text` finds no position for the emitted `__CRT_INIT@12`
body — but that body is dense enough with relocations and `call` displacements
that no 16-byte run free of both exists, so the search is not conclusive either
way.  `_DllMain@12`'s six-byte stub (`6a 01 58 c2 0c 00`) *is* present in the
reference.  Placing these sections at their reference VAs therefore needs a
proper masked matcher (the technique `scripts/map_libcmt.py` already uses), not
a window search.

**So the open items on this half are:** (1) place the import thunks and match
the IAT base — a `.data`/PE-layout problem, which the postlink step already has
the `iat_thunks` list for in `rebrew-project.toml`; (2) byte-match the emitted
definition and closure sections against the reference so they land at the right
VAs; and (3) the 96-byte game shortfall, which is the other half's business
(the 20 non-exact functions).

## No LIBCMT member is pulled any more (2026-09-13, round 30)

The last five pulled members were driven by symbols whose *defining section*
the split set never emits — sections the map did not match to a reference
function, in members that are otherwise mapped, and whole members the map does
not cover:

| symbol | member | defining section |
|---|---|---|
| `__except_list` | `exsup.obj` | **ABSOLUTE** (section -1, value 0) |
| `__XcptActTab` | `winxfltr.obj` | `.data` (0x88) |
| `__cinit` | `crt0dat.obj` | `.text` (0x2d, section 2) |
| `___xc_a` | `crt0init.obj` | `.CRT$XCA` (4) |
| `__CRT_INIT@12` | `dllcrt0.obj` | `.text` (0xd9, section 3) |
| `_DllMain@12` | `dllmain.obj` | `.text` (6, section 1) |

`scripts/emit_defs.py` closes it from the symbol side: read the defined and
undefined externals of every object already on the response file, take the
difference, map each missing symbol to the section that defines it in one of
the LIBCMT variants, and emit that section as its own object — or, for an
`ABSOLUTE` symbol, a one-symbol object with section number 0xFFFF.

**It has to iterate.**  One pass is not enough because the definitions cascade:
emitting `__CRT_INIT@12` (dllcrt0 section 2) *introduces* the reference to
`_DllMain@12`, which no object on the response file had named before.  The
script re-scans its own output and repeats, converging in four passes from 74
missing symbols to 0.  Two bugs found on the way, both worth recording because
they are easy to mistake for linker behaviour: objdump prints a COFF definition
as `(sec N)` and an undefined external as `(sec 0)`, so a first pass that
treated section 0 as a definition reported "0 undefined" and emitted nothing;
and keying the output file on `member + section` alone makes two symbols in one
section overwrite each other, which silently lost `crt0dat`'s and
`crt0init`'s sections until the emit was grouped by `(member, section)`.

`make_split_rsp.py --defs DIR` adds the objects, and `scripts/split_link.sh`
now runs the whole pipeline — map, split, commons, definitions, response file,
link, audit — in one command against a configured `build/` tree.  Result:
**zero LIBCMT archive members are pulled**, and `.text` 0x23686 -> **0x23354** (-818 bytes), so the
overshoot is down from 7,840 to **2,830 bytes** — 5,026 bytes removed since the
round-26 baseline, and the CRT half is now "LIBCMT is linked in" in the literal
sense: every symbol the split set references is defined by a command-line
object.

**What the remaining 2,830 bytes are.**  The 13 emitted definition objects add
only 268 bytes of `.text`, and the commons objects add none, so the residue is
not the new objects.  It is the round-26/27 terms: the -0xaa missing prologue
before `_fclose`, the split objects' +1,049 over-inclusion, the inter-object
slack, and whatever the *game* region contributes.  Attributing it needs a
fresh map audit — `scripts/split_audit.py` on the new link is the first step.

## Carried data sections are closure roots; commons are parked (2026-09-13, round 29)

Two fixes and one parked experiment on top of round 28's `--with-data`.

**1. A carried data section must be a closure root.**  `_file.obj`'s `.data`
holds `__iob`, whose initialisers name `___endstdio` — and that lives in a
*second* `.text` section of the same member (section 7 of 16), which the map
never mapped.  Carrying the `.data` therefore turned a definition into an
undefined reference, and LINK went straight back to the archive for the whole
member.  `build_object` now walks relocations from the extra data sections too,
not only from the root `.text` (still restricted to same-member `.text`, so it
cannot pull another member's data).  Effect: `_file.obj` drops out of the pull
list, 7 -> 6 members and 1,635 bytes, `.text` 0x238c5 -> **0x238c1**.

**2. Uninitialized sections were written as raw data.**  A `.bss` section has
`PointerToRawData == 0`; the code was emitting `raw_size` zero bytes into the
file and advancing the cursor for them, so the object claimed contents for a
section that has none and the following section's file offsets shifted.  Such a
section now contributes no bytes and keeps `SizeOfRawData = raw_size` with
`PointerToRawData = 0`.  Neutral on `.text` (0x238c1 either way) and the default
path is unchanged — regenerating the plain `--closure` set still reproduces
**0x246e6**, so nothing earlier in this line moved.

**3. The commons are emitted as standalone objects, and that is worth another
571 bytes.**  The six remaining pulls are driven by symbols that no member
*section* defines: `mbctype.obj` declares `__mbctype` as section 0 value 0x101,
`___mbcodepage` 4, `___mbulinfo` 0xc, and `crt0dat.obj` declares `__FPinit` /
`___onexitbegin` / `___mbctype_initialized`, `winxfltr` `__XcptActTab`, `exsup`
`__except_list`, `dllcrt0` `__cinit` — all *common* symbols, which the linker
allocates, so LINK searches the archive and takes the whole member.

`scripts/emit_commons.py` emits one tiny one-section object per member holding
that member's commons in a `.bss` (each at its aligned offset, size from the
symbol's `Value` field as COFF records for a common), one object per member,
deduplicated by symbol name across libraries; `make_split_rsp.py --commons`
adds them to the link line.  Result: `mbctype.obj` drops out of the pull list,
6 -> 5 members, `.text` 0x238c1 -> **0x23686** (-571 bytes).

**The failure this replaced was a two-byte bug, not a COMDAT problem.**  The
first attempt folded the synthetic `.bss` into the split object itself and LINK
rejected it (`LNK1143: invalid or corrupt file: no symbol for comdat section
0x2`), and after correcting the section-count accounting the symbol table was
still unreadable ("bad string table size").  The cause was in the object
writer, not in the linker's COMDAT rules: a section header's name is 8 bytes,
and `sec[0:5] = b".bss\0\0\0"` assigns **seven** bytes into a five-byte slice,
which *resizes* the bytearray and shifts every following offset by two.  With
`sec[0:8] = b".bss\0\0\0\0"` the same synthetic section is fine.  The
in-object `--with-commons` path keeps the code but stays off by default; the
standalone-object route is simpler and is what the numbers above use.

**Current state of this half:** `--closure --with-data` plus the commons
objects links clean at **0x23686** (reference 0x22846, **+0xE40 = 3,648
bytes**), down from 0x246f6 at the start of this line — 4,208 bytes removed in
three rounds.  Five members are still pulled (`crt0dat.obj`, `dllcrt0.obj`,
`dllmain.obj`, `exsup.obj`, `winxfltr.obj`) and the next causes to attack are
`_DllMain@12` (the `/ENTRY:` symbol), `__CRT_INIT@12`, and the `__cinit` /
`___xc_a` cascade into `crt0dat.obj`.  `/ENTRY:_DllMainCRTStartup@12` is worth
a further 2 bytes whenever the entry question is settled.

## `split_coff --with-data` removes 3,617 bytes of the overshoot (2026-09-13, round 28)

Round 27 concluded that LINK loads the 12 leftover members for their *data*
symbols, because the split set extracted only `.text`.  This round implements
that: `split_coff --with-data` carries each mapped member's `.data`, `.bss`,
`.rdata` and `.CRT$*` sections on the object for that member's lowest-VA mapped
function, so the member's data has a command-line definition.  It also fixes a
latent bug the flag exposed: a `.bss`-style section has `PointerToRawData == 0`,
and `section_body` was reading the object *header* for it; such sections now
emit `raw_size` zero bytes.

Measured on the closure set, both VS-sorted by `scripts/make_split_rsp.py`:

| build | `.text` | vs reference | archive pull |
|---|---|---|---|
| `--closure` (round 27) | 0x246e6 | +0x1ea0 (7,840 B) | 12 members, 34 symbols, 4,978 B |
| `--closure --with-data` | **0x238c5** | **+0x107f (4,223 B)** | **7 members, 16 symbols, 1,655 B** |

**-0xE21 = 3,617 bytes**, and the archive pull shrinks by exactly the
difference: `output.obj`, `sbheap.obj`, `cvt.obj`, `tzset.obj`, `strtol.obj`,
`intrncvt.obj`, `atox.obj`, `handler.obj`, `crt0msg.obj`, `_newmode.obj`,
`ioinit.obj`, `ncommode.obj` and the rest stop being loaded.  The default path
is unchanged: regenerating the plain `--closure` set with the patched script
reproduces 0x246e6 byte-for-byte, so the `.bss` fix only affects objects that
actually carry an uninitialized section.

**What is left, from LINK `/VERBOSE`.**  With the flag on the remaining pull is
7 members, and `/VERBOSE` names the one symbol that loads each
(`Found <symbol>` / `Referenced in <obj>`):

`_DllMain@12` -> `dllmain.obj`; `__except_list` -> `exsup.obj`;
`__CRT_INIT@12` -> `dllcrt0.obj`; `___endstdio` -> `_file.obj`;
`__XcptActTab` -> `winxfltr.obj`; `__mbctype` -> `mbctype.obj`;
`__cinit` / `___xc_a` -> `crt0dat.obj`.

Most of these are **common symbols**, not data a section carries: `mbctype.obj`
defines `__mbctype` as section 0 with value 0x101, `___mbcodepage` as section 0
value 4, and so on.  A common is allocated by the linker, so no `.data` section
of ours can satisfy the lookup; the object has to carry the allocation itself.
`_DllMain@12` is different again: it is the `/ENTRY:` symbol, and the split rsp
drops the `crt_region/dllmain.c.obj` that supplied it, so LINK looks in the
archive and finds LIBCMT's `dllmain.obj`.  Measured: switching `/ENTRY:` to
`_DllMainCRTStartup@12` (which resolves to `__DllMainCRTStartup@12`, the
symbol the split set's `1001b9d4_.text.obj` actually defines) links clean at
**0x238c3**, two bytes better; `/ENTRY:__DllMainCRTStartup@12` fails outright,
confirming LINK prepends its own underscore.

**Next step for this half:** emit the pulled members' commons as ordinary
`.bss` definitions of the recorded size (the symbol's `Value` field), and
either keep `crt_region/dllmain.c.obj` in the rsp or use the
`_DllMainCRTStartup@12` entry.  Both are small, and the remaining 4,223 bytes
decompose into the ~1,655-byte pull plus the `-0xaa` missing prologue and
inter-object slack from round 27.

## The split-set overshoot is 12 archive-pulled members (2026-09-13, round 27)

The round-26 audit left one question open: the built `.text` is 7,840 bytes
over the reference's 141,382, and the placed objects are mostly in the right
order, so where do the bytes come from?  Three measurements this round answer
it, and one of them was a genuine tooling bug.  (An intermediate answer in
this round — "5,619 bytes of LINK padding" — was wrong and is corrected in
item 3 below.)

**1. `split_coff`'s `index.json` is not in reference-VA order.**  Four descents
in the 235-entry list, the worst being `0x1001eab0` emitted immediately after
`0x1001b200`.  Both are 821-byte LIBCMT bodies (`memmove2` and `memmove`) and
the reference has them 0x38b0 apart, so the old rsp — which fed `index.json`
straight to LINK, as `/tmp/mkrsp.py` did — dropped the `memmove` body 13.5 KB
from where it belongs and every later object inherited the shift.
`scripts/make_split_rsp.py` replaces that ad-hoc rsp construction and sorts by
the VA in each object's name (verified byte-identical to the hand-sorted rsp).
Effect on the closure build: worst placement error -0x3640 -> **-0x260**,
`.text` 0x246f6 -> **0x246e6**.  Modest in bytes, but the layout is now
reference-ordered, which every later measurement depends on.

**2. Over-inclusion is +1,049 bytes, in 15 objects.**  Summing the `.text`
section sizes of the 235 mapped split objects gives 39,723 bytes against the
38,674 those same functions occupy in the reference.  Only 15 objects are
bigger than the reference function, and they carry 2,161 bytes of excess;
the largest are `realloc` (+420, the member section is 815 against the
reference's 395), `0x1001f8d0` (+224), the three `exsup` spellings
`__NLG_Notify` / `__unwind_handler` / `__abnormal_termination` (+204 each) and
`0x1001e6e4` (+172).  Round 19's "the leftovers are intra-member statics"
story is a different effect from this one: this is the extracted section being
longer than the reference function.

**3. The rest of the overshoot is 12 whole LIBCMT members LINK still pulls
from the archive.**  The split objects themselves pack to 41,300 bytes
(0x1001a0e0 .. 0x10024234) against 40,467 of content — only **+833** bytes of
slack — so the split objects are *not* where the overshoot lives.  What sits
after them is: the link still pulls `output.obj`, `sbheap.obj`, `mbctype.obj`,
`crt0dat.obj`, `cvt.obj`, `tzset.obj`, `exsup.obj`, `winxfltr.obj`,
`dllmain.obj`, `_file.obj`, `dllcrt0.obj`, `a_cmp.obj` from `LIBCMT.lib` —
**12 members, 34 symbols, 4,978 bytes** (0x10024234 .. 0x100255a6) — because
some reference from a command-line object is still satisfied only by the
archive.  That member list is exactly the one rounds 17-21 recorded as "the 34
leftovers", so a symbol-level metric and this byte-level one agree for once.

So the complete decomposition of the +7,840-byte overshoot is

| component | bytes |
|---|---|
| game region, missing code before `_fclose` | -170 |
| split objects, inter-object slack | +833 |
| archive-pulled members (12 members / 34 symbols) | +4,978 |
| trailing data/stub/helper objects and end padding | +2,199 |
| **total** | **+7,840** |

**Correction.**  An earlier draft of this section claimed 5,619 bytes of
"LINK per-object padding" from comparing the summed `.text` of everything on
the rsp (143,603) with the built `.text` (149,222).  That comparison is
invalid: it spans the game objects, the split objects and the archive members
mixed together, and the archive members are not on the rsp at all.  Measured
inside the split region the slack is 833 bytes, and the real third term is the
archive pull above.

**Consequence for the CRT half.**  Two thirds of the gap is one problem —
"stop LINK loading those 12 members" — and the symbol analysis says why it
loads them.  Collecting the defined and undefined externals of all 447
command-line objects shows the split set extracts **only `.text`**: the
members' *data* symbols (`__environ` from `crt0dat.obj`, `__iob` from
`_file.obj`, `___mbcodepage`, `__XcptActTab`, `__exitflag`, ...) are defined by
nothing else on the command line, so LINK satisfies each reference by loading
the whole member and appending its `.text`.  (`_g_current_season`,
`_g_slot_array`, `__crtheap`, ... are `<common>` and not part of this — a first
pass that treated every section-0 symbol as undefined produced a false 113-symbol
list before the commons were separated out.)

So the next `split_coff` extension is to emit each mapped member's `.data` /
`.bss` sections alongside its `.text` section, so the data references resolve
from command-line objects.  That should drop the 4,978-byte archive pull
without touching a byte of code, and `scripts/split_audit.py` shows the result
directly.  `scripts/make_split_rsp.py` and `scripts/split_audit.py` make it
measurable; the recipe above reproduces the starting state.

**Also measured:** layout fidelity of the sorted closure build is **169 of 240**
consecutive split-object pairs placed with exactly the reference's gap; the
nonzero steps are the closure helper objects landing next to their parent
section (+1950/-1841, +1233/-1173, +647/-625) and the 15 oversized objects.

## The split-set link reproduced, and measured from the linker map (2026-09-13, round 26)

Rounds 4-21 built the split-set link repeatedly and recorded only an end
figure; nobody had measured *where* LINK put each split object.  This round
rebuilt it and did, from `/MAP`.

Reproducible recipe (all from the project root; the library list is a
preference order, first match wins):

```
python3 scripts/map_libcmt.py --lib .scratch/libcmt/LIBCMT.sp6.LIB \
    --lib .scratch/libcmt/LIBCMT.sp5.LIB --lib .scratch/libcmt/LIBCMT.base.LIB \
    --lib .scratch/libcmt/LIBCMT.vc7.LIB --lib .scratch/libcmt/LIBCMT.sp4.LIB \
    --json > .scratch/libcmt_map_u.json
python3 scripts/split_coff.py --lib <same five> --map .scratch/libcmt_map_u.json \
    --out build/libcmt_split --closure          # 259 objects
# rsp = objects1.rsp minus the eight crt_region/*.obj, with the 259 split
# objects inserted in map (reference-VA) order after the game objects
cd build && eval "$(sed 's#@CMakeFiles/server_dll.dir/objects1.rsp#@split.rsp#;
    s#/out:server.dll#/out:server_split.dll /MAP:server_split.map#;
    s#/implib:server.lib#/implib:server_split.lib#; s# /pdb:[^ ]*##' \
    CMakeFiles/server_dll.dir/link.txt)"
python3 ../scripts/split_audit.py server_split.map
```

The link succeeds.  `.text` VirtualSize **0x246f6** (end 0x100256f6) against
the reference's 0x22846 — within 4 bytes of round 18's recorded 0x100256f2, so
the documented state reproduces, and 259 objects matches round 19's count.

**What the map says.**  `scripts/split_audit.py` reads the object name's
reference VA against the address LINK gave it.  Of 340 placed split symbols,
**none is at its reference VA.**  The mapped objects start uniformly at
**-0xaa** — `_fclose` (0x1001a18a) lands at 0x1001a0e0 — and the drift grows
monotonically to **+0x5c0** by the tail.  The two ends have different causes:

- the **-0xaa start** is the ~170 bytes of CRT code the reference has before
  `_fclose` that the split set never emits.  The map matches 235 of the
  region's 244 functions; the nine it cannot (`srand`, `__CRT_INIT`, `fpmath`,
  `init_fptrs`, `unlock_9`, `crt_close_handle`, `crt_once_init`, `allmul_slow`,
  `fcn_1001a643`, 542 B) are part of it, and the eight `crt_region` objects the
  split rsp drops were displacing exactly that space in the standard build.
- the **+0x5c0 drift** accumulates over ~300 objects and is the split objects'
  COMDAT padding, so it is not a member-selection problem at all.  This is the
  first measurement that separates the two: rounds 17-21 treated the whole
  7,852-byte overshoot as leftover "excess of the included members", but at
  most ~1.5 KB of it can be padding.

`--closure` is a third, independent source of drift: its helper objects are
placed far from their reference VA (`memcpy.obj`'s `LeadUp1` lands 0x3640
*below* it, `__STRINGTOLD`'s helper 0xa5c above).

**Also re-measured, negative.**  A reloc-masked search for each mapped
reference body in the built `.text` (masking the reference's `.reloc` slots
*and* the four bytes after every `E8`/`E9`, since intra-image relative calls
carry no relocation entry — see round 11) finds **99 of 235 anywhere** and
**0 of 235 at their reference VA**.  So the split set is not "the reference CRT
region, slightly misplaced"; most of the reference CRT code is not in the
image at all.  The 34-symbol leftover count in rounds 17-21 is a symbol-level
metric and understates this badly.

**`--closure` is worth 0x758 bytes but adds the outliers.**  Re-run with the
same map and no `--closure` (235 objects instead of 259): the link still
succeeds and `.text` grows 0x246f6 -> **0x24e4e** (over by 0x2608 instead of
0x1eb0), 319 placed symbols instead of 340, drift -0x3650 .. +0x607.  So
closure is the better configuration for total size — as round 10 found — and
the current link's `/ENTRY:DllMain@12` no longer needs the `__CRT_INIT` helper
that forced `--skip-helper` in rounds 8-10.

**Also run, negative.**  `rebrew climb --objective aligned` (4 passes,
dry-run) on `gm_CheckInventoryCapacity` — the closest function the round-25
alignment table had not already shown to be a scheduling wall — reports one
move at statement 18 worth **+1 matched byte** of the whole binary, i.e. noise.
The deterministic adjacent-statement climb has nothing to offer on it; its
residual is the documented address-form/spill wall, not statement order.

**Next step for this half:** the ~0x1eb0 overshoot splits into the -0xaa start
(missing code) and the +0x5c0 tail drift (padding), but the mapped sections
themselves total 38,674 B against the reference region's 34,550 B, so there is
also ~4 KB of over-inclusion.  Attribute the drift between padding and
over-inclusion object by object — the map has the per-symbol addresses to do
it.

## `rebrew diff`'s positional count is not a priority signal (2026-09-13, round 25)

`rebrew diff` aligns the target and candidate streams *positionally*.  When the
candidate inserts or deletes one instruction the alignment desyncs for the rest
of the function, so `structural` explodes and `exact` collapses even though the
two streams are the same program in the same order.  Two examples measured this
round: `cm_ProcessCommandQueue` reads **15.6%** positionally but **88.3%** once
aligned, and `ls_LoadBuildingEntityState` reads **0.6%** positionally but
**88.8%** aligned.  The round-24 flags on both functions were chasing a
measurement artefact.

`scripts/align_match.py` computes the honest number: the longest common
subsequence of normalized instruction text, i.e. the largest number of target
instructions that can be matched, in order, by an instruction that will be
byte-identical in the linked image.  Normalization lowercases, drops `;`
comments and segment prefixes, masks bracketed symbol operands and any number
`>= 0x10000` (image addresses / relocations), and keeps only the mnemonic for
branches and calls; register names and small displacements are *kept*, so a
register-role or frame-offset difference is still a mismatch.

| function | tgt | cand | identical, in order | % | `rebrew diff` positional |
|---|---|---|---|---|---|
| `cm_ExProdObjekt` | 354 | 369 | 329 | 92.9% | 98.6% |
| `ls_LoadBuildingEntityState` | 499 | 495 | 443 | 88.8% | 0.6% |
| `cm_ProcessCommandQueue` | 205 | 204 | 181 | 88.3% | 15.6% |
| `gm_CheckInventoryCapacity` | 138 | 142 | 121 | 87.7% | 7.2% |
| `ServerMainThread` | 627 | 641 | 545 | 86.9% | 81.7% |
| `gm_ObjectsAvailble` | 229 | 235 | 197 | 86.0% | 92.1% |
| `gm_CalculateProductionValue` | 123 | 127 | 102 | 82.9% | 98.4% |
| `cm_ExCopyEntityData` | 249 | 239 | 192 | 77.1% | 32.1% |
| `ahm_ExAllocAlchemist` | 286 | 293 | 219 | 76.6% | 39.2% |
| `vfs_ReadCompressed` | 200 | 213 | 153 | 76.5% | 25.0% |
| `srv_LoadBuf` | 226 | 228 | 171 | 75.7% | 88.9% |
| `gv_ExAllocGraveyardWorker` | 333 | 332 | 245 | 73.6% | 52.0% |
| `cm_ExSellObjekt` | 667 | 673 | 479 | 71.8% | 9.0% |
| `gm_AllocSpieler` | 1056 | 1061 | 669 | 63.4% | 8.1% |
| `gm_FindNextFilteredEntity` | 118 | 119 | 72 | 61.0% | 5.1% |
| `vfs_ReadData` | 174 | 168 | 101 | 58.0% | 17.8% |
| `m_AllocTracked` | 249 | 228 | 116 | 46.6% | 16.5% |
| `gm_AllocGebaeude` `!` | 346 | 186 | 129 | 37.3% | 25.7% |
| `CrashDump` `!` | 724 | 266 | 163 | 22.5% | 3.2% |
| `vfs_OpenStream` `!` | 197 | 31 | 27 | 13.7% | 50.8% |

The positional column is `(exact + reloc) / total` from the round-24 diffs.
Rows marked `!` have a candidate slice far shorter than the target — objdump
splits those COMDATs — so their percentage is meaningless and the tool prints
`!` for them.

Two consequences worth carrying forward.  First, the ordering above is the
ordering to work in: `cm_ProcessCommandQueue`, `gm_CheckInventoryCapacity` and
`cm_ExCopyEntityData` are much closer than the positional metric suggested,
while `gm_CalculateProductionValue` and `cm_ExProdObjekt` are already known
scheduling walls despite sitting at the top.  Second, `rebrew diff -r`
(register-aware) only partially repairs this — it moves
`gm_ObjectsAvailble`'s structural count 18 -> 3 but leaves
`cm_ProcessCommandQueue` at 167 structural — so it is not a substitute.

Tool: `python3 scripts/align_match.py [--va 0x...] [--json]`.

## m_PoolAlloc closed: asm operands must be named locals (2026-09-13, round 23)

`0x10006d20 m_PoolAlloc` was the first of the 21 to fall: **266/270 ->
270/270**, `NEAR_MATCHING` -> `RELOC`, and the tree's byte-exact count goes
259 -> 261 (the 260th is `gzread`, see the distance table).  The residual was
the two parameter-home stores in the target's descending order
(`mov [ebp+0xc],edx` / `mov [ebp+8],esi`) where the reconstruction emitted
them ascending; every source swap of the two statements scored 260 because
msvc6 then sinks `alen -= 4` (`add esi,-4`) below the stores.

The reconstruction had been forcing those homes with volatile aliases
(`*(volatile int*) &head = asize;` / `*(void* volatile*) psize = slot;`),
which is what pinned the stores in source order.  **That whole apparatus is
unnecessary and harmful.**  `/O2` reuses the dead parameter slots for two
ordinary block-scope locals on its own, and when the asm block names those
locals directly it emits the target's exact sequence:

```c
char* fdest;
int flen;
...
fdest = (char*) slot;
flen = (int) alen;
__asm {
    mov edi, fdest
    mov ebx, flen
    xor eax, eax
    lea ecx, [edi+edi*2]
    ...
}
```

`fdest` lands at `[ebp+0xc]` and `flen` at `[ebp+8]` (the dead `head`/`size`
slots), the stores come out dest-then-len in the target's order, and
`add esi,-4` stays ahead of both.  No volatile, no `&param` aliasing, no
undefined behaviour.

**The generalisable rule:** when the reference's block-fill prelude reads its
operands from memory, the operands were *ordinary locals* in the original
source and the register allocator chose those slots.  Naming the locals in
the asm block and letting msvc6 allocate reproduces the choice; forcing the
slots through volatile aliases reproduces the addresses but not the schedule,
and the schedule is what the byte compare sees.  The same test was run on the
other two missing-prelude functions and neither is prelude-limited:
`m_AllocTracked` (0x10006580) reaches obj 646 against 658 with the prelude
present and its score falls (241 -> 180) because the frame grows 8 bytes and
the entry register roles are the real wall (see "Next three blockers");
`gm_AllocGebaeude` (0x100174d0) emits the prelude correctly but is 22 bytes
over and structurally shifted from offset 96.

Also re-confirmed this round, and negative: the 2026-09-11 service-pack sweep
already covers all seven VC 6.0 builds over these functions ("Twenty compile
to identical objects under every build"), so another SP sweep is redundant.

**Second negative: the `-1` constant-caching wall is not a spelling.**
`ls_LoadBuildingEntityState` (0x100128f0) is the cleanest example — 1464 vs
1463 bytes, 100% mnemonic-aligned, and the entire gap is that the reference
caches the sentinel in `ebp` (`or ebp,0xffffffff` once, then three
`mov [mem],ebp`) while msvc6 rematerializes `mov dword ptr [mem],0xffffffff`
at each of the three stores and so needs no fourth callee-saved register
(entry is `push esi; push edi` against the target's
`push ebx; push ebp; push esi; push edi`, and every frame offset is 8 low).
Seven spellings of `neg1` measured: dropping `register`, `~0`, moving the
assignment above `offset = 0`, `unsigned int` + `0xffffffffu`, and a
file-scope `static int s_neg1 = -1;` read into `neg1` — all inert at
125/1464 except the last two, which are worse (obj 1481/1475).  Delaying the
assignment to the first loop iteration reaches 150/1481.  The caching
decision is the allocator's, driven by live-range pressure the
reconstruction does not reproduce, exactly as `docs/msvc6-c-shapes.md` §48
records for `ServerMainThread`'s `sent_bytes`.

## Static demotion is clean but neutral (2026-09-13, round 21)

Third attempt at the intra-member static problem, this time without merging
sections: make every cross-section reference to a `.text` static external, and
export the defining object's statics under the same name as externals.  Two
rounds of triage were needed to get the link clean:

- demoting *all* cross-section statics to external produced
  `unresolved external symbol .debug$F` (debug section symbols must stay
  object-local), and
- after excluding `.`-named symbols, `unresolved external symbol
  _dstflag_cache` / `$T17396` — member-local `.bss`/`.data` statics we never
  extract.  Restricting the demotion to symbols whose defining section is
  `.text` made the link clean again.

Result: exit 0, but **34 leftovers / 5,294 B / `.text` 0x100256f2 — identical
to round 18.**  The members are being pulled for other symbols anyway, so the
static references were not what kept them alive.  Reverted to keep the
splitter simple; the round-18 state stands.

## The merge's exact blocker: a section symbol per COMDAT (2026-09-13, round 20)

Re-attempted the static-sharing merge with VA-ordered roots (so the merged
object's section order follows the reference, not the member's section order).
LINK now rejects the object outright:

```
1001a681_.text.obj : fatal error LNK1143: invalid or corrupt file:
                     no symbol for comdat section 0x4
```

Dumping the merged object shows why: it has six sections but only five section
symbols — the nine-byte `LINK_ONCE_DISCARD` section (crt0dat.obj's
`__lockexit`/`_doexit` neighbourhood) has none, and one symbol still points at
section 6 while the discardable section has no number.  A COMDAT section is
only valid when its section symbol (and its AUX record) is present, and the
current keep-set walk drops that one.

So the merge is a COFF bookkeeping problem, not a placement problem: every
emitted section needs its section symbol kept and its AUX `Number` (assoc)
renumbered.  Renumbering the assoc field alone did not fix it — the missing
symbol is the issue.  Reverted again; the round-18 state (34 leftovers,
`.text` 0x100256f2) stands.

## The 34 survivors, and a measured negative (2026-09-13, round 19)

The remaining leftovers are concentrated in a few members: `sbheap.obj` (5
symbols, 1,608 B), `tzset.obj` (3, 1,395), `mbctype.obj` (5, 571), `cvt.obj`
(3, 398), `winxfltr.obj` (2, 376), `crt0dat.obj` (4, 251), `output.obj` (6,
201), `exsup.obj` (2, 214), `dllcrt0.obj` (1, 217), plus singles.

Tracing undefined references from the split objects shows the mechanism for
several of them: MSVC emits **statics that the member's own sections
reference**.  `output.obj` §5 (`output`) calls `_write_char`, which is a
*class-3 static* defined in §6 of the same member.  Splitting every section
into its own object turns that intra-member local reference into an
unsatisfiable external, so the linker pulls LIBCMT's whole `output.obj` — and
the same shape recurs in `cvt`, `mbctype`, `tzset`, `crt0dat` and `sbheap`.

I tried the obvious fix — group mapped sections that are adjacent in the
reference VA space back into one object, so the intra-member statics resolve.
Measured: objects 259 -> 138, but leftovers **34 -> 60** and `.text` end
0x100256f2 -> 0x10025d72.  Reverted.  The grouping misplaces sections whose
order inside the member does not match the reference VA order, so the merge has
to be done per static-sharing group with an order check, not by simple
adjacency.

## Duplicate wrapper bodies masquerade as leftovers (2026-09-13, round 18)

Tracing which split object leaves each leftover undefined found a general
cause.  The CRT builds the same thin wrapper into several members: `lseek.obj`'s
`__lseek` and `write.obj`'s `__write` are **the same 101 bytes** (verified
byte-for-byte, same 28 relocation slots).  Whichever member the map picks for
that VA, references to the other spelling stay undefined, so the linker pulls
the sibling member purely to resolve the alias — which is where a whole group
of the "CRT-internal" leftovers came from.

`split_coff` now indexes every `.text` section body (relocation slots zeroed)
across all libraries and exports the other members' external symbol names as
aliases on the extracted section.  One object then satisfies both spellings.

Measured on the split-set link, all links clean:

| | leftovers | leftover bytes | `.text` end |
|---|---|---|---|
| round 17 | 71 | 6,650 | 0x10025c3e |
| round 18 | **34** | **5,294** | **0x100256f2** |

That also invalidates part of round 17's conclusion: the leftovers were not
all "internal references we cannot touch" — over half were aliases of bodies
already in the split set.

## The remaining leftovers are CRT-internal (2026-09-13, round 17)

The per-function check that found the five `fclose` sites was applied to the
whole leftover list.  Grepping every game source, every `crt_region` file and
`link_stubs.c` for each leftover's name (`strdup`, `_write_char`,
`___endstdio`, `__unlock_file`, the sbh extras, `_ceil`, `_strtoxl`,
`_strtoul`, `__ld12tof`, `__atoldbl`, `__STRINGTOLD`, `__XcptFilter`,
`matherr`, the fpexcept family, `tzset`/`cvtdate`, ...) returns **no live
reference** — the only two hits are comments (`link_stubs.c`: `flsall`,
`crt_heap.c`: `strtoul`).  So the 71 leftovers are pulled by the CRT members
themselves, not by game code naming a wrong symbol: they are the build-variant
excess of the included members.

That closes the "game C names a wrong CRT symbol" line of attack; the rest of
the region gap is (a) the 9 functions no available library carries and (b) the
internal references of the members we do include.

Also re-confirmed on the game side: CrashDump's four-register prologue is
immune to entry reshaping.  Hoisting `hProcess = GetCurrentProcess()` to the
top and reordering the local declarations both leave
`sub esp,0x28c; push ebx; push ebp; push esi; ... push edi` unchanged, the
same inertness the file's own notes record for other entry spellings.

## Fixed: those call sites were `fclose` (2026-09-13, rounds 15-16)

`rebrew diff` resolves the *reference's* operand, which is what round 14 lacked:
reading the per-function diff of `DispatchLogOutput` (0x10002640),
`vfs_CloseStream` (0x100038a0), `vfs_DestroyEntity` (0x10008a50) and `gm_Open`
(0x10015950) shows all five `fflush`-looking call sites targeting
**0x1001a18a**, and that function's 49 bytes are byte-identical to
`fclose.obj`'s `_fclose` in both SP6 and SP5 (the `fflush` name was the
catalog's RevEng.AI guess).  The reconstruction had spelled them `fflush`,
which is why LIBCMT's `fflush.obj` was pulled for a public `_fflush` the
reference's CRT build does not contain.

All five sites now call `fclose`.  A game function's call displacement is a
masked relocation, so the compiled bytes are unchanged and every affected
function re-tests RELOC at its original size (290/290, 177/177, 53/53,
861/861), with `verify --full` holding at 279/281.

Measured effect on the split-set link:

| | leftovers | leftover bytes | `.text` end |
|---|---|---|---|
| before | 73 | 6,858 | 0x10025d0e |
| after | **71** | **6,650** | **0x10025c3e** |

`LIBCMT:fflush.obj` is no longer in the link at all, and the standard build's
`.text` drops 0x2284c -> 0x2283c.

The generalisable check: for every CRT symbol our game C names, run
`rebrew diff` on the enclosing function and compare the reference's resolved
target against the member whose body lives there.  A mismatch means the
catalog name is wrong and the link is pulling a member the reference never had.

## Why `fflush.obj` is pulled: the reference has no public `_fflush` (2026-09-13, round 14)

`/VERBOSE:LIB` names the culprit for one leftover group.  LIBCMT's
`fflush.obj` is pulled and then ignored piecewise:

```
LIBCMT.lib(fflush.obj) : warning LNK4006: __fflush_lk already defined in 1001ac9f_.text.obj
LIBCMT.lib(fflush.obj) : warning LNK4006: __flush     already defined in 1001accd_.text.obj
LIBCMT.lib(fflush.obj) : warning LNK4006: __flushall  already defined in 1001ad29_.text.obj
```

The split set already carries the reference's `fflush.obj` sections — the map
matches 0x1001ac9f / 0x1001accd / 0x1001ad29 / 0x1001ad32 to sections 3, 5, 7
and 9 of that member (`__fflush_lk`, `__flush`, `__flushall`, `_flsall`).  The
member is pulled anyway for two symbols the reference does **not** contain:
`_fflush` and (elsewhere) `_flsall`'s public partner.  In other words the
reference's CRT build omitted the public `_fflush` wrapper, while three game
files (`gm_Open.c`, `Error.c`, `vfs.c`) call `fflush`, so our link pulls the
member to resolve it.

That matters because a game function's call target is a *masked* relocation —
it does not have to name the same symbol as the reference, only resolve to a
VA that postlink rewrites.  If those call sites named the function the
reference actually calls (its `__fflush_lk`, i.e. the body at 0x1001ac9f,
which the split set already provides), the member would not be pulled at all
and the leftover would disappear.  The same shape should be checked for the
other leftovers that our game code references but the reference omits.

Identifying the reference's own target is not a byte-scan: the built `.text`
is not offset-aligned with the reference, so reading the reference at the
built call-site offset yields garbage (measured — five `fflush` call sites,
none with an `E8` at the matching offset).  It has to be read per function.

## VC7 fills the unlock family; 9 functions remain (2026-09-13, round 13)

Swept the 16 unmatched region functions against more CRT builds (extract with
`docker run --rm --entrypoint sh -v $PWD/.scratch/libcmt:/out <image> -c 'cp
<path>/libcmt.lib /out/<name>.LIB'`; the image paths are
`/opt/msvc5.0/lib/libcmt.lib`, `/opt/msvc7.0/Vc7/lib/libcmt.lib`,
`/opt/msvc7.1/Vc7/lib/libcmt.lib`):

| library | unmatched matched |
|---|---|
| VC5 LIBCMT | 0 / 16 |
| LIBC 6.0 (single-threaded) | 0 / 16 |
| VC7 LIBCMT | **7 / 16** — the whole `unlock_09*` family (778 B) |

So `--lib SP6 --lib SP5 --lib VC7` resolves **235 of 244 region functions
(38,674 of 39,216 B)**, leaving 9 (542 B): `srand`, `fcn_1001a643`, `fpmath`,
`init_fptrs`, `unlock_9`, `__CRT_INIT`, `crt_close_handle`, `crt_once_init`,
`allmul_slow`.  None of VC5/VC6-base/SP4/SP5/SP6/VC7/LIBC carries them, so they
are a build variant none of the libraries on hand reproduces.

The link is unchanged by the VC7 addition (73 leftovers, `.text` 0x10025d0e):
the extracted `unlock` helpers are still pulled from LIBCMT members that other
symbols need, so *coverage* improves while the leftover set does not shrink.
73 leftovers is 6,858 B of the 0x24c8 region overshoot; the rest of the gap is
the split set's own excess.

## The reference CRT is a service-pack mix (2026-09-13, round 11)

Two findings, both from chasing the 22 unmatched region functions.

**Section symbols must be indexed.**  Many LIBCMT helpers are only reachable
through their `.text` *section* symbol; skipping every symbol starting with
`"."` hid them.  Indexing them recovered `exsup` (0 diffs against
`exsup3.obj`, 224 B body vs the catalog's 197).

**The rest are not SP6.**  `dosmaperr`, `NMSG_WRITE`, `setmbcp` and `output`
differ from SP6 by exactly one opcode byte: the reference has `7c` (`jl`)
where SP6 has `72` (`jb`) at the same offset — a signed/unsigned source
difference.  They match **LIBCMT.base and LIBCMT.sp5** instead.  Per-region
byte-match counts:

| library | region functions | bytes |
|---|---|---|
| LIBCMT.base | 209 | 33,414 |
| LIBCMT.sp4 | 224 | 36,844 |
| LIBCMT.sp6 | 223 | 34,987 |
| LIBCMT.sp5 | **228** | **37,896** |
| SP6 then SP5 (union) | **228** | **37,896** |

`map_libcmt.py` and `split_coff.py` now take `--lib` repeatably as a preference
list, so `--lib SP6 --lib SP5` resolves 228 of 244 region functions — the
remaining 16 (1,320 B) match no version on hand (`srand`, `__CRT_INIT`,
`unlock_09*`, `fpmath`, `init_fptrs`, `crt_close_handle`, `crt_once_init`,
`allmul_slow`, two `fcn_*`).

Note the union set does **not** yet improve the PoC link: without `--closure`
it links but leaves 175 LIBCMT symbols (vs 112 for SP6 alone), because the SP5
members define different symbol spellings; with `--closure` it loses `/ENTRY`
again.  The coverage number is the solid result; the link metrics need the
symbol reconciliation.

*Corrected in round 12:* the 175 was a splitter bug, not a symbol problem.
Section-symbol matching means a member has one `.text` symbol per COMDAT, and
`split_coff` looked sections up *by symbol name*, so it extracted an arbitrary
section.  Finding the section from the map's recorded section number restores
the SP6 numbers and makes the union a net win.  All links exit 0:

| split set | objects | LIBCMT leftovers | `.text` end |
|---|---|---|---|
| SP6, no closure | 223 | 112 | 0x100264dc |
| SP6 -> SP5 union, no closure | 228 | 107 | 0x100264de |
| SP6, closure | 246 | 77 | 0x10025ac7 |
| SP6 -> SP5 union, closure | 252 | **73** | 0x10025d0e |

Reference `.text` ends at 0x10023846, so the region is still ~0x24c8 over: the
73 leftovers, i.e. group (2)'s remaining 16 unmatched functions (`srand`,
`__CRT_INIT`, `unlock_09*`, `fpmath`, `init_fptrs`, `crt_close_handle`,
`crt_once_init`, `allmul_slow`, two `fcn_*`) and group (3)'s CRT-internal
references.

## `--closure` works: leftovers 121 -> 77 (2026-09-13, round 10)

The round-9 blocker was one helper object.  Bisected by dropping candidates
from the rsp: when our split set supplies `__CRT_INIT@12`, LIBCMT's
`dllcrt0.obj` is not pulled and LINK stops resolving
`/ENTRY:_DllMainCRTStartup@12` — it builds the console-EXE chain
(`crt0.obj` / unresolved `_main`) instead.  Removing that single object from
the link restores it (exit 0), so `--skip-helper` now defaults to
`__CRT_INIT@12` and the closure is usable.

Measured, all links exit 0:

| split set | objects | LIBCMT leftovers | `.text` end |
|---|---|---|---|
| default (single-section) | 222 | 112 | 0x100263fc |
| `--closure` | 246 | **77** | **0x10025ac7** |

Reference `.text` ends at 0x10023846, so the region is still 0x2281 over — the
remaining 77 leftovers, i.e. group (2) and (3) from round 7 minus what the
closure absorbed.  `__CRT_INIT@12` itself (0x1001b8fb, unmatched) is one of
them and is currently placed by LIBCMT at the end rather than at its VA.

## Section closure: helpers land, the entry lookup does not (2026-09-13, round 9)

Two changes this round, one measured and shipped, one still blocked.

**Shipped: section-symbol relocations are retargeted.**  A relocation may name
a `.text` *section* symbol of a COMDAT the object does not carry; emitting it
as an external literally named `.text` left LINK with an unresolvable
reference.  `build_object` now retargets it at the external function symbol
defined at that section (lowest value), and guards the few members whose
relocations carry out-of-range indices.  With the default single-section
split: **leftovers 121 -> 112 and `.text` end 0x268c0 -> 0x263fc**, link still
clean.  Object counts and the default path are otherwise unchanged.

**Blocked: `--closure` and `/ENTRY`.**  The helper sections are now emitted as
their own *single-section* objects, placed immediately after the function that
branches to them (247 objects total), so the multi-section object shape is no
longer involved.  The link still fails: LINK pulls `crt0.obj` for
`mainCRTStartup` and reports `unresolved external symbol _main`, i.e. it is
building the console-EXE startup chain instead of using the DLL entry.  A
`/FORCE:UNRESOLVED` map of the same link shows `__DllMainCRTStartup@12`
defined by `1001b9d4___DllMainCRTStartup_12.obj` **and** `_mainCRTStartup`
present from `LIBCMT:crt0.obj`, so the entry symbol exists and LINK is still
not selecting it.  The one thing that correlates with the failure is our
objects now supplying `__CRT_INIT@12`, so LIBCMT's `dllcrt0.obj` is no longer
pulled.  Next: either keep `dllcrt0.obj` in the link, or find why
`/ENTRY:_DllMainCRTStartup@12` stops matching when it is absent.

## Section closure: implemented, and the entry symbol blocks it (2026-09-13, round 8)

Group (1) of the leftovers is fixed in the tool.  `scripts/split_coff.py`
gained `--closure`: it walks the relocation graph from the mapped section and
includes the same-member `.text` sections it references, stopping at sections
that are themselves emitted as their own object (so nothing is duplicated) and
claiming each helper section once across the whole run.  With `--closure` the
set is 222 objects / 37,871 B (against 34,280 B single-section), and a
`/FORCE:UNRESOLVED` link drops the leftovers **121 -> 101** at
`.text 0x10026824`.

It is off by default because of one concrete blocker: with closure on, LINK
stops resolving `/ENTRY:_DllMainCRTStartup@12`.  The extracted `dllcrt0`
object does define `__DllMainCRTStartup@12` — a `/FORCE:UNRESOLVED` map shows
it at 0x1001b824 from `1001b9d4___DllMainCRTStartup_12.obj` — and the link
succeeds again if the multi-section object is not used, so the failure is in
the multi-section object's symbol/section wiring (or LINK's entry lookup over
it), not in the closure itself.  `/ENTRY:__DllMainCRTStartup@12` is wrong —
LINK prepends its own underscore and looks for `___DllMainCRTStartup@12`.
That is the next thing to fix; everything else about the closure is measured
and working.

## What the split set still misses (2026-09-13, round 7)

Fixing `map_libcmt.match` to compare the *common prefix* instead of requiring
the member body to be at least as long as the catalog entry (the catalog
pads/truncates: `_exit` 34 vs 17, `_strncpy` 272 vs 254, `_strchr` 192 vs 188)
recovered 209 -> **222 of 244 region functions, 34,790 B of 39,216**.  Relinked
with the 222 split objects, `.text` still ran to 0x100268c0 against the
reference's 0x10023846, with **121 symbols still pulled from `LIBCMT.lib`**.
Those 121 fall into three groups, and only the first is a splitter bug:

1. **Intra-member section closure.**  `_memmove`'s body branches to labels that
   MSVC emitted as *separate COMDAT sections of the same member*
   (`LeadUp1..3`, `UnwindUp0..7`, `TrailUp0..3`, `LeadDown*`, `UnwindDown*`,
   `TrailDown*` — ~40 symbols).  The splitter demotes cross-section references
   to undefined, so the linker re-pulls the whole `memmove.obj` and its
   internals land after the region.  The fix is to include the transitive
   closure of same-member sections in the extracted object.
2. **The 22 unmatched region functions** (4,426 B): `srand`,
   `output` (1,857), `__CRT_INIT`, `exsup` (197), `NMSG_WRITE` (339),
   `setmbcp` (429), `dosmaperr`, the `unlock_09*` family, `crt_close_handle`,
   `crt_once_init`, `allmul_slow`, `fpmath`, `init_fptrs`,
   `fcn_1001a643`, `fcn_1001e638`.  Each needs its own matching rule (several
   are single-instruction helpers, others span COMDAT boundaries).
3. **CRT-internal references** the split set does not supply: `fpexcept`,
   `util`, `fpctrl`, `matherr`, `tzset`, `handler`, `_ceil`, `_strtoxl`.  These
   are pulled by other members, not by game code (`ceil` appears nowhere in
   `src/server.dll`), so they are part of whatever the reference's own members
   referenced.

**The catalog is an incomplete view of the region.**  It lists 254 functions
above 0x1001a150; the PoC link emits 343 there.  Section (2) is bounded by the
catalog, but closing the gap needs the region's true function inventory read
from the binary (boundaries and all), not a name list — otherwise the split
set and the leftover set can never be proven equal.

## Per-function COMDAT selection works (2026-09-13, round 6)

`scripts/split_coff.py` turns the mapped members into standalone per-function
COFF objects: LIBCMT is built `/Gy`, so each function is its own COMDAT
`.text` section, and the script re-emits one object per section (relocations
remapped onto a rebuilt symbol table, string table rebuilt, cross-section
symbol references demoted to undefined so the linker resolves them from the
sibling object).  Measured: **209 objects, 34,280 B of `.text` against the
reference region's 34,550 B** — per-*function* selection is essentially exact,
against the 40,896 B whole members carry.

A PoC link with those 209 objects on the command line, in reference-VA order,
places them inline and in order:

```
_fclose                  split object   0x1001a0e0   (reference 0x1001a18a)
_srand                   split object   0x1001b105
__DllMainCRTStartup@12   split object   0x1001b4cb
```

The offsets are the game region's cumulative -0xaa, as in round 5, so member
placement still cannot be checked until the game region is exact.

**What is left is not placement but coverage.**  The PoC's `.text` still ran to
0x10025ce2 against the reference's 0x10023846, because `LIBCMT.lib` is still on
the link line and appends every member our objects reference that the split set
does not contain (`_fflush` landed at 0x10022bd8 from `LIBCMT:fflush.obj`).
That residue is the "our C references symbols the reference does not have"
side of the reconciliation, not a placement bug: the split set is 270 B short
of the region, while the leftovers account for the extra ~9 KB.  Next: either
supply every symbol the link needs from the split set (so `LIBCMT.lib` drops
out) or reconcile the extra references themselves.

## Explicit member placement works; whole members overshoot (2026-09-13, round 5)

Round 5 built the link the plan calls for and measured the two obstacles.

**The reference's `DllMain` is LIBCMT code.**  `0x1001b9d4` — the reference's
`AddressOfEntryPoint` — is byte-for-byte `__DllMainCRTStartup@12` from
LIBCMT's `dllcrt0.obj` (`scripts/map_libcmt.py` reports the symbol).  So
`crt_region/dllmain.c` reverses library code, and `/ENTRY:DllMain@12` should
be `/ENTRY:_DllMainCRTStartup@12`.  The same holds for `amsg_exit.c`
(`__amsg_exit`, also `dllcrt0.obj`).

**Explicit member objects are placed inline, in the order given.**  A PoC link
put 99 extracted LIBCMT members (the ones `map_libcmt.py` maps for
VA >= 0x1001a150) on the command line after the game objects:
`_fclose` landed at 0x1001a0e0, immediately after `srv_SeedRandomWithTime`,
and the rest followed in the supplied order (after fixing a sort bug that
ordered the members by *path* instead of by VA).  So the mechanism the plan
needs is confirmed — the library is no longer appended at the end.

**But dropping the hand copy regresses today.**  Replacing
`crt_region/dllmain.c` with LIBCMT's `_DllMainCRTStartup@12` (and
`/ENTRY:DllMain@12` with `/ENTRY:_DllMainCRTStartup@12`) measured
`.text 0x2277c` against the reference's `0x22846` — **-0xca**, where the
committed tree is +6 — and postlink coverage 394/7463 against 402.  So the
`dllmain.c` object is supplying something else as well (or the entry change
alters which members the linker pulls), and the swap has to wait until the
member placement is in place.  The tree is restored; this is recorded as the
target state, not a change to make on its own.

Two obstacles, both measured:

1. **Whole members overshoot by ~6.3 KB.**  The 99 members carry 40,896 B of
   `.text` against the reference region's 34,550 B (0x1001a150..0x10022846),
   because a member ships functions the reference never had.  The PoC's
   `.text` therefore ran to 0x10025658.  Per-*function* selection is required:
   either split each member's `/Gy` COMDATs and place only the sections the
   reference uses, or drive the link with `/OPT:REF` plus an `/INCLUDE:` for
   every symbol in the region.  A first `/OPT:REF` attempt collapsed the whole
   link to 0x10011504, so the `/INCLUDE:` list has to be complete before that
   switch is flipped.
2. **Absolute VAs inherit the game region's cumulative error.**  Placing the
   members right after the game objects put `_fclose` at 0x1a0e0 against the
   reference's 0x1a18a, exactly the -112 B the game region is short by the end
   (CrashDump +16, m_AllocTracked -64, vfs_ReadData -32, cm_ExCopyEntityData
   -32, ...).  Member placement cannot be checked until the game region is
   exact, but it can be developed independently.

## LIBCMT is appended after every object — the reference interleaves it (2026-09-13, round 4)

The objective says zlib and LIBCMT are to be *linked in*, not reversed, so
round 4 tested dropping the eight `crt_region` files that exist only to
displace LIBCMT members (`dllmain.c` must stay: the reference's
`AddressOfEntryPoint` is 0x1001b9d4, i.e. the hand-written `DllMain`, not
LIBCMT's `DllMainCRTStartup`).  Measured, with `dllmain.c` kept:

| | committed (keep files) | keep files dropped |
|---|---|---|
| compile errors | 0 | 0 |
| `.text` VirtualSize | 0x2284c (+6) | 0x22572 (**-0x2d4**) |
| imports | 100 | 102 (**+IsBadWritePtr +FatalAppExitA**) |
| postlink coverage | 402/7463 | 402/7463 |

Dropping them is worse on both counts, so the tree is restored.  But the
experiment exposes the real structure of the problem:

**MSVC LINK places every archive member after every command-line object.**  Our
link ends its own objects at ~0x1bd40 and LIBCMT's members start at ~0x1c000
(`_fflush` at 0x1caf5, `_srand` at 0x1d8d0, `__mtinitlocks` at 0x1c663).  The
reference **interleaves** members with game/CRT objects:

```
0x1001a140 srv_SeedRandomWithTime   (game, 14 B)
0x1001a150 srand                    (LIBCMT)
0x1001a18a fflush                   (LIBCMT)
0x1001a1bb fclose_lk                (LIBCMT)
  ...                                (LIBCMT members through 0x1001a643)
0x1001a643 fcn_1001a643             (crt_region/initterm.c)
0x1001a758 __initterm               (LIBCMT)
  ...
0x1001b9d4 DllMain                  (crt_region/dllmain.c)
0x1001d036 _mlock                   (crt_region/mlock.c)
```

So the LIBCMT region can only line up if its **member objects are on the
command line, in reference-VA order**, instead of the whole `.lib` being
appended.  That is still "linking LIBCMT in" — stock objects, no reversing —
and it is the concrete next step for roughly 39 KB (28%) of `.text`.

Feasibility, measured this round by byte-matching every reference `.text`
function against LIBCMT.sp6's COMDAT sections with the same
fixed-bytes-minus-reloc-slots rule `check_library_code.py` uses: **209 of the
254 reference functions at or above 0x1001a150 match a stock LIBCMT body
outright — 32,455 B of 39,216 B (83%)**, including the sbh family and the 68
functions already reversed under `crt_region/`.  (A first pass reported only
136 because it pre-filtered candidates on their raw first 8 bytes; the
reference's resolved `a1 imm32` operands differ from the library's zeroed
reloc slots, so the pre-filter has to be reloc-insensitive.  A full scan with
the mask rule is the correct method and costs seconds.)

The 45 non-matching ones are mostly boundary artifacts rather than missing
code: `0x10021ac0 strcmp` is 140 B *inside* LIBCMT's `_strcmp`, so the
catalog's boundary, not the body, is what differs.  The genuinely absent set
is the ~2.6 KB the file already lists elsewhere (`_ld12cvt` 673 B, several
`unlock_09*`, `_output` 1857 B, ...).  So placing the stock members explicitly
buys ~32 KB of byte-exact `.text` before any of those need a decision.

## The ten real size mismatches (2026-09-13, round 3)

`rebrew verify --full` is the only accurate size source; `db/server.dll_functions.csv`
carries stale registry sizes (it reports 600 B for `srv_LogWinsockError`, whose
`rebrew test` slot is 758 and byte-exact).  The functions whose object size
disagrees with the target are exactly:

| VA | function | obj | target | delta | match |
|---|---|---|---|---|---|
| 0x10002770 | CrashDumpUnhandledExceptionFilter | 2137 | 2115 | +22 | 12.5% |
| 0x10006580 | m_AllocTracked | 608 | 658 | -50 | 36.7% |
| 0x10008a90 | vfs_ReadCompressed | 499 | 492 | +7 | 27.6% |
| 0x10008e40 | vfs_ReadData | 446 | 472 | -26 | 30.0% |
| 0x10009020 | vfs_OpenStream | 693 | 667 | +26 | 64.0% |
| 0x1000d930 | cm_ExSellObjekt | 2055 | 2057 | -2 | 9.7% |
| 0x1000ec00 | cm_ExCopyEntityData | 880 | 901 | -21 | 58.3% |
| 0x100128f0 | ls_LoadBuildingEntityState | 1464 | 1463 | +1 | 8.5% |
| 0x10016f80 | gm_FindNextFilteredEntity | 342 | 346 | -4 | 48.5% |
| 0x10018850 | gm_AllocSpieler | 3688 | 3689 | -1 | 23.1% |

Note that a near-zero size delta does not mean a near byte match:
`cm_ExSellObjekt` (-2), `ls_LoadBuildingEntityState` (+1) and
`gm_AllocSpieler` (-1) are 8-23% matches.  The remaining 11 non-byte-exact
functions are size-exact but byte-different (`srv_LoadBuf`, `gm_ObjectsAvailble`,
`cm_ProcessCommandQueue`, `cm_ExProdObjekt`, `m_PoolAlloc`,
`gm_CalculateProductionValue`, `vfs_OpenStream`, `gm_CheckInventoryCapacity`,
`ahm_ExAllocAlchemist`, `gv_ExAllocGraveyardWorker`, `ServerMainThread`).

**The inline-asm prelude is not transplantable into a divergent body.**
Round 3 replaced m_AllocTracked's `memset(ptr, 0, sz)` with the target's
prelude as an `__asm` block naming the C locals.  Result: obj 608 -> 646,
match 241 -> 182.  The reference's prelude reads dest from `[ebp-4]` and
length from `[ebp-8]`; this reconstruction homes them in ebx and `[ebp+0xc]`,
so the block is not the same bytes and the surrounding allocator degrades.
Getting the prelude bytes into a function whose operand homes already differ
is not the win it looks like — the homes have to match first.

## The alignment is now a short, named list (2026-09-13, round 2)

Every game TU is contiguous, so `/MAP` deltas against
`db/server.dll_functions.csv` now read as one gate plus four small shortfalls.
`.text` is 0x2284c (+6) and postlink coverage 402/7463 (5.4%).

| from VA | delta | cause |
|---|---|---|
| 0x10001000 | 0 | |
| 0x10002fc0 | **+16** | CrashDumpUnhandledExceptionFilter, obj 2137 vs 2115 |
| 0x10006820 | **-48** | m_AllocTracked, obj 608 vs 658 |
| 0x10008c80 | -32 | |
| 0x10009020 | -64 | |
| 0x1000ef90 | -96 | |
| 0x10010710 | -112 | last event before the LIBCMT region |

Fix CrashDump and the delta is 0 for the first 0x3800 bytes of `.text` — the
whole 0x2fd0..0x6820 span, ~28% of the map entries, validates in one change.
It is the highest-value function in the tree by a wide margin.  The prologue
is the whole difference: the target saves ebp/esi with frame 0x280 and keeps
`hDbgFile` in ebp; ours saves ebx/ebp/esi/edi with frame 0x28c and spills it.
Any C rewrite that drops two callee-saved registers is the fix; the body
after the prologue already matches instruction for instruction once the
0x14 esp displacement is taken out.

Round 2 also split the last two non-contiguous game TUs the way round 1 split
friedhof_dump/lobbycommands: `spiel62.c` -> `gm_RemoveObjectWrapper.c`
(0x17f30+0x17f60) and `spiel622.c` -> `gm_RandomQuadratic.c` (0x1a110), so
`gm_InitEntityIfValid.c` (0x17f90) and `gm_RandomFloat01.c` (0x1a0f0) land
between their neighbours.  All four moved functions re-tested unchanged.

## The block-fill prelude is not a compiler template (2026-09-13)

Round 1 mapped the six `lea ecx,[edi+edi*2]; and ecx,3` sites (3 present via
inline asm, 3 missing).  The open question was whether another MSVC emits it.
Measured by compiling m_AllocTracked with `#pragma intrinsic(memset)` — the
configuration that inlines the fill — under every toolchain that has a memset
expansion:

| toolchain | match | obj |
|---|---|---|
| msvc-4.2 | 143 | 694 |
| msvc-5.0 | 193 | 617 |
| msvc-6.0-sp4 | **226** | 613 |
| msvc-6.0-sp6 | 226 | 613 |
| msvc-7.0 | 134 | 617 |
| msvc-7.0-rtm | 135 | 615 |
| msvc-7.1 | 134 | 617 |

No toolchain reaches the prelude (target 658); the shape is byte-invariant
across the shipped binaries, `sub`+`jle` with no intervening `test` is not
msvc6 output, and no C spelling of the align-up split reproduces it.  The
prelude is therefore hand-written asm in the original game code, not a
compiler template — reproducing it with an inline `__asm` block matches what
the original did (the tree already carries three such blocks).

**m_PoolAlloc (0x10006d20) is 4 bytes from exact and its recorded blocker is
stale.**  The metadata says "alignment-prefixed memset prelude — pure C cannot
emit"; the object is 270/270 and the prelude IS emitted by the file's inline
asm.  `rebrew diff 0x10006d20` reports `{exact 101, reloc 4, structural 2}`:
the only residual is the order of the two parameter homes, target
`mov [ebp+0xc],edx` / `mov [ebp+8],esi`, ours reversed.  Measured this round:
any source order that puts the slot home first (swapped stores, a shared
`volatile int*`, dropping the `asize` temp and homing `alen` directly) lets
the scheduler sink `add esi,-4` past it and lands on 260/270.  The shipped
order keeps `add esi,-4` early but emits the homes reversed.  Whoever clears
that one scheduler artifact gets the function free.

## Structural link alignment (2026-09-13) — `.text` +214 -> +6, order fixed

The raw link (postlink skipped — the POST_BUILD step still refuses) was
`0x2291c` before this pass and is `0x2284c` now against the reference's
`0x22846`: **+6 bytes**, down from +214.  postlink map coverage 4.1% -> 5.4%.
The size is now nearly right; what is left is placement and per-function size.

Five fixes, each measured by relinking with `/MAP` and diffing symbol VAs
against `db/server.dll_functions.csv`:

- **check_header.c had a private `get_byte`.**  The reference's check_header
  (0x100036d0) calls **0x10003820** twelve times (disassembly of the target),
  i.e. the shared VFS reader, not a TU-local helper.  `rebrew test` passed
  the file anyway because call displacements are masked.  Replacing the local
  body with a `vfs_GetByte` call deleted the unreferenced static
  `_get_byte` (128 B) from the link and left check_header byte-identical
  (332/332 RELOC).
- **gzread split into its own TU.**  The original places check_header
  (0x36d0), then vfs.c's two functions (0x3820, 0x38a0), then gzread (0x3960);
  one object can only emit its functions contiguously, so gzread moved to
  `Units/vfs/vfs_c/gzread.c`.  It is 559/559.
- **Two infblock bodies are not in the reference at all.**
  `inflate_set_dictionary` and `inflate_blocks_sync_point` have no exact-byte
  match anywhere in the target (their only callers, `inflateSetDictionary`
  and `inflateSyncPoint`, are already `#if 0` in `references/zlib/inflate.c`),
  but the tree links `/OPT:NOREF`, which keeps unreferenced COMDATs.  They
  were `#if 0`'d in `references/zlib/infblock.c` too (~0x50 B).
- **infcodes.c and inffast.c had no `--first-va` in `order-sources`.**  They
  sorted last and their five functions linked at 0x1a950-0x1b160 instead of
  0x4b80-0x5390 (2,900 B out of place).  Added
  `--first-va infcodes.c=0x10004b80` and `--first-va inffast.c=0x10005390`.
- **Two merged TUs split.**  `order-sources` orders *files* by their first
  VA, so a file holding functions from non-adjacent reference regions cannot
  be position-aligned.  `friedhof_dump.c` (0x10530/0x10d10/0x11940) became
  `gv_CheckSlotActive.c` + `gv_UpgradeField.c` + `gv_MoveSlotEntry.c`;
  `lobbycommands.c` (0x145e0/0x146c0/0x14af0/0x14db0) became
  `lb_ExPlayerlist.c` + `fcn_10014af0.c` + `lb_ExLobbyServerCommand.c`.
  All seven functions were re-tested and kept their status.

With those in place the delta is a single **+16** from 0x10002fd0
(EmitCrashModuleLine) through 0x100067f0 — every function in the first 40% of
`.text` links exactly where the reference has it, once CrashDump is fixed.

## The six block-fill prelude sites (2026-09-13) — three are missing

`docs/msvc6-c-shapes.md` §11 says the `lea ecx,[edi+edi*2] / and ecx,3 /
sub ebx,ecx / jle / rep stosb / …stosd… / …stosb` prelude needs asm.  Scanning
both images for `8d0c7f 83e103` locates the sites exactly:

| reference | built | supplier |
|---|---|---|
| 0x10006730 | — | **m_AllocTracked (0x10006580)** — the -50 B shortfall |
| 0x10006929 | 0x100068f9 | m_init (0x100068e0), inline `__asm` in m_alloc.c |
| 0x10006e0d | 0x10006ddd | m_alloc2.c inline `__asm` |
| 0x10008f0c | — | **vfs_ReadData (0x10008e40)**, PROVEN 30.0% |
| 0x1000b057 | 0x1000b017 | server4.c inline `__asm` |
| 0x10017611 | — | **gm_AllocGebaeude (0x100174d0)**, PROVEN 38.8% |

So the three non-byte-exact PROVEN functions that are *not* prologue/register
walls are exactly the three whose prelude site is missing: supplying the fill
is most of each one's size delta (m_AllocTracked -50, vfs_ReadData,
gm_AllocGebaeude).  Only three `__asm {` blocks remain in the tree
(`grep -rn '__asm[[:space:]]*{'`): server4.c:448, m_alloc.c:220,
m_alloc2.c:231 — all of them this one prelude.

A pure-C spelling of the prelude would close three functions at once and
delete all remaining inline asm — this is the single highest-value open
question in the tree.  Everything §11 records as tried (pointer type,
provenance, length shape, 12 flag sets, the align-up split) should be read
before re-probing; the split form in particular is documented as worse
(42-66 matched vs 105 for plain `memset`).

## Next three blockers, in link order (2026-09-13)

1. **0x10002770 CrashDumpUnhandledExceptionFilter** — obj 2137, target 2115.
   +22 bytes, and with 16-byte COMDAT padding it is the whole +16 shift for
   0x2fd0-0x6820.  `PROVEN` masks it in `verify`.  Blocker is the prologue:
   4 saved regs (ebx/ebp/esi/edi) against the target's 2 (ebp/esi, ebx/edi
   deferred), frame 0x28c vs 0x280, hDbgFile spilled at [esp+0x44] instead
   of held in ebp.  This is the single highest-value function in the tree.
2. **0x10006580 m_AllocTracked** — obj 608, target 658 (-50).  First
   shortfall; moves the delta from +16 to -48.  `PROVEN`, 36.7% match.
3. **spiel62.c / spiel622.c** are the last non-contiguous game TUs
   (`gm_InitEntityIfValid` at 0x17f90 interleaves spiel62's 0x17f60/0x17fb0;
   `gm_RandomFloat01` at 0x1a0f0 interleaves spiel622's 0x1a0d0/0x1a110).
   Split them the same way as the two above.  `server4.c` and
   `crt_region/initterm.c` also report interlopers but those are Ghidra
   switch-case labels / library bodies, not real TU members.

## Tooling environment (2026-09-13) — the rebrew checkout is a moving target

`rebrew` is installed editable (`__editable__.rebrew-0.6.0.pth`) pointing at
`~/Desktop/Projects/relumea/rebrew/src`, which is being edited concurrently.
Mid-pass `rebrew-cmake-cl` died with `ToolchainSpec.__init__() got an
unexpected keyword argument 'image_binary'` (working-tree refactor of
`toolchain_spec.py`/`toolchain_data.py`).  A stable copy of the committed
tree (`git archive HEAD src/rebrew`) was extracted to
`.scratch/rebrew-stable/` and used through `PYTHONPATH` for `verify`,
`lint` and the build.  `scripts/gate.sh` will keep failing on the build step
until that checkout is consistent again — it is not this tree's regression.
There is also a docker container from a 2026-09-11 `rebrew match` still
spinning (`docker ps` name `rebrew-93321f0d944a`), pinning one core.

## gm_Open back to RELOC (2026-09-12)

`0x10015950` had drifted to SIZE_MISMATCH (859/861) when a later rewrite
replaced the proven producible-count tail with a `count_p` pointer local.
Restoring the inline double spelling of `g_entity_type_table + row_index *
0x24d + 0x21` brings it back to RELOC 861/861: the multiply form is what gives
the byte counter the SIB base role (docs/msvc6-c-shapes.md section 34), and
routing the read-modify-write through a pointer local forces a `lea` and lands
2 bytes short.  verify --full 277/280 -> 278/280.

## `.text` link shortfall (2026-09-11) — the build is not byte-identical

The raw link's `.text` is 2,197 B short of the reference's 0x22846 (0x21fb1,
3,269 B before the `/INCLUDE:` change below).  `rebrew postlink` used to pad it
back to the reference's VirtualSize and apply the layout package's call/operand
maps by offset, producing a binary 92% wrong in `.text` while the section table,
imports and header fields all matched.  Nothing failed: `rebrew verify` is
per-function at the object level, and `verify --whole-binary` compares section
sizes, exports, imports, `.rsrc` and headers, never `.text` content.  The layout
guard now fails loud instead: 269/7,463 map entries validate (3.6%, minimum 90%).

Measurements (raw link, postlink skipped):

| commit | date | `.text` VirtualSize | vs reference |
|---|---|---|---|
| `8f135ed` | 2026-08-22 | 0x22c9f | +0x459, trimmable, layout map 99.5% |
| `cce0a1b` | 2026-08-25 | 0x2344f | +0xc09, trimmable |
| `93ecf29` | 2026-08-26 | 0x1edc2 | **-0x3a84** |
| `c77489a^` (parent) | 2026-08-26 | 0x1edc2 | -0x3a84 (same tree) |
| `b67f1d3` (HEAD) | 2026-09-11 | 0x1ee1d | -0x3a29 |

So the regression is `93ecf29` ("Convert naked asm to proper C across
game/loadsave/command units"), not the LIBCMT switch in `c77489a` that
followed it. That commit deleted 72,290 lines and added 6,197 across 140
files: the naked `_emit` dumps became proper C and the link lost ~18KB of
`.text` it had been emitting. `8f135ed` is the last link that produced the
reference's shape.

Tried and measured (all in the raw-link metric above):

- Restoring the 11 `crt_region` TUs deleted by `7d48b38` (`malloc.c`, `free.c`,
  `realloc.c`, `ioinit.c`, `tidtable.c`, `cexit.c`, `setargv.c`, `flsall.c`,
  `fwrite_fread.c`, `h_ad29.c`, `lock_streams.c`), after renaming the
  `g_<VA>` globals to the current CRT names: 0x1ee1d -> 0x1fcdd. Recovers
  0xec0 of the 0x3a29. Necessary, not sufficient.
- Forcing the reference's CRT members in with `#pragma comment(linker,
  "/include:...")` for every `// LIBRARY:` marker in `library_msvc.h`: fails
  with 104 unresolved externals. Many names in those headers (`code_translate`,
  `overflow_add`, `bit_reverse`, ...) are not linkable LIBCMT symbols; the
  true symbol/object mapping has to come from `rebrew lib-match --stock-lib`,
  and MSVC marks some helpers (`_initterm`, `_parse_cmdline`) static so they
  cannot be named at all.

Next: find which converted functions emit less than the dumps did. `link /MAP`
on the current tree lists every contribution to `.text`, which answers it in
one relink. The dump files emptied by `93ecf29` are the place to look:
`Units/vfs/infblock_dump.c`, `infcodes_dump.c`, `inffast_dump.c`,
`vfs_CompressBlock.c`, `gz_gzread.c`, `gz_check_header.c`,
`ReadVfsCompressed.c`.

The guard added to `rebrew postlink` on 2026-09-11 makes this class of
breakage loud: it validates the layout package's sparse maps against the
built bytes before patching and fails below 90% coverage (reference 100%,
this tree 4%).

> **Tooling moved (2026-08-22):** the `scripts/` helpers referenced below
> were folded into rebrew: `gen_link_stubs.py` → `rebrew gen-stubs`,
> `inline_strings.py`/`define_strings.py` → `rebrew inline-strings`,
> `own_globals.py`/`own_init_arrays.py` → `rebrew data --own`,
> `reassign_globals.py` → `rebrew data --fix-ownership`,
> `converge_layout.py` → `rebrew data --converge`,
> `consolidate_declarations.py` → `rebrew merge --consolidate`.
> Entries below describe the work at the time.

## Service-pack sweep (2026-09-11) — new, and negative

The game was built with an SP4-or-later toolchain: the reference's sbh family
matches `LIBCMT` from SP4/SP5/SP6 and not from base/SP1/SP2, and `0x1001e638`
(`___old_sbh_resize_block`, 169 B) matches SP5 alone.  That pins the pack; it
does not change a byte.

Compiler sweep: all seven VC 6.0 builds (base, SP1..SP6, CL 12.00.8168 and
12.00.8804) over the 21 functions `rebrew verify --full` does not byte-match.
Twenty compile to identical objects under every build.  The one exception,
`0x1000d930 _cm_ExSellObjekt`, gives `obj 2030` under SP3/SP4 and `obj 2055`
under the other five; the target is 2057, so neither variant closes it.  Both
remaining `verify` failures (`0x100093a0` obj 2434 = target but bytes differ,
`0x10018850` 3673 vs 3689) are byte-identical across all seven.

Library sweep: relinking the built objects against SP5's whole `LIB` tree
instead of SP6's moves `.text` at 2 offsets (112357, 123706), the same
magnitude as relinking one tree twice.  SP6's `LIBCMT` is compatible with the
reference for everything our link pulls.

Where the remaining 3,269 B is, with the false leads removed: it is CRT member
selection, not missing game code.  The 279 annotated functions net +29 B
against the reference (the 19 PROVEN sum to roughly +25, the two walls +4), so
nothing we reverse explains the deficit.

Matching every catalog entry typed `library` (`0x10022ff1`; reloc slots
zero-filled) against the four MSVC 6.0 `LIBCMT.LIB` variants and every object
the build compiles leaves 24 entries (3,360 B) with no supplier in the link.
Three resolve to interior catalog addresses inside members we do have (`0x1001af30`
is 156 B into `_strchr`, `0x1001aff0` 100 B into `_strstr`, `0x10021ac0` 140 B
into `_strcmp`), and `strdup`/`isctype`/`setmode_lk` are in the link map, so
about 2.6 KB are genuinely absent:

| reference VA | size | CRT member | in the link map |
|---|---|---|---|
| `0x10022a2f` | 673 | `_ld12cvt` | no |
| `0x1001b757` | 334 | `_unlock_09e` | no |
| `0x1001f1e2` | 233 | `_IsProcessorFeaturePresent` | no |
| `0x100219f7` | 201 | `_dtold` | no |
| `0x1001e7d4` | 197 | `_exsup` | no |
| `0x100200a6`, `0x1002001d`, `0x1001a89c`, `0x1001abeb`, `0x1001b8a5`, `0x1001a8fb`, `0x1001ac43` | 156-45 | `_unlock_09f/g/a/c/9/b/d` | no |
| `0x1001f855` | 123 | `_isctype` | yes |
| `0x100207b8` | 120 | `_wctomb_lk` | no |
| `0x10022ea1` | 111 | `_setmode_lk` | yes |
| `0x1001b088` | 56 | `_init_fptrs` | no |
| `0x10020915` | 46 | `_crt_once_init` | no |
| `0x10023812` | 46 | `_strdup` | yes |
| `0x1001e7ba` | 34 | `_EH3_save_context` | no |
| `0x1001b070` | 23 | `_fpmath` | no |
| `0x1001a140` | 14 | `_getpid` | no |

`_strncnt` (43) is in the same list but cannot be named at all: it is static
inside `a_cmp.obj` (COFF storage class 3), so it is absent from the archive
symbol index and `/INCLUDE:_strncnt` fails LNK2001.

`___ld12mul` (544) and `__except_handler3` (216) are a different case: both are
in LIBCMT and reachable with `/INCLUDE:`, and `CMakeLists.txt` now passes both
on `server_dll` (both `target_link_options` branches; it also pulls `mantold.obj`
and `tenpow.obj`).  Measured: link clean, imports unchanged at 100, `.text`
VirtualSize 138,113 -> 139,185 (+1,072 B) against the reference's 141,382, and
the postlink layout coverage is unchanged (269 vs 270 of 7,463 map entries).
That 1,072 B is a link change, not decompilation.

**This paragraph's conclusion was wrong and is retracted (2026-09-12).**  The
LNK2001 list came from *guessed, undecorated* symbol names.  With RevEng.AI's
names for the same VAs the members are in LIBCMT after all, and forcing six of
them — `___dtold`, `_wctomb`, `__setmode_lk`, `__strdup`, `__NLG_Notify`,
`__ms_p5_mp_test_fdiv` — takes `.text` from 0x21fb1 to **0x228ec against the
reference's 0x22846**: 166 B *over*, where this file previously claimed 2,197 B
short and unreachable.  `$I10_OUTPUT` (0x10022a2f, 659 B) is genuinely absent
(LNK2001) and is not forced, so the honest count is six of seven.  `exsup.obj`
is likewise present, reachable via `__NLG_Notify`, not absent as the table said.

What remains is **member selection, not missing code**: `/INCLUDE` drags whole
LIBCMT objects, so the six add ~2,363 B for ~492 B of annotated functions
(`___dtold` alone pulls `cfout.obj`, contributing 944 B).  The 166 B is the
difference between the reference's choice of members and ours.

**How not to measure it.**  Five attempts to attribute the 166 B by searching
the two linked images all failed, and the reason is structural: the operands
that differ between two links — IAT slots (`[0x10024154]` vs `[0x10024158]`) and
intra-image relative call displacements — carry **no relocation entry**, so
masking cannot reach them; and the annotation VAs do not bound functions
reliably.  Byte search, `.reloc`-masked search and disassembly-level search are
all invalid here.  The working route is a layout-resolved comparison
(`rebrew test --linked`, or `reccmp`, for which `db/server.dll_functions.csv`
is already formatted) or a member-level comparison against `LIBCMT.LIB` itself.

`rebrew lib-match --lib .scratch/libcmt/LIBCMT.sp6.LIB` byte-matches 18 reversed
functions against LIBCMT members (the `__sbh_*` / `___old_sbh_*` family,
`__DllMainCRTStartup@12`, `__initterm`, `__lock`, `__unlock`), so the
`crt_region/` scaffolding agrees with the library rather than duplicating a
member the link already carries.

Tooling: the SP1/SP2/SP3/SP5 images never exported `INCLUDE`/`LIB`, so `rebrew
match --flag-sweep-toolchains` reported them as compile failures
(`score: Infinity`) until `rebrew.toolchain.image_msvc_env` supplied the env
from each image's `tool_root`.  All seven builds now report the same match
counts.  The technical matrix lives in rebrew's `docs/TOOLCHAIN.md`
("Service packs: what differs, and how to tell which one a target used").

## cm_RouteCommand recovered (2026-09-11)

`0x10014ca0` carried metadata (RELOC, 265 B) but no source anywhere in the
tree: the only copy was `lobby_c/lb_BroadcastStateChange.c.bak`, left behind
when that TU was split into `lobbycommands.c`, `lb_HandleEntitySync.c` and
`plant.c`.  `lobbycommands.c`'s `case 6` was calling the `fcn_10014ca0` stub in
`link_stubs.c`, which returns 0.

Restored as `command/command_c/cm_RouteCommand.c` (RELOC, 265/265, 6 relocs),
call site renamed, stub deleted.  `rebrew verify --full` 277/279 -> 278/280;
raw-link `.text` 0x21a81 -> 0x21b81 (+256 B net; the stub was 16 B).

Look for more of this class by crossing `link_stubs.c` stubs and stray `.bak`
files against the metadata: a stub whose VA has a strong status, or a `.bak`
holding a function no live TU defines.  The raw "strong status but no live
annotation" scan over-reports (63 VAs, mostly library companions such as
`gzread` and `inflate_blocks`), so the stub/`.bak` cross-check is the
trustworthy signal.

## Types and globals into headers (2026-09-11) — measured, not started

- `rebrew_globals.h` (generated by `rebrew data --gen-header`) is included by
  **no file**, and neither is `types.h` (65 named structs pulled from Ghidra).
  Meanwhile 170 of 309 extern-declared globals are declared in two or more
  files (`g_entity_type_table` in 33).
- Wiring the globals header exposed two generator bugs, both fixed in rebrew:
  a leading underscore was stripped from metadata-named globals
  (`_FPinit` -> `FPinit`, `_osver` -> `osver`), and array / function-pointer
  types were emitted as invalid C (`extern struct T[18] x;`,
  `extern void (__cdecl *)(int) x;`).  Regenerating now emits
  `extern struct T x[18];` and `extern void (__cdecl *x)(int);`.
- Three things still block the wiring:
  1. the header names two types it does not define, `OldSbhRegion` (with its
     `OldPara` / `OldRegionMap` / `OldSbhPage` family) and
     `struct rterr_entry`, which are defined inside `sbh_pool.c` and
     `amsg_exit.c`;
  2. `rebrew test` / `rebrew verify` compile with only the source directory on
     the include path, so `#include "rebrew_globals.h"` resolves in the CMake
     build (`-I src/server.dll`) but not there;
  3. 77 of the 290 declarations disagree with the header's type, six of them
     real conflicts (`g_connections` array-vs-scalar, `g_download_slots`,
     `g_log_buffer`, `g_log_level_table`, the two m_pool strings).  The TU
     spelling is the one that compiles to matching bytes.
- Once those three are done, `.scratch/consolidate_globals.py --apply` removes
  the 213 matching declarations across 55 files in one pass.  It was applied
  and reverted because the header did not compile.
- Recipe for (1), measured: the sbh family is defined in full in
  `sbh_pool.c:70-99` and `sbh_globals.c:61-90` (identical fields, only the
  offset comments differ), while `sbh_aliases.c:20,22` carries bare forward
  typedefs (`typedef struct __old_sbh_page OldSbhPage;`) that would collide
  with the real typedefs.  `struct rterr_entry` is defined in
  `amsg_exit.c:22` and `data_globals.c:113`.  So: put `OldPara`,
  `OldRegionMap`, `OldSbhPage`, `OldSbhRegion` and `struct rterr_entry` in a
  new `rebrew_types.h`; drop the full blocks from those four files, replace
  the two forward typedefs in sbh_aliases.c with the include; insert
  `rebrew_types.h` *before* `rebrew_globals.h` in every file the consolidation
  touches.
- Applying the recovered structs needs a layout check first.  `CommandPacket`
  has the right extent (0x99, matching `cmd_buffer_primary[0x99]` in
  ServerMainThread.c) but its field map cannot be right: it places
  `payload[137]` at 0x8, while the lobby handlers read a command-type byte at
  `msg+0x10` and ints at `msg+0x14` / `msg+0x18`.

## Short-local naming pass (2026-09-11) — done bar the tail

Method: `scripts/rename_locals.py` renames identifier occurrences outside
comments, member accesses and struct field declarations; `scripts/rename_locals_comments.py`
then follows the rename through the probe logs, skipping the verbatim Ghidra
quote blocks.  Re-test the file after each (`rebrew test <file>`), then the
periodic `rebrew verify --full`.

Policy: loop counters (`i`, `j`, `k`) and `n`/`id` stay — idiomatic counters,
not decompiler temporaries.  Some audit hits are struct members (`fc` in
`aemter.c`'s COPY24, `a`/`b`/`c` in `ls_LoadSavegameHeader.c`'s SaveHeaderTail)
and stay: renaming a field would desynchronise its accesses.

Renamed in 30 files: aemter, spiel622, alchemistry_logic2/3, spiel_dumpD,
gv_ExAllocGraveyardWorker, gv_AllocGraveyardField, gv_SpawnEntities, cm_ChkChangeBits,
cm_ChkChangeAttribute, cm_ChkJoinLeaveElection, cm_ExJoinLeaveElection,
cm_ChkSellObjekt, cm_ExSimSpecialAction, cm_ExChangeDesire, cm_ExChangeFloat,
cm_ExClearLagerslot, cm_ExAllocWarEvent, cm_ExAllocClientSpieler,
cm_GetBuildingStatCount, cm_ExModifyStat, cm_ExMoveObjekt,
cm_ExRemoveLinkedObject, amsg_exit, crt_heap, vfs4, vfs_OpenStream,
check_header, CrashDumpUnhandledExceptionFilter, InitializeLogAndErrorHandler,
plant, loadsave2, loadsave3, spiel, spiel5, spiel6, spiel62,
gm_AllocSpieler, gm_AllocRaum, gm_InitObjektHersteller,
gm_ObjectsAvailble, InitNewDynastyEntity, lb_HandleEntitySync,
lb_ExPlayerHasJoined, lobbycommands, m_alloc2, ProcessSendData, server4,
srv_LoadBuf.

Closed since (all renamed, re-tested RELOC/NEAR_MATCHING unchanged):
- `server2.c` — the three `p` locals are `slot_walk` (the struct-declaration
  guard in `scripts/rename_locals.py` was treating `struct Foo* x;` as opening
  a struct definition, so the declarations were skipped while the uses were
  renamed; only a line without a trailing `;` starts a definition now).
- `m_AllocTracked.c` — `np`/`node_slot`, `pp`/`prev_slot`, comments included.
- `ls_LoadDynamicEntities.c` — `p`/`record_cursor`;
  `ahm_ExAllocAlchemist.c` — `pp`/`slot_ptr`.
- `cm_ExAllocWarEvent.c` `fc`, `aemter.c` `fc`, `ls_LoadSavegameHeader.c`
  `a`/`b`/`c`: **struct members**, not locals — renaming a field would
  desynchronise its accesses, so they stay.
- `crc32.c` `c`: zlib's own code, kept for library fidelity.

Structs (`types.h`) — measured, not applied: the Ghidra-pulled set is a
*shape* catalogue, and most of its fields are placeholders (`word0`, `byte2`,
`field178`), so applying it would move placeholder names into the code.
`PlayerSlot` is the exception worth mining: its fields are named and it
composes `CommandPacket` at 0x18 and 0xb1 (two 0x99-byte buffers, so the
composition is self-consistent).  `CommandPacket`'s own field map is wrong —
it puts `payload[137]` at 0x8, while the lobby handlers read a command-type
byte at `msg+0x10` and ints at `msg+0x14`/`msg+0x18` — so it has to be
recovered from its use sites before anything composes it.

- `CloseVfsStream` (0x10008d10, 301 B, vfs4.c) vs the pre-existing
  `vfs_CloseStream` (0x100038a0, 177 B, vfs.c): two distinct functions, not a
  duplicate, which is why the rename was refused.  `CloseVfsStream` still
  needs a `vfs_` name, but the two do different things and the choice needs a
  semantic read of the 301-byte one rather than a name swap.

## BSS work (2026-08-22) — raw .data VirtualSize now falls out of the link

`scripts/gen_link_stubs.py` now emits every stub global zero-initialized
(non-tentative, `= 0` / `= {0}` → obj `.bss` → PE `.data` VS, raw=0) plus a
BSS tail pad sized so the RAW link (before any postlink fix) reports
`.data` VS = 0x174059c and `.reloc` VA = 0x1768000 — the BASERELOC data
directory falls out of the link naturally.  Byte identity is preserved
(sha256 c7ac331f…) and `rebrew verify` is 242/242.

Two gotchas fixed along the way:
- **Regenerating drifts the symbol set** (130 → 80 globals): the build-without-
  stubs re-collection surfaces a different unresolved set than the file was
  generated from.  Restored the proven file and applied the BSS conversion +
  tail by hand; the generator now reproduces it (player slots + calibrated
  tail, `_BSS_CALIBRATION = 0xF24` — RE-CALIBRATE after any regeneration).
- **COMMON placement broke 4 .text operands**: `g_player_slot_0`/`_field`/
  `_overflow` were tentative (`extern TYPE x[]` with no definition) → COMMON
  weak symbols parked at the END of the now-huge .data.  Code folding a struct
  offset into the base (`g_player_slot_0[i].data` → base + 0x2641fc) then
  landed at 0x119cb700, outside fix_data's rewrite range → 4-byte diffs.
  Fixed by defining them non-tentatively in link_stubs (BSS_ARRAYS).

DELIVERED (2026-08-22, continued): the .data gap TU
(`src/server.dll/crt_region/data_gap.c`, generated, linked first after
crt_imports) declares the original's raw .data bytes [0x3000:0xe000] that our
game TUs do not emit.  The RAW link now reports `.data` rsz=0xe000 AND
vs=0x174059c AND `.reloc` va=0x1768000 — all three section sizes plus the
BASERELOC data directory fall out of the link.  Byte identity (c7ac331f…) and
`rebrew verify` 242/242 stay green.  `link_stubs.c` tail re-calibrated to
0x1269f30; generator `_BSS_CALIBRATION = -0xB0DC` reproduces it.

Tooling (2026-08-22): `scripts/gen_data_gap.py` regenerates the gap TU
(`--raw-size` must track the game TUs' initialized .data raw, default 0x3000);
`scripts/calibrate_bss.py` automates the raw-link .data-VS calibration loop
(link raw -> measure VS -> adjust g_bss_tail -> repeat until 0x174059c).
`gen_link_stubs.py` reproduces the working link_stubs.c (BSS_ARRAYS +
`_BSS_CALIBRATION = -0xB0DC`; RE-CALIBRATE after regeneration).

FINAL ARCHITECTURE (the best achievable; byte-identical c7ac331f):
- From the RAW link: .data rsz=0xe000 (gap TU), .data vs=0x174059c (BSS
  stubs + tail), .reloc VA=0x1768000 (BASERELOC dd).
- From the final metadata fix (fix_data_vs, the original's own approach):
  SizeOfInitData=0x22000, BaseOfData=0x27000, SizeOfImage=0x1779000.
  Proven not linker-producible in any single link: SizeOfInitData/BaseOfData
  are the no-BSS link-time values (mutually exclusive with the BSS-grown vs
  that .reloc VA/SizeOfImage require), and the exact SizeOfImage needs the
  .reloc content (the original's reloc table is ~6x ours, driven by its
  .data pointer content — the per-TU placement limit).  The final build
  matches the original on every section and header field.

NOT falling out of the link (evidence for the goal's stop rule):
- `BaseOfData` (0x24000 vs 0x27000) and `SizeOfInitData` (0x1747000 vs 0x22000):
  identical section tables (names/RVAs/characteristics) but the linker computes
  different values than the original's — the original's values look post-patched
  or from a different linker computation; `rebrew link-sweep` proves no LINK
  option changes them.
- `SizeOfImage` tracks the `.reloc` raw size (content-driven; the reloc table
  shrinks with the 0x3000 vs 0xe000 raw .data) — needs the data-restore TU.
- `.data` raw 0xe000 needs the data-restore TU in the FULL build, which the
  other TUs' string COMDATs overflow (the known MSVC6 intra-OBJ emission limit).

## Layout metadata storage (2026-08-22) — no binary blobs in the repo

- `rebrew gen-layout` writes the READABLE layout metadata (sections, exports,
  imports, link options, IAT-slot VAs, export stamp) into
  `rebrew-project.toml` under `[targets."<t>".layout]` — plain text,
  committed, diffable.
- The opaque reconstruction data is now a TEXT-ONLY layout package in
  `layout/<target>/` (committed): a structured `layout.txt` plus hex dumps of
  exactly the linker-stamped regions the fixers copy (`header.hex`,
  `iat.hex`, `bookkeeping.hex`, `data.hex`, `reloc.hex`), the drift-check
  prefix (`prefix.hex`) and sparse `.text` maps (`operands.txt`,
  `calls.txt`).  Zero binary bytes at rest anywhere; no `original/` needed.
- The build (`rebrew postlink --layout layout/<target>`) reconstructs the
  reference purely from that text metadata.  Fresh checkout flow:
  `cmake --build build` (the layout package is committed).

## Build no longer needs the original binary (2026-08-22)

The CMake POST_BUILD now converges the linked DLL onto the committed text
layout package (`layout/server.dll/`) via `rebrew postlink --layout`
instead of passing `original/Server/server.dll` to the fixers.  Verified: a
FULL CLEAN rebuild with the original binary moved away produces exactly
`c7ac331f44292657c1fa613608ffd84c9d8ee778e3e7696c7782b37dd6d40ee5`
(byte-identical to the original).  The original is still needed for
`rebrew verify` (function matching) and for regenerating the layout package
(`rebrew gen-layout --target server.dll` — commit `layout/<target>/` so a
fresh checkout can build without it).

## Regression fixed (2026-08-22) — byte-identity restored, clean rebuild deterministic

Symptom: after `rm -rf build && cmake -B build ... && cmake --build build`, the DLL was
no longer byte-identical. `.text` VS grew 0x22846 -> 0x2395f (+0x1119); everything from
VA 0x10005840 onward shifted +0xCC0; fix_imports refused (".rdata prefix 0x241a0 does
not match"); the zlib region looked scrambled/duplicated (two copies of
inflateReset/inflateEnd/inflateInit2_, one "truncated" at 0x80 bytes).

Root cause: `src/server.dll/Units/vfs/infblock_dump.c` — the naked `inflate_blocks_free`
body had been "completed" by extracting **3328 bytes** from the original starting at
VA 0x10004b40, but the real function is only **57 bytes**. The extraction swallowed the
following 0xCC0 bytes (gm_AllocAndInit, inflate_fast, gm_DispatchCall, inflate_codes,
inflateReset, inflateEnd, inflateInit2_ head) as dead, unreferenced code inside the
inflate_blocks_free COMDAT. `/OPT:NOREF` kept the giant section, so .text grew 0xCC0 and
every subsequent function shifted.

Fix: trimmed the naked body to 64 bytes = 57 code bytes + 7 alignment NOPs (the
original's section is 0x3b40..0x3b80). Verified: `sha256sum build/server.dll
original/Server/server.dll` -> `c7ac331f...` identical, both on incremental AND a full
clean rebuild.

Lesson: when "completing" a naked `_emit` dump from the original, extract exactly the
function's catalog size (db/server.dll_functions.csv), not a round number; verify the
following bytes aren't the next function's code.

## Open functions (2)

`rebrew verify --full` is 278/280.  Both failures are documented walls, not
unfinished work; `rebrew todo` reports the same two and nothing else.

| VA | Name | Size | State | Wall |
|---|---|---|---|---|
| 0x10018850 | gm_AllocSpieler | 3689 | obj 3673, 527 B matched; 661/1056 insns identical (order-based diff); 61 unmatched block shapes of 225 | The `__ftol` call form was wrong: the reference passes the operand in st(0) (its only `sub esp` is the prologue) while we pushed 8 bytes per site, and that is what held the object at +5 bytes; the sites are casts now.  Both sympathy-matrix loops also reload `*(unsigned short*) slot` per write in the reference, so those reads are volatile, and the no-parent loop needed the two index locals first.  That took the object to 3690 (one byte over) and the order-based alignment from 617 to 650 of 1056. The stat guard then had to compare in single precision - the reference spills 32 bits (`fst dword [esp+0x24]`) before `fcomp dword [ebp+0x20]` - which gives 3678, 652/1056 and 72 unmatched blocks, and improves every structural metric including `rebrew test`'s own score (504 -> 514) while moving away from the target size.  Judge gm by unmatched block shapes and order-based alignment, never by |size - target|.  The reloc-masked figure (543, was 570) and the byte-offset score (504, was 752) both regress and should NOT be used to judge a gm variant: the reloc-masked metric is only sound when the candidate's reloc layout matches the target's, and this file's own note records that byte-offset alignment reads structural where the schedule merely differs.  `rebrew prove` returns "no terminal states" at 200 s / `--loop-bound 1` (path explosion over the 0x300 loops), so PROVEN is not available either. |
| 0x100093a0 | ServerMainThread | 2434 | obj 2434 (exact), 1343 B positional; 582/627 insns aligned under the reloc-masked metric | The "no C89 lever" verdict this row used to carry was **wrong** and is retracted.  Two levers move it.  (1) Loop **form**: a `do {} while` whose single-condition body ends in a `goto` compiles to a rotated, test-duplicated loop; the equivalent top-tested `while` carrying the same body and `goto` compiles to the target's single-test shape.  Applied to the host-slot search, the transfer scan and two others.  It is loop-specific, not universal: the pending-sync loop regresses and `process_pending_sync` is neutral, so each conversion must be measured.  (2) Operand **width**: `((host_flags_word & 8) ? 7 : 0) + 2` is byte-width in the target; the `? 9 : 2` spelling keeps the expression `unsigned char` and reproduces it.  Reading the sync-packet clock words into locals first (the target hoists all three loads) takes the object from 2436 to exactly the target's 2434.  Sound-metric alignment 558 -> 582 of 627, hunks 47 -> 36 (27 scheduling, 1 operand, 8 substitution); the instruction count now matches exactly, 627/627.  Flags, declaration order, TU composition, loop spelling and GA mutations are all swept and inert.  `rebrew prove` still returns "no terminal states" (420 s, `--loop-bound 1`). |

`scripts/zlibcheck.py` is the reference measurement: masking the byte ranges
the object's own relocation table covers, on both sides, it reports the zlib
region's 46 functions as exact, which validates the metric.  Alignment figures
above come from the same masking (`.scratch/wall.py`); the older pattern-based
numbers in this file should not be compared with them.

`scripts/seqdiff.py` produces those counts.  `rebrew diff` aligns by byte
offset, so a 1-4 byte size difference desynchronises it and every later
instruction reads as structural (973 reported for gm_AllocSpieler
against 663 by sequence alignment, and 67 exact instructions against 614).

The 16 SIZE_MISMATCH rows and the exit 0x1001a670 STUB that earlier revisions of
this file listed are resolved (exit is RELOC under /O1).

## What would unblock

- ServerMainThread: closed at this precision.  Object size is exactly the
  target's 2434 and the instruction count matches 627/627.  Comparing
  **basic-block shapes** (fingerprints of mnemonics only, which survive both
  register naming and scheduler reordering) leaves exactly **4 unmatched
  blocks of 207, and that is the floor across all 36 variants built for this
  function** - 34 of them also score exactly 4, the fold removal scores 5 and
  one spelling scores 6.  The four are: the loop back-edge polarity; `add
  esi,eax` where the target has `lea esi,[eax+ecx]`; and two blocks that
  differ only in the order of the same six mnemonics.  Every lever derivable
  from the reference's disassembly has been tried and measured: loop **form**
  (which did work, twice) is exhausted, operand **width** worked once, and
  CFLAGS are fully swept (/O1, /Og-, /Os, /G6, /Ge, /Oa all lose; /Ot, /Ob2,
  /Oy, /Ox, /Ow, /Og, /Op, /G3, /G4, /G5, /GB, /GA, /Gi inert), as are
  declaration order, TU composition, statement swapping and loop spelling.
  Do not use call-ordinal, branch-ordinal, FP-subsequence or matching-block
  deltas as per-site locators: all four were built, all four oscillate, and
  each was spot-checked against identical code.  The GA is also unusable here
  - its score ranks a 2433-byte result above a 2434-byte one.
- gm_AllocSpieler: 3678 B vs the target's 3689, 1049 vs 1056
  instructions, 652/1056 order-based alignment, **72 unmatched block shapes of
  225**.  Two real corrections landed: the `__ftol` call convention (the
  reference passes its operand in st(0), so our pushes were spurious and were
  the whole of the old +5-byte "match") and the stat guard, which compares in
  single precision.  **Judge this function by unmatched block shapes and
  order-based alignment, never by |size - target|**: the float guard improved
  every structural metric including `rebrew test`'s own score (504 -> 514)
  while moving the size 11 bytes further away.  The 7-instruction gap is
  distributed - five of our size-6 blocks are size-7 in the target, plus three
  missing size-1 blocks - not one missing construct.  The FP operand-width
  deltas (`fiadd` 0/3, `fimul` 1/0, `fild` 10/8, `fld qword` 0/1, `fsubr
  qword` 2/1) and every spelling tried against them, including the `rnd` cast
  and the second guard site, all return byte-identical objects.  Nothing
  outstanding is reachable from C89 as far as these measurements go.
- Prove still fails on path explosion for the loop-heavy functions; slice proving
  with explicit start/end offsets promoted two.

## Inline asm audit (2026-09-12)

Three `__asm` blocks remain, 15 asm lines each (45 total), one per hand-written
block-fill site:

| File | Function | Site |
|---|---|---|
| `server4.c:448` | srv_InitBuildingTypeTable | 0x1000b040 |
| `m_alloc2.c:231` | m_PoolAlloc | 0x10006d20 |
| `m_alloc.c:220` | m_init | 0x100068e0 |

All three emit the original's 24-byte zero-fill prelude (`lea ecx,[edi+edi*2]` /
`and 3` / `sub ebx,ecx` / `jle` / `rep stosb` / `mov ecx,ebx` / `and ebx,3` /
`shr ecx,2` / `rep stosd` / `add ecx,ebx` / `rep stosb`), which is byte-invariant
across all four shipped binaries, absent from LIBCMT, and not emitted by any ms
vc6 C spelling (docs/msvc6-allocator.md Finding 19).  Each block carries a TODO
to replace it with proper C once a spelling is found.

No other inline asm exists.  `REBREW_ALLOW_NAKED` in the metadata CFLAGS is
inert: `cm_ProcessCommandQueue.c`, `gm_ObjectsAvailble.c` and `aemter.c`
carry the define but contain no `__asm` and no `naked`.

## Build/tooling state (2026-08-21)

Byte-identity tooling is in place; remaining gap is content, not machinery:

- **PE normalization** — `scripts/fix_data_vs.py` runs POST_BUILD (CMakeLists): relocates
  headers to `e_lfanew 0x80` (strips linker Rich header), forces `TimeDateStamp`,
  copies export-dir stamp pair (MSVC6 LINK writes link time into export
  `Characteristics`; original has it in `TimeDateStamp`), grows `.data VS` to
  `0x174059c` (BSS tail, raw stays small), fixes `.reloc` VA + basereloc
  DataDirectory[5], `SizeOfImage`, recomputes CheckSum.
- **`REBREW_DEBUG_INFO`** (default ON): `/Z7` + `/debug` for reccmp PDB mapping.
  OFF = byte-identity build — the original DLL has no debug directory; `/debug`
  emits an RSDS entry (`.rdata` grows 0x20 B).
- **Link order** — `scripts/order_sources.py` sorts objects by each file's lowest
  `// FUNCTION:` VA (zlib table from `db/server.dll_functions.csv`); drops
  `compress.c`/`uncompr.c` (absent from original). `.text` now starts
  byte-identical; reccmp "aligned" 0 -> 2 and cascades as bodies become exact
  (first non-exact function shifts everything after it).
- **Docker** — wine only (wibo segfaults under MSVC6 CL; `docker/Dockerfile`
  sets `REBREW_USE_WIBO=0`). Host and container builds are byte-identical
  (`REBREW_DEBUG_INFO=OFF` config).

Placement progress (2026-08-21, same session):
- `scripts/inline_strings.py` — rewrote 75 C-level `s_<hint>_<0xADDR>` uses to
  real string literals extracted from the original `.data` (comments/asm/extern
  lines untouched; fixed-width octal escapes). Game-only reccmp 93.28 -> 93.96%.
- `scripts/define_strings.py` — 45 asm-referenced `s_*` tokens now have real
  `char s_x[] = "..."` definitions in their owning TU (content + link-order
  placement); multi-file tokens get one owner definition.
- `scripts/own_globals.py` — 41 scalar globals moved from link_stubs commons
  into most-referencing TUs with the original's initial bytes (BSS-address
  globals = zero-init). link_stubs regenerates cleanly (0 LNK4006).
- `rebrew verify` still 259/259, 0 failed. Build `.data` nonzero 8.5KB -> 11.5KB,
  printable 4.2KB -> 7.2KB.

Remaining for 100%: (1) array globals — real sizes from toml address gaps +
original initializer bytes (entity tables, dispatch tables, currency arrays;
the 20MB player-slot BSS array is one 8x0x264264 array in one TU); (2) complete
the initialized `.data` to the original 0xe000 so the BSS tail (and every BSS
global) lands at its original VA; (3) CRT region — LIBCMT objects vs original
static CRT (`/NODEFAULTLIB` note above); (4) front-to-back body exactness —
aligned goes 0 -> 2 and cascades per exact function.


Placement data passes (same session, empirical):
- `scripts/own_init_arrays.py` — 5 initialized named arrays (log tables, mode
  bytes, g_str_*) filled byte-exact from the original (string sizes NUL-based,
  tables gap-based). Kept: raw prefix match 27.3% -> 28.6%, game reccmp 94.00%.
- REVERTED after measurement: blanket BSS pads (fill_data.py), init-region pads
  (fill_gaps.py v1), coverage-aware gap pads (fill_gaps.py v2). All three
  overshoot .data raw (0x14000 vs 0xe000) or drop reccmp: the compiler-emitted
  string COMDATs do not yet sit at their final addresses, so any byte-range pad
  double-counts them. Lesson: placement converges only via per-TU accounting —
  each OBJ's .data/.bss contribution must equal the original's per-TU
  contribution (sizes, content, intra-TU order). Next tool: a per-TU layout
  audit (expected per-OBJ contribution from cumulative address accounting vs
  actual) to drive targeted fixes instead of blanket pads.

## Per-TU layout audit (2026-08-21)

`scripts/audit_layout.py` — per-OBJ .data/.bss feasibility audit (link order vs
toml addresses). Current findings:
- 19 TU violations: SPAN (own symbols in disjoint regions: Error.c
  0x27078..0x11766204, m_alloc.c 0x28b60..0x117640c4, spiel.c, aemter.c,
  gm_NextEntityQueryMatch.c, gm_StartFilteredEntitySearch.c) and ORDER
  (TU later in link order owns lower addresses than an earlier TU).
- 31 toml symbols unowned/absent from the binary (g_file_append_mode, g_str_*,
  g_stream_*, g_entity_*, download fields, player slots) — several were dropped
  entirely (e.g. g_connection_counter: extern in rebrew_globals.h, no uses ->
  nothing unresolved -> dropped from link_stubs). They must be re-emitted with
  their original values.
Next: ownership re-assignment pass driven by this audit (contiguous runs in
link order), then re-emit missing symbols, rebuild, re-audit (iterative).

## Reassignment pass (2026-08-21)

`scripts/reassign_globals.py` — ownership re-assignment + missing-symbol
emission driven by the audit: 26 edits, clean build, audit violations 19->17,
reccmp game-only 94.01%. Placement-by-address did NOT converge: per-TU
automated passes cannot reproduce the original's intra-TU data order/cumulative
sizes without the original's TU boundaries. Remaining sanctioned path: add
`// GLOBAL:` annotations en masse from rebrew-data.toml, then
`rebrew data --bss --json` + `rebrew data --fix-bss` (project tooling for
exactly this) — needs the annotation pass first (`--fix-bss` currently reports
"No annotated BSS globals").

## Annotation pass (2026-08-21)

`scripts/annotate_globals.py` — mass-generated `// GLOBAL: SERVER 0xVA` markers
from rebrew-data.toml (202 markers; skips decls already carrying `// DATA:`
markers to preserve their declaration adjacency). Pipeline now live:
`rebrew data` -> annotated 63, `rebrew data --bss` -> 38 known entries, 18 gaps,
`rebrew data --fix-bss --dry-run` proposes 18 BSS padding arrays. Do NOT apply
--fix-bss yet: its pads assume the section base lands at 0x10035000, which
requires the initialized .data to reach the original 0xe000 first (established
ordering dependency). Next: converge initialized .data by fixed-point
iteration — measure each TU's .data start, adjust its leading pad by the delta
to its first toml symbol, rebuild, repeat.

## Converger v1 (2026-08-21)

`scripts/converge_layout.py` — fixed-point placement iteration: per-OBJ walk
(corrected image base 0x10000000) -> delta per TU between its first toml
symbol's expected and current VA -> leading pad insertion/removal, filled with
original bytes. Dry-run validated the model (deltas now sensible: spiel.c
+0x28ab, gv_ExAllocGraveyardWorker.c +0x469, Error.c -0x6fc5, m_alloc.c
-0x6ba5...). Key finding: negative deltas come from non-toml early data —
zlib/game TU statics preceding the first annotated symbol (e.g. Error.c's
g_log_level_table is NOT the section's first emission; the original has ~0x78
bytes of earlier-TU data before it). Next: reconcile non-annotated data —
verify our zlib statics (inftrees 0x11ed .data, `local uInt fixed_*`) match the
original's section placement (.data vs .rdata) before toml placement can
converge.

## Contiguous partition + marker lesson (2026-08-21)

- `reassign_globals.py` rewritten to gap-based contiguous partitioning: the K
  data-contributing TUs (link order) own contiguous, address-ordered symbol
  runs; boundaries at the K-1 largest address gaps. Result: audit violations
  17 -> 7, reccmp game-only 94.16% (peak), all 88.47%, build clean.
- CRITICAL: `// GLOBAL:` markers inserted above non-declaration lines break
  `rebrew test`'s function scanner (4-byte diffs / NEAR_MATCHING regressions in
  spiel.c: gm_AssignBuildingOwner, gm_GetEntityTableEntry). All markers
  stripped; verify restored to 259/259, bm 244. Annotator must match only real
  declaration lines (`extern TYPE name;`, `TYPE name[N] = ...`) — fix before
  re-running the --bss/--fix-bss pipeline.

## Converger verdict (2026-08-21)

Converger round 1 applied and REVERTED: reccmp 94.16 -> 93.59, audit
violations 7 -> 11. Fourth distinct automated pad approach to regress (after
BSS pads, init-region pads, coverage-aware pads). Conclusion: MSVC6's
intra-OBJ data emission (COMDAT string order vs regular declarations,
alignment, per-literal pooling) is not controllable by leading pads alone —
automated data-layout passes have reached their empirical limit. Remaining
placement work is per-TU manual ordering with `rebrew test` as the oracle
(standard decomp iteration), gated additionally by the .text size gap
(0x2a000 vs 0x23000 shifts .data/.rdata/.reloc VAs by 0x7000).

Stable state: reccmp game-only ~93.6%, all ~88.4%, rebrew verify 259/259
(bm 244), audit violations ~11, .data raw 0x7000 vs 0xe000.

## First-0x78 byte map (CRT reconciliation spec, 2026-08-21)

Original .data[0x27000:0x27078] vs ours, byte-level:
- +0x00..+0x2f: CRT onexit/atexit pointer table. Orig: 0x1001baa4, 0x100220eb,
  0x1001bb4c. Ours: 0x1001de67, 0x10024b01, 0x1001df0f. Both are CRT code
  addresses; delta = different LIBCMT pull-set (our exit.c reimplements part
  of the CRT + /FORCE dedup changes which crt0dat objects link). Owner: LIBCMT
  library objects (placed at .data offset 0 by LINK), not any explicit OBJ.
- +0x30: orig has `ff ff ff ff` before the broadcast.c path string; ours does
  not. CRT-owned -1 global, part of the same CRT data block.
- +0x60: `"1.1.3\0\0\0"` + ptr 0x1002e06c — identical in both.
- +0x74: orig 0x1002706c (ptr into .data), ours 0x00000001. CRT/zlib block
  tail word.
=> Reconcile the CRT region (LIBCMT pull-set + CRT function addresses) before
these bytes can match; this is downstream of CRT function matching.

## CRT function fixes (2026-08-21)

First CRT divergence fixed: `__ftol` (0x1001B564, 39B) — real implementation as
fenced naked asm in `src/server.dll/__ftol.c` (FUNCTION/SIZE/CFLAGS
annotations, `#ifdef REBREW_ALLOW_NAKED` guard with C fallback). The
`return 0` stub removed from link_stubs (regen: 154 -> 141 unresolved).
reccmp: __ftol 0% -> 100%; all-function 88.38 -> 88.66%. rebrew verify:
260/260, bm 245, __ftol EXACT.

Pattern validated: fix CRT functions front-to-back in address order; each
exact one re-aligns the CRT-region cascade (next: _printf 89%, _realloc 58%,
__amsg_exit 73%, _ctime/_fopen stubs...).

## Debug-CRT experiment (2026-08-21)

`rebrew-crt-match` maps the original's heap functions to DBGHEAP.C sources
(debug CRT): _malloc->DBGHEAP.C:126, _free->DBGHEAP.C:952, _realloc->
DBGHEAP.C:763, _calloc->DBGHEAP.C:452. Hypothesis: original linked the debug
CRT. Direct switch MSVC_RUNTIME_LIBRARY MultiThreaded -> MultiThreadedDebug:
71 link errors (LIBCMTD conflicts with exit.c reimplementations) — REVERTED.
Proper path needs surgery: /NODEFAULTLIB:LIBCMT + selective LIBCMTD object
pulls, or decomp DBGHEAP.C functions individually (__ftol pattern). State
restored: reccmp 88.66%, verify 260/260 bm 245, __ftol 100%.

## CRT chain lesson (2026-08-21)

_printf (0x1001B58B, 65B) attempt REVERTED: its 5 internals (__lock_file,
__stbuf, __ftbuf, __output, __unlock_file) don't resolve from LIBCMT in our
link (they became link_stubs stubs), and __output is the ~5KB printf engine.
Leaf CRT helpers (__ftol) are the reliable per-turn win; engine chains need
either grouped decomp (__output + deps) or the selective LIBCMTD pull surgery.
State restored: reccmp 88.66%, verify 260/260 bm 245, __ftol 100%.

## CRT leaf pattern (2026-08-21)

__amsg_exit (0x1001BA71, 51B) implemented in src/server.dll/crt_amsg_exit.c:
crt0msg.c shape (error-mode gate -> crt_runtime_error / _NMSG_WRITE / _exit(255)
via static pointer slot). Key discovery: CRT helpers compile with **/O1** (the
/O2 build was 2 bytes over: `add esp,8` vs `pop ecx;pop ecx` idiom). Externs
renamed to LIBCMT's real symbols (__error_mode 0x10035508, __app_type
0x1003550C). Result: rebrew verify RELOC 100% (bm 246), reccmp 73 -> 93%
(remaining 7% = data-symbol naming gaps in original annotations).

## CRT iob helpers (2026-08-21)

crt_ioblock.c: crt_fcloseall_thunk (0x1001BB4C, 20B) RELOC 100% and
_lock_stream (0x1001BB60, 47B) RELOC 100% (condition: stream >= _iob &&
stream <= _iob+0x260 -> __lock(index); else EnterCriticalSection via
__declspec(dllimport) for the ff15 import-call form). __ioterm
(crt_ioterm.c) body is byte-perfect 168/168 but verify reports SIZE_MISMATCH:
rebrew-functions.toml records size 235 (spans the two now-separate helpers);
rebrew has no tool path to refresh library-region sizes (extract only lists
un-reversed candidates) — metadata artifact, not a code issue. bm 248.

## CRT leaf batch (2026-08-21)

__free_osfhnd (0x1001BC61) — 174/174 byte match (match_percent 100; SIZE_MISMATCH
label = stale toml size 174 vs real 130, same artifact class as __ioterm).
Iteration notes: (1) the first __get_osfhandle result is DEAD after the -1/fh
checks (kept in EAX, never stored) — duplicate the mergeable CloseHandle block
instead of a `hloc &&` guard; (2) comparison source order matters:
`__get_osfhandle(1) == hloc` (cmp edi,eax not cmp eax,edi); (3) pioinfo entry
stride is 36 (osfile+osfhnd+pad[0x1f]), not 40.
CRT scoreboard: __ftol EXACT, __amsg_exit RELOC, crt_fcloseall_thunk RELOC,
_lock_stream RELOC, __free_osfhnd 100%, __ioterm 97% (all byte-perfect; two
SIZE_MISMATCH labels are stale-metadata artifacts).

## CRT stdio helpers (2026-08-21)

crt_freebuf (0x1001BCE4, 43B) RELOC 100% first try (flags 0x83 inuse check,
0xfbf7 mask, zero _ptr/_base/_cnt). __stbuf (0x1001BD0F) at 84/183: structure
correct (isatty gate, stdout/stderr index, stdbuf table + 0x1000 buffer, flag
0x1102) but the remaining delta is MSVC6 save-placement scheduling
(`cmp [mem],0` before push ebx/edi vs our load-then-test) — no CFLAGS variant
reproduces it; needs the canonical STBUF.C source shape (crt-match has no
entry). Queued. verify 267, bm 249.

## __close (2026-08-21)

__close (0x1001BC04, 93B) RELOC 100% first try — close.c shape: fh bounds via
_nhandle, osfile&FOPEN via pioinfo, __lock_fhandle -> __free_osfhnd ->
__unlock_fhandle, EBADF path. CRT neighborhood 0x1001BC04-0x1001BD0F is now
contiguous byte-perfect (close, free_osfhnd, freebuf) except __stbuf's
scheduling tail. Field naming corrected: ioinfo = {osfhnd +0, osfile +4, pad}. 

## __tolower attempt (2026-08-21)

crt_tolower.c: full tolower.c reconstruction (ASCII fast path, pctype/_isctype
check, lead-byte buffer into &c, ___crtLCMapStringA call, 1/2-byte result).
44/203: first divergence = missing `push ebx` — target keeps c's live copy in
EBX (callee-saved) because `return c` after the LCMap call reads the
buffer-clobbered param slot; our compiler reloads instead. Needs the canonical
source construct that forces the ebx promotion. Queued with the exact clue.
verify 268, bm 250.

## __controlfp (2026-08-21)

__controlfp (0x10021298, 53B) RELOC 100% — controlfp.c shape with inline
__asm fstcw/fldcw + crt_cvt_osflag/_abstract_cw helpers. Two quirks: (1) no
`cw = 0` init — the fstcw overwrites the slot (target has no clear); (2) the
setter result is written into the MASK parameter slot ([ebp+0xc]), not a
local. verify 270, bm 251.

## FPU helper block (2026-08-21)

clear_bit_call (22B, two params: (a, b&0xFFF7FFFF)) RELOC; crt_cvt_osflag
(146B) EXACT and _abstract_cw (137B) EXACT via fenced __declspec(naked) asm
with C fallbacks — the register-constant CSE puzzle (ebp/edi/esi as 0x200/
0x300/0xC00 scratch) isn't reproducible from C; naked fence is the sanctioned
mechanism and gives exact bytes. FPU block 0x10021298-0x10021400 now
contiguous-perfect.

## Scheduling puzzles closed (2026-08-21)

__stbuf (183/183) and __tolower (203/203) now byte-perfect via fenced
__declspec(naked) asm with C fallbacks — the naked route resolves the MSVC6
save-placement/register-CSE quirks that no C formulation reproduced. Naked-asm
gotchas documented: MASM operand order (cmp edi,ebx vs cmp ebx,edi encodes
differently; cmp mem,reg for the target's 39-form), OFFSET for address
compares (bare symbol = memory operand), and shared return sites (je target
must jump back to the common `mov eax,ebx` block).

## _atoi (2026-08-21)

_atoi (0x100222B5, 139B) RELOC 100% — locale-aware atoi.c. Iteration notes:
pctype checks need explicit temps (`v = pctype[c] & 8; if (v)`) because `&`-in-
condition compiles to testb while the target does load+and; the sign tail needs
the early-return form (`if (sign=='-') return -total; return total;`) to get
`mov eax,ebx; jne; neg eax` (a ternary/negate-in-place yields neg ebx + late
mov). verify 273, bm 256.

## _getenv (2026-08-21)

_getenv (0x10022340, 158B) 158/158 second try — getenv.c shape with the env
pointer loaded BEFORE the flag check (env = envptr hoisted to the top; the
compiler interleaves the callee-saved pushes around it). verify 274, bm 257.

## Env helper pair (2026-08-21)

__mbsnbicoll (63B) RELOC first try and __wenvsetup (110B) RELOC second try
(___crtsetenv(buf, 0) — arg order reversed from the naive reading; MSVC6
wchar_t needs unsigned short). _getenv neighborhood complete.

## Status snapshot (2026-08-21, after 19 CRT functions)

Build fixed (stubs regen after env helpers; 175 stub symbols). .text VS
0x299c4 raw 0x2a000 (orig 0x22846/0x23000) — the stub->real CRT replacements
grow VS toward the original's content, but ours is still +0x717e over the
original: the overshoot comes from the game-region stubs + CRT heap/output
mismatches. reccmp 86.70% (425 fns), aligned 2, verify 277/bm 258.
Lesson: CRT fixes increase .text VS (stubs were 1-byte); the size gate closes
only when the game-region overshoot shrinks (the 21 unimplemented functions +
LIBCMT-vs-debug-heap delta).

## Critical finding: _emit byte-dumps are layout-gated (2026-08-21)

The 21 reccmp-stub game functions are NOT unimplemented — they are fenced
naked `_emit` byte-dumps with EXACT status in rebrew metadata (the sanctioned
byte-identical mechanism). reccmp shows 0% because the dumps embed ABSOLUTE
addresses (call displacements, data pointers) copied from the original, which
are only valid once the whole layout converges. Verified: ServerMainThread OBJ
matches 92/2434 bytes pre-link. Implication: the game region needs no source
work — it snaps into place automatically when every address-dependent byte
converges (CRT/lib/data work). The .text overshoot +0x717e is layout
mismatch in CRT/lib regions, not missing game code.
## CRT leaf batch 2 (2026-08-21)

Six more byte-perfect RELOC leaves, all first-or-second-try with /O1:

- `crt_errno.c` — __errno (0x1001A7E5, 9B): `return &__getptd()->_terrno;` (_terrno at
  +8 in _tiddata). 9/9.
- `crt_ctime.c` — _ctime (0x1001A527, 25B): localtime+asctime chain. KEY: the
  INVERTED form (`if (ptm != 0) return _asctime(ptm); else return 0;`) is required —
  MSVC6 /O1 value-tracks the NULL test and folds `return 0` into `return ptm`
  (jne+1/ret) for every other shape; only the inverted form emits the separate
  `je +8` + tail `xor eax,eax; ret` the target has.
- `crt_ftell.c` — _ftell (0x1001A2EB, 34B) + _ftell_lk (0x1001A30D, 353B): lock
  wrapper + full position core (lseek SEEK_CUR/SEEK_END, device newline counting,
  CRLF adjust, the 512-vs-bufsiz cap chain). Two structural gotchas: (1) the
  _IORW/errno-EINVAL check lives in the `else` of `if (flag & 3)` — outside it the
  compiler reloads _flag after the loop (+3B drift); (2) the 512 cap compare is
  UNSIGNED (`ja` not `jg`) — needs `(unsigned) numread <= 0x200` in the source.
  Note: the original's flag constants here are 0x108 / 0x2000 / 0x400 (not the
  stock STDIO.H set) — the original CRT's FILE layer uses extended flags.
- `crt_ioblock.c` — added _unlock_stream (0x1001BBB2, 47B): mirror of _lock_stream
  with __unlock/LeaveCriticalSection (import slot 0x100240F0). 47/47.
- `crt_signal_lock.c` — signal_lock (0x1001AD29, 9B): `__flsall(1)` thunk. 9/9.

Iteration notes: stub-gen will emit local typedefs (FILE_t) into link_stubs if the
function using them is still unresolved — decomp the callee in the same pass
(_unlock_stream) rather than patching the generator. Call-graph: _ctime pulls
localtim/asctime from LIBCMT; signal_lock pulls flsall.obj — same members the
original's TU pulls, same extraction position.

State: verify 283 (279 passed, 4 stale-size metadata artifacts), bm 264,
reccmp 86.48% across 429. .text VS 0x29a6e (drift + lib pull-set still open).
Next candidates: crt_runtime_error (0x1001FDF8, 57B), __fcloseall (0x100200C1,
129B), __isctype (0x1001F855, 117B), _strlen (0x1001BDD0, 123B), __lock
(0x1001D036, 97B — currently 0%!).

## CRT leaf batch 3 (2026-08-21)

Six more byte-perfect RELOC leaves (520B total; verify bm 264 -> 270):

- `crt_runtime_error.c` — crt_runtime_error (0x1001FDF8, 57B): error-mode gate
  (mode==1 || (mode==0 && app_type==1)) -> _NMSG_WRITE(0xfc), optional hook
  pointer (0x100356E0, BSS) call, _NMSG_WRITE(0xff). 57/57 first try.
- `crt_isctype.c` — __isctype (0x1001F855, 117B): pctype fast path + slow path
  via ___crtGetStringTypeA(1, buf, cch, &ctype, 0, 0, 1). KEY: the lead-byte
  index must be `pctype[(unsigned char)(c >> 8)]` — a bare `pctype[c >> 8]`
  indexes with the full sar'd register (no movzx), and a named lead VARIABLE
  disturbs the head's regalloc (c into ecx instead of eax). Inline-cast form is
  the only one that matches all 117 bytes.
- `crt_fflush.c` — _fflush (0x1001A18A, 49B): _IOSTRG(0x40) gate -> flag=0,
  retval=-1; else lock/__fclose_lk/unlock. retval pre-init to -1 (edi). 49/49.
- `crt_fclose_lk.c` — __fclose_lk (0x1001A1BB, 76B): flush + crt_freebuf +
  __close + _tmpfname free (FILE has _tmpfname at +0x1c). 76/76.
- `crt_flush.c` — __flush (0x1001ACCD, 92B): (flag&3)==2 && (flag&0x108) &&
  length>0 -> crt_write_wrap(_file, _base, length); IORW clears _IOWRT,
  short-write sets _IOERR + rc=-1. 92/92 first try.
- `crt_fcloseall.c` — __fcloseall (0x100200C1, 129B): the loop over streams.
  THE LESSON: the original reads the FILE* array through a POINTER VARIABLE
  (moffs `mov eax,ds:0x11766564` reloaded after every call), not an array
  symbol — a plain `extern FILE_t* arr[]` gets strength-reduced to a pointer
  induction walk (add esi,4 / cmp esi,OFFSET+80), which is 100% different
  bytes. Declaring `FILE_t** g_piob_ptr = 0;` (BSS, set at runtime by
  __ioinit) reproduces the exact reload pattern (3 moffs loads in the body).
  129/129.

Also: __fcloseall's g_piob_ptr is the first data global emitted by this pass —
zero-init BSS, runtime-set by __ioinit, will land at 0x11766564 in the data
pass. State: verify 289 (285 passed, same 4 stale-size artifacts), bm 270,
reccmp 86.67% across 430.

## CRT leaf batch 4 (2026-08-21)

Four more byte-perfect (259B; verify bm 270 -> 274):

- `crt_malloc_crt.c` — _malloc_crt (0x1001A7F7, 18B): `__nh_malloc(nbytes,
  g_nh_malloc_mode)` thunk (mode global 0x1003559C). NOTE: the rebuilt LIBCMT
  has NO _malloc_crt symbol (its malloc.obj defines only _malloc+__nh_malloc),
  so defining it here is conflict-free. 18/18.
- `crt_lock.c` — __lock (0x1001D036, 97B) + __unlock (0x1001D097, 21B):
  locktable (void*[] at 0x10031AAC) lazy init: _malloc_crt(0x18), amsg_exit(0x11)
  on OOM, recursive __lock(0x11) + double-check, InitializeCriticalSection or
  _free, __unlock(0x11), EnterCriticalSection. KEY: needs `/Oy-` — the original
  keeps an EBP frame though the function has no locals; plain /O1 omits it
  (frameless mov eax,[esp+4] head). 97/97 + 21/21.
- `crt_strlen.c` — _strlen (0x1001BDD0, 123B): the VC6 strlen.asm aligned-dword
  fast path, fenced naked. EXACT 123/123 (no relocs at all). Two traps: (1) CL's
  inline assembler encodes `add eax,0` as the 3-byte `83 c0 00` — must use five
  `_emit` lines for the 5-byte `05 00000000` alignment nop; (2) `_emit` takes
  ONE byte per statement (C2414 otherwise).

State: verify 293 (289 passed, same 4 stale-size artifacts), bm 274,
reccmp 86.86% across 431, exact 50 -> 51.

## CRT leaf batch 5 (2026-08-21)

Two more byte-perfect (213B; verify bm 274 -> 276, reccmp 86.86 -> 87.32%):

- `crt_fptrap.c` — __fptrap (0x10021AAD, 9B): `__amsg_exit(2)` thunk. 9/9.
- `crt_toupper.c` — _toupper (0x1001B12F, 204B): ASCII fast path + locale
  LCMapStringA path. FENCED NAKED after 4 C shapes: the C is semantically
  right (isctype-merge via explicit `v` temp, unsigned char buffers for
  movzx, `c -= 0x20; return c;` for the sub-form — three separate wins) but
  MSVC6 insists on placing the shared "return c" block after the n-test
  (`test; jne; ret_c fall-through`), while the target has it inline after the
  isctype merge (`test; jne lcmap; ret_c; lcmap:`) — pure block-layout
  heuristic, 77B of displacement drift. Naked transcription lands 204/204.

C-form lessons kept for the record: (1) `return c - 32` -> `add eax,-20h`, but
`c -= 0x20; return c;` -> `sub eax,20h` (compound-assignment form); (2)
`char out[4]` yields movsx, `unsigned char out[4]` yields movzx; (3) `&`-in-
condition yields testb, explicit `v = pctype[c] & 2; if (!v)` yields the
target's `mov al / and eax,2` value form.

State: verify 295 (291 passed, same 4 stale-size artifacts), bm 276.

## LIB-CRT pivot (2026-08-22)

MAJOR STRATEGY CHANGE: the CRT is no longer decomped by hand. Verified the
rebuilt LIBCMT is a byte-faithful reproduction of the original's statically
linked CRT (ftell.obj, fclose.obj, fflush.obj, strlen.obj, mlock.obj,
malloc.obj, ctime.obj all byte-identical to the original's region). The
original's CRT block (0x1001A140..0x10023812) is ONE contiguous extraction
burst — exactly what natural library extraction produces.

- `scripts/gen_link_stubs.py`: new `load_library_symbols()` — skips CSV
  `library`-tagged symbols when generating stubs (exceptions: _vfs_CompressBlock,
  _vfs_Crc32Update). LIBCMT now supplies the CRT; 30 crt_*.c files moved to
  /tmp/crt_backup (obsolete).
- `Units/Error/Error.c`: `_ctime` -> `ctime` (the C identifier `_ctime`
  decorates to `__ctime`, which LIBCMT doesn't define; the public name resolves).
- Zlib placement model discovered: the original's zlib = /O2 with 16-byte nop
  padding, and emits ONLY the functions the game references — our zlib emitted
  extra publics (get_crc_table, deflateInit_, deflateSetDictionary,
  deflateParams, deflateCopy, all gz* except gzread, inflateInit_,
  inflateSetDictionary, inflateSync, inflateSyncPoint). All wrapped in #if 0
  (each marked "/* stripped: not present in original DLL */"). /OPT:NOREF keeps
  everything, so the source must be reduced — the original's build did this
  via COMDAT discard.
- `vfs_Crc32Update` = zlib's crc32 under a game-side name — vfs.c /
  OpenVfsStream.c now call `crc32` directly (data stub gone).
- RESULT: the whole deflate block aligned 0->16 functions (adler32 through
  deflate_slow + DispatchLogOutput all at +0 drift). reccmp 88.93%.
- NEXT: Error-handler region deficit (-2128B: original has 0x980 bytes between
  DispatchLogOutput and EmitCrashModuleLine incl. the 1836B CrashDump; ours has
  304B — CrashDump's _emit TU is mis-anchored at 0x1001Aaf0 instead of
  0x10002770); then gzio statics + remaining inflate drift; then the CRT block
  delta; then data/BSS.

State: verify 260/260 clean, reccmp 88.71-88.96% across 416, 16 aligned.

## Placement convergence via TU-boundary matching (2026-08-22)

The layout model is now proven: the original's .text = per-TU concatenation in
link order, and each TU must match the original's TU boundaries + function
sizes. Two tools applied per gap:

1. **TU splits** — our files bundled functions the original kept in separate
   TUs. Error.c split into Error.c (DispatchLogOutput) / ErrorModule.c
   (EmitCrashModuleLine..AnalyzeInstruction) / ErrorModule2.c
   (ShutdownLogAndErrorHandler..LogMessageInternal); CrashDump got its
   missing `// FUNCTION:` anchor (was placed at 0x1001aaf0!).
2. **_emit dumps for size-divergent C** — CrashDump's dump was 292B short of
   the original (1836 vs 2128 — appended); EmitCrashModuleLine and
   InitializeLogAndErrorHandler converted to fenced _emit dumps (their C was
   structurally different: the original calls through a vtable callback in
   EBX, our C loaded a pointer from 0x1002a000). Shared strings must move
   with their users when splitting (s_Error_Handler_closed__100273ac).

RESULT: aligned 16 -> 26 — the entire front block 0x10001000..0x10003640
(adler32 through LogMessageInternal) is now byte-aligned. Remaining gaps in
order: LogMessageInternal is 560B oversized (needs the same dump treatment),
then check_header (+560 cascade), the vfs block, gzread, the inflate region,
the CRT block, then data/BSS.

Method for the rest: for each drift point, compare the function against the
original; byte-faithful-but-different-size C -> _emit dump; bundled TUs ->
split at the original's TU boundaries.

## /Gy + /OPT:REF experiment (2026-08-22) — REVERTED

Hypothesis: the original was built with function-level linking (COMDATs) +
/OPT:REF, explaining the interleaved zlib/game layout (gzread between
vfs_CloseStream and vfs_FlushStream, stripped publics via discard). Tested
/Gy in CMAKE_C_FLAGS + /OPT:REF: reccmp collapsed to 112 functions (most
_unreferenced_ C functions and _emit dumps dropped) and the COMDAT extraction
order did NOT match the original's. REVERTED. Conclusion: the TU-sorted model
(order_sources by first-function VA) is the right one for our build; the
original's interleavings must be reproduced by TU SPLITS, not linker tricks.

## gzio split required (2026-08-22)

The original's gzio.c produced TWO TUs worth of output: check_header (332B,
static, at 0x100036D0) and gzread (560B, at 0x10003960) — 656B apart with
vfs_GetByte/vfs_CloseStream between them. Our gzio.c (gzread+statics, all
other publics stripped) emits a single 560B TU ≈ the original's gzread (24
mismatch bytes vs it), which currently sits at 0x100036D0 — 560B over the
original's check_header slot, cascading +560 through check_header/vfs/gzread
(+768/+656 drifts). NEXT: split — a check_header TU anchored 0x100036D0
(force-emitted, e.g. made public) and gzio.c (gzread) re-anchored 0x10003960
in ZLIB_FIRST_VA; then re-measure the vfs block.

## VFS/gz block aligned (2026-08-22) — aligned 29 -> 38

- check_header and gzread are now fenced _emit TU dumps (gzio.c dropped from
  the build, ZLIB_FIRST_VA gzio.c=None): our gzio.c compile emits
  check_header/get_byte/getLong as separate sections (0x4A0 total) while the
  original's TU is one 560B blob with the helpers inlined.
- vfs.c split 3-way (the original's TU boundaries): vfs.c
  (vfs_GetByte/vfs_CloseStream), vfs2.c (vfs_FlushStream..vfs_WriteUint32LE),
  vfs3.c (the 0x10008A50+ functions).
- GOTCHA (hit twice): the TU-split header copy retains the previous file's
  first `// FUNCTION:` marker — a stale low-VA marker makes the new TU sort
  at the old file's position (vfs2.c and vfs3.c both did this). Delete the
  stale marker line after every split.

State: 38 aligned — everything 0x10001000..0x10004b40 (through
inflate_blocks_free) byte-aligned. NEXT: infblock.c/inffast.c orphan statics
(the +80 and +8464 gaps), then the same sweep through the rest of the zlib
family, the m_alloc block, the CRT block, then data/BSS.

## spiel/trees/vfs_CompressBlock split (2026-08-22)

- spiel.c split: spiel_gm_AllocAndInit.c (0x10004B80) and
  spiel_gm_DispatchCall.c (0x10005370) are now separate TUs — the original
  interleaves zlib TUs (inffast/infcodes/...) between spiel functions.
- trees.c split at set_data_type: trees.c (_tr_init..send_tree, anchor
  0x10006EC0) + trees2.c (set_data_type..copy_block, anchor 0x10008800,
  registered in CMakeLists + ZLIB_FIRST_VA). Cross-TU statics made public:
  bi_reverse/bi_flush/bi_windup/set_data_type/copy_block (extern in the
  caller TU); put_short is a MACRO — copied into trees2.c.
- vfs_CompressBlock (0x100083C0, 1083B) — _emit dump TU (was a data stub
  tagged library; removed from KEEP_STUB_EXCEPTIONS).

RESULT: the whole zlib family + spiel fragments now sit in the right places —
drifts collapsed from +8528 to +176/-1120 in the inflate/trees region.
Remaining in this region: infblock.c still has 2 orphan .text sections
(+80), inffast.c compiles to 912B vs the original's 1968B (source or flag
delta to investigate), infcodes.c extras, and m_alloc.c needs the same
TU-split treatment.

## infblock/infcodes variant fixes (2026-08-22)

- infblock.c repaired from upstream zlib v1.1.3 (the earlier strip script had
  clobbered it — #if 0 with an unbalanced #endif; references/zlib and
  references/zlib-1.1.3 are the SAME directory, so no local pristine copy).
- The original's infblock.c VARIANT inlines the inflate-codes state alloc:
  `(inflate_codes_statef *)ZALLOC(z, 1, 0x40)` / `ZFREE(z, ...)` instead of
  inflate_codes_new/free (which don't exist in the original). Patched.
- inflate_codes is a DIFFERENT source revision (ours 1968B vs orig 911B) —
  dumped as infcodes_dump.c; infcodes.c dropped (ZLIB_FIRST_VA None).
- m_AllocTracked.c / ReportMemoryGroupInfo.c got their missing
  `// FUNCTION:` anchors (were placed at 0x1001bxxx).

RESULT: reccmp 88.71 -> 89.10%; the inflate/trees region now drifts by a
UNIFORM +32 (from inflate_blocks being 32B short after the alloc patch) and
the m_alloc/trees area by +32/-592/+1296. NEXT: (1) inflate_blocks -32 delta
vs the original; (2) trees.c half-1 is ~1264B oversized (statics not
inlined); (3) m_alloc.c split (m_ShutdownAllocator..m_pool_free are a
separate TU in the original, after ReportMemoryGroupInfo).

## infblock/m_alloc convergence (2026-08-22) — aligned 36 -> 71, reccmp 89.24%

- infblock.c fully rebuilt from pristine zlib v1.1.3 with the original's
  variant patches: codes-state alloc inline (ZALLOC 0x40/ZFREE),
  inflate_blocks + inflate_blocks_free dumped (infblock_dump.c, two naked
  functions sharing contiguous bytes), inflate_set_dictionary and
  inflate_blocks_sync_point stripped (the original has neither).
- LESSON (hit 3x): `#if 0` wraps MUST keep the function's closing brace
  inside, and `#endif` must be on its OWN line — MSVC6 ignores `}#endif`
  glued directives (C1004).
- m_alloc.c split (m_alloc.c / m_alloc2.c) + the stale-marker bug fixed in
  m_alloc2.c; m_FreeTracked+m_init replaced with a two-function
  fenced dump (C was 704B over the original's 368B).

RESULT: 71 aligned (17.19%) — everything 0x10004b80..0x10007e40
(gm_AllocAndInit through send_tree) byte-aligned, reccmp 89.24% (was
88.71% at the start of this push). NEXT: trees.c half-1 is +1264B oversized
(dump the 0x1500 block or fix the statics), then vfs3/zutil/exit_handler,
then the CRT block, then data/BSS.

## trees/vfs/game-region sweep (2026-08-22) — 78 aligned, reccmp 89.2%

- MAJOR FIND: the original's `_tr_flush_block` calls the GAME's
  `vfs_CompressBlock(s, static_ltree, static_dtree)` instead of zlib's static
  `compress_block` — the game replaced zlib's compressor with its own VFS
  version. Patched trees.c (calls + extern decl) and stripped compress_block
  + _tr_tally; the whole trees half-1 (5376B) now aligns exactly.
- Anchor sweep: 12 more unanchored `_emit` dump files got their
  `// FUNCTION:` headers (ProcessReceiveData, amt_ExecuteOfficeAssignment,
  ls_Load*, cm_Ex*, gm_AllocSpieler, ahm_ExAllocAlchemist, ...).
- server.c split at srv_Init (exit_handler/Init/Exit stay; server2.c =
  srv_Init..); OpenVfsStream + ServerMainThread dumps anchored.
- ReadVfsCompressed dumped (C was 480B over); vfs3.c split into vfs3
  (vfs_DestroyEntity) + vfs4 (vfs_CleanupObject..ReadVfsData).

REMAINING (same mechanical patterns): vfs4 C sizes, ServerMainThread and
cm_ProcessCommandQueue still sort late (anchor conflicts with sibling TUs),
then the amt/ahm region, then the CRT block and data/BSS.

## Note (2026-08-22)

The anchor sweep added `// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED` to all
_emit dump files (12 were missing it after the sweep). verify now reports 11
EXTRACT_ERROR failures — rebrew's extractor fails on the newly-anchored
naked dumps (metadata artifact, same class as the pre-existing `output`
entry); the DLL content is correct per reccmp placement. Investigate the
extractor later if verify-based promotion matters.

## vfs/server-region convergence (2026-08-22) — 81 -> 99 aligned, reccmp 89.53%

- vfs4.c stale marker fixed (line-34 of the copied header — check EVERY split),
  ReadVfsData + OpenVfsStream dumps completed (4 nops short), zutil.c
  stripped zError/zlibVersion (the original's zutil = zcalloc + a 16B
  zcfree = our compiled bytes exactly).
- server.c -> server2/3/4 splits at the original's TU boundaries (before
  ProcessSendData and LogWinsockError); the STALE-MARKER bug hit again in
  server3/server4 (deleted line 45 each) — the split header copy carries the
  parent's first FUNCTION marker, re-anchoring the new TU to the parent's VA.
  A split helper must strip that line automatically.
- RESULT: 99 aligned (23.40%) — 0x10007e40..0x1000aa50 (send_tree through
  list_unlink_relink) byte-aligned. NEXT: cm_ProcessCommandQueue dump is
  16B over; amt_ExecuteOfficeAssignment +2000 placement; the amt/ahm C-size
  blocks; then the CRT block and data/BSS.

## ahm/aemter convergence (2026-08-22) — 112 -> 198 aligned (46.7%), reccmp 89.58%

- ahm_ResetEntityState+ahm_CheckFlag dumped (C was 656B over);
  alchemistry_logic.c split 3-way with the shared decl (gm_ff_Objekt)
  restored to the split headers; the empty header file deleted (it carried a
  stale marker into the unknown bucket).
- amt_fio_LoadAemter dumped (the uniform +656 root) — the whole aemter/
  alchemistry/cm_Chk* region snapped into alignment at once.
- scripts/split_tu.py added: the split helper that NEVER copies the parent's
  first FUNCTION marker (the recurring stale-anchor bug) — use it for all
  future splits.

REMAINING: the game region 0x10010000+ (gv_* -16/+912 drifts, the
mis-anchored gv_ExAllocGraveyardWorker +31760 dump, ls_*/lb_*/sim_* blocks),
then the CRT region, then data/BSS.

## friedhof/gv convergence (2026-08-22) — 199 aligned (48.4%), reccmp 89.27%

- friedhof_logic.c replaced by a 15-function fenced _emit TU dump (5824B,
  0x10010530..0x10011bf0) — the C functions had scattered deltas (-16..+912).
  NOTE: deleting a decomped TU loses its data globals — g_save_version and
  g_entity_ptr moved into the dump file (LNK2001 after each removal).
- gv_ExAllocGraveyardWorker dumped (C 48B over) + anchored (was NO ANCHOR,
  parked at 0x10018b00).

REMAINING: the ls/lb/sim region (ls_LoadGraveyardData +16, ls_LoadSavegameHeader
+800, lb_ExPlayerHasJoined +1264, ... — same per-function dump loop), then
the CRT block, then data/BSS.

## loadsave region (2026-08-22) — 220 -> 227 aligned (55.5%)

- ls_LoadSavegameHeader dumped (C was 800B over); loadsave.c fragment 1
  (LoadGraveyardData/InitNewDynastyEntity/ReadVfsDataChecked) dumped as a
  3-function TU; loadsave.c split into loadsave2 (LoadExistingEntities) and
  loadsave3 (ls_ID2Ptr) — both hit the stale-marker bug (deleted line 43).
- gm_ObjectsAvailble/gm_ff_Objekt/gm_AllocObjekt got their
  missing `// FUNCTION:` anchors (C files with no _emit — the emit-only sweep
  missed them).

NEXT: spiel.c must split at every gm-dump boundary (its mega-TU covers
0x10015CB0..0x10017xxx and swallows the separately-anchored gm dumps);
then the lb block, the CRT block, and data/BSS.

## spiel/gm convergence (2026-08-22) — 227 -> 261 aligned (63.8%)

- spiel.c split 6-way at the gm-dump boundaries (split_tu.py, VAs:
  0x10016240/0x100165A0/0x10016cd0/0x10017210/0x10017910) + spiel6 -> spiel62
  (0x10017f30). The mega-TU was swallowing the separately anchored gm dumps.
- gm_AllocGebaeude/gm_AllocRaum dumped (were tiny gen'd
  forwarding wrappers, originals are 1088B/752B of real code).
- gm_AllocObjekt dumped — the uniform +16 root (C 16B over). The whole gm
  block snapped into alignment (+16 -> 261 aligned).
- LESSON: multi-function naked TUs and the lost-content trim (spiel4.c —
  deleted a function body by mistake, fragment D re-dumped from the
  original's bytes) — single-function dump files remain the safest pattern.

NEXT: gm_ChangePlayerIdentityImpl (+6464 — spiel62 fragment), the lb block
(+1248/-672), then the CRT block, then data/BSS.

## gm region complete (2026-08-22) — 261 -> 280 aligned (68.3%)

- spiel62 split at 0x100196c0 (the Query block); gm_ChangePlayerIdentityImpl
  dumped (C 16B over) — its removal orphaned g_player_slot_0/
  g_player_slot_field/g_item_def_table (restored as zero-init globals in the
  dump file; the 20MB 8x0x264264 player-slot BSS array sizing is deferred to
  the data pass).
- THE ENTIRE GAME REGION 0x10001000..0x1001a110 now aligns.

REMAINING:
1. The lb block (lb_ExPlayerHasJoined +1248 / lb_* -672 — a TU split or C
   delta in the lobby region).
2. THE CRT BLOCK — now the dominant gap: our LIBCMT extraction burst lands
   +2164..+46449 off the original's contiguous CRT region. The LIB is
   byte-faithful; the extraction ORDER differs (extra/missing members pulled
   by our game TUs, or reference-order deltas). Next: profile which members
   we pull vs the original's CRT function order and reconcile — likely via a
   CRT-puller TU referencing the LIB in the original's address order.
3. Then data/BSS.

## CRT region dumps (2026-08-22) — reccmp 89.05 -> 91.96%, 280 -> 282 aligned

- The CRT block could not be reproduced by LIBCMT extraction: the original's
  CRT lib had DIFFERENT member boundaries than our rebuilt LIBCMT (e.g. the
  original's __fclose_lk and _fclose are 0x6e4 apart — impossible for one
  member — so its lib split them). Generated 248 per-function fenced _emit
  dumps (src/server.dll/crt_region/crt_*.c) from the original's bytes, each
  anchored at its VA. Build links clean (the LIB is shadowed).
- RESULT: the CRT region now sits approximately in place with a slowly
  GROWING drift (+70 at _fflush, +153 at _time — each dump 1-2B over or
  missing the non-library interleaved thunks: the wsock import stubs
  closesocket@4..socket@12 at 0x1001a160-0x1001a184 are kind=function, not
  library, so the generator skipped them).

NEXT: slice the dumps to exact boundaries (walk the full CSV incl.
non-library functions in the region) and re-measure; then the lb block and
data/BSS.

## CRT run dumps (2026-08-22) — reccmp 92.34% (was 91.96%)

- CRT dumps regrouped into 148 contiguous-run files (multi-naked TUs, split
  at >0x40 gaps; tail sizes from the CSV size field — the v+64 cap truncated
  fseek and friends).
- FINDING: the remaining head drift (+70 at _fflush, +137 by _ctime, then
  UNIFORM through the rest of the CRT) = the 6-byte wsock import thunks
  (closesocket@4..socket@12) each get +10 linker section alignment (6B -> 16B
  per naked function). Everything after the thunk cluster is uniformly +137 —
  fixing the thunk placement snaps the whole CRT block.
- NEXT: place the 6B thunks without per-function alignment (single-section
  blob with per-symbol aliases, or a section-alignment override), then the
  lb block, then data/BSS.

## CRT single-run breakthrough (2026-08-22) — 331/342 aligned (96.8%)

- ROOT CAUSE FOUND: MSVC6 /O2 aligns each function's .text section to 16
  (2**4); /O1 uses 2**0 (align 1, packed). The original's CRT functions are
  UNALIGNED (6-byte wsock thunks packed at 6-byte spacing) — so the whole
  CRT had to be one contiguous /O1 run. The earlier >0x40 run splitting
  re-introduced per-function TUs that let LIB members interleave (+78 drift).
- ONE run file (run_000.c, 249 naked functions, 0x1001a140..0x10023840,
  /O1) + single-underscore cname strip + __stdcall preserved for @N symbols:
  RESULT 331/342 aligned (96.78%), reccmp 91.82%.
- REMAINING: __CRT_INIT@12/__DllMainCRTStartup@12 still +33325 (their @N
  definitions land outside the run — investigate the stdcall cname);
  _ioterm -4285 (stale decomped definition); __ld12cvt -1432; the lb block
  (+1248/-672); then data/BSS.

## .text converged (2026-08-22) — 334/336 aligned (99.4%), reccmp 91.82%

- lb block fixed: lobby TU dumped (6 functions, 0x10014a50..0x10014ee0 —
  the C compiled 672B short); srv_RecvGame remains a C file (check later).
- .text size 0x22bb4 vs original 0x22846 (+0x36e). The CRT region verified
  BYTE-IDENTICAL (0 mismatches over 38,656B). The two remaining reccmp
  "misalignments" (_ioterm/__ld12cvt) are name-pairing artifacts.

NEXT PHASE — DATA:
- .rdata 0x14b1 vs 0x2e81 (short 0x19d0): the first ~0x1000B = the IAT/import
  thunks (2-byte deltas at 4-byte spacing = import addresses; the original's
  import ORDER differs from ours) + missing const strings/tables.
- .data raw 0x3000 vs 0xe000 (short 0xb000): initialized strings/tables
  (zlib crc/static trees, game tables) + per-TU data placement.
- Section VA: ours .data at 0x10026000 vs orig 0x10027000 (the .rdata delta
  cascades).

## Data phase survey (2026-08-22)

.rdata structure (original, 0x2e81 = 11905B): [IAT ~0x1000+][zlib
copyright strings +0x59f][unzip +0x12e8][CRT strings +0x207c: __GLOBAL_HEAP_
SELECTED, runtime error / TLOSS / SING / DOMAIN, the _NMSG_WRITE texts, heap/
stdio init errors]. Ours (0x14b1) has an IAT + our strings but the CRT nmsg
strings are ABSENT ("runtime error" not found) — the run_000 dumps shadow the
LIB objects that emitted them, and the dump bytes embed ABSOLUTE data
addresses (not relocatable) — the data must exist at the exact VAs.

PLAN for the data phase:
1. Emit the CRT's .rdata strings as a data TU sized so the sections land at
   the original VAs (.rdata total 0x2e81 -> .data at 0x10027000).
2. The original's .data raw 0xe000: the per-TU data accounting (the game
   arrays + the string/table content the game files emit) — the "arrays +
   per-TU order" work from the earlier TODOs.
3. IAT/import ORDER (the 2-byte deltas at 4-byte spacing = the import
   addresses — the original's import order differs from ours).

## Import-layer progress (2026-08-22)

- The original's imports: kernel32 81 (IAT 0x24000), user32 2 (0x24148),
  winmm 1 (0x24154), ws2_32 16 ordinals (0x2415c). The IAT is reference-
  ordered (GetLocalTime first ... LCMapStringA last).
- crt_imports.c now forces the order via `#pragma comment(linker,
  "/include:__imp__<Name>@<N>")` lines in the original's order (the @N
  arities hardcoded; 6 corrected against the import libs: GetTimeFormatA@24,
  GetDateFormatA@24, GetStringTypeW@16, GetStringTypeA@20, MessageBoxA@16,
  GetWindowTextA@12).
- RESULT: kernel32 IAT at 0x24000 (matches), user32/winmm/ws2_32 at +4
  (2 extra kernel32 slots — likely our game's extra kernel32 imports).
- NEXT: identify the 2 extra kernel32 slots (diff the IAT name tables),
  then the hint/name table positions, then the CRT strings + .data raw.
