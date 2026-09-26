#include "client_types.h"
typedef entry_100d0c0 fcn_0047e220_entry;
// SIZE 0x58

extern int g_100b0ac;
extern entry_100d0c0 g_100d0c0[];

void __cdecl fcn_004c52d0(int, int);

// FUNCTION: GOLD 0x47ed50
// SIZE: 68
// FUNCTION: GOLDTL 0x47e220
// SIZE: 68

void __cdecl fcn_0047e220(char* x)
{
	int i;

	for (i = 0; i < g_100b0ac; i++) {
		if (g_100d0c0[i].f3c == 0 && (g_100d0c0[i].flags & 8) == 0)
			fcn_004c52d0(*(int*) (x + 2), g_100d0c0[i].f0);
	}
}
