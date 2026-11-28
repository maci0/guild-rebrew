#include <string.h>
#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "Develop/client_types.h"

/* SIZE 0xf8 */
typedef struct {
	int f0;			/* +0x00 */
	unsigned char b4;	/* +0x04 */
	char pad5[3];
	int f8;			/* +0x08 */
	int fc;			/* +0x0c */
	char pad10[0x18];
	pos14_7f4c00 pos28;	/* +0x28 */
	unsigned char b36;	/* +0x36 */
	char pad37[0x21];
	int f58;		/* +0x58 */
	int f5c;		/* +0x5c */
	char pad60[8];
	int f68;		/* +0x68 */
	int f6c;		/* +0x6c */
	char pad70[0x88];
} Msg_59d380;

#include "Develop/DieGildeAddOn/game/game_data.h"
extern pos14_7f4c00 gm_GameTime;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char* d2_HoveredSceneObject;
extern int g_14abd04;
extern int d2_CurrentElementId;
extern int io_RightButtonReleased;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern char s_6aa4b8[];

extern char* __cdecl he_StartHandlungSearch(int, int, int);
extern char* __cdecl he_fn_Handlung(void);
extern int __cdecl he_HasNoActiveAction0x62(char*);
extern void __cdecl io_FormatTextBuffer(char*, char*, ...);
extern int __cdecl d2_ShowModalMessageBox(char*, int);
extern int __cdecl d2_LoadForm(int, int, char*);
extern void __cdecl d2_CenterDialogWindows(int);
extern void __cdecl d2_SetOverlayAnimation(int, int);
extern void __cdecl d2_SetForm(int, int);
extern int __cdecl io_AppendText(int, ...);
extern int __cdecl d2_GetWindowListItem(int, int, int);
extern void __cdecl d3snd_PlayWorkerOrderVoice(void);
extern void __cdecl cm_SendCopyEntityData(Msg_59d380*);
extern void __cdecl sv_ClearObjectSelection(void);
extern int __cdecl main_RunFrameLoop(void*, int);
extern void __cdecl d2_DestroyForm(int);


/* Oeffnet den Jahrmarkt-Dialog eines Objekts, bietet seine zwei Eintraege an
 * und schickt beim Anklicken das Nachrichtenpaket 0x62. */
/* ADDRESS: GOLDTL 0x0059d380 */
int __cdecl d2_RunRaeuberlagerTargetDialog(int unusedFlags, char* object)
{
	Msg_59d380 message;
	char buf[512];
	char* event;
	int i;
	int dlg;
	int text;
	int item1;
	int item2;
	int slot;

	if (object == 0) {
		return 0;
	}
	event = he_StartHandlungSearch(1, 0, 0x62);
	while (event != 0) {
		if (*(int*) (event + 0xb0) == *(int*) (object + 1)) {
			io_FormatTextBuffer(buf, (char*) 0x1a91, *(unsigned short*) (object + 0x27), object);
			d2_ShowModalMessageBox(buf, 0);
			return 0;
		}
		event = he_fn_Handlung();
	}
	for (i = 0; i < 0x300; i++) {
		if ((char)((ENTITY_RECORD*)gm_EntitySlotTable)[i].unk_17c[12] != 0) {
			break;
		}
	}
	if (i >= 0x300) {
		d2_ShowModalMessageBox((char*) g_14abd04, 0);
		return 0;
	}
	if (he_HasNoActiveAction0x62(object) == 0) {
		io_FormatTextBuffer(buf, (char*) 0x1a89, *(unsigned short*) (object + 0x27), object);
		d2_ShowModalMessageBox(buf, 0);
		return 0;
	}
	dlg = d2_LoadForm(0, 0, s_6aa4b8);
	d2_CenterDialogWindows(dlg);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(dlg, 1);
	text = io_AppendText(0x1a8b, object);
	item1 = d2_GetWindowListItem(dlg, 1, text);
	item2 = d2_GetWindowListItem(dlg, 1, text + 1);
	d2_DialogButtonAction = -1;
	do {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
		if (d2_DialogButtonAction == -1) {
			continue;
		}
		if (d2_CurrentElementId == item1) {
			d3snd_PlayWorkerOrderVoice();
			message.b4 = 0x62;
			slot = gm_LocalPlayerSlot;
			message.f8 = ((ENTITY_RECORD*)gm_EntitySlotTable)[slot].entity_id;
			if (d2_VisitedBuilding != 0) {
				message.fc = *(int*) (d2_VisitedBuilding + 1);
			} else {
				message.fc = *(int*) (d2_InteriorBuilding + 1);
			}
			message.pos28 = gm_GameTime;
			message.b36 = 2;
			message.f5c = *(int*) (object + 1);
			if (d2_VisitedBuilding != 0) {
				message.f68 = *(int*) (d2_VisitedBuilding + 1);
			} else {
				message.f68 = *(int*) (d2_InteriorBuilding + 1);
			}
			if (sv_SelectedBuilding != 0) {
				message.f6c = *(int*) (sv_SelectedBuilding + 2);
			} else {
				message.f6c = -1;
			}
			for (i = 0; i < 0x20; i++) {
				if (ch_ContextCharacters[i] != 0 && ch_ContextCharacters[i][0x188] != 0) {
					message.f58 = *(int*) (ch_ContextCharacters[i] + 4);
					break;
				}
			}
			cm_SendCopyEntityData(&message);
			d2_DialogCloseRequested = 1;
			sv_ClearObjectSelection();
		} else if (d2_CurrentElementId == item2) {
			d2_DialogCloseRequested = 1;
		}
	} while (main_RunFrameLoop((void*) d2_RunRaeuberlagerTargetDialog, 0x677c7) != 0);
	d2_DestroyForm(dlg);
	return 0;
}
