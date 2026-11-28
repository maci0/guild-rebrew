


extern int d2_CurrentWindowId;
extern int d2_DialogButtonAction;
extern int io_RightButtonReleased;
extern int d2_CurrentElementId;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int main_LoopFlags;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char gm_ActiveTownIndex;
extern int he_GraveSlotTextIds[];
#include "Develop/DieGildeAddOn/game/entity_record.h"

int __cdecl d2_LoadForm(int, int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl gm_CheckEntityStock(void*, int, char);
int __cdecl gv_SendMoveSlotEntry(void*, int, char*, int, int, int);
int __cdecl cm_GetCommandStatus(int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl d2_ShowModalMessageBox(char*, int);

/* ADDRESS: GOLDDE 0x00572550 */
int __cdecl d2_RunFriedhofDialog(char* entity, int a2, unsigned char a3, int choice)
{
	int r;
	int ok;
	int cancel;
	char buf[0x200];
	int dlg;
	int cost;
	int id;
	int h;
	int s;

	r = 0;
	cost = *(unsigned short*) (entity + 0x27) != gm_LocalPlayerSlot ? 16000 : 0;
	dlg = d2_LoadForm(0, 0, (int) "Locations\\Friedhof\\Friedhof");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetForm(dlg, 1);
	if (*(unsigned short*) (entity + 0x27) == gm_LocalPlayerSlot) {
		io_AppendText(0x4115, 0x4112, entity, he_GraveSlotTextIds[choice]);
	} else {
		io_AppendText(0x4114, 0x4112, he_GraveSlotTextIds[choice], cost);
	}
	d2_SetForm(dlg, 2);
	id = io_AppendText(0x4116);
	ok = d2_GetWindowListItem(dlg, 2, id);
	cancel = d2_GetWindowListItem(dlg, 2, id + 1);
	d2_DialogButtonAction = -1;
	do {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		} else if (d2_DialogButtonAction != -1) {
			if (d2_CurrentElementId == ok) {
				if (cost == 0 || gm_CheckEntityStock(((char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot]), cost, (*(char*)&gm_ActiveTownIndex)) != 0) {
					h = gv_SendMoveSlotEntry(((char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot]), choice, entity, a2, a3, cost);
					while (h != -1 && (s = cm_GetCommandStatus(h)) == 0) {
						main_RunFrameLoop((void*) s, 0x20007);
					}
					main_LoopFlags = 0x677c7;
					if (cm_GetCommandStatus(h) == 2) {
						io_FormatTextBuffer(buf, 0x411b, 0x4112, he_GraveSlotTextIds[choice]);
						d2_ShowModalMessageBox(buf, 0x100);
					} else {
						d2_DialogCloseRequested = 1;
						r = 1;
					}
				}
			} else if (d2_CurrentElementId == cancel) {
				d2_DialogCloseRequested = 1;
			}
		}
	} while (main_RunFrameLoop((void*) d2_RunFriedhofDialog, 0x677c7) != 0);
	d2_DestroyForm(dlg);
	return r;
}
