#include <string.h>
#include "Develop/DieGildeAddOn/game/object_prototype.h"
extern int d2_CurrentWindowId;
extern char* lpObjektePROT;
extern char* d2_Controls;
extern int d2_DialogButtonAction;
extern int g_100f884;
extern int d2_CurrentElementId;
extern int sv_SelectedBuilding;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int io_RightButtonReleased;
extern int g_7798a0;
extern int gm_GameTime;
extern int gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned short g_7f3ee4;

int __cdecl d2_CheckOwnerBlocked(int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_InitPlayerBar(char*, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int);
void __cdecl d2_ResetBuildingUiSlots(void);
void __cdecl d2_DrawPanelFrame(int, int, int);
int __cdecl d2_GetFormWindow(int, int, int, int*, int*, int*);
void __cdecl d2_CreateWindowScrollbar(int, int, int, int);
int __cdecl gm_QueryEntities(int, int, ...);
int __cdecl he_StartHandlungSearch(int, int, int, int, int);
int __cdecl he_fn_Handlung(void);
void __cdecl d3snd_PlayWorkerOrderVoice(void);
int __cdecl cm_SendCopyEntityData(void*);
int __cdecl cm_GetCommandStatus(int);
int __cdecl cm_GetCommandResult(int);
int __cdecl main_RunFrameLoop(int, int);
void __cdecl he_AssignActionSlot(char*, int, int, int);
void __cdecl gm_CollectTradeItemsByKind(char*);
void __cdecl d3_EndCameraAndUiMode(void);
int __cdecl gm_GetMsgField(int, int);
void __cdecl d2_SetLabelText(int, char*);
void __cdecl d2_RenderProduktionStockRows(int, int, int, int, int);
void __cdecl d2_SyncWareProduktionSlotGrid(char*, int);
void __cdecl d2_RefreshWorkshopInventoryGrids(int, int, int, char*);
void __cdecl d2_DestroyForm(int);
void __cdecl d2_RestoreHudAfterDialog(void);
char* __cdecl itoa(int, char*, int);

typedef struct {
	int kind;
	char flag4;
	char pad5[3];
	int f8;
	int f12;
	int f16;
	int f20;
	char pad18[0x10];
	int c28;
	int c2c;
	int c30;
	unsigned short c34;
	char flag36;
	char pad37[0x21];
	unsigned short id;
	char pad5a[2];
	int neg5c;
	char pad60[8];
	int f68;
	int f6c;
	char pad70[0x88];
} Req_59c000;
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x0059c000 */
/* ADDRESS: GOLDDE 0x005812a0 */
int __cdecl d2_RunMetalProduktionDialog(char* building)
{
	Req_59c000 req;
	char buf[8];
	int v15;
	int v16;
	int item;
	int h;
	int q;
	int t;
	int found;
	int i;
	int k;
	int j;
	int m;
	int count;
	int any;
	int sel;
	int* p;
	int* rows;
	int* ep;
	int* acc;
	char* row;

	if (d2_CheckOwnerBlocked((int) building))
		return 0;
	h = d2_LoadForm(0, 0, "Handel\\Handel_PRODUKTION");
	d2_CenterDialogWindows(h);
	d2_InitPlayerBar(building, 0);
	d2_SetForm(h, 3);
	io_AppendText(0xcb);
	d2_ResetBuildingUiSlots();
	count = 0;
	d2_SetForm(h, 0);
	p = (int*) (0x10162e8 + d2_CurrentWindowId * 0x3cc);
	p[0] = 0xe;
	p[1] = 0xe;
	p[2] = 0xe;
	p[3] = 0xe;
	d2_DrawPanelFrame(d2_CurrentWindowId, 0x70b, 0x742);
	d2_CreateWindowScrollbar(0x270, 0x15e, d2_CurrentWindowId, d2_GetFormWindow(h, 2, 0x78, &v16, &v15, &item));
	*(unsigned int*) (&((D2_CONTROL_TL*) (d2_Controls))[item].font) = 0x54;
	do {
		d2_SetForm(h, 2);
		t = gm_QueryEntities(*(unsigned int*) (building + 0x5d), 2, 6, 0, 0xff);
		if (!t)
			return 0;
		q = gm_QueryEntities(*(unsigned int*) (building + 0x5d), 2, 6, 0, 0x2a);
		if (!q)
			return 0;
		if ((d2_DialogButtonAction != -1) && (g_100f884 == h)) {
			any = 0;
			p = (int*) 0x7e30e0;
			do {
				if ((int) p >= 0x7e35e0)
					break;
				if (p[-4] == 0xffff)
					break;
				if (*p)
					any = 1;
				p += 10;
			} while (!any);
			if (count > 0) {
				rows = (int*) 0x7798c0;
				for (k = 0; k < count; k++) {
					if (d2_CurrentElementId == *(int*) (0x779194 + k * 0x58)) {
						if (any == 0) {
							p = (int*) 0x7e30d0;
							do {
								if (*p == 0xffff)
									break;
								row = *(char**) (*p * 0x21c + 0x7f4e1c);
								if (row && (*row == 4) && (*(int*) (row + 0x10) == *(int*) (building + 1)) && (*(unsigned short*) (row + 0xac) == *(unsigned int*) (0x779160 + k * 0x58)))
									*(char*) (*p * 0x21c + 0x7f4e28) = 1;
								p += 10;
							} while ((int) p < 0x7e35d0);
						} else {
							found = he_StartHandlungSearch(2, 0, 4, 3, *(unsigned int*) (building + 1));
							while (found) {
								if (*(unsigned short*) (found + 0xac) == *rows)
									goto located;
								found = he_fn_Handlung();
							}
							d3snd_PlayWorkerOrderVoice();
							memset(&req, 0, sizeof(req));
							req.flag4 = 4;
							if (*(unsigned short*) (building + 0x27) != 0xffff)
								req.f8 = *(unsigned int*) (*(unsigned short*) (building + 0x27) * 0x21c + 0x7f4ca4);
							else
								req.f8 = *(unsigned int*) ((unsigned int) gm_LocalPlayerSlot * 0x21c + 0x7f4ca4);
							req.c28 = gm_GameTime;
							req.c2c = gm_GameTimeHour;
							req.c30 = gm_GameTimeSliceDword;
							req.c34 = gm_GameTimeTailWord;
							req.id = *(unsigned short*) (0x779160 + k * 0x58);
							req.f12 = *(unsigned int*) (building + 1);
							req.f16 = 0;
							req.f20 = 0;
							req.flag36 = 1;
							req.neg5c = -1;
							req.f68 = *(unsigned int*) (building + 1);
							req.f6c = *(unsigned int*) (q + 2);
							m = cm_SendCopyEntityData(&req);
							while (!cm_GetCommandStatus(m))
								main_RunFrameLoop(0, 0x20007);
							found = cm_GetCommandResult(m);
located:
							p = (int*) 0x7e30d0;
							do {
								if (*p == 0xffff)
									break;
								if (p[4]) {
									j = sv_SelectedBuilding;
									if (!j)
										j = gm_QueryEntities(*(unsigned int*) (building + 0x5d), 1, 0, 0xfd);
									he_AssignActionSlot(building, j, *p, found);
									*(char*) (*p * 0x21c + 0x7f4e28) = 0;
								}
								p += 10;
							} while ((int) p < 0x7e35d0);
							if (!*(int*) (found + 0x70))
								*(int*) (found + 0x70) = 1;
						}
					}
					ep = (int*) (0x779164 + k * 0x58);
					for (j = 0; j < 4; j++) {
						if (d2_CurrentElementId == ep[0xe]) {
							if (*(int*) (0x77918c + k * 0x58) != j)
								g_7798a0 = *ep;
							else
								g_7798a0 = 0;
						}
						ep++;
					}
					rows += 0xe;
				}
			}
		}
		if (io_RightButtonReleased) {
			any = 0;
			p = (int*) 0x7e30e0;
			do {
				if ((int) p >= 0x7e35e0)
					break;
				if (p[-4] == 0xffff)
					break;
				if (*p)
					any = 1;
				p += 10;
			} while (!any);
			if (any) {
				p = (int*) 0x7e30d0;
				do {
					if (*p == 0xffff)
						break;
					*(char*) (*p * 0x21c + 0x7f4e28) = 0;
					p += 10;
				} while ((int) p < 0x7e35d0);
			} else {
				d2_DialogCloseRequested = 1;
				d3_EndCameraAndUiMode();
			}
		}
		gm_CollectTradeItemsByKind(building);
		if (count < 0x10) {
			p = (int*) 0x90d520;
			acc = (int*) (0x779160 + count * 0x58);
			for (i = 0; i < (int) (unsigned short) g_7f3ee4 && (int) acc < 0x7796e0; i++) {
				row = (char*) (((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[*p]));
				if (*row == 0x17)
					goto nextcand;
				found = 1;
				for (j = 0; j < 4 && found; j++) {
					if (((OBJECT_PROTOTYPE *)row)->ingredient_ids[j]) {
						m = gm_QueryEntities(*(unsigned int*) (t + 0x14), 1, 0, ((OBJECT_PROTOTYPE *)row)->ingredient_ids[j]);
						if (!m || (*(int*) (m + 0xe) != 2 && *building != 0x1e))
							found = 0;
					}
				}
				if (found) {
					for (m = 0; m < count; m++) {
						if (*(int*) (0x779160 + m * 0x58) == *p)
							break;
					}
					if (m == count) {
						if ((int) acc < 0x7796e0) {
							*acc = *p;
							count++;
							acc += 0x16;
						}
					}
				}
nextcand:
				p++;
			}
		}
		if (count > 0) {
			acc = (int*) 0x7791b0;
			for (k = 0; k < count; k++) {
				*acc = 0x7fffffff;
				for (j = 0; j < 4; j++) {
					row = (char*) (((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[*(int*) (0x779160 + k * 0x58)]));
					*(int*) (0x779164 + k * 0x58 + j * 4) = ((OBJECT_PROTOTYPE *)row)->ingredient_ids[j];
					*(int*) (0x779174 + k * 0x58 + j * 4) = ((OBJECT_PROTOTYPE *)row)->ingredient_amounts[j];
					if (!*(int*) (0x779164 + k * 0x58 + j * 4))
						continue;
					m = gm_QueryEntities(*(unsigned int*) (q + 0x14), 1, 0, *(int*) (0x779164 + k * 0x58 + j * 4));
					if (m == 0) {
						*acc = 0;
					} else {
						if (*acc >= gm_GetMsgField(q, m) / *(int*) (0x779174 + k * 0x58 + j * 4))
							*acc = gm_GetMsgField(q, m) / *(int*) (0x779174 + k * 0x58 + j * 4);
					}
				}
				*acc = ((OBJECT_PROTOTYPE *)lpObjektePROT)[*(int*) (0x779160 + k * 0x58)].value_036 * *acc;
				m = gm_QueryEntities(*(unsigned int*) (q + 0x14), 1, 0, *(int*) (0x779160 + k * 0x58));
				if (m)
					acc[1] = gm_GetMsgField(q, m);
				else
					acc[1] = 0;
				acc += 0x16;
			}
		}
		itoa(count, buf, 10);
		d2_SetLabelText(item, buf);
		d2_RenderProduktionStockRows(h, 2, count, q, 2);
		d2_SyncWareProduktionSlotGrid(building, q);
		d2_RefreshWorkshopInventoryGrids(h, 1, 0, building);
	} while (main_RunFrameLoop(0x59c000, 0x677c7));
	d2_DestroyForm(h);
	d2_RestoreHudAfterDialog();
	return 0;
}
