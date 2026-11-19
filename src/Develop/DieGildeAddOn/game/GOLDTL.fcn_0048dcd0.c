


#include "entity_record.h"









#include "Develop/DieGildeAddOn/game/game_data.h"

unsigned short __cdecl gm_RandomMod(int n);
int __cdecl fcn_004a5340(char* e, int a, int* b, int c, float r, int* out);
int __cdecl fcn_004e99c0(int k);

int __cdecl fcn_0048dcd0(char* e, char* a2, char* a3)
{
	int mask;
	int idx;
	int thr[3];
	ENTITY_RECORD* t;
	int n;
	int k;

	mask = 0xf00500;
	if (fcn_004a5340(e, 1, &mask, 0, gm_RandomMod(0x20) + 25.0f, &idx) == 0) {
		return 0;
	}
	t = &((ENTITY_RECORD*)g_7f4ca0)[(unsigned short) idx];
	n = fcn_004e99c0(t->unk_165[1]) / 3 + 2;
	thr[0] = n + 3;
	thr[1] = n + 5;
	thr[2] = n + 8;
	if (*(int*) (e + 0x194) >= thr[2]) {
		k = 2;
	} else if (*(int*) (e + 0x194) >= thr[1]) {
		k = 1;
	} else if (*(int*) (e + 0x194) >= thr[0]) {
		k = 0;
	} else {
		return 0;
	}
	*(int*) (a2 + 8) = thr[k];
	*(int*) (a3 + 0xc) = t->entity_id;
	*(int*) (a3 + 0x10) = k;
	*(int*) (a2 + 0x10) = 1;
	return 1;
}
