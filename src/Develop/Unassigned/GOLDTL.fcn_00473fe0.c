extern int tp_d2_SelectedControl;
extern char* g_1015ea0;
extern int g_67d8e8;
extern int g_100f1d8;
extern int g_100f1e0;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x00473fe0 */
void __cdecl d2_ClearSelectedControl(void)
{
	if ((*(char**)&tp_d2_SelectedControl) != 0) {
		((D2_CONTROL_TL*) g_1015ea0)[*(int*) ((*(char**)&tp_d2_SelectedControl) + 0x134)].value_03c = 0;
		(*(char**)&tp_d2_SelectedControl) = 0;
		if (g_67d8e8 != -1) {
			g_67d8e8 = -1;
			d2_MouseBottomBoundary = g_100f1d8;
			d2_MouseTopBoundary = g_100f1e0;
		}
	}
}
