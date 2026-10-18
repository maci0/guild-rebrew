#include <string.h>

/* ADDRESS: GOLD 0x004d2650 */
char __cdecl fcn_004d2650(char* object, void* context)
{
	int count;

	if (strncmp(object, "sp_CONQUER", 10) == 0) {
		count = *(int*) 0x6f0d60;
		((char**) 0x930380)[count] = object;
		*(int*) 0x6f0d60 = count + 1;
	}
	return 1;
}
