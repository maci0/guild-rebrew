#include "g_688118.h"

extern IdGroup g_688118[];

// FUNCTION: GOLD 0x004c1fc0
// FUNCTION: GOLDTL 0x4c2820

int __cdecl fcn_004c2820(int key)
{
	int i;
	int j;

	i = 0;
	do {
		for (j = 0; g_688118[i].ids[j] != 0; j++) {
			if (g_688118[i].ids[j] == key)
				return i;
		}
	} while (g_688118[i++].ids[0] != 0);
	return -1;
}
