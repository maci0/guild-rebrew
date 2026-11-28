


#include "Develop/DieGildeAddOn/game/game_data.h"

unsigned short* __cdecl gm_LookupEntityRecordById(int id);
float __cdecl gm_CalcEntityFavor(unsigned int a0, unsigned int a1, unsigned int a2);

/* ADDRESS: GOLDDE 0x004faaf0 */
float __cdecl gm_CalcAvgEntityFavor(int entityIdx, int count, int* ids)
{
	float sum;
	int cnt;
	int i;
	unsigned short* e;

	cnt = 0;
	sum = 0;
	for (i = 0; i < count; i++) {
		if (ids[i] != -1) {
			e = gm_LookupEntityRecordById(ids[i]);
			if (e != 0) {
				sum = gm_CalcEntityFavor(entityIdx, *e, 0) + sum;
				cnt++;
			}
		}
	}
	if (cnt != 0) {
		return (float)(sum * 0.01 / cnt);
	}
	return g_6628cc;
}
