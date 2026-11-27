extern int g_100f1dc;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d2_CurrentWindowId;
#include "client_dialog_state.h"

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl io_AppendText(int, ...);
void __cdecl fcn_0058c4f0(char*, int, int, int*, int*);
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
	dlg = fcn_00470820(0, 0, "Locations\\Friedhof\\RentAGrave");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	fcn_005340f0(d2_CurrentWindowId);
	d2_SetForm(dlg, 1);
	io_AppendText(0x410a, 0x4108);
	fcn_0058c4f0(a0, dlg, 2, ids, &sel);
	d2_SetForm(dlg, 3);
	task = d2_GetWindowListItem(dlg, 3, io_AppendText(0x6a4078, 0x4117));
	selected = sel; g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (d2_CurrentElementId == task) {
				d2_SetFormVisibility(dlg, 0);
				if (d2_ConfirmRentAGrave(a0, selected) == 1) {
					g_774654 = 1;
				}
				d2_SetFormVisibility(dlg, 1);
			} else {
				for (i = 0; i < 4; i++) {
					if (d2_CurrentElementId == ids[i] && i != selected) {
						sel = i;
						fcn_0058c4f0(a0, dlg, 2, ids, &sel); selected = sel;
						break;
					}
				}
			}
		}
	} while (main_RunFrameLoop(0x58d020, 0x677c7) != 0);
	d2_DestroyForm(dlg);
}
