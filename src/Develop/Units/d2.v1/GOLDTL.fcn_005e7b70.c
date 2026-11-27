#include <stdio.h>

// SIZE 0x1c
typedef struct {
	int win;
	int items[6];
} CARD_ROW_WIN;

// SIZE 0x34
typedef struct {
	int pad0;
	unsigned char* info;
	int icon;
	char padc[0x20];
	int fixed;
	char pad30[4];
} CARD_PLAYER_SLOT;

// SIZE 0x3cc
typedef struct {
	char pad0[0xc];
	int w;
	int h;
	char pad14[0x3b8];
} D2_CARD_WIN;

// SIZE 0x2f4
typedef struct {
	char pad0[0x18];
	int w;
	char pad1c[0x44];
	int x60;
	char pad64[8];
	int x6c;
	char pad70[0x284];
} D2_CARD_CTL;

// SIZE 0x54
typedef struct {
	char pad0[0x52];
	short w;
} D2_CARD_GFX;

// SIZE 0x21c
typedef struct {
	char pad0[0x18c];
	int icon;
	char pad190[0x8c];
} CARD_PLAYER_ENT;

extern CARD_ROW_WIN g_6ad584[];
extern CARD_PLAYER_SLOT g_7765a0[];
#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;
extern char* g_772500;
extern char g_7f4ca0[];
extern char* txt_TextEntries[];
extern int d2_CurrentWindowId;
extern unsigned short g_774970;
extern short g_776658;
extern int g_664454;

char* __cdecl io_AppendText(int, ...);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d2_SetElementFont(int, int);
int __cdecl d2_AddElementToWindow(int x, int y, int gfx, int win);

/* ADDRESS: GOLDTL 0x005e7b70 */

/* Lays out one row of the panel: caption, icon, then one button per item. */
void __cdecl d2_LayoutCardGameRow(int row, int count, int* list)
{
	char buf[0x100];
	int w;
	int h;
	int x;
	int y;
	int i;
	int c;
	int icon;
	unsigned char* info;

	d2_CurrentWindowId = g_6ad584[row].win;
	io_AppendText((int) "$C");
	w = ((D2_CARD_WIN*)g_1015f40)[d2_CurrentWindowId].w;
	h = ((D2_CARD_WIN*)g_1015f40)[d2_CurrentWindowId].h;
	x = (w - 0xc4) / 2;
	info = g_7765a0[row].info;
	sprintf(buf, "%s %s %s", txt_TextEntries[(info[9] ? 0x11e : 0x114) + info[0xd]], info + 0x30, info + 0x40);
	c = d2_ShowTxt(0, 5, buf, g_6ad584[row].win);
	((D2_CARD_CTL*)g_1015ea0)[c].w = w;
	((D2_CARD_CTL*)g_1015ea0)[c].x6c = 1;
	d2_SetElementFont(c, 0x54);
	if (row != 0) {
		icon = g_7765a0[row].icon;
		y = h / 2;
		d2_AddElementToWindow(x - 0x37, y - ((D2_CARD_GFX*)g_772500)[icon].w / 2, icon, g_6ad584[row].win);
	} else {
		icon = ((CARD_PLAYER_ENT*)g_7f4ca0)[g_774970].icon;
		y = h / 2;
		d2_AddElementToWindow(x - 0x37, y - ((D2_CARD_GFX*)g_772500)[icon].w / 2, icon, g_6ad584[row].win);
	}
	for (i = 0; i < count; i++, x += 0x20) {
		if (g_7765a0[row].fixed >= 0) {
			g_6ad584[row].items[i] = d2_AddElementToWindow(x, y - ((D2_CARD_GFX*)g_772500)[g_664454 + 0x775].w / 2, g_664454 + 0x775, g_6ad584[row].win);
		} else if (row != 0 && i < 2 && g_776658 == 4) {
			g_6ad584[row].items[i] = d2_AddElementToWindow(x, y - ((D2_CARD_GFX*)g_772500)[g_664454 + 0x775].w / 2, g_664454 + 0x775, g_6ad584[row].win);
		} else {
			g_6ad584[row].items[i] = d2_AddElementToWindow(x, y - ((D2_CARD_GFX*)g_772500)[list[i] + 0x775].w / 2, list[i] + 0x775, g_6ad584[row].win);
			if (row == 0 && i < 2) {
				((D2_CARD_CTL*)g_1015ea0)[g_6ad584[0].items[i]].x60 = 1;
			}
		}
	}
}

