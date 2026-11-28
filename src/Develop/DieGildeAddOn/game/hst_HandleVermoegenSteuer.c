


extern char gm_EntityIdField[];


void* __cdecl gm_GetGuildHall(int);
void* __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl atoi(char*);
int __cdecl gm_IsSlotActivePerson(int);
#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, int, int);

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
		if (gm_IsSlotActivePerson(i) != 0) {
			cm_RequestTransferCurrencyNoKill(*(int*) (obj + 2), *(int*) (gm_EntityIdField + i * 0x21c), 0,
			    (int) ((float) gm_WalkEntityChain(*(unsigned short*) (gm_EntityIdField + i * 0x21c - 4)) * scale));
		}
	}
	return 1;
}
