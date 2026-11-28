#include "Develop/client_types.h"
typedef slot_1007ce8 CARD_HAND_SLOT;
// SIZE 0x10

typedef struct {
	char pad0[0x8];
	int slot[7];
	int last;
} CARD_SEAT;

extern slot_1007ce8 g_1007ce8[];

int __cdecl gm_DrawCard(int);


/* ADDRESS: GOLDTL 0x004a7af0 */
/* ADDRESS: GOLDDE 0x00495e40 */
void __cdecl gm_ReplaceCardSlot(CARD_SEAT* seat, int slotIdx)
{
	int oldState;

	if (slotIdx < 2) {
		oldState = g_1007ce8[seat->slot[slotIdx]].state;
		g_1007ce8[seat->slot[slotIdx]].state = 4;
		seat->last = seat->slot[slotIdx];
		seat->slot[slotIdx] = gm_DrawCard(oldState);
		g_1007ce8[seat->slot[slotIdx]].flag = 0;
	}
}
