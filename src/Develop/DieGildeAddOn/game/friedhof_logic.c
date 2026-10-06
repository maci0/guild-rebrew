extern unsigned char g_current_season;
extern char g_graveyard_const_c[];
extern char g_graveyard_const_b[];
extern char g_graveyard_const_a[];
#include "rebrew_types.h"
#include "rebrew_globals.h"

extern int g_file_version;
#include "entity.h"
#include "entity.h"

extern int g_field_worker_count[4];

extern int g_field_entry_count[4];

extern int g_field_worker_count_wt0[4];

extern int g_field_worker_count_wt1[4];

extern int g_field_worker_count_wt2[4];

extern int g_field_worker_count_wt3[4];


int __cdecl gv_CheckSlotActive(void* slot, int type)
{
	if (type == 0) {
		if (*(int*) ((char*) slot + 8) != 0 && *(unsigned char*) ((char*) slot + 0x18) != 0)
			return 1;
		return 0;
	}
	if (type == 1) {
		if (*(int*) ((char*) slot + 0xc) != 0 && *(unsigned char*) ((char*) slot + 0x19) != 0)
			return 1;
		return 0;
	}
	if (type == 2) {
		if (*(int*) ((char*) slot + 0x10) != 0 && *(unsigned char*) ((char*) slot + 0x1a) != 0)
			return 1;
		return 0;
	}
	if (type == 3) {
		if (*(int*) ((char*) slot + 0x14) != 0 && *(unsigned char*) ((char*) slot + 0x1b) != 0)
			return 1;
		return 0;
	}
	return 1;
}


extern int __cdecl gv_CheckSlotActive(void* worker, int worktype);

void* __cdecl gv_GetSlotEntry(void* worker, int worktype, unsigned char job)
{
	if (*(int*) ((char*) worker + 4) < 1 || *(int*) ((char*) worker + 4) > 3)
		return 0;
	if (worktype == 0) {
		if (!gv_CheckSlotActive(worker, 0))
			return 0;
		if (*(int*) ((char*) worker + 4) == 1 && job >= 8)
			return 0;
		if (*(int*) ((char*) worker + 4) == 2 && job >= 0xc)
			return 0;
		if (*(int*) ((char*) worker + 4) == 3 && job >= 0x10)
			return 0;
		return (char*) *(void**) ((char*) worker + 8) + (unsigned int) job * 20;
	}
	if (worktype == 1) {
		if (!gv_CheckSlotActive(worker, 1))
			return 0;
		if (*(int*) ((char*) worker + 4) == 1 && job >= 4)
			return 0;
		if (*(int*) ((char*) worker + 4) == 2 && job >= 6)
			return 0;
		if (*(int*) ((char*) worker + 4) == 3 && job >= 8)
			return 0;
		return (char*) *(void**) ((char*) worker + 0xc) + (unsigned int) job * 20;
	}
	if (worktype == 2) {
		if (!gv_CheckSlotActive(worker, 2))
			return 0;
		if (*(int*) ((char*) worker + 4) == 1)
			return 0;
		if (*(int*) ((char*) worker + 4) == 2 && job >= 2)
			return 0;
		if (*(int*) ((char*) worker + 4) == 3 && job >= 4)
			return 0;
		return (char*) *(void**) ((char*) worker + 0x10) + (unsigned int) job * 20;
	}
	if (worktype == 3) {
		if (!gv_CheckSlotActive(worker, 3))
			return 0;
		if (*(int*) ((char*) worker + 4) == 1 || *(int*) ((char*) worker + 4) == 2)
			return 0;
		if (*(int*) ((char*) worker + 4) == 3 && job >= 2)
			return 0;
		return (char*) *(void**) ((char*) worker + 0x14) + (unsigned int) job * 20;
	}
	return 0;
}

/* gv_eval_SlotFrei -- 14 bytes at 0x10010700, between this function and
 * FindSlotEntryFiltered, in the same translation unit in the reference.  The 7
 * bytes of `nop` that separate the two are msvc6's 16-byte intra-section
 * function alignment.
 *
 * It is a filter CALLBACK, not an unreferenced helper.  An earlier version of
 * this comment said "no caller", which was wrong: it has three, none of them a
 * `call` instruction, because all three pass its ADDRESS as the fourth argument
 * of FindSlotEntryFiltered -- gv_SpawnEntities.c:41, gv_HireProductionWorker.c:55
 * and gv_MoveSlotEntry.c:121.  That is also why the catalogue has no name for it
 * and why the callee invokes it indirectly:
 *
 *     if (((int (__cdecl*) (void*, void*)) filter)(filter_arg, cursor)) { ... }
 *
 * The contract is therefore the callee's: `filter(arg, entry)` returns non-zero
 * to accept `entry`.  This one accepts an entry whose owner id is -1, i.e. one
 * with no owner assigned.
 *
 * Named for that.  `_eval_` is this tree's predicate idiom
 * (`gm_eval_SlotVoll`, `gm_eval_ObjektBesitzer`); German `frei` parallels that
 * name's `Voll`, and the +4 field is the owner id -- gv_ReplaceProductionWorker
 * tests the same dword with `!= -1` before resolving it through
 * gm_ResolveEntityById and storing it into `slot + 4`. */


int __cdecl gv_eval_SlotFrei(void* unused, int* p)
{
	(void) unused;
	return *(int*) ((char*) p + 4) == -1;
}


#include "rebrew_types.h"
#include "rebrew_globals.h"
extern int __cdecl gv_CheckSlotActive(void* slot, int type);
extern int __cdecl cm_GetBuildingStatCount(unsigned char* entity);

/* Scans a graveyard slot list for an entry matching the filter callback.
 * The slot list is selected by type (0..3) or derived from the building
 * stats for type 0xff.  Returns the first slot for which the filter
 * returns non-zero, or NULL. */

