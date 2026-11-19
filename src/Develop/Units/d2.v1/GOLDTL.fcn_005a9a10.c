


typedef struct
{
	int x0;
	int x4;
	int x8;
} Ent;
// SIZE 0xc

#include "Develop/DieGildeAddOn/game/entity_record.h"












#include "Develop/DieGildeAddOn/game/game_player.h"
extern int g_14abb2c;
extern int g_14abb28;
extern int g_14abb38;
extern int g_14abb54;
extern int d2_CurrentWindowId;
extern int g_100f1dc;
extern int d2_CurrentElementId;
extern int g_14ce8e0;
#include "client_dialog_state.h"
extern char s_6aaebc[];

int __cdecl fcn_00526120(int, int);
int __cdecl fcn_005a96a0(ENTITY_RECORD*, int);
void __cdecl fcn_00532ef0(void);
int __cdecl fcn_004e8ee0(ENTITY_RECORD*, int, Ent*, int*);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl fcn_004e8d10(ENTITY_RECORD*, int, Ent*);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_ClearWindowChildren(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_005a9a10(void)
{
	int flag;
	int cnt;
	ENTITY_RECORD* p;
	int prev;
	int btns[6];
	Ent list[6];
	int n;
	int dlg;
	int i;
	int sel;

	prev = -1;
	cnt = 0;
	flag = 1;
	p = &((ENTITY_RECORD*)g_7f4ca0)[g_774970];
	if (p->unk_00d < 2) {
		fcn_00526120(g_14abb2c, 0);
		return;
	}
	if (p->unk_165[3] != 0) {
		fcn_005a96a0(p, p->unk_165[3]);
		fcn_00532ef0();
		return;
	}
	if (fcn_004e8ee0(p, 6, list, &cnt) == 0) {
		if (cnt == 0) {
			fcn_00526120(g_14abb28, 0);
		}
		else {
			fcn_00526120(g_14abb38, 0);
		}
		return;
	}
	dlg = fcn_00470820(0, 0, s_6aaebc);
	d2_CenterDialogWindows(dlg);
	d2_SetOverlayAnimation(0, 0);
	g_100f1dc = prev;
	do {
		n = fcn_004e8d10(p, 6, list);
		if (n != prev) {
			flag = 1;
		}
		prev = n;
		if (flag != 0) {
			d2_SetForm(dlg, 1);
			d2_ClearWindowChildren(d2_CurrentWindowId, 1);
			io_AppendText(0x1a01);
			for (i = 0; i < n; i++) {
				btns[i] = fcn_00472250(dlg, 1, io_AppendText(0x1a04, list[i].x0 + 0x253));
			}
			for (i = n; i < 6; i++) {
				btns[i] = -1;
			}
			flag = 0;
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			sel = -1;
			for (i = 0; i < n; i++) {
				if (btns[i] == d2_CurrentElementId) {
					sel = i;
					break;
				}
			}
			if (sel > -1 && sel < n) {
				if (fcn_005a96a0(p, list[sel].x0) == 1) {
					fcn_00526120(g_14abb54, 0);
					g_774654 = 1;
				}
			}
		}
	} while (fcn_005373e0((void*) fcn_005a9a10, 0x677c7) != 0);
	fcn_00471e30(dlg);
	fcn_00532ef0();
}
