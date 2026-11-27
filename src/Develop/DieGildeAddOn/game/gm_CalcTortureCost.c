#include "g_664260.h"

extern Mult664260 g_664260[7];

#include "Develop/DieGildeAddOn/game/spiel.h"

/* ADDRESS: GOLDTL 0x00493ee0 */
int __cdecl gm_CalcTortureCost(unsigned short* entityA, unsigned short* entityB, int key)
{
	int baseCost;
	int i;

	baseCost = (int) ((gm_WalkEntityChain(*entityA) + gm_WalkEntityChain(*entityB)) * 0.0005f);
	for (i = 0; i < 7; i++) {
		if (g_664260[i].key == key) {
			return g_664260[i].mult * baseCost;
		}
	}
	return baseCost * 10;
}
