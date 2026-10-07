#include "g_688118.h"
// GLOBAL: GOLDTL 0x688118
extern IdGroup g_688118[];
// GLOBAL: GOLD 0x6094b0
extern IdGroup g_688118[];
// FUNCTION: GOLD 0x004c1f90
// FUNCTION: GOLDTL 0x4c27f0

int __cdecl fcn_004c27f0(void)
{
	int i;
	int v;
	char* p;

	i = 0;
	p = (char*) g_688118;
	do {
		if (p[0x112] != 0) {
			return i;
		}
		v = *(int*) p;
		i++;
		p += 0x114;
	} while (v != 0);
	return -1;
}
