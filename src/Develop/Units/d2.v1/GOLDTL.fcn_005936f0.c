#include <windows.h>
#include <string.h>

extern char g_7e22c0[];      /* ini file path */
extern char g_7e23ea[];      /* first name buffer (0x20) */
extern char g_7e240a[];      /* family name buffer (0x20) */
extern char g_14cf950;       /* last pressed key */
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_100f1dc;        /* focused element id */
#include "client_dialog_state.h"
extern int* g_774a34;        /* entity list head */
extern int* g_779cb8;        /* rejected entity */
extern int* g_779ce4;
extern char* g_100f1e4;      /* element of the current player */
extern int g_102cbc8[];
extern int g_102cbcc[];
extern char g_1015f4c[];
extern char g_7e23e0;
extern unsigned char g_7e23e1; extern unsigned char g_7e23e2;
extern int g_7e23e4;
extern char g_7e23e8;
extern char g_7e23e9;
extern signed char g_6a3440;
extern int g_14abe74;
extern int g_14abe78;
extern int g_14abe80;
extern int g_14abe84;
#include "Develop/Units/d2.v1/d2_gui.h"

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl fcn_00517b10(char*, char*);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00533a60(int, int, int*, int, ...);
int __cdecl d2_CreateRadioGroup(int, ...);
int __cdecl fcn_0046f740(int, int, int, int);
void __cdecl fcn_00469470(int, int);
void __cdecl d2_SelectRadioGroup(int, int);
void __cdecl d2_SetBildArgument(int, int);
void __cdecl fcn_00476b60(void);
void __cdecl d2_SelectControl(int);
int __cdecl d2_SetSlotVisibility(int, int);
char* __cdecl fcn_00471f80(int);
void __cdecl fcn_00471e30(int);
void __cdecl d2_ClearRadioGroup(int);
void __cdecl d2_UpdateRadioGroup(int);
int __cdecl fcn_004ce190(int);
int __cdecl fcn_004ce1d0(void);
int __cdecl fcn_004c4450(int);
int __cdecl fcn_004ce180(void);
void __cdecl fcn_00535960(void);
int __cdecl fcn_005373e0(int (__cdecl*)(void), int);
char* __cdecl itoa(int, char*, int);


/* Player name editor: loads the stored name, religion, sex and crest, lays out
 * the eight crest buttons and runs the modal edit loop until the dialog
 * closes, then writes the selected name back to the ini file. */
