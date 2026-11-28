#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLDTL 0x0042a070 */
/* ADDRESS: GOLDDE 0x00424a00 */
void __cdecl evt_ResetCurrentContextId(void)
{
	evt_ActiveContextId = -1;
}
