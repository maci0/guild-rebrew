// FUNCTION: GOLDTL 0x4226b0
// SIZE: 73

#include <string.h>

void __cdecl fcn_004226b0(char* s)
{
	if (s != 0) {
		strcpy((char*) 0x6b7d88, s);
		if (s[strlen(s) - 1] != '\\') {
			strcat((char*) 0x6b7d88, "\\");
		}
	}
}
