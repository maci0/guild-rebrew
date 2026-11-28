extern unsigned char gm_ActiveTownIndex;

#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl gm_AmountToUnits(int, char);


/* ADDRESS: GOLDTL 0x004b4760 */
int __cdecl gm_HasMinDynastyWealth(short* e, char* thr)
{
	return gm_AmountToUnits(gm_WalkEntityChain(*e), (*(char*)&gm_ActiveTownIndex)) >= *(int*) (thr + 0x14);
}
