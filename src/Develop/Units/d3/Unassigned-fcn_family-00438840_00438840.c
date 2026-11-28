extern float g_1042ce4;
extern float g_1042a14;
extern float g_1042588;
extern float g_104328c;
extern char g_6b8060;
extern float g_10529d0;
extern float d3_ViewportZFar;
extern float g_1042a24;
extern float g_1042a28;
extern float d3_ProjectionDist;
extern float d3_ViewportZNear;
extern float g_1043288;
extern float g_10529c4;
extern float g_10529d4;
extern float g_10529d8;

void __cdecl d3_SetViewport(float, float, float, float, float, float, float, float, float);
void __cdecl d3_InvalidateSceneRenderCache(unsigned char);
#include "Develop/Units/d8_vesa/d3d_device_view.h"
typedef long (__stdcall* FloatRenderStateFn)(D3D_DEVICE_VIEW*, int, float);









extern int d3_FogColor;
extern float g_10425fc;
extern float g_104329c;

void __cdecl d3_SetFogRange(float, float);
void __cdecl d3_SetViewport(float, float, float, float, float, float, float, float, float);

/* ADDRESS: GOLD 0x0043a610 */
/* ADDRESS: GOLDTL 0x00438840 */
/* ADDRESS: GOLDDE 0x00431a90 */
void __cdecl d3_SetFogRange(float a, float b)
{
	float lim;

	if (g_1042ce4 == a && g_1042a14 == b) {
		return;
	}
	g_1042588 = 255.0f / (b - a);
	g_1042ce4 = a;
	g_1042a14 = b;
	g_104328c = a * a;
	if (g_6b8060 != 0) {
		lim = g_10529d0;
	} else {
		g_10529d0 = d3_ViewportZFar;
		lim = d3_ViewportZFar;
	}
	if (b < lim) {
		d3_SetViewport(g_10529d8, g_10529d4, g_10529c4, g_1043288, d3_ViewportZNear, b, d3_ProjectionDist, g_1042a28, g_1042a24);
	}
	d3_InvalidateSceneRenderCache(0);
}

/* ADDRESS: GOLDTL 0x00438920 */
/* ADDRESS: GOLDDE 0x00431b70 */
void __cdecl d3_SetFog(float fog_start, float fog_end, int fog_color)
{
	char on;

	if (fog_start < fog_end) {
		on = 1;
		d3_SetFogRange(fog_start, fog_end);
		g_10425fc = fog_start;
		g_104329c = fog_end;
		((FloatRenderStateFn) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState)(((D3D_DEVICE_VIEW*)g_6b5de0), 0x24, g_1042ce4);
		((FloatRenderStateFn) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState)(((D3D_DEVICE_VIEW*)g_6b5de0), 0x25, g_1042a14);
	} else {
		on = 0;
		if (g_6b8060 != 0) {
			d3_SetViewport(g_10529d8, g_10529d4, g_10529c4, g_1043288, d3_ViewportZNear, g_10529d0, d3_ProjectionDist, g_1042a28, g_1042a24);
		}
		g_10425fc = fog_start;
		g_104329c = fog_end;
	}
	g_6b8060 = on;
	d3_FogColor = fog_color;
}
