/* gm_ObjectsAvailble — refreshes the market item availability. */

// FUNCTION: SERVER 0x10015f70

#include "../../../Units/Error/error.h"

#include <stddef.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

extern int g_active_player_count; /* 0x1003543c */
extern unsigned char g_current_season; /* 0x10035439 */

void* __cdecl gm_FindNextFilteredEntity(void);
void* __cdecl gm_NextEntityQueryMatch(void);
unsigned short* __cdecl gm_ff_Objekt(int, int, int, ...);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);


/* Rebuilds the market slots for the given season: clears the slot
 * flags, marks every slot whose item some market entity's inventory holds
 * (and every slot whose item is in that item's four-entry list at
 * def+0x2e), allocates missing objects and refreshes the per-item counts
 * for the ids list.
 *
 * Byte-exact.  `g_slot_array` is the array symbol (`(char*) &g_slot_array`,
 * not a pointer load), 0x55 slots of 0x80 bytes per season.  Every walk is
 * a counted index loop; msvc6 strength-reduces them into the reference's
 * down-counters and pointer walks, and the ids walk folds its first
 * `ids[i] != 0` test into the reference's `mov eax,0x92` head.  The dead
 * `query = 0` orders the frame: without it `slots` and `query` swap their
 * [esp+0x10]/[esp+0x14] homes (consistent with c2 placing equal-weight
 * slots in first-reference order, docs/msvc6-allocator.md "Frame slots").
 * The previous body spelled the walks as cursors and sat at 25 linked
 * bytes of ebx/edi role swap. */

void __cdecl gm_ObjectsAvailble(int season)
{
	unsigned int ids[8];
	char* slots;
	void* entity;
	void* query;
	unsigned short* result;
	unsigned short* r2;
	char* def;
	int i;
	int j;
	int k;
	int count;

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

	query = 0;
	slots = (char*) &g_slot_array + season * 0x2a90;
	if (season != g_current_season) {
		return;
	}
	for (i = 0; i < 0x55; i++) {
		*(int*) (slots + i * 0x80 + 4) = 0;
	}

	entity = gm_StartFilteredEntitySearch(1, 6);
	while (entity != 0) {
		if (*(char*) (g_entity_type_table + *(unsigned char*) entity * 0x24d) != '\n') {
			query = gm_ff_Objekt(*(int*) ((char*) entity + 0x5d), 1, 0, 0xff);
			for (i = 0; query != 0 && i < 0x55; i++) {
				if (*(unsigned short*) (slots + i * 0x80) != 0 &&
				    gm_ff_Objekt(*(int*) ((char*) query + 0x14), 1, 0, *(unsigned short*) (slots + i * 0x80)) != 0) {
					*(int*) (slots + i * 0x80 + 4) = 1;
					def = g_item_def_table + *(unsigned short*) (slots + i * 0x80) * 0x41;
					for (j = 0; j < 0x55; j++) {
						for (k = 0; k < 4; k++) {
							if (*(unsigned short*) (slots + j * 0x80) == *(unsigned short*) (def + 0x2e + k * 2)) {
								*(int*) (slots + j * 0x80 + 4) = 1;
							}
						}
					}
				}
			}
		}
		entity = gm_FindNextFilteredEntity();
	}

	for (i = 0; i < 0x55; i++) {
		result = (unsigned short*) gm_ff_Objekt(*(int*) ((char*) g_active_player_count + 0x5d), 1, 0,
			*(unsigned short*) (slots + i * 0x80 + 0x3c));
		if (result != 0) {
			result = (unsigned short*) gm_ff_Objekt(*(int*) ((char*) result + 0x14), 1, 0, 0xff);
			if (*(int*) (slots + i * 0x80 + 4) != 0) {
				if (gm_ff_Objekt(*(int*) ((char*) result + 0x14), 1, 0, *(unsigned short*) (slots + i * 0x80)) == 0) {
					gm_AllocObjekt(*(int*) ((char*) result + 2), *(unsigned short*) (slots + i * 0x80), 1);
				}
			}
		}
	}

	for (i = 0; ids[i] != 0; i++) {
		count = 0;
		result = (unsigned short*) gm_ff_Objekt(*(int*) ((char*) g_active_player_count + 0x5d), 1, 0, ids[i]);
		if (result != 0) {
			r2 = (unsigned short*) gm_ff_Objekt(*(int*) ((char*) result + 0x14), 1, 0, 0xff);
			if (r2 != 0) {
				r2 = (unsigned short*) gm_ff_Objekt(*(int*) ((char*) r2 + 0x14), 1, 5);
				while (r2 != 0) {
					count++;
					r2 = (unsigned short*) gm_NextEntityQueryMatch();
				}
				result = (unsigned short*) gm_ff_Objekt(*(int*) ((char*) result + 0x14), 1, 4, 0x11);
				if (result != 0 && *(unsigned char*) ((char*) result + 0x1c) != count)
					*(unsigned char*) ((char*) result + 0x1c) = (unsigned char) count;
			}
		}
	}
}
