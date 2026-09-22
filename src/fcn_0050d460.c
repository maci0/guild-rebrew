// FUNCTION: GOLD 0x0050d460
// SIZE: 37
// fcn_0050d460 — fill 0x76faa0 (0x2cc B) + 0x76fa60 (0x24 B + word) with -1.

#include <string.h>

void __cdecl fcn_0050d460(void)
{
	memset((void*) 0x76faa0, 0xff, 0x2cc);
	memset((void*) 0x76fa60, 0xff, 0x24);
	*(short*) 0x76fa84 = 0xffff;
}
