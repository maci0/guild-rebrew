

#include "Develop/Units/d3/d3_camera.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
extern float g_10432a4;
float* __stdcall fcn_005ebbb9(float* out, const float* in);
void __cdecl fcn_004518a0(float* v);

void __cdecl fcn_004132a0(float x, float y, float y0, float y1, float* out)
{
	float v[4];
	float m[16];
	float dx;
	float dy;
	float t;

	fcn_005ebbb9(m, (float*) (((char*)d3_ActiveCamera) + 0x18c));
	v[0] = x - d3_ViewportCenterX;
	v[1] = -(y - g_1052bc8);
	v[2] = g_10432a4;
	fcn_004518a0(v);
	dx = m[8] * v[2] + m[4] * v[1] + m[0] * v[0];
	dy = m[9] * v[2] + m[5] * v[1] + m[1] * v[0];
	v[2] = m[10] * v[2] + m[6] * v[1] + m[2] * v[0];
	t = (y1 - y0) / dy;
	out[0] = t * dx;
	out[1] = t * dy;
	out[2] = t * v[2];
}
