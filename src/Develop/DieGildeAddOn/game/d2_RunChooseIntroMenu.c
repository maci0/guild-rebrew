

extern char g_6a4120[];
extern unsigned char g_77670a;
extern int gm_DifficultyLevel;
extern int io_RightButtonReleased;
extern char io_LastKeyScancode;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int d2_DialogButtonAction;
extern int d2_CurrentElementId;

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl main_RunFrameLoop(int (__cdecl*)(void), int);
int __cdecl d2_CreateRadioGroup(int, ...);
void __cdecl d2_SelectRadioGroup(int, int);
void __cdecl d2_UpdateRadioGroup(int);
void __cdecl d2_ClearRadioGroup(int);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDDE 0x005254c0 */
int __cdecl d2_RunChooseIntroMenu(void)
{
	int option1;
	int option2;
	int option3;
	int option4;
	int result;
	int h;
	int s;
	int option0;
	int list;

	result = 0;
	h = d2_LoadForm(0, 0, g_6a4120);
	d2_CenterDialogWindows(h);
	gm_DifficultyLevel = g_77670a;
	s = io_AppendText(0x1abf);
	option0 = d2_GetWindowListItem(h, 0, s);
	option1 = d2_GetWindowListItem(h, 0, s + 1);
	option2 = d2_GetWindowListItem(h, 0, s + 2);
	option3 = d2_GetWindowListItem(h, 0, s + 3);
	option4 = d2_GetWindowListItem(h, 0, s + 4);
	list = d2_CreateRadioGroup(6, option0, option1, option2, option3, option4, d2_GetWindowListItem(h, 0, s + 5));
	d2_SelectRadioGroup(list, gm_DifficultyLevel);
	while (main_RunFrameLoop(d2_RunChooseIntroMenu, 0xc6) != 0) {
		d2_UpdateRadioGroup(list);
		if (io_RightButtonReleased != 0 || io_LastKeyScancode == 1) {
			result = 0;
			d2_DialogCloseRequested = 1;
		}
		if (d2_DialogButtonAction == 2 || io_LastKeyScancode == 0x1c) {
			if (d2_CurrentElementId == option0) {
				gm_DifficultyLevel = 0;
			} else if (d2_CurrentElementId == option1) {
				gm_DifficultyLevel = 1;
			} else if (d2_CurrentElementId == option2) {
				gm_DifficultyLevel = 2;
			} else if (d2_CurrentElementId == option3) {
				gm_DifficultyLevel = 3;
			} else if (d2_CurrentElementId == option4) {
				gm_DifficultyLevel = 4;
			}
			result = 1;
			d2_DialogCloseRequested = 1;
		} else if (d2_DialogButtonAction == 1) {
			d2_DialogCloseRequested = 1;
		}
	}
	g_77670a = (unsigned char) gm_DifficultyLevel;
	d2_ClearRadioGroup(list);
	d2_DestroyForm(h);
	return result;
}
