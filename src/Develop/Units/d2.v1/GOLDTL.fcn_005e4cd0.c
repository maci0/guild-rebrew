

extern int d2_CurrentWindowId;
extern char* g_1015ea0;
extern int g_14ac660[];
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_14cf950;
#include "client_dialog_state.h"

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl d2_AddElementToWindow(int, int, int, int);
void __cdecl d2_SetElementFont(int, int);
void __cdecl d2_SetControlText(int, int);
int __cdecl d2_IsPrivilegeMessageEnabled(int);
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl d2_GetControlValue(int);
void __cdecl d2_ToggleMessageFilterFlag(int, int);
void __cdecl d2_DestroyForm(int);

void __cdecl d2_RunMessageFilterDialog(void)
{
	int h;
	int btn[16];
	int i;
	int b;

	h = d2_LoadForm(0, 0, "menu\\messagefilter");
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 2);
	for (i = 0; i < 9; i++) {
		b = d2_AddElementToWindow(8, i * 0x1c + 0xa, 0x605 + i, d2_CurrentWindowId);
		btn[i] = b;
		*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[b].value_058)) = 1;
		*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[b].value_05c)) = 1;
		d2_SetElementFont(b, 0x55);
		d2_SetControlText(b, g_14ac660[i]);
		*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[b].value_1d4)) = 0x78;
		*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[b].value_1dc)) = 0x1e;
		*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[b].value_1e0)) = 3;
		d2_SetElementValue(b, d2_IsPrivilegeMessageEnabled(0x605 + i) == 0);
	}
	while (main_RunFrameLoop(d2_RunMessageFilterDialog, 0x677c7) != 0) {
		if (g_14ce8e0 != 0 || (*(unsigned char*)&g_14cf950) == 1) {
			g_774654 = 1;
			for (i = 0; i < 9; i++) {
				d2_ToggleMessageFilterFlag(0x605 + i, d2_GetControlValue(btn[i]) == 0);
			}
		}
	}
	d2_DestroyForm(h);
}