/* ADDRESS: GOLDTL 0x005936f0 */
int __cdecl fcn_005936f0(int msg, int param)
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
	h = fcn_00470820(0, 0, "Menu\\CHOOSEPLAYER");
	d2_CenterDialogWindows(h);
	fcn_00517b10((char*) 0x9baa76, text);
	d2_SetForm(h, 1);
	io_AppendText(0x1acf, text);
	first = fcn_00472250(h, 1, io_AppendText(0x1ad0, 0x1ad2));
	d2_SetForm(h, 2);
	second = fcn_00472250(h, 2, io_AppendText(0x1ad1, 0x1ad3));
	d2_SetForm(h, 3);
	io_AppendText(0x1ad4);
	fcn_00533a60(d2_CurrentWindowId, 0x1c, out, 2, g_14abe74, g_14abe78);
	sex0 = out[0];
	sex1 = out[1];
	d2_SetForm(h, 4);
	io_AppendText(0x1ad7);
	fcn_00533a60(d2_CurrentWindowId, 0x1c, out, 2, g_14abe80, g_14abe84);
	faith1 = out[1];
	faith0 = out[0];
	d2_SetForm(h, 5);
	io_AppendText(0x1adb);
	cols = (*(int*) (d2_CurrentWindowId * 0x3cc + (int) g_1015f4c) - 0x20) / 0x30;
	group = d2_CreateRadioGroup(0);
	for (i = 0; i < 8; i++) {
		ids[i] = fcn_0046f740((i % cols) * 0x30 + 0x50, (i / cols) * 0x30 + 0x20, i + 0x59a, d2_CurrentWindowId);
		((D2_CONTROL_TL*)g_1015ea0)[ids[i]].value_058 = 1;
		((D2_CONTROL_TL*)g_1015ea0)[ids[i]].value_038 = 0;
		((D2_CONTROL_TL*)g_1015ea0)[ids[i]].value_03c = 0;
		((D2_CONTROL_TL*)g_1015ea0)[ids[i]].value_060 = 1;
		((D2_CONTROL_TL*)g_1015ea0)[ids[i]].flags_1d0 = 3;
		fcn_00469470(group, ids[i]);
	}
	d2_SetForm(h, 6);
	elem6 = fcn_00472250(h, 6, io_AppendText(0x7e));
	d2_SetElementValue(first, g_7e23ea);
	d2_SetElementValue(second, g_7e240a);
	for (i = 0; i < 8; i++) {
		if (((D2_CONTROL_TL*)g_1015ea0)[ids[i]].value_008 == g_7e23e4) {
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
	fcn_00476b60();
	g_14cf950 = 0;
	for (i = 0; i < 8; i++)
		((D2_CONTROL_TL*)g_1015ea0)[ids[i]].disabled = 0;
	for (p = 1; p < 9; p++) {
		ent = (int*) g_774a34[p];
		if (ent != 0) {
			n = fcn_004ce190((int) ent);
			if (n != 0) {
				if (*(int*) n != 0 && (int*) n != g_779cb8) {
					((D2_CONTROL_TL*)g_1015ea0)[ids[*(int*) (n + 0xc)]].disabled = 1;
					if (((D2_CONTROL_TL*)g_1015ea0)[ids[*(int*) (n + 0xc)]].value_038 != 0) {
						((D2_CONTROL_TL*)g_1015ea0)[ids[*(int*) (n + 0xc)]].value_038 = 0;
						((D2_CONTROL_TL*)g_1015ea0)[ids[g_779cb8[3]]].value_038 = 1;
					}
				}
			}
		}
	}
	for (;;) {
		if (g_779ce4[1] != 0) {
			g_779ce4[1] = 0;
			p = fcn_004ce1d0();
			while (!fcn_004c4450(p)) {
				fcn_00535960();
			}
			g_774a34 = (int*) fcn_004ce180();
			for (i = 0; i < 8; i++)
				((D2_CONTROL_TL*)g_1015ea0)[ids[i]].disabled = 0;
			for (p = 1; p < 9; p++) {
				ent = (int*) g_774a34[p];
				if (ent != 0) {
					n = fcn_004ce190((int) ent);
					if (n != 0) {
						if (*(int*) n != 0 && (int*) n != g_779cb8) {
							((D2_CONTROL_TL*)g_1015ea0)[ids[*(int*) (n + 0xc)]].disabled = 1;
							((D2_CONTROL_TL*)g_1015ea0)[ids[*(int*) (n + 0xc)]].value_038 = 0;
						}
					}
				}
			}
		}
		if (g_14ce8e0 != 0 || (g_100f1dc != -1 && d2_CurrentElementId == elem6) || g_14cf950 == 1) {
			if (sel == 0) {
				g_774654 = 1;
			} else {
				sel = sel - 1;
				redraw = 1;
			}
		}
		if (redraw) {
			for (i = 0; i < 5; i++) {
				int slot = fcn_00472250(h, 0, i);
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
			if (g_14cf950 == 0x1c) {
				s = fcn_00471f80(first);
				strcpy(g_7e23ea, s);
				sel = 1;
				redraw = 1;
				g_14cf950 = 0;
			}
		}
		else if (sel == 1) {
			if (g_14cf950 == 0x1c) {
				s = fcn_00471f80(second);
				strcpy(g_7e240a, s);
				sel = 2;
				redraw = 1;
				g_14cf950 = 0;
			}
		}
		else if (sel == 2) {
			d2_UpdateRadioGroup(w8);
			if (g_100f1dc != -1) {
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
			if (g_100f1dc != -1) {
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
			if (g_14cf950 == 0x1c) {
				sel = 5;
				redraw = 1;
			}
			if (g_100f1dc >= 0x59a && g_100f1dc < 0x5a2) {
				for (i = 0; i < 8; i++) {
					if ((char*)&((D2_CONTROL_TL*)g_1015ea0)[ids[i]] != g_100f1e4) {
						((D2_CONTROL_TL*)g_1015ea0)[ids[i]].value_038 = 0;
						((D2_CONTROL_TL*)g_1015ea0)[ids[i]].value_03c = 0;
						((D2_CONTROL_TL*)g_1015ea0)[ids[i]].value_060 = 1;
					}
				}
				sel = sel + 1;
			}
		}
		else if (sel == 5) {
			g_7e23e0 = 0;
			(*(char *)&g_7e23e1) = 0;
			(*(char *)&g_7e23e2) = 0x12;
			g_7e23e4 = ((D2_CONTROL_TL*)g_1015ea0)[g_102cbcc[group * 35 + g_102cbc8[group * 35]]].value_008;
			if (g_6a3440 == -1) {
				result = 1;
			}
			else {
				(void) *(volatile int*) &param;
				result = 1;
			}
			g_774654 = 1;
		}
		if (fcn_005373e0((int (__cdecl*)(void)) 0x53d490, msg) == 0) {
			d2_ClearRadioGroup(w8);
			d2_ClearRadioGroup(w24);
			d2_ClearRadioGroup(group);
			fcn_00471e30(h);
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
