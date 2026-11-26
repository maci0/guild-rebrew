


extern char g_7f4ca4[];


void* __cdecl gm_GetGuildHall(int);
void* __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl atoi(char*);
int __cdecl fcn_004ae130(int);
#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl fcn_004c51a0(int, int, int, int);

int __cdecl hst_HandleVermoegenSteuer(int sel, int id, char* arg)
{
	void* city;
	char* obj;
	float scale;
	int i;

	city = gm_GetGuildHall(1);
	if (city == 0)
		return 0;
	obj = fcn_00502cd0(*(int*) ((char*) city + 0x5d), 2, 6, 0, 0x115);
	if (obj == 0)
		return 0;
	if (*arg != '-')
		return 0;
	scale = (float) atoi(arg + 1) * 0.01f;
	for (i = 0; i < 0x300; i++) {
		if (fcn_004ae130(i) != 0) {
			fcn_004c51a0(*(int*) (obj + 2), *(int*) (g_7f4ca4 + i * 0x21c), 0,
			    (int) ((float) gm_WalkEntityChain(*(unsigned short*) (g_7f4ca4 + i * 0x21c - 4)) * scale));
		}
	}
	return 1;
}
