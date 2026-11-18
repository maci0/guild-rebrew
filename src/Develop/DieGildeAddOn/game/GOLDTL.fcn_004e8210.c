/* fcn_004e8210 — dispatch the fixed-argument job, -1 without a payload. */

#include "Develop/DieGildeAddOn/game/aemter.h"

/* ADDRESS: GOLD 0x004e6650 */
/* ADDRESS: GOLDTL 0x004e8210 */
int __cdecl fcn_004e8210(int a1, unsigned char* payload, int a3)
{
	if (payload == 0) {
		return -1;
	}
	return fcn_004e8240(a1, payload, 0, 1, a3);
}
