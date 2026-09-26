void __cdecl fcn_00546190(char*);

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

// FUNCTION: GOLD 0x00552770
// SIZE: 119
// FUNCTION: GOLDTL 0x55a860
// SIZE: 119

void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
int __cdecl fcn_004c5620(int, char*);

void __cdecl fcn_0055a860(char* o)
{
	if (*(int*) (o + 0x70) < 0 || *(int*) (o + 0xac) <= 0) {
		fcn_00546190(o);
		return;
	}
	if ((o[0x78] & 4) == 0) {
		(*(int*) (o + 0xac))--;
		*(pos14_7f4c00*) (o + 0x52) = g_7f4c00;
		fcn_00500bb0((pos14_7f4c00*) (o + 0x52), 0x18, 0, 0);
		*(int*) (o + 0x84) = fcn_004c5620(0, o);
	}
}
