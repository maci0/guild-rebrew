#include "Develop/Units/d8_vesa/d3d_device_view.h"
typedef long (__stdcall* Scene437160Fn)(D3D_DEVICE_VIEW*);
typedef long (__stdcall* Texture437160Fn)(D3D_DEVICE_VIEW*, int, int);














#include "client_types.h"
extern VECTOR3 g_67bbdc;
extern float g_1052bd8;
extern int g_1052bdc;
extern char g_1052c40;
extern unsigned char g_6b7ff9;
extern char g_6b7ffa;
extern unsigned char g_6b7ffd;
extern char g_67a2ac;

void __cdecl fcn_00450b20(float a, char* b, int c, int d);

/* ADDRESS: GOLDTL 0x00437160 */
void __cdecl fcn_00437160(unsigned char fog, int color, char light)
{
	((Scene437160Fn) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->unk_00[34])(((D3D_DEVICE_VIEW*)g_6b5de0));
	((Texture437160Fn) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->unk_cc[10])(((D3D_DEVICE_VIEW*)g_6b5de0), 0, 0);
	fcn_00450b20(1.0f, &(*(char*)&g_67bbdc), 0, 0);
	g_1052bd8 = 1.0f;
	g_1052bdc = 0;
	g_1052c40 = 0;
	((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 0x1c, fog);
	if (fog) {
		((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 0x22, color);
	}
	((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 7, light ? ((*(char *)&g_6b7ff9) != 0) + 1 : 0);
	if (light) {
		((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 0xe, light && g_6b7ffa == 0);
		((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 0x2f, g_6b7ffa ? 0x10 : 0);
	}
	g_6b7ffd = fog;
	g_67a2ac = light;
}
