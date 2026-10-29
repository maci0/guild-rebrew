#include <math.h>

/* ADDRESS: GOLDTL 0x004cefb0 */

/* Flat distance between a2's position and the position reached from a1. */
float __cdecl fcn_004cefb0(char* a1, char* a2)
{
	char* p;
	float ax;
	float ay;
	float px;
	float py;

	ax = *(float*) (a2 + 0x4c);
	ay = *(float*) (a2 + 0x54);
	p = *(char**) (*(char**) (a1 + 0x184) + 0x34);
	px = *(float*) (p + 0x4c);
	py = *(float*) (p + 0x54);
	return (float) sqrt((ax - px) * (ax - px) + (ay - py) * (ay - py));
}
