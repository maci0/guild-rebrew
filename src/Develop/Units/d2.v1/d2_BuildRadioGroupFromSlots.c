#include "Develop/Units/d2.v1/d2_radio_slot.h"

extern D2_RADIO_SLOT d2_RadioSlots[8];
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl d2_CreateRadioGroup(int, int);
void __cdecl d2_AddToRadioGroup(int, int);


/* ADDRESS: GOLDTL 0x004be380 */
void __cdecl d2_BuildRadioGroupFromSlots(void)
{
	int i;

	for (i = 0; i < 8; i++) {
		if (d2_RadioSlots[i].id != -1) {
			if (d2_RouteRadioGroupId == -1)
				d2_RouteRadioGroupId = d2_CreateRadioGroup(1, d2_RadioSlots[i].id);
			else
				d2_AddToRadioGroup(d2_RouteRadioGroupId, d2_RadioSlots[i].id);
		}
	}
}
