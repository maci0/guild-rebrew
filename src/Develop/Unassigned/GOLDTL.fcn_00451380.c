#include <math.h>

extern float g_662d60;
extern float g_662d64;
extern float g_662d68;

void __cdecl fcn_004518a0(float* v);
int __cdecl CompareVector3WithinTolerance(float* a, float* b, float eps);

/* ADDRESS: GOLDTL 0x00451380 */
float __cdecl fcn_00451380(float* a, float* b)
{
	float va[4];
	float vb[4];
	float nvb[4];
	float cr[3];
	float cross;

	va[0] = a[0];
	vb[1] = 0.0f;
	va[1] = 0.0f;
	va[2] = a[2];
	vb[0] = b[0];
	vb[2] = b[2];
	fcn_004518a0(va);
	fcn_004518a0(vb);
	if (CompareVector3WithinTolerance(va, vb, 1.0e-7f)) {
		return *(float*) 0x6628a8;
	}
	nvb[0] = -vb[0];
	nvb[1] = -vb[1];
	nvb[2] = -vb[2];
	if (CompareVector3WithinTolerance(va, nvb, 1.0e-7f)) {
		return *(float*) 0x6628f8;
	}
	cr[0] = *(volatile float*) &vb[2] * va[1] - *(volatile float*) &vb[1] * va[2];
	cr[1] = *(volatile float*) &vb[0] * va[2] - *(volatile float*) &vb[2] * va[0];
	cr[2] = *(volatile float*) &vb[1] * va[0] - *(volatile float*) &vb[0] * va[1];
	cross = g_662d60 * cr[0] + g_662d64 * cr[1] + g_662d68 * cr[2];
	if (cross > *(float*) 0x6628a8) {
		return (float) (-asin(*(volatile float*) &vb[2] * va[2] + *(volatile float*) &vb[1] * va[1] + *(volatile float*) &vb[0] * va[0]));
	}
	return (float) (asin(*(volatile float*) &vb[2] * va[2] + *(volatile float*) &vb[1] * va[1] + *(volatile float*) &vb[0] * va[0]) - *(double*) 0x662958);
}
