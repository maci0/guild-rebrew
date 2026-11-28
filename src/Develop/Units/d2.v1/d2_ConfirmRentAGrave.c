


// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"








#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char gm_ActiveTownIndex;
extern int d2_CurrentWindowId;
extern int d2_DialogButtonAction;
extern int io_RightButtonReleased;
extern int d2_CurrentElementId;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int he_GraveSlotTextIds[];
extern int main_LoopFlags;

int __cdecl gm_CalcBribeOrPriceScore(ENTITY_RECORD*, int, int, int, int*);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl io_AppendText();
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl gm_CheckEntityStock(ENTITY_RECORD*, int, unsigned char);
int __cdecl gv_RequestRentGrave(ENTITY_RECORD*, char*, int, int, int);
int __cdecl cm_GetCommandStatus(int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl d2_ShowModalMessageBox(char*, int);
void __cdecl d2_DestroyForm(int);

int __cdecl d2_ConfirmRentAGrave(char* who, int k)
{
	int h;
	int r;
	int ok;
	int cancel;
	int got;
	char buf[0x200];
	int x;
	int s;
	int id;

	r = 0;
	if (*(unsigned short*) (who + 0x27) == gm_LocalPlayerSlot) {
		x = 0;
	} else {
		x = gm_CalcBribeOrPriceScore(((ENTITY_RECORD *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[gm_LocalPlayerSlot]), 0xff, k, 1, &got);
	}
	h = d2_LoadForm(0, 0, "Locations\\Friedhof\\Friedhof");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetForm(h, 1);
	if (*(unsigned short*) (who + 0x27) == gm_LocalPlayerSlot) {
		io_AppendText(0x410c, 0x4109, who, he_GraveSlotTextIds[k]);
	} else {
		io_AppendText(0x410b, 0x4108, he_GraveSlotTextIds[k], x);
	}
	d2_SetForm(h, 2);
	s = io_AppendText(0x410d);
	ok = d2_GetWindowListItem(h, 2, s);
	cancel = d2_GetWindowListItem(h, 2, s + 1);
	d2_DialogButtonAction = -1;
	do {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		} else if (d2_DialogButtonAction != -1) {
			if (d2_CurrentElementId == ok) {
				if (x == 0 || gm_CheckEntityStock(((ENTITY_RECORD *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[gm_LocalPlayerSlot]), x, gm_ActiveTownIndex) != 0) {
					id = gv_RequestRentGrave(((ENTITY_RECORD *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[gm_LocalPlayerSlot]), who, k, 10, x);
					while (id != -1 && cm_GetCommandStatus(id) == 0) {
						main_RunFrameLoop(0, 0x20007);
					}
					main_LoopFlags = 0x677c7;
					if (cm_GetCommandStatus(id) == 2) {
						io_FormatTextBuffer(buf, 0x411b, (*(unsigned short*) (who + 0x27) == gm_LocalPlayerSlot) + 0x4108,
						    he_GraveSlotTextIds[k]);
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
	} while (main_RunFrameLoop(d2_ConfirmRentAGrave, 0x677c7) != 0);
	d2_DestroyForm(h);
	return r;
}
