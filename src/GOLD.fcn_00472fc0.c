

#include <string.h>

#include "gold_gui.h"

extern GuiWin g_00f8f120[]; /* 0x00f8f120 */
extern GuiEnt** g_006ed964; /* 0x006ed964 */

void __cdecl fcn_00472f40(int id);

void __cdecl fcn_00472fc0(int win)
{
	GuiWin* w;
	GuiEnt* tmp[0x181];
	int i;
	int first;
	int last;
	int n;

	first = -1;
	last = -1;
	w = &g_00f8f120[win];
	for (i = 0x2ff; i >= 0; i--) {
		if (g_006ed964[i] != 0 && g_006ed964[i]->id == w->id) {
			last = i;
			break;
		}
		if (g_006ed964[i] != 0 && g_006ed964[i]->parent == w && first == -1) {
			first = i;
		}
	}
	if (first == -1) {
		first = last;
	}
	n = (first - last) * 4 + 4;
	memcpy(tmp, &g_006ed964[last], n);
	memmove(&g_006ed964[last], &g_006ed964[first + 1], 0xbf8 - first * 4);
	for (i = 0x2ff; i >= 0; i--) {
		if (g_006ed964[i] != 0) {
			break;
		}
	}
	memcpy(&g_006ed964[i + 1], tmp, n);
	for (i = 0; i < w->count; i++) {
		fcn_00472f40(w->list[i]);
	}
}
