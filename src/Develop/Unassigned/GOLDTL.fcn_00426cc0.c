#include "Develop/DieGildeAddOn/game/game_data.h"

/* ADDRESS: GOLD 0x004284a0 */
/* ADDRESS: GOLDTL 0x00426cc0 */
void* __cdecl fcn_00426cc0(int recordId)
{
	int i;
	char* base;
	char* p;

	if (recordId == -1) {
		return 0;
	}
	base = g_6b7e94;
	for (i = 0, p = base + 0x100; i < 0x80; i++, p += 0xc98) {
		if (*(int*) p == recordId) {
			return (void*) ((int) base + i * 3224);
		}
	}
	return 0;
}
