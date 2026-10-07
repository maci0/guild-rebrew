#include <string.h>

extern char* g_772500;

// FUNCTION: GOLD 0x00468880
// FUNCTION: GOLDTL 0x465950
int __cdecl fcn_00465950(const char* name)
{
	int i;

	for (i = 0; i < 0x800; i++) {
		if (g_772500[i * 0x54] != 0 && strcmp(name, g_772500 + i * 0x54) == 0) {
			return i;
		}
	}
	return -1;
}
