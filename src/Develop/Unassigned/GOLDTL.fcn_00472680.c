#include <stdlib.h>

typedef struct {
	char pad0[0x18];
	int w;
	int h;
	char pad20[0x60];
	int f80;
	char pad84[0x270];
} Slot_00472680;
// SIZE 0x2f4

#include "Develop/Units/d2.v1/d2_gui.h"

int __cdecl d2_GetElementResourceSize(int, int*, int*);

/* ADDRESS: GOLDTL 0x00472680 */
void __cdecl fcn_00472680(int id, int type)
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
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].value_080) = type;
	if (type > 1) {
		(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].width) = h0 * type;
		(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].height) = w0 * type;
	}
	if (type < -1) {
		n = abs(type);
		(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].width) = h0 / n;
		(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].height) = w0 / n;
	}
}
