// FUNCTION: GOLD 0x004247e0
// fcn_004247e0 — memset 0x1460b00 (0x1a8*4) + zero 4 globals.

#include <string.h>

void __cdecl fcn_004247e0(void)
{
	memset((void*) 0x1460b00, 0, 0x1a8 * 4);
	*(int*) 0x633178 = 0;
	*(int*) 0x633174 = 0;
	*(int*) 0x633180 = 0;
	*(int*) 0x63317c = 0;
}
