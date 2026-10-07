int __cdecl fcn_004c5620(int, char*);

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

// SIZE 0x10
struct slot_5595e0 {
	int a;
	int b;
	char c[4];
	int pad;
};

// FUNCTION: GOLD 0x00551510
// FUNCTION: GOLDTL 0x5595e0

void __cdecl fcn_005595e0(char* o)
{
	int i;

	*(int*) (o + 0x70) = 0;
	if ((o[0x78] & 4) == 0) {
		for (i = 0; i < 10; i++) {
			((struct slot_5595e0*) (o + 0xac))[i].a = -1;
			((struct slot_5595e0*) (o + 0xac))[i].b = -1;
			((struct slot_5595e0*) (o + 0xac))[i].c[0] = 0;
			((struct slot_5595e0*) (o + 0xac))[i].c[1] = 0;
			((struct slot_5595e0*) (o + 0xac))[i].c[2] = 0;
			((struct slot_5595e0*) (o + 0xac))[i].c[3] = 0;
		}
		*(pos14_7f4c00*) (o + 0x52) = g_7f4c00;
		*(short*) (o + 0x56) = 0xb;
		*(int*) (o + 0x58) = 0;
		*(int*) (o + 0x84) = fcn_004c5620(0, o);
	}
}
