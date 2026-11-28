


#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl ahm_CalcResearchDuration(int a, int b);

/* ADDRESS: GOLDDE 0x004d9170 */
int __cdecl ahm_CalcUnlockDuration(int entity, int recipe)
{
	return (int) (ahm_CalcResearchDuration(entity, recipe) * 0.1f);
}
