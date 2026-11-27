


// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	char pad8[0x1c4];
	unsigned char flags;
	char pad1cd[0x4f];
};

// SIZE 0x44
struct rec44 {
	int v[0x11];
};

// SIZE 0x58
struct result {
	int kind;
	int cost;
	int f8;
	unsigned char fc;
	char padd[3];
	int f10;
	struct rec44 rec;
};

extern char g_7f4ca0[];
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int d2_CurrentWindowId;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int d2_CurrentElementId;
#include "client_dialog_state.h"
extern int g_14b5650;
extern int g_14b5654;

void __cdecl d2_ShowGreenMessageBox(int, int, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl io_AppendText();
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl d2_CheckActionBlocker(struct house*, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

int __cdecl d2_OpenSeanceDialog(int a1, char* s, struct result* out)
{
	int b8;
	int price[3];
	int r;
	int h;
	int b4;
	int b6;
	int cancel;
	int k;
	struct rec44* p;

	r = 0;
	out->cost = 0;
	out->kind = 0;
	out->f8 = *(int*) (s + 0x20);
	out->fc = s[0x24];
	price[0] = 4;
	price[1] = 6;
	price[2] = 8;
	out->f10 = **(int**) (s + 0x2c + *(int*) (s + 0x88) * 0xc);
	p = *(struct rec44**) (s + 0x2c + *(int*) (s + 0x88) * 0xc);
	out->rec = *p;
	if ((((struct house*)g_7f4ca0)[g_774970].flags & 8) != 0) {
		d2_ShowGreenMessageBox(g_14b5650, g_14b5654, 0);
		return 0;
	}
	h = d2_LoadForm(0, 0, "Locations\\Friedhof\\Seance");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetForm(h, 1);
	io_AppendText(0x40ce, 0x40cc);
	d2_SetForm(h, 2);
	b4 = d2_GetWindowListItem(h, 2, io_AppendText(0x40cf, 4));
	b6 = d2_GetWindowListItem(h, 2, io_AppendText(0x40d0, 6));
	b8 = d2_GetWindowListItem(h, 2, io_AppendText(0x40d1, 8));
	cancel = d2_GetWindowListItem(h, 2, io_AppendText(0x40d2));
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (d2_CurrentElementId == cancel) {
				g_774654 = 1;
			} else {
				if (d2_CurrentElementId == b4) {
					k = d2_CheckActionBlocker(&((struct house*)g_7f4ca0)[g_774970], 4);
				} else if (d2_CurrentElementId == b6) {
					k = d2_CheckActionBlocker(&((struct house*)g_7f4ca0)[g_774970], 6) * 2;
				} else if (d2_CurrentElementId == b8) {
					k = d2_CheckActionBlocker(&((struct house*)g_7f4ca0)[g_774970], 8) * 3;
				} else {
					continue;
				}
				if (k != 0) {
					out->kind = k;
					out->cost = price[k - 1];
					r = 1;
					g_774654 = 1;
				}
			}
		}
	} while (main_RunFrameLoop(d2_OpenSeanceDialog, 0x677c7) != 0);
	d2_DestroyForm(h);
	return r;
}
