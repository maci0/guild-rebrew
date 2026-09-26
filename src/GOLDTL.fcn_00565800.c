void __cdecl fcn_00546190(char*);

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

// FUNCTION: GOLD 0x0055d590
// SIZE: 115
// FUNCTION: GOLDTL 0x565800
// SIZE: 115

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl fcn_0050c710(char*, int, int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

void __cdecl fcn_00565800(char* o)
{
	char* e;

	e = gm_StartFilteredEntitySearch(1, 1, *(int*) (o + 0xac));
	if (e != 0) {
		fcn_0050c710(e, 0x10, 1);
		*(pos14_7f4c00*) (o + 0x52) = g_7f4c00;
		fcn_00500bb0((pos14_7f4c00*) (o + 0x52), 0x18, 0, 0);
		*(int*) (o + 0x58) = 0;
		return;
	}
	fcn_00546190(o);
}
