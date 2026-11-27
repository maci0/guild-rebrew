extern float g_10529d8;
extern float g_10529d4;
extern float g_10529c4;
extern float g_1043288;
extern float g_10529c8;
extern float g_10421a0;
extern float g_10432a4;
extern float g_1042a28;
extern float g_1042a24;
extern float g_1052bbc;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern float g_1052bb4;
extern float g_1042a10;
extern float g_1042a18;
extern float g_1042fa4;

void __cdecl d3_UpdateViewFrustum(void);
void __cdecl d3_SetViewportAndProjection(float fov, float aspect, float width, float height, float x, float y, float znear, float zfar);
void __cdecl d3_InvalidateSceneRenderCache(unsigned char);


/* Sets the 3D viewport (size, origin, depth range, view distance, screen
 * mode) and rebuilds the projection when anything changed. */
/* ADDRESS: GOLDTL 0x00438da0 */
void __cdecl d3_SetViewport(float w, float h, float x, float y, float znear, float zfar, float dist, int sw, int sh)
{
	int left;
	int top;
	int right;
	int bottom;

	if (g_10529d8 == w && g_10529d4 == h && g_1042570 == x && g_1042574 == y && g_10432a4 == dist && g_10529c8 == znear
	    && g_10421a0 == zfar && (*(int*)&g_1042a28) == sw && (*(int*)&g_1042a24) == sh) {
		return;
	}
	(*(int*)&g_1042a28) = sw;
	(*(int*)&g_1042a24) = sh;
	g_10529d8 = w;
	g_10529d4 = h;
	g_10529c8 = znear;
	g_10421a0 = zfar;
	d3_ViewportCenterX = (g_1052bbc = w * 0.5f) + x;
	g_10529c4 = x;
	g_1043288 = y;
	g_1052bc8 = (g_1052bb4 = h * 0.5f) + y;
	g_1042a10 = 1.0f / zfar;
	g_1042a18 = sh * 4.0f / (sw * 3.0f);
	g_10432a4 = dist;
	d3_ProjectionScaleY = g_1042a18 * dist * -1.0f;
	left = (int) (x + 0.5f);
	top = (int) (y + 0.5f);
	right = (int) (w + x);
	bottom = (int) (h + y);
	if (left != g_1042570 || right != d3_ViewportRight || top != g_1042574 || bottom != d3_ViewportBottom) {
		g_1042570 = left;
		g_1042574 = top;
		d3_ViewportRight = right;
		d3_ViewportBottom = bottom;
	}
	d3_UpdateViewFrustum();
	d3_SetViewportAndProjection(g_1042fa4 + g_1042fa4, w / h, w, h, x, y, znear, zfar);
	d3_InvalidateSceneRenderCache(0);
}
unsigned char _dpad_10529c8[484];
