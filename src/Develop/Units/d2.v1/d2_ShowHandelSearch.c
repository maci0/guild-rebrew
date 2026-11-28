#include <string.h>
#include "Develop/Units/d2.v1/d2_gui.h"
extern char* g_entity_type_table;
extern char* d2_Controls;
extern int d2_CurrentWindowId;
extern int d2_CurrentElementId;
extern int d2_DialogButtonAction;
extern int io_RightButtonReleased;
extern int gm_GameTime;
extern int gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;
#include "Develop/DieGildeAddOn/game/entity_record.h"
int __cdecl fcn_00502cd0(int a, int b, ...);
int __cdecl d2_CheckOwnerBlocked(void* obj);
void* __cdecl he_StartHandlungSearch(int a, int b, int c, int d, int e);
void* __cdecl he_fn_Handlung(void);
int __cdecl d2_LoadForm(int a, int b, char* name);
void __cdecl d2_CenterDialogWindows(int dlg);
void __cdecl d2_SetForm(int dlg, int flag);
void __cdecl d2_DrawPanelFrame(int ctx, int a, int b);
int __cdecl io_AppendText(int id, ...);
void __cdecl d2_InitPlayerBar(void* obj, int flag);
void __cdecl d2_ResetBuildingUiSlots(void);
int __cdecl d2_AddElementToWindow(int a, int b, int c, int d);
void __cdecl d2_SetControlText(int handle, char* name);
void __cdecl d2_SetElementEnabled(int handle, int flag);
void __cdecl d2_SyncWareProduktionSlotGrid(void* obj, int packet);
void __cdecl d2_RefreshWorkshopInventoryGrids(int dlg, int a, int b, void* obj);
int __cdecl main_RunFrameLoop(void* fn, int key);
void __cdecl sv_ClearObjectSelection(void);
void __cdecl d2_RestoreHudAfterDialog(void);
void __cdecl d2_DestroyForm(int dlg);
int __cdecl cm_SendCopyEntityData(char* msg);
void __cdecl d3snd_PlayWorkerOrderVoice(void);
int __cdecl cm_GetCommandStatus(int handle);
void __cdecl cm_GetCommandResult(int handle);
void __cdecl io_FormatTextBuffer(char* buf, int id, ...);
void __cdecl d2_ShowModalMessageBox(char* buf, int flag);
void __cdecl d3_EndCameraAndUiMode(void);
#include "Develop/DieGildeAddOn/game/building_prototype.h"
/* ADDRESS: GOLDTL 0x0059e740 */
void __cdecl d2_ShowHandelSearch(unsigned char* targetBuilding, unsigned char* a1)
{
	int count;
	int ids[7];
	int y;
	int dlg;
	int handles[3];
	char pkt[0xf8];
	char buf[0x100];
	int i;
	int j;
	int k;
	int h;
	int x;
	unsigned char type;
	unsigned char kind;
	char* rec;
	int p;
	void* entity;

	ids[0] = 0x1c4;
	ids[1] = 0x1c5;
	ids[2] = 0x1c6;
	ids[6] = fcn_00502cd0(*(int*) (targetBuilding + 0x5d), 2, 6, 0, 0x2a);
	type = *(unsigned char*) targetBuilding;
	rec = (char*)&((BUILDING_PROTOTYPE*)g_entity_type_table)[type];
	kind = *(unsigned char*) rec;
	if (kind == 0x20) {
		ids[0] = 0x2af;
		count = 1;
		if (*(unsigned char*) (rec + 0x247) >= 2) {
			ids[1] = 0x2b0;
			count = 2;
		}
	} else if (kind == 0x1f) {
		ids[0] = 0x293;
		ids[1] = 0x294;
		ids[2] = 0x295;
		count = 3;
	} else {
		count = 3;
		if (kind == 8 || *(unsigned char*) (rec + 0x247) < 2) {
			count = 2;
		}
	}
	if (d2_CheckOwnerBlocked(targetBuilding) != 0) {
		return;
	}
	memset(ids + 3, 0, 3 * sizeof(int));
	entity = he_StartHandlungSearch(2, 0, 0x14, 3, *(int*) (targetBuilding + 1));
	while (entity != 0) {
		for (i = 0; i < 3; i++) {
			if (*(unsigned short*) ((char*) entity + 0xae) == ids[i]) {
				ids[i + 3] += *(unsigned char*) ((char*) entity + 0xac);
				break;
			}
		}
		entity = he_fn_Handlung();
	}
	dlg = d2_LoadForm(0, 0, (char*) 0x6a9750);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	d2_DrawPanelFrame(d2_CurrentWindowId, 0x70f, 0x741);
	d2_SetForm(dlg, 3);
	io_AppendText(0x17fe);
	d2_InitPlayerBar(targetBuilding, 0);
	d2_ResetBuildingUiSlots();
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 2);
	if (count > 0) {
		y = *(int*) (d2_CurrentWindowId * 0x3cc + 0x1015f4c) / 2 - 0x80;
		x = 0x19;
		for (i = 0; i < count; i++) {
			h = d2_AddElementToWindow(y, x, ids[i] + 0xdf, d2_CurrentWindowId);
			*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[h]) + 0x5c) = 1;
			*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[h]) + 0x1d0) = 3;
			*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[h]) + 0x1dc) = 100;
			*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[h]) + 0x1e0) = 0x10;
			*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[h]) + 0x84) = 0x54;
			d2_SetControlText(h, (char*) *(int*) (ids[i] * 8 + 0x14a79c0));
			handles[i] = h;
			d2_SetElementEnabled(h, 1);
			x += 0x50;
		}
	}
	d2_SetOverlayAnimation(0, 0);
	d2_SyncWareProduktionSlotGrid(targetBuilding, ids[6]);
	d2_RefreshWorkshopInventoryGrids(dlg, 1, 0, targetBuilding);
	while (main_RunFrameLoop((void*) d2_ShowHandelSearch, 0x677c7) != 0) {
		d2_SyncWareProduktionSlotGrid(targetBuilding, ids[6]);
		d2_RefreshWorkshopInventoryGrids(dlg, 1, 0, targetBuilding);
		memset(ids + 3, 0, 3 * sizeof(int));
		entity = he_StartHandlungSearch(2, 0, 0x14, 3, *(int*) (targetBuilding + 1));
		while (entity != 0) {
			for (i = 0; i < 3; i++) {
				if (*(unsigned short*) ((char*) entity + 0xae) == ids[i]) {
					ids[i + 3] += *(unsigned char*) ((char*) entity + 0xac);
					break;
				}
			}
			entity = he_fn_Handlung();
		}
		d2_SetForm(dlg, 2);
		if (count > 0) {
			for (i = 0; i < count; i++) {
				d2_SetElementEnabled(handles[i], 1);
				if (ids[i + 3] == 1) {
					io_FormatTextBuffer(buf, 0x17ff, ids[i + 3], ids[i] * 2 + 0x9a8);
				} else if (ids[i + 3] > 1) {
					io_FormatTextBuffer(buf, 0x1800, ids[i + 3], ids[i] * 2 + 0x9a8);
				} else {
					io_FormatTextBuffer(buf, (int) 0x679060, ids[i] * 2 + 0x9a8);
				}
				d2_SetControlText(handles[i], buf);
			}
		}
		if (d2_DialogButtonAction != -1 && count > 0) {
			for (i = 0; i < count; i++) {
				if (handles[i] == d2_CurrentElementId) {
					memset(pkt, 0, sizeof(pkt));
					pkt[4] = 0x14;
					pkt[0x36] = 1;
					*(int*) (pkt + 8) = *(int*)&((ENTITY_RECORD*)0x7f4ca0)[*(unsigned short*) (targetBuilding + 0x27)].entity_id;
					*(int*) (pkt + 0x28) = gm_GameTime;
					*(int*) (pkt + 0xc) = *(int*) (targetBuilding + 1);
					*(int*) (pkt + 0x30) = gm_GameTimeSliceDword;
					*(int*) (pkt + 0x2c) = gm_GameTimeHour;
					*(unsigned short*) (pkt + 0x5a) = (unsigned short) ids[i];
					*(short*) (pkt + 0x34) = gm_GameTimeTailWord;
					*(int*) (pkt + 0x5c) = *(int*) (a1 + 2);
					j = 0;
					p = 0x7f4ca4;
					do {
						if (j >= 6) {
							break;
						}
						if (*(char*) (p + 0x184) != 0) {
							*(int*) (pkt + 0x38 + j * 4) = *(int*) p;
							j++;
						}
						p += 0x21c;
					} while (p < 0x85a0a4);
					if (j < 6) {
						for (k = j; k < 6; k++) {
							*(int*) (pkt + 0x38 + k * 4) = -1;
						}
					}
					pkt[0x58] = (char) j;
					if (j != 0) {
						d3snd_PlayWorkerOrderVoice();
						sv_ClearObjectSelection();
						h = cm_SendCopyEntityData(pkt);
						while (cm_GetCommandStatus(h) == 0) {
							main_RunFrameLoop(0, 0x20007);
						}
						cm_GetCommandResult(h);
					} else {
						d2_ShowModalMessageBox((char*) *(int*) 0x14ab324, 4);
					}
					break;
				}
			}
		} else if (io_RightButtonReleased != 0) {
			*(int*) 0x774654 = 1;
		}
	}
	sv_ClearObjectSelection();
	d2_RestoreHudAfterDialog();
	d2_DestroyForm(dlg);
	d3_EndCameraAndUiMode();
}
