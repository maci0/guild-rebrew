extern float g_10529d8;
extern float g_10529c4;
extern float g_10529d4;
extern float g_1043288;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d2_ScreenHeight;
extern int g_1040494;


/* ADDRESS: GOLDTL 0x00537320 */
/* ADDRESS: GOLDDE 0x0051ecd0 */
void __cdecl d2_UpdateViewportCenter(int flags)
{
	if (flags & 0x40) {
		if (flags & 0x100) {
			d2_CenterX = (int) (g_10529d8 * 0.5f + g_10529c4 - d2_UiScale * 6.0f);
			d2_DialogCenterY = (int) (g_10529d4 * 0.5f + d2_UiScale * 10.0f + g_1043288);
		} else {
			d2_CenterX = (int) (g_10529d8 * 0.5f + g_10529c4);
			d2_DialogCenterY = (int) (g_10529d4 * 0.5f + g_1043288);
		}
	} else {
		d2_CenterX = g_1040494 >> 1;
		d2_DialogCenterY = d2_ScreenHeight >> 1;
	}
}
