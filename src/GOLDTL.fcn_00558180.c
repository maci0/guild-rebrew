void __cdecl fcn_00546190(char*);

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

// FUNCTION: GOLD 0x005500d0
// SIZE: 145
// FUNCTION: GOLDTL 0x558180
// SIZE: 145

char* __cdecl fcn_005c61e0(int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

void __cdecl fcn_00558180(char* o)
{
	char* t;

	*(pos14_7f4c00*) (o + 0x52) = g_7f4c00;
	t = fcn_005c61e0(0x178);
	if (t != 0 && *(int*) (t + 4) != 0) {
		*(pos14_7f4c00*) (o + 0xb0) = g_7f4c00;
		fcn_00500bb0((pos14_7f4c00*) (o + 0xb0), 0, *(int*) (t + 4), 0);
		return;
	}
	fcn_00546190(o);
}
