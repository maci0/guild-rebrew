#include "Develop/client_types.h"

extern Card_1007ce0 g_1007ce0[24];

/* ADDRESS: GOLDTL 0x004a70c0 */
int __cdecl gm_GetCardInHand(int player_idx, int card_slot, Card_1007ce0* out)
{
	int idx;

	if (player_idx <= 2 && card_slot <= 4) {
		idx = *(int*) (*(int*) 0x1007cd4 + (player_idx * 13 + card_slot) * 4 + 0xc);
		if (idx != -1) {
			*out = g_1007ce0[idx];
			return 1;
		}
	}
	return 0;
}
