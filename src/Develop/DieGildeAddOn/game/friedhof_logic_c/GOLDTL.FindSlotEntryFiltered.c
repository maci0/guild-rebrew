#include "rebrew_types.h"
#include "rebrew_globals.h"
extern int __cdecl gv_CheckSlotActive(void* slot, int type);
extern int __cdecl cm_GetBuildingStatCount(unsigned char* entity);

/* ADDRESS: GOLDTL 0x004f18d0 */
void* __cdecl FindSlotEntryFiltered(void* filter_arg, void* entity, void* cursor, void* filter, int type)
{
	unsigned char* e;
	unsigned char* entry;
	unsigned char* limit;
	void* workers;
	e = (unsigned char*) entity;
	entry = (unsigned char*) ((g_entity_type_table + (unsigned char) *e) + (unsigned char) *e * 588);
	workers = *(void**) (e + 0x65);
	if (type != 0xff && !gv_CheckSlotActive(workers, type)) {
		return 0;
	}
	if (type == 0) {
		limit = (unsigned char*) *(void**) ((char*) workers + 8) + ((int*) 0x665328)[entry[0x247]] * 20;
	} else if (type == 1) {
		limit = (unsigned char*) *(void**) ((char*) workers + 0xc) + ((int*) 0x665338)[entry[0x247]] * 20;
	} else if (type == 2) {
		limit = (unsigned char*) *(void**) ((char*) workers + 0x10) + ((int*) 0x665348)[entry[0x247]] * 20;
	} else if (type == 3) {
		limit = (unsigned char*) *(void**) ((char*) workers + 0x14) + ((int*) 0x665358)[entry[0x247]] * 20;
	} else if (type == 0xff) {
		limit = (unsigned char*) *(void**) ((char*) workers + 0x1c) + cm_GetBuildingStatCount(e) * 20;
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
