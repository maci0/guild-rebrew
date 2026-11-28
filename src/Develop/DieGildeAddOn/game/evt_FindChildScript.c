


#include <string.h>

/* ADDRESS: GOLDDE 0x00420d10 */
char* __cdecl evt_FindChildScript(char* o, const char* name)
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
