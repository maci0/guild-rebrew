#include "g_688118.h"
/* ADDRESS: GOLDTL 0x00688118 */
extern IdGroup g_688118[];
/* ADDRESS: GOLD 0x006094b0 */
extern IdGroup g_688118[];
/* ADDRESS: GOLD 0x004c1f90 */
/* ADDRESS: GOLDTL 0x004c27f0 */

int __cdecl fcn_004c27f0(void)
{
	int i;
	int v;
	char* p;

	i = 0;
	p = (char*) g_688118;
	do {
		if (p[0x112] != 0) {
			return i;
		}
		v = *(int*) p;
		i++;
		p += 0x114;
	} while (v != 0);
	return -1;
}
