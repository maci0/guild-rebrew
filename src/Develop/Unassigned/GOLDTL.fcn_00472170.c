typedef struct Slot {
	int id;
	int used;
	int value;
	char* data;
	int x;
	int y;
	int w;
	int h;
	int type;
	char pad24[0x38 - 0x24];
	int text;
	char pad3c[0x48 - 0x3c];
	int hidden;
	char pad4c[0x58 - 0x4c];
	int dirty;
	char pad5c[0x88 - 0x5c];
	int result;
	char* buf;
	char pad90[0x2f4 - 0x90];
} Slot;
// SIZE 0x2f4
#include "Develop/Units/d2.v1/d2_window_view.h"












// SIZE 0x3cc

extern char* g_1015ea0;
#include "client_types.h"

#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x00472170 */
void __cdecl d2_SetSlotVisibility(int slot, int flag)
{
	Slot* s;
	D2_WIN* w;
	int i;

	s = (Slot*) &((D2_CONTROL_TL*) g_1015ea0)[slot];
	((D2_CONTROL_TL*) s)->value_048 = (flag == 0);
	if (((D2_CONTROL_TL*) s)->kind == 0x40) {
		w = &((D2_WIN*)g_1015f40)[((D2_CONTROL_TL*) s)->value_088];
		for (i = 0; i < w->count; i++) {
			d2_SetSlotVisibility(w->children[i], flag);
		}
	}
}
