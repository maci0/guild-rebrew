#include <string.h>
char __cdecl fcn_0052dd40(char* name, int* list)
{
	if (strstr(name, "sp_WIMPEL")) {
		list[list[0] + 1] = (int) name;
		list[0]++;
	}
	return list[0] < 0x20;
}
