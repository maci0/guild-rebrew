#include <string.h>
#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime; extern char gm_EntityIdField[];
extern int d2_DialogButtonAction, d2_CurrentElementId, io_RightButtonReleased, d2_DialogCloseRequested;

#include "Develop/Units/d2.v1/d2_gui.h"
extern int d2_CurrentWindowId;
extern s_1015f4c d2_WindowMetricsView[];
extern int d2_ObjektNameTable[];

typedef struct D2_HANDEL_SUCHEN_REQ {
	int f00;                    /* 0x00 */
	unsigned char kind;         /* 0x04 */
	unsigned char pad05[3];
	int f08;                    /* 0x08 */
	int f0c;                    /* 0x0c */
	unsigned char pad10[0x18];   /* 0x10 */
	int f28;                    /* 0x28 */
	int f2c;                    /* 0x2c */
	int f30;                    /* 0x30 */
	unsigned short f34;         /* 0x34 */
	unsigned char f36;          /* 0x36 */
	unsigned char pad37;
	unsigned int list[6];
	unsigned char pad50[8];
	unsigned char f58;          /* 0x58 */
	unsigned char pad59;
	unsigned short f5a;         /* 0x5a */
	unsigned char pad5c[4];
	int f60;                    /* 0x60 */
	unsigned char pad64[0x94];
} D2_HANDEL_SUCHEN_REQ;

