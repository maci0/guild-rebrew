#include "rebrew_types.h"
#include "rebrew_globals.h"
#include "entity.h"

// FUNCTION: GOLDTL 0x4f2fe0
// SIZE: 672
// FUNCTION: SERVER 0x10011940
// SIZE: 674

extern unsigned short* g_entity_table_end;
extern int g_next_object_id;
extern unsigned char g_current_season;
int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
int __cdecl gv_CheckSlotActive(void* slot, int type);
void* __cdecl gv_GetSlotEntry(void* worker, int worktype, unsigned char job);
int __cdecl gv_eval_SlotFrei(void* unused, int* p);
void* __cdecl FindSlotEntryFiltered(void* filter_arg, void* entity, void* cursor,
                                    void* filter, int type);
int __cdecl gm_SubObjectNoKill(int a, int b, int c);
int __cdecl gm_AddObjekt(int a, int b, int c);

/* Moves a graveyard worker's slot entry to the field it currently works
 * in: finds the source entry and a free destination slot, copies the
 * entry across, clears the source, and accumulates the produced goods
 * for the current season.
 *
 * The loop walks the destination region for a free (-1) slot, then migrates
 * the source entry there (rep movsd / rep stosd). Each cursor is bounded by
 * its own end pointer, and occupied source entries are skipped by advancing
 * src against src_end (0x10011ac4), not by advancing dst against src.
 *
 * The first gm_ResolveEntityById receives (0, 0, &a, id); the out-param
 * reuses the arg-1 slot, hence the `cmd = a` register copy.
 *
 * RELOC 674/674. What closed the bulk:
 * the 0x1003546c guard read an undeclared `g_entity_table_end` instead of
 * `g_entity_table_end`; the three -1 guards are one `||` chain, not three
 * separate `goto`s; the source bound g_worker_entry_count[cmd+8] is computed before
 * the FindSlotEntryFiltered call and spilled (0x10011a4d); the post-loop
 * move clears the source entry and fills the destination, not both on
 * found2 (0x10011b0d-0x10011b3e); 0xff lives in one register across the
 * byte and word stores (0x10011b32); the ftol result is a plain cast of a
 * re-read field, not a pushed double (0x10011b7c); the +0x27 index at the
 * gm_AddObjekt call site reads rec2 via the [esp+0x1c] reload
 * (0x10011bb1).
 *
 * The last 12 bytes were the skip loop's back edge. Every earlier attempt
 * kept the copy OUTSIDE the skip loop, reached by `goto copy` or by falling
 * out of it, which forces msvc6 to re-test `*src` on the back edge
 * (`cmp [ebx],-1` / `je`, 3 bytes) or to peel a `cmp ebx,ecx` / `jae` pair
 * above it. Measured: do/while 434, explicit goto back edge 434, peeled
 * test 434, no pre-guard 435, bound test hoisted inside `for(;;)` 435 at
 * obj 670, `*(volatile int*)` on the value test 420, short-circuit
 * `while (src < end && *src == -1)` 437 at obj 670.
 *
 * What closes it: put the copy INSIDE the skip loop and leave by `break`.
 * `while (src < src_end) { if (*src != -1) { copy; break; } src += 0x11; }`
 * gives the loop exactly one test per iteration at the top, so the back
 * edge carries nothing and msvc6 emits the target's bare `jmp 0x10011ac4`
 * (0x10011ad0). The `if (src >= src_end) goto done;` after the loop is the
 * shared exit at 0x10011afc. Verified on a standalone probe before editing:
 * the emitted opcode lengths match the target byte for byte.
 *
 * All 19 relocation slots resolved against the target: the eight calls are
 * gm_ResolveEntityById (x2), gv_CheckSlotActive, gv_GetSlotEntry,
 * FindSlotEntryFiltered, gm_SubObjectNoKill, __ftol and
 * gm_AddObjekt; the globals are g_entity_table_end,
 * g_entity_type_table, g_worker_entry_count (x2), g_current_year, g_next_object_id,
 * g_current_season (x2), g_entity_slot_table (x2) and g_output_share. */

