// FUNCTION: GOLD 0x004ffc90
// SIZE: 43
// fcn_004ffc90 — sqrt((x1-x2)^2+(y1-y2)^2) * [0x5ee8e0].

#include <math.h>

double __cdecl fcn_004ffc90(double x1, double y1, double x2, double y2)
{
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) * *(double*) 0x5ee8e0;
}
