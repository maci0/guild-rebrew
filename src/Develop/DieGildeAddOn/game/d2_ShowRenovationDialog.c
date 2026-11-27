extern char* g_14ab248;
extern char* gm_CityEntity;
extern char g_7f4ca0[];
extern int g_100f1dc;
extern int g_14ce8e0;
extern int d2_CurrentElementId;
#include "client_dialog_state.h"
extern unsigned char g_773d75;
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_DestroyForm(int);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl cm_SendLogAction(char*);
void __cdecl cm_SendTraceEnd(char*);
void __cdecl cm_RequestMoveCredits(int, int, char, int);
int __cdecl cm_SendCopyEntityData(void*);
int __cdecl gm_SearchTable67(int);
char* __cdecl gm_FindBuildingTreasury(char*);
int __cdecl gm_GetEntityTableEntry(char*);
int __cdecl gm_CalculateGebaeudeValue(char*, int);
int __cdecl io_AppendText(int, char*, int, int, int);
int __cdecl gm_CheckEntityStock(char*, int, char);
int __cdecl d2_CheckFundsAndNotify(char*, int, int, char);
int __cdecl d2_ShowModalMessageBox(char*, int);
int __cdecl main_RunFrameLoop(void*, int);


/* Renovation order dialog of the currently selected building. The handler
 * polls its own dialog until the user closes it and dispatches the order to
 * the owning building or to the local player entity. */
/* ADDRESS: GOLDTL 0x005c2580 */
void __cdecl d2_ShowRenovationDialog(char* e)
{
	char msg[0xf8];
	float x;
	int p;
	int n;
	int id;
	int a;
	int b;
	int c;
	int h0;
	int h1;
	int h2;
	int h3;
	int dur;
	int val;
	int win;
	int h;

	id = *(int*) (e + 1);
	p = gm_CalculateGebaeudeValue(e, 100);
	x = (float) p;
	n = 100 - (int) *(char*) (e + 0x5c);
	if (n <= 0) {
		d2_ShowModalMessageBox(g_14ab248, 4);
		return;
	}
	x = x * 0.005f;
	if (128.0f > x) {
		x = 128.0f;
	}
	win = d2_LoadForm(0, 0, "Panel\\Gebaeude_Renovieren");
	d2_CenterDialogWindows(win);
	d2_SetForm(win, 2);
	a = (int) (n * x);
	b = (int) (n * x * 0.5);
	c = (int) (n * x * 0.25);
	h = io_AppendText(0x17c8, e, c, b, a);
	h0 = d2_GetWindowListItem(win, 2, h);
	h1 = d2_GetWindowListItem(win, 2, h + 1);
	h2 = d2_GetWindowListItem(win, 2, h + 2);
	h3 = d2_GetWindowListItem(win, 2, h + 3);
	d2_SetOverlayAnimation(0, 0);
	main_RunFrameLoop(0, 0x677c7);
	do {
		p = gm_SearchTable67(id);
		if (!((*(unsigned char*) (e + 0x5b) & 4) == 0 && p != 0)) {
			g_774654 = 1;
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (d2_CurrentElementId != h0 && d2_CurrentElementId != h1 && d2_CurrentElementId != h2) {
				if (d2_CurrentElementId == h3) {
					g_774654 = 1;
				}
			} else {
				val = 0;
				dur = 0;
				*(unsigned char*) (msg + 4) = 0x1c;
				*(int*) (msg + 8) = ((ENTITY_RECORD*)g_7f4ca0)[(unsigned int) g_774970].entity_id;
				*(int*) (msg + 0xc) = -1;
				*(unsigned char*) (msg + 0x36) = 1;
				*(int*) (msg + 0x58) = *(int*) (e + 1);
				if (d2_CurrentElementId == h0) {
					dur = (int) (n * 0.25);
					val = c;
				} else if (d2_CurrentElementId == h1) {
					dur = (int) (n * 0.5);
					val = b;
				} else if (d2_CurrentElementId == h2) {
					dur = n;
					val = a;
				}
				if (*(unsigned short*) (e + 0x27) == *(unsigned short*) gm_CityEntity) {
					char* q;

					q = gm_FindBuildingTreasury(e);
					if (q != 0 && d2_CheckFundsAndNotify(q, *(int*) (q + 0x14), val, (char) g_773d75) != 0) {
						*(int*) (msg + 0x5c) = dur;
						cm_SendLogAction("renovieren");
						cm_RequestMoveCredits(-1, *(int*) (q + 2), (char) g_773d75, val);
						cm_SendCopyEntityData(msg);
						cm_SendTraceEnd("renovieren");
						g_774654 = 1;
					}
				} else if (gm_CheckEntityStock((char*)&((ENTITY_RECORD*)g_7f4ca0)[(unsigned int) g_774970], val, (char) g_773d75) != 0) {
					char* q;

					q = gm_GetEntityTableEntry((char*)&((ENTITY_RECORD*)g_7f4ca0)[(unsigned int) g_774970]);
					if (q != 0) {
						*(int*) (q + 0x44) += val;
					}
					*(int*) (msg + 0x5c) = dur;
					cm_SendLogAction("renovieren");
					cm_RequestMoveCredits(-1, ((ENTITY_RECORD*)g_7f4ca0)[(unsigned int) g_774970].entity_id, (char) g_773d75, val);
					cm_SendCopyEntityData(msg);
					cm_SendTraceEnd("renovieren");
					g_774654 = 1;
				}
			}
		}
	} while (main_RunFrameLoop((void*) d2_ShowRenovationDialog, 0x677c7) != 0);
	d2_DestroyForm(win);
}
