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

`src/server.dll/DieGildeAddOn/game/friedhof_logic_c/gv_HireProductionWorker.c:15,72`

One declaration fix corrected four functions: `gv_HireProductionWorker`
(0x100111b0), `gv_ExtendProductionTime` (0x100113b0),
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
width the disassembly implies rather than defaulting to `int`. The widening
mask itself is a `volatile` tell rather than a width tell: check section 52
before retyping the load.

## 7. Branch polarity: merge sequential returns

Two consecutive guards returning the same value compile to two epilogues:

```c
if (!slot) return -7;
if (a != b) return -7;
```

The target had one. A short-circuit merge produces the single shared exit and
flips the branch sense (`jne` to `je`):

```c
	slot = gv_GetSlotEntry(workers, *(int*) ((char*) req + 0xc),
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
before tuning anything else. When the residual is a back-edge encoding rather
than an epilogue count, section 57 is the discriminator.

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
	count = g_worker_entry_count[*(int*) ((char*) req + 0xc)];
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

`m_init` (0x100068e0) emits a head-alignment prelude:

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
`m_init` is exactly this conflict: the target's frame pointer needs
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
conflict: `m_init` (0x100068e0) needs the frame pointer, and
`m_FreeTracked` (0x10006820) in the same file must not have it and stays
RELOC 188/188.

```c
#pragma optimize("y", off)
void __cdecl m_init(int n)
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
`m_init` 0x1000691b-0x10006924 and raising it from 97 to 105 matched
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

`src/server.dll/DieGildeAddOn/game/spiel_c/gm_AllocSpieler.c:457`
closed the last 6 bytes of `gm_AllocSpieler` (0x10018850), taking it
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
invented, omitted, or placed in the wrong branch. In `gm_AllocSpieler`
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

> **Narrowed in part by §59.**  The blanket claim holds for the *statement* used to
> reach a block — spelling a guard as `if (cond) goto L;` compiles to a byte-identical
> object to the inline `if`, so the label is not the lever.  It does **not** hold for
> the block's *creation* order: writing the guards as `if (success) {...} else {
> error }` makes the front end create the `else`-blocks innermost-first, which places
> the cold handlers at the tail in reverse source order.  That was worth -29 linked
> bytes on CrashDumpUnhandledExceptionFilter (0x10002770).  Read this section with
> §59, not instead of it.

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
loop before layout. Section 57 draws the boundary: shape is a lever only where
the divergence is a back edge pushed out of `rel8` range, and register pressure
elsewhere leaves it inert.

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
sub = gm_ff_Objekt(*(int*) ((char*) q + 0x14), 1, 0, comp & 0x7fff);
```

leaves the load owned by the call site and scores 343/355 with the cursor in
esi. Assigning it first gives the load its own definition point, and the
allocator then places the cursor in edi and the query in esi as the original
does:

```c
qbase = *(int*) ((char*) q + 0x14);
sub = gm_ff_Objekt(qbase, 1, 0, comp & 0x7fff);
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
`ahm_GetCommandPayloadSize` (0x1000c710) the target keeps the switch byte in `dl`
and the loop index in `ecx`; the `case 0x16` body reads `cmd_payload` twice,
once for the `*cmd_payload == 0x16` test and once for `cmd_payload[0x14]`.
Reading the byte for the test first pins it in `dl`:

```c
cursor = (*cmd_payload == 0x16) ? (cmd_payload + 0x15) : (cmd_payload + 0x15);
count = cmd_payload[0x14];    /* RELOC 752/752 */
```

The reverse order scores 742/752, and hoisting the unrelated
`total_size = 0x15` above both scores 508/752.
`src/server.dll/DieGildeAddOn/game/alchemistry_logic_c/ahm_GetCommandPayloadSize.c:93`.

**A hoisted `~x` temp takes the register the target gave the other value.**
In `amt_ExecuteOfficeAssignment` (0x1000b4d0) the loop clear was written as a
`neg_mask` local, which parked the mask in `ecx` and pushed `role_ch` to
`edx`, the reverse of the reference. Spelling the complement inline in the
loop body restores both:

```c
*scan = *scan & ~mask;        /* 826/836 -> 829/836 */
```

`src/server.dll/DieGildeAddOn/game/aemter_c/amt_ExecuteOfficeAssignment.c:260`.
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

In `ahm_GetCommandPayloadSize` (0x1000c710) the target keeps a switch byte in
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

**Preheader instruction order.** In `amt_ExecuteOfficeAssignment` (0x1000b4d0) the
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
q = gm_ff_Objekt(...);
q_slot = *q;                                    /* int local */
total = ... gm_CalculateProductionValue(q_slot, *(unsigned char*) ((char*) q + 0x12)) ...;
```

Reading `*q` into a local and passing the local, instead of passing `*q`
directly, moved the query into esi and the cursor into edi, and reproduced the
reference's `mov dl,[esi+0x12]` / `xor eax,eax` / `mov ax,[esi]` read order.

The local's width matters. The natural `unsigned short` emits an
`and eax,0xffff` widen and reorders the two field reads (SIZE_MISMATCH, 167 of
355). An `int` local is exact. See also section 6 on local width.

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

`amt_ValidateAndAssignOffice` (0x1000b290) reads a holder byte
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
`gm_FindNextFilteredEntity` (0x10016f80) and `gm_NextEntityQueryMatch`
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
`gv_SpawnEntities` (0x10010850) came instead from removing a
semantically dead `if (count > 0)` wrapper around a `while` loop that already
tested it: the extra nesting raised register pressure enough to flip the
roles.

A read-modify-write in the same loop keeps its address as two direct
`[counter + table + disp]` operands. Routing it through a pointer local forces
a `lea` into a register plus `[reg]` accesses; in `gm_Open` that shape is 2
bytes shorter than the reference (859/861) while the double spelling is exact.

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

`gm_AllocRaum` (0x10017c40) opens with

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

`src/server.dll/DieGildeAddOn/game/spiel_c/gm_AllocRaum.c:107`,
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

**Composition requires opposite BYTE signs, and deltas do not always add
(round 184).** Two traps, both hit on `gm_AllocSpieler`:

*Instructions and bytes have independent signs.* A round-178 note recorded that
moving a stranded statement into its loop "makes the instruction count exact
(1054 -> 1056), i.e. it ADDS instructions" — true, and irrelevant. The same change
*shortens* the real body by 14 bytes, because the three FP ops it gains inside the
loop are outweighed by the out-of-line copy it deletes and by the addressing
collapsing to 3-byte `[esi-0xc]` forms. Pairing it with a -11 fix under this section
was therefore doomed from the start: both are negative. **Record the byte delta
explicitly whenever a note claims a length effect**; an instruction count is not a
length.

*Overlapping levers do not compose.* Those two fixes measured -11 and -14 alone and
**-9 together**, not -25 — they overlap by 16 bytes because both rewrite the same FP
scheduling region, and together they even regress the instruction count back to 1054
from the 1056 one of them reached alone. So a combination's delta must be *measured*,
never predicted by addition, and two levers that touch one region are candidates for
fighting rather than composing. The case below works precisely because its two
clusters were one fault seen twice; that is the configuration to look for.

`gm_AllocRaum` (0x10017c40) sat at NEAR_MATCHING 677/742 for nine
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

`src/server.dll/DieGildeAddOn/game/spiel_c/gm_AllocRaum.c:107`

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

In `sim_AdvanceGameClock` (0x100155c0) the target emits

```
xor esi,esi; mov si,word ptr [ecx+4]; mov dword ptr [ecx+6],edx
```

and every source spelling that hoisted the `x04` read above the `x06` store
either left the pair transposed (187/197) or re-folded an earlier carry and
collapsed to 87. Wrapping the function in `#pragma optimize("a", on)` emitted
the target's order with no source change at all, 187 to 194/197.

```c
#pragma optimize("a", on)
void __cdecl sim_AdvanceGameClock(SIM_CLOCK* clock, int arg2, int arg3, int arg4)
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

`sim_AdvanceGameClock`'s second loop had to emit

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
mod_value = (float) ((double) mod_value * g_const_half);
value = (float) (acc * mod_value);            /* cmp; fxch  -> 391/396 */
```

Scaling through a `double` local puts the `[esi]` access after the `fxch`, as
the target does, but msvc6 then keeps the byte in a register and emits
`mov al,[esi]` plus a later `cmp al,0x17`, one byte longer:

```c
p2_wide = (double) mod_value * g_const_half;
value = (float) (acc * p2_wide);              /* fxch; mov al -> obj 397 */
```

A `volatile` store to the float result lands the `fxch` correctly too, but
sinks the compare two slots, past `fmulp` and `fstp` (387/396).

The `fxch` itself is a removable stack fixup, not a fixed instruction. Making
the scaled double the destination of the merge multiply drops it and shortens
the object by two bytes:

```c
acc = (double) mod_value * g_const_half;
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

## 47. A loop's form, not its text, decides where C2 puts its cold exit block

`ServerMainThread` (0x100093a0) has a loop whose taken branch leads to a cold
block that the reference keeps out of line — after the *next* loop, in a gap in
an unrelated chain.  Everything about the loop's text matched the reference
already: the instructions were identical, the branch target was right, and nine
rounds of probes left the block inline, immediately after the loop with a `jump`
over it.

- label position (including moving the cold body to the end of the function)
- branch polarity (`if (clear) { advance; continue; } goto cold;` versus
  `if (taken) goto cold;`)
- guard form, block duplication, cold-tail placement, region size
- `#pragma optimize` letters
- every VC6 service pack, and a CFLAGS sweep

What moves it is the loop's **form**:

```c
    do {                                  /* cold block lands inline */
        if ((*p & mask) == 0) { advance; continue; }
        goto cold;
    } while ((int) p < bound);

    while ((int) p < bound) {             /* cold block lands out of line */
        if ((*p & mask) != 0) { goto cold; }
        advance;
    }
```

The body, the condition and the `goto` are the same; only the rotation differs.
Three loops in that function gained alignment this way (522 -> 547 -> 557 -> 558
of 627 instructions, localised with the relocation-masked sequence diff).

Two cautions, both measured:

- **It is loop-specific, not universal.**  The same edit on the pending-sync
  transfer loop *regressed* 558 -> 523, and on `process_pending_sync` it was
  neutral.  Convert only loops whose taken branch targets a cold block the
  reference places out of line, and measure each one.
- **Do not judge it by the positional byte score.**  That score fell 1162 -> 828
  on the change that raised alignment by 25 instructions: one extra instruction
  shifts every later byte, so the positional count desynchronises.  Compare
  instruction sequences with relocations masked (`scripts/seqdiff.py`,
  `scripts/zlibcheck.py`) and keep the build's own `.text` size as the
  link-level figure.

## 48. msvc6 folds a compared variable into a later store, and no spelling keeps it in the register

`ServerMainThread` (0x100093a0) builds a command packet in the
`if (sent_bytes == 0xffffffff)` arm of the transfer loop.  The reference keeps
`sent_bytes` in `eax` across the arm and loads `total_size` into `ecx`:

```asm
    mov  eax, [ebx]                    ; sent_bytes (compared with -1)
    cmp  eax, -1
    jne  ...
    mov  ecx, [0x101deac0]             ; total_size
    lea  edx, [esp+0x10]
    push edx
    push ebp
    mov  byte  [esp+0x18], 8
    mov  byte  [esp+0x1b], 0xff
    mov  dword [esp+0x1c], eax         ; sent_bytes, register form
    mov  dword [esp+0x24], 0
    mov  dword [esp+0x28], ecx         ; total_size
    call cm_QueuePlayerCommand
```

When the arm stores `sent_bytes`, msvc6 constant-propagates the value the
`if` compared and emits the 8-byte immediate `mov dword [esp+0x1c], 0xffffffff`
instead.  That frees `eax`, so `total_size` lands in `eax` and the `lea` takes
`ecx`: three instructions differ and the object is four bytes long.

Measured on the same file, all **inert** (byte-identical objects): comparing
`(int) sent_bytes == -1`; storing a literal `0xffffffff`; storing
`(unsigned int) (int) sent_bytes`; copying `sent_bytes` into a second local
and comparing or storing *that* (copy propagation carries the constant
through); declaring `total_size` inside the arm.  The fold is driven by the
compared *expression*, and neither a cast nor an intermediate variable breaks
it.

The one spelling that clears it is to compare the memory operand instead of the
local, `*(unsigned int*) transfer_progress == 0xffffffff`.  The value then
survives in `eax` and `total_size` moves to `ecx`, exactly as the reference.
The cost is a second live value across the argument pushes: c2 then stores
`total_size` before the pushes (pre-push displacements) and gives the `lea`
`ecx`, so three hunks close and three open, and the object drops to 2431 bytes.
Recorded as a dead end rather than a fix.

Note the *other* arm of the same `if`, at target 0x10009846, stores the literal
`0xffffffff` and the reference keeps the 8-byte immediate there too.  Only the
arm whose store operand is a variable reaches this rule.

Amendment (2026-09-13): two further probes on the same arm, both reverted.
Dropping `volatile` from the cmd+4 store changes nothing structural (2074 ->
2070 positional); reading `total_size` at its point of use instead of hoisting
it re-derives the memory-operand outcome above (obj 2431, SIZE_MISMATCH).
The fold is a fixed point of the compared expression, not of any statement
order around it.

## 49. A CFLAGS sweep on one function: inert, negative, and one near miss

`gm_AllocSpieler` (0x10018850, target object 3689 bytes; an earlier revision of
this section cited 0x1001A0F0, which is `gm_RandomFloat01`) is the smallest
remaining size mismatch in the tree (ours 3688, same span), and it was used to
sweep the flags that are plausibly still in play.  Numbers are the object size
and the register-agnostic matched-byte count from `rebrew diff`; "inert" means
a byte-identical object.

| flags added to `/DREBREW_ALLOW_NAKED /O2 /Gd /Oa /Ow` | object | reg-agnostic | verdict |
|---|---|---|---|
| (base) | 3688 | 853 | — |
| `/Ow-` | 3692 | 840 | size closer, content worse |
| `/G6` | 3701 | 819 | size closer, content worse |
| `/Op` | 3766 | — | much larger |
| `/Za` | — | — | larger |
| `/QIfist` | — | — | larger |
| `/Zp1 /Zp2 /Zp4 /Zp8` | 3688 | 853 | inert |
| `/Ob2`, `/Ot`, `/Oi`, `/Oi-`, `/Oa-`, `/G5`, `/GB` | 3688 | 853 | inert |

A later campaign measures `/Oa` and `/Ow` as load-bearing on this function and
`/O2`-class flags as inert on it (section 58), which supersedes the `/Oa-` row
above.

The lesson is the general one: on this codebase a flag that moves the size
towards the target has so far always moved the *bytes* away from it, because
the size gap is one instruction's worth of a scheduling decision, not a
codegen-policy difference.  Sweep a flag only when a *specific* instruction
class is wrong (section 50), and score with the reg-agnostic count, never the
size alone.

## 50. The residual codegen classes, as instructions

Across the game region the remaining differences keep falling into five
shapes.  Quoting target disassembly first, ours second:

```
0x100097fb  mov [r+0x1c], r          / mov [r+0x1c], 0xffffffff   -1 materialization
0x1000984b  lea r, [r+r]             / add r, r                    strength reduction
0x100098e3  je  <loop head>          / jne <exit>                  branch polarity
0x10009baf  mov [r+0x30], r  ...     / [r+0x28], [r+0x2c], ...     frame offsets
 0x8c9       mov ax, [ebp]           / xor r, r                    zero-register cache
             and eax, 0xffff         / mov r16, [mem]
```

* **`-1`/zero materialization.** The reference keeps `-1` in a register once
  (`or ebp, -1`) and stores the register; we emit the 8-byte immediate.  This
  is msvc6's absence of constant caching and has no source lever
  (`docs/msvc6-allocator.md`).
* **`lea r,[r+r]` vs `add r,r`.** c2 picks `lea` when the flags are live;
  a spelling that kills the flags register is the only lever found.
* **Branch polarity** (see also section 7).  `je <head>` against our
  `jne <exit>` is a block-placement consequence, not a source choice — except
  where several guards share an error tail, where a guard inversion decides
  which site falls through and is a source lever (section 54).
* **Frame offsets.** `+0x20/+0x24/+0x30` against our `+0x1c/+0x28/+0x2c` is
  the local-slot layout inside one function; it follows `volatile` placement
  and the order of declarations, and it has been steered exactly once
  (round 110).
* **`and eax, 0xffff` after a 16-bit load.** The reference zeroes a register
  once and uses `mov reg16, [mem]`; we widen with `and`.  Section 43's
  byte-width rule is the related lever, and it is why
  `ls_LoadBuildingEntityState` stays one byte long.  The pair is not an
  unsteerable residue: the `and` form is what a `volatile` load emits and the
  `xor`/`mov` form is what a plain one emits (section 52), so where the
  reference has `xor`/`mov` and we have `mov`/`and`, drop the qualifier on that
  load rather than retyping it.

The one case that *was* steerable had a structural cause — `cm_ExCopyEntityData`
(round 110) reached its store block from several duplicated branches, and
spelling the clamp "in range first, then high, then low" collapsed them.
Before spending a round on any of the five, look for that shape first.

## 51. `volatile` on a local is a scheduling barrier; qualify at the use site

A `volatile int x;` declaration makes *every* store to `x` a scheduling
barrier, so msvc6 will not move a load across it. Declaring the local plain and
qualifying only the accesses that need ordering (`*(volatile int*) &x`)
produces a different — sometimes exactly the reference's — schedule. It is a
scheduling lever, not a semantics knob.

`vfs_ReadCompressed` (0x10008a90) declared `volatile int done; volatile int
result;`. Replacing both with plain locals plus casts at the use sites
reproduced the reference's prologue byte for byte —

```
mov eax,[esp+0xc] / push ebx / push ebp / push esi / test eax,eax / push edi /
store / store / jne
```

— and was worth -62 linked bytes.

Two sub-facts, both measured:

- It is the two *init* stores that are the barrier, not the declaration as
  such. On the older body, merely casting the init stores (`*(int*) &done = 0;`)
  with the `volatile` declarations kept already scored 382.
- One plain read (`int acc = result;`) MUST stay plain. Qualifying it cost 32
  bytes.

This is the converse of section 39 (a volatile read *deferring* a load past the
prologue pushes) and of 8c (a volatile read *pinning* load order): here the
qualifier is removed, and the granularity is one access, not the variable.

`src/server.dll/Units/vfs/vfs_ReadCompressed.c`

## 52. The 16-bit zero-extend idiom is selected by `volatile`, not by C spelling

A plain `unsigned short` load emits `xor r,r; mov r16,[mem]`. The same load
through a `volatile` pointer emits `mov r16,[mem]; and r,0xffff`. Seventeen
spellings on msvc6 `/O2 /Gd` in a micro TU — global, cast, typed pointer, struct
member — all follow the qualifier, not the syntax.

**Corollary, and the reason this section exists: the idiom cannot be reached by
spelling at all.** On `gm_AllocSpieler` (0x10018850) every attempt to write the
reference's `xor r,r; mov r16,[mem]` form while keeping the `volatile` — `(int)(unsigned)*(volatile
unsigned short*) p`, the same through a temp local, the same for a second site, and a
`n = 0x3c + (idx < 6 ? 0x86 : 0)` temp for the paired `and edx,0x86` (6-byte imm32)
against our `and edx,0xffffff86` — folded straight back to the current code. The
qualifier wins every time, so a site whose reference form differs has to be fixed by
removing the qualifier (and paying whatever hoist that causes) or by a size-compensated
rewrite, never by casting around it. Check the qualifier before spending probes on the
expression.

So an `and r,0xffff` in our output is evidence the source reads that field
`volatile`, and where the reference has `xor`/`mov` and we have `mov`/`and`,
the residual is the qualifier, not the expression.

`gv_ExAllocGraveyardWorker` (0x10011bf0): its two neighbour-loop reads are
volatile in our source and demonstrably were not in the original.

This refines section 6 — the widening mask is a `volatile` tell, not a width
tell — and supersedes the last bullet of section 50, where the pair was recorded
as a residue with no source lever. The lever is dropping the qualifier on that
one load.

**Amendment (round 245) — the lever has a wall, and the direction is easy to
invert.** A pass was briefed with the qualifier backwards ("add `volatile` to get
the reference's `xor`/`mov`") and refuted it in 14 probes; the brief was wrong,
this section was right. What that pass *did* establish is where the lever stops:

- **The qualifier is load-bearing for register allocation at some sites, and there
  the lever cannot be cashed.** On `gm_AllocSpieler` (0x10018850) dropping it at
  the two sympathy-loop reads *does* produce the reference's `xor ecx,ecx; push
  0x40; mov cx,[bp]` locally — and costs 362 matched bytes (736 -> 374), because
  the qualifier is what holds that loop's allocation. Dropping it at both loops:
  397. Form and allocation are coupled; this is the same shape as
  `gv_ExAllocGraveyardWorker` above, now measured on the larger function too.
- **Sweeping the qualifier *in* is worse than leaving it alone.** Adding `volatile`
  at 1 / 8 / 17 sites gives matched 488 / 408 / 365 against HEAD's 736, and the
  full sets push the object to COMDAT 3728/3744, past the 3696 composition band —
  so they fail on layout as well as on score.
- **A count of `and r,0xffff` sites is not a length signal.** The inventory on this
  function ("6 extra `and`, 4 missing `xor`") is a fixed-offset artifact: both
  sides' real code is already exactly 3689 bytes, the gap curve oscillates +-48 and
  returns to 0, and the 4 reference `xor`s are all present in our object (the last
  one displaced by one statement-order divergence, not missing). Of our 16 masks
  only 7 are genuinely extra — 3 are a redundant second mask on a call result, 4
  are the volatile loads.
- **`matched` has a ceiling here of ~3115 of 3689** (`matched-reloc - matched` =
  574, one-sided relocations; see allocator Finding 59). Do not treat the distance
  from 736 to 3689 as reachable codegen work.

The practical rule this leaves: `volatile` is a *per-variable fixed point*
(allocator Finding 61). Check the qualifier first, in the direction this section
states, and expect the lever to be blocked wherever that value's live range also
determines the allocation.

Amendment (2026-09-13): the same fixed point, third instance, on
`vfs_OpenStream` (0x10009020). Dropping `current_char` gives the reference's
`cmp byte [eax],0` entry test and `movsx eax,[esi]` head load byte-exact, plus
a byte-exact rotated back edge — but frees `al` and recolors the switch body
into ~40 small hunks (linked +194). Two proof-breaking spellings (volatile-
sourced init+increment; `p[1]`-before-inc reorder) both fail: c2's value
numbering sees through them, and the unproven forms add traffic. Any
proven-equal local is reused at the head; any unproven one costs elsewhere.

`src/server.dll/DieGildeAddOn/game/friedhof_logic_c/gv_ExAllocGraveyardWorker.c`

## 53. `switch` case bodies are laid out in source order

Reordering the case groups to match the reference's addresses put every body on
its reference offset; the jump table and byte map are then byte-identical. The
case *order* is the lever, not the case set.

`gm_AllocGebaeude` (0x100174d0), worth ~-200 linked bytes.

`src/server.dll/DieGildeAddOn/game/spiel_c/gm_AllocGebaeude.c`

## 54. A guard inversion moves which site falls through, and with it the branch histogram

Where several error sites share one tail, `if (success) { body } else { error }`
and `if (failure) { error } body` are semantically identical but reach that tail
differently: one site falls through, the others `jmp`. Which site falls through
decides the displacement sizes, and therefore the rel8/rel32 mix.

`cm_ExSellObjekt` (0x1000d930) has, in the reference, 13 `LogMessageInternal`
sites: 3 inline `sprintf` tails and 10 on a shared tail at 0x1000e00e, 9 by
`jmp` and 1 by fall-through. Reverting one inversion restored the reference's
fall-through site and its exact encoding histogram (12 x rel32 + 10 x rel8),
worth -38 linked bytes.

This refines section 50's "branch polarity ... is a block-placement consequence,
not a source choice": the polarity of a guard that *shares* a tail is a source
choice. Section 7 covers the same edit from the epilogue-count side.

`src/server.dll/DieGildeAddOn/command/command_c/cm_ExSellObjekt.c`

## 55. Comparison rewrites must keep the strict/non-strict boundary

`a - b < 0` is `a < b`, never `b <= a`. A candidate written
`if (0 <= slots - g_stat2)` for `if (g_stat2 - slots < 0)` flipped the equality
case: a behavioural change, not a codegen one, and it was caught by reading the
diff, not by any score.

To change which operand folds, flip the operands of the same operator
(`slots > g_stat2`), never the operator's sense.

Same blind spot as sections 34 and 36: `match_count` and the `~~` mask cannot
see it. The candidate's VA was not recorded; the finding is a diff-reading
habit, not a site.

## 56. A missing exit epilogue is a `return` that hands back a register

Where the reference's tail returns re-read a volatile local
(`jne` / `mov eax,[esp+0x14]` / pops / `ret`), a source `return d;` returns a
register that already holds the value, so msvc6 needs no load and tail-merges
that exit onto the main epilogue. Spelling it `return *(volatile int*) &done;`
restores the separate epilogue byte for byte.

`vfs_ReadCompressed` (0x10008a90): a whole third exit epilogue, 12 bytes, worth
-22 linked. Same function and the same lever as section 51 — the qualifier sits
on the use, and it is what makes the load reappear.

`src/server.dll/Units/vfs/vfs_ReadCompressed.c`

## 57. Loop shape is a lever only when the divergence is not register pressure

A bottom-tested `do{}while` can put the body out of range of a short back edge,
so msvc6 emits `jge exit` plus a long `jmp`; a top-tested `for` restores the
single `jl` back edge.

`cm_ExProdObjekt` (0x1000e140), worth a large re-alignment.

Where the reference simply holds a different set of live values, loop *shape*
rewrites are inert:

- `CrashDumpUnhandledExceptionFilter` (0x10002770): five spellings of the
  decrypt loop (`for`, `while`, `do-while`, `>>2`, pointer increment) are
  byte-identical.
- `ahm_ExAllocAlchemist` (0x1000bdf0): all eight factorisations of a stride
  (`*0x21c`, `*540`, `*45*12`, shifts) are byte-identical, because the strength
  reducer re-derives the same chain.

Read the diff for a live-value difference before reshaping a loop; sections 8,
20, 31 and 47 are the cases where the shape itself was the divergence.

`src/server.dll/DieGildeAddOn/command/command_c/cm_ExProdObjekt.c`

## 58. `/Ox` versus `/O2` is per-file and load-bearing

`/O2` enables `/Og`, which makes msvc6 tail-merge early error blocks the
reference keeps separate; `/Ox` is what several command-handler files need.
`/Oa` and `/Ow` are load-bearing on `gm_AllocSpieler` (0x10018850), and
`/O2`-class flags are inert on it.

Flags are per-file in practice, not per-function: a flag one function needs can
break a file-mate. Section 12 is that conflict, and section 49 is the measured
flag sweep on `gm_AllocSpieler` — where the same flag set's `/Oa-` row is
superseded by the `/Oa` measurement here, and `/Ox` is byte-identical on an
individual function (section 46) while being load-bearing per file.

`src/server.dll/DieGildeAddOn/game/spiel_c/gm_AllocSpieler.c`

## 59. `if (cond) goto L;` compiles to `if (cond) { body }`; cold handlers are placed by block *creation* order

`if (cond) goto L;` — a branch to a label — compiles to a byte-identical
object to `if (cond) { body }` with the body inline. Both spellings of the same
guard sequence were compiled and their COMDATs byte-compared: 2128 bytes each,
identical. msvc6 normalises the `if`-goto form back into a plain `if` and still
lays the then-block inline, so "I wrote a `goto`, so the handler must sit out
of line" is false, and any note that credits a `goto` for a block's position is
wrong.

What actually places cold handlers at the tail — and in **reverse source
order** — is block *creation* order: the front end creates `else`-blocks
innermost-first. A sequence of guards written
`if (failure) { error; goto done; }` therefore does not give the reference's
layout, while `if (success) { body } else { error }` does; the handlers then
materialise at the tail in reverse source order.

Measured on `CrashDumpUnhandledExceptionFilter` (0x10002770): rewriting its
guards in the `if (success) {...} else { error }` shape put all four
`LogMessageInternal` sites at the tail, gave 44 calls (the reference's count)
and was worth **-29 linked bytes**, size-neutral (COMDAT 2128, frame
unchanged). The same change written as `if (cond) goto L;` with tail labels was
byte-identical to the original and worth nothing.

The reference's own cold blocks there sit at 0x10002db3, 0x10002de9,
0x10002e1b, 0x10002e29, 0x10002e35, 0x10002e4d — reverse source order, which is
the signature to look for on other functions whose cold handlers differ.

This is the same family as section 54 (a guard inversion moves which site falls
through, and with it the rel8/rel32 branch histogram) and section 50's
branch-polarity item: block order, not statement shape. It also narrows section
17, which recorded out-of-line placement as unsteerable from source — the
`goto` label is not the lever, the `if`/`else` form that *creates* the block is.

`src/server.dll/Units/Error/Error_c/CrashDumpUnhandledExceptionFilter.c`

## 60. A volatile store's position is a dependency fixed point, not a statement-order choice

On `cm_ExProdObjekt` (0x1000e140) the reference emits
`mov edx,[0x101de450]` before the volatile dead store that follows, and we emit
it after. Moving the volatile `loop_count` store below the
`recipe_shift = g_unknown_1de450 + ...` statement — so that the global load
precedes it in source order — produced a byte-identical object to the
unmodified source. The scheduler places a volatile store by its dependence, not
by where the statement sits, so a volatile store cannot be slid past a global
load by rewriting the source order. The reference's global load is above a
volatile store, and a store through a cast pointer is treated as aliasing every
global, so the shipped msvc6 will not emit that order from any source shape
tried: treat it as closed.

This is the third site in this campaign where statement order was inert in
exactly this way — the converse of section 51 (where the lever was moving the
`volatile` *qualifier*, not the statement) and the same shape as section 57's
loop case. Where a load/store transposition does have a lever, it is section
44's `#pragma optimize("a", on)`, which switches the aliasing assumption off.

