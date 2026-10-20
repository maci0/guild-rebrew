#include <math.h>

double __cdecl atan2(double, double);
double __cdecl sin(double);
double __cdecl cos(double);
#pragma intrinsic(atan2, sin, cos)

extern float g_1052bbc;
extern float g_1052bb4;
extern float g_10432a4;
extern float g_1042584;
extern float g_1042ce8;
extern float g_1042fa4;
extern float g_10529c8;
extern float g_10421a0;
extern float g_6628a8;
extern float g_1042fc8[24];
extern float g_10425a0[19];

void __cdecl fcn_00451900(float* a, float* m);

/* ADDRESS: GOLDTL 0x00437bc0 */

/* Rebuilds the view frustum: the four side planes from the half-angles of the
 * viewport, the four corner rays and the near and far planes. */
void __cdecl fcn_00437bc0(void)
{
	float ax;
	float ay;
	float s;
	float c;
	float a[3];
	float m[16];

	ax = (float) atan2(g_1052bbc, g_10432a4);
	g_1042ce8 = ax;
	g_1042fc8[0] = c = (float) cos((double) ax);
	g_1042fc8[1] = 0.0f;
	g_1042fc8[2] = s = (float) sin((double) ax);
	g_1042fc8[3] = -1e-7f;
	g_1042fc8[4] = -c;
	g_1042fc8[5] = 0.0f;
	g_1042fc8[6] = s;
	g_1042fc8[7] = 1e-7f;
	ay = (float) atan2(g_1052bb4, -g_1042584);
	g_1042fa4 = ay;
	g_1042fc8[8] = 0.0f;
	g_1042fc8[9] = c = (float) cos((double) ay);
	g_1042fc8[10] = s = (float) sin((double) ay);
	g_1042fc8[11] = 1e-7f;
	g_1042fc8[12] = 0.0f;
	g_1042fc8[13] = -c;
	g_1042fc8[14] = s;
	g_1042fc8[15] = -1e-7f;
	a[0] = -ay;
	a[1] = -ax;
	a[2] = 0.0f;
	fcn_00451900(a, m);
	g_10425a0[0] = (m[0] + m[4]) * g_6628a8 + m[8];
	g_10425a0[1] = (m[1] + m[5]) * g_6628a8 + m[9];
	g_10425a0[2] = (m[2] + m[6]) * g_6628a8 + m[10];
	a[0] = -ay;
	a[1] = ax;
	a[2] = 0.0f;
	fcn_00451900(a, m);
	g_10425a0[4] = (m[0] + m[4]) * g_6628a8 + m[8];
	g_10425a0[5] = (m[1] + m[5]) * g_6628a8 + m[9];
	g_10425a0[6] = (m[2] + m[6]) * g_6628a8 + m[10];
	a[0] = ay;
	a[1] = -ax;
	a[2] = 0.0f;
	fcn_00451900(a, m);
	g_10425a0[8] = (m[0] + m[4]) * g_6628a8 + m[8];
	g_10425a0[9] = (m[1] + m[5]) * g_6628a8 + m[9];
	g_10425a0[10] = (m[2] + m[6]) * g_6628a8 + m[10];
	a[0] = ay;
	a[1] = ax;
	a[2] = 0.0f;
	fcn_00451900(a, m);
	g_10425a0[12] = (m[0] + m[4]) * g_6628a8 + m[8];
	g_10425a0[13] = (m[1] + m[5]) * g_6628a8 + m[9];
	g_10425a0[14] = (m[2] + m[6]) * g_6628a8 + m[10];
	g_10425a0[16] = 0.0f;
	g_10425a0[17] = 0.0f;
	g_10425a0[18] = 1.0f;
	g_1042fc8[16] = 0.0f;
	g_1042fc8[17] = 0.0f;
	g_1042fc8[18] = 1.0f;
	g_1042fc8[19] = g_10529c8;
	g_1042fc8[20] = 0.0f;
	g_1042fc8[21] = 0.0f;
	g_1042fc8[22] = -1.0f;
	g_1042fc8[23] = -g_10421a0;
}
