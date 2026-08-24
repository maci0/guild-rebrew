# MSVC 6.0 (12.00) — register allocation: empirical findings

Reverse-engineering notes on how the MSVC 6.0 (CL 12.00) code generator
assigns `eax/ecx/edx` vs the callee-saved `ebx/esi/edi`, derived from
minimal probe functions compiled against the real toolchain
(`rebrew/msvc:6.0-win32`, wine) and byte-compared with the original
`server.dll` (target `gm_StartEntityQuery` 0x10016460, `gm_NextEntityQueryMatch`
0x10016290 and friends).

This complements `rebrew/docs/codegen/msvc/msvc-6.md`. Where that doc
describes instruction *shapes*, this one documents the *allocation
decisions* that pick registers — which is what decides whether a
C function compiles to the original bytes at all.

## Methodology

Every probe is a self-contained `.c` with the same externs as the target
function and one candidate body. It is compiled in the project build dir:

```sh
cd build
cp /tmp/probeNN.c _v.c
/home/maci/.local/bin/rebrew-cmake-cl /nologo \
  -I/home/maci/Desktop/Projects/relumea/guild-rebrew/src/server.dll \
  /W3 -MT /O2 /Gd /Fo"_v.obj" /Fd. -c _v.c
objdump -d _v.obj | sed -n '/<_gm_StartEntityQuery>:/,/^$/p'
```

Reference bytes come from `rebrew asm 0x10016460 --size 200 --json`.

## Register set & baseline (from rebrew docs)

- Volatile: `eax ecx edx` (caller-saved); callee-saved: `ebx esi edi`.
- VC 6.0 does **no constant caching**: loop-invariant constants stay as
  immediate stores (`c7 05 ...`) rather than being hoisted into a
  callee-saved register (4.x/5.0 hoist them; 6.0 does not).
- The zero-comparison era marker (5.0–7.1): `a == 0` = load + `test`/
  `cmp` + branch against a materialized zero register.
- The target function is fully register-resident: `flag1`→`dl`, `flag2`→`bl`,
  loop counter `i`→`esi`, arg walker→`eax`. No stack locals.

## Finding 1 — the "zero register" is allocated once and reused

For `if (g_item_def_table == 0) return 0;` followed by
`g_query_count = 0; g_query_match_count = 0;` and an `arg_count == 0`
compare, MSVC 6.0 materializes the constant `0` **once** and reuses it:

```asm
; reference (0x10016460)
mov  ecx, [g_item_def_table]   ; 8b 0d ...
xor  eax, eax                  ; 33 c0   <-- the zero
cmp  ecx, eax                  ; 3b c8
push ebx                       ; 53
jne  Lmain                     ; 75 02
pop  ebx                       ; 5b        ; inline early return
ret                            ; c3        ; reuses eax == 0
Lmain:
mov  ecx, [esp + 0xc]          ; arg_count -> ecx
xor  dl, dl                    ; flag2 = 0
xor  bl, bl                    ; flag1 = 0
cmp  ecx, eax                  ; 3b c8     ; arg_count vs the SAME zero
...
mov  [g_query_count], eax      ; a3 ...    ; eax-specific moffs encoding!
mov  [g_query_match_count], eax; a3 ...
jle  Lcheck_container
```

Notes:

- The `a3`/`a2`/`a1` opcodes are **EAX-specific** encodings
  (`mov moffs, eax`). Their presence is a reliable fingerprint that the
  value lived in `eax`, not just "a register".
- The early `return 0` is **inline** (`pop ebx; ret`) and reuses the zero
  register — no `xor eax,eax` on that path. The zero doubles as the
  return value, which is what anchors it to `eax`.
- The same zero register is used for the `arg_count` compare *and* both
  count stores, then it dies before the loop (`eax` becomes the arg
  pointer walker).

## Finding 2 — the LIVE-RANGE-ACROSS-LOOP flip (the big one)

Add a second literal `return 0` that is reachable after the loop
**without an intervening call** (a flag test like
`if (flag2 == 0) return 0;`), and the whole entry allocation flips:

```asm
; probe26a — probe26 + "if (flag2 == 0) return 0;" after the loop
mov  eax, [g_item_def_table]   ; a1 00 00 00 00  <-- table now in eax!
push ebx                       ; 53
push esi                       ; 56            <-- esi pushed at ENTRY
xor  esi, esi                  ; 33 f6         <-- zero now in esi!
cmp  esi, eax                  ; 3b c6
je   Lshared_tail              ; 0f 84 ...     <-- far je to a merged tail
...
mov  [g_query_count], esi      ; 89 35 ...     <-- count stores from esi
mov  [g_query_match_count], esi; 89 35 ...
```

The cascade:

1. The post-loop `return 0` (no call between entry and it) is **constant-
   commoned** with the entry `return 0` → MSVC merges them into one shared
   return tail at the end of the function (a far `je`).
2. The shared tail is reached both with and without the loop having run →
   the stack states must match → `esi` gets pushed at **function entry**
   (before the table check).
3. With `esi` pushed from the start, the allocator parks the zero in `esi`
   (volatile regs are all busy: `eax`=table, `ecx`=arg_count, `edx`=flag1,
   `ebx`=flag2), the table lands in `eax`, `-1` is materialized in the dead
   table register (`or eax,-1`), and the count stores become `89 35` (esi)
   instead of `a3` (eax).

Everything in Finding 1 that anchored the zero to `eax` is defeated by the
single extra post-loop `return 0`.

### What does NOT trigger or fix the flip (all tested, byte-compared)

Tried — allocation stayed flipped (zero in `esi`, table in `eax`):

- Changing the post-loop flag logic: `goto check_container` vs duplicated
  block vs `if (flag2 != 0) { error }` vs `if (flag2 == 0) goto query`.
- Making the final return a *variable* (`return container_id;`) instead of
  a literal — MSVC folds `container_id == 0` on that path and merges the
  tail anyway.
- Removing the final return entirely (fall off the end, C4715) — the entry
  return becomes inline again, **but** the zero is still parked in `esi`
  and the entry return still re-materializes (`pop esi; xor eax,eax; ...`).
- Comparison operand order (`0 == g_item_def_table`), variable declaration
  order (flags first / `i` before `arg_ptr`), store ordering (count stores
  before flag stores), explicit `int zero = 0;` variable threaded through
  the entry check and stores, `i = arg_count;` hoisted before the stores.
- Every `/O` variant and the pragma family from the summary (`optimize`,
  `intrinsic`, `check_stack`, `auto_inline`, `inline_depth`, `volatile`,
  `default_char_unsigned`), SP1–SP6 toolchains, `rebrew match
  --flag-sweep-only --tier quick` (produced no better result).

Conclusion so far: the flip is driven by the **presence of a post-loop
literal-0 return with no intervening call**, and the merge it causes. The
remaining unsolved piece is that in the reference the *error-path* `return 0`
(after the `LogMessageInternal` call) does **not** merge with the entry
return, while our probes' equivalent paths always do. The reference keeps
three separate return sites (entry inline, error separate, check returns
`container_id`).

## Finding 3 — flag variables: first-tested flag gets `dl`, second gets `bl`

`gm_StartEntityQuery` keeps two byte flags in registers. The assignment
tracks the *dispatch order*, not declaration order:

- case 7 handler: `mov dl, 1` → flag tested **first** (`test dl,dl;
  je check_container`).
- case 6 handler: `mov bl, 1` → flag tested **second** (`test bl,bl;
  je query_path`).

So the flag that the code tests first ends up in `dl`, the second in `bl`.
Writing the dispatch in the wrong order (`if (flag2 == 0)` before
`if (flag1 == 0)`) swaps them and produces `88 1d` where the reference has
`88 15` and vice versa (a 1-byte diff per store).

## Finding 4 — `-1` stores: immediate vs register is a *consequence*

`g_query_filter_owner = -1` etc. compile either to `c7 05 <addr> ffffffff`
(10B immediate) or `or reg,-1` + `mov [addr],reg` (8B, register form).
MSVC 6.0 picks the register form whenever a volatile register is free at
that point. In the reference it is **never** free (`eax`=zero,
`ecx`=arg_count, `edx`/`ebx`=flags) → all immediates. In the flipped
probes, `eax` is free (dead table) → `or eax,-1` → 1-byte-size stores
(`a3`/`66 a3`/`a2`). So immediate-`-1` stores are a downstream symptom of
Finding 1, not a separate knob.

## Finding 5 — `esi` push/pop placement tracks its live range

- Reference: `push esi` at loop entry (after the `jle`), `pop esi` right
  after the loop (before the flag dispatch). All post-loop blocks run with
  `ebx`-only frames → `[esp+8]` addressing for `container_id`.
- Flipped probes: `push esi` at function entry, `pop esi` in each exit
  path (three pops), and the post-loop blocks keep `esi` pushed →
  `[esp+0xc]` addressing.

The `[esp+8]` vs `[esp+0xc]` difference in the `container_id` load is a
direct consequence of when `esi` is pushed. You cannot mix: matching the
reference's `mov eax,[esp+8]` requires the whole "esi only in the loop"
scheme (Finding 1 intact).

## Finding 6 — shared store+call tail needs both values in the same register

The reference merges the query path and the check_container path into one
tail:

```asm
query: mov eax, [g_query_base]       ; 0x10016561
shared: mov [g_query_cursor], eax    ; 0x10016566
        call gm_NextEntityQueryMatch
        pop ebx
        ret
check: mov eax, [esp+8]              ; container_id
       test eax, eax
       jne shared                    ; 75 ec
       pop ebx
       ret
```

For the tails to merge, both paths must load their value into the **same**
register (`eax` here). In the probes, the query value consistently lands in
`edx` (reusing the just-dead `dl` flag register) while the check value is
in `eax` — so no merge happens and the check path emits its own
store+call. The query value landing in `edx` vs `eax` appears tied to
which block is emitted first (error block before query → eax is "fresh"
from the error's `xor eax,eax`; query before error → `edx` reuse).

## Practical recipe for writing matching C

1. Identify every literal `return 0` in the original and their *paths*.
   Any post-loop literal-0 return reachable without a call in between will
   merge with the entry return and flip the whole allocation. Restructure
   so post-loop "zero" returns either (a) come after a call, or (b) return
   a variable value the compiler cannot fold to 0 (e.g. the compared
   variable itself), or (c) fall off the end.
2. Keep the entry `return 0` inline (short `jne` + `pop ebx; ret`) so the
   zero doubles as the return value and anchors to `eax`.
3. Match the flag dispatch order exactly (Finding 3) — the first-tested
   flag is `dl`, the second `bl`.
4. Expect `-1`/`0` constant stores to be immediates **only when** no
   volatile register is free at that point; if your output shows
   `or reg,-1` + register stores, a register that should be busy (zero /
   arg_count) is free — the allocation upstream is wrong.
5. For byte-matching, `a3`/`a2` (eax-moffs) stores are the fingerprint
   that the zero is in `eax`; `89 35`/`89 0d` mean the zero moved.

## Finding 7 — address-taken parameter kills the callee-save base

The `cm_*` command handlers share a shape: the command pointer is kept in
a callee-save register (`push esi; mov esi,[esp+0x10]`) across a
`gm_GetFieldByType` call, then its address is passed to
`gm_ResolveEntityById((void**)&cmd, ...)` (the callee writes the resolved
entity back into the parameter slot). Reproducing this in C fails:

- With a plain `iVar1 = cmd;` copy (Ghidra's structure) MSVC **unifies**
  the copy with the parameter via copy propagation. Once `&cmd` is taken
  the unified value is memory-resident → the base lands in a volatile
  register (`mov eax,[esp+4]` emitted *before* the frame), the store
  address is CSE-hoisted (`lea esi,[eax+0x10]`), and the post-resolve
  uses get a second callee-save (`mov edi,eax`) — three registers where
  the reference uses one (`esi`).
- The reference loads the base into `esi` *after* the frame
  (`sub esp,N; push esi; mov esi,[esp+0x10]`) and never hoists the
  displacement.
- Tried and failed (all produce the split): copy via `char* p`, read via
  param / store via copy and vice versa, struct member access, single
  combined statements, `int` vs `unsigned short` field types, explicit
  result variables, /O1 /Og- /Oy- /G5 /arch:SSE, all declaration orders.
- A minimal head with **no** address-taken (`gm_GetFieldByType(cmd, ...)`
  twice, no resolve) DOES keep the base in `esi` — the address-taken is
  the trigger, not the call count.
- Affected: `cm_ExFree` (0x1000d730), `cm_ChkChangeBits` (0x1000cf30) and
  the other handlers that pass `&cmd` to `gm_ResolveEntityById`. These
  stay readable-`__asm` (byte-identical, RELOC) pending a C formulation
  that defeats the copy propagation.

## Finding 8b — multi-branch dispatch register cascade

`cm_ExCopyEntityData` (0x1000ec00, 901B) converts at the head (first 34
bytes byte-identical: frame, `mov edi,cmd`, two deferred-cleanup
`gm_GetFieldByType` calls, `mov [edi+0x14],eax`) and then diverges on the
dispatch register allocation:

- Reference: `mov ebx,[edi+0x1c]` — the field/type value (`fld`) lives in
  **ebx**, and the `cnt >= fld` dispatch emits `cmp edi,ebx; jae case4`
  with a duplicated `test edi,edi; jbe default` guard pair (a comparison
  chain, *not* a jump table — so the original was not a `switch`).
- Mine: `fld` lands in `esi`, the dispatch inverts to `cmp <fld>,<cnt>;
  jb check3`, and MSVC eliminates the redundant guard (it proves
  `cnt==fld` is subsumed by `cnt>=fld`). ~20 chain/switch formulations
  tested; every `switch` form compiles to a jump table (`lea eax,[cnt-1];
  cmp eax,3; ja; jmp [eax*4]`), and every if/else chain either inverts or
  removes the dead checks. The exact reference chain (jumped-to case4 +
  kept redundant guards) is not reproducible.
- The register cascade (fld → ebx vs esi) is the same class of GRA
  sensitivity as Finding 7: the reference's allocation is "better"
  (single callee-save for fld, reused later) and cannot be steered from C.

## Finding 8d — value propagation splits shared blocks

`gm_SetBuildingWorkerLimits` (0x10017400, 202B) converts at the head
(the `push esi; push edi; mov edi,[esp+0xc]` base + interleaved
`gm_StartEntityQuery` arg pushes + table `lea` chain match byte-for-byte)
and then diverges in the field chain:

```c
if (t23d == 0 && t23e == 0 && t23f != 0) { result[0x1c] = t23f; }
else { if (t23d < 2) t23d = 2; result[0x1c] = t23d; ... }
```

- Reference: keeps `t23d` in `cl` across the whole chain (reads
  `t23e`/`t23f` into `dl`) and emits **one** shared clamp block
  (`cmp cl,2; jae; mov ecx,2; ...`) for all three failure paths.
- Ours: MSVC6's value propagation proves `t23d == 0` on the
  `t23e != 0`/`t23f == 0` paths and **splits** the clamp — those paths
  jump straight to `mov cl,2` while only the `t23d != 0` path keeps the
  `cmp cl,2`. The result is semantically correct but a different block
  layout (5–20 bytes shorter). ~6 formulations (`&&` chain, nested ifs,
  duplicated else, ternary clamp, goto dispatch, inverted conditions)
  all trigger the propagation; none reproduce the single shared block.
- Same class as Findings 7/8b: the reference was compiled from a source
  shape that hides the value from the optimizer's path analysis, and
  that shape has not been found.

## Finding 8c — the convertible head pattern (summary)

The *only* shape verified to convert byte-identically so far: a base
pointer passed **by value** across two or more calls with no address-taken
and no multi-branch dispatch on its fields (`ls_LoadEntities` 0x10013230
RELOC 2268/2268; synthetic head with two `gm_GetFieldByType` calls). The
moment the function takes `&param`, dispatches on a field read into a
callee-save, or keeps a single-use value across a call, MSVC6's GRA picks
a different (split/reloaded) allocation than the reference.

## Finding 8 — multi-call value base converts cleanly

When the base is passed *by value* across two or more calls and its
address is never taken, MSVC 6.0 keeps it in a callee-save register
naturally — a minimal head compiles to the reference shape:

```c
/* head: two gm_GetFieldByType calls, base by value */
*(int*)((char*)cmd + 0x10) = gm_GetFieldByType((char*)cmd, *(int*)((char*)cmd + 0x10));
*(int*)((char*)cmd + 0x14) = gm_GetFieldByType((char*)cmd, *(int*)((char*)cmd + 0x14));
ebx = *(int*)((char*)cmd + 0x1c);
```
→
```asm
push esi
mov  esi, [esp + 8]      ; base -> esi
mov  eax, [esi + 0x10]   ; arg2 read via esi
push eax
push esi                 ; arg1 = base
call gm_GetFieldByType
...
```
This is the `ls_LoadEntities` (0x10013230, RELOC 2268/2268) class — the
large conversions that already match were all of this shape. The recipe:
never take the address of a base you also keep across a call; pass the
value.

## Finding 8e — a CONVERTIBLE recipe (verified)

`amt_ValidateOfficeCandidate` (0x1000b1c0, 205B) converted to C with a
**RELOC 205/205** match. The winning recipe, in order:

1. Base pointer used *by value* across a call, then dead (multi-use across
   the call is fine; address-taking is fatal).
2. Table scans written as `for (i = 0; i < 30; i++) { if (table[i] == x)
   break; }` — MSVC6 emits the do-while shape (`xor edx,edx; mov ecx,base;
   cmp; je; add; inc; cmp; jl`) byte-identically.
3. Post-scan table checks must use a **shared offset variable**
   (`off = i * 0x18;` then `*(int*)(0x101de5a4 + off)`), NOT the raw
   `i * 0x18` expression — MSVC6's linear-function factoring otherwise
   re-derives the address from the loop counter (`lea edx,[eax+eax*2+
   0x203bcb6]; cmp [edx*8],3`) when the displacement divides evenly by 8
   (0xb0 and 0xa8 fold; 0xa4/0xac do not — inconsistent per-expression).
4. Shared return tails: write `if (cond) { ... } return 1;` (return at the
   function tail) instead of `if (cond) return 1; ...; return 1;` — the
   former lets MSVC lay the shared return-1 out as the tail block with
   short forward `je`s, matching the reference.
5. `if (cond) goto L_ret0;`-style early returns merge into one shared
   return-0 block naturally.

Also verified: `memcpy(buf, (void*)(base + n*0x18), 24)` with
`#pragma intrinsic(memcpy)` emits `mov ecx,6; rep movsd` (per the
msvc-6.md docs).

**CRITICAL for the byte-identity guard:** converted functions must use
**absolute addresses** for every string constant (`(char*)0x1002a0a0`),
never C string literals. The byte-identity build (sha `c7ac331f…`)
reproduces the original `.rdata` layout exactly; a literal in a converted
`.c` adds new `.rdata` bytes, shifting the section and breaking ~150
bytes of absolute references in *unrelated* functions (observed:
m_alloc at 0x10006cc0). The rebrew test still reports RELOC (reloc
masking hides the shift), so only the final `sha256sum` comparison
catches it. `amt_fio_LoadAemter` (0x1000baf0, 606B) converted to RELOC
606/606 with this rule; also confirms the signed/unsigned branch rule
(loop bound as `unsigned int` → `jbe`/`jb`, matching the reference).

`ValidateAndAssignOffice` (0x1000b290, 425B, same family) is a documented
near-miss: the identical recipe gets 41/425 with the head matching, then
MSVC6 assigns `result` to `edi`+spill (frame grows to 0x1c, `buf` shifts
to [esp+0x14]) instead of the reference's `ebp`-resident `result` (frame
0x18, `buf` at [esp+0x10]). The cascade root is the byte-register choice
for `type4` (`dl` in ours vs `al` in the reference), which shifts the
scan counter register and everything downstream. ~8 formulations
(declaration orders A–D, inlined reads, off-variables) did not steer it.

## Open questions

- Why does the reference's error-path `return 0` (after the
  `LogMessageInternal` call) stay a separate block instead of merging with
  the entry return? The merge of *that* pair is what forces `esi` at
  entry in every probe tried. The call itself should make the zero's live
  range end before it (volatile clobber), so MSVC *could* re-materialize —
  it does, in the reference; it doesn't, in our probes. The deciding
  factor is still unknown.
