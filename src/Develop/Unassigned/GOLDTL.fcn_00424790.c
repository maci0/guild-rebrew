

#include <string.h>

char* __cdecl sbs_GetNextSample(char* p, char* dst, int n)
{
	if (p != 0) {
		p = *(char**) (p + 0x104);
		if (p != 0) {
			strncpy(dst, p, n);
		}
	}
	return p;
}
