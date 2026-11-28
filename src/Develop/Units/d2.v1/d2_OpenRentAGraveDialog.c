extern int d2_DialogButtonAction;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d2_CurrentWindowId;
#include "Develop/Units/d2.v1/client_dialog_state.h"

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl io_AppendText(int, ...);
void __cdecl d2_RefreshRentAGraveOptions(char*, int, int, int*, int*);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl main_RunFrameLoop(int, int);
void __cdecl d2_DestroyForm(int);
int __cdecl d2_ConfirmRentAGrave(char*, int);
void __cdecl d2_SetFormVisibility(int, int);

/* ADDRESS: GOLDTL 0x0058d020 */
void __cdecl d2_OpenRentAGraveDialog(char* a0)
{
	int sel; int selected;
	int ids[4];
	int dlg;
	int task;
	int i;

	sel = 0;
	dlg = d2_LoadForm(0, 0, "Locations\\Friedhof\\RentAGrave");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetForm(dlg, 1);
	io_AppendText(0x410a, 0x4108);
	d2_RefreshRentAGraveOptions(a0, dlg, 2, ids, &sel);
	d2_SetForm(dlg, 3);
	task = d2_GetWindowListItem(dlg, 3, io_AppendText(0x6a4078, 0x4117));
	selected = sel; d2_DialogButtonAction = -1;
	do {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		} else if (d2_DialogButtonAction != -1) {
			if (d2_CurrentElementId == task) {
				d2_SetFormVisibility(dlg, 0);
				if (d2_ConfirmRentAGrave(a0, selected) == 1) {
					d2_DialogCloseRequested = 1;
				}
				d2_SetFormVisibility(dlg, 1);
			} else {
				for (i = 0; i < 4; i++) {
					if (d2_CurrentElementId == ids[i] && i != selected) {
						sel = i;
						d2_RefreshRentAGraveOptions(a0, dlg, 2, ids, &sel); selected = sel;
						break;
					}
				}
			}
		}
	} while (main_RunFrameLoop(0x58d020, 0x677c7) != 0);
	d2_DestroyForm(dlg);
}
