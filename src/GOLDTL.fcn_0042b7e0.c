// FUNCTION: GOLD 0x42c480
// FUNCTION: GOLDTL 0x42b7e0

#include <string.h>

#pragma intrinsic(strlen)

void __cdecl fcn_0042b7e0(char* s)
{
	int n;

	n = (int) strlen(s) - 1;
	if (s[n] == ' ' && n > 0) {
		do {
			if (s[n] != ' ') {
				s[n + 1] = 0;
				return;
			}
			n--;
		} while (n > 0);
	}
}
