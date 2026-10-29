#include "g_680bd0.h"
extern Entry680bd0 g_680bd0[48];
extern Entry680bd0 g_680bd0[48];

/* ADDRESS: GOLD 0x004b3ae0 */
/* ADDRESS: GOLDTL 0x004b3c50 */
char* __cdecl fcn_004b3c50(int a1)
{
	int i;
	int p;

	for (i = 0, p = (int) g_680bd0; p < (int) g_680bd0 + 0x540; p += 0x1c, i++) {
		if (*(int*) p == a1) {
			return (char*) ((int) g_680bd0 + i * 0x1c);
		}
	}
	return 0;
}
