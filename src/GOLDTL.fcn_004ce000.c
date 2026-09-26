// FUNCTION: GOLD 0x004cd480
// SIZE: 52
// FUNCTION: GOLDTL 0x4ce000
// SIZE: 52

#include "g_9ba3a0.h"

extern int g_772e88;
extern int g_772e8c;
extern int g_9ba9f4;
extern logrec g_9ba3a0[15];

char* __cdecl fcn_004ce000(void)
{
	if (g_772e88 != 0) {
		g_772e8c = g_9ba9f4 - g_772e88;
		if (g_772e8c < 0) {
			g_772e8c = g_9ba9f4 + 1;
		}
		return (char*) g_9ba3a0 + g_772e8c * 0x6c;
	}
	return 0;
}
