#include <math.h>

extern char* g_6b8014;
extern float g_1052bc0;
extern float g_1052bc8;
extern float g_10432a4;
extern float g_1042584;
extern float g_6628a8;
extern float g_6628a0;
extern double g_662e68;

float* __stdcall fcn_005ebbb9(float* out, const float* in);

/* Projects the screen point into map space and steps along the ray until a
 * map cell (x, z) is at least as high as the ray's y. */
/* ADDRESS: GOLDTL 0x0045bad0 */
char __cdecl fcn_0045bad0(char* e, int gx, int gy, int* ox, int* oy)
{
	float m[16];
	float u;
	float v;
	float x0;
	float y0;
	float z0;
	float px;
	float py;
	float pz;
	float t;
	float lim;
	int ix;
	int iz;
	int iw;

	if (e == 0) {
		return 0;
	}
	x0 = (*(float*) (g_6b8014 + 0x4c) - *(float*) (e + 0)) / *(float*) (e + 0x10);
	y0 = (*(float*) (g_6b8014 + 0x50) - *(float*) (e + 4)) / *(float*) (e + 0x14);
	z0 = (*(float*) (g_6b8014 + 0x54) - *(float*) (e + 8)) / *(float*) (e + 0x18);
	u = ((float) gx - g_1052bc0) / g_10432a4;
	v = ((float) gy - g_1052bc8) / g_1042584;
	fcn_005ebbb9(m, (float*) (g_6b8014 + 0x18c));
	px = m[4] * v + m[0] * u + m[8];
	py = m[5] * v + m[1] * u + m[9];
	pz = m[6] * v + m[2] * u + m[10];
	px = px / *(float*) (e + 0x10);
	py = py / *(float*) (e + 0x14);
	pz = pz / *(float*) (e + 0x18);
	if (fabs(px) < g_662e68 && fabs(pz) < g_662e68) {
		ix = (int) x0;
		iz = (int) z0;
		if (py > g_6628a8) {
			if ((float) *(unsigned char*) (*(int*) (e + 0x28) + *(int*) (e + 0x20) * iz + ix) < y0) {
				return 0;
			}
		}
		*ox = ix;
		*oy = iz;
		return 1;
	}
	t = g_6628a0 / (fabs(px) > fabs(pz) ? fabs(px) : fabs(pz));
	px = px * t;
	py = py * t;
	pz = pz * t;
	if (!(x0 >= g_6628a8)) {
		return 0;
	}
	iw = *(int*) (e + 0x20);
	lim = (float) iw;
	do {
		if (!(x0 < lim)) {
			return 0;
		}
		if (!(z0 >= g_6628a8)) {
			return 0;
		}
		if (!(z0 < lim)) {
			return 0;
		}
		if ((float) *(unsigned char*) (*(int*) (e + 0x28) + (int) z0 * iw + (int) x0) >= y0) {
			*ox = (int) x0;
			*oy = (int) z0;
			return 1;
		}
		x0 = x0 + px;
		y0 = y0 + py;
		z0 = z0 + pz;
	} while (x0 >= g_6628a8);
	return 0;
}
