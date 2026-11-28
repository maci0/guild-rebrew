#include "Develop/Units/d2.v1/gold_gui.h"
#include "Develop/client_types.h"

extern GuiObj g_00fb1020[]; /* 0x00fb1020 */
extern D2_FORM_RECORD d2_Forms[];

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
/* ADDRESS: GOLDDE 0x00463d10 */
void __cdecl d2_BringFormToFront(int k)
{
	int j;

	for (j = 0; j < *(int*) (((char*)d2_Forms) + k * 0x2bc + 0x184); j++) {
		d2_BringWindowToFront(((int*) (((char*)d2_Forms) + k * 0x2bc + 4))[j]);
	}
}
#endif
