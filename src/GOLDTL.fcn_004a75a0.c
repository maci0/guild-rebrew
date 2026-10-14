#include "client_types.h"
typedef Card_1007ce0 Card;
// SIZE 0x10

extern Card_1007ce0 g_1007ce0[24];

/* ADDRESS: GOLDTL 0x004a75a0 */
int __cdecl fcn_004a75a0(int* h, int* out, int a3)
{
	int i;
	int suit;

	if (!a3 && h[0] >= 0 && h[1] >= 0 && h[2] >= 0 && h[3] >= 0 && h[4] >= 0) {
		suit = g_1007ce0[h[0]].suit;
		out[0] = h[0];
		for (i = 1; i < 5; i++) {
			if (g_1007ce0[h[i]].suit != suit) {
				return 0;
			}
			out[i] = h[i];
		}
		return 1;
	}
	return 0;
}
