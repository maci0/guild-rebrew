typedef struct Kind {
	unsigned char type;
	char pad1[0x24c];
} Kind;
// SIZE 0x24d
#include "Develop/DieGildeAddOn/game/building_prototype.h"
struct BUILDING_SLOT_LIMITS {
	unsigned short cap;
	short pad2;
	int pad4;
};
// SIZE 0x8

extern unsigned char* lpGebaeudePROT;

unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl gm_GetBuildingSlotLimits(int, struct BUILDING_SLOT_LIMITS*);


/* ADDRESS: GOLDTL 0x004cb6f0 */
int __cdecl fcn_004cb6f0(char* a1, char* out)
{
	struct BUILDING_SLOT_LIMITS info;
	unsigned char* e;
	unsigned char* old;
	char* p;

	e = gm_StartFilteredEntitySearch(1, 1, *(int*) (a1 + 0x10));
	if (e == 0)
		return 1;
	p = gm_LookupEntityRecordById(*(int*) (a1 + 0x14));
	if (p == 0 && *(int*) (a1 + 0x14) != -1)
		return 1;
	if (((BUILDING_PROTOTYPE*)lpGebaeudePROT)[e[0]].category == 1) {
		gm_GetBuildingSlotLimits(e[0], &info);
		if (e[0x65] >= info.cap)
			return 1;
		e[0x65]++;
	}
	old = *(unsigned char**) (p + 0x170);
	if (old != 0 && ((BUILDING_PROTOTYPE*)lpGebaeudePROT)[old[0]].category == 1 && old[0x65] > 0)
		old[0x65]--;
	*(unsigned char**) (p + 0x170) = e;
	if (out != 0) {
		out[0] = 1;
		out[1] = 0;
		*(int*) (out + 6) = 0;
	}
	return 0;
}
