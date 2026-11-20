#include "Develop/Units/d2.v1/d2_window_view.h"












// SIZE 0x3cc
typedef struct Obj {
	int pad0;
	int wins[0x60];
	int count;
	char pad188[0x190 - 0x188];
	int used;
	char pad194[0x19c - 0x194];
	int shown;
	int active;
	char pad1a4[0x2bc - 0x1a4];
} Obj;
// SIZE 0x2bc

typedef struct Slot {
	char pad0[0x40];
	void* link;
	char pad44[0x2f4 - 0x44];
} Slot;
// SIZE 0x2f4

#include "client_types.h"
extern Obj_1038140 g_1038140[];

#include "Develop/Units/d2.v1/d2_gui.h"
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl fcn_00469c40(int x, int y, int slot);

/* ADDRESS: GOLDTL 0x00471b60 */
void __cdecl d2_CenterDialogWindows(int k)
{
	Obj* o;
	D2_WIN* w;
	int i;

	o = &((Obj*)g_1038140)[k];
	for (i = 0; i < o->count; i++) {
		w = &((D2_WIN*)g_1015f40)[o->wins[i]];
		if ((*(void**)&((D2_CONTROL_TL*)g_1015ea0)[w->slot].parent) == 0) {
			fcn_00469c40(d2_CenterX - w->width / 2, d2_DialogCenterY - w->height / 2, w->slot);
		}
	}
}
