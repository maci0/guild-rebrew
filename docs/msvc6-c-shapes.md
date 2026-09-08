# MSVC 6.0: C source shapes that decide the emitted bytes

Catalogue of source-level patterns that changed a function from mismatch to
byte match against the original `server.dll`. Each entry names the emitted
instruction difference, the fix, and a verified call site.

Companion docs: `msvc6-allocator.md` covers register allocation decisions;
this file covers declaration types, operand forms, statement order, and loop
shape. Both are empirical, derived from compile-and-compare against the
target, not from documentation.

Verify any change with `rebrew diff <VA>` and `rebrew test <file>`. A `**`
match code marks a genuine structural difference; `~~` is relocation-only and
counts as a match.

## How to probe a hypothesis

Compile an isolated file rather than iterating on the real function. Seconds
instead of minutes, and it isolates one variable:

```sh
cd .scratch
rebrew-cmake-cl /nologo /c /MT /O2 /Gd probe.c
objdump -d probe.obj
```

Put every probe in `.scratch/`. Ground truth for a target comes from
`rebrew asm <VA> --size N --json`.

---

## 1. Global array element type sets the addressing scale

The declared element type picks the index scale in the addressing mode. A
wrong type is invisible in C but changes every access.

Target emitted `mov cx, word ptr [eax*4 + g_entity_slot_table]`; the source
declared the table as `unsigned short`, so it emitted `mov cx, word ptr
[eax*2]`, scale 2 against scale 4.

The table holds 4-byte entries with a 189-entry stride (189 x 4 = 0x2f4) and
only the low word of each entry is read. Declaring the element type as the
stride unit, indexing in entries, and narrowing at the point of use restores
scale 4:

```c
/* 189 4-byte entries per object type; only the low word of each entry is read. */
extern unsigned int g_entity_slot_table[];

word1 = (unsigned short) g_entity_slot_table[(unsigned int) *(unsigned char*) 0x10035439 * 189];
```

`src/server.dll/DieGildeAddOn/game/friedhof_logic_c/HireProductionWorker.c:15,72`

One declaration fix corrected four functions: `HireProductionWorker`
(0x100111b0), `ExtendProductionTime` (0x100113b0),
`cm_ExTransferCurrencyNoKill` (0x1000d8a0), `gm_QueryEntitySum` (0x100196c0).

A byte-offset form (`*(unsigned short*)((char*) tbl + idx * 0x2f4)`) also
byte-matches at some sites and is what `cm_ExTransferCurrency` and
`cm_ExSellObjekt` already use. Do not convert working call sites; the two
forms are not interchangeable everywhere.

## 2. Pointer vs array: `mov` load against `lea`

`extern char* g_slot_table;` declares a pointer variable, so the compiler
loads its contents: `mov ecx, dword ptr [g_slot_table]`. When the symbol *is*
the array, the original computes an address instead: `lea ecx, [esi + g_slot_table]`.

Take the address at the use site:

```c
result = (int) gm_GetEntityTableEntry((char*) &g_slot_table + idx);
```

`src/server.dll/DieGildeAddOn/game/spiel62.c:374`,
`src/server.dll/DieGildeAddOn/game/spiel622.c:378`

Fixed `gm_CheckStatLevel` (0x100181a0) and `gm_ResolveParentEntity`
(0x10019ae0). Note `g_slot_table` is declared inconsistently across the tree
(pointer in the `spiel*` files, `char[]` in `command_internal.h`); fix at the
use site rather than unifying the declaration, which would disturb functions
that already match.

## 3. Uninitialized locals from decompilation

A local read before assignment is always a decompiler artifact. The original
disassembly shows what the value should have been. Two shapes seen:

A loop pointer never given its base. The target opens with
`mov edx, g_entity_base` before the fill loop:

```c
ptr = (char*) g_entity_base;
do {
    memset(ptr, 0, 0xAC);
    ...
} while ((int) ptr < (int) g_entity_end);
```

`src/server.dll/DieGildeAddOn/game/spiel62.c:285`, fixing `gm_InitEntitySlots`
(0x100180d0).

An index computed from itself (`idx = idx * 189;` with `idx` never set). The
target's `mov cl, byte ptr [g_current_season]` names the real source:

```c
idx = (unsigned int) (unsigned char) g_current_season * 189;
```

`src/server.dll/DieGildeAddOn/game/spiel622.c:327`, fixing
`gm_AccumulateTyped2` (0x10019a20).

## 4. Wrong global in a guard

Two globals of the same type read identically in C and differ only by
address. `ReportMessage` guarded on `g_handler_started` (0x10034680) where the
target loads `g_panic_callback` (0x10034610):

```c
if (!g_panic_callback) {
    MessageBoxA(0, "ERROR-Handler has not been started...", "Error!", 0x10030);
    return;
}
```

`src/server.dll/Units/Error/Error_c/ErrorModule2.c:97`, fixing 0x100035c0.

Cross-check every global address in the target disassembly against the VA
comments in `src/server.dll/rebrew_globals.h`. That header also carries
duplicate declarations of the same symbol, so a plausible-looking name is not
evidence the address is right.

## 5. An explicit pointer local defeats the induction-variable rewrite

Carrying a walking pointer alongside an index makes MSVC 6.0 treat the
pointer as a user variable it must materialize where written, emitting a bare
offset with no base (`mov ecx, 0x46`; `mov ax, word ptr [ecx]`). The target
instead sets the base once and advances it: `mov ecx, g_plant_info_table`
then `mov ax, word ptr [ecx + 0x46]` / `add ecx, 0x46`.

Express the walk purely through the index and let the compiler build the
induction variable:

```c
char* __cdecl lb_SearchRecordTable(int key)
{
	unsigned int idx;

	idx = 0;
	while (*(unsigned short*) ((char*) &g_plant_info_table + idx * 0x46) != 0) {
		if ((int) *(unsigned short*) ((char*) &g_plant_info_table + idx * 0x46) == key)
			return (char*) &g_plant_info_table + idx * 0x46;
		idx++;
	}
	return 0;
}
```

`src/server.dll/DieGildeAddOn/auxillary/plant.c:12`, fixing 0x10014ee0 at
69/69 bytes. The repeated index expression is deliberate: the strength
reduction to `lea eax,[edx*8]; sub eax,edx; lea eax,[eax+eax*4]` comes from
the compiler, and hoisting it into a named pointer suppresses it.

## 6. Local variable width

`unsigned int` where the original kept a value in 16 bits changes the loop
body. The tell in the target is a 16-bit update paired with a widening mask
each iteration: `mov ax, word ptr [...]` plus `and eax, 0xffff`. Match the
width the disassembly implies rather than defaulting to `int`.

## 7. Branch polarity: merge sequential returns

Two consecutive guards returning the same value compile to two epilogues:

```c
if (!slot) return -7;
if (a != b) return -7;
```

The target had one. A short-circuit merge produces the single shared exit and
flips the branch sense (`jne` to `je`):

```c
	slot = GetSlotEntry(workers, *(int*) ((char*) req + 0xc),
	                    *(unsigned char*) ((char*) req + 0x10));
	if (!slot ||
	    *(unsigned short*) ((char*) slot + 8) !=
	        *(unsigned short*) ((char*) owner + 0x50))
		return -7;
```

`src/server.dll/DieGildeAddOn/game/friedhof_logic_c/AssignProductionSlot.c:56`

## 8. Loop shape: `for(;;)` with early return vs `do/while` with a tail return

The exit structure decides branch layout and total size. A `for(;;)` with
returns inside the body emits an epilogue per return; a `do/while` with a
shared tail return emits one. Read the target's exits and mirror the count
before tuning anything else.

## 8a. x87 memory-operand forms: `fimul`/`fidiv` vs `fild` + `fmulp`/`fdivp`

MSVC 6.0 fuses an integer operand into `fimul <mem>` or `fidiv <mem>` only
when that operand is memory-resident at the FPU op. When its last use is the
multiply or divide itself, the value stays in a register and you get the
two-instruction `fild` + `fmulp`/`fdivp` form instead.

A `volatile` alias forces residency without emitting extra code ahead of the
FPU op. Two shapes, both verified in `.scratch/probe_fi3.c` and `probe_fd1.c`:

