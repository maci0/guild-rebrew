

#include "Develop/Units/d8_vesa/d3d_device_view.h"
typedef long (__stdcall* Texture458d20Fn)(D3D_DEVICE_VIEW*, int, void*);
typedef long (__stdcall* Draw458d20Fn)(D3D_DEVICE_VIEW*, int, unsigned int, unsigned int, unsigned int, unsigned int);
typedef long (__stdcall* Stream458d20Fn)(D3D_DEVICE_VIEW*, unsigned int, void*, unsigned int);
typedef long (__stdcall* Indices458d20Fn)(D3D_DEVICE_VIEW*, void*, unsigned int);













#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl fcn_00458d20(char* o)
{
	int i;
	char* e;

	for (i = 0; i < 4; i++) {
		e = *(char**) (o + 0x1ec) + i * 0x9c + 0x1384;
		if (*(char**) e != 0 && *(int*) (e + 0x90) > 0) {
			((Stream458d20Fn) ((void**)((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl)[0x14c / 4])(((D3D_DEVICE_VIEW*)g_6b5de0), 0, *(void**) (e + 0x80), 0x18);
			((Indices458d20Fn) ((void**)((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl)[0x154 / 4])(((D3D_DEVICE_VIEW*)g_6b5de0), *(void**) (e + 0x84), 0);
			((Texture458d20Fn) ((void**)((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl)[0xf4 / 4])(((D3D_DEVICE_VIEW*)g_6b5de0), 0, *(void**) (*(char**) e + 0x50));
			((Draw458d20Fn) ((void**)((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl)[0x11c / 4])(((D3D_DEVICE_VIEW*)g_6b5de0), 4, 0, *(unsigned int*) (e + 0x94), 0, *(unsigned int*) (e + 0x90));
			d3_RenderedVertexCount += *(int*) (e + 0x94);
			g_1042a08 += *(int*) (e + 0x90);
		}
	}
}
