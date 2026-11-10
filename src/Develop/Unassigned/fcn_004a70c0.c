#include "client_types.h"

extern Card_1007ce0 g_1007ce0[24];

/* ADDRESS: GOLDTL 0x004a70c0 */
int __cdecl fcn_004a70c0(int a1, int a2, Card_1007ce0* out)
{
	int idx;

	if (a1 <= 2 && a2 <= 4) {
		idx = *(int*) (*(int*) 0x1007cd4 + (a1 * 13 + a2) * 4 + 0xc);
		if (idx != -1) {
			*out = g_1007ce0[idx];
			return 1;
		}
	}
	return 0;
}