- The query-value register (`eax` vs `edx`) and the `esi` pop placement
  are correlated with block emission order, but the ordering heuristic
  (why the error block precedes the query block in the reference but not
  in our C) is not yet pinned down.
- How the reference `cm_*` handlers keep the base in `esi` *despite*
  passing `&cmd` (Finding 7) — some C structure defeats MSVC6's copy
  propagation of `iVar1 = cmd`; it has not been found after ~25 variants.

Probe corpus: `/tmp/probe26.c` (correct allocation, no flag tests),
`/tmp/probe26a.c` (minimal flip trigger), `/tmp/probe27/31/32/33/34/35/
36/37/38.c` (structural variants, all flipped), `/tmp/probeA..D.c`
(declaration/order variants). All compiled with the command in
"Methodology".

## gm_CalculateProductionValue (0x10019720) — recursion + FPU

Recursive FPU cache function; C reconstruction in `spiel622.c` (#else of the
fence) is **semantically correct** (verified statement-by-statement against
the naked asm), but byte-matching stalls at 87/420 with four distinct
allocator/codegen divergences:

1. **Register choice for the live index**: reference keeps `entity_index`
   in `ecx` from entry (`mov ecx,[esp+4]` → later `mov eax,[ecx*4+table]`);
   every C formulation puts it in `eax` (indexing `[eax*4+table]` instead).
   This cascades: with `eax` occupied, the reference's `mov eax,[esi+0x38]`
   (cache) becomes `mov ecx,[esi+0x38]` in ours.
2. **`push edi` placement**: reference pushes `edi` only inside the recurse
   branch (`L_recurse: push ebp; push edi; lea edi,[esi+0x2e]`) — cold-path
   region allocation. Ours pushes `edi` in the prologue unconditionally,
   shifting every stack offset by 4 (`[esp+0x1c]` vs `[esp+0x18]` for arg2).
3. **`fidiv` vs `fild`+`fdivp`**: reference divides a double by a memory
   int with `fidiv dword`; ours converts the int to double first
   (`fild dword` + `fdivp st(1)`), even with the divisor as a named `int`
   or `unsigned int` local and with the division split across two
   statements. MSVC6's `fidiv` emission trigger here is not reproduced.
4. **`fimul` fusion**: reference multiplies `(double)v * int` as a fused
   `fimul dword`; ours emits `fild`+`fmulp` and reorders the constant
   multiply (`fmul 5fb8` before the `fild` of the int). A named int local
   for the masked param (`p = (unsigned char)param2; (double)v * p`)
   does not change this — the fusion peephole is suppressed in our shape.

Also confirmed while reconstructing: `0x101de450` is a **pointer global**
(`mov edx,[0x101de450]`), i.e. `g_entity_table` — the reference never uses
`0x101de450` as a literal base; `(double)` of the unsigned dword at
`ent+0x22` zero-extends via the `fild qword` pair (`[esp+8]=val,[esp+0xc]=0`),
so the source type is `unsigned int` → double.

## gm_KannObjektHergestellt (0x10019d30) — CONVERTED, patterns that mattered

Byte-identical C achieved (RELOC 407/407) after ~8 iterations. Each of these
was the deciding factor for one divergence class:

1. **Extra ignored call argument** — the reference calls `compute_size` with
   TWO pushed args (`push esi; push edi; call`), the callee reading only the
   first. The C form
   `((int (__cdecl *)(char*, int)) compute_size)(obj, entity_index)` (cast
   call) reproduces it — and the early `mov esi,[esp+0x1c]` (entity_index →
   callee-saved esi) follows from the arg materialization. A 1-arg call
   drops both the junk push and the early esi load.
2. **`count = 0` before the call** — the reference zeroes `esi` between the
   arg pushes and `call gm_StartEntityQuery`; the C must be
   `count = 0; q = gm_StartEntityQuery(...)` (assignment textually first),
   not `q = ...; count = 0;`.
3. **Signed limit type** — `int limit` (not `unsigned int`): the reference
   compares with `jl` (signed). The zero-extended byte load
   (`xor ecx,ecx; mov cl,[edi+0x1c]`) is unchanged either way.
4. **Inverted tail conditions prevent epilogue merging** — with
   `if (count < limit) goto use_max; return 0;` MSVC6 *merges* the three
   return-0 blocks into a shared split epilogue (`xor eax,eax` then
   `pop`-chain entered at two offsets) and shares one `jl` via `jmp`.
   Writing `if (count >= limit) return 0;` with the use_max code as the
   fall-through reproduces the reference's three separate return-0 blocks
   (`pop edi; pop esi; pop ebp; xor eax,eax; pop ebx; ret`) exactly.
5. **`avail` must be a temp, not a named variable** —
   `avail = gm_GetMsgField(obj, q); if (size - avail > requested) ...`
   with the subtraction written twice (CSE'd). A named `avail` gets
   allocated to ebp (reusing/destroying `size`); the inline temp form lands
   in ecx (`mov ecx, ebp; sub ecx, eax`), preserving size in ebp — which
   the reference does.
6. **use_max = min(size, requested)** — the reference spills `size` into the
   dead `obj` arg slot (`mov [esp+0x30], ebp` before the call) and reads it
   back at use_max (`mov ecx, [esp+0x14]`). The long live-range of `size`
   (through use_max) is what gives it ebp; entity_index gets esi.

## gm_CheckInventoryCapacity (0x10019ed0) — blocked (GRA/peephole)

Semantically correct C reconstruction preserved as a comment above the naked
function in `spiel622.c` (best result 35/395 after ~7 formulations). The
cap/goto CFG shape (single `cap` variable, shared clamp epilogue reached via
`goto clamp`) DOES reproduce the reference's prologue register set (4
callee-saved pushes, `edi`=entity_index) — that part was the key unlock.
Still blocked on three allocation/peephole details:

1. **Ent-address shape**: reference emits `mov ecx,[g_entity_table]; mov
   eax,edi; shl eax,6; add ecx,eax; mov eax,edi; add eax,ecx` (separate
   adds) then `mov al,[eax]`. Ours folds the `+idx` term into the load
   addressing mode (`mov cl,[edi+edx]`) and assigns the base to edx. Writing
   `ent = base + idx*0x40; ent += idx;` is strength-reduced right back.
2. **Base register**: `mov ecx,[g_entity_table]` (ref) vs `mov edx,[...]`
   (ours) — cascades into the idx*64 register (eax vs ecx).
3. **Clamp peephole**: ref emits `test ebp,ebp; setl al` (after the sub and
   a `pop edi` in between); ours emits `sets dl` directly on the sub flags
   (no re-test), plus `mov edx,0` instead of `xor eax,eax`.

Also notable: the return-clamp idiom `xor eax,eax; test ebp,ebp; setl al;
dec eax; and eax, ebp` == `(x < 0) ? 0 : x` (mask select); the reference
returns the RAW `requested` on the `t == 9` early path (no clamp).

## sim_PriorityUpdate (0x10015400) — CONVERTED (frame-size oracle)

Byte-identical (RELOC 83/83). The blocking divergence was the frame layout:
the reference does `sub esp,8` + `lea eax,[esp]` with the 2-byte compare
operand at `[esp+4]`; every `unsigned short local` formulation reused the
dead arg2 slot instead (`lea eax,[esp+0xc]`, no sub). The **sub esp,8 gave
away the original's local type**: an 8-byte `char local[8]` buffer (the
compare reads its first two bytes as `*(unsigned short*)local`). With that
type the arg-slot reuse is impossible (8 bytes don't fit the 4-byte slot)
and the frame matches exactly.

Lesson: when the reference frame size (sub esp,N) is larger than the
smallest local you're modeling, the original local is likely a bigger
buffer/array — the frame size is an oracle for the declared local types.
Also note the arg-slot reuse rule implied here: MSVC6 reuses a dead
argument slot for a small address-taken local (as in gm_CalculateProductionValue)
but a fresh frame slot when the local doesn't fit.

## sim_StartEntityQueryByType (0x10015460) — blocked (GRA)

Semantically correct C preserved in sim.c above the naked function (best
12/145 after ~6 formulations). The reference's register picture:
`esi`=arg1 (first callee-saved, loaded immediately), `edx`=type,
`edi`=table base (second callee-saved), `eax`=0 materialized at the top
(the 0-arg of every query call, pushed as `push eax`), `ecx`=the 589x lea
chain and the rec[0] dispatch byte (`cl`). Ours: arg1 in `edx` (scratch,
valid per-path since each branch reads `[arg1+0x5d]` before its call),
type in `ecx`, table in `esi`, 0-arg as `push 0` (no early materialization),
rec[0] in `al`. A `z=0` variable did not produce the early `xor eax,eax`;
a switch form ballooned to 189 bytes (not the if/else chain). The
pre-materialized 0 constant appears to be the linchpin of the reference's
register allocation, and no C shape reproduced it.

## AdvanceGameClock (0x100155c0) — blocked (arg4 live-range split)

Semantically correct C preserved in sim.c (best 19/200, ref 197). The
function's /60 and /24 magic-multiply idioms (`0x88888889` = ÷60 signed,
`0xaaaaaaab` = ÷24) and the negative-hours floored-modulo trick
(`q = (23-t)/24; t += q*24`) all reproduced once the day-loops were written
as do-while (`do { days++; } while (--q != 0)`) — a `while (q-- != 0)` adds
an unwanted pre-check.

Blocked solely on arg4's allocation: the reference keeps ONLY `esi` saved
and RELOADS arg4 from `[esp+0x10]` per section (live-range split — its uses
die at each `lea esi,[edx+eax]`), which forces the sequential store order
(memory operands serialize). Ours keeps arg4 in `edi` across the sections
(+2 push/pop) which lets the scheduler hoist section-2's `t` computation
before the section-1 stores and defers the minutes store past the idiv.
~9 formulations (single/shared/scoped temps, inline CSE, struct pointer,
do-while, zero-var) could not trigger the split. The clock struct is
`{int days; short hours; int minutes; int seconds;}` packed (SIZE 0xe);
the caller is `AdvanceGameClock((int*)0x10035880, 0, 1, 0)`.

## ReceivePacketHeader (0x1000a340) — blocked (cross-jump + branch polarity)

Semantically complete C preserved in server2.c (best 104/336; the remaining
232 bytes of divergence are offset shifts caused by one 23-byte difference).
All instructions match the reference except:

1. **Cross-jumping of the two identical error paths**: the reference emits
   the timeout error block (`gettick; cmp; jae; push 1/msg/line/file; call
   LogMessageInternal; push conn; call cm_ClosePlayerConnection; add esp,
   0x14; or eax,-1; pop; pop; ret`) INLINE at both recv sites (lines 0x52a
   and 0x552). MSVC6 merges our two tails into one shared block
   (`push 0x52a; jmp shared`) — saving 23 bytes. No C shape (inline,
   goto-add, nested-if, gettick-temp vs inline call) prevented the merge.
2. **merge1 branch polarity**: reference `cmp eax,-1; jne add; jmp wsa`
   (conditional to the near add block); ours `je wsa; jmp add` regardless
   of how the `r == -1` check is written.

Notable reproductions: the recv function pointer is stdcall (no caller
cleanup — `call edi` then straight on), the >=3 path reads the *dead arg
slot* for the never-set `r` (`mov eax,[esp+0xc]` — an uninitialized-read
reproduced naturally by reusing `r` after the conditional recv), and the
header-complete flag is a dword OR (`mov eax,[esi]; or al,0x80; mov
[esi],eax`) not a byte OR.

## gm_RandomStatModifier (0x10018450) — blocked (byte vs dword load)

Semantically correct C preserved in spiel62.c (best 29/78 after ~12
formulations). Everything matches except the char-param load width: the
reference does `mov bl, byte ptr [esp+8]` (partial-register load), which
forces the FPU conversion to re-read the param slot
(`mov eax,[esp+8]; and eax,0xff; mov [esp+8],eax; fild`) and the final
addition to be byte-sized (`add bl,al; mov al,bl`). Ours does
`mov ebx, dword ptr [esp+8]` and derives everything from the register
(`mov eax,ebx; ...; add eax,ebx`) — 5 bytes shorter. No C shape (param
direct, `char`/`unsigned char` locals, `==0`/`!x`/truthiness tests, inner
casts vs return-type truncation, ternary n shared across the merged call
block, `if` branch orders) nor any flag (/O1, /Ox, /O2 variants) flipped
the load width. What DID reproduce: the float comparison (`(float)x >=
const` → `fcomp dword ptr [const]; test ah,1; je` — C0-only, no unordered
bit) and MSVC6 merging the two gm_RandomMod calls into one shared block
via a ternary variable (`mov eax,0xb; je; mov eax,6; push eax; call`).

## Loop-form finding (gm_FindSlotById 0x10016240, ahm_QueryEntityBuildingType 0x1000c6a0)

Two more successful conversions, each with a decisive code-shape lesson:

1. **gm_FindSlotById (EXACT 72/72)** — a 589-entry table scan. Three keys:
   `int i = 0` BEFORE the base computation (the counter's `xor ecx` must
   land right after the arg1 load), the found-return recomputed from the
   counter (`return base + arg1*10896 + i*0x80`, not the induction
   pointer), and the increments BOTH in the for-clause (`for (; i < 0x55;
   i++, p += 0x80)` — the reference emits `inc ecx` before `add eax,0x80`).
2. **ahm_QueryEntityBuildingType (RELOC 102/102)** — a query loop with a
   mid-loop return. The `do { ... } while (q != 0)` form made MSVC6 PEEL
   the first iteration and rotate the loop so the next-match call sits at
   the loop top, duplicating the body with different registers. The plain
   `while (q != 0)` form emits the reference's non-peeled layout exactly
   (body once, next-match at the bottom, back-edge to the body).

## ahm_InitRandomEntity (0x1000c600) — blocked (fmul-loop store scheduling)

