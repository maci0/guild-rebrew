// FUNCTION: GOLD 0x004d8b30
// fcn_004d8b30 — zeroes the 0x40-byte table at 0x92ca80.

#include <string.h>

void __cdecl fcn_004d8b30(void)
{
	memset((void*) 0x92ca80, 0, 0x40);
}
