#include "client_types.h"
typedef Card_1007ce0 Card;
// SIZE 0x10

extern Card_1007ce0 g_1007ce0[24];

// FUNCTION: GOLDTL 0x4a7620
// SIZE: 163
int __cdecl fcn_004a7620(int* h, int* out, int a3)
{
	int i;
	int k;
	int n;
	int rank;
	int* p;

	if (!a3 && h[0] >= 0 && h[1] >= 0 && h[2] >= 0 && h[3] >= 0) {
		for (i = 1, p = h; i < 3; p++, i++) {
			rank = g_1007ce0[*p].rank;
			out[0] = *p;
			n = 1;
			for (k = i; k < 5; k++) {
				if (h[k] < 0) {
					return 0;
				}
				if (g_1007ce0[h[k]].rank == rank) {
					out[n++] = h[k];
					if (n == 4) {
						return 1;
					}
				}
			}
		}
	}
	return 0;
}
