


#include "Develop/DieGildeAddOn/game/game_data.h"

double __cdecl gm_GetCityStatsSummary(float*);

int __cdecl gm_CheckCityStatThresholds(void)
{
	float buf[10];

	if (gm_GetCityStatsSummary(buf) > 0.1)
		return 0;
	if (buf[3] < 0.3f)
		return 0;
	if (buf[1] < 0.3f)
		return 0;
	if (buf[2] < 0.3f)
		return 0;
	return 1;
}
