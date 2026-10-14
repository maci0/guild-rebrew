

#include "gold_gui.h"

extern GuiWin g_00f8f120[]; /* 0x00f8f120 */
extern GuiEnt* g_00f8f080; /* 0x00f8f080 */

int __cdecl fcn_004731c0(int x, int y, int a3, int win);

void __cdecl fcn_00472260(int x, int y, int win, int target, int id)
{
	int wo;

	wo = win * sizeof(GuiWin);
	if (x == -1 && y == -1) {
		x = *(short*) ((char*) g_00f8f120 + wo + 0x8) - 0x20;
		y = *(short*) ((char*) g_00f8f120 + wo + 0xa) - 0x20;
	}
	*(int*) ((char*) g_00f8f120 + wo + 0x3ac) = fcn_004731c0(x, y, id, win);
	g_00f8f080[*(int*) ((char*) g_00f8f120 + wo + 0x3ac)].target = target;
	g_00f8f080[*(int*) ((char*) g_00f8f120 + wo + 0x3ac)].flags = 3;
	x -= 0x20;
	*(int*) ((char*) g_00f8f120 + wo + 0x3a8) = fcn_004731c0(x, y, id + 1, win);
	g_00f8f080[*(int*) ((char*) g_00f8f120 + wo + 0x3a8)].target = target;
	g_00f8f080[*(int*) ((char*) g_00f8f120 + wo + 0x3a8)].flags = 3;
	*(int*) ((char*) g_00f8f120 + wo + 0x248) = 0;
	g_00f8f120[target].f264 = 0x30;
}
