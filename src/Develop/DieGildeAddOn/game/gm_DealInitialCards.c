#include "Develop/client_types.h"
typedef Card_1007ce0 Card;
// SIZE 0x10

extern Card_1007ce0 g_1007ce0[24];

#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl gm_DrawCard(int owner);

/* ADDRESS: GOLDTL 0x004a8640 */
/* ADDRESS: GOLDDE 0x00496990 */
void __cdecl gm_DealInitialCards(void)
{
	int j;
	int p;

	for (j = 0; j < 3; j++) {
		for (p = 0; p < 3; p++) {
			*(int*) (g_1007cd4 + 0xc + j * 4 + p * 0x34) = gm_DrawCard(p);
			if (j > 1) {
				g_1007ce0[*(int*) (g_1007cd4 + 0xc + j * 4 + p * 0x34)].owner = 1;
			} else {
				g_1007ce0[*(int*) (g_1007cd4 + 0xc + j * 4 + p * 0x34)].owner = 0;
			}
		}
	}
	g_1007cd4[0xb5] += 3;
}
