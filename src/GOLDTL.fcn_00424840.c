// FUNCTION: GOLDTL 0x424840
// SIZE: 39

#include <string.h>

char* __cdecl fcn_00424840(char* p, char* dst, int n)
{
	if (p != 0) {
		p = *(char**) (p + 0x3c);
		if (p != 0) {
			strncpy(dst, p, n);
		}
	}
	return p;
}
