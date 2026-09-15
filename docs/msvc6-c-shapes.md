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
