#include "Develop/DieGildeAddOn/game/ch_queue.h"

int __cdecl fcn_00404f60(char* task);

/* ADDRESS: GOLDTL 0x004079d0 */
void __cdecl fcn_004079d0(struct CH_ACTION* task)
{
    if (fcn_00404f60((char*) task) == -1)
        ch_RemoveQueueEntry((char*) task);
}
