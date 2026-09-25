typedef struct Card {
	int rank;
	int suit;
	int count;
	int owner;
} Card;
// SIZE 0x10

extern Card g_1007ce0[24];

// FUNCTION: GOLDTL 0x4a77f0
// SIZE: 141
int __cdecl fcn_004a77f0(int* h, int a2)
{
	int s;
	int best;
	int i;
	int rank;
	int suit;

	s = a2 ? 2 : 0;
	best = h[s];
	if (best < 0) {
		return -1;
	}
	i = s + 1;
	if (h[i] < 0) {
		return best;
	}
		rank = g_1007ce0[best].rank;
		suit = g_1007ce0[best].suit;
		for (; i < 5; i++) {
			if (h[i] < 0) {
				break;
			}
			if (g_1007ce0[h[i]].rank > rank) {
				best = h[i];
				rank = g_1007ce0[best].rank;
				suit = g_1007ce0[best].suit;
			} else if (g_1007ce0[h[i]].rank == rank && g_1007ce0[h[i]].suit > suit) {
				best = h[i];
				suit = g_1007ce0[best].suit;
			}
		}
	return best;
}
