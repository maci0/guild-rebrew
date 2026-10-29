

#include <string.h>

char* __cdecl fcn_00423a50(char* s)
{
	char* g;
	char* p;

	p = 0;
	g = *(char**) 0x6b7d68;
	if (g != 0) {
		for (p = *(char**) (g + 0x38); p != 0; p = *(char**) (p + 0x104)) {
			if (strcmp(p, s) == 0) {
				break;
			}
		}
	}
	return p;
}
