#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d2_CurrentWindowId;
extern char* d2_Controls;
extern int d2_DialogButtonAction;
extern int d2_DialogCloseRequested;

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(char* fmt, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl d2_CreateRadioGroup(int);
int __cdecl d2_CreateWindowTextButton(int, int, int);
char* __cdecl fcn_00502cd0(int, int, int, ...);
void __cdecl d2_AddToRadioGroup(int, int);
void __cdecl d2_SelectRadioGroup(int, int);
void __cdecl d2_ResetSelectionAndInput(void);
int __cdecl d2_ClearWindowChildren(int, int);
int __cdecl d2_GetFormWindow(int, int);
int __cdecl d2_AddElementToWindow(int, int, int, int);
void __cdecl d2_ClearRadioGroup(int);
void __cdecl d2_DestroyForm(int);
void __cdecl io_ClearInputState(void);
void* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl main_RunFrameLoop(void* fn, int arg);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x004bec20 */
unsigned int __cdecl d2_ChooseRoutingGood(int a0, int a1, unsigned int a2)
{
	int handles[7];
	int ids[7];
	int list[0x30];
	int items[0x30];
	int g;
	int closeButton;
	int v6;
	unsigned int v7;
	unsigned int selection;
	int v18;
	int v2;
	int i;
	int k;
	int n;
	char* p;
	char* p2;

	selection = a2;
	v2 = 1;
	v18 = -1;
	ids[0] = 0x95;
	ids[1] = 0x92;
	ids[2] = 0x93;
	ids[3] = 0x94;
	ids[4] = 0x97;
	ids[5] = 0x96;
	ids[6] = 0x2db;
	g = d2_LoadForm(0, 0, "misc\\routing_choose_good_enhanced");
	d2_CenterDialogWindows(g);
	d2_SetForm(g, 1);
	io_AppendText("$Z%2N3$A%1G", *(unsigned short*) (a0 + 0x27), a0);
	d2_SetForm(g, 4);
	closeButton = d2_GetWindowListItem(g, 4, io_AppendText(0x7d));
	d2_SetForm(g, 3);
	k = d2_CreateRadioGroup(0);
	for (i = 0; i < 7; i++) {
		v6 = d2_CreateWindowTextButton(0, 4 + i * 0x1e, *(int*) (0x14a56e8 + i * 4));
		handles[i] = v6;
		v7 = fcn_00502cd0(*(int*) (a0 + 0x5d), 2, 6, 0, *(int*) (ids + i));
		*(int*) (&((D2_CONTROL_TL*) (d2_Controls))[v6].associated_object) = v7;
		d2_AddToRadioGroup(k, v6);
	}
	d2_SelectRadioGroup(k, 0);
	d2_ResetSelectionAndInput();
	for (;;) {
		n = k * 0x8c;
		if (io_RightButtonReleased != 0 || selection != 0 || (d2_DialogButtonAction != -1 && d2_CurrentElementId == closeButton)) {
			d2_DialogCloseRequested = 1;
		}
		if (*(int*) (0x102cbc8 + n) != v18 || v2) {
			d2_SetForm(g, 2);
			d2_ClearWindowChildren(d2_GetFormWindow(g, 2), 0);
			for (i = 0; i < 0x30; i++) {
				list[i] = -1;
			}
			i = 0;
			v6 = *(int*) (&((D2_CONTROL_TL*) (d2_Controls))[handles[*(int*) (0x102cbc8 + n)]].associated_object);
			if (v6 != 0) {
				v7 = *(unsigned int*) (v6 + 0x14);
			} else {
				v7 = *(unsigned int*) (a0 + 0x5d);
			}
			p = fcn_00502cd0(v7, 1, 0, 0xff);
			if (p != 0) {
				p2 = fcn_00502cd0(*(unsigned int*) (p + 0x14), 1, 5, 0);
				while (p2 != 0) {
					v6 = d2_AddElementToWindow((i % 4) * 0x40, (i / 4) * 0x40, *(unsigned short*) p2 + 0xdf, d2_CurrentWindowId);
					list[i] = v6;
					((D2_CONTROL_TL*) (d2_Controls))[v6].value_05c = 1;
					((D2_CONTROL_TL*) (d2_Controls))[v6].flags_1d0 = 3;
					((D2_CONTROL_TL*) (d2_Controls))[v6].value_1e4 = 0x525;
					items[i] = *(unsigned short*) p2;
					p2 = (char*) gm_NextEntityQueryMatch();
					i++;
				}
			}
			items[i] = 0;
			v6 = d2_AddElementToWindow((i % 4) * 0x40 + 7, (i / 4) * 0x40 + 7, 0x527, d2_CurrentWindowId);
			list[i] = v6;
			v2 = 0;
			((D2_CONTROL_TL*) (d2_Controls))[v6].value_05c = 1;
			((D2_CONTROL_TL*) (d2_Controls))[v6].flags_1d0 = 3;
			v18 = *(int*) (0x102cbc8 + n);
		}
		if (d2_DialogButtonAction != -1) {
			for (i = 0; i < 0x30; i++) {
				if (d2_CurrentElementId == list[i]) {
					selection = items[i];
					break;
				}
			}
		}
		if (!main_RunFrameLoop((void*) 0x4bec20, 0x657c7)) {
			d2_ClearRadioGroup(k);
			d2_DestroyForm(g);
			io_ClearInputState();
			return selection;
		}
	}
}