Retired lever, not a general law: measured with `scripts/probe_function.py` and
`scripts/instr_diff.py --obj`, and it did not move the linked residue.

`src/server.dll/DieGildeAddOn/command/command_c/cm_ExProdObjekt.c`

## 61. A shared guard the reference falls into cannot be reached by fall-through from C

On `cm_ProcessCommandQueue` (0x1000aac0) the reference has a shared `recheck`
guard (`test ebx,ebx; je <unlink>`) that arm 5 falls into after `held = pkt`.
Our arm 5 does `goto advance` and skips it, so our `jne` retargets. Changing it
to `held = pkt; goto recheck;` collapses the entire function — matched-reloc
584 -> 142 on the object metric, 624 -> 204 — because msvc6 re-lays the block
graph.

Same family as section 59 (block order, not statement shape) and section 54:
what is not reachable from C here is the *layout decision*, not the statement.
A `goto` is normalised back into an `if` (section 59), so it cannot express
"make this arm fall through into the guard the reference shares".

Retired lever, not a general law: measured with `scripts/probe_function.py` and
`scripts/instr_diff.py --obj`; neither spelling moved the linked residue.

`src/server.dll/DieGildeAddOnServer/server_c/cm_ProcessCommandQueue.c`

## 62. A literal shared by several comparisons is not a lever for register residence

Hoisting a repeated immediate into one named local does **not** make msvc6 keep
it in a register.  On `cm_ExCopyEntityData` (0x1000ec00) the four slot guards
each compare against `0xffff`; feeding all four from a single local

```c
ushort empty = (ushort) 0xffff;      /* int instead of ushort: same result */
```

is **byte-identical** to spelling the four literals out.  msvc6 rematerialises
`cmp word ptr [reg+disp32],0xffff` (9-10 B) at each site rather than keeping the
value live.

The reference does hold it — `mov ebp,0xffff` once at 0x1000edc0, then
`cmp word ptr [eax+0x100358a0],bp` (7 B) — but `ebp` is free there only because
the instruction that clobbers it (`mov ebp,[eax+0x10035ab0]`, the type-3 arm's
owner_id load) sits on the other side of a branch.  That is a CSE plus
callee-saved allocation decision with no C spelling: the value's live range is
what it is, and a source-level name does not extend it.  A wall, not a lever.

Contrast section 22 (`4 + load_result`), where the *spelling of the load*
selected the cached form.  The distinction: there the spelling changed the
address expression the optimizer had to compute; here it changes only a name the
optimizer erases before allocation.

`src/server.dll/DieGildeAddOn/command/command_c/cm_ExCopyEntityData.c`

## 63. A clamp's winning arm order is per-site, not per-function

The same three-arm clamp wants a different source order in each of the several
arms of one function, and copying a neighbouring arm's order is not
transferable.  Measured on `cm_ExCopyEntityData` (0x1000ec00), one arm at a
time, all exhaustively equivalent so semantics are constant and only layout
moves:

| arm | order that wins | effect |
|---|---|---|
| type-2 | in-range / HIGH / low | honest matched +13 (`jl low / jge high / store / jmp`) |
| type-1 (secondary) | in-range / LOW / high | honest +7, aligned +10 |
| type-0 | per-arm stores, trailing store duplicated into each arm | matched-reloc +6, honest -2 |
| matrix loop | in-range / LOW / high, store after the join (already HEAD) | in-range / HIGH / low craters to 342/524 |

What selects the winner is which order puts the cold blocks in the reference's
**address order** (section 59: block *creation* order, not statement shape).
Since that order differs per site, there is no function-level rule to extract:
measure each arm.  A general "reorder the clamps like the neighbour" edit is not
a lever.

`src/server.dll/DieGildeAddOn/command/command_c/cm_ExCopyEntityData.c`

## 64. `for (;;) { if (x) break; ... }` is normalised to the `do/while` form

An indefinite loop exited by `break` is re-lowered into the loop test, producing
byte-identical output to the equivalent `do { ... } while (!x)`.  Measured on
`cm_ExCopyEntityData` (0x1000ec00): the dst-slot scan written `for (;;) { if
(match) break; ... }` compiles identically to the `do/while` spelling, with the
same peeled first compare plus rotated body.

Same normalisation family as section 59 (`goto` re-lowered into `if`): here the
`break` re-appears as the loop's own test, so `for(;;)`+`break` cannot be used to
force a loop shape the `do/while` form does not already produce.  Corollary for
this function: the reference's *unrotated* dst scan is reachable only from the
top-tested `while` spelling, and that spelling costs the entry guard the
reference lacks (+3 B, aligned +6, honest -47) -- so the rotation is a genuine
fixed point, not a spelling problem.

`src/server.dll/DieGildeAddOn/command/command_c/cm_ExCopyEntityData.c`

## 65. an if/else-if chain and a real `switch` emit their jump tables in OPPOSITE order

The strongest read-out of dispatch form found so far, because it is a *structural*
difference a byte compare sees as a region of total mismatch.

On `CrashDumpUnhandledExceptionFilter` (0x10002770), written as a hand-rolled
`if/else if` chain over the exception code, the COMDAT's two out-of-line tables are
emitted **10-entry then 5-entry**.  Rewritten as one `switch (excCode)` with the same
case set and the same bodies, they come out **5-entry then 10-entry** -- which is the
reference's order (5-entry at 0x10002e9c, 10-entry at 0x10002f1c).

Measured with the switch rewrite *alone*, nothing else changed:

```
matched        231 -> 387
matched-reloc  655 -> 811
aligned        283 -> 366
drift at 0x10002a43   +470 -> -26
```

So the table order is not cosmetic and not downstream of the case bodies: `switch`
selection changes the block layout, and the fix is to *use a switch*, not to try to
reorder tables from C.  Corollary: the two hand-computed index maps (0x69 bytes for the
`-0xc0000025` switch, 0x6f for `-0xc000008f`), the `lea ecx,[ecx+0]` 3-byte align pad and
the 1-byte `90` pad are all *consequences* of that layout and cannot be fixed directly.

**Use it as a diagnostic in the other direction too:** when a function's residue contains
a region that looks like total mismatch and the source has a long `if/else if` chain over
a dense integer key, try the `switch` form first.

**Precondition (round 176) — check the reference for a jump table before applying this.**
The win above worked because that reference *already had* two out-of-line tables, so
`switch` matched the selection msvc6 had made originally. `ls_LoadBuildingEntityState`
(0x100128f0) looked like the same situation and is the opposite: its reference dispatch is
a linear `cmp al,0xNN` / `je` chain with the default falling through, and the if/else-if
chain is the only C form that reproduces it. A genuine `switch` over the same key set
({0x1e, 0x48-0x4a, 0x4b-0x4d}) is dense enough to trip msvc6's table heuristic, which
emits `jmp DWORD PTR [ecx*4+...]` plus an index/address table: object 1472 -> 1520 (+48),
matched 690 -> 573. So the rule is *match the reference's selection*, not "prefer switch".

**And verify the arm order from the emitted bytes, never from the source text.** A round-175
block-order map recorded this function's arms as fully reversed and queued the rewrite on
that basis; objdump showed the baseline already emits them in the reference's order
(uniform +2 drift, byte-identical compare chain including all six `je` displacements, zero
hunks in the region). The map had compared source text order against emitted order. msvc6
emits else-blocks innermost-first (section 59), so source order is *expected* to look
inverted — reading it as a divergence manufactures work that does not exist.

`src/server.dll/Units/Error/Error_c/CrashDumpUnhandledExceptionFilter.c`
`src/server.dll/DieGildeAddOn/loadsave/loadsave_c/ls_LoadBuildingEntityState.c`

## 66. a dead store in the source appears as a store in the reference — comparing stores is a dead-code oracle

`frameInfo[0] = (int) pDbgBuf;` occurred twice in the source on
`CrashDumpUnhandledExceptionFilter` (0x10002770); the reference has exactly **one** store
there, and the pre-chain copy is absent (no store between `mov edi,[esp+0x294]` at
0x100029f7 and the first `cmp eax,0xc000008e` at 0x10002a02).  Deleting the first copy:
`ret` moves -8 bytes, `matched` 442 -> 475, span 2128 -> 2112, no warning.

The general technique: **count the stores to a location in the reference and compare with
the source.**  The compiler cannot remove a store the reference contains, and it will not
invent one, so a store-count difference is a source-level contradiction -- a duplicated
assignment, or one the original never had.  This is much cheaper than reading a diff, and
it works on a location whose address is a frame slot rather than a symbol.

`src/server.dll/Units/Error/Error_c/CrashDumpUnhandledExceptionFilter.c`

## 67. msvc6 does not reorder calls, so call order in the source is recoverable from the reference

`CrashDumpUnhandledExceptionFilter` (0x10002770): in the hCrashLog-OK path the reference
calls `GetCurrentProcess` ([0x1002402c], 0x100028fb) **before** the two `szLine`/`szSep`
memcpys (0x10002901..0x10002923) and `SetFilePointer` ([0x10024028], 0x1000294c); the
source had `GetCurrentProcess` after `SetFilePointer`.  Hoisting it: `matched` 475 -> 478,
everything else unchanged.

Unlike register allocation or block layout, **statement order across calls is a
source-order property**, so the reference's call sequence reads directly into a
reordering.  Worth checking early on a mismatching function: list the calls in reference
address order and compare with the source's order.

`src/server.dll/Units/Error/Error_c/CrashDumpUnhandledExceptionFilter.c`

## 68. a redundant null test after a search loop is NOT eliminated, and its width matters

`gm_AllocGebaeude` (0x100174d0).  Written

```c
while (q != NULL && *q == 0xfd) { q = next(); }
if (q != NULL) { store; }
```

msvc6 keeps a redundant 4-byte `cmp eax,ebx; je` for the second test.  The equivalent

```c
while (q != NULL) { if (*q != 0xfd) { store; break; } q = next(); }
```

matches the reference's rotated form (`jne top; jmp out`) and costs 4 bytes less -- and
because those 4 bytes sit *before* a 600-byte aligned region, they shift the switch and its
jump table: `matched` 503 -> 830.

Lever, and a reminder that the value of a byte is positional: 4 bytes here were worth 327
matched bytes, while 4 bytes elsewhere in the same function were worth nothing.

`src/server.dll/DieGildeAddOn/game/spiel_c/gm_AllocGebaeude.c`

## 69. an `__asm` block is a scheduling barrier — and this project's C-only constraint forbids using it as one

**Mechanically real:** on `gm_AllocGebaeude` (0x100174d0) inserting

```c
__asm { nop nop nop }
```

between `idx = comp & 0x7fff;` and the `g_item_def_table` address expression made msvc6
move `mov ebx,[g_item_def_table]` across the two surrounding instructions, which flipped the
loop's forward `je` from rel8 to rel32 and realigned a 129-byte loop body onto the
reference's offsets.  With three further equivalent changes it measured `matched` 683 -> 830
and `matched-reloc` 823 -> 970 at an unchanged COMDAT of 1088.

**It is not usable here.**  The objective for this recompilation is C only, with a single
exception: hand-written assembly that the *original* code itself contained.  A `nop`
barrier is neither -- it is a directive to our compiler to reproduce a schedule no C
spelling produces, so it manufactures bytes the source does not explain.  The pre-existing
`__asm` block-fill in this same file is admissible because the original has a 24-byte
hand-written fill prelude there (Finding 19); the barrier is not.

Measured cost of honouring the constraint: removing only the barrier from that candidate
gives `matched` 377 (worse than HEAD's 683) and drops the COMDAT to **1072**, which moves the
jump table and breaks the composition.  So **the entire +147 rested on the barrier**, and
`gm_AllocGebaeude` was reverted to HEAD rather than shipped.  Recorded so the lever is not
re-derived as "free": it is real, it is large, and it is off-limits.

**What remains legitimate:** when a schedule is unreachable from C, look for a *source*
mechanism with the same effect -- an extra local that extends a live range, a
`volatile` qualification that pins a value to memory (section 60), or a statement order
that changes which block is created first (section 59).  Those are C, and their effect on
the scheduler is explainable.

`src/server.dll/DieGildeAddOn/game/spiel_c/gm_AllocGebaeude.c`

## 70. operand order in a commutative address expression is inert; only the *nesting* steers

`ls_LoadBuildingEntityState` (0x100128f0): eight spellings of the same address
expression -- swapping the two operands of the `+`, reordering the addition chain, naming
an intermediate -- are **byte-identical**.  What does steer codegen is how the additions are
*nested*: `(load_result + N) + ptr` and `(ptr + load_result) + N` are different, because the
first computes a scaled index off `load_result` and the second folds `ptr` into the base.

So when an operand shape is wrong, the lever is the parenthesisation, not the order of a
commutative operator.  A sweep over operand orders is wasted budget; a sweep over nestings
is not (and this site was already at its optimum).

`src/server.dll/DieGildeAddOn/loadsave/loadsave_c/ls_LoadBuildingEntityState.c`

## 71. `memset(p, 0, N)` is an intrinsic that is not value-tracked, so it beats `p[0]=0; p[0]|=1`

`ls_LoadBuildingEntityState` (0x100128f0).  Writing the state block as

```c
memset((void*) state_ptr, 0, 0x10);
state_ptr[0] |= 1;
*(int*) (esi + 0xa5) = -1;
```

reproduces the reference's state block **instruction for instruction** (34 bytes, 11
instructions), where `p[0] = 0; p[0] |= 1;` folds to a single store.  The reason is that the
`memset` intrinsic is opaque to the value tracker: msvc6 cannot see that the following
`|= 1` only touches a byte it just zeroed, so it keeps both the fill and the read-modify-write.

**Caveat that makes it a wall in practice here:** it is byte-neutral at this site
(`matched` 645 -> 645, `matched-reloc` 879 -> 869) because the block is compared at offsets
that are already +2 wrong, and the extra 4 bytes remove the compensating length that gave the
only aligned stretch in the tail.  A shape that is locally perfect still buys nothing when
its position is wrong -- check the running delta at the block *before* spending probes on
its internal shape.

`src/server.dll/DieGildeAddOn/loadsave/loadsave_c/ls_LoadBuildingEntityState.c`

## 72. a callee-saved sentinel and a CSE can be one mechanism, not two

`ls_LoadBuildingEntityState` (0x100128f0).  The reference caches the `-1` sentinel in `ebp`
(`or ebp,-1` once, `mov [..],ebp` at three sites) and its read loop also relies on a CSE.
The two are **not separable**: give either of the two read-loop sites the other address
nesting (section 70) and the CSE disappears *and* the sentinel goes with it -- `push ebp`
1 -> 0, `or ebp,-1` 2 -> 0, `mov [..],0xffffffff` 0 -> 3, `matched` 645 -> 79.

Practical rule: when two register-allocation effects vanish together, they are one
decision upstream, and the 2-instruction form you are trying to fix is the *cheap* half of
it.  Here rematerialising the immediate costs +3 bytes, but rematerialising it at the three
stores costs +12 -- so the current encoding is the cheapest point on that trade, not a
mistake.

`src/server.dll/DieGildeAddOn/loadsave/loadsave_c/ls_LoadBuildingEntityState.c`

## 72b. a locally exact nesting fix can still lose to the cascade it triggers

Same function (2026-09-13): the `+0xc`/`+0xd` call sites spelled
`(load_result + const) + idx` while their `+9`/`+0xa`/`+0x10` siblings spell
`(idx + load_result) + const` — and the siblings match.  Normalising all four
anomalous sites to the sibling nesting emits exactly the reference shape at
both call sites (`mov eax,[esi+0x71]; lea ecx,[ebx+eax+0xc]`, the cross-call
`lea ebp,[ebx+0xd]` hoist gone; aligned 401 -> 414) and kills the +144 middle
desync — but the object stays span-neutral while the previously-aligned tail
(0x0429-0x054b) recolors wholesale (`mov [eax],ebp` becomes
`mov [eax],0xffffffff`, slot shifts, an extra `push edx`): linked +672
(728 -> 1400).  Reverted.  Section 70's lever is confirmed real and at the
same time not link-profitable in this body: a shape fix that changes which
values are live re-runs the allocator over everything downstream.  Do not
re-try without a plan for the tail recoloring.

`src/server.dll/DieGildeAddOn/loadsave/loadsave_c/ls_LoadBuildingEntityState.c`

## 73. `base + idx*0x40 + idx` always folds to one `[reg+reg]` operand

`gm_AllocGebaeude` (0x100174d0): nineteen spellings -- pointer cast, array subscript,
two-step pointer, `idx << 6`, `(unsigned)` cast, `int*`-scaled, `&arr[..]`, named
intermediates, split across two statements -- **all** emit `mov cl,[eax+ebx]`.  The
reference's materialised form (`mov ecx,eax; add ecx,ebx; mov cl,[ecx]`) is not reachable
from C at this site.

A wall: the indexed addressing mode is chosen whenever msvc6 can express the sum as
`base + index`, and no spelling suppresses it.  (The site was reached here only by a
scheduling barrier, which section 69 rules out.)

## 74. msvc6 folds byte-identical early-return epilogues unconditionally; the reference folds none

The wall behind every "the reference keeps N epilogues and we keep one" note in this
project, now measured rather than assumed.

On `gm_FindNextFilteredEntity` (0x10016f80) the reference has **five `ret` sites and merges
none of them** — three short ones (`xor eax,eax; pop esi; ret`, at `+0x17`, `+0x27`, `+0x75`,
all byte-identical) and two long ones (`pop edi; pop ebp; pop ebx; pop esi; ret`, at `+0x141`,
`+0x155`, byte-identical).  Each short one is reached by a **2-byte** conditional
(`jne +4` / `jle +4` / `jb +4`) that jumps *over* an inline fall-through return.

Our object keeps **two** `ret` sites: one short, one long, with five `rel32` branches
(`je 0x100170d2`, 6 bytes) into the shared short block.  So the cross-jump is **not**
downstream of any difference between the exits — the exit paths are byte-identical in the
reference and it still does not merge them.  Our compiler merges unconditionally.