void* __cdecl FindSlotEntryFiltered(void* filter_arg, void* entity, void* cursor, void* filter, int type)
{
	unsigned char* entry;
	unsigned char* limit;
	void* workers;

	/* The walk reuses the `cursor` parameter rather than a separate local.
	 * That is what fixes the register assignment: with a distinct `cur`
	 * local msvc6 gives type/workers/entry edi/esi/ebx where the target
	 * uses ebx/edi/esi, scoring 263/320 (38 register and 6 structural
	 * diffs, the latter a prologue reschedule that sinks the type load
	 * below the entity load).  Writing the walker back into the parameter
	 * shortens the cursor value's live range so the dispatch result
	 * inherits esi and `limit` inherits ebp, reproducing the target
	 * exactly.  Permuting or retyping the locals, splitting the guard,
	 * hoisting the slot index, volatile pins and the CFLAGS sweep all
	 * leave the cycle in place.
	 *
	 * Now 320/320 RELOC; the 7 reloc bytes are the four g_10025* tables,
	 * g_entity_type_table and the two calls, so RELOC is the ceiling. */

	entry = (unsigned char*) ((g_entity_type_table + *(unsigned char*) entity) + *(unsigned char*) entity * 588);
	workers = *(void**) ((char*) entity + 0x65);
	if (type != 0xff && !gv_CheckSlotActive(workers, type)) {
		return 0;
	}
	if (type == 0) {
		limit = (unsigned char*) *(int*) ((char*) workers + 8) + g_field_worker_count_wt0[*(unsigned char*) (entry + 0x247)] * 20;
	} else if (type == 1) {
		limit = (unsigned char*) *(int*) ((char*) workers + 0xc) + g_field_worker_count_wt1[*(unsigned char*) (entry + 0x247)] * 20;
	} else if (type == 2) {
		limit = (unsigned char*) *(int*) ((char*) workers + 0x10) + g_field_worker_count_wt2[*(unsigned char*) (entry + 0x247)] * 20;
	} else if (type == 3) {
		limit = (unsigned char*) *(int*) ((char*) workers + 0x14) + g_field_worker_count_wt3[*(unsigned char*) (entry + 0x247)] * 20;
	} else if (type == 0xff) {
		limit = (unsigned char*) *(int*) ((char*) workers + 0x1c) + cm_GetBuildingStatCount((unsigned char*) entity) * 20;
	} else {
		return 0;
	}
	if (!cursor) {
		if (type == 0) {
			cursor = *(void**) ((char*) workers + 8);
		} else if (type == 1) {
			cursor = *(void**) ((char*) workers + 0xc);
		} else if (type == 2) {
			cursor = *(void**) ((char*) workers + 0x10);
		} else if (type == 3) {
			cursor = *(void**) ((char*) workers + 0x14);
		} else {
			cursor = *(void**) ((char*) workers + 0x1c);
		}
	} else {
		cursor = (char*) cursor + 0x14;
	}
	while ((unsigned char*) cursor < limit) {
		if (!filter) {
			return cursor;
		}
		if (((int (__cdecl*) (void*, void*)) filter)(filter_arg, cursor)) {
			return cursor;
		}
		cursor = (char*) cursor + 0x14;
	}
	return 0;
}


#include "rebrew_types.h"
#include "rebrew_globals.h"
extern int g_next_object_id;
int __cdecl gm_RandomMod(int range);
void* __cdecl FindSlotEntryFiltered(void* filter_arg, void* entity, void* cursor,
                                    void* filter, int type);
int __cdecl gv_eval_SlotFrei(void* unused, int* p);

/* Spawns up to *count* graveyard workers for the entity.  Validates the
 * entity type (0x1d) and maturity level (1..3), then fills each spawned
 * slot's record with a fresh object id, random stats and random role
 * values.  Returns the number of slots spawned. */

/* Byte-match note: RELOC 370/370.  The spawn loop must be a bare
 * `while (spawned < count)`; wrapping it in a redundant `if (count > 0)`
 * left the stat loop's store as `mov [edi+ecx+0x23],al` against the
 * reference's `mov [ecx+edi+0x23],al` (369/370).  The extra guard raises
 * register pressure enough to swap the SIB base and index roles.  The
 * addressing expression itself is not the lever: twelve spellings of the
 * store address (subscript, pointer walk, split index, addend order,
 * hoisted base) all emit identical bytes. */

int __cdecl gv_SpawnEntities(void* entity, int count)
{
	unsigned char type;
	unsigned char* taddr;
	void* slot;
	int i;
	int random_value;
	int spawned;

	type = *(unsigned char*) entity;
	taddr = (unsigned char*) (g_entity_type_table + type + type * 0x24c);
	if ((*taddr == 0x1d) && (*(taddr + 0x247) >= 1) && (*(taddr + 0x247) <= 3)) {
		spawned = 0;
		while (spawned < count) {
			slot = FindSlotEntryFiltered(0, entity, 0, (void*) gv_eval_SlotFrei, 0);
			if (slot == 0)
				break;
			*(int*) *(int*) ((char*) slot + 0x10) = g_next_object_id;
			g_next_object_id++;
			*(int*) ((char*) slot + 4) = *(int*) *(int*) ((char*) slot + 0x10);
			*(unsigned short*) ((char*) slot + 8) = 0x7fff;
			*(unsigned short*) ((char*) slot + 0xa) =
			    (unsigned short) (g_current_year + 5);
			*(unsigned char*) ((char*) slot + 0xc) = 0xff;
			for (i = 0; i < 5; i++) {
				random_value = gm_RandomMod(8) & 0xffff;
				*(unsigned char*) (i + *(int*) ((char*) slot + 0x10) + 0x24) =
				    (unsigned char) ((float) random_value * g_const_21_0 + g_const_42_0);
			}
			*(int*) (*(int*) ((char*) slot + 0x10) + 0x2c) =
			    (gm_RandomMod(9) & 0xffff) + 1;
			*(int*) (*(int*) ((char*) slot + 0x10) + 0x30) =
			    (gm_RandomMod(2) & 0xffff) + 1;
			*(int*) (*(int*) ((char*) slot + 0x10) + 0x34) =
			    (gm_RandomMod(0x5e) & 0xffff) + 1;
			*(int*) (*(int*) ((char*) slot + 0x10) + 0x40) =
			    g_current_year - (gm_RandomMod(4) & 0xffff) - 1;
			*(int*) (*(int*) ((char*) slot + 0x10) + 0x38) =
			    gm_RandomMod(2) & 0xffff;
			gm_RandomMod(0x10);
			gm_RandomMod(0x10);
			gm_RandomMod(0x10);
			spawned++;
		}
	} else {
		spawned = 0;
	}
	return spawned;
}


#include "rebrew_types.h"
#include "rebrew_globals.h"
extern void* __cdecl m_AllocTracked(unsigned int size, const char* tag);
extern void __cdecl m_FreeTracked(void* ptr);
extern void* __cdecl memset(void* dest, int c, unsigned int count);

/* Allocates a graveyard field slot: verifies the field type, allocates
 * the slot plus its worker table and slot-entry table, initializes the
 * production slots for the field type, and links the slot to the field. */

