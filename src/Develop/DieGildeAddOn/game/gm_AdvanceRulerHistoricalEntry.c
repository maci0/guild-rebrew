#include "Develop/DieGildeAddOn/game/g_67fbb0.h"

extern int g_67fbac;
extern Entry2c* g_67fbb4;
#include "Develop/DieGildeAddOn/game/game_data.h"


/* ADDRESS: GOLDTL 0x004adf80 */
void __cdecl gm_AdvanceRulerHistoricalEntry(void)
{
	int i;

	for (i = 0; i < g_67fbac; i++) {
		if (g_67fbb4[i].key == g_7728cc) {
			g_7728c8 = g_7728cc;
			if (i < g_67fbac - 1)
				g_7728cc = g_67fbb4[i + 1].key;
			else
				g_7728cc = -1;
			return;
		}
	}
}
