


#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl ahm_CalcResearchDuration(int a, int b);

int __cdecl ahm_CalcUnlockDuration(int entity, int recipe)
{
	return (int) (ahm_CalcResearchDuration(entity, recipe) * 0.1f);
}
