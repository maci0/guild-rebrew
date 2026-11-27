#include "g_7f4ca2.h"

extern Slot7f4ca2 g_7f4ca2[768];

char* __cdecl gm_StartFilteredEntitySearch(int arg_count, ...);
char* __cdecl gm_AddObjekt(void);
char* __cdecl gm_FindNextFilteredEntity(void);


/* ADDRESS: GOLDTL 0x004b5360 */
int __cdecl gm_CountPlayerBuildingsByCategory(int category)
{
	int count;
	char* building;
	unsigned short ownerSlot;
	unsigned char kind;

	count = 0;
	for (building = gm_StartFilteredEntitySearch(1, 5, category); building != 0; building = gm_FindNextFilteredEntity()) {
		ownerSlot = *(unsigned short*) (building + 0x27);
		if (ownerSlot == 0xffff)
			return -1;
		kind = g_7f4ca2[ownerSlot].kind;
		if (kind != 6 && kind != 7)
			return -1;
		count++;
	}
	return count;
}
