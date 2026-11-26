/* fcn_004e8210 — dispatch the fixed-argument job, -1 without a payload. */

#include "Develop/DieGildeAddOn/game/aemter.h"

/* ADDRESS: GOLD 0x004e6650 */
/* ADDRESS: GOLDTL 0x004e8210 */
int __cdecl amt_AssignOfficeHolder(int office_id, unsigned char* payload, int mode)
{
	if (payload == 0) {
		return -1;
	}
	return amt_SendOfficeCommand(office_id, payload, 0, 1, mode);
}
