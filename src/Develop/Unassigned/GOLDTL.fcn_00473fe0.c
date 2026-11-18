extern int tp_d2_SelectedControl;
extern char* g_1015ea0;
extern int g_67d8e8;
extern int g_100f1d8;
extern int g_100f1e0;
#include "Develop/DieGildeAddOn/game/game_data.h"

/* ADDRESS: GOLDTL 0x00473fe0 */
void __cdecl fcn_00473fe0(void)
{
	if ((*(char**)&tp_d2_SelectedControl) != 0) {
		((int*)g_1015ea0)[*(int*) ((*(char**)&tp_d2_SelectedControl) + 0x134) * 189 + 15] = 0;
		(*(char**)&tp_d2_SelectedControl) = 0;
		if (g_67d8e8 != -1) {
			g_67d8e8 = -1;
			d2_MouseBottomBoundary = g_100f1d8;
			d2_MouseTopBoundary = g_100f1e0;
		}
	}
}
