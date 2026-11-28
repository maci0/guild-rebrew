#include "Develop/DieGildeAddOn/game/cutscene_clock.h"

/* ADDRESS: GOLDTL 0x004e4a60 */
/* ADDRESS: GOLDDE 0x004d1400 */
void __cdecl cut_UpdateClock(void)
{
    cut_ClockExpired = cut_CurrentTick > cut_ClockDeadline;
    cut_CurrentTick++;
}
