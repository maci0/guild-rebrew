#include <math.h>

extern float flt_0_0;
extern float flt_1_0;

/* ADDRESS: GOLDTL 0x004518a0 */
void __cdecl d3_NormalizeVector(float* v)
{
	float x;
	float y;
	float z;
	float len;

	z = v[2];
	y = v[1];
	x = v[0];
	len = (float) sqrt(x * x + y * y + z * z);
	if (len != flt_0_0) {
		len = flt_1_0 / len;
		v[0] *= len;
		v[1] *= len;
		v[2] *= len;
	} else {
		v[0] = 0.0f;
		v[1] = 0.0f;
		v[2] = 0.0f;
	}
}
