

#include "Develop/client_types.h"
typedef D2_ITEM_BUTTON Btn;
// SIZE 0x8

#include "Develop/Units/d2.v1/d2_win.h"








// SIZE 0x3cc

extern int d2_InventoryPanelWindowId;
extern int d2_ScreenHeight;
extern int g_1040494;
extern Win_1015f40 d2_Windows[0x60];
extern int d2_CurrentWindowId;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern D2_ITEM_BUTTON g_776c60[6];
extern int d2_DialogButtonAction;
extern int d2_CurrentElementId;
extern int g_14a92bc;
extern int io_RightButtonReleased;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern char s_6ac77c[];

int __cdecl d2_TutorialAllowsFlag(int);
void __cdecl d2_DispatchTutorialInput(int, int, int, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_OpenEntityQuickSlots(int, int, int, unsigned short, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_UpdateActiveItemSlots(void);

int __cdecl gm_LookupSpecialObject(int);
void __cdecl d2_SetFormVisibility(int, int);
void __cdecl d2_ConfirmUseObjekt(char*);
#include "Develop/Units/d2.v1/d2_gui.h"

int __cdecl d2_ShowModalMessageBox(int, int);
int __cdecl d2_GetControlValue(int);
void __cdecl d2_CloseInventoryPanel(void);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDDE 0x005a8a50 */
void __cdecl d2_ShowInventoryDialog(void)
{
	int dlg;
	int i;

	if (d2_InventoryPanelWindowId != -1) {
		return;
	}
	if (d2_TutorialAllowsFlag(0x1000) == 0) {
		return;
	}
	d2_DispatchTutorialInput(0x14, 0, 0, 0);
	dlg = d2_LoadForm(g_1040494 - 0x158, d2_ScreenHeight - 0x108, s_6ac77c);
	d2_SetForm(dlg, 0);
	*(int*) &((D2_WIN*)d2_Windows)[d2_CurrentWindowId].pad3a8[0] = 0x18;
	*(int*) &((D2_WIN*)d2_Windows)[d2_CurrentWindowId].pad3a8[4] = 0x18;
	*(int*) &((D2_WIN*)d2_Windows)[d2_CurrentWindowId].pad3a8[8] = 0x18;
	*(int*) &((D2_WIN*)d2_Windows)[d2_CurrentWindowId].pad3a8[12] = 0x18;
	d2_SetForm(dlg, 0);
	d2_SetOverlayAnimation(0, 0);
	d2_OpenEntityQuickSlots(d2_CurrentWindowId, 0, 0, gm_LocalPlayerSlot, 0x1f3b);
	if (main_RunFrameLoop((void*) d2_ShowInventoryDialog, 0x657c7) != 0) {
		do {
			d2_UpdateActiveItemSlots();
			if (d2_DialogButtonAction != -1 || CountDisplayCounters() != 0) {
				for (i = 0; i < 6; i++) {
					if (g_776c60[i].item != 0 && d2_CurrentElementId == g_776c60[i].btn) {
						if (gm_LookupSpecialObject(*(unsigned short*) g_776c60[i].item) != 0) {
							d2_SetFormVisibility(dlg, 0);
							d2_ConfirmUseObjekt(g_776c60[i].item);
							d2_SetElementValue(g_776c60[i].btn, 0, 0x3e7, 0);
							ResetDisplayCounters();
							d2_SetFormVisibility(dlg, 1);
						}
						else {
							d2_ShowModalMessageBox(g_14a92bc, 0);
						}
					}
				}
			}
			if (io_RightButtonReleased != 0) {
				if (CountDisplayCounters() != 0) {
					for (i = 0; i < 6; i++) {
						if (g_776c60[i].item != 0 && d2_GetControlValue(g_776c60[i].btn) != 0) {
							d2_SetElementValue(g_776c60[i].btn, 0, 0x3e7, 0);
						}
					}
					ResetDisplayCounters();
				}
				else {
					d2_DialogCloseRequested = 1;
				}
			}
		} while (main_RunFrameLoop((void*) d2_ShowInventoryDialog, 0x657c7) != 0);
	}
	d2_CloseInventoryPanel();
	d2_DestroyForm(dlg);
	d2_DispatchTutorialInput(0x14, 0, 1, 0);
}
