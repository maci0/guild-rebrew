#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLDTL 0x0042a070 */
void __cdecl evt_ResetCurrentContextId(void)
{
	evt_ActiveContextId = -1;
}
