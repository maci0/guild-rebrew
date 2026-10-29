#include "g_10058a0.h"
extern IdSlot10058a0 g_10058a0[8];
extern IdSlot10058a0 g_10058a0[8];
// fcn_004bf3e0: first i with table[i].id != -1 && table[i].b == a
// (GOLDTL 0x10058a0 / GOLD 0xf812a0).

/* ADDRESS: GOLD 0x004bf3e0 */
/* ADDRESS: GOLDTL 0x004bfc40 */
int __cdecl fcn_004bf3e0(int a)
{
	int i;
	for (i = 0; i < 8; i++) {
		if (g_10058a0[i].id != -1 && g_10058a0[i].b == a) {
			return i;
		}
	}
	return -1;
}
unsigned char _dpad_1005820[128];
