#include "Develop/DieGildeAddOn/game/ch_queue.h"

extern char* g_6b5c20;

typedef char slot_size_must_be_404[(sizeof(CH_QUEUE_SLOT) == 0x194) ? 1 : -1];

/* ADDRESS: GOLDTL 0x0051fd30 */
CH_QUEUE_SLOT* __cdecl fcn_0051ad90(int index)
{
    if (index == -1)
        return 0;
    return &((CH_QUEUE_SLOT*)g_6b5c20)[index];
}
