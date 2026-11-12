#include "gold_gui.h"

extern GuiObj g_00fb1020[];
void __cdecl fcn_00474d00(int index);
void __cdecl fcn_00474d80(int index, void* a, void* b);
void __cdecl fcn_00474e70(int index);

/* ADDRESS: GOLD 0x00474c90 */
int __cdecl fcn_00474c90(int index, void* a, void* b)
{
	char* record;
	record = (char*) &g_00fb1020[index];
	if (*(int*) (record + 0x190) == 0) {
		return 0;
	}
	if (*(int*) (record + 0x198) == 0) {
		return 0;
	}
	if (a != 0 && b != 0) {
		fcn_00474d00(index);
		fcn_00474d80(index, a, b);
		fcn_00474e70(index);
	}
	return 1;
}
