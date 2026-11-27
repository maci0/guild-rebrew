#include "Develop/DieGildeAddOn/game/building_prototype.h"


extern int* g_665f08;
extern unsigned char* lpGebaeudePROT;

int __cdecl d2_CheckTutMsg1aNotCat12Node74(int* m);

int __cdecl fcn_0057fa40(int* m)
{
	if (g_665f08[14] >= 0 && m[0] == 0x25 && m[3] == 0x155) {
		g_665f08[14] = 1;
		return 1;
	}
	if (g_665f08[14] >= 1 && m[1] != 0 && m[0] == 0x24) {
		if (((char) ((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*(unsigned char*) m[1]].category) == 0xa) {
			g_665f08[14] = 2;
			return 1;
		}
		return 0;
	}
	return d2_CheckTutMsg1aNotCat12Node74(m);
}
