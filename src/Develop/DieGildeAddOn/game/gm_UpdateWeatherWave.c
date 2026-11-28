


#include "Develop/DieGildeAddOn/game/game_timestamp.h"
// SIZE 0xe








// SIZE 0x1f0
typedef struct {
	int a;
	int b;
	int c;
	float t0[24];
	float t1[24];
	float t2[24];
	float t3[24];
	float t4[24];
	float phase;
} Weather;

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern int g_7763a0;
extern int g_6ad62c;
extern float g_6ad628;
extern float g_6ad630;
extern float g_6ad634;

double __cdecl sin(double);
#pragma intrinsic(sin)
int __cdecl gm_GetElapsedMinutes(GAME_TIMESTAMP*, GAME_TIMESTAMP*);

void __cdecl gm_UpdateWeatherWave(void)
{
	int elapsedMinutes;
	GAME_TIMESTAMP ts;
	float elapsedHours;
	int hour;

	ts.unit_0 = (*(Weather*)&g_7763a0).a;
	ts.hour = (unsigned short) (*(Weather*)&g_7763a0).b;
	ts.minute = (*(Weather*)&g_7763a0).c;
	ts.second = 0;
	elapsedMinutes = gm_GetElapsedMinutes(&ts, &(*(GAME_TIMESTAMP*)&gm_GameTime));
	elapsedHours = elapsedMinutes * (1.0f / 60.0f);
	if (!(elapsedHours < 0.0f)) {
		hour = (*(GAME_TIMESTAMP*)&gm_GameTime).hour;
		g_6ad62c = 0;
		(*(Weather*)&g_7763a0).phase += elapsedHours * (*(Weather*)&g_7763a0).t4[hour];
		g_6ad628 = (*(Weather*)&g_7763a0).t0[hour];
		g_6ad630 = (*(Weather*)&g_7763a0).t1[hour];
		g_6ad634 = ((float) sin((*(Weather*)&g_7763a0).phase) + 1.0f) * (*(Weather*)&g_7763a0).t3[hour] * 0.5f + (*(Weather*)&g_7763a0).t2[hour];
		(*(Weather*)&g_7763a0).a = (*(GAME_TIMESTAMP*)&gm_GameTime).unit_0;
		(*(Weather*)&g_7763a0).b = hour;
		(*(Weather*)&g_7763a0).c = (*(GAME_TIMESTAMP*)&gm_GameTime).minute;
	}
}
