


typedef struct
{
	int x0;
	unsigned char type;
	char pad5[3];
	int x8;
	char padc[0x2a];
	unsigned char x36;
	char pad37;
	int ids[8];
	int x58;
	int x5c;
	char pad60[0x98];
} Packet;
// SIZE 0xf8

#include "Develop/DieGildeAddOn/game/entity_record.h"











#include "Develop/DieGildeAddOn/game/game_player.h"
extern char* d2_VisitedBuilding;
extern int g_14abab4;
extern int g_14abaac;
extern int d2_DialogButtonAction;
extern int d2_CurrentElementId;
extern int io_RightButtonReleased;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern char s_6aa464[];

int __cdecl he_HasNoActiveAction0x62(char*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl d2_ShowModalMessageBox(char*, int);
int __cdecl gm_HasLevelFor(char*, char*);
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

/* ADDRESS: GOLDDE 0x00591e90 */
int __cdecl d2_ConfirmEinbruch(int unused, char* e)
{
	int r;
	int btn1;
	Packet pkt;
	char buf[0x400];
	ENTITY_RECORD* p;
	int dlg;
	int s;
	int btn2;
	int n;
	int i;

	r = 0;
	if (e == 0) {
		return 0;
	}
	p = ((ENTITY_RECORD *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[*(unsigned short*) (e + 0x27)]);
	if (he_HasNoActiveAction0x62(e) == 0) {
		io_FormatTextBuffer(buf, 0x1a92, *(unsigned short*) (e + 0x27), e);
		d2_ShowModalMessageBox(buf, 0);
		return 0;
	}
	if (gm_HasLevelFor(d2_VisitedBuilding, e) == 0) {
		d2_ShowModalMessageBox((char*) g_14abab4, 0);
		return 0;
	}
	dlg = d2_LoadForm(0, 0, s_6aa464);
	d2_CenterDialogWindows(dlg);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(dlg, 1);
	s = io_AppendText(0x19e4, p->entity_index, e);
	btn1 = d2_GetWindowListItem(dlg, 1, s);
	btn2 = d2_GetWindowListItem(dlg, 1, s + 1);
	d2_DialogButtonAction = -1;
	do {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
		if (d2_DialogButtonAction != -1) {
			if (d2_CurrentElementId == btn1) {
				pkt.type = 0x3f;
				pkt.x36 = 1;
				n = 0;
				pkt.x8 = ((ENTITY_RECORD_VIEW *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[gm_LocalPlayerSlot])->entity_id;
				pkt.x58 = *(int*) (e + 1);
				pkt.x5c = *(int*) (d2_VisitedBuilding + 1);
				for (i = 0; i < 8; i++) {
					pkt.ids[i] = -1;
				}
				for (i = 0; i < 768; i++) {
					if (((ENTITY_RECORD *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[i])->unk_17c[12] != 0) {
						pkt.ids[n] = ((ENTITY_RECORD_VIEW *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[i])->entity_id;
						n++;
					}
				}
				if (n != 0) {
					cm_SendCopyEntityData(&pkt);
					cm_ExProdObjekt();
				}
				else {
					d2_ShowModalMessageBox((char*) g_14abaac, 0);
				}
				sv_ClearObjectSelection();
				d2_DialogCloseRequested = 1;
				r = 1;
			}
			else if (d2_CurrentElementId == btn2) {
				d2_DialogCloseRequested = 1;
			}
		}
	} while (main_RunFrameLoop((void*) d2_ConfirmEinbruch, 0x677c7) != 0);
	d2_DestroyForm(dlg);
	return r;
}
