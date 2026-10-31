#include <stdlib.h>
#include <string.h>

void __cdecl fcn_0044ecc0(int a1, char* a2)
{
	char* p;

	p = strtok(0, (const char*) 0x5ebb58);
	*(int*) (a2 + 4) = atoi(p);
}
