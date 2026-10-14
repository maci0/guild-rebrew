

#include <string.h>

extern int g_6b7d6c;

int __cdecl fcn_00423de0(char* s)
{
	int r = 0;

	if (*(char**) 0x6b7d68 != 0) {
		strncpy(*(char**) 0x6b7d68, s, 0x32);
		g_6b7d6c++;
	} else {
		r = -1;
	}
	return r;
}
