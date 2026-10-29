#include "g_7f4ca2.h"

extern char g_776708;

extern Slot7f4ca2 g_7f4ca2[768];




#include "Develop/DieGildeAddOn/game/spiel.h"

int __cdecl fcn_00527000(void)
{
	int r;
	int i;
	int k;

	r = 0x534;
	if (g_776708 == 0) {
		for (i = 0; i < 768; i++) {
			if (g_7f4ca2[i].kind == 6 || g_7f4ca2[i].kind == 7) {
				break;
			}
		}
		k = gm_MapEntityStatRange(g_7f4ca2[i].b);
		if (k == 1 || k == 2 || k == 10) {
			r = 0x534;
		} else if (k == 3 || k == 4) {
			r = 0x538;
		} else if (k == 11 || k == 12 || k == 6) {
			r = 0x53c;
		} else if (k == 5 || k == 7 || k == 8 || k == 9) {
			r = 0x540;
		}
	} else if (g_776708 == 1) {
		r = 0x534;
	} else if (g_776708 == 2) {
		r = 0x538;
	} else if (g_776708 == 3) {
		r = 0x53c;
	} else if (g_776708 == 4) {
		r = 0x540;
	}
	return r;
}
