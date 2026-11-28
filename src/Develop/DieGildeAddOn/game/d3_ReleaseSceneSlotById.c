


#include "he_tables.h"

extern Rec7dc6e0 g_7dc6e0[64];

void __cdecl d3_FreeEventGfxSlot(Rec7dc6e0*);

/* ADDRESS: GOLDDE 0x0052d200 */
void __cdecl d3_ReleaseSceneSlotById(int k)
{
	int i;

	for (i = 0; i < 0x40; i++) {
		if (g_7dc6e0[i].c == k) {
			d3_FreeEventGfxSlot(&g_7dc6e0[i]);
		}
	}
}
