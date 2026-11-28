#include "Develop/client_types.h"
extern Slot170_7731b8 gm_CannonTowers[8];
extern Slot170_7731b8 gm_CannonTowers[8];

/* ADDRESS: GOLD 0x004eedd0 */
/* ADDRESS: GOLDTL 0x004f0c90 */
int __cdecl gm_FindSlot170Entry(int value)
{
	int i;
	int cursor;

	i = 0;
	for (cursor = (int) gm_CannonTowers; cursor < (int) gm_CannonTowers + 0xb80; cursor += 0x170, i++) {
		if (*(int*) cursor == value) {
			return (int) ((int) gm_CannonTowers + i * 368);
		}
	}
	return 0;
}
