// FUNCTION: SERVER 0x100156c0
#include "../../../Units/Error/error.h"
#include "../../../Units/m_alloc/m_alloc.h"

#include <string.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

#pragma intrinsic(memcpy, memset)

extern int g_manufacturer_types[25];
extern int g_minimum_manufacturer[732];



/* Game function - gm_InitObjektHersteller (initialize object manufacturers)
 *
 * RELOC, 642/642, obj size equals the target (642).
 *
 * The last 28 bytes came from three changes to the scan loop, in this order.
 * Earlier rounds read the residual as "msvc6 rotates the loop and the target
 * does not"; the rotation was a symptom, and each of the three has its own
 * cause:
 *
 *   1. The rotation itself (614 -> 498, un-rotated but 2 bytes short).
 *      With `scan = record` and `entity_type = *record`, msvc6 proves the
 *      loop's first byte test true and peels it above the head. A
 *      loop-invariant head test it cannot fold defeats that: spelling the
 *      loop as `while (byte_offset < 0xca78)` with the counter break at the
 *      bottom keeps the byte test at the head, exactly as the target has it.
 *      0x58 * 0x24d == 0xca78, so the target's `cmp ebp,0xca78` is the
 *      counter bound strength-reduced onto the live byte offset, not a
 *      separate guard.
 *   2. The `mov eax,[esp+0x1c]` load hoisting above the guard (615 -> 635).
 *      Wrapping the loop in a redundant `if (byte_offset < 0xca78)` gives
 *      the loads a block that post-dominates the guard, so they sink below
 *      the `jge` where the target has them. The inner test then folds into
 *      the back edge and costs nothing.
 *   3. Bottom-branch polarity, `jge out; jmp head` against the target's
 *      `jl head; jmp out` (639 -> 642). Decided by the outer entity-type
 *      branch, not by the loop: with the `goto diff_type` skeleton msvc6
 *      lays the loop exit ahead of the same_count++ block. Spelling it as a
 *      plain `if (entity_type != prev_type) { ... } else { same_count++; }`
 *      puts the two blocks in the target's order and flips both branches.
 *
 * All six `~~` operands resolved: the four calls are LogMessageInternal
 * 0x10003640 (disps -0x120b5, -0x1212f, -0x121c6, -0x122ca from 0x100156f0,
 * 0x1001576a, 0x10015801, 0x10015905) and both absolute loads are
 * g_item_def_table 0x101de450. The four string arguments are unrelocated
 * literals and read out of original/server.exe as the file name
 * "D:\Develop\DieGildeAddOn\game\spiel.c" at 0x10031004 plus three
 * gm_InitObjektHersteller() messages at 0x1003102c, 0x10030fb0 and
 * 0x10030f54.
 *
 * Dead ends measured this round, all reverted: `volatile` on the scan-site
 * byte read (246/651) or on the outer read (239/647); deriving `scan` from
 * `record_base + byte_offset` instead of `record` (290/649); indexing the
 * scan by `record_base + idx * 0x24d` (214/662); comparing against a
 * byte-punned `entity_type` (217/641); guarding on `record_index < 0x58`
 * with the head test on the counter (223/651); the bottom test spelled
 * `continue`/`break`, `!(idx < 0x58)` or `idx == 0x58`, and both breaks as
 * `goto after_branch` (all inert at 639); `for (; byte_offset < 0xca78;
 * scan += 0x24d, idx++)` (227/638); folding the two tests into
 * `while (byte_offset < 0xca78 && idx < 0x58)` (279/641); inverting only
 * the outer test while keeping the goto skeleton (570/642).
 *
 * Levers that moved it from the 131/653 baseline:
 *   - `record_index` declared volatile homed it in the target's [esp+0x1c]
 *     slot, which made the outer loop head fall through instead of jumping
 *     to a reloaded index (131 -> 147). Removed again at 584 once the other
 *     levers below were in place; by then it cost 24 bytes (584 -> 608).
 *   - Spelling the entity-type test as `!=` with the same_count++ arm inline
 *     puts the shared tail where the target has it (147 -> 167).
 *   - Reading `idx` before `scan` in the scan loop's setup gives the target's
 *     `mov eax,[esp+0x1c]; mov ecx,edi` order (167 -> 170).
 *   - The scan loop as do/while drops the pre-test the target does not have
 *     (170 -> 181).
 *   - Zeroing `comp_count` before the record_base reload lets the target's
 *     `mov [esp+0x28],ebx; mov ebx,[g_entity_type_table]` pair emit in order
 *     and closed the size gap (181 -> 464, obj 642 = target).
 *   - The same read-order fix in the inner manufacturer scan (464 -> 466).
 *   - Accumulating into `mfr_start` and loading the table entry into its own
 *     local gives the target's `add ecx,eax; cmp ecx,eax` roles (466 -> 470).
 *   - `record_index++` before `byte_offset += 0x24d` in the outer loop tail
 *     (470 -> 478).
 *   - Writing the ten constant stores through a local base pointer
 *     (`mfr_table[8] = 0x2f`) instead of ten independent literal-address
 *     stores lets the second LogMessageInternal's four argument pushes hoist
 *     ahead of them, as the target does at 0x100156f5 (478 -> 577). The
 *     literal addresses are preserved: an `extern int g_mfr[]` declaration
 *     also hoists but emits relocations against a symbol that does not exist.
 *   - The component-count guard as unsigned `> 0` gives the target's
 *     `test al,al; jbe` at 0x10015818 where `!= 0` gives `je`; the loop-bottom
 *     compare stays signed `jl` (577 -> 578).
 *   - `j++` before the cursor advance in the inner manufacturer scan gives the
 *     target's `inc eax; inc edi; add ebp,0x24d` at 0x10015881 (578 -> 584).
 *   - Dropping the now-stale `volatile` on `record_index` (584 -> 608): with
 *     the loop bodies in the target's shape it no longer bought the [esp+0x1c]
 *     home, and its ordering pin cost 24 bytes across the outer loop tail.
 *   - Assigning `prev_type = 0x58` *after* the 0x2dc fill loop instead of
 *     before it emits the target's `mov ecx,0x2dc; mov eax,0x58` count-then-
 *     value order (608 -> 614). Written first, msvc6 materializes 0x58 into
 *     eax ahead of the rep-stosd count and the two immediates swap.
 *
 * Residual: 28 bytes in one cluster, indices 57-67. MSVC6 rotates the scan
 * loop, peeling the first byte test above the head and copying it to the
 * bottom as the back-edge; the target does not rotate and uses the counter
 * test there, reloading run_length from [esp+0x14] inside the body.
 *   - Rotating forms that keep the target's `mov eax,[esp+0x1c]; mov ecx,edi`
 *     roles but stay rotated (all 614, no change): do/while+break, while,
 *     for(;;) with either exit order, `goto` out of the enclosing block,
 *     operand order swapped, the byte hoisted to a local, an `int*` alias on
 *     entity_type, `unsigned char* scan`, `idx != 0x58` as the exit test, a
 *     `char`-aliased store on run_length, and `prev_type` moved below the
 *     scan loop.
 *   - Forms that DO un-rotate all grow the function and score far worse:
 *     recomputing the cursor as `record_base + byte_offset` instead of
 *     reusing `record`, a `char**` alias read of `record`, and a volatile
 *     read of `record` each defeat the value numbering that peels the test,
 *     but cost 7 bytes (obj 649) and swap the eax/ecx roles: 290/649.
 *     A `for (idx = record_index; idx < 0x58; idx++)` counter loop keeps the
 *     target's eax/ecx roles and un-rotates, but msvc6 then emits its own
 *     redundant `cmp eax,0x58` pre-test above the head: 9 bytes, 223/651.
 *     Volatile on the byte read un-rotates but adds `and edx,0xff` per read.
 *     That round read the peel and the register roles as coupled. They are
 *     not; see the top of this comment.
 *   - 2026-09-05 round, all 614/642 at obj 642, i.e. byte-identical output:
 *     an `int*` alias carrying every `run_length` read and write (aimed at
 *     the target's [esp+0x14] reload), a `*(char*) &prev_type` narrow store
 *     before the widening one, an `int*` alias on `prev_type` used for the
 *     store, testing the scan byte against `prev_type` instead of the
 *     equal-valued `entity_type`, and both remaining body permutations
 *     (`scan += 0x24d` first, and `idx++` ahead of `run_length++`).
 *     Re-measured on the un-rotating cursor recompute: initializing `idx`
 *     before `scan` rather than after does not move it off 290/649, and a
 *     `while (*scan == entity_type)` head with the counter break at the
 *     bottom lands on the same 290/649. A `goto`-based loop whose only
 *     back-edge is the counter test still rotates: 614/642.
 *   - 2026-09-06 round. The residual is a pure cyclic rotation: both sides
 *     emit the same eleven instructions with the same register roles and the
 *     object size already equals the target's 642, so the whole 28-byte
 *     deficit is where the block starts, not what it contains. Still 614/642:
 *     a `while (*scan == entity_type)` head with the counter break at the
 *     bottom, `for (;;)` with both breaks explicit, a redundant
 *     `if (*scan == entity_type)` wrapper above the loop, the scan byte
 *     hoisted into a block-local `int`, the compare operands reversed, an
 *     `int*` alias carrying run_length, an explicit `goto` loop, and
 *     initializing `scan` before `idx`.
 *     Regressions, all rejected: `while (idx < 0x58)` as the head and
 *     `for (idx = record_index; idx < 0x58; idx++)` both make msvc6 duplicate
 *     the byte test at the bottom (223/651); `while (idx < 0x58 && *scan ==
 *     entity_type)` likewise (223/651); a redundant `if (idx < 0x58)` wrapper
 *     224/651; `volatile` on the outer `entity_type` read 239/647; a
 *     `char* volatile` cursor 223/656; a `volatile` counter 215/659;
 *     `*scan - entity_type != 0` 234/642; a do/while with the byte test at
 *     the bottom 219/666; and aliased pre-stores through `&run_length`,
 *     `&prev_type` or `&same_count` cost 281/646, 239/642 and 285/646.
 *     The peel comes from msvc6 proving `*record == entity_type` on entry,
 *     since `scan = record` and `entity_type = *record`. Every form that
 *     defeats that proof also defeats the value numbering that keeps the
 *     cursor in the target's registers, so the block grows past 642. 614
 *     stands.
 *   - 2026-09-06 round, aimed squarely at the rotation. Still 614/642 at obj
 *     642: `goto` into the middle of a `for (;;)` so the byte test is the loop
 *     entry, the scan byte hoisted into a block-local `int` read once per
 *     iteration, the compare operands reversed with a `goto` exit past the
 *     block, re-deriving `entity_type` from `scan` inside the block, an
 *     `unsigned char` copy of `entity_type` as the compare operand, and
 *     `idx++` moved ahead of `run_length++`.
 *     Regressions, all rejected: `while (idx < 0x58 && *scan == entity_type)`
 *     un-rotates but msvc6 then adds its own `cmp eax,0x58` pre-test above the
 *     head (223/651); `for (;;)` with both breaks at the bottom 219/666; a
 *     do/while with the counter break inside and the byte test as the back-edge
 *     219/666; advancing `record` itself and restoring it after 263/646; two
 *     reaching definitions for `scan` (an `if (idx != 0)` picking between
 *     `record` and a recomputed `record_base + byte_offset`) does defeat the
 *     peel but costs 13 bytes, 218/655; `scan = record + (idx - record_index)`
 *     290/649; a `t = entity_type + run_length - run_length` launder 614/642.
 *     Dropping the enclosing `if (byte_offset < 0xca78)` and letting the
 *     `idx < 0x58` head serve as the guard emits the target's un-rotated loop
 *     instruction-for-instruction, but msvc6 then reorders the two [esp] spills
 *     above it and folds the guard to `cmp ebp,0x58`, so the block lands two
 *     bytes short and 8 instructions out of phase: 498/642 at obj 640. That is
 *     the closest any un-rotating form has come.
 *     Flag sweep (/G5 /G6 /Ob1 /Oy- /Ox /Gy) does not un-rotate either; /G6
 *     shortens the function to 186 instructions and diverges much earlier.
 *   - 2026-09-05 round, aimed at the ebp allocation rather than the rotation.
 *     The un-rotated 498/640 form's residual was localized precisely: at that
 *     form the eleven scan-loop instructions (target IDX 57-68) match the
 *     target one-for-one with identical register roles, and the entire deficit
 *     is that ebp holds `record_index` where the target holds `byte_offset`.
 *     That single role swap costs the 2 bytes (`cmp ebp,0x58` 3 bytes against
 *     the target's `cmp ebp,0xca78` 6) and shifts every later instruction by
 *     one slot, which is what collapses the positional score. The two outer
 *     spill slots are swapped for the same reason: the target keeps
 *     record_index at [esp+0x1c] and byte_offset at [esp+0x2c] (IDX 141-147),
 *     ours the reverse.
 *     Levers tried against that swap, none of which moved ebp to byte_offset:
 *     swapping the two initializers (498), swapping their declaration order
 *     (498), swapping `record_index++` and `byte_offset += 0x24d` in the outer
 *     tail (495), recomputing `record_base + byte_offset` for the entity_type
 *     read rather than reusing `record` (498), assigning `scan` before `idx`
 *     (498), and `idx++` ahead of `scan += 0x24d` (498). Forcing
 *     record_index to memory to free ebp regresses badly: an `int*` alias
 *     carrying its reads 231/628, address-taken with `(*ri)++` 233/628,
 *     `volatile` 254/639.
 *     Rewriting the scan loop to induct on the byte offset directly
 *     (`off = byte_offset; while (off < 0xca78) { ...; off += 0x24d; }`) does
 *     put a 0xca78 compare in the loop but loses the counter entirely: 197/629.
 *     `while (idx * 0x24d < 0xca78)` 235/655.
 *     Keeping the `if (byte_offset < 0xca78)` guard above the un-rotated
 *     `while (idx < 0x58)` head emits BOTH tests (target's `cmp ebp,0xca78`
 *     plus msvc6's own `cmp eax,0x58` pre-test, 9 bytes): 223/651. Guarding on
 *     `record_index < 0x58` instead lets msvc6 fold the guard into the head,
 *     which is the 499/640 variant of the same un-rotated shape.
 *     `#pragma optimize` sweep on the whole function: "a",off, "l",off,
 *     "w",off and "table_cursor",on are all inert at 614/642; "g",off explodes to obj 926
 *     at 26/926.
 *     That round concluded the rotation and the ebp role were one coupled
 *     decision and that 614 was the ceiling. Superseded: they are separate,
 *     and both are reachable together. See the three-step account at the top
 *     of this comment, which closed the function at 642/642.
 *
 * PROVEN 2026-08-29: symbolic equivalence (mem on 0x10139840 + 0x101dd8e0)
 * with --loop-bound 4000. The scan loop's per-state back-edge count is
 * cumulative (88+87+...+1 = 3916) across the outer loop's iterations, so a
 * bound below ~3900 makes LoopSeer discard the state before the function
 * terminates; lower bounds report "no terminal states". */

