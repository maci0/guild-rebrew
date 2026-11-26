#include "Develop/DieGildeAddOn/game/building_prototype.h"


extern unsigned char* lpGebaeudePROT;

unsigned char* __cdecl gm_StartFilteredEntitySearch(int a, int b, int kind);

int __cdecl amt_CheckZunftLevel2Eligibility(unsigned char* obj)
{
	unsigned char* building;
	int kind;

	if (obj[0x169] < 0x1e || obj[0x169] > 0x21) {
		return 0;
	}
	switch (obj[0x169]) {
	case 0x1f:
		kind = 0x18;
		break;
	case 0x20:
		kind = 0x19;
		break;
	case 0x21:
		kind = 0x1a;
		break;
	case 0x1e:
		kind = 0x17;
		break;
	default:
		return 0;
	}
	building = gm_StartFilteredEntitySearch(1, 5, kind);
	if (building == 0 || (building[0x5a] & 1) != 0) {
		return 0;
	}
	if (((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*building].level < 2) {
		return 0;
	}
	if (*(unsigned int*) (obj + 0x1c8) & 0x8000000) {
		return -1;
	}
	return *(int*) (obj + 0x194) < 5 ? -2 : 1;
}
