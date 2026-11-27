

#include "gold_gui.h"

extern GuiObj g_00fb1020[]; /* 0x00fb1020 */

void __cdecl d2_BringWindowToFront(int id);

void __cdecl fcn_00474190(int k)
{
	int j;

	for (j = 0; j < g_00fb1020[k].count; j++) {
		d2_BringWindowToFront(g_00fb1020[k].wins[j]);
	}
}
