extern char cut_RandomSeed[];

#include <stdio.h>

void __cdecl cut_SetRandSeed(int seed)
{
	char buf[0x40];

	*(int*) &cut_RandomSeed = seed;
	sprintf(buf, (char*) 0x68d6a8, seed);
}
