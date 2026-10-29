


#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
void __cdecl fcn_004c5420(int, int, int, int, int);

void __cdecl fcn_00553c60(char* e)
{
	char* t;

	t = gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0xb0));
	*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
	fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 2, 0);
	if (t != 0) {
		fcn_004c5420(*(int*) (t + 1), 0x5a, 2, 0x800, 0);
	}
}
