

extern char g_6a4120[];
extern signed char g_6a3440;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_14cf950;
#include "client_dialog_state.h"
extern int g_100f1dc;

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
	if ((*(char*)&g_6a3440) != -1) {
		io_AppendText(0x1ae0);
	}
	s = io_AppendText(0x1ae1);
	a = d2_GetWindowListItem(h, 0, s);
	list = d2_CreateRadioGroup(2, a, d2_GetWindowListItem(h, 0, s + 1));
	while (main_RunFrameLoop(d2_RunChooseCharacterIntroDialog, 0xc6) != 0) {
		d2_UpdateRadioGroup(list);
		if (g_14ce8e0 != 0 || g_14cf950 == 1) {
			result = -1;
			g_774654 = 1;
		}
		if (g_100f1dc == 2 || g_14cf950 == 0x1c) {
			result = 1;
			g_774654 = 1;
		} else if (g_100f1dc == 1) {
			g_774654 = 1;
		}
	}
	d2_ClearRadioGroup(list);
	d2_DestroyForm(h);
	return result;
}
