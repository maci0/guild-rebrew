int __cdecl fcn_004c5620(int, char*);

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

// FUNCTION: GOLD 0x0054c070
// FUNCTION: GOLDTL 0x5540d0

void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

void __cdecl fcn_005540d0(char* o)
{
	if ((o[0x78] & 4) == 0) {
		*(int*) (o + 0xd4) = -1;
		o[0xdc] = 0;
		*(pos14_7f4c00*) (o + 0x44) = g_7f4c00;
		*(pos14_7f4c00*) (o + 0x52) = g_7f4c00;
		fcn_00500bb0((pos14_7f4c00*) (o + 0x52), 0, 1, 0);
		*(int*) (o + 0x84) = fcn_004c5620(0, o);
	}
}
