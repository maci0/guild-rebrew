#include "client_types.h"
typedef Card_1007ce0 Card;
// SIZE 0x10

extern Card_1007ce0 g_1007ce0[24];

/* ADDRESS: GOLDTL 0x004a7620 */
int __cdecl gm_FindCardFourOfAKind(int* hand, int* out, int flag)
{
	int i;
	int k;
	int n;
	int rank;
	int* p;

	if (!flag && hand[0] >= 0 && hand[1] >= 0 && hand[2] >= 0 && hand[3] >= 0) {
		for (i = 1, p = hand; i < 3; p++, i++) {
			rank = g_1007ce0[*p].rank;
			out[0] = *p;
			n = 1;
			for (k = i; k < 5; k++) {
				if (hand[k] < 0) {
					return 0;
				}
				if (g_1007ce0[hand[k]].rank == rank) {
					out[n++] = hand[k];
					if (n == 4) {
						return 1;
					}
				}
			}
		}
	}
	return 0;
}
