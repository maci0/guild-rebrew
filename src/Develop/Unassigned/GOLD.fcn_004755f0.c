

#include "gold_gui.h"
#include "Develop/Units/d2.v1/gold_window.h"

extern GuiObj g_00fb1020[]; /* 0x00fb1020 */
extern GOLD_GUI_WINDOW g_00f8f120[]; /* 0x00f8f120 */
extern GuiEnt* g_00f8f080; /* 0x00f8f080 */
extern int g_00f8f088; /* 0x00f8f088 */
extern int g_00f8f08c; /* 0x00f8f08c */

void __cdecl fcn_0046cd90(int x, int y, int slot);

void __cdecl fcn_004755f0(int k)
{
	GuiObj* o;
	GOLD_GUI_WINDOW* w;
	int i;

	o = &g_00fb1020[k];
	for (i = 0; i < o->count; i++) {
		w = &g_00f8f120[o->wins[i]];
		if (g_00f8f080[w->id].parent == 0) {
			fcn_0046cd90(g_00f8f08c - w->width / 2, g_00f8f088 - w->height / 2, w->id);
		}
	}
}
