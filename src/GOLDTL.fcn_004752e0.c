#include <string.h>

#include "g_100f200.h"

extern int g_100f804;
extern Slot100f200 g_100f200[];
/* ADDRESS: GOLDTL 0x004752e0 */

void __cdecl fcn_004752e0(int i)
{
	if (g_100f804 >= 1 && i >= 0) {
		memset(&g_100f200[i], 0, sizeof(g_100f200[i]));
		g_100f804--;
	}
}
