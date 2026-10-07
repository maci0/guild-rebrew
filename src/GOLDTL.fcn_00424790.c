// FUNCTION: GOLDTL 0x424790

#include <string.h>

char* __cdecl fcn_00424790(char* p, char* dst, int n)
{
	if (p != 0) {
		p = *(char**) (p + 0x104);
		if (p != 0) {
			strncpy(dst, p, n);
		}
	}
	return p;
}
