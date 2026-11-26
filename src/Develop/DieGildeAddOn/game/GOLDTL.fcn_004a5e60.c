#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned char* g_entity_ptr;

int __cdecl gm_RandomMod(int a0);
int __cdecl fcn_005cfb00(unsigned short* a0, int* a1, int a2);
float __cdecl gm_CalcEntityFavor(unsigned short a0, unsigned short a1, int a2);

/* ADDRESS: GOLDTL 0x004a5e60 */
int __cdecl ai_FindEntityInFavorRange(unsigned short* entity, int kind, int filterLo, int filterHi, float minimum, float maximum, int* resultId)
{
	int buf[20];
	int step;
	int flag;
	int found;
	int ent;
	int i;
	int idx;
	float f;

	step = g_6643d8[(gm_RandomMod(0x10) & 0xffff)];
	flag = 0;
	buf[2] = filterLo;

	buf[4] = kind;

	buf[5] = 0;
	buf[3] = filterHi | 0x80000000;
	*resultId = -1;
	found = 0;
	if ((minimum > 0.0 || maximum < 100.0) && minimum < maximum) {
		flag = 1;
	}
	i = 0x100;
	idx = (unsigned short) gm_RandomMod(0x100);
	do {
		if (i == 0) {
			if (found != 0) {
				return 1;
			}
			return 0;
		}
		ent = (int) &g_entity_ptr[idx * 169];
		if (*(char*) ent == 0) {
			goto next;
		}
		if (fcn_005cfb00(entity, buf, ent) == 0) {
			goto next;
		}
		if (flag != 0) {
			f = gm_CalcEntityFavor(*(unsigned short*) (ent + 0x27), *entity, 1);
			if (f < *(float*) (buf + 17) || f > *(float*) (buf + 17)) {
				goto next;
			}
		}
		*resultId = *(int*) (ent + 1);
		found = 1;
next:
		i--;
		idx = (idx + step) % 256;
	} while (found == 0);
	return 1;
}
