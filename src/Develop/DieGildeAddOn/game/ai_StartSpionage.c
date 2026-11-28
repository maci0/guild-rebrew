extern double dbl_10;
extern float g_664138;
extern float g_664160;
extern float g_664188;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned char gm_ActiveTownIndex;
#include "Develop/DieGildeAddOn/game/entity_record.h"

int __cdecl gm_RandomMod(int a0);
int __cdecl gm_GetSeasonTreasury(short* ent, unsigned char player);
int __cdecl ai_SelectRankedCandidates(short* a0, int a1, int* a2, int a3, float a4, int* a5);
int __cdecl gm_WalkEntityChain(unsigned short a0);
int __cdecl he_StartHandlungSearch(int a0, int a1, int a2, int a3, int a4);

/* ADDRESS: GOLDTL 0x0049bfa0 */
int __cdecl ai_StartSpionage(int code, short* target, int zero, char* out1, char* out2)
{
	int mask;
	int idx;
	int rnd;
	int thr;
	char* p;
	int score;
	float first;

	mask = 0xf00500;
	rnd = gm_RandomMod(3) & 0xffff;
	thr = gm_GetSeasonTreasury(target, gm_ActiveTownIndex);
	if (zero != 0) {
		return 0;
	}
	if (ai_SelectRankedCandidates(target, 1, &mask, 0, (float) ((double) (gm_RandomMod(0x19) & 0xffff) + 10.0), &idx) == 0) {
		return 0;
	}
	p = (char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[(unsigned short) idx];
	first = (float) gm_WalkEntityChain(*target) * g_664138;
	score = (int) ((float) gm_WalkEntityChain(*(unsigned short*) p) * g_664138 + first);
	first = (float) score;
	score = (int) (first * ((float) rnd * g_664188 + 1.0f));
	if ((float) thr * g_664160 < (float) score) {
		return 0;
	}
	if (he_StartHandlungSearch(2, 0, 0x18, 2, *(unsigned short*) target) != 0) {
		return 0;
	}
	*out1 = 7;
	*(int*) (out1 + 4) = *(int*) (p + 4);
	*(int*) (out1 + 8) = 1;
	*(int*) (out1 + 0x10) = score;
	*out2 = 0;
	*(int*) (out2 + 4) = 0;
	*(int*) (out2 + 8) = 0;
	*(int*) (out2 + 0x10) = 0;
	return 0x25;
}
