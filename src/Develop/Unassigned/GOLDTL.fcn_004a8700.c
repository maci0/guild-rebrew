typedef struct {
	int state;
	int flag;
	int c;
	int d;
} fcn_004a8700_slot;
// SIZE 0x10

typedef struct {
	char pad0[0x1c];
	int h;
	char pad[0x34 - 4 - 0x1c];
} fcn_004a8700_entry;

typedef struct {
	fcn_004a8700_entry e[3];
	char pad9c[0x19];
	unsigned char count;
} fcn_004a8700_game;

#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_types.h"
extern slot_1007ce8 g_1007ce8[];

int __cdecl gm_DrawCard(int);


/* ADDRESS: GOLDTL 0x004a8700 */
void __cdecl gm_DealFifthCard(void)
{
	int i;

	for (i = 0; i < 3; i++) {
		((fcn_004a8700_game*)g_1007cd4)->e[i].h = gm_DrawCard(i);
		((fcn_004a8700_slot*)g_1007ce8)[((fcn_004a8700_game*)g_1007cd4)->e[i].h].flag = 1;
	}
	((fcn_004a8700_game*)g_1007cd4)->count++;
}
