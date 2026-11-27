#include "Develop/DieGildeAddOn/game/game_data.h"

/* ADDRESS: GOLD 0x004e50e0 */
/* ADDRESS: GOLDTL 0x004e6a70 */
int __cdecl gm_FindPlayerById(int id)
{
	int i;
	int a;

	i = 0;
	for (a = (int) g_9b0e20 + 0x10; a < (int) g_9b0e20 + 0x35d0; a += 0x35c, i++) {
		if (*(int*) a == id) {
			return (int) ((int) g_9b0e20 + i * 860);
		}
	}
	return 0;
}
