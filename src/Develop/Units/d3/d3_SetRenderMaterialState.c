

#include "Develop/Units/d8_vesa/d3d_device_view.h"












#include "Develop/client_types.h"

extern VECTOR3 d3_SceneAmbientColor;
extern float g_1052bd8;
extern int g_1052bdc;
extern char g_1052c40;
extern char d3_RenderAmbientOnly;
extern unsigned char g_6b7ffb;
extern unsigned char g_6b7ffc;
extern unsigned char g_6b7ffd;
extern unsigned char g_6b7ffe;
extern unsigned char g_6b7fff;
extern char g_6b8000;
char d3_LightingEnabled = 1;

void __cdecl d3_SetScaledMaterial(float a, char* b, int c, char d);

void __cdecl d3_SetRenderMaterialState(unsigned char alpha, unsigned char flags, int color, unsigned char test, unsigned char cull)
{
	float f;
	unsigned char b;

	f = (float) alpha * (1.0f / 255.0f);
	if (alpha < 0xff || (flags & 1) != 0) {
		if (d3_RenderAmbientOnly == 0) {
			if (d3_LightingEnabled) {
				((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(g_6b5de0, 0x2f, 0x10);
				((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(g_6b5de0, 0xe, 0);
			}
			((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(g_6b5de0, 0x1b, 1);
			d3_RenderAmbientOnly = 1;
		}
		if ((flags & 1) != 0 && g_6b7ffb == 0) {
			((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(g_6b5de0, 0x14, 2);
			((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(g_6b5de0, 0x13, 2);
			if (g_6b7ffd) {
				((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(g_6b5de0, 0x1c, 0);
			}
			g_6b7ffb = 1;
		} else if ((flags & 1) == 0) {
			((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(g_6b5de0, 0x14, 6);
			((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(g_6b5de0, 0x13, 5);
			if (g_6b7ffd) {
				((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(g_6b5de0, 0x1c, 1);
			}
			g_6b7ffb = 0;
		}
	} else if (d3_RenderAmbientOnly != 0) {
		if (d3_LightingEnabled) {
			((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(g_6b5de0, 0x2f, 0);
			((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(g_6b5de0, 0xe, 1);
		}
		((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(g_6b5de0, 0x1b, 0);
		((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(g_6b5de0, 0x14, 1);
		((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(g_6b5de0, 0x13, 2);
		d3_RenderAmbientOnly = 0;
		g_6b7ffb = 0;
	}
	if (f != g_1052bd8 || color != g_1052bdc) {
		d3_SetScaledMaterial((float) alpha * (1.0f / 255.0f), (char*)&d3_SceneAmbientColor, color, flags & 1);
		g_1052bd8 = f;
		g_1052c40 = flags;
		g_1052bdc = color;
	}
	if (test != g_6b7ffc) {
		((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(g_6b5de0, 0xf, test);
		((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetTextureStageState(g_6b5de0, 0, 4, test ? 4 : 3);
		g_6b7ffc = test;
	}
	if (test) {
		((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(g_6b5de0, 0x18, d3_RenderAmbientOnly ? 0 : 0xbf);
	}
	if (cull != g_6b7ffe) {
		((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(g_6b5de0, 0x16, cull ? 1 : (g_6b8000 ? 2 : 3));
		g_6b7ffe = cull;
	}
	b = (flags >> 1) & 1;
	if (b != g_6b7fff) {
		g_6b7fff = b;
		((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetTextureStageState(g_6b5de0, 0, 0xb, b ? 0x30000 : 0);
		((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetTextureStageState(g_6b5de0, 0, 0x18, g_6b7fff ? 2 : 0);
	}
}