Read through the alias (also schedules the mask after the `fild`, matching the
target's `and eax,0xff` placement):

```c
volatile int* p2_alias;

p2_alias = (volatile int*) &param2;
*p2_alias = param2 & 0xff;
cached = cached * (int) *p2_alias;      /* fimul dword ptr [esp+0x18] */
```

Assign through an alias, where the local is read normally afterwards:

```c
int* d_alias;

d_alias = &divisor;
*d_alias = (*(unsigned short*) (entity + 0x36) == 0) + *(unsigned short*) (entity + 0x36);
quot = quot / divisor;                  /* fidiv dword ptr [esp+0x14] */
```

`src/server.dll/DieGildeAddOn/game/spiel622.c` in
`gm_CalculateProductionValue` (0x10019720), which went 132 to 322 matched
instructions across these changes plus 8b and 8c below.

### Pick the weaker lever when the target's schedule is looser

Both a `volatile` alias and a plain `int*` alias force residency and produce
the fused `fidiv <mem>`. They differ in ordering:

- **`volatile` forces residency *and* ordering.** Volatile accesses are
  ordered against each other, so a volatile store cannot sink past a volatile
  read elsewhere in the function.
- **A plain alias forces residency only**, leaving MSVC 6.0 free to schedule
  the store where it likes.

In `gm_CalculateProductionValue` the numerator needs a volatile *read* to pin
its load ahead of the divisor computation, but the divisor then needs a
**plain** alias: a volatile store there would be ordered against that read and
forced ahead of the `fild qword`, whereas the target sinks
`mov [esp+0x14],edx` after it. Using volatile at both sites scored 141;
volatile read plus plain alias scored 322.

Reach for `volatile` when you need ordering, and the plain alias when you need
residency without constraining the schedule.

## 8b. A folded `cmp` hides a load the target keeps in a register

Where the target reads a byte into a register and compares it
(`mov al, byte ptr [esi+0x21]` then `cmp al, 3`), MSVC 6.0 will happily fold
both into `cmp byte ptr [esi+0x21], 3`, which is one instruction shorter and
lands in the wrong place relative to a neighbouring FPU op.

Hoisting into a plain local does not prevent the fold. Reading through
`volatile` does, and also pulls the load ahead of the FPU instruction:

```c
char kind;

kind = *(volatile char*) (entity + 0x21);
cached = cached * (int) *p2_alias;      /* mov al,... ; fimul ... ; cmp al,3 */
```

`src/server.dll/DieGildeAddOn/game/spiel622.c:216`. This single change moved
0x10019720 from 119 to 207 matched instructions, the largest single jump of
the session.

## 8c. A volatile read pins load order between two field reads

Section 10 covers reordering adjacent field reads by moving the C statements.
When that is not enough, because a neighbouring volatile access or an FPU op
lets the compiler sink the load anyway, a volatile *read* on the operand that
must come first pins it there.

The target loads the numerator `[esi+0x22]` before the divisor source
`[esi+0x36]`; plain statement reordering did not reproduce that, and hoisting
the numerator into an ordinary local left it in place:

```c
quot = (double) (unsigned int) *(volatile int*) (entity + 0x22);
```

That fixed the order and the qword home at `[esp+8]`/`[esp+0xc]`, matching
target instructions 30 through 47. Combined with the plain-alias divisor from
8a, 0x10019720 went 263 to 322.

Cost: a volatile read is also an ordering barrier, so it constrains every
other volatile access in the function. See the "weaker lever" note in 8a.

## 9. Register roles follow order of first use

When the instruction stream matches and only register roles differ (esi and
edi exchanged, everything else identical), the cause is allocation order, not
logic. MSVC 6.0 assigns in order of first use.

Reorder the declarations, or the statements that first touch each variable,
until the roles line up. In `AssignProductionSlot` the counter `i` and the
walking pointer had to be established in the target's order:

```c
	i = 0;
	entries = *(int**) ((char*) slot + 0x10);
	selected = entries;
	count = dword_1002574c[*(int*) ((char*) req + 0xc)];
	for (; i < count; i++) {
```

`src/server.dll/DieGildeAddOn/game/friedhof_logic_c/AssignProductionSlot.c:62`
closing out 0x10010fa0 at 525/525 after the size was already correct.

### 9a. Shorten a live range to break an esi/edi tie

When both candidates for esi/edi are established at the same point (two
parameters, first touched in the same call), reordering first use has nothing
to reorder and section 9 does not apply. What decides the tie is then the
*length* of each live range, and the lever is a fresh local that ends one of
them early.

`ls_LoadSavegameHeader` (0x10012470) passes `stream` and `dest` to the same
function ~25 times. Advancing the destination in the tail,

```c
dest += 0x9c;                 /* stream->edi, dest->esi: 801/857 */
```

keeps `dest` live to the last instruction and loses the tie. Hoisting the
advance into a separate local ends `dest` at the hoist:

```c
tail = dest + 0x9c;           /* stream->esi, dest->edi: 819/857 */
```

No instruction is added or removed; only the register assignment changes.

Neither half was the whole answer here: the hoisted `tail` gave up the
target's duplicated `add edi,0x9c` and its memory-form version compare, so
819/857 was the ceiling for this lever alone. Section 40 closes the function
by keeping the `dest += 0x9c` shape and cutting dest's *reference count*
instead of its live range.

Diagnostic for this class: delete the statement you suspect of adding weight
and recompile. If the roles flip, that statement is the trigger and the fix is
to shorten its variable's range, not to remove it. Adding a use of the *other*
variable also flips the tie (`if (stream == 0) return 0;` scored the target
roles) but costs instructions; prefer the live-range split.

## 10. Load scheduling between adjacent field reads

Which of two struct fields loads first can differ with the instruction stream
otherwise identical. Reorder the C statements that read them. This was the
residual difference in `AssignProductionSlot` after the loop shape was
correct: the target loads `slot->0x10` before `req->0xc`.

## 11. Inline memset expansion (partial result, no byte match)

`InitPacketPool` (0x100068e0) emits a head-alignment prelude:

```
lea ecx,[edi+edi*2]; and ecx,3; sub ebx,ecx; jle; rep stosb; ...; rep stosd; ...; rep stosb
```

`lea ecx,[edi+edi*2]` with `and ecx,3` computes `(-p) & 3` (3 is -1 mod 4).

A plain `memset` never emits this. Probes across pointer type (`void*`,
`char*`, `unsigned char*`, `int*`), destination provenance (allocator return
vs reloaded from a global), length shape (constant, runtime, provable
multiple of 4), and 12 flag sets all produce the plain
`shr ecx,2; rep stosd; and ecx,3; rep stosb` form
(`.scratch/probe_ms1.c`, `probe_ms3.c`, `probe_ms4.c`).

An explicit align-up split in pure C does **not** emit the prelude either. An
earlier revision of this section claimed it did, from a partial reading of
`.scratch/probe_ms2.c` `w1`; disassembled in full, `w1` differs at every point
of the shape:

| target | align-up split `w1` |
|---|---|
| `lea ecx,[edi+edi*2]` + `and ecx,3` | `neg edx` + `and edx,3` |
| `sub ebx,ecx` + `jle` | `sub ebp,edx` + `test ebp,ebp` + `jle` |
| 3 reps: stosb, stosd, stosb | 4 reps: two complete stosd/stosb memsets |

Its 162 bytes are two full memset expansions landing on the target's size by
coincidence, not the target's shape. It also scores far worse than the plain
`memset`: 42 to 66 matched across `.scratch/ipp/bodies/split_a..h.c`, and 54
when combined with parameter-slot homing (`.scratch/ipp/bodies/u1.c`), against
105 for the plain form. Do not re-try the split.

Two measurements show why the prelude is a different template, not a
scheduling or residency difference:

- `sub reg,reg` followed directly by `jle`, with no `test` between, is not
  msvc6 output. Every C spelling of "difference <= 0" emits `sub; test; jle`
  (13 spellings in `.scratch/ipp/p29.c` and `p30.c`); `< 1` gives `cmp $1`,
  and only a comparison against 0 with a dead difference fuses, as `sub; jns`.
  Across all 576 catalog functions of `server.dll`, `sub`+`jle` occurs at
  exactly 6 addresses, the 6 prelude sites and nowhere else
  (`.scratch/ipp/scan_target_subjle.py`, output in `subjle_scan.txt`).
- The inlined `memset` always orders its two reps
  `shr ecx,2; rep stosd; and ecx,3; rep stosb`. The prelude runs `rep stosb`
  first, then `shr; rep stosd`, then a third `rep stosb`: three reps in a
  different order.

So the original claim stands after all: no pure-C shape found so far emits the
prelude, and a byte match needs asm. Best pure-C result is 105/162.

## 12. CFLAGS are per-file in practice, not per-function

`rebrew-functions.toml` stores `cflags` per function, but a compile covers the
whole translation unit. Adding a `// CFLAGS:` header for one function caused
`rebrew test` to write those flags into the toml entry of a *sibling*
function in the same file, breaking `m_FreeTracked` (0x10006820) from
RELOC 188/188 to SIZE_MISMATCH.

A flag one function needs can break another in the same file. `/Oy-` on
`InitPacketPool` is exactly this conflict: the target's frame pointer needs
it, its file-mate must not have it. Where the flag has a `#pragma optimize`
equivalent, use that instead; see section 13 for the frame-pointer case.

After any flag change, diff per-function status against the previous run
rather than reading the summary count:

```sh
rebrew verify --json 2>/dev/null > .scratch/after.json
jq -r '.results[] | "\(.va) \(.status)"' .scratch/before.json | sort > .scratch/b.txt
jq -r '.results[] | "\(.va) \(.status)"' .scratch/after.json  | sort > .scratch/a.txt
join .scratch/b.txt .scratch/a.txt | awk '{if ($2!=$3) print}'
```

Empty output means no drift. `rebrew-functions.toml` is tool-managed and
write-protected; reset a corrupted entry by re-running `rebrew test` with an
explicit `--cflags`, not by editing the file.

## 13. Per-function frame pointer without a CFLAGS header

`#pragma optimize("y", off)` around a single function emits
`push ebp; mov ebp, esp` and `pop ebp` under `/O2 /Gd`, with no `// CFLAGS:`
header and no effect on its file-mates. It is the way out of the section 12
conflict: `InitPacketPool` (0x100068e0) needs the frame pointer, and
`m_FreeTracked` (0x10006820) in the same file must not have it and stays
RELOC 188/188.

```c
#pragma optimize("y", off)
void __cdecl InitPacketPool(int n)
{
	/* ... */
}
#pragma optimize("", on)
```

Close with `#pragma optimize("", on)`, which restores the command-line
settings; the following function compiles unchanged. Verified by compiling
three identical bodies in one file with only the middle one wrapped
(`.scratch/ipp/p4.c`): only the middle one gained the frame.

Address-taking a parameter or a local does not force a frame; msvc6 keeps
addressing them off `esp`. `_alloca` does force one, but it also emits the
allocation code, so the pragma is the clean lever.

## 14. Homing a value in the incoming parameter slot

Assigning to a parameter and reading it back through a `volatile` alias spills
that value to the parameter's own stack slot and reloads it from there,
reproducing a target that keeps a value in memory across a call instead of in
a register:

```c
n = len;                                                     /* plain store */
memset(g_array_ptr, 0, (unsigned int) *(volatile int*) &n);  /* volatile read */
```

This emits `mov [ebp+8],edi` then `mov ecx,[ebp+8]`, matching
`InitPacketPool` 0x1000691b-0x10006924 and raising it from 97 to 105 matched
bytes. The same idea as section 8a applied to a call boundary rather than an
FPU operand: the read forces the value to live in memory, and reusing the
parameter as the destination picks which slot.

**The store must be plain; only the read is `volatile`.** This is the section
8a residency/ordering distinction applied to an integer spill. A `volatile`
store is ordered against the surrounding volatile accesses, so it floats up
ahead of the allocator call and drags the `add esp,4` and the `g_array_ptr`
store out of the target's order, costing 15 bytes: `*(volatile int*) &n = len`
scores 90, the plain `n = len` scores 105, with identical read-backs. Homing
via a plain `int*` alias (`int* pn = &n; *pn = len;`) instead of assigning to
the parameter scores 90 to 104 depending on the read form, never above.

## 15. `_ftol(expr)` pushes a double; a plain `(int)` cast does not

`__ftol` takes its argument in `st(0)` and returns in `eax`. Spelling the
conversion as an explicit call to a `_ftol` declared with a parameter list
makes msvc6 marshal the value as a normal stack argument first:

```
sub esp,8 ; ... ; fstp qword ptr [esp] ; call __ftol ; add esp,8
```

A plain `(int)` cast of the same expression emits only `call __ftol` with the
value already on the x87 stack, three instructions and 11 bytes shorter. The
target has no `sub esp,8` / `fstp qword ptr [esp]` pair anywhere, so any such
pair in the candidate is a spelling artefact, not a scheduling difference.

```c
/* pushes a double */
rnd = gm_RandomMod((unsigned short) _ftol(*(float*) (slot + 0x1c) * k));
/* leaves the value in st(0) */
rnd = gm_RandomMod((unsigned short) (int) (*(float*) (slot + 0x1c) * k));
```

`src/server.dll/DieGildeAddOn/game/spiel_c/gm_CreateEntityFromParents.c:457`
closed the last 6 bytes of `gm_CreateEntityFromParents` (0x10018850), taking it
from 3695 to exactly 3689 bytes and 608 to 670 matched.

**Not interchangeable across call sites.** The same rewrite applied to the four
other `_ftol` sites in that function *lowered* the score every time (670 to 649,
608 to 536, 573 to 492/515). Where the result feeds a loop counter that msvc6
keeps in a register, the pushed form is what the target emits. Convert one site
at a time and keep only the ones that measure better.

A later session found one more convertible site in the same function: the
second age loop, `for (n = _ftol((double) *(u16*)(slot + 0xa) - *(float*)(slot
+ 0x20)))`, converted cleanly and took the score from 711 to 715. The four
remaining sites were each retested from that new base and still lose badly
(715 to 491, 466, 464, 471), which confirms the per-site rule rather than
weakening it. Retest every site again after any change that moves the
schedule; convertibility is a property of the current surrounding code, not of
the call site alone.

The conversion also has a frame-layout side effect worth knowing. Removing the
`sub esp,8` / `fstp qword ptr [esp]` pair freed the spill slot that had pushed
the loop index from the target's `esp+0x1c` to `esp+0x20`, which was the first
mismatching byte of the whole function (offset 15). Declaration order is *not*
a lever for this: placing the index at every position among the locals scored
identically, because msvc6 assigns spill slots by liveness. Where a frame slot
is off by one, look for a live range to remove, not a declaration to move.

## 16. Compare the call skeleton before chasing instruction diffs

`rebrew diff` aligns instruction-by-instruction, so a single early structural
difference desynchronises everything after it and the `**` markers past that
point are alignment noise, not real divergences. Extracting the ordered list of
relocation targets from both sides gives an alignment-independent skeleton:

```sh
rebrew asm <VA> --size <N> --json | jq -r '.instructions[]|select(.mnemonic=="call")|.operands'
objdump -r <candidate>.obj | grep 'DISP32\|REL32' | awk '{print $3}'
```

A mismatch in that list is a genuine logic error: a call the reconstruction
invented, omitted, or placed in the wrong branch. In `gm_CreateEntityFromParents`
this found a `gm_RandomMod(2)` / `gm_RandomFloat01()` pair the source ran on the
two-parent path where the reference only has it on the no-parent path, and a
`gm_RandomMod(0x10)` drawn twice in the reference (first result discarded) but
once in the source.

Counting instructions *between* consecutive calls localises the remaining work
to a specific segment without depending on the aligner. A segment whose count
is short by a double-digit margin is missing a branch, not scheduled
differently: a 20-instruction gap pointed straight at a four-way class pick
(reference 0x10019228-0x100192b3) that the source had collapsed to two arms,
worth 35 matched bytes and 27 instructions once restored.

The helper used here is `.scratch/seg.py`; it needs only the two instruction
lists and the call indices.

## 17. Out-of-line block placement is not steerable from source

MSVC 6.0 decides whether a `goto`-target block sits inline or out of line in
its own layout pass. Source position does not influence it.

In `ServerMainThread` (0x100093a0) the target keeps the host-slot block out of
line, ending in a 5-byte backward `jmp`:

```
0x1000973a  mov eax, ecx ... or dword ptr [eax*4 + g_connections], 8
0x10009756  jmp 0x10009657
```

The reconstruction emits the same instructions with the same operands, but
placed so control falls through into the following loop, so the block needs
only a 2-byte skip `jmp`. That 3-byte difference is the whole size deficit:
obj 2431 against a target of 2434.

Three placements were tried, all compiled and measured, all leaving both the
match count and the object size unchanged at 1122/2434 and 2431:

- label between the two `goto`s inside the later loop (original shape)
- label moved after the `transfer_pending` arm, with an extra `goto`
- label moved past the function's `return`, at the very end of the body

Rewriting the search loop so the found case runs inline instead of via `goto`
(no label at all) scored **776**, well below the 1122 baseline.

Do not spend further attempts steering block placement from C. Treat a
remaining out-of-line/inline difference as a layout-pass artifact and work the
instruction content instead.

## 18. Byte-width levers move encodings, not always the score

The same function's target holds a constant in a byte register and computes a
mask in 8 bits:

```
mov bl, 7 ... and al, 8 ; neg al ; sbb al, al ; and al, bl ; add al, 2
```

The reconstruction emitted `mov ebx, 7` / `and eax, ebx` (3 bytes larger).
Forcing byte width does reproduce the target encoding exactly, and both
formulations below produced `mov bl,7`, `neg al`, `sbb al,al`, `and al,bl`:

```c
/* scored 854 */
cmd[0x10] = (unsigned char) ((unsigned char) (-(signed char) ((c & 8) != 0) & ready_flag) + 2);
/* scored 881 */
host_ready_mask = (unsigned char) ((c & 8) ? 0xff : 0);
cmd[0x10] = (unsigned char) ((host_ready_mask & ready_flag) + 2);
```

Both scored *below* the 1122 baseline, whose plain int ternary keeps the wrong
encoding. Matching a local encoding can still cost more downstream than it
gains: the byte forms perturbed register allocation across the rest of the
loop. Measure the whole function, never the instruction you aimed at.

A byte-typed local alone does not force the narrow register: routing the
constant 7 through an `unsigned char` local still emitted `mov ebx, 7` while
the ternary stayed in int context. The narrow form appears only once the whole
expression is byte-typed.

## 19. `match_count` is positional, so one size delta hides a good match

`match_count` compares the two byte streams *at the same offset*, with
relocation slots masked (`rebrew/src/rebrew/core/matching.py:488`). It is not
an alignment-aware score. A single displaced block therefore charges every
later byte as a miss, and a low percentage can hide a function that is almost
entirely correct.

`ServerMainThread` (0x100093a0) scores 1122/2434 (46%). Aligning each region at
its own best shift would score 1955/2434, and under an optimal instruction
alignment 466 of 627 instructions are already byte-identical. Roughly 942 of
the ~1300 missing bytes are cascade from one 3-byte size deficit.

Before working an instruction, check whether it is a cause or a symptom.
Re-score the candidate stream with each region shifted to its own best offset:
what the shift recovers is cascade, and only what remains is real. Applied
here, that reduced 457 reported structural differences to a single `jne`.

The same reasoning localises the true residual. In the 672-byte prefix that is
still aligned, the only non-relocation differences were one `jne` and three
`jmp` displacements off by exactly 3, all consequences of the same deficit.

Also beware unlinked relocation slots when reading a raw diff. An unlinked
`.obj` leaves them zero and the scorer masks them, but a *non-zero* slot is not
masked and is a real loss. `(&g_max_players)[1]` emitted `mov dword ptr [4],
eax`, whose `04000000` field failed the zero-dword heuristic; splitting the
neighbour into its own `extern int g_tick_rate` restored `mov dword ptr [0]`
and removed the false mismatch.

## 20. Statement order does not move stores into the same buffer

MSVC 6.0 schedules stores to one stack buffer freely, so reordering the C
statements that fill a packet changes nothing. In `ServerMainThread`, swapping
the `cmd+0x18` and `cmd+0x1c` stores produced byte-identical output.

Rewriting a loop between `while`, `do/while`, and `for(;;)` with explicit
breaks is likewise inert once the bodies are equivalent: all three shapes of
the flag-scan loop compiled to the same bytes. The compiler canonicalises the
loop before layout.

What *does* move is the order in which distinct globals are first read, since
that sets register roles. Reordering the sync-packet loads changed the object
size from 2431 to 2432 and the score from 1122 to 1121. Real lever, wrong
direction here, but worth trying when register roles are the mismatch.

## 16. `match_count` is a positional byte compare, not an alignment-aware score

`match_count` counts byte positions that agree after masking relocation slots
(`rebrew/src/rebrew/core/matching.py:488`). It does not realign after an
insertion or deletion.

One extra or missing instruction early in a function therefore shifts every
later byte and collapses the score, even when the whole remainder is
semantically correct. A low percentage on a large function is evidence of an
early divergence, not of widespread wrongness.

Read the percentage as "bytes correct at their target offset", and judge real
progress from `rebrew diff`: specifically how far the matching prefix extends
before the first `**`, and how many `**` clusters remain. A change that fixes
an early divergence can jump the score by hundreds; a change that adds one
instruction near the top can erase an otherwise-correct body.

## 21. Fold the offset into the pointer before the access

When the target computes an address once and reuses it (`add eax,edx; fstp
[eax]`, or a `mov`/`inc` pair on a cursor), repeating the offset expression
inside the access keeps MSVC 6.0 in a scaled-index addressing mode and picks a
different scratch register. Doing the arithmetic in a separate statement first
forces the materialized address the target uses.

`cm_ExChangeFloat` (0x1000eb70) read the field offset twice, once on each side
of the store:

```c
*(float*) (p + *(int*) (base + 0x14)) =
    *(float*) (base + 0x18) + *(float*) (p + *(int*) (base + 0x14));
```

That emitted `mov ecx,[esi+0x14]` and `fadd [eax+ecx]`. Folding the offset into
`p` first put the temp in `edx` and produced the reference's `add eax,edx`:

```c
p = p + *(int*) (base + 0x14);
*(float*) p = *(float*) (base + 0x18) + *(float*) p;
```

`src/server.dll/DieGildeAddOn/command/command_c/cm_ExChangeFloat.c:44`
(0x1000eb70, 132/135 to RELOC 135/135).

The same lever applies to a cursor kept in a struct field. `vfs_GetByte`
(0x10003820) copied the read pointer into a local, which made MSVC 6.0 hold it
in `ecx` and zero-extend the byte into `eax`; the reference reuses `eax` for
both the count temp and the cursor. Post-incrementing in place through a
pointer alias of the field restores that:

```c
stream[1] = stream[1] - 1;
return *(*(unsigned char**) &stream[0])++;
```

`src/server.dll/Units/vfs/vfs.c:60` (0x10003820, 104/114 to RELOC 114/114).

### 21a. Hoisting a field load out of an argument list breaks an esi/edi tie

Section 9 reorders first use; 9a shortens a live range. Neither applies when
the tie is between a loop cursor and a value the loop only reads inside a call
argument. What decides it there is whether the field load is *materialized*
into a local at all.

`gm_SumBuildingProductionValues` (0x100198b0) held the component cursor and
the query result in exchanged registers, 12 mismatched bytes with an otherwise
byte-identical stream. Reading the query's field inside the argument list,

```c
sub = gm_StartEntityQuery(*(int*) ((char*) q + 0x14), 1, 0, comp & 0x7fff);
```

leaves the load owned by the call site and scores 343/355 with the cursor in
esi. Assigning it first gives the load its own definition point, and the
allocator then places the cursor in edi and the query in esi as the original
does:

```c
qbase = *(int*) ((char*) q + 0x14);
sub = gm_StartEntityQuery(qbase, 1, 0, comp & 0x7fff);
```

`src/server.dll/DieGildeAddOn/game/spiel622.c:430` (343/355 to 350/355).

The two states are exclusive under `/O2 /Gd`: the hoist costs the target's
argument schedule (it pushes the id, then loads into eax and pushes it last;
the hoist loads into ecx before the pushes), worth 5 bytes against the 12 the
register roles were worth. Address-only hoists (`qbase = (int) q + 0x14`),
`int*`/`char*` alias locals, `((int*) q)[5]`, a dead hoist beside the inline
load, `register int`, and an assignment folded into the argument all score
343: they do not materialize the loaded value, so the tie does not flip.

Diagnostic: when every `**` line is a register name with identical mnemonics
and operands, look for a value the target holds across a call that your source
only ever spells inside an argument.

## 22. `volatile` on the store target pins a store against loop scheduling

MSVC 6.0 sinks a store past a pointer bump when it can rewrite the address as
a negative displacement, turning `fstp [eax]; add eax,0xc` into `add eax,0xc;
fstp [eax-0xc]`. Neither loop shape (`for`, `while`, `do/while`), induction
form (index vs pointer), nor CPU flag moves it, because all of them
canonicalise to the same schedule. Qualifying the store target does.

`ahm_InitRandomEntity` (0x1000c600) scale loop:

```c
do {
    *(volatile float*) p = p[-1] * dScaleFactor;
    p += 3;
    n--;
} while (n != 0);
```

`src/server.dll/DieGildeAddOn/game/alchemistry_logic2.c:293` (0x1000c600,
100/109 to RELOC 109/109).

Note the asymmetry with section 15: `volatile` on the *loaded* operand pins
the load and blocks the memory-operand fold, which is usually not what a
scheduling mismatch needs. When the diff shows the right instructions in the
wrong order, qualify the destination, not the source.

## 23. A shared clamp value needs a 32-bit temp assigned in both arms

A guard that stores a constant on one path and a reloaded value on the other
emits two independent stores when each path writes memory directly:

```c
if (*(unsigned char*) (obj + 0x37) > 100) {
    *(unsigned char*) (obj + 0x37) = 100;   /* mov byte ptr [eax+0x37],0x64 */
    return 0;
}
```

The reference instead materializes the value in a 32-bit register and stores
it once after the join (`mov ecx,0x64` on one path, `xor ecx,ecx; mov cl,
[eax+0x37]` on the other, then a shared `mov [eax+0x37],cl`). Writing that
join in C reproduces it exactly:

```c
if (*(unsigned char*) (obj + 0x37) > 100) {
    clamped = 100;
} else {
    clamped = *(unsigned char*) (obj + 0x37);
}
*(unsigned char*) (obj + 0x37) = (unsigned char) clamped;
```

`src/server.dll/DieGildeAddOn/command/command_c/cm_ExAllocWarEvent.c:86`
(0x10010140, 258/280 to RELOC 280/280). The temp must be wider than the
stored type: a `unsigned char clamped` folds back to the immediate stores.
This also removes the size delta, since the joined form is shorter than two
epilogues.

## 24. Two volatile reads pick both the register form and the schedule

A read-modify-write of a flag word emits `mov edx,0x80; or eax,edx` when the
optimizer is free to sink the load past an unrelated store. The reference
uses the 2-byte `or al,0x80`, which requires the load to stay adjacent to the
OR. Two separate `volatile` qualifications are needed, and they do different
jobs:

```c
flags = *(volatile unsigned int*) conn;              /* keeps the OR in al   */
*(volatile unsigned short*) ((char*) conn + 0x14a) = 0;  /* pins it between   */
*(unsigned int*) conn = flags | 0x80;
```

`src/server.dll/DieGildeAddOnServer/server2.c:406` (0x1000a340, 312/336 to
RELOC 336/336).

The volatile read alone gets `mov (%esi),%eax; or $0x80,%al` but leaves the
clear after the OR; the volatile store alone sinks the load below the clear
and restores the edx materialization. Neither a plain temp, an `|=` on the
low byte, nor any statement permutation reaches the pair. This extends
section 22: `volatile` on the loaded operand is the lever when the diff shows
a wrong *register form*, not only a wrong order.

## 25. ecx/edx naming residue is usually a first-read or a hoisted-temp bug

A diff whose `**` lines all read `T: <op> <regA>` / `C: <op> <regB>` with
identical mnemonics and offsets looks like an allocator floor, but two cheap
levers close most of them. Both were found on functions this section
previously listed as unreachable.

**Which value is read from memory first fixes the byte register.** In
`GetCommandPayloadSize` (0x1000c710) the target keeps the switch byte in `dl`
and the loop index in `ecx`; the `case 0x16` body reads `cmd_payload` twice,
once for the `*cmd_payload == 0x16` test and once for `cmd_payload[0x14]`.
Reading the byte for the test first pins it in `dl`:

```c
cursor = (*cmd_payload == 0x16) ? (cmd_payload + 0x15) : (cmd_payload + 0x15);
count = cmd_payload[0x14];    /* RELOC 752/752 */
```

The reverse order scores 742/752, and hoisting the unrelated
`total_size = 0x15` above both scores 508/752.
`src/server.dll/DieGildeAddOn/game/alchemistry_logic_c/GetCommandPayloadSize.c:93`.

**A hoisted `~x` temp takes the register the target gave the other value.**
In `ExecuteOfficeAssignment` (0x1000b4d0) the loop clear was written as a
`neg_mask` local, which parked the mask in `ecx` and pushed `role_ch` to
`edx`, the reverse of the reference. Spelling the complement inline in the
loop body restores both:

```c
*scan = *scan & ~mask;        /* 826/836 -> 829/836 */
```

`src/server.dll/DieGildeAddOn/game/aemter_c/ExecuteOfficeAssignment.c:260`.
The same complement written as `neg_mask = ~mask`, as `mask = ~mask` before
the loop, or inside a `for`-init all score 826.

Levers that still moved nothing on either function: declaration order and
block scope of the competing locals, signed/unsigned and width changes,
`volatile` on either operand (it moves the *schedule*, then re-swaps),
pointer-vs-index address forms, and `/O1 /Ox /Og /Oxs /G5 /G6`.
`cm_ExChangeAttribute` (0x1000e7d0, 216/242, descriptor cursor and
destination as eax/ecx) is still open.

Check the `structural` count in `rebrew diff --json` first: it counts real
shape differences, and a small non-zero value points at the statement to
reorder rather than at an allocator floor.

## 26. Spelling a clamp as `setle`/`dec`/`and` decides the loads before it

`(x <= 0) ? 0 : x` and the explicit mask below compile to the same
`xor`/`test`/`setle`/`dec`/`and` sequence, but they schedule the *preceding*
loads differently:

```c
neg = (sum <= 0) ? 1 : 0;
sum &= neg - 1;
```

`UpdateProductionProgress` (0x10011790) adds a byte field to a dword field and
clamps the result. The target opens the tail with
`xor ecx,ecx; mov cl,[eax+0xc]; mov edx,ecx; mov ecx,[edi+0x13]; add ecx,edx`
(byte load first, then a register-to-register copy). With the ternary, msvc6
loads the dword first and drops the copy, costing exactly the 2 bytes of
`mov edx,ecx` and every byte after it. Fifteen rewrites of the add itself
(operand order, separate `cur`/`prod` locals, `unsigned char` vs `int` carrier,
`volatile` on either operand, pointer aliases, statement splits) all produced
the dword-first form; only the clamp spelling moved it. That took the function
from 195/242 to RELOC 242/242.

`if (sum < 0) sum = 0;` also emits the byte-load-first pair, but as
`add ecx,edx; jns` instead of the mask, so it fixes the loads and breaks the
clamp. Read which of the three forms the target uses before choosing.

Generalisation: when a diff shows the right instructions in the wrong order
just *before* a clamp or a select, treat the clamp spelling as the lever. The
operand that ends up in a register is chosen along with the code that consumes
it, not independently of it.

## 27. A volatile byte read defeats the byte/dword load merge on one slot

Reading a `char` parameter as a byte and then re-reading the same slot as a
dword normally merges into one dword load. Making only the byte read
`volatile` keeps both:

```c
result = *(volatile char*) &stat_value;          /* mov bl, [esp+8]   */
if (result == 0) { ... }
result += (char) f((float) (*(int*) &stat_value & 0xff) >= k ? 0xb : 6);
                                                  /* mov eax,[esp+8]  */
                                                  /* and eax,0xff     */
                                                  /* mov [esp+8],eax  */
```

`gm_RandomStatModifier` (0x10018450) needs exactly this: `bl` holds the signed
byte for the guard and the final `add bl,al`, while the masked dword is homed
back in the parameter slot for `fild` to read. Every non-volatile spelling
(`(unsigned char) v`, an `int uv` temp, `*(int*)&v & 0xff`, masking through the
parameter, an `int` parameter) folded the two reads into one `mov ebx,[esp+8]`,
which loses the `mov bl` and everything downstream: 32/78.

The second half of the fix is the result shape. `v += f(...)` compiles to
`add al,bl` (result in `al`), but the target ends `add bl,al; mov al,bl`:
the accumulator is the *named* variable, not the call result. Assigning the
same local in both arms of an `if`/`else`, rather than returning from the first
arm, produces that:

```c
result = *(volatile char*) &stat_value;
if (result == 0)
	result = (char) (f(0x2a) + 0x15);
else
	result += (char) f(...);
return result;
```

Both together: RELOC 78/78. `.scratch/work/p1.c` through `p7.c` hold the
thirteen spellings that do not work.

## 28. Constant CSE in a straight-line store block has no source lever

`gm_StartFilteredEntitySearch` (0x100170e0) opens with nine global stores; the
reference hoists `0xff` into `cl` and parks zero in `edx`, reusing both. Hoisting
the constants into locals does not reproduce it. `char ff = 0xff`, `int zero =
0`, both together, either alone, `int`/`unsigned char`/`volatile` carriers, `ff`
derived from a shared `-1`, and moving the two `0xff` stores adjacent all
compile to output byte-identical to the literal form: msvc6 re-materializes a
constant at each store site and picks its own register for the parked zero.

Constant sharing is decided after the source-level temps are folded away, so
there is no C spelling for it. Treat a diff whose only differences are
`mov [addr],imm` against `mov [addr],reg` in a store block the same way as
section 25's register naming: check for real structure elsewhere first.

## 29. Hoist a common addend out of a select, and let the select assign the result

Where a three-way select picks a base pointer and every arm adds the same
offset, the target computes the offset once at the merge:

```
mov eax,[esp+0x10] ; test eax,eax ; jne merge
mov eax,[esp+4]    ; test eax,eax ; jne merge
mov eax,[esp+8]
merge: mov ecx,[esi+0x14] ; add eax,ecx
```

Repeating the add in each arm costs three loads and three adds
(`cm_ExChangeBits` 0x1000eaa0, 96/209 with a size overrun). Hoisting it closes
most of the gap, but *which* local the arms assign then decides the register:

```c
/* 202/208: pointer ends up in ecx, target holds it in eax */
if (resolved != 0) sel = (char*) resolved; else ... ;
puVar3 = (unsigned int*) (sel + *(int*) (base + 0x14));

/* 208/208 RELOC: the select assigns the result variable itself */
if (resolved != 0) puVar3 = (unsigned int*) resolved; else ... ;
puVar3 = (unsigned int*) ((char*) puVar3 + *(int*) (base + 0x14));
```

`sel += off; puVar3 = sel;` also scores 202: the intermediate local is what
pins the value in ecx, not the syntax of the add.
`src/server.dll/DieGildeAddOn/command/command_c/cm_ExChangeBits.c:49`.

Same function, second lever: a read-modify-write spelled
`v = *p & ~mask; *p = v; *p = val | v;` caches the masked value in a register,
where the target re-reads through the pointer. Writing both statements against
memory (`*p = *p & ~mask; *p = val | *p;`) drops one instruction per block.
Three size cases fixed the same way took 126/208 to 202/208.

## 30. `volatile` at the load site defeats displacement folding

msvc6 folds a constant field offset into a scaled load,
`mov al,[esi+eax*4+0x247]`, where the target materializes the record address
first:

```
lea eax,[esi+eax*4]
mov al,[eax+0x247]
```

How the address is *built* does not change this. Probed against
`cm_GetBuildingStatCount` (0x100104a0), all scoring 41/135: an int-typed
address local, a struct pointer with the field at 0x247, a `char(*)[0x24d]`
row pointer, `&tbl[i * 0x24d]`, `(tbl + 0x247)[i * 0x24d]`, a compound `+=`,
a `uint` offset local, and `/O1 /Ox /Og /Oxs` plus `/G3`-`/G6`.

Reading through `volatile` at the point of use forces the address into a
register:

```c
building_tier = *(volatile char*) (type_entry + 0x247);   /* 41 -> 118/135 */
```

`src/server.dll/DieGildeAddOn/command/command_c/cm_GetBuildingStatCount.c:85`.
Qualify the load only; a `volatile` *pointer* local spills through the stack
instead. Section 10's load scheduling then applies on top: moving the
neighbouring `*(int*)(param_1 + 0x65)` read ahead of the volatile load took it
to 121/135.

Same lever, opposite outcome in `sim_StartEntityQueryByType` (0x10015460): the
`volatile` does emit the target's `lea`/`mov` pair, but costs the esi/edi
assignment that keeps the argument and table base live across four calls, so
the score stays at 10/145. Measure the whole function, per section 18.

## 31. A pointer sweep with a separate index beats an indexed walk

A scan that tests fields at a stride and returns an address derived from the
index compiles to two different loops. Indexing rebuilds the record address in
the body; the target walks a pointer against an end address and carries the
index only to compute the result:

```c
/* 12/98: address rebuilt per iteration */
for (i = 0; i < 0x300; i++) {
    p = (char*) 0x100358a2 + i * 0x21c;
    ...
}

/* 98/98 EXACT */
r = NULL;
if (arg1 == 0) {
    return r;
}
i = 0;
p = 0x100358a2;
while (p < 0x1009aca2) {
    ...
            r = (char*) (0x100358a0 + i * 0x21c);
            break;
    ...
    p += 0x21c;
    i++;
}
return r;
```

`src/server.dll/DieGildeAddOn/game/spiel622.c:608`, fixing
`gm_FindEntityByOwner`.

Three details are each load-bearing, measured separately:

- **`int` for the walking pointer**, not `char*`. The target's bound compare is
  signed (`jl`); a `char*` compares unsigned (`jae`).
- **`while`, not `do`/`while`.** The `do` form emits `jge` past the loop plus a
  `jmp` back to the top, two instructions where the target has one `jl`.
- **A result local zeroed before the argument test.** It lets both no-match
  exits share one `xor eax,eax`, and raises pressure enough to put the argument
  in edi and the index in esi, matching the target. With an early
  `return NULL` and no result local the function uses one saved register and
  the wrong roles.

The result local must be set before the guard (`r = NULL; if (arg1 == 0)
return r;`). Assigning it after an `if (arg1 == 0) return NULL;` emits the push
order `esi, edi` against the target's `edi` followed by a lazy `esi` inside the
loop, and scores 0/98 despite an otherwise instruction-identical body.

## 32. PROVEN is not a byte match, and it hides tractable work

`PROVEN` records that a symbolic prover showed the C semantically equivalent
to the target. It says nothing about the emitted bytes: every PROVEN entry in
this project carries `delta > 0`, from 1 byte to over 1800.

Those functions were never *attempted* as byte matches, only proven and set
aside, so the ordinary causes in this document still apply to them untried.
Twelve converted to EXACT/RELOC in one session, several from a single
statement swap.

Read the verify summary's `byte_matched` field (EXACT + RELOC) rather than
`passed`, which counts PROVEN as done via `metadata.MATCHED_STATUSES` for
coverage accounting.

Rank the remaining ones by `delta` and start at the top:

```sh
rebrew verify --json 2>/dev/null > .scratch/v.json
jq -r '.results[] | select(.status=="PROVEN")
       | "\(.delta)\t\(.va)\t\(.size)\t\(.match_percent|floor)%\t\(.filepath)"' \
   .scratch/v.json | sort -n
```

A small delta on a large function means a long correct prefix and one late
cluster. A low match percentage on a small function means it diverges near
instruction 0. Both are more tractable than the percentage suggests, because
`match_count` does not realign after an insertion (section 16).

## 33. Statement order decides which register holds a value

Recurring across the conversions: when two reads feed different consumers,
the one you write first claims the register the target expects.

In `GetCommandPayloadSize` (0x1000c710) the target keeps a switch byte in
`dl` and a loop index in `ecx`. Assigning the cursor, whose initializer reads
the switch byte, *before* reading the count pins the byte in `dl` and closed
a 10-byte gap. Reversing the two statements scores 742 of 752.

This is the same mechanism as section 9 (register roles follow order of first
use) seen from the source side: reordering two adjacent, independent
statements is often the whole fix. Try it before reshaping anything.

Corollary: treat existing "unreachable" comments as unverified. Three in this
codebase were wrong, including one claiming a function needed "the original's
exact CL.EXE build" when a single statement swap closed it.

## 34. RELOC can hide a wrong global: check `~~` operands against the symbol

`rebrew diff` marks an instruction `~~` when it differs only in a relocation
slot, and `rebrew test` counts `~~` as a match. The mask covers all four
operand bytes, so an instruction referencing *the wrong global* still scores
`~~`, and a function built entirely from such instructions reports RELOC with
`match_count == total` while being semantically wrong.

Hit in `cm_ExModifyStat` (0x100100a0). The reference's third compare is
`fcom dword ptr [0x100256a4]` (`_g_stat_max`, 252.0). Spelling the retest
`v >= _g_stat_min` emits `fcom dword ptr [0x100256cc]` (`_g_stat_min`, 0.0);
every other byte agreed, so the diff went green at 159/159 RELOC. The two are
not equivalent: for `min < v < max` the reference stores `v` and that
spelling stores `max` (wrong for v = 1, 100, 251 at the shipped 0.0/252.0
bounds).

Guard for it: whenever a `~~` instruction carries a global operand, read the
reference's operand address out of `.target.bytes` (little-endian
displacement) and check it against `src/server.dll/rebrew_globals.h` or the
raw image. Two same-typed globals sitting near each other in `.rdata` make
this easy to hit, and RELOC gives no signal at all.