int __cdecl gv_AllocGraveyardField(unsigned char* field)
{
	unsigned char* entry;
	void* slot;
	char* entity_cursor;
	char* record_cursor;
	int i;

	entry = (unsigned char*) (g_entity_type_table + field[0] + field[0] * 588);
	if (entry[0] != 0x1d) {
		return 0;
	}
	if (entry[0x247] < 1 || entry[0x247] > 3) {
		return 0;
	}
	slot = m_AllocTracked(0x24, "gv_AllocGraveyardField");
	if (!slot) {
		return 0;
	}
	memset(slot, 0, 0x24);
	*(int*) slot = *(int*) (field + 1);
	*(int*) ((char*) slot + 4) = entry[0x247];
	*(void**) ((char*) slot + 0x1c) = (char*) m_AllocTracked(g_field_worker_count[entry[0x247]] * 20,
	    "gv_Alloc:_all_graves");
	if (!*(void**) ((char*) slot + 0x1c)) {
		goto cleanup;
	}
	memset(*(void**) ((char*) slot + 0x1c), 0, g_field_worker_count[entry[0x247]] * 20);
	*(void**) ((char*) slot + 0x20) = (char*) m_AllocTracked(g_field_entry_count[entry[0x247]] * 68,
	    "gv_Alloc:_all_zombies");
	if (*(void**) ((char*) slot + 0x20) == 0) {
cleanup:
		if (*(void**) ((char*) slot + 0x1c)) {
			m_FreeTracked(*(void**) ((char*) slot + 0x1c));
			*(void**) ((char*) slot + 0x1c) = 0;
		}
		if (*(void**) ((char*) slot + 0x20)) {
			m_FreeTracked(*(void**) ((char*) slot + 0x20));
			*(void**) ((char*) slot + 0x20) = 0;
		}
		m_FreeTracked(slot);
		return 0;
	}
	memset(*(void**) ((char*) slot + 0x20), 0, g_field_entry_count[entry[0x247]] * 68);
	for (i = 0; i < g_field_entry_count[entry[0x247]]; i++)
		*(unsigned*) ((char*) *(void**) ((char*) slot + 0x20) + i * 0x44) = 0xFFFFFFFFu;
	*(void**) ((char*) slot + 8) = *(void**) ((char*) slot + 0x1c);
	*(char*) ((char*) slot + 0x18) = 1;
	*(char*) ((char*) slot + 0x19) = 0;
	*(char*) ((char*) slot + 0x1a) = 0;
	*(char*) ((char*) slot + 0x1b) = 0;
	entity_cursor = (char*) *(void**) ((char*) slot + 0x1c);
	record_cursor = (char*) *(void**) ((char*) slot + 0x20);
	if (*(int*) ((char*) slot + 4) == 1) {
		*(void**) ((char*) slot + 0x10) = 0;
		*(void**) ((char*) slot + 0xc) = entity_cursor + 0xa0;
		*(void**) ((char*) slot + 0x14) = 0;
		for (i = 0; i < 8; i++) {
			*(int*) entity_cursor = 0;
			*(void**) (entity_cursor + 0x10) = record_cursor;
			*(unsigned*) (entity_cursor + 4) = 0xFFFFFFFFu;
			*(unsigned short*) (entity_cursor + 8) = 0xFFFFu;
			record_cursor += 0x44;
			entity_cursor += 0x14;
		}
		for (i = 0; i < 4; i++) {
			*(int*) entity_cursor = 1;
			*(void**) (entity_cursor + 0x10) = record_cursor;
			*(unsigned*) (entity_cursor + 4) = 0xFFFFFFFFu;
			*(unsigned short*) (entity_cursor + 8) = 0xFFFFu;
			record_cursor += 0x88;
			entity_cursor += 0x14;
		}
	} else if (*(int*) ((char*) slot + 4) == 2) {
		*(void**) ((char*) slot + 0x14) = 0;
		*(void**) ((char*) slot + 0xc) = entity_cursor + 0xf0;
		*(void**) ((char*) slot + 0x10) = entity_cursor + 0x168;
		for (i = 0; i < 0xc; i++) {
			*(int*) entity_cursor = 0;
			*(void**) (entity_cursor + 0x10) = record_cursor;
			*(unsigned*) (entity_cursor + 4) = 0xFFFFFFFFu;
			*(unsigned short*) (entity_cursor + 8) = 0xFFFFu;
			record_cursor += 0x44;
			entity_cursor += 0x14;
		}
		for (i = 0; i < 6; i++) {
			*(int*) entity_cursor = 1;
			*(void**) (entity_cursor + 0x10) = record_cursor;
			*(unsigned*) (entity_cursor + 4) = 0xFFFFFFFFu;
			*(unsigned short*) (entity_cursor + 8) = 0xFFFFu;
			record_cursor += 0x88;
			entity_cursor += 0x14;
		}
		for (i = 0; i < 2; i++) {
			*(int*) entity_cursor = 2;
			*(void**) (entity_cursor + 0x10) = record_cursor;
			*(unsigned*) (entity_cursor + 4) = 0xFFFFFFFFu;
			*(unsigned short*) (entity_cursor + 8) = 0xFFFFu;
			record_cursor += 0x110;
			entity_cursor += 0x14;
		}
	} else {
		*(void**) ((char*) slot + 0xc) = entity_cursor + 0x140;
		*(void**) ((char*) slot + 0x10) = entity_cursor + 0x1e0;
		*(void**) ((char*) slot + 0x14) = entity_cursor + 0x230;
		for (i = 0; i < 0x10; i++) {
			*(int*) entity_cursor = 0;
			*(void**) (entity_cursor + 0x10) = record_cursor;
			*(unsigned*) (entity_cursor + 4) = 0xFFFFFFFFu;
			*(unsigned short*) (entity_cursor + 8) = 0xFFFFu;
			record_cursor += 0x44;
			entity_cursor += 0x14;
		}
		for (i = 0; i < 8; i++) {
			*(int*) entity_cursor = 1;
			*(void**) (entity_cursor + 0x10) = record_cursor;
			*(unsigned*) (entity_cursor + 4) = 0xFFFFFFFFu;
			*(unsigned short*) (entity_cursor + 8) = 0xFFFFu;
			record_cursor += 0x88;
			entity_cursor += 0x14;
		}
		for (i = 0; i < 4; i++) {
			*(int*) entity_cursor = 2;
			*(void**) (entity_cursor + 0x10) = record_cursor;
			*(unsigned*) (entity_cursor + 4) = 0xFFFFFFFFu;
			*(unsigned short*) (entity_cursor + 8) = 0xFFFFu;
			record_cursor += 0x110;
			entity_cursor += 0x14;
		}
		for (i = 0; i < 2; i++) {
			*(int*) entity_cursor = 3;
			*(void**) (entity_cursor + 0x10) = record_cursor;
			*(unsigned*) (entity_cursor + 4) = 0xFFFFFFFFu;
			*(unsigned short*) (entity_cursor + 8) = 0xFFFFu;
			record_cursor += 0x220;
			entity_cursor += 0x14;
		}
	}
	*(void**) (field + 0x65) = slot;
	return (int) slot;
}


int __cdecl gv_AllocGraveyardField(unsigned char* field);
void __cdecl gv_Free3Fields(int* slot);

/* Upgrades a graveyard field to the next maturity level: allocates a new
 * field slot via gv_AllocGraveyardField, copies the worker data across, then
 * frees the old allocation.  Returns the new field data pointer.
 *
 * RELOC, 570/570. Four shapes were needed together; each is noted at its
 * site below:
 *   - the old_alloc read hoisted above the entry-type guard, which pushes edi
 *     with the other callee-saves and puts the guard zero in it,
 *   - the third counter homed in a plain (not volatile) 4-dword array, which
 *     both reserves the target's `sub esp,0x10` frame and leaves the store
 *     reorderable into the first memcpy's setup,
 *   - the shared 0x88 element count of the last memcpy named in a local, which
 *     stops a tail merge that folded 8 bytes out of the two arms,
 *   - the copy loops written as `while` over a row counter with an explicit
 *     `* 0x14`, which fixes both the SIB base/index roles and the order of the
 *     preheader's two initializations.
 */

