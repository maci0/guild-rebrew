


#include <string.h>

#pragma intrinsic(strlen)

void __cdecl fcn_0042e570(char* p)
{
	int n;

	if (p == 0) {
		return;
	}
	n = (int) strlen(p);
	if (n <= 0) {
		return;
	}
	do {
		if (*p == '/') {
			*p = '\\';
		}
		p++;
		n--;
	} while (n != 0);
}
