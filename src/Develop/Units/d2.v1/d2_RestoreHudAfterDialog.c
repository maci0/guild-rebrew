#include "Develop/client_types.h"
extern int g_6a25b4;
#include "Develop/DieGildeAddOn/game/game_data.h"




void __cdecl d2_DestroyForm(int);

void __cdecl d2_SetFormVisibility(int, int);
void __cdecl d2_UpdateSelectionPanels(void);

/* ADDRESS: GOLDDE 0x005134e0 */
void __cdecl d2_RestoreHudAfterDialog(void)
{
	d2_DestroyForm(g_6a25b4);
	g_6a25b4 = -1;
	ResetDisplayCounters();
	if (g_6a25b8 != -1) {
		d2_SetFormVisibility(g_6a25b8, 1);
	}
	d2_UpdateSelectionPanels();
}
