#include "Develop/DieGildeAddOn/game/building_prototype.h"


// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"










extern unsigned char* lpGebaeudePROT;
extern char gm_TownTable[];
#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char gm_ActiveTownIndex;
extern int d2_DialogButtonAction;
extern int io_RightButtonReleased;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int d2_CurrentElementId;
extern char g_6aae08[];

unsigned char* __cdecl gm_QueryEntities(int, int, int, int, int);
int __cdecl gm_SumQueryEntryValues(int a, char b);
int __cdecl gm_AccumulateTyped2(ENTITY_RECORD* entity);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText();
void __cdecl d2_ClampAmountToRange(int, int, int, int*);
int __cdecl gm_AmountToUnits(int a, unsigned char b);
int __cdecl d2_GetWindowListItem(int, int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl d2_GetControlValue(int slot);
int __cdecl gm_ConvertUnitsToAmount(int a, unsigned char k);
int __cdecl gm_CheckEntityStock(ENTITY_RECORD*, int, unsigned char);
void __cdecl cm_RequestMoveCredits(int, int, unsigned char, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d3_EndCameraAndUiMode(void);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDDE 0x0058e8e0 */
void __cdecl d2_RunGildenkasseDialog(unsigned char* p)
{
	int h2;
	int n;
	int h1;
	unsigned char* obj;
	unsigned char* tbl;
	int acc;
	int ok;
	int d;
	int b;
	int v;

	h2 = -1;
	h1 = -1;
	b = 0;
	tbl = (unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[p[0]];
	obj = gm_QueryEntities(*(int*) (p + 0x5d), 2, 6, 0, 0x142);
	n = gm_SumQueryEntryValues(*(int*) (obj + 0x14), gm_ActiveTownIndex);
	acc = gm_AccumulateTyped2(((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot]));
	if ((((BUILDING_PROTOTYPE*)tbl)->category) == 0x17 && ((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].grade == 0x1e) {
		ok = 1;
	}
	else if ((((BUILDING_PROTOTYPE*)tbl)->category) == 0x18 && ((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].grade == 0x1f) {
		ok = 1;
	}
	else if ((((BUILDING_PROTOTYPE*)tbl)->category) == 0x19 && ((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].grade == 0x20) {
		ok = 1;
	}
	else if ((((BUILDING_PROTOTYPE*)tbl)->category) == 0x1a && ((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].grade == 0x21) {
		ok = 1;
	}
	else {
		ok = 0;
	}
	d = d2_LoadForm(0, 0, g_6aae08);
	d2_CenterDialogWindows(d);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(d, 1);
	io_AppendText(0x1a1a, n);
	if (ok != 0) {
		int col;

		b = io_AppendText(0x1a1b, *(unsigned short*) (((char(*)[0x2f4])gm_TownTable)[gm_ActiveTownIndex] + 0x54) * 2 + 0x9a8);
		d2_ClampAmountToRange(0x640, acc, 0x20, &col);
		d2_SetElementValue(d2_GetWindowListItem(d, 1, b), gm_AmountToUnits(0x640, gm_ActiveTownIndex), gm_AmountToUnits(col, gm_ActiveTownIndex), gm_AmountToUnits(0x640, gm_ActiveTownIndex));
		h1 = d2_GetWindowListItem(d, 1, b + 1);
		h2 = d2_GetWindowListItem(d, 1, b + 2);
	}
	d2_DialogButtonAction = -1;
	while (main_RunFrameLoop(d2_RunGildenkasseDialog, 0x677c7) != 0) {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
		if (ok != 0 && d2_DialogButtonAction != -1) {
			if (d2_CurrentElementId == h1) {
				v = d2_GetControlValue(d2_GetWindowListItem(d, 1, b));
				v = gm_ConvertUnitsToAmount(v, gm_ActiveTownIndex);
				if (gm_CheckEntityStock(((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot]), v, gm_ActiveTownIndex) != 0) {
					cm_RequestMoveCredits(*(int*) (obj + 2), ((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id, gm_ActiveTownIndex, v);
					d2_DialogCloseRequested = 1;
				}
			}
			else if (d2_CurrentElementId == h2) {
				d2_DialogCloseRequested = 1;
			}
		}
	}
	d3_EndCameraAndUiMode();
	d2_DestroyForm(d);
}
