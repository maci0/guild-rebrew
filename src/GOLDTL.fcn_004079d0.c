#include "Develop/DieGildeAddOn/game/ch_queue.h"

int __cdecl fcn_00404f60(char* task);

/* ADDRESS: GOLDTL 0x004079d0 */
void __cdecl fcn_004079d0(struct Task* task)
{
    if (fcn_00404f60((char*) task) == -1)
        fcn_004050c0((char*) task);
}
