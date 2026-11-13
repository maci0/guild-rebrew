#include <math.h>

/* Horizontal distance from a to the point held at b->member->pos. */
/* ADDRESS: GOLD 0x004ce1b0 */
float __cdecl fcn_004ce1b0(char* a, char* b)
{
	char* p;
	float dx;
	float dz;

	p = *(char**) (*(char**) (b + 0x184) + 0x34);
	dx = *(float*) (a + 0x4c) - *(float*) (p + 0x4c);
	dz = *(float*) (a + 0x54) - *(float*) (p + 0x54);
	return (float) sqrt(dx * dx + dz * dz);
}
