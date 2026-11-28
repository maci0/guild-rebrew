#include "Develop/client_types.h"



void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)





// SIZE 0xe

typedef struct
{
	int x0;
	unsigned char type;
	char pad5[3];
	int x8;
	int xc;
	char pad10[0x18];
	pos14_7f4c00 name;
	unsigned char x36;
	char pad37[0x21];
	int x58;
	int x5c;
	int x60;
	int x64;
	char pad68[0x90];
} Packet;
// SIZE 0xf8

typedef struct
{
	int x0;
	int x4;
	char pad8[0x180];
	unsigned char x188;
	char pad189[0x93];
} Player;
// SIZE 0x21c

#include "Develop/DieGildeAddOn/game/entity_record.h"
extern char* ch_ContextCharacters[32];
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern int g_14abc98;
extern int g_14b5290;
extern int g_14abcf0;
extern int d2_DialogButtonAction;
extern int d2_CurrentElementId;
extern int io_RightButtonReleased;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern char* d2_VisitedBuilding;
extern char* sv_SelectedBuilding;
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
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDDE 0x00594450 */
int __cdecl d2_SelectBetriebsPruefungTarget(int unused, char* e)
{
	int btn1;
	Packet pkt;
	int i;
	int n;
	int dlg;
	int s;
	int btn2;

	if (e == 0) {
		return 0;
	}
	for (i = 0; i < 768; i++) {
		if ((*(unsigned char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].selected) != 0) {
			break;
		}
	}
	if (i >= 768) {
		d2_ShowModalMessageBox(g_14abc98, 0);
		return 0;
	}
	if (e[0x5b] & 8) {
		d2_ShowModalMessageBox(g_14b5290, 0);
		return 0;
	}
	dlg = d2_LoadForm(0, 0, s_6ab348);
	d2_CenterDialogWindows(dlg);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(dlg, 1);
	s = io_AppendText(0x1a73, e);
	btn1 = d2_GetWindowListItem(dlg, 1, s);
	btn2 = d2_GetWindowListItem(dlg, 1, s + 1);
	d2_DialogButtonAction = -1;
	do {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
		if (d2_DialogButtonAction != -1) {
			if (d2_CurrentElementId == btn1) {
				memset(&pkt, 0, sizeof(pkt));
				pkt.type = 0x64;
				pkt.x8 = (*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id);
				pkt.xc = *(int*) (d2_VisitedBuilding + 1);
				pkt.name = (*(pos14_7f4c00*)&gm_GameTime);
				pkt.x36 = 1;
				pkt.x5c = *(int*) (e + 1);
				pkt.x60 = *(int*) (d2_VisitedBuilding + 1);
				pkt.x64 = *(int*) (sv_SelectedBuilding + 2);
				for (i = 0; i < 32; i++) {
					if (((Player**)ch_ContextCharacters)[i] != 0 && ((Player**)ch_ContextCharacters)[i]->x188 != 0) {
						pkt.x58 = ((Player**)ch_ContextCharacters)[i]->x4;
						cm_SendCopyEntityData(&pkt);
						cm_ExProdObjekt();
						break;
					}
				}
				n = 0;
				for (i = 0; i < 32; i++) {
					if (((Player**)ch_ContextCharacters)[i] != 0 && ((Player**)ch_ContextCharacters)[i]->x188 != 0) {
						n++;
					}
				}
				if (n > 1) {
					d2_ShowModalMessageBox(g_14abcf0, 4);
				}
				d2_DialogCloseRequested = 2;
			}
			else if (d2_CurrentElementId == btn2) {
				d2_DialogCloseRequested = 1;
			}
		}
	} while (main_RunFrameLoop((void*) d2_SelectBetriebsPruefungTarget, 0x677c7) != 0);
	d2_DestroyForm(dlg);
	return 0;
}
