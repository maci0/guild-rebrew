#include <string.h>

// SIZE 0xf8
typedef struct {
	char pad0[4];
	unsigned char type;
	char pad5[3];
	int key;
	int owner;
	char pad10[0x26];
	unsigned char flags;
	char pad37[0x21];
	int other;

	int extra;
	char pad60[0x98];
} Msg5c23b0;

extern unsigned char g_773d75;
extern int g_100f1dc; extern int g_774654; extern int g_14ce8e0;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char g_7f4ca4[];

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl gm_CalculateGebaeudeValue(void*, int);
int __cdecl gm_AmountToUnits(int, unsigned char);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, void*, int);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl d2_CreateGuiWindow(int, int, int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl gm_SearchTable67(int);
int __cdecl d2_GetControlValue(int);
int __cdecl fcn_0050b750(int, unsigned char);
void __cdecl cm_SendCopyEntityData(Msg5c23b0*);
int __cdecl d2_ShowModalMessageBox(int, int);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDTL 0x005c23b0 */
void __cdecl d2_ShowSellGebaeudeDialog(char* e)
{
	Msg5c23b0 m;
	int id;

	int win;
	int p;
	int v;
	int h;
	int ret;

	id = *(int*) (e + 1);
	win = d2_LoadForm(0, 0, "Panel\\Gebaeude_Verkaufen_pergament");
	d2_CenterDialogWindows(win);
	p = gm_CalculateGebaeudeValue(e, *(char*) (e + 0x5c));
	v = gm_AmountToUnits(p, g_773d75);
	d2_SetForm(win, 2);
	h = d2_GetWindowListItem(win, 2, io_AppendText(0x17c5, e, *(unsigned short*) (g_773d75 * 0x2f4 + 0x8680b4) * 2 + 0x9a8));
	d2_CreateGuiWindow(h, (int) (v * 0.5), (int) (v * 1.5), v);
	d2_SetOverlayAnimation(0, 0);
	main_RunFrameLoop(0, 0x677c7);
	do {
		ret = gm_SearchTable67(id);
		if ((*(unsigned char*) (e + 0x5b) & 4) || ret == 0) {
			g_774654 = 1;
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc == 2) {
			memset(&m, 0, sizeof(m));
			m.type = 0x1b;
			m.owner = -1;
			m.flags = 2;
			m.key = *(int*) (g_7f4ca4 + g_774970 * 0x21c);
			m.other = *(int*) (e + 1);
			m.extra = fcn_0050b750(d2_GetControlValue(h), g_773d75);
			cm_SendCopyEntityData(&m);
			d2_ShowModalMessageBox(*(int*) 0x14ab238, 0);
			g_774654 = 1;
		}
		else if (g_100f1dc == 1) {
			g_774654 = 1;
		}
	} while (main_RunFrameLoop((void*) d2_ShowSellGebaeudeDialog, 0x677c7) != 0);
	d2_DestroyForm(win);
}
