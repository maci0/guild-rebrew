#include "g_67a470.h"
/* ADDRESS: GOLDTL 0x0067a470 */
extern Named24 g_67a470[8];
/* ADDRESS: GOLD 0x005fb800 */
extern Named24 g_67a470[8];
/* ADDRESS: GOLD 0x0043e710 */
/* ADDRESS: GOLDTL 0x0043b550 */

char* __cdecl fcn_0043b550(int a1)
{
	int i;
	unsigned off;

	i = 0;
	for (off = 0; off < 0x120; off += 0x24, i++) {
		if (a1 == *(int*) ((char*) g_67a470 + 0x20 + off)) {
			return (char*) g_67a470 + i * 0x24;
		}
	}
	return (char*) g_67a470 + 0x124;
}
