#include "Develop/DieGildeAddOn/game/ch_queue.h"

int __cdecl ch_FinishAnimation(char* task);

/* ADDRESS: GOLDTL 0x004079d0 */
void __cdecl ch_ExecFinishAnimation(struct CH_ACTION* task)
{
    if (ch_FinishAnimation((char*) task) == -1)
        ch_RemoveQueueEntry((char*) task);
}
