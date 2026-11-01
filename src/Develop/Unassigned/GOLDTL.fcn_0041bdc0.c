extern unsigned short g_6b6d20[256];
extern unsigned short g_6b5e08[256];
extern unsigned short g_6b6b18[256];
extern int g_6b6714[];
#include "GOLDTL.fcn_0041bdc0_gconf.h"

/* ADDRESS: GOLDTL 0x0041bdc0 */
void __cdecl fcn_0041bdc0(void)
{
	int i;
	int p;
	int r;
	int s;

	for (i = 0; i < 0x100; i++) {
		p = ((((i & 0x80) << 2) | (i & 0x40)) << 2) | (i & 0x20);
		r = i & 0x10;
		s = i >> 1;
		g_6b6d20[i] = (unsigned short) (((p * 4 | r) * 2) | (s & 4));
		g_6b5e08[i] = (unsigned short) ((i >> 2 & 2) | (p * 4) | r);
		g_6b6b18[i] = (unsigned short) ((i >> 3 & 1) | (p * 2) | (s & 8));
	}
	for (i = -0xff; i <= 0xff; i++) {
		g_6b6714[i] = i * i;
	}
	g_6b6d18 = g_6b6714;
}
