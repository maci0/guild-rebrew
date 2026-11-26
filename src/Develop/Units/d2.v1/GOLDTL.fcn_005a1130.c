int __cdecl d2_ClearWindowChildren();
int __cdecl d2_AddElementToWindow();
int __cdecl fcn_00471af0();
int __cdecl d2_CenterDialogWindows();
int __cdecl fcn_00471e30();
int __cdecl d2_GetWindowListItem();
int __cdecl d2_SetForm();
int __cdecl d2_SetOverlayAnimation();
int __cdecl fcn_004927c0();
int __cdecl fcn_00492950();
int __cdecl fcn_00492d60();
int __cdecl ai_EvalBlackjackAction();
int __cdecl fcn_00493000();
int __cdecl cm_RequestTransferCurrencyNoKill();
int __cdecl gm_LookupEntityRecordById();
int __cdecl fcn_0050b710();
int __cdecl io_AppendText();
int __cdecl io_FormatTextBuffer();
int __cdecl fcn_00532ef0();
int __cdecl fcn_005340f0();
int __cdecl main_RunFrameLoop();
int __cdecl d2_ShowWirtshausRules();
int __cdecl fcn_005a0cd0();
int __cdecl fcn_005a1130();
int __cdecl d2_BuildPersonStatusDesc();
int __cdecl fcn_005ca740();
int __cdecl gm_LookupEntityRecordById();
int __cdecl fcn_00591990();
#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLDTL 0x005a1130 */
int __cdecl fcn_005a1130(char* a0, int window)
{
	char* self;
	int i;
	int x;
	int y;

	d2_SetForm(window, 2);
	d2_ClearWindowChildren(*(int*) &d2_CurrentWindowId, 1);
	d2_SetForm(window, 3);
	d2_ClearWindowChildren(*(int*) &d2_CurrentWindowId, 1);
	self = a0;

	if (*(unsigned char*) (*(char**) (self + 0xc) + 2) == 6) {
		d2_SetForm(window, 3);
		io_AppendText(0x6a9694, *(char**) (self + 0xc) + 0x30);
		i = 0;
		x = 0x1c;
		y = 0x1d;
		while (i < *(unsigned char*) (self + 0x10)) {
			d2_AddElementToWindow(x, y, *(unsigned char*) (self + 0x18 + i) + 0x75a, *(int*) &d2_CurrentWindowId);
			i++;
			if (i % 8 == 0) x = 0; else x += 0x3a;
			y = 0x1d + (i > 7 ? 0x29 : 0);
		}
	} else {
		d2_SetForm(window, 2);
		io_AppendText(0x6a9694, *(char**) (self + 0xc) + 0x30);
		i = 0;
		x = 0x1c;
		y = 0x1d;
		while (i < *(unsigned char*) (self + 0x10)) {
			if (*(int*) (self + 0x28) == 4) {
				d2_AddElementToWindow(x, y, 0x761, *(int*) &d2_CurrentWindowId);
			} else {
				d2_AddElementToWindow(x, y, *(unsigned char*) (self + 0x18 + i) + 0x75a, *(int*) &d2_CurrentWindowId);
			}
			i++;
			if (i % 8 == 0) x = 0; else x += 0x3a;
			y = 0x1d + (i > 7 ? 0x29 : 0);
		}
	}

	if (*(unsigned char*) (*(char**) (self + 0x30) + 2) == 6) {
		d2_SetForm(window, 3);
		io_AppendText(0x6a9694, *(char**) (self + 0x30) + 0x30);
		i = 0;
		x = 0x1c;
		y = 0x1d;
		while (i < *(unsigned char*) (self + 0x34)) {
			d2_AddElementToWindow(x, y, *(unsigned char*) (self + 0x3c + i) + 0x75a, *(int*) &d2_CurrentWindowId);
			i++;
			if (i % 8 == 0) x = 0; else x += 0x3a;
			y = 0x1d + (i > 7 ? 0x29 : 0);
		}
	} else {
		d2_SetForm(window, 2);
		io_AppendText(0x6a9694, *(char**) (self + 0x30) + 0x30);
		i = 0;
		x = 0x1c;
		y = 0x1d;
		while (i < *(unsigned char*) (self + 0x34)) {
			if (*(int*) (self + 0x28) == 4) {
				d2_AddElementToWindow(x, y, 0x761, *(int*) &d2_CurrentWindowId);
			} else {
				d2_AddElementToWindow(x, y, *(unsigned char*) (self + 0x3c + i) + 0x75a, *(int*) &d2_CurrentWindowId);
			}
			i++;
			if (i % 8 == 0) x = 0; else x += 0x3a;
			y = 0x1d + (i > 7 ? 0x29 : 0);
		}
	}

	d2_SetForm(window, 4);
	d2_ClearWindowChildren(*(int*) &d2_CurrentWindowId, 1);
	if ((*(int*) (self + 8) == 5 && *(unsigned char*) (*(char**) (self + 0xc) + 2) == 6)
		|| (*(int*) (self + 8) == 6 && *(unsigned char*) (*(char**) (self + 0x30) + 2) == 6)) {
		return io_AppendText(0x1887, *(int*) (self + 0x54));
	}
	return io_AppendText(0x1888, *(int*) (self + 0x54) / 2);
}
