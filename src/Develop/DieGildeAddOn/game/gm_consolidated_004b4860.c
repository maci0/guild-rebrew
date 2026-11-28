#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
#include "Develop/DieGildeAddOn/game/building_prototype.h"
unsigned char* __cdecl gm_StartFilteredEntitySearch(int, ...);
unsigned char* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl gm_GetElapsedMinutes(void*, void*);
extern unsigned char* lpGebaeudePROT;

int __cdecl gm_JobToBuildingCategory(int);
unsigned char* __cdecl gm_StartFilteredEntitySearch(int, ...);
unsigned char* __cdecl gm_FindNextFilteredEntity(void);
void* __cdecl gm_QueryEntities(int, int, int, int, int);

/* ADDRESS: GOLD 0x004b46f0 */
/* ADDRESS: GOLDTL 0x004b4860 */
/* ADDRESS: GOLDDE 0x004a2b50 */
int __cdecl gm_HasMatureCategory2Building(unsigned short* key, char* x)
{
	unsigned char* e;

	e = gm_StartFilteredEntitySearch(2, 4, key[0], 5, 2);
	while (e != 0) {
		if (*e >= 5 && *(int*) (e + 0x65) == *(int*) (key + 2) &&
		    gm_GetElapsedMinutes(e + 0x69, ((char*)&gm_GameTime)) > *(int*) (x + 0x18))
			return 1;
		e = gm_FindNextFilteredEntity();
	}
	return 0;
}

/* ADDRESS: GOLD 0x004b4760 */
/* ADDRESS: GOLDTL 0x004b48d0 */
/* ADDRESS: GOLDDE 0x004a2bc0 */
int __cdecl gm_HasThreeFullyEquippedBuildings(unsigned short* a1)
{
	unsigned char* e;
	int x;
	int cnt;
	int ok;
	int j;
	char* row;
	unsigned short v;

	x = gm_JobToBuildingCategory(*((unsigned char*) a1 + 0x164));
	if (x == 0)
		return 0;
	cnt = 0;
	e = gm_StartFilteredEntitySearch(2, 4, a1[0], 5, x);
	while (cnt < 3 && e != 0) {
		ok = 1;
		row = (char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*e];
		for (j = 0; j < 0x40; j++) {
			v = ((BUILDING_PROTOTYPE*)row)->components[j];
			if (v == 0)
				break;
			if (gm_QueryEntities(*(int*) (e + 0x5d), 2, 6, 0, v & 0x7fff) == 0) {
				ok = 0;
				break;
			}
		}
		cnt += ok;
		e = gm_FindNextFilteredEntity();
	}
	if (cnt >= 3)
		return 1;
	return 0;
}
