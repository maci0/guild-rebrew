#include "gold_gui.h"
#include "Develop/Units/d2.v1/gold_window.h"

extern GuiObj g_00fb1020[];
extern GOLD_GUI_WINDOW g_00f8f120[];

/* ADDRESS: GOLD 0x00475b70 */
int __cdecl fcn_00475b70(int group, int item, int index)
{
	GOLD_GUI_WINDOW* p;

	if (group != -1) {
		p = &g_00f8f120[g_00fb1020[group].wins[item]];
	} else {
		p = &g_00f8f120[item];
	}
	if (index > p->count)
		return -1;
	return p->list[index];
}
