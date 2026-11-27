#include <string.h>
#include "Develop/DieGildeAddOn/game/building_prototype.h"

int __cdecl d3_FindFreeSceneContext(void);

#if defined(REBREW_GOLD)
#include "Develop/DieGildeAddOn/game/game_data.h"
extern signed char g_76fa60[];
extern unsigned char* g_6f230c;

/* SIZE 0x3e0 */
struct s_fd7ba0 {
	char name[0x3d5];
	char used;
	char pad[0xa];
};

extern struct s_fd7ba0 g_fd7ba0[];

void __cdecl init_LoadBuildingScene(int);

/* Twin of GOLDTL 0x5155e0; the GOLD slot records are 0x3e0 bytes, not 0x3dc. */
/* ADDRESS: GOLD 0x00511e90 */
int __cdecl init_AllocateGebaeudeSceneSlot(unsigned char* e)
{
	int k;
	int r;

	k = ((BUILDING_PROTOTYPE*)g_7e3f30)[*e].category;
	if (((signed char*)g_76fa60)[k] == -1) {
		if (e == g_6f230c || *e == 0x1e) {
			init_LoadBuildingScene(*e);
		} else {
			r = d3_FindFreeSceneContext();
			if (r == -1) {
				return r;
			}
			((signed char*)g_76fa60)[k] = (signed char) r;
			g_fd7ba0[r].used = 1;
			strcpy((char*)&g_fd7ba0[r],
				(char*)&((BUILDING_PROTOTYPE*)g_7e3f30)[*e] + 1);
		}
	}
	return ((signed char*)g_76fa60)[k];
}
#else
typedef struct D3_UNIVERSE_VIEW {
	char name[0x3d5];
	unsigned char verwendet;
	char unbekannt_3d6[6];
} D3_UNIVERSE_VIEW;

extern unsigned char* lpGebaeudePROT;
extern signed char g_7f3b00[];
extern unsigned char* g_7746c8;
extern char g_10432c0[];

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
#endif
