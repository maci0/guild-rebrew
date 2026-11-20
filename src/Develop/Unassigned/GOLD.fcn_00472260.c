

#include "gold_gui.h"
#include "Develop/Units/d2.v1/gold_window.h"

extern GOLD_GUI_WINDOW g_00f8f120[]; /* 0x00f8f120 */
extern GuiEnt* g_00f8f080; /* 0x00f8f080 */

int __cdecl d2_AddElementToWindow(int x, int y, int a3, int win);

void __cdecl fcn_00472260(int x, int y, int win, int target, int id)
{
	int wo;

	wo = win * sizeof(GOLD_GUI_WINDOW);
	if (x == -1 && y == -1) {
		x = *(short*) ((char*) g_00f8f120 + wo + 0x8) - 0x20;
		y = *(short*) ((char*) g_00f8f120 + wo + 0xa) - 0x20;
	}
	*(int*) ((char*) g_00f8f120 + wo + 0x3ac) = d2_AddElementToWindow(x, y, id, win);
	g_00f8f080[*(int*) ((char*) g_00f8f120 + wo + 0x3ac)].target = target;
	g_00f8f080[*(int*) ((char*) g_00f8f120 + wo + 0x3ac)].flags = 3;
	x -= 0x20;
	*(int*) ((char*) g_00f8f120 + wo + 0x3a8) = d2_AddElementToWindow(x, y, id + 1, win);
	g_00f8f080[*(int*) ((char*) g_00f8f120 + wo + 0x3a8)].target = target;
	g_00f8f080[*(int*) ((char*) g_00f8f120 + wo + 0x3a8)].flags = 3;
	*(int*) ((char*) g_00f8f120 + wo + 0x248) = 0;
	g_00f8f120[target].step = 0x30;
}
