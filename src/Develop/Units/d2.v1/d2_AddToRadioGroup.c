#include "Develop/Units/d2.v1/gold_gui.h"
#include "client_types.h"
#include "Develop/Units/d2.v1/d2_gui.h"

typedef struct Group {
	int count;
	int sel;
	int ids[33];
} Group;
// SIZE 0x8c

extern Group g_00fa5aa4[8]; /* 0x00fa5aa4 */
extern GuiEnt* g_00f8f080; /* 0x00f8f080 */
extern D2_RADIO_GROUP g_102cbc4[8];
extern char* g_1015ea0;

void __cdecl fcn_0046c620(int g, int sel);
void __cdecl d2_SelectRadioGroup(int g, int sel);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x0046c550 */
void __cdecl d2_AddToRadioGroup(int g, int id)
{
	g_00fa5aa4[g].ids[g_00fa5aa4[g].count] = id;
	g_00f8f080[id].dirty = 1;
	g_00f8f080[id].flags &= ~2;
	g_00fa5aa4[g].count++;
	if (g_00fa5aa4[g].sel == -1) {
		fcn_0046c620(g, 0);
	}
}
#else
/* ADDRESS: GOLDTL 0x00469470 */
void __cdecl d2_AddToRadioGroup(int g, int id)
{
	g_102cbc4[g].ids[g_102cbc4[g].count] = id;
	((D2_CONTROL_TL*) g_1015ea0)[id].value_058 = 1;
	((D2_CONTROL_TL*) g_1015ea0)[id].flags_1d0 &= ~2;
	g_102cbc4[g].count++;
	if (g_102cbc4[g].sel == -1) {
		d2_SelectRadioGroup(g, 0);
	}
}
#endif
