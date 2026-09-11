/* gm_RefreshMarketAvailability — refreshes the market item availability. */

// FUNCTION: SERVER 0x10015f70

#include "../../../Units/Error/error.h"

#include <stddef.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

extern int g_active_player_count; /* 0x1003543c */
extern unsigned char g_current_season; /* 0x10035439 */

void* __cdecl gm_FindNextFilteredEntity(void);
void* __cdecl gm_NextEntityQueryMatch(void);
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);


/* Rebuilds the market slots for the given season: seeds the slot table
 * from the market object list, marks matching item definitions as
 * available, allocates missing objects and tracks per-item counts.
 *
 * SIZE_MISMATCH at byte level (obj 718 vs target 720), 306/718 matched,
 * up from 85. Five fixes, in the order they were found:
 *
 *   - `g_slot_array` is the array symbol, not a pointer to it. The target
 *     does `add esi, g_slot_array` (0x10016004); reading it as `char*`
 *     emitted a `mov` load of its first four bytes, so slot_base pointed
 *     at whatever those bytes held and every later slot access was wrong.
 *     Taking `(char*) &g_slot_array` fixed the base. 189 -> 283.
 *   - the id list was split as `local_20` plus `local_1c[7]`. MSVC6 kept
 *     only the first store and dead-stored the rest, giving a 0x8 frame
 *     against the target's 0x28. One `unsigned int ids[9]` restores all
 *     eight stores and the frame size. 85 -> 186, then 189 with the
 *     ninth element that matches `sub esp,0x28` exactly.
 *   - the target's list starts at [esp+0x18], one slot above the frame
 *     base, so the stores live in ids[1..8] and the walk starts at
 *     &ids[1]. 283 -> 291.
 *   - the item-def base is loop-invariant and the target hoists it out of
 *     the 0x55 outer loop (0x100160cb-0x100160dd computes it once, then
 *     `lea ecx,[eax+0x2e]` reloads only the 4-entry cursor per iteration).
 *     Recomputing it inside the loop cost 13 bytes. Hoisting it into the
 *     otherwise-dead ids[8] slot also fixes the register rotation: slot_base
 *     moves ebx -> esi and pb/q take edi/ebx, matching the target's prologue
 *     `push esi` and every `add esi, g_slot_array` role. 291 -> 298.
 *     A plain `char*`/`int*` local for the same hoist scores 299 at 714 bytes
 *     (msvc6 keeps it in a register and drops a frame slot); the ids[8]
 *     spelling is what pins the spill the target has.
 *   - the eight id stores then sit one slot high, so they move back to
 *     ids[0..7] with the walk starting at &ids[0]. All eight store offsets
 *     go exact. 298 -> 306.
 *
 *   - the 0x55 counter's increment written as a volatile READ plus a plain
 *     store, `season = *(volatile int*) &season + 1`. That is the section 14
 *     residency lever: the read pins the counter in the [esp+0x40] frame
 *     slot the way the target pins it at [esp+0x3c], without the ordering a
 *     volatile store imposes. The `mov [esp+0x40],0` initialiser and the
 *     `mov eax,[esp+0x40]; inc eax` load/inc pair then match the target's
 *     0x10016082 and 0x1001610f-0x10016113, and the compile grows from 718
 *     to 721, one byte over the target's 720. 306 -> 329. Making the
 *     *condition* volatile as well pins the compare too but costs 16 bytes
 *     (737) and drops the score to 218.
 *   - `pv` was declared and never used; removed, inert at 329.
 *
 * Residual: 1-byte overshoot (721 vs 720). The counter now lives in memory
 * but msvc6 still rotates the loop so the test sits at the bottom
 * (`cmp eax,0x55; jl`) where the target tests at the top through memory
 * (`cmp dword ptr [esp+0x3c],0x55; jge`) with a bare `jmp` back edge, and
 * the two spill slots [esp+0x10]/[esp+0x14] are swapped against the target.
 *
 * Loop rotation was attacked again and is not steerable from source here:
 * rewriting the 0x55 walk as `for (;;)` with an `if (season >= 0x55) break;`
 * at the top emits the identical 721 bytes and the identical 331, so msvc6
 * re-rotates it regardless of how the exit test is spelled. Making the
 * condition volatile does pin the compare in memory the way the target has
 * it, but costs 16 bytes (737) at 218 with the plain increment and 220 with
 * the volatile-read increment, so the memory compare is not worth its size.
 *
 * The 1-byte overshoot is the ids[9] frame slot: the target's frame is 0x28
 * and ours 0x2c. Spending that slot on a plain `char* defbase` for the
 * item-def hoist instead of ids[8] does reach 717 bytes, but the register
 * rotation it brings back caps it at 312, below the 331 kept here; splitting
 * the same hoist into a `* 0x40` plus index step to chase the target's
 * base/index roles is inert at 312. Reshaping the inner match loop was also
 * inert at 331: `do/while` counters in place of the `for` pair, swapping the
 * compare operand order to `def == base`, and introducing an `unsigned short
 * cmpv` temp for the target's `bp` value.
 *
 * Dead ends, with the score each produced: a `volatile` read of q at the
 * inner query call, to force the target's [esp+0x10] spill, 291 -> 214;
 * declaring slot_base before ids 291; reusing the dead `season` parameter
 * slot for the 0x55 counter 291; hoisting `season = 0` above the q null
 * test, and establishing slot before season, both 291; establishing
 * slot_base before `cur = g_current_season` 291; hoisting pb's entity id
 * into its own local to shorten pb's live range (section 9a) 291 -> 289.
 * On top of the 306 body: shrinking ids to [8] and holding the hoisted base
 * in `cur` 303 at 714; the same in a `pv` pointer local 299 at 714; indexing
 * `slot = slot_base + season * 0x80` instead of the += walk, inert at 306.
 *
 * The 0x55 counter's form was the blocker, and the volatile-read increment
 * above is what moved it.  The target loads, tests, increments and stores it
 * through [esp+0x3c] on every iteration, an opaque-memory counter; every
 * earlier spelling left msvc6 free to reverse it into a register
 * down-counter, or spilled far more than the target.  Measured on the 306
 * body before that fix, all reverted: `pv = &season` with the loop reading
 * and writing `*pv` (inert at 306, msvc6 forwards through the alias);
 * `*(volatile int*)&season` on the store, condition and increment together
 * (228 at 737); volatile on the condition read alone (218 at 737); a `for (;
 * season < 0x55; season++)` rewrite of the same walk (inert at 306); a
 * dedicated `i` counter local instead of reusing the `season` parameter
 * (inert at 306); establishing slot_base before `cur = g_current_season` to
 * move the [esp+8] spill past the compare (inert at 306).
 *
 * Measured on top of the 329 body, all reverted: volatile on the condition
 * as well as the increment (220 at 737); a `goto`-based rewrite with the
 * test at the top and an unconditional back edge, aiming at the target's
 * `jmp` (inert at 329, msvc6 rotates it back); a dedicated `k` counter local
 * instead of the `season` parameter slot (inert at 329); declaring
 * `slot_base` after `q`, to swap the [esp+0x10]/[esp+0x14] spill pair (inert
 * at 329, in both declaration positions tried); shrinking `ids` to [8] with
 * the hoisted item-def base in the dead `cur` local, which reaches 717 bytes
 * and 78 exact instructions but only 312 matched; `season++` with a bare
 * `*(volatile int*)&season;` read after it (318 at 722); hoisting `base =
 * slot_base` above the item-def computation (inert at 329).
 *
 * Shrinking `ids` to [8] with the hoisted item-def base in a plain `char*`
 * local reaches the target's `sub esp,0x28` frame and its exact 714-byte
 * size, and the prologue then matches through instruction 37, but it scores
 * lower on the positional byte compare: 303 at 714 against 306 at 718, and
 * `rebrew diff` exact-match instructions fall 73 -> 61.  The size win does
 * not pay for the body.  Kept at ids[9]/718 for the higher score.
 * (The STUB that `rebrew test` prints for the 714 variant is only a report:
 * PROVEN is sticky in metadata, promoted only by EXACT/RELOC, so it is a
 * score signal and not a demotion.)
 *
 * On top of that 714-byte ids[8] variant, measured and all reverted with it:
 * moving `slot = slot_base` above `season = 0` scores 304 (the target's
 * `mov edi,esi` then precedes the `je`, but the counter form does not
 * change); `pv = &season` with the loop reading and writing `*pv` inert at
 * 304; a `for (; season < 0x55; season++, slot += 0x80)` rewrite inert at
 * 303; indexing `slot = slot_base + season * 0x80` inside the loop inert at
 * 303; reordering the local declarations to put `q` before `slot_base`,
 * aiming at the target's [esp+8]/[esp+0x10] spill pair against our
 * [esp+4]/[esp+0x14], inert at 303.
 *
 * Those ids[8] measurements predate the volatile-read counter; with it the
 * same shrink scores 312 at 717, still below the 329 kept here.
 *
 * Now at 341/721 with the counter's increment written as a volatile STORE,
 * `*(volatile int*) &season = season + 1`, in place of the volatile read.
 * The read form pins only residency; the store also orders the write against
 * the surrounding accesses, which is what stops msvc6 from sinking the
 * counter into a register across the inner match loop.  With it the whole
 * inner loop body (diff instructions 80-114, the query call, the item-def
 * hoist and both nested walks) emits the target's exact instructions, merely
 * shifted by the two-instruction rotation at the loop head.
 *
 * The loop rotation is the entire residue: the target tests at the top
 * through memory (`cmp [esp+0x3c],0x55; jge`) with a bare `jmp` back edge,
 * ours tests at the bottom (`cmp eax,0x55; jl`).  Measured on the 341 body
 * and reverted: volatile on the condition read, which does pin the memory
 * compare but costs 12 bytes (221 at 733); volatile on the loop's zero
 * initialiser (330 at 721); a plain `*(int*) &season` alias in the condition
 * (inert at 341); a `for (;;)` with `if (season >= 0x55) break;` at the top
 * (inert at 341, msvc6 re-rotates); volatile read AND store on the increment
 * together (inert at 341).
 *
 * Also measured on the 714-byte ids[8]/defbase body, which does reach the
 * target's `sub esp,0x28` frame and its exact size with instructions 0-37
 * exact (76 exact-match instructions against 62 at ids[9]): 310 with the
 * plain increment, 299 with the volatile-store increment, and moving `q`
 * above `slot_base` in the declarations inert at 310.  The frame is right
 * but the positional score is 31 below the 341 kept here, because the
 * [esp+8]/[esp+4] spill-slot swap at instruction 38 shifts everything after
 * it.  Closing this function needs the 714-byte frame AND the spill pair,
 * not either alone.
 *
 * Measured again on the 341 body and reverted, all with their scores: the
 * loop's zero initialiser written as a volatile store, 330 at 721; the
 * increment as a volatile READ plus plain store, 310 at 717; a `for (;;)`
 * with `if (*(volatile int*)&season >= 0x55) break;` at the top, 221 at 733;
 * a plain `int* pv = &season` alias in the condition, inert; splitting the
 * increment into a temp stored after `slot += 0x80` to match the target's
 * load/inc/advance/store tail order, 335 (the temp reused the live `cur`);
 * declaring `q` before `slot_base` to swap the [esp+8]/[esp+4] pair, inert.
 *
 * The item-def match block's five locals (`defbase`, `base`, `def`, `outer`,
 * `inner`) were narrowed from function scope to the block that uses them.
 * Inert at 341, kept because it is the correct scope and the whole block
 * already emits the target's instructions.
 *
 * Later pass, no movement: still 341 at obj 721.  Dead ends measured and
 * reverted, with their scores:
 *   - the loop's zero initialiser as a volatile store, 330; the increment
 *     split so `slot += 0x80` lands between the `inc` and the volatile store,
 *     to reach the target's 0x10016113-0x1001611a order, 335.
 *   - a volatile read in the loop condition, which does pin the memory compare
 *     the target has at 0x10016092 but costs 12 bytes, 221 at obj 733.  This
 *     re-confirms the entry above.
 *   - the 0x55 walk's `slot` narrowed to a `cs` local declared inside the
 *     `q != 0` block, the loop-scope lever from ls_LoadGraveyardData: inert.
 *     `slot` is genuinely shared with the two later 0x55 loops, so narrowing
 *     it here does not shorten any live range msvc6 cares about.
 *   - the counter moved off the `season` parameter slot onto the dead `cur`
 *     local, to give back the frame byte, inert.
 *   - a `base2` copy of `slot_base` taken at the `q != 0` entry and used by
 *     the match block, aimed at the [esp+0x10]/[esp+0x14] spill swap, inert;
 *     declaring `def` before `base` to swap their induction roles, inert;
 *     an `idp` pointer for the final ids walk so `q` dies earlier, inert;
 *     a `cur = season` copy as the first statement, inert; a volatile
 *     self-store on `slot_base`, inert; the pb entity-id read narrowed into
 *     its own block-scope local, inert.
 *   - `ids` shrunk to [7] with the eighth store dropped, 138 at obj 713, and
 *     grown back to [9], 97 at obj 712.  The [8] spelling remains the only one
 *     that keeps the eight store offsets and the counter form together.
 *
 * The residue is unchanged and is two coupled facts: the 1-byte frame
 * overshoot (0x2c against the target's 0x28) and the loop rotation at
 * 0x10016092.  Every spelling that gives back the byte loses the register
 * rotation that the volatile-store counter buys, and every spelling that pins
 * the memory compare costs 12 or more bytes.
 *
 * This session, 341/721 -> 386/720: folding the `q != 0` guard into the
 * 0x55 loop condition (`while (q != 0 && season < 0x55)`) emits the target's
 * top-tested memory-compare loop (cmp [esp+0x3c],0x55; jge) with the bare
 * `jmp` back edge, and reading the slot word once into the existing `id`
 * local (`id = *(unsigned short*) slot; if (id != 0) ... (…, id)`) emits the
 * target's `xor eax,eax; mov ax,[esi]; test eax,eax` + widened push. Both
 * together fix the size to exactly 720. The item-def hoist still splits the
 * roles (def-cursor eax vs target ecx, row/base edx vs target esi) and the
 * [esp+0x10]/[esp+0x14] spill pair is still swapped; ~25 isolated probes of
 * the hoist (offset temps, row counters, end-pointer bounds, byte-compare
 * rewrites) all keep our roles.
 *
 * Follow-up session, 386 -> 445/713. Three structural fixes from reading the
 * target rather than the candidate:
 *   - the final ids walk was MISCOMPILED, not just misaligned: `id = q[1]`
 *     over the int array folds (q[1] of just-stored 0x92 is constant 0), so
 *     msvc6 proved a single iteration and dead-stored ids[1..7] (only the
 *     0x92 store survived). `id = ((int*) q)[0]; q = (ushort*) ((int*) q + 1)`
 *     reads dwords and keeps all eight stores; the walk now queries
 *     92,92,93..0x2db like the target (its bottom is still [edi] vs [edi+4]).
 *   - the second 0x55 loop checked the wrong guard: source tested the 0xff
 *     query result, the target tests *(slot+4) (`mov eax,[esi+4]` before the
 *     `add esp,0x10` cleanup, then `test eax; je`) and dereferences the 0xff
 *     result unchecked. `if (*(slot+4) != 0)` matches the target's order.
 *   - the 0x55 loop head uses a ushort `w` (`mov ax; test ax; je; and` now
 *     exact at 80-83) with a separate `w = *(slot)` re-read feeding a
 *     `defbase = table + w*0x41` hoist before `base = slot_base`, which gives
 *     the target's `xor; mov [edi+4],1; mov ax` at 93-95. Moving the `q != 0`
 *     test outside (`if (q != 0) { slot = slot_base; while (q != 0 && ...) }`)
 *     puts `mov edi,esi` after the `je` like the target; the redundant inner
 *     q check is folded by msvc6. The counter tail is split across the slot
 *     advance (`cur = season + 1; slot += 0x80; *(volatile)&season = cur`)
 *     to approach the target's inc/advance/store order (same score, closer).
 * Measured and reverted: deref-into-mbase / w3-temp / dderef-temp / mbase-in-
 * args spellings of the second-loop head (324-387, the (g,word) register pair
 * is stuck at eax,ecx with loads-first and splits with temps); row-before-
 * base / row-first / count-up-indexed-base / i-and-count-counter-reuse
 * spellings of the match block (304-441, row stays esi and base stays ecx);
 * dropping `cur`+`mbase` (401, spill unchanged); declaring q before
 * slot_base, match locals at function scope (both inert at 439-445). The
 * [esp+8]/[esp+4] slot_base spill (one frame slot below the target, with the
 * q/slot spill pair swapped as the same fact) never moved under any of these.
 * The `~~` operands are the known globals (slot array, season, entity-type
 * table, item-def table, g_active_player_count) and the two query/alloc
 * callees; no string or call-target invented.
 *
 * This session, 445 -> 557/713 (+112). Two fixes:
 *   - the item-def match block rewritten as an upward `for (inner = 0;
 *     inner < 4; inner++)` with `def = defbase + 0x2e + inner * 2` inside.
 *     The downward form kept a stale def cursor alive across the row loop
 *     and blocked the defbase+base strength reduction; the upward form lets
 *     msvc6 fold the hoist (`mov edx,[table]; mov ecx,eax; mov ebx,0x55;
 *     shl ecx,6; add edx,ecx; add eax,edx; mov edx,esi;
 *     lea ecx,[eax+0x2e]; mov esi,4; mov bp,[edx]; cmp bp,[ecx]`) exactly.
 *     445 -> 466. Same +21 measured standalone.
 *   - the second 0x55 loop's id hoisted into a block-scope `int w3`
 *     (`w3 = *(slot+0x3c)` ahead of the call), which yields the target's
 *     `mov ecx,[mbase]; xor eax,eax; mov ax,[esi+0x3c]; mov edx,[ecx+0x5d];
 *     push eax; push 0; push 1; push edx` head. 466 -> 557.
 *   - `q = &ids[1]` for the final walk (target reads [edi+4] first) is
 *     score-neutral at 466-557 (kept: it matches the target's first read).
 * Checksum: instructions 95-114 (the whole match block) now exact; the
 * whole second 0x55 loop and final walk exact except `~~` call/jump slots.
 * Residue: q/slot in edi/ebx vs target ebx/edi (block-scope `qb`/`qq`
 * copies of q inert), [esp+8]/[esp+4] slot_base spill one slot low, and the
 * counter tail (`add edi,0x80` before the counter reload vs target's
 * `inc ecx; add edi,0x80; mov [esp+0x3c],ecx`). All `~~` are the known
 * globals and query/alloc callees.
 *
 * This session, file 557/713 -> 652/714 (probe 680/720; the test harness
 * strips trailing 0x90 padding so obj reads 714, and scores the common
 * prefix: 660 probe == 652 test on the same bytes). Kept, all
 * semantics-preserving except the query-C filter noted below:
 *   - clear loop and second 0x55 loop counters moved from `i` to `count`
 *     and `i` dropped: the dead counter's spill slot was what kept
 *     slot_base one frame slot low (`mov [esp+4],esi` vs target
 *     `mov [esp+8],esi`). 568 -> 611 in probe.
 *   - match-block establishment order to base, row, defbase (was
 *     defbase, base, row): puts the row counter in esi and the def
 *     cursor in ecx/edi closer to the target's ebx/esi/ecx triple.
 *     568 -> 608 standalone, 611 -> 613 combined.
 *   - 0x55 counter tail simplified to `*(volatile int*) &season =
 *     season + 1; slot += 0x80;` (was via `cur` temp) and `cur` dropped
 *     for a direct `season == g_current_season` compare: two dead locals
 *     removed, no frame change, tail order closer to target.
 *   - second-loop `w3`/`mbase` read order swapped (word before dword).
 *   - final-walk `q = ids` (was `&ids[1]`), advance-then-read bottom
 *     (`q = (int*)q + 1; id = q[0]`, matching target `mov eax,[edi+4]`),
 *     and `slot = slot_base` established before the pb+0x5d query
 *     instead of inside `if (q)`.
 *   - query-C filter corrected from `count` (0 at that point) to literal
 *     5: the target pushes (edx, 1, 5) at 0x100161e9-0x100161f1, verified
 *     in original/server.exe bytes (`8b 50 14 6a 05 6a 01 52` at file
 *     offset 0x16279). The old value queried filter 0 where the binary
 *     queries filter 5, so this is a genuine bug fix; the query sequence
 *     92..2db is unchanged. 613 -> 663 in probe.
 * Residue (21 `**`): the q/slot ebx/edi swap and slot_base spill slot
 * (unchanged: declaration order, hoist positions, extra-copy and cursor
 * splits all inert; the spill costs 1 cascade byte), the match-block row
 * role (esi vs ebx; up/down/indexed/derived-def and decl-order variants
 * all keep our roles), and the counter-tail order. `~~` audit: calls are
 * gm_StartFilteredEntitySearch/gm_StartEntityQuery/gm_AllocObjekt/
 * gm_FindNextFilteredEntity/LogMessageInternal; globals are
 * g_active_player_count, g_current_season, g_slot_array,
 * g_entity_type_table, g_item_def_table; the two message pointers read
 * as 0x1003122c "gm_ObjectsAvailble(): Kein Markt" and 0x10031004
 * "D:\Develop\DieGildeAddOn\game\spiel.c" out of original/server.exe.
 *
 * This session, 652 -> 674/714. One fix: the clear loop runs on its own
 * `clr` cursor (`clr = slot_base + 4`) with `slot = slot_base` established
 * before the pb loop, instead of the clear loop borrowing `slot`. The extra
 * copy lets msvc6 keep slot_base in esi across the prologue compare instead
 * of recomputing roles, aligning the head through IDX 70 (the query-B call).
 * Then ~90 isolated probes (`.scratch/gmprobe/`, scored with
 * `.scratch/M7/score.py` at the true 714-byte size after noticing the 720
 * score counts 6 trailing 0x90 pad bytes) all plateau at 674: the whole
 * decl-x-estab cross product for the match block (35 shapes, decl inert,
 * estab base,row,defbase optimal), defbase/q/w/cursor/slot_base types,
 * q-copy/arg-copy/cur-first/clear-on-slot temps, row-check hoists, tail
 * splits, and live-range narrowing of `count`. The spill slot ([esp+4] vs
 * target [esp+8]) and the q/cursor ebx/edi swap are one coupled allocator
 * fact that no probed spelling steers; the old note's ids[8]/defbase-local
 * `[esp+8]` claim did not reproduce on the current body (g1_fundefbase
 * inert at 674). Residue is now 20 `**` at first_diff file offset 0xa0.
 *
 * 2026-09-06, ~120 isolated probes (`.scratch/gmprobe/`, base 680/720
 * at obj 720). Mechanism found: the residue is one allocator pressure
 * unit both regions need in opposite homes (zero-sum). Dropping the
 * second-loop `mbase` temp (534/720: `v_nombase`) rotates the match
 * block to the target roles (row ebx, inner esi) but breaks the second
 * loop head (global lands in edx, target ecx); the `mbase` form matches
 * the second-loop head exactly but keeps match-block slot ebx/row esi/
 * inner edi against target edi/ebx/esi. The 0x55-loop `&&` order is
 * load-bearing (`season`-first 349, outer-if/inner-plain 349). The
 * `mbase` home is what matters, not its scope/name/type/use: block
 * scope, `q`-reuse, `void*`/`char*` types, extra first-loop use all
 * byte-identical at 680; `id`-as-temp (function-scope neighbour home)
 * also identical. Count-minus-one variants that fix the match block
 * (no-`w3` 571, `w3`-as-global-temp 571, field-into-`w3` 533) all lose
 * the second-loop head the same way. No single spelling satisfies both
 * regions; the temp belongs in a function-scope home for the second
 * loop and a block-scope home for the match block.
 * Inert (byte-identical, verified by objdump, not only score):
 * q/slot establishment orders, slot-pre/pb-hoist/clear-split cursor
 * splits, whole match-block decl-x-estab product, def/ushort-def/
 * index-def/inner-do/row-do/row-for/clear-while/clear-do/pb-for/
 * tab-while/season-for/final-walk-for loop rewrites, all compare
 * directions, volatile on w/w3, tail reorder/fence/read forms,
 * increment spellings, mbase-via-q/id/count, result/r2 role swap and
 * r2-copy, flag/word pre-hoists into temps, fw nesting/count/fork
 * variants, ids reverse/pre/q-first/walk-from-1, season-compare
 * direction (that one 679, cmp swapped but spill shifted), cond-split
 * nested guards, type/w/inner-guard goto inversions, defbase-via-slot,
 * base-via-slot, no-`w`, row-via-count. Worse: `w3` short (462),
 * volatile `w3` (462), flag-before-call hoists (455/521), def-walk
 * (410), no-reread (347, frame push change), do/while season loop
 * (349), no-base (317 at obj 704), no-defbase (249 at obj 736),
 * ids[9] (673, frame shift), base-pre-call (156), slot-index (230).
 * `~~` re-audited 2026-09-06: calls are gm_StartFilteredEntitySearch
 * (0x100170e0), gm_StartEntityQuery (0x10016460), gm_AllocObjekt
 * (0x10016760), gm_FindNextFilteredEntity (0x10016f80),
 * gm_NextEntityQueryMatch (0x10016290), LogMessageInternal
 * (0x10003640); globals g_active_player_count, g_current_season,
 * g_slot_array, g_entity_type_table, g_item_def_table; strings
 * re-read from original/server.exe: 0x1003122c "gm_ObjectsAvailble():
 * Kein Markt" (sic), 0x10031004 "D:\Develop\DieGildeAddOn\game\spiel.c".
 * STATUS: PROVEN retained; not a byte match.
 *
 * 2026-09-06 session 2, ~90 probes (`.scratch/gmprobe/batch_*.c`, scored
 * with `.scratch/M7/score.py`), plateau confirmed at 674/714. The 20 `**`
 * are one coupled allocator permutation, byte-evidence:
 *   - q/slot homes edi/ebx vs target ebx/edi (IDX 71,77,80,85,94,95),
 *     pure register/offset names, size-neutral;
 *   - match-block row/inner esi/edi vs target ebx/esi (IDX 98-116; the
 *     96-104 stretch differs in length but resyncs at `lea ecx,[eax+0x2e]`);
 *   - the {q, slot_base} spill pair swapped ([esp+0x14]/[esp+0x10] vs
 *     target [esp+0x10]/[esp+0x14], IDX 74/115/116) plus the write-only
 *     prologue spill ([esp+4] vs target [esp+8], IDX 38);
 *   - counter tail order (store-then-advance vs target advance-then-store,
 *     IDX 119-120): every advance-first spelling (G2/H3/AZ1, slot+= before
 *     the volatile store, plain or comma) adds a `mov edx,[esp+0x3c]`
 *     reload after the store and scores 672, so the tail order is not
 *     available at 674.
 * New mechanism found: the residue turns on w's live range across the
 * inner query call. Killing the `w = *(slot)` re-read (AF1, or int-w AC1,
 * or id-as-w Y1) flips the whole function to a second allocator state
 * (slot_base ebp, prologue `push ebp`, first_diff@0x0003, 323-359), and
 * every branch-local-copy variant that shortens w's range without killing
 * the re-read (Z2/AA1/AD2/AE1/AK1) lands in that same flipped state; every
 * variant that keeps w spanning the call (Z1/AA2/AF3/AJ1/AK2/AC2/AB2)
 * stays at 674 with our roles. No probed spelling keeps the 674 prologue
 * AND flips q/slot: the def-cursor family (BA1/BB2/BB3/BF1: `def` walked
 * with `+= 2` instead of derived per inner iteration) does fix q=ebx and
 * slot=edi with the target tail order, but rotates the match block to
 * base ecx/row esi/inner edx/def eax (407) and all micro-variants
 * (compare direction, decl swaps, do/while, pre/post advance, defbase
 * addend order/table-local/(w<<6)+w) stay byte-identical at 407.
 * Exhaustively inert at 674 (byte-identical, verified by objdump):
 * declaration order of all 10 locals (24 head + 6 tail permutations),
 * `register` on q/slot/slot_base/pb/row/inner, q/slot/slot_base/pb/
 * result/r2/mbase/row/inner/def/defbase types and scopes, per-loop
 * cursors (M1/Q1/AV5), slot-before-q establishment (AT1, -20), all tail
 * spellings, outer-call arg hoists (AW2/AW3, -11), volatile/alias-forced
 * slot_base residency (AL/AM, msvc6 forwards through), early-id (AQ,
 * frame 0x2c), clear-counter homes, row-across-call (AY1, flips like AF1),
 * base-after-def orders (BC1/BD1 spill base, worse). Inert at 674 means
 * the allocator ignores that axis here, not that it is untested.
 *
 * 2026-09-07: early `q = 0;` before `slot_base` claims the low frame hole
 * so the prologue spill lands at target `[esp+8]` (was `[esp+4]`). Verified
 * 677/714 (`rebrew test`, obj_size 714). IDX 38 is now `==`. The early store
 * itself is dead (no emitted write); it only changes which stack slot
 * `slot_base` occupies. ~40 follow-up probes (`.scratch/p_*.c`, scored with
 * `.scratch/M7/score.py`) could not flip q→ebx / slot→edi while keeping that
 * spill and the 720-byte frame:
 *   - etab kept live across the query (`&& etab`, volatile, `id=(int)etab`)
 *     either no-ops at 677 or flips to ebp/push-ebp (337/736);
 *   - pre-query `slot = slot_base` without reassignment moves `mov esi,ebx`
 *     before the call (656) but still assigns q to edi;
 *   - def-cursor (`def += 2`) flips q/slot homes but rotates the match block
 *     (303, first_diff@0x0002);
 *   - pb kept live via early-return (p_q0_pbkeep) gets `mov ebx,eax` for q
 *     but wrecks the prologue (126/736);
 *   - gentler pb-live (`?:`, volatile, `&& pb`) stays at 677 with edi, or
 *     enlarges the frame when the keep is real;
 *   - `__asm mov ebx,eax` / `mov edi,esi` after the query confirms the role
 *     ceiling is real but is not a C path (274).
 * Residue is now 19 `**` from IDX 71: q/slot edi/ebx vs target ebx/edi,
 * the match-block row/inner cascade, and the counter-tail order (119-120).
 *
 * 2026-09-08, 677 -> 683/714. The counter tail reaches the target's
 * load/inc/advance/store order (`mov ecx,[esp+0x3c]; inc ecx; add edi,0x80;
 * mov [esp+0x3c],ecx`) when BOTH counter accesses go through the volatile
 * alias and the increment lands in a temp read before the slot advance:
 *   nxt = *(volatile int*) &season + 1; slot += 0x80;
 *   *(volatile int*) &season = nxt;
 * The earlier tails failed for opposite reasons. `*(volatile int*) &season =
 * season + 1` reads `season` plainly, so msvc6 is free to schedule the load
 * and keeps the store ahead of the advance; a plain temp (`nxt = season + 1`
 * before the advance) lets it sink a `mov edx,[esp+0x3c]` reload in after the
 * store (672-675). The volatile READ is what pins the load at the top of the
 * tail, and only then does the advance fit between the inc and the store.
 * The temp's home is irrelevant: `count`, `id`, `mbase`, a fresh function-
 * scope local and a loop-block local are all byte-identical at 683.
 *
 * The q/slot wall is unchanged and the search around it is now exhaustive on
 * these axes, all inert at 683 unless noted (probes in `.scratch/mkt/`,
 * scored with `.scratch/M7/score.py` at the true 714-byte size):
 *   - reference weight: q's loop-condition test dropped (343), duplicated,
 *     or moved after `season` (343); q re-tested at the loop top; q's field
 *     hoisted into a temp (668); slot's reads moved onto a loop-local alias
 *     or made volatile. None of these change the pair.
 *   - split roles: the pb-loop query result on its own local (674), the final
 *     ids walk on its own `int*`/`unsigned short*` pointer in four
 *     declaration positions, both splits together, and the final walk indexed
 *     instead of walked.
 *   - frame shape: `ids` declared last, a pad slot ahead of it, the clear and
 *     second-loop counters split onto separate locals, and the final walk's
 *     match count on its own local.
 *   - match-block demand: row and inner moved onto the function-scope `count`
 *     and `id`, the item-def table hoisted into a named local, `*0x41` as
 *     `(w<<6)+w` or via an offset temp, unsigned row/inner, `unsigned short*`
 *     base and def, and a bp2 alias for the `base+4` store.
 * The only spellings that DO flip q to ebx and slot to edi are the ones that
 * add a live value inside the match block: the def cursor (`def += 2`, seeded
 * per row, up or down counted, with or without a pre-offset defbase) at
 * 409-415, and full unrolling of the inner four compares at 121. Both rotate
 * the match block onto base ecx/row esi/def eax and lose ~270 bytes, so the
 * pressure that buys the target's outer pair is the same pressure that
 * destroys the inner block. That is the wall: one allocator pressure unit,
 * needed in two places at once.
 *
 * 2026-09-08 later, 683 -> 686/714. The volatile alias on the 0x55 counter
 * is no longer needed and now costs 3 bytes: with the tail written plainly as
 *   season++;
 *   slot += 0x80;
 * msvc6 emits the target's `mov ecx,[esp+0x3c]; inc ecx; add reg,0x80;
 * mov [esp+0x3c],ecx` (0x1001610f-0x1001611a) directly. The counter still
 * lives in the [esp+0x3c] frame slot because the `season` parameter's address
 * is what homes it there, not the alias. The alias forms that the earlier note
 * called load-bearing were compensating for the ORDER, not the residency, and
 * once the increment precedes the advance in the source the plain form wins:
 * both alias spellings (`nxt = *(volatile int*)&season + 1` with the store
 * after the advance, and the volatile store alone) now score 680, and
 * advance-before-increment scores 680 as well. The dead `nxt` local was
 * removed with them; dropping it is byte-neutral.
 *
 * The q/slot wall survives that change unmoved, and the residue is now 20 `**`
 * that are ONE two-cycle: q edi / slot ebx against the target's ebx / edi,
 * with the match block's row esi / inner edi following mechanically (msvc6
 * hands the free callee-saved pair out in ebx < esi < edi order, so fixing the
 * outer pair fixes the inner one). Everything else in the pb loop, including
 * the eager [esp+0x10] spill, the [esp+0x14] slot_base spill, the memory
 * compare, the bare `jmp` back edge and the whole match block, is instruction
 * for instruction identical. Probed this session and inert at 686 (roles read
 * off objdump, not inferred from score): every slot-web split (pb walk,
 * second 0x55 loop and final ids walk on one, two or three separate locals, in
 * five declaration positions), every q-web split (the query result carried on
 * count/mbase/id/result/r2, the final walk carried on slot/slot_base/pb), all
 * ten pointer and integer types for both, `register` on either, all
 * declaration orders, the loop guard and condition rewrites (guard folded,
 * dropped, duplicated, tested through a copy or an int flag, `for` header
 * form, `season != 0x55`), the entity-type check rewrites, the tail orders,
 * and the match-block establishment product. The only spellings that reach
 * q=ebx / slot=edi still do it by adding a live value inside the match block
 * (0x2e folded into defbase, `def += 2`, an unrolled inner loop) and land at
 * 407-415 with the block rotated onto base ecx / row esi / def eax, which is
 * the same zero-sum wall the earlier note recorded.
 *
 * `/DREBREW_ALLOW_NAKED` is dead here (the file has no `__asm` and no
 * `naked`); objdump of the two builds is identical at 686, the only .obj
 * difference being the header timestamp. A CFLAGS sweep over /O2 /Ox /O1
 * /Oxs /Gy /Ob2 /Oy- and the /Og /Oi /Ot /Oy /Ob1 /Gs expansion leaves
 * /O2 /Gd best; /O1 and /Oxs compile to 617 bytes (121), /Oy- to 133, the
 * rest tie at 686.
 *
 * 2026-09-08 later still, ~100 further probes (`.scratch/mkt3/`, generator
 * `roles.py` rebuilds the whole body from the four cursor roles, scored with
 * `score.py` at the true 714-byte size). No movement: 686 stands. What the
 * pass added is the mechanism, read off objdump rather than inferred:
 *
 * The residue is exactly one ebx<->edi rename over 0x108-0x1a5. Both spill
 * slots are already the target's ([esp+0x10] for the query result,
 * [esp+0x14] for slot_base), as are the [esp+0x3c] counter, the memory
 * compare, the bare `jmp` back edge, the `and eax,0xffff` widened push, the
 * match block's shl/add chain, the `lea ecx,[eax+0x2e]` reseed and the
 * load/inc/advance/store tail. Two allocator states exist and each gives
 * exactly one half:
 *   UP (`def = defbase + 0x2e + inner * 2`, derived per inner iteration):
 *     the match block is byte-exact over 0x14f-0x196, the outer pair is
 *     ours. 686.
 *   DN (`def` an explicit cursor walked `+= 2`, seeded per row): the outer
 *     pair is byte-exact over 0x107-0x142 (`mov ebx,eax`, `test ebx,ebx`,
 *     `mov ax,[edi]`, `mov eax,[ebx+0x14]`, `mov [edi+4],1`), the match
 *     block rotates to base ecx / row esi / inner edx. 409-426.
 * The cursor is what flips the pair, not the counter direction: a cursor
 * counted upward flips (410) and a derived def counted downward does not
 * (inert at 686). The flip needs one extra invariant live value in the
 * match block, and that value is what displaces the block's own three
 * callee-saved roles.
 *
 * New axes swept this pass, all inert at 686 unless noted:
 *   - full 16-way permutation of the four cursor roles (pb-loop query
 *     result, pb-loop 0x55 walk, second 0x55 walk, final ids walk) over q
 *     and slot: only the query result's home matters (q 686, slot 683);
 *     the three walks are inert in every assignment. Putting all four on
 *     one local changes the frame and scores 330.
 *   - the query result carried on `pb` itself, the parameter-reuse lever:
 *     683. It costs the [esp+8] prologue spill, because the dead `q = 0`
 *     is what claims the low frame hole.
 *   - splitting defbase into a table temp or an offset temp so `row = 0x55`
 *     can be interleaved into the computation the way the target has it at
 *     0x160d3: 465-473 (the interleave is a scheduler artefact, not
 *     source-ordered), except the two orders that keep base first, inert.
 *   - reducing the values live across the inner query call rather than
 *     adding to them: base sourced from slot minus the walked offset (349),
 *     from the global base (400), the walk run backwards (345), the counter
 *     replaced by a slot end test (326), the walk as a byte offset (inert).
 *   - the second 0x55 loop and the final ids walk moved onto their own
 *     locals so q and slot carry pb-loop uses only: 235, the frame grows.
 *   - q and slot as int, void*, char*, int*, unsigned short*: all inert.
 *   - advance and increment placement inside the loop body: advance before
 *     the increment 680, advance at the top with negative-offset reads 586,
 *     a dead q read after the match block inert, a counter temp inert.
 *   - repairing the match block inside the DN state (row end pointer,
 *     pre-offset defbase, inner counted up, compare direction, advance
 *     first, while-form row loop, all six establishment orders, a per-row
 *     def end pointer): 392-426, best 426 at the def end pointer.
 *   - volatile reads to raise q's colouring priority: 324-363, volatile
 *     pins the value in memory instead of giving it a register.
 * `/DREBREW_ALLOW_NAKED` re-confirmed dead: byte-identical to plain
 * /O2 /Gd. /Ox /Gy /Ob2 /Ot /GB also tie at 686, /Os 121, /Oy- 133.
 *
 * 2026-09-08 later, 123 probes (`.scratch/mkt4/`, `run.sh` compiles and
 * scores at the true 714-byte size; `ranks.py` reads the three long-lived
 * homes and `mroles.py` the match-block roles off objdump). No movement:
 * 686 stands, and no probe in any batch exceeded it. What this pass adds is
 * the mechanism, read off objdump rather than inferred from score.
 *
 * The match block does not choose its own registers. It spills q and
 * slot_base at 0x197 and takes exactly those two, handed out row first in
 * ebx < esi < edi order:
 *   target frees {ebx=q, esi=slot_base} -> row ebx, inner esi
 *   ours   frees {esi=slot_base, edi=q} -> row esi, inner edi
 * So all 28 bytes follow from one fact, q's home, and the block's roles are
 * a consequence, not a second wall. That also explains why every earlier
 * match-block reshaping was inert.
 *
 * q's home is NOT decided by register recycling at its birth, and the
 * earlier note claiming so was wrong: the target loads the entity-type table
 * temp into edi at 0x0d6 exactly as we do (`8b 3d`, IDX 57 differs only in
 * the relocated operand), and both builds spill q eagerly to [esp+0x10] at
 * birth. Birth order is already the target's (q at 0x107, slot at 0x120) and
 * the emitted instruction sequence around both is identical, so the weighted
 * use counts are identical too. The target hands ebx to the first-born and
 * edi to the second; we do the reverse. What differs is a tie-break inside
 * the allocator, not any property the source can name. Extending the temp
 * past q's birth is inert at 686 (ab1/y1/y4) or grows the frame when the
 * keep is real (y2 317, y3 267, y5 273, k1 121 at obj 736).
 *
 * The pressure budget is exact and is the whole wall. The DN cursor
 * (`def += 2`) is still the only spelling that flips q to ebx, and it does
 * so by adding a fourth value inside the row loop; the block is then one
 * register short. Dropping `inner` for a `def != defbase + 0x36` end test
 * gives the block that register back and is the first shape to hold the
 * target's outer pair AND row=ebx AND the target's shl/add chain through
 * 0x16b (w4/w5/w6, 439, the best the flipped state has reached; v2 426).
 * Restoring `inner` on top of it spends the pair straight back (x1-x6, all
 * 399, all q=esi). Freeing a register elsewhere instead of inside the block
 * does not pay for it either: sourcing `base` by backing `slot` out
 * (z1 341, z4 349) or from the global (z2 249, z3 234) loses more than the
 * flip is worth.
 *
 * Ruled out this pass, inert at 686 unless noted, with roles read off
 * objdump: all six match-block establishment orders on the UP form
 * (a1 686, a2 684, a5 534, a3/a4/a6 465-473 and those three rotate the
 * whole function by one, giving the target's chain byte for byte but
 * slot_base=edi); the clear loop and the final ids walk moved onto q, slot,
 * pb and result in every combination (c1-c5, h1-h4, 686, and the ranking is
 * decided inside the pb loop alone); the pb-loop query result carried on the
 * `pb` parameter, the parameter-reuse lever (d1-d5, 683, it costs the
 * [esp+8] prologue spill that the dead `q = 0` claims); the dead pre-clear
 * `slot = slot_base` dropped, moved, or replaced by a `q` store (e1-e5,
 * 683-686); q's field read hoisted to loop-body level (g1/g2/g5 672, g3/g4
 * 686); slot's reads routed through a loop-local alias, singly and together
 * (j1-j5); an extra long-lived value at each of the three pb-loop depths
 * (k1-k5); the walk expressed as pure indexing off the counter with no
 * cursor in the source (p1/p2/p4, msvc6 strength-reduces it back; p5 315);
 * the item-def table temp merged into `base` to match the target's shared
 * edx (f1-f6, 372, rotates the function); the hoist folded so the chain
 * needs no third register (n1-n4 686, n5 684, n6 465); a third row-loop-live
 * value in the UP state (aa1 686, aa5 419, aa2 403, aa3 347, aa4 242); the
 * head `w` made to span the query call (ab1/ab2 338, ab3 356, ab5 331) and
 * the query argument hoisted to span it (ab4 348); q given a use after the
 * walk (u1 125), slot killed before it (u4 344), the byte-offset walk with
 * its own down-counter (u5 361, l1 686), and `base` sourced from slot so
 * slot_base has no in-block use (u2 349).
 *
 * 2026-09-08 final pass, 27 further probes (`.scratch/mkt5/`). No movement:
 * 686 stands. The exact residue is 26 instruction slots holding 41 differing
 * bytes, of which 28 are scored (the rest sit inside relocated operands the
 * scorer masks). Every one is a register NAME: 14 of the 26 rows differ only
 * in the ModRM byte with the encoding length unchanged, and the remaining 12
 * are the 0x163-0x16f reschedule that the rename forces on the item-def
 * hoist (same six operations, different order, no instruction added or
 * removed). The full list, target vs ours:
 *   0x107/0x10c/0x10e  mov/test/spill q        ebx  vs edi
 *   0x120/0x12d/0x151/0x158/0x1a4  the slot walk  edi  vs ebx
 *   0x13b  q's +0x14 field read                  ebx  vs edi
 *   0x163-0x16f  the shl/add hoist chain, rescheduled around row's register
 *   0x174/0x18b  inner                           esi  vs edi
 *   0x194  row                                   ebx  vs esi
 *   0x197  q reloaded from [esp+0x10]            ebx  vs edi
 * Both spill slots, the [esp+0x3c] counter, the memory compare, the bare
 * `jmp` back edge, the widened push, the `lea ecx,[eax+0x2e]` reseed and the
 * load/inc/advance/store tail are already the target's.
 *
 * Ruled out this pass, all inert at 686 with roles read off objdump unless
 * noted: the frame layout ahead of the two pointers (`ids` declared last, q
 * hoisted above slot, pb moved between them, a1/a2/a6); which pointer the
 * clear loop touches first, including running it on q or on slot itself
 * (a3/a4/a5); the nesting depth of slot's definition, which is the last
 * structural asymmetry between the two (the depth-3 advance moved onto a
 * fresh cursor, the whole walk moved onto one, q given a matching depth-3
 * definition, q re-established from a copy each iteration, the advance
 * hoisted into a `for` header: b1-b5, msvc6 coalesces all of them back);
 * the pb loop's own shape, never varied before (guard inverted with
 * `continue`, do/while, `for` with the advance in the header, a `goto` to
 * the advance: c1/c2/c3/c5, and the query hoisted above the guard c4 670).
 * Paying for the DN flip out of the 0x55 counter instead of the match block
 * fails on size: bounding the walk with a slot end pointer drops the memory
 * compare and the object to 704 (d1 324, d2 326, d5 325), a register
 * down-counter scores 346, and folding the advance into the read offset
 * holds the target pair but scores 410. Paying for it by killing `defbase`
 * inside the block (cursor reseeded from the table each row, defbase decayed
 * per row, base reseeded from a row index) scores 264-395.
 * STATUS: PROVEN retained; NEAR_MATCHING 686/714. */

