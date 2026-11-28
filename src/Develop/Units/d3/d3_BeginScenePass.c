#include "Develop/Units/d8_vesa/d3d_device_view.h"
typedef long (__stdcall* D3_SCENE_METHOD_FN)(D3D_DEVICE_VIEW*);
typedef long (__stdcall* D3_TEXTURE_SET_FN)(D3D_DEVICE_VIEW*, int, int);














#include "Develop/client_types.h"
extern VECTOR3 d3_SceneAmbientColor;
extern float g_1052bd8;
extern int g_1052bdc;
extern char g_1052c40;
extern unsigned char g_6b7ff9;
extern char d3_RenderAmbientOnly;
extern unsigned char g_6b7ffd;
extern char d3_LightingEnabled;

void __cdecl d3_SetScaledMaterial(float a, char* b, int c, int d);

/* ADDRESS: GOLDTL 0x00437160 */
/* ADDRESS: GOLDDE 0x00430660 */
void __cdecl d3_BeginScenePass(unsigned char fog, int color, char light)
{
	((D3_SCENE_METHOD_FN) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->unk_00[34])(((D3D_DEVICE_VIEW*)g_6b5de0));
	((D3_TEXTURE_SET_FN) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->unk_cc[10])(((D3D_DEVICE_VIEW*)g_6b5de0), 0, 0);
	d3_SetScaledMaterial(1.0f, &(*(char*)&d3_SceneAmbientColor), 0, 0);
	g_1052bd8 = 1.0f;
	g_1052bdc = 0;
	g_1052c40 = 0;
	((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 0x1c, fog);
	if (fog) {
		((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 0x22, color);
	}
	((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 7, light ? ((*(char *)&g_6b7ff9) != 0) + 1 : 0);
	if (light) {
		((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 0xe, light && d3_RenderAmbientOnly == 0);
		((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 0x2f, d3_RenderAmbientOnly ? 0x10 : 0);
	}
	g_6b7ffd = fog;
	d3_LightingEnabled = light;
}
