/* Dialog pump at 0x005a59d0. */

typedef struct {
	int sel;
	int pad4[2];
	int val;
	int pad10[1];
	int x14;
	int x18;
} Lrow;

extern int d2_CurrentWindowId;
extern char* g_77255c;
#include "Develop/Units/d2.v1/d2_gui.h"
#include "Develop/Units/d2.v1/d2_win.h"
extern char g_1015f40[];
extern char g_6b5c60[];
extern char g_6aac84[];
extern char g_6aac7c[];
extern char g_6aacac[];
extern int g_14ab710;
extern int g_14ab718;
extern int g_14ab6fc;
extern int g_14ce8e0;
extern char g_100f8c0;
extern int g_100f1dc;
#include "client_dialog_state.h"
#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char g_773d75;
extern int d2_CurrentElementId;
extern double g_6640e8;

void __cdecl ResetDisplayCounters(void);
int __cdecl CountDisplayCounters(void);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_DrawPanelFrame(int, int, int);
int __cdecl d2_ShowTxt(int, int, char*, int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00475220(char*);
int __cdecl io_AppendText(int, ...);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl fcn_00533a40(char*);
int __cdecl fcn_005a5440(int, void*, int, int, int);
int __cdecl fcn_005a5980(void*);
int __cdecl d2_CountActiveListRows(void*);
int __cdecl fcn_0046f940(int, char*);
void __cdecl fcn_0046ed00(int, int, int);
int __cdecl d2_SetSlotVisibility(int, int);
void __cdecl d2_SetElementImage(int, int);
void __cdecl d2_SetElementValue(int, ...);
void __cdecl d2_ClearSelectedControl(void);
int __cdecl fcn_00508620(int, int);
int __cdecl cm_GetCommandStatus(int);
int __cdecl cm_SendLogAction(char*);
int __cdecl cm_SendTraceEnd(char*);
int __cdecl cm_SendSellObjekt(int, int, int, int, unsigned char, int);
void __cdecl cm_BeginPacketFieldDelta(int, int);
void __cdecl cm_AppendPacketFieldDelta(int, int, int, int);
int __cdecl cm_RequestChangeAttribute(int);
int __cdecl d2_GetControlValue(int);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl fcn_00532ef0(void);
char* __cdecl itoa(int, char*, int);

/* ADDRESS: GOLDTL 0x005a59d0 */
int __cdecl d2_ShowMoneyExchangeDialog(char* a0)
{
	int v1, v2, v3, v4, v5, v6, v7, dialogId;
	int v17, v18, v19;
	int e0, e1, e2, e3, e4;
	int h1, h2;
	int v15, v16, v28, v29, v30, v31;
	Lrow ownRows[16];
	Lrow globRows[16];
	char buf[256];
	float value, fee, factor;

	v7 = 0;
	v31 = 0;
	do {
		*(int*)((char*)ownRows + v7) = -1;
		*(int*)((char*)ownRows + v7 + 0xc) = 0;
		*(int*)((char*)globRows + v7) = -1;
		*(int*)((char*)globRows + v7 + 0xc) = 0;
		v7 += 0x1c;
	} while (v7 < 0x1c0);
	dialogId = fcn_00470820(0, 0, g_6aac84);
	d2_CenterDialogWindows(dialogId);
	e2 = d2_GetWindowListItem(dialogId, 0, 2);
	e3 = d2_GetWindowListItem(dialogId, 0, 3);
	e1 = d2_GetWindowListItem(dialogId, 0, 1);
	e0 = d2_GetWindowListItem(dialogId, 0, 0);
	e4 = d2_GetWindowListItem(dialogId, 0, 4);
	d2_SetForm(dialogId, 0);
	d2_DrawPanelFrame(d2_CurrentWindowId, 0x73b, 0x73f);
	d2_SetForm(dialogId, 0);
	h1 = d2_ShowTxt((*(int*)(((char*)&((D2_CONTROL_TL*)g_1015ea0)[e1].x)) - *(int*)(g_77255c + 4)) + 2,
		(*(int*)(((char*)&((D2_CONTROL_TL*)g_1015ea0)[e1].height)) - *(int*)(g_77255c + 8)) + 2
			+ *(int*)(((char*)&((D2_CONTROL_TL*)g_1015ea0)[e1].y)),
		g_6b5c60, d2_CurrentWindowId);
	h2 = d2_ShowTxt((*(int*)(((char*)&((D2_CONTROL_TL*)g_1015ea0)[e2].x)) - *(int*)(g_77255c + 4)) + 2,
		(*(int*)(((char*)&((D2_CONTROL_TL*)g_1015ea0)[e2].height)) - *(int*)(g_77255c + 8)) + 2
			+ *(int*)(((char*)&((D2_CONTROL_TL*)g_1015ea0)[e2].y)),
		g_6b5c60, d2_CurrentWindowId);
	*(int*)(((char*)&((D2_CONTROL_TL*)g_1015ea0)[h1].font)) = 0x54;
	*(int*)(((char*)&((D2_CONTROL_TL*)g_1015ea0)[h2].font)) = 0x54;
	*(int*)(((char*)&((D2_CONTROL_TL*)g_1015ea0)[e4].value_054)) = 1;
	d2_SetForm(dialogId, 0);
	*(int*) &((D2_WIN*)g_1015f40)[d2_CurrentWindowId].pad3a8[0] = 0xe;
	*(int*) &((D2_WIN*)g_1015f40)[d2_CurrentWindowId].pad3a8[4] = 0x18;
	*(int*) &((D2_WIN*)g_1015f40)[d2_CurrentWindowId].pad3a8[8] = 0xe;
	*(int*) &((D2_WIN*)g_1015f40)[d2_CurrentWindowId].pad3a8[12] = 0xe;
	d2_SetForm(dialogId, 1);
	io_AppendText(0x18f5);
	d2_SetForm(dialogId, 2);
	io_AppendText(0x18f6, *(int*)(a0 + 0x69),
		*(unsigned short*)(g_773d75 * 0x2f4 + 0x8680b4) * 2 + 0x9a8, *(int*)(a0 + 0x6d));
	fcn_00475220(g_14ab6fc);
	d2_SetOverlayAnimation(0, 0);
	v29 = -1;
	do {
		if (g_14ce8e0) {
			if (CountDisplayCounters()) {
				d2_ClearSelectedControl();
				for (v15 = 0; v15 < 0x1c0; v15 += 0x1c) {
					if (*(int*)((char*)ownRows + v15) != -1)
						d2_SetElementValue(*(int*)((char*)ownRows + v15), 0, 0, 0);
					if (*(int*)((char*)globRows + v15) != -1)
						d2_SetElementValue(*(int*)((char*)globRows + v15), 0, 0, 0);
				}
			} else {
				g_774654 = 1;
			}
		}
		ResetDisplayCounters();
		if (v31 != 2) {
			v29 = fcn_005a5440(*(int*)(a0 + 0x5d), ownRows, dialogId, 5, 1);
			if (v29 != -1) {
				if (!g_100f8c0 || !v31) {
					io_FormatTextBuffer(buf, 0x18fa, ownRows[v29].x14, ownRows[v29].val * 2 + 0x9a8);
					fcn_00475220(buf);
				}
				v31 = 1;
				v30 = v29;
				d2_SetElementImage(e4, 0x4f8);
				goto label_image_done;
			}
		}
		v29 = fcn_005a5440(*(int*)(g_774970 * 0x21c + 0x7f4e18), globRows, dialogId, 4, 1);
		if (v29 == -1) {
			v30 = -1;
			v31 = 0;
			fcn_00475220(g_14ab6fc);
			d2_SetElementImage(e4, 0x4f7);
		} else {
			if (!g_100f8c0 || !v31) {
				io_FormatTextBuffer(buf, 0x18f8, globRows[v29].x14, globRows[v29].val * 2 + 0x9a8);
				fcn_00475220(buf);
			}
			v31 = 2;
			v30 = v29;
			d2_SetElementImage(e4, 0x4f9);
		}
	label_image_done:
		v15 = d2_CountActiveListRows(ownRows);
		v16 = d2_CountActiveListRows(globRows);
		if (!(v15 > 4)) {
			d2_SetSlotVisibility(e1, 0);
			d2_SetSlotVisibility(e0, 0);
			d2_SetSlotVisibility(h1, 0);
		} else {
			d2_SetSlotVisibility(e1, 1);
			d2_SetSlotVisibility(e0, 1);
			d2_SetSlotVisibility(h1, 1);
			itoa(v15, buf, 10);
			fcn_0046f940(h1, buf);
		}
		if (!(v16 > 4)) {
			d2_SetSlotVisibility(e2, 0);
			d2_SetSlotVisibility(e3, 0);
			d2_SetSlotVisibility(h2, 0);
		} else {
			d2_SetSlotVisibility(e2, 1);
			d2_SetSlotVisibility(e3, 1);
			d2_SetSlotVisibility(h2, 1);
			itoa(v16, buf, 10);
			fcn_0046f940(h2, buf);
		}
		if (g_100f1dc == 3 || g_100f1dc == 4) {
			if (d2_CurrentElementId == e2) {
				d2_SetForm(dialogId, 4);
				fcn_0046ed00(0, -0x4c, d2_CurrentWindowId);
			} else if (d2_CurrentElementId == e3) {
				d2_SetForm(dialogId, 4);
				fcn_0046ed00(0, 0x4c, d2_CurrentWindowId);
			} else if (d2_CurrentElementId == e1) {
				d2_SetForm(dialogId, 5);
				fcn_0046ed00(0, -0x4c, d2_CurrentWindowId);
			} else if (d2_CurrentElementId == e0) {
				d2_SetForm(dialogId, 5);
				fcn_0046ed00(0, 0x4c, d2_CurrentWindowId);
			}
		}
		if (v31 == 1) {
			v16 = fcn_005a5980(globRows);
			if (v16 != -1) {
				v2 = globRows[v16].val;
				v3 = ownRows[v30].val;
				if (v2 != v3) {
					v4 = ownRows[v30].x14;
					factor = (float) (*(int*)(a0 + 0x6d) * 0.01);
					value = (float) fcn_00508620(v4, v3);
					if (g_774970 != *(unsigned short*)(a0 + 0x27)) {
						fee = value * factor;
						v17 = fcn_00508620(1, v3);
						if (!((float) v17 < fee)) fee = (float) fcn_00508620(1, v3);
					} else fee = 0.0f;
					v17 = fcn_00508620(globRows[v16].x18, v2);
					if ((float) v17 < value) {
						io_FormatTextBuffer(buf, 0x18fd, v2 * 2 + 0x9a8);
						fcn_00475220(buf);
					} else {
						v28 = (int) value;
						v17 = fcn_00508620(v4, v3);
						cm_SendLogAction(g_6aac7c);
						cm_SendSellObjekt(-1, *(int*)(g_774970 * 0x21c + 0x7f4ca4), v2, v28, g_773d75, 0);
						cm_SendSellObjekt(*(int*)(g_774970 * 0x21c + 0x7f4ca4), -1, v3, (int) (v17 - fee), g_773d75, 0);
						cm_SendSellObjekt(-1, *(int*)(a0 + 1), v3, v17, g_773d75, 0);
						cm_SendSellObjekt(*(int*)(a0 + 1), -1, v2, (int) (v17 + fee), g_773d75, 0);
						v5 = cm_SendTraceEnd(g_6aac7c);
						while (!cm_GetCommandStatus(v5)) main_RunFrameLoop(0, 0x677c7);
						fcn_005a5440(*(int*)(g_774970 * 0x21c + 0x7f4e18), globRows, dialogId, 4, 1);
						fcn_005a5440(*(int*)(a0 + 0x5d), ownRows, dialogId, 5, 1);
						fcn_00533a40(g_14ab718);
						d2_ClearSelectedControl();
						for (v15 = 0; v15 < 0x1c0; v15 += 0x1c) {
							if (*(int*)((char*)ownRows + v15) != -1) d2_SetElementValue(*(int*)((char*)ownRows + v15), 0, 0, 0);
							if (*(int*)((char*)globRows + v15) != -1) d2_SetElementValue(*(int*)((char*)globRows + v15), 0, 0, 0);
						}
					}
				} else fcn_00475220(g_14ab710);
			}
		} else if (v31 == 2) {
			v16 = fcn_005a5980(ownRows);
			if (v16 != -1) {
				v2 = ownRows[v16].val;
				v3 = globRows[v30].val;
				if (v3 != v2) {
					v4 = globRows[v30].x14;
					v1 = ownRows[v16].x18 < v4 ? ownRows[v16].x18 : v4;
					value = (float) fcn_00508620(v1, v2);
					if (g_774970 != *(unsigned short*)(a0 + 0x27)) {
						fee = (float) (*(int*)(a0 + 0x6d) * 0.01 * value);
						v17 = fcn_00508620(1, v3);
						if (!((float) v17 < fee)) fee = (float) fcn_00508620(1, v3);
					} else fee = 0.0f;
					v17 = fcn_00508620(globRows[v30].x18, v3);
					if (!((float) v17 < value)) {
						fcn_00508620(v1, v3);
						cm_SendLogAction(g_6aac7c);
						v28 = (int) value;
						cm_SendSellObjekt(-1, *(int*)(g_774970 * 0x21c + 0x7f4ca4), v3, v28, g_773d75, 0);
						v17 = (int) (value - fee);
						cm_SendSellObjekt(*(int*)(g_774970 * 0x21c + 0x7f4ca4), -1, v2, v17, g_773d75, 0);
						cm_SendSellObjekt(-1, *(int*)(a0 + 1), v2, v17, g_773d75, 0);
						cm_SendSellObjekt(*(int*)(a0 + 1), -1, v3, v28, g_773d75, 0);
						v5 = cm_SendTraceEnd(g_6aac7c);
						while (!cm_GetCommandStatus(v5)) main_RunFrameLoop(0, 0x677c7);
						fcn_005a5440(*(int*)(g_774970 * 0x21c + 0x7f4e18), globRows, dialogId, 4, 1);
						fcn_005a5440(*(int*)(a0 + 0x5d), ownRows, dialogId, 5, 1);
						fcn_00533a40(g_14ab718);
						d2_ClearSelectedControl();
						for (v15 = 0; v15 < 0x1c0; v15 += 0x1c) {
							if (*(int*)((char*)ownRows + v15) != -1) d2_SetElementValue(*(int*)((char*)ownRows + v15), 0, 0, 0);
							if (*(int*)((char*)globRows + v15) != -1) d2_SetElementValue(*(int*)((char*)globRows + v15), 0, 0, 0);
						}
					} else {
						io_FormatTextBuffer(buf, 0x18fd, v2 * 2 + 0x9a8);
						fcn_00533a40(buf);
					}
				} else fcn_00533a40(g_14ab710);
			}
		}
	} while (main_RunFrameLoop(d2_ShowMoneyExchangeDialog, 0x677c7));
	ResetDisplayCounters();
	fcn_00471e30(dialogId);
	return fcn_00532ef0();
}
