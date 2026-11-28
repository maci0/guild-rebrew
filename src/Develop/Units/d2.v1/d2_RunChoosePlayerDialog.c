#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include "Develop/Units/d2.v1/d2_gui.h"
extern int d2_DialogButtonAction;
extern int tp_d2_HoveredControl;
extern int g_14abe74;
extern int g_14abe78;
extern int g_14abe80;
extern int g_14abe84;
extern char* d2_Controls;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char io_LastKeyScancode;
extern int d2_CurrentWindowId;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern char g_7e22c0[];
extern char g_7e23ea[];
extern char g_7e240a[];
extern int g_7e23e4;
extern char g_7e23e8;
extern char g_7e23e9; extern unsigned char g_7e23e1; extern unsigned char g_7e23e2;
extern char g_7e23e0[];

extern char s_6a1e4c[]; /* "Network" */
extern char s_6a1e54[]; /* "Name" */
extern char s_6a1e3c[]; /* "Familienname" */
extern char s_6a401c[]; /* "Vorname" */
extern char s_6a4010[]; /* "Nachname" */
extern char s_6a4008[]; /* "Wappen" */
extern char s_6a3ffc[]; /* "Geschlecht" */
extern char s_6a3ff4[]; /* "Glauben" */
extern char s_6a3fe0[]; /* "Menu\\CHOOSEPLAYER" */