```bash
rebrew diff <VA> --json | jq -r '.instructions[] | select(.match=="~~") |
  "\(.index) \(.target.bytes) \(.target.disasm)"'
```

Distrust a RELOC that arrives from changing *which symbol* an expression
names rather than from changing code shape.

## 35. Row multiply vs offset accumulation decides strength-reduction fallout

A loop that walks fixed-size rows can be written two ways, and msvc6 treats
them differently even though both emit the same induction register:

```c
off = 0;  do { ... base + off ... ; off += STRIDE; } while (off < LIMIT);
row = 0;  do { ... base + row * STRIDE ... ; row++; } while (row < COUNT);
```

The multiply form hands msvc6 a `row * STRIDE` to strength-reduce, and the
reduction runs before the surrounding scheduling decisions. Two consequences,
both observed closing functions that were 3 bytes short:

**SIB base/index roles.** In `gm_Open` (0x10015950) the reference addressed the
producible-count table as `[esi+eax+0x21]`, counter as SIB *base* and reloaded
table pointer as *index*. The accumulating form emits `[eax+esi+0x21]`, and no
addend-order swap, array-subscript spelling, or cast changes it: the roles come
from the induction variable's form. Counting rows and spelling every access as
`g_entity_type_table + row_index * 0x24d + disp` gives the counter the base
role and closed the function (858/861 -> 861/861 RELOC).

