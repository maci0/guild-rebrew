


#include "g_772f90.h"

extern int g_772fd8;
extern Draw772* g_772fdc;

unsigned short __cdecl gm_RandomMod(unsigned short n);

void __cdecl fcn_004ecb40(void)
{
	int n;
	int i;
	int a;
	int b;
	Draw772 tmp;

	n = g_772fd8 * 2;
	for (i = 0; i < n; i++) {
		a = gm_RandomMod((unsigned short) g_772fd8);
		b = gm_RandomMod((unsigned short) g_772fd8);
		if (a != b) {
			tmp = g_772fdc[a];
			g_772fdc[a] = g_772fdc[b];
			g_772fdc[b] = tmp;
		}
	}
}
