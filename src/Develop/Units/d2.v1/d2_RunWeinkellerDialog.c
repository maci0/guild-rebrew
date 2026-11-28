

#include "Develop/DieGildeAddOn/game/entity_record.h"








#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char gm_ActiveTownIndex;
extern char* sv_SelectedBuilding;
extern int d2_CurrentWindowId;
extern int d2_DialogButtonAction;
extern int io_RightButtonReleased;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern char s_6aa830[];

int __cdecl d2_LoadForm(int, int, char*);
int __cdecl gm_AccumulateTyped2(ENTITY_RECORD*);
int __cdecl gm_SumContainerCredits(int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl gm_AmountToUnits(int, char);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl d2_GetControlValue(int);
int __cdecl gm_ConvertUnitsToAmount(int, char);
void __cdecl cm_RequestMoveCredits(int, int, char, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
void __cdecl d3_EndCameraAndUiMode(void);

/* ADDRESS: GOLDDE 0x00588b20 */
void __cdecl d2_RunWeinkellerDialog(void)
{
	int sl;
	int dlg;
	int have;
	int stock;
	int max;
	int v;

	dlg = d2_LoadForm(0, 0, s_6aa830);
	have = gm_AccumulateTyped2(((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot]));
	stock = gm_SumContainerCredits(*(int*) (sv_SelectedBuilding + 0x14));
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1a4c);
	d2_SetForm(dlg, 2);
	sl = d2_GetWindowListItem(dlg, 2, io_AppendText(0x1a4d, gm_ActiveTownIndex));
	max = gm_AmountToUnits(stock, gm_ActiveTownIndex) + gm_AmountToUnits(have, gm_ActiveTownIndex) > gm_AmountToUnits(stock, gm_ActiveTownIndex) ?
	      gm_AmountToUnits(stock, gm_ActiveTownIndex) + gm_AmountToUnits(have, gm_ActiveTownIndex) : gm_AmountToUnits(stock, gm_ActiveTownIndex);
	d2_SetElementValue(sl, 0, max, gm_AmountToUnits(stock, gm_ActiveTownIndex));
	d2_SetOverlayAnimation(0, 0);
	if (main_RunFrameLoop((void*) d2_RunWeinkellerDialog, 0x677c7) != 0) {
		do {
			if (io_RightButtonReleased != 0 || d2_DialogButtonAction == 1) {
				d2_DialogCloseRequested = 1;
			}
			if (d2_DialogButtonAction == 2) {
				v = gm_ConvertUnitsToAmount(d2_GetControlValue(sl), gm_ActiveTownIndex);
				if (stock < v) {
					cm_RequestMoveCredits(*(int*) (sv_SelectedBuilding + 2), ((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id, gm_ActiveTownIndex, v - stock);
				}
				else {
					cm_RequestMoveCredits(((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id, *(int*) (sv_SelectedBuilding + 2), gm_ActiveTownIndex, stock - v);
				}
				d2_DialogCloseRequested = 1;
			}
		} while (main_RunFrameLoop((void*) d2_RunWeinkellerDialog, 0x677c7) != 0);
	}
	if (dlg != 0) {
		d2_DestroyForm(dlg);
	}
	d3_EndCameraAndUiMode();
}
