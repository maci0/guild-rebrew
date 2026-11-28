#include <windows.h>
#include <string.h>

extern char g_7e22c0[];      /* ini file path */
extern char g_7e23ea[];      /* first name buffer (0x20) */
extern char g_7e240a[];      /* family name buffer (0x20) */
extern char io_LastKeyScancode;       /* last pressed key */
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d2_DialogButtonAction;        /* focused element id */
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int* lb_LobbyPlayerList;        /* entity list head */
extern int* d2_LobbyLocalPlayerEntry;        /* rejected entity */
extern int* tp_d3_SceneState;
extern char* tp_d2_HoveredControl;      /* element of the current player */
extern int d2_RadioGroupItems[];
extern int g_102cbcc[];
extern char d2_WindowMetricsView[];
extern char g_7e23e0[];
extern unsigned char g_7e23e1; extern unsigned char g_7e23e2;
extern int g_7e23e4;
extern char g_7e23e8;
extern char g_7e23e9;
extern signed char gm_SelectedMissionIndex;
extern int g_14abe74;
extern int g_14abe78;
extern int g_14abe80;
extern int g_14abe84;
#include "Develop/Units/d2.v1/d2_gui.h"

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl txt_GetCitySelectInfo(char*, char*);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl d2_CreateButtonRow(int, int, int*, int, ...);
int __cdecl d2_CreateRadioGroup(int, ...);
int __cdecl d2_AddElementToWindow(int, int, int, int);
void __cdecl d2_AddToRadioGroup(int, int);
void __cdecl d2_SelectRadioGroup(int, int);
void __cdecl d2_SetBildArgument(int, int);
void __cdecl d2_ResetSelectionAndInput(void);
void __cdecl d2_SelectControl(int);
int __cdecl d2_SetSlotVisibility(int, int);
char* __cdecl d2_GetControlValue(int);
void __cdecl d2_DestroyForm(int);
void __cdecl d2_ClearRadioGroup(int);
void __cdecl d2_UpdateRadioGroup(int);
int __cdecl d3_GetSceneEntry(int);
int __cdecl cm_RequestClearSceneEntries(void);
int __cdecl cm_GetCommandStatus(int);
int __cdecl lb_GetPlayerList(void);
void __cdecl cm_StepCommandQueue(void);
int __cdecl main_RunFrameLoop(int (__cdecl*)(void), int);
char* __cdecl itoa(int, char*, int);


/* Player name editor: loads the stored name, religion, sex and crest, lays out
 * the eight crest buttons and runs the modal edit loop until the dialog
 * closes, then writes the selected name back to the ini file. */
