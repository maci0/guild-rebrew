#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d2_ResetQuadDeviceState(void);


/* ADDRESS: GOLDTL 0x0047cdf0 */
/* ADDRESS: GOLDDE 0x0046bdc0 */
void __cdecl d2_ResetDrawState(void)
{
	d2_DrawDepthIndex = 0;
	d2_ResetQuadDeviceState();
}
