typedef struct {
	int state;
	int flag;
	int c;
	int d;
} FOURTH_CARD_SLOT;
// SIZE 0x10

typedef struct {
	char pad0[0x18];
	int h;
	char pad[0x34 - 4 - 0x18];
} FOURTH_CARD_ENTRY;

typedef struct {
	FOURTH_CARD_ENTRY e[3];
	char pad9c[0x19];
	unsigned char count;
} FOURTH_CARD_GAME;

#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_types.h"
extern slot_1007ce8 g_1007ce8[];

int __cdecl gm_DrawCard(int);


/* ADDRESS: GOLDTL 0x004a86b0 */
void __cdecl gm_DealFourthCard(void)
{
	int i;

	for (i = 0; i < 3; i++) {
		((FOURTH_CARD_GAME*)g_1007cd4)->e[i].h = gm_DrawCard(i);
		((FOURTH_CARD_SLOT*)g_1007ce8)[((FOURTH_CARD_GAME*)g_1007cd4)->e[i].h].flag = 1;
	}
	((FOURTH_CARD_GAME*)g_1007cd4)->count++;
}
