


// SIZE 0x21c
typedef struct {
	unsigned short id;
	unsigned char b2;
	char pad3;
	int f4;
	char pad8[4];
	unsigned char bc;
	char padd[0x77];
	unsigned char b84;
	char pad85[0x197];
} House;

extern char gm_EntitySlotTable[];
extern float g_662964;
extern unsigned char gm_ActiveTownIndex;
extern char s_6acdcc[];
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"

#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl gm_AccumulateTyped2(House*);
void __cdecl cm_RequestMoveCredits(int, int, char, int);
void __cdecl cm_RequestModifyHealth(int, int);
unsigned short __cdecl gm_RandomMod(int);
#include "Develop/DieGildeAddOn/command/client_packet_builder.h"
void __cdecl cm_AppendPacketFieldDelta(int, int, int, unsigned int*);
void __cdecl cm_RequestChangeAttribute(void);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl d2_CheckActionBlocker(House*, int);
int __cdecl gm_CheckEntityStock(House*, int, char);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl d2_ShowModalMessageBox(char*, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

int __cdecl gm_HandleBekehren(House* e)
{
	int i;

	if (e->b2 != 6) {
		unsigned int who;
		int money;
		unsigned int rank;

		*(unsigned char*) &rank = e->b84;
		who = e->bc;
		if (*(int*) ((char*) e + 0x194) < 6) {
			return 0x20;
		}
		money = (int) (gm_CalcPersonWealth(e->id) * g_662964);
		if (gm_AccumulateTyped2(e) < money) {
			return 0x20;
		}
		cm_RequestMoveCredits(-1, e->f4, gm_ActiveTownIndex, money);
		cm_RequestModifyHealth(e->f4, -6);
		for (i = 0; i < 768; i++) {
			if (((House*)gm_EntitySlotTable)[i].id != 0xffff && ((House*)gm_EntitySlotTable)[i].b2 < 10 && ((House*)gm_EntitySlotTable)[i].b2 != 6 && ((House*)gm_EntitySlotTable)[i].b2 != 7 &&
				((House*)gm_EntitySlotTable)[i].bc != e->bc) {
				if ((unsigned char) rank > gm_RandomMod(0x7e) + ((House*)gm_EntitySlotTable)[i].b84) {
					cm_BeginPacketFieldDelta((char*) &((House*)gm_EntitySlotTable)[i], ((House*)gm_EntitySlotTable)[i].f4);
					cm_AppendPacketFieldDelta(1, 1, 0xc, &who);
					cm_RequestChangeAttribute();
				}
			}
		}
		return 0x10;
	} else {
		int ok;
		int dlg;
		int money;
		unsigned char rank;
		int cancel;
		unsigned int who;
		char text[0x100];
		int id;
		int n;
		int result;
		House* h;

		result = 0;
		money = (int) (gm_CalcPersonWealth(e->id) * g_662964);
		dlg = d2_LoadForm(0, 0, s_6acdcc);
		d2_SetOverlayAnimation(0, 0);
		d2_CenterDialogWindows(dlg);
		d2_SetForm(dlg, 1);
		id = io_AppendText(0x1de1, 6, money);
		ok = d2_GetWindowListItem(dlg, 1, id);
		cancel = d2_GetWindowListItem(dlg, 1, id + 1);
		d2_DialogButtonAction = -1;
		do {
			if (d2_DialogButtonAction != -1) {
				if (d2_CurrentElementId == ok) {
					n = 0;
					rank = e->b84;
					who = e->bc;
					if (d2_CheckActionBlocker(e, 6) && gm_CheckEntityStock(e, money, gm_ActiveTownIndex)) {
						cm_RequestMoveCredits(-1, e->f4, gm_ActiveTownIndex, money);
						cm_RequestModifyHealth(e->f4, -6);
						for (i = 0; i < 768; i++) {
							h = &((House*)gm_EntitySlotTable)[i];
							/* the redundant b2 test keeps the loop pointer on b2, as in the original */
							if (h->id != 0xffff && h->b2 < 10 && h->b2 <= 10 && h->bc != e->bc) {
								if (rank > gm_RandomMod(0x7e) + h->b84) {
									n++;
									cm_BeginPacketFieldDelta((char*) h, h->f4);
									cm_AppendPacketFieldDelta(1, 1, 0xc, &who);
									cm_RequestChangeAttribute();
								}
							}
						}
						io_FormatTextBuffer(text, 0x1de2, n);
						d2_ShowModalMessageBox(text, 0);
						result = 1;
						d2_DialogCloseRequested = 1;
					}
				} else if (d2_CurrentElementId == cancel) {
					d2_DialogCloseRequested = 1;
				}
			}
			if (io_RightButtonReleased != 0) {
				d2_DialogCloseRequested = 1;
			}
		} while (main_RunFrameLoop((void*) gm_HandleBekehren, 0x657c7) != 0);
		d2_DestroyForm(dlg);
		return result;
	}
}
