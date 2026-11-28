#include "game_data.h"
#include "game_player.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int g_14abaac;
int __cdecl he_HasNoActiveAction0x62(char* obj); void* __cdecl gm_QueryEntities(int container_id, int arg_count, ...);
#include "Develop/DieGildeAddOn/game/entity_record.h"
void* __cdecl gm_NextEntityQueryMatch(void);
void* __cdecl he_StartHandlungSearch(int a, int b, int c, int d, int e);
void* __cdecl he_fn_Handlung(void);
void __cdecl io_FormatTextBuffer(char* buf, int id, ...);
void __cdecl d2_ShowModalMessageBox(char* buf, int flag);
int __cdecl d2_LoadForm(int a, int b, char* name);
void __cdecl d2_CenterDialogWindows(int dlg);
void __cdecl d2_SetOverlayAnimation(int a, int b);
void __cdecl d2_SetForm(int dlg, int flag);
int __cdecl io_AppendText(int id, ...);
int __cdecl d2_GetWindowListItem(int dlg, int a, int b);
void __cdecl cm_SendCopyEntityData(int a1);
void __cdecl d3snd_PlayWorkerOrderVoice(void);
void __cdecl sv_ClearObjectSelection(void);
int __cdecl main_RunFrameLoop(int a, int b);
void __cdecl d2_DestroyForm(int dlg);
#include "Develop/DieGildeAddOn/game/building_prototype.h"
/* ADDRESS: GOLDTL 0x0059d6b0 */
void __cdecl d2_ShowBriberyDialog(unsigned int id, char* obj)
{
	char msg[0x400];
	char msg2[0x100];
	char* list[16];
	char packet[0xf8];
	unsigned char* profile;
	int count;
	int extra;
	int entity;
	int other;
	int index;
	char* choice;
	int option;
	int i;
	extra = 0;
	if (obj == 0) {
		return;
	}
	if (*(unsigned short*) (obj + 0x27) == 0xffff) {
		return;
	}
	if (he_HasNoActiveAction0x62(obj) == 0) {
		io_FormatTextBuffer(msg, 0x1a92, *(unsigned short*) (obj + 0x27), obj);
		d2_ShowModalMessageBox(msg, 0);
		return;
	}
	count = 0;
	profile = (unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*(unsigned char*)obj];
	entity = (int) d2_VisitedBuilding;
	if (d2_VisitedBuilding != 0 || (entity = (int) d2_InteriorBuilding) != 0) {
		other = (int) gm_QueryEntities(*(int*) (entity + 0x5d), 1, 0, 0xca);
		while (other != 0) {
			if (*(int*) (other + 0x2a) != *(int*) (obj + 1)) {
				list[count] = (char*) other;
				count++;
			}
			other = (int) gm_NextEntityQueryMatch();
		}
	}
	other = (int) he_StartHandlungSearch(2, 2, gm_LocalPlayerSlot, 0, 0x40);
	while (other != 0) {
		for (index = 0; index < count; index++) {
			if (*(int*) (other + 0xac) == *(int*) (list[index] + 0x2a)) {
				break;
			}
		}
		if (index >= count) {
			extra++;
		}
		other = (int) he_fn_Handlung();
	}
	count += extra;
	if (count >= *(unsigned char*) (profile + 0x247) * 2) {
		io_FormatTextBuffer(msg2, 0x19fa, count, d2_InteriorBuilding);
		d2_ShowModalMessageBox(msg2, 0);
		return;
	}
	choice = (char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*)(obj + 0x27)];
	option = d2_LoadForm(0, 0, "misc\\Bestechung");
	d2_CenterDialogWindows(option);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(option, 1);
	index = io_AppendText(0x19f7, *(unsigned short*) choice, obj);
	other = d2_GetWindowListItem(option, 1, index);
	index = d2_GetWindowListItem(option, 1, index + 1);
	d2_DialogButtonAction = -1;
	do {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
		if (d2_DialogButtonAction != -1) {
			if (d2_CurrentElementId == other) {
				for (i = 0; i < 8; i++) {
					((unsigned int*) (packet + 0x38))[i] = 0xffffffff;
				}
				packet[4] = 0x40;
				packet[0x36] = 1;
				*(int*) (packet + 8) = *(int*) (gm_EntityIdField + gm_LocalPlayerSlot * 0x21c);
				*(int*) (packet + 0x58) = *(int*) (obj + 1);
				*(int*) (packet + 0x5c) = *(int*) (d2_InteriorBuilding + 1);
				i = 0;
				for (entity = 0x7f4ca4; entity < 0x85a0a4 && i < 8; entity += 0x21c) {
					if (*(char*) (entity + 0x184) != 0) {
						((unsigned int*) (packet + 0x38))[i] = *(unsigned int*) entity;
						i++;
					}
				}
				if (i != 0) {
					cm_SendCopyEntityData((int) packet);
					d3snd_PlayWorkerOrderVoice();
					sv_ClearObjectSelection();
					d2_DialogCloseRequested = 1;
				}
				else {
					d2_ShowModalMessageBox((char*) g_14abaac, 0);
					d2_DialogCloseRequested = 1;
				}
			}
			else if (d2_CurrentElementId == index) {
				d2_DialogCloseRequested = 1;
			}
		}
	} while (main_RunFrameLoop(0x59d6b0, 0x677c7));
	d2_DestroyForm(option);
}
