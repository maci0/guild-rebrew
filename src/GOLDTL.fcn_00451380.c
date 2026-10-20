#include <math.h>

void __cdecl fcn_004518a0(float* v);
int __cdecl fcn_00451840(float* a, float* b, float eps);

/* ADDRESS: GOLDTL 0x00451380 */
float __cdecl fcn_00451380(float* a, float* b)
{
	float va[4];
	float vb[4];
	float nvb[4];
	float cross;

	va[0] = a[0];
	va[1] = 0.0f;
	va[2] = a[2];
	vb[0] = b[0];
	vb[1] = 0.0f;
	vb[2] = b[2];
	fcn_004518a0(va);
	fcn_004518a0(vb);
	if (fcn_00451840(va, vb, 1.0e-7f)) {
		return *(float*) 0x6628a8;
	}
	nvb[0] = -vb[0];
	nvb[1] = -vb[1];
	nvb[2] = -vb[2];
	if (fcn_00451840(va, nvb, 1.0e-7f)) {
		return *(float*) 0x6628f8;
	}
	cross = *(float*) 0x662d68 * (vb[2] * va[1] - vb[1] * va[2]) + *(float*) 0x662d64 * (vb[0] * va[2] - vb[2] * va[0]) + *(float*) 0x662d60 * (vb[1] * va[0] - vb[0] * va[1]);
	if (cross > *(float*) 0x6628a8) {
		return (float) (-asin(vb[2] * va[2] + vb[1] * va[1] + vb[0] * va[0]));
	}
	return (float) (asin(vb[2] * va[2] + vb[1] * va[1] + vb[0] * va[0]) - *(double*) 0x662958);
}
