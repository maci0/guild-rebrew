#include "Develop/DieGildeAddOn/game/g_67fbb0.h"

extern int g_67fba8;
extern int g_67fbac;
extern Entry2c* g_67fbb0;
extern Entry2c* g_67fbb4;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl m_FreeTracked(void*);


/* ADDRESS: GOLDTL 0x004acf00 */
int __cdecl gm_FreeHistoricalTable(void)
{
	if (g_67fbb4 != 0) {
		m_FreeTracked(g_67fbb4);
		g_67fbb4 = 0;
	}
	if (g_67fbb0 != 0) {
		m_FreeTracked(g_67fbb0);
		g_67fbb0 = 0;
	}
	g_67fba8 = 0;
	g_67fbac = 0;
	g_7728c0 = -1;
	g_7728c8 = -1;
	g_7728c4 = -1;
	g_7728cc = -1;
	g_7728d0 = -1;
	return 0;
}