void __cdecl gm_RefreshMarketAvailability(int season)
{
	unsigned int ids[8];
	char* slot_base;
	char* slot;
	void* pb;
	unsigned short* q;
	unsigned short* result;
	unsigned short* r2;
	int count;
	int id;
	int mbase;

	ids[0] = 0x92;
	ids[1] = 0x93;
	ids[2] = 0x94;
	ids[3] = 0x95;
	ids[4] = 0x96;
	ids[5] = 0x97;
	ids[6] = 0x2db;
	ids[7] = 0;

	g_active_player_count = (int) gm_StartFilteredEntitySearch(1, 5, 0xa);
	if (g_active_player_count == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x7cf,
			"gm_ObjectsAvailble(): Kein Markt", 1);
		return;
	}

	q = 0;
	slot_base = (char*) &g_slot_array + season * 0x2a90;
	if (season == g_current_season) {
		slot = slot_base;
		{
			char* clr;
			clr = slot_base + 4;
			for (count = 0x55; count != 0; count--) {
				*(int*) clr = 0;
				clr += 0x80;
			}
		}

		pb = gm_StartFilteredEntitySearch(1, 6);
		while (pb != 0) {
			if (*(char*)(g_entity_type_table + *(unsigned char*) pb * 0x24d) != '\n') {
				q = (unsigned short*) gm_StartEntityQuery(*(int*)((char*) pb + 0x5d), 1, 0, 0xff);
				season = 0;
				if (q != 0) {
				slot = slot_base;
				while (q != 0 && season < 0x55) {
					unsigned short w;
					w = *(unsigned short*) slot;
					if (w != 0) {
						if (gm_StartEntityQuery(*(int*)((char*) q + 0x14), 1, 0, w) != 0) {
								char* defbase;
								char* base;
								int row;
								char* def;
								int inner;

							*(int*)(slot + 4) = 1;
							w = *(unsigned short*) slot;
							base = slot_base;
							row = 0x55;
							defbase = g_item_def_table + w * 0x41;
							for (;;) {
								for (inner = 0; inner < 4; inner++) {
									def = defbase + 0x2e + inner * 2;
									if (*(unsigned short*) base == *(unsigned short*) def)
										*(int*)(base + 4) = 1;
								}
								base += 0x80;
								row--;
								if (row == 0)
									break;
							}
						}
					}
					season++;
					slot += 0x80;
				}
				}
			}
			pb = gm_FindNextFilteredEntity();
		}

		slot = slot_base;
		for (count = 0x55; count != 0; count--) {
			int w3;
			w3 = *(unsigned short*)(slot + 0x3c);
			mbase = g_active_player_count;
			result = (unsigned short*) gm_StartEntityQuery(*(int*)((char*) mbase + 0x5d), 1, 0, w3);
			if (result != 0) {
				result = (unsigned short*) gm_StartEntityQuery(*(int*)((char*) result + 0x14), 1, 0, 0xff);
				if (*(int*)(slot + 4) != 0) {
					r2 = (unsigned short*) gm_StartEntityQuery(*(int*)((char*) result + 0x14), 1, 0, *(unsigned short*) slot);
					if (r2 == 0) {
						gm_AllocObjekt(*(int*)((char*) result + 2), *(unsigned short*) slot, 1);
					}
				}
			}
			slot += 0x80;
		}

		id = 0x92;
		q = (unsigned short*) ids;
		do {
			count = 0;
			result = (unsigned short*) gm_StartEntityQuery(*(int*)((char*) g_active_player_count + 0x5d), 1, 0, id);
			if (result != 0) {
				r2 = (unsigned short*) gm_StartEntityQuery(*(int*)((char*) result + 0x14), 1, 0, 0xff);
				if (r2 != 0) {
					r2 = (unsigned short*) gm_StartEntityQuery(*(int*)((char*) r2 + 0x14), 1, 5);
					while (r2 != 0) {
						count++;
						r2 = (unsigned short*) gm_NextEntityQueryMatch();
					}
					result = (unsigned short*) gm_StartEntityQuery(*(int*)((char*) result + 0x14), 1, 4, 0x11);
					if (result != 0 && *(unsigned char*)((char*) result + 0x1c) != count)
						*(unsigned char*)((char*) result + 0x1c) = (unsigned char) count;
				}
			}
			q = (unsigned short*) ((int*) q + 1);
			id = ((int*) q)[0];
		} while (id != 0);
	}
}
