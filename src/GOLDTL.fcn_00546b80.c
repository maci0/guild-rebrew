


#include "he_tables.h"

extern Rec7dc6e0 g_7dc6e0[64];

void __cdecl fcn_005467e0(Rec7dc6e0*);

void __cdecl fcn_00546b80(int k)
{
	int i;

	for (i = 0; i < 0x40; i++) {
		if (g_7dc6e0[i].c == k) {
			fcn_005467e0(&g_7dc6e0[i]);
		}
	}
}