**Preheader instruction order.** In `ExecuteOfficeAssignment` (0x1000b4d0) the
reference emitted `not edx; mov eax,0x10035a6c` and a pointer-cursor loop
emitted the two the other way round. Rewriting the sweep as
`*(int*) (0x10035a6c + row * 0x21c)` over `row < 768` put the `not` first and
closed it (829/836 -> 836/836 RELOC). A byte-offset counter also emits `not`
first but recomputes the bound with a `lea`/`cmp` pair and is longer.

Derive `COUNT` from the addresses rather than assuming it: for that sweep,
`0x1009ae6c - 0x10035a6c = 0x65400 = 768 * 0x21c`.

When a loop is a few bytes short and the residue is addressing-mode or
scheduling noise around the induction variable, switch the loop between these
two forms before probing anything else.

## 36. The outer call's argument form can fix a whole-function register swap

Two callee-saved values can end up in each other's registers across an entire
function, with every instruction otherwise correct. In
`gm_SumBuildingProductionValues` (0x100198b0) the reference kept the query
result in esi and the table cursor in edi; our compile had them swapped at 12
sites, and every lever aimed at the *cursor* (declaration order, `register`
qualifiers, retyping, init order, loop-bound shape, end-pointer bounds) left
the pair untouched.

The lever was the first argument of the call that *defines* the query:

