#include "client_types.h"
extern Slot170_7731b8 g_7731b8[8];
extern Slot170_7731b8 g_7731b8[8];

/* ADDRESS: GOLD 0x004eedd0 */
/* ADDRESS: GOLDTL 0x004f0c90 */
int __cdecl fcn_004f0c90(int a1)
{
	int i;
	int a;

	i = 0;
	for (a = (int) g_7731b8; a < (int) g_7731b8 + 0xb80; a += 0x170, i++) {
		if (*(int*) a == a1) {
			return (int) ((int) g_7731b8 + i * 368);
		}
	}
	return 0;
}
