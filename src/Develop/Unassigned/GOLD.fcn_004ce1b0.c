#include <math.h>

/* Horizontal distance from the point a to the position held at b->member->pos. */
/* ADDRESS: GOLD 0x004ce1b0 */
float __cdecl gm_GetCharacterDistFromTarget(char* b, char* a)
{
	char* p;
	float pos_a[2];
	struct { float z, x; } pos_b;

	pos_a[0] = *(float*) (a + 0x4c);
	pos_a[1] = *(float*) (a + 0x54);
	p = *(char**) (*(char**) (b + 0x184) + 0x34);
	pos_b.x = *(float*) (p + 0x4c);
	pos_b.z = *(float*) (p + 0x54);
	pos_a[0] -= pos_b.x;
	return (float) sqrt((pos_a[1] - pos_b.z) * (pos_a[1] - pos_b.z) + pos_a[0] * pos_a[0]);
}
