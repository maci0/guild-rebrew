extern char* g_889f74;
#include "Develop/DieGildeAddOn/game/game_data.h"
void* __cdecl fcn_004ef7c0(void* a0, void* a1, void* a2, void* a3, int a4);

/* ADDRESS: GOLD 0x004f25d0 */
int __cdecl gv_FindGraveyardWorkerSlot(void* a0, void** out_slot, void** out_val)
{
	char* slot;
	void* res;
	int i;

	*out_slot = 0;
	*out_val = 0;
	slot = g_889f74;
	for (i = 0; i < 0x100; i++, slot += 0xa9) {
		if (*(unsigned char*) slot == 0) {
			continue;
		}
		if (g_7e3f30[0x24d * *(unsigned char*) slot] == 0x1d) {
			res = fcn_004ef7c0(a0, slot, 0, (void*) 0x4ef740, 0xff);
			if (res != 0) {
				*out_slot = slot;
				*out_val = res;
				return 1;
			}
		}
	}
	return 0;
}
