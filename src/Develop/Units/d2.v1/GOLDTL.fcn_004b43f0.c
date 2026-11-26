#include "Develop/DieGildeAddOn/game/game_data.h"
extern int main_LoopFlags;
extern int g_100f1dc;
#include "client_dialog_state.h"
extern signed char g_6a3440;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl d2_SetForm(int k, int i);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl d2_CreateRadioGroup(int, ...);
void __cdecl fcn_00472640(int, int);
void __cdecl d2_SelectRadioGroup(int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_UpdateRadioGroup(int);
int __cdecl d2_ChooseMission(int);
void __cdecl d2_ClearRadioGroup(int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_004b41b0(void);

/* ADDRESS: GOLDTL 0x004b43f0 */
int __cdecl fcn_004b43f0(int n)
{
	int b0;
	int b1;
	int b2;
	int b3;
	int b4;
	int b5;
	int b6;
	int list;
	int dlg;
	int base;
	int sel;
	int r;

	r = 0;
	dlg = fcn_00470820(0, 0, "Menu\\CHOOSEHISTORY");
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	base = io_AppendText(0x1b9f);
	b0 = d2_GetWindowListItem(dlg, 0, base);
	b1 = d2_GetWindowListItem(dlg, 0, base + 1);
	b2 = d2_GetWindowListItem(dlg, 0, base + 2);
	b3 = d2_GetWindowListItem(dlg, 0, base + 3);
	b4 = d2_GetWindowListItem(dlg, 0, base + 4);
	b5 = d2_GetWindowListItem(dlg, 0, base + 5);
	b6 = d2_GetWindowListItem(dlg, 0, base + 6);
	list = d2_CreateRadioGroup(7, b0, b1, b2, b3, b4, b5, b6);
	sel = 1;
	if (n > 0) {
		fcn_00472640(b1, 0);
		sel = 2;
	}
	if (n > 1) {
		fcn_00472640(b2, 0);
		sel++;
	}
	if (n > 2) {
		fcn_00472640(b3, 0);
		sel++;
	}
	if (n > 3) {
		fcn_00472640(b4, 0);
		sel++;
	}
	if (n > 4) {
		fcn_00472640(b5, 0);
		sel = 0;
	}
	d2_SelectRadioGroup(list, sel);
	if (main_RunFrameLoop(fcn_004b41b0, main_LoopFlags) != 0) {
		do {
			d2_UpdateRadioGroup(list);
			if (g_100f1dc == 2) {
				if (d2_CurrentElementId == b6) {
					g_6a3440 = -1;
					r = 0xff;
					g_774654 = 1;
				} else if (d2_CurrentElementId == b0) {
					g_6a3440 = -1;
					r = 0;
					g_774654 = 1;
				} else {
					if (d2_CurrentElementId == b1) {
						g_6a3440 = 0;
					} else if (d2_CurrentElementId == b2) {
						g_6a3440 = 1;
					} else if (d2_CurrentElementId == b3) {
						g_6a3440 = 2;
					} else if (d2_CurrentElementId == b4) {
						g_6a3440 = 3;
					} else if (d2_CurrentElementId == b5) {
						g_6a3440 = 4;
					}
					d2_SelectRadioGroup(list, 0);
					r = d2_ChooseMission(g_6a3440);
					if (r != 0 && r != 0xff) {
						g_774654 = 1;
					}
				}
			}
		} while (main_RunFrameLoop(fcn_004b41b0, main_LoopFlags) != 0);
	}
	d2_ClearRadioGroup(list);
	fcn_00471e30(dlg);
	return r;
}
