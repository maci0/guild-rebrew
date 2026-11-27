#include "g_10058a0.h"

extern D2_RADIO_SLOT g_10058a0[8];
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl d2_CreateRadioGroup(int, int);
void __cdecl d2_AddToRadioGroup(int, int);


/* ADDRESS: GOLDTL 0x004be380 */
void __cdecl d2_BuildRadioGroupFromSlots(void)
{
	int i;

	for (i = 0; i < 8; i++) {
		if (g_10058a0[i].id != -1) {
			if (g_6816d8 == -1)
				g_6816d8 = d2_CreateRadioGroup(1, g_10058a0[i].id);
			else
				d2_AddToRadioGroup(g_6816d8, g_10058a0[i].id);
		}
	}
}
