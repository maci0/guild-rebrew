#include <string.h>

#include "client_types.h"
extern Anim_100e7a0 g_100e7a0[0x30];

/* ADDRESS: GOLDTL 0x0047a2b0 */

void __cdecl fcn_0047a2b0(int i)
{
	memset(((int(*)[5])g_100e7a0)[i], 0, sizeof(((int(*)[5])g_100e7a0)[i]));
}
