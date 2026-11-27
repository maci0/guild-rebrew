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
	char pad0[0x20];
	int type;
	char pad24[0x48 - 0x24];
	int hidden;
	int pad4c;
	Obj* owner;
	char pad54[0x2f4 - 0x54];
} Slot;
// SIZE 0x2f4

#include "client_types.h"
extern D2_FORM_RECORD g_1038140[];
extern char* g_1015ea0;
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x00471af0 */
void __cdecl d2_SetFormVisibility(int formId, int visible)
{
	Obj* form;
	int i;

	form = &((Obj*)g_1038140)[formId];
	if (form->used) {
		for (i = 0; i < 0x400; i++) {
			if (((D2_CONTROL_TL*) g_1015ea0)[i].kind && *(Obj**) &((D2_CONTROL_TL*) g_1015ea0)[i].value_050 == form) {
				((D2_CONTROL_TL*) g_1015ea0)[i].value_048 = (visible == 0);
			}
		}
		form->active = visible;
	}
}