```c
q = gm_StartEntityQuery(...);
q_slot = *q;                                    /* int local */
total = ... gm_CalculateProductionValue(q_slot, *(unsigned char*) ((char*) q + 0x12)) ...;
```

Reading `*q` into a local and passing the local, instead of passing `*q`
directly, moved the query into esi and the cursor into edi, and reproduced the
reference's `mov dl,[esi+0x12]` / `xor eax,eax` / `mov ax,[esi]` read order.

The local's width matters. The natural `unsigned short` emits an
`and eax,0xffff` widen and reorders the two field reads (SIZE_MISMATCH, 167 of
355). An `int` local is exact. See also §16 on local width.

Before hoisting a value out of an argument list to fix register naming, check
whether hoisting one out of a *different* call fixes it instead: the hoist that
fixes the names may cost the argument schedule at the site you hoisted from.
Here the earlier fix hoisted the inner call's `q+0x14` load, which fixed the
names but cost 5 bytes of schedule; hoisting at the outer call fixed the names
and left the inner call's `push eax` / `mov eax,[esi+0x14]` / `push eax`
schedule intact.

## 37. A dead parameter slot can home more than one byte

Section 14 homes one value in an incoming parameter's own slot. The slot is
four bytes, and the *other* bytes of it are usable homes too. That matters when
the frame is one dword too large because a single byte value needs a spill.

