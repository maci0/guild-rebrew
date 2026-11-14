/* Gold twin of GOLDTL 0x004424c0: quad/frustum clipping test against the
 * basis matrix at a2 and the five stored planes at 0xfc2964, returning the
 * nearest positive crossing. 0xfc2964 and the 1.0f pool constant at 0x5eb780
 * have no Gold data names, so both are read through their addresses. */

#include <math.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

/* ADDRESS: GOLD 0x00446990 */
float __cdecl fcn_00446990(float* a0, float* a1, float* a2)
{
	float* tp;
	float u0;
	float u1;
	float u2;
	float t0;
	float t1;
	float t2;
	float c0;
	float c1;
	float c2;
	float v0;
	float v1;
	float v2;
	float k;
	float d;
	float t;
	float mn;
	float best;
	float plane[4][4];
	int i;
	int j;

	u0 = a0[36] - a1[0];
	u1 = a0[37] - a1[1];
	u2 = a0[38] - a1[2];
	t0 = u0*a2[0] + u2*a2[8] + u1*a2[4];
	t1 = u0*a2[1] + u2*a2[9] + u1*a2[5];
	t2 = u2*a2[10] + u1*a2[6] + u0*a2[2];
	c0 = a2[4]*0.0f;
	plane[0][0] = (a2[0]*0.0f - a2[8] * *(float*) 0x5eb780) + c0;
	c1 = a2[5]*0.0f;
	plane[0][1] = (a2[1]*0.0f - a2[9] * *(float*) 0x5eb780) + c1;
	c2 = a2[6]*0.0f;
	plane[0][2] = (a2[2]*0.0f - a2[10] * *(float*) 0x5eb780) + c2;
	plane[0][3] = plane[0][2]*t2 + plane[0][1]*t1 + plane[0][0]*t0;
	v0 = a2[8]*0.0f + c0;
	plane[1][0] = v0 + a2[0];
	v1 = a2[9]*0.0f + c1;
	plane[1][1] = v1 + a2[1];
	v2 = a2[10]*0.0f + c2;
	plane[1][2] = v2 + a2[2];
	plane[1][3] = plane[1][2]*t2 + plane[1][1]*t1 + plane[1][0]*t0;
	k = (float) (*(int*) a0 - 4);
	u0 = (a0[36] + k*a0[40] + k*a0[44]) - a1[0];
	u1 = (a0[37] + k*a0[41] + k*a0[45]) - a1[1];
	u2 = (a0[38] + k*a0[42] + k*a0[46]) - a1[2];
	t0 = u0*a2[0] + u2*a2[8] + u1*a2[4];
	t1 = u0*a2[1] + u2*a2[9] + u1*a2[5];
	t2 = u2*a2[10] + u1*a2[6] + u0*a2[2];
	plane[2][0] = v0 - a2[0] * *(float*) 0x5eb780;
	plane[2][1] = v1 - a2[1] * *(float*) 0x5eb780;
	plane[2][2] = v2 - a2[2] * *(float*) 0x5eb780;
	plane[2][3] = plane[2][2]*t2 + plane[2][1]*t1 + plane[2][0]*t0;
	plane[3][0] = a2[0]*0.0f + c0 + a2[8];
	plane[3][1] = a2[1]*0.0f + c1 + a2[9];
	plane[3][2] = a2[2]*0.0f + c2 + a2[10];
	plane[3][3] = plane[3][2]*t2 + plane[3][1]*t1 + plane[3][0]*t0;
	mn = MIN(plane[0][3], MIN(plane[1][3], MIN(plane[2][3], plane[3][3])));
	best = 1e10;
	tp = (float*) 0xfc2964;
	for (j = 0; j < 5; j++) {
		for (i = 0; i < 4; i++) {
			d = plane[i][0]*tp[0] + plane[i][2]*tp[2] + tp[1]*plane[i][1];
			if (d < -1e-7f || d > 1e-7f) {
				t = plane[i][3] / d;
				if (t > 0.0f) {
					if (t > mn) {
						if (t < best) {
							best = t;
						}
					}
				}
			}
		}
		tp += 4;
	}
	if (best == 1e10) {
		return fabs(mn);
	}
	return best;
}
