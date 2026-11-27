#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"
extern int g_14ce8e0;
extern char g_7f4ca4[];
/* Dialog message loop for 0x6ac5d8: validates the click id through
   fcn_00504f30, shows the dialog, then forwards the 0x39 packet to
   fcn_004c5530 while fcn_005373e0 keeps the loop alive. */

int __cdecl gm_CanBuildBuildingType(int, int);
int __cdecl d2_ShowModalMessageBox(int, int);
void* __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(void*);
void __cdecl d2_DestroyForm(void*);
int __cdecl gm_CalculateGebaeudeValue(char*, int);
int __cdecl gm_AmountToUnits(int, char);
int __cdecl d2_SetForm(void*, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(void*, int, int);
void __cdecl d2_CreateGuiWindow(int, int, int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl gm_SearchTable67(int);
int __cdecl gm_ConvertUnitsToAmount(int, char);
int __cdecl d2_GetControlValue(int);
int __cdecl gm_CheckEntityStock(char*, int, char);
void __cdecl cm_SendCopyEntityData(void*);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);

/* ADDRESS: GOLDTL 0x005c35d0 */
void __cdecl d2_RunSellGebaeudeDialog(char* e)
{
	char pkt[0xf8];
	int w;
	int ctl;
	int x;
	int y;
	void* dlg; int id;

	id = *(int*) (e + 1); if (gm_CanBuildBuildingType(*(unsigned char*) e, g_774970) != 1) {
		d2_ShowModalMessageBox(*(int*) 0x14ab29c, 0);
		return;
	}
	dlg = d2_LoadForm(0, 0, (char*) 0x6ac5d8);
	d2_CenterDialogWindows(dlg);
	x = gm_CalculateGebaeudeValue(e, *(signed char*) (e + 0x5c));
	w = gm_AmountToUnits(x, g_773d75);
	d2_SetForm(dlg, 2);
	ctl = d2_GetWindowListItem(dlg, 2,
	                   io_AppendText(0x17de, *(unsigned short*) (e + 0x25), e,
	                                g_773d75));
	x = (int) ((double) w * 10.0);
	y = (int) ((double) w * 0.5);
	d2_CreateGuiWindow(ctl, y, x, w);
	d2_SetOverlayAnimation(0, 0);
	main_RunFrameLoop(0, 0x677c7);
	do {
		x = gm_SearchTable67(id);
		if ((*(unsigned char*) (e + 0x5b) & 4) != 0 || x == 0) {
			g_774654 = 1;
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc == 2) {



			if (gm_CheckEntityStock((char*) (0x7f4ca0 +
			                          g_774970 * 0x21c),
			                 gm_ConvertUnitsToAmount(d2_GetControlValue(ctl), g_773d75), g_773d75)) {
				*(char*) (pkt + 4) = 0x21;
				*(int*) (pkt + 8) = *(int*) (g_7f4ca4 +
				                             *(unsigned short*) (e + 0x25) * 0x21c);
				*(int*) (pkt + 0xc) = -1;
				*(char*) (pkt + 0x36) = 9;
				*(int*) (pkt + 0x58) = *(int*) (e + 1);
				*(int*) (pkt + 0x5c) = gm_ConvertUnitsToAmount(
				    d2_GetControlValue(ctl),
				    g_773d75);
				*(int*) (pkt + 0x60) = *(int*) (g_7f4ca4 +
				                                g_774970 * 0x21c);
				cm_SendCopyEntityData(pkt);
				cm_RequestChangeBits(*(int*) (e + 1), 0x5a, 2, 0x200, 0);
			}
			g_774654 = 1;
		} else if (g_100f1dc == 1) {
			g_774654 = 1;
		}
	} while (main_RunFrameLoop((void*) d2_RunSellGebaeudeDialog, 0x677c7) != 0);
	d2_DestroyForm(dlg);
}
