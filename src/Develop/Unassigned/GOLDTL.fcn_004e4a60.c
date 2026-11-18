#include "Develop/DieGildeAddOn/game/cutscene_clock.h"

/* ADDRESS: GOLDTL 0x004e4a60 */
void __cdecl fcn_004e4a60(void)
{
    g_772f38 = cut_CurrentTick > g_772f34;
    cut_CurrentTick++;
}
