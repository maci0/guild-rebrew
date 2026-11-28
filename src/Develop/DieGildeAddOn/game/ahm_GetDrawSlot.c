#include "Develop/DieGildeAddOn/game/alchemy_player_prototype.h"
extern ALCHEMY_DRAW_SLOT ahm_DrawSlots[3];
extern ALCHEMY_DRAW_SLOT ahm_DrawSlots[3];

/* ADDRESS: GOLD 0x004ec2d0 */
/* ADDRESS: GOLDTL 0x004ee060 */
char* __cdecl ahm_GetDrawSlot(int i)
{
	if (i < 0 || i >= 3) {
		return 0;
	}
	return (char*) ahm_DrawSlots + i * 24;
}
