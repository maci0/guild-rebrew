

#include <math.h>

extern int d3_ActiveScene;

void __cdecl d3_GridPointToWorld(int, int, int, float*);

float __cdecl d3_CalcGridPointDistance(int a, int b, int c, int d)
{
	float pointA[4];
	float pointB[4];
	float dx;
	float dy;
	float dz;
	int h;

	h = *(int*) (((char*)d3_ActiveScene) + 0xb0);
	d3_GridPointToWorld(h, a, b, pointA);
	d3_GridPointToWorld(h, c, d, pointB);
	dx = pointA[0] - pointB[0];
	dy = pointA[1] - pointB[1];
	dz = pointA[2] - pointB[2];
	return (float) sqrt(dz * dz + dy * dy + dx * dx);
}
