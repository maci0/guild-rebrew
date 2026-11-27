#include "client_types.h"
typedef Card_1007ce0 Card;
// SIZE 0x10

extern Card_1007ce0 g_1007ce0[24];

/* ADDRESS: GOLDTL 0x004a75a0 */
int __cdecl gm_CheckCardFlush(int* hand, int* out, int disabled)
{
	int i;
	int suit;

	if (!disabled && hand[0] >= 0 && hand[1] >= 0 && hand[2] >= 0 && hand[3] >= 0 && hand[4] >= 0) {
		suit = g_1007ce0[hand[0]].suit;
		out[0] = hand[0];
		for (i = 1; i < 5; i++) {
			if (g_1007ce0[hand[i]].suit != suit) {
				return 0;
			}
			out[i] = hand[i];
		}
		return 1;
	}
	return 0;
}
