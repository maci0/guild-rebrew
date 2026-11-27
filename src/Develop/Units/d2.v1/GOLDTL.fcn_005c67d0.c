

#include "client_types.h"
typedef D2_ITEM_BUTTON Btn;
// SIZE 0x8

#include "Develop/Units/d2.v1/d2_win.h"








// SIZE 0x3cc

extern int g_6abb00;
extern int d2_ScreenHeight;
extern int g_1040494;
extern Win_1015f40 g_1015f40[0x60];
extern int d2_CurrentWindowId;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern D2_ITEM_BUTTON g_776c60[6];
extern int g_100f1dc;
extern int d2_CurrentElementId;
extern int g_14a92bc;
extern int g_14ce8e0;
#include "client_dialog_state.h"
extern char s_6ac77c[];

int __cdecl d2_TutorialAllowsFlag(int);
void __cdecl fcn_0057e880(int, int, int, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_005c5da0(int, int, int, unsigned short, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_UpdateActiveItemSlots(void);

int __cdecl gm_LookupSpecialObject(int);
void __cdecl d2_SetFormVisibility(int, int);
void __cdecl d2_ConfirmUseObjekt(char*);
#include "Develop/Units/d2.v1/d2_gui.h"

int __cdecl fcn_00526120(int, int);
int __cdecl d2_GetControlValue(int);
void __cdecl d2_CloseInventoryPanel(void);
void __cdecl d2_DestroyForm(int);

void __cdecl d2_ShowInventoryDialog(void)
{
	int dlg;
	int i;

	if (g_6abb00 != -1) {
		return;
	}
	if (d2_TutorialAllowsFlag(0x1000) == 0) {
		return;
	}
	fcn_0057e880(0x14, 0, 0, 0);
	dlg = d2_LoadForm(g_1040494 - 0x158, d2_ScreenHeight - 0x108, s_6ac77c);
	d2_SetForm(dlg, 0);
	*(int*) &((D2_WIN*)g_1015f40)[d2_CurrentWindowId].pad3a8[0] = 0x18;
	*(int*) &((D2_WIN*)g_1015f40)[d2_CurrentWindowId].pad3a8[4] = 0x18;
	*(int*) &((D2_WIN*)g_1015f40)[d2_CurrentWindowId].pad3a8[8] = 0x18;
	*(int*) &((D2_WIN*)g_1015f40)[d2_CurrentWindowId].pad3a8[12] = 0x18;
	d2_SetForm(dlg, 0);
	d2_SetOverlayAnimation(0, 0);
	fcn_005c5da0(d2_CurrentWindowId, 0, 0, g_774970, 0x1f3b);
	if (main_RunFrameLoop((void*) d2_ShowInventoryDialog, 0x657c7) != 0) {
		do {
			d2_UpdateActiveItemSlots();
			if (g_100f1dc != -1 || CountDisplayCounters() != 0) {
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
							fcn_00526120(g_14a92bc, 0);
						}
					}
				}
			}
			if (g_14ce8e0 != 0) {
				if (CountDisplayCounters() != 0) {
					for (i = 0; i < 6; i++) {
						if (g_776c60[i].item != 0 && d2_GetControlValue(g_776c60[i].btn) != 0) {
							d2_SetElementValue(g_776c60[i].btn, 0, 0x3e7, 0);
						}
					}
					ResetDisplayCounters();
				}
				else {
					g_774654 = 1;
				}
			}
		} while (main_RunFrameLoop((void*) d2_ShowInventoryDialog, 0x657c7) != 0);
	}
	d2_CloseInventoryPanel();
	d2_DestroyForm(dlg);
	fcn_0057e880(0x14, 0, 1, 0);
}
