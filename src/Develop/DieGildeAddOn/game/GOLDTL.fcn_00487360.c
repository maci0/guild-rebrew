


#include "Develop/DieGildeAddOn/game/entity_record.h"











extern unsigned short g_7f4c04;
extern unsigned char* lpGebaeudePROT;

unsigned short __cdecl gm_RandomMod(int n);
void __cdecl fcn_004f36f0(char* o);

void __cdecl fcn_00487360(char* e)
{
	short k;
	char* o;
	unsigned char kind;
	int n;
	int i;

	k = (*(short*)&g_7f4c04);
	if (k != 7 && k != 12 && k != 18) {
		*(int*) (e + 0x1b4) &= ~0x40;
		return;
	}
	if (*(int*) (e + 0x1b4) & 0x40) {
		return;
	}
	o = *(char**) (e + 0x16c);
	*(int*) (e + 0x1b4) |= 0x40;
	kind = ((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (o + 0x27)].entity_state;
	if ((kind == 6 || kind == 7) && !(*(int*) (e + 0x1b4) & 2)) {
		return;
	}
	n = 0;
	for (i = 0; i < 768; i++) {
		if (((ENTITY_RECORD*)g_7f4ca0)[i].entity_index != 0xffff && ((ENTITY_RECORD*)g_7f4ca0)[i].unk_16c == o && ((ENTITY_RECORD*)g_7f4ca0)[i].unk_165[0] != 0) {
			n++;
		}
	}
	if (n >= lpGebaeudePROT[*(unsigned char*) o * 0x24d + 0x232] + lpGebaeudePROT[*(unsigned char*) o * 0x24d + 0x231]) {
		return;
	}
	if (n != 0) {
		if (e[0x1c8] & 8) {
			return;
		}
		if (gm_RandomMod(0x48) < (0x12 - n) * 2) {
			return;
		}
	}
	fcn_004f36f0(*(char**) (e + 0x16c));
}