int __cdecl gv_UpgradeField(unsigned char* field)
{
	unsigned char* entry;
	void* old_alloc;
	void* new_alloc;
	int maturity;
	int level;
	int type;
	int count8;
	int countc;
	/* The third counter is homed in memory, not a register: the target stores
	 * it to [esp+0x18] (0x10010d8c / 0x10010dc0) and reloads it once at
	 * 0x10010ec2. Taking the address of a 4-dword array forces the home and
	 * reserves the target's `sub esp,0x10` frame; a lone `volatile int` homes
	 * the value but reserves only one dword, and with the do/while copy loops
	 * register pressure is low enough that the frame then collapses to
	 * `push ecx`. Element [2] lands at [esp+0x18] under the four callee-save
	 * pushes.
	 *
	 * Plain, not volatile: volatile also pins the ordering, which blocks the
	 * scheduler from interleaving the store into the first memcpy's setup and
	 * forces a second load for the third loop's guard (LCS 177 against 185). */
	int slot[4];
	int* count10;
	int n10;
	int last_n;
	int i;
	int row;

	/* All four guard failures and the failed-alloc path share one epilogue in
	 * the target (0x10010d70), so they share one `goto fail` here.
	 *
	 * The old_alloc read is hoisted above the entry-type guard and the type
	 * byte is named, which is what puts `mov ebx,[ebp+0x65]` next to
	 * `mov cl,[ebp]` at 0x10010d23 and pushes edi with the other
	 * callee-saves, so the constant 0 lands in edi (0x10010d40). */
	count10 = &slot[2];
	type = field[0];
	old_alloc = *(void**) (field + 0x65);
	entry = (unsigned char*) (g_entity_type_table + type + type * 588);
	if (entry[0] != 0x1d)
		goto fail;
	if (old_alloc == 0)
		goto fail;
	level = *(int*) ((char*) old_alloc + 4);
	if (level >= 3)
		goto fail;
	maturity = entry[0x247];
	if (maturity - level != 1)
		goto fail;
	*(void**) (field + 0x65) = 0;
	new_alloc = gv_AllocGraveyardField(field);
	if (new_alloc == 0) {
		*(void**) (field + 0x65) = old_alloc;
		goto fail;
	}
	/* Re-read rather than reuse `maturity`: the target loads
	 * [esi+0x247] a second time at 0x10010d7a. */
	/* Both arms end in the same four instructions
	 * (`mov ecx,0x88` / two pointer loads / `rep movsd`), but the target
	 * cross-jumps only the last two, joining at 0x10010dfc and keeping
	 * `mov ecx,0x88` and one pointer load duplicated per arm. Naming the
	 * shared 0x88 element count in a local stops the deeper tail merge that
	 * otherwise folds all four and costs 8 bytes. */
	last_n = 0x88;
	if (entry[0x247] == 2) {
		count8 = 8;
		countc = 4;
		*count10 = 0;
		memcpy(*(void**) (*(char**) ((char*) new_alloc + 8) + 0x10),
		       *(void**) (*(char**) ((char*) old_alloc + 8) + 0x10), 0x88 * 4);
		memcpy(*(void**) (*(char**) ((char*) new_alloc + 0xc) + 0x10),
		       *(void**) (*(char**) ((char*) old_alloc + 0xc) + 0x10), last_n * 4);
	} else {
		count8 = 0xc;
		countc = 6;
		*count10 = 2;
		memcpy(*(void**) (*(char**) ((char*) new_alloc + 8) + 0x10),
		       *(void**) (*(char**) ((char*) old_alloc + 8) + 0x10), 0xcc * 4);
		memcpy(*(void**) (*(char**) ((char*) new_alloc + 0xc) + 0x10),
		       *(void**) (*(char**) ((char*) old_alloc + 0xc) + 0x10), 0xcc * 4);
		memcpy(*(void**) (*(char**) ((char*) new_alloc + 0x10) + 0x10),
		       *(void**) (*(char**) ((char*) old_alloc + 0x10) + 0x10), last_n * 4);
	}
	/* Byte-offset stride with a separate count decremented to zero, not
	 * `i * 0x14` off a signed compare: that is what emits the target's
	 * `add esi,0x14` / `dec edi` / `jne` back edge at 0x10010e58. */
	if (((char**) old_alloc)[2] != 0 && count8 > 0) {
		row = 0;
		i = count8;
		while (i != 0) {
			*(int*) (((char**) new_alloc)[2] + row * 0x14) =
			    *(int*) (((char**) old_alloc)[2] + row * 0x14);
			*(int*) (((char**) new_alloc)[2] + row * 0x14 + 4) =
			    *(int*) (((char**) old_alloc)[2] + row * 0x14 + 4);
			*(unsigned short*) (((char**) new_alloc)[2] + row * 0x14 + 8) =
			    *(unsigned short*) (((char**) old_alloc)[2] + row * 0x14 + 8);
			*(unsigned short*) (((char**) new_alloc)[2] + row * 0x14 + 0xa) =
			    *(unsigned short*) (((char**) old_alloc)[2] + row * 0x14 + 0xa);
			*(unsigned char*) (((char**) new_alloc)[2] + row * 0x14 + 0xc) =
			    *(unsigned char*) (((char**) old_alloc)[2] + row * 0x14 + 0xc);
			row++;
			i--;
		}
	}
	if (((char**) old_alloc)[3] != 0 && countc > 0) {
		row = 0;
		i = countc;
		while (i != 0) {
			*(int*) (((char**) new_alloc)[3] + row * 0x14) =
			    *(int*) (((char**) old_alloc)[3] + row * 0x14);
			*(int*) (((char**) new_alloc)[3] + row * 0x14 + 4) =
			    *(int*) (((char**) old_alloc)[3] + row * 0x14 + 4);
			*(unsigned short*) (((char**) new_alloc)[3] + row * 0x14 + 8) =
			    *(unsigned short*) (((char**) old_alloc)[3] + row * 0x14 + 8);
			*(unsigned short*) (((char**) new_alloc)[3] + row * 0x14 + 0xa) =
			    *(unsigned short*) (((char**) old_alloc)[3] + row * 0x14 + 0xa);
			*(unsigned char*) (((char**) new_alloc)[3] + row * 0x14 + 0xc) =
			    *(unsigned char*) (((char**) old_alloc)[3] + row * 0x14 + 0xc);
			row++;
			i--;
		}
	}
	/* One read, not two: the target loads the home into edi at 0x10010ec2 and
	 * uses that single value for both the guard and the loop counter. */
	n10 = *count10;
	if (((char**) old_alloc)[4] != 0 && n10 > 0) {
		row = 0;
		i = n10;
		while (i != 0) {
			*(int*) (((char**) new_alloc)[4] + row * 0x14) =
			    *(int*) (((char**) old_alloc)[4] + row * 0x14);
			*(int*) (((char**) new_alloc)[4] + row * 0x14 + 4) =
			    *(int*) (((char**) old_alloc)[4] + row * 0x14 + 4);
			*(unsigned short*) (((char**) new_alloc)[4] + row * 0x14 + 8) =
			    *(unsigned short*) (((char**) old_alloc)[4] + row * 0x14 + 8);
			*(unsigned short*) (((char**) new_alloc)[4] + row * 0x14 + 0xa) =
			    *(unsigned short*) (((char**) old_alloc)[4] + row * 0x14 + 0xa);
			*(unsigned char*) (((char**) new_alloc)[4] + row * 0x14 + 0xc) =
			    *(unsigned char*) (((char**) old_alloc)[4] + row * 0x14 + 0xc);
			row++;
			i--;
		}
	}
	((char*) new_alloc)[0x18] = ((char*) old_alloc)[0x18];
	((char*) new_alloc)[0x19] = ((char*) old_alloc)[0x19];
	((char*) new_alloc)[0x1a] = ((char*) old_alloc)[0x1a];
	((char*) new_alloc)[0x1b] = ((char*) old_alloc)[0x1b];
	gv_Free3Fields((int*) old_alloc);
	return *(int*) (field + 0x65);

fail:
	return 0;
}


