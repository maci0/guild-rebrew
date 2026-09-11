/* gv_ExAllocGraveyardWorker - allocates a graveyard worker entity of type
 * 0x1b/0x1c: validates the request against the resolved entity, finds a free
 * grave slot (or reuses one marked 0xf), initializes it from the matched
 * production entry, and returns the new grave id (0xffff on failure).
 *
 * Conversion state: 606/1040 at obj exactly 1040.  Each dated pass below
 * records the score it started and ended at.
 *
 * Shape notes (399/1040, from 393; size 1064 vs 1040):
 * - Both grave sweeps walk an `int` cursor against an end address
 *   (msvc6-c-shapes.md §31).  As typed pointers they compiled to an
 *   unsigned `jb`; the target's bound compare is signed `jl`.
 * - The 0x300 neighbour loop strides a byte offset 0..0x90000 by 0x300
 *   instead of recomputing i*0x300, which is what the target does.  The
 *   four stores keep their original order: they alias on the diagonal
 *   (i == grave), so reordering them changes which random draw lands in
 *   which cell.
 * - `count < 1` over `count <= 0` (identical for int) gains 13 bytes.
 *
 * Blocker: the frame is 0x14 where the target uses 0x10, so every [esp+N]
 * operand is off by 4.  Both use exactly the four slots 0x10/0x14/0x18/0x1c,
 * but MSVC6 allocates a fifth.  Tried without effect: inlining field_id,
 * job_id and workers; reusing j/count for the row offset; hoisting
 * grave*0x300 into the column index; a pre-zeroed entry result local.
 * The count/j register pair (target ecx/edx, ours edx/ecx) follows from
 * the same allocation.  Regressions measured: removing the volatile on the
 * grave-id store 377, re-basing grave+4 or grave+0x5c onto
 * 0x100358a4/0x100358fc 360/378, symbol-relative &g_slot_table 129.
 *
 * The fifth slot IS removable: writing the job-search guard as
 * `if (count <= j)` instead of `if (count < 1)` emits `sub esp,0x10` with
 * every frame reference on the target's offsets, and drops structural
 * mismatches 242 -> 225 (instructions 0-98 then align).  It is not kept
 * because the positional byte score falls 393 -> 390 at obj 1019 against
 * 1038: the guard collapse removes ~19 bytes, so the tail shifts.  Closing
 * the function likely needs this guard form plus whatever restores those
 * bytes; on top of it these were measured: `count <= 0` 390, declaring j
 * before count 390, loading count before zeroing j 390, `j >= count` 99,
 * bottom-testing the job loop 88, bottom-testing both grave sweeps 89,
 * splitting entry from the p walk 149, moving the job_id load after the
 * p load 386.
 *
 * The job-entry search emits one compare too many: this C tests the count
 * twice (`cmp ecx,1; jl` for the guard, then `cmp ecx,ebx; jle` for the
 * loop) where the reference tests it once against the zero already parked
 * in ebx (`cmp edx,ebx; jle` at 0x10011cf4) and falls into a rotated loop
 * whose bound compare sits at the bottom.  Collapsing the guard into the
 * loop does not fix it: a `do { } while (j < count)` with `count <= 0`
 * scores 97, the same do-while keeping `count < 1` scores 97, a `while (j <
 * count)` body is inert at 393, `count <= 0` alone is 390 (and 21 bytes
 * short), and pre-initializing `entry = 0` costs 63 (330).  The extra
 * compare is a symptom of the fifth spill slot, not an independent
 * defect.
 *
 * Both halves of that blocker are now fixed together, 393 -> 399, and the
 * function opens exactly like the target:
 *
 *   - the job-search guard as `if (count <= j)` (j is already 0) instead of
 *     `if (count < 1)` removes the fifth spill slot, so the frame is the
 *     target's `sub esp,0x10` and every [esp+N] operand lands on its offset.
 *     Instructions 0-98 then match exactly, exact-match instructions rise
 *     87 -> 103 and structural mismatches fall 242 -> 225.  On its own this
 *     costs 21 bytes (390 at obj 1019): the collapse removes the duplicate
 *     count test the notes above describe, and the tail shifts.
 *   - `volatile` on all four grave-id reads in the 0x300 neighbour loop
 *     restores them.  The target re-reads the id from the slot before each
 *     store pair (`mov cx,word ptr [ebp]` at 0x10011f2b, `mov ax,word ptr
 *     [ebp]` at 0x10011f36); msvc6 CSEs the four reads into one and parks
 *     the value in ebp.  Qualifying them emits the target's per-store
 *     reload.  All four must be volatile: dropping any one collapses the
 *     loop (383-391, and 100 with only the two outer ones).
 *
 * The remaining 24 bytes are the zero-extend form in that loop: the target
 * pre-clears the register (`xor ecx,ecx; mov cx,[ebp]`, 4 bytes per read),
 * msvc6 emits `mov dx,[ebp]; and edx,0xffff` (7 bytes).  An explicit `(int)`
 * cast on the read is inert at 399, and hoisting the read into an `int gid`
 * temp defeats the reload entirely (109).
 *
 * Also measured and reverted: `volatile` on the `req+0x15` byte read at
 * grave+0x165, to stop msvc6 hoisting it nine instructions above the
 * target's 0x10011eb9, 387; `volatile` on the returned grave-id read, to get
 * the target's closing `mov ax,word ptr [ebp]` instead of our `mov eax,ebp`,
 * 106; shared `one`/`neg1` constant locals for the repeated 1 and -1 stores,
 * chasing the target's `mov dl,1` and reused eax, both inert at 390;
 * declaring `chosen` before `gv` in either grave sweep, inert.
 *
 * 399 -> 446 at obj 1064 -> 1056 by narrowing counter scope.  `chosen` was a
 * function-scope local counted by both grave sweeps and read again at the
 * 0x100358a2 flag test and the `grave` base, so msvc6 spilled it and emitted
 * a `mov [esp+0x10],reg` inside each sweep that the target does not have (the
 * target keeps the sweep counter in esi throughout).  Counting each sweep in
 * its own block-scoped `int n` and assigning `chosen = n` after the loop
 * removes both spills and aligns the sweeps' `cmp`/`jl` pairs.  The same
 * narrowing on the three later `j` loops (the 5-byte copy, the 0x90000 walk
 * and the neighbour rescan, each given its own `n`, the rescan its own
 * `cnt2`) removes the second `mov [esp+0x14]` spill at the entry search.
 *
 * 446 -> 482 at obj 1056 -> 1032 by two independent changes:
 *
 *   - the 0x300 neighbour loop's column counter is a block-scoped `volatile
 *     int iv` instead of the function-scope `i`, and each store pair reads
 *     the grave id once into a block-local index (`a` for the row pair, `b`
 *     for the column pair) instead of four times inline.  The volatile homes
 *     the counter in the target's `[esp+0x14]` slot and the two index locals
 *     give each pair the single index register the target folds into its
 *     `mov byte ptr [edi+base]` stores.  446 -> 465 at obj 1042.
 *   - `volatile` on the returned grave-id read (`return *(volatile unsigned
 *     short*) grave`).  The target closes with `mov ax,word ptr [ebp]`, a
 *     fresh reload of the id from the slot; without the qualifier msvc6
 *     reuses the spilled copy at `[esp+0x18]` and drags an extra
 *     `and eax,0xffff` into the epilogue.  465 -> 482 at obj 1032.
 *     (An earlier note recorded this read as scoring 106; that was measured
 *     against the pre-465 body, where the neighbour loop still CSE'd the id.)
 *
 * Structural mismatches fell 217 -> 180.  Remaining 8-byte gap is still the
 * zero-extend form in the neighbour loop: target `xor ecx,ecx; mov cx,[ebp]`
 * (4 bytes per read), ours `mov si,[ebp]; and esi,0xffff` (7).  Measured on
 * the 482 body and reverted or inert: `unsigned int` index locals, inert;
 * writing the row index as `id + n` instead of `n + id`, inert; `unsigned
 * char one`, inert; a shared `gid = -1` local feeding grave+0x18c/0x20c/0x210,
 * inert (semantically identical, not kept); an `int* ivp` alias instead of the
 * volatile counter, 96; a single `chosen` counted by both grave sweeps, 379;
 * merging the second sweep into the first block, 399; sinking `chosen = n`
 * past the 0x300 log branch, 396 and STUB; hoisting `g_citizen_count++` above the
 * grave-id store, 451; hoisting `j = 0` above the count load, inert.
 *
 * Still open: an ecx<->edx role exchange at the entry-search loop (diff 99-118,
 * the target loads count through `mov edx,[edx*4+0x1002574c]` and counts in
 * ecx, ours is the reverse).  The loop is otherwise instruction-for-instruction
 * identical, so this is a register-naming difference, not a shape difference.
 * Measured on the 446 body and reverted: `count <= 0` instead of `count <= j`
 * as the guard, inert; declaring `j` before `count`, inert; a
 * `do { } while (j < count)` rewrite of the entry search, 103; splitting the
 * second sweep out with a `goto have_slot` so `chosen`'s store sinks past the
 * branch, inert at 446.
 *
 * 2026-09-06 session (482 -> 484, obj 1032 -> 1038).  SUPERSEDED by pass 6
 * below: the numerator hoist described here was reverted, and the reference
 * reads 0x10025680 only as the fdivr memory operand.  The float tail is a
 * numerator-hoist plus sunk-store shape. The target loads the 1000.0 numerator
 * into ecx BEFORE the RandomFloat01 call (`mov ecx,[0x10025680]` at 0x10011ef0,
 * ahead of `call`), keeps it resident across fmul/fadd, stores grave+0x1c from
 * it between fadd and fdivr, and only then divides (`fdivr [0x10025680]`) into
 * the st(0) denominator. Spelling the numerator as a hoisted `float fnum` local
 * (`fnum = *(float*) 0x10025680`, quotient `fnum / (...)`) reproduces the ecx
 * traffic and the shape; sinking the 0x20/0x24/0x28/0x2c stores ahead of 0x18,
 * with `*(float*)(grave+0x1c) = fnum` last before the neighbour loop, matches
 * the target's store order (probe gvec_sh27 ah-forms). +2 bytes, still 2 short
 * of target size. The int-bits spelling (`fbits` + `*(float*)&fbits`) is worse
 * (481); splitting the expression to park the RandomFloat01 result first loses
 * the hoist (482). The remaining float-block delta is the homed `fdivr [esp]`
 * vs the target's `fdivr [0x10025680]`: keeping fnum live across the divide and
 * homing it on the stack is structural to the hoist, and volatile/plain-alias
 * reads of the numerator do not move it (probes gvec_sh28/36, identical output).
 * Do not retry: parked `q14` quotient-last (482), split-expression (482),
 * parked gid locals in the neighbour loop (459/107 STUB: the four volatile
 * reads are load-bearing, one reload per store pair), plain-alias `pg` (107
 * STUB), strcpy/grave+9 reorder (479), 0x18/0x1c order swap (482).
 *
 * All six `~~` operands resolved against the original: the four calls are
 * gm_ResolveEntityById 0x10015e90, gv_CheckSlotActive 0x10010530, gv_GetSlotEntry
 * 0x100105b0 and LogMessageInternal 0x10003640; the two data slots are
 * 0x1003546c (g_entity_table_end) and 0x100a8c30 (g_entity_type_table).
 *
 * 2026-09-08 pass (484 -> 526, obj 1038 -> 1044): the `grave + 4` store
 * re-based onto the raw slot offset.  Holding `chosen * 0x21c` in an `off`
 * local and writing the store as `*(int*)((char*) 0x100358a4 + off) = -1`
 * keeps the offset register live across the block, so the reference's
 * `mov [edx+0x100358a4],eax` at 0x10011db9 comes out with the base folded
 * into the displacement, and the whole slot-init block re-aligns.  Same
 * address as `grave + 4`, so the change is behaviour-preserving.
 *
 * An earlier note recorded re-basing grave+4 as scoring 360.  That was
 * measured against the 393 body, before the counter-scope and neighbour-loop
 * fixes; re-measure a parked lever after the body around it changes.
 *
 * The second memset must NOT be re-based the same way: `grave + 0x5c` scores
 * 526, `(char*) 0x100358fc + off` 504, and the two together 504.  Also
 * measured and reverted on the 526 body: `g_slot_table` in place of the
 * 0x100358a0 literals (510-514; unlike cm_ExCopyEntityData, the literal form
 * here already yields the folded displacement), an `off`-killed second memset
 * 504, a rotated or do/while entry search 109, the p load sunk below the
 * count guard (inert), a byte-typed temp in the 5-byte copy (inert), store
 * reordering around grave+0x50 (inert), an int cast on the neighbour-loop id
 * reads (inert), a pre-store before the clear_entry memset (inert).
 * `return (short) *(volatile unsigned short*) grave` reaches obj 1039, one
 * byte under target, but scores 524; the extra `and eax,0xffff` it removes
 * costs more positionally than it saves.
 *
 * 2026-09-08 pass 2 (526 -> 537, obj unchanged at 1044): both slot scans
 * counted directly into `chosen` instead of into a block-scoped `int n` copied
 * out afterwards.  The reference keeps the scan counter in esi across both
 * loops; the block-local's short live range let msvc6 put it in edx, so every
 * `inc`, `cmp` and `xor` in the two scans took the wrong register.  Removing
 * the temp gives the reference's esi for all of them.
 *
 * The same lever does NOT apply to the entry search above: hoisting its `q`
 * out of the block scores 528, because `p` is live across the loop there and
 * the reference wants it reloaded.  Also measured on the 537 body and
 * reverted: the second memset re-based as `(char*) 0x100358fc + off` 504 (the
 * pre-existing note still holds after the counter fix), the citizen-count bump
 * read into a local before the two entity stores (inert), `one = 1` moved
 * above the slot-index store or above `grave + 2` (both inert), the count and
 * index loads reordered around `j = 0` (inert), declaration order of
 * j/count/job_id (inert).
 *
 * 2026-09-08 pass 3 (537 -> 541, obj 1044 -> 1050, target 1040):
 *   - `*(unsigned short*) grave = 0xffff` qualified volatile.  Without it
 *     msvc6 dead-store-eliminates the write, because the slot-index store to
 *     the same halfword follows a few statements later.  The reference keeps
 *     it (`mov word ptr [ebp],0xffff` at 0x10011db3), so it is one whole
 *     instruction the object was missing.  537 -> 538.
 *   - the object-id and citizen-count bumps read into `seq` and `live` locals
 *     before the two entity stores, with the writebacks after.  The reference
 *     loads g_citizen_count into edi and g_next_object_id into ecx ahead of the
 *     grave+0x170 / grave+0x16c pair and writes both back at the end
 *     (0x10011dd2-0x10011dff).  Reading them inline emitted a load-inc-store
 *     round trip per counter instead.  538 -> 541.  The narrower spelling
 *     with `live++` as a separate statement scores 538, so the initializer
 *     form (`int live = g_citizen_count + 1`) is the one to keep.
 *
 * The pass-2 note above records the counter bump as inert; that was measured
 * before the volatile 0xffff store existed.  The two are coupled: neither
 * moves the score alone.
 *
 * Residual: 10 bytes over target, still the `and eax,0xffff` zero-extend in
 * the neighbour loop (target `xor ecx,ecx; mov cx,[ebp]` at 4 bytes per read,
 * ours 7).  Re-probed on the 541 body and reverted: an `unsigned int id`
 * temp for the loop index reads (540), a half-word write through `&a` (539 at
 * obj 1057), two separate id reads one per store pair (540), the 1000.0
 * numerator inlined so the target's `mov [ebp+0x1c],0x447a0000` immediate
 * comes out (527 - the fnum hoist is worth more than the immediate), the
 * 0x18/0x1c stores hoisted above 0x20 (533), both grave sweeps and the
 * entry search converted to for-shape (all inert at 541, unlike
 * cm_ExProdObjekt they already emit the reference's back edge).
 *
 * 2026-09-08 pass 4 (541, nothing kept).  The CFLAGS sweep is a no-op here
 * too: /O2 and /Ox produce the identical 1050-byte object, /O1 and /Og are
 * far worse (111-112).  The zero-extend residual resists every C spelling
 * tried: an `unsigned int id` zeroed then half-word-assigned through
 * `*(unsigned short*)&id` grows the object to 1065 (540), and an
 * `unsigned short ga` temp for the first read plus a redundant cast on the
 * second reaches 1051 (541), so neither buys the reference's 4-byte
 * `xor ecx,ecx; mov cx,[ebp]`.  Also re-probed on the 541 body and reverted:
 * the worktype index hoisted into its own local ahead of the count load and
 * `j = 0` placed before the count load, both aimed at the still-open
 * ecx/edx role exchange at the entry search, both inert; the sweep tails
 * with the counter bumped before the pointer (inert, and the reference order
 * at 0x10011d49 is `add eax,0x21c` then `inc esi`); `off` computed above the
 * 0x100358a2 flag test (inert); a shared `neg = -1` local feeding the slot+4
 * store and the memset fill, chasing the reference's `or eax,0xffffffff`
 * ahead of the 0xffff store at 0x10011daf (inert); the second memset re-based
 * as `(char*) 0x100358fc + off` (501 at obj 1056, the pre-existing note still
 * holds); `fail_ffff` moved to a shared tail block after `clear_entry`
 * (inert, msvc6 duplicates the block per goto site).
 *
 * 2026-09-08 pass 5, two changes.
 *
 *   - The neighbour loop called `ahm_RandomBelow`, which is not a function in
 *     this binary: it resolves to the zero-returning stub in src/link_stubs.c.
 *     The reference calls gm_RandomMod at 0x1001a0d0 (db/server.dll_functions
 *     .csv, and the sibling gv_SpawnEntities.c in this directory reaches
 *     RELOC 370/370 with the same `int __cdecl gm_RandomMod(int)`
 *     declaration).  The emitted instruction bytes are unchanged - both names
 *     compile to the same `call rel32` with a zero addend - so the positional
 *     score reads 541 -> 533 only because the two call displacement slots at
 *     object offsets 844-847 and 880-883 stop being masked as local and start
 *     counting as reloc bytes.  near-diag moves 6 bytes from unclassified into
 *     reloc and leaves match/register/encoding identical.  This is a
 *     correctness fix: the old spelling linked against a stub.
 *   - The second random draw read into an `r` local with `iv` bumped between
 *     the call and its two stores.  The reference bumps both counters between
 *     `call gm_RandomMod` at 0x10011f5a and the `mov byte ptr [edi+...]` pair
 *     at 0x10011f75/f7b (`add esi,0x300` / `inc edx` at f68/f6e); writing the
 *     stores inline emitted them immediately after the call.  533 -> 538.
 *     Inert around it: an `r1` temp for the first draw as well, `iv` bumped
 *     before the `b` index, the `- 0x20` folded into the temp, an
 *     `unsigned char` temp.
 *
 * The `#pragma optimize` sweep does not transfer from cm_ExCopyEntityData:
 * "a",on craters to 265 here (the four volatile grave-id reads are exactly the
 * aliasing the pragma discards), "w",on 525, "p",on 532, "s",on and "t",off
 * 75, "g",off 102, "y",off 113, the rest inert.
 *
 * Residual at 538: 10 bytes over target, still the zero-extend form in the
 * neighbour loop (reference `xor ecx,ecx; mov cx,[ebp]` at 4 bytes per read,
 * ours `mov si,[ebp]; and esi,0xffff` at 7).  Re-probed on this body and
 * reverted: an `unsigned int` cast on the id read, the addends swapped, the
 * row index spelled `<< 8` times 3 and 3 times `<< 8`, and a pre-zeroed int
 * assigned through `*(unsigned short*)&x` both hoisted and in-loop (the last
 * grows the object to 1065).
 *
 * 2026-09-08 pass 6 (538 -> 603, obj 1050 -> exactly 1040, the target size).
 * Five changes, each measured:
 *   - The 1000.0 numerator is NOT hoisted.  The reference stores the constant
 *     as an immediate at grave+0x1c (`mov [ebp+0x1c],0x447a0000` at
 *     0x10011efe) and divides straight from memory with
 *     `fdivr [0x10025680]`; the `fnum` local emitted an ecx hoist plus a
 *     homed `fdivr [esp]` and cost 8 bytes.  Writing the divide inline and
 *     the 0x1c store as the raw int immediate, with the zero stores back in
 *     ascending 0x18/0x1c/0x20/0x24/0x28/0x2c order, closes the object from
 *     1050 to 1042 and brings the instruction count to the reference's 333.
 *     The pre-existing note recording the immediate form as 527 was measured
 *     against the 541 body, where the hoist was still load-bearing.
 *   - The second strcpy's source reloaded through a volatile alias
 *     (`(char*) *(void* volatile*) &entry + 0x14`).  The reference reloads
 *     `entry` from [esp+0x10] for the second copy (0x10011ecb) where msvc6
 *     kept it in edx across both; the reload re-aligns the whole strcpy pair
 *     and the tail behind it.  524 -> 578, and register bytes fall 9.8% to
 *     4.2%.  The alias must be on the SECOND copy only: on the first it is
 *     497, on the grave+9 read 497, and qualifying the whole `entry`
 *     declaration volatile is 114.
 *   - `return (short) *(volatile unsigned short*) grave`.  The reference's
 *     closing `mov ax,word ptr [ebp]` leaves the high half of eax alone, so
 *     the value is returned as a short, not zero-extended; the int form drags
 *     an `and eax,0xffff` into the epilogue.  578 -> 598 at obj exactly 1040.
 *     The earlier note scoring this 524 was measured on the 526 body.
 *   - The slot+4 `-1` store moved above the volatile 0xffff store, matching
 *     the reference's `or eax,0xffffffff` ahead of `mov word ptr [ebp],0xffff`
 *     at 0x10011dc0.  598 -> 600.
 *   - The neighbour loop's column counter read once into a block-local `col`
 *     instead of twice from the volatile `iv`.  The reference loads
 *     [esp+0x1c] once per iteration; two reads emitted two loads.  600 -> 603.
 *     Feeding the increment from `col` as well regresses to 498 at obj 1036,
 *     so the writeback stays `iv = iv + 1`.
 *
 * Residual at 603: the object is exactly the target size and the instruction
 * count matches, so the remaining delta is placement and register naming, not
 * missing code.  The zero-extend form in the neighbour loop is unchanged
 * (reference `xor ecx,ecx; mov cx,[ebp]` at 4 bytes per read, ours `mov
 * si,[ebp]; and esi,0xffff` at 7).  Measured on the 603 body and reverted:
 * the second memset re-based as `(char*) 0x100358fc + off` 485 and as
 * `(char*) 0x100358a0 + off + 0x5c` 487 (both still hold after the size fix),
 * the g_next_object_id read sunk below the two entity stores 598, `one = 1` moved
 * out of the counter block (inert), volatile on the grave+0x218 store 594 and
 * on grave+0xd 595, a shared `neg = -1` local feeding the slot+4 store, the
 * memset fill and the 0x210/0x18c/0x20c stores (inert at 538), volatile on
 * the grave+0x10 store 522, and volatile on the req+0x15 read 514.
 *
 * 2026-09-08 pass 7 (603 -> 606, obj stays exactly 1040).  The grave+0x10
 * zero store hoisted above both strcpy calls instead of sitting between them
 * and the float expression.  msvc6 was sinking it into the second copy's
 * register shuffle (`mov [ebp+0x10],ebx` at 0x2ec, between `mov edi,edx` and
 * `shr ecx,2`); with the statement above the copies the shuffle is clean and
 * the reference's own placement at 0x10011eed follows.  Pinning it in the
 * original position with volatile instead scores 604, so the move is the
 * lever, not the qualifier.
 *
 * Levers ported from ahm_ExAllocAlchemist's passes 5 and 6 that do NOT
 * transfer here, each measured on the 606 body: the volatile-pointer reload
 * (`*(void* volatile*) &x`) applied to `req` for the +0x15 byte read 480, to
 * `entry` for the grave+9 read 494, and to `p` for the entry-search walk 337;
 * a `dst2` local for the second strcpy destination, chasing the reference's
 * early `lea edx,[ebp+0x40]` at 0x2ca, 496; the neighbour loop's two grave-id
 * reads through a plain `unsigned short gid` local in the alchemist's grid
 * shape 499 at obj 1041 (the four volatile reads stay load-bearing).  Also
 * inert on this body: the entry-search bound written `count > j` 605,
 * declaring `count` before `j`, the `p` load sunk below the count guard, the
 * `off` multiply hoisted above the 0x100358a2 flag test, the second grid
 * index written `col + gid * 0x300`, the fail return cast through
 * `(int)(unsigned short)`, and a `src` local for the 5-byte copy source.
 * The tail's `movsx eax,word ptr [ebp]` against the reference's `mov ax`
 * is an encoding difference of equal length: assigning through
 * `*(unsigned short*) &rv` on a plain int grows the object to 1049 (583).
 *
 * 2026-09-08 pass 8 (606, nothing kept).  The compile result classifies as
 * STUB rather than NEAR_MATCHING purely on the 60% threshold in
 * rebrew/compile.py: 606/1040 is 58.3%, so the function needs 18 more
 * positional bytes (or 6 more once the classifier's 4-byte relocation
 * windows are masked) to cross.  The stored metadata status is PROVEN and
 * cannot be demoted by this - metadata.should_promote_status makes PROVEN
 * sticky against everything except a real EXACT/RELOC byte match - so the
 * STUB in `rebrew verify` output is the freshly computed compile
 * classification, not a stored regression.  `rebrew prove` refuses to run
 * for the same reason: its gate requires NEAR_MATCHING or SIZE_MISMATCH and
 * rejects an already-PROVEN function as adding no information.
 *
 * The remaining deficit is three phase shifts, each confirmed
 * instruction-for-instruction identical to the reference and displaced only
 * by msvc6's scheduler:
 *   - the strcpy pair (run of 61 bytes at 0x2ee): the reference hoists
 *     `lea edx,[ebp+0x40]` into the FIRST copy at 0x2ca, ours emits it after
 *     the second copy's `sub edi,ecx`.  Probed and reverted: `d1`/`d2`
 *     destination locals ahead of both copies (494), an `s2` source local
 *     for the reloaded pointer (inert), the grave+0x10 store placed before
 *     the copies, between them, and after the grave+9 read (all 606 - the
 *     scheduler moves it regardless of source position).
 *   - the 5-byte fill block (run of 46 at 0x296) is identical to the
 *     reference and shifted 6 bytes by the strcpy region above it.
 *   - the field-init block (run of 24 at 0x212): source order already
 *     matches the reference (0x1f0 then 0x210), so the early
 *     grave+0x218 / grave+0xd stores are scheduler placement.  `one = 1`
 *     moved down to just above the 0x218 store is inert.
 *
 * Also measured this pass and reverted: the return type changed to
 * `unsigned short` so the tail keeps `mov ax` (125 at obj 1015 - the
 * negative early returns truncate, and the caller cm_ExAllocGraveyardWorker
 * only compares the low half against 0xffff, so the type is defensible but
 * the codegen is not); four further return spellings (`volatile short`
 * deref, a `short` temp, a double cast, an int temp) all tie at 606, an
 * `unsigned short` temp is 584.  The second rescan loop as a do/while 540,
 * its `entry` field re-read per iteration 525, hoisted into a `want` local
 * (inert), the slot+4/entry compare operands swapped 605, the worktype index
 * hoisted (inert).  Four neighbour-loop index spellings (operand swap,
 * `unsigned int`, `|` instead of `+`, an explicit unsigned cast) are all
 * inert.  The `0x21c` stride split as `chosen * 3 * 0xb4` to route the lea
 * chain through a second register is inert.  A CFLAGS sweep (/O2, /Ox,
 * /O2 /Gy, /Ox /Ob0, /O2 /Gf, /Oxt, all with /Gd) produces the identical
 * 1040-byte object, and the `#pragma optimize` sweep that gained 11 bytes on
 * cm_ExCopyEntityData does not transfer: "a",on craters to 245, "s",on to
 * 76, and "w"/"p"/"q"/"g"/"y"/"t" on plus "a"/"w"/"p"/"q" off are all
 * inert. */

