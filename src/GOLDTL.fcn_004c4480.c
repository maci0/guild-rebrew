#include "client_types.h"
extern cell10_fb5760 g_fb5760[0x8000];

/* ADDRESS: GOLD 0x004c3b10 */
/* ADDRESS: GOLDTL 0x004c4480 */

int __cdecl fcn_004c4480(int i)
{
	if (i >= 0 && i < 0x8000)
		return *(int*) &((unsigned char(*)[10])g_fb5760)[i][6];
	return 0;
}
