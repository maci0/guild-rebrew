


// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"








#include "Develop/DieGildeAddOn/game/game_player.h"
extern int d2_CurrentWindowId;
extern int d2_DialogButtonAction;
extern int io_RightButtonReleased;
extern int d2_CurrentElementId;
#include "Develop/Units/d2.v1/client_dialog_state.h"

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl io_AppendText();
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl d2_CheckActionBlocker(ENTITY_RECORD*, int);
void __cdecl gm_ModifyHealth(int, int);
#include "Develop/DieGildeAddOn/command/client_packet_builder.h"
void __cdecl cm_AppendPacketFieldDelta(int, int, int, int*);
int __cdecl cm_RequestChangeAttribute(void);
int __cdecl cm_GetCommandStatus(int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
void __cdecl d3_EndCameraAndUiMode(void);

/* ADDRESS: GOLDDE 0x00570970 */
void __cdecl d2_RunDomizilKabinettDialog(int unused, char* p)
{
	int ok;
	int cancel;
	int b;
	int h;
	int s;
	int v;
	int id;

	b = *(int*) (p + 0x20);
	h = d2_LoadForm(0, 0, "Locations\\Domizil\\kabinett");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetForm(h, 1);
	io_AppendText("$C");
	io_AppendText(0x407d, 0x4171, b);
	d2_SetForm(h, 2);
	s = io_AppendText(0x407e);
	ok = d2_GetWindowListItem(h, 2, s);
	cancel = d2_GetWindowListItem(h, 2, s + 1);
	do {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		} else if (d2_DialogButtonAction != -1) {
			if (d2_CurrentElementId == ok) {
				if (d2_CheckActionBlocker(((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot]), b) == 1) {
					v = 0;
					gm_ModifyHealth(((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id, -b);
					cm_BeginPacketFieldDelta(p, *(int*) (p + 2));
					cm_AppendPacketFieldDelta(4, 1, 0x1c, &v);
					cm_AppendPacketFieldDelta(4, 1, 0x20, &v);
					id = cm_RequestChangeAttribute();
					while (id != -1 && cm_GetCommandStatus(id) == 0) {
						main_RunFrameLoop(0, 0x20007);
					}
					d2_DialogCloseRequested = 1;
				}
			} else if (d2_CurrentElementId == cancel) {
				d2_DialogCloseRequested = 1;
			}
		}
	} while (main_RunFrameLoop(d2_RunDomizilKabinettDialog, 0x677c7) != 0);
	d2_DestroyForm(h);
	d3_EndCameraAndUiMode();
}
