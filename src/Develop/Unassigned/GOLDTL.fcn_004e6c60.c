extern char cut_RandomSeed[];

#include <stdio.h>

void __cdecl fcn_004e6c60(int a1)
{
	char buf[0x40];

	*(int*) &cut_RandomSeed = a1;
	sprintf(buf, (char*) 0x68d6a8, a1);
}
