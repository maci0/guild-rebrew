/* Quad/frustum clipping test against the basis matrix at camRot and the five
 * stored planes (0xfc2960 in Gold, g_10425a0 in GoldTL), returning the nearest
 * positive crossing. */

#include <math.h>
#include "Develop/DieGildeAddOn/game/game_data.h"
extern float g_10425a0[];

#define MIN(a, b) ((a) < (b) ? (a) : (b))

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x00446990 */
float __cdecl d3_CalcFloorFogDistance(float* floor, float* camPos, float* camRot)
{
	float* tp;
	float t[4];
	float u[4];
	float c0;
	float c1;
	float c2;
	float v0;
	float v1;
	float v2;
	float k;
	float d;
	float cross_t;
	float mn;
	float best;
	float plane[4][4];
	int i;
	int j;

	u[0] = floor[36] - camPos[0];
	u[1] = floor[37] - camPos[1];
	u[2] = floor[38] - camPos[2];
	t[0] = u[0]*camRot[0] + u[2]*camRot[8] + u[1]*camRot[4];
	t[1] = u[0]*camRot[1] + u[2]*camRot[9] + u[1]*camRot[5];
	t[2] = u[2]*camRot[10] + u[1]*camRot[6] + u[0]*camRot[2];
	c0 = camRot[4]*0.0f;
	plane[0][0] = (camRot[0]*0.0f - camRot[8] * *(float*) 0x5eb780) + c0;
	c1 = camRot[5]*0.0f;
	plane[0][1] = (camRot[1]*0.0f - camRot[9] * *(float*) 0x5eb780) + c1;
	c2 = camRot[6]*0.0f;
	plane[0][2] = (camRot[2]*0.0f - camRot[10] * *(float*) 0x5eb780) + c2;
	plane[0][3] = plane[0][2]*t[2] + plane[0][1]*t[1] + plane[0][0]*t[0];
	v0 = camRot[8]*0.0f + c0;
	plane[1][0] = v0 + camRot[0];
	v1 = camRot[9]*0.0f + c1;
	plane[1][1] = v1 + camRot[1];
	v2 = camRot[10]*0.0f + c2;
	plane[1][2] = v2 + camRot[2];
	plane[1][3] = plane[1][2]*t[2] + plane[1][1]*t[1] + plane[1][0]*t[0];
	k = (float) (*(int*) floor - 4);
	u[0] = k*floor[40] + floor[36];
	u[1] = k*floor[41] + floor[37];
	u[2] = k*floor[42] + floor[38];
	u[0] += k*floor[44];
	u[1] += k*floor[45];
	u[2] += k*floor[46];
	u[0] -= camPos[0];
	u[1] -= camPos[1];
	u[2] -= camPos[2];
	t[0] = u[0]*camRot[0] + u[2]*camRot[8] + u[1]*camRot[4];
	t[1] = u[0]*camRot[1] + u[2]*camRot[9] + u[1]*camRot[5];
	t[2] = u[2]*camRot[10] + u[1]*camRot[6] + u[0]*camRot[2];
	plane[2][0] = v0 - camRot[0] * *(float*) 0x5eb780;
	plane[2][1] = v1 - camRot[1] * *(float*) 0x5eb780;
	plane[2][2] = v2 - camRot[2] * *(float*) 0x5eb780;
	plane[2][3] = plane[2][2]*t[2] + plane[2][1]*t[1] + plane[2][0]*t[0];
	plane[3][0] = camRot[0]*0.0f + c0 + camRot[8];
	plane[3][1] = camRot[1]*0.0f + c1 + camRot[9];
	plane[3][2] = camRot[2]*0.0f + c2 + camRot[10];
	plane[3][3] = plane[3][2]*t[2] + plane[3][1]*t[1] + plane[3][0]*t[0];
	mn = MIN(plane[0][3], MIN(plane[1][3], MIN(plane[2][3], plane[3][3])));
	best = 1e10;
	tp = (float*) 0xfc2960;
	for (j = 0; j < 5; j++) {
		for (i = 0; i < 4; i++) {
			d = plane[i][0]*tp[0] + plane[i][2]*tp[2] + tp[1]*plane[i][1];
			if (d < -1e-7f || d > 1e-7f) {
				cross_t = plane[i][3] / d;
				if (cross_t > 0.0f) {
					if (cross_t > mn) {
						if (cross_t < best) {
							best = cross_t;
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
#else
/* The native body multiplies by the pool literal 1.0f at 0x6628a0 as a memory
 * operand, so it is read through its address; a source-level 1.0f multiply is
 * folded away by this compiler. The 0.0f, 1e-7f and 1e10 constants are plain
 * literals. */

/* ADDRESS: GOLDTL 0x004424c0 */
float __cdecl d3_CalcFloorFogDistance(float* floor, float* camPos, float* camRot)
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

	u0 = floor[20] - camPos[0];
	u1 = floor[21] - camPos[1];
	u2 = floor[22] - camPos[2];
	t0 = u0*camRot[0] + u2*camRot[8] + u1*camRot[4];
	t1 = u0*camRot[1] + u2*camRot[9] + u1*camRot[5];
	t2 = u2*camRot[10] + u1*camRot[6] + u0*camRot[2];
	c0 = camRot[4]*0.0f;
	plane[0][0] = (camRot[0]*0.0f - camRot[8]*g_6628a0) + c0;
	c1 = camRot[5]*0.0f;
	plane[0][1] = (camRot[1]*0.0f - camRot[9]*g_6628a0) + c1;
	c2 = camRot[6]*0.0f;
	plane[0][2] = (camRot[2]*0.0f - camRot[10]*g_6628a0) + c2;
	plane[0][3] = plane[0][2]*t2 + plane[0][1]*t1 + plane[0][0]*t0;
	v0 = camRot[8]*0.0f + c0;
	plane[1][0] = v0 + camRot[0];
	v1 = camRot[9]*0.0f + c1;
	plane[1][1] = v1 + camRot[1];
	v2 = camRot[10]*0.0f + c2;
	plane[1][2] = v2 + camRot[2];
	plane[1][3] = plane[1][2]*t2 + plane[1][1]*t1 + plane[1][0]*t0;
	k = (float) (*(int*) floor - 4);
	u0 = (floor[20] + k*floor[24] + k*floor[28]) - camPos[0];
	u1 = (floor[21] + k*floor[25] + k*floor[29]) - camPos[1];
	u2 = (floor[22] + k*floor[26] + k*floor[30]) - camPos[2];
	t0 = u0*camRot[0] + u2*camRot[8] + u1*camRot[4];
	t1 = u0*camRot[1] + u2*camRot[9] + u1*camRot[5];
	t2 = u2*camRot[10] + u1*camRot[6] + u0*camRot[2];
	plane[2][0] = v0 - camRot[0]*g_6628a0;
	plane[2][1] = v1 - camRot[1]*g_6628a0;
	plane[2][2] = v2 - camRot[2]*g_6628a0;
	plane[2][3] = plane[2][2]*t2 + plane[2][1]*t1 + plane[2][0]*t0;
	plane[3][0] = camRot[0]*0.0f + c0 + camRot[8];
	plane[3][1] = camRot[1]*0.0f + c1 + camRot[9];
	plane[3][2] = camRot[2]*0.0f + c2 + camRot[10];
	plane[3][3] = plane[3][2]*t2 + plane[3][1]*t1 + plane[3][0]*t0;
	mn = MIN(plane[0][3], MIN(plane[1][3], MIN(plane[2][3], plane[3][3])));
	best = 1e10;
	tp = g_10425a0;
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
/* Layout scaffolding: shifts the next source object to its reference
 * VA. 0x90 filler, not reconstruction. Generated by the text lead pass. */
#pragma data_seg(".text")
#endif
