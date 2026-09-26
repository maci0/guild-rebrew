int __cdecl fcn_004c5620(int, char*);

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

// FUNCTION: GOLD 0x0054b3c0
// SIZE: 108
// FUNCTION: GOLDTL 0x553420
// SIZE: 108

void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

void __cdecl fcn_00553420(char* o)
{
	*(int*) (o + 0x84) = -1;
	if ((o[0x78] & 4) == 0) {
		*(int*) (o + 0xb8) = -1;
		*(pos14_7f4c00*) (o + 0x52) = g_7f4c00;
		fcn_00500bb0((pos14_7f4c00*) (o + 0x52), 0, 2, 0);
		*(int*) (o + 0x70) = 1;
		*(int*) (o + 0x84) = fcn_004c5620(1, o);
	}
}
