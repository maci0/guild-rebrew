typedef int(__stdcall* FnVB)(void* self, int len, int usage, int fvf, int pool, void** out);

#include "Develop/Units/d8_vesa/d3d_device_view.h"
extern unsigned int g_6b8710;
extern unsigned int g_6b8714;
extern int g_67bc4c;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_6b8718;

/* ADDRESS: GOLDTL 0x00452360 */
void __cdecl fcn_00452360(void)
{
	((FnVB) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->unk_00[23])(((void**)g_6b5de0), g_67bc4c * (*(int*)&g_6b8714), 0x248, (*(int*)&g_6b8710), 0, &tp_d3_RenderVertexBuffer);
	g_6b8718 = 0;
}
