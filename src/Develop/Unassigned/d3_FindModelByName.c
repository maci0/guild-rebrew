#include <string.h>

/* ADDRESS: GOLD 0x0044c5d0 */
char* __cdecl d3_FindModelByName(char* name)
{
	char* e;

	for (e = *(char**) 0xfc2ffc; e != (char*) 0xfc4a40; e = *(char**) (e + 0x1fc)) {
		if (_strnicmp(name, e, 0x3f) == 0) {
			return e;
		}
	}
	return 0;
}
