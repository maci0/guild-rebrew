#include <math.h>

/* ADDRESS: GOLD 0x0044ce40 */
void __cdecl fcn_0044ce40(char* object)
{
	float radius;
	float length;
	float minx, miny, minz, maxx, maxy, maxz;
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
	minx = miny = minz = 1.0e10f;
	maxx = maxy = maxz = -1.0e10f;
	corners = *(float**) (object + 0x40);
	for (p = corners, i = n; i > 0; i--, p += 6) {
		if (!(minx < p[0])) minx = p[0];
		if (!(p[1] > miny)) miny = p[1];
		if (!(p[2] > minz)) minz = p[2];
		if (!(maxx > p[0])) maxx = p[0];
		if (!(p[1] < maxy)) maxy = p[1];
		if (!(maxz > p[2])) maxz = p[2];
	}
	corners[n * 6] = minx;
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 1] = miny;
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 2] = minz;
	(*(float**) (object + 0x40))[(*(int*) (object + 0x44) + 1) * 6] = maxx;
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 7] = miny;
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 8] = minz;
	(*(float**) (object + 0x40))[(*(int*) (object + 0x44) + 2) * 6] = minx;
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 13] = maxy;
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 14] = minz;
	(*(float**) (object + 0x40))[(*(int*) (object + 0x44) + 3) * 6] = maxx;
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 19] = maxy;
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 20] = minz;
	(*(float**) (object + 0x40))[(*(int*) (object + 0x44) + 4) * 6] = minx;
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 25] = miny;
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 26] = maxz;
	(*(float**) (object + 0x40))[(*(int*) (object + 0x44) + 5) * 6] = maxx;
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 31] = miny;
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 32] = maxz;
	(*(float**) (object + 0x40))[(*(int*) (object + 0x44) + 6) * 6] = minx;
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 37] = maxy;
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 38] = maxz;
	(*(float**) (object + 0x40))[(*(int*) (object + 0x44) + 7) * 6] = maxx;
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 43] = maxy;
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 44] = maxz;
	dx = maxx - minx;
	dy = maxy - miny;
	dz = maxz - minz;
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
