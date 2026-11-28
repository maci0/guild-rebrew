#include "Develop/DieGildeAddOn/game/building_prototype.h"


extern unsigned char* lpGebaeudeINST;
extern unsigned char* lpGebaeudePROT;
extern float flt_0_0;

/* ADDRESS: GOLDDE 0x004e7990 */
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
	return flt_0_0;
}
