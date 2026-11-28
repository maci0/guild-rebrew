


extern char* d2_SelectedBuilding;
extern char* d3_FocusedEntityObject;
extern int g_7746d4;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char* gm_MarketEntity;
extern char* sv_SelectedBuilding;

void __cdecl d2_DestroySelectionPanel(void);
void __cdecl sv_ClearObjectSelection(void);
void __cdecl d2_SetFormVisibility(int, int);
int __cdecl gm_QueryEntities(int, int, int, int);
void __cdecl d2_DispatchTutorialInput(int, int, int, int);
void __cdecl d2_RunTradeInventoryPanel(int, int);

/* ADDRESS: GOLDDE 0x00588750 */
void __cdecl d2_OpenMarktstandPanel(int buildingArg, int queryTypeId)
{
	(*(int*)&d2_SelectedBuilding) = 0;
	d3_FocusedEntityObject = 0;
	d2_DestroySelectionPanel();
	sv_ClearObjectSelection();
	g_7746d4 = 1;
	if (g_6a25b8 != -1) {
		d2_SetFormVisibility(g_6a25b8, 0);
	}
	(*(int*)&sv_SelectedBuilding) = gm_QueryEntities(*(int*) (gm_MarketEntity + 0x5d), 1, 0, queryTypeId);
	if ((*(int*)&sv_SelectedBuilding) != 0) {
		d2_DispatchTutorialInput(0x17, (*(int*)&sv_SelectedBuilding), 0, queryTypeId);
		while ((*(int*)&sv_SelectedBuilding) != 0) {
			g_7746d4 = 1;
			d2_RunTradeInventoryPanel(buildingArg, 9);
		}
	}
	d2_DispatchTutorialInput(0x18, (*(int*)&sv_SelectedBuilding), 0, queryTypeId);
	d2_DispatchTutorialInput(0x17, (*(int*)&sv_SelectedBuilding), 1, queryTypeId);
	(*(int*)&sv_SelectedBuilding) = 0;
	if (g_6a25b8 != -1) {
		d2_SetFormVisibility(g_6a25b8, 1);
	}
}
