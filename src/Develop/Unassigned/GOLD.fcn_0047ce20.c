#include <string.h>

/* ADDRESS: GOLD 0x0047ce20 */
void __cdecl fcn_0047ce20(int index)
{
	/* 0x11-byte records at 0xf8a520 (DATA TODO: no Gold name yet). */
	memset((char*) 0xf8a520 + index * 0x11, 0, 0x11);
}
