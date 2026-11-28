


void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

typedef struct
{
	int x0;
	unsigned char type;
	char pad5[3];
	int x8;
	char padc[0x2a];
	unsigned char x36;
	char pad37[0x21];
	int x58;
	int x5c;
	char pad60[0x10];
	int ids[4];
	char pad80[0x78];
} Packet;
// SIZE 0xf8

#include "Develop/DieGildeAddOn/game/entity_record.h"










#include "Develop/DieGildeAddOn/game/game_player.h"
extern int g_14abc98;
extern int d2_DialogButtonAction;
extern int d2_CurrentElementId;
extern int io_RightButtonReleased;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern char* d2_VisitedBuilding;
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
void __cdecl sv_ClearObjectSelection(void);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
void __cdecl d3_EndCameraAndUiMode(void);

/* Inferred name from the selection dialog and production-command packet. */
int __cdecl ConfirmProductionSelection(int unused, char* a)
{
	int btn1;
	Packet pkt;
	int i;
	int n;
	int dlg;
	int s;
	int btn2;

	if (a == 0) {
		return 0;
	}
	for (i = 0; i < 768; i++) {
		if (((ENTITY_RECORD*)gm_EntitySlotTable)[i].unk_17c[12] != 0) {
			break;
		}
	}
	if (i >= 768) {
		d2_ShowModalMessageBox(g_14abc98, 0);
		return 0;
	}
	dlg = d2_LoadForm(0, 0, s_6ab348);
	d2_CenterDialogWindows(dlg);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(dlg, 1);
	s = io_AppendText(0x1a69);
	btn1 = d2_GetWindowListItem(dlg, 1, s);
	btn2 = d2_GetWindowListItem(dlg, 1, s + 1);
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
					if (n >= 4) {
						break;
					}
					if (((ENTITY_RECORD*)gm_EntitySlotTable)[i].unk_17c[12] != 0) {
						pkt.ids[n] = ((ENTITY_RECORD*)gm_EntitySlotTable)[i].entity_id;
						n++;
					}
				}
				if (n != 0) {
					pkt.type = 0x43;
					pkt.x36 = 2;
					pkt.x8 = ((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id;
					pkt.x58 = *(int*) (a + 1);
					pkt.x5c = *(int*) (d2_VisitedBuilding + 1);
					for (; n < 4; n++) {
						pkt.ids[n] = -1;
					}
					cm_SendCopyEntityData(&pkt);
					cm_ExProdObjekt();
				}
				sv_ClearObjectSelection();
				d2_DialogCloseRequested = 2;
			}
			else if (d2_CurrentElementId == btn2) {
				d2_DialogCloseRequested = 1;
			}
		}
	} while (main_RunFrameLoop((void*) ConfirmProductionSelection, 0x677c7) != 0);
	d2_DestroyForm(dlg);
	d3_EndCameraAndUiMode();
	return 1;
}
