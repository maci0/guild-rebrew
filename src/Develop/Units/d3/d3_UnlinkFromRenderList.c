

#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_1040960[];
extern int d3_ActiveScene;

/* ADDRESS: GOLDDE 0x00447c50 */
void __cdecl d3_UnlinkFromRenderList(char* node)
{
	char* owner;

#ifdef REBREW_GOLD
	owner = *(char**) (node + 0x2f0);
#else
	owner = *(char**) (node + 0x2f4);
#endif
	if (*(char**) (node + 0x318) == g_1040960) {
		*(char**) (owner + 0xa4) = *(char**) (node + 0x314);
	} else {
		*(char**) (*(char**) (node + 0x318) + 0x314) = *(char**) (node + 0x314);
	}
	if (*(char**) (node + 0x314) == g_1040640) {
		*(char**) (owner + 0xa8) = *(char**) (node + 0x318);
	} else {
		*(char**) (*(char**) (node + 0x314) + 0x318) = *(char**) (node + 0x318);
	}
	if (owner == ((char*)d3_ActiveScene)) {
		d3_SceneRenderListHead = *(char**) (owner + 0xa4);
		g_1040958 = *(char**) (owner + 0xa8);
	}
}
