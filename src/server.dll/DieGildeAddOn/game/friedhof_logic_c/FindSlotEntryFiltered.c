/* FindSlotEntryFiltered - proper C */

// FUNCTION: SERVER 0x10010710
// SYMBOL: _FindSlotEntryFiltered
// SIZE: 320

extern char* dword_100a8c30;
extern int g_1002577c[];
extern int g_1002578c[];
extern int g_1002579c[];
extern int g_100257ac[];
extern int __cdecl gv_CheckSlotActive(void* slot, int type);
extern int __cdecl cm_GetBuildingStatCount(unsigned char* entity);

/* Scans a graveyard slot list for an entry matching the filter callback.
 * The slot list is selected by type (0..3) or derived from the building
 * stats for type 0xff.  Returns the first slot for which the filter
 * returns non-zero, or NULL. */

void* __cdecl FindSlotEntryFiltered(void* filter_arg, void* entity, void* cursor, void* filter, int type)
{
	unsigned char* entry;
	char* limit;
	char* cur;
	void* workers;

	entry = (unsigned char*) ((dword_100a8c30 + *(unsigned char*) entity) + *(unsigned char*) entity * 588);
	workers = *(void**) ((char*) entity + 0x65);
	if (type != 0xff && !gv_CheckSlotActive(workers, type)) {
		return 0;
	}
	if (type == 0) {
		limit = (char*) *(int*) ((char*) workers + 8) + g_1002577c[*(unsigned char*) (entry + 0x247)] * 20;
	} else if (type == 1) {
		limit = (char*) *(int*) ((char*) workers + 0xc) + g_1002578c[*(unsigned char*) (entry + 0x247)] * 20;
	} else if (type == 2) {
		limit = (char*) *(int*) ((char*) workers + 0x10) + g_1002579c[*(unsigned char*) (entry + 0x247)] * 20;
	} else if (type == 3) {
		limit = (char*) *(int*) ((char*) workers + 0x14) + g_100257ac[*(unsigned char*) (entry + 0x247)] * 20;
	} else if (type == 0xff) {
		limit = (char*) *(int*) ((char*) workers + 0x1c) + cm_GetBuildingStatCount((unsigned char*) entity) * 20;
	} else {
		return 0;
	}
	if (!cursor) {
		if (type == 0) {
			cur = *(char**) ((char*) workers + 8);
		} else if (type == 1) {
			cur = *(char**) ((char*) workers + 0xc);
		} else if (type == 2) {
			cur = *(char**) ((char*) workers + 0x10);
		} else if (type == 3) {
			cur = *(char**) ((char*) workers + 0x14);
		} else {
			cur = *(char**) ((char*) workers + 0x1c);
		}
	} else {
		cur = (char*) cursor + 0x14;
	}
	while (cur < limit) {
		if (!filter) {
			return cur;
		}
		if (((int (__cdecl*) (void*, void*)) filter)(filter_arg, cur)) {
			return cur;
		}
		cur += 0x14;
	}
	return 0;
}
