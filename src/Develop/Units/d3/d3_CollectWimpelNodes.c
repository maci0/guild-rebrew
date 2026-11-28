#include <string.h>
/* ADDRESS: GOLDDE 0x005166d0 */
char __cdecl d3_CollectWimpelNodes(char* name, int* list)
{
	if (strstr(name, "sp_WIMPEL")) {
		list[list[0] + 1] = (int) name;
		list[0]++;
	}
	return list[0] < 0x20;
}
