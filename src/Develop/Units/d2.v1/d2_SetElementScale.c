#include <stdlib.h>
#include "Develop/Units/d2.v1/gold_gui.h"
#include "Develop/Units/d2.v1/d2_gui.h"

typedef struct {
	char pad0[0x18];
	int w;
	int h;
	char pad20[0x60];
	int f80;
	char pad84[0x270];
} D2_ELEMENT_SCALE_SLOT;
// SIZE 0x2f4

extern GuiEnt* g_00f8f080;

int __cdecl d2_QueryElementResourceSize(int, int*, int*);
int __cdecl d2_GetElementResourceSize(int, int*, int*);

#if defined(REBREW_GOLD)
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
	if (!d2_QueryElementResourceSize(idx, &w, &id)) {
		d2_QueryElementResourceSize(idx, &w, &id);
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
#else
/* ADDRESS: GOLDTL 0x00472680 */
/* ADDRESS: GOLDDE 0x00465870 */
void __cdecl d2_SetElementScale(int id, int scale)
{
	int h;
	int w;
	int n;
	int w0;
	int h0;

	if (id == -1) {
		return;
	}
	if (d2_GetElementResourceSize(id, &h, &w) == 0) {
		d2_GetElementResourceSize(id, &h, &w);
		return;
	}
	w0 = w;
	h0 = h;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].value_080) = scale;
	if (scale > 1) {
		(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].width) = h0 * scale;
		(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].height) = w0 * scale;
	}
	if (scale < -1) {
		n = abs(scale);
		(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].width) = h0 / n;
		(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].height) = w0 / n;
	}
}
#endif
