


#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl fcn_004c64b0(int, int, int, int, int, int, char*);

void __cdecl he_ScheduleSabotage(char* e)
{
	char* t;

	*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
	gm_AddTime((pos14_7f4c00*) (e + 0x52), 0, 1, 0);
	if (*(int*) (e + 0x10) == -1) {
		t = gm_StartFilteredEntitySearch(1, 5, 0x16);
		if (t != 0 || (t = gm_StartFilteredEntitySearch(1, 5, 0xf)) != 0) {
			*(int*) (e + 0x10) = *(int*) (t + 1);
		}
	}
	*(int*) (e + 0xc4) = -1;
	*(int*) (e + 0xc8) = fcn_004c64b0(0, *(int*) (e + 0x10), -1, 0, 1, 0x174, "SABOTAGE");
}
