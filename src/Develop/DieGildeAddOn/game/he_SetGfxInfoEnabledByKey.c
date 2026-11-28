


#include "he_tables.h"

extern Rec7dc6e0 g_7dc6e0[64];

void __cdecl d3_SetObjectVisible(int, int);

/* ADDRESS: GOLDDE 0x0052d230 */
void __cdecl he_SetGfxInfoEnabledByKey(int k, int v)
{
	int i;

	for (i = 0; i < 0x40; i++) {
		if (g_7dc6e0[i].c == k) {
			d3_SetObjectVisible(g_7dc6e0[i].d, v);
		}
	}
}
