

#include "Develop/DieGildeAddOn/game/entity_record.h"








#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char g_773d75;
extern char* g_7746cc;
extern int d2_CurrentWindowId;
extern int g_100f1dc;
extern int g_14ce8e0;
#include "client_dialog_state.h"
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
int __cdecl fcn_0050b750(int, char);
void __cdecl cm_RequestMoveCredits(int, int, char, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
void __cdecl d3_EndCameraAndUiMode(void);

void __cdecl d2_RunWeinkellerDialog(void)
{
	int sl;
	int dlg;
	int have;
	int stock;
	int max;
	int v;

	dlg = d2_LoadForm(0, 0, s_6aa830);
	have = gm_AccumulateTyped2(((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970]));
	stock = gm_SumContainerCredits(*(int*) (g_7746cc + 0x14));
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1a4c);
	d2_SetForm(dlg, 2);
	sl = d2_GetWindowListItem(dlg, 2, io_AppendText(0x1a4d, g_773d75));
	max = gm_AmountToUnits(stock, g_773d75) + gm_AmountToUnits(have, g_773d75) > gm_AmountToUnits(stock, g_773d75) ?
	      gm_AmountToUnits(stock, g_773d75) + gm_AmountToUnits(have, g_773d75) : gm_AmountToUnits(stock, g_773d75);
	d2_SetElementValue(sl, 0, max, gm_AmountToUnits(stock, g_773d75));
	d2_SetOverlayAnimation(0, 0);
	if (main_RunFrameLoop((void*) d2_RunWeinkellerDialog, 0x677c7) != 0) {
		do {
			if (g_14ce8e0 != 0 || g_100f1dc == 1) {
				g_774654 = 1;
			}
			if (g_100f1dc == 2) {
				v = fcn_0050b750(d2_GetControlValue(sl), g_773d75);
				if (stock < v) {
					cm_RequestMoveCredits(*(int*) (g_7746cc + 2), ((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970].entity_id, g_773d75, v - stock);
				}
				else {
					cm_RequestMoveCredits(((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970].entity_id, *(int*) (g_7746cc + 2), g_773d75, stock - v);
				}
				g_774654 = 1;
			}
		} while (main_RunFrameLoop((void*) d2_RunWeinkellerDialog, 0x677c7) != 0);
	}
	if (dlg != 0) {
		d2_DestroyForm(dlg);
	}
	d3_EndCameraAndUiMode();
}
