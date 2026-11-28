typedef struct {
	int state;
	int flag;
	int c;
	int d;
} FIFTH_CARD_SLOT;
// SIZE 0x10

typedef struct {
	char pad0[0x1c];
	int h;
	char pad[0x34 - 4 - 0x1c];
} FIFTH_CARD_ENTRY;

typedef struct {
	FIFTH_CARD_ENTRY e[3];
	char pad9c[0x19];
	unsigned char count;
} FIFTH_CARD_GAME;

#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/client_types.h"
extern slot_1007ce8 g_1007ce8[];

int __cdecl gm_DrawCard(int);


/* ADDRESS: GOLDTL 0x004a8700 */
/* ADDRESS: GOLDDE 0x00496a50 */
void __cdecl gm_DealFifthCard(void)
{
	int i;

	for (i = 0; i < 3; i++) {
		((FIFTH_CARD_GAME*)g_1007cd4)->e[i].h = gm_DrawCard(i);
		((FIFTH_CARD_SLOT*)g_1007ce8)[((FIFTH_CARD_GAME*)g_1007cd4)->e[i].h].flag = 1;
	}
	((FIFTH_CARD_GAME*)g_1007cd4)->count++;
}
