#include <string.h>
int __cdecl fcn_00411b70(void*);

char __cdecl fcn_0040e4c0(void* a, void* b)
{
	if (strstr(a, b) != 0) {
		fcn_00411b70(a);
	}
	return 1;
}
