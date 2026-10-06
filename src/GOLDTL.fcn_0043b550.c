#include "g_67a470.h"
// GLOBAL: GOLDTL 0x67a470
extern Named24 g_67a470[8];
// GLOBAL: GOLD 0x5fb800
extern Named24 g_67a470[8];
// FUNCTION: GOLD 0x0043e710
// FUNCTION: GOLDTL 0x43b550

char* __cdecl fcn_0043b550(int a1)
{
	int i;
	unsigned off;

	i = 0;
	for (off = 0; off < 0x120; off += 0x24, i++) {
		if (a1 == *(int*) ((char*) g_67a470 + 0x20 + off)) {
			return (char*) g_67a470 + i * 0x24;
		}
	}
	return (char*) g_67a470 + 0x124;
}
