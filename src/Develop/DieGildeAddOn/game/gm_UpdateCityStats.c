#include <string.h>
#include "Develop/client_types.h"

#pragma pack(push, 2)
typedef struct
{
	int a;
	unsigned short b;
	short b2;
	int c;
	short d;
} Blob14;
#pragma pack(pop)

extern Blob14 gm_LastCityPopTime;
extern pos14_7f4c00 gm_GameTime;
extern char gm_CityStatsBuffer[];
extern float gm_CityPopulation, gm_TargetCityPopulation, g_773d54, g_99ec14, g_6628cc;

#pragma intrinsic(memcpy)

float __cdecl gm_GetCityStatsSummary(char* p);

/* ADDRESS: GOLDTL 0x004fb2c0 */
int __cdecl gm_UpdateCityStats(void)
{
	float buf[10];
	float v;
	double d;

	v = gm_GetCityStatsSummary((char*) buf);
	if (gm_CityPopulation == 0.0f) {
		memcpy(gm_CityStatsBuffer, buf, 40);
		d = ((double) v + 1.0) * g_773d54;
		gm_TargetCityPopulation = (float) d;
		gm_CityPopulation = (float) (d * 0.95);
	} else {
		memcpy(gm_CityStatsBuffer, buf, 40);
		d = ((double) v + 1.0) * g_773d54;
		gm_TargetCityPopulation = (float) ((d - gm_TargetCityPopulation) * g_6628cc + gm_TargetCityPopulation);
	}
	g_99ec14 = (float) ((gm_TargetCityPopulation - gm_CityPopulation) * 0.0007336182331406322);
	gm_LastCityPopTime = *(Blob14*) &gm_GameTime;
	return (int) gm_TargetCityPopulation;
}
