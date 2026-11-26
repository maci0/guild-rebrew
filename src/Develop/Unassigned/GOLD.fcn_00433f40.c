#include <string.h>

/* ADDRESS: GOLD 0x00433f40 */
char* __cdecl d3_FindAnimByName(const char* name)
{
	char* node;

	node = *(char**) 0xfc26e0;
	while (node != (char*) 0xfe7440) {
		if (stricmp(name, node) == 0) {
			return node;
		}
		node = *(char**) (node + 0x160);
	}
	return 0;
}
