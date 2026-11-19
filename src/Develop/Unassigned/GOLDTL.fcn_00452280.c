

#include "Develop/Units/d8_vesa/d3d_device_view.h"
typedef long (__stdcall* CreateVertexBufferFn)(D3D_DEVICE_VIEW*, unsigned int, unsigned long, unsigned long, int, void**);










extern unsigned int g_14ce7cc;
extern unsigned int g_6b8710;
extern unsigned int g_6b8714;
extern int g_67bc4c;
extern void* g_6b5de0;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_1040960[];
extern int g_1040954;
extern int g_1040c78;
extern int g_6b8718;

void __cdecl d3_InitRenderVertexBuffer(void)
{
	unsigned int fvf;
	unsigned int stride;

	fvf = ((g_14ce7cc & 0x100000) | 0x210000) >> 15;
	g_6b8710 = fvf;
	stride = ((fvf & 0x20) | 0x80) >> 3;
	d3_SceneRenderListHead = g_1040640;
	g_1040954 = 0;
	g_1040c78 = 0;
	g_1040958 = g_1040960;
	g_6b8714 = stride;
	((CreateVertexBufferFn) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->unk_00[23])(((D3D_DEVICE_VIEW*)g_6b5de0), g_67bc4c * stride, 0x248, fvf, 0, &tp_d3_RenderVertexBuffer);
	g_6b8718 = 0;
}
