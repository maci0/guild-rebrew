#include "g_67fbb0.h"

extern int g_67fba8;
extern Entry2c* g_67fbb0;
extern Entry2c* g_67fbb4;
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl ai_LoadHistoricalDfn(int*);

extern int g_67fbac;

/* ADDRESS: GOLDTL 0x004acbb0 */
int __cdecl gm_LoadHistoricalTable(void)
{
	int r;

	g_7728c0 = -1;
	g_7728c8 = -1;
	g_7728c4 = -1;
	g_7728cc = -1;
	g_7728d0 = -1;
	r = ai_LoadHistoricalDfn(&g_67fba8);
	if (r == 0) {
		g_7728c4 = g_67fbb0->key;
		g_7728cc = g_67fbb4->key;
	}
	return r;
}

/* ADDRESS: GOLDTL 0x004acee0 */
void __cdecl gm_ResetHistoricalCursors(void)
{
	g_7728c4 = g_67fbb0->key;
	g_7728cc = g_67fbb4->key;
}

/* ADDRESS: GOLD 0x004ad010 */
/* ADDRESS: GOLDTL 0x004ad130 */
char* __cdecl gm_LookupHistoricalEntry(int id, int* kind)
{
	int i;

	for (i = 0; i < g_67fba8; i++) {
		if (*(int*) ((char*) g_67fbb0 + i * 0x2c) == id) {
			if (kind != 0)
				*kind = 0x27;
			return (char*) g_67fbb0 + i * 0x2c;
		}
	}
	for (i = 0; i < g_67fbac; i++) {
		if (*(int*) ((char*) g_67fbb4 + i * 0x2c) == id) {
			if (kind != 0)
				*kind = 0x26;
			return (char*) g_67fbb4 + i * 0x2c;
		}
	}
	return 0;
}
