// FUNCTION: GOLD 0x426240
// FUNCTION: GOLDTL 0x4226b0

#include <string.h>

extern char g_6b7d88[];

void __cdecl fcn_004226b0(char* s)
{
	if (s != 0) {
		strcpy(g_6b7d88, s);
		if (s[strlen(s) - 1] != '\\') {
			strcat(g_6b7d88, "\\");
		}
	}
}
