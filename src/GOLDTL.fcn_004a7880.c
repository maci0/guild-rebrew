#include "client_types.h"
typedef Card_1007ce0 Card;
// SIZE 0x10

extern Card_1007ce0 g_1007ce0[24];

extern char* g_1007cd4;

unsigned short __cdecl gm_RandomMod(int n);

/* ADDRESS: GOLD 0x004a7760 */
/* ADDRESS: GOLDTL 0x004a7880 */
int __cdecl fcn_004a7880(int owner)
{
	int i;

	if (!g_1007cd4[0xb4]) {
		return -1;
	}
	if ((unsigned char) g_1007cd4[0xb4] > 10) {
		do {
			i = gm_RandomMod(0x18);
		} while (g_1007ce0[i].count != 3);
	} else {
		for (i = 0; i < 24; i++) {
			if (g_1007ce0[i].count == 3) {
				break;
			}
		}
	}
	g_1007ce0[i].count = owner;
	g_1007cd4[0xb4]--;
	return i;
}
