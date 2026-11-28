#include <string.h>

/* ADDRESS: GOLDTL 0x0042b790 */
char* __cdecl txt_SkipLeadingSpaces(char* s)
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
