#include <string.h>
#pragma intrinsic(memset)

typedef struct {
	int sel;
	int pad4[2];
	int id;
	int idx;
	int ent;
	int count;
} ListRow;
/* SIZE 0x1c */

extern char g_868060[];
extern char g_6aac84[];
extern char* g_1015ea0;
extern int g_10162e8;
extern int g_10162ec;
extern int g_10162f0;
extern int g_10162f4;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_100f1dc;
#include "client_dialog_state.h"
extern char* g_77255c;
extern int d2_CurrentWindowId;
extern int g_14ab738;
extern int g_14b5278;
extern char g_6b5c60[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl d2_DrawPanelFrame(int, int, int);
int __cdecl fcn_0046fac0(int, int, void*, int);
void __cdecl d2_CreateButtonRow(int, int, int*, int, ...);
int __cdecl gm_SumContainerCredits(int);
void __cdecl fcn_005a5760(void*, int, int, int);
void __cdecl d2_SetElementEnabled(int, int);
void __cdecl d2_DestroyForm(int);
void __cdecl d3_EndCameraAndUiMode(void);
int __cdecl he_StartHandlungSearch(int, int, int);
int __cdecl he_fn_Handlung(void);
void __cdecl ResetDisplayCounters(void);
int __cdecl fcn_005a5440(int, ListRow*, int, int, char);
int __cdecl d2_FindSelectedListRow(ListRow*);
int __cdecl fcn_005a66b0(char*, int, int, unsigned char);
void __cdecl d2_ClearSelectedControl(void);
void __cdecl fcn_00472380(int, int, int, int);
int __cdecl d2_CountActiveListRows(ListRow*);
void __cdecl d2_SetSlotVisibility(int, int);
int __cdecl fcn_00657a73(int, void*, int);
void __cdecl fcn_0046f940(int, void*);
void __cdecl d2_ScrollWindow(int, int, int);
void __cdecl fcn_005a6570(char*);
void __cdecl d2_ShowMoneyExchangeDialog(char*);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x005a6880 */
void __cdecl d2_RunGeldleiheWechselDialog(char* obj)
{
	ListRow list1[16];
	ListRow list2[16];
	int i;
	int h;
	int w1;
	int w2;
	int w3;
	int w4;
	int w0;
	int sel1;
	int sel2;
	int cur;
	int selected = -1;
	int cx;
	int cy;
	int cb;
	int d270;
	int label2;
	int buttons[2];
	char text[0x20];

	for (i = 0; i < 16; i++) {
		list2[i].sel = -1;
		list2[i].id = 0;
		list1[i].sel = -1;
		list1[i].id = 0;
	}
	for (i = 0; i < 4; i++) {
		if (g_868060[i * 0x2f4] != 0) {
			list1[i].id = *(unsigned short*) (g_868060 + i * 0x2f4 + 0x54);
			*(unsigned char*)&list1[i].idx = (unsigned char)i;
		}
	}
	h = fcn_00470820(0, 0, g_6aac84);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 0);
	d2_DrawPanelFrame(d2_CurrentWindowId, 0x73b, 0x73f);
	w2 = d2_GetWindowListItem(h, 0, 2);
	w3 = d2_GetWindowListItem(h, 0, 3);
	w1 = d2_GetWindowListItem(h, 0, 1);
	w0 = d2_GetWindowListItem(h, 0, 0);
	w4 = d2_GetWindowListItem(h, 0, 4);
	d2_SetForm(h, 0);
	cx = ((D2_CONTROL_TL*) (g_1015ea0))[w1].x - *(int*) (g_77255c + 4) + 2;
	cy = ((D2_CONTROL_TL*) (g_1015ea0))[w1].height -
	     *(int*) (g_77255c + 8) + ((D2_CONTROL_TL*) (g_1015ea0))[w1].y +
	     2;
	cb = fcn_0046fac0(cx, cy, g_6b5c60, d2_CurrentWindowId);
	cx = ((D2_CONTROL_TL*) (g_1015ea0))[w2].x - *(int*) (g_77255c + 4) + 2;
	cy = ((D2_CONTROL_TL*) (g_1015ea0))[w2].height -
	     *(int*) (g_77255c + 8) + ((D2_CONTROL_TL*) (g_1015ea0))[w2].y +
	     2;
	label2 = fcn_0046fac0(cx, cy, g_6b5c60, d2_CurrentWindowId);
	((D2_CONTROL_TL*) (g_1015ea0))[cb].font = 0x54;
	((D2_CONTROL_TL*) (g_1015ea0))[label2].font = 0x54;
	d2_SetForm(h, 0);
	i = d2_CurrentWindowId;
	*(int*) (0x10162e8 + i * 0x3cc) = 0xe;
	*(int*) (0x10162ec + i * 0x3cc) = 0x18;
	*(int*) (0x10162f0 + i * 0x3cc) = 0xe;
	*(int*) (0x10162f4 + i * 0x3cc) = 0xe;
	d2_SetForm(h, 1);
	io_AppendText(0x1900);
	d2_SetForm(h, 3);
	d2_CreateButtonRow(d2_CurrentWindowId, 0, buttons, 2, g_14ab738, g_14b5278);

	d270 = gm_SumContainerCredits(*(int*) (obj + 0x5d));
	if (d270 <= 0) {
		d2_SetForm(h, 5);
		io_AppendText(0x190a, obj);
	}
	fcn_005a5760(list1, h, 4, 0);
	for (i = 0; i < 16; i++) {
		if (list1[i].sel != -1)
			d2_SetElementEnabled(list1[i].sel, 0);
	}
	while (main_RunFrameLoop((void*) 0x5a6880, 0x677c7) != 0) {
		cur = he_StartHandlungSearch(1, 0, 0x27);
		if (cur != 0) {
			while (cur != 0 && *(int*) (cur + 0xac) != *(int*) (obj + 1))
				cur = he_fn_Handlung();
		}
		d2_SetForm(h, 2);
		io_AppendText(0x6811b0);
		io_AppendText(0x1902, *(int*) (obj + 0x69));
		if (cur == 0)
			io_AppendText(0x1903);
		else
			io_AppendText(0x1901, g_868060 + (unsigned char) ((char*) cur)[0xb0] * 0x2f4);
		if (g_14ce8e0 != 0)
			g_774654 = 1;
		ResetDisplayCounters();
		if (cur == 0) {
			selected = fcn_005a5440(*(int*) (obj + 0x5d), list2, h, 5, 1);
		}
		sel2 = d2_FindSelectedListRow(list1);
		if (cur == 0 && sel2 != -1 && selected != -1) {
			ResetDisplayCounters();
			if (fcn_005a66b0(obj, list2[selected].id, list2[selected].idx,
			             *(unsigned char*)&list1[sel2].idx)) {
				d2_ClearSelectedControl();
				for (i = 0; i < 16; i++) {
					if (list2[i].sel != -1)
						fcn_00472380(list2[i].sel, 0, 0, 0);
				}
			}
		}
		for (i = 0; i < 16; i++) {
			if (list1[i].sel != -1)
				d2_SetElementEnabled(list1[i].sel,
				             selected != -1 ? 1 : 0);
		}
		sel1 = d2_CountActiveListRows(list2);
		sel2 = d2_CountActiveListRows(list1);
		if (sel1 <= 4) {
			d2_SetSlotVisibility(w1, 0);
			d2_SetSlotVisibility(w0, 0);
			d2_SetSlotVisibility(cb, 0);
		} else {
			d2_SetSlotVisibility(w1, 1);
			d2_SetSlotVisibility(w0, 1);
			d2_SetSlotVisibility(cb, 1);
			fcn_00657a73(sel1, text, 0xa);
			fcn_0046f940(cb, text);
		}
		if (sel2 <= 4) {
			d2_SetSlotVisibility(w2, 0);
			d2_SetSlotVisibility(w3, 0);
			d2_SetSlotVisibility(label2, 0);
		} else {
			d2_SetSlotVisibility(w2, 1);
			d2_SetSlotVisibility(w3, 1);
			d2_SetSlotVisibility(label2, 1);
			fcn_00657a73(sel2, text, 0xa);
			fcn_0046f940(label2, text);
		}
		if (g_100f1dc == 3 || g_100f1dc == 4) {
			cur = d2_CurrentElementId;
			if (cur == w2) {
				d2_SetForm(h, 4);
				d2_ScrollWindow(0, -0x4c, d2_CurrentWindowId);
			} else if (cur == w3) {
				d2_SetForm(h, 4);
				d2_ScrollWindow(0, 0x4c, d2_CurrentWindowId);
			} else if (cur == w1) {
				d2_SetForm(h, 5);
				d2_ScrollWindow(0, -0x4c, d2_CurrentWindowId);
			} else if (cur == w0) {
				d2_SetForm(h, 5);
				d2_ScrollWindow(0, 0x4c, d2_CurrentWindowId);
			}
		}
		if (g_100f1dc == 2) {
			cur = d2_CurrentElementId;
			if (cur == buttons[0])
				fcn_005a6570(obj);
			else if (cur == buttons[1])
				d2_ShowMoneyExchangeDialog(obj);
		}
	}
	ResetDisplayCounters();
	d2_DestroyForm(h);
	d3_EndCameraAndUiMode();
}
