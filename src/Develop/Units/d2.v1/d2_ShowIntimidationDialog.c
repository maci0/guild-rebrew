#include "Develop/client_types.h"


#include <string.h>





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
	char pad60[0x98];
} Packet;
// SIZE 0xf8

#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern int d2_DialogButtonAction;
extern int io_RightButtonReleased;
#include "Develop/Units/d2.v1/client_dialog_state.h"

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_CheckActionBlocker(char*, int);
void __cdecl cm_RequestModifyHealth(int, int);
int __cdecl cm_SendCopyEntityData(Packet*);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl d2_ShowModalMessageBox(char*, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDDE 0x005b7a30 */
int __cdecl d2_ShowIntimidationDialog(unsigned short* target)
{
	int dlg;
	pos14_7f4c00 nm;
	Packet pkt;
	char buf[0x100];
	int r;

	r = 0;
	dlg = d2_LoadForm(0, 0, "privillegien\\furcht_einfloessen");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1d62, *target, *target, 2, *target);
	d2_DialogButtonAction = -1;
	do {
		if (d2_DialogButtonAction != -1) {
			if (d2_DialogButtonAction == 2) {
				if (d2_CheckActionBlocker(((char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot]), 2) != 0) {
					cm_RequestModifyHealth(*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id, -2);
					memset(&pkt, 0, sizeof(pkt));
					pkt.type = 0x4b;
					pkt.x8 = *(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id;
					pkt.xc = pkt.x8;
					pkt.name = (*(pos14_7f4c00*)&gm_GameTime);
					pkt.x36 = 2;
					pkt.x5c = *(int*) (target + 2);
					pkt.x58 = pkt.x8;
					cm_SendCopyEntityData(&pkt);
					nm = (*(pos14_7f4c00*)&gm_GameTime);
					gm_AddTime(&nm, 0x18, 0, 0);
					io_FormatTextBuffer(buf, 0x1d63, &nm, *target);
					d2_ShowModalMessageBox(buf, 0);
					d2_DialogCloseRequested = 4;
					r = 1;
				}
			} else if (d2_DialogButtonAction == 1) {
				d2_DialogCloseRequested = 2;
			}
		}
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
	} while (main_RunFrameLoop((void*) d2_ShowIntimidationDialog, 0x657c7) != 0);
	d2_DestroyForm(dlg);
	return r;
}
