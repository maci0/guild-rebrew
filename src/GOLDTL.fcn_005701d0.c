extern char g_77e020[];

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

// FUNCTION: GOLD 0x00567e20
// SIZE: 120
// FUNCTION: GOLDTL 0x5701d0
// SIZE: 120

char* __cdecl fcn_005463a0(int, int, int, ...);
void __cdecl fcn_00508cf0(int, char*);

void __cdecl fcn_005701d0(char* o)
{
	pos14_7f4c00* p;

	p = (pos14_7f4c00*) (o + 0x52);
	*p = g_7f4c00;
	if (fcn_005463a0(1, 0, 0x83) != 0) {
		p->a = g_7f4c00.a + 4;
	} else {
		p->a = g_7f4c00.a;
	}
	*(short*) (o + 0x56) = 8;
	*(int*) (o + 0x58) = 0;
	fcn_00508cf0(0x1a, g_77e020);
}
