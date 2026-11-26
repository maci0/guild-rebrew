



extern float g_6628a8;

#include "Develop/DieGildeAddOn/game/aemter.h"
unsigned short* __cdecl gm_LookupEntityRecordById(int id);
float __cdecl gm_CalcEntityFavor(unsigned int a0, unsigned int a1, unsigned int a2);

float __cdecl amt_GetOfficeAffinityScore(unsigned short* p, int kind)
{
	OFFICE_SLOT recs[6];
	float sum;
	int count;
	int n;
	int i;
	unsigned short* q;

	sum = 0;
	if (kind < 1 || kind > 7) {
		return g_6628a8;
	}
	n = amt_FindOfficeSlotsByKind(kind, 6, recs);
	count = 0;
	for (i = 0; i < n; i++) {
		if (recs[i].mplayerid != *(int*) (p + 2) && recs[i].mplayerid != -1) {
			q = gm_LookupEntityRecordById(recs[i].mplayerid);
			if (q != 0) {
				sum += gm_CalcEntityFavor(*p, *q, 1) * 0.01f;
				count++;
			}
		}
	}
	if (count != 0) {
		sum = sum / count;
	}
	return sum;
}
