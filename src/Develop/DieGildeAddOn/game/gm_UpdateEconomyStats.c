#include "Develop/DieGildeAddOn/game/client_data.h"
extern float gm_CityPopulation, gm_TargetCityPopulation, g_99ec14, gm_LastCityPopTime[];
extern char gm_CityStatsBuffer[];
void __cdecl gm_CollectOccupancyStats(void*);
void __cdecl cm_RequestUpdateEconomyStats(void*);
void* __cdecl memcpy(void* dst, const void* src, unsigned int n);

/* ADDRESS: GOLDTL 0x004fb390 */
/* ADDRESS: GOLDDE 0x004e70a0 */
void __cdecl gm_UpdateEconomyStats(void)
{
	int buf[0x19];
	float sample;
	float slope;

	gm_CollectOccupancyStats(buf);
	memcpy((void*) (gm_CityStatsBuffer + 0x0), buf, 0x28);
	if (gm_CityPopulation == 0.0f) {
		sample = *(float*) &buf[5];
		gm_TargetCityPopulation = (float) sample;
		gm_CityPopulation = *(float*) &buf[5] * 0.95;
	} else {
		sample = gm_TargetCityPopulation + (*(float*) &buf[5] - gm_TargetCityPopulation) * 0.5f;
		gm_TargetCityPopulation = (float) sample;
	}
	*(float*) (gm_CityStatsBuffer + 0x14) = (float) sample;
	*(int*) (gm_CityStatsBuffer + 0x18) = *(int*) &gm_CityPopulation;
	slope = (sample - gm_CityPopulation) * 0.0007336182331406322;
	g_99ec14 = (float) slope;
	*(int*) ((char*) buf + 0x28) = *(int*) gm_CityStatsBuffer;
	*(int*) ((char*) buf + 0x2c) = *(int*) (gm_CityStatsBuffer + 4);
	*(int*) ((char*) buf + 0x30) = *(int*) (gm_CityStatsBuffer + 8);
	*(int*) ((char*) buf + 0x34) = *(int*) (gm_CityStatsBuffer + 0xc);
	*(int*) ((char*) buf + 0x38) = *(int*) (gm_CityStatsBuffer + 0x10);
	*(float*) ((char*) buf + 0x3c) = (float) sample;

	*(int*) ((char*) buf + 0x40) = *(int*) &gm_CityPopulation;
	*(int*) ((char*) buf + 0x44) = *(int*) (gm_CityStatsBuffer + 0x1c);
	*(int*) ((char*) buf + 0x48) = *(int*) (gm_CityStatsBuffer + 0x20);
	*(int*) ((char*) buf + 0x4c) = *(int*) (gm_CityStatsBuffer + 0x24);
	*(float*) ((char*) buf + 0x50) = (float) slope;
	*(int*) ((char*) buf + 0x54) = gm_GameTime.a;
	*(int*) ((char*) buf + 0x58) = gm_GameTime.b;
	*(int*) ((char*) buf + 0x5c) = gm_GameTime.c;
	*(short*) ((char*) buf + 0x60) = gm_GameTime.d;
	*(int*) gm_LastCityPopTime = gm_GameTime.a;
	*(int*) ((char*) gm_LastCityPopTime + 4) = gm_GameTime.b;
	*(int*) ((char*) gm_LastCityPopTime + 8) = gm_GameTime.c;
	*(short*) ((char*) gm_LastCityPopTime + 12) = gm_GameTime.d;
	cm_RequestUpdateEconomyStats((char*) buf + 0x28);
}
