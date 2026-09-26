// FUNCTION: GOLD 0x004eae60
// SIZE: 52
// FUNCTION: GOLDTL 0x4ecbe0
// SIZE: 52

#include "g_772f90.h"

extern int g_772fe0;
extern Rec772fe4* g_772fe4;

Rec772fe4* __cdecl fcn_004ecbe0(int key)
{
	int i;

	for (i = 0; i < g_772fe0; i++) {
		if (g_772fe4[i].key == key) {
			return &g_772fe4[i];
		}
	}
	return 0;
}
