// FUNCTION: GOLD 0x4c4480
// SIZE: 80
// FUNCTION: GOLDTL 0x4c4df0
// SIZE: 79

#include <string.h>

extern int g_aed330;
extern unsigned short g_aece00;
extern char g_aece02[];

int __cdecl fcn_004c4df0(unsigned short n, void* src)
{
	if (g_aed330 != 0) {
		return 0;
	}
	if (n > 0x3fe) {
		return 0;
	}
	g_aece00 = n;
	memcpy(g_aece02, src, n);
	g_aed330 = n + 2;
	return 1;
}