`ValidateAndAssignOffice` (0x1000b290) reads a holder byte
(`g_office_slots[i].b`) before a scan loop and uses it after. The reference
keeps it in `al` across the loop; every C shape that carries it in a local puts
it in `cl`, which the loop's cursor clobbers, so msvc6 spills it to a fresh
dword and the frame is `sub esp,0x1c` against the reference's `0x18`. The whole
prologue then sits one slot off and the positional compare collapses.

`arg1`'s slot is already dead (a `cmd` local holds the pointer) and byte 0 of
it homes the requested-office byte. Homing the holder byte in byte 1 of the
same slot removes the spill:

```c
x6 = cmd[6];
*(unsigned char*) &arg1 = x6;                       /* byte 0, section 14 */
if (g_office_slots[i].b != x6)
	return 0;
((unsigned char*) &arg1)[1] = g_office_slots[i].b;  /* byte 1, no spill dword */
/* ... scan loop ... */
b = ((unsigned char*) &arg1)[1];
```

`src/server.dll/DieGildeAddOn/game/aemter.c:206`. It emits `sub esp,0x18` with
`push ebx/ebp/esi/edi` intact in the prologue, aligning instructions 0-35
(prologue, entity lookup, all three guards and the whole first scan loop), and
took the function from 187 to 191 of 425.

Two things this supersedes, both previously recorded as ceilings:

- "No probed ordering keeps the 0x18 frame and the prologue push together"
  (17 shapes). The byte-1 home does both.
- "The extra dword is one spilled byte value and every C shape spills it."
  Correct on the diagnosis, wrong that it was unavoidable: the byte needs a
  *home*, not a register, and a dead slot already in the frame is one.

Which byte you pick matters (byte 2 loses the frame), and the store's position
in the emitted stream does not follow source order: writing it before the
sibling read, after it, or before the byte-0 home all place it identically.

## 38. msvc6 shrink-wraps, and the lever is loop register demand

A target that pushes one callee-saved register at entry and the rest later,
interleaved with loads past the early-exit guards, is not using an idiom that
is out of reach from C. msvc6 defers a `push` to the first block that needs
the register whenever few enough callee-saved values are live across the
guards:

```c
int __cdecl m(void)
{
    int a, b, c, d;
    if (ga == 0) return 0;          /* early exits reached with no push */
    if (gb > 0x100) return 0;
    a = gc; b = gd; c = ge; d = gf; /* push ebx/esi/edi emitted here */
    while (a < 100) { a += b + c + d + ga; b += gb; c += gc; d += gd; }
    return a + b + c + d;
}
```

emits `test/jne/xor eax,eax/ret` before any push, then `push ebx; mov ebx,...;
push esi; mov esi,...; push edi`. `.scratch/w_l2/m1.c`; `m2.c` and `m3.c` show
the same with one register (`esi`) live from entry, which is the exact shape of
`FindNextFilteredEntity` (0x10016f80) and `gm_NextEntityQueryMatch`
(0x10016290).

The threshold is real and low. `m4.c` differs from `m3.c` only in carrying two
more values through the loop, and that alone collapses the head back to pushing
at entry and adds a frame. So when a function will not split its prologue, the
lever is reducing how many callee-saved values the *loop* needs, not respelling
the entry: every entry reshape probed on both functions above (statement
permutations, `!p` against an explicit null compare, testing the global
directly, returning a literal against returning the pointer, aliasing, sinking
the initialisers below the guards) is inert while the loop demand stands.

Corollary for bisecting: delete the loop and recompile. If the head then
matches the target, the entry spelling is already right and the loop is the
blocker. Adding the loop back one block at a time locates the flip precisely.
On 0x10016290 that isolated it to a single `if (g_flag) is_match = 1;` joining
a scan loop and an early return (`.scratch/w_l2/g/k1.c` against `k2.c`), which
no amount of entry rewriting could have found.

## 34. SIB base/index roles follow the induction variable's form

When the target and the candidate differ only by which register is base and
which is index in the same addressing mode (`[esi+eax+0x21]` against
`[eax+esi+0x21]`), reordering the addends in the C expression does nothing.
MSVC 6.0 decides the roles from how the loop advances.

