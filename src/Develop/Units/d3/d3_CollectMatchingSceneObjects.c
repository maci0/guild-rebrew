#include <string.h>
/* ADDRESS: GOLDDE 0x004fe8a0 */
int __cdecl d3_CollectMatchingSceneObjects(char* name, int* list)
{
	if (strstr(name, (char*) list + 0x804)) {
		list[list[0] + 1] = (int) name;
		list[0]++;
	}
	return list[0] < 0x200;
}
