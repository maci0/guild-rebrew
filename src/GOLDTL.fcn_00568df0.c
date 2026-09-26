char* __cdecl fcn_00508e40(int);

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

// FUNCTION: GOLD 0x00560b10
// SIZE: 209
// FUNCTION: GOLDTL 0x568df0
// SIZE: 209

char* __cdecl fcn_005463a0(int, int, int, ...);
char* __cdecl fcn_005462a0(void);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

void __cdecl fcn_00568df0(char* o)
{
	char* p;
	char* e;
	char* x;

	for (p = fcn_005463a0(1, 0, 0x3c); p != 0; p = fcn_005462a0()) {
		if (p != o && (*(int*) (p + 0xb4) == *(int*) (o + 0xb4) ||
		               *(int*) (p + 0xac) == *(int*) (o + 0xac))) {
			break;
		}
	}
	e = gm_StartFilteredEntitySearch(1, 1, *(int*) (o + 0xb4));
	if (p != 0 || (e != 0 && *(int*) (e + 0x65) != -1)) {
		*(int*) (o + 0x70) = -1;
	}
	x = fcn_00508e40(*(int*) (o + 0xac));
	if (x != 0 && x[0x1b1] != 0) {
		*(int*) (o + 0x70) = -1;
	}
	*(pos14_7f4c00*) (o + 0x52) = g_7f4c00;
	fcn_00500bb0((pos14_7f4c00*) (o + 0x52), 0, 0, 1);
}
