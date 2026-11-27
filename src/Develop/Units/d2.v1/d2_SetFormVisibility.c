#include "client_types.h"
#include "gold_gui.h"
#include "Develop/Units/d2.v1/d2_gui.h"

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
/* SIZE 0x2bc */

typedef struct Slot {
	char pad0[0x20];
	int type;
	char pad24[0x48 - 0x24];
	int hidden;
	int pad4c;
	Obj* owner;
	char pad54[0x2f4 - 0x54];
} Slot;
/* SIZE 0x2f4 */

extern GuiObj g_00fb1020[];
extern GuiEnt* g_00f8f080;
void __cdecl d2_ApplyElementEnabled(int index, int value);

extern D2_FORM_RECORD g_1038140[];
extern char* g_1015ea0;

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x00475580 */
void __cdecl d2_SetFormVisibility(int index, int value)
{
    GuiObj* object;
    int i;

    object = &g_00fb1020[index];
    if (object->used != 0) {
        for (i = 0; i < 0x300; i++) {
            if (g_00f8f080[i].kind != 0 &&
                g_00f8f080[i].f40 == (int) object) {
                d2_ApplyElementEnabled(i, value);
            }
        }
        *(int*) ((char*) object + 0x1a0) = value;
    }
}
#else
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
#endif
