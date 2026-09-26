extern unsigned char g_7766bb;
// FUNCTION: GOLD 0x0053ee00
// SIZE: 53
// FUNCTION: GOLDTL 0x00546b40
// SIZE: 53

#include "he_tables.h"

extern Rec7dc6e0 g_7dc6e0[64];

void __cdecl fcn_005467e0(Rec7dc6e0*);

void __cdecl fcn_00546b40(void)
{
	int i;

	for (i = 0; i < 0x40; i++) {
		if (g_7dc6e0[i].b != 0 && (*(int*) (g_7dc6e0[i].b + 4) != g_7dc6e0[i].a || g_7766bb == 0)) {
			fcn_005467e0(&g_7dc6e0[i]);
		}
	}
}