Semantically correct C preserved in alchemistry_logic2.c (best 87/110; the
only divergence is one loop's store placement). What DID reproduce: the
scan loop EXACTLY (EXACT bytes) once written as
`for (i = 0x20; i != 0; idx = (idx + 1) & 0x1f) { if (used == 0) goto
found; i--; }` — the idx-update as the for-increment and the counter
decrement in the body gives the reference's `dec; inc; and; test; jne`
order. A do-while peels (body duplicated, registers differ); a plain for
with `i--` as the increment emits `inc; and; dec` (wrong order).

Blocked on the 14-iteration float-copy loop: the reference emits
`fld [eax-4]; fmul dScaleFactor; fstp [eax]; add eax,0xc; dec edx; jne`
(store immediately after the multiply, 2-byte `fstp [eax]`); ours defers
the store past the add/dec (`add eax,0xc; dec edx; fstp [eax-0xc]` — 1
byte longer). ~12 formulations (for/while/do-while, increment-clause
orders, index vs pointer induction, temp variable, /G5//G6 CPU scheduling
flags) could not move the store. The reference's dScaleFactor is a
`double` (fmul qword).

## gm_CleanupObjectEntities (0x10015cf0) — blocked (addressing-mode roles)

Semantically correct C preserved in spiel.c (best 139/194; the remaining 55
bytes are pure encoding-role differences). The full structure reproduces:
the ptr-variable pattern (the reference computes `ptr = dy+0x5d /
ex+0x14 / st+0x178` in three branches that fall/jmp into ONE shared
`gm_RemoveObjectByType` call block, with a re-check `test eax,eax; je
cleanup`), and the `rep stosd` memset tail (EXACT).

Blocked on the base/index register ROLES in every `g_query_base + i`
addressing: the reference emits `[esi+eax]` / `[esi+edx]` (the loop counter
esi as the BASE), ours `[eax+esi]` / `[edx+esi]` (the base pointer as the
base) — same registers, different ModRM (`0x06` vs `0x30`). Swapping the C
operand order (`i + g_query_base`) and the /G5//G6 CPU-scheduling flags do
not change the roles. Also the NoopRet2 arg materializes in `ecx` via
`lea` (reference) vs `eax` via `add` (ours). ~6 formulations.

## cm_ExChangeFloat (0x1000eb70) — blocked (offset-temp register)

Semantically correct C preserved in cm_ExChangeFloat.c (best 132/135 —
98%). The Ghidra-decomp comment in the file gives the exact original shape
(`iVar1 = param_1` copy, `gm_ResolveEntityById(&pvStack_4, &pvStack_8,
(void**)&param_1, iVar2)` — the static output into the param slot — and the
comma-operator fallback chain `if (param_1 == 0 && (param_1 = pvStack_8,
pvStack_8 == 0)) param_1 = pvStack_4`). The check ORDER (static → existing
→ dynamic) and the address-taken param slot reuse all reproduce.

Blocked on ONE byte-register choice: the float-op's offset temp
(`mov edx,[esi+0x14]` in the reference vs `mov ecx,[esi+0x14]` in ours, 3
bytes). The full Ghidra shape folds `iVar1 + 0x10` into a field pointer
(`lea esi,[eax+0x10]`), and the address-taken `&param_1` forces slot
re-reads — both diverge more than the plain three-local form. ~10
formulations (Ghidra shape, &param_1, check orders, offset locals, operand
orders, int-array/char* access forms, /O1//G5//G6) could not move the temp
to edx.

## AnalyzeInstruction (0x10003260) — blocked (4th-check register role)

Opcode-length checker (183B); semantically correct C preserved in
ErrorModule.c (best 104/183 — the 1st/2nd/3rd/5th/6th checks are EXACT,
including the `or bl,0xff` 0xff-materialization from the signed `== -1`
compares). Blocked ONLY on the 4th check: the reference loads `[eax-2]`
into `cl` once (`mov cl,[eax-2]; cmp cl,bl`) and re-checks it at the
`L_chk_d0` block (`cmp cl,bl` after the `[eax-1] >= 0x40` branch), with
`[eax-1]` re-read fresh for the d0 mask. Ours compares `[eax-2]` directly
and keeps `[eax-1]` in cl — 10 bytes shorter. ~9 formulations (nested vs
two separate ifs, c/b2 locals in conditions, comma-operator assignments,
re-reads) could not make MSVC6 materialize `[eax-2]` into cl across the
branch; the second `[eax-2]` check is always eliminated (dataflow knows it
is unchanged).

## cm_ChkMoveCredits (0x1000cb20) — CONVERTED (call-site byte view)

Byte-identical (RELOC 171/171). The final 2-byte blocker was the second
`gm_QueryEntitySum` argument: the reference emits the RAW byte load
`mov cl, byte ptr [esi+0x1c]; push ecx` (register upper bits garbage —
Ghidra shows the CONCAT31 of `extraout_ECX`). A `(unsigned char)` cast
forces `xor ecx,ecx`; a `(char)` cast forces `movsx`. The raw byte appears
when the CALLER's view of the callee prototype has `unsigned char` for the
param. Since the callee's actual definition is `unsigned int`, the
conversion uses a fn-ptr cast call
`((int (__cdecl *)(int, unsigned char)) gm_QueryEntitySum)(...)`. Same
pattern as the compute_size (extra arg) and ShutdownLogAndErrorHandler
(int mask) casts: the reference's caller-side prototype view differs from
the current definition, and the cast-call reproduces it.

## gm_ResolveEntityById (0x10015e90) — blocked (existing-loop counter register)

Entity resolution (static/dynamic/existing table scans); semantically
correct C preserved in spiel.c (best 193/211). The static and dynamic scans
are EXACT (the counter in `ecx` — matching both sides). Blocked on the
existing scan: the reference loads the count into `edx` and keeps the loop
counter in `ecx` (`mov edx,[count]; xor ecx,ecx; ...; inc ecx; cmp ecx,edx`);
ours puts the count in `ecx` and the counter in `edx`. Also reproduced:
the existing-loop counter increments ONLY on non-zero entries (the `je`
skips the `inc` — the counter must live inside the `if (*p != 0)` branch,
not the for-increment), and the query base must be read via the
`g_query_base` pointer variable (a load), not the literal. ~8 formulations
(declaration orders, inline count vs local, explicit `n <= 0` check, named
global vs raw address) could not move the count to edx.

## cm_ExModifyStat (0x100100a0) — blocked (FPU clamp compare forms)

Stat-modify with float min/max clamping; semantically correct C preserved
in cm_ExModifyStat.c (best 107/159 — the head, the `fild`+`fcom dword`
float-compare from the `(float)(int)(...)` sum cast, and the first
`sum < max` check are EXACT). Blocked on the clamp region's FPU compare
forms: the reference emits `fcom min; fnstsw; test ah,0x41; jne` (C0|C2)
for the second comparison while using `test ah,1` (C0) for the first —
ours emits `test ah,1; je` (inverted polarity) for the second regardless
of the C form (`sum < min`, `g_stat_min > sum` [loads the const →
`fcomp st(1)`], `!(sum >= min)`, `!(g_stat_min <= sum)`). ~6 formulations
plus the Ghidra-decomp condition shape `((max <= f) || (min < f)) && (max
<= f)`. The register-layout of the clamp block (fstp/fld swap, __ftol
call) follows once the tests match.

## CheckZoneAvailability (0x10014ff0) — DONE (induction-base folding)

Converted to C, RELOC 175/175. Finding: **MSVC6 folds the largest
positive address constant into the induction pointer's base when the
pointer is re-derived each iteration** (`e = base + i*0x18` → init
`add eax, base+1`, accesses `[eax+4]/[eax-1]/[eax]`). Writing the loop
in pointer-increment form (`e = base + 8;` before the loop, `e += 0x18;`
at the loop tail — the same shape as the neighboring `find_zone_record`)
keeps the base at `zone_table+8` with the reference's `[eax+5]/[eax]/[eax+1]`
displacements. Struct-field access (`struct zone_record` sized 0x18) does
NOT prevent the fold — only the increment-form source does. Contrast with
`FindRecord` (0x10014f30) / `plt_SetPlantMap` scan1 (0x100150a0): there the
reference itself has the +1 folded (`lea esi,[edi+9]`, `[esi-1]/[esi]/[esi+4]`),
so per-iteration recompute or `p = base+9` is the matching form. Rule of
thumb: **read the reference's folded base constant from the init `lea`/`add`
and pick the C pointer form that reproduces it** — recompute-for-each-iteration
yields the compiler's own folding, increment-form preserves the source base.

## plt_SetPlantMap (0x100150a0) — DONE (constant coalescing + byte-reg pairing)

Converted to C, RELOC 257/257. Findings:
- **Explicit marker variable forces constant materialization.** The reference
  pre-loads `0xffffffff` into edx once (`or edx,0xffffffff`), then uses `dl`
  for the two byte marker compares and `edx` for the dword `-1` store. This
  appears only when C keeps a named `unsigned char marker = 0xff` (as in the
  neighboring `FindRecord`); literal `0xff` compares compile to
  `cmp byte[mem],0xff` immediates and lose the `or`/`dl` form.
- **Dead param-slot reuse:** the SearchRecordTable result lands in
  `zone_type`'s stack slot (`mov [esp+0x20],eax`) because zone_type's value
  was hoisted into ebp early (used as the call arg AND after the loops).
  If the C uses the wrong variable there (e.g. `extra`), the local gets a
  fresh slot and every `[esp+N]` offsets shift by 4.
- **The `if (A) goto; ...; if (B) x; else y;` two-test idiom reproduces
  exactly when A and B are DIFFERENT variables** — here first test is
  `extra`, second `zone_type`; both values live in different registers
  (fresh load vs ebp copy) so MSVC6 emits both tests.
- **Byte-store/load pairing:** the two `(char)` field stores compile with the
  y-value in cl and x in dl (loads emitted y-first, x-second, store y at +9,
  x at +8 AFTER the interleaved map test). Source order that reproduces it is
  x-store THEN y-store (`rec+8 = x; rec+9 = y;`) — MSVC6 reorders to the
  y-first/cl form. The naive source order (y then x) swaps the pairing.

## ProcessSendData (0x1000a860) — blocked (rep-movsd src register role)

Connection loop iterating 8 slots (`0x101deb00` + `0x264264` stride to
`0x114ffe20`, signed `jge` end compare — cast to int, else `jae`); per
slot: flag bit 1 gate, `SendPlayerData`, inner packet loop
(pkt at `+0x2641f4`, flag bit 0x100, `memcpy(dst +0xb1, pkt, 0x99)`
via rep movsd/movsb, `FreeCommandBuffer(conn, pkt)`, clear flag bit,
re-send). Semantically correct C preserved in server3.c (best 18/132).
Blocked on two coupled allocation choices: (1) the reference loads the
packet ONCE into esi (the rep movsd src register) at the loop top and the
`mov eax,[ebx+0x2641f4]` reload for the FreeCommandBuffer arg comes AFTER
the rep (esi was consumed); our compile keeps the packet in edx (rep does
not clobber edx) and pre-pushes it before the rep — no reload. (2) the
reference computes the memcpy dest with `lea edi,[ebx+0xb1]` in-loop; our
compile LICM-hoists `conn+0xb1` into ebp (a 4th saved register, +1 byte
prologue) and re-expresses the pkt load through it (`mov edx,[ebp+0x264143]`).
~4 formulations (inline vs named pkt, int vs char* pkt, while-cond
assignment, unsigned char* conn) could not move the packet to esi or keep
the dest lea in-loop.

## m_PoolAlloc (0x10006d20) / InitBuildingTypeTable (0x1000b040) — blocked (alignment-prefixed memset)

Both functions otherwise convert cleanly (m_PoolAlloc 223/270 with msvc6
`/O2 /Oy-`; InitBuildingTypeTable 261/372 with explicit-store C) but share
an unreproducible memset expansion. The reference emits a **dest-alignment
prelude** before the dword stores:

    xor eax,eax
    lea ecx,[edi+edi*2]   ; (3*dest)&3 = alignment offset
    and ecx,3
    sub ebx,ecx           ; len -= prefix
    jle L_after
    rep stosb             ; prefix bytes (aligns dest to 4)
    mov ecx,ebx
    and ebx,3
    shr ecx,2
    rep stosd             ; dwords
    add ecx,ebx
    rep stosb             ; tail

Every msvc 4.0/4.2/5.0/6.0/7.0 / VC7 compile of ~25 probe shapes emits the
plain dword+tail form (`shr ecx,2; rep stosd; and ecx,3; rep stosb`)
instead. Probed: constant/runtime/local/unsigned/size_t lengths, escaping
locals (`&n` taken), global vs param dests, explicit `for`/`while(n--)`
zero loops, the CRT `memset` loop source, `/O1 /O2 /Ox /Os /Ot /Og`, codegen
`/G3 /G4 /G5 /G6 /GB`, `/Zp1`, `/Oy-`, `/Ob0/1/2`, msvc5 SP1-3 / msvc6
SP3/SP6. `/Og-` (`/Oi /Ot /Oy`) keeps the length in a local (matching the
reference's `mov [ebp-4],0x3f0; mov ebx,[ebp-4]`) but expands the memset
without the prelude; `/Ot`/`/O1` emit a real `call memset`. The reference
also spills payload+len to dead param slots (`[ebp+0xc]`/`[ebp+8]`) around
the memset — a consequence of the prelude's extra register pressure. Suspect
a service-pack or custom-build codegen difference; preserved C is in
m_alloc2.c / server4.c. The rest of both functions (alignment calc, node
search, slot scan, and InitBuildingTypeTable's loop + 42 unrolled constant
stores with their `mov al,N` value grouping) matches msvc6 `/O2` exactly.

## lb_ExPlayerlist (0x100145e0) — DONE (struct-for-layout + auto-zero + tail layout)

Converted to C, RELOC 209/209. Findings:
- **A struct `{int count; int ids[8];}` (36 bytes) reproduces the contiguous
  count+ids frame** that a separate `int count; int ids[8];` does not — the
  compiler parked `count` in a dead param slot and the `memcpy(&count, 0x24)`
  became a garbage read. The struct forces adjacency; `memcpy(msg+0x14,
  &list, sizeof(list))` then reads the intended 9 dwords.
- **The reference's `rep stosd` (9 dwords) + redundant `mov [esp+0xc],eax`
  (count=0) requires an EXPLICIT `memset(&list, 0, sizeof(list))` before
  `list.count = 0;`** — MSVC6's auto-init of fully-copied partially-written
  locals did not fire; the explicit memset places the rep-stosd first and the
  count store after, byte-identical to the reference.
- **Tail layout:** the final `if (result != -1) { log; return 0; } return -1;`
  puts the -1 path at the end (`je`, `or eax,0xffffffff`); the reference has
  the -1 path in fall-through with `jne L_queued_ok` and a no-op `or eax,eax`
  — produced by `if (result == -1) { return result; } log; return 0;`
  (`return result` keeps eax untouched; `return -1` forces `or eax,0xffffffff`).
- Same-function idioms reconfirmed: `(result + 1 == 0) ? -1 : 0` for the
  sbb chain; dword flag loads (`*(unsigned int*)conn & 0x200` — a byte load
  here constant-folds to `test cl,0`, a no-op).

## amt_SwapOfficeHolders (0x1000b880) — blocked (epilogue merging + frame)

Semantically correct C preserved in aemter2.c (best 10/263 with msvc6
`/O2 /Gd` — the same ratio as other blocker-class functions, i.e. the CFG
matches and the frame/allocation diverges). Two coupled allocator choices
differ from the reference: (1) the reference INLINES each error epilogue at
its site — the call-result paths (`req==0`, `ent_a_rec==0`, `ent_b_rec==0`)
emit plain `pop;pop;pop;pop;ret` with NO `xor eax,eax` (eax already 0 from
the test), the other error paths emit `xor eax,eax` — while our compile
tail-merges all six into one shared xor block; (2) the reference uses zero
stack locals (req lives in the dead arg1 param slot, `ent_a_rec` in ebp,
ent_a/ent_b in edi/esi, swap temps in ecx/edx/eax) while our compile spills
8 bytes (`sub esp,8` — req + a swap temp), shifting every `[esp+N]` offset
and breaking the byte identity. Note the reference's `if (req == 0)` compiles
to `jne L_have_req` (error in fall-through, inline epilogue) vs ours
`je L_return0` (shared block) — epilogue-merging is the culprit. Also
confirmed: `lea edx,[ecx+ecx*2]; lea edi,[edx*8+base]` for `base + i*24`,
`test edi,edi; jne` kept even though `base+i*24` is never 0.

## gm_DeallocEntity (0x10017fb0) — FENCED + PROVEN (267/278, scheduling swap)

Entity deallocation; C in the #else fence of spiel62.c, PROVEN via
`rebrew prove` (symbolic equivalence). Findings:
- **The `_emit` byte sequences in the naked body are 16-bit ops the inline
  asm parser can't spell** — `66 A1 moffs` = `mov ax,[abs]`, `66 81 3E FF FF`
  = `cmp word [esi],0xffff`, `FF 0D moffs` = `dec dword [abs]`. All three
  express directly in C (`*(unsigned short*)0x10035880`,
  `*(unsigned short*)entity == 0xffff`, `g_citizen_count--`).
- **`dec [g_citizen_count]` (the FF 0D memory form) requires the NAMED
  symbol** — a raw `*(int*)0x10035434 -= 1` compiles to load/dec/store.
- **`mov [ebp+0x100358a4],eax` (index-based address) requires the raw
  expression `*(int*)(0x100358a4 + index * 0x21c) = -1`** — writing
  `*(int*)(entity + 4)` emits the 3-byte `mov [esi+4],eax` instead of the
  reference's 6-byte ebp+disp form, cascading into a different store order.
- **Branch layout:** `if (arg2 != 0) { big } else { sprintf }` (sprintf in
  the else, emitted as the jump target at the end) reproduces the
  reference's `je L_param2_zero`; the inverted if put the sprintf in
  fall-through.
- **Persistent 11-byte blocker:** the refs-fill `memset(...0x20)` setup
  schedules `mov ecx,8` before `lea edi,[ebp+0x100358fc]`; the reference has
  them reversed. ~6 C/flag variations (operand order, parenthesization, /G3
  /G5 /GB /G6 /O1 /Ox) did not move it. All other 267 bytes match, and the
  function is semantically PROVEN.

## ls_LoadExistingEntities (0x100127d0) — FENCED + PROVEN (271/282)

Record loader; C fenced in loadsave2.c's #else, PROVEN via `rebrew prove`.
Blocked on two coupled register-role choices: (1) the reference sinks the
`offset = 0` store into the loop preheader (after the `count <= 0` guard —
`xor ebp; test; jle; xor ebx`) while our compile emits it before the guard;
(2) the reference's `lea esi,[offset+base]` puts the offset in the ModRM
base slot, ours `[base+offset]` — despite the same `offset + base` C
expression. Declaration order, for-increment forms, guard+do-while, and
/O1 /G5 /GB did not move either. Everything else matches: the `_emit`
`mov ecx,[0x100a8c34]` / `mov [0x10035450],eax` = plain global reads/writes
(`g_100a8c34`, `g_query_limit`), the record field reads at +0/+2/+6/+0xa/
+0xe/+0x12/+0x13/+0x1c with the 0x43 stride, and the shared `L_ret0` epilogue.
Note: proving a fenced function requires the toml status to be
NEAR_MATCHING first — run `rebrew test <file> --cflags "/O2 /Gd"` (no naked
define) to compile the #else path and set it, then `rebrew prove`.

## srv_Init (0x10009d30) — FENCED + PROVEN (38/296)

Server init; C fenced in server2.c's #else, PROVEN via `rebrew prove`.
Blocked on two allocator choices: (1) **MSVC6 lays the four string buffers
by size** (b2@[esp+0], b0@[esp+0xc], b1@[esp+0x48], b3@[esp+0x110]) while
the reference keeps them contiguous in declaration order
(b0@0xc, b1@0x20, b2@0x104, b3@0x110) — sizes b0[0x14], b1[0xe4], b2[0xc],
b3[0x3f4]; (2) `SetThreadPriority(GetCurrentThread(), 2)` hoists the
`push 2` before the GetCurrentThread call (a temp handle fixes the order
but re-introduces a stack local that shifts the buffers). Other findings:
- **Deferred cleanup across 4 calls** — `InitializeLogAndErrorHandler`
  (4 args, via a cast-call against the 1-arg prototype), `InitPacketPool`,
  `gm_Open` all pop their cdecl args in ONE `add esp,0x18` after gm_Open.
- **The `0x7fa6` stack-arg reuse**: `InitPacketPool(0x7fa6)`'s push doubles
  as gm_Open's 2nd param — only reproducible by calling gm_Open as a 1-arg
  cast-call (`((int(__cdecl*)(char*))gm_Open)(b1)`); a literal 2-arg call
  emits a second push (+4 bytes).
- The `_emit` sequences decode as `call [GetCurrentThread]` /
  `call [SetThreadPriority]` (IAT entries at 0x1002406c/0x10024068),
  `mov ecx,[0x10117688]`, `mov [0x101176ec],eax`, `mov dword[0x10117690],0`,
  `lea ecx,[esp+0]` (the sprintf's 3rd arg = &b0).
- strcpy/strcat inline as the repne-scasb strlen + rep-movsd/movsb copies
  when written as plain `strcpy`/`strcat` on the char buffers.

## cm_ExChangeBits (0x1000eaa0) — blocked (address materialization + prove explosion)

Bitmask edit handler; C preserved as a comment in cm_ExChangeBits.c (best
18/213 — the Ghidra decomp at the top of the file matches the asm exactly).
Blocked on: MSVC6 materializes `base + 0x10` into a callee-saved edi across
the `gm_GetFieldByType` call (`lea edi,[esi+0x10]; ...; mov [edi],eax`) while
the reference emits `mov [esi+0x10],eax` inline; the `gm_ResolveEntityById`
arg pushes are also scheduled differently (~7 C formulations: iVar1/orig
copies, char* base, target-variable selection, comma-form, switch vs if-else,
declaration orders — none moved the materialization). Additionally
`rebrew prove` cannot mark it PROVEN (symbolic-execution state explosion even
with --loop-bound 30 / slice offsets), so the #else fence cannot be used
(SIZE_MISMATCH would fail `rebrew verify`) — the function remains plain
naked with the C as a comment.

## ls_ID2Ptr (0x10014070) — blocked (lazy ebp save, first draft)

491-byte savegame/entity-link fixup; first-draft C preserved in /tmp/lsid.c
(best 103/491). The reference pushes ebp/esi/edi together in the prologue
(ebp = the outer g_query_limit-loop counter) while MSVC6 pushes ebp lazily
at the outer loop's preheader (shifting every [esp+N] offset). Other
first-pass deltas: the resolve out-param locals and the lookup-array pass.
The decode is complete (see the file comment): g_1003546c player lookup,
gm_StartFilteredEntitySearch(1,5,0xa), the g_file_version-gated lookup
array, the 0x21c-stride entity pass with the word@-0x170 gate and
resolve/replace of ids at -4/0, and the outer loop's linked-list attaches
(pv1->5d / pv2->14 / pv3->178 with the 0x3f tail walk).

## cm_ExAllocThemaPredigt (0x1000f2f0) — FENCED + PROVEN (76/172)

Sermon-theme allocator; C fenced in cm_ExAllocThemaPredigt.c's #else,
PROVEN via `rebrew prove`. Blocked on pointer materialization: the
reference computes `payload = cmd + 0x18` and `dst = obj + 0x1c` into
registers (`add edi,0x18` / `lea ecx,[esi+0x1c]`) while MSVC6 folds the
arithmetic into the addressing modes (~6 orderings/pointer forms did not
move it). Finding: the reference's redundant `*(char*)(obj+0x22) =
payload[6]` then `*(char*)(obj+0x22) = 0` survives dead-store elimination
only when written via DISTINCT pointer expressions (`dst+6` vs `obj+0x22`).
The `type * 0x264264` table index reproduces via the reference's exact
lea chain (`shl`-based ×0x11011, `lea [eax+eax*8]` ×9, ModRM ×4 scale).

## cm_ExClearLagerslot (0x1000e690) — blocked (param-in-esi allocation + prove explosion)

Storage-slot clear; C preserved as a comment in cm_ExClearLagerslot.c (best
28/191; the Ghidra decomp at the top matches the asm). Blocked on: the
reference keeps the ORIGINAL cmd in esi across the GetField/Resolve calls
(`mov esi,[esp+8]` in the prologue; `mov [esi+0x10],eax` field store;
`mov dx,[esi+0x14]` word reads) while MSVC6 reloads the param slot after
each call — ~8 C forms (msg/line variables, duplicated log calls for the
tail-merge, psVar1/c original copies, Ghidra short* arithmetic) could not
force the esi allocation. Also `rebrew prove` state-explodes on the
gm_ResolveEntityById path (like cm_ExChangeBits) so the #else fence cannot
be used — remains plain naked. Note the resolve-heavy functions
(cm_* with gm_ResolveEntityById) are systematically unprovable by the
current symbolic engine; the fence+PROVEN pattern only works for
resolve-free functions.

## m_PoolFree (0x10006e30) — blocked (pool register role + block order)

Block return to the pool free list; C preserved as a comment in m_alloc2.c
(best 23/137 with /O2 — size matches). Blocked on: MSVC6 keeps the pool
pointer in esi (callee-saved) and places the fatal block between the checks
and the main body, while the reference uses edx (the value dies before the
m_FreeTracked calls) with the fatal after the main. /O1 swaps the register
(pool in edx ✓) but changes the encodings (`andl $0,mem` / `decl mem` vs the
reference's `mov [mem],0` + load-dec-store) and the walk's back-edge shape.
`rebrew prove` state-explodes on the walk loop → no fence. The decode:
slot = pool-1, node = *slot, bounds (node+0x10 .. node+0x10+size*max,
unsigned jb/jae), *slot = 0, count--, and when empty unlink from *pool
(head case or prev->next walk) + m_FreeTracked; fatal =
ReportFatalError(0x10028888, 0x279, 0x10028b94).

## ShutdownMemoryAllocator (0x10006c00) — blocked (buffer layout + prove explosion)

Memory-allocator teardown; C preserved in /tmp/sma.c (best 96/283). Blocked
on the four sprintf/ReportMessage/log buffer offsets: the reference lays
them at [esp+0xc]/[esp+0x18]/[esp+0x1c]/[esp+0x24], while MSVC6 16-aligns
or overlaps them (single 0x400 buffer → scattered bases; separate
b3[0xc]/b4[4]/b1[8]/b2[0x3dc] → b1@0x1c + b4@0x18 match but b3 overlaps b4
and b2 lands at 0x38). `rebrew prove` explodes on the array/list loops →
no fence; remains plain naked. Note the recurring file-edit hazard: the
#else-fence revert pattern truncates everything after the fence — always
re-check the build after reverting (this cost two restore cycles).

## gm_RandomStatModifier (0x10018450) — blocked (char value representation)

Random stat modifier; C preserved in /tmp/grsm.c (best 29/78). Blocked on
MSVC6's char-value representation: the reference loads the char param as a
BYTE (`mov bl,[esp+8]`), reloads the param slot for the fild zero-extension
(`mov eax,[esp+8]; and eax,0xff`), and does the sums in byte registers
(`add al,0x15`; `add bl,al; mov al,bl`); MSVC6 loads the dword and sums in
eax/ebx regardless of the cast form. `rebrew prove` additionally flags a
char-sign EAX difference (4294967040 vs 0) → no fence; remains plain naked.
The Ghidra reference (in the file) matches the decode exactly.

## CloseVfsStream (0x10008d10) — blocked (return-block layout + STUB class)

VFS stream close; C preserved in /tmp/cvs.c (best ~62/301 with /O2; the
byte-loop crc/size writes, the unsigned `>= 8` bounds (cast to unsigned, or
`jb` appears instead of `jl`), the flags reload for the final check (read
the memory, not a register copy — else an extra `push ebx` appears), and the
flags-in-al register all match). Blocked on: the reference places the
stream==0 return at the END (`je 0x128` long jump, `mov eax,ebp`) while
MSVC6 inlines it (`jne` short, `xor eax`); `return result` still folds to
xor. The diff ratio classifies as STUB, which `rebrew prove` rejects →
no fence. Also note: the STUB/SIZE_MISMATCH/NEAR_MATCHING class comes from
the byte-diff ratio, and prove only accepts the latter two.

## ahm_InitRandomEntity (0x1000c600) — DONE (RELOC 109/109)

Random alchemy-entity initializer; converted to C, RELOC 109/109. Findings:
- **The scan-loop tail order (`dec count; inc idx; and; test; jne`) requires a
  WHILE loop with `count--; idx = (idx+1)&0x1f;` in that order in the body**
  — the equivalent for-loop (`for (count=0x20; count; count--)`) emits
  `inc/and` before `dec`, and a do-while PEELS the first iteration.
- **The float-store scheduling (`fstp [eax]` before `add eax,0xc`) needs an
  explicit `(float)` cast on the store** — `((float*)p)[0] = (float)(*(p-1)
  * dScaleFactor)` (double multiply via `fmul qword`, single store) vs the
  uncast form which defers the fstp after the pointer add.
- The `idx*244` lea chain (`idx*3 → *15 → idx*61` then `shl 2`) and the
  `[ecx*4 + base]` marker check reproduce from plain `idx * 244` arithmetic.

## sim_StartEntityQueryByType (0x10015460) — blocked (arg/table register roles)

Type-dispatched entity query; C preserved as a comment in sim.c (best
10/145 — the size matches; the register roles shift everything). The
reference keeps arg1 in esi and the entity-type table in edi (both
callee-saved, restored per branch epilogue); MSVC6 allocates edx/esi
instead. The `type * 0x24d` (589) record index reproduces via the reference's
lea chain (×3 → shl 4 → +type → ×3 → ModRM ×4). `rebrew prove` rejects the
STUB-class ratio → no fence.

## amt_UpdateEntityLinks (0x1000ba30) — blocked (ebp dual-role allocation)

Office-entity link fixup; C preserved as a comment in aemter2.c (best
~49/179). The reference keeps arg1 in ebp at the start (for the `[ebp+4]`
field reads) and REASSIGNS ebp = arg2 inside loop1 (for the later
`[ebp+0x168]` uses), checking the arg2 condition directly against the param
slot; MSVC6 hoists arg2 into ebp from the start and adds an extra
callee-saved edi. ~5 forms (rec-based vs eax-style loop pointers, arg1+4 vs
arg2+4 in the field compare, byte vs dword `+3`) did not move it. The
`(def > 0xb) + 3` (seta; add) and the two-loop structure decode cleanly.

## gm_FindEntityByOwner (0x10019c60) — blocked (loop register roles)

Owner lookup; C preserved as a comment in spiel622.c (best 13/98). The
reference keeps arg1 in edi, the loop pointer in ecx, the counter in esi
and inlines the arg1==0 return-0; MSVC6 allocates esi/eax/edx with the
return at the end. The owner/type checks and the `i * 0x21c` lea-chain
return decode cleanly.

## cm_ExChangeDesire (0x1000e9c0) — blocked (cmd-in-edi role)

Desire-stat update; C preserved as a comment in cm_ExChangeDesire.c (best
37/214 — the size matches). The reference keeps cmd in edi (callee-saved)
with the loop counter in ebx; MSVC6 reloads the param slot. Interesting
decode: the clamp is the ternary `*slot = (*slot >= _g_stat_max_d) ?
_g_stat_min_d : _g_stat_max_d;` — the reference's redundant middle
slot-vs-min check is the compiler's ternary expansion.

## cm_ExSetAttribute (0x1000e8d0) — blocked (cmd-in-ebp role)

Attribute-set handler; C preserved in cm_ExSetAttribute.c + /tmp/cxsa.c
(best 15/243). The reference keeps cmd in ebp across the
GetField/Resolve calls; MSVC6 reloads the param slot and schedules the
resolve arg pushes differently. The descriptor decode is clean: signed
size/count bytes + 16-bit offset, three size-dispatched copy loops
(1/2/4 bytes) with the `movsx`+`jbe`/dec-jne pattern.

## cm_ExRemoveLinkedObject (0x1000f0d0) — blocked (result/cmd register roles)

Linked-node removal; C preserved in cm_ExRemoveLinkedObject.c + /tmp/cxrlo.c
(best 22/197). The reference keeps result in edi and the original cmd in esi
across the resolve/query calls (with the resolve's 2nd out writing into the
result param slot); MSVC6 keeps both in volatile registers. The decode is
clean: pre-mark `*result = 2`, the resolve with the result-slot out, the
three removal paths (cmd+0x5d direct, q+0x14 query, local0+0x178,
result+0x14) with the -2/-1/0/eax return conventions.

## cm_ExChangeAttribute (0x1000e7d0) — blocked (cmd-in-ebp / dst-in-edi roles)

Attribute accumulator (the `*dst += src` sibling of cm_ExSetAttribute); C
preserved in cm_ExChangeAttribute.c + /tmp/cxca.c (best 18/261). Same
blocker class: the reference keeps the original cmd in ebp and dst_base in
edi across the descriptor loop; MSVC6 reloads the param slots. The Ghidra
reference at the top of the file matches the decode exactly.

---

## Session findings — five more conversions + two register-role blockers

### Converted to byte-identical C (all RELOC, verified via `rebrew verify` 245/245, build hash c7ac331f)

**FindAndMatchParents (0x100151e0, 535B)** — `gm_RandomMod` parent scan.
- The loop values are `unsigned short`: the compares compile to 16-bit
  `cmp bp/si, 0xffff` and the return-0 epilogue to `xor ax,ax` — the return
  type is `unsigned short` (the whole-register `mov ebp,eax` after the call
  leaves garbage in bits 16-31; only the low half is meaningful).
- `(range * 3) / 4` is SIGNED division: `lea;cdq;and edx,3;add;sar` — writing
  `>> 2` produces a plain `sar` (3 bytes shorter, mismatches).
- The three check-fails share one `mov ebp,0xffff` tail block. MSVC6 only
  produces the shared tail when the checks are an `else if` chain ending in
  `goto done1; continue;` — a plain `goto fail1` label anywhere else gets
  placed mid-loop (after the last check) and inverts the final test.

**cm_ChkChangeAttribute (0x1000cde0, 331B)** — descriptor walker.
- Declaring `kind`/`n` as `signed char` makes MSVC6 allocate BYTE registers
  (`mov cl/bl`) and spill the call-crossing one to the freed param slot;
  declaring them `int` forces `movsx ebx/edi` (full registers, no spill).
- The switch cases are **1, 2, 4**, not 1,2,3: MSVC6's dense-switch test
  chain is `dec;je;dec;je;sub eax,2;jne default` (kind==3 would hit the
  default; the `p += 4*n` arm is case 4).
- `p++; p++` with a load between them (`n = *p` after the first increment)
  survives as `inc esi; inc esi` — adjacent increments merge into `add esi,2`.
- The record-sum expression needs a temp variable (`s = a + b; call(s)`) to
  get `mov eax,[esi]; mov edx,[ecx]; add eax,edx; push eax` instead of an
  edx-first load order.

**cm_ChkJoinLeaveElection (0x1000d110, 333B) / cm_ExJoinLeaveElection
(0x1000fd50, 445B)** — election validation/execution.
- `do { if (c) return 1; i++; } while (i < 4)` PEELS the first iteration
  (extra `mov edx,[q+0x1c]; lea edi,...` + a jge/jne loop reshape). The plain
  `for (i = 0; i < 4; i++)` with `break` + `if (i >= 4) return 1; return 0;`
  compiles to the reference's bottom-tested walk (`cmp [p],x; je; inc; add
  p,4; cmp i,4; jl`) with the loop-complete falling into the shared fail.
- `if (c) return 1; return 0;` (adjacent returns) triggers MSVC6's boolean
  idiom: `xor eax,eax; cmp; setge al` — 2 bytes longer and different layout
  from the reference's `cmp; jge shared_fail; xor eax,eax; ret`. Only the
  break+post-check shape (where the loop-complete path falls into `return 1`)
  avoids the idiom.
- In the Ex variant, writing the slot as `*(int*)(q+0x1c+i*4) =
  *(int*)(cmd+0x14)` (re-reading cmd+0x14 at the write) instead of a cached
  `player` variable lets the allocator reuse the register for the scan value
  and reload cmd+0x14 — matching the reference byte-for-byte.
- The cler branch returns the INVERTED boolean: `result == 0` compiles to
  `neg eax; sbb eax,eax; inc eax`, while `!= 0` gives `neg;sbb;neg`. Both are
  valid 0/1 booleanizations; MSVC6 picks `inc` for `== 0` and `neg` for
  `!= 0` on call results (pointer comparisons give `neg;sbb;neg`).

**cm_ChkSellObjekt (0x1000cbd0, 517B)** — two-phase sell validation.
- The `w == 0xffff ? 0 : rec` ternary inverts to `jne` with the rec-chain
  inline; the reference has `je` with the zero inline — write
  `if (w != 0xffff) { p = rec; } else { p = 0; }` (the reference's then-arm
  is the rec computation).
- `gm_QueryEntitySum` takes a raw `char` second param: the reference pushes
  `mov dl, byte[...]` with garbage upper bits. The project-wide `(int, int)`
  declaration would sign-extend; use the cast idiom
  `((int (__cdecl *)(int, unsigned char)) gm_QueryEntitySum)(...)`.

### Blocked (documented with preserved C, see file comments)

**lb_SendLobbyConfig (0x100146c0) — CONVERTED 236/236 RELOC** (was 225/236).
The reference loads `*player` flags into eax and keeps it there across the
value_ok path, doing `test ah,0x60`, `or/and ah,8`, `mov [esi],eax`; the
former C (with a `flags` local) made MSVC6 put the flags value in ecx and
the short-lived msg+0x18 value in eax.  **The fix: drop the `flags` local
entirely and read/write `*player` directly** (`if ((*player & 0x6000) != 0)
...; *player |= 0x800 / *player &= ~0x800;`).  The optimizer CSEs the two
`*player` reads into one value either way, but a *named* local is a distinct
IR node created at the assignment statement, while the anonymous CSE'd
load is created at its first use — and that creation point changes the
value's position in the allocator's priority list, flipping eax↔ecx (see
Finding 12 for the allocator-internal mechanism).  ~50 other formulations
(declaration order, signed/unsigned, `v` temp placement, `if (v != 0)`
polarity, ternary forms, goto structure, removing the `result` local, all
/O-flag axes) did not move it; removing the *flags* local did.

**cm_ExAllocClientSpieler (0x1000d570) — 142/361 (result-register role).**
The reference keeps `result` in ebx (loaded at the `result ? 6 : 7` arg
computation, with the pending srand arg shifting esp so `[esp+0x18]` is the
arg2 slot) and cmd in edi, with rec pushed into ebp only at L_ok; MSVC6
allocates result→ebp and cmd→esi, and the arg-load scheduling diverges.
Flag sweep (/O2 /G5 /G6 /Og /Gy) and the GA matcher (10-min timeout, no
improvement) did not help. The `g_static_entity_table_358a0` symbol form
(over the 0x100358a0 literal) gained 4 matches; the rest is the register
roles.

**ls_LoadEntities (0x10013230) — 2239/2268 (frame layout).** The C in the
fence's #else is structurally byte-identical (the body matches instruction
for instruction; 89 relocs) except for the frame: the reference keeps
`sub esp, 0xc` (3 dwords: record_count, i, id) and REUSES the ctx arg slot
(`lea ecx,[esp+0x28]` with two args pushed) for header_field; MSVC6
allocates a 4th frame dword (`sub esp, 0x10`), shifting every [esp+N]
operand by 4. ~14 formulations (declaration orders, for/while loop forms,
merging id/rec_id, removing the slot_ext_ptr variable) could not shrink the
frame; the arg-slot reuse for a late address-taken local is a GRA slot-
allocation decision that resisted steering.

**gm_StartFilteredEntitySearch (0x100170e0) — 241/296 (setup register/CSE).**
The fence's #else C is complete and matches from the switch dispatch onward;
the divergence is the 9-global setup block.  The reference parks the zero in
`edx` (`xor edx,edx` reused for the null-check `cmp` and the three zero
stores) and CSEs the repeated `0xff` byte constants into `cl` (one hoisted
`mov cl,0xff`, two `mov [addr],cl` stores), emitting the stores in source
order.  MSVC6 picks `ecx` for the zero, emits per-store immediates
(`c6 05 addr,0xff`), and schedules the extra5 byte store ahead of the
extra2/extra3 word stores.  Cast removal, statement reordering, and the
/O1 /Ox /Og /Oy sweep did not change it.

**gm_Open (0x10015950) — 732/861 (pointer-base + register roles).** The
fence's #else C is a full reconstruction; two regions diverge. (1) The
player-slot init loop: the reference bases dst_player_ptr at dst[0]
(`lea edi,[eax+0xc]` for the memcpy, stores at [eax-4]/[eax]/[eax+4]/
[eax+8]) while MSVC6 normalizes the base to dst[1] (stores at
[eax-8]/[eax-4]/[eax]/[eax+4], `lea edi,[eax+8]`) — the [-1] index in the
source drives the base normalization. (2) The producible-count tail loop:
the reference walks the entity table in esi with the g_item_def_table base
in ebp and keeps producible_count/slot_counter on the stack; MSVC6's
register roles and the `+= producible_count` addressing
(`[esi+eax-0x22c]` vs a plain store) differ. Semantics match throughout.

**GetCommandPayloadSize (0x1000c710) — 494/752 (switch preamble + case split).**
The fence's #else C is a partial reconstruction of the 103-case payload-size
switch.  Two blockers: (1) the switch preamble — the reference emits
`mov dl,[eax]; mov ecx,edx; and ecx,0xff; add ecx,-3; cmp ecx,0x66; ja;
jmp [ecx*4+0x1000c864]` (10-byte index prep that keeps the byte in dl for a
later `cmp dl,0x16`), MSVC6 emits `xor ecx,ecx; mov cl,[eax]` (4 bytes) and
folds the `(*cmd_payload == 0x16 ? 0x15 : 0x15)` ternary away — the 6-byte
delta shifts every subsequent case body; (2) case 0x16's entry-count loop is
misplaced in the reconstruction (the reference has the loop inline in case
0x16; the C sets cursor/total and breaks, with the loop in a different
case).  Switch-expression casts (`unsigned char`, `(int)`, `& 0xff`,
explicit variable) and the /O1 /Ox /Og sweep did not change the preamble.

---

## Deep-dive: the unsigned-char zero-extension form (and-idiom) — resolved

The rebrew codegen docs (`docs/codegen/msvc/msvc-6.md`) claim the /O2
unsigned-char form is `and eax,0xff` (`25 ff 00 00 00` / `81 e1 ff 00 00 00`)
— the 5.0/6.0 marker.  The GetCommandPayloadSize (0x1000c710) target shows
exactly this in its switch preamble, yet every probe of a bare byte load
produced `xor reg,reg; mov reg_low,[mem]`, and the file's own investigation
comment claimed no available MSVC build reproduces the and-idiom.  The
deep-dive resolved the contradiction — the form is selected by **whether the
byte value stays live after the load**:

### The three forms and when each appears

| Context | Codegen | Notes |
|---|---|---|
| unsigned char PARAMETER (32-bit stack slot, garbage high bits) | `mov eax,[esp+4]; and eax,0xff` | always masked — the slot's upper bits are unknown |
| byte from pointer-deref, value DEAD after | `xor reg,reg; mov reg_low,[mem]` | the "clean" zero-extend |
| byte from pointer-deref, value LIVE after (used later) | `mov reg_low,[mem]; mov reg2,reg; and reg2,0xff` | byte kept in a byte register, masked copy for the consuming op |

Probes (docker msvc6 12.00.8168, /O2):
- `uc_add(unsigned char a, unsigned char b) { return a+b; }` →
  `mov eax,[esp+4]; mov ecx,[esp+8]; and eax,0xff; and ecx,0xff; add eax,ecx`
  (the docs' claim — param values).
- `switch (*p) { ... }` with the byte dead → `xor ecx,ecx; mov cl,[eax]`.
- `switch (*p)` where a case uses `*p` again (e.g. `return (*p==0x16) ? total : total;`)
  → `mov al,[eax]; and eax,0xff` — the and-form, byte kept in al.

### The liveness lever (what keeps the byte live)

The fold of `(cond ? CONST : CONST)` with equal constant arms REMOVES the
comparison and kills the byte's liveness → xor-form.  A ternary with
VARIABLE or POINTER arms does NOT fold (MSVC6 evaluates the condition, then
selects) → byte stays live → and-form.  For GetCommandPayloadSize the
decisive change was the cursor expression:

```c
/* before — folds, byte dead, xor-form preamble (494/752): */
cursor = cmd_payload + (*cmd_payload == 0x16 ? 0x15 : 0x15);
/* after — byte live, and-form preamble (623/760): */
cursor = (*cmd_payload == 0x16) ? (cmd_payload + 0x15) : (cmd_payload + 0x15);
```

This raised GetCommandPayloadSize from 494 to 623 matches and produced the
target's exact preamble shape (`mov reg_low,[eax]; mov reg2,reg; and
reg2,0xff; add reg2,-3; cmp reg2,0x66; ja; jmp [reg2*4+table]`) — the
previous "needs the original's exact CL.EXE build" conclusion in the file
header is OUTDATED; the remaining delta is the register roles (target keeps
the byte in dl and the index in ecx; MSVC6 picks cl/edx) and the case-0x20
negation idiom (below).

### Related: `-(x != c)` negation idiom

The target's case 0x20 (`(-(cmd_payload[0x10] != 0xe) & 0x7c) + 0x11`)
compiles to `sub al,0xe; neg al; sbb eax,eax; and eax,0x7c; add eax,0x11`
(the fused compare-and-negate producing -1/0).  MSVC6's alternative is
`cmp cl,0xe; setne dl; neg edx; and edx,0x7c; add edx,0x11` (setne then
negate) — 7 bytes larger.  The choice follows the same register-role/
context rule; `0 - (x != c)` and `x == c ? 0 : -1` forms were tested and did
not flip it.

### Refines the CODEGEN_PATTERNS.md "NOT controllable" row

`CODEGEN_PATTERNS.md` lists "Byte param zero-extend: `mov dl,[reg+off]` vs
`xor edx,edx; mov dl,[reg+off]` — compiler decides based on register
liveness — NOT controllable from C; accept as NEAR_MATCHING blocker".  The
liveness IS controllable via the fold lever above: a byte value kept live
across the switch (variable/pointer-arm ternary, or any later use of the
value) forces the and-form.  The remaining register-role choice (dl vs cl
for the kept byte) is still not steerable.

## Deep-dive: the rebrew flag-sweep tiers (never fully swept)

The earlier sweeps tried only the /O and /G axes by hand (~6 combos).
`rebrew match --flag-sweep-only` exposes the full tiered grid
(`docs/FLAG_SWEEP_TIERS.md`): quick 192, targeted 1,152 (default), normal
5,376, thorough ~86k sampled, full ~100k sampled.  The axes include
`/Ob0..2` (inlining), `/ML /MT /MD /MLd /MTd /MDd` (runtime library),
`/Zp1..16` (alignment), `/GX` (EH), `/Gs` (stack checking), `/GZ` (debug
checks), `/GR` (RTTI), `/TP` (C++ mode).  A targeted-tier run on the
GetCommandPayloadSize reconstruction produced no improvement (the register
roles are not flag-selectable); the run confirmed the register-role blockers
are structural, not flag-fixable.

### GetCommandPayloadSize follow-up: 494 → 742 (three more levers found)

Continuing from the and-idiom resolution, three further levers took the
reconstruction from 623 to 742/752 (sizes match):

1. **Case body ORDER is the original source order, not numeric.**  The
   generated case bodies follow the switch's source order.  The Ghidra
   reconstruction had the cases grouped non-numerically (the 0xd-group
   returning 0x18 placed early; the `default` in the middle), producing a
   different body layout.  Reordering the switch to the target's exact
   generated order (read from the jump-table targets:
   `{3,...}→0x1c, {4}→0x11, {8,...}→0x14, {0xa}→0x50, {0xb}→0x2a,
   {0xc}→0x49, {0xf,0x2c}→0x21, {0x11,0x3d}→0x27, {0x12,0x1e}→0x1e,
   {0x14}→0x16, {0x15}→0x39, {0x16,0x17}→loop, {0x18}→computed,
   {0x19,0x53}→0x24, {0x1b,0x64}→0x28, {0x1d}→0x5f, {0x20}→code,
   {0x22}→0x3d, {0xd,...}→0x18, ...`) aligned the bodies (644 → 742).

2. **The `-(x != c)` negation idiom.**  `-(x != 0xe)` compiles to
   `cmp cl,0xe; setne al; neg eax` (setne form); `(x != c ? -1 : 0)` (or
   `(x == c ? 0 : -1)`) compiles to `sub al,0xe; neg al; sbb eax,eax` —
   the target's form.  The setne variant is 7 bytes larger; switching the
   case-0x20 expression to the ternary-? -1 : 0 form removed the size
   excess (760 → 752) and added matches (623 → 644).

3. **Register roles remain** (byte dl vs cl, index ecx vs edx, count cl vs
   dl) — the last 10 bytes.  Declaration order of the four locals, an
   explicit `unsigned char sw` switch-value variable (which regressed to
   599), and the flag sweep (targeted tier) did not move them.

### Register-role residue confirmed for GetCommandPayloadSize (742/752)

The final 10 bytes are exclusively register-role encodings in the switch
preamble and the case-0x16 count setup: the reference uses `dl` for the
kept switch byte (`8a 10`), `ecx` for the masked index (`8b ca; 81 e1 ff 00
00 00; 83 c1 fd; 83 f9 66; ff 24 8d`) and `cl` for the loop count; MSVC6
picks `cl`/`edx`/`dl`.  Levers tried and rejected: four declaration orders,
an explicit `unsigned char sw` switch-value variable (regressed 742→599),
hoisting `count = cmd_payload[0x14]` before the switch (regressed →461),
count types `unsigned char`/`short` (regressed), and the targeted-tier flag
sweep.  The `rebrew diff -r` register-aware path crashes (Capstone
CS_ERR_DETAIL) so the residue cannot be machine-normalized either.

## Finding 12 — named local vs anonymous CSE'd load (the eax↔ecx lever)

**Rule:** for a value loaded from memory once and reused across a branchy
fall-through, whether MSVC6 gives it eax or ecx can depend on whether the C
source names it as a local variable or reads the memory location directly.

- **Named local** (`flags = *player; ... *player = flags;`): the value is a
  distinct IR node created at the assignment.  In the lb_SendLobbyConfig
  shape it landed **ecx** (short-lived msg+0x18 value took eax).
- **Direct memory** (`if ((*player & 0x6000) != 0) ...; *player |= 0x800;`):
  the optimizer CSEs the two reads into one anonymous value created at its
  first use — it landed **eax**, byte-matching the original binary.

The final code is *identical* modulo the register roles, so this is purely
an allocator input-ordering effect, not a codegen difference.

### Allocator internals (from reversing c2.dll, p2 backend)

The register allocator is a priority-based graph-coloring pass in c2.dll,
source `P2\color.c` (`E:\8168\vc98\p2\src\P2\color.c` in the string table):

- **Priority computation** (FUN_1071431d @ 0x1071431d): per use,
  `node+0x3c += use_weight × loop_weight`.  `node+0x18` accumulates the
  plain use count, `node+0x24` the def count.  `loop_weight` is `1` by
  default, or `1 << depth` when optimizing for speed (`DAT_107ac0b0`).
- **Use weights** (FUN_10714c76/10714eeb/10714c90): default **6** per use;
  class 3/4/5/6 (ebx/esp/ebp/esi) operands ≈ 3; the special register class
  `0xd` ('\r') gets 2/3/5 depending on the referencing instruction.  So a
  `test`/`or`/`and`/`cmp`/store chain of 3 uses ≈ priority 18 each.
- **Priority list** (FUN_10717220/10717260): nodes sorted **ascending** by
  `node+0x3c` (head = lowest priority); class-0xd nodes are always appended
  at the tail (highest priority slot); equal-priority inserts go **before**
  the equal group (reverse insertion order).  The simplify driver
  (FUN_1071700b) consumes the head (lowest) first; nodes with priority < 1
  go down the cheap-spill path.
- **Node layout** (from the use/def loops): +0x14 prev, +0x18 next,
  +0x1c id, +0x28..+0x30 neighbor lists, +0x3c priority, +0x40 order
  number, +4 register class of the referencing instruction.

**Practical consequence:** when two memory-derived values have equal
weighted priority (the common 3-use case), the register they receive is
decided by their relative creation order in the value table — which the C
source can steer by choosing *which* memory reads are named locals and
which are left as implicit CSE'd loads.  If a register role won't budge,
try deleting the local and writing the memory operand directly (or vice
versa), then re-test.

## Finding 13 — lb_ExPlayerlist (0x100145e0): struct-fields beat array-index counters

Converted 209/209 RELOC with two extra rules on top of Finding 12:

1. **Statement order drives load placement.**  The target loads `*player`
   into eax *immediately* after the prologue (before zeroing the local
   array).  The C must therefore put the `if ((*player & 0x6000) != 0)`
   check **before** the `memset`/count-init statements — putting the
   zeroing first moved the flags load after the `rep stosd` and shifted
   every byte.  (This is the same "value created at first use" effect as
   Finding 12: the memory-load value is born at the check, which is where
   the reference wants it.)

2. **A plain `int list[9]` with `list[++list[0]]` gets scalarized.**  The
   optimizer recognizes `list[0]` is only ever used as a counter, extracts
   it into its own frame slot, and shrinks the zeroed array to 8 dwords —
   so the `rep stosd` count, the index arithmetic and the final `rep movsd`
   source all shift.  Wrapping the array in a struct
   (`typedef struct { int count; int ids[8]; } PlayerList9;`) makes the
   counter a *field*: struct fields are never scalarized, `memset(&list,
   0, 36)` stays `mov ecx,9; rep stosd`, and the trailing
   `memcpy(msg+0x14, &list, 36)` copies count+ids as the reference does.

Both rules are the same underlying lever as Finding 12: **what the
optimizer/allocator sees is not the C statements but the value graph, and
anonymous loads, statement order, and struct-field access all change that
graph's shape.**

## Finding 14 — AH-relative masks (read the byte before the mask)

`lb_BroadcastStateChange (0x10014a50) — 157/157 RELOC` and its lobby
siblings use `test ah,0x60` / `or ah,0x30` / `test ah,0x4` on the
`*player` flags.  The `ah` prefix means the mask must be read **8 bits
high**: `test ah,0x60` = `*player & 0x6000`, `or ah,0x30` = `|= 0x3000`,
`test ah,0x4` = `& 0x400`.  Writing the literal low-byte masks (`0x30`,
`4`) made the compiler emit the AL forms (`or al,0x30`, `mov al,[esi];
test al,4`) — a 2-byte size regression and shifted bytes.  Once the masks
were shifted to the AH-relative values the function matched 157/157 on
the first try with the Finding-12 direct-memory style (`*player` reads,
no `flags` local).

General rule: **when a flag value's tests appear as `test ah/…` in the
reference, every constant in the byte-ops must be `(value << 8)`** — the
compiler commits the value to the AH byte-slot and will not mix AL and AH
ops on the same value.

## Finding 15 — COMDAT placement: functions in a file must be VA-contiguous

Each ``.c`` file compiles to one object whose functions the linker places as a
contiguous run (each function padded to 0x10 alignment) starting at the file's
first ``// FUNCTION:`` VA.  Consequences:

- **A contiguous VA run cannot be split across files.**  Moving one function
  (e.g. lb_HandleEntitySync 0x10014bf0) into its own ``.c`` reorders the
  object layout: the remaining functions shift onto the vacated VAs and the
  whole .text after that point drifts.  Keep functions that are VA-adjacent
  (gap == padded size of the predecessor) in the same file.
- **Uncovered holes must be occupied.**  The original may have functions the
  project has not reversed (e.g. 0x10014ee0 between lb_ExLobbyServerCommand
  and plant.c's find_zone_record).  A naked ``_emit`` placeholder for the hole
  must stay in the file (in VA order) or every later function shifts.
- Duplicate VA coverage across files (e.g. defining 0x10014f80 in two files)
  breaks the layout silently — check ``// FUNCTION:`` markers before adding.

### 0x10014ee0 — word-table search (naked placeholder kept)

The 80-byte helper searches a word table at 0x1002d878 (0x46-byte records,
word id at offset 0) and returns ``table + i*0x46``.  The C conversion is
blocked on two codegen patterns the optimizer will not reproduce:

1. **Dword-first / word-rest loads.**  The reference loads the first record
   id with ``mov eax,[0x1002d878]`` (a1 — DWORD) and the loop ids with
   ``mov ax,[ecx+0x46]`` (WORD), masking with ``and eax,0xffff`` at the loop
   top.  Every C formulation (word-typed v, dword-typed v, explicit casts,
   do-while/for shapes) yields either a word first-load (``66 a1``) or a
   ``xor eax,eax`` zero-extend instead of the mask-at-loop-top form.
2. **Induction-variable setup.**  The reference keeps the scan pointer at
   0x1002d878 and loads ``[ecx+0x46]``; the compiler instead folds the first
   stride into the pointer (``mov ecx,0x1002d8be``) and loads ``[ecx]``.

Kept as the fenced-naked placeholder (byte-identical, EXACT 69/69) — see the
"tiny asm" allowance.  The same two patterns are worth checking in other
table-search helpers before attempting C.

## Finding 16 — three new blocker patterns (cm_* family)

- **cm_ExChangeFloat (0x1000eb70) / cm_ChkMoveCredits (0x1000cb20) — prologue
  scheduling.**  The reference's prologue is `sub esp,8; push esi; mov
  esi,[esp+0x10]` — the frame is set up and the param loaded *into esi*
  (callee-saved) only after the `push esi`.  Every C formulation (with/without
  an iVar1 alias, pointer-typed, indexed stores, `&param` in the
  gm_ResolveEntityById call) makes MSVC6 hoist a *volatile* load
  (`mov eax,[esp+4]`) before the frame setup and materialize `cmd+0x10` into a
  second callee-saved register.  The flag sweep cannot help: `rebrew match
  --flag-sweep-only` crashes on the Capstone CS_ERR_DETAIL bug (same as
  `rebrew diff -r`).  Kept fenced-naked.

- **cm_ExModifyStat (0x100100a0) — FPU re-compare.**  The reference clamps a
  float with a convoluted FPU sequence that *re-compares* `_g_stat_max` at the
  join (`fcom max; test ah,1; je L_chk_max; fcom min; test ah,0x41; jne
  USE_MIN; L_chk_max: fcom max; test ah,1; jne USE_X; …`).  All five C shapes
  (simple clamps, nested ifs, empty else, `else if (x >= max)`) make MSVC6
  reuse the first compare's flags instead of re-comparing.  The FPU flag
  decode (`test ah,1` = C0 = ST0<op; `test ah,0x41` = C0|C3 = ST0<=op) is
  standard, but the block layout is not reproducible from C.  Kept
  fenced-naked.

- **cm_GetBuildingStatCount (0x100104a0) — arg-register + zero-extend order.**
  The reference's prologue is `mov edx,[esp+4]; xor ecx,ecx; push ebx; push
  esi; mov cl,[edx]` — the arg lands in edx and the byte index is
  zero-extended by clearing ecx *before* the `mov cl` load, all before the
  callee-saved pushes.  Every C shape puts the arg in eax and emits the
  byte load without the pre-clear (later movzx/mask), and the if/else
  result chains compile to branchless `dec/neg/sbb/and/add` selects instead
  of the reference's explicit `mov eax,imm; cmp; jne` branches.  The
  zero-extend-timing and select-vs-branch choices are both allocator
  liveness decisions (see Finding 12's mechanism).  Kept fenced-naked.

- **gm_FindEntityByOwner (0x10019c60) — callee-saved pair order.**  The
  reference keeps `owner` in edi and the loop counter in esi (`push edi;
  mov edi,[esp+8]; xor eax,eax; test edi,edi; jne L_search; [inline return
  0]; L_search: push esi; xor esi,esi`).  Every C shape (for/do-while,
  result-variable init, signed/unsigned casts) puts `owner` in esi and the
  counter in a volatile register — one callee-saved fewer, and the
  `owner==0` return becomes a jump-to-tail instead of the reference's inline
  fall-through.  Kept fenced-naked.

- **cm_ExClearLagerslot (0x1000e690) — address-taken param value-copy.**
  The reference passes `&cmd` (the param slot) to gm_ResolveEntityById yet
  keeps a callee-saved *value* copy (esi) for the pre-resolve uses — simple
  `push esi; mov esi,[esp+8]` prologue.  Any C with `&cmd` makes MSVC6 treat
  the param as memory-only: it hoists a volatile load to offset 0, drops the
  esi copy, and reloads the slot after the resolve.  Passing a *different*
  param's address (&result) keeps the simple prologue but the arg order then
  mismatches the reference (the resolve genuinely targets the cmd slot).
  Kept fenced-naked.

## Finding 17 — signed `-1` byte compares materialize 0xff via `or reg,0xff`

`AnalyzeInstruction (0x10003260) — EXACT 183/183`.  The reference compares
bytes against 0xff by keeping the constant in `bl` and materializing it as
`or bl,0xff` (80 cb ff) *before* the length check of the block that first
uses it.  Writing the compares as `== -1` against `*(char*)` (signed) makes
MSVC6 emit exactly this `or bl,0xff` + hoisted placement; writing `== 0xff`
against `*(unsigned char*)` emits `mov bl,0xff` (2B) *after* the length
check instead.  The split `if (len>=2 && p[-2]==-1 && p[-1]<0x40) return 2;
if (len>=2 && p[-2]==-1 && (p[-1]&0xf8)==0xd0) return 2;` (two separate
ifs) also reproduces the reference's `cl` load + redundant re-compare at
the second block — a single `||` condition merges the return-2 paths and
loses the re-check.

## Finding 18 — memory-operand byte params: local vs global load form

`ShutdownLogAndErrorHandler (0x100034c0) — RELOC 83/83`.  Passing a
*global* (`g_log_mode_flags`) to a callee whose param is declared
`unsigned char` makes MSVC6 load only the byte (`mov cl,[mem]`, 3B);
passing a *local* makes it push the full register (no truncation).  The
reference loads the full dword (`mov ecx,[mem]`) from the global in *both*
callers — so the original declaration was `int`.  The rebrew declaration
was `unsigned char`, which the other caller (ReportFatalError) matched
only because its explicit `(unsigned char)` cast then became a no-op.
**Fixing both**: declare the callee param `int` AND drop the caller's
byte cast (the reference passes the untruncated value) — both call sites
then byte-match.  (Also: `__declspec(dllimport)` on FreeConsole is needed
to get the reference's `call dword ptr [__imp__FreeConsole]` IAT form
instead of a direct `call`.)

## Finding 19 — InitPacketPool (0x100068e0): memset alignment-pass + param-slot spill

The reference memsets the pool with the *alignment-aware* inline form
(`lea ecx,[edi+edi*2]; and ecx,3; sub ebx,ecx; jle; rep stosb; rep stosd;
add ecx,ebx; rep stosb`) — an ebp frame appears because the size*16 value is
spilled to the param slot (`mov [ebp+8],edi`) so edi can be reused for the
pool, then reloaded (`mov ebx,[ebp+8]`).  Every C shape (memset of the fresh
`_callnewh` result, of the stored global, with a global-read size) makes
MSVC6 emit the simpler `rep stosd; rep stosb` form without the alignment
pass, keep the size in a register, and skip the frame.  The alignment pass
is the compiler's response to an *opaque* destination+size pair with a
potentially large size; the register-reuse that forces the spill is an
allocator scheduling choice.  Kept fenced-naked.

## Finding 20 — m_FreeTracked (0x10006820): transient-register alternation (185/188)

The reference's post-`free` block alternates edx/ecx for the four global
decrements (`g_count3`→edx, `data[0x14]`→ecx, `g_count2`→edx,
`data[0x10]`→ecx) — the first transient *reuses the just-freed block
register* (edx).  Every C shape (with/without a `g3` temp, `b` block copy,
`int`-returning `free`, statement reordering, /G5/G6) makes MSVC6 keep the
first transient in ecx (two consecutive ecx transients) — a 3-byte
register-role residue (`8b 0d` vs `8b 15`, `49` vs `4a`).  All other 185
bytes match, including the `while`-loop form (a `do/break` loop was
rotated with a duplicated compare; the combined `while (i < count &&
p[i].block != b)` condition reproduces the reference's straight
`cmp/jl` back-edge) and the global-load hoisting (reading g_count1 into a
temp before the count/pool loads, then storing g_count1-1 last, matches
the reference's three-hoisted-loads order).  Kept fenced-naked.

## Finding 21 — the `?:` flag chain splits only in sibling-specific register contexts

`amt_UpdateEntityLinks (0x1000ba30) — best C 170/179, kept fenced-naked`.  The
match branch stores `b[0] = -1; b[4] = -1; b[3]byte = (gword > 0xb) ? 4 : 3;
b[2] = 0; result |= 1`.  The reference emits the flag chain *split* around the
first store: `seta cl; mov [eax-0x10],-1; add ecx,3; mov [eax],-1;
mov [eax-4],cl; mov [eax-8],ebx; or esi,1`.  With the identical C statement
order, `amt_ClearEntityLinks (0x1000b990)` — which is EXACT 157/157 — emits
the chain *before* the first store (`mov [ecx-0x10],-1; seta dl; add edx,3;
...`), and UpdateEntityLinks under the same flags emits it fully fused
(`seta cl; add ecx,3; mov [eax-0x10],-1; ...`).

Exhausted: 5 statement orders (b0/b4/byte/b2 permutations) × {/O2, /O2 /G6};
byte/bool/int temps; `if/else`; `3+(gword>0xb)` (narrows to `add cl,3` — 80 c1
03 — vs the reference's `add ecx,3` 83 c1 03); flags /G3 /G4 /G5 /G6 /GB /O1
/Og; `#pragma optimize("s"/"t")`; GA.  /G6 sinks the whole chain below all
four stores AND switches the second loop's byte compare to the memory-operand
form (`cmp dl,[ebp+0x168]`) — but the reference loads it into cl
(`mov cl,[ebp+0x168]; cmp dl,cl`), i.e. the reference's second loop is
/G5-style.  No single flag or C shape reproduces both loops; the split chain
needs a scheduler behavior 8168 exhibits in neither mode.  All other 170
bytes match (arg1-based semantics — `mov ebp,[esp+0x10]` after `push esi` is
*a reload of arg1*, not arg2; the `b+4 < bound` / `b+1 < bound` loop-bound
idiom from Finding 20 applies).  Kept fenced-naked.

## Finding 22 — SwapOfficeHolders (0x1000b880): register-name residue (264/263)

The best C is 264 bytes vs 263 target — every instruction shape, order, and
slot matches; only *register names* differ.  The allocator assigns
arg1→ebp/ent2→ebx where the reference has arg1→ebx/ent2→ebp (the two
persistent callee-saved values swap ebx/ebp), names the two swap temps
eax/ecx the other way round, and schedules the ent1 reload
(`mov eax,[esp+0x14]`) between the two swap stores instead of after them.
The logic, prologue shape, search loops, and the arg1-slot spill are all
byte-identical.

Key discoveries along the way (all required for 264):
- The swap temps MUST be volatile reads.  A plain `t = *(int*)(rec2+4)` is
  value-numbered with the 3rd call's argument (same address) and kept alive
  across the call in a callee-saved register; `u = *(int*)(rec1+4)` does the
  same with the 2nd call's argument.  Either unification cascades into a
  frame (`sub esp,8`/`push ecx`) and an ent2 stack spill.  Two volatile
  temps force both loads at the swap site and collapse the function to
  264 bytes.
- The loop-bound compare must be SIGNED: pointer compares emit `jb` (72),
  the reference uses `jl` (7c) — cast the pointer to `(int)`.
- The rec2-first load order (`t=rec2; rec1=t; rec2=rec1-old`) reproduces the
  reference's load order; the rec1-first form emits the loads the other way.
- Struct-typed accesses, statement-order permutations, `int`-typed arg1, and
  flags /G3–/G6 /GB /O1 /Og /Ox do not change the ebx/ebp assignment.

The remaining 8-byte residue is a pure allocator register-preference quirk
(ebp for the entry parameter vs ebx) with no C-shape lever found.  Kept
fenced-naked.

## Finding 23 — ValidateOfficeCandidate (0x1000b1c0): fail-block sinking + loop rotation

Best C is 244 bytes vs 205 target.  The reference's structure: the two
search loops are *non-rotated* do-whiles (`cmp byte [eax],dl; je found; add;
inc; cmp eax,bound; jl loop` — the bound check is the back-edge), and the
shared fail-return block (`pop esi; xor eax,eax; pop ebx; ret`) sits
mid-function as the FIRST loop's fall-through, with the found-path jumping
over it and the found-checks jumping *back* to it.  The second search's
not-found has its own inline return-0 copy.

MSVC6 12.00.8168 will not reproduce this: every C/goto/loop form
(`do-while`+goto, `while(1)`+break, explicit `loop:`/`goto` back-edges,
combined `&&` conditions, `#pragma optimize("t",off)`, /O1 /Ox /Og /G6)
either sinks the fail return block to the function end (turning every check
into a long `0f 8x` jump — the ent-null check alone is `0f 84` vs the
reference's short `74 23`) or rotates the loops with a duplicated byte
compare.  The two behaviors are coupled: sinking the fail block turns the
loop's fall-through exit into a jump, which then triggers rotation.
Additional notes: the `i >= 30` check after each found-exit is provably
dead (the loop bound 0x101de870 = base + 30*0x18) but kept; the slot base is
folded into the memory operands (`[eax + 0x101de5a4]` etc.) — writing the
slot as `(char*)0x101de5a0 + i*24 + off` reproduces the `lea i*3; shl 3`
index form.  Kept fenced-naked.

## Finding 24 — ahm_ClampFloatValue (0x1000c3c0): three FPU return blocks

Best C is 82 bytes vs 83 target (or 74 with the FPU store form).  The
reference emits the clamp as three SEPARATE return blocks: the v-store
(`fstp [mem]; mov eax,1; ret`) as the main flow's fall-through, then the
min and max blocks at the end, each `fstp st(0); fld const; mov eax,1;
fstp [mem]; ret` — the return-1 load scheduled *between* the fld and the
fstp.  MSVC6 8168 will not reproduce this:
- `*(float*)(arg2+4) = *(float*)const;` direct stores compile to integer
  moves (`mov edx,[const]; mov [ecx+4],edx`) and inline the clamp blocks
  (jump-over branches, inverted from the reference's jump-to blocks) — 82B;
- routing the constant through an FPU-resident `v` (`v = const; store v;`)
  yields the fld/fstp round-trip but the compiler tail-merges the max block
  into the v-store (`fstp [mem]; mov eax,1; ret` shared) — 74B;
- else-if vs separate ifs, goto-labeled blocks, and the single-store clamp
  (65B) do not change either behavior;
- /G6 fixes the min block's mov position but reorders the prologue
  (`fld` before the second arg load) and keeps the max merge.

The three-way split with the early `mov eax,1` is a scheduler+block-layout
choice 8168 makes in neither mode.  Kept fenced-naked.

## Finding 25 — m_PoolFree (0x10006e30): block param register + fatal placement

Best C is 133 bytes vs 137 target.  The reference keeps the `block`
parameter in edx (volatile — its live range spans no call) and RELOADS it
from the stack (`mov ecx,[esp+8]`) for the list-walk part; the bounds
temps live in esi; the fatal block (`push 0x10028b94; push 0x279; push
0x10028888; call ReportFatalError`) is sunk to the end with the checks
jumping forward to it.  MSVC6 8168 instead assigns block to esi (callee-
saved) for its whole live range and places the fatal block inline after
the checks (the main flow jumps over it).  Seven formulations — separate
ifs, combined `||` with the p-load hoisted (which does sink the fatal but
speculatively loads `*(hdr)` before the hdr==0 test), assignment-in-
condition (correct load order but inline fatal), named lo/hi temps, a blk
local, /G6 — all normalize to the same 133B.  The fatal-sink and the
load-order are mutually exclusive in this compiler.  Kept fenced-naked.

## Finding 26 — sim_PriorityUpdate (0x10015400): frame vs arg-slot reuse

Best C is 76 bytes vs 83 target.  The reference allocates an 8-byte frame
(`sub esp,8`) for the `table_lookup` range output and addresses it as
`[esp+4]` (word compare against `entity[0x65]`); MSVC6 8168 slot-reuses the
dead arg2 slot instead (no frame, `[esp+0xc]` after `push esi`), producing
the same semantics 7 bytes shorter.  An `unsigned short`, two `int`, and an
8-byte struct local all pack into the arg slots; /G6 reorders the arg
prep without allocating the frame; /O1 switches to a frame pointer.  The
rest of the function (byte arg zero-extend into ecx for `table_lookup`,
unsigned word compare with `jae`, byte `>0` guard + decrement of the old
entity, `ctx->0x170` reassignment, `entity[0x65]++`) matches byte-for-byte.
Kept fenced-naked.

## Finding 27 — sim_StartEntityQueryByType (0x10015460): callee-saved roles

Best C is 130 bytes vs 145 target.  The reference's register roles: arg1→esi,
base (from the `g_entity_type_table` global pointer) →edi, type byte→edx
(zero-extended), index→ecx, and a `xor eax,eax` hoisted before the table
computation feeding the first branch's `push eax` (arg3=0).  MSVC6 8168
assigns arg1→edx and base→esi (one push instead of two), folds the index
chain the same way but into eax, and emits `push 0` for the first branch's
arg3.  Type/base temps, /G6, and the natural forms all normalize to the
same 130B.  The type*589 index chain (lea 3t; shl 4; +t; lea *3; lea
[base+*4]) and the four `gm_StartEntityQuery(v,1,0,code)` dispatch calls
match.  Kept fenced-naked.

## Finding 28 — AdvanceGameClock (0x100155c0): arg4 preserve vs reload

Best C is 215 bytes vs 197 target.  The reference keeps only esi as a
callee-saved register and RELOADS arg4 from its stack slot after the idiv
clobbers edx (`mov eax,[esp+0x10]`); MSVC6 8168 preserves arg4 in edi and
pushes ebx/esi/edi (three pushes, 18 bytes larger).  The signed /60 magic
(0x88888889 imul + sar 5), the unsigned /24 magic (0xaaaaaaab mul + shr 4),
the `h - days*24` strength-reduced modulo, and both day-rollover loops
match; /G6 reorders the prologue without changing the register count.
Kept fenced-naked.

## Finding 29 — gm_CleanupObjectEntities (0x10015cf0): SIB base/index roles

Best C is 193 bytes vs 194 target — the only differences are addressing
encodings.  The reference uses the loop counter as the SIB *base* and the
reloaded array as the *index* (`cmp word [esi+eax],0`, `lea ecx,[esi+eax]`
on the free path); MSVC6 8168 emits the array as the base with the counter
scaled (`cmp word [eax+esi*1],0`) and `add eax,esi` instead of the lea.
Operand-order swaps in the C (`array+i` vs `i+array`), /G6, and a named
`g_query_limit` global (which DID fix the counter decrement to the `a3`
moffs form) do not change the SIB roles.  Everything else — the loop
structure, the gm_ResolveEntityById out-param chain (c→+0x5d, b→+0x14,
a→+0x178), the free path, and the final rep stosd memset — matches.
Kept fenced-naked.

## Finding 30 — gm_CheckEntityType (0x10017ab0): lea vs folded table load

Best C is 72 bytes vs 74 target.  The reference materializes the
`base + type*589` address with a separate `lea eax,[edx+eax*4]` before the
byte load (`mov al,[eax]`); MSVC6 8168 always strength-reduces the address
into the load's SIB (`mov al,[edx+eax*4]`), 2 bytes shorter.  Pointer
variables, split `base + type + type*588` expressions, idx temps, and /G6
do not prevent the fold.  The 7-way `== 0xb/0xd/0xc/0x10/0x1c/0x1d/0x1f`
compare chain, the type*589 lea chain, and the null-arg return (which
naturally returns eax=0 without an xor) match.  Kept fenced-naked.

## Finding 31 — ahm_ProcessEntityChain (0x1000ca00): do-while inversion

Best C is 136 bytes vs 130 target.  The reference's dispatch loop keeps the
ok test at the bottom (`test ebx,ebx; jne loop` back-edge) with the type-6
check as a forward `je` to a block after the set2 fall-through; MSVC6 8168
inverts the loop — the ok test is hoisted above the type check and the
back-edge jumps to the handler, 6 bytes larger.  Break, goto, and
post-loop-ok-test structures all trigger the inversion.  The handler
dispatch (`call [eax*4+0x1002c5a0]` with the byte index zero-extended via
`and eax,0xff`), the two walk-and-set paths (set-2 sets every node, set-1
only the final type-6 node), and the byte-compare `cmp al,6` (avoid a
`t` temp — it forces a pre-zero + full-register compare) match.  Kept
fenced-naked.

## Finding 32 — cm_GetBuildingStatCount (0x100104a0): branchless if-conversion + lea fold

Best C is 133 bytes vs 135 target.  Two residue patterns:
1. `if (x == 1) return 0xc; return 8;` (constant returns) triggers MSVC6's
   branchless if-conversion (`dec al; neg al; sbb eax,eax; and al,0xfc`);
   the reference keeps branchy `mov eax,8; cmp bl,dl; jne; mov eax,0xc`
   — writing `r = 8; if (x == 1) r = 0xc; return r;` preserves the branch.
2. The type*589 address is folded into the 0x247 load
   (`mov al,[esi+eax*4+0x247]`) where the reference materializes it
   (`lea eax,[esi+eax*4]; mov al,[eax+0x247]`) — the Finding 30 fold.
   Statement order matters: the index chain must precede the obj
   (`cmd+0x65`) load to match the reference's scheduling.  Kept fenced-naked.

## Finding 33 — cm_ChkMoveCredits (0x1000cb20): arg3-lea hoist (3 bytes)

Best C is 168 bytes vs 171 target.  The reference hoists the `&c` (arg3)
address lea above the `*(arg1+0x14)=r` store (computed at an earlier esp,
3 disp8 bytes differ); MSVC6 8168 emits all three out-param leas after the
arg4 push regardless of C structure (pc/pa/pb temps, declaration order,
statement order).  The unsigned-char `gm_QueryEntitySum` 2nd param (byte
passed raw in cl — declaring it `unsigned char` stops the zero-extension)
and the `sum - limit < 0` form (sub + jns back-edge) match.  Kept
fenced-naked.

## Finding 34 — cm_ExChangeFloat (0x1000eb70): offset-register role

Best C is 130 bytes vs 135 target.  The reference loads the float-offset
(`esi->0x14`) into edx (`mov edx,[esi+0x14]; fadd [eax+edx]; add eax,edx`);
MSVC6 8168 puts it in ecx, emitting `[eax+ecx*1]` (SIB) — a
register-role difference — plus the Finding 33 arg3-lea hoist residue.
The GetFieldByType/ResolveEntityById chain, the c?a:b selection, the
`+=` float add with `fld; fadd; add; fstp`, and the result-byte store
otherwise match.  Kept fenced-naked.

## Finding 35 — cm_ExModifyStat (0x100100a0): FPU re-compare fold

Best C is 146 bytes vs 159 target.  The reference's clamp routes the
merge point (f>=a4 → clamp to a4, versus cc<f<a4 → keep) through a second
`fcom [a4]` compare; MSVC6 8168 always folds the redundant compare away,
emitting the tighter if-converted clamp (13 bytes shorter).  The
`mov [esp+0x10],edx; fild [esp+0x10]` int→double spill, the byte stat
read/`+`/store, and the `__ftol` conversion otherwise match.  The
`if (f < a4) { if (f <= cc) f = cc; } else { f = a4; }` form is the
closest; per-branch stores over-shoot (180B).  Kept fenced-naked.

## Finding 36 — cm_ExAllocThemaPredigt (0x1000f2f0): add-edi fold + dead-store elimination

Best C is 162 bytes vs 176 target.  The reference materializes
`add edi,0x18` once (adjusting the param base before the 7-byte entity
copy: `mov edx,[edi]; mov [ecx],edx; mov ax,[edi+4]; mov [ecx+4],ax;
mov dl,[edi+6]; mov [ecx+6],dl`) and keeps a dead byte copy
(`mov dl,[edi+6]; mov [ecx+6],dl` then `mov byte [esi+0x22],0` — same
destination, overwritten).  MSVC6 8168 folds the add back into
base+offset addressing on each access (saving the 3-byte `add` + the
separate `lea ecx,[esi+0x1c]` dst pointer is also folded) and eliminates
the dead store entirely.  Both differences are optimizer strength
reductions that no C shape prevents: any `base += 0x18` formulation
flips esi/edi register roles (the two pointer temps spill), and the
dead store is only preserved by pointer-alias hiding which the GRA
resolves.  The prologue offsets 0-63, the
gm_GetFieldByType/gm_AllocObjekt calls, the interleaved
LogMessageInternal arg pushes, the `type*2507364` table store
(`lea edx,[eax+eax*8]; mov [edx*4+0x10442d08],eax2`), the `ent+0x12=0x40`
and the result-byte stores all match.  Kept fenced-naked
(`REBREW_ALLOW_NAKED`).

## Finding 37 — cm_ExMoveObjekt (0x1000e530): node-spill fixed point + store1 address form

Best C is 340 bytes vs 346 target (10+ formulations: cmd/base stores,
`volatile`, `int*` base, inline-if calls).  Two allocator decisions are
unreproducible:

1. **store1 address form.**  The reference emits the folded
   `mov [esi+0x14],eax` (field store).  A cmd-based store
   (`*(int*)(cmd + 0x14)`) makes MSVC6 reload the address-taken param
   into a scratch (`mov ecx,[esp+0x20]`), shifting the call-1 lea
   round-robin by one register; a base-based store (`*(int*)(base+0x14)`
   or `base[5]`) makes MSVC6 hoist `lea edi,[esi+0x14]` before the
   first GetFieldByType call and store via `[edi]` (+2 bytes).  The
   reference's folded form needs neither, and no formulation produces it
   (volatile on the store target does not change the hoist).

2. **Scan-loop node spill.**  The reference spills the list node to
   `[esp+0x18]` at each loop definition, re-tests it after the unlink
   (`mov eax,[esp+0x18]; test eax,eax; jne L_attach` — a redundant
   `if (node)` that MSVC6 keeps only because the value lives in memory)
   and reloads it 3x in the attach.  The closest C keeps node in ecx
   instead (no spill, redundant check eliminated by the optimizer), and
   the attach's field2 load lands in eax instead of ecx.  Both are
   self-consistent register allocations; the spill primes the attach's
   round-robin (test-eax → field2 in ecx) and the register form primes
   eax — no C shape inverts the choice.

Everything else matches byte-for-byte: the prologue offsets, all three
GetFieldByType/ResolveEntityById call sequences (including the call-1
lea round-robin (ecx,edx,eax) and call-2 (eax,ecx,edx)), both entity
selections (src/dst via 0x5d/0x14/0x178), the `cmp [ecx+8]` scan, the
unlink, and the attach stores.  Kept fenced-naked (`REBREW_ALLOW_NAKED`).

## Finding 38 — cm_ExChangeAttribute (0x1000e7d0): loop register-pairing swap

Best C is 213/242 bytes (19 formulations).  The reference's loop pairs
`{count, offset, dst2}` in ecx with the payload pointer (src) in eax;
every C formulation allocates the opposite pairing
(`{count, offset, dst2}` in eax, src in ecx) — a systematic eax↔ecx
swap across ~29 register-encoding bytes.  The pairing is decided by the
src pointer's register at the loop-setup `lea` (`lea eax,[ebp+0x15]` vs
`lea ecx,[ebp+0x15]`); the count byte-load then takes the other register
(cl vs al), and the offset zero-extend (`xor ecx,ecx; mov cx,[eax]` vs
`xor eax,eax; mov ax,[ecx]`) and the `dst2 = entity + offset` sum follow
it.  Declaration order, `register` hints, statement order, and the
puVar5 pointer forms (which fix the offset-read scheduling to
`inc;xor;inc;mov cx,[eax]`) cannot flip the pairing.

What DID converge (matches byte-for-byte): the `&resolved`-local trick
(Finding 7 workaround — a local `int* resolved` whose slot reuses the
dead `cmd` param home; the source never takes `&cmd`, so the base stays
in ebp and the field store folds to `mov [ebp+0x10],esi`); the resolve
lea round-robin (ecx,edx,eax); the dst selection into edi; the
dispatch dec-chain (switch on size {1,2,4}); the `src++;src++`-style
offset walk with the zero-extend scheduled between the increments; the
`unsigned n` + `while (n > 0)` form (emits `test; jbe`); and all three
add-to-memory inner loops (only reachable when the entity/dst2 split
keeps the entity in edi and the loop has no free scratch register).
Kept fenced-naked (`REBREW_ALLOW_NAKED`).

## Finding 39 — cm_ExChangeBits (0x1000eaa0): pre-resolve field store materialization

Best C matches everything except the first 20 bytes (6+ formulations:
cmd/base stores, char-cast read/store splits, `cmd + 0`, volatile base,
`int* base` with `base[4]`, flag sweep incl. /O1 — which switches to a
frame-pointer prologue).  The reference passes `&cmd` to
gm_ResolveEntityById AND folds the pre-resolve field store as
`mov [esi+0x10],eax` with the base kept in esi (pushed once).  Every C
formulation either CSE-hoists the store address
(`lea edi,[esi+0x10]` scheduled before the first GetFieldByType call —
the Finding 7 family split, stealing edi and shifting the resolve lea
round-robin) or reloads cmd from its home slot into a scratch.  The
base copy is semantically required (the post-resolve offset/size/mask/
value reads at `cmd+0x14/0x18/0x1c/0x20` use the ORIGINAL cmd while the
entity uses the modified `&cmd` slot), and its presence is what
triggers the split — the same fixed point as cm_ExFree (fenced,
177/180), cm_ExMoveObjekt (Finding 37) and cm_ExChangeAttribute
(Finding 38).

What matches byte-for-byte modulo the head: the folded resolve leas
(ecx,edx,eax), the selection (`cmd ? cmd : (pv8 ? pv8 : pv4)`), the
`puVar3 = entity + *(int*)(base+0x14)` pointer, the dec-chain dispatch
(switch on size {1,2,4}), the size1 byte-temp form
(`bVar4 = *puVar3 & ~*(char*)(base+0x20)` with byte not/and/or), the
size2 in-place `and word ptr [eax],cx` + reload, the size4 dword
pattern, and the result-byte store.  Kept fenced-naked
(`REBREW_ALLOW_NAKED`).

## Finding 40 — cm_ExChangeDesire (0x1000e9c0): family store materialization + FPU clamp

Two blockers.  (1) The Finding 7 family store materialization: the
reference keeps the cmd base in edi (single prologue push) and folds
the field store (`mov [edi+0x10],eax`) while passing `&cmd` to
gm_ResolveEntityById(0, 0, &cmd, field); every C emits
`mov eax,[esp+4]` first, CSE-hoists `lea esi,[eax+0x10]`, and pushes
three callee-saved registers in the prologue instead of deferring ebx
and esi to L_resolved/loop-entry.  (2) The Finding 35 FPU clamp
re-compare: the reference's stat clamp routes through a second
`fcom max` after the first compare already established stat<max
(the L_clamp_chk re-check), which MSVC6 always folds away in C.

What matches: the resolve's `push 0; push 0; lea ecx,&cmd` arg pattern,
the loop's `lea ecx,[eax+eax*2+0x24]; shl ecx,2` stat-index chain
(`entity + (idx*3+0x24)*4`), the `fld [edx]; fadd [ecx+eax]; fstp`
in-place add, the entity reload from the cmd slot each iteration, the
unsigned count guard (jbe), the ebx counter with per-iteration count
reload, and the result-byte store.  Kept fenced-naked
(`REBREW_ALLOW_NAKED`).

## Finding 41 — cm_ExRemoveLinkedObject (0x1000f0d0): prologue scheduling

Best C matches the control flow and all four gm_RemoveLinkedNodeById
call sites, but the prologue scheduling diverges (4 formulations): the
reference pushes ecx/esi/edi and then loads the original-result copy
into edi (`mov edi,[esp+0x14]`) and the cmd base into esi
(`mov esi,[esp+0x10]` at L_skip_mark, after the `*result=2` mark);
every C emits `push ecx; mov eax,[esp+0xc]` (result loaded into the
volatile eax first), interleaves the loads between the pushes, and
shifts the resolve lea round-robin by one register.  Statement order
(r-copy before/after base, mark before/after base) does not change it.

Semantics worth preserving in the fallback: the function takes
`&result` (the char* param) as a resolve out-param, so the original
result pointer must be copied (edi) for the `*result=2` / `*result=1`
marks, and the node-id reads at `cmd+0x14` / `cmd+0x18` must use a
`base` copy of the ORIGINAL cmd — the post-resolve cmd slot holds the
resolved entity (never 0 in the p1/p2 branches, so using it would fold
`*(0+0x18)` into an absolute load).  The -2 (query empty), -1 (no
entity), 0 (success) and q (remove result) return paths all match.
Kept fenced-naked (`REBREW_ALLOW_NAKED`).

## Finding 42 — cm_ExClearLagerslot (0x1000e690): family store materialization (short* base)

The Finding 7 family store materialization with a `short*` base: the
reference keeps the base in esi (`push esi; mov esi,[esp+8]`) and folds
`mov [esi+0x10],eax` (the `*(int*)(psVar1+8) = field` store, +8 shorts)
while passing `&cmd` in the middle of
`gm_ResolveEntityById(0, &cmd, 0, field)`; every C emits
`mov eax,[esp+4]` first, CSE-hoists `lea esi,[eax+0x10]`, and shifts
the resolve arg pushes (the ref interleaves the store between `push
ecx` and `push 0`).  The rest of the Ghidra reference converts cleanly:
the `*cmd == 0x2a || *cmd == 0x116` word compare, the
`gm_StartEntityQuery(*(int*)(cmd+10), 1, 0, (uint)(ushort)psVar1[10])`
call with the `xor edx,edx; mov dx,[esi+0x14]` zero-extend, the
`*(int*)(puVar3+7) != 1` count check, the
`gm_RemoveObjectByType((char**)(cmd+10), ...)` call, and the shared
log-return-1 tail.  Kept fenced-naked (`REBREW_ALLOW_NAKED`).

## Finding 43 — cm_ExSetAttribute (0x1000e8d0): loop-head offset-read scheduling

Best C is 234/239 (the closest conversion of the family; 6 formulations).
The reference's loop head walks the payload pointer for the 16-bit
offset: `inc eax; xor ecx,ecx; inc eax; mov cx,[eax]; add eax,2` — the
offset zero-extend is scheduled BETWEEN the two pointer increments,
which prevents MSVC6 from merging them.  Every C (char* walk, puVar5
pointer forms, post-read `src++;src++` splits, int* piVar6 casts —
which regress the frame) either merges the increments into
`add $0x3,%eax` with a disp+1 read (`mov cx,[eax+1]`) or moves the xor
after the merged add — a scheduler fixed-point.  The 5-byte residue is
localized to offsets 0x87-0x8d.

What matches: the `resolved`-local trick (Finding 7 workaround — base in
ebp, `mov [ebp+0x10],eax` folded store BEFORE the resolve), the resolve
lea round-robin, the deferred ebx/edi pushes, the selection into edi,
the count guard (jbe), the dec-chain dispatch, and all three inner
STORE loops (`mov [ecx],edx` — set, not accumulate; the twin of
cm_ExChangeAttribute's add loops).  Kept fenced-naked
(`REBREW_ALLOW_NAKED`).

## Finding 44 — gv_UpdateProductionProgress (0x10011790): arg-order + sum-register fixed points

Best C is 203/242 (13+ formulations).  The head, the shared -1
epilogue (nested ifs with a final `return -1` — the three early
`return -1` sites merge only via fall-through, not goto), the 589-
multiply type check (`dword_100a8c30 + (uchar)*v * 589`), the
CheckSlotActive call, and the ternary clamp `(val <= 0) ? 0 : val`
(branchless setle/dec/and) all match.  Two scheduler fixed-points
remain:

1. **GetSlotEntry arg setup.**  The reference loads the byte arg3
   first (`mov dl,[edi+0x10]; mov eax,[edi+0xc]; push edx; push eax`)
   with NO zero/sign extension (raw byte push — the callee reads only
   the low byte); every C either zero-extends (`xor edx,edx; mov dl`
   with an unsigned char cast — +2 bytes) or sign-extends (`movsx` for
   a char cast), and the arg2 load is always hoisted ahead of arg3's
   regardless of evaluation order, temps (which break the frame), or
   char/uchar parameter declarations.
2. **Clamp sum-register role.**  The reference computes
   `val = *(uchar*)(r+0xc) + *(int*)(a+0x13)` with the byte loaded
   first into ecx, copied to edx, the dword into ecx, and the sum in
   ecx; every C lands the dword load first and the sum in edx.

Kept fenced-naked (`REBREW_ALLOW_NAKED`); the 203/242 C is preserved
in the #else fallback.

## Finding 45 — gv_ActivateGraveyardSection (0x10011660): error-block placement

Best C is 275/306 (4 formulations: nested-if fall-through, error-first
ifs, if-else, block-scoped).  The head (resolve, 589-type check, the
t==3/2/1 dispatch with the shared store tails) matches byte-for-byte,
and the second resolve's `&v2` must be passed in the MIDDLE position
(`gm_ResolveEntityById(0, 0, &v2, *(a+4))` — the first resolve passes
`&v` first; the two out-params live in the arg slot and the push-ecx
local respectively).  Two layout fixed-points remain:

1. The reference INLINES the `p==0 → -3` and `v2==0 → -6` return
   blocks right after their `jne` checks; every C groups them at the
   tail with the -7/-8/-1 epilogues (je to the tail), making the
   function 9 bytes shorter and shifting the -1 target.
2. The t==2 success path pops edi BEFORE the two stores in the
   compiled (`pop edi; mov [esi+0x1a],cl; ...`) vs after in the
   reference.

The -2 (type-check) return inlines correctly in both.  Kept
fenced-naked (`REBREW_ALLOW_NAKED`); the 275/306 C is preserved in the
#else fallback.

## Finding 46 — gv_GetSlotEntry (0x100105b0): shared return-0 epilogue

Best C is 35/329 positional (5 formulations).  The reference shares ONE
`xor eax,eax; pop esi; ret` epilogue for ALL fail paths (the size-range
check, every gv_CheckSlotActive fail, and every per-(b,size) c-limit
check — all `jae/jl/jg` to 0x145), with the success
`base + (uchar)c * 20` lea-chain inline.  Every C either inlines the
fail returns (`xor eax,eax; pop esi; ret` right after each `jb` —
shifting the whole layout) or explodes the success returns into
duplicated blocks (437B when the success is written inline with
inverted conditions).  The size must be re-read from `*(a+4)` at each
site (a `size` local forces a second callee-saved push).  The
per-path c-limits (b=0: 8/0xc/0x10, b=1: 4/6/8, b=2: size1 invalid +
2/4, b=3: size1/2 invalid + 2) and the `c*20` index chain otherwise
decode cleanly.  Kept fenced-naked (`REBREW_ALLOW_NAKED`); the C is
preserved in the #else fallback.

## Finding 47 — gv_FindSlotEntryFiltered (0x10010710): long-lived arg register role

Best C is 63/320 positional (3 formulations).  The full control flow
decodes and matches: the `dword_100a8c30 + (uchar)*a * 589` type-table
pointer, the `*(a+0x65)` slot, the b2 dispatch (0/1/2/3 → the
per-b tables 0x1002577c/8c/9c/ac indexed by `(uchar)tp[0x247]` with
the `+ base*20` end pointers; 0xff → cm_GetBuildingStatCount(a) with
the +0x1c base), the second b dispatch (slot bases +8/0xc/0x10/0x14/
0x1c), and the callback walk (`slot += 0x14; while (slot < end) {
if (cb == 0 || cb(b, slot)) return slot; slot += 0x14; } return 0;`).
The register roles are a fixed-point: the reference keeps the long-lived
arg `a` in ebp and the type-table pointer in esi with the slot in edi;
every C allocates `a` in volatile edx (its live range does not cross a
call in either path, so the allocator is free to choose it) and swaps
the tp/slot roles.  Kept fenced-naked (`REBREW_ALLOW_NAKED`); the C is
preserved in the #else fallback.

## Finding 48 — SpawnGraveyardEntities (0x10010850): prologue region-split (cold-path saves)

[2026-08-24 exhaustive follow-up — goal-mode audit.]  Best C is 292/370
positional (10+ formulations).  Additional evidence gathered:

- **Toolchain sweep** (all vendored MSVC 4.0→9.0 SP1 incl. every MSVC6
  SP1-SP6): none reproduces the reference prologue; the best toolchain
  remains the base msvc6 (the same 292 wall).
- **GA** (40 generations × 64 population, 27.5 min, stagnant after 25
  gens): best individual is the same nested-if shape — no mutation
  (pragma optimize g/s/t/y, intrinsic, check_stack, auto_inline)
  reaches the reference.
- **Flag variants**: /O1 (57), /O2+/Os (45), /O2+/Og- (66),
  /O2+/G5 (292, identical), `#pragma optimize("", off)` (72/491),
  `#pragma optimize("t", off)` (45) — all strictly worse or unchanged.
- **Live-range lever confirmed**: adding `count > 0` to the guard chain
  does pull `push ebx` to entry (ebx becomes live across the guards),
  proving MSVC6 places a callee-saved save at entry iff the register's
  live range crosses the guard block.  But ebp/esi/edi have no legal
  pre-guard use: the reference's own fail epilogue returns the
  constant 0 (`xor eax,eax`), so even ebp is dead across the guards in
  the reference — its entry save has no C-expressible cause.
- **register-keyword / pointer-typed arg / do-while / goto-body /
  shared-return forms**: all ≤ 292.

Conclusion: the reference build emitted function-level saves (both
epilogues pop all four), our toolchain emits region-local saves; this
divergence is a compiler-build behavior, same class as the
gm_NextEntityQueryMatch blocker (declared unreproducible across all
available compilers).  Kept fenced-naked; C preserved in #else.

Best C is 291/370 positional (5+ formulations).  The entire body decodes
and matches: the `dword_100a8c30 + (uchar)*a * 589` type check (field
`tp[0x247]` in 1..3), the `gv_FindSlotEntryFiltered(0, a, 0,
0x10010700, 0)` slot acquisition, the `*p = g_10030b6c++` counter bump,
the `slot+4/+8/+0xa/+0xc` field stores, the 5-iteration `gm_RandomMod`
byte fill (offsets +0x24..+0x28), the four `gm_RandomMod`+1 dword stores
(+0x2c/+0x30/+0x34/+0x38/+0x40), and the three discarded `gm_RandomMod`
calls.  The single blocker is the prologue: the reference saves ebx/ebp/
esi/edi all at entry (with the `mov cl,[eax]` 147-chain load interleaved
between `push ebp` and `push esi`) and its `return 0` guard epilogue pops
all four; every C formulation MSVC6 region-splits the callee-saved saves
past the three guard checks (`jne/jb/ja` to the shared ret0), so the ret0
path pops only the registers already saved.  Nested-if (guards as the
success gate) is required — the early-`return 0` form degrades to inline
`xor eax,eax; ret` per guard (56/370) and `goto fail` inlines the ret too.
The `(float)gm_RandomMod(8) & 0xffff` float-chain (`fild; fmul 21.0; fadd
42.0; __ftol`) and the `do { j++; store[j+0x23]; } while (j < 5)` rotation
both byte-match.  Kept fenced-naked; C preserved in #else.

## Finding 49 — ls_InitNewDynastyEntity (0x100122e0): 768x768 fill induction-variable elimination

Best C is 99/341 positional (5 formulations).  The resolve/flag-select
head is byte-identical (4 real args — the 4th is the entity struct; the
`a == 0x15` selects `[d+0x1cc] |= 0x1000` + `fcn_1000b820` vs `|=
0x2000` + `fcn_1000b850`; `[d+0xa] = (short)c`), as are the tail float
stores (1000.0/1.0/12.0/330.0/1000.0), the 5-iteration `fild; fadd` byte
fill, and the `gm_AddOrAccumulateObject` call.  The blocker is the nested
768x768 fill (`for p = 0x100a9820..0x10139820 step 0x300; for i < 0x300`
`p[i] = rnd(0x40)-0x20; p2[p-0x100a9820+i] = 0`): MSVC6 strength-reduces
`i` into a running pointer pair (eliminating the counter), while the
reference keeps the counter in esi and the base-offset in edi and reloads
the running slot pointer `p` from the reused arg-3 stack slot each outer
iteration.  A named `zero` variable and a `q = p - base` offset both fail
to stop the elimination.  Kept fenced-naked; C preserved in #else.

## Finding 50 — AllocGraveyardField (0x100109d0): alloc/field-init loop allocation

Best C is 141/661 positional (3 formulations).  The validation/alloc head
is byte-identical (the `dword_100a8c30` 147-chain type check, the
`m_AllocTracked(0x24, "0x1002d474")` 36-byte struct + `memset 36`,
`[esi] = *(b+1)`, `[esi+4] = tp[0x247]`, the two sub-allocations
`g_1002575c[type]*20` and `g_1002576c[type]*68` with their `memset`s, and
the cleanup free chain).  The divergence is the six `field-init` loops
(type 1: 8+4, type 2: 12, type 3: 16+12 — each storing `0`/`1`,
`q`, `-1`, `0xffff` per 0x14-byte slot while stepping `q` by 0x44 or
0x88) plus the `-1` fill loop and the second `memset`: MSVC6 merges the
`-1` dword store with the `0xffff` word store into one register (the
reference keeps `edi = -1` and `edx = 0xffff` separate), and its induction
variables fold the `+0x14/+0x44` walks into a single pointer where the
reference keeps the counter, offset, and base separate.  `0x1000` must be
written `*(int*) |= 0x1000` (not `0x100000`) to get the `or dh,0x10`
byte-form.  Kept fenced-naked; C preserved in #else.
