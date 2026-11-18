/* fcn_004d85c0 — tail-call the handler with the record's field. */

void* __cdecl gm_LookupEntityRecordIn32SlotTable(int);
#include "Develop/DieGildeAddOn/game/ch_queue.h"

/* ADDRESS: GOLDTL 0x004d85c0 */
void __cdecl fcn_004d85c0(int* request)
{
	void* record;

	if (request[1] == 0) {
		return;
	}
	if (request[0] == -1) {
		return;
	}
	record = gm_LookupEntityRecordIn32SlotTable(request[0]);
	if (record == 0) {
		return;
	}
	ch_CancelActionQueue((char*) *(int*) ((char*) record + 0x184));
}
