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

extern char* g_1015ea0;

int __cdecl fcn_00472050(int, int*, int*);

/* ADDRESS: GOLDTL 0x00472680 */
void __cdecl fcn_00472680(int id, int type)
{
	int w;
	int h;
	int n;
	int w0;
	int h0;

	if (id == -1) {
		return;
	}
	if (fcn_00472050(id, &w, &h) == 0) {
		fcn_00472050(id, &w, &h);
		return;
	}
	w0 = w;
	h0 = h;
	((Slot_00472680*) g_1015ea0)[id].f80 = type;
	if (type > 1) {
		((Slot_00472680*) g_1015ea0)[id].w = w0 * type;
		((Slot_00472680*) g_1015ea0)[id].h = h0 * type;
	}
	if (type < -1) {
		n = abs(type);
		((Slot_00472680*) g_1015ea0)[id].w = w0 / n;
		((Slot_00472680*) g_1015ea0)[id].h = h0 / n;
	}
}
