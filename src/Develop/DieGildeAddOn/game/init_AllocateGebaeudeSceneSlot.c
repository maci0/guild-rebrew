#include <string.h>
#include "Develop/DieGildeAddOn/game/building_prototype.h"

typedef struct D3_UNIVERSE_VIEW {
	char name[0x3d5];
	unsigned char verwendet;
	char unbekannt_3d6[6];
} D3_UNIVERSE_VIEW;

extern unsigned char* lpGebaeudePROT;
extern signed char g_7f3b00[];
extern unsigned char* g_7746c8;
extern char g_10432c0[];

int __cdecl d3_FindFreeSceneContext(void);
void __cdecl init_LoadGebaeudeScene(int);

/* ADDRESS: GOLDTL 0x005155e0 */
int __cdecl init_AllocateGebaeudeSceneSlot(unsigned char* e)
{
	int k;
	int r;

	k = ((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*e].category;
	if (((signed char*)g_7f3b00)[k] == -1) {
		if (e == g_7746c8 || *e == 0x1e) {
			init_LoadGebaeudeScene(*e);
		} else {
			r = d3_FindFreeSceneContext();
			if (r == -1) {
				return r;
			}
			((signed char*)g_7f3b00)[k] = (signed char) r;
			((D3_UNIVERSE_VIEW*)g_10432c0)[r].verwendet = 1;
			strcpy((char*)&((D3_UNIVERSE_VIEW*)g_10432c0)[r],
				(char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*e] + 1);
		}
	}
	return ((signed char*)g_7f3b00)[k];
}
