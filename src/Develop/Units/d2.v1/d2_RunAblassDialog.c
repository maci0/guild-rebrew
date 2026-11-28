#include <math.h>
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern int d2_DialogCloseRequested;
extern int d2_CurrentElementId;
extern int io_RightButtonReleased;


int __cdecl gm_CountStraftatenForEntity(int a);
int __cdecl gm_SumStraftatSeverity(int a);
void __cdecl gs_ClearTargetStraftaten(int a, int b);
int __cdecl gm_WalkEntityChain(unsigned short);
float __cdecl gm_CalcEntityFavor(unsigned int a0, unsigned int a1, unsigned int a2);
int __cdecl gm_HasActiveSpecialObject(char*, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl gm_CheckEntityStock(char*, int, int);
int __cdecl cm_BeginPacketFieldDelta(char*, int);
void __cdecl cm_AppendPacketFieldValue(int, int, int, int*);
void __cdecl cm_RequestChangeAttribute(void);
int __cdecl cm_RequestMoveCredits(int, int, int, int);
int __cdecl cm_GetCommandStatus(int);
void __cdecl he_NotifyAblassPurchase(char*, char*, char*, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl d2_ShowModalMessageBox(char*, int);
void __cdecl d2_DestroyForm(int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl cm_StepCommandQueue(void);
int __cdecl gm_GetKircheRank(int, int);
void __cdecl d3_EndCameraAndUiMode(void);
void __cdecl d2_ShowKircheTop5(void);

/* Church indulgence ("Ablass") dialog: offers the indulgence for the current
 * player and, once bought, continues with the results screen. */
/* ADDRESS: GOLDTL 0x005ab3e0 */
void __cdecl d2_RunAblassDialog(char* churchBuilding)
{
	char text[0x200];
	char* rec;
	int count;
	int kind;
	int cost;
	int dlg;
	int item;
	int sel;
	int val;
	int changed;
	float scale;
	float factor;
	double scaledPrice;

	item = -1;
	cost = 0;
	count = gm_CountStraftatenForEntity(*(int*) ((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot] + 4));
	kind = gm_SumStraftatSeverity(*(int*) ((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot] + 4));
	if (kind != 0) {
		scale = (float) gm_WalkEntityChain(gm_LocalPlayerSlot) * 0.005f;
		factor = 1.5f;
		if (*(unsigned short*) (churchBuilding + 0x27) != gm_LocalPlayerSlot)
			factor = (200.0f - gm_CalcEntityFavor(gm_LocalPlayerSlot, *(unsigned short*) (churchBuilding + 0x27), 1)) * 0.01f;
		cost = (int) ((float) kind * factor * scale);
		scaledPrice = (double) cost * 0.1;
		cost = (int) (320000.0 < (scaledPrice > 3200.0 ? scaledPrice : 3200.0) ? 320000.0 : (scaledPrice > 3200.0 ? scaledPrice : 3200.0));
		if (gm_HasActiveSpecialObject((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot], 0x2c6) != 0)
			cost = cost / 2;
	}
	dlg = d2_LoadForm(0, 0, (char*) 0x6ab014);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1960);
	if (cost > 0) {
		io_AppendText(0x1962, count, cost);
		d2_SetForm(dlg, 2);
		item = d2_GetWindowListItem(dlg, 2, io_AppendText(0x1963));
	} else {
		io_AppendText(0x1961, gm_LocalPlayerSlot);
	}
	d2_DialogButtonAction = -1;
	changed = 0;
	do {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		} else if (d2_DialogButtonAction != -1 && d2_CurrentElementId == item
			&& gm_CheckEntityStock((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot], cost, gm_ActiveTownIndex) != 0) {
			rec = (char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot];
			cm_BeginPacketFieldDelta(rec, *(int*) (rec + 4));
			cm_AppendPacketFieldValue(4, 1, 0x1ac, &cost);
			cm_RequestChangeAttribute();
			gs_ClearTargetStraftaten(*(int*) (rec + 4), count);
			if (*(unsigned short*) (churchBuilding + 0x27) != 0xffff
				&& *(unsigned short*) (churchBuilding + 0x27) != gm_LocalPlayerSlot) {
				val = (int) (cost / log10((double) cost));
				cm_RequestMoveCredits(-1, *(int*) (rec + 4), gm_ActiveTownIndex, cost);
				sel = cm_RequestMoveCredits(*(int*) ((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*)(churchBuilding + 0x27)] + 4),
					-1, gm_ActiveTownIndex, val);
				he_NotifyAblassPurchase(rec, (char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*)(churchBuilding + 0x27)], churchBuilding, val, cost);
			} else {
				sel = cm_RequestMoveCredits(-1, *(int*) (rec + 4), gm_ActiveTownIndex, cost);
			}
			while (sel != -1 && cm_GetCommandStatus(sel) == 0)
				cm_StepCommandQueue();
			io_FormatTextBuffer(text, 0x1964, *(int*) (rec + 0x1ac), gm_GetKircheRank(gm_LocalPlayerSlot, 0));
			d2_ShowModalMessageBox(text, 0x100);
			changed = 1;
			d2_DialogCloseRequested = 1;
		}
	} while (main_RunFrameLoop((void*) d2_RunAblassDialog, 0x677c7) != 0);
	d2_DestroyForm(dlg);
	if (changed)
		d2_ShowKircheTop5();
	else
		d3_EndCameraAndUiMode();
}