extern void __cdecl m_FreeTracked(void* ptr);

/* Frees a 3-field slot: releases the two tracked pointers at
 * +0x1c and +0x20 (if set), then the slot itself. */

void __cdecl gv_Free3Fields(int* slot)
{
	if (slot == 0)
		return;
	if (slot[7] != 0) {
		m_FreeTracked((void*) slot[7]);
		slot[7] = 0;
	}
	if (slot[8] != 0) {
		m_FreeTracked((void*) slot[8]);
		slot[8] = 0;
	}
	m_FreeTracked((void*) slot);
}


#include "rebrew_types.h"
#include "rebrew_globals.h"
#include "entity.h"
extern unsigned short* g_entity_table_end; /* 0x1003546c */
extern int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
extern int __cdecl gv_CheckSlotActive(void* slot, int type);
extern void* __cdecl gv_GetSlotEntry(void* worker, int worktype, unsigned char job);

#pragma intrinsic(strcpy)

/* 4-byte value plus its trailing flag byte, copied as one 5-byte unit. */
#pragma pack(push, 1)
// SIZE 0x5
struct slot_tail {
	int value;
	char flag;
};
#pragma pack(pop)

int __cdecl AssignProductionSlot(void* req)
{
	void* building;
	void* owner;
	void* workers;
	void* slot;
	int* entries;
	int* selected;
	int* walk;
	int count;
	int i;

	gm_ResolveEntityById(&building, 0, 0, *(int*) ((char*) req + 8));
	if (!building ||
	    *(unsigned short*) ((char*) building + 0x27) == 0xffff ||
	    (char*) &g_slot_table + *(unsigned short*) ((char*) building + 0x27) * 0x21c ==
	        (char*) g_entity_table_end)
		return -1;
	if (g_entity_type_table[*(unsigned char*) building +
	                   *(unsigned char*) building * 588] != 0x1d)
		return -2;
	workers = *(void**) ((char*) building + 0x65);
	if (!workers)
		return -3;
	if (!gv_CheckSlotActive(workers, *(int*) ((char*) req + 0xc)))
		return -4;
	gm_ResolveEntityById(0, 0, &owner, *(int*) ((char*) req + 4));
	if (!owner)
		return -6;
	slot = gv_GetSlotEntry(workers, *(int*) ((char*) req + 0xc),
	                    *(unsigned char*) ((char*) req + 0x10));
	if (!slot ||
	    *(unsigned short*) ((char*) slot + 8) !=
	        *(unsigned short*) ((char*) owner + 0x50))
		return -7;

	i = 0;
	entries = *(int**) ((char*) slot + 0x10);
	selected = entries;
	count = g_worker_entry_count[*(int*) ((char*) req + 0xc)];
	for (; i < count; i++) {
		walk = (int*) ((char*) entries + i * 0x44);
		if (*selected == -1)
			break;
		if (*walk == -1) {
			selected = &entries[i * 17];
			break;
		}
		if (*(int*) ((char*) selected + 0x40) >
		    *(int*) ((char*) walk + 0x40))
			selected = walk;
	}

	*selected = *(int*) ((char*) owner + 4);
	strcpy((char*) selected + 4, (char*) owner + 0x30);
	strcpy((char*) selected + 0x14, (char*) owner + 0x40);
	*(struct slot_tail*) ((char*) selected + 0x24) =
	    *(struct slot_tail*) ((char*) owner + 0x80);
	*(int*) ((char*) selected + 0x2c) =
	    (unsigned char) *((char*) owner + 0x167);
	*(int*) ((char*) selected + 0x30) =
	    (unsigned char) *((char*) owner + 0xd);
	*(int*) ((char*) selected + 0x34) =
	    (unsigned char) *((char*) owner + 0x164);
	*(int*) ((char*) selected + 0x38) =
	    (unsigned char) *((char*) owner + 9);
	*(int*) ((char*) selected + 0x40) = g_current_year;
	*(int*) ((char*) selected + 0x3c) = *(int*) ((char*) owner + 0x18c);
	return 0;
}


#include "rebrew_types.h"
#include "rebrew_globals.h"
#include "entity.h"
extern unsigned short* g_entity_table_end; /* 0x1003546c */
/* 189 4-byte entries per object type; only the low word of each entry is read. */
extern int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
extern int __cdecl gv_eval_SlotFrei(void* unused, int* p);
extern int __cdecl gv_CheckSlotActive(void* slot, int type);
extern void* __cdecl FindSlotEntryFiltered(void* a, void* b, int c, int d, int e);
extern int __cdecl gm_SubObjectNoKill(int a, int b, int c); /* 0x10016ea0 */
extern int __cdecl gm_AddObjekt(int a, int b, int c);

