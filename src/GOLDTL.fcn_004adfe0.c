#include "g_67fbb0.h"

extern int g_67fba8;
extern Entry2c* g_67fbb0;
extern int g_7728c4;
extern int g_7728c0;

/* ADDRESS: GOLDTL 0x004adfe0 */

void __cdecl fcn_004adfe0(void)
{
	int i;

	for (i = 0; i < g_67fba8; i++) {
		if (g_67fbb0[i].key == g_7728c4) {
			g_7728c0 = g_7728c4;
			if (i < g_67fba8 - 1)
				g_7728c4 = g_67fbb0[i + 1].key;
			else
				g_7728c4 = -1;
			return;
		}
	}
}
