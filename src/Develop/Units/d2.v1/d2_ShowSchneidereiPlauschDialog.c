


#include "Develop/DieGildeAddOn/game/entity_record.h"









#include "Develop/DieGildeAddOn/game/game_player.h"
extern char s_6ad3c4[];
extern char s_681140[];
extern char s_6ad3bc[];
extern char s_6ad3a8[];
extern char* d2_VisitedBuilding;
extern int io_RightButtonReleased;
extern int d2_DialogButtonAction;
extern int d2_CurrentElementId;
#include "Develop/Units/d2.v1/client_dialog_state.h"

int __cdecl d2_LoadForm(int, int, char*);
int __cdecl gm_FindMostWantedCrimeTarget(ENTITY_RECORD*, int, int*, int*);
int __cdecl gm_GetBuildingTechEffect(int, int, int);
int __cdecl d2_GetFormWindow(int, int);
void __cdecl d2_InitWindowBounds(int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_ClearStatusTextSlots(void);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl d2_SetElementEnabled(int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl cm_RequestLinkEvidence(int, int);
void __cdecl cm_RequestModifyHealth(int, int);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, char*);
void __cdecl d2_DestroyForm(int);

void __cdecl d2_ShowSchneidereiPlauschDialog(ENTITY_RECORD* other)
{
	int count;
	int yes;
	int found;
	int list[4];
	char text[0x400];
	ENTITY_RECORD* me;
	int dlg;
	int max;
	int i;

	me = &((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot];
	dlg = d2_LoadForm(0, 0, s_6ad3c4);
	found = gm_FindMostWantedCrimeTarget(&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot], 4, list, &count);
	if ((*(int*)&d2_VisitedBuilding)) {
		max = gm_GetBuildingTechEffect((*(int*)&d2_VisitedBuilding), 0x24, 1);
	} else {
		max = 1;
	}
	if (count >= max + 1) {
		count = max + 1;
	}
	d2_InitWindowBounds(d2_GetFormWindow(dlg, 0));
	d2_CenterDialogWindows(dlg);
	d2_ClearStatusTextSlots();
	d2_SetForm(dlg, 1);
	io_AppendText(0x4227);
	io_AppendText(0x422b, other->entity_index, count, 0x422c, other->entity_index, 1);
	d2_SetForm(dlg, 2);
	yes = d2_GetWindowListItem(dlg, 2, io_AppendText((int) s_681140, 0x422d));
	io_AppendText((int) s_6ad3bc, 0x422e);
	if (found == 0 || count == 0) {
		d2_SetElementEnabled(yes, 0);
	}
	while (main_RunFrameLoop(d2_ShowSchneidereiPlauschDialog, 0x67fff)) {
		if (io_RightButtonReleased || d2_DialogButtonAction == 1) {
			d2_DialogCloseRequested = 1;
		}
		if (d2_DialogButtonAction != -1 && d2_CurrentElementId == yes) {
			if (found) {
				for (i = 0; i < count; i++) {
					cm_RequestLinkEvidence(list[i], ((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id);
				}
				cm_RequestModifyHealth(((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id, -1);
				cm_RequestModifyHealth(other->entity_id, -1);
				cm_RequestChangeBits(me->entity_id, 0x1cc, 4, 0x20000, 0);
				io_FormatTextBuffer(text, 0x422f, other->entity_index);
				he_PostEntityMessage(((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id, -1, text, 0, 0x5ec, 0);
				if (other->entity_state == 6 || other->entity_state == 7) {
					io_FormatTextBuffer(text, 0x4230, gm_LocalPlayerSlot, 1);
					he_PostEntityMessage(other->entity_id, -1, text, 0, 0x5ec, s_6ad3a8);
				}
				d2_DialogCloseRequested = 3;
			} else {
				cm_RequestModifyHealth(other->entity_id, -1);
				d2_DialogCloseRequested = 3;
			}
		}
	}
	d2_DestroyForm(dlg);
}
