#include "g_664260.h"

extern Mult664260 g_664260[7];

#include "Develop/DieGildeAddOn/game/spiel.h"

/* ADDRESS: GOLDTL 0x00493ee0 */
int __cdecl fcn_00493ee0(unsigned short* a, unsigned short* b, int key)
{
	int v;
	int i;

	v = (int) ((gm_WalkEntityChain(*a) + gm_WalkEntityChain(*b)) * 0.0005f);
	for (i = 0; i < 7; i++) {
		if (g_664260[i].key == key) {
			return g_664260[i].mult * v;
		}
	}
	return v * 10;
}
