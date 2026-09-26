unsigned short __cdecl fcn_0042e410(int);

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

// FUNCTION: GOLD 0x0056dfc0
// SIZE: 147
// FUNCTION: GOLDTL 0x576400
// SIZE: 147

int __cdecl fcn_004c5620(int, char*);

void __cdecl fcn_00576400(char* o)
{
	pos14_7f4c00* p;

	if (o[0x78] & 4) {
		return;
	}
	p = (pos14_7f4c00*) (o + 0x52);
	*p = g_7f4c00;
	if (*(unsigned short*) (o + 0x56) > 0x13) {
		((pos14_7f4c00*) (o + 0x52))->a++;
		*(short*) (o + 0x56) = 0xd;
	} else if (*(unsigned short*) (o + 0x56) < 9) {
		*(short*) (o + 0x56) = fcn_0042e410(8) + 9;
	}
	*(int*) (o + 0xac) = 0;
	*(int*) (o + 0xb0) = -1;
	*(int*) (o + 0xb4) = -1;
	*(int*) (o + 0x84) = fcn_004c5620(0, o);
}
