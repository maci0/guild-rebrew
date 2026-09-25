// FUNCTION: GOLDTL 0x00426240
// SIZE: 112

#include <string.h>

char* __cdecl fcn_00426240(char* o, const char* name)
{
	int i;
	char** p;

	i = 0;
	for (p = (char**) (o + 0xc3c); i < 8; i++, p++) {
		if (*p != 0 && strcmp(*p, name) == 0) {
			return ((char**) (o + 0xc3c))[i];
		}
	}
	return 0;
}
