


extern char g_6a3a80[];
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char io_LastKeyScancode;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int d2_DialogButtonAction;
extern unsigned char gm_ClientModeFlags;
extern signed char gm_SelectedMissionIndex;

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl main_RunFrameLoop(int (__cdecl*)(void), int);
int __cdecl d2_CreateRadioGroup(int, int, int, int);
void __cdecl d2_UpdateRadioGroup(int);
void __cdecl d2_ClearRadioGroup(int);
void __cdecl d2_SetFormVisibility(int, int);
void __cdecl d2_DestroyForm(int);
int __cdecl d2_StartLocalSessionSetup(void);
int __cdecl d2_ShowServerBrowser(int);
int __cdecl d2_ShowNetworkLoadDialog(void);

int __cdecl d2_ShowChooseNetworkDialog(void)
{
	int list;
	int b;
	int c;
	int result;
	int h;
	int a;

	result = 0;
	h = d2_LoadForm(0, 0, g_6a3a80);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 0);
	io_AppendText(0x1ca5);
	a = d2_GetWindowListItem(h, 0, io_AppendText(0x1ca6));
	b = d2_GetWindowListItem(h, 0, io_AppendText(0x1ca7));
	c = d2_GetWindowListItem(h, 0, io_AppendText(0x1ca8));
	list = d2_CreateRadioGroup(3, a, b, c);
	(*(unsigned char*)&gm_SelectedMissionIndex) = 0xfe;
	while (main_RunFrameLoop(d2_ShowChooseNetworkDialog, 0x24087) != 0) {
		d2_UpdateRadioGroup(list);
		if (io_RightButtonReleased != 0 || io_LastKeyScancode == 1) {
			d2_DialogCloseRequested = 1;
			result = 0;
		}
		if (d2_DialogButtonAction != -1) {
			if (d2_CurrentElementId == a) {
				(*(int*)&gm_ClientModeFlags) = 5;
				d2_SetFormVisibility(h, 0);
				if (d2_StartLocalSessionSetup() != 0) {
					d2_DialogCloseRequested = 1;
					result = 1;
				}
				d2_SetFormVisibility(h, 1);
			} else if (d2_CurrentElementId == b) {
				(*(int*)&gm_ClientModeFlags) = 5;
				d2_SetFormVisibility(h, 0);
				if (d2_ShowServerBrowser(0) != 0) {
					d2_DialogCloseRequested = 1;
					result = 1;
				}
				d2_SetFormVisibility(h, 1);
			} else if (d2_CurrentElementId == c) {
				(*(int*)&gm_ClientModeFlags) = 4;
				d2_SetFormVisibility(h, 0);
				if (d2_ShowNetworkLoadDialog() != 0) {
					d2_DialogCloseRequested = 1;
					result = 1;
				}
				d2_SetFormVisibility(h, 1);
			}
		}
	}
	d2_ClearRadioGroup(list);
	d2_DestroyForm(h);
	return result;
}
