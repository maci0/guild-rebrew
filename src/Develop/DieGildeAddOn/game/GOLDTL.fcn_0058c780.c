

typedef struct
{
	char pad0[0x38];
	int x38;
	char pad3c[0x10];
	int x4c;
	char pad50[0x2f4 - 0x50];
} Ctl;
// SIZE 0x2f4

extern char* g_1015ea0;

void __cdecl d2_SetElementEnabled(int, int);
int __cdecl gv_CheckSlotActive(void* slot, int type);
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl d2_UpdateRentGraveOptions(char* building, int unlockedCount, int unused, int* controlIds, int* selectedIndex)
{
	int r;
	int sel;
	int i;



	r = 0;
	sel = -1;
	for (i = 0; i < unlockedCount + 1; i++) {
		d2_SetElementEnabled(controlIds[i], 0);
		((D2_CONTROL_TL*) g_1015ea0)[controlIds[i]].value_038 = 0;
	}
	for (i = unlockedCount + 1; i < 4; i++) {
		if (gv_CheckSlotActive(*(void**) (building + 0x65), i)) {
			r = 1;
			d2_SetElementEnabled(controlIds[i], 1);
			if (sel == -1) {
				sel = i;
			}
		} else {
			d2_SetElementEnabled(controlIds[i], 0);
			((D2_CONTROL_TL*) g_1015ea0)[controlIds[i]].value_038 = 0;
		}
	}
	if (((D2_CONTROL_TL*) g_1015ea0)[controlIds[*selectedIndex]].disabled != 0 && sel != -1) {
		*selectedIndex = sel;
		((D2_CONTROL_TL*) g_1015ea0)[controlIds[sel]].value_038 = 1;
	}
	return r;
}
