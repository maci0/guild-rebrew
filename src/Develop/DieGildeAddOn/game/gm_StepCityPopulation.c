

#pragma pack(push, 2)
typedef struct
{
	int a;
	unsigned short b;
	short b2;
	int c;
	short d;
} Blob14;
// SIZE 0xe
#pragma pack(pop)

extern Blob14 gm_LastCityPopTime;
#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern float gm_CityPopulation;
extern float gm_TargetCityPopulation;
extern float g_99ec14;
extern float flt_0_0;
extern double g_662ad8;

int __cdecl gm_GetElapsedMinutes(Blob14* a, Blob14* b);

/* ADDRESS: GOLDDE 0x004e7dd0 */
void __cdecl gm_StepCityPopulation(void)
{
	int r;
	double lim;

	r = gm_GetElapsedMinutes(&gm_LastCityPopTime, &(*(Blob14*)&gm_GameTime));
	if (r == 0) {
		gm_LastCityPopTime = (*(Blob14*)&gm_GameTime);
		return;
	}
	if (gm_TargetCityPopulation != flt_0_0 && (*(Blob14*)&gm_GameTime).b > 6 && (*(Blob14*)&gm_GameTime).b < 0x15) {
		gm_CityPopulation += r * g_99ec14;
		lim = gm_TargetCityPopulation * 0.25;
		if (gm_CityPopulation < lim) {
			gm_CityPopulation = (float) lim;
		}
		gm_LastCityPopTime = (*(Blob14*)&gm_GameTime);
	}
}
unsigned char _dpad_99f590[80];
