#include <stdlib.h>
#include "gold_gui.h"
extern GuiEnt* g_00f8f080;
int __cdecl fcn_004759e0(int, int*, int*);

/* ADDRESS: GOLD 0x00475e70 */
void __cdecl d2_SetElementScale(int id, int scale)
{
	int w;
	int idx;
	int d;
	int cw;
	int ch;

	if (id == -1) {
		return;
	}
	idx = id;
	if (!fcn_004759e0(idx, &w, &id)) {
		fcn_004759e0(idx, &w, &id);
		return;
	}
	ch = id;
	cw = w;
	*(int*) ((char*) &g_00f8f080[idx] + 0x70) = scale;
	if (scale > 1) {
		g_00f8f080[idx].w = (short) (cw * scale);
		g_00f8f080[idx].f16 = (short) (ch * scale);
	}
	if (scale < -1) {
		d = abs(scale);
		g_00f8f080[idx].w = (short) (cw / d);
		g_00f8f080[idx].f16 = (short) (ch / d);
	}
}
