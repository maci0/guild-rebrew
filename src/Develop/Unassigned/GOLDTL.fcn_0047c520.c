#include "Develop/Units/d8_vesa/d3d_device_view.h"
typedef int (__stdcall* Texture47c520Fn)(D3D_DEVICE_VIEW*, int, int);
typedef int (__stdcall* Stream47c520Fn)(D3D_DEVICE_VIEW*, int, int, int);









extern int g_772618;



/* ADDRESS: GOLDTL 0x0047c520 */
void __cdecl fcn_0047c520(void)
{
	if (g_772618 != 0) {
		((Stream47c520Fn) ((void**)((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl)[0x14c / 4])(((D3D_DEVICE_VIEW*)g_6b5de0), 0, 0, 0);
		((Texture47c520Fn) ((void**)((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl)[0xf4 / 4])(((D3D_DEVICE_VIEW*)g_6b5de0), 0, 0);
		g_772618 = 0;
	}
}
