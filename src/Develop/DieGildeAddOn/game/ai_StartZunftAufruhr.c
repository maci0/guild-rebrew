#define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct F8 {
	int mask;
	int b;
} F8;
// SIZE 0x8

#include "Develop/DieGildeAddOn/game/entity_record.h"

extern unsigned char gm_ActiveTownIndex;

unsigned short __cdecl gm_RandomMod(int n);
int __cdecl amt_CanUpgradeBuildingTier2(char* e);
#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl gm_GetSeasonTreasury(char* e, char k);
int __cdecl ai_FindEntityInFavorRange(char* p, int kind, F8 f, int c, float r, int* out);

int __cdecl gm_ExecZunftPreismanipulation(int, int*);

/* ADDRESS: GOLDTL 0x0049fa80 */
/* AI method 0x36 (Zunft Aufruhr) start callback: forwards {3, e+4, e+0x10, ., .} to
 * gm_ExecZunftPreismanipulation when the record is kind 0x15. */
int __cdecl fcn_0049fa80(int a1, char* e)
{
	int m[5];

	if (e[0] == 0x15) {
		m[1] = *(int*) (e + 4);
		m[0] = 3;
		m[2] = *(int*) (e + 0x10);
		gm_ExecZunftPreismanipulation(a1, m);
		return 0x36;
	}
	return 0;
}

int __cdecl ai_StartZunftAufruhr(int a1, char* e, int a3, char* out)
{
	int v;
	int targetId;
	char* target;
	int count;
	int i;
	F8 f;

	if (a3 != 0) {
		return 0;
	}
	if (a1 != 0) {
		return 0;
	}
	if (amt_CanUpgradeBuildingTier2(e) != 1) {
		return 0;
	}
	v = (int) max(gm_WalkEntityChain(*(unsigned short*) e) * 0.01f, 160.0f);
	if (v > (int) (gm_GetSeasonTreasury(e, (*(char*)&gm_ActiveTownIndex)) * 0.22f)) {
		return 0;
	}
	f.mask = 0x807d4190;
	f.b = 1;
	if (ai_FindEntityInFavorRange(e, 6, f, 0, (float) (gm_RandomMod(0x20) + 0x20), &targetId) == 0) {
		return 0;
	}
	gm_ResolveEntityById((void**) (&target), 0, 0, targetId);
	if (target == 0) {
		return 0;
	}
	count = 0;
	for (i = 0; i < 768; i++) {
		if ((*(char**)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].ptr_16c) == target) {
			count++;
		}
	}
	if (count == 0) {
		return 0;
	}
	*(int*) (out + 0x10) = v;
	out[0] = 4;
	*(int*) (out + 4) = targetId;
	return 0x37;
}
