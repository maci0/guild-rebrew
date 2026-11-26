#include "client_types.h"
typedef Card_1007ce0 Card;
// SIZE 0x10

extern Card_1007ce0 g_1007ce0[24];

/* ADDRESS: GOLD 0x004a76d0 */
/* ADDRESS: GOLDTL 0x004a77f0 */
int __cdecl gm_GetHighestCard(int* hand, int skipFirstTwo)
{
	int start;
	int best;
	int i;
	int rank;
	int suit;

	start = skipFirstTwo ? 2 : 0;
	best = hand[start];
	if (best < 0) {
		return -1;
	}
	i = start + 1;
	if (hand[i] < 0) {
		return best;
	}
	rank = g_1007ce0[best].rank;
	suit = g_1007ce0[best].suit;
	for (; i < 5; i++) {
		if (hand[i] < 0) {
			break;
		}
		if (g_1007ce0[hand[i]].rank > rank) {
			best = hand[i];
			rank = g_1007ce0[best].rank;
			suit = g_1007ce0[best].suit;
		} else if (g_1007ce0[hand[i]].rank == rank && g_1007ce0[hand[i]].suit > suit) {
			best = hand[i];
			suit = g_1007ce0[best].suit;
		}
	}
	return best;
}
