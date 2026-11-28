

#include "Develop/Units/d8_vesa/d3d_device_view.h"
typedef long (__stdcall* D3_SHADOW_TEXTURE_FN)(D3D_DEVICE_VIEW*, int, void*);
typedef long (__stdcall* D3_SHADOW_DRAW_FN)(D3D_DEVICE_VIEW*, int, unsigned int, unsigned int, unsigned int, unsigned int);
typedef long (__stdcall* D3_SHADOW_STREAM_FN)(D3D_DEVICE_VIEW*, unsigned int, void*, unsigned int);
typedef long (__stdcall* D3_SHADOW_INDICES_FN)(D3D_DEVICE_VIEW*, void*, unsigned int);













#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d3_DrawObjectShadowPatches(char* o)
{
	int i;
	char* e;

	for (i = 0; i < 4; i++) {
		e = *(char**) (o + 0x1ec) + i * 0x9c + 0x1384;
		if (*(char**) e != 0 && *(int*) (e + 0x90) > 0) {
			((D3_SHADOW_STREAM_FN) ((void**)((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl)[0x14c / 4])(((D3D_DEVICE_VIEW*)g_6b5de0), 0, *(void**) (e + 0x80), 0x18);
			((D3_SHADOW_INDICES_FN) ((void**)((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl)[0x154 / 4])(((D3D_DEVICE_VIEW*)g_6b5de0), *(void**) (e + 0x84), 0);
			((D3_SHADOW_TEXTURE_FN) ((void**)((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl)[0xf4 / 4])(((D3D_DEVICE_VIEW*)g_6b5de0), 0, *(void**) (*(char**) e + 0x50));
			((D3_SHADOW_DRAW_FN) ((void**)((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl)[0x11c / 4])(((D3D_DEVICE_VIEW*)g_6b5de0), 4, 0, *(unsigned int*) (e + 0x94), 0, *(unsigned int*) (e + 0x90));
			d3_RenderedVertexCount += *(int*) (e + 0x94);
			d3_RenderedFaceCount += *(int*) (e + 0x90);
		}
	}
}
