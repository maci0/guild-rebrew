#include "client_types.h"
typedef Group_102cbc4 Group;
// SIZE 0x8c

extern Group_102cbc4 g_102cbc4[8];

#include "Develop/Units/d2.v1/d2_gui.h"

/* ADDRESS: GOLD 0x0046c620 */
/* ADDRESS: GOLDTL 0x004695a0 */
void __cdecl fcn_004695a0(int g, int sel)
{
	int i;

	for (i = 0; i < g_102cbc4[g].count; i++) {
		if (i != sel) {
			d2_SetElementValue(g_102cbc4[g].ids[i], 0);
		} else {
			d2_SetElementValue(g_102cbc4[g].ids[i], 1);
		}
	}
	g_102cbc4[g].sel = sel;
}