int __cdecl gm_QueryEntities(int, int, ...);
int __cdecl d2_CheckOwnerBlocked(int);
int __cdecl he_StartHandlungSearch(int, int, int, int, int);
int __cdecl he_fn_Handlung(void);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_DrawPanelFrame(int, int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl d2_InitPlayerBar(int, int);
void __cdecl d2_ResetBuildingUiSlots(void);
int __cdecl d2_AddElementToWindow(int, int, int, int);
void __cdecl d2_SetControlText(int, int);
void __cdecl d2_SetElementEnabled(int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SyncWareProduktionSlotGrid(int, int);
void __cdecl d2_RefreshWorkshopInventoryGrids(int, int, int, int);
int __cdecl main_RunFrameLoop(int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl d3snd_PlayWorkerOrderVoice(void);
void __cdecl sv_ClearObjectSelection(void);
int __cdecl cm_SendCopyEntityData(void*);
int __cdecl cm_GetCommandStatus(int);
int __cdecl cm_GetCommandResult(int);
void __cdecl d2_ShowModalMessageBox(int, int);
void __cdecl d2_RestoreHudAfterDialog(void);
void __cdecl d2_DestroyForm(int);
void __cdecl d3_EndCameraAndUiMode(void);

/* ADDRESS: GOLDTL 0x0059ecc0 */
/* ADDRESS: GOLDDE 0x00583b40 */
void __cdecl d2_RunHandelSuchenDialog(int gebaeude, int a1)
{
	int i;
	int h;
	int x;
	int sel;
	int cnt;
	char* p;
	unsigned int ids[7];
	int y;
	int total;
	int handles[3];
	D2_HANDEL_SUCHEN_REQ req;
	char text[256];

	ids[0] = 0x1c1;
	ids[1] = 0x1c2;
	ids[2] = 0x1c3;
	ids[6] = gm_QueryEntities(*(int*) (gebaeude + 0x5d), 2, 6, 0, 0x2a);
	if (d2_CheckOwnerBlocked(gebaeude))
		return;
	for (i = 3; i < 6; i++) {
		ids[i] = 0;
	}
	h = he_StartHandlungSearch(2, 0, 0x15, 3, *(int*) (gebaeude + 1));
	while (h) {
		i = 0;
		do {
			if (*(unsigned short*) (h + 0xae) == ids[i]) {
				ids[i + 3] += *(unsigned char*) (h + 0xac);
				break;
			}
			i++;
		} while (i < 3);
		h = he_fn_Handlung();
	}
	total = d2_LoadForm(0, 0, (char*) 0x6a9750);
	d2_CenterDialogWindows(total);
	d2_SetForm(total, 0);
	d2_DrawPanelFrame(d2_CurrentWindowId, 0x70f, 0x741);
	d2_SetForm(total, 3);
	io_AppendText(0x1806);
	d2_InitPlayerBar(gebaeude, 0);
	d2_ResetBuildingUiSlots();
	d2_CenterDialogWindows(total);
	d2_SetForm(total, 2);
	y = -0x80 + *(int*) ((char*) d2_WindowMetricsView + d2_CurrentWindowId * 0x3cc) / 2;
	for (x = 0x19, cnt = 0; x < 0x109; x += 0x50, cnt++) {
		h = d2_AddElementToWindow(y, x, (int) ids[cnt] + 0xdf, d2_CurrentWindowId);
		*(unsigned int*)&((D2_CONTROL_TL*)d2_Controls)[h].value_05c = 1;
		*(unsigned int*)&((D2_CONTROL_TL*)d2_Controls)[h].flags_1d0 = 3;
		*(unsigned int*)&((D2_CONTROL_TL*)d2_Controls)[h].value_1dc = 100;
		*(unsigned int*)&((D2_CONTROL_TL*)d2_Controls)[h].value_1e0 = 0x10;
		*(unsigned int*)&((D2_CONTROL_TL*)d2_Controls)[h].font = 0x54;
		d2_SetControlText(h, d2_ObjektNameTable[(int) ids[cnt] * 2]);
		handles[cnt] = h;
		d2_SetElementEnabled(h, 1);
	}
	d2_SetOverlayAnimation(0, 0);
	d2_SyncWareProduktionSlotGrid(gebaeude, ids[6]);
	d2_RefreshWorkshopInventoryGrids(total, 1, 0, gebaeude);
	sel = main_RunFrameLoop(0x59ecc0, 0x677c7);
	while (sel) {
		d2_SyncWareProduktionSlotGrid(gebaeude, ids[6]);
		d2_RefreshWorkshopInventoryGrids(total, 1, 0, gebaeude);
		for (i = 3; i < 6; i++) {
			ids[i] = 0;
		}
		h = he_StartHandlungSearch(2, 0, 0x15, 3, *(int*) (gebaeude + 1));
		while (h) {
			i = 0;
			do {
				if (*(unsigned short*) (h + 0xae) == ids[i]) {
					ids[i + 3] += *(unsigned char*) (h + 0xac);
					break;
				}
				i++;
			} while (i < 3);
			h = he_fn_Handlung();
		}
		d2_SetForm(total, 2);
		for (i = 0; i < 3; i++) {
			d2_SetElementEnabled(handles[i], 1);
			if (ids[i + 3] == 1) {
				io_FormatTextBuffer(text, 0x1807, ids[i + 3], (int)ids[i] * 2 + 0x9a8);
			}
			else if ((int)ids[i + 3] > 1) {
				io_FormatTextBuffer(text, 0x1808, ids[i + 3], (int)ids[i] * 2 + 0x9a8);
			}
			else {
				io_FormatTextBuffer(text, 0x679060,
					(int) ids[i] * 2 + 0x9a8);
			}
			d2_SetControlText(handles[i], text);
		}
		if (d2_DialogButtonAction != -1) {
			for (sel = 0; sel < 3; sel++) {
				if (handles[sel] == d2_CurrentElementId)
					goto found;
			}
			goto skip_req;
		found:
			if (sel != -1) {
				memset(&req, 0, 0xf8);
				req.kind = 0x15;
				req.f36 = 1;
				req.f08 = *(int*) (*(unsigned short*) (gebaeude + 0x27) * 0x21c
					+ gm_EntityIdField);
				req.f0c = *(int*) (gebaeude + 1);
				*(pos14_7f4c00*)&req.f28 = gm_GameTime;

				req.f5a = (unsigned short) ids[sel];
				req.f60 = *(int*) (a1 + 2);
				cnt = 0;
				p = gm_EntityIdField;
				do {
					if (cnt >= 6)
						break;
					if (p[0x184] != 0) {
						req.list[cnt] = *(unsigned int*) p;
						cnt++;
					}
					p += 0x21c;
				} while ((int) p < 0x85a0a4);
				for (i = cnt; i < 6; i++) {
					req.list[i] = -1;
				}
				req.f58 = (unsigned char) cnt;
				if (cnt != 0) {
					d3snd_PlayWorkerOrderVoice();
					sv_ClearObjectSelection();
					sel = cm_SendCopyEntityData(&req);
					while (!cm_GetCommandStatus(sel)) {
						main_RunFrameLoop(0, 0x20007);
					}
					cm_GetCommandResult(sel);
				}
				else {
					d2_ShowModalMessageBox(*(int*) 0x14ab324, 4);
				}
			}
		skip_req: ;
		}
		else if (io_RightButtonReleased != 0)
			d2_DialogCloseRequested = 1;
		sel = main_RunFrameLoop(0x59ecc0, 0x677c7);
	}
	sv_ClearObjectSelection();
	d2_RestoreHudAfterDialog();
	d2_DestroyForm(total);
	return d3_EndCameraAndUiMode();
}
