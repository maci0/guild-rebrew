
// y = s->y assigned after x in each arm schedules the load between the two
// divisions.

typedef struct D2_CENTER_PARENT_RECT {
	int pad0;
	int left;
	int pad8;
	int width;
} D2_CENTER_PARENT_RECT;

typedef struct D2_CENTER_ELEMENT_SLOT {
	char pad0[0x14];
	int y;
	int width;
	char pad1c[0x40 - 0x1c];
	D2_CENTER_PARENT_RECT* link;
	char pad44[0x6c - 0x44];
	int used;
	char pad70[0x2f4 - 0x70];
} D2_CENTER_ELEMENT_SLOT;
// SIZE 0x2f4

extern char* g_1015ea0;
extern int g_1040494;

void __cdecl fcn_00469c40(int x, int y, int slot);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d2_CenterElement(int slot)
{
	D2_CENTER_ELEMENT_SLOT* s;
	D2_CENTER_PARENT_RECT* r;
	int x;
	int y;

	s = (D2_CENTER_ELEMENT_SLOT*) &((D2_CONTROL_TL*) g_1015ea0)[slot];
	if (((D2_CONTROL_TL*) s)->value_06c != 0) {
		r = (D2_CENTER_PARENT_RECT*) ((D2_CONTROL_TL*) s)->parent;
		if (r != 0) {
			x = r->width / 2 - ((D2_CONTROL_TL*) s)->width / 2 + r->left;
			y = ((D2_CONTROL_TL*) s)->y;
		} else {
			x = g_1040494 / 2 - ((D2_CONTROL_TL*) s)->width / 2;
			y = ((D2_CONTROL_TL*) s)->y;
		}
		fcn_00469c40(x, y, slot);
	}
}
