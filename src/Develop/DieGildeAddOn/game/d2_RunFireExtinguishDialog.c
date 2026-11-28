#include "Develop/DieGildeAddOn/game/entity_record.h"


#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d2_DialogCloseRequested;




int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl gm_SearchTable67(int);
int __cdecl d2_CheckActionBlocker(char*, int);
void __cdecl gm_ModifyHealth(int, int);
void __cdecl d2_SetFormVisibility(int, int);
double __cdecl gm_RandomFloat01(void);
int __cdecl d2_ShowModalMessageBox(int, int);
char* __cdecl he_StartHandlungSearch(int, int, int);
char* __cdecl he_fn_Handlung(void);
int __cdecl cm_SendSetHE(int, int);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDTL 0x005c3cc0 */
void __cdecl d2_RunFireExtinguishDialog(char* e)
{
	char* ent;
	int id;
	int win;
	int base;
	int h1;
	int h2;
	int h3;
	int cur;
	int n;
	float p;

	id = *(int*) (e + 1);
	win = d2_LoadForm(0, 0, "Panel\\Gebaeude_Brand_loeschen");
	d2_CenterDialogWindows(win);
	d2_SetForm(win, 1);
	io_AppendText(0x17e4, e);
	d2_SetForm(win, 2);
	base = io_AppendText(0x17e5, 1, 2, 4);
	h1 = d2_GetWindowListItem(win, 2, base);
	h2 = d2_GetWindowListItem(win, 2, base + 1);
	h3 = d2_GetWindowListItem(win, 2, base + 2);
	d2_SetOverlayAnimation(0, 0);
	main_RunFrameLoop(0, 0x677c7);
	do {
		cur = gm_SearchTable67(id);
		if ((*(unsigned char*) (e + 0x5b) & 4) != 0 || cur == 0) {
			d2_DialogCloseRequested = 1;
		}
		n = 1;
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
		if (d2_DialogButtonAction == 2) {
			if (d2_CurrentElementId == h1) {
				p = 0.2f;
			} else if (d2_CurrentElementId == h2) {
				p = 0.5f;
				n = 2;
			} else if (d2_CurrentElementId == h3) {
				p = 0.8f;
				n = 4;
			} else {
				goto next;
			}
			if (d2_CheckActionBlocker(((char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot]), n)) {
				gm_ModifyHealth(*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id, -n);
				d2_SetFormVisibility(win, 0);
				if (gm_RandomFloat01() < p) {
					ent = he_StartHandlungSearch(1, 0, 0x4f);
					if (ent != 0) {
						do {
							if (*(int*) (ent + 0xac) == *(int*) (e + 1)) {
								*(int*) (ent + 0x84) = cm_SendSetHE(-1, (int) ent);
								d2_ShowModalMessageBox((*(int*) 0x14ab2fc), 4);
								goto done;
							}
							ent = he_fn_Handlung();
						} while (ent != 0);
					}
done:
					d2_DialogCloseRequested = 1;
					d2_SetFormVisibility(win, 1);
				} else {
					d2_ShowModalMessageBox((*(int*) 0x14ab300), 4);
					d2_SetFormVisibility(win, 1);
				}
			}
		} else if (d2_DialogButtonAction == n) {
			d2_DialogCloseRequested = n;
		}
next:
		if (main_RunFrameLoop((void*) d2_RunFireExtinguishDialog, 0x677c7) == 0) {
			break;
		}
	} while (1);
	d2_DestroyForm(win);
}
