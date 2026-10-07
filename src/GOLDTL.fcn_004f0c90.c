#include "client_types.h"
// GLOBAL: GOLDTL 0x7731b8
extern Slot170_7731b8 g_7731b8[8];
// GLOBAL: GOLD 0x6f1008
extern Slot170_7731b8 g_7731b8[8];
// FUNCTION: GOLD 0x004eedd0
// FUNCTION: GOLDTL 0x4f0c90

int __cdecl fcn_004f0c90(int a1)
{
	int i;
	int a;

	i = 0;
	for (a = (int) g_7731b8; a < (int) g_7731b8 + 0xb80; a += 0x170, i++) {
		if (*(int*) a == a1) {
			return (int) ((int) g_7731b8 + i * 368);
		}
	}
	return 0;
}
