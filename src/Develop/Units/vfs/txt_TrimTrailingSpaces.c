


#include <string.h>

#pragma intrinsic(strlen)

/* ADDRESS: GOLDDE 0x00425770 */
void __cdecl txt_TrimTrailingSpaces(char* s)
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
