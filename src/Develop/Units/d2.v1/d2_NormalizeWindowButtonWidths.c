typedef struct Win {
	char pad0[0x28];
	int* children;
	int count;
	char pad30[0x3cc - 0x30];
} Win;
// SIZE 0x3cc

typedef struct Slot {
	char pad0[0x18];
	int w;
	char pad1c[0x20 - 0x1c];
	int type;
	char pad24[0x6c - 0x24];
	int visible;
	char pad70[0x2f4 - 0x70];
} Slot;
// SIZE 0x2f4

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;

void __cdecl d2_SetElementWidth(int slot, int w);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x0046c4e0 */
void __cdecl d2_NormalizeWindowButtonWidths(int win)
{
	Win* w;
	int maxw;
	int i;

	w = &((Win*)g_1015f40)[win];
	maxw = 0;
	for (i = 0; i < w->count; i++) {
		if (((D2_CONTROL_TL*) g_1015ea0)[w->children[i]].kind == 9 && ((D2_CONTROL_TL*) g_1015ea0)[w->children[i]].width > maxw) {
			maxw = ((D2_CONTROL_TL*) g_1015ea0)[w->children[i]].width;
		}
	}
	maxw += 8;
	if (maxw < 0x80) {
		maxw = 0x80;
	}
	for (i = 0; i < w->count; i++) {
		if (((D2_CONTROL_TL*) g_1015ea0)[w->children[i]].kind == 9) {
			((D2_CONTROL_TL*) g_1015ea0)[w->children[i]].value_06c = 1;
			d2_SetElementWidth(w->children[i], maxw);
		}
	}
}
