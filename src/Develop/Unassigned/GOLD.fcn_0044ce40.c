#include <math.h>

/* ADDRESS: GOLD 0x0044ce40 */
void __cdecl fcn_0044ce40(char* object)
{
	float radius;
	float length;
	float mn[3], mx[3];
	float dx, dy, dz;
	float sx, sy, sz;
	float* p;
	float* corners;
	int n;
	int i;

	radius = 0.0f;
	n = *(int*) (object + 0x44);
	p = *(float**) (object + 0x40);
	for (i = n; i > 0; i--, p += 6) {
		length = (float) sqrt(p[2] * p[2] + p[0] * p[0] + p[1] * p[1]);
		if (length > radius)
			radius = length;
	}
	*(float*) (object + 0x1d8) = radius;
	*(float*) (object + 0x1d4) = radius;
	*(float*) (object + 0x68) = 0.0f;
	*(float*) (object + 0x6c) = 0.0f;
	*(float*) (object + 0x70) = 0.0f;
	if (n <= 0)
		return;
	mn[0] = mn[1] = mn[2] = 1.0e10f;
	mx[0] = mx[1] = mx[2] = -1.0e10f;
	corners = *(float**) (object + 0x40);
	for (p = corners, i = n; i > 0; i--, p += 6) {
		if (!(mn[0] < p[0])) mn[0] = p[0];
		if (!(p[1] > mn[1])) mn[1] = p[1];
		if (!(p[2] > mn[2])) mn[2] = p[2];
		if (!(mx[0] > p[0])) mx[0] = p[0];
		if (!(p[1] < mx[1])) mx[1] = p[1];
		if (!(mx[2] > p[2])) mx[2] = p[2];
	}
	corners[n * 6] = mn[0];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 1] = mn[1];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 2] = mn[2];
	(*(float**) (object + 0x40))[(*(int*) (object + 0x44) + 1) * 6] = mx[0];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 7] = mn[1];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 8] = mn[2];
	(*(float**) (object + 0x40))[(*(int*) (object + 0x44) + 2) * 6] = mn[0];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 13] = mx[1];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 14] = mn[2];
	(*(float**) (object + 0x40))[(*(int*) (object + 0x44) + 3) * 6] = mx[0];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 19] = mx[1];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 20] = mn[2];
	(*(float**) (object + 0x40))[(*(int*) (object + 0x44) + 4) * 6] = mn[0];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 25] = mn[1];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 26] = mx[2];
	(*(float**) (object + 0x40))[(*(int*) (object + 0x44) + 5) * 6] = mx[0];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 31] = mn[1];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 32] = mx[2];
	(*(float**) (object + 0x40))[(*(int*) (object + 0x44) + 6) * 6] = mn[0];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 37] = mx[1];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 38] = mx[2];
	(*(float**) (object + 0x40))[(*(int*) (object + 0x44) + 7) * 6] = mx[0];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 43] = mx[1];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 44] = mx[2];
	dx = mx[0] - mn[0];
	dy = mx[1] - mn[1];
	dz = mx[2] - mn[2];
	corners = *(float**) (object + 0x40) + *(int*) (object + 0x44) * 6;
	*(float*) (object + 0x1d8) = (float) sqrt(dz * dz + dy * dy + dx * dx);
	sx = sy = sz = 0.0f;
	for (i = 8, p = corners; i > 0; i--, p += 6) {
		sx += p[0];
		sy += p[1];
		sz += p[2];
	}
	*(float*) (object + 0x68) = sx * 0.125f;
	*(float*) (object + 0x6c) = sy * 0.125f;
	*(float*) (object + 0x70) = sz * 0.125f;
}
