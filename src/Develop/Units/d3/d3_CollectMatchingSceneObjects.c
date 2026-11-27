#include <string.h>
int __cdecl d3_CollectMatchingSceneObjects(char* name, int* list)
{
	if (strstr(name, (char*) list + 0x804)) {
		list[list[0] + 1] = (int) name;
		list[0]++;
	}
	return list[0] < 0x200;
}
