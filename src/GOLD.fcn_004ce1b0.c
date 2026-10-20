#include <math.h>

/* ADDRESS: GOLD 0x004ce1b0 */

/* Flat distance between a2's position and the position reached from a1. */
float __cdecl fcn_004ce1b0(char* a1, char* a2)
{
	char* p;
	float dx;
	float dy;

	p = *(char**) (*(char**) (a1 + 0x184) + 0x34);
	dx = *(float*) (a2 + 0x4c) - *(float*) (p + 0x4c);
	dy = *(float*) (a2 + 0x54) - *(float*) (p + 0x54);
	return (float) sqrt(dx * dx + dy * dy);
}
