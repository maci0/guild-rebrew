


#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl amt_FindOfficeSlotByType(int, int*);
char* __cdecl gm_LookupHistoricalEntry(int, int*);
char* __cdecl gm_RandomMod(int);
void __cdecl cm_RequestAllocSpieler(int, int, int, char*, int, int, int, int);

void __cdecl amt_SpawnHistoricalOfficeHolders(void)
{
	int kind;
	int a[6];
	int b[6];
	int limit;
	char* p;

	limit = (*(int*)&gm_GameTime) + 0x578;
	if (amt_FindOfficeSlotByType(0x26, a) == 0)
		return;
	if (amt_FindOfficeSlotByType(0x27, b) == 0)
		return;
	if (a[1] == -1 && g_7728cc != -1) {
		p = gm_LookupHistoricalEntry(g_7728cc, &kind);
		if (p != 0 && *(int*) (p + 4) <= limit)
			cm_RequestAllocSpieler(0x15, g_7728cc, -1, gm_RandomMod(8) + 0x19, -1, 0, 0, 0);
	}
	if (b[1] == -1 && g_7728c4 != -1) {
		p = gm_LookupHistoricalEntry(g_7728c4, &kind);
		if (p != 0 && *(int*) (p + 4) <= limit)
			cm_RequestAllocSpieler(0x16, g_7728c4, -1, gm_RandomMod(8) + 0x19, -1, 0, 0, 0);
	}
}
