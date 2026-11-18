

#include <math.h>

extern int g_67a370;

void __cdecl fcn_0045b920(int, int, int, float*);

float __cdecl fcn_004cf070(int a, int b, int c, int d)
{
	float pointA[4];
	float pointB[4];
	float dx;
	float dy;
	float dz;
	int h;

	h = *(int*) (((char*)g_67a370) + 0xb0);
	fcn_0045b920(h, a, b, pointA);
	fcn_0045b920(h, c, d, pointB);
	dx = pointA[0] - pointB[0];
	dy = pointA[1] - pointB[1];
	dz = pointA[2] - pointB[2];
	return (float) sqrt(dz * dz + dy * dy + dx * dx);
}
