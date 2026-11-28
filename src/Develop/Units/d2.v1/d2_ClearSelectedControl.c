extern int tp_d2_SelectedControl;
extern char* d2_Controls;
extern int g_67d8e8;
extern int g_100f1d8;
extern int g_100f1e0;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x00473fe0 */
/* ADDRESS: GOLDDE 0x00466ce0 */
void __cdecl d2_ClearSelectedControl(void)
{
	if ((*(char**)&tp_d2_SelectedControl) != 0) {
		((D2_CONTROL_TL*) d2_Controls)[*(int*) ((*(char**)&tp_d2_SelectedControl) + 0x134)].value_03c = 0;
		(*(char**)&tp_d2_SelectedControl) = 0;
		if (g_67d8e8 != -1) {
			g_67d8e8 = -1;
			d2_MouseBottomBoundary = g_100f1d8;
			d2_MouseTopBoundary = g_100f1e0;
		}
	}
}
