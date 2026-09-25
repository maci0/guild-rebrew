extern int g_773de0;
extern char* g_7f3e60[];

// FUNCTION: GOLDTL 0x514d00
// SIZE: 48

#include <string.h>

void __cdecl fcn_00514d00(char* s)
{
	if (strstr(s, "ub_FACKEL_") != 0 && g_773de0 < 0x20) {
		g_7f3e60[g_773de0++] = s;
	}
}
