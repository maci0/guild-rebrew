/* FindSlotEntryFiltered - scans a worker slot list for the first entry the
 * filter callback accepts. */

#include "rebrew_types.h"
#include "rebrew_globals.h"
extern int __cdecl gv_CheckSlotActive(void* slot, int type);
extern int __cdecl cm_GetBuildingStatCount(unsigned char* entity);

/* The slot list is selected by type (0..3) or derived from the building
 * stats for type 0xff.  Returns the first slot for which the filter
 * returns non-zero, or NULL. */

/* ADDRESS: GOLDTL 0x004f18d0 */
void* __cdecl FindSlotEntryFiltered(void* filter_arg, void* entity, void* cursor, void* filter, int type)
{
	unsigned char* entry;
	unsigned char* limit;
	void* workers;

	workers = *(void**) ((char*) entity + 0x65);
	entry = (unsigned char*) ((g_entity_type_table + *(unsigned char*) entity) + *(unsigned char*) entity * 588);
	if (type != 0xff && !gv_CheckSlotActive(workers, type)) {
		return 0;
	}
	if (type == 0) {
		limit = (unsigned char*) *(int*) ((char*) workers + 8) + *(int*) (0x665328 + *(unsigned char*) (entry + 0x247) * 4) * 20;
	} else if (type == 1) {
		limit = (unsigned char*) *(int*) ((char*) workers + 0xc) + *(int*) (0x665338 + *(unsigned char*) (entry + 0x247) * 4) * 20;
	} else if (type == 2) {
		limit = (unsigned char*) *(int*) ((char*) workers + 0x10) + *(int*) (0x665348 + *(unsigned char*) (entry + 0x247) * 4) * 20;
	} else if (type == 3) {
		limit = (unsigned char*) *(int*) ((char*) workers + 0x14) + *(int*) (0x665358 + *(unsigned char*) (entry + 0x247) * 4) * 20;
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
