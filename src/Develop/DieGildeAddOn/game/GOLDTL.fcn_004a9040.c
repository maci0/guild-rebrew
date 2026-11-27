


#include "entity_record.h"







extern float g_664458;
extern float g_6629e8;

unsigned short __cdecl gm_RandomMod(int n);
int __cdecl ai_SelectRankedCandidates(char* e, int a, int* b, float c, float r, unsigned short* out);
float __cdecl gm_CalcEntityFavor(unsigned int a0, unsigned int a1, unsigned int a2);

int __cdecl ai_CheckAction02aPredicate(char* unused1, char* e, char* ctx, char* unused2, char* out)
{
	unsigned short idx[2];
	int mask[2];
	float d1;
	float d2;

	mask[0] = 0xf00500;
	mask[1] = 0xf00500;
	if (ai_SelectRankedCandidates(e, 2, mask, 33.0f, gm_RandomMod(0x18) + g_664458, idx) == 0) {
		return 0;
	}
	d1 = gm_CalcEntityFavor(idx[0], idx[1], 1);
	d2 = gm_CalcEntityFavor(idx[1], idx[0], 1);
	if (!(d1 > g_6629e8) || !(d2 > g_6629e8)) {
		out[0] = 7;
		*(int*) (out + 4) = ((ENTITY_RECORD*)g_7f4ca0)[idx[0]].entity_id;
		*(int*) (out + 8) = ((ENTITY_RECORD*)g_7f4ca0)[idx[1]].entity_id;
		return 1;
	}
	return 0;
}
