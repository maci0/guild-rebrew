extern int d2_CurrentWindowId;
extern char* d2_FileObjTable;
extern char* d2_CurrentWindow;
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int d2_DialogButtonAction;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char str_empty[];

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
void __cdecl d2_SetOverlayAnimation(int, int);
char* __cdecl gm_LookupEntityRecordById(int);
void* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void* __cdecl gm_FindNextFilteredEntity(void);
char* __cdecl gm_QueryEntities(int, ...);
int __cdecl d2_ClearWindowChildren(int, int);
int __cdecl io_AppendText(char* fmt, ...);
int __cdecl d2_BuildPersonStatusDesc(void*);
void __cdecl d2_DrawPersonCard(int, int, int, int, void*, int);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl cm_SendLogAction(char*);
int __cdecl cm_RequestJoinLeaveElection(int*);
void __cdecl cm_SendTraceEnd(char*);
int __cdecl cm_GetCommandStatus(int);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl io_FormatTextBuffer(char*, int, int);
int __cdecl d2_ShowModalMessageBox(char*, int);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDTL 0x005a2080 */
void __cdecl d2_RunPlayerStammtischDialog(int building, int table)
{
	int sel[4][0xe];
	int join[3];
	int win;
	int btn;
	int next;
	int i;
	int n;
	int found;
	int state;
	int changed;
	int x0;
	int y0;
	int *p;
	int *q;
	unsigned int *ip;
	unsigned short* ent;

	for (i = 0; i < 4; i++) {
		for (n = 0; n < 0xe; n++) {
			sel[i][n] = 0;
		}
	}
	btn = -1;
	win = d2_LoadForm(0, 0, "locations\\Wirtshaus\\Stammtisch");
	d2_CenterDialogWindows(win);
	d2_SetForm(win, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetOverlayAnimation(0, 0);
	ip = (unsigned int*) (table + 0x1c);
	for (;;) {
		i = 0;
		state = 0;
		n = 0;
		changed = 0;
		p = sel[0];
		q = (int*) ip;
		for (i = 0; i < 4; i++) {
			ent = (unsigned short*) gm_LookupEntityRecordById(*q);
			if ((int) ent != p[0]) {
				changed = 1;
			}
			if (ent != 0) {
				p[0] = (int) ent;
				n++;
				p += 0xe;
				if (*(int*) (ent + 2) == *(int*) (gm_LocalPlayerSlot * 0x21c + 0x7f4ca4)) {
					state = 1;
				}
			}
			q++;
		}
		if (n == 4) {
			if (state == 0) {
				state = 2;
			}
		} else if (n < 4) {
			if (state == 0) {
				state = 3;
				next = (int) gm_StartFilteredEntitySearch(1, 0, 0x37);
				while (next != 0) {
					next = (int) gm_QueryEntities(*(int*) (next + 0x5d), 2, 6, 0, 0x12d);
					if (next != 0) {
						i = 0;
						p = (int*) (next + 0x1c);
						do {
							if (*p == *(int*) (gm_LocalPlayerSlot * 0x21c + 0x7f4ca4)) {
								state = 4;
								break;
							}
							p++;
							i++;
						} while (i < 4);
					}
					next = (int) gm_FindNextFilteredEntity();
				}
			}
			for (i = n; i < 4; i++) {
				sel[i][0] = 0;
			}
		}
		if (changed) {
			d2_SetForm(win, 1);
			d2_ClearWindowChildren(d2_CurrentWindowId, 1);
			io_AppendText((char*) 0x188c, building);
			if (n == 0) {
				io_AppendText((char*) 0x188e);
			} else {
				x0 = *(int*) (d2_CurrentWindow + 0xc) + *(short*) (d2_FileObjTable + 0x1ebd8) * -2;
				p = sel[0];
				for (i = 0; i < n; i++) {
					p[0xc] = 1;
					p[4] = (i % 2 + 1) * (x0 / 3) + -10 + (x0 % 3) / 2 + (*(short*) (d2_FileObjTable + 0x1ebd8) + 10) * (i % 2);
					p[5] = (i / 2) * 0x82 + 100;
					d2_BuildPersonStatusDesc(p);
					d2_DrawPersonCard(p[4], p[5], d2_CurrentWindowId, 0x54, p, 1);
					p += 0xe;
				}
			}
			d2_SetForm(win, 2);
			d2_ClearWindowChildren(d2_CurrentWindowId, 1);
			io_AppendText(str_dollar_C);
			btn = -1;
			if (state == 2) {
				io_AppendText((char*) 0x1892);
			} else if (state == 4) {
				io_AppendText((char*) 0x1891);
			} else if (state == 3) {
				btn = d2_GetWindowListItem(win, 2, io_AppendText((char*) 0x188f));
			} else if (state == 1) {
				btn = d2_GetWindowListItem(win, 2, io_AppendText((char*) 0x1890));
			}
		}
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		} else if (d2_DialogButtonAction != -1 && d2_CurrentElementId == btn && state == 3) {
			char buf[0x200] = "";

			if (d2_DialogButtonAction == 2) {
				join[0] = 0x6a6f696e;
				join[2] = *(int*) (building + 1);
				join[1] = *(int*) (gm_LocalPlayerSlot * 0x21c + 0x7f4ca4);
				cm_SendLogAction("stammtisch join H-Plr");
				next = cm_RequestJoinLeaveElection(join);
				cm_SendTraceEnd("stammtisch join H-Plr");
				n = cm_GetCommandStatus(next);
				while (n == 0) {
					main_RunFrameLoop(0, 0x20007);
					n = cm_GetCommandStatus(next);
				}
				if (n == 1) {
					io_FormatTextBuffer(buf, 0x189e, building);
				} else {
					io_FormatTextBuffer(buf, 0x189f, building);
				}
			}
			if (buf[0] != 0) {
				d2_ShowModalMessageBox(buf, 0);
			}
		}
		if (!main_RunFrameLoop((void*) 0x5a1e40, 0x677c7)) {
			d2_DestroyForm(win);
			return;
		}
	}
}
