


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

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern int g_7763a0;
extern int g_6ad62c;
extern float g_6ad628;
extern float g_6ad630;
extern float g_6ad634;

double __cdecl sin(double);
#pragma intrinsic(sin)
int __cdecl gm_GetElapsedMinutes(GAME_TIMESTAMP*, GAME_TIMESTAMP*);

void __cdecl fcn_005e8b10(void)
{
	int r;
	GAME_TIMESTAMP s;
	float v;
	int i;

	s.unit_0 = (*(Weather*)&g_7763a0).a;
	s.hour = (unsigned short) (*(Weather*)&g_7763a0).b;
	s.minute = (*(Weather*)&g_7763a0).c;
	s.second = 0;
	r = gm_GetElapsedMinutes(&s, &(*(GAME_TIMESTAMP*)&gm_GameTime));
	v = r * (1.0f / 60.0f);
	if (!(v < 0.0f)) {
		i = (*(GAME_TIMESTAMP*)&gm_GameTime).hour;
		g_6ad62c = 0;
		(*(Weather*)&g_7763a0).phase += v * (*(Weather*)&g_7763a0).t4[i];
		g_6ad628 = (*(Weather*)&g_7763a0).t0[i];
		g_6ad630 = (*(Weather*)&g_7763a0).t1[i];
		g_6ad634 = ((float) sin((*(Weather*)&g_7763a0).phase) + 1.0f) * (*(Weather*)&g_7763a0).t3[i] * 0.5f + (*(Weather*)&g_7763a0).t2[i];
		(*(Weather*)&g_7763a0).a = (*(GAME_TIMESTAMP*)&gm_GameTime).unit_0;
		(*(Weather*)&g_7763a0).b = i;
		(*(Weather*)&g_7763a0).c = (*(GAME_TIMESTAMP*)&gm_GameTime).minute;
	}
}
