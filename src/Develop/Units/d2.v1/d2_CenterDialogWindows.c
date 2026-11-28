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

#include "Develop/client_types.h"
extern D2_FORM_RECORD d2_Forms[];

#include "Develop/Units/d2.v1/d2_gui.h"
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d2_PositionControl(int x, int y, int slot);

/* ADDRESS: GOLDTL 0x00471b60 */
/* ADDRESS: GOLDDE 0x00465060 */
void __cdecl d2_CenterDialogWindows(int k)
{
	Obj* o;
	D2_WIN* w;
	int i;

	o = &((Obj*)d2_Forms)[k];
	for (i = 0; i < o->count; i++) {
		w = &((D2_WIN*)d2_Windows)[o->wins[i]];
		if ((*(void**)&((D2_CONTROL_TL*)d2_Controls)[w->slot].parent) == 0) {
			d2_PositionControl(d2_CenterX - w->width / 2, d2_DialogCenterY - w->height / 2, w->slot);
		}
	}
}
