#include "Develop/Units/d2.v1/gold_gui.h"
#include "client_types.h"

extern GuiObj g_00fb1020[]; /* 0x00fb1020 */
extern D2_FORM_RECORD g_1038140[];

void __cdecl d2_BringWindowToFront(int id);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x00474190 */
void __cdecl d2_BringFormToFront(int k)
{
	int j;

	for (j = 0; j < g_00fb1020[k].count; j++) {
		d2_BringWindowToFront(g_00fb1020[k].wins[j]);
	}
}
#else
/* ADDRESS: GOLDTL 0x004707d0 */
void __cdecl d2_BringFormToFront(int k)
{
	int j;

	for (j = 0; j < *(int*) (((char*)g_1038140) + k * 0x2bc + 0x184); j++) {
		d2_BringWindowToFront(((int*) (((char*)g_1038140) + k * 0x2bc + 4))[j]);
	}
}
#endif
