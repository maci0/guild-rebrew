typedef struct {
	char b[14];
} Name14;
/* SIZE 0xe */

typedef struct {
	int x0;
	unsigned char type;
	char pad5[3];
	int x8;
	int xc;
	char pad10[0x18];
	Name14 name;
	unsigned char x36;
	char pad37;
	int ids[8];
	int x58;
	int x5c;
	int x60;
	char pad64[0x94];
} Packet;
/* SIZE 0xf8 */

#include "Develop/DieGildeAddOn/game/entity_record.h"






/* SIZE 0x21c */

void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)


#include "Develop/DieGildeAddOn/game/game_player.h"
extern char* d2_VisitedBuilding;
extern int g_14abc98;
extern int d2_DialogButtonAction;
extern int d2_CurrentElementId;
extern int io_RightButtonReleased;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern char s_6ab348[];

int __cdecl d2_ShowModalMessageBox(int, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl cm_SendCopyEntityData(Packet*);
void __cdecl cm_ExProdObjekt(void);
int __cdecl io_FormatTextBuffer(char*, int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDTL 0x005af550 */
int __cdecl d2_RunStadtwacheDispatchDialog(int unused, char* param)
{
	Packet pkt;
	char buf[0x400];
	int flag;
	int count;
	int btn2;
	int btn1;
	int dlg;
	int btn;
	int i;
	int n;

	flag = 0;
	if (param == 0) {
		return 0;
	}
	for (i = 0; i < 768; i++) {
		if (((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].selected != 0)
			break;
	}
	if (i >= 768) {
		d2_ShowModalMessageBox(g_14abc98, 0);
		return 0;
	}
	dlg = d2_LoadForm(0, 0, s_6ab348);
	d2_CenterDialogWindows(dlg);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(dlg, 1);
	btn = io_AppendText(0x1a6d, param);
	btn1 = d2_GetWindowListItem(dlg, 1, btn);
	btn2 = d2_GetWindowListItem(dlg, 1, btn + 1);
	d2_DialogButtonAction = -1;
	do {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
		if (d2_DialogButtonAction != -1) {
			if (d2_CurrentElementId == btn1) {
				n = 0;
				memset(pkt.ids, 0xff, sizeof(pkt.ids));
				for (i = 0; i < 768; i++) {
					if (n >= 6) {
						break;
					}
					if (((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].selected != 0) {
						pkt.ids[n] = ((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].entity_id;
						n++;
					}
				}
				if (n != 0) {
					count = 0;
					pkt.type = 0x44;
					pkt.x8 = ((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id;
					pkt.x36 = 2;
					pkt.x58 = *(int*) (param + 1);
					pkt.x5c = *(int*) (d2_VisitedBuilding + 1);
					cm_SendCopyEntityData(&pkt);
					cm_ExProdObjekt();
					flag = 1;
					for (i = 0; i < 768; i++) {
						if (((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].selected != 0)
							count++;
					}
					if (count > 6) {
						io_FormatTextBuffer(buf, 0x19ef, 6);
						d2_ShowModalMessageBox(buf, 0);
					}
				}
				d2_DialogCloseRequested = 2;
			}
			else if (d2_CurrentElementId == btn2) {
				d2_DialogCloseRequested = 1;
			}
		}
	} while (main_RunFrameLoop((void*) d2_RunStadtwacheDispatchDialog, 0x677c7) != 0);
	d2_DestroyForm(dlg);
	return flag;
}
