extern char cut_RandomSeed[];

#include <stdio.h>

/* ADDRESS: GOLDDE 0x004d3480 */
void __cdecl cut_SetRandSeed(int seed)
{
	char buf[0x40];

	*(int*) &cut_RandomSeed = seed;
	sprintf(buf, "cut_randseed: %i", seed);
}