void __cdecl gm_InitObjektHersteller(void)
{
	int* table_cursor;
	int i;
	int* mfr_table;
	char* record_base;
	int byte_offset;
	int record_index;
	int same_count;
	int run_length;
	int prev_type;
	char* record;
	int entity_type;
	int comp_count;

	/* Zero manufacturer table (25 ints) */
	table_cursor = g_manufacturer_types;
	for (i = 0x19; i != 0; i--) {
		*table_cursor = 0;
		table_cursor++;
	}

	same_count = 0;
	run_length = 0;

	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x458, "gm_InitObjektHersteller(): fill tab...", 1);

	/* Indexing through a local base pointer, rather than ten independent
	 * literal-address stores, lets the second call's argument pushes hoist
	 * ahead of the stores the way the target does. */
	mfr_table = g_manufacturer_types;
	mfr_table[8] = 0x2f;
	mfr_table[7] = 0x32;
	mfr_table[6] = 0x29;
	mfr_table[10] = 0x21;
	mfr_table[14] = 0x1e;
	mfr_table[15] = 0x1f;
	mfr_table[16] = 0x20;
	mfr_table[11] = 0x17;
	mfr_table[12] = 0x35;
	mfr_table[9] = 0x14;

	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x46d, "gm_InitObjektHersteller(): Initialisiere gm_ObjektNr2MinimalHersteller[Objekte_MAX]", 1);

	record_base = (char*) g_entity_type_table;

	/* Fill ObjektNr2MinimalHersteller with 0x58 (732 ints) */
	table_cursor = g_minimum_manufacturer;
	for (i = 0x2dc; i != 0; i--) {
		*table_cursor = 0x58;
		table_cursor++;
	}

	/* prev_type shares the fill constant and must be written *after* the loop:
	 * that order gives the target's `mov ecx,0x2dc; mov eax,0x58`. Written
	 * first, 0x58 lands in eax ahead of the count and the two swap. */
	prev_type = 0x58;

	record_index = 0;
	byte_offset = 0;

	do {
		record = record_base + byte_offset;
		entity_type = *(unsigned char*) record;

		if (entity_type != prev_type) {
			same_count = 0;
			prev_type = entity_type;
			run_length = 0;

			if (byte_offset < 0xca78) {
				int idx;
				char* scan;
				idx = record_index;
				scan = record;
				while (byte_offset < 0xca78) {
					if (*(unsigned char*) scan != entity_type) {
						break;
					}
					run_length++;
					scan += 0x24d;
					idx++;
					if (idx >= 0x58) {
						break;
					}
				}
			}
		} else {
			same_count++;
		}
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x490, "gm_InitObjektHersteller(): // ---- Alle Objekte im Geb\344ude-Prototypen durchgehen... ----", 1);

		comp_count = 0;
		record_base = (char*) g_entity_type_table;

		/* Unsigned `> 0` gives the target's `test al,al; jbe`, where a plain
		 * `!= 0` emits `je`; the loop-bottom compare stays signed (`jl`). */
		if ((unsigned int) *(unsigned char*) (record + 0x22) > 0u) {
			unsigned short* comp_ptr;

			comp_ptr = (unsigned short*) (record + 0x23);

			do {
				unsigned short entry;

				entry = *comp_ptr;

				if (entry != 0xffff) {
					int ent_idx;
					int mfr_start;
					char* mfr_record;
					int mfr_type;
					int* mfr_type_alias;
					int consec;
					int new_val;

					ent_idx = entry & 0x7fff;
					mfr_start = *(unsigned char*) (g_item_def_table + (ent_idx << 6) + ent_idx + 0x21);
					mfr_start = g_manufacturer_types[mfr_start];

					mfr_record = record_base + mfr_start * 0x24d;
					mfr_type_alias = &mfr_type;
					*mfr_type_alias = *(unsigned char*) mfr_record;
					consec = 0;

					if (mfr_start < 0x58) {
						int j;
						char* scan;
						j = mfr_start;
						scan = mfr_record;
						/* j++ ahead of the cursor advance gives the target's
						 * `inc eax; inc edi; add ebp,0x24d` order. */
						while (j < 0x58) {
							if (*(unsigned char*) scan != *mfr_type_alias) {
								break;
							}
							consec++;
							j++;
							scan += 0x24d;
						}
					}

					mfr_start += (consec * same_count) / run_length;
					new_val = g_minimum_manufacturer[ent_idx];
					if (mfr_start < new_val) {
						g_minimum_manufacturer[ent_idx] = mfr_start;
					}
				}

				comp_count++;
				comp_ptr++;
			} while (comp_count < *(unsigned char*) (record + 0x22));
		}

		record_index++;
		byte_offset += 0x24d;
	} while (byte_offset < 0xca78);

	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4ae, "gm_InitObjektHersteller(): Initialisieren der Objekt2MinimalHersteller-Tabelle anhand der Rohstoffe ", 1);

	{
		int* min_ptr;
		unsigned char* type_ptr;

		min_ptr = g_minimum_manufacturer;
		type_ptr = (unsigned char*) (g_item_def_table + 0x21);

		do {
			if (*min_ptr == 0x58) {
				*min_ptr = g_manufacturer_types[*type_ptr];
			}
			min_ptr++;
			type_ptr += 0x41;
		} while ((int) min_ptr < (int) (g_minimum_manufacturer + 732));
	}
}


