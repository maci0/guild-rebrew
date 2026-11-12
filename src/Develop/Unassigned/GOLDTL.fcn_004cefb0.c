#include <math.h>

/* ADDRESS: GOLDTL 0x004cefb0 */

/* Flat distance between a2's position and the position reached from a1. */
float __cdecl fcn_004cefb0(char* a1, char* a2)
{
	char* p;
	float a[2];
	float b[2];

	a[0] = *(float*) (a2 + 0x4c);
	a[1] = *(float*) (a2 + 0x54);
	p = *(char**) (*(char**) (a1 + 0x184) + 0x34);
	b[0] = *(float*) (p + 0x4c);
	b[1] = *(float*) (p + 0x54);
	a[0] -= b[0];
	return (float) sqrt((a[1] - b[1]) * (a[1] - b[1]) + a[0] * a[0]);
}
