#include <string.h>


#include "Develop/DieGildeAddOn/game/ch_queue.h"

extern char* g_6b5c20;

CH_QUEUE_SLOT* __cdecl ch_GetFreeQueueEntry(void)
{
	int i;

	for (i = 0; i < 2000;) {
		if (((CH_QUEUE_SLOT*)g_6b5c20)[i++].belegt == 0) {
			break;
		}
	}
	if (i >= 2000) {
		return 0;
	}
	return &((CH_QUEUE_SLOT*)g_6b5c20)[i - 1];
}
