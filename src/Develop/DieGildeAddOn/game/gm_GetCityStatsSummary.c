extern float flt_0_0;
extern float flt_0_0;
extern char gm_CityStatsBuffer[];
extern char gm_CityStatsBuffer[];
#include "Develop/DieGildeAddOn/game/game_data.h"



#include <string.h>

#pragma intrinsic(memcpy, memset)

float __cdecl gm_GetCityStatsSummary(char* p)
{
	float v;

	if (p == 0) {
		return *(float*) ((char*)&flt_0_0);
	}
	memcpy(p, (void*) gm_CityStatsBuffer, 40);
	v = *(float*) (p + 0x24);
	*(int*) (p + 0x18) = *(int*) ((char*)&gm_CityPopulation);
	return v;
}
