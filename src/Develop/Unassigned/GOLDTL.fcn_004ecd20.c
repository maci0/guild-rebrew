


#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl ahm_CalcResearchDuration(int a, int b);

int __cdecl fcn_004ecd20(int a, int b)
{
	return (int) (ahm_CalcResearchDuration(a, b) * 0.1f);
}
