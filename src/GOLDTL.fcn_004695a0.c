#include "client_types.h"
typedef Group_102cbc4 Group;
// SIZE 0x8c

extern Group_102cbc4 g_102cbc4[8];

void __cdecl fcn_00472380(int id, int on);

// FUNCTION: GOLD 0x0046c620
// FUNCTION: GOLDTL 0x4695a0
void __cdecl fcn_004695a0(int g, int sel)
{
	int i;

	for (i = 0; i < g_102cbc4[g].count; i++) {
		if (i != sel) {
			fcn_00472380(g_102cbc4[g].ids[i], 0);
		} else {
			fcn_00472380(g_102cbc4[g].ids[i], 1);
		}
	}
	g_102cbc4[g].sel = sel;
}
