

#include <string.h>

void __cdecl d2_ShowStatusBanner(char* a)
{
	strcpy((char*) 0x7e5fc0, a);
	*(int*) 0x6a251c = *(int*) 0x6b7fac;
}
