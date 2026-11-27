typedef int(__stdcall* Fn1)(void* self);

#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned long g_14ce728;

void __cdecl fcn_00452420(char* p);

/* ADDRESS: GOLDTL 0x00452300 */
void __cdecl d3_ReleaseRenderVertexBuffer(void)
{
	while (d3_SceneRenderListHead != g_1040640) {
		fcn_00452420(d3_SceneRenderListHead);
	}
	(*(int*)&g_14ce728) = ((Fn1) ((void**) *(*(void***)&tp_d3_RenderVertexBuffer))[2])((*(void***)&tp_d3_RenderVertexBuffer));
	(*(void***)&tp_d3_RenderVertexBuffer) = 0;
}
