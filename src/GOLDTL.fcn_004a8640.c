#include "client_types.h"
typedef Card_1007ce0 Card;
// SIZE 0x10

extern Card_1007ce0 g_1007ce0[24];

extern char* g_1007cd4;

int __cdecl fcn_004a7880(int owner);

// FUNCTION: GOLD 0x004a8520
// SIZE: 110
// FUNCTION: GOLDTL 0x4a8640
// SIZE: 110
void __cdecl fcn_004a8640(void)
{
	int j;
	int p;

	for (j = 0; j < 3; j++) {
		for (p = 0; p < 3; p++) {
			*(int*) (g_1007cd4 + 0xc + j * 4 + p * 0x34) = fcn_004a7880(p);
			if (j > 1) {
				g_1007ce0[*(int*) (g_1007cd4 + 0xc + j * 4 + p * 0x34)].owner = 1;
			} else {
				g_1007ce0[*(int*) (g_1007cd4 + 0xc + j * 4 + p * 0x34)].owner = 0;
			}
		}
	}
	g_1007cd4[0xb5] += 3;
}
