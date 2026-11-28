#include "Develop/Units/d2.v1/d2_radio_slot.h"
extern D2_RADIO_SLOT d2_RadioSlots[8];
extern D2_RADIO_SLOT d2_RadioSlots[8];
// fcn_004bf3e0: first i with table[i].id != -1 && table[i].b == a
// (GOLDTL 0x10058a0 / GOLD 0xf812a0).

/* ADDRESS: GOLD 0x004bf3e0 */
/* ADDRESS: GOLDTL 0x004bfc40 */
/* ADDRESS: GOLDDE 0x004ad7c0 */
int __cdecl d2_FindRadioSlotByValue(int a)
{
	int i;
	for (i = 0; i < 8; i++) {
		if (d2_RadioSlots[i].id != -1 && d2_RadioSlots[i].b == a) {
			return i;
		}
	}
	return -1;
}
unsigned char _dpad_1005820[128];
