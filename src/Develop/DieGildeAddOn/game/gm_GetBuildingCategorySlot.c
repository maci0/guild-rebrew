#include "Develop/DieGildeAddOn/game/building_prototype.h"


extern unsigned char* lpGebaeudePROT;

int __cdecl gm_GetBuildingCategorySlot(int buildingType, int* out)
{
	int r;

	r = 1;
	switch (((BUILDING_PROTOTYPE*)lpGebaeudePROT)[buildingType].category) {
	case 15:
		*out = 1;
		break;
	case 23:
		*out = 2;
		break;
	case 24:
		*out = 3;
		break;
	case 25:
		*out = 4;
		break;
	case 26:
		*out = 5;
		break;
	case 7:
		*out = 6;
		r = 0;
		break;
	case 4:
		*out = 7;
		r = 0;
		break;
	case 16:
		*out = 7;
	default:
		r = 0;
		break;
	}
	return r;
}
