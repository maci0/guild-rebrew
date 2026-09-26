// FUNCTION: GOLD 0x00424250
// SIZE: 112
// FUNCTION: GOLDTL 0x004205e0
// SIZE: 112

#include <string.h>

#include "g_6b71b0.h"

extern Chan g_6b71b0[10];

Chan* __cdecl fcn_004205e0(const char* name)
{
	int i;

	for (i = 0; i < 10; i++) {
		if (strcmp(g_6b71b0[i].name, name) == 0) {
			return &g_6b71b0[i];
		}
	}
	return 0;
}
