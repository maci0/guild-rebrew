#include "Develop/DieGildeAddOn/game/building_prototype.h"


extern unsigned char* lpGebaeudeINST;
extern unsigned char* lpGebaeudePROT;

#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl gm_GetBuildingTechEffect(unsigned char* rec, int a, int b);

float __cdecl gm_CalcCrimeReportChance(unsigned short* key)
{
	unsigned char* rec;
	int best;
	int v;
	int i;

	best = 0;
	rec = lpGebaeudeINST;
	for (i = 0; i < 256; i++, rec += 0xa9) {
		if (rec[0] != 0 && *(unsigned short*) (rec + 0x27) == *key && ((BUILDING_PROTOTYPE*)lpGebaeudePROT)[rec[0]].category == 7) {
			v = gm_GetBuildingTechEffect(rec, 10, 1);
			if (v == 0x4b) {
				return g_662a6c;
			}
			if (v > best) {
				best = v;
			}
		}
	}
	return best * 0.01f;
}
