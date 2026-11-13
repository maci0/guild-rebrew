#include <math.h>

/* ADDRESS: GOLDTL 0x004cefb0 */

/* Flat distance between a2's position and the position reached from a1. */
float __cdecl fcn_004cefb0(char* a1, char* a2)
{
	char* p;
	float a[2];
	struct { float z, x; } b;

	a[0] = *(float*) (a2 + 0x4c);
	a[1] = *(float*) (a2 + 0x54);
	p = *(char**) (*(char**) (a1 + 0x184) + 0x34);
	b.x = *(float*) (p + 0x4c);
	b.z = *(float*) (p + 0x54);
	a[0] -= b.x;
	return (float) sqrt((a[1] - b.z) * (a[1] - b.z) + a[0] * a[0]);
}
