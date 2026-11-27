#include <string.h>
void __cdecl d3_InitGateNodeFlags(char* e)
{
	if (strstr(e, "gate")) {
		e[0x214] &= 0xbf;
		*(int*) (e + 0x224) = 1;
	} else {
		*(int*) (e + 0x224) = 0;
	}
}
