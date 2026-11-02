#include <string.h>
int __cdecl fcn_0040e610(char* s, char* p)
{
	if (strstr(s, p + 0x84) != 0) {
		((char**) p)[*(int*) (p + 0x80)] = s;
		(*(int*) (p + 0x80))++;
	}
	return *(int*) (p + 0x80) < 0x20;
}
