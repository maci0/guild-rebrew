// FUNCTION: GOLD 0x0053ee70
// FUNCTION: GOLDTL 0x00546bb0

#include "he_tables.h"

extern Rec7dc6e0 g_7dc6e0[64];

void __cdecl fcn_00442c00(int, int);

void __cdecl fcn_00546bb0(int k, int v)
{
	int i;

	for (i = 0; i < 0x40; i++) {
		if (g_7dc6e0[i].c == k) {
			fcn_00442c00(g_7dc6e0[i].d, v);
		}
	}
}
