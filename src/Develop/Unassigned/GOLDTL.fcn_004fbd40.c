#include "Develop/DieGildeAddOn/game/building_prototype.h"


extern unsigned char* lpGebaeudeINST;
extern unsigned char* lpGebaeudePROT;
extern float g_6628a8;

float __cdecl gm_GetBuildingLevelRatio(void)
{
	int s1;
	int s2;
	int i;
	unsigned char* rec;
	BUILDING_PROTOTYPE *t;

	s1 = 0;
	s2 = 0;
	rec = lpGebaeudeINST + 0xa9;
	for (i = 0; i < 32; i++, rec += 0xa9) {
		if (rec[0] != 0) {
			t = &((BUILDING_PROTOTYPE *)lpGebaeudePROT)[rec[0]];
			s1 += t->level;
			s2 += t->level_limit;
		}
	}
	if (s2 != 0) {
		return (float) s1 / s2;
	}
	return g_6628a8;
}
