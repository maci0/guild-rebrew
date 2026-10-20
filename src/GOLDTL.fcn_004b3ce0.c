#include "g_680bd0.h"

extern Entry680bd0 g_680bd0[48];

/* ADDRESS: GOLDTL 0x004b3ce0 */

int* __cdecl fcn_004b3ce0(int a0, int* a1)
{
	int* q;
	int p;
	int i;

	if (a1 == 0) {
		for (i = 0, p = (int) g_680bd0 + 4; p < (int) g_680bd0 + 0x544; p += 0x1c, i++) {
			if (*(int*) p == a0) {
				return (int*) ((int) g_680bd0 + i * 0x1c);
			}
		}
		return 0;
	}
	if (a1 < (int*) &g_680bd0[47]) {
		for (q = (int*) ((char*) a1 + 0x1c); q <= (int*) &g_680bd0[47]; q = (int*) ((char*) q + 0x1c)) {
			if (q[1] == a0) {
				return q;
			}
		}
	}
	return 0;
}
