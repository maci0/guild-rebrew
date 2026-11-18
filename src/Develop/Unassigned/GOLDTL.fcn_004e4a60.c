#include "Develop/DieGildeAddOn/game/cutscene_clock.h"

/* ADDRESS: GOLDTL 0x004e4a60 */
void __cdecl fcn_004e4a60(void)
{
    cut_ClockExpired = cut_CurrentTick > cut_ClockDeadline;
    cut_CurrentTick++;
}
