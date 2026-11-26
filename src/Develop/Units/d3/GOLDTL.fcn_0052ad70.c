


#include <math.h>

// SIZE 0x10
typedef struct {
	float x;
	float y;
	float z;
	float w;
} Vec4;

// SIZE 0x80
typedef struct {
	char pad0[0x4c];
	float x;
	float y;
	float z;
	char pad58[0x7c - 0x58];
	float height;
} View;

#include "Develop/Units/d3/d3_camera.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d3_ActiveCameraAnimation;
extern float g_774730;

float __cdecl fcn_00413d10(float* p);
void __cdecl d3_SetNodePosition(View* v, Vec4* p);

void __cdecl d3_AdjustCameraHeight(void)
{
	float step;
	Vec4 p;
	float d;
	View* v;

	if (((View*)d3_ActiveCamera) != 0) {
		d = fcn_00413d10(&((View*)d3_ActiveCamera)->x);
		v = ((View*)d3_ActiveCamera);
		d = d + ((g_6a2560 - g_6a2558) * d3_CameraHeightFraction + g_6a2558) - (v->height + v->y);
		if (fabs(d) > 5.0) {
			step = d * 0.06666667f;
			if (step > 0.0f) {
				if (!(step < 10.0f)) {
					step = 10.0f;
				}
			} else if (step < 0.0f) {
				if (!(step > -10.0f)) {
					step = -10.0f;
				}
			}
			p.x = v->x;
			p.y = v->y;
			p.z = v->z;
			p.y = p.y + step;
			if (d3_ActiveCameraAnimation == 0) {
				d3_SetNodePosition(v, &p);
			}
			g_774730 = step;
		} else {
			g_774730 = 0.0f;
		}
	}
}
