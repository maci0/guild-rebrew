// FUNCTION: GOLD 0x004e5180
// SIZE: 39
// FUNCTION: GOLDTL 0x4e6b10
// SIZE: 39

#include <string.h>

char* __cdecl fcn_004e6a30(int);

void __cdecl fcn_004e6b10(int a1)
{
	char* p;

	p = fcn_004e6a30(a1);
	if (p != 0) {
		memset(p, 0, 0x114);
		*(int*) p = -1;
	}
}
