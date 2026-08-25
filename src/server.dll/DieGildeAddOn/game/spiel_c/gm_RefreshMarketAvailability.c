/* gm_RefreshMarketAvailability — refreshes the market item availability. */

// FUNCTION: SERVER 0x10015f70

#include "../../../Units/Error/error.h"

#include <stddef.h>

extern int g_active_player_count; /* 0x1003543c */
extern unsigned char g_current_season; /* 0x10035439 */
extern char* g_slot_array; /* 0x1009b770 */
extern char* g_item_def_table; /* 0x101de450 */
extern int g_entity_type_table; /* 0x100a8c30 */

void* __cdecl FindNextFilteredEntity(void);
void* __cdecl gm_NextEntityQueryMatch(void);
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);

/* Rebuilds the market slots for the given season: seeds the slot table
 * from the market object list, marks matching item definitions as
 * available, allocates missing objects and tracks per-item counts. */
void __cdecl gm_RefreshMarketAvailability(int season)
{
	unsigned int local_20;
	unsigned int local_1c[7];
	char* slot_base;
	char* slot;
	char* base;
	char* def;
	void* pb;
	unsigned short* q;
	unsigned short* result;
	unsigned short* r2;
	int* pv;
	int counter;
	int outer;
	int inner;
	int count;
	int i;
	int id;
	int mbase;

	local_20 = 0x92;
	local_1c[0] = 0x93;
	local_1c[1] = 0x94;
	local_1c[2] = 0x95;
	local_1c[3] = 0x96;
	local_1c[4] = 0x97;
	local_1c[5] = 0x2db;
	local_1c[6] = 0;

	g_active_player_count = (int) gm_StartFilteredEntitySearch(1, 5, 0xa);
	if (g_active_player_count == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x7cf,
			"gm_ObjectsAvailble - Kein Markt", 1);
		return;
	}

	slot_base = g_slot_array + season * 0x2a90;
	if (season == g_current_season) {
		slot = slot_base + 4;
		for (i = 0x55; i != 0; i--) {
			*(int*) slot = 0;
			slot += 0x80;
		}

		pb = gm_StartFilteredEntitySearch(1, 6);
		while (pb != 0) {
			if (*(char*)(g_entity_type_table + *(unsigned char*) pb * 0x24d) != '\n') {
				q = (unsigned short*) gm_StartEntityQuery(*(int*)((char*) pb + 0x5d), 1, 0, 0xff);
				if (q != 0) {
					counter = 0;
					slot = slot_base;
					while (counter < 0x55) {
						if (*(unsigned short*) slot != 0) {
							if (gm_StartEntityQuery(*(int*)((char*) q + 0x14), 1, 0, *(unsigned short*) slot) != 0) {
								*(int*)(slot + 4) = 1;
								base = slot_base;
								for (outer = 0x55; outer != 0; outer--) {
									def = g_item_def_table + *(unsigned short*) slot * 0x41 + 0x2e;
									for (inner = 4; inner != 0; inner--) {
										if (*(unsigned short*) base == *(unsigned short*) def)
											*(int*)(base + 4) = 1;
										def += 2;
									}
									base += 0x80;
								}
							}
						}
						counter++;
						slot += 0x80;
					}
				}
			}
			pb = FindNextFilteredEntity();
		}

		slot = slot_base;
		for (i = 0x55; i != 0; i--) {
			mbase = g_active_player_count;
			result = (unsigned short*) gm_StartEntityQuery(*(int*)((char*) mbase + 0x5d), 1, 0, *(unsigned short*)(slot + 0x3c));
			if (result != 0) {
				result = (unsigned short*) gm_StartEntityQuery(*(int*)((char*) result + 0x14), 1, 0, 0xff);
				if (result != 0 && *(int*)(slot + 4) != 0) {
					r2 = (unsigned short*) gm_StartEntityQuery(*(int*)((char*) result + 0x14), 1, 0, *(unsigned short*) slot);
					if (r2 == 0) {
						gm_AllocObjekt(*(int*)((char*) result + 2), *(unsigned short*) slot, 1);
					}
				}
			}
			slot += 0x80;
		}

		id = 0x92;
		q = (unsigned short*) &local_20;
		do {
			count = 0;
			result = (unsigned short*) gm_StartEntityQuery(*(int*)((char*) g_active_player_count + 0x5d), 1, 0, id);
			if (result != 0) {
				r2 = (unsigned short*) gm_StartEntityQuery(*(int*)((char*) result + 0x14), 1, 0, 0xff);
				if (r2 != 0) {
					r2 = (unsigned short*) gm_StartEntityQuery(*(int*)((char*) r2 + 0x14), 1, count);
					while (r2 != 0) {
						count++;
						r2 = (unsigned short*) gm_NextEntityQueryMatch();
					}
					result = (unsigned short*) gm_StartEntityQuery(*(int*)((char*) result + 0x14), 1, 4, 0x11);
					if (result != 0 && *(unsigned char*)((char*) result + 0x1c) != count)
						*(unsigned char*)((char*) result + 0x1c) = (unsigned char) count;
				}
			}
			id = (int) q[1];
			q += 2;
		} while (id != 0);
	}
}