int __cdecl gv_MoveSlotEntry(void* a)
{
	void* cmd;
	void* rec2;
	void* slot;
	void* found2;
	void* found;
	int* src_entry;
	int* dst_entry;
	int* dst_end;
	int* src_end;
	int src_count;
	int clear;
	int count;
	int i;

	cmd = a;
	gm_ResolveEntityById(0, 0, &a, *(int*) a);
	if (a == 0)
		return -6;
	gm_ResolveEntityById(&rec2, 0, 0, *(int*) ((char*) cmd + 4));
	/* The three -1 exits share one epilogue in the target (0x10011bd8),
	 * reached by a far jump from each guard. */
	if (rec2 == 0 || *(unsigned short*) ((char*) rec2 + 0x27) == 0xffff ||
	    0x100358a0 + (*(unsigned short*) ((char*) rec2 + 0x27) & 0xffff) * 540 ==
	        g_entity_table_end)
		return -1;
	if (*(unsigned char*) (g_entity_type_table + *(unsigned char*) rec2 +
	    *(unsigned char*) rec2 * 588) != 0x1d)
		return -2;
	slot = *(void**) ((char*) rec2 + 0x65);
	if (slot == 0)
		return -3;
	if (!gv_CheckSlotActive(slot, *(int*) ((char*) cmd + 8)))
		return -4;
	found = gv_GetSlotEntry(slot, *(int*) ((char*) cmd + 8),
	                     *(unsigned char*) ((char*) cmd + 0xc));
	/* One -7 epilogue in the target at 0x10011a7b, shared by all three
	 * guards. */
	if (found == 0)
		goto fail7;
	if (*(unsigned short*) ((char*) found + 8) != *(unsigned short*) ((char*) a + 0x50))
		goto fail7;

	src_entry = *(int**) ((char*) found + 0x10);
	/* The source bound is computed before the call (0x10011a4d) and spilled
	 * to [esp+0x10]. */
	src_count = g_worker_entry_count[*(int*) ((char*) cmd + 8)];
	found2 = FindSlotEntryFiltered(a, rec2, 0, (void*) gv_eval_SlotFrei,
	                               *(int*) ((char*) cmd + 0xd));
	if (found2 == 0)
		goto fail7;
	dst_entry = *(int**) ((char*) found2 + 0x10);
	dst_end = dst_entry + g_worker_entry_count[*(int*) ((char*) cmd + 0xd)] * 17;
	src_end = src_entry + src_count * 17;

	if (dst_entry < dst_end) {
		for (;;) {
			if (*dst_entry == -1) {
				/* Skip occupied source entries by walking src, not dst;
				 * both bounds are the ends, not each other (0x10011ac0).
				 * The copy lives INSIDE the skip loop, exited by `break`:
				 * that is what emits the target's bare `jmp 0x10011ac4`
				 * back edge instead of a duplicated `cmp [ebx],-1`/`je`. */
				while (src_entry < src_end) {
					if (*src_entry != -1) {
						memcpy(dst_entry, src_entry, 0x44);
						memset(src_entry, 0, 0x44);
						*src_entry = -1;
						break;
					}
					src_entry += 0x11;
				}
				if (src_entry >= src_end)
					goto done;
			}
			dst_entry += 0x11;
			if (dst_entry < dst_end)
				continue;
			break;
		}
	}
done:

	/* The move clears the source entry (found) and fills the destination
	 * (found2): 0x10011b0d-0x10011b3e. */
	*(int*) ((char*) found2 + 4) = *(int*) ((char*) found + 4);
	*(int*) ((char*) found + 4) = -1;
	*(unsigned short*) ((char*) found2 + 8) = *(unsigned short*) ((char*) found + 8);
	*(unsigned short*) ((char*) found + 8) = 0xffff;
	/* 0xff is materialized once in a 32-bit register (0x10011b32) and reused
	 * by both the byte and the word store. */
	clear = 0xff;
	*(unsigned short*) ((char*) found2 + 0xa) = (unsigned short) (g_current_year + 0xa);
	*(unsigned char*) ((char*) found2 + 0xc) = (unsigned char) clear;
	*(unsigned short*) ((char*) found + 0xa) = (unsigned short) clear;
	*(int*) ((char*) cmd + 0x15) = g_next_object_id;

	count = *(int*) ((char*) cmd + 0x11);
	if (count > 0) {
		gm_SubObjectNoKill(*(int*) ((char*) a + 4),
		                   (unsigned int) *(unsigned short*) ((char*) g_entity_slot_table +
		                                                       g_current_season * 756),
		                   count);
		/* fild re-reads the field (0x10011b7c) instead of the register, and
		 * the conversion is an implicit cast, not a pushed double. */
		i = (int) ((float) *(int*) ((char*) cmd + 0x11) *
		           g_output_share[*(int*) ((char*) cmd + 0xd)]);
		gm_AddObjekt(*(int*) (0x100358a4 +
		                                 (unsigned short) *(unsigned short*) ((char*) rec2 + 0x27) * 540),
		                         (unsigned int) *(unsigned short*) ((char*) g_entity_slot_table +
		                                                             g_current_season * 756),
		                         i);
	}
	return 0;

fail7:
	return -7;

fail1:
	return -1;
}

