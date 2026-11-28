

extern char g_6a4120[];
extern signed char gm_SelectedMissionIndex;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char io_LastKeyScancode;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int d2_DialogButtonAction;

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl main_RunFrameLoop(int (__cdecl*)(void), int);
int __cdecl d2_CreateRadioGroup(int, ...);
void __cdecl d2_UpdateRadioGroup(int);
void __cdecl d2_ClearRadioGroup(int);
void __cdecl d2_DestroyForm(int);

int __cdecl d2_RunChooseCharacterIntroDialog(void)
{
	int result;
	int h;
	int s;
	int a;
	int list;

	result = 0;
	h = d2_LoadForm(0, 0, g_6a4120);
	d2_CenterDialogWindows(h);
	io_AppendText(0x1adf);
	if ((*(char*)&gm_SelectedMissionIndex) != -1) {
		io_AppendText(0x1ae0);
	}
	s = io_AppendText(0x1ae1);
	a = d2_GetWindowListItem(h, 0, s);
	list = d2_CreateRadioGroup(2, a, d2_GetWindowListItem(h, 0, s + 1));
	while (main_RunFrameLoop(d2_RunChooseCharacterIntroDialog, 0xc6) != 0) {
		d2_UpdateRadioGroup(list);
		if (io_RightButtonReleased != 0 || io_LastKeyScancode == 1) {
			result = -1;
			d2_DialogCloseRequested = 1;
		}
		if (d2_DialogButtonAction == 2 || io_LastKeyScancode == 0x1c) {
			result = 1;
			d2_DialogCloseRequested = 1;
		} else if (d2_DialogButtonAction == 1) {
			d2_DialogCloseRequested = 1;
		}
	}
	d2_ClearRadioGroup(list);
	d2_DestroyForm(h);
	return result;
}