int __cdecl d2_CreateRadioGroup(int, ...);
void __cdecl d2_AddToRadioGroup(int, int);
void __cdecl d2_ClearRadioGroup(int);
void __cdecl d2_SelectRadioGroup(int, int);
void __cdecl d2_UpdateRadioGroup(int);
int __cdecl d2_AddElementToWindow(int, int, int, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_DestroyForm(int);
char* __cdecl d2_GetControlValue(int);
void __cdecl d2_SetSlotVisibility(int, int);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl d2_CreateGuiWindow(int, ...);
void __cdecl d2_SetBildArgument(int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_ResetSelectionAndInput(void);
void __cdecl d2_SelectControl(int);
int __cdecl txt_GetCitySelectInfo(char*, char*);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_CreateButtonRow(int, int, int*, int, int, int);
int __cdecl main_RunFrameLoop(int (__cdecl*)(void), int);

/* ADDRESS: GOLDTL 0x0053d490 */
int __cdecl d2_RunChoosePlayerDialog(int a0, int a1)
{
	int list;
	int glyphs;
	int list1;
	int list2;
	char* s1a;
	char* s1b;
	char* s2a;
	char* s2b;
	int dlg;
	int firstNameField;
	int surnameField;
	int v27;
	int i;
	int j;
	int n;
	int id;
	int rows;
	int v11[2];
	int sel[8];
	int v9;
	unsigned char redraw;
	int result;
	char itoa_buf[0x30];
	char buf[0x100];

	redraw = 1;
	result = 0;
	i = 0;
	list = 0;
	v9 = 0;
	GetPrivateProfileStringA(s_6a1e4c, s_6a1e54, s_6a401c, g_7e23ea, 0x20,
	    g_7e22c0);
	GetPrivateProfileStringA(s_6a1e4c, s_6a1e3c, s_6a4010, g_7e240a, 0x20,
	    g_7e22c0);
	g_7e23e4 = GetPrivateProfileIntA(s_6a1e4c, s_6a4008, 0, g_7e22c0) + 0x59a;
	g_7e23e8 = GetPrivateProfileIntA(s_6a1e4c, s_6a3ffc, 0, g_7e22c0);
	g_7e23e9 = GetPrivateProfileIntA(s_6a1e4c, s_6a3ff4, 0, g_7e22c0);
	dlg = d2_LoadForm(0, 0, s_6a3fe0);
	d2_CenterDialogWindows(dlg);
	txt_GetCitySelectInfo(g_7e1d00, buf);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1acf, buf);
	firstNameField = d2_GetWindowListItem(dlg, 1, io_AppendText(0x1ad0, 0x1ad2));
	d2_SetForm(dlg, 2);
	surnameField = d2_GetWindowListItem(dlg, 2, io_AppendText(0x1ad1, 0x1ad3));
	d2_SetForm(dlg, 3);
	io_AppendText(0x1ad4);
	d2_CreateButtonRow(d2_CurrentWindowId, 0x1c, v11, 2, g_14abe74,
	    g_14abe78);
	s1a = (char*) v11[0];
	s1b = (char*) v11[1];
	d2_SetForm(dlg, 4);
	io_AppendText(0x1ad7);
	d2_CreateButtonRow(d2_CurrentWindowId, 0x1c, v11, 2, g_14abe80,
	    g_14abe84);
	s2a = (char*) v11[0];
	s2b = (char*) v11[1];
	d2_SetForm(dlg, 5);
	io_AppendText(0x1adb);
	rows = (*(int*) (d2_CurrentWindowId * 0x3cc + 0x1015f4c) - 0x20) / 0x30;
	list = d2_CreateRadioGroup(0);
	for (i = 0; i < 8; i++) {
		id = d2_AddElementToWindow((i % rows) * 0x30 + 0x50,
		    (i / rows) * 0x30 + 0x20, i + 0x59a, d2_CurrentWindowId);
		sel[i] = id;
		((D2_CONTROL_TL*)d2_Controls)[id].value_058 = 1;
		((D2_CONTROL_TL*)d2_Controls)[id].value_038 = 0;
		((D2_CONTROL_TL*)d2_Controls)[id].value_03c = 0;
		((D2_CONTROL_TL*)d2_Controls)[id].value_060 = 1;
		((D2_CONTROL_TL*)d2_Controls)[id].flags_1d0 = 3;
		d2_AddToRadioGroup(list, id);
	}
	d2_SetForm(dlg, 6);
	v27 = d2_GetWindowListItem(dlg, 6, io_AppendText(0x7e));
	d2_CreateGuiWindow(firstNameField, g_7e23ea);
	d2_CreateGuiWindow(surnameField, g_7e240a);
	for (j = 0; j < 8; j++) {
		if (((D2_CONTROL_TL*)d2_Controls)[sel[j]].value_008 == g_7e23e4) {
			d2_SelectRadioGroup(list, j);
			break;
		}
	}
	d2_SetBildArgument(firstNameField, 0xc);
	d2_SetBildArgument(surnameField, 0xc);
	list1 = d2_CreateRadioGroup(2, s1a, s1b);
	d2_SelectRadioGroup(list1, g_7e23e8 & 0xff);
	list2 = d2_CreateRadioGroup(2, s2a, s2b);
	d2_SelectRadioGroup(list2, (unsigned char) g_7e23e9);
	d2_ResetSelectionAndInput();
	io_LastKeyScancode = 0;
	for (;;) {
		if (io_RightButtonReleased != 0
		    || (d2_DialogButtonAction != -1 && d2_CurrentElementId == v27)
		    || io_LastKeyScancode == 1) {
			if (v9 == 0 && a1 == 0) {
				d2_DialogCloseRequested = 1;
				goto check_redraw;
			}
			v9--;
			goto redraw_ui;
		}
	check_redraw:
		if (redraw == 0) {
			goto state_machine;
		}
	redraw_ui:
		for (i = 0; i < 5; i++) {
			d2_SetSlotVisibility(d2_GetWindowListItem(dlg, 0, i), i <= v9);
		}
		if (v9 == 0) {
			d2_SelectControl(firstNameField);
		} else if (v9 == 1) {
			d2_SelectControl(surnameField);
		}
		redraw = 0;
	state_machine:
		if (v9 == 0) {
			if (io_LastKeyScancode == 0x1c) {
				strcpy(g_7e23ea, d2_GetControlValue(firstNameField));
				v9 = 1;
				redraw = 1;
				io_LastKeyScancode = 0;
			}
		} else if (v9 == 1) {
			if (io_LastKeyScancode == 0x1c) {
				strcpy(g_7e240a, d2_GetControlValue(surnameField));
				v9 = 2;
				redraw = 1;
				io_LastKeyScancode = 0;
			}
		} else if (v9 == 2) {
			d2_UpdateRadioGroup(list1);
			if (d2_DialogButtonAction != -1) {
				if (d2_CurrentElementId == (int) s1a) {
					g_7e23e8 = 0;
					v9 = 3;
					redraw = 1;
				} else if (d2_CurrentElementId == (int) s1b) {
					g_7e23e8 = 1;
					v9 = 3;
					redraw = 1;
				}
			}
		} else if (v9 == 3) {
			d2_UpdateRadioGroup(list2);
			if (d2_DialogButtonAction != -1) {
				if (d2_CurrentElementId == (int) s2b) {
					g_7e23e9 = 1;
					v9 = 4;
					redraw = 1;
				} else if (d2_CurrentElementId == (int) s2a) {
					g_7e23e9 = 0;
					v9 = 4;
					redraw = 1;
				}
			}
		} else if (v9 == 4) {
			d2_UpdateRadioGroup(list);
			if (io_LastKeyScancode == 0x1c) {
				v9 = 5;
				redraw = 1;
			}
			if (0x59a <= d2_DialogButtonAction && d2_DialogButtonAction <= 0x5a1) {
				for (j = 0; j < 8; j++) {
					n = sel[j];
					if ((char*)&((D2_CONTROL_TL*)d2_Controls)[n] != (char*) tp_d2_HoveredControl) {
						((D2_CONTROL_TL*)d2_Controls)[n].value_038 = 0;
						((D2_CONTROL_TL*)d2_Controls)[n].value_03c = 0;
						((D2_CONTROL_TL*)d2_Controls)[n].value_060 = 1;
					}
				}
				v9++;
			}
		} else if (v9 == 5) {
			g_7e23e0[0] = 0;
			g_7e23e1 = 0;
			g_7e23e2 = 0x12;
			g_7e23e4 = ((D2_CONTROL_TL*)d2_Controls)[
			     *(int*) (((list * 8 - list) * 5
					   + *(int*) (list * 0x8c + 0x102cbc8)) * 4
				       + 0x102cbcc)
				]
			    .value_008;
			result = 1;
			d2_DialogCloseRequested = 1;
		}
		if (main_RunFrameLoop((int (__cdecl*)(void)) d2_RunChoosePlayerDialog, a0) != 0) {
			continue;
		}
		d2_ClearRadioGroup(list1);
		d2_ClearRadioGroup(list2);
		d2_ClearRadioGroup(list);
		d2_DestroyForm(dlg);
		WritePrivateProfileStringA(s_6a1e4c, s_6a1e54, g_7e23ea,
		    g_7e22c0);
		WritePrivateProfileStringA(s_6a1e4c, s_6a1e3c, g_7e240a,
		    g_7e22c0);
		itoa(g_7e23e4 - 0x59a, itoa_buf, 10);
		WritePrivateProfileStringA(s_6a1e4c, s_6a4008, itoa_buf,
		    g_7e22c0);
		itoa(g_7e23e8 & 0xff, itoa_buf, 10);
		WritePrivateProfileStringA(s_6a1e4c, s_6a3ffc, itoa_buf,
		    g_7e22c0);
		itoa((unsigned char) g_7e23e9, itoa_buf, 10);
		WritePrivateProfileStringA(s_6a1e4c, s_6a3ff4, itoa_buf,
		    g_7e22c0);
		return result;
	}
}
