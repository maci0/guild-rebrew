// FUNCTION: GOLDTL 0x4c7670
// SIZE: 65

#include <string.h>

extern char* g_fb5740;
extern int g_1005820;

int __cdecl fcn_004c7670(char* a1, char* a2)
{
	memcpy(g_fb5740 + g_1005820, a1 + 0x10, 0x80);
	g_1005820 += 0x80;
	if (a2 != 0) {
		*a2 = 1;
	}
	return 0;
}
