#include "g_10058a0.h"

extern IdSlot10058a0 g_10058a0[8];
extern int g_6816d8;

int __cdecl fcn_004693b0(int, int);
void __cdecl fcn_00469470(int, int);

/* ADDRESS: GOLD 0x004bdae0 */
/* ADDRESS: GOLDTL 0x004be380 */

void __cdecl fcn_004be380(void)
{
	int i;

	for (i = 0; i < 8; i++) {
		if (g_10058a0[i].id != -1) {
			if (g_6816d8 == -1)
				g_6816d8 = fcn_004693b0(1, g_10058a0[i].id);
			else
				fcn_00469470(g_6816d8, g_10058a0[i].id);
		}
	}
}
