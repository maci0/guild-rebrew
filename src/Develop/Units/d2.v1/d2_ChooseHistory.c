

extern char g_68116c[];
extern char g_6a4078[];
extern int g_776704;
extern signed char gm_SelectedMissionIndex;
extern int io_RightButtonReleased;
extern char io_LastKeyScancode;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int d2_DialogButtonAction;
extern int d2_CurrentElementId;

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl main_RunFrameLoop(int (__cdecl*)(void), int);
int __cdecl d2_CreateRadioGroup(int, ...);
void __cdecl d2_SelectRadioGroup(int, int);
void __cdecl d2_UpdateRadioGroup(int);
void __cdecl d2_ClearRadioGroup(int);
void __cdecl d2_DestroyForm(int);

int __cdecl d2_ChooseHistory(void)
{
	int option1;
	int option2;
	int option3;
	int option4;
	int option5;
	int option6;
	int result;
	int dialogHandle;
	int textStart;
	int option0;
	int radioGroup;

	result = 0;
	dialogHandle = d2_LoadForm(0, 0, g_68116c);
	d2_CenterDialogWindows(dialogHandle);
	d2_SetForm(dialogHandle, 0);
	textStart = io_AppendText(0x1ac5, 0x1ac7, 0x1ac8, 0x1ac9, 0x1aca, 0x1acb, 0x1acc);
	option0 = d2_GetWindowListItem(dialogHandle, 0, textStart);
	option1 = d2_GetWindowListItem(dialogHandle, 0, textStart + 1);
	option2 = d2_GetWindowListItem(dialogHandle, 0, textStart + 2);
	option3 = d2_GetWindowListItem(dialogHandle, 0, textStart + 3);
	option4 = d2_GetWindowListItem(dialogHandle, 0, textStart + 4);
	option5 = d2_GetWindowListItem(dialogHandle, 0, textStart + 5);
	option6 = d2_GetWindowListItem(dialogHandle, 0, io_AppendText((int) g_6a4078, 0x1acd));
	if (g_776704 <= -1) {
		g_776704 = -1;
	}
	radioGroup = d2_CreateRadioGroup(7, option0, option1, option2, option3, option4, option5, option6);
	if (g_776704 != -1) {
		d2_SelectRadioGroup(radioGroup, g_776704 + 1);
	} else {
		d2_SelectRadioGroup(radioGroup, 0);
	}
	while (main_RunFrameLoop(d2_ChooseHistory, 0xc6) != 0) {
		d2_UpdateRadioGroup(radioGroup);
		if (io_RightButtonReleased != 0 || io_LastKeyScancode == 1) {
			d2_DialogCloseRequested = 1;
		}
		if (d2_DialogButtonAction == 2) {
			if (d2_CurrentElementId == option0) {
				(*(char*)&gm_SelectedMissionIndex) = -1;
			} else if (d2_CurrentElementId == option1) {
				(*(char*)&gm_SelectedMissionIndex) = 0;
			} else if (d2_CurrentElementId == option2) {
				(*(char*)&gm_SelectedMissionIndex) = 1;
			} else if (d2_CurrentElementId == option3) {
				(*(char*)&gm_SelectedMissionIndex) = 2;
			} else if (d2_CurrentElementId == option4) {
				(*(char*)&gm_SelectedMissionIndex) = 3;
			} else if (d2_CurrentElementId == option5) {
				(*(char*)&gm_SelectedMissionIndex) = 4;
			} else if (d2_CurrentElementId == option6) {
				(*(char*)&gm_SelectedMissionIndex) = 5;
			}
			g_776704 = (*(char*)&gm_SelectedMissionIndex);
			if (g_776704 != -1) {
				d2_SelectRadioGroup(radioGroup, g_776704 + 1);
			} else {
				d2_SelectRadioGroup(radioGroup, 0);
			}
			result = 1;
			d2_DialogCloseRequested = 1;
		} else if (d2_DialogButtonAction == 1) {
			d2_DialogCloseRequested = 1;
		}
	}
	d2_ClearRadioGroup(radioGroup);
	d2_DestroyForm(dialogHandle);
	return result;
}