- Accumulating a byte offset (`off += 0x24d`) gives a reloaded table pointer
  the base role.
- Counting rows and spelling the address as `table + row * 0x24d + disp`
  hands the compiler a multiply to strength-reduce, which gives the counter
  the base role.

Three such swaps in `gm_Open` (0x10015950) closed it at 861/861 after the
addend-order approach had been tried and failed. The same swap in
`SpawnGraveyardEntities` (0x10010850) came instead from removing a
semantically dead `if (count > 0)` wrapper around a `while` loop that already
tested it: the extra nesting raised register pressure enough to flip the
roles.

A read-modify-write in the same loop may additionally need its address held
in a pointer local used for both the load and the store; otherwise msvc6
emits a `lea` plus separate `[reg]` accesses.

## 35. PROVEN status is lost by a STUB result, and that is a real regression

`rebrew verify` overlays a metadata `PROVEN` status onto a byte result only
when that result is `NEAR_MATCHING` or `SIZE_MISMATCH` (`verify.py:1325`).
A `COMPILE_ERROR`, `MISSING_FILE`, or `STUB` result means the source no
longer builds or the annotation moved, so the proof is treated as stale and
the function is reported as failing.

Chasing `match_count` can therefore make a function worse. Twice in one
session an edit raised the positional score while dropping the status to
STUB; one of those had introduced a genuine semantic bug (scanning a fixed
element instead of the walking cursor), which is exactly what the proof had
ruled out.

When editing a PROVEN function, treat its status as the floor: a higher
percentage that lands on STUB is a loss, not a gain. Revert to baseline
instead.

## 36. Relocation masking can hide a wrong symbol: the false RELOC

`rebrew diff` masks the 4-byte relocation slot, so an instruction whose only
difference lies inside that slot is reported `~~` and counted as a match. A
function can therefore reach RELOC with `match_count == total` while
referencing the **wrong global, wrong string, or wrong call target**: the
address bytes differ, but the diff cannot see them.

Two confirmed instances:

- `cm_ExModifyStat` (0x100100a0): spelling a bound test `v >= _g_stat_min`
  scored a clean 159/159 RELOC, but the original compares `0x100256a4`
  (`_g_stat_max`, 252.0) where that spelling compares `0x100256cc`
  (`_g_stat_min`, 0.0). Not equivalent for any value strictly between the
  bounds. Rejected.
- `gm_Open` (0x10015950): two `LogMessageInternal` calls passed invented
  German text (`"gm_Open(): Spieler initialisieren"`,
  `"gm_Open(): Gebaeude-Daten"`) where the binary holds
  `"gm_Open(): St\344dte"` at `0x10031204` and `"gm_Open(): Geb\344ude"` at
  `0x100311f0` (Latin-1 `0xe4`). The strings sit behind relocation slots, so
  the function scored RELOC 861/861 with the wrong log output.

**Before trusting a RELOC, resolve every `~~` operand.** Our object is
unlinked, so its slot holds only the addend while the original's holds
`symbol_va + addend`; subtracting gives the symbol VA, which
`src/server.dll/rebrew_globals.h`, `db/server.dll_functions.csv`, and
`src/rebrew-data.toml` can name. For string literals, read the bytes at the
original's address straight out of the binary and compare.

An audit of 19 recently converted functions resolved all 211 masked
instructions and found the single `gm_Open` defect; the other 18 were clean.
Non-ASCII text belongs in octal escapes (`\344`) so the source stays ASCII
and the byte value is unambiguous.

## 39. A volatile argument read defers a parameter load past the prologue pushes

When the target loads two incoming parameters in one order and msvc6 picks the
other, the cause can be a load that floated *above* the callee-save pushes. The
reference reads the parameter it needs at the call site first, so that value
claims the register pushed first; msvc6 hoists the dereference of the *other*
parameter into the prologue, and that parameter wins the register instead.

`gm_AllocBuildingContents` (0x10017c40) opens with

```
push ebx; push ebp; push esi; mov esi,[esp+0x14]; push edi; mov edi,[esp+0x14]
push 1; push esi; mov ecx,[edi+1]; push ecx; call gm_AllocObjekt
```

so `obj_id` lands in esi and `geb` in edi. Ours hoisted the `geb+1` load into
the prologue (`mov ebp,[esp+0xc]` before the first push), which put `geb` in
ebp and pushed `obj_id` down. A volatile read at the argument defers it:

```c
obj = (char*) gm_AllocObjekt(*(volatile int*) (geb + 1), obj_id, 1);
```

`src/server.dll/DieGildeAddOn/game/spiel_c/gm_AllocBuildingContents.c:107`,
672 -> 677 of 742 with the object size unchanged.

This is section 8c's residency/ordering distinction applied to an argument
rather than a field pair: the qualifier belongs on the *load that must stay
put*, not on the variable. Qualifying the local (`char* volatile`), the other
parameter's byte read, or the value the loop consumes all rebuild the frame
instead (`abc_x1`/`abc_z1`, 113/751 and 68/760).

The lever is not universal. On `FindSlotEntryFiltered` (0x10010710) the same
trick applied to the competing `entity+0x65` load delays the load but flips the
push order (`push esi` before `push edi`), losing five bytes for no register
gain: 263 -> 249 of 320. Check the push sequence in the diff, not just the load
position, before keeping it.

## 40. A struct assignment breaks a register tie without changing a byte

Section 9a breaks an esi/edi tie by shortening a live range. When that has
nothing left to shorten, the other side of the tie is the *reference count*:
how many times the source names each candidate. A struct assignment lowers
that count without changing the emitted instructions.

`ls_LoadSavegameHeader` (0x10012470) passes `stream` and `dest` to the same
reader ~25 times, then writes a three-field tail from three globals. Two
shapes each got one half of the target right and neither got both, across
eight prior rounds:

- a hoisted `tail = dest + 0x9c` local restored the target's esi/edi roles but
  lost its duplicated `add edi,0x9c` and its memory-form version compare
  (819/857);
- `dest += 0x9c` inside each tail arm restored both of those and reached the
  exact 857-byte size, with every instruction, operand and branch offset
  correct and only esi and edi exchanged at 56 sites (801/857).

The second shape names `dest` three times in the else arm:

```c
	dest += 0x9c;
	*(int*) dest = g_1002d4f0;          /* 3 references to dest */
	*(int*) (dest + 4) = g_1002d4f4;
	*(char*) (dest + 8) = g_1002d4f8;
```

One packed struct assignment emits the identical bytes (`mov edx,[g];
add edi,0x9c; mov [edi],edx; mov eax,[g+4]; mov [edi+4],eax; mov cl,[g+8];
mov [edi+8],cl`, verified in isolation) while naming `dest` once:

```c
#pragma pack(1)
struct SaveHeaderTail { int a; int b; char c; };
#pragma pack()
extern struct SaveHeaderTail g_save_header_tail; /* 0x1002d4f0 */

	*(struct SaveHeaderTail*) (dest + 0x9c) = g_save_header_tail;
```

That alone moved `dest` into edi and `stream` into esi, closing the function
at RELOC 857/857.
`src/server.dll/DieGildeAddOn/loadsave/loadsave_c/ls_LoadSavegameHeader.c:24`.

`#pragma pack(1)` is required: the natural layout pads the trailing `char` to
a 12-byte struct and copies 12 bytes, costing 2 bytes (855/857).

Diagnostic for this class: when the diff is *only* a register exchange and
every live-range lever is exhausted, count how many times each candidate is
named in the source and look for a construct that says the same thing with
fewer mentions. Struct assignment, a single `memcpy` of a field group, and an
array store through one base all qualify.

The lever is not universal, and it is not a general "fold the stores" rule.
On `AcceptConnections` (0x1000a080) the same packed-struct assignment applied
to its adjacent `[slot+0x2641f8]` / `[slot+0x2641fc]` pointer stores does
change the emitted bytes: it folds the second `lea` and misses the size
(495/600 at obj 599, against 546/600 for the plain pair). Verify the struct
form emits the same instructions in an isolated probe before keeping it.

## 41. Two levers that each regress can be exact together

A shape change that lowers `match_count` is not necessarily wrong. When it
fixes the instruction stream but leaves the object one byte off, the score
collapses positionally (section 19) and hides a real structural gain. Track
`obj_size` and the `**` count alongside `match_count`, and when a change lands
one byte away from the target size, look for a second change that supplies
exactly that byte rather than discarding the first.

`gm_AllocBuildingContents` (0x10017c40) sat at NEAR_MATCHING 677/742 for nine
prior batches with 18 residual `**` in two clusters that were recorded as
separate register-role problems: the scan cursor built as `lea ecx,[ebp+0x25]`
where the reference splits the row base and the cursor, and `geb` living in
ebp where the reference uses edi.

Advancing the cursor before the read, rather than reading through a
displacement and then advancing,

```c
	scan = row + 0x23;
	comp = *(unsigned short*) scan & 0x7fff;
	if (comp != obj_id) {
		do {
			scan += 2;
			comp = *(unsigned short*) scan & 0x7fff;
			i++;
		} while (comp != obj_id);
	}
```

emits the reference's `lea ebp,[eax+edx*4]` / `lea eax,[ebp+0x23]` pair and
raises exact instructions from 203 to 210, but scores 131/743: one byte long,
because `geb` still occupies ebp and `mov cl,[ebp]` needs a displacement byte
(`8a4d00`) that the reference's `mov cl,[edi]` (`8a0f`) does not.

Computing the row before zeroing the counter,

```c
	row = g_entity_type_table + (unsigned char) geb[0] * 0x24d;
	i = 0;
```

frees ebp for the row base. On its own it is 167 at obj 741, one byte short.
Applied together the two are exact: RELOC 742/742.

`src/server.dll/DieGildeAddOn/game/spiel_c/gm_AllocBuildingContents.c:107`

