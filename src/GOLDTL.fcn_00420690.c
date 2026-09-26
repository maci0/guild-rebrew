// FUNCTION: GOLD 0x00424300
// SIZE: 112
// FUNCTION: GOLDTL 0x00420690
// SIZE: 112

#include "g_6b71b0.h"

extern Chan g_6b71b0[10];

Chan* __cdecl fcn_00420690(void)
{
	int i;

	for (i = 0; i < 10; i++) {
		if (g_6b71b0[i].active == 0 && g_6b71b0[i].handle == 0 && g_6b71b0[i].f10c == 0) {
			return &g_6b71b0[i];
		}
	}
	for (i = 0; i < 10; i++) {
		if (g_6b71b0[i].active == 0 && g_6b71b0[i].handle == 0) {
			return &g_6b71b0[i];
		}
	}
	return 0;
}
