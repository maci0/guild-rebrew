#include "Develop/Units/d8_vesa/d3d_device_view.h"
typedef int (__stdcall* Shader47c4e0Fn)(D3D_DEVICE_VIEW*, int);
typedef int (__stdcall* Stream47c4e0Fn)(D3D_DEVICE_VIEW*, int, int, int);









extern int g_772618;
extern int g_772614;



/* ADDRESS: GOLDTL 0x0047c4e0 */
void __cdecl d2_BindQuadVertexBuffer(void)
{
	if (g_772618 == 0) {
		((Stream47c4e0Fn) ((void**)((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl)[0x14c / 4])(((D3D_DEVICE_VIEW*)g_6b5de0), 0, g_772614, 0x1c);
		((Shader47c4e0Fn) ((void**)((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl)[0x130 / 4])(((D3D_DEVICE_VIEW*)g_6b5de0), 0x144);
		g_772618 = 1;
	}
}
