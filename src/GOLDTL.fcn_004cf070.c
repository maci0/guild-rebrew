// FUNCTION: GOLDTL 0x4cf070
// SIZE: 113

#include <math.h>

extern int g_67a370;

void __cdecl fcn_0045b920(int, int, int, float*);

float __cdecl fcn_004cf070(int a, int b, int c, int d)
{
	float v1[4];
	float v2[4];
	float dx;
	float dy;
	float dz;
	int h;

	h = *(int*) (((char*)g_67a370) + 0xb0);
	fcn_0045b920(h, a, b, v1);
	fcn_0045b920(h, c, d, v2);
	dx = v1[0] - v2[0];
	dy = v1[1] - v2[1];
	dz = v1[2] - v2[2];
	return (float) sqrt(dz * dz + dy * dy + dx * dx);
}
