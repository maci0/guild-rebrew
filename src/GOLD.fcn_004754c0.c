// FUNCTION: GOLD 0x004754c0
// SIZE: 187

#include "gold_gui.h"

extern GuiObj g_00fb1020[]; /* 0x00fb1020 */
extern GuiWin g_00f8f120[]; /* 0x00f8f120 */
extern GuiEnt* g_00f8f080; /* 0x00f8f080 */

void __cdecl fcn_004754c0(int k, int flag)
{
	GuiObj* o;
	GuiWin* w;
	int i;
	int j;

	o = &g_00fb1020[k];
	if (o->used) {
		for (i = 0; i < o->count; i++) {
			w = &g_00f8f120[o->wins[i]];
			for (j = 0; j < w->count; j++) {
				g_00f8f080[w->list[j]].hidden = (flag == 0);
			}
		}
		o->shown = flag;
	}
}