int __cdecl gv_HireProductionWorker(void* req)
{
	void* entity1;
	void* entity2;
	void* workers;
	void* slot;
	unsigned short grave_id;
	unsigned char field_id;
	unsigned short word1;
	unsigned short word2;
	int ftol_val;
	int j;

	gm_ResolveEntityById(&entity1, 0, 0, *(int*) ((char*) req + 8));
	if (!entity1 ||
	    *(unsigned short*) ((char*) entity1 + 0x27) == 0xffff ||
	    (char*) &g_slot_table + *(unsigned short*) ((char*) entity1 + 0x27) * 0x21c == (char*) g_entity_table_end)
		return -1;
	field_id = *(unsigned char*) entity1;
	if (g_entity_type_table[field_id + field_id * 588] != 0x1d) {
		return -2;
	}
	workers = *(void**) ((char*) entity1 + 0x65);
	if (!workers) {
		return -3;
	}
	if (!gv_CheckSlotActive(workers, *(int*) ((char*) req + 0xc))) {
		return -4;
	}
	gm_ResolveEntityById(0, 0, &entity2, *(int*) ((char*) req + 4));
	if (!entity2) {
		return -6;
	}
	if (*(int*) ((char*) req + 0xc) < 0 || *(int*) ((char*) req + 0xc) > 3) {
		return -5;
	}
	slot = FindSlotEntryFiltered(entity2, entity1, 0, (void*) gv_eval_SlotFrei, *(int*) ((char*) req + 0xc));
	if (!slot) {
		return -7;
	}
	*(int*) ((char*) slot + 4) = *(int*) ((char*) entity2 + 4);
	*(unsigned short*) ((char*) slot + 8) = *(unsigned short*) ((char*) entity2 + 0x50);
	*(unsigned short*) ((char*) slot + 0xa) =
	    *(unsigned short*) ((char*) req + 0x11) + *(unsigned short*) ((char*) &g_current_year);
	*(unsigned char*) ((char*) slot + 0xc) = 0xff;
	for (j = 0; j < g_worker_entry_count[*(int*) ((char*) req + 0xc)]; j++) {
		*(int*) ((char*) *(void**) ((char*) slot + 0x10) + j * 0x44) = -1;
	}
	if (*(int*) ((char*) req + 0x13) > 0) {
		word1 = (unsigned short) g_entity_slot_table[(unsigned int) *(unsigned char*) &g_current_season * 189];
		gm_SubObjectNoKill(*(int*) ((char*) entity2 + 4), word1, *(int*) ((char*) req + 0x13));
		word2 = (unsigned short) g_entity_slot_table[(unsigned int) *(unsigned char*) &g_current_season * 189];
		ftol_val = (int) (*(int*) ((char*) req + 0x13) * g_output_share[*(int*) ((char*) req + 0xc)]);
		gm_AddObjekt(*(int*) ((char*) &g_entity_id_field + *(unsigned short*) ((char*) entity1 + 0x27) * 0x21c),
		    word2, ftol_val);
	}
	return 0;
}


#include "rebrew_types.h"
#include "rebrew_globals.h"
#include "entity.h"
extern unsigned short* g_entity_table_end; /* 0x1003546c */
/* 189 4-byte entries per object type; only the low word of each entry is read. */
extern int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
extern int __cdecl gv_CheckSlotActive(void* slot, int type);
extern void* __cdecl gv_GetSlotEntry(void* worker, int worktype, unsigned char job);
extern int __cdecl gm_SubObjectNoKill(int a, int b, int c); /* 0x10016ea0 */
extern int __cdecl gm_AddObjekt(int a, int b, int c);

/* Extends a production slot's remaining time: resolves the building's
 * entity, verifies the grave slot, then adds the building's production
 * time to the slot and accumulates the produced goods. */

int __cdecl gv_ExtendProductionTime(void* building)
{
	void* entity;
	void* workers;
	void* object;
	void* slot;
	unsigned short grave_id;
	unsigned char field_id;
	unsigned short word1;
	unsigned short word2;
	int obj4;
	int ftol_val;

	gm_ResolveEntityById(&entity, 0, 0, *(int*) ((char*) building + 8));
	if (entity) {
		grave_id = *(unsigned short*) ((char*) entity + 0x27);
		if (grave_id != 0xffff) {
			if ((char*) &g_slot_table + grave_id * 0x21c != (char*) g_entity_table_end) {
				field_id = *(unsigned char*) entity;
				if (g_entity_type_table[field_id + field_id * 588] != 0x1d) {
					return -2;
				}
				workers = *(void**) ((char*) entity + 0x65);
				if (!workers) {
					return -3;
				}
				if (!gv_CheckSlotActive(workers, *(int*) ((char*) building + 0xc))) {
					return -4;
				}
				gm_ResolveEntityById(0, 0, &object, *(int*) ((char*) building + 4));
				if (!object) {
					return -6;
				}
				slot = gv_GetSlotEntry(workers, *(int*) ((char*) building + 0xc),
				    *(unsigned char*) ((char*) building + 0x10));
				if (!slot) {
					return -7;
				}
				*(short*) ((char*) slot + 0xa) += *(short*) ((char*) building + 0x11);
				if (*(int*) ((char*) building + 0x13) > 0) {
					obj4 = *(int*) ((char*) object + 4);
					word1 = (unsigned short) g_entity_slot_table[(unsigned int) *(unsigned char*) &g_current_season * 189];
					gm_SubObjectNoKill(obj4, word1, *(int*) ((char*) building + 0x13));
					word2 = (unsigned short) g_entity_slot_table[(unsigned int) *(unsigned char*) &g_current_season * 189];
					ftol_val = (int) (*(int*) ((char*) building + 0x13) * g_output_share[*(int*) ((char*) building + 0xc)]);
					gm_AddObjekt(*(int*) ((char*) &g_entity_id_field + *(unsigned short*) ((char*) entity + 0x27) * 0x21c),
					    word2, ftol_val);
				}
				return 0;
			}
		}
	}
	return -1;
}


#include "rebrew_types.h"
#include "rebrew_globals.h"
extern unsigned short* g_entity_table_end; /* 0x1003546c */
int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
int __cdecl gv_CheckSlotActive(void* slot, int type);
void* __cdecl gv_GetSlotEntry(void* worker, int worktype, unsigned char job);

int __cdecl gv_ReplaceProductionWorker(void* a)
{
	void* rec;
	void* rec2;
	void* slot;
	unsigned short slot_off;
	unsigned short limit;
	int owner_id;
	int worker;
	int type;

	owner_id = -1;
	limit = 0xffff;
	slot_off = limit;
	gm_ResolveEntityById(&rec, 0, 0, *(int*) ((char*) a + 8));
	if (rec == 0 ||
	    *(unsigned short*) ((char*) rec + 0x27) == limit ||
	    0x100358a0 + (unsigned int) (*(unsigned short*) ((char*) rec + 0x27) & limit) * 540 ==
	        g_entity_table_end)
		return -1;
	type = *(unsigned char*) rec;
	if (*(unsigned char*) (g_entity_type_table + type + type * 0x24c) != 0x1d)
		return -2;
	worker = *(int*) ((char*) rec + 0x65);
	if (worker == 0)
		return -3;
	if (!gv_CheckSlotActive((void*) worker, *(int*) ((char*) a + 0xc)))
		return -4;
	if (*(int*) ((char*) a + 4) != -1) {
		gm_ResolveEntityById(0, 0, &rec2, *(int*) ((char*) a + 4));
		if (rec2 == 0)
			return -6;
		owner_id = *(int*) ((char*) a + 4);
		slot_off = *(unsigned short*) ((char*) rec2 + 0x50);
	}
	slot = gv_GetSlotEntry((void*) worker, *(int*) ((char*) a + 0xc),
	                       *(unsigned char*) ((char*) a + 0x10));
	if (slot == 0)
		return -7;
	*(unsigned short*) ((char*) slot + 8) = slot_off;
	*(int*) ((char*) slot + 4) = owner_id;
	return 0;
}


#include "rebrew_types.h"
#include "rebrew_globals.h"
extern unsigned short* g_entity_table_end; /* 0x1003546c */
extern int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);

/* Validates and activates a graveyard section: resolves the section's
 * entity, checks the grave slot is a free graveyard field, then enables
 * the production slots of the worker array for the section's field type. */

