

#include <string.h>

#pragma intrinsic(strlen, strcpy, strcat)

char* __cdecl fcn_00423a50(int);

int __cdecl fcn_00423f60(int a1, char* a2)
{
	char* dest;

	dest = fcn_00423a50(a1);
	if (dest != 0) {
		strcpy(dest, a2);
		return 0;
	}
	return -1;
}
