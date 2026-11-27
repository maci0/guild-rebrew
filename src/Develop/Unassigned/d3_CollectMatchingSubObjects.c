#include <string.h>
int __cdecl d3_CollectMatchingSubObjects(char* name, char* query)
{
	if (strstr(name, query + 0x84) != 0) {
		((char**) query)[*(int*) (query + 0x80)] = name;
		(*(int*) (query + 0x80))++;
	}
	return *(int*) (query + 0x80) < 0x20;
}
