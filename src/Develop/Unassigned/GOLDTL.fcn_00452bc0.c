

#include "Develop/Units/d8_vesa/d3d_device_view.h"
typedef long (__stdcall* SetVertexShaderFn)(D3D_DEVICE_VIEW*, unsigned int);
typedef long (__stdcall* SetStreamSourceFn)(D3D_DEVICE_VIEW*, unsigned int, void*, unsigned int);















extern unsigned int g_6b8714;
extern unsigned int g_6b8710;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl fcn_00452740(char*);

void __cdecl fcn_00452bc0(void)
{
	char* p;
	char* next;

	((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 0x8d, 1);
	((SetStreamSourceFn) ((void**)((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl)[0x14c / 4])(((D3D_DEVICE_VIEW*)g_6b5de0), 0, tp_d3_RenderVertexBuffer, g_6b8714);
	((SetVertexShaderFn) ((void**)((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl)[0x130 / 4])(((D3D_DEVICE_VIEW*)g_6b5de0), g_6b8710);
	for (p = d3_SceneRenderListHead; p != g_1040640; p = next) {
		next = *(char**) (p + 0x314);
		fcn_00452740(p);
	}
	((SetStreamSourceFn) ((void**)((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl)[0x14c / 4])(((D3D_DEVICE_VIEW*)g_6b5de0), 0, 0, 0);
	((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 0x8d, 0);
}
