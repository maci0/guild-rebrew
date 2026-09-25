// FUNCTION: GOLD 0x00525f20
// SIZE: 272
// FUNCTION: GOLDTL 0x0052ad70
// SIZE: 272

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

extern View* g_6b8014;
extern float g_774690;
extern float g_6a2558;
extern float g_6a2560;
extern int g_6b5cc0;
extern float g_774730;

float __cdecl fcn_00413d10(float* p);
void __cdecl fcn_00438b40(View* v, Vec4* p);

void __cdecl fcn_0052ad70(void)
{
	float step;
	Vec4 p;
	float d;
	View* v;

	if (g_6b8014 != 0) {
		d = fcn_00413d10(&g_6b8014->x);
		v = g_6b8014;
		d = d + ((g_6a2560 - g_6a2558) * g_774690 + g_6a2558) - (v->height + v->y);
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
			if (g_6b5cc0 == 0) {
				fcn_00438b40(v, &p);
			}
			g_774730 = step;
		} else {
			g_774730 = 0.0f;
		}
	}
}