int __cdecl gv_ActivateSection(void* cmd)
{
	void* entity;
	void* workers;
	void* resolved;
	unsigned short grave_id;
	unsigned char field_id;
	int field_type;

	gm_ResolveEntityById(&entity, 0, 0, *(int*) ((char*) cmd + 8));
	if (entity) {
		grave_id = *(unsigned short*) ((char*) entity + 0x27);
		if (grave_id != 0xffff) {
			if ((char*) &g_slot_table + grave_id * 0x21c != (char*) g_entity_table_end) {
				field_id = *(unsigned char*) entity;
				if (g_entity_type_table[field_id + field_id * 588] != 0x1d) {
					return -2;
				}
				workers = *(void**) ((char*) entity + 0x65);
				if (!workers) {
					return -3;
				}
				gm_ResolveEntityById(0, 0, &resolved, *(int*) ((char*) cmd + 4));
				if (!resolved) {
					return -6;
				}
				field_type = *(int*) ((char*) cmd + 0xc);
				if (field_type == 3) {
					if (*(int*) ((char*) workers + 0x14)
					    && *(int*) ((char*) workers + 4) >= 3) {
						*(char*) ((char*) workers + 0x1b) = 1;
						*(char*) ((char*) workers + 0x1a) = 1;
						*(char*) ((char*) workers + 0x19) = 1;
						return 0;
					}
					return -7;
				}
				if (field_type == 2) {
					if (*(int*) ((char*) workers + 0x10) != 0) {
						if (*(int*) ((char*) workers + 4) >= 2) {
							*(char*) ((char*) workers + 0x1a) = 1;
							*(char*) ((char*) workers + 0x19) = 1;
							return 0;
						}
					}
					return -7;
				}
				if (field_type == 1) {
					if (*(int*) ((char*) workers + 0xc) == 0) {
						return -7;
					}
					*(char*) ((char*) workers + 0x19) = 1;
					return 0;
				}
				return -8;
			}
		}
	}
	return -1;
}


#include "rebrew_types.h"
#include "rebrew_globals.h"
extern unsigned short* g_entity_table_end; /* 0x1003546c */
extern int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
extern int __cdecl gv_CheckSlotActive(void* slot, int type);
extern void* __cdecl gv_GetSlotEntry(void* worker, int worktype, unsigned char job);

int __cdecl gv_UpdateProductionProgress(void* building)
{
	void* entity;
	unsigned short grave_id;
	unsigned char field_id;
	void* workers;
	void* slot;
	int sum;
	int neg;

	gm_ResolveEntityById(&entity, 0, 0, *(int*) ((char*) building + 8));
	if (entity) {
		grave_id = *(unsigned short*) ((char*) entity + 0x27);
		if (grave_id != 0xffff) {
			if ((char*) &g_slot_table + grave_id * 0x21c != (char*) g_entity_table_end) {
				field_id = *(unsigned char*) entity;
				if (g_entity_type_table[field_id + field_id * 588] != 0x1d) {
					return -2;
				}
				workers = *(void**) ((char*) entity + 0x65);
				if (!workers) {
					return -3;
				}
				if (!gv_CheckSlotActive(workers, *(int*) ((char*) building + 0xc))) {
					return -4;
				}
				slot = gv_GetSlotEntry(workers, *(int*) ((char*) building + 0xc), *(unsigned char*) ((char*) building + 0x10));
				if (!slot) {
					return -7;
				}
				sum = *(unsigned char*) ((char*) slot + 0xc);
				sum = *(int*) ((char*) building + 0x13) + sum;
				/* Spelling the negative clamp as an explicit setle/dec/and
				 * mask, rather than a ternary, is what emits the target's
				 * byte-load-then-copy pair ahead of the add. */
				neg = (sum <= 0) ? 1 : 0;
				sum &= neg - 1;
				if (sum >= 0xff) {
					sum = 0xff;
				}
				*(unsigned char*) ((char*) slot + 0xc) = (unsigned char) sum;
				return 0;
			}
		}
	}
	return -1;
}


#include "rebrew_types.h"
#include "rebrew_globals.h"
extern unsigned short* g_entity_table_end; /* 0x1003546c */
extern int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
extern int __cdecl gv_SpawnEntities(void* building, int count);

int __cdecl gv_ValidateEntityAction(void* cmd)
{
	void* entity;
	unsigned short grave_id;
	unsigned char field_id;

	gm_ResolveEntityById(&entity, 0, 0, *(int*) ((char*) cmd + 8));
	if (entity) {
		grave_id = *(unsigned short*) ((char*) entity + 0x27);
		if (grave_id != 0xffff) {
			if ((char*) &g_slot_table + grave_id * 0x21c != (char*) g_entity_table_end) {
				field_id = *(unsigned char*) entity;
				if (g_entity_type_table[field_id + field_id * 588] != 0x1d) {
					return -2;
				}
				if (*(void**) ((char*) entity + 0x65) == 0) {
					return -3;
				}
				return gv_SpawnEntities(entity, *(int*) ((char*) cmd + 0x13)) > 0 ? 0 : -4;
			}
		}
	}
	return -1;
}


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


