
#include "Develop/DieGildeAddOn/game/entity_record.h"











extern char* g_77261c;
#include "Develop/DieGildeAddOn/game/game_data.h"

unsigned short __cdecl gm_RandomMod(int n);
typedef struct F8 {
	int mask;
	int b;
} F8;
// SIZE 0x8

int __cdecl fcn_004a5e60(char* p, int kind, F8 f, int c, float r, int* out);
char* __cdecl gm_StartFilteredEntitySearch(int a, int b, int id);


/* ADDRESS: GOLDTL 0x004a8ed0 */
int __cdecl fcn_004a8ed0(char* unused1, char* e, char* unused3, char* unused4, char* out)
{
	int found;
	char* q;
	ENTITY_RECORD* t;
	int i;
	int n;
	F8 f;

	f.mask = 0x807d4190;
	f.b = 1;
	if (g_77261c != 0) {
		fcn_004a5e60(g_77261c, 4, f, 0, 100.0f, &found);
	}
	if (found == -1 && fcn_004a5e60(e, 6, f, 0, gm_RandomMod(0x20) + 32.0f, &found) == 0) {
		return 0;
	}
	q = gm_StartFilteredEntitySearch(1, 1, found);
	if (q == 0) {
		return 0;
	}
	t = 0;
	i = gm_RandomMod(0x300);
	for (n = 0x300; n != 0;) {
		if (((ENTITY_RECORD*)g_7f4ca0)[i].entity_index != 0xffff && ((ENTITY_RECORD*)g_7f4ca0)[i].unk_16c == q && ((ENTITY_RECORD*)g_7f4ca0)[i].entity_state == 0) {
			t = &((ENTITY_RECORD*)g_7f4ca0)[i];
			break;
		}
		n--;
		i = (i + 1) % 0x300;
	}
	if (t == 0) {
		return 0;
	}
	out[0] = 7;
	*(int*) (out + 4) = t->entity_id;
	*(int*) (out + 8) = *(int*) (q + 1);
	return 1;
}
