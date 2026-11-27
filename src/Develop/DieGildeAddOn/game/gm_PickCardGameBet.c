typedef struct {
	char pad0[0x24];
	int canFullBet;
	char pad28[0xc];
} CardGameSlot;
// SIZE 0x34

typedef struct {
	CardGameSlot slots[3];
	char pad9c[0x8];
	int minBet;
	int maxBet;
	int currentBet;
	int activeSlot;
} CardGameState;

#include "Develop/DieGildeAddOn/game/game_data.h"

unsigned short __cdecl gm_RandomMod(short);


/* ADDRESS: GOLDTL 0x004a8810 */
void __cdecl gm_PickCardGameBet(void)
{
	if (((CardGameState*)g_1007cd4)->activeSlot != 0) {
		if (((CardGameState*)g_1007cd4)->slots[((CardGameState*)g_1007cd4)->activeSlot].canFullBet != 0)
			((CardGameState*)g_1007cd4)->currentBet =
				gm_RandomMod((short) ((CardGameState*)g_1007cd4)->maxBet -
					     (short) ((CardGameState*)g_1007cd4)->minBet) +
				((CardGameState*)g_1007cd4)->minBet;
		else
			((CardGameState*)g_1007cd4)->currentBet =
				gm_RandomMod((short) ((((CardGameState*)g_1007cd4)->maxBet -
						       ((CardGameState*)g_1007cd4)->minBet) >> 1)) +
				((CardGameState*)g_1007cd4)->minBet;
	}
}