// FUNCTION: SERVER 0x10011bf0

#include "rebrew_types.h"
#include "rebrew_globals.h"
extern unsigned short* g_entity_table_end; /* 0x1003546c */
extern int g_citizen_count;
extern int g_next_object_id;
extern int g_worker_entry_count[];
extern char g_relationship_matrix_primary[];
extern char g_relationship_matrix_secondary[];
extern int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
extern int __cdecl gv_CheckSlotActive(void* worker, int worktype);
extern void* __cdecl gv_GetSlotEntry(void* worker, int worktype, unsigned char job);
extern int __cdecl gm_RandomMod(int n);
extern float __cdecl gm_RandomFloat01(void);
extern void __cdecl LogMessageInternal(char* module, unsigned int line, char* msg, int severity);
extern void* __cdecl memset(void* dest, int c, unsigned int size);
extern char* __cdecl strcpy(char* dest, const char* src);

int __cdecl gv_ExAllocGraveyardWorker(void* req)
{
	void* entry;
	void* entity;
	void* slot;
	void* workers;
	void* p;
	int gv;
	char* grave;
	int chosen;
	int j;
	int count;
	int job_id;
	unsigned char field_id;
	int one;
	int neg;
	int off;

	if (*(int*) ((char*) req + 0x15) != 0x1b && *(int*) ((char*) req + 0x15) != 0x1c)
		return -6;
	gm_ResolveEntityById(&entity, 0, 0, *(int*) ((char*) req + 8));
	if (!entity ||
	    *(unsigned short*) ((char*) entity + 0x27) == 0xffff ||
	    (char*) 0x100358a0 + *(unsigned short*) ((char*) entity + 0x27) * 0x21c == (char*) g_entity_table_end)
		return -1;
	field_id = *(unsigned char*) entity;
	if (g_entity_type_table[field_id + field_id * 588] != 0x1d)
		return -2;
	workers = *(void**) ((char*) entity + 0x65);
	if (!workers)
		return -3;
	if (!gv_CheckSlotActive(workers, *(int*) ((char*) req + 0xc)))
		return -4;
	slot = gv_GetSlotEntry(workers, *(int*) ((char*) req + 0xc), *(unsigned char*) ((char*) req + 0x10));
	if (!slot)
		return 0xffff;
	p = *(void**) ((char*) slot + 0x10);
	count = g_worker_entry_count[*(int*) ((char*) req + 0xc)];
	j = 0;
	if (count <= j)
		goto fail_ffff;
	job_id = *(int*) ((char*) req + 0x11);
	{
		char* q = (char*) p;
		for (; j < count; j++, q = q + 0x44) {
			entry = q;
			if (*(int*) q == job_id)
				break;
		}
		p = q;
	}
	if (!entry || *(int*) entry != job_id)
		goto fail_ffff;
	chosen = 0;
	gv = 0x100358a0;
	while (gv < 0x1009aca0) {
		if (*(unsigned short*) gv == 0xffff)
			break;
		gv += 0x21c;
		chosen++;
	}
	if (chosen == 0x300) {
		chosen = 0;
		gv = 0x100358a2;
		while (gv < 0x1009aca2) {
			if (*(unsigned char*) gv == 0xf)
				break;
			gv += 0x21c;
			chosen++;
		}
		if (chosen == 0x300) {
			LogMessageInternal((char*) 0x1002d48c, 0x6ef, (char*) 0x1002d4bc, 1);
fail_ffff:
			return 0xffff;
		}
	}
	if (*(unsigned char*) ((char*) 0x100358a2 + chosen * 0x21c) == 0xf)
		g_citizen_count--;
	off = chosen * 0x21c;
	grave = (char*) 0x100358a0 + off;
	memset(grave, 0, 0x21c);
	/* volatile: the slot-index store below writes the same halfword, so
	 * without the qualifier msvc6 drops this write and the object loses the
	 * reference's `mov word ptr [ebp],0xffff` at 0x10011db3. */
	neg = -1;
	*(int*) ((char*) 0x100358a4 + off) = neg;
	*(volatile unsigned short*) grave = 0xffff;
	memset(grave + 0x5c, neg, 32);
	/* Both counters are read before the entity stores and written back after,
	 * matching the reference's edi/ecx traffic at 0x10011dd2-0x10011dff.
	 * Bumping them in place emits a load-inc-store round trip each. */
	{
		int live = g_citizen_count + 1;
		int seq = g_next_object_id;
		*(int*) (grave + 0x170) = (int) entity;
		*(int*) (grave + 0x16c) = (int) entity;
		*(int*) (grave + 4) = seq;
		g_next_object_id = seq + 1;
		one = 1;
		*(volatile unsigned short*) grave = (unsigned short) chosen;
		g_citizen_count = live;
	}
	*(unsigned char*) (grave + 2) = 0x14;
	*(int*) (grave + 0x1f0) = 0;
	*(int*) (grave + 0x210) = -1;
	*(unsigned char*) (grave + 0x215) = 0;
	*(unsigned char*) (grave + 0x216) = 0;
	*(unsigned char*) (grave + 0x217) = 0;
	*(unsigned char*) (grave + 0x218) = (unsigned char) one;
	*(int*) (grave + 0x1e4) = 0x3f800000; /* 1.0f */
	*(unsigned char*) (grave + 8) = 0x64;
	*(unsigned short*) (grave + 0xa) = 0x10;
	*(unsigned char*) (grave + 0x164) = 0;
	*(unsigned char*) (grave + 0x166) = 0;
	*(unsigned char*) (grave + 0x165) = *(unsigned char*) ((char*) req + 0x15);
	*(unsigned char*) (grave + 0x1f4) = 0;
	*(int*) (grave + 0x190) = 4;
	*(int*) (grave + 0x194) = 0;
	*(unsigned char*) (grave + 0xd) = (unsigned char) one;
	*(int*) (grave + 0x18c) = -1;
	*(int*) (grave + 0x20c) = -1;
	*(unsigned short*) (grave + 0x50) = 0x7fff;
	{
		int n;
		for (n = 0; n < 5; n++)
			*(unsigned char*) (grave + 0x80 + n) = *(unsigned char*) ((char*) entry + 0x24 + n) >> 1;
	}
	*(unsigned char*) (grave + 9) = *(unsigned char*) ((char*) entry + 0x38);
	*(int*) (grave + 0x10) = 0;
	strcpy((char*) grave + 0x30, (char*) entry + 4);
	strcpy((char*) grave + 0x40, (char*) *(void* volatile*) &entry + 0x14);
	*(float*) (grave + 0x14) =
	    *(float*) 0x10025680 / (gm_RandomFloat01() * *(float*) 0x100257c8 + *(float*) 0x100257c4);
	*(int*) (grave + 0x18) = 0;
	*(int*) (grave + 0x1c) = 0x447a0000; /* 1000.0f */
	*(int*) (grave + 0x20) = 0;
	*(int*) (grave + 0x24) = 0;
	*(unsigned short*) (grave + 0x28) = 0;
	*(int*) (grave + 0x2c) = 0;
	{
		int n;
		volatile int iv;
		iv = 0;
		for (n = 0; n < 0x90000; n += 0x300) {
			int a = n + *(volatile unsigned short*) grave;
			int b;
			int r;
			int col;
			r = gm_RandomMod(0x40);
			g_relationship_matrix_secondary[a] = 0;
			g_relationship_matrix_primary[a] = (unsigned char) r - 0x20;
			col = iv;
			b = *(volatile unsigned short*) grave * 0x300 + col;
			/* The counter bump sits between the call and its stores to
			 * match the reference's `add esi,0x300` / `inc edx` at
			 * 0x10011f68, ahead of the store pair at 0x10011f75. */
			r = gm_RandomMod(0x40);
			iv = iv + 1;
			g_relationship_matrix_primary[b] = (unsigned char) r - 0x20;
			g_relationship_matrix_secondary[b] = 0;
		}
	}
	if (*(int*) entry == *(int*) ((char*) slot + 4)) {
		int n;
		count = g_worker_entry_count[*(int*) ((char*) req + 0xc)];
		if (count > 0) {
			p = *(void**) ((char*) slot + 0x10);
			for (n = 0; n < count; n++, p = (char*) p + 0x44) {
				if (*(int*) p == -1)
					continue;
				if (*(int*) p != *(int*) entry) {
					*(int*) ((char*) slot + 4) = *(int*) p;
					goto clear_entry;
				}
			}
		}
		*(int*) ((char*) slot + 4) = -1;
		*(unsigned short*) ((char*) slot + 8) = 0xffff;
	}
clear_entry:
	memset(entry, 0, 0x44);
	*(int*) entry = -1;
	return (short) *(volatile unsigned short*) grave;
}
