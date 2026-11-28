#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned char gm_ActiveTownIndex;

void __cdecl gm_ConvertUnitsToAmount(int amount, unsigned char k);
void __cdecl cm_RequestTransferCurrencyNoKill(int a, int b, unsigned char k, int amount);
#include "Develop/client_types.h"
typedef Card_1007ce0 Card;

extern Card_1007ce0 g_1007ce0[24];

/* ADDRESS: GOLDTL 0x004a7b40 */
/* ADDRESS: GOLDDE 0x00495e90 */
void __cdecl gm_CollectCardGameBets(void)
{
	int i;

	for (i = 0; i < 3; i++) {
		if (*(int*) (g_1007cd4 + 0x2c + i * 0x34) < 0) {
			*(int*) (g_1007cd4 + 0xa0) += *(int*) (g_1007cd4 + 0xac);
			if (i == 0) {
				gm_ConvertUnitsToAmount(*(int*) (g_1007cd4 + 0xac), gm_ActiveTownIndex);
				cm_RequestTransferCurrencyNoKill(-1, *(int*) (*(char**) (g_1007cd4 + 4) + 4), gm_ActiveTownIndex, *(int*) (g_1007cd4 + 0xac));
			}
			*(int*) (g_1007cd4 + 0x20 + i * 0x34) += *(int*) (g_1007cd4 + 0xac);
		}
	}
}
