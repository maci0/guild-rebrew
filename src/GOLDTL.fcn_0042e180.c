#include <string.h>

/* ADDRESS: GOLDTL 0x0042e180 */
void __cdecl fcn_0042e180(void)
{
	int n;

	if (*(unsigned int*) 0x6b7fd0 != 0 && *(unsigned int*) 0x6b7fd0 > *(unsigned int*) 0x6b7fd8) {
		n = 0x30;
		*(unsigned int*) 0x6b7fd0 -= 0x84;
		memset((char*) *(unsigned int*) 0x6b7fd0 + 0xe, 0, n);
		memset((char*) *(unsigned int*) 0x6b7fd0 + 0x3e, 0, n);
		*(unsigned int*) (*(unsigned int*) 0x6b7fd0 + 0x70) = 0;
	}
	else {
		__asm { int 3 }
	}
}
