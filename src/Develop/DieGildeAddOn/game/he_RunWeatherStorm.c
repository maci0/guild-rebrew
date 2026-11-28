


// SIZE 0x188
#include "Develop/client_types.h"
typedef Tabs_7e43a8 Tabs;

extern Tabs_7e43a8 gm_HourlyWeatherSlots;
extern unsigned short gm_GameTimeHour;

char* __cdecl gm_StartFilteredEntitySearch(int, ...);
unsigned short __cdecl gm_RandomMod(int n);
void __cdecl gm_AdjustGebaeudeCondition(char* o, int delta);
void __cdecl he_FreeAction(char* p);

void __cdecl he_RunWeatherStorm(char* p)
{
	int i;
	char* e;
	int d;

	switch (*(int*) (p + 0x70)) {
	case 0:
		for (i = ((*(int*)&gm_GameTimeHour) & 0xffff) + 1; i < ((*(int*)&gm_GameTimeHour) & 0xffff) + 4; i++) {
			gm_HourlyWeatherSlots.a[i] = 1000;
			gm_HourlyWeatherSlots.b[i] = 3;
		}
		*(short*) (p + 0x56) = (short) ((*(int*)&gm_GameTimeHour) + 2);
		*(int*) (p + 0x58) = 0;
		*(int*) (p + 0x70) += 1;
		return;
	case 1:
		if ((p[0x78] & 2) != 0 && p[0xec] != 0) {
			for (i = 0; i < 16; i++) {
				if (((int*) (p + 0xac))[i] != -1) {
					e = gm_StartFilteredEntitySearch(1, 1, ((int*) (p + 0xac))[i]);
					if (e != 0) {
						d = gm_RandomMod(5) + 5;
						gm_AdjustGebaeudeCondition(e, -d);
					}
				}
			}
			p[0xec] = 0;
		}
		he_FreeAction(p);
		return;
	case -1:
	case -2:
		he_FreeAction(p);
		return;
	}
}
