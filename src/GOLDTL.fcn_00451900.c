// FUNCTION: GOLD 0x4545b0
// SIZE: 198
// FUNCTION: GOLDTL 0x451900
// SIZE: 198

#include <math.h>

void __cdecl fcn_00451900(float* a, float* m)
{
	float sx;
	float sy;
	float sz;
	float cx;
	float cz;
	float czsy;
	float t[2];

	sx = sin(a[0]);
	sy = sin(a[1]);
	sz = sin(a[2]);
	cx = cos(a[0]);
	t[0] = cos(a[1]);
	cz = cos(a[2]);
	m[11] = 0.0f;
	m[7] = 0.0f;
	m[3] = 0.0f;
	m[14] = 0.0f;
	m[13] = 0.0f;
	m[12] = 0.0f;
	m[15] = 1.0f;
	czsy = cz * sy;
	t[1] = sz * sy;
	m[0] = cz * t[0];
	m[1] = czsy * sx - cx * sz;
	m[2] = czsy * cx + sz * sx;
	m[4] = t[0] * sz;
	m[5] = cx * cz + t[1] * sx;
	m[6] = t[1] * cx - cz * sx;
	m[8] = -sy;
	m[9] = t[0] * sx;
	m[10] = t[0] * cx;
}
