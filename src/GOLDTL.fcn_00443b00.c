

#include <math.h>

extern float g_10432a4;
extern float g_1042584;

char __cdecl fcn_0043a820(char*, int, float*, float*);

char __cdecl fcn_00443b00(char* e, char* ctx)
{
	float v[4];
	float w;
	float inv;
	float x;
	float y;
	float d2;
	char* d;
	float* slot;

	if (*(int*) (ctx + 0x4c) != 0 && (*(int*) (e + 0x224) & *(int*) (ctx + 0x4c)) == 0) {
		return 1;
	}
	d = *(char**) (e + 0x1ec);
	if (d != 0 && (d[0x163d] & 0x40) != 0 && *(int*) (d + 4) == *(int*) (ctx + 0x48)) {
		return 1;
	}
	if (*(int*) (e + 0x218) == 4 && d == 0) {
		return 1;
	}
	if (fcn_0043a820(e, *(int*) (ctx + 0x48), v, &w)) {
		inv = 1.0f / v[2];
		slot = (float*) (ctx + *(int*) (e + 0x218) * 8);
		w = g_10432a4 * inv * w;
		x = g_10432a4 * v[0] * inv + *(float*) (ctx + 0x50);
		y = g_1042584 * v[1] * inv + *(float*) (ctx + 0x54);
		d2 = x * x + y * y;
		if (d2 < slot[1] && (float) sqrt(d2) < w) {
			slot[1] = d2;
			*(char**) slot = e;
		}
	}
	return 1;
}
