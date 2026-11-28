#include "Develop/DieGildeAddOn/game/ch_queue.h"
extern char* tp_ch_ActionQueue;

/* ADDRESS: GOLDTL 0x00402b80 */
int __cdecl ch_CountOccupiedQueueSlots(void)
{
	CH_QUEUE_SLOT* base;
	int count;
	int i;

	base = (CH_QUEUE_SLOT*) tp_ch_ActionQueue;
	count = 0;
	for (i = 0; i < 2000; i++) {
		if ((base++)->belegt != 0) {
			count++;
		}
	}
	return count;
}
