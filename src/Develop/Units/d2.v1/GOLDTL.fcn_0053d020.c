extern int d2_CurrentWindowId;
extern char* g_1015ea0;
extern int g_100f1dc;
extern int g_100f1e4;
extern char g_1015f4c[];
extern char g_7e23e0[];
extern unsigned char g_7e23e1;
extern unsigned char g_7e23e2;
extern int g_7e23e4;
extern char g_7e23e8;
extern char g_7e23e9;
extern char g_7e23ea[];
extern char g_7e240a[];
#include "client_dialog_state.h"
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_AddElementToWindow(int, int, int, int);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl d2_CreateGuiWindow(int, char*);
int __cdecl d2_GetControlValue(int);
void __cdecl fcn_00476b60(void);
void __cdecl d2_DestroyForm(int);
int __cdecl main_RunFrameLoop(int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x0053d020 */
unsigned int __cdecl d2_ShowChoosePlayerDialog(int a0)
{
	int items[8];
	int sel;
	unsigned int changed;
	int win;
	int n;
	int i;
	int slot;
	int id;
	int w3;
	int w4;
	int elementAddress;
	int found;
	int r3;
	int r4;
	char* src;
	char* dst;
	char ch;

	sel = -1;
	changed = 0;
	win = d2_LoadForm(0, 0, "Menu\\CHOOSEPLAYER_NEW");
	d2_CenterDialogWindows(win);
	d2_SetForm(win, 1);
	io_AppendText(0x1acf, g_7e1d00);
	d2_SetForm(win, 2);
	n = (*(int*) (g_1015f4c + d2_CurrentWindowId * 0x3cc) - 0x20) / 0x30;
	for (i = 0; i < 8; i++) {
		slot = d2_AddElementToWindow((i % n) * 0x30, (i / n) * 0x30, i + 0x59a, d2_CurrentWindowId);
		items[i] = slot;
		((D2_CONTROL_TL*) g_1015ea0)[slot].value_058 = 1;
		((D2_CONTROL_TL*) g_1015ea0)[slot].value_038 = 0;
		((D2_CONTROL_TL*) g_1015ea0)[slot].value_03c = 0;
		((D2_CONTROL_TL*) g_1015ea0)[slot].value_060 = 1;
	}
	for (i = 0; i < 8; i++) {
		if (g_7e23e4 == i + 0x59a) {
			slot = items[i];
			((D2_CONTROL_TL*) g_1015ea0)[slot].disabled = 1;
			((D2_CONTROL_TL*) g_1015ea0)[slot].value_068 = 1;
			((D2_CONTROL_TL*) g_1015ea0)[slot].value_060 = 0;
			((D2_CONTROL_TL*) g_1015ea0)[slot].value_03c = 0;
		}
	}
	for (i = 0; i < 8; i++) {
		if (((D2_CONTROL_TL*) g_1015ea0)[items[i]].disabled == 0) {
			sel = items[i];
			((D2_CONTROL_TL*) g_1015ea0)[sel].value_038 = 1;
			((D2_CONTROL_TL*) g_1015ea0)[sel].value_03c = 1;
			break;
		}
	}
	d2_SetForm(win, 3);
	r3 = d2_GetWindowListItem(win, 3, io_AppendText((int) "%2mt", 0x489, 0x489));
	d2_SetForm(win, 4);
	r4 = d2_GetWindowListItem(win, 4, io_AppendText((int) "%2mt", 0x486, 0x486));
	w3 = d2_GetWindowListItem(win, 0, 3);
	w4 = d2_GetWindowListItem(win, 0, 5);
	*(unsigned int*) (d2_BildArgument2 + ((D2_CONTROL_TL*) g_1015ea0)[w3].value_088 * 0x160) = 0xc;
	*(unsigned int*) (d2_BildArgument2 + ((D2_CONTROL_TL*) g_1015ea0)[w4].value_088 * 0x160) = 0xc;
	if (g_7e23ea[0]) {
		d2_CreateGuiWindow(w3, g_7e23ea);
		d2_CreateGuiWindow(w4, g_7e240a);
		for (i = 0; i < 8; i++) {
			if (((D2_CONTROL_TL*) g_1015ea0)[items[i]].value_008 == g_7e23e4) {
				sel = items[i];
				((D2_CONTROL_TL*) g_1015ea0)[sel].value_038 = 1;
				((D2_CONTROL_TL*) g_1015ea0)[sel].value_03c = 1;
				break;
			}
		}
	}
	fcn_00476b60();
	id = main_RunFrameLoop((int) d2_ShowChoosePlayerDialog, a0);
	while (id) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc == 2) {
			g_7e23e0[0] = 0;
			g_7e23e1 = 0;
			g_7e23e2 = 0x12;
			g_7e23e4 = ((D2_CONTROL_TL*) g_1015ea0)[sel].value_008;
			g_7e23e8 = (char) (d2_GetControlValue(r3) + 'w');
			g_7e23e9 = (char) (d2_GetControlValue(r4) + 'z');
			src = (char*) d2_GetControlValue(w3);
			dst = g_7e23ea;
			do {
				ch = *src;
				src++;
				*dst = ch;
				dst++;
			} while (ch);
			src = (char*) d2_GetControlValue(w4);
			dst = g_7e240a;
			do {
				ch = *src;
				src++;
				*dst = ch;
				dst++;
			} while (ch);
			g_774654 = 1;
			changed = 1;
		} else if (g_100f1dc >= 0x59a && g_100f1dc < 0x5a2) {
			for (i = 0; i < 8; i++) {
				elementAddress = (int) &((D2_CONTROL_TL*) g_1015ea0)[items[i]];
				found = 0;
				if (elementAddress != g_100f1e4) {
					((D2_CONTROL_TL*) g_1015ea0)[items[i]].value_038 = 0;
					((D2_CONTROL_TL*) g_1015ea0)[items[i]].value_03c = 0;
					((D2_CONTROL_TL*) g_1015ea0)[items[i]].value_060 = 1;
				} else {
					sel = items[i];
					found = 1;
				}
			}
			if (!found) {
				((D2_CONTROL_TL*) g_1015ea0)[sel].value_038 = 1;
				((D2_CONTROL_TL*) g_1015ea0)[sel].value_03c = 1;
			}
		}
		id = main_RunFrameLoop((int) d2_ShowChoosePlayerDialog, a0);
	}
	d2_DestroyForm(win);
	return changed;
}
