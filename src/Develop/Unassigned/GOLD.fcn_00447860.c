extern unsigned char* g_fb9074;
extern unsigned int g_fb9084;
#include "Develop/DieGildeAddOn/game/game_data.h"
int __cdecl d3_VisitSceneNodes(int, int, int, void*);
int __cdecl d3_BuildFloorTileTextures(int);
int __cdecl d3_PrecacheObjectTextures();

/* ADDRESS: GOLD 0x00447860 */
void __cdecl d3_PrecacheSceneTextures(char buildFloor)
{
	unsigned int i;
	void* obj;
	typedef void (__stdcall* method_t)(void*);

	for (i = 0; i < g_fb9084; i++)
		g_fb9074[i * 0x80 + 0x68] &= 0x7f;
	obj = *(void**) 0x633418;
	((method_t) (*(void**) (*(char**) obj + 0x24)))(obj);
	d3_VisitSceneNodes((int) g_5fb5b0, 0, 0x40, (void*) d3_PrecacheObjectTextures);
	obj = *(void**) 0x633738;
	if (obj != 0 && buildFloor != 0)
		d3_BuildFloorTileTextures((int) obj);
	obj = *(void**) 0x633418;
	((method_t) (*(void**) (*(char**) obj + 0x28)))(obj);
}
