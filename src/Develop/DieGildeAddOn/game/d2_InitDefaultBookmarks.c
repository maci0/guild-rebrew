#include "Develop/DieGildeAddOn/game/building_prototype.h"


extern char gm_EntitySlotTable[];
extern unsigned char* lpGebaeudePROT;
extern char* gm_MarketEntity;

void __cdecl d2_SetBookmarkSlotEntity(int, int);
unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
unsigned char* __cdecl gm_AddObjekt(void);
unsigned char* __cdecl gm_FindNextFilteredEntity(void);

void __cdecl d2_InitDefaultBookmarks(void)
{
	int i;
	int n;
	unsigned char* e;

	for (i = 0; i < 768; i++) {
		if (gm_EntitySlotTable[i * 540 + 2] == 6) {
			break;
		}
	}
	n = 1;
	d2_SetBookmarkSlotEntity(0, (*(int*)&gm_MarketEntity));
	e = gm_StartFilteredEntitySearch(1, 5, 0xf);
	if (e != 0) {
		n = 2;
		d2_SetBookmarkSlotEntity(1, (int) e);
	}
	if (*(int*) (gm_EntitySlotTable + i * 540 + 0x170) != 0) {
		d2_SetBookmarkSlotEntity(n, *(int*) (gm_EntitySlotTable + i * 540 + 0x170));
	}
	n = 3;
	for (e = gm_StartFilteredEntitySearch(1, 4, i); e != 0; e = gm_FindNextFilteredEntity()) {
		if (((char)(((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*e].category)) != 2) {
			d2_SetBookmarkSlotEntity(n++, (int) e);
		}
	}
}
