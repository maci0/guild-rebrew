#include <string.h>

// FUNCTION: GOLDTL 0x42b790
// SIZE: 72
char* __cdecl fcn_0042b790(char* s)
{
	unsigned int i;

	for (i = 0; i < strlen(s);) {
		if (s[i++] != ' ') {
			break;
		}
	}
	if (i == strlen(s)) {
		return 0;
	}
	return s + i - 1;
}