**It is not a C-shape problem, and this is the evidence that settles it.**  A 352-byte
standalone TU (`.scratch/l8/m2.c`) carrying the target's exact guard/loop structure
reproduces the reference's prologue *byte-for-byte* — `mov eax,[g_entity_ptr]; push esi;
xor cl,cl; lea esi,[eax+0xa900]; mov eax,[g_entity_type_table]; test eax,eax` — and still
folds all three early exits into one far block.  `/O1`, `/O2 /Os`, `/O2 /Og-` and
`/O2 /Ot /Oy-` all give two `ret` sites as well.

Consequence: **eight return spellings have now been compiled across two passes and all are
inert**, which is what the wall predicts.  Do not spend probes trying to make an exit unique.
Recorded so the "two epilogues against the reference's three/five" note that recurs in this
project's file headers is recognised as this wall and not as an unsolved shape.

`src/server.dll/DieGildeAddOn/game/spiel_dumpD.c`

## 75. A prologue-fidelity lever, and a past "climb win" that cost it

`gm_FindNextFilteredEntity` (0x10016f80): **`end = g_entity_ptr + 0xa900;` must precede
`if (g_entity_type_table == 0)`** for the reference's prologue to come out byte-exact.  With
that order the compiler emits

```
mov eax,[g_entity_ptr]; push esi; xor cl,cl; lea esi,[eax+0xa900];
mov eax,[g_entity_type_table]; test eax,eax
```

which is bytes `0x0`-`0x15` exactly.  Commit `551bea67`, accepted at the time as a climb win,
moved that assignment *below* the guard; the byte-exact prologue is lost and `matched` falls
130 -> 127.  A later variant that also drops the redundant `match = 0;` at `candidate:`
restores the prologue through `+0x15` — the only variant that does — but scores 57 once the
far-jump guards dominate.

Two lessons: a climb metric can accept a commit that is locally worse in a region it does not
weight, and the guard/assignment order around an early-exit prologue is a *lever* worth
checking whenever a function's first 0x20 bytes are wrong.

`src/server.dll/DieGildeAddOn/game/spiel_dumpD.c`

## 76. A `volatile` read at a *post*-loop test blocks the loop's entry-guard fold

The cheapest win of the last stretch, and a shape worth checking first when a loop's entry
guard retargets.

`vfs_ReadCompressed` (0x10008a90): the guard's `jbe` at `0x10008b0f` targets the **result**
epilogue (`0x10008c59`) in the reference, but our build targeted the merged `done` test block
(`0x10008c51`), because the post-loop test read `done` through a `volatile` qualifier and that
blocked msvc6 from proving `done == 0` on the entry edge.  Making that **one** test plain --
`if (done == 0)` -- while leaving both `return` reads and the in-loop read volatile removed
exactly that hunk: `matched` 447 -> 448, `matched-reloc` 467 -> 468, object/real/aligned
unchanged, hunks 8 -> 7, and **-1 at the link**.

Reach for it whenever an entry guard retargets because a value could not be proven on the entry
edge: check whether the *post*-loop test reads that value through a volatile qualifier.

**And it is per-site, which is the refinement of allocator Finding 61.**  Making the same tail
plain at *all* sites collapses the function: object 496 -> 480, real `0x1f0` -> `0x1e0`,
`matched` 447 -> 21.  Those volatile reads are what keep `done`'s and `result`'s memory homes,
so one qualifier can be a lever and its neighbour load-bearing in the same five lines.

`src/server.dll/Units/vfs/vfs_ReadCompressed.c`

## 77. Group same-kind memory operations to match the reference's store sequence

Two wins from one rule: when the reference performs same-kind stores adjacently
and ours scatters them between other operations, regrouping to the reference's
sequence closes bytes even when no single store is wrong.

`cm_ExSellObjekt` (0x1000d930): the reference runs the season loops
(FindSlotById at 0x1000ddc8/df9) BEFORE source-finalize (0x1000de10+); ours ran
them after. Moving the whole dest-season block above `dest_object =
dest_game_object` — object 613/861 → 684/910, linked 1404 → 1346 (-58, -2
outside = -60). `gm_AllocSpieler` (0x10018850): the three byte-copies
(slot[9]/[0x164]/[0xc]) grouped ahead of the three strcpys — linked 2861 →
2857 (-4). `ls_LoadBuildingEntityState` (0x100128f0): `current_index = 0;`
hoisted above the aux-count read, matching xor-zero/read/realloc/re-read/test
— linked 728 → 675 (-53).

The rule is order, not spelling: every spelling probe on the same regions had
already failed. Read the reference's block/store sequence from disassembly
first; move whole blocks to match. It is 1-for-13 as a blind method — it only
pays where source order was never directly compared during reversing. Where
source order already matches (Tracked, Objects, PCQ, Gebaeude, vfs mode arms),
regrouping loses or is inert.

`src/server.dll/DieGildeAddOn/command/command_c/cm_ExSellObjekt.c`
`src/server.dll/DieGildeAddOn/game/spiel_c/gm_AllocSpieler.c`
`src/server.dll/DieGildeAddOn/loadsave/loadsave_c/ls_LoadBuildingEntityState.c`

## 78. A one-token guard reorder can be worth one linked byte

`cm_ExSellObjekt` (0x1000d930): the source-block category guard tests `'\x06'`
first (`'\x06' || '\x02'`; dest-side twin keeps `'\x02'`-first) — object +1/+1
both rulers, linked 1346 → 1345 (-1). The dest-twin mirror is byte-neutral, so
the effect is positional, not logical: keep the twin that moves bytes, leave
the twin that does not. `gm_AllocSpieler` (0x10018850): father-wins copies in
0xc/0x1d0/0x217 order (was 0x217-first) — linked 2857 → 2856 (-1);
per-trait selection best_mother-first — object +7/+7 with aligned -2, linked
2856 → 2848 (-8). `m_AllocTracked` (0x10006580): node zero-stores reversed —
object +1/+1, linked 93 → 92 (-1), even though the reversed order contradicts
the target's emission (a downstream scheduling accident, not a region fix).

Small wins compound the same way large ones do: verify each at the link
(one-token changes can shift jump encodings ±bytes elsewhere), and keep a win
whose mechanism note honestly says "scheduling accident".

`src/server.dll/DieGildeAddOn/command/command_c/cm_ExSellObjekt.c`
`src/server.dll/DieGildeAddOn/game/spiel_c/gm_AllocSpieler.c`
`src/server.dll/Units/m_alloc/m_alloc_c/m_AllocTracked.c`

## 79. Position beats alignment, repeatedly

Three landings (Spieler best_mother-first +7/-2 aligned → -8 linked; Tracked
reversed stores +1/-5 aligned → -1 linked; CopyData secondary low-before-high
+11 aligned → +3 linked, reverted) establish the ranking: when object-level
`matched` rises and `aligned` falls, the link is the only adjudicator, and it
has favoured position twice against alignment once. Never keep or reject an
aligned-positive/matched-negative candidate without `scripts/linktest.sh`;
never cite aligned-only gains as wins.

## 80. xor-xor RMW beats xor-then-or when the scheduler prefers it

`vfs_OpenStream` (0x10009020): finalize as `g_stream_count = g_stream_count
+ 1` plus `& 0xf6 ^ m14 ^ m18<<3` instead of `^ m14 | m18<<3` — object +8/+13,
linked 245 → 233 (-12). The target itself emits xor-then-or, so the gain is
positional/scheduling, not opcode truth. Spelling the RMW to suit the
scheduler rather than the reference is legitimate when the link confirms it;
note the dishonesty in the header so the next reader does not "fix" it back.

`src/server.dll/Units/vfs/vfs_OpenStream.c`

## 81. CrashDump frame rule: every 0x280 path costs ~50 bytes

Four independent routes to the target frame (`space`-drop, hProcess reload,
pDbgBuf kill, nested-loop shape) all land `sub esp,0x280` exactly and all lose
~45-60 matches on both rulers. The frame counts overlapping live ranges
([esp+0x44] is a shared spill: hProcess across SetFilePointer, reused for the
Eip temp), not use-count or declaration-count — adding uses cannot free it,
dropping scalars shifts codegen elsewhere. Do not link-test another 0x280
variant unless it also holds matches; the frame will close only together with
the bytes, not before them.

**Round 174 — the rule survives its strongest test, and the mechanism is now
known.** A block-order map of this function found `pCtx` to be the section-84
value: defined at entry, then unread for ~1200 bytes (CreateFile, ReadFile,
VirtualAlloc, decrypt, date/time, dispatch). The reference lets that span
*reuse* pCtx's spill slot (hDbgFile takes `[esp+0x28]` at 0x1000281d) and
re-materialises pCtx from memory at each later use — `[esp+0x2c]` at the
frameInfo fill and again inside the walk loop at 0x10002cb8. Ours pinned it in
a register across the whole span, which is the surplus dword.

Reading the loop guard through the parameter instead of the local ends that
live range — a one-token edit, `pCtx->Eip` to
`pExceptionPointers->ContextRecord->Eip` — and it produced `sub esp,0x280`
exactly, with aligned instructions *rising* 392 -> 407 and the object shrinking
2128 -> 2123. That is the first 0x280 route to gain alignment rather than lose
~50, so it earned the link test the rule's proviso allows. **It still lost:
+66 linked (8,871 -> 8,937), the function's own row +58.**

Sixth confirmation, and the sharpest: the frame is reachable, cheaply, without
deleting anything — and closing it alone still costs bytes, because the smaller
frame moves every subsequent `[esp+N]` displacement. Do not spend further
rounds on the frame as a target. The remaining reference-order differences
(deferred `push ebx; push edi` at 0x1000282c; `pCtx->Esp` parked in ebx from
0x10002931 across the date/time region) are the real levers, and they would
have to land *with* the frame in one change, not before it.

## 82. `fimul` needs an int memory home AND a live ST(0), supplied by two separate constructs

`fimul dword [mem]` multiplies ST(0) by an integer read straight from memory.
msvc6 emits it only when **both** conditions hold at the multiply, and each is
produced by a different source construct:

1. the integer operand has a *memory home* — a plain alias (`int v; int* a = &v;
   *a = byte;`) supplies one, a bare `int` local does not (it stays in a
   register), and `volatile` supplies one but also pins ordering and costs the
   schedule;
2. the running double is *still on the FPU stack* — which requires the product
   to be split across statements so nothing forces a store between them.

On `gm_AllocSpieler` (0x10018850) the reference's per-trait interpolation at
0x10018f4c is `fld [esp+0x10]; fsubr qword[7d8]; fimul dword[esp+0x14]; fild;
fmul dword[esp+0x10]; faddp`. Neither half alone reaches it: the alias home by
itself emits `fimul` at the *fast paths* instead, and the ordering rewrites by
themselves emit `fild`+`fmulp` everywhere. Together:

```c
double t; int fbh; int* fb_alias;
fb_alias = &fbh;
t = g_dbl_const_7d8 - (double) acc;      /* (1-acc) stays on ST(0) */
*fb_alias = *(unsigned char*) (father + 0x80 + i);
t = t * fbh;                             /* fimul dword [esp+...] */
```

**Integerizing the whole product is the opposite of the fix.** Computing
`(cw*fb + w*mb)` in the int domain and converting once emits a single `fild`
of the sum, so nothing is live on ST(0) and `fimul` cannot appear — three such
variants scored 352-382 against a 748 baseline.

The shape is recorded because it is *reached*, not because it is kept: the
object comes out 3680 against a 3689 real body and the link regresses +409.

**Correction (round 173).** This section first claimed the residual nine bytes
*were* the second multiply, where the reference uses `fild` + `fmul`-mem +
`faddp` and the form above emits `fild` + `fld st(2)` + `fmulp` + `faddp`.
That was wrong, and measuring it is what showed so. The memory form is
reachable — give `acc` a `volatile float*` alias and msvc6 emits the
reference's window verbatim, `[esp+0x14]` slot and shared int home included —
and reaching it makes the object *larger* (3728, |Δ|=39 against 3680's |Δ|=9)
instead of closing the gap. The second multiply is locally size-neutral
(`fmul`-mem is 4 bytes against `fld st(2)`+`fmulp`'s 4); the growth is
`volatile` pinning FPU ordering across the whole function for ~48 bytes of
collateral. So the second multiply is a separate, solved, affordable problem
and the nine bytes live elsewhere in the loop or its exit.

The general lesson outlives this function: **a `volatile` qualifier buys a
local instruction form and charges for it globally.** Measure the whole
function, never the window you were aiming at.

`src/server.dll/DieGildeAddOn/game/spiel_c/gm_AllocSpieler.c`

## 83. A measurement pipeline must refuse stale inputs, or it will report the last good number

`scripts/split_link.sh` reads five stock `LIBCMT` copies out of gitignored
`.scratch/`. A scratch cleanup deleted them; the script died in its first step,
and because the caller chained `split_link.sh; postlink_residual.py` with `;`,
the residual tool happily re-measured the *previous* build and printed the same
figure for five rounds.

Two properties make a verification trustworthy, and this pipeline had neither:

- **every stage's exit status is checked** — `;` between a producer and its
  measurer hides the producer's failure, and `grep`-ing only the interesting
  line hides the error text as well;
- **the measurer validates its own inputs** — `postlink_residual.py` now
  refuses a build older than any `src/**/*.c` and names the offending files,
  so a binary that predates the edit under test can never be scored.

`scripts/gate.sh` now performs the link and the residue measurement itself and
fails on either, which makes the per-round residue an assertion rather than a
recollection. Regenerable inputs that live in ignored directories should also
be re-derivable by a documented command: these were recovered with
`docker create`/`docker cp` from the toolchain images.

`scripts/postlink_residual.py`, `scripts/gate.sh`

## 84. Sink a value's definition into the guard that uses it, and let the other region keep its own register

The largest win on `cm_ExSellObjekt` after the season-block move (-173 linked,
9,067 -> 8,894) was moving one assignment down into the block that reads it:

```c
-	dest_object = dest_game_object;
 	if (*(int*)(cmd + 0x14) != -1) {
 		/* source-finalize: reads the SOURCE object */
 	}
 	if (*(int*)(cmd + 0x10) != -1) {
+		dest_object = dest_game_object;
```

The reference loads the dest object at `0x1000df0a`, *inside* the
`cmd+0x10` guard, and runs source-finalize at `0x1000de10` entirely on the
source object in `ebx`. Defining the dest pointer above source-finalize made
that whole region compete for the dest pointer's slot and drifted the schedule
to the end of the function: object `685/911 -> 829/1047`, `rebrew test`
`796 -> 971`.

Two conditions are worth carrying to other functions:

- **Placement inside the guard is the lever, not the statement order.** The
  same assignment written at top level immediately *before* the `if` scores
  92/2057 — catastrophic. msvc6 sinks a load into the taken arm only when the
  source writes it inside that arm; written just above, it stays live across
  the guard and pins a register.
- **The object legitimately shrank** (real 2053 -> 2025, span 2064 -> 2032).
  A real body below the reference span is composition-legal (allocator
  Finding 58), so a shrinking object is not by itself a span break — but
  fixed-offset scores cannot rank it, and only the link can.

Diagnostic: when one region's diff is clean and everything after it drifts,
look for a value defined before that region and used only after it.

`src/server.dll/DieGildeAddOn/command/command_c/cm_ExSellObjekt.c`

## 85. The boundary of section 84: it moves a value's definition, not a constant

Section 84's lever — sink a definition into the guard that reads it — paid
-173 on `cm_ExSellObjekt` and -23 on `gm_AllocSpieler`. Applying the same
block-order mapping to two more functions found the shape present in both and
unreachable in both, which fixes the rule's scope.

**`cm_ExCopyEntityData` (0x1000ec00): the pinned value is a constant, so
source scoping cannot move it.** The reference materialises `mov ebp,0xffff`
at 0x1000edc0 and holds ebp across the whole src-scan region to serve a guard
0x9c bytes later — a textbook section-84 signature, and the reason its src
scan needs no entry guard (ebp is simply unavailable to the loop). Ours spells
both guards as inline `cmp word ptr [...],0xffff`, which leaves ebp free, and
msvc6 spends it on a 3-instruction scan entry guard.

Declaring a shared `0xffff` local *inside* the dst-valid guard — the correct
section-84 placement, which earlier passes had not tried — is **byte-identical**
to the inline spelling. msvc6 rematerialises an immediate at each use however
the source scopes it. A `volatile` variant (tried earlier) homes it to the
stack, which is the wrong mechanism entirely.

So the lever needs a value with a real definition site: a pointer, a loaded
field, a call result. A constant has no definition to move.

**`ls_LoadBuildingEntityState` (0x100128f0): the shape was already spent.**
Round 130's hoist had put both of this function's section-84 values (`offset`,
`neg1`) inside their guard already. A third candidate (`current_index` before
the aux region) looked identical in form but is a *consequence* of the aux loop
being its own region: that counter shares `[esp+0x10]` with the outer loop's,
so splitting the live ranges forces a second slot and shifts the frame
(probe: 627/1463 against a 690 baseline, `rebrew test` -61).

Two practical rules follow. **Map first, probe second** — both lanes produced a
complete ordering map, and in both cases the map explained the failure before
the probes confirmed it. And **a function whose order already matches is done
for this lever**: `cm_ExCopyEntityData` agrees with the reference at 12 of 16
top-level blocks, and its four differences are all allocator-downstream
(loop rotation, cross-jumped epilogues, the ebp guard, an address split).

**A warning about maps produced in bulk (round 177).** Two leads from a single
round-176 mapping pass were both false, and both were phrased confidently enough
to fund a probe round each. The first claimed reversed dispatch arms (refuted:
zero hunks in the region). The second claimed the reference *hoists*
`mov edx,[esi+0x71]` above the 0x1e-arm loop while ours sinks it — the reference
in fact re-reads that field at all nine sites, exactly as we do, and the loop
back-edge lands on a load. Three probes built on the phantom axis cost
-344, -158 and -613 matched.

The real difference at those sites is *load-versus-push scheduling*: the
reference emits `mov edx,[esi+0x71]; mov ecx,ebx; push edi; push 1; add ecx,edx;
push 4; push ecx` — load first, address arithmetic interleaved with the pushes —
while ours pushes first and then loads. The `lea` operand order that the map
fixated on is a *symptom* of which register the load landed in (section 70:
operand order in a commutative address expression is inert on its own).

Rule: **verify a map's claim against the disassembly before spending a round on
it**, especially a claim about hoisting, ordering, or duplication — those are
exactly the properties that look different in source text and identical in
emitted bytes. One `grep -c` on the reference listing would have caught both.

**Third and fourth boundary cases (round 176).** `gv_ExAllocGraveyardWorker`
(0x10011bf0) maps as identical to the reference in 21 of 22 top-level blocks;
its one difference is a three-store triple deliberately held *off* reference
order because the positional ruler pays 671 for our order against 668 for the
reference's. Its genuine section-84 candidate — `slot_ptr` defined above the
count guard where the reference loads it inside, at exactly the reported first
diff — is **byte-identical** when moved: msvc6 already sinks that load, and the
writeback was dead. `ls_LoadBuildingEntityState`'s dispatch region likewise
turned out to have zero hunks.

So the lever's real precondition is: **the function's emitted block order must
actually differ from the reference's.** Four of six functions mapped so far
were already in reference order, and on those the method's value is the map
itself — it retires the lane instead of funding more probes. Read the order
from emitted bytes (`instr_diff`, objdump), never from source text: msvc6
emits else-blocks innermost-first (section 59), so source order routinely
*looks* inverted when the emitted order already matches.

`src/server.dll/DieGildeAddOn/command/command_c/cm_ExCopyEntityData.c`
`src/server.dll/DieGildeAddOn/loadsave/loadsave_c/ls_LoadBuildingEntityState.c`
`src/server.dll/DieGildeAddOn/game/friedhof_logic_c/gv_ExAllocGraveyardWorker.c`

## 86. A join block is exiled when its fall-through predecessor must end in a reload + `jmp`

The inverse of section 84, and worth -200 linked bytes on one function.

`cm_ExSellObjekt` (0x1000d930) carried a -147 placement cliff: from 0x1000dfc1 to
the end, every instruction was byte-identical to the reference and 147 bytes late.
The round-179 census localised it but read it as a layout problem. It is not — it is
**register pressure at a join**.

msvc6 had enregistered `dest_dynamic_entity` in `ebp` across the `cmd+0x10` then-arm,
so that arm had to end by restoring the registers the join expected:

```
mov edi,[esp+0x10]; mov ebp,[esp+0x18]; jmp <join>
```

A block that ends in `jmp` cannot be the join's fall-through predecessor. msvc6
therefore laid the *else*-region inline and exiled the join — the player-slot store
and the `gm_SubObjekt` body — 147 bytes past it. The reference keeps nothing live
there: it reloads the pointer from `[esp+0x2c]` at the test (0x1000df97
`mov eax,[esp+0x2c]; test eax,eax`), its then-arm falls straight through into
0x1000df2a, and the else-region goes to the tail.

Forcing that one reload from source reproduces the reference's block order:

```c
if (*(short* volatile*) &dest_dynamic_entity != (short*) 0) {
```

Object 836/1052 -> 1037/1217, instruction count 678 -> **667 = the reference's
exactly**, COMDAT span 2032 -> **2064 = the reference's exactly**, `rebrew test`
977 -> 1149, linked **-200**.

Diagnostic: when a contiguous tail of the function is byte-identical but uniformly
displaced, look for a *join* whose predecessor arm ends in register restores. The
fix is to force the value out of a register at the post-join test — the opposite
move from section 84, which sinks a definition *into* a guard to free one.

Two cautions from the same lane. Reloading a second pointer as well
(`dest_owner_entity`) also kills the cliff but costs ~150 bytes — reload only the
value the join actually contends for. And duplicating the join body into both arms
to delete the join outright is catastrophic (336/2057).

**Screen candidates on the delta profile before funding a probe round (round 181).**
The qualifying signature is *one step that holds to the last aligned pair* —
`cm_ExSellObjekt` went to -147 at 0x1000dfc1 and stayed there to the final byte.
Function size and hunk count do not predict it. Two functions screened against this
rule and were correctly retired without spending a probe:

- `ls_LoadBuildingEntityState`: its largest step (+144 at ref 0x02f5) survives six
  instructions, collapses to -1, and the delta returns to **zero twice more** before
  ending at -3. Scattered hunks, no exiled join. (Its +144 window is also the
  `[esi+0x71]` load-versus-push region that section 85's round-177 warning already
  refuted as an axis.)
- `cm_ExCopyEntityData`: delta wobbles ±10 throughout, its +75 spike lasts two
  instructions, and the tail sits at +4 in an object whose size equals the
  reference exactly (912 = 912). A same-size object with a small wobble is
  register/schedule noise, not a displaced join.

A profile that returns to zero mid-body, or finishes within a few bytes of zero, has
no join to un-exile. Reading the profile costs minutes; a probe round costs hours.

**Second pre-check: the `jmp` census must show a built-only surplus.** The
precondition is not "our build has a restore+`jmp`" — it is that *we* jump where the
*reference falls through*. Align both `jmp` lists by source address and compare.
`gm_AllocSpieler` was screened this way: reference 26 jumps, built 27, and the single
built-only jump is a protected known bug, while the one restore-then-`jmp` join
(0x10018c28 / 0x10018c23) is **byte-identical on both sides** — the reference ends
that arm the same way we do. With no jump surplus there is no exiled join, and three
volatile-reload probes duly cost -429/-389/-351 matched, each breaking the span by
+16 (a homed stack slot) and destabilising the FPU region.

That last detail is the mechanism's real boundary: on `cm_ExSellObjekt` the contended
pointer was **dead across the arm**, so forcing it to memory cost nothing. Where the
value is *live* across surrounding loops, homing it buys a slot and reschedules
everything near it. Check liveness before reaching for the reload.

So the full screen, in order, before any probe: (1) does one delta step hold to the
last aligned pair? (2) does the `jmp` census show a built-only surplus at that point?
(3) is the contended value dead across the predecessor arm? Three cheap commands;
all three must pass.

**The jump surplus must be inspected, not counted (round 182).** A raw count
comparison mis-passes. Screening nine rows produced three apparent built-only
surpluses and all three dissolved once aligned by source address: `ServerMainThread`
had inverted branch polarity (reference `je` + `jmp` against our `jne` + `jmp`, equal
counts), `ahm_ExAllocAlchemist` had a reference `cmp edi,5; jl` folded into one built
`jmp`, and `vfs_OpenStream`'s "extra" jump was the shared jump table
`jmp [ecx*4+0x100092bc]` present on both sides. In each case one built instruction
stands where the reference has two — never a jump where the reference falls through.
Counting alone would have sent two of them into step 3.

**Measured rarity.** Twelve rows have now been screened against this signature and
exactly one — `cm_ExSellObjekt` — has it. Eight of the nine screened in round 182
finish at delta exactly 0; the ninth (`gm_FindNextFilteredEntity`) holds -4 for a
single aligned pair, and its real problem is a body-shape mismatch at 57.6%
alignment, not a displaced join. Treat section 86 as a rare, screened lever rather
than a general lane: the profile read costs seconds per row and retired nine rows
for zero probe rounds, which is exactly what the screen is for.

One operational note for whoever runs this next: **screen the function's own VA and
size**, not the mismatch-region start that residue tables report. `gm_AllocGebaeude`
is 0x100174d0 size 1088; the 0x10017530 that appears in a residue listing is 529
bytes into it and has no metadata entry of its own, so screening that address
measures nothing.

`src/server.dll/DieGildeAddOn/command/command_c/cm_ExSellObjekt.c`

## 86b. Store order IS a lever through a fresh pointer, inert through a stack buffer

Section 20 records that statement order does not move stores into the same buffer.
That holds for a *stack* buffer, where msvc6 knows the object and schedules freely.
It does not hold for stores through a pointer into memory the compiler cannot prove
non-aliasing for — a freshly `malloc`'d node, for instance. There msvc6 emits the
stores in exact source order, so their order is a lever.

`m_AllocTracked` (0x10006580) zeroes six fields of a just-allocated node. The
reference emits them `0x14, 0x10, 0x1c, 0x18, 0x20, 0x24` (verified at
0x100066bc-0x100066cb: six `mov [edx+N],ebx`), which is the exact reverse of the
natural declaration order the source used. Reversing the source makes the block
byte-identical to the reference and lifts aligned 225 -> 230 of 249, span-neutral at
obj 672.

**And it still loses: +1 linked.** The alignment gain is noise, which the `matched`
ruler said at the time (566 -> 565). The lever is real, the win is not — so the
natural order is kept deliberately, with a note at the site.

Two rejection modes worth naming from the same lane. An edit can win alignment and
lose on COMDAT span: `node->count_total > node->count_max` in place of the
`- ... > 0` form reached aligned 233 — the best figure measured on that function —
and did emit the reference's `cmp eax,ecx`, but shrank the object 672 -> 656, a span
that round 104 recorded as breaking position alignment for every later symbol.
Separately, the `- ... < 0` spelling of the slot guard is load-bearing for §8b
register residency: the plain `<` lets msvc6 fold one side into the compare and costs
99 on the reloc ruler.

**Boundary: the stores must actually differ in SOURCE order (round 185).** This
lever only exists when our source writes the stores in a different order than the
reference emits them. Where the difference is instead msvc6 *tail-merging* a store
common to both arms of an `if`/`else` into the join — while the reference duplicates
it per arm — there is no source order to change, and `volatile` does not help:
qualifying the store side is **byte-for-byte identical** to the baseline object, and
qualifying the load side sinks the store back into the arms but at the wrong position,
costing -370 matched.

Diagnose it by reading the *stores* specifically. On `gm_AllocSpieler` a census
recorded the mother-type copies as emitted `0x50, 0x58, 0x54` by the reference against
our `0x58, 0x50, 0x54` and concluded this lever applied. It does not: our **store**
order is already `0x50, 0x58, 0x54` (verified at 0x1001904d/0x10019056/0x1001905c
against our 0x10019052/0x10019056/0x1001906e) — the census had read our **load** order
off the disassembly. Loads get hoisted freely; only the stores carry the order.

`src/server.dll/Units/m_alloc/m_alloc_c/m_AllocTracked.c`

## 87. Audit a function's own header notes before trusting them — six for six

Every census run in rounds 178-182 found at least one false claim in the header of
the file it was censusing. Four censuses, four bad claims, each of which had been
sitting there long enough to redirect work:

- `gm_AllocSpieler`: the store-tail order was recorded backwards ([0xa] last,
  [0x20c] third; the bytes put [0xa] second at 0x100189c4 and [0x20c] last at
  0x100189f4).
- `CrashDumpUnhandledExceptionFilter`: "the body is 11 bytes longer, so the tail
  jump tables sit 11 bytes late" — the body is length-exact, `ret 4` sits at
  +0x729 on both sides, and all 279 table bytes are byte-identical in the object.
  Also "the call count is now the reference's 44": it is 43.
- `ServerMainThread`: a rounds 6-9 verdict that its two cold blocks could not be
  made to defer into gaps. A later round had fixed exactly that and nobody re-read
  the object; both sit at identical offsets in no hunk.
- `cm_ExSellObjekt`: a "dead [esp+0x44] spill the reference materialises" — the
  reference writes it at 0x1000dd2a and reads it back at 0x1000dd33 across a call,
  and esp-depth tracking shows our `[esp+0x3c]` is the same physical slot
  (frame+0x468). The real difference is push interleaving.

- The three tail rows (`srv_LoadBuf`, `m_AllocTracked`,
  `gm_CheckInventoryCapacity`): all three headers carried stale baselines —
  srv_LoadBuf's by 109 matched bytes, and m_AllocTracked's aligned count was off by
  five with its round-118 store-order claim **inverted in sign** (recorded as +1 on
  both rulers; actually costs five aligned instructions).

- `gm_AllocSpieler` a second time: the round-178 census built cluster #13's entire
  220-byte premise on a store-order difference that does not exist — it had read our
  *load* order as store order (see section 86b's boundary note). It also
  double-counted that cluster's register-name and `and reg,0xffff` items as fresh
  when the function's own blocker note already listed them.

- `vfs_OpenStream` and `gm_AllocGebaeude`: **the tool-managed blockers were stale
  too**, not just the prose headers. vfs's said `11B size gap (693 vs 704) — parked`
  when its real body is 701 = the reference exactly, its span 704 = the reference,
  and its instruction counts are equal at 197 vs 197 — the body it described no
  longer exists, and it named size as the wall when size is not the wall.
  Gebaeude's said `parked at 418/1078` against an actual 683/1088, stale by 265
  bytes. Both were refreshed with `rebrew diff --fix-blocker` (never by hand — that
  file is CLI-managed). The blocker field is *evidence about the present*; when a
  function moves and nobody re-runs the tool, it silently becomes a claim about a
  build that is gone. Detailed reasoning belongs in the `.c` header, which survives
  the refresh; the blocker should stay a measured one-liner.

**Systematic audit (round 186): 11 of 19 blockers were stale.** Auditing every
non-matching row against fresh measurement — rather than spot-checking — found the
base rate is far worse than the anecdotes suggested, and `blocker_delta` disagreed
with the current delta on 13 of 19. Two findings generalise:

- **A refuted blocker is worse than a stale one.** `cm_ExSellObjekt`'s named a frame
  wall, `ref 0x228 vs msvc6 0x224`. Both the reference and our object emit
  `sub esp,0x228` — I verified both. Its own `.c` header had already recorded the
  frame as fixed; the blocker went on advertising a wall that does not exist.
- **`--fix-blocker` deletes a blocker when it finds no structural diffs.** Use
  `rebrew blocker set <VA> "<text>" --delta N` to rewrite a blocker while keeping it
  a measured one-liner, and reserve `--fix-blocker` for rows whose claim is merely
  numeric.

  **Correction (round 187): the "no structural diffs" readings that motivated that
  caution were themselves an artifact.** The audit had reported four functions as
  having zero structural diffs despite carrying linked residue — a contradiction,
  since residue *is* differing bytes. Invoking `rebrew diff <VA>` directly shows
  `gm_ObjectsAvailble` 18 structural, `srv_LoadBuf` 25, `vfs_ReadCompressed` 11,
  `cm_ExProdObjekt` 5. The deletion risk is real in principle and the `blocker set`
  advice stands, but no row in this tree is currently in that state. When a
  measurement asserts something structurally impossible — zero differences yet
  non-zero residue — re-derive it with the tool directly before building on it.

Before overwriting any blocker, confirm the *reasoning* survives in the `.c` header —
on the 11 stale rows it did, except that two of them (`gm_AllocSpieler`,
`ServerMainThread`) were the sole record of their ndiff/cdiff hunk figures, which were
carried into the replacement text rather than dropped.

The common mechanism is that a note is written as a *conclusion* at the moment it
is measured, then outlives the state it described — usually because a later round
fixed the thing without re-reading the bytes. Two of the four were actively
harmful: they named an axis ("eliminate the dead store", "the tables are late")
that does not exist, and a round was spent aiming at it.

Practical rules:

- **Re-verify a header claim against `rebrew asm` before acting on it**, especially
  claims about placement, ordering, counts and dead code. One `grep -c` is cheaper
  than a probe round.
- **Timestamp claims and mark superseded ones in place.** A claim that was true at
  round 110 should say so, and when a later round spends the lever it describes,
  the old paragraph needs a SUPERSEDED marker — not just a newer paragraph below
  it, which readers hit second.
- **Prefer facts that stay true** (byte sequences, addresses, measured scores with
  their date) over conclusions that expire ("the highest-value untried lever").

## 88. A "span deficit" is code bytes plus alignment round-up — separate them before hunting

COMDAT sections are padded to an alignment (0x10 here), so a span figure conflates
two very different quantities. Confusing them sent two rounds hunting the wrong
number on `m_AllocTracked` (0x10006580).

The reference body is **658 bytes**, which pads to a **672** span with 14 trailing
nops. A candidate emitting **656** is already 16-aligned, so it pads to itself and
the span reads 656 — recorded at the time as a **"-16 span deficit"**. It is nothing
of the kind: the code is 2 bytes short, and the ceiling arithmetic is

```
656 -> 656      657 -> 672      658 -> 672
```

so the recoverable quantity was **+1 byte**, not +16. Hunting sixteen bytes in a
658-byte function is hopeless; finding one is a normal question.

Worse, the hunt had been aimed at the wrong regions (a `repne scasb` block and a
zero-register idiom, both length-exact on our side). The entire deficit was **one
instruction**: the reference materialises the value twice —

```
0x100067d8  8bc7  mov eax,edi
0x100067da  897e14 mov [esi+0x14],edi
0x100067dd  3bc1  cmp eax,ecx
0x100067df  7e28  jle
0x100067e1  8bcf  mov ecx,edi      <-- ref-only: the whole 2 bytes
0x100067e4  894e1c mov [esi+0x1c],ecx
```

— and stores the second field from the *second* copy, where we store from the first.
Supplying it with `count_max = *(volatile int*) &count_total` does hold span 672 at
aligned 233/249, the best figure on that function, which confirms the arithmetic. It
still loses **+40 linked**, because the `volatile` costs more elsewhere than the
alignment gains. So the lane closes on measurement rather than on a phantom.

**The ceiling also decides whether a lane can AFFORD an edit at all (round 190).**
Compute the upward slack, not just the deficit, before opening a lane. Two sibling
functions triaged together show the asymmetry starkly:

- `gv_ExAllocGraveyardWorker`: body **1040 = the reference exactly**, and 1040 is
  *itself* 16-aligned, so it pads to itself and 1041 jumps to 1056. **Zero upward
  slack.** Every one of its three faults is length-neutral, so there is nothing to buy
  and any one-byte growth costs sixteen bytes of span. That is why every "restore the
  missing bytes" idea on that function died, and it is the real reason it is a wall —
  not the register-role difference its header blamed for seven consecutive passes while
  the body had been length-exact since pass six.
- `ahm_ExAllocAlchemist`: body **1002**, padding to 1008 with the reference's own six
  trailing nops. **+6 bytes of genuine slack.** Its open float-tail lane can actually
  afford an edit.

So "length-exact with the reference" is not one condition but two: a body equal to the
reference *and* the slack that body leaves. State both when parking or opening a lane.

Practical rules: when a span looks short by exactly one alignment unit, compute
`real_body` and the round-up separately before planning anything; state deficits in
**code bytes** with the ceiling spelled out; and derive the target from the hunk
list's own byte widths (here ref-only `8bcf`+`3bc1`+`0f8d..` = 10 against built-only
`2bc7`+`0f89..` = 8, closing the gap exactly with no residual) rather than guessing
which region is short.

`src/server.dll/Units/m_alloc/m_alloc_c/m_AllocTracked.c`

## 89. Attribute residue by COMDAT extent, not body size — msvc6 emits tables past the body

`scripts/postlink_residual.py` attributed each differing `.text` byte to a function by
testing `lo <= off < lo + size`, where `size` is the **body** size from
`function_structure.json`. msvc6 emits switch jump tables and case-index maps *after*
the body inside the same COMDAT, so those trailing structures fell outside every
extent and were reported as a phantom `<outside the non-matching functions>` bucket.

`vfs_OpenStream` (0x10009020) is the clean example. Its recorded size is 667, so the
extent ended at `+0x82bb` — one `nop` short of its jump table at `+0x82bc`:

```
0x10009020..0x100092ba  body, 667 bytes      <- recorded size
0x100092bb              90                   nop pad, identical both sides
0x100092bc..0x100092cf  5 dwords             the "unattributed" bytes
0x100092d0..0x100092dc  case index map       identical both sides
0x100092dd..0x100092df  90 90 90             COMDAT 0x10 pad
```

Extending each extent to the next tracked function's start fixes it: the report went
from `0x21d5 of 0x21da inside … 0x5 are not` to **`0x21da of 0x21da … 0x0 are not`**,
and that function's true count is 238 rather than 233. The total residue is unchanged —
this is an accounting fix, not a byte gain — but a phantom category invites rounds
spent hunting a wall that is really part of a known one.

The five bytes themselves are worth recording as a closed question: each is exactly
`+1` in the low byte of a jump-table dword, all tracing to one origin at 0x10009056
where the reference emits `cmp byte ptr [eax],0` (3 bytes) and we emit
`mov al,[eax]; test al,al` (4). Removing that byte makes the loop and table byte-exact
and shifts everything after it — measured at match 450 -> 272. Five bytes recovered
for ~178 lost.

`scripts/postlink_residual.py`

## 90. Some "compiler fixed points" are service-pack decisions — sp5-pp as an oracle

Two walls documented as compiler fixed points are reproduced *exactly* by a different
MSVC6 service pack, without any source change. That reframes them: the reference's
scheduling is reachable, our backend simply chose otherwise.

A 3x8 sweep (`rebrew test --toolchain <name>`) over `msvc-6.0`, `sp1`-`sp5`, `sp5-pp`
and `sp6`:

- **Seven of the eight are byte-identical** on all three functions — same
  `match_count`, same `obj_size`, identical mismatch lists. This is genuine codegen
  stability, not a packaging duplicate: `C2.DLL` has five distinct md5s across those
  images and `C1.DLL` four. It upgrades "SP1-SP6 byte-identical" from a one-function
  anecdote to a measurement.
- **`msvc-6.0-sp5-pp` is the outlier, and it reproduces two walls:**
  - `vfs_ReadCompressed`'s stack-cleanup sinking. sp5-pp emits the reference's tail
    verbatim — `8b5e5c / 8b542424 / 894650 / 8b442428 / 83c414` — reading args at the
    pre-cleanup `[esp+0x24]`/`[esp+0x28]` with `add esp,0x14` sunk four instructions,
    where sp6 leads with the cleanup. Its mismatch list *ends at offset 395*. So the
    fixed point is the **cleanup placement**, not the argument reads — the earlier note
    blaming the reads was aiming at the wrong thing.
  - `cm_ExProdObjekt`'s global-load position. sp5-pp puts `mov edx,[global]` first at
    +204 followed by `33c0 / 668b4514 / 8b5d16 / 8bc8 / 895c2418`, all identical to the
    reference; sp6 sinks that load 13 bytes. First diff moves 205 -> 410.
- **Two other walls are NOT version-sensitive**: `cm_ExProdObjekt`'s byte 410 (the
  reference spends ebx, all 8 toolchains spend eax) and `m_AllocTracked`'s
  double-materialisation. Those stay allocator-level.

**Do not pin sp5-pp.** It is net-negative on all three functions (461/492, 722/991
SIZE_MISMATCH, 266/634 SIZE_MISMATCH) because it wrecks other regions. And a
per-function `toolchain` pin cannot change the deliverable anyway: the CMake build's
compiler is fixed by the toolchain file, so a pin moves `rebrew test`/`verify` verdicts
only — a divergence `rebrew cmake-flags` now reports rather than swallowing.

The value is diagnostic: **sp5-pp is a cheap oracle for "am I fighting the scheduler or
the source?"** If sp5-pp already emits the reference's shape for a region, no source
spelling under sp6 is likely to, and the lane should be retired rather than probed.

`src/server.dll/Units/vfs/vfs_ReadCompressed.c`,
`src/server.dll/DieGildeAddOn/command/command_c/cm_ExProdObjekt.c`

## 91. The sp5-pp oracle, applied to the whole residue table: 14 source-bound, 4 scheduler-bound

Section 90 established `msvc-6.0-sp5-pp` as a diagnostic: where it already emits the
reference's shape, no sp6 source spelling is likely to, so that lane should be retired
rather than probed. Running it over all 19 non-matching functions (38 `rebrew test`
runs, `--no-promote`, each function's own VA and size) turns that into a routing rule.

The screen is one-sided. sp5-pp is `SIZE_MISMATCH` on 15 of 19 rows against sp6's 6,
which extends section 90's "do not pin" from three functions to the whole table. But
the *classification* is the useful part:

**SCHEDULER-BOUND (retire these regions)** — sp5-pp equals or beats sp6:

| function | sp6 | sp5-pp | the region sp5-pp gets right |
|---|---|---|---|
| `gm_FindNextFilteredEntity` | 162/346, obj **342** | 171/346, obj **346** | tail epilogue ordering, +0x315-0x336: the cold `xor cl,cl; jmp` stub placed *after* the pop/ret (ref 0x100170bb `0f844effffff` / `5f 5d 5b 5e` / `c3` / `32c9` / `ebc7`). sp5-pp also fixes the 4-byte body shortfall, so that is a block-ordering decision, not a source defect. Probe the body, not the epilogue. |
| `ahm_ExAllocAlchemist` | 828/1002 | 834/1002 | two clusters: the store order around the two `rep stosd` fills (ref 0x1000bee6 `83c8ff` / `66c706ffff` / `8982a4580310` / `8d92fc580310`), and the FPU chain interleaved with integer stores (ref 0x1000c01e `db442414` / `d9461c` / `d80db8560210` / `895618` / `895c2414` / `dec1`). |
| `ls_LoadBuildingEntityState` | 820/1463 | 824/1463 | the `ls_ReadVfsDataChecked` argument idiom at +0x687-0x836 — `add ecx,edx` interleaved into the push run (ref 0x10012b9f `8b5671` / `8bcb` / `57` / `6a01` / `03ca`) against the folded `lea eax,[ebx+edx+4]` (0x10012bc4 `8d441304`). The per-site `add`-vs-`lea` choice is version-dependent. |
| `vfs_ReadCompressed` | 468/492, diffs to 417 | 461/492, diffs **end at 395** | the `add esp,0x14` placement, confirming section 90. |

**INDIFFERENT (1 row)** — `gm_CheckInventoryCapacity` is byte-for-byte identical under
both toolchains (same 97 mismatches at the same offsets). The one row this oracle cannot
screen at all.

**SOURCE-BOUND (14 rows)** — sp6 wins, so our shape is doing real work and probing can
pay. On the five heaviest (`ServerMainThread` -849, `srv_LoadBuf` -571,
`gm_AllocSpieler` -554, `gm_AllocGebaeude` -356, `vfs_OpenStream` -354) sp5-pp's first
mismatch moves *earlier* (967->586, 80->2, 134->2, 54->12) — it cannot even reach our
current prologue shape, which is strong evidence those spellings are load-bearing.

One row splits: `cm_ExProdObjekt`'s first diff moves 205 -> 410 exactly as section 90
predicted, so its **+204 global-load lane is scheduler-bound and retires** — but the
function as a whole is -254 and `SIZE_MISMATCH` under sp5-pp, so it classifies
source-bound. Retire the lane, not the row. Byte 410 stays allocator-level.

Practical use: classify before probing. A row where sp5-pp's first mismatch moves
*earlier* is source-bound; a region sp5-pp reproduces verbatim is scheduler-bound and
should be written up as a wall instead of probed again.

## 92. Three closures, and the codegen facts they establish

Round 191 closed the three smallest-residue functions in the tree. None yielded a byte,
but each produced a fact worth more than its residue, and two of them refuted claims this
document or a file header had been carrying.

### The image sweep is nine IMAGES but only three GENERATORS

Sections 90 and 91 swept eight MSVC6 images; a ninth existed
(`rebrew/msvc:6.0-win9x-win32`, `C2.DLL` md5 `3c21de2c`, matching none of the other
eight) and was missed. It is now registered as `msvc-6.0-win9x` so the CLI can reach it.

**But it is not a ninth generator, and the inference that it was is wrong.** Swept over
all 19 residue rows (171 runs, comparing full mismatch *lists* rather than counts), it is
**byte-identical to base/sp1/sp2/sp3 on all 19** and beats sp6 on none: 18 ties and one
loss. The mechanism: win9x ships `CL.EXE` byte-identical to sp3 — md5 `6e3f639e` on both,
against sp6's `5a4ec02b`, which I verified directly — i.e. the same 12.00.8168 frontend,
with the differing `C2.DLL` md5 being a differently-packaged build of the same code
generator.

**The rule this establishes: a distinct backend md5 counts IMAGES, not GENERATORS. Count
generators by emitted bytes.** Across these nine images there are exactly **three** real
generators on this table — the pre-sp4 class (base, sp1, sp2, sp3, win9x), the sp4/sp5/sp6
class (all 12.00.8804), and sp5-pp. No further image hunting is worth a round, and
section 91's four scheduler-bound retirements rest entirely on sp5-pp, unaffected.

The one divergent row is a *loss*, so it retires nothing: `gm_ObjectsAvailble` scores 683
under the pre-sp4 class against sp6's 686, three single-byte `[esp+N]`/register faults at
+0xa0, +0x111 and +0x19c that sp4's frontend bump *fixes*. Useful as confirmation that our
sp6 spelling is not the limiter on those bytes.

### `cm_ProcessCommandQueue`: tail-sharing, not arm order — and a greedy layout pass

Its header blamed "arm order" for 21 rounds. Our committed form **already has the
reference's exact block order** (arm5 0x38, arm6 0x44, unlink 0x78 against 0x38/0x48/0x78,
read off the objects). The real fault is **tail-sharing**: the reference shares one
`jmp advance` between arm5's fallthrough and arm6's exit while we duplicate it. The
arithmetic is exactly zero-sum — arm5+join 16B reference against our 12B, arm6 48B against
our 52B — which is why 15 bytes differ at *identical size* and why fixing either side
breaks the other.

The mechanism is worth recording on its own: **sp6 fuses `je unlink` + `jmp advance` into
one `0f85` even though the fusion is a net 3-byte loss.** It saves one byte locally and
costs arm6 four, because a 2-byte backward edge becomes a 6-byte near jump. The layout
pass is greedy per block, so no size-first flag declines it — `/Os`, `/O2 /Os`, `/Ox /Os`,
`/Oxs`, `/Os /Ob2`, `/Og /Os /Oi` all score 112-130 because `/Os` reshapes the function
wholesale. **A flag sweep cannot undo a greedy local decision that is globally wrong.**

Building the live-join form under all seven distinct generators puts the join at 0x3f
(reference-exact) in every one, but arm6 at 0x55 with unlink spliced into the freed
fallthrough slot. The fusion is invariant.

### `gm_ObjectsAvailble`: a downstream reschedule can be a rename's shadow

Its 25 faulting bytes are **one** allocator tie-break, traced end to end. Both builds free
exactly two registers into the match block: the target frees `{ebx, esi}` so row lands in
`ebx` (verified: `0x100160d3 bb55000000 mov ebx,0x55`), we free `{edi, esi}` so row lands
in `esi` — **and `esi` also holds `slot_base`**. So the `base = slot_base` copy must be
emitted before `mov esi,0x55` clobbers it. That true data dependency pulls the copy early,
consumes `edx`, displaces the item-def table into `edi`, and reorders the whole `shl`/`add`
chain.

The lesson generalises: **a 15-byte "second cluster" downstream of a register rename may be
the rename's shadow rather than an independent fault.** Test it by asking whether our
register choice collides with something already live. Four families of match-block
reshaping (a1-a6, f1-f6, n1-n6, x1-x6) were inert here, and this is why.

Also: 28 fixed-offset mismatches are **25 faulting bytes plus 3 collateral** — offsets
0x168-0x16a hold `c1e106 shl ecx,6`, byte-identical in both builds and displaced only
because a neighbour diverges in length. Quote which count is meant.

### `ahm_ExAllocAlchemist`: `faddp` is unreachable from any C expression

A 66-byte float-tail run reduces to **one byte**: ours `d8c1 fadd st(1)` against the
reference's `dec1 faddp st(1)` at 0x1000c034. The trailing `ddd8 fstp st(0)` is not an
independent fault — it is the cleanup msvc6 must add because non-popping `fadd` leaves the
operand on the x87 stack. Fix the byte and the run closes with it, so section 88 slack is
irrelevant: the correct form is two bytes *shorter*.

msvc6 collapses six spellings into **three** objects, and those are the only outcomes:

| shape | result |
|---|---|
| integer in a `float`/`double` local | correct `fild` first, but the local is live at the add, so msvc6 must use non-popping `fadd` |
| integer *not* in a local | it stays memory-resident and the add fuses into `fiadd [esp+0x14]`, which pops and does delete the `fstp st(0)` — wrong instruction, and it costs the whole preceding schedule (699 -> 377) |
| reassociated sub-first | `fsubr st(2)` + `fadd st(1)`, leaving two dead registers and emitting `fstp st(0)` **twice** |

`faddp st(1)` needs the conversion to be *both* a distinct `fild` (which requires a local)
*and* dead at the add (which requires no local). In msvc6's x87 model those are the same
property, so **no C expression can satisfy both** — closed by construction, not merely
inert. Two header claims died with it: that a `p1` local pinned `fld [esi+0x1c]; fmul`
(it pins the pair's *position*, never its operand roles — our baseline loads the constant
first) and that deleting `p1` reached 286 instructions at -15 (two different probes fused;
the -15 body is 287, the 286 body scores 398).

## 93. PROVEN is not a byte match, and the headline number hid that

A process finding rather than a codegen one, but it was silently mis-scoring every round.

`rebrew verify --full` printed `Verification: 281/283 passed, 2 failed`, and `scripts/gate.sh`
guarded that 281. But `passed` folds **PROVEN** in with EXACT and RELOC, and `AGENTS.md` is
explicit that PROVEN is semantic equivalence and *not* a byte match — every PROVEN entry
carries a non-zero delta. The real split here is **264 byte-matched + 17 PROVEN**.

That made the figure wrong in two directions at once:

- it **overstates progress** against a byte-identical objective (281 reads as "done" for
  264 functions that are, plus 17 that are not);
- a **RELOC -> PROVEN regression is invisible**: `passed` stays at 281 while the
  deliverable loses bytes, and a gate keyed on 281 stays green.

Fixed in both places. Upstream, the summary now prints the split and the accounting lives in
an importable `byte_match_counts()` helper, with a test that flips one RELOC to PROVEN and
asserts the byte-match count drops even though `passed` would not (`ab50856`). In this tree,
`scripts/gate.sh` gained a `BYTE_BASELINE` guard (264) checked independently of `BASELINE`,
verified to trip when the threshold is raised by one.

The general lesson for any metric this work leans on: **a status that is "good but not the
goal" must never be summed into the goal's counter.** The JSON had carried
`summary.byte_matched` correctly all along — the defect was only in the number humans and
scripts actually read, which is exactly where it does the most damage.

`scripts/gate.sh`

### The 117 lint warnings were all rebrew's own false positives (round 193)

Fixed upstream in `540b935`; the tree went from 117 warnings to **0**, with no
annotation changed — which is the point, because every one of them was unactionable.

**W028 treated the function inventory as ground truth.** That inventory is heuristic
(rizin `aaa` plus a capstone sweep) and it *merges adjacent functions* when the only
boundary is `ret` plus alignment padding. So the check fired on annotations that had
already compiled and compared byte-for-byte at that VA, advising "re-annotate the marker
VA" — which would have broken a matched function. 15 fired at once here, one of them
EXACT; `cm_ExSellObjekt` at 0x1000d930 was reported as inside `fcn.1000d8a0` even though
the reference has `ret` at 0x1000d92d followed by two `nop`s and a fresh
`sub esp,0x228` prologue, which I verified before changing anything. EXACT, RELOC and
PROVEN now outrank the inventory; every other status still warns, since there the
inventory is the only evidence available.

**The other 102 were a stale inventory**, truncated at 0x10012440 with 219 entries against
543 real functions — every warning named a VA above that line. `rebrew discover-functions`
refreshes it.

**And that refresh exposed a third, destructive bug**: `layout` was missing from the
known-target-key set, so a project carrying the position-alignment package warned
`unrecognized keys: {'layout'}` on *every* rebrew invocation — and an unrecognised key is
one a config rewriter silently drops. The discovery run deleted this tree's entire
`layout` block (image base, section geometry, exports, all 100 imports) and it had to be
restored from git. **An unrecognised-key warning is not cosmetic; it marks data the tools
will eventually throw away.**

## 94. `volatile` wins the alignment ruler and loses the link — three for three

Every `volatile`-pinning lever measured so far improves the aligned-instruction ruler and
then costs bytes at the link. The pattern is now consistent enough to price the lane before
funding it:

| function | what was pinned | aligned | link |
|---|---|---|---|
| `m_AllocTracked` | `count_total` through a volatile read | 225 -> **233/249**, the best on that function | **+40** |
| `ServerMainThread` | two global zero-stores reordered (86b proper, no volatile) | neutral | **0** |
| `gm_AllocSpieler` | six parent loads pinned to their stores | 662 -> **670/1056** | **+2** |

The `gm_AllocSpieler` case is the cleanest test, because it removed every excuse: it is
**byte-neutral** (real body 3689 both ways, so no §88 span risk), it *deletes* 11
insert/delete hunks rather than trading registers, and it moves the chain from 17/45 to
33/45 text-identical with the reference. It still cost +2.

**Why the rulers disagree.** `volatile` forces each load to its use, which is exactly what
the reference's schedule looks like locally — so the aligned ruler, which pairs
instructions positionally, scores it up. But it also forbids msvc6 from reusing a loaded
value anywhere else in the function, and the resulting register pressure shifts code
*outside* the region being fixed. The alignment gain is real and local; the loss is real
and remote.

**Round 196 makes it four for four, and the fourth is worse than a link loss.** A
`volatile match` on `gm_FindNextFilteredEntity` — the only candidate on that function that
qualified under the block-placement clause below — took the real body from 342 to **393
(+51)** and the span from 352 to **400 (+48)**, breaking the alignment ceiling outright
rather than merely costing bytes at the link. So the lane now has three link losses and one
span break, with no wins outside section 86's join-exile case.

**Practical rule: treat an aligned-only gain from `volatile` as unproven until linked, and
expect it to lose.** A `volatile` edit is worth landing only when it changes *block
placement* (§86, which paid -200 on `cm_ExSellObjekt` by un-exiling a join) rather than
merely re-pairing loads and stores inside a block. Re-pairing is cosmetic to the linker.

Also from this lane, two corrections worth carrying:

- The 344-byte "parent-wins cluster" was **174 bytes** of chain plus its displacement wake.
  A census that sums a region's mismatching bytes will attribute the wake to the fault; the
  chain's own byte multiset and kind multiset were *equal* to the reference's.
- `gm_AllocSpieler`'s header claimed a 20-variant CFLAGS sweep in which "every one scores
  identically". False: **`/Ow` is load-bearing** (766 -> 317 without it) and **`/Oa` is
  entirely inert**. A sweep that reports a flat result is worth re-running before it is
  cited as evidence.

`src/server.dll/DieGildeAddOn/game/spiel_c/gm_AllocSpieler.c`

## 95. A jcc width difference is a readout of stub distance, never a source lever

Branch-encoding width differences look like codegen faults and are not. `jcc` takes a
2-byte `rel8` form when the target is within ±127 bytes and a 6-byte near form otherwise, so
a width difference is *arithmetic* on the distance to the target — it reports where the
target block landed and nothing about the source.

`gm_FindNextFilteredEntity` (0x10016f80) shows it cleanly. The filter arms at +168, +184 and
+225 differ in width between the streams, and every width is exactly what its displacement
mandates on both sides — 7 of 7 correct, no encoding defect either way:

```
reference, no_match stub at +326:  +168 (disp 152) -> near 6B   +184 (136) -> near 6B
                                   +203 (121)      -> short 2B  +225 ( 99) -> short 2B
ours,      no_match stub at +223:  +172 ( 49)      -> short 2B  +184 ( 37) -> short 2B
                                   +199 ( 22)      -> short 2B
```

And the function's entire 4-byte length deficit reconciles from those widths alone: the two
early `jcc` are 6+6 in the reference against our 2+2 (**-8**), and the extra arm is a 2-byte
`jne` against our 6-byte `je`/`xor`/`jmp` (**+4**), netting **-4**. So the deficit is
downstream of *stub placement*, which section 17 already owns.

**Two consequences.** Never open a lane on a width difference: fix the block placement and
the widths follow, or accept the placement and the widths are correct as they stand. And
when a byte deficit reconciles exactly against branch widths, the fault is not where the
bytes are missing — it is wherever the branch target moved.

This also refutes by arithmetic an instruction section 91 gave: it retired that function's
epilogue ordering and said to probe the body instead, on the assumption the shortfall might
be a body defect. The body is **byte-count exact** (315 reference bytes against 315 of ours)
and the whole -4 sits in the retired region, so the body and the epilogue were one finding
seen from two ends.

Also recorded from that measurement — but **corrected in round 197, because the stated
cause was wrong**: `probe_function.py` does *not* compile standalone. It passes `-c <src>`
on the whole file (line 152) and every `.text` COMDAT body is md5-identical between
probe-built and CMake-built objects across all 18 files, so there is no standalone-vs-in-file
divergence to guard against. The 352-against-342 and 74-against-118 figures are the same
object under different *rulers*, which is a different and more useful trap — see section 96.

`src/server.dll/DieGildeAddOn/game/spiel_dumpD.c`

## 96. Four rulers, one object — always state which convention a number used

A round-197 audit measured all 19 non-matching rows two ways and found **zero** divergence
between what `probe_function.py` builds and what CMake builds: every `.text` COMDAT body is
md5-identical across all 18 files, including all 16 sections of `spiel622.c`. So no recorded
verdict in this project is a compilation artifact, and **no measured wall needs re-opening on
that basis.**

What the audit did establish is that four defensible numbers coexist for the same bytes, and
quoting one without its convention is how the confusion starts. On
`gm_FindNextFilteredEntity` all four were reproduced from one identical object:

| figure | convention |
|---|---|
| `obj 352` | COMDAT span, trailing alignment nops included |
| `obj 342` | same object, `rstrip(b'\x90')` — code length |
| `aligned 74/118` | probe's policy: union both sides' reloc masks |
| `aligned 87/118` | each side masks only its **own** relocs |
| `aligned 68/118` | both sides fully unioned |
| `matched 130` vs `match_count 162` vs `matched-reloc 210` vs raw 88 | four masking strictnesses |

Two rules follow.

**A bare `obj N` is span-or-code ambiguous by 0-15 bytes.** The gap equals that COMDAT's
trailing nop count on 18 of 19 rows. `m_AllocTracked.c` already documented this for itself in
round 92 — "the honest field is `obj_size`, the function's object bytes with the COMDAT's
trailing alignment nops trimmed" — and the same ambiguity applies to every other row. Only
`gm_CheckInventoryCapacity` hides a *real* 1-byte code shortfall inside its gap (COMDAT 400,
code 396, `rebrew test` 395).

**A bare `aligned N` is mask-policy ambiguous by up to ±89 instructions, signed both ways.**
Worst offenders if a quoted figure lacks its convention: `ServerMainThread` **-89**
(576 against 487), `gm_AllocSpieler` **+36** (662 against 698), `cm_ExCopyEntityData` +19,
`cm_ExSellObjekt` +17, `CrashDumpUnhandledExceptionFilter` +15, `gm_FindNextFilteredEntity`
+13. The two policies agree exactly on `m_AllocTracked`, `vfs_ReadCompressed`,
`gm_ObjectsAvailble`, `gm_AllocGebaeude` and `gm_CheckInventoryCapacity`.

And the standing rule this reinforces: **never compare a probe `matched` against a
`rebrew test` match_count** — 130 against 162 on identical bytes, because `coff_reloc.py`
masks only the object's validated relocs and compares over `min(obj_code, ref_size)`.

One latent hazard found while verifying: `spiel622.c` contains two **400-byte** COMDATs
(`_gm_CalculateProductionValue` and `_gm_CheckInventoryCapacity`), plus three 96-byte and
three 112-byte collisions. `probe_function.py` disambiguates through `build/split_poc.map`
and falls back to a prologue tie-break, which was verified to still pick correctly with the
map removed — but any *other* script selecting a COMDAT by size alone on that file will pick
the wrong one.

## 97. Spec audit: every live `__asm` block is inside the "original used asm" carve-out

The governing objective allows **no naked asm unless the original code was using it to**.
Round 198 audited that directly for the first time. Result: **six live `__asm` blocks, all six
compliant, zero naked functions.**

| file | function | VA | status | reference contains it |
|---|---|---|---|---|
| `server4.c:448` | `srv_InitBuildingTypeTable` | 0x1000b040 | RELOC | yes, at 0x1000b057 |
| `gm_AllocGebaeude.c:241` | `gm_AllocGebaeude` | 0x100174d0 | PROVEN | yes, at 0x10017611 |
| `m_AllocTracked.c:451` | `m_AllocTracked` | 0x10006580 | PROVEN | yes, at 0x10006730 |
| `m_alloc.c:220` | `m_init` | 0x100068e0 | RELOC | yes, at 0x10006929 |
| `m_alloc2.c:232` | `m_PoolAlloc` | 0x10006d20 | RELOC | yes, at 0x10006e0d |
| `vfs_ReadData.c:414` | `vfs_ReadData` | 0x10008e40 | RELOC | yes, at 0x10008f0c |

All six are the same alignment-prefixed block-fill skeleton, byte-identical in the reference
at every site:

```
8d0c7f lea ecx,[edi+edi*2]   83e103 and ecx,3   2bd9 sub ebx,ecx   7e0c jle
f3aa rep stosb   8bcb mov ecx,ebx   83e303 and ebx,3   c1e902 shr ecx,2
f3ab rep stosd   03cb add ecx,ebx   f3aa rep stosb
```

`vfs_ReadData` is the **copy** variant of the same skeleton — `f3a4 rep movsb` / `f3a5 rep
movsd`, and correctly *no* `xor eax,eax` since there is no fill value (verified at
0x10008f0c). Its C block spells movsb/movsd accordingly.

**Why these are asm in the original, not our shortcut.** Three independent signals:
the three-`rep` alignment pass (a plain `memset`/`memcpy` expansion emits two); the operand
homing, which matches the C block's named operands at all six sites; and the use of
callee-saved `ebx` as scratch, which no msvc6 `memset` expansion does. The template is also
absent from LIBCMT and LIBC, so it is not an out-of-line CRT routine the linker inlined.

**Independently re-measured rather than assumed.** On the cheapest block (`m_init`) all three
C alternatives collapse to the plain two-`rep` form and fall 15-19 code bytes short:

| shape | result | code length |
|---|---|---|
| `__asm` (shipped) | RELOC 162/162 | 162 |
| `memset` | SIZE_MISMATCH 97/162 | 143 |
| `char*` loop | SIZE_MISMATCH 98/162 | 147 |
| dword `for` loop | SIZE_MISMATCH 98/162 | 146 |

**The stronger prohibition is not violated either:** no `__declspec(naked)` and no
`#pragma naked` anywhere in the tree. All six are `__asm` statements inside ordinary C
functions, with `push ebp; mov ebp,esp` present on both sides. Every `naked` grep hit is
historical prose; the naked-`_emit` era was converted at `93ecf29`.

Cleanup done in the same round: `/DREBREW_ALLOW_NAKED` sat in the cflags of 0x100174d0 and
0x10008e40 while appearing **zero** times in either source. Measured byte-identical with and
without it (753/1078 and 472/472 unchanged), so it was dropped via `rebrew test --cflags` —
it was reading like a live naked-asm escape hatch that does not exist.

## 98. "Byte-identical outside `.text`" means *copied* outside `.text`

The objective is a byte-identical **file**, and every round of this session has measured one
section. Round 199 audited the rest, and the answer has two halves that must be stated
together.

**The deliverable is genuinely byte-identical outside `.text`.** Verified three independent
ways (a standalone stdlib PE parser, `cmp -l`, and the project's own script, all agreeing on
8,666 differing bytes with **100% attributed to `.text`**): headers, `.rdata`, `.data`,
`.reloc`, all 4 section headers compared as raw 40-byte blocks, all 30 optional-header fields,
all 16 data directories, the import table (**4 DLLs / 100 symbols, identical in order** — WS2_32
imported by ordinal), the export table (`Exit` ord 1 → 0x9350, `Init` ord 2 → 0x9320), and the
file size (286,720 both). Nothing there is broken and nothing needs fixing.

**But that identity is copied, not produced.** The raw link's own non-`.text` output diverges
from the reference by **43,705 bytes**, and the postlink fixers blit reference bytes over it
from `layout/server.dll/`. I verified the package holds verbatim reference slices:
`data.hex == ref[0x27000:]` and `reloc.hex == ref[0x35000:]`, both exactly `True`. So every
`differing 0x0` outside `.text` was a tautology — the metric was grading its own answer key.

Pre-fixer divergence, now printed by `scripts/postlink_residual.py` beside the `.text`
residue so the number stops being self-certifying:

```
.rdata   0x4f4 of 0x3000 (10.3%)      .data  0x893b of 0xe000 (61.3%)
.reloc  0x1bab of 0x9000 (19.2%)      headers  0xdf of 0x1000 (5.4%)
```

Four further gaps the residue number cannot show, worth knowing before anyone calls this done:

- **The stored PE checksum is a stamped constant that is wrong for the built content** —
  `0x4d328` shipped, `0x4b330` computed. It is the one header field that hashes the whole
  file, so it currently masks the `.text` gap and will be the last thing to become genuinely
  correct.
- **`.reloc` is inconsistent with the image it ships with.** Of 3,499 relocation entries, 223
  point at bytes that are not pointers in our build (RVA 0x278f: reference `0x10024040`
  against our `0x404015ff`). Those targets sit inside unmatched functions, so the divergence
  is already counted in the 8,666 — but nothing cross-validates `.reloc` against the shipped
  image, so a reloc-only regression would be silent.
- **1,978 bytes of the `.text` raw tail sit outside the measurement**, and the *measuring
  script* — not `rebrew.postlink.FIXERS` — zeroes 638 nonzero emitted bytes there (a stub
  DllMain `6a 01 58 c2 0c 00` plus ~100 `ff 25` IAT thunks). `rebrew postlink` would ship them.
- **23.6 MB of `.data` VirtualSize has no file bytes at all** (VirtualSize 0x174059c against
  raw 0xe000), so the BSS *size* matches but its runtime content is unverifiable from the file.
  A naive `min(VirtualSize)` comparison loop runs past EOF here.

Also corrected: AGENTS.md's "`.text` link shortfall … 0x3a84 short" is stale. The split-link
path now **overshoots** by 0x282 (`0x22ac8` against `0x22846`), placing its own DllMain at
0x23846, past the reference's `.text` end, where the fixer stamps the reference's
`AddressOfEntryPoint` of 0x1b9d4 over it.

Finally, a negative worth recording so nobody repeats the search: **neither binary has a Rich
header.** The DOS stub runs straight from the standard message to the PE signature, and both
stubs are byte-identical across all 0x80 bytes. So the exact MSVC build IDs cannot be
recovered from file metadata, and the compiler-identity question stays where section 92 left
it — answerable only from emitted bytes.

## 99. The measuring script and the shipping pipeline had drifted apart

Section 98 found that `scripts/postlink_residual.py` zeroed 638 real emitted bytes in the
`.text` raw tail while `rebrew postlink` shipped them. Round 200 chased that to the end, and
the two halves of the answer are worth keeping together.

**Fixed: the `.text` overshoot (638 bytes).** `_fix_data`'s tail trim starts at the
reference's **raw** size (0x23000), so anything the link emitted between the reference's
**VirtualSize** (0x22846) and that point survived — here a stub DllMain
`6a 01 58 c2 0c 00` plus ~100 `ff 25` IAT thunks the original build dead-stripped. The
script normalised the span for its own measurement, so the residue number looked clean while
the shipped binary carried the bytes. Now zeroed in the fixer: verified on the real binary,
638 nonzero → **0**.

The guard turned out to matter more than the fix. My first attempt zeroed that span
unconditionally and broke two existing tests — correctly, because **when the built `.text`
does *not* overshoot, that region is the reference's own section padding, which real linkers
fill with `0xCC`, not zeros.** Zeroing it would corrupt an already-matching build. The fix now
acts only when `built .text VirtualSize > reference VirtualSize`.

**Not fixable: the 3 stale operands (12 bytes).** The script also recovers operands whose
surrounding instruction is byte-identical but whose value is stale (our
`cmp eax,0x117f65b4` against the reference's `cmp eax,0x10139820`), using a locality test —
twelve bytes either side must match outside other operand slots. Its own comment says "those
are the fixer's job". They cannot be: that test needs the reference's `.text` bytes, and the
layout package is designed to hold **zero binary bytes at rest** — `prefix.hex` is the
`.rdata` prefix, not `.text`. I implemented it, measured it doing nothing, and reverted.

So `rebrew postlink` lands at 8,678 differing bytes against the script's 8,666, and the
remaining 12 are structural: closing them would mean shipping reference `.text` bytes inside
the layout package, which defeats its purpose. **The right reading is that 8,666 is the
script's number and 8,678 is the pipeline's**, and the gap is now understood rather than
invisible.

General lesson, which is why this is worth a section: **a measuring tool that "normalises"
anything has forked from the thing it measures.** Every such normalisation is a silent claim
that the pipeline will do the same, and that claim needs a test or it drifts. Two existed
here; one was a real bug and one was load-bearing by design.

## 100. `.data` is placement-bound: MSVC6 puts every string literal in its own COMDAT

Section 98 showed the raw link gets **61.3% of `.data` wrong** (35,131 of 57,344 bytes) and
that the shipped identity is copied from `layout/server.dll/data.hex`. Round 201 attacked it
and the attempt *failed usefully*.

**The measured shape of the problem:**

| metric | value |
|---|---|
| positional match | 22,062 / 57,344 = **38.5%** |
| content-multiset overlap (ceiling if bytes could be permuted) | 51,086 = **89.1%** |
| ⇒ present but **misplaced** | **29,024 bytes (50.6%)** |

So `.data` is **placement-bound, not content-bound**, and that inverts the obvious strategy.
Six literals the build was failing to emit were converted to real C strings; they emitted
correctly and `.data` got **worse** — 0x893b → 0x89d2 (+151 bytes) — because each added
literal grows the section and shifts every later object. **Emitting correct content cannot
improve this metric until ordering is solved.** Reverted.

**The mechanism, verified by dumping an object.** MSVC6 emits every anonymous string literal
into **its own COMDAT `.data` section**, separate from the object's single regular `.data`.
`Error.c.obj` has `.data` 0xa1 (regular) plus `.data` 0x3 and `.data` 0x6 as COMDATs. The
linker gathers each object's regular `.data` first and its COMDATs after, so **all named
globals precede all string literals within every object** — our map reads `_g_log_level_table`
0x7980 … `_g_log_default_name` 0x7a14 and only then `??_C@_02JNFB@at?$AA@` 0x7a24. The
reference **interleaves them in declaration order**: at `.data+0x84..0x108` the strings
`__server.log`, `gilde_server.log`, `__dbg.log`, `at`, `%s\%s` sit adjacent to the named
tables, not gathered behind them.

**What does and does not steer it:**

- `/Gy` is absent and irrelevant — it governs `.text` COMDATs.
- Object order is *already* steered (sources are VA-sorted), and the map confirms one
  contiguous `.data` run per object in that order. Not the problem.
- `/Gf` does **not** change COMDAT-ness; `/GF` moves literals to `.rdata` COMDATs, which is
  worse since `.rdata` already matches.
- **Naming a literal as an initialised `char[]` moves it into the object's regular `.data`,
  in declaration order** — probe-verified, and it reproduces the reference's shape. The tree
  already uses that convention (`char s_..._<VA>[]`).
- **Do not name a literal that several TUs share.** MSVC LINK folds identical `??_C@` COMDATs
  by name, so a shared literal exists once in the image; naming it locally breaks the fold and
  *adds* its length. `"D:\Develop\Units\m_alloc\m_alloc.c"` is shared by six TUs — naming it
  would have added 35 bytes. Convert only literals unique to their TU.

So the reference was almost certainly built from sources where these were named globals. The
lane is real but must be done **whole-TU at a time**, gated on the `.data` figure: six
literals lose, and the payoff only arrives once a TU stops shifting. ~29 KB is recoverable by
placement alone, with no new bytes.

**CORRECTED by section 101 (round 202): this framing has the dependency backwards.** A whole-TU
conversion was run and measured **exactly zero** — because the lever is blocked *behind* a
uniform section displacement, not ahead of it. Per-TU ordering is invisible while every object
is shifted by more than its own `.data` size. Remove the displacement first; only then does
within-object order become measurable, and only for TUs whose named globals and literals
actually interleave in the reference.

Two scoping corrections from the same measurement. The large cluster at `+0x2730..0x6c4e` is
**not** an ordering problem — of its 383 printable runs only 95 are emitted and **288 are
absent from the build entirely** (`"Usefull Sync"`, `"GamePath"`, `"\game.ini"`, …), none
appearing anywhere in `src/`: that is a content gap from missing or stubbed translation units,
a separate and larger lane. And `"This is Gilde talking, can you hear me?"` has **no xref
anywhere in the image** and sits between zlib's `z_errmsg` entries — dead data, unreachable by
any C edit.

The literals that *are* missing have three distinct causes, worth distinguishing before
anyone re-opens this: five are absolute-address casts (`(char*)0x10027448`) so no data is
emitted; `_main_:` is typed `extern int` and defined `= 0` in `link_stubs.c`, a wrong-type
placeholder; and the dead string above. All five push sites in the reference *are* relocated,
so C literals were the right shape.

## 101. `.data` placement was dominated by the link-order of the length pad, not by COMDATs

Section 100 concluded the named-`char[]` lever had to be tried **whole-TU**. Round 202 did
exactly that on `m_ReportGroupInfo.c` (the smallest TU with a meaningful literal count, 8
anonymous `??_C@` COMDATs) and the result is a **clean negative with the mechanism confirmed**
— plus the real cause found next door.

**The lever works at the object level, exactly as §100 predicted.** Converting all 8 literals
to named `char[]` collapsed the object from 9 COMDAT `.data` sections to one regular `.data`:

```
before:  .text 0x270 | .data 0x18 0x1a 0x18 0x46 0x39 0x1c 0x23 0x74 0x4c   (9 COMDATs)
after:   .data 0x1ac (regular, all 8 in declaration order) | .text 0x270 | .data 0x23
```

The map confirms the named symbols replace the mangled ones at the same relative order, and
the surviving `0x23` COMDAT is `"D:\Develop\Units\m_alloc\m_alloc.c"` — shared by six TUs and
folded by the linker, so naming it locally would *add* 35 bytes and break the fold. Leave
shared literals anonymous.

**But `.data` did not move: 0x893b before, 0x893b after — a delta of exactly zero.** Not worse
(unlike §100's six-literal attempt), just inert. The reason is that the strings' content was
never wrong: at their build VAs the bytes are already byte-identical to the reference. They sat
at `0x10030268` where the reference has `0x10028940` — a **uniform +0x7928 displacement**
shared by every game `.data` symbol. Within-object ordering is invisible while the whole
section is shifted by more than its own length.

**The +0x7928 was `data_restore_split.obj`.** `split_link.sh` generates that object as a
**length-only pad** (its bytes are a copy of the reference `.data` *tail*, and postlink
overwrites `.data` wholesale, so only its size matters — §2 of `msvc6-link-layout.md`), then
inserted it at rsp position 1. Its single regular `.data` is `0x74a0`, sitting at `0x10027030`
and ending at exactly `0x1002e4d0`, the first game string. It was pushing all real data off
the end of the section.

**Appending the pad instead of prepending it is a one-token change and it is worth 6008 bytes:**

| | `.data` differing | displacement of game data |
|---|---|---|
| pad first (old) | `0x893b` (61.3%) | `+0x7928` |
| pad last | **`0x71e3` (50.8%)** | `+0x488` |

`.text` also ticked `0x395d`→`0x395b`, `.data` raw stays `0xe000`, the shipped binary is still
byte-identical (`delta +0`), and the gate holds (187/187 lint, 0 errors, 281 passed / 264
byte-matched). Verified by a **control run with the conversion reverted**: pad-last alone gives
`0x71e3`, so the entire gain is the pad move and the conversion contributes nothing. The
conversion was reverted.

**The residual `+0x488` is `fold_literals.obj`** (`0x45c` at `0x10027030`, also linked first).
That object is a deliberate mechanism for folding member-library string COMDATs by name, not a
defect, so the last 1160 bytes of displacement are not free the way the pad was.

**What this means for the named-`char[]` lane.** It is not dead, but it is **blocked behind
displacement, not ahead of it**, and §100's "convert whole TUs and the payoff arrives" framing
has the dependency backwards. Per-TU conversion cannot pay while a uniform shift exceeds a
TU's own `.data` (`0x1ac` here vs `0x488` remaining). The order is:

1. Remove the displacement first — done for `0x74a0` of it; `fold_literals`' `0x45c` is what
   is left, and it needs a way to keep the fold without occupying the section prefix.
2. Only then does within-object ordering become measurable, and only for TUs whose named
   globals and literals actually interleave in the reference. **This TU has no named `.data`
   globals at all**, so there is nothing to interleave — converting it was always going to be
   a no-op once displacement was gone. Pick TUs from §100's `+0x84..0x108` example instead,
   where tables and strings genuinely alternate.

**It also moved the shipped binary.** The lane measured only the pre-fixer figure; re-linking
and re-measuring the deliverable gives **8,666 -> 8,665 differing bytes** in `.text`, with
**zero differing bytes outside `.text`** and the file size still exactly 286,720. Small, but it
is the first `.text` movement in this session that came from the *link* rather than from a
source shape — and it is free, in the sense that no C was changed.

Corollary worth keeping: **measure the displacement before attributing a `.data` figure to
content or ordering.** A uniform delta across every object is a link-order bug, and it is
cheaper to fix than any number of source edits.

## 102. Fold priority only needs to beat the first *member* COMDAT, not the whole link

Section 101 removed the `.data` pad from the head of the section and paid 6,008 bytes. The
same reasoning applies to the other object sitting there, and this one had a stated reason to
be first — which turned out to be true but far stronger than necessary.

`scripts/split_link.sh` generates `fold_literals.obj` (from `gen_fold_literals.py`) and
inserted it at rsp token 1, commented *"first, so our COMDATs are the ones kept"*. The purpose
is real: msvc6 derives a `??_C@` COMDAT name from the literal's contents and LINK folds
COMDATs by name, so re-declaring every member-library string makes the linker discard the
**members'** copies — that is what holds `.rdata` at the reference's size. But what the object
contributes to `.data` is not the literals (those are COMDATs); it is the
`const char* g_rdata_fold_refs[]` **pointer array**, which exists only to keep them referenced,
and at token 1 that array displaced every game `.data` symbol by **+0x488**.

**LINK keeps the first COMDAT of a given name, so the fold object only has to precede the
first *member* object that defines one** — not every game object. Objects of ours that appear
earlier are irrelevant: if one of them defines the literal first, the member's copy is
discarded either way. Scanning the response file's member objects for a `??_C@` symbol
(COFF symbol class 2, section > 0) and inserting immediately before the first hit puts the
array at **token 263** instead of 1:

| fold object at | `.data` differing | `.rdata` vsize/raw | dominant `.data` shift |
|---|---|---|---|
| token 1 (old) | `0x71e3` | 0x2e81 / 0x3000 | `+0x488` |
| token 263 (before first member `??_C@`) | **`0x6d33`** | 0x2e81 / 0x3000 | **`+0x20`** |

`.rdata` is unchanged at the reference's `0x2e81`/`0x3000`, which is the tell that the fold
still holds — a `.data` gain bought by breaking the fold would show up there immediately.
Shipped `.text` goes **8,665 → 8,664**, still zero differing bytes outside `.text`, file size
exactly 286,720.

**The cumulative effect of the two link-order fixes is the point.** Tracking the dominant
displacement of game `.data` symbols across rounds 202-204:

```
+0x7928  (pad at token 1)   ->  +0x488  (pad appended)  ->  +0x20  (fold object moved)
```

`.data` went `0x893b` → `0x71e3` → **`0x6d33`**, i.e. **7,208 bytes** recovered from link order
alone, with no C changed. And `.rdata` is now 60 of 111 located strings at **shift 0** — it was
never characterised before and is much closer than `.data`.

The general rule, which generalises past this project: **an object whose only job is to win a
COMDAT name, or to pad a length, should be placed as late as its job allows.** Both objects
here were placed at the extreme (token 1) when the requirement was merely "before the first
competitor" or "anywhere at all", and each cost the section's whole prefix.

## 103. `.rdata`'s whole residue is the import table, and the symbol order is already correct

`.rdata` was never characterised before round 205. It has **1,268 differing bytes in only five
clusters**, and all of them are one structure:

| cluster | size | RVA | what it is |
|---|---|---|---|
| `+0x0000` | 2 B | — | trivial |
| `+0x0070` | 297 B | 0x24070 | inside the **IAT** (dir 0x24000, size 0x1a0) |
| `+0x2614` | 90 B | 0x26614 | thunk array, partly matching |
| `+0x26dc` | 319 B | 0x266dc | **OriginalFirstThunk** array (same reference content as +0x0070) |
| `+0x2a06` | 1074 B | 0x26a06 | **import hint/name table** |

Resolving the dwords settles it: `+0x0070`'s entries are RVAs into `.rdata` pointing at
`0x00026bb2 -> "\x50\x01GetStartupInfoA"`, `0x00026acc -> "\x9f\x01HeapFree"` and so on — the
thunk arrays point at the very hint/name entries in the largest cluster. `+0x0070` and
`+0x26dc` hold identical reference content because an IAT and its OriginalFirstThunk array are
copies of the same list. **So 85% of `.rdata`'s gap is the name table and the remaining 15% is
the two thunk arrays that index it.**

**What is NOT wrong, checked directly:**

- The **DLL order matches**: `KERNEL32.dll, USER32.dll, WS2_32.dll, WINMM.dll` on both sides.
- The **symbol order matches for the named imports** — walking KERNEL32's thunk array on both
  sides gives the same 81 names in the same positions, same set. **Corrected round 206: that is
  81 of 100, not all of them.** WS2_32's 16 ordinal-only entries *are* permuted, so the true
  figure is **85/100 slots positionally correct**, costing exactly 30 bytes (15 in the IAT at
  0x2415c..0x2419c, 15 in the INT at 0x267c8..0x26808). Those slots come from
  `scripts/emit_thunks.py`'s `THUNKS` map and WS2_32.lib, **not** from `crt_imports.c`, and
  attempting to reorder them there measured worse.

So the raw link already produces the correct import *structure*; what differs is only **where
each name string lands inside the name table**. And the strings are not block-displaced the way
`.data`'s were — each moves by its own amount (`GetStartupInfoA` -0x1ac, `HeapFree` -0xb4,
`GetLocalTime` -0x282, `timeGetTime` +0x3c2), so this is an internal permutation of the name
pool, not a section-prefix problem.

That matters for effort allocation: **the link-order lever that paid 7,208 bytes on `.data`
does apply in principle but is blocked in practice** — a sharper statement than the original
"does not apply", and a testable one. `.data`'s wins came from uniform displacements caused by an object
sitting at the head of the section; `.rdata`'s residue has no uniform component to remove. The
name-pool layout is chosen by LINK from the order symbols are *first referenced*, which is a
property of the whole `.text` link rather than of any one object's position — and postlink's
`imports` fixer already produces the correct bytes in the shipped binary, which is why the
import table is byte-identical there (4 DLLs, 100 symbols, verified in section 98).

**Why it is blocked, measured (round 206).** Our name-pool order *is* literally the `/include`
directive order in `src/server.dll/crt_region/crt_imports.c` — verified — so the pool is
directly steerable. The reference's own law was derived and validated exactly: the pool runs
`[imports a game object references, KERNEL32 group first] [the four DLL name strings]
[the member-only LIBCMT imports]`, a clean partition with zero exceptions (31 game-referenced,
53 member-only), with the DLL name strings *interleaved* at pool indices 28/31/32/34 rather
than gathered. We cannot reproduce that shape because we pin all 100 imports up front as one
contiguous run.

The blocker is a hard coupling: `/include` order sets the **pool** order, but the **IAT slot**
order is what `.text` is position-aligned against, and the baseline already has 85/100 slots
correct. Three measured attempts:

| edit | `.rdata` | `.text` |
|---|---|---|
| baseline | `0x4f4` | `0x3898` |
| all 100 `/include` in reference pool order | 0x4e4 (-16) | 0x3954 (**+188**) |
| pin only the game-referenced imports | 0x4d4 (-32) | 0x394c (**+180**) |
| permute the three WS2_32 lines | 0x4f6 (+2) | +2 |

Every one trades ≤32 bytes of `.rdata` for ~180 bytes of `.text`, and the first two break
`cmake --build` outright (layout-map validation falls to 64.8%, i.e. they destroy position
alignment). Pool order and IAT order are independently determined — in the reference,
pool order != IAT order — so one cannot be fixed from `crt_imports.c` without disturbing the
other.

Practical conclusion: `.rdata` is the *closest* non-`.text` section (1,268 bytes, 10.3%) but it
is **not the cheapest**. It only closes once the pool can be reordered without moving IAT
slots, which needs the reference's two-group link structure (game objects pinning their own
imports, LIBCMT discovered afterwards) rather than a directive permutation.

**`.reloc` is downstream too, and the evidence is unambiguous.** Our `.reloc` VirtualSize is
`0x8370` against the reference's `0x10374` — **less than half** — with 41 relocation blocks
against 44. Seven reference pages are missing entirely, and they are overwhelmingly `.data`
pages:

```
page 0x025000    6 entries        page 0x02c000  212 entries
page 0x026000   14 entries        page 0x031000   16 entries
page 0x029000   16 entries        page 0x033000   28 entries
page 0x034000   58 entries        (350 entries of the reference's 3,526)
```

A `.reloc` entry exists for every absolute address the image needs fixed up at load time, so a
missing page means **we are not emitting the pointers that live on it**. Those pages sit in
`.data` (RVA ≥ 0x27000), which is precisely the section section 100 showed is still missing 288
strings' worth of content from stubbed translation units. `.reloc` therefore cannot be attacked
directly: it is a *readout* of what `.text` and `.data` contain, and it will shrink toward the
reference exactly as those do. Of the 37 pages we do emit, only 12 have identical entry counts,
which is the same story at finer grain.

## 104. Inlining is not the residue: call counts already match

A natural hypothesis for the three largest walled rows is that the reference inlined a callee
we still call (or vice versa), which would explain a large, diffuse, un-spellable difference.
**Measured, and it is false.** Counting `call` instructions in the reference against our own
object for each row:

| function | reference calls | our calls |
|---|---|---|
| `gm_AllocSpieler` | 55 | **55** |
| `cm_ExSellObjekt` | 31 | **31** |
| `CrashDumpUnhandledExceptionFilter` | 44 | **43** |

Two match exactly, and the third is *one call short* — the wrong direction for an inlining
story, since an un-inlined callee on our side would make us call **more**, not fewer.
`gm_AllocSpieler`'s reference body also makes real calls to 14 distinct targets
(0x10003640, 0x1000bd50, 0x1000c600, 0x100122e0, 0x10018130, 0x10018150, …), all of which we
call too. There is no inlined callee to reproduce and no surplus call to eliminate.

This rules out a whole class of proposed fixes — `__forceinline`, macro-ising a helper,
manually pasting a callee's body — for these rows. It also reinforces what sections 84-99
found from the other direction: the residue in the big rows is **register allocation and
instruction scheduling inside blocks whose call structure already matches**, not a
call-graph-shape difference.

The missing call in `CrashDumpUnhandledExceptionFilter` is a separate, already-recorded fact:
its own header notes the reference has 44 calls in the body against our 43, the absent one
being the final indirect `call [0x10024008]` (`UnhandledExceptionFilter`).

### The related question: does emitting missing `.data` content help `.text`?

Also measured this round, on `ServerMainThread` — the TU with the most absolute-address string
casts. Converting its 16 TU-unique `(char*) 0x...` references to real C literals (leaving two
shared ones anonymous per the fold rule) **does** improve the function:

| metric | before | after |
|---|---|---|
| `rebrew test` match_count | 2075/2434 | **2087** |
| probe `matched` | 1525 (62.7%) | **1603 (65.9%)** |
| reference `.data` strings present | 242/415 | **252** |
| `.data` pre-fixer | 0x6d33 | 0x6f76 (**+579**) |
| **linked `.text` residue** | **0x21d8** | **0x21d9 (+1)** |

The 25 push sites become relocated operands matching the reference's shape, which is why the
object-level rulers move so much. **But the shipped residue went up by one byte, so it is
rejected** — `.text` residue is the objective's metric, `.data` pre-fixer is a diagnostic
(§98: the shipped `.data` is blitted from the layout package either way). An edit that gains 78
bytes on an object ruler and loses 1 byte at the link is a loss, and this is the clearest case
yet of why only the link decides (§19, §41, §94).

Two measurement traps from the same lane, both worth avoiding:

- **The dominant `.data` shift is not every object's shift.** §102's `+0x20` is the largest
  cluster (39 of ~400 strings), not a global property. `ServerMainThread`'s own block lands at
  **-0xa08** — 2,568 bytes *early* — and **zero strings sit at their exact reference VA, before
  or after the conversion**. Measure the specific TU's block before assuming the headline shift
  applies to it.
- **`split_link.sh`'s `GAP` must be re-swept when a TU's `.data` size changes.** An uncorrected
  `GAP` silently produced a 290,816-byte image and a false `.data` figure; re-sweeping
  `0x74a0` -> `0x732f` restored the exact 286,720 geometry. Any `.data` measurement taken
  without that check is void.

## 105. The GA flag sweep, finally run — and why it says nothing new

The objective names `rebrew match`, but no run of it had ever produced a result in this
session: two attempts hung and were killed. The cause was a tool bug, now fixed upstream
(`8820f1e`).

**The bug:** `--timeout-min` was applied only around the GA run. `--flag-sweep-only` returns
before reaching that code, so the flag was **silently inert on exactly the path where it
matters** — a `targeted` tier is thousands of combinations and `thorough` is 258k. Measured
here: `--timeout-min 6` was still running after 13 minutes with an empty output file;
`--timeout-min 2` was still going at 7 minutes. With a cooperative deadline threaded through
`flag_sweep` → `run_flag_sweep` → `_run_single_flag_sweep` → the CLI, the same command
finishes in **126 seconds** and writes its JSON report.

**The result, on `gm_CalculateProductionValue` (the 5-byte row):**

```
tier targeted, 20 flag combinations evaluated
best_score 7500.0   best_flags "/G3 /Gd /Oy"   exact false
... and all 20 combinations score exactly 7500.0
```

A perfectly flat landscape: `/G3`, `/G3 /Gd`, `/G3 /Oy`, `/G3 /Gd /Oy` and the empty set all
score identically. That is independent confirmation of what section 92 concluded from the
bytes — this row's residue is an **x87-stack allocator decision**, and no flag reaches it.
A flat sweep is a genuinely useful negative: it separates "we have not found the flag" from
"no flag exists", and this is the latter.

Two practical notes for anyone running the engine here:

- **Always pass `--timeout-min`** — and now it works. Without a bound, a sweep on a
  multi-function file will outlive any wrapper `timeout` you put around it, because the
  compiles it spawns survive the signal.
- The sweep is per-*function* via `--va`, but it still compiles the whole translation unit
  each time, so cost scales with the file, not the function. `spiel622.c` (16 functions) takes
  ~6 s per combination.

## 106. The flag landscape is flat on every walled row — five for five

Section 105 ran the repaired flag sweep on one function and found all 20 combinations scoring
identically. Round 208 asked whether that generalises. It does, and the result is worth having
because it closes an entire class of "have we tried the flags?" questions.

Sweeping the five largest walled rows, `targeted` tier, 20 combinations each:

| function | residue | combos | distinct scores | best score |
|---|---|---|---|---|
| `gm_AllocSpieler` | 2,824 | 20 | **1** | 3,849,233.33 |
| `CrashDumpUnhandledExceptionFilter` | 1,595 | 20 | **1** | 2,224,585.73 |
| `cm_ExSellObjekt` | 967 | 20 | **1** | 1,301,503.00 |
| `vfs_ReadCompressed` | 24 | 20 | **1** | 35,900.00 |
| `m_AllocTracked` | 92 | 20 | **1** | 34,500.00 |

**Five for five, one distinct score each.** The flags genuinely vary — 20 distinct flag strings
per row, verified (`/G3`, `/G3 /Gd`, `/G3 /Gd /Oy`, `/G3 /Gd /Oy /Op`, `/G3 /Gd /Oy-`, …) — the
emitted code simply does not respond to any of them.

The `targeted` tier covers `/G?`, `/Gd`, `/Op`, `/Oy`, `/Oy-`. To check the finding was not an
artefact of that narrow set, `m_AllocTracked` was also swept at `thorough` tier, which reaches
a different group — `/GX`, `/Gs`, `/ML`, `/Ob?`, `/Zp?` — and it is **still 1 distinct score**.
That is **12 distinct flag axes and ~120 compilations, all inert**.

**Why this matters more than any single row.** Every one of these rows was closed by byte-level
analysis (sections 84-104) concluding the residue is register allocation, instruction
scheduling, or an x87-stack decision. The sweep is an *independent instrument* reaching the
same verdict without looking at a single byte: if a compiler flag could move these functions,
a flat landscape is exactly what you would not see. Two methods agreeing from different
directions is much stronger than either alone.

It also retires a standing question cheaply. "Has anyone tried `/Ob2`? `/Zp1`? `/GX`?" now has
a measured answer for the rows that matter, rather than an appeal to the CFLAGS sweeps recorded
in individual file headers (which were per-function, undated, and in one case — section 94's
`gm_AllocSpieler` note — found to be wrong about which flags were load-bearing).

Practical caveat: a flat landscape says the *flags* are inert, not that the function is
unreachable. It is silent about source shape, which is where every landed win in this session
came from.

## 107. The GA finds nothing either, and stagnates immediately

Section 106 established that the flag landscape is flat on every walled row, but was explicit
that this says nothing about **source shape** — the axis every landed win in this session came
from. `rebrew match`'s GA mode mutates source, so it tests exactly that axis. Round 209 ran it
for the first time (it was unusable before the round-457 timeout fix).

Two rows, 12 generations, population 16, `--mutation-focus auto` (which reads the function's
BLOCKER metadata to bias operator selection):

| function | best score | stagnant generations | vs flag-sweep baseline |
|---|---|---|---|
| `m_AllocTracked` | 147,228.92 | **11 of 12** | 34,500 — **4x worse** |
| `vfs_ReadCompressed` | 35,900.00 | **11 of 12** | 35,900 — **identical** |

**Both stagnate after a single generation.** On `vfs_ReadCompressed` the GA never beat the
unmutated source; on `m_AllocTracked` its best candidate ended four times worse than doing
nothing, i.e. every mutation it kept was harmful and it simply had nothing better to fall back
to within the budget.

The one mutation that survived on `m_AllocTracked` is instructive:

```c
- while (i < slots) {
+ while (!(i >= slots)) {
```

Applied by hand and measured: **566/658, byte-identical to baseline.** msvc6 canonicalises the
double-negated comparison straight back, which is the same normalisation section 92 found for
commuted multiplies and section 59 for `if (c) goto L;`. The GA's "best" source change is
provably a no-op.

**What this adds to section 106.** The two instruments now cover both axes and agree:

- flags — flat across 12 axes and ~120 compilations (section 106);
- source mutations — immediate stagnation, no candidate better than the unmutated source.

Neither is a proof of impossibility, and the GA's operator set is generic rather than aimed at
the specific allocator decisions these rows are blocked on (sections 92, 94, 104). But it does
mean the two *automated* search paths the toolchain offers are exhausted on these functions,
and the remaining progress has to come from reading the reference's bytes and reasoning about
what C shape produces them — which is how every win in this session was actually found.

Practical note: budget the GA by wall clock, not generations. 12 generations at population 16
is ~95 s per row here, and the stagnation counter tells you almost immediately whether more
generations would help — 11 of 12 stagnant means they would not.

## 108. `near-diag`'s verdict is a different ruler — reconcile it before believing it

`rebrew near-diag` classifies a NEAR_MATCHING residual and suggests mutation operators. Run
across the walled rows it reports, uniformly, a **RELOC-dominated** verdict:

| function | verdict | near-diag "real bytes" | `rebrew test` delta |
|---|---|---|---|
| `cm_ExProdObjekt` | RELOC (91% of delta) | 17 | **17** |
| `cm_ProcessCommandQueue` | RELOC (88% of delta) | 13 | 15 |
| `gm_ObjectsAvailble` | RELOC (69% of delta) | 56 | 28 |
| `vfs_ReadCompressed` | RELOC (41% of delta) | 36 | 24 |
| `m_AllocTracked` | RELOC (62% of delta) | 103 | 92 |

Read carelessly, "91% of the delta is relocations" suggests these functions are nearly solved
and the residue is an artefact. **That reading is wrong**, and the tool itself says so in the
next sentence: *"Most of the delta sits at relocation sites, but 17 real byte(s) differ — the
match is NEAR_MATCHING-level, not RELOC."*

**Round 211 pinned the exact mechanism**, because three rows disagree in *both* directions
(56 vs 28, 36 vs 24, but 13 vs 15) and a one-way masking story cannot explain a sign flip.
Ground truth on `cm_ProcessCommandQueue`, computed directly from the object and the reference:
**75 raw differing bytes**, which `rebrew test` masks down to 15 and `near-diag` reports as 13.

The cause is that the two tools count in **different units**:

- `rebrew test` counts **individual differing bytes** after masking relocation slots.
- `near-diag` walks aligned instruction pairs and adds each differing instruction's **whole
  size** to a category (`reloc`, `register`, `encoding`, `equivalent`, `structural`), so one
  mismatching 6-byte instruction contributes 6 to the total even if a single byte differs — and
  contributes 0 to "real bytes" if it happens to carry a relocation, even when non-relocated
  bytes inside it also differ.

That is why the sign can flip: instruction-granular accounting over-counts a row whose
differences are spread across long instructions (`gm_ObjectsAvailble`, 56 vs 28) and
under-counts one whose differing bytes cluster inside relocated instructions
(`cm_ProcessCommandQueue`, 13 vs 15). Neither tool is wrong; they answer different questions.
**Use `rebrew test`'s number for "how many bytes differ" and `near-diag`'s categories for
"what kind of difference is it".**

The two numbers are different rulers over the same object, exactly as section 96 warned:

- `rebrew test` reports the delta **after masking relocation slots** — 17 on `cm_ExProdObjekt`,
  with `reloc_count: 34` masked separately.
- `near-diag`'s percentage is computed over **unmasked** spans, so every relocation site counts
  toward the denominator and the percentage says how much of the *raw* difference is explained
  by relocations rather than how close the function is.

Its `bytes` field is also the **function size** (993 for `cm_ExProdObjekt`), not a delta — easy
to misread as a residual. Once reconciled, the two tools agree exactly where it matters: both
say 17 real bytes on `cm_ExProdObjekt`.

**What it adds that is genuinely new.** `near-diag` flags *"control flow / block layout
differs"* on exactly two of the five rows — `vfs_ReadCompressed` and `m_AllocTracked` — and
stays silent on the other three. That is an independent structural signal, and it is consistent
with the byte-level findings: section 99 traced `vfs_ReadCompressed`'s residue to a
scheduler-sunk `add esp,0x14` (a layout decision), and section 86b traced `m_AllocTracked`'s to
store ordering through a fresh pointer. The three rows it stays silent on
(`cm_ExProdObjekt`, `cm_ProcessCommandQueue`, `gm_ObjectsAvailble`) are exactly the ones whose
documented causes are *not* layout — a coupled allocator decision (section 104), provably-dead
code the compiler deletes (section 92), and a register-rename shadow (section 92).

So the classifier's structural flag agrees with five independent byte-level investigations.
That is worth having: it is a cheap first-pass triage that would have pointed at the right
category on all five rows without disassembling anything.

The suggested mutation operators are generic control-flow rewrites (`mut_swap_if_else`,
`mut_guard_clause`, `mut_while_to_dowhile`, `mut_for_to_while`, …) — the same family section 107
measured the GA applying, where the one surviving candidate proved byte-inert because msvc6
canonicalises it.

## 109. `gm_AllocSpieler`'s first fault is a scheduler sink, not a statement order

`gm_AllocSpieler` (0x10018850) carries **2,824 of the 8,664 residual bytes — 33% of everything
left**, so its first divergence is the highest-value single question in the tree. Round 212
located it exactly.

**Our object is byte-identical to the reference through +0xa9.** At +0xaa the streams split:

```
reference +0xaa:  8d92fc580310   lea edx,[edx+0x100358fc]
ours      +0xaa:  66895d00       mov word ptr [ebp],bx      <-- we emit these two
                  33db           xor ebx,ebx                <--   first
                  8dbafc580310   lea edi,[edx+0x100358fc]   (edi, not edx)
```

The reference emits that same `mov word ptr [ebp],bx` / `xor ebx,ebx` pair at **0x10018918 —
after the `rep stosd`**. So neither side is missing an instruction: the same work is scheduled
on opposite sides of the block fill, and the reference keeps the scaled index live in `edx`
where we move it to `edi`.

The corresponding C is the record-header init, where `*(unsigned short*)(0x100358a0 + idx *
0x21c) = (unsigned short) idx;` precedes the `memset`.

**Reordering the C to match makes it worse, measured:**

| shape | `rebrew test` | obj |
|---|---|---|
| shipped (idx store before `memset`) | **1004/3689** | 3689 |
| `memset` hoisted above the idx store | 633/3694 | 3694 |
| same, also moving the two zeroing stores after | 633/3694 | 3694 |

Both variants lose **371 matched bytes and grow the object by 5**, because hoisting the
`memset` call forces the scaled index to be rematerialised across it — the call clobbers the
register the reference is carefully keeping live.

**So this is a scheduler decision downstream of register pressure, not a statement order.**
msvc6 is sinking the 16-bit store past the block fill on its own, and C has no way to request
that: the fill is a `memset` call, and any source order that puts the store after it also puts
the call *before* it, which costs the register. This is the same class as section 99's
`vfs_ReadCompressed` finding (a scheduler-sunk `add esp,0x14`) and section 86b's store
ordering, and it is consistent with section 106 — no compiler flag moves this row either.

Worth stating plainly because it bounds expectations on the biggest row: the first 0xaa bytes
already match, the fault at 0xaa is not a source shape, and the 2,824-byte residue behind it is
that one scheduling decision's displacement wake rather than 2,824 bytes of wrong code.

### Round 216: the `lea` split is not source-reachable either

The obvious remaining hypothesis was that the reference's `lea edx,[edx+0x100358fc]` followed
by `mov edi,edx` means the destination is a **named C object** rather than an argument computed
in place, and that we fuse into one `lea edi` because ours is anonymous.

**Tracing `edx` in the reference kills the simplest version of that story.** `edx` is *dead*
immediately after the copy — its next appearance is an unrelated `lea edx,[esp+0x3c]` at
0x1001896f — and every statement after the fill is addressed off `ebp`, not off the scaled
index. So the reference is not keeping a live value: it computes into `edx` and copies.

Tested anyway, two ways:

| shape | `rebrew test` | obj | `lea` at +0xaa |
|---|---|---|---|
| baseline | **1004/3689** | 3689 | fused (`8dbafc580310`) |
| new `char* refs` local (round 465) | 595/3696 | 3696 | — frame grew, broke instruction #0 |
| **reuse an existing pointer local** (`mother`) | 1004/3689 | 3689 | **still fused** |

Reusing a local that already exists avoids the frame growth entirely — the object stays exactly
3689 and the score is byte-identical — but msvc6 **folds the assignment away** and still emits
the fused `lea edi`. So the split cannot be requested through a named destination: with a new
local it costs 4 bytes of frame and breaks the prologue, and with an existing local it is
optimised out.

Combined with the seventeen-variant sweep (every one moved the first fault *earlier*), the
+0xaa fault is closed to source-level work on both of its tells — the store sink and the `lea`
split. Section 109's narrowed claim stands: C can request the sink alone, but not while keeping
the `0xffff` store alive, and the `lea` split is unreachable in either configuration.

Housekeeping from the same round: the metadata note claiming "SIZE 3209/3689 (480B short)" was
stale from the naked-asm era — the object is now **exactly 3689 bytes**, the target size — and
an inert `/DREBREW_ALLOW_NAKED` was removed from its cflags (verified byte-identical at
1004/3689 both ways), the last of the three section 97 identified.

## 110. A deliberate semantic bug is shipped in `gm_AllocSpieler` — state it plainly

This one is not a codegen fact; it is a standing decision that deserves to be visible outside
a file header, because it trades **correctness for byte score**.

`gm_AllocSpieler` contains a real bug. In the `arg8 != 2` branch we store a value that is
always zero:

```c
if (arg8 == 2) {
        slot[9] = (char) gm_RandomMod((unsigned short) arg8);
} else {
        slot[9] = slot[0x166];          /* always 0 -- WRONG */
}
```

The reference stores **`arg8` itself**, which I verified at the bytes (round 213):

```
0x10018cd4  8b84244c040000  mov eax,[esp+0x44c]   ; arg8
0x10018cdb  83f802          cmp eax,2
0x10018cde  7509            jne 0x10018ce9        ; skips the call, eax still = arg8
0x10018ce0  50              push eax
0x10018ce1  e8ea130000      call gm_RandomMod
0x10018ce9  83fe04          cmp esi,4
0x10018cec  884509          mov byte ptr [ebp+9],al   ; stores arg8 when the call was skipped
```

`eax` holds `arg8` on the skip path, so the store writes the argument. Our version writes 0.
**Observable whenever `arg8` is neither 2 nor 0.**

Measured cost of being correct:

| shape | `rebrew test` | obj |
|---|---|---|
| shipped (wrong) | **1004/3689** | 3689 |
| `slot[9] = (char) arg8` | 565/3689 | **3679** |
| reference's single-store shape (`n = arg8; if (...) n = call(...); slot[9] = (char) n;`) | 565/3689 | **3679** |

Both correct spellings land **identically**, so the 10-byte deficit is structural — the correct
code is simply shorter — not a spelling that can be tuned. An earlier attempt also measured
**+393 linked** through tail desynchronisation.

**Why this is worth a numbered section.** Sections 19, 41 and 94 established that only the link
decides, and that rule has correctly rejected many byte-losing edits. This is the one case
where the rule is being applied to a *correctness* regression rather than a stylistic one, and
that is a different kind of decision: the objective is a byte-identical recompilation, so the
shipped source is allowed to diverge from correct behaviour only because the reference binary
is the specification. Anyone using this tree as a *source* release rather than a byte-matching
exercise must fix this line first.

The blocking condition is precise and worth restating: a correct spelling that is **10 bytes
longer**, or a resynchronised tail that absorbs the shortfall. Until then the bug stays, and it
should stay *documented here*, not only in a comment 450 lines above the defect.

### Round 214 correction: the size match is an accident of the bug

The framing above — "being correct costs 10 bytes" — is misleading, and the instruction counts
show why:

| shape | instructions (ref 1056) | obj |
|---|---|---|
| shipped (buggy store) | 1054 — **2 short** | 3689 (**matches**) |
| correct semantics | 1053 — **3 short** | 3679 (10 short) |

Both shapes emit **fewer instructions than the reference**. The buggy `slot[9] = slot[0x166]`
spelling loads from an absolute address, which emits one extra instruction worth ~10 bytes, and
that coincidentally pads the object back to exactly 3689. **The size match is an artefact of the
defect, not evidence that the shipped shape is right.**

That inverts the correct reading of the deficit. It is not that correctness costs 10 bytes; it
is that **the reference contains ~10 bytes of work we are not emitting anywhere**, and the wrong
store has been masking that gap by accident. Chasing "a correct spelling 10 bytes longer" is
therefore the wrong target — padding with a different wrong instruction would match the size
just as accidentally.

### Round 215: half the deficit was the argument cast, not the store

The "10 bytes short" figure assumed the only variable was the store. It was not. The call in
the `arg8 == 2` arm was spelled `gm_RandomMod((unsigned short) arg8)`, and that cast is
**load-bearing only when the store is correct**:

| variant | `rebrew test` | obj | short by |
|---|---|---|---|
| shipped (buggy store, masked arg) | **1004/3689** | 3689 | 0 |
| correct store, masked arg | 565/3689 | 3679 | 10 |
| **correct store, unmasked arg** | **745/3689** | **3684** | **5** |
| buggy store, unmasked arg | 1004/3689 | 3689 | 0 |

Removing the cast recovers **180 matched bytes and half the size deficit** — but only in
combination with the correct store. With the buggy store it is perfectly inert (1004/3689 both
ways), which is why nobody found it: the cast can only be evaluated against a correct store,
and the correct store was rejected on its own numbers before the cast was ever varied.

The reference supports the unmasked form directly — at 0x10018cd4 it loads the full dword
`mov eax,[esp+0x44c]` and pushes `eax` unmodified, with no 16-bit narrowing anywhere.

**This changes the unblocking condition.** Section 110 asked for "a correct spelling 10 bytes
longer", which the round-214 correction then showed was the wrong target anyway. The real
target is now 5 bytes, not 10, and the remaining 5 are the section 109 scheduler sink — the
`jmp` displacement evidence (`0xc01` against `0xbfc`) measures exactly that. Correct semantics
still costs 259 matched bytes against the shipped bug, so it does not land yet, but the gap is
half what it was and the residue is now attributed to a single known cause rather than an
unexplained deficit.

Where the missing work sits is already known. With correct semantics the first non-relocation
divergence is still **+0xaa**, the section 109 scheduler sink, and the `jmp` at +0x85 carries
displacement `0xc01` against our `0xbfc` — **exactly 5 bytes**, so the reference's jump target
sits 5 bytes later than ours. Half the deficit is behind that one scheduling decision, which
section 109 established C cannot request. (Relocation slots must be masked before reading any of
this: unmasked, the first difference appears at +0x6d, which is only an unresolved `0x10035434`
against zeros.)

## 111. Count calls by ENCODING, not by grep — and what it shows on `CrashDumpUnhandledExceptionFilter`

Section 104 compared call counts between the reference and our objects to rule out inlining.
That comparison was right in its conclusion but sloppy in its method: it grepped lines
containing `call`, which also matches operands and comments. Counting strictly from the
**encoding bytes** is both correct and far more informative, because the three x86 call forms
map onto three different C-level constructs:

| form | encoding | C that produces it |
|---|---|---|
| direct | `e8 rel32` | a call to a function in the same image |
| indirect through memory | `ff15 disp32` | a call to a `__declspec(dllimport)` API by name |
| indirect through a register | `ffd?` | a call through a function-pointer *value* |

On `CrashDumpUnhandledExceptionFilter` (0x10002770, 1,595 residual bytes — the second largest
in the tree) the strict counts are:

| kind | reference | ours |
|---|---|---|
| direct `e8` | 8 | 8 |
| **memory-indirect `ff15`** | **19** | **17** |
| **register `ffd?`** | **17** | **18** |
| total | **44** | **43** |

So the shape of the difference is precise: **we make two fewer calls straight through the IAT
and one more through a register**, and we emit one call fewer overall. Direct calls match
exactly, which again rules out an inlining difference (section 104's conclusion survives its
method being corrected).

Two measurement notes that cost time here and will cost it again:

- **Our object's IAT slots are unresolved zeros**, so a naive comparison of call *targets*
  reports every slot as differing (`ds:0x0` against `0x10024010`). Compare by count and by
  relocation symbol, not by address, until after the link.
- The reference calls 13 times through `esi`, which looks like one cached import but is not:
  `esi` is reloaded at least four times in the body (`mov esi,[0x10024038]`,
  `mov esi,[esp+0x20]`, `mov esi,0x100272f8`, `mov esi,[0x10024024]`). Several different values
  flow through the same register.

Reading the object's relocations gives the useful cross-check: we reference **15 distinct
`__imp_` symbols** where the reference calls through **12 IAT slots**, with `CloseHandle` x4 and
`VirtualFree` x3 the most repeated. The source has **five** `CloseHandle` call sites against
four relocations, i.e. msvc6 has already merged two of them — which is consistent with both the
missing call and the extra register call being the same event: a repeated import getting cached
into a register and one of its call sites folded.

## 112. The reference does not cross-jump identical cleanup arms — and neither should we

Section 111 traced `CrashDumpUnhandledExceptionFilter`'s call-kind delta (19 `ff15` in the
reference against our 17) to three `else` arms that each end with the same two statements:

```c
VirtualFree(pDbgBuf, 0, 0x8000);
CloseHandle(hDbgFile);
```

msvc6 folds two of ours into a shared tail. **The reference emits the pair three separate
times**, at 0x10002d9f/0x10002da6, 0x10002dd8/0x10002ddf and 0x10002e0a/0x10002e11.

The interesting part is *why*, and reading all three aligned (rather than two, as I first did)
gives the answer — the arms are **not** interchangeable blocks:

```
arm 1  0x10002d96:  mov ebx,[esp+0x3c]  mov ebp,[esp+0x38]  push ebx  call VF  push ebp  call CH
arm 2  0x10002dc9:  mov ebp,[esp+0x40]  add esp,0x10        push 0x8000 push 0 push ebx call VF ...
arm 3  0x10002e02:                      push 0x8000 push 0  push ebx  call VF  push ebp  call CH
```

Each arm reaches the cleanup with a different register/stack state — arm 1 reloads both `ebx`
and `ebp`, arm 2 reloads `ebp` and unwinds `esp` by 0x10, arm 3 arrives with everything live.
The *call pair* is identical in all three, but the blocks containing it are not, so there is
nothing for the compiler to fold. Our version reaches all three arms in the same state, which
is what makes them foldable.

**So the lever is not "stop msvc6 cross-jumping".** It is that the reference's three arms do
genuinely different amounts of stack and register restoration before the cleanup, because they
are exited from different nesting depths. Reproducing that means matching the *scope structure*
that produces those different exits — not perturbing the cleanup statements themselves.

Worth recording as a general caution: **two byte-identical instruction sequences in the
reference are not evidence that the compiler declined an optimisation.** Check what precedes
them. Here arms 2 and 3 have identical six-instruction tails and different four-instruction
lead-ins, and it is the lead-ins that keep them apart. I nearly delegated a probe to "prevent
cross-jumping" before reading the third arm aligned — the misalignment in
`rebrew asm` output when starting mid-instruction is easy to mistake for real code.

### Round 219: count call sites per IMPORT, not adjacent-call "pairs"

The analysis above was still one abstraction too loose. Counting *adjacent `ff15` pairs* gave
"reference 3, ours 2" and pointed at a missing cleanup arm — but the heuristic conflated two
different sequences. Reference arm 1 actually runs
`WriteFile` (via `esi`) → `CloseHandle(hCrashLog)` → `VirtualFree` → `CloseHandle(hDbgFile)`,
so its "+0x62f pair" is `CloseHandle`+`VirtualFree`, not the cleanup pair at all.

Counting **per import slot** settles it exactly:

| import | slot | reference sites | our relocations |
|---|---|---|---|
| `VirtualFree` | 0x1002400c | 3 (+0x62f, +0x668, +0x69a) | **3** |
| `CloseHandle` | 0x10024010 | 5 (+0x619, +0x636, +0x66f, +0x6a1, +0x6d3) | **4** |

So `VirtualFree` already matches, and **exactly one `CloseHandle` call is missing**. Our source
has five `CloseHandle` call sites, so msvc6 folded two of *those* — and the three-arm cleanup
story, while true about the arms differing, was not where the lost call lives.

The method rule: **count call sites per import symbol** (from the reference's IAT slot and from
the object's relocation symbols), never by positional adjacency. Adjacency is a property of
scheduling; the per-symbol count is a property of the source.

### Round 220: that rule is ALSO wrong — a relocation is not a call

The per-symbol count above was measured from **relocation entries**, and a relocation marks
where an address is *materialised*, not where it is *called*. When msvc6 caches an import in a
callee-saved register it emits **one** relocation (`8b35 mov esi,[__imp__X]`) and then any
number of `ffd6 call esi`. Two independent probe lanes caught this, and the object confirms it
directly — our own breakdown by preceding opcode:

```
__imp__CloseHandle@4   ff15 x3  +  mov-CSE x1     -> 3 relocs but 5 calls
__imp__WriteFile@20    mov-CSE x1                 -> 1 reloc  but 10 calls
__imp__VirtualFree@12  ff15 x3                    -> 3 relocs and 3 calls
```

So "CloseHandle 5 vs 4, one missing" (round 219, committed in `f4a73057`) was an artefact of
counting relocations. Resolved properly — by tracing each cached register back to the
relocation that loaded it — the inventory is:

| callee | reference | ours |
|---|---|---|
| `VirtualFree` | 3 | **3** |
| `CloseHandle` | 5 | **5** |
| `WriteFile` | 11 | **10** |
| everything else | 1:1 | 1:1 |

**`VirtualFree` and `CloseHandle` already match. The entire call delta is one `WriteFile`.**
Sections 111 and 112's cleanup-arm story is therefore retired: those three and five calls are
all present in our object, and there is nothing to win there.

The corrected rule, third time: **count calls, not relocations** — resolve `ffd?` sites by
tracing the register back to its defining `mov reg,[__imp__…]`. The `ff15`/`ffd?` ratio itself
is a *register-allocation* artefact (the reference caches three imports in callee-saved
registers, we cache four), not a source property, so the encoding ratio is a shadow worth
chasing only after the call inventory matches.

**Now automated (round 221).** Three separate probe lanes had to derive this inventory by hand,
each time re-discovering the same trap, so it is now a command:

```
rebrew xrefs 0x10002770 --calls-from 2115
  WriteFile 11 | CloseHandle 5 | 0x10003640 4 | VirtualFree 3 | ... | total 44
```

It walks the function, tracks which import each register currently holds (`mov reg,[__imp__X]`),
and attributes a `call reg` to the same callee as a direct call — reproducing in one command
what took four rounds and three wrong methods to establish. Use it before reasoning about call
counts on any row.

**Where the real missing call is.** The reference compiles the exception switch as **two jump
tables, each with its own newline tail**: table 1 at 0x10002b2a (6 arms, tail 0x10002b7f,
`call esi` at **0x10002b80** — the absent WriteFile) and table 2 at 0x10002bab (8 arms, tail
0x10002c40). Fan-in confirms two joins: 6 × `jmp 0x10002b7f`, 11 × `jmp 0x10002c40`. We emit
**both range tests at identical constants** — our case partition already matches — then funnel
every arm into one shared tail.

So the phenomenon is real but inverted from the original guess: **we fold, the reference keeps
two copies**, and it lives in the switch message writes rather than the cleanup. Splitting the
second range into its own `switch` does not buy it (406/2141, SIZE_MISMATCH): msvc6's two
tables are one switch it split because the case values form two dense clusters (spans 0x68 and
0x6e), and the duplicated tail is its own downstream layout decision, not something the keyword
produces.

## 113. Tree-wide call-inventory sweep: exactly one row has a real defect

With the inventory automated (section 112), round 222 swept it across every measurable walled
row — comparing the reference's per-callee counts against the same inventory computed from our
objects, resolving register-cached imports on both sides.

| row | reference | ours | |
|---|---|---|---|
| `gm_AllocSpieler` | 55 | **55** | ok |
| `ServerMainThread` | 55 | **55** | ok |
| `cm_ExSellObjekt` | 31 | **31** | ok |
| `ls_LoadBuildingEntityState` | 45 | **45** | ok |
| `cm_ExProdObjekt` | 21 | **21** | ok |
| `gm_AllocGebaeude` | 18 | **18** | ok |
| `srv_LoadBuf` | 17 | **17** | ok |
| `gm_ObjectsAvailble` | 15 | **15** | ok |
| `ahm_ExAllocAlchemist` | 13 | **13** | ok |
| `m_AllocTracked` | 10 | **10** | ok |
| `vfs_OpenStream`, `cm_ProcessCommandQueue`, `gv_ExAllocGraveyardWorker` | 7 | **7** | ok |
| `gm_CheckInventoryCapacity` | 5 | **5** | ok |
| `cm_ExCopyEntityData` | 3 | **3** | ok |
| `gm_CalculateProductionValue` | 2 | **2** | ok |
| `gm_FindNextFilteredEntity` | 0 | **0** | ok |
| **`CrashDumpUnhandledExceptionFilter`** | **44** | **43** | **`WriteFile` 11 vs 10** |

**Every row matches except one.** That is a strong negative result: whatever the remaining 8,664
bytes are, they are almost entirely *not* missing or extra calls. Combined with section 104
(direct-call counts equal, so nothing is inlined) and section 106 (the flag landscape is flat),
the residue is confined to register allocation, instruction scheduling and block layout — with a
single exception worth one `WriteFile` in `CrashDumpUnhandledExceptionFilter`'s exception-switch
tail.

Two measurement traps, both hit while running this sweep:

- **Selecting a COMDAT by "largest `.text` section" is wrong on a multi-function file.**
  `spiel622.c` has 16 functions, and picking the largest COMDAT reported 10 calls against the
  reference's 2 — a phantom mismatch. Both apparent failures in this sweep were this artefact;
  re-measured on the correct COMDAT they match exactly. Select by the section index the probe
  reports, and note the COMDAT is sized by *span* (400) not code length (396).
- The reference-side tool takes the function's **size from metadata**; passing a stale size
  truncates the walk and undercounts silently.

## 114. The last call defect: two switch tails the reference keeps and we merge

Section 113 established that exactly one row in the tree has a call-inventory defect —
`CrashDumpUnhandledExceptionFilter`, `WriteFile` 11 against our 10. Round 223 located it
exactly, and it is the clearest remaining *structural* difference in the function.

The reference compiles the exception-code switch as **two jump tables, each with its own copy of
the message-write tail**:

```
tail A  0x10002b7f  55 push ebp / ffd6 call esi   <- the WriteFile we never emit
                    8d4c2410 lea ecx,[esp+0x10] ... 6a02 push 2
tail B  0x10002c40  55 push ebp / ffd6 call esi
                    8d442410 lea eax,[esp+0x10] ... 6a02 push 2
```

The two tails are **structurally identical and differ only in scratch register** (`ecx`/`edx`
against `eax`/`ecx`), which is exactly why msvc6 did not fold them: they are reached in
different register states. Fan-in, counted from the reference's own `jmp` targets:

```
jmp 0x10002b7f :  6 arms      jmp 0x10002c40 : 11 arms      jmp 0x10002c51 : 1 arm (newline)
```

Walking the jump tables confirms the split: table 1 at 0x10002e9c holds four real arm addresses
(0x10002b31/41/51/61) before its index bytes, table 2 at 0x10002f1c holds eight
(0x10002bb2…0x10002c22). Each arm pushes its own message pointer and length —
`lea eax,[esp+0x10]; push 0; push eax; push 0x15; push 0x10027278` — then `jmp` to its group's
tail, which supplies the handle and makes the call.

**We emit both range tests at identical constants**, so our case partition already matches the
reference; what we do not reproduce is the duplicated tail. Our source writes each case's
message with its own `WriteFile(...)` followed by `break;`, and msvc6 cross-jumps every arm into
a single shared tail — one call site where the reference has two.

**Corrected by section 117 (round 225):** tail A does not run to its own end — it finishes
`push edx; jmp 0x10002c51`, landing *inside* tail B at its **second** `call esi`. So the two
tails **share the newline write** and duplicate only the **message** write. The reference has 13
`call esi` sites for 19 arms; whole-tail duplication would give 14. Any shape that duplicates the
whole tail is structurally wrong before it is compiled.

Known dead ends, so nobody re-spends them: spelling the second range as its own `switch`
statement measures **406/2141 (SIZE_MISMATCH)**, because msvc6's two tables are *one* switch it
split internally on dense case clusters rather than two source constructs; splitting a single
case to its own tail reaches the correct call count (44) and better alignment (+13) but costs 79
matched bytes and 4 bytes of size (**554/2119**); and writing the reference's exact seven-case
group split compiles **byte-identical**, because msvc6 simply re-merges it.

### Why the reference's spill reloads are not a storage signal

Section 112 read the reference's `mov ebx,[esp+0x3c]` / `mov ebp,[esp+0x38]` between the two
`CloseHandle` calls as evidence that the handles must live in distinct storage. **That inference
does not hold**, and the bytes two instructions later say why:

```
0x10002da6  ff1510400210  call [0x10024010]   ; CloseHandle(hDbgFile)
0x10002dac  5f            pop edi
0x10002dad  5b            pop ebx
0x10002dae  e9b3000000    jmp 0x10002e66
```

The reference reloads into `ebx`/`ebp` because it is **about to pop `edi`/`ebx` for the epilogue
path** and needs those values back in registers first. Our build keeps the same values in
`edx`/`eax`, in distinct stack slots (`[esp+0x2c]` and `[esp+0x58]`), and never spills — so the
asymmetry the earlier reading treated as a source-level storage difference is pure register
allocation. It follows that `volatile` on a handle could not have helped here, which is
consistent with section 94's record of it losing four times out of four.

Two further probes confirmed the dead end from a different arm partition: two `switch`
statements sharing one newline write measured **336/2117**, and two switches each with their own
inline newline write measured **338/2133** — and neither even bought the extra call, because the
second `switch` keyword still cross-jumped into a single tail.

So the duplicated tail is a *layout* consequence of how msvc6 placed the two arm clusters, not
something the source requests directly — consistent with section 109's finding on
`gm_AllocSpieler` and section 112's on the cleanup arms. It is worth one `WriteFile` plus about
twenty bytes of duplicated argument setup, and it sits exactly where this function's alignment
deltas step from +21 to +43.

## 115. The sp5-pp toolchain axis, finally measured — a real gain that cannot ship

Section 91 recorded that `msvc-6.0-sp5-pp` reproduces `gm_FindNextFilteredEntity`'s tail verbatim
and reaches obj 346, the reference's exact size, where sp6 emits 342. Nobody had measured it.
Round 224 did, and the answer has two halves that must be kept together.

**The gain is real.** On `gm_FindNextFilteredEntity` (0x10016f80):

| toolchain | status | match | obj |
|---|---|---|---|
| msvc-6.0-sp6 (default) | SIZE_MISMATCH | 162/346 | 342 (**4 short**) |
| **msvc-6.0-sp5-pp** | STUB | **171/346** | **346 — exact** |

And the file is safe: all three of its file-mates (0x10016cd0, 0x10016de0, 0x10016ea0) stay
**RELOC-perfect** under sp5-pp — 272/272, 186/186, 211/211 — so switching this one file would
cost nothing elsewhere in it. That matters because section 12 established CFLAGS are per-file in
practice, and a toolchain is per-file too.

**But it is not a global win, and it cannot ship.** Two independent blockers:

- **sp5-pp is much worse on other rows**, so it cannot be adopted project-wide:
  `gm_CalculateProductionValue` 391/396 → **236/396**, `m_AllocTracked` 566/658 → **266/658**
  (and obj 658 → 634), `vfs_ReadCompressed` 468/492 → 461/492. The nine MSVC6 images are three
  distinct generators (section 92); sp5-pp is its own, and it disagrees with sp6 broadly.
- **A per-function toolchain pin never reaches the link.** `rebrew cmake-flags` says so
  explicitly: *"resolves toolchain 'msvc-6.0-sp6', but the CMake build's compiler is fixed by the
  toolchain file — the pin affects `rebrew test`/`verify` only, never the linked bytes."* The
  build selects one compiler through `cmake/toolchain-msvc-6.0-sp6-docker.cmake`, for every
  translation unit.

So this is the measure-vs-ship divergence of section 99 in a new place: a metadata pin can move
`rebrew test` by +9 matched bytes and a perfect object size while the shipped binary does not
change by one byte. **Recording the figure without that caveat would be recording a phantom
win.**

What it would take to bank it: per-file compiler selection in the CMake build — a second
toolchain file plus a `set_source_files_properties`-style override, or splitting the file into
its own target. That is a build-system change, not a source change, and it is worth exactly the
4 bytes of size plus 9 matched bytes on one function, so it is recorded rather than pursued.

The general rule, which generalises past this project: **a compiler pin that the build system
cannot honour is a measurement setting, not a fix.** Check what the link actually uses before
counting any toolchain result as progress.

## 117. The two tails at 0x10002770 are a register-pressure artefact, not a source shape

Section 113 left exactly one call-inventory defect in the tree: `CrashDumpUnhandledExceptionFilter`
emits **10** `WriteFile` calls where the reference has **11**. The reference compiles the
exception switch as two jump tables with two structurally identical tails that differ only in
register assignment (tail A at 0x10002b7f uses `ecx`/`edx`, tail B at 0x10002c40 uses `eax`/`ecx`),
so msvc6 declined to fold them.

**The tail groups, walked from the `jmp` fan-in** (not the tables — the fan-in is unambiguous):

| tail | arms | case values |
|---|---|---|
| A `0x10002b7f` | 7 | `0x80000003`, `0x80000004`, `0xc0000025`, `0xc0000026`, `0xc000008c`, `0xc000008d`, `0xc000008e` |
| B `0x10002c40` | 12 | `0xc0000005`, `0xc0000006`, `0xc000001d`, `0xc000008f`–`0xc0000096`, `0xc00000fd` |

Our source already splits at exactly this boundary — both range tests are emitted at the
identical constants (`add eax,0x3fffffdb; cmp eax,0x68` and `add eax,0x3fffff71; cmp eax,0x6e`).
**The case partition was never the problem.**

**What the duplicated call actually is.** Tail A does not end in a `ret` or a jump past tail B —
it ends `push edx; jmp 0x10002c51`, landing *inside* tail B at its **second** `call esi`. So the
two tails share the newline `WriteFile` and duplicate only the **message** `WriteFile`. The
reference has 13 `call esi` sites for 19 arms; a whole-tail duplication would give 14.

**Three shapes measured against that, all rejected** (each from a clean
`git checkout HEAD --`, baseline 633/2115):

| attempt | result |
|---|---|
| `goto write_nl_a/b` — two labelled write sites, one per group | **526/2139**, SIZE_MISMATCH |
| newline `WriteFile` inlined into all 19 arms instead of a shared tail | **352/2267**, SIZE_MISMATCH |
| per-group locals (`exc_msg`/`exc_len` assigned per arm, one write per group) | **631/2123**, SIZE_MISMATCH |

The `goto` variants are the instructive failures: a label per group **defeats tail merging
outright** rather than splitting it — the object goes from 12 `call ebx` sites to 19, one per
arm, because an explicit jump target stops msvc6 from threading the arms into a common tail at
all. The per-group-local variant is the closest miss and the most informative: it does produce
**two** tails and drives the inventory to `WriteFile` **13**, total **46**, but msvc6 then
materialises the message/length into `eax`/`ecx` (`mov eax,0x10027208; mov ecx,0x12; jmp`) instead
of pushing them as immediates per arm, which is what costs the bytes. **Routing the message
through a variable is the wrong lever: the reference pushes immediates in every arm.**

**The lever that did work is register pressure, not the switch at all.** The reference keeps three
long-lived values in callee-saved registers across the switch (`esi` = `WriteFile`,
`edi` = `pExceptionPointers`, **`ebx` = `Context->Esp`, loaded at 0x10002931 — before the separator
write**, with the `-4` applied only at 0x10002c6c). Ours loaded `pCtx->Esp` after the switch, which
left `edi` free, and msvc6 filled it by caching the constant `0` (`xor edi,edi`, then `push edi`
for every `WriteFile` `lpOverlapped`). Hoisting the two stores to just above
`hProcess = GetCurrentProcess();`:

```c
if (hCrashLog != (void*) -1) {
        /* Write separator line */
        pStack = (unsigned int*) (pCtx->Esp - 4);   /* hoisted: reference loads */
        nFrames = 0x800;                            /* Context->Esp into ebx here */
        hProcess = GetCurrentProcess();
```

measures **633 -> 643 / 2115**, obj_size unchanged at **2115**, probe matched 532 -> 555 and
matched-reloc 842 -> 853. This is a pure statement-order move of two semantically dead-until-later
stores, and it is the first improvement on this row since section 106 measured the flag landscape
flat. **It does not add the call** — inventory is still `WriteFile` 10, total 43.

**Conclusion for the next lane.** The missing `WriteFile` is downstream of register allocation: the
two tails exist in the reference *because* three registers were already committed, leaving
different scratch registers live at each group's exit. No arrangement of `break`/`goto`/locals in
the switch reproduces it while the surrounding function still caches `0` in `edi`. The hoist above
recovers one of the three committed registers and is kept for the bytes; the remaining gap is the
same `ebx`/`edi` deferral cascade already named in the file header and section 81, **not** a
property of the switch statement. Do not spend another lane reshaping the switch.

## 116. A +10 win on CrashDump: hoist the stack-walk setup to the reference's computation point

Round 225 found an uncommitted edit left in the worktree by a probe lane, measured it, and it is
a genuine win — the first byte gain on `CrashDumpUnhandledExceptionFilter` in this session.

The edit hoists two initialisations about 110 source lines earlier, from just before the
stack-walk loop to immediately after the crash-log handle is opened:

```c
 if (hCrashLog != (void*) -1) {
+        pStack = (unsigned int*) (pCtx->Esp - 4);
+        nFrames = 0x800;
         hProcess = GetCurrentProcess();
         ...
         frameInfo[6] = 0;
-        pStack = (unsigned int*) (pCtx->Esp - 4);
-        nFrames = 0x800;
         for (;;) {
```

That is where the reference computes them (0x10002931/0x1000293a), far ahead of the loop that
uses them.

| | `rebrew test` | obj |
|---|---|---|
| before | 633/2115 | 2115 |
| **after** | **643/2115** | **2115** |

Measured at the link from a clean rebuild: **`.text` residue 8,664 → 8,652**, twelve bytes, with
the shipped file still 286,720 bytes and **zero differing bytes outside `.text`**. The object
size is unchanged, so this is pure placement, not extra or missing code.

**Why it works.** Computing `pCtx->Esp - 4` early lets msvc6 keep the value in a register across
the intervening block instead of rematerialising it at the loop head; the same class of lever as
section 101's link-order wins and the opposite of section 109, where hoisting a `memset` call
*cost* bytes because the call clobbered a live register. The distinction is that these two
statements are pure computation with no call between them and their first use.

**Process note, and it is the important part of this round.** The edit was sitting uncommitted
and unreported in a shared worktree. It was only found because the residue moved unexpectedly
during unrelated work and `git status` was checked before attributing the change. Two habits
made that recovery possible: gating on the *residue* (section 99's guard, added round 215) and
checking `git diff --stat` before trusting any measurement. Without them this would have been
recorded as a toolchain result and the real cause would have been lost.

## 118. Scope of the hoist lever: when it applies, and where it is already satisfied

Section 116's hoist produced the first byte gain in 21 rounds, so round 226 tested how far it
generalises. The selection rule matters more than the lever itself:

**It applies only to pure computation with no call between the reference's computation point and
first use.** Section 109 is the counter-example — hoisting a `memset` *call* on `gm_AllocSpieler`
cost 371 matched bytes, because a call clobbers the very register the reference is keeping live.
So the test is not "does the reference compute this earlier" but "does the reference commit a
**callee-saved register** to it early, across code that does not clobber it".

Surveying the remaining rows for candidates, most are already satisfied:

- **`srv_LoadBuf`** (0x1000a570): the reference parks the connection table base in `ebp` at
  0x1000a57c — `mov ebp,0x101deb00`, five instructions in — and uses it throughout
  (`test byte ptr [ebp],1`, `mov eax,[ebp]`, `mov cl,[ebp+0x18]`). **Our source already computes
  it at the same point**, in a `for`-initialiser:
  `for (i = 0, conn = (unsigned int*) 0x101deb00; ...)`. Candidate dead — and the row is at
  701/750 with only 49 residual bytes.
- **`cm_ExProdObjekt`** (0x1000e140): the only early callee-saved load is
  `mov ebp,[esp+0x1c]` at +0xa, which is ordinary parameter homing, not a hoistable computation.
  At 976/993, 17 bytes off.
- **`gm_ObjectsAvailble`** (0x10015f70): the prologue is a stack-array initialisation
  (`mov dword ptr [esp+0x18],0x92` …), with no register commitment to hoist toward.

That is the useful negative: **the lever is not a general-purpose sweep**. It fired on
`CrashDumpUnhandledExceptionFilter` because that function computes a context value *after* a
long block the reference spans with a committed register — an unusually large gap, created by the
stack-walk setup sitting ~110 lines from its first use. Rows whose values are computed near their
use, or homed in the prologue, have nothing to move.

Practical rule for the next reader: before proposing a hoist, check three things in order —
(1) the reference commits a **callee-saved** register, not a scratch one; (2) the span between
computation and first use contains **no call**; (3) our source actually computes it **later**
than the reference does. If any fails, the candidate is dead and costs a compile to prove it.

### The `gm_AllocSpieler` near-miss, settled at the link

One candidate passed all three tests and still lost, and it is worth recording because the
object rulers said the opposite. The reference commits `arg4` to `edi` at 0x10018990 and first
uses it at 0x100189c4 — 13 instructions, **zero calls between**, a textbook shape. Hoisting
`*(unsigned short*)(slot+0xa) = (unsigned short) arg4;` to sit directly after `slot[8] = 0x64;`
**reproduces the reference's instruction sequence exactly**: our object then emits
`mov word ptr [ebp+0xa],di` immediately after `mov byte ptr [ebp+8],0x64`, as the reference does.

Pursuing the neighbouring statements made the local block progressively more reference-like, and
the two object rulers moved in **opposite directions**:

| variant | match_count | aligned | obj |
|---|---|---|---|
| baseline | **1004** | 662/1056 | 3689 |
| + `slot[0xa]` hoist | 962 | 663 | 3689 |
| + `slot[0x20c]` sink | 961 | 664 | 3689 |
| + `slot[0x218]` hoist | 947 | **665** | 3689 |

`aligned` rises monotonically while `match_count` falls, with `obj_size` pinned — section 19/16
in its purest form. That made the candidate genuinely ambiguous at object level: structurally
correct, byte-neutral in size, and plausibly a link win masked by positional scoring.

**Measured at the link, it is a clear loss: residue 8,652 → 8,694, forty-two bytes worse.**
Reverted. So the anti-correlation was not hiding value — the moves shift byte offsets upstream
of a large unmatched region and the displacement costs more downstream than the local agreement
wins. **When `match_count` and `aligned` disagree, link and find out; do not reason about which
ruler deserves trust.**

Also dead on the same row, and it confirms an existing note generalises: hoisting the
`0x100a8c30` global load through a new `unsigned char* type_base` local produced
**byte-identical output** — 1004/3689, aligned 662, emitted instructions unchanged. msvc6 folds
the local away entirely, exactly as section 109 (round 216) found for the `lea` split.

## 119. `linktest.sh` already existed — the gap was that nobody was told

Section 118 ended on a rule: when the object rulers disagree, link and find out. That rule is
only actionable if linking a candidate is cheap, and every probe lane this session ran
object-only because a link measurement looked like a manual rebuild-relink-measure cycle.

**It is not. `scripts/linktest.sh` has done this all along**, and it is better than the manual
cycle because it recompiles with the exact command `build.make` records — so the flags cannot
drift — then relinks, applies postlink, and prints a per-function delta:

```
$ bash scripts/linktest.sh src/server.dll/DieGildeAddOn/game/spiel_c/gm_AllocSpieler.c
function                                  before   after   delta
gm_AllocSpieler                             2824    2866     +42  <-- worse
.text total 8652 -> 8694  (+42)
revert candidates: gm_AllocSpieler (+42)
```

Verified both directions this round: **+0 on an unmodified file**, and **+42 attributed to the
right function** when section 118's known-bad hoist is re-applied as a control.

Two reasons it went unused, both now fixed:

- **It was absent from `AGENTS.md`**, the file every agent reads first, and mentioned only in
  passing several thousand lines into `docs/TODO.md`. It is now documented in the Linking
  section next to `gate.sh`, with the worked example above and the reason it matters.
- **Its baseline snapshot was stale** — `.scratch/residue_base.log` contained a 183-byte
  *error message* from a previous run ("split_poc.dll is older than 1 source file") rather than
  a residue table, so the delta report had nothing to compare against. Re-snapshotted with
  `.venv/bin/python scripts/postlink_residual.py --write build/server.dll > .scratch/residue_base.log`.

The general lesson is worth more than the tool: **a capability nobody knows about is
indistinguishable from a missing one**. Three rounds of this session built or hand-rolled
measurement that already existed — the call inventory in section 112 was a genuine gap, but this
was not. Before building a measurement, grep `scripts/` and read the header comments; they carry
the rationale for why each one exists.

## 120. Two dead ends on `gm_AllocSpieler`, and a caution about shared-worktree probing

Round 228 ran the first link-judged lane on `gm_AllocSpieler` (2,824 residual bytes, 33% of the
tree). No win; two shapes are now measured and closed.

**The `work` buffer size is not a free knob.** Our source declares `char work[0x3fc]`, and the
reference's frame is `sub esp,0x41c`. Rounding the buffer to `0x400` does bring the emitted
frame to the reference's value — but it costs **+341 bytes at the link**. Matching the frame
size is not the same as matching the code that uses it: every `[esp+X]` displacement in the
function shifts, and the positional compare loses far more downstream than the prologue gains.
This is the same trap section 81 recorded for the `0x284`/`0x280` question, now confirmed from
the opposite direction — *making* the frame match is as costly as leaving it wrong.

**`double` → `float` on the trait interpolation is also a loss.** Changing
`(double) *(unsigned short*)(slot + 0xa)` to `(float)` in the comparison and the loop bound was
measured in the same probe: still **+341**. The x87 sequence the reference emits is not reached
by narrowing the C type here.

**The process caution is the more useful output.** This lane ran in a worktree shared with the
coordinator, and its intermediate states were visible as ordinary uncommitted edits. Measuring
"the baseline" while it worked produced **+345, then +18, then +5, then +341** on successive
runs of the same command against a nominally clean tree — because the source and the compiled
object were moving underneath. Two rules follow:

- **`git status` clean does not mean the build is at baseline.** `linktest.sh` recompiles the
  named file, but the rest of the object tree can still carry another lane's probe. Confirm a
  baseline by seeing `+0`, not by seeing an empty `git status`.
- **A number measured while another lane is mid-probe is worthless.** If the same command gives
  different answers on consecutive runs, stop measuring and settle the tree first.

Both were resolved by interrupting the lane, reverting with `git checkout HEAD -- <file>`, and
re-measuring until `linktest.sh` reported `8652 -> 8652 (+0)`.

## 121. `cm_ExSellObjekt`'s one-byte gap is a zero-extension, and the cast is load-bearing

`cm_ExSellObjekt` (0x1000d930) has the smallest object-size gap in the tree — **obj 2056 against
the reference's 2057, one byte** — with instruction counts equal at 667. That combination says
exactly one instruction differs in encoding, so round 229 chased it.

The streams agree through index 192. At **+0x236** the reference has:

```
0x1000db66  8a461e        mov al, byte ptr [esi+0x1e]     <- 3 bytes
0x1000db69  8b8d78010000  mov ecx, dword ptr [ebp+0x178]
0x1000db6f  50            push eax
0x1000db70  51            push ecx
0x1000db71  e84abb0000    call gm_QueryEntitySum
```

and we emit:

```
+0x236  mov ecx, dword ptr [ebp+0x178]
+0x23c  xor eax, eax                    <- the extra instruction
+0x23e  mov al, byte ptr [esi+0x1e]
+0x241  push eax
+0x242  push ecx
```

So it is not a shorter encoding of the same instruction: **we emit an extra `xor eax,eax`** to
zero-extend the byte, and the reference does not — it pushes `eax` with its upper bits
undisturbed, i.e. the callee's second argument is effectively don't-care above the low byte.
The reference also loads the byte *first* and the dword second; we do the reverse.

Two shapes tested against that reading, both measured at the link and both rejected:

| shape | link delta |
|---|---|
| narrow the prototype to `gm_QueryEntitySum(int, unsigned char)` | **+36** |
| drop the `(unsigned char)` cast at all four call sites | **+448** |

The second is the informative one. Dropping the cast is what "the reference doesn't zero-extend"
naively suggests, and it is **catastrophically worse** — the cast is load-bearing and correct.
A temporary local to force the reference's argument-evaluation order was also tried and lost
(object 680/2062, obj +6).

**What this actually means.** The reference's `xor`-free sequence is not reachable by changing
the *type* of the argument; msvc6 emits the zero-extension because the C value genuinely is a
narrowed byte, and every spelling that keeps that meaning emits it. The reference's form implies
its source did **not** narrow at the call site — the byte was already in a register as a full
word from an earlier operation, which is a property of the surrounding code, not of this
expression.

Recorded because the one-byte gap makes this row look like the cheapest win in the tree and it
is not: **three shapes, +36 / +448 / object-worse, all reverted.** Also worth noting for the
next reader, the header declares `gm_QueryEntitySum(int, int)` while the definition in
`spiel622.c` is `(int, unsigned int)` — a real inconsistency, but narrowing the declaration to
match the use measured worse, so it is documented rather than "fixed".

## 122. Bounding a missing byte with a jump displacement

`ls_LoadBuildingEntityState` (0x100128f0) is 3 bytes short (obj 1460 against 1463) and its first
non-relocation divergence is very early, at **+0x3c**. Early faults displace everything after
them, so it looked like the highest-leverage target left. It is worth recording how the search
was narrowed, because the technique is reusable and cost nothing.

**The first divergence is not a fault — it is a readout.** At +0x3c the only differing bytes are
inside a `jle` displacement: reference `0x4ba`, ours `0x4b8`. Both sides emit the same
instruction; only the target differs. That immediately gives an arithmetic bound:

```
ref  jle -> +0x4fe        ours jle -> +0x4fc
=> between +0x44 and +0x4fe we emit exactly 2 bytes fewer
=> the third missing byte is somewhere after +0x4fe
```

So a two-byte window was located without disassembling anything, purely from a branch
displacement (the same principle as section 95: a `jcc` width or target is a *measurement* of
downstream layout, never a defect in itself).

Walking that window in lockstep shows the streams desync at **+0x2af**, in a repeated
`ls_ReadVfsDataChecked` call pattern. The reference computes the address in two steps,
interleaved among the argument pushes:

```
0x10012b9f  8b5671    mov edx,[esi+0x71]
0x10012ba2  8bcb      mov ecx,ebx            <- load_result
0x10012ba4  57        push edi
0x10012ba5  6a01      push 1
0x10012ba7  03ca      add ecx,edx            <- second step, between the pushes
0x10012ba9  6a04      push 4
0x10012bab  51        push ecx
```

We fold the same expression into a single `lea`, which is shorter — that is where the two bytes
go.

Two shapes tested at the link, both rejected:

| shape | link delta |
|---|---|
| reorder the address expression to `load_result + field + off` | **+0** (byte-identical) |
| split it through an `int field_addr` local, two statements | **+52** |

The `+0` is the more interesting one: **msvc6 canonicalises the addition order**, so writing the
operands in the reference's order changes nothing — the same normalisation section 92 found for
commuted multiplies and section 107 for a double-negated comparison. And forcing the two-step
form through a local *defeats* the reference's scheduling rather than reproducing it, because
the local pins the value where the reference keeps it in flight between pushes.

That leaves the `lea`-vs-`add` split as another instance of the pattern in sections 109 and 120:
**the reference's instruction sequence is a scheduling outcome, and C can request the operations
but not their interleaving with the argument pushes.**

Existing prior art on this row, worth not re-deriving: the eight field reads are already spelled
`*(volatile int*)(esi + 0x71)` — one of the rare places where `volatile` *won* (section 94 records
it losing 4 of 4 elsewhere), because it forces the reference's per-call reload instead of a
cached register.

## 123. `drift_windows.py`: localise a byte fault without reading the bytes

Section 122 bounded a missing byte using a single jump displacement. That technique is
mechanical, so round 231 scripted it as `scripts/drift_windows.py` — and scripted, it is far
sharper than the manual version, because **nested windows subtract**.

The rule: a jump whose *encoding* matches the reference but whose *target* differs is not a
defect, it is a measurement. The target difference is exactly the byte drift accumulated between
the jump and its target, so every aligned pair yields a window `[jump, target)` with a signed
byte count — for free, without disassembling the window's contents.

```
python3 scripts/probe_function.py --va <va> --file <src>     # builds the object
python3 scripts/drift_windows.py <va> <size> build/objtest/probe_*.obj
```

Two filters matter and are built in: `call` targets are unresolved relocations in our object, so
they are pure noise and are excluded; and a jump target outside the function is a tail-call, not
a layout signal.

**Validation — it rediscovered a known finding unaided.** On `cm_ExSellObjekt` three windows
converge:

```
[0x49, 0x249)  +2      [0x230, 0x249)  +2      [0x234, 0x249)  +2
```

The surplus is inside the smallest, `[0x234, 0x249)` — **21 bytes**, which is exactly the
`xor eax,eax` that section 121 found at +0x236 by hand. The script located it from branch
targets alone.

**Nested subtraction, on `ls_LoadBuildingEntityState`:**

```
[0x3a,  0x4fa)  -2        [0x292, 0x3b6)  +2        [0x543, 0x5aa)  -3
```

The outer window is 2 bytes short while an inner window is 2 bytes long, so the shortfall lives
in `[0x3a,0x292)` or `[0x3b6,0x4fa)` and there is a *separate* surplus inside `[0x292,0x3b6)`.
**Two independent faults, separated without reading an instruction** — section 122 saw only the
outer window and therefore only one of them.

**A new lead on the biggest row.** `gm_AllocSpieler` shows `[0x4c3, 0x4d6)` drifting **+1 in 19
bytes**. Disassembling just those bytes shows we emit an extra 2-byte `jmp 0x4d7` that the
reference does not have: our `if (arg7) … else if (arg6) …` chain enters the shared
`slot[9] = (char) n;` store by branching over the second arm, where the reference falls into it.
Rewriting the chain as two independent `if`s (with `arg7 == 0 &&` guarding the second) measured
**+0 at the link** — msvc6 canonicalises the control flow straight back, the same normalisation
as sections 92, 107 and 122.

So the extra jump is real and localised, but not reachable by restructuring the conditional.
The window is recorded for whoever attacks that row next: **19 bytes, one surplus byte, at
+0x4c3**.

## 124. Drift sweep across the remaining rows, and a build-state trap

Round 232 ran `scripts/drift_windows.py` (section 123) across the rows it had not seen. The
useful output is a set of localised windows for future work:

| function | window | drift |
|---|---|---|
| `cm_ExCopyEntityData` | `[0x130, 0x165)` | **-9** |
| `cm_ExCopyEntityData` | `[0x152, 0x15d)` | **-4** → so ~5 bytes short in `[0x130, 0x152)` |
| `CrashDumpUnhandledExceptionFilter` | `[0x11c, 0x679)` | -9 |
| `ServerMainThread` | `[0x406, 0x55c)` | +1 |
| `gv_ExAllocGraveyardWorker` | `[0x128, 0x187)` | -156 |

**The `cm_ExCopyEntityData` window resolved to a known shape.** Disassembling the 34 bytes shows
our stream is byte-identical to the reference through +0x152; the shortfall is the *clamp*. The
reference emits **both arms inline** with a shared store:

```
0x1000ed4d  jle  0x1000ed56
0x1000ed4f  cmp  eax, 0x7f
...
0x1000ed56  b881ffffff  mov eax, 0xffffff81     <- low arm, inline
0x1000ed5b  eb05        jmp 0x1000ed62
0x1000ed5d  b87f000000  mov eax, 0x7f           <- high arm, inline
0x1000ed62  88040a      mov byte ptr [edx+ecx], al
```

We branch away to an out-of-line low-clamp instead, which is 9 bytes shorter. Two spellings were
measured at the link and both rejected: rewriting it as the reference's two-arm
`if (val <= -0x7f) … else if (val >= 0x7f)` costs **+3**, and swapping the arms while keeping the
in-range guard costs **+76,125** — that second one changed the semantics, and the damage spread
across thirteen functions, which is exactly what a semantic break looks like in this metric.

**The build-state trap is the more important finding.** After reverting that bad edit, a clean
source tree still measured 57.7% residue, and a full `find -name '*.obj' -delete` plus rebuild
did not fix it. The give-away was in `split_link.sh`'s own output:

```
placed split symbols: 319
exactly at their reference VA: 0        <- should be 246
```

The stale artefact was **`build/split_poc/`**, the split-link workspace — deleting the CMake
objects orphans it, and it is not regenerated on its own. `rm -rf build/split_poc` followed by
`scripts/split_link.sh` restored `exactly at their reference VA: 246` and residue 8,652
immediately.

So the recovery procedure, in order, when residue is wildly wrong and the source is clean:
**(1)** check `git status`; **(2)** rebuild objects; **(3)** check `exactly at their reference
VA` in the link log — if it is 0, **`rm -rf build/split_poc`** and relink. Step 3 is the one that
is easy to miss, because every other signal points at the source.

## 125. Guarding the composition collapse

Section 124 recorded a failure mode that cost most of a round: the split link places each object
at its reference VA, and when that collapses **every residue number is meaningless while nothing
says so**. The residue simply reads ten times too high, and every other signal — clean
`git status`, clean rebuild, zero compile errors — points at the source.

The only evidence is one line in `split_link.sh`'s output:

```
placed split symbols: 319
exactly at their reference VA: 0        <- should be 246
```

Round 233 turned that into a guard. `scripts/linktest.sh` now parses the line after linking and
refuses to report anything if fewer than 100 symbols landed:

```
COMPOSITION COLLAPSED: only 0 symbols landed at their reference VA.
         Every residue number below would be meaningless.  Fix with:
             rm -rf build/split_poc && bash scripts/split_link.sh
```

Verified both directions: it passes at the real value (246) and trips on a collapsed log (0).

This is the third guard on that script, and the set is worth reading together because each was
added after a specific round was lost to the failure it catches:

| guard | catches | cost when missing |
|---|---|---|
| stale-object | a source newer than its object (a revert without recompiling) | round 195 |
| attribution | a `.c` modified but not named in the run | round 179 committed a "-58" that re-measured "+56" |
| **composition** | the split workspace orphaned by an object delete | round 232 |

The general point, and the reason to keep adding them: **a measurement harness needs guards
against its own stale state more than against bad input.** Every one of these three produced
confident, plausible, completely wrong numbers, and in each case the tree looked clean.

## 126. `ServerMainThread`'s +3 window: a rematerialised constant the reference carries in a register

The drift sweep (section 123) gives `ServerMainThread` four nested windows, and subtracting them
is what makes the lead usable:

```
[0x406, 0x55c)  +1        [0x438, 0x510)  +2
[0x3c5, 0x487)  +3        [0x443, 0x498)  +3   <- 85 bytes, the tightest
```

The outer window is only **+1** while the inner one is **+3**, so there is a **-2** elsewhere in
`[0x406,0x55c)` — two faults of opposite sign, again separated without reading a byte.

Disassembling the tight window shows the surplus exactly. We emit:

```
+0x0454  8B  mov dword ptr [esp+0x14], 0xffffffff     <- 8 bytes
```

where the reference emits:

```
0x100097fb  4B  mov dword ptr [esp+0x1c], eax          <- 4 bytes
```

The reference already has the value in `eax`: four instructions earlier it loads
`mov eax,[ebx]` and tests `cmp eax,-1`, so on the equal path `eax` *is* -1 and it reuses the
compared value as the stored value. We rematerialise the constant instead.

**The source already expresses this correctly** — it stores `sent_bytes`, the same variable the
`if` compared:

```c
sent_bytes = *(volatile unsigned int*) transfer_progress;
if (sent_bytes == 0xffffffff) {
        ...
        *(volatile unsigned int*) (cmd_buffer_primary + 4) = sent_bytes;
```

so the divergence is not a missing idiom but a `volatile` interaction. Two probes settle which
side matters:

| change | link delta |
|---|---|
| drop `volatile` on the **store** | **+4** |
| drop `volatile` on the **read** (line 481 only) | **+0**, byte-identical |

So the store's `volatile` is **load-bearing** — it is what forces the value to memory in the
reference's shape — while the read's `volatile` at that site is **inert**. That is a useful
asymmetry to record, because section 94 treats `volatile` as a single lever that loses 4 times
out of 4, and the row-level exception noted in section 122 (`ls_LoadBuildingEntityState`, where
`volatile` won) is likewise a *read*. The rule is finer than "volatile loses": **a `volatile`
read can be inert or load-bearing depending on whether the reference reloads; a `volatile` store
is load-bearing wherever the reference writes through.**

The rematerialised constant itself is not reachable from source here: msvc6 chooses whether to
reuse the compared register or re-emit the immediate, and both C spellings that express the
intent compile to the same bytes.

## 127. Guarding the silent no-op, and locating `ServerMainThread`'s -2

Round 234 nearly closed a live lead on a false negative: a probe's edit silently failed to apply
(its target line occurred twice in the file, so the guarded replace refused), the run printed
**`+0`**, and a byte-neutral result reads exactly like "harmless, move on". Nothing in the output
distinguished *"this change is byte-neutral"* from *"there was no change"*.

`scripts/linktest.sh` now checks each named file against HEAD before measuring:

```
NOTE: identical to HEAD, so any delta below is the BASELINE, not a result:
        src/server.dll/DieGildeAddOnServer/server_c/ServerMainThread.c
      (did the edit apply?  check with: git diff --stat -- <file>)
```

Verified both directions: the note appears for an unmodified file and is **absent** when a real
edit is in place — including when that edit measures `+0`, which is the case that matters.

**It paid immediately.** Chasing the `-2` that section 126's subtraction proved must exist,
narrowing by overlap gives:

```
[0x406,0x55c) = +1   outer          [0x443,0x498) = +3   (section 126's surplus)
[0x438,0x510) = +2                  => the -2 lies in [0x498, 0x510)
```

Disassembling those 120 bytes shows it:

```
reference  0x10009838  mov ecx,[0x101deae8]     lea esi,[eax+ecx]      (6 + 3)
ours       +0x049b     mov esi,[0x101deae8]     add esi,eax            (6 + 2)
```

The reference loads into `ecx` and forms the sum into a **third** register with `lea`; we load
into `esi` and accumulate in place. This is the `lea`-versus-`add` fold of section 122 running in
the *opposite* direction — there the reference used two-step `add` where we folded into `lea`,
here it uses `lea` where we use `add`. **Neither form is "the msvc6 way"; both appear in the same
binary, chosen by which registers are live.**

Splitting the C into `payload_base = (char*) *(void**) 0x101deae8;` then
`payload_src = (unsigned int*) (payload_base + sent_bytes);` measured **+0** — and the absent
no-op note confirms the edit really applied, so this is a genuine canonicalisation, not a failed
probe. Same result as section 122's local, and the same reason: msvc6 folds the two statements
back together.

Recorded for the next reader: the reference **does** materialise `0xffffffff` in eight bytes at
0x10009858 on this sibling path, which is the very instruction section 126 identified as *our*
surplus 90 bytes earlier. The same constant is worth eight bytes in one place and four in
another, purely by whether a compared register survives — more evidence that the choice is
allocator state, not source shape.

## 128. `drift_windows.py` was wrong on backward jumps

The drift tool (section 123) assumed every jump runs forward, so it printed a window of
`[jump, target)` and took the raw target difference as the drift. For a **backward** jump that is
wrong in both halves: the measured span is `[target, jump)`, and the sign is inverted — if our
backward target sits 2 bytes earlier than the reference's, the code between target and jump
**grew** by 2, it did not shrink.

On `ahm_ExAllocAlchemist` both of its windows are backward, so both were reported inside out:

```
before:  drift -2 bytes in [0x1de, 0x1c7)      <- a negative-width window, visibly wrong
after:   drift +2 bytes in [0x1c7, 0x1de)  (backward)
```

The give-away was the negative width, which is worth watching for in any such tool. Fixed, with
forward windows re-checked against section 126's known values (`[0x406,0x55c) +1`,
`[0x443,0x498) +3`) to confirm the change was surgical.

**What the corrected window shows.** The 23-byte span is a loop, and the difference is loop
*shape*:

```
reference   body … inc edi ; cmp edi,5 ; jl back            <- bottom-tested, ONE branch
ours        cmp edi,5 ; jge out ; body … inc edi ; jmp back <- top-tested, TWO branches
```

Our source spells it `while (1) { if (!(i < 5)) break; … }`. The reference's form is a plain
`do/while`, and that is a genuine source-level lever rather than one of the canonicalised shapes
in sections 122, 126 and 127.

**It still loses: +439 at the link.** The file's own header already warned that "a do-while here
cascades: 998 obj / 285 match" — but that was measured at *object* level, before `linktest.sh`
existed, so the link number is new information and it is far worse than the object figure
suggested. The loop shape is correct in isolation and the register allocation it forces is not.

Worth stating as a rule, since three sections now point the same way: **matching the reference's
local shape is not the objective — matching its bytes is.** A construct can be demonstrably the
one the original used and still be the wrong thing to write, because the surrounding allocation
was produced by code we have not matched yet.

## 129. Re-sweep after the backward-jump fix, and why the Graveyard reload cannot be cached

Section 128 fixed `drift_windows.py`'s handling of backward jumps, which meant every earlier
sweep had to be re-run: a misreported window is worse than no window. Re-sweeping the rows
covered in sections 123 and 124 turned up **one** window that had been hidden —
`gv_ExAllocGraveyardWorker`, `[0x337, 0x395)`, **+5 bytes in 94**. The other rows' backward jumps
either did not exist or landed on the same targets already reported.

That is a useful calibration of the bug's blast radius: it distorted one row's reporting, not
all of them.

**What the window shows.** The reference reads a 16-bit id with a zero-extending pair:

```
0x10011f27  33c9        xor ecx,ecx
0x10011f2b  668b4d00    mov cx,word ptr [ebp]      <- 6 bytes total
```

and we emit:

```
+0x0332  4B  mov si,word ptr [ebp]
+0x0336  6B  and esi,0xffff                        <- 10 bytes total
```

The file's own header already names this gap ("target `xor ecx,ecx; mov cx,[ebp]`, ours
`mov si,[ebp]; and esi,0xffff`") and lists a long series of attempts against it. Two shapes it
does **not** list were measured this round:

| shape | link delta |
|---|---|
| hoist the id into an `unsigned short gid` local, used by both sites | **+117** |
| narrow only the accumulator (`int a` → `unsigned int a`), keeping both reloads | **+0** |

The **+117** is the informative one, and it explains why this gap is hard: the reference reads
`word ptr [ebp]` **twice**, once per use, and caching it in a local is exactly what a reader
"tidying" the code would do. That CSE removes the second reload and costs 117 bytes. The two
`*(volatile unsigned short*)` reads in the source are there precisely to defeat that, and
section 126's rule applies — this is a **volatile read that is load-bearing**, because the
reference genuinely reloads.

The `+0` confirms once more that a type narrowing which does not change what is loaded is
canonicalised away (sections 122, 126, 127).

So the 4-byte-per-read gap stays open, with its cause now stated precisely: **msvc6 chooses
`and reg,0xffff` over `xor`+`mov r16` for a 16-bit read into a register it is already using for
the accumulator.** The reference's form needs a *free* register at that point, which is an
allocation state we do not reach — the same conclusion as sections 109, 120 and 128, reached
from a different direction.

## 130. The register-pressure cascade is one row's fact, not the tree's

Sections 109, 120, 128 and 129 each closed a lead by attributing it to allocation state, and the
phrase that recurs is that we commit more callee-saved registers than the reference, so its
instruction forms are unreachable. Round 238 tested that directly, by comparing prologues rather
than reasoning from downstream symptoms.

| function | reference prologue | ours | claim |
|---|---|---|---|
| `CrashDumpUnhandledExceptionFilter` | `sub esp,0x280`, pushes `ebp esi` (**2**) | `sub esp,0x284`, pushes `ebx ebp esi` (**3**) | **true** |
| `gv_ExAllocGraveyardWorker` | `sub esp,0x10`, `ebx ebp esi`, `edi` deferred to +0x0a | **byte-identical** | false |
| `cm_ExCopyEntityData` | `sub esp,0xc`, `ebx ebp esi edi` | identical for 17 bytes | false |
| `ahm_ExAllocAlchemist` | — | identical for 23 bytes | false |

**Only `CrashDumpUnhandledExceptionFilter` actually commits a different register set.** On the
other three the prologues match byte for byte — same registers, same frame, and on the Graveyard
row even the same deferral of `edi` to +0x0a, which is a distinctive choice and a strong sign the
allocator is in the same state we are.

So section 81's frame rule is real but **local**: it is a fact about one function, and it was
generalised into a tree-wide explanation. That matters for planning, because "the allocator is in
a different state" is unfalsifiable at the point where it gets invoked, and it was being used to
close leads on rows where the allocator demonstrably is *not* in a different state.

The findings themselves stand — the `lea`/`add` fold (sections 122, 127), the zero-extend form
(section 129), the loop shape (section 128) are all still measured losses. What changes is the
*reason*: on those rows the divergence is a **local instruction-selection choice made from the
same register state**, not a downstream consequence of a different prologue. That is a narrower
and more hopeful conclusion, because instruction selection is driven by the expression shape
reaching the selector, which is a source-level property — it simply has not been found yet.

Method note worth keeping: **check the prologue before invoking allocation state.** It costs one
`rebrew asm` and one probe disassembly, and it distinguishes a real cascade from a convenient
explanation.

## 131. The Graveyard zero-extend is closed: four spellings, none reaches `xor`+`mov r16`

Section 130 narrowed these divergences from "allocator cascade" to "local instruction-selection
choice made from the same register state", which implies a source-level lever must exist.
Round 239 tested that implication on the sharpest case — `gv_ExAllocGraveyardWorker`'s 16-bit
read, where the reference uses 6 bytes and we use 10:

```
reference  0x10011f27  33c9      xor ecx,ecx
           0x10011f2b  668b4d00  mov cx,word ptr [ebp]
           0x10011f2f  8d3c31    lea edi,[ecx+esi]
ours       +0x0332     mov si,word ptr [ebp]
           +0x0336     and esi,0xffff
```

Reading the reference in context (re-anchored, after `rebrew asm` mid-instruction output
produced convincing garbage — section 112's rule) shows `xor esi,esi` initialising the loop
counter, so `lea edi,[ecx+esi]` sums *id + counter* into a third register.

Four distinct source spellings have now been measured against it:

| spelling | link delta |
|---|---|
| operand order `id + n`, matching `lea [ecx+esi]` | **+0** |
| explicit `(unsigned int)` widening on the read | **+0** |
| cache the id in an `unsigned short` local (round 237) | **+117** |
| narrow the accumulator type only (round 237) | **+0** |

Three are canonicalised away and the fourth is a large loss. **The reference's form is not
reachable from this expression by any spelling tried**, which is now a measured statement rather
than an appeal to allocator state.

What distinguishes the two forms is which register receives the widened value: `xor`+`mov r16`
needs a register that is *dead* at that point, while `and reg,0xffff` widens in place. Both
compile from the same C; msvc6 picks by what is free. Since section 130 established the register
state here is identical to the reference's, the remaining difference must come from **what else
is live across the read** — i.e. from code outside this expression, which is why editing the
expression cannot move it.

The practical rule, and the reason to record a closed lead in full: **when three or more distinct
spellings of the same intent all canonicalise to identical bytes, the lever is not in that
expression.** Stop rewriting it and look at what surrounds it. Sections 122, 126, 127 and 129 all
ended the same way, and naming the pattern is cheaper than rediscovering it a fifth time.

## 132. What surrounds the Graveyard read: an addressing-mode choice, also not source-selectable

Section 131 closed the read itself and pointed at the surrounding code, since that is what decides
which register is free. Round 240 looked, and found the answer — it is the **addressing mode of
the two stores**, not anything about the read:

```
reference   0x10011f2f  8d3c31          lea edi,[ecx+esi]              <- edi = INDEX only
            0x10011f39  889fe0d81410    mov byte ptr [edi+0x1014d8e0], bl
            0x10011f3f  888720980a10    mov byte ptr [edi+0x100a9820], al

ours        +0x033e     add esi,edi                                    <- esi = FULL ADDRESS
            +0x0347     mov byte ptr [esi], bl
            +0x034d     mov byte ptr [esi], al
```

The reference keeps the array base as a **constant displacement** in each store and carries only
`id + counter` in a register. We fold the base into the pointer, so our register holds a complete
address that must stay live across the `gm_RandomMod` call — and that is precisely why the
widened read has nowhere to go but back into `esi`, forcing `and esi,0xffff` instead of
`xor`+`mov cx`.

So the chain is now fully explained: **addressing mode → register occupancy → zero-extend form**,
and the 4-byte-per-read gap of section 129 is a consequence, not a cause.

Two more spellings were measured against it, both aimed at the addressing rather than the read:

| spelling | link delta |
|---|---|
| stores written as `*(char*)(0x1014d8e0 + a)` — explicit base + index | **+0** |
| narrowed store-value cast `(char)(random_value - 0x20)` | **+0** |

Both canonicalise. **That makes six distinct spellings measured on this one row** (four in
sections 129 and 131, two here), five byte-identical and one a 117-byte loss.

The conclusion is sharper than "not source-reachable": msvc6 chose to materialise the array base
into the pointer, and **no way of writing the C changes that decision** — `extern char[]` indexed
by a variable, an explicit absolute-address cast, and a base-plus-index cast all emit the same
bytes. The choice is made by the code generator from the *whole loop's* pressure, and the only
remaining lever would be changing what else the loop keeps live, which is the loop body's real
work and cannot be removed.

**This row is now closed with a complete mechanism** rather than an open lead — worth more than
leaving it on the list, because the next reader would otherwise re-derive the same six probes.

## 133. The `[reg + absolute]` pattern is common, but its cost is not

Section 132 explained the Graveyard row through an addressing-mode difference: the reference
keeps an array base as a constant displacement inside each store, while we fold it into the
pointer, which pins a live address across a call and forces the wider zero-extend form. The
obvious next question is whether that generalises, so round 241 counted it.

The reference uses `[reg + absolute]` addressing widely — 14 such store sites in
`cm_ExCopyEntityData`, 8 in `ahm_ExAllocAlchemist`, 12 in `gm_AllocSpieler`. So the *pattern* is
not special to the Graveyard loop.

**But the pattern's cost is.** Two checks say so:

- Our objects carry 19 `DIR32` relocations in `ahm_ExAllocAlchemist` — i.e. we materialise
  absolute addresses in comparable quantity. We are not systematically folding bases where the
  reference does not.
- `ahm_ExAllocAlchemist`'s drift windows are **unchanged** from section 128 (`[0x1c7,0x1de)` +2,
  `[0x254,0x2b0)` -2). If the addressing choice were costing bytes there, the windows would have
  moved when section 132's mechanism was understood — they did not.

So the Graveyard case is specific: it needs an addressing choice **and** a call inside the loop
**and** a 16-bit read competing for the same register. Remove any one and the pattern is free.
That is the same shape of conclusion as section 130 — a real mechanism, correctly identified, but
local rather than tree-wide.

**Two counting traps, both hit this round and worth avoiding:**

- `rebrew asm | grep -c "0x1[0-9a-f]{7}"` counts the **address column**, so every instruction
  matches and the answer is meaningless (286 for a 1002-byte function). Strip the leading
  `VA:` field first — the honest count was 64.
- Even then, a reference "absolute operand" count is not comparable to our `DIR32` relocation
  count: the reference's includes IAT slots and jump-table entries that never become relocations
  in an object. **Compare like for like, or compare drift windows instead** — the windows are
  already normalised against the reference.

Recorded as a closed question rather than an open lead: the addressing pattern is real, it is
understood, and outside the Graveyard loop it costs nothing.