The two clusters were one fault. With `i = 0` first, msvc6 has ebp tied up and
folds the row+0x23 displacement into the first read; freeing ebp and advancing
the cursor before the read clears both at once. Where a function's notes list
several independent register-role clusters, test whether one allocation
decision explains all of them before treating them as separate problems.

The converse holds and is the trap: a lever that removes `**` while changing
the size must not be kept alone. Re-measure the pair.

## 42. The number of reaching definitions decides load/store scheduling

Where a value reaches a block from two assignments written in *different*
forms, msvc6 keeps them as two definitions and schedules conservatively around
the merge: stores that use the value issue before any independent load. Write
both assignments as the same base+index expression and it treats them as one
value, and the scheduler is free to hoist an unrelated load above them.

`AcceptConnections` (0x1000a080) picks a connection slot in a search loop and
falls back to a fixed record when the search fails:

```c
	slot = (unsigned char*) 0x101deb00 + i * 0x264264;   /* search hit */
	...
	slot = (unsigned char*) 0x114ffe20;                  /* fallback   */
```

Far below, past a 0x2000-iteration loop, it stores two pointers into the slot
and calls `sprintf` with four bytes of a `sockaddr`. The reference issues the
first byte load *before* either pointer lea:

```asm
mov  edx,[esp+0x1f]          ; addr[7], first
lea  eax,[esi+0x154]
lea  ecx,[esi+0x132154]
mov  [esi+0x2641f8],eax
mov  eax,[esp+0x1e]          ; addr[6]
and  edx,0xff                ; mask deferred past the store
mov  [esi+0x2641fc],ecx
```

No spelling of the argument list reproduces it: comma expressions in any
argument slot, `volatile` on either store pair, struct-block assignment, and
hoisting the bytes into locals all leave both leas above the first load (about
thirty shapes, `.scratch/l2x/mk*.py`). The lever is at the *definition* site.
Writing the fallback in the same expression shape as the search hit,

```c
	slot = (unsigned char*) 0x101deb00 + 8 * 0x264264;   /* == 0x114ffe20 */
```

emits the reference's order exactly, verified in isolation with the real
search, the real loop and the real tail (`.scratch/l2x/p9.c:m3`,
`.scratch/l2x/pa.c:n1`).

Two details matter when reaching for this:

- **The cast has to stay inside.** `(unsigned char*) (0x101deb00 + 8 *
  0x264264)` folds to the literal at compile time and changes nothing; the
  arithmetic must be on the cast pointer for the two definitions to match.
- **It extends the index's live range.** In `AcceptConnections` the join sits
  above the `accept()` call, so `i` survives the call, the accept result
  spills to a new frame slot, and the frame grows 0x118 to 0x11c: the cluster
  aligns but 130 downstream instructions shift, 546/600 down to 177/600. It is
  only a win where the merge is not separated from its uses by a call.

The general rule is worth more than the case: when a scheduling difference
sits far from anything the source seems to control, count the definitions
reaching the block instead of rewriting the statements next to the divergence.

## 43. `and eax,0xff` is one byte shorter than the same mask on any other register

The mask against 0xff has an accumulator-specific short form: `and eax,0xff`
assembles as `25 ff 00 00 00` (5 bytes), while `and edx,0xff` needs the ModRM
form `81 e2 ff 00 00 00` (6). A byte value that msvc6 parks in eax therefore
makes the object one byte shorter than a reference that masks the same value
in edx or ecx.

This shows up as a persistent `obj_size` deficit of exactly one that no
statement reordering fixes. In `AcceptConnections` every hoist that produced
the reference's load-first schedule landed at obj 599 for this reason alone
(sixty builds: each of the four `sockaddr` bytes, four declared types, every
placement against the surrounding stores, `.scratch/l2x/mk4.py`).

When a candidate is one byte short and the diff shows a mask, compare the mask
encodings before assuming an instruction is missing. Section 19's warning
applies in reverse here: the positional score collapses downstream, so a
one-byte encoding difference reads as a structural one.

## 44. `#pragma optimize("a", on)` reorders a field read against a store

MSVC6's `"a"` flag (assume no aliasing) is a per-function lever in the same
family as section 13's `"y"`, and it moves scheduling, not just addressing.
Where the target reads one struct field and stores to another in the opposite
order from the candidate, `"a"` is the difference: without it msvc6 must assume
the store may alias the read and keeps source order.

In `AdvanceGameClock` (0x100155c0) the target emits

```
xor esi,esi; mov si,word ptr [ecx+4]; mov dword ptr [ecx+6],edx
```

and every source spelling that hoisted the `x04` read above the `x06` store
either left the pair transposed (187/197) or re-folded an earlier carry and
collapsed to 87. Wrapping the function in `#pragma optimize("a", on)` emitted
the target's order with no source change at all, 187 to 194/197.

```c
#pragma optimize("a", on)
void __cdecl AdvanceGameClock(SIM_CLOCK* clock, int arg2, int arg3, int arg4)
{
	/* ... */
}
#pragma optimize("", on)
```

Close with `#pragma optimize("", on)` as in section 13; file-mates are
unaffected (the other five functions in `sim.c` held their status). `"w"`
scores the same here, `"g"`, `"p"` and `"t"` are inert, and `"s"` and
`-"t"` collapse the body to 142 bytes.

Reach for this when the diff is a pure transposition of a load and a store to
the same object and no statement order reproduces it: the obstacle is the
aliasing assumption, which no C spelling can express.

`src/server.dll/DieGildeAddOn/game/sim.c:251`

## 45. Merging duplicated tail stores sinks a loop store below the decrement

Two exits that write the same value to the same field, one inside an `if` with
a `return` and one at the end of the function, cost more than the duplicated
store: they change how the preceding loop schedules.

`AdvanceGameClock`'s second loop had to emit

```
mov esi,[ecx]; dec esi; dec edx; mov [ecx],esi; jne
```

with the store *after* the counter decrement. With a `return` inside the
`minutes < 0` branch the store landed ahead of `dec edx` in every one of ~30
body spellings (194/197): plain, `volatile` on the store, an `int*` alias, a
value local, `--days`, `days--`, an explicit `break`. Deleting the branch's
duplicate store and its `return`, so both paths fall through to one tail
`clock->x04 = (unsigned short) minutes;`, sank the store below the decrement
and took the function to 197/197 EXACT with no other change.

Section 7 covers merging *sequential returns* for branch polarity; this is the
scheduling consequence of the same edit. When a loop store is one slot early
and the loop's body resists every rewrite, look at what follows the loop.

`src/server.dll/DieGildeAddOn/game/sim.c:294`

## 46. The x87 `fxch` slot and a folded byte compare are set by one type choice

Where a float scaled by a constant meets an integer byte compare in the same
scheduling region, msvc6 decides both the `fxch st(1)` position and whether the
compare folds from the *type of the local that holds the scaled value*. The two
cannot be steered apart.

`gm_CalculateProductionValue` (0x10019720) needs

```asm
fmul   qword ptr [0x100257d0]
fxch   st(1)
cmp    byte ptr [esi], 0x17
fmulp  st(1)
```

Scaling through a `float` local folds the compare into `cmp byte ptr [esi],0x17`
but schedules it ahead of the `fxch`:

```c
mod_value = (float) ((double) mod_value * g_const_57d0);
value = (float) (acc * mod_value);            /* cmp; fxch  -> 391/396 */
```

Scaling through a `double` local puts the `[esi]` access after the `fxch`, as
the target does, but msvc6 then keeps the byte in a register and emits
`mov al,[esi]` plus a later `cmp al,0x17`, one byte longer:

```c
p2_wide = (double) mod_value * g_const_57d0;
value = (float) (acc * p2_wide);              /* fxch; mov al -> obj 397 */
```

A `volatile` store to the float result lands the `fxch` correctly too, but
sinks the compare two slots, past `fmulp` and `fstp` (387/396).

The `fxch` itself is a removable stack fixup, not a fixed instruction. Making
the scaled double the destination of the merge multiply drops it and shortens
the object by two bytes:

```c
acc = (double) mod_value * g_const_57d0;
mod_value = (float) (acc * quot);             /* no fxch -> obj 394 */
```

So the question is never how to move the `fxch`, but why the folded compare is
ranked ahead of it. Every measured shape falls into one of four classes, and the
target's `fxch; cmp` is in none: `cmp; fxch` (391), `fxch; mov al` (obj 397),
`fxch; fmulp` with the compare sunk past `fstp` (387), and no `fxch` at all
(394 or 385, the latter keeping the non-popping `fmul st,st(1)`).

Inert here, and worth skipping on a similar diff: every CFLAGS variant (`/G3`
`/G4` `/G5` `/GB` `/Ox` `/Ot` `/Oa` `/Ow` `/Gy` `/Oi-` `/Ob1` `/QIfdiv-` `/GX`
`/GR` `/Gs` `/GF` `/Gf` `/Zp1` `/Ob2` `/Oi` `/Og` `/Gi` emit byte-identical
objects, compared as hex rather than by score), 20 `#pragma optimize`
combinations plus dropping the pragma entirely (which holds the same order at
383, so this site and the section 44 epilogue lever are independent), all four
msvc6 service packs, 14 declaration orders, every compare spelling and branch
shape, the compare's pointer provenance, reading the byte at the top of the
function, a double accumulator in the arms, duplicating the scale into both arms
(msvc6 duplicates the `fmul` rather than cross-jumping, so the merge block
boundary does not move), eight nested association trees, and 942 generated tail
permutations. Section 8b's `volatile` read defeats the fold but also moves the
load, so it does not separate the two either.

When a diff is a single adjacent transposition of an FPU stack op and an
integer compare, check whether the two are coupled through one type choice
before spending a pass on statement order.

`src/server.dll/DieGildeAddOn/game/spiel622.c:232`, search scripts in
`.scratch/pv-x87/` and `.scratch/spiel622-x87/`.
