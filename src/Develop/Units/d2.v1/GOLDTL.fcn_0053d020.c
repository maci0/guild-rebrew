extern int d2_CurrentWindowId;
extern char* g_1015ea0;
extern int g_100f1dc;
#include "client_dialog_state.h"
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, char*);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_00472380(int, char*);
int __cdecl fcn_00471f80(int);
void __cdecl fcn_00476b60(void);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_005373e0(int, int);
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
	int v;
	int elementAddress;
	int found;
	unsigned int r3;
	unsigned int r4;
	char* src;
	char* dst;
	char ch;

	sel = -1;
	changed = 0;
	win = fcn_00470820(0, 0, (char*) 0x6a3fc8);
	d2_CenterDialogWindows(win);
	d2_SetForm(win, 1);
	io_AppendText(0x1acf, (char*) 0x7e1d00);
	d2_SetForm(win, 2);
	n = (*(int*) (d2_CurrentWindowId * 0x3cc + 0x1015f4c) - 0x20) / 0x30;
	i = 0;
	do {
		slot = fcn_0046f740((i % n) * 0x30, (i / n) * 0x30, i + 0x59a, d2_CurrentWindowId);
		items[i] = slot;
		v = slot * 0x2f4;
		i++;
		*(unsigned int*) (&(*(D2_CONTROL_TL*) ((char*) ((int) g_1015ea0) + v)).value_058) = 1;
		*(unsigned int*) (&(*(D2_CONTROL_TL*) ((char*) ((int) g_1015ea0) + v)).value_038) = 0;
		*(unsigned int*) (&(*(D2_CONTROL_TL*) ((char*) ((int) g_1015ea0) + v)).value_03c) = 0;
		*(unsigned int*) (&(*(D2_CONTROL_TL*) ((char*) ((int) g_1015ea0) + v)).value_060) = 1;
	} while (i < 8);
	i = 0;
	do {
		if (*(int*) 0x7e23e4 == i + 0x59a) {
			v = items[i] * 0x2f4;
			*(unsigned int*) (&(*(D2_CONTROL_TL*) ((char*) ((int) g_1015ea0) + v)).disabled) = 1;
			*(unsigned int*) (&(*(D2_CONTROL_TL*) ((char*) ((int) g_1015ea0) + v)).value_068) = 1;
			*(unsigned int*) (&(*(D2_CONTROL_TL*) ((char*) ((int) g_1015ea0) + v)).value_060) = 0;
			*(unsigned int*) (&(*(D2_CONTROL_TL*) ((char*) ((int) g_1015ea0) + v)).value_03c) = 0;
		}
		i++;
	} while (i < 8);
	i = 0;
	do {
		if (((D2_CONTROL_TL*) (g_1015ea0))[items[i]].disabled == 0) {
			sel = items[i];
			*(unsigned int*) (&((D2_CONTROL_TL*) ((int) g_1015ea0))[sel].value_038) = 1;
			*(unsigned int*) (&((D2_CONTROL_TL*) ((int) g_1015ea0))[sel].value_03c) = 1;
			break;
		}
		i++;
	} while (i < 8);
	d2_SetForm(win, 3);
	r3 = fcn_00472250(win, 3, io_AppendText(0x489, (char*) 0x6a3fc0));
	d2_SetForm(win, 4);
	r4 = fcn_00472250(win, 4, io_AppendText(0x486, (char*) 0x6a3fc0));
	w3 = fcn_00472250(win, 0, 3);
	w4 = fcn_00472250(win, 0, 5);
	*(unsigned int*) (((D2_CONTROL_TL*) (g_1015ea0))[w3].value_088 * 0x160 + 0x102d158) = 0xc;
	*(unsigned int*) (((D2_CONTROL_TL*) (g_1015ea0))[w4].value_088 * 0x160 + 0x102d158) = 0xc;
	if (*(char*) 0x7e23ea) {
		fcn_00472380(w3, (char*) 0x7e23ea);
		fcn_00472380(w4, (char*) 0x7e240a);
		i = 0;
		do {
			if (((D2_CONTROL_TL*) (g_1015ea0))[items[i]].value_008 == *(int*) 0x7e23e4) {
				sel = items[i];
				*(unsigned int*) (&((D2_CONTROL_TL*) ((int) g_1015ea0))[sel].value_038) = 1;
				*(unsigned int*) (&((D2_CONTROL_TL*) ((int) g_1015ea0))[sel].value_03c) = 1;
				break;
			}
			i++;
		} while (i < 8);
	}
	fcn_00476b60();
	id = fcn_005373e0(0x53d020, a0);
	while (id) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc == 2) {
			*(char*) 0x7e23e0 = 0;
			*(char*) 0x7e23e1 = 0;
			*(char*) 0x7e23e2 = 0x12;
			*(int*) 0x7e23e4 = ((D2_CONTROL_TL*) (g_1015ea0))[sel].value_008;
			*(char*) 0x7e23e8 = (char) (fcn_00471f80(r3) + 'w');
			*(char*) 0x7e23e9 = (char) (fcn_00471f80(r4) + 'z');
			src = (char*) fcn_00471f80(w3);
			dst = (char*) 0x7e23ea;
			do {
				ch = *src;
				src++;
				*dst = ch;
				dst++;
			} while (ch);
			src = (char*) fcn_00471f80(w4);
			dst = (char*) 0x7e240a;
			do {
				ch = *src;
				src++;
				*dst = ch;
				dst++;
			} while (ch);
			g_774654 = 1;
			changed = 1;
		} else if (g_100f1dc >= 0x59a && g_100f1dc < 0x5a2) {
			i = 0;
			do {
				elementAddress = (int) &((D2_CONTROL_TL*) g_1015ea0)[items[i]];
				found = 0;
				if (elementAddress == *(int*) 0x100f1e4) {
					sel = items[i];
					found = 1;
				} else {
					*(unsigned int*) (&((D2_CONTROL_TL*) (g_1015ea0))[items[i]].value_038) = 0;
					*(unsigned int*) (&((D2_CONTROL_TL*) (g_1015ea0))[items[i]].value_03c) = 0;
					*(unsigned int*) (&((D2_CONTROL_TL*) (g_1015ea0))[items[i]].value_060) = 1;
				}
				i++;
			} while (i < 8);
			if (!found) {
				*(unsigned int*) (&((D2_CONTROL_TL*) ((int) g_1015ea0))[sel].value_038) = 1;
				*(unsigned int*) (&((D2_CONTROL_TL*) ((int) g_1015ea0))[sel].value_03c) = 1;
			}
		}
		id = fcn_005373e0(0x53d020, a0);
	}
	fcn_00471e30(win);
	return changed;
}
