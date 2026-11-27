


extern char g_6a3a80[];
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_14cf950;
#include "client_dialog_state.h"
extern int g_100f1dc;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl main_RunFrameLoop(int (__cdecl*)(void), int);
int __cdecl d2_CreateRadioGroup(int, int, int);
void __cdecl d2_UpdateRadioGroup(int);
void __cdecl d2_ClearRadioGroup(int);
void __cdecl fcn_00471af0(int, int);
void __cdecl d2_DestroyForm(int);
int __cdecl ls_LoadNetworkSaveHeader(void);
int __cdecl d2_ShowServerBrowser(int);

int __cdecl d2_ShowNetworkLoadDialog(void)
{
	int radio_group;
	int join_btn;
	int result;
	int dlg;
	int host_btn;

	result = 0;
	dlg = fcn_00470820(0, 0, g_6a3a80);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	io_AppendText(0x1ca5);
	host_btn = d2_GetWindowListItem(dlg, 0, io_AppendText(0x1ca9));
	join_btn = d2_GetWindowListItem(dlg, 0, io_AppendText(0x1caa));
	radio_group = d2_CreateRadioGroup(2, host_btn, join_btn);
	while (main_RunFrameLoop(d2_ShowNetworkLoadDialog, 0x24087) != 0) {
		d2_UpdateRadioGroup(radio_group);
		if (g_14ce8e0 != 0 || g_14cf950 == 1) {
			g_774654 = 1;
			result = 0;
		}
		if (g_100f1dc != -1) {
			if (d2_CurrentElementId == host_btn) {
				fcn_00471af0(dlg, 0);
				if (ls_LoadNetworkSaveHeader() != 0) {
					g_774654 = 1;
					result = 1;
				}
				fcn_00471af0(dlg, 1);
			} else if (d2_CurrentElementId == join_btn) {
				fcn_00471af0(dlg, 0);
				if (d2_ShowServerBrowser(1) != 0) {
					g_774654 = 1;
					result = 1;
				}
				fcn_00471af0(dlg, 1);
			}
		}
	}
	d2_ClearRadioGroup(radio_group);
	d2_DestroyForm(dlg);
	return result;
}
