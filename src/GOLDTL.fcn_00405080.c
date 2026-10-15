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

/* ADDRESS: GOLDTL 0x004050c0 */
/* ADDRESS: GOLD 0x004047a0 */
int __cdecl fcn_004050c0(char* task)
{
    char* next;
    char* previous;
    char* owner;

    if (task == 0) {
        return 0;
    }
    next = *(char**) (task + 0x28);
    if (next == 0) {
        owner = *(char**) (task + 0x14);
        if (owner != 0 && task == *(char**) (owner + 0x128)) {
            *(char**) (owner + 0x128) = next;
            memset(task, 0, 0x194);
            return 1;
        }
    }
    previous = *(char**) (task + 0x24);
    if (previous != 0) {
        *(char**) (previous + 0x28) = next;
    }
    next = *(char**) (task + 0x28);
    if (next != 0) {
        *(char**) (next + 0x24) = previous;
    }
    if (previous == 0) {
        owner = *(char**) (task + 0x14);
        if (owner != 0) {
            *(char**) (owner + 0x128) = next;
        }
    }
    memset(task, 0, 0x194);
    return 1;
}
