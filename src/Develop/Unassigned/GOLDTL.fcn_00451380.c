#include <math.h>

extern double g_662958;
extern float d3_BasisUpX;
extern float d3_BasisUpY;
extern float d3_BasisUpZ;

void __cdecl d3_NormalizeVector(float* v);
int __cdecl CompareVector3WithinTolerance(float* a, float* b, float eps);

/* ADDRESS: GOLDTL 0x00451380 */
float __cdecl d3_SignedPlanarAngle(float* vecA, float* vecB)
{
	float va[4];
	float vb[4];
	float nvb[4];
	float cr[3];
	float cross;

	va[0] = vecA[0];
	vb[1] = 0.0f;
	va[1] = 0.0f;
	va[2] = vecA[2];
	vb[0] = vecB[0];
	vb[2] = vecB[2];
	d3_NormalizeVector(va);
	d3_NormalizeVector(vb);
	if (CompareVector3WithinTolerance(va, vb, 1.0e-7f)) {
		return 0.0f;
	}
	nvb[0] = -vb[0];
	nvb[1] = -vb[1];
	nvb[2] = -vb[2];
	if (CompareVector3WithinTolerance(va, nvb, 1.0e-7f)) {
		return -3.1415927f;
	}
	cr[0] = vb[2] * va[1] - vb[1] * va[2];
	cr[1] = vb[0] * va[2] - vb[2] * va[0];
	cr[2] = vb[1] * va[0] - vb[0] * va[1];
	cross = d3_BasisUpX * cr[0] + d3_BasisUpY * cr[1] + d3_BasisUpZ * cr[2];
	if (cross > 0.0f) {
		return (float) (-asin(vb[2] * va[2] + vb[1] * va[1] + vb[0] * va[0]));
	}
	return (float) (asin(vb[2] * va[2] + vb[1] * va[1] + vb[0] * va[0]) - g_662958);
}
