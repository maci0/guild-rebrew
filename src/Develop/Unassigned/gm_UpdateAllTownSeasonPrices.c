

typedef struct
{
	char used;
	char pad[0x2f3];
} TOWN_RECORD_2F4;
// SIZE 0x2f4

extern char g_868060[];
#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl gm_UpdateTownSeasonPrices(int, char*);

void __cdecl gm_UpdateAllTownSeasonPrices(void)
{
	int i;

	for (i = 0; i < 4; i++) {
		if (((TOWN_RECORD_2F4*)g_868060)[i].used == 0) {
			break;
		}
		gm_UpdateTownSeasonPrices(i, ((char*)&gm_GameTime));
	}
}