/* ADDRESS: GOLDTL 0x005936f0 */
int __cdecl d2_RunPlayerEditorDialog(int msg, int param)
{
	char text[0x100];
	char digit[0x30];
	int out[4];
	int ids[8];
	int first;
	int second;
	int elem6;
	int group;
	int h;
	int w8;
	int w24;
	int cols;
	int sel;
	int result;
	int i;
	int n;
	int p;
	char redraw;
	char* s;
	int sex1;
	int sex0;
	int faith1;
	int faith0;
	int* ent;

	redraw = 1;
	result = 0;
	sel = 0;
	GetPrivateProfileStringA("Network", "Name", "Vorname", g_7e23ea, 0x20, g_7e22c0);
	GetPrivateProfileStringA("Network", "Familienname", "Nachname", g_7e240a, 0x20, g_7e22c0);
	g_7e23e4 = GetPrivateProfileIntA("Network", "Wappen", 0, g_7e22c0) + 0x59a;
	g_7e23e8 = (char) GetPrivateProfileIntA("Network", "Geschlecht", 0, g_7e22c0);
	g_7e23e9 = (char) GetPrivateProfileIntA("Network", "Glauben", 0, g_7e22c0);
	h = d2_LoadForm(0, 0, "Menu\\CHOOSEPLAYER");
	d2_CenterDialogWindows(h);
	txt_GetCitySelectInfo((char*) 0x9baa76, text);
	d2_SetForm(h, 1);
	io_AppendText(0x1acf, text);
	first = d2_GetWindowListItem(h, 1, io_AppendText(0x1ad0, 0x1ad2));
	d2_SetForm(h, 2);
	second = d2_GetWindowListItem(h, 2, io_AppendText(0x1ad1, 0x1ad3));
	d2_SetForm(h, 3);
	io_AppendText(0x1ad4);
	d2_CreateButtonRow(d2_CurrentWindowId, 0x1c, out, 2, g_14abe74, g_14abe78);
	sex0 = out[0];
	sex1 = out[1];
	d2_SetForm(h, 4);
	io_AppendText(0x1ad7);
	d2_CreateButtonRow(d2_CurrentWindowId, 0x1c, out, 2, g_14abe80, g_14abe84);
	faith1 = out[1];
	faith0 = out[0];
	d2_SetForm(h, 5);
	io_AppendText(0x1adb);
	cols = (*(int*) (d2_CurrentWindowId * 0x3cc + (int) d2_WindowMetricsView) - 0x20) / 0x30;
	group = d2_CreateRadioGroup(0);
	for (i = 0; i < 8; i++) {
		ids[i] = d2_AddElementToWindow((i % cols) * 0x30 + 0x50, (i / cols) * 0x30 + 0x20, i + 0x59a, d2_CurrentWindowId);
		((D2_CONTROL_TL*)d2_Controls)[ids[i]].value_058 = 1;
		((D2_CONTROL_TL*)d2_Controls)[ids[i]].value_038 = 0;
		((D2_CONTROL_TL*)d2_Controls)[ids[i]].value_03c = 0;
		((D2_CONTROL_TL*)d2_Controls)[ids[i]].value_060 = 1;
		((D2_CONTROL_TL*)d2_Controls)[ids[i]].flags_1d0 = 3;
		d2_AddToRadioGroup(group, ids[i]);
	}
	d2_SetForm(h, 6);
	elem6 = d2_GetWindowListItem(h, 6, io_AppendText(0x7e));
	d2_SetElementValue(first, g_7e23ea);
	d2_SetElementValue(second, g_7e240a);
	for (i = 0; i < 8; i++) {
		if (((D2_CONTROL_TL*)d2_Controls)[ids[i]].value_008 == g_7e23e4) {
			d2_SelectRadioGroup(group, i);
			break;
		}
	}
	d2_SetBildArgument(first, 0xc);
	d2_SetBildArgument(second, 0xc);
	w8 = d2_CreateRadioGroup(2, sex0, sex1);
	d2_SelectRadioGroup(w8, (*(int*) &g_7e23e8) & 0xff);
	w24 = d2_CreateRadioGroup(2, faith0, faith1);
	d2_SelectRadioGroup(w24, g_7e23e9 & 0xff);
	d2_ResetSelectionAndInput();
	io_LastKeyScancode = 0;
	for (i = 0; i < 8; i++)
		((D2_CONTROL_TL*)d2_Controls)[ids[i]].disabled = 0;
	for (p = 1; p < 9; p++) {
		ent = (int*) lb_LobbyPlayerList[p];
		if (ent != 0) {
			n = d3_GetSceneEntry((int) ent);
			if (n != 0) {
				if (*(int*) n != 0 && (int*) n != d2_LobbyLocalPlayerEntry) {
					((D2_CONTROL_TL*)d2_Controls)[ids[*(int*) (n + 0xc)]].disabled = 1;
					if (((D2_CONTROL_TL*)d2_Controls)[ids[*(int*) (n + 0xc)]].value_038 != 0) {
						((D2_CONTROL_TL*)d2_Controls)[ids[*(int*) (n + 0xc)]].value_038 = 0;
						((D2_CONTROL_TL*)d2_Controls)[ids[d2_LobbyLocalPlayerEntry[3]]].value_038 = 1;
					}
				}
			}
		}
	}
	for (;;) {
		if (tp_d3_SceneState[1] != 0) {
			tp_d3_SceneState[1] = 0;
			p = cm_RequestClearSceneEntries();
			while (!cm_GetCommandStatus(p)) {
				cm_StepCommandQueue();
			}
			lb_LobbyPlayerList = (int*) lb_GetPlayerList();
			for (i = 0; i < 8; i++)
				((D2_CONTROL_TL*)d2_Controls)[ids[i]].disabled = 0;
			for (p = 1; p < 9; p++) {
				ent = (int*) lb_LobbyPlayerList[p];
				if (ent != 0) {
					n = d3_GetSceneEntry((int) ent);
					if (n != 0) {
						if (*(int*) n != 0 && (int*) n != d2_LobbyLocalPlayerEntry) {
							((D2_CONTROL_TL*)d2_Controls)[ids[*(int*) (n + 0xc)]].disabled = 1;
							((D2_CONTROL_TL*)d2_Controls)[ids[*(int*) (n + 0xc)]].value_038 = 0;
						}
					}
				}
			}
		}
		if (io_RightButtonReleased != 0 || (d2_DialogButtonAction != -1 && d2_CurrentElementId == elem6) || io_LastKeyScancode == 1) {
			if (sel == 0) {
				d2_DialogCloseRequested = 1;
			} else {
				sel = sel - 1;
				redraw = 1;
			}
		}
		if (redraw) {
			for (i = 0; i < 5; i++) {
				int slot = d2_GetWindowListItem(h, 0, i);
				if (i <= sel)
					d2_SetSlotVisibility(slot, 1);
				else
					d2_SetSlotVisibility(slot, 0);
			}
			if (sel == 0)
				d2_SelectControl(first);
			else if (sel == 1)
				d2_SelectControl(second);
			redraw = 0;
		}
		if (sel == 0) {
			if (io_LastKeyScancode == 0x1c) {
				s = d2_GetControlValue(first);
				strcpy(g_7e23ea, s);
				sel = 1;
				redraw = 1;
				io_LastKeyScancode = 0;
			}
		}
		else if (sel == 1) {
			if (io_LastKeyScancode == 0x1c) {
				s = d2_GetControlValue(second);
				strcpy(g_7e240a, s);
				sel = 2;
				redraw = 1;
				io_LastKeyScancode = 0;
			}
		}
		else if (sel == 2) {
			d2_UpdateRadioGroup(w8);
			if (d2_DialogButtonAction != -1) {
				if (d2_CurrentElementId == sex0) {
					g_7e23e8 = 0;
					sel = 3;
					redraw = 1;
				}
				else if (d2_CurrentElementId == sex1) {
					g_7e23e8 = 1;
					sel = 3;
					redraw = 1;
				}
			}
		}
		else if (sel == 3) {
			d2_UpdateRadioGroup(w24);
			if (d2_DialogButtonAction != -1) {
				if (d2_CurrentElementId == faith0) {
					g_7e23e9 = 1;
					sel = 4;
					redraw = 1;
				}
				else if (d2_CurrentElementId == faith1) {
					g_7e23e9 = 0;
					sel = 4;
					redraw = 1;
				}
			}
		}
		else if (sel == 4) {
			d2_UpdateRadioGroup(group);
			if (io_LastKeyScancode == 0x1c) {
				sel = 5;
				redraw = 1;
			}
			if (d2_DialogButtonAction >= 0x59a && d2_DialogButtonAction < 0x5a2) {
				for (i = 0; i < 8; i++) {
					if ((char*)&((D2_CONTROL_TL*)d2_Controls)[ids[i]] != tp_d2_HoveredControl) {
						((D2_CONTROL_TL*)d2_Controls)[ids[i]].value_038 = 0;
						((D2_CONTROL_TL*)d2_Controls)[ids[i]].value_03c = 0;
						((D2_CONTROL_TL*)d2_Controls)[ids[i]].value_060 = 1;
					}
				}
				sel = sel + 1;
			}
		}
		else if (sel == 5) {
			g_7e23e0[0] = 0;
			(*(char *)&g_7e23e1) = 0;
			(*(char *)&g_7e23e2) = 0x12;
			g_7e23e4 = ((D2_CONTROL_TL*)d2_Controls)[g_102cbcc[group * 35 + d2_RadioGroupItems[group * 35]]].value_008;
			if (gm_SelectedMissionIndex == -1) {
				result = 1;
			}
			else {
				(void) *(volatile int*) &param;
				result = 1;
			}
			d2_DialogCloseRequested = 1;
		}
		if (main_RunFrameLoop((int (__cdecl*)(void)) 0x53d490, msg) == 0) {
			d2_ClearRadioGroup(w8);
			d2_ClearRadioGroup(w24);
			d2_ClearRadioGroup(group);
			d2_DestroyForm(h);
			WritePrivateProfileStringA("Network", "Name", g_7e23ea, g_7e22c0);
			WritePrivateProfileStringA("Network", "Familienname", g_7e240a, g_7e22c0);
			itoa(g_7e23e4 - 0x59a, digit, 10);
			WritePrivateProfileStringA("Network", "Wappen", digit, g_7e22c0);
			itoa((*(int*) &g_7e23e8) & 0xff, digit, 10);
			WritePrivateProfileStringA("Network", "Geschlecht", digit, g_7e22c0);
			itoa(g_7e23e9 & 0xff, digit, 10);
			WritePrivateProfileStringA("Network", "Glauben", digit, g_7e22c0);
			return result;
		}
	}
}
