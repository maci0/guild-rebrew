#include <math.h>

/* Horizontal distance from the point a to the position held at b->member->pos. */
/* ADDRESS: GOLD 0x004ce1b0 */
float __cdecl fcn_004ce1b0(char* b, char* a)
{
	char* p;
	float dx;
	float dz;

	p = *(char**) (*(char**) (b + 0x184) + 0x34);
	dx = *(float*) (a + 0x4c) - *(float*) (p + 0x4c);
	dz = *(float*) (a + 0x54) - *(float*) (p + 0x54);
	return (float) sqrt(dx * dx + dz * dz);
}
