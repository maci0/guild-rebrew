#include "Develop/DieGildeAddOn/game/ch_queue.h"
extern char* g_6b5c20;

/* ADDRESS: GOLDTL 0x00402b80 */
int __cdecl fcn_00402b80(void)
{
	CH_QUEUE_SLOT* base;
	int count;
	int i;

	base = (CH_QUEUE_SLOT*) g_6b5c20;
	count = 0;
	for (i = 0; i < 2000; i++) {
		if ((base++)->belegt != 0) {
			count++;
		}
	}
	return count;
}
