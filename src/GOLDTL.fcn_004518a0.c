#include <math.h>

extern float g_6628a8;
extern float g_6628a0;

// FUNCTION: GOLDTL 0x4518a0
// SIZE: 89
void __cdecl fcn_004518a0(float* v)
{
	float x;
	float y;
	float z;
	float len;

	z = v[2];
	y = v[1];
	x = v[0];
	len = (float) sqrt(x * x + y * y + z * z);
	if (len != g_6628a8) {
		len = g_6628a0 / len;
		v[0] *= len;
		v[1] *= len;
		v[2] *= len;
	} else {
		v[0] = 0.0f;
		v[1] = 0.0f;
		v[2] = 0.0f;
	}
}
