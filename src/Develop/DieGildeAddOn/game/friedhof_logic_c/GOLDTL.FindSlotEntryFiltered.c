/* FindSlotEntryFiltered - proper C */

// FUNCTION: GOLDTL 0x4f18d0


#include "rebrew_types.h"
#include "rebrew_globals.h"
extern int __cdecl gv_CheckSlotActive(void* slot, int type);
extern int __cdecl cm_GetBuildingStatCount(unsigned char* entity);
extern int g_field_worker_count_wt0[4];
extern int g_field_worker_count_wt1[4];
extern int g_field_worker_count_wt2[4];
extern int g_field_worker_count_wt3[4];

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
