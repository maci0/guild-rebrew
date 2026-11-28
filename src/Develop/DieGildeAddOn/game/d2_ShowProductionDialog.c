#include "Develop/DieGildeAddOn/game/client_data.h"
#include "Develop/Units/d2.v1/d2_win.h"
extern char d2_ProductionPanels[];
extern char* d2_Controls;
extern char* g_item_def_table;
extern int d2_CurrentWindowId;
extern int d2_DialogButtonAction;
extern int g_100f884;
extern int d2_CurrentElementId;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int io_RightButtonReleased;
#include "game_player.h"
extern char* sv_SelectedBuilding;
#include "Develop/Units/d2.v1/d2_gui.h"
extern int gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;
extern char gm_EntityIdField[];
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern int d2_DialogCloseRequested;

void* __cdecl memset(void*, int, unsigned int);
char* __cdecl itoa(int, char*, int);
int __cdecl d2_CheckOwnerBlocked(int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_DestroyForm(int);
void __cdecl d2_SetForm(int, int);
int __cdecl d2_GetFormWindow(int, int, int, int*, int*, int*);
int __cdecl d2_SetLabelText(int, char*);
int __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl io_AppendText(int, ...);
void __cdecl d2_InitPlayerBar(int, int);
void __cdecl d2_RestoreHudAfterDialog(void);
void __cdecl d3_EndCameraAndUiMode(void);
void __cdecl d2_DrawPanelFrame(int, int, int);
void __cdecl d2_CreateWindowScrollbar(int, int, int, int);
void __cdecl d2_ResetBuildingUiSlots(void);
char* __cdecl gm_QueryEntities(int, int, int, ...);
int __cdecl gm_GetMsgField(char*, char*);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl he_AssignActionSlot(char*, char*, int, char*);
void __cdecl d2_RunProduktionDialog(int);
void __cdecl d2_UpdateProduktionPanels(int, int, int, char*);
int __cdecl d2_SyncWareProduktionSlotGrid(int, int);
void __cdecl d2_RefreshWorkshopInventoryGrids(int, int, int, int);
void __cdecl d3snd_PlayWorkerOrderVoice(void);
char* __cdecl he_StartHandlungSearch(int, ...);
char* __cdecl he_fn_Handlung(void);
int __cdecl cm_SendCopyEntityData(char*);
int __cdecl cm_GetCommandStatus(int);
char* __cdecl cm_GetCommandResult(int);
char* __cdecl gm_NextEntityQueryMatch(void);

typedef struct Msg59b {
	char pad0[4];
	unsigned char type;
	char pad5[3];
	int f08;
	int f0c;
	int f10;
	int f14;
	int f18;
	char pad1c[0xc];
	pos14_7f4c00 timestamp;
	unsigned char f36;
	char pad37[1];
	unsigned short f38;
	char pad3a[0x1e];
	int f58;
	int f5c;
	int f60;
	int f64;
	char pad68[0x90];
} Msg59b;

/* ADDRESS: GOLDTL 0x0059b260 */
/* ADDRESS: GOLDDE 0x00580500 */
int __cdecl d2_ShowProductionDialog(char* building)
{
	Msg59b msg;
	char buf[4];
	int v15;
	int v16;
	int item;
	int count;
	int hasAny;
	int n;
	int i;
	int k;
	int h;
	char* p1;
	char* p2;
	char* p3;
	char* p;
	char* q;
	char* e;
	int v;
	int prev;

	if (d2_CheckOwnerBlocked((int) building) != 0) {
		return 0;
	}
	h = d2_LoadForm(0, 0, (char*) 0x6aa148);
	d2_CenterDialogWindows(h);
	d2_InitPlayerBar((int) building, 0);
	d2_SetForm(h, 3);
	io_AppendText(0xc7);
	d2_ResetBuildingUiSlots();
	*(int*) d2_ProductionPanels = 0;
	count = 1;
	d2_SetForm(h, 0);
	k = d2_CurrentWindowId * 0x3cc;
	*(int*) &((D2_WIN*)((char*)d2_Windows + k))->pad3a8[0] = 0xe;
	*(int*) &((D2_WIN*)((char*)d2_Windows + k))->pad3a8[4] = 0xe;
	*(int*) &((D2_WIN*)((char*)d2_Windows + k))->pad3a8[8] = 0xe;
	*(int*) &((D2_WIN*)((char*)d2_Windows + k))->pad3a8[12] = 0xe;
	d2_DrawPanelFrame(d2_CurrentWindowId, 0x70b, 0x742);
	d2_CreateWindowScrollbar(0x270, 0x15e, d2_CurrentWindowId, d2_GetFormWindow(h, 2, 0x78, &v16, &v15, &item));
	*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[item].font)) = 0x54;
	d2_SetOverlayAnimation(0, 0);
	do {
		d2_SetForm(h, 2);
		p1 = gm_QueryEntities(*(int*) (building + 0x5d), 2, 6, 0, 0xff);
		if (p1 == 0) {
			return 0;
		}
		p2 = gm_QueryEntities(*(int*) (building + 0x5d), 2, 6, 0, 0x2a);
		if (p2 == 0) {
			return 0;
		}
		p3 = gm_QueryEntities(*(int*) (building + 0x5d), 1, 0, 0xfe);
		if (p3 == 0) {
			return 0;
		}
		if (d2_DialogButtonAction != -1 && g_100f884 == h) {
			hasAny = 0;
			q = (char*) 0x7e30e0;
			do {
				if (q >= (char*) 0x7e35e0) {
					break;
				}
				if (*(int*) (q - 0x10) == 0xffff) {
					break;
				}
				if (*(int*) q != 0) {
					hasAny = 1;
				}
				q += 0x28;
			} while (hasAny == 0);
			i = 0;
			if (count > 0) {
				do {
					e = (char*) ((int) d2_ProductionPanels + i * 0x58);
					if (d2_CurrentElementId == *(int*) (e + 0x34)) {
						if (hasAny == 0) {
							q = (char*) 0x7e30d0;
							do {
								n = *(int*) q;
								if (n == 0xffff) {
									break;
								}
								p = *(char**) ((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[n] + 0x17c);
								if (i == 0) {
									if (p != 0 && *(char*) p == 9 && *(int*) (p + 0x10) == *(int*) (building + 1)) {
										*(unsigned char*) ((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[n] + 0x188) = 0;
									}
								}
								else {
									if (p != 0 && *(char*) p == 8 && *(int*) (p + 0x10) == *(int*) (building + 1)
										&& *(unsigned short*) (p + 0xac) == *(int*) e) {
										*(unsigned char*) ((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[n] + 0x188) = 1;
									}
								}
								q += 0x28;
							} while (q < (char*) 0x7e35d0);
						} else {
							if (i == 0) {
								d3snd_PlayWorkerOrderVoice();
								p = he_StartHandlungSearch(2, 0, 9, 3, *(int*) (building + 1));
								if (p == 0) {
									memset(&msg, 0, 0xf8);
									msg.timestamp.a = gm_GameTime.a;
									msg.timestamp.c = gm_GameTimeSliceDword;
									msg.type = 9;
									msg.f08 = *(int*) (&((ENTITY_RECORD*)gm_EntitySlotTable)[(unsigned)gm_LocalPlayerSlot].entity_id);
									msg.f0c = *(int*) (building + 1);
									msg.f10 = 0;
									msg.f14 = 0;
									msg.f36 = 1;
									msg.timestamp.b = gm_GameTimeHour;
									msg.timestamp.d = (unsigned short) gm_GameTimeTailWord;
									msg.f58 = *(int*) (building + 1);
									msg.f5c = *(int*) (p1 + 2);
									msg.f60 = *(int*) (p3 + 2);
									k = cm_SendCopyEntityData((char*) &msg);
									e = (char*) cm_GetCommandStatus(k);
									while (e == 0) {
										main_RunFrameLoop(0, 0x20007);
										e = (char*) cm_GetCommandStatus(k);
									}
									p = cm_GetCommandResult(k);
								}
							}
							else {
								d3snd_PlayWorkerOrderVoice();
								p = he_StartHandlungSearch(2, 0, 8, 3, *(int*) (building + 1));
								while (p != 0) {
									if (*(unsigned short*) (p + 0xac) == *(int*) e) {
										break;
									}
									p = he_fn_Handlung();
								}
								if (p == 0) {
									memset(&msg, 0, 0xf8);
									msg.timestamp.a = gm_GameTime.a;
									msg.type = 8;
									msg.timestamp.c = gm_GameTimeSliceDword;
									msg.f36 = 1;
									*(unsigned short*) &msg.f58 = (unsigned short) *(int*) e;
									msg.f08 = *(int*) (&((ENTITY_RECORD*)gm_EntitySlotTable)[(unsigned)gm_LocalPlayerSlot].entity_id);
									msg.f10 = 0;
									msg.f14 = 0;
									msg.f0c = *(int*) (building + 1);
									msg.timestamp.b = gm_GameTimeHour;
									msg.timestamp.d = (unsigned short) gm_GameTimeTailWord;
									msg.f5c = *(int*) (building + 1);
									msg.f60 = *(int*) (p3 + 2);
									k = cm_SendCopyEntityData((char*) &msg);
									e = (char*) cm_GetCommandStatus(k);
									while (e == 0) {
										main_RunFrameLoop(0, 0x20007);
										e = (char*) cm_GetCommandStatus(k);
									}
									p = cm_GetCommandResult(k);
								}
							}
							if (p != 0) {
								q = (char*) 0x7e30d0;
								do {
									n = *(int*) q;
									if (n == 0xffff) {
										break;
									}
									if (*(int*) (q + 0x10) != 0) {
										he_AssignActionSlot(building, sv_SelectedBuilding, n, p);
										*(unsigned char*) ((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[n] + 0x188) = 0;
									}
									q += 0x28;
								} while (q < (char*) 0x7e35d0);
								if (*(int*) (p + 0x70) == 0) {
									*(int*) (p + 0x70) = 1;
								}
							}
						}
					}
					i++;
				} while (i < count);
			}
		}
		if (io_RightButtonReleased != 0) {
			hasAny = 0;
			q = (char*) 0x7e30e0;
			do {
				if (q >= (char*) 0x7e35e0) {
					break;
				}
				if (*(int*) (q - 0x10) == 0xffff) {
					break;
				}
				if (*(int*) q != 0) {
					hasAny = 1;
				}
				q += 0x28;
			} while (hasAny == 0);
			if (hasAny != 0) {
				q = (char*) 0x7e30d0;
				do {
					n = *(int*) q;
					if (n == 0xffff) {
						break;
					}
					*(unsigned char*) ((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[n] + 0x188) = 0;
					q += 0x28;
				} while (q < (char*) 0x7e35d0);
			}
			else {
				d2_DialogCloseRequested = 1;
				d3_EndCameraAndUiMode();
			}
		}
		e = gm_QueryEntities(*(int*) (p1 + 0x14), 1, 4, 0x17);
		if (e != 0) {
			k = count;
			p = (char*) ((int) d2_ProductionPanels + count * 0x58);
			do {
				if (*(int*) (e + 0xe) > 1) {
					v = 0;
					for (n = 1; n < k; n++) {
						if (*(int*) ((int) d2_ProductionPanels + n * 0x58) == *(unsigned short*) e) {
							v = 1;
							break;
						}
					}
					if (v == 0 && p < (d2_ProductionPanels + 0x580)) {
						*(int*) p = *(unsigned short*) e;
						p += 0x58;
						k++;
					}
				}
				e = gm_NextEntityQueryMatch();
			} while (e != 0);
			count = k;
		}
		if (count > 1) {
			n = count - 1;
			p = (d2_ProductionPanels + 0xa8);
			do {
				q = p - 0x4c;
				*(int*) p = 0x7fffffff;
				k = 0x26;
				do {
					i = *(int*) (p - 0x50);
					v = *(unsigned short*) (g_item_def_table + i * 0x41 + k + 8);
					*(int*) q = v;
					prev = *(unsigned short*) (g_item_def_table + i * 0x41 + k);
					*(int*) (q + 0x10) = prev;
					if (v != 0) {
						e = gm_QueryEntities(*(int*) (p2 + 0x14), 1, 0, v);
						if (e == 0) {
							*(int*) p = 0;
						}
						else {
							prev = *(int*) p;
							v = gm_GetMsgField(p2, e);
							i = *(int*) (p - 0x50);
							v /= *(unsigned short*) (g_item_def_table + i * 0x41 + k);
							if (prev >= v) {
								v = gm_GetMsgField(p2, e);
								i = *(int*) (p - 0x50);
								v /= *(unsigned short*) (g_item_def_table + i * 0x41 + k);
							}
							else {
								v = prev;
							}
							*(int*) p = v;
						}
					}
					k += 2;
					q += 4;
				} while (k < 0x2e);
				i = *(int*) (p - 0x50);
				v = *(unsigned short*) (g_item_def_table + i * 0x41 + 0x36);
				*(int*) p *= v;
				e = gm_QueryEntities(*(int*) (p2 + 0x14), 1, 0, i);
				if (e != 0) {
					*(int*) (p + 4) = gm_GetMsgField(p2, e);
				}
				else {
					*(int*) (p + 4) = 0;
				}
				p += 0x58;
			} while (--n);
		}
		itoa(count - 1, buf, 10);
		d2_SetLabelText(item, buf);
		d2_UpdateProduktionPanels(h, 2, count, p3);
		d2_SyncWareProduktionSlotGrid((int) building, (int) p2);
		d2_RefreshWorkshopInventoryGrids(h, 1, 0, (int) building);
	} while (main_RunFrameLoop(d2_RunProduktionDialog, 0x677c7) != 0);
	d2_DestroyForm(h);
	d2_RestoreHudAfterDialog();
	return 0;
}
