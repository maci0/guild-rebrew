typedef int(__stdcall* Fn1)(void* self);

#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned long d3_LastReleaseRefCount;

void __cdecl d3_FreeMeshObject(char* p);

/* ADDRESS: GOLDTL 0x00452300 */
/* ADDRESS: GOLDDE 0x00447bb0 */
void __cdecl d3_ReleaseRenderVertexBuffer(void)
{
	while (d3_SceneRenderListHead != g_1040640) {
		d3_FreeMeshObject(d3_SceneRenderListHead);
	}
	(*(int*)&d3_LastReleaseRefCount) = ((Fn1) ((void**) *(*(void***)&tp_d3_RenderVertexBuffer))[2])((*(void***)&tp_d3_RenderVertexBuffer));
	(*(void***)&tp_d3_RenderVertexBuffer) = 0;
}
