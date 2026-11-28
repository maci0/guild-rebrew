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
	char pad0[0x4c];
	int hidden;
	char pad50[0x2f4 - 0x50];
} Slot;
// SIZE 0x2f4

#include "Develop/client_types.h"
extern D2_FORM_RECORD d2_Forms[];
#include "Develop/Units/d2.v1/d2_gui.h"

/* ADDRESS: GOLDTL 0x00471a30 */
/* ADDRESS: GOLDDE 0x00464f30 */
void __cdecl d2_SetGroupVisibility(int k, int flag)
{
	Obj* o;
	D2_WIN* w;
	int i;
	int j;

	o = &((Obj*)d2_Forms)[k];
	if (o->used) {
		for (i = 0; i < o->count; i++) {
			w = &((D2_WIN*)d2_Windows)[o->wins[i]];
			for (j = 0; j < w->count; j++) {
				(*(int*)&((D2_CONTROL_TL*)d2_Controls)[w->children[j]].disabled) = (flag == 0);
			}
		}
		o->shown = flag;
	}
}
