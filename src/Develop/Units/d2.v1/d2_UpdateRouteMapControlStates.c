#include "Develop/Units/d2.v1/d2_gui.h"
extern char* g_772904;

struct CITY_MAP_SLOT {
	int id;
	char* obj;
	char pad8[0x10];
};
// SIZE 0x18

struct CITY_MAP_PANEL {
	char pad0[0xdc];
	struct CITY_MAP_SLOT slots[412];
	char pad277c[0x28];
	int count;
};
// SIZE 0x27a8


/* ADDRESS: GOLDTL 0x004bfca0 */
/* ADDRESS: GOLDDE 0x004ad820 */
void __cdecl d2_UpdateRouteMapControlStates(char* list, struct CITY_MAP_PANEL* panel)
{
	char* out[8];
	char** p;
	char* n;
	int i;

	for (i = 0; i < panel->count; i++) {
		if (panel->slots[i].obj != 0) {
			if (panel->slots[i].obj != g_772904) {
				*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[panel->slots[i].id].flags_1d0)) |= 1;
				*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[panel->slots[i].id].value_03c)) = 0;
			} else {
				*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[panel->slots[i].id].flags_1d0)) &= ~1;
				*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[panel->slots[i].id].value_03c)) = 1;
			}
		}
	}
	n = list;
	if (n != 0) {
		p = out;
		do {
			for (i = 0; i < panel->count; i++) {
				if (panel->slots[i].obj != 0 && *(int*) (panel->slots[i].obj + 1) == *(int*) (n + 4)) {
					*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[panel->slots[i].id].value_03c)) = 1;
					*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[panel->slots[i].id].flags_1d0)) &= ~1;
					*p++ = panel->slots[i].obj;
					break;
				}
			}
			n = *(char**) (n + 0x3c);
		} while (n != 0);
	}
}
