


#include "entity_record.h"








extern unsigned char g_773d75;
#include "Develop/DieGildeAddOn/game/game_data.h"

unsigned short __cdecl gm_RandomMod(int n);
int __cdecl fcn_004a5340(char* e, int a, int* b, int c, float r, int* out);
int __cdecl fcn_0050b810(int a, char b);
#include "Develop/DieGildeAddOn/game/spiel.h"

int __cdecl fcn_0048dbc0(char* e, char* a2, char* a3)
{
	int mask;
	int idx;
	ENTITY_RECORD* t;
	int have;
	int need;

	if (*(int*) (e + 0x194) < 16) {
		return 0;
	}
	mask = 0xf00500;
	if (fcn_004a5340(e, 1, &mask, 0, gm_RandomMod(0x20) + 25.0f, &idx) == 0) {
		return 0;
	}
	t = &((ENTITY_RECORD*)g_7f4ca0)[(unsigned short) idx];
	have = (int) (fcn_0050b810(*(int*) (e + 0x178), (*(char*)&g_773d75)) * 0.25f);
	need = gm_WalkEntityChain(*(unsigned short*) e);
	need = (int) ((gm_WalkEntityChain(t->entity_index) + need) * 0.02f);
	if (have < need) {
		return 0;
	}
	*(int*) (a3 + 8) = need;
	*(int*) (a2 + 8) = 0;
	*(int*) (a3 + 0xc) = t->entity_id;
	*(int*) (a3 + 0x10) = 0;
	*(int*) (a2 + 0x10) = 0;
	return 1;
}
