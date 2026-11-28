#include "Develop/DieGildeAddOn/game/ch_queue.h"

extern char* tp_ch_ActionQueue;

typedef char slot_size_must_be_404[(sizeof(CH_QUEUE_SLOT) == 0x194) ? 1 : -1];

/* ADDRESS: GOLDTL 0x0051fd30 */
/* ADDRESS: GOLDDE 0x00509000 */
CH_QUEUE_SLOT* __cdecl ch_GetQueueEntryByIndex(int index)
{
    if (index == -1)
        return 0;
    return &((CH_QUEUE_SLOT*)tp_ch_ActionQueue)[index];
}
