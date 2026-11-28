typedef struct Ent {
	unsigned short id;
	char pad2[0x178 - 2];
	int stock;
} Ent;
// SIZE 0x17c

extern unsigned char gm_ActiveTownIndex;

#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl gm_SumQueryEntryValues(int a, unsigned char b);

/* ADDRESS: GOLDTL 0x0048df90 */
int __cdecl ai_SetupSecretRoomMode3(Ent* e, char* firstOut, char* secondOut)
{
	int t;
	int thr[3];
	int m;
	int v;
	int i;

	t = gm_WalkEntityChain(e->id);
	m = gm_SumQueryEntryValues(e->stock, gm_ActiveTownIndex);
	v = (int) (m * 0.25f);
	thr[0] = (int) (t * 0.01f);
	thr[1] = (int) (t * 0.015f);
	thr[2] = (int) (t * 0.02f);
	if (v > thr[2]) {
		i = 2;
	} else if (v > thr[1]) {
		i = 1;
	} else if (v > thr[0]) {
		i = 0;
	} else {
		return 0;
	}
	*(int*) (firstOut + 0x10) = 3;
	*(int*) (secondOut + 0x10) = i;
	*(int*) (secondOut + 8) = thr[i];
	return 1;
}
