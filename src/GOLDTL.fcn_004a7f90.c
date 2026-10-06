#include "client_types.h"
typedef Card_1007ce0 Card;
// SIZE 0x10

extern Card_1007ce0 g_1007ce0[24];

extern char* g_1007cd4;

// FUNCTION: GOLDTL 0x4a7f90
// FUNCTION: GOLD 0x004a7e70
void __cdecl fcn_004a7f90(int* h, int* rank_n, int* rank, int* suit_n, int* suit)
{
	int suits[4] = { 0 };
	int ranks[6] = { 0 };
	int n;
	int i;

	n = ((unsigned char*)g_1007cd4)[0xb5];
	for (i = 2; i < n; i++) {
		suits[g_1007ce0[h[i + 2]].suit]++;
		ranks[g_1007ce0[h[i + 2]].rank]++;
	}
	*rank_n = ranks[0];
	*rank = 0;
	for (i = 1; i < 6; i++) {
		if (ranks[i] > *rank_n) {
			*rank_n = ranks[i];
			*rank = i;
		}
	}
	*suit_n = suits[0];
	*suit = 0;
	for (i = 1; i < 4; i++) {
		if (suits[i] > *suit_n) {
			*suit_n = suits[i];
			*suit = i;
		}
	}
}
