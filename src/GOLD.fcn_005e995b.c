
// fcn_005e995b — memset 0x14eac20 (0x100) + zero 3 globals + 3 stosd at 0x14eab10.

#include <string.h>

void __cdecl fcn_005e995b(void)
{
	memset((void*) 0x14eac20, 0, 0x100);
	memset((void*) 0x14eab10, 0, 0xc);
	*(int*) 0x14eab00 = 0;
	*(int*) 0x14eab1c = 0;
	*(int*) 0x14ead24 = 0;
}
