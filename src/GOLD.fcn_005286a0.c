#include <string.h>

/* ADDRESS: GOLD 0x005286a0 */
char __cdecl fcn_005286a0(char* name, int* list)
{
	if (strstr(name, "sp_WIMPEL")) {
		list[list[0] + 1] = (int) name;
		list[0]++;
	}
	return list[0] < 0x20;
}
