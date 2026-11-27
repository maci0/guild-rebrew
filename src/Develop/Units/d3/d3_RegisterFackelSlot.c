extern int g_773de0;
extern char* g_7f3e60[];



#include <string.h>

void __cdecl d3_RegisterFackelSlot(char* s)
{
	if (strstr(s, "ub_FACKEL_") != 0 && g_773de0 < 0x20) {
		g_7f3e60[g_773de0++] = s;
	}
}
