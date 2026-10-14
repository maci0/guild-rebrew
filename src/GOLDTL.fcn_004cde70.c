


char* __cdecl fcn_00501510(int);
#include "Develop/DieGildeAddOn/game/spiel.h"

int __cdecl fcn_004cde70(char* a1, char* a2)
{
	char* p;

	if (a2 != 0) {
		a2[0] = 2;
		a2[1] = 0;
		*(int*) (a2 + 6) = 0;
	}
	p = fcn_00501510(*(int*) (a1 + 0x10));
	if (p == 0) {
		return -1;
	}
	if (*(int*) (p + 0x29) != 0) {
		fcn_004be280(*(char**) (p + 0x29));
		*(int*) (p + 0x29) = 0;
	}
	if (a2 != 0) {
		*a2 = 1;
	}
	return 0;
}
