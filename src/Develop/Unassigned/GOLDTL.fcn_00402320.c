extern char g_675170[];

#include "GOLDTL.fcn_00402320_gconf.h"

void __cdecl fcn_00402320(void)
{
	int h;

	h = *(int*) &g_675170;
	if (h != -1) {
		g_66234c(h);
		*(int*) &g_675170 = -1;
	}
}