#include "rebrew_types.h"
#include "rebrew_globals.h"
extern unsigned short* g_entity_table_end; /* 0x1003546c */
extern int g_citizen_count;
extern int g_next_object_id;
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
	void* slot_ptr;
	int grave_cursor;
	char* grave;
	int chosen;
	int j;
	int count;
	int job_id;
	unsigned char field_id;
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
	slot_ptr = *(void**) ((char*) slot + 0x10);
	j = 0;
	count = g_worker_entry_count[*(int*) ((char*) req + 0xc)];
	if (j >= count)
		goto fail_ffff;
	job_id = *(int*) ((char*) req + 0x11);
	{
		char* q = (char*) slot_ptr;
		for (; j < count; j++, q = q + 0x44) {
			entry = q;
			if (*(int*) q == job_id)
				break;
		}
		slot_ptr = q;
	}
	if (!entry || *(int*) entry != job_id)
		goto fail_ffff;
	chosen = 0;
	grave_cursor = 0x100358a0;
	while (grave_cursor < 0x1009aca0) {
		if (*(unsigned short*) grave_cursor == 0xffff)
			break;
		grave_cursor += 0x21c;
		chosen++;
	}
	if (chosen == 0x300) {
		chosen = 0;
		grave_cursor = 0x100358a2;
		while (grave_cursor < 0x1009aca2) {
			if (*(unsigned char*) grave_cursor == 0xf)
				break;
			grave_cursor += 0x21c;
			chosen++;
		}
		if (chosen == 0x300) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\friedhof_logic.c", 0x6ef, "gv_ExAllocGraveyardWorker: array overflow...", 1);
			return 0xffff;
		}
	}
	if (*(unsigned char*) ((char*) 0x100358a2 + chosen * 0x21c) == 0xf)
		g_citizen_count--;
	off = chosen * 0x21c;
	grave = (char*) g_slot_table + off;
	memset(grave, 0, 0x21c);
	/* The 0xffff store goes through `grave` and the +4 store through the
	 * symbol: c2 cannot prove the two disjoint, so the +4 store depends on
	 * this one, giving the reference's `or eax,-1; mov word ptr [ebp],0xffff`
	 * at 0x10011db0.  The later slot-index store goes through the symbol,
	 * not `grave`, or msvc6 drops this store as dead. */
	*(unsigned short*) grave = 0xffff;
	*(int*) ((char*) g_slot_table + 4 + off) = -1;
	/* A loop, not memset: msvc6 turns it into the same rep stosd, but the
	 * destination stays its own register (`lea edx,[edx+...]; mov edi,edx`
	 * at 0x10011dbf) where memset computes it straight into edi, 5 bytes
	 * short (shapes 197).  Through the g_slot_table symbol it is a `lea`;
	 * through the raw address it is `add edx,0x100358fc`. */
	for (j = 0; j < 8; j++)
		*(int*) (g_slot_table + 0x5c + off + j * 4) = -1;
	/* Stores in the reference's order, compiled without /Ow.  Plain /O2
	 * chains no stores, so equal-priority stores issue in source order.
	 * The slot-index store through the symbol may alias every later `grave`
	 * store and lifts it above them.  The citizen store's only successor is
	 * the `req` read, which may alias it, so it ties with the +2 store and
	 * issues right after the slot index (0x10011dff).  The byte copy is a
	 * named local: as a colouring candidate it takes ecx over the range of
	 * the constant 1, which moves the 1 to dl and hoists the `req` reload
	 * to 0x10011df5 (shapes 201).  Inline, the 1 takes cl and the reload
	 * edx; a plain read hoists above the counter stores. */
	{
		unsigned char type;

		*(int*) (grave + 0x170) = (int) entity;
		*(int*) (grave + 0x16c) = (int) entity;
		g_citizen_count++;
		*(int*) (grave + 4) = g_next_object_id++;
		*(unsigned short*) ((char*) g_slot_table + off) = (unsigned short) chosen;
		*(unsigned char*) (grave + 2) = 0x14;
		*(int*) (grave + 0x1f0) = 0;
		*(int*) (grave + 0x210) = -1;
		*(unsigned char*) (grave + 0x215) = 0;
		*(unsigned char*) (grave + 0x216) = 0;
		*(unsigned char*) (grave + 0x217) = 0;
		*(unsigned char*) (grave + 0x218) = 1;
		*(int*) (grave + 0x1e4) = 0x3f800000; /* 1.0f */
		*(unsigned char*) (grave + 8) = 0x64;
		*(unsigned short*) (grave + 0xa) = 0x10;
		*(unsigned char*) (grave + 0x164) = 0;
		*(unsigned char*) (grave + 0x166) = 0;
		type = *(volatile unsigned char*) ((char*) req + 0x15);
		*(unsigned char*) (grave + 0x165) = type;
		*(unsigned char*) (grave + 0x1f4) = 0;
		*(int*) (grave + 0x190) = 4;
		*(int*) (grave + 0x194) = 0;
		*(unsigned char*) (grave + 0xd) = 1;
		*(int*) (grave + 0x18c) = -1;
		*(int*) (grave + 0x20c) = -1;
		*(unsigned short*) (grave + 0x50) = 0x7fff;
	}
	{
		int n;
		for (n = 0; n < 5; n++)
			*(unsigned char*) (grave + 0x80 + n) = *(unsigned char*) ((char*) entry + 0x24 + n) >> 1;
	}
	*(unsigned char*) (grave + 9) = *(unsigned char*) ((char*) entry + 0x38);
	strcpy((char*) grave + 0x30, (char*) entry + 4);
	strcpy((char*) grave + 0x40, (char*) entry + 0x14);
	/* After both copies, as at 0x10011eed; volatile keeps it there. */
	*(volatile int*) (grave + 0x10) = 0;
	{
		int n;
		float f;
		double g;
		/* The product before the zero stores and the rest after lets the
		 * scheduler fill the x87 latency with those stores (0x10011ef5).
		 * The literal constant may alias the slot, so `fadd [0x100257c4]`
		 * stays behind the stores written before it: the sum goes between
		 * the +0x24 and +0x28 stores (0x10011f0b).  Dividing by `(float) g`
		 * rather than `g` gives `fdivr [mem]`; a plain variable divisor
		 * gives `fld; fdiv st,st(1)` plus a trailing `fstp st(0)`. */
		f = gm_RandomFloat01() * *(float*) 0x100257c8;
		*(int*) (grave + 0x18) = 0;
		*(int*) (grave + 0x1c) = 0x447a0000; /* 1000.0f */
		*(int*) (grave + 0x20) = 0;
		*(int*) (grave + 0x24) = 0;
		g = f + *(float*) 0x100257c4;
		*(unsigned short*) (grave + 0x28) = 0;
		*(int*) (grave + 0x2c) = 0;
		*(float*) (grave + 0x14) = *(float*) 0x10025680 / (float) g;
		/* Index expressions inline, each call inside its store: the index
		 * temporaries then rank below the strength-reduced n*0x300 (esi),
		 * n itself stays on the stack and the zeros come from ebx, as at
		 * 0x10011f27.  Named index locals take esi first. */
		for (n = 0; n < 0x300; n++) {
			g_relationship_matrix_primary[n * 0x300 + *(unsigned short*) grave] = (unsigned char) gm_RandomMod(0x40) - 0x20;
			g_relationship_matrix_secondary[n * 0x300 + *(unsigned short*) grave] = 0;
			g_relationship_matrix_primary[*(unsigned short*) grave * 0x300 + n] = (unsigned char) gm_RandomMod(0x40) - 0x20;
			g_relationship_matrix_secondary[*(unsigned short*) grave * 0x300 + n] = 0;
		}
	}
	if (*(int*) entry == *(int*) ((char*) slot + 4)) {
		int n;
		count = g_worker_entry_count[*(int*) ((char*) req + 0xc)];
		if (count > 0) {
			slot_ptr = *(void**) ((char*) slot + 0x10);
			for (n = 0; n < count; n++, slot_ptr = (char*) slot_ptr + 0x44) {
				if (*(int*) slot_ptr == -1)
					continue;
				if (*(int*) slot_ptr != *(int*) entry) {
					*(int*) ((char*) slot + 4) = *(int*) slot_ptr;
					goto clear_entry;
				}
			}
		}
		*(int*) ((char*) slot + 4) = -1;
		*(unsigned short*) ((char*) slot + 8) = 0xffff;
	}
clear_entry:
	memset(entry, 0, 0x44);
	/* A plain zero-extending read lets msvc6 skip the `xor eax,eax`, since
	 * eax is still 0 from the memset: `mov ax,[ebp]` as at 0x10011fe2.  The
	 * volatile store keeps that read after the -1 store. */
	*(volatile int*) entry = -1;
	return *(unsigned short*) grave;
	/* With this label inside the log block, msvc6 routes the three
	 * entry-search exits to the `!slot` epilogue at 0x10011cdb; placed here
	 * they reach the log path's epilogue at 0x10011d77, as in the reference. */
fail_ffff:
	return 0xffff;
}
