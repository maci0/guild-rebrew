#include "client_types.h"
typedef Group_102cbc4 Group;
// SIZE 0x8c

typedef struct Slot {
	char pad0[0x58];
	int dirty;
	char pad5c[0x1d0 - 0x5c];
	int flags;
	char pad1d4[0x2f4 - 0x1d4];
} Slot;
// SIZE 0x2f4

extern Group_102cbc4 g_102cbc4[8];
extern char* g_1015ea0;

void __cdecl d2_SelectRadioGroup(int g, int sel);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x00469470 */
void __cdecl fcn_00469470(int g, int id)
{
	g_102cbc4[g].ids[g_102cbc4[g].count] = id;
	((D2_CONTROL_TL*) g_1015ea0)[id].value_058 = 1;
	((D2_CONTROL_TL*) g_1015ea0)[id].flags_1d0 &= ~2;
	g_102cbc4[g].count++;
	if (g_102cbc4[g].sel == -1) {
		d2_SelectRadioGroup(g, 0);
	}
}
