#include <stdio.h>

// SIZE 0x1c
typedef struct {
	int win;
	int items[6];
} Row_5e7b70;

// SIZE 0x34
typedef struct {
	int pad0;
	unsigned char* info;
	int icon;
	char padc[0x20];
	int fixed;
	char pad30[4];
} Slot_5e7b70;

// SIZE 0x3cc
typedef struct {
	char pad0[0xc];
	int w;
	int h;
	char pad14[0x3b8];
} Win_5e7b70;

// SIZE 0x2f4
typedef struct {
	char pad0[0x18];
	int w;
	char pad1c[0x44];
	int x60;
	char pad64[8];
	int x6c;
	char pad70[0x284];
} Ctl_5e7b70;

// SIZE 0x54
typedef struct {
	char pad0[0x52];
	short w;
} Gfx_5e7b70;

// SIZE 0x21c
typedef struct {
	char pad0[0x18c];
	int icon;
	char pad190[0x8c];
} Ent_5e7b70;

extern Row_5e7b70 g_6ad584[];
extern Slot_5e7b70 g_7765a0[];
extern Win_5e7b70 g_1015f40[];
extern Ctl_5e7b70* g_1015ea0;
extern Gfx_5e7b70* g_772500;
extern Ent_5e7b70 g_7f4ca0[];
extern char* g_14a5320[];
extern int g_772514;
extern unsigned short g_774970;
extern short g_776658;
extern int g_664454;

char* __cdecl fcn_00519190(int, ...);
int __cdecl fcn_0046fac0(int, int, char*, int);
void __cdecl fcn_00472900(int, int);
int __cdecl fcn_0046f740(int x, int y, int gfx, int win);

// FUNCTION: GOLDTL 0x5e7b70
// SIZE: 691

/* Lays out one row of the panel: caption, icon, then one button per item. */
void __cdecl fcn_005e7b70(int row, int count, int* list)
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

	g_772514 = g_6ad584[row].win;
	fcn_00519190((int) "$C");
	w = g_1015f40[g_772514].w;
	h = g_1015f40[g_772514].h;
	x = (w - 0xc4) / 2;
	info = g_7765a0[row].info;
	sprintf(buf, "%s %s %s", g_14a5320[(info[9] ? 0x11e : 0x114) + info[0xd]], info + 0x30, info + 0x40);
	c = fcn_0046fac0(0, 5, buf, g_6ad584[row].win);
	g_1015ea0[c].w = w;
	g_1015ea0[c].x6c = 1;
	fcn_00472900(c, 0x54);
	if (row != 0) {
		icon = g_7765a0[row].icon;
		y = h / 2;
		fcn_0046f740(x - 0x37, y - g_772500[icon].w / 2, icon, g_6ad584[row].win);
	} else {
		icon = g_7f4ca0[g_774970].icon;
		y = h / 2;
		fcn_0046f740(x - 0x37, y - g_772500[icon].w / 2, icon, g_6ad584[row].win);
	}
	for (i = 0; i < count; i++, x += 0x20) {
		if (g_7765a0[row].fixed >= 0) {
			g_6ad584[row].items[i] = fcn_0046f740(x, y - g_772500[g_664454 + 0x775].w / 2, g_664454 + 0x775, g_6ad584[row].win);
		} else if (row != 0 && i < 2 && g_776658 == 4) {
			g_6ad584[row].items[i] = fcn_0046f740(x, y - g_772500[g_664454 + 0x775].w / 2, g_664454 + 0x775, g_6ad584[row].win);
		} else {
			g_6ad584[row].items[i] = fcn_0046f740(x, y - g_772500[list[i] + 0x775].w / 2, list[i] + 0x775, g_6ad584[row].win);
			if (row == 0 && i < 2) {
				g_1015ea0[g_6ad584[0].items[i]].x60 = 1;
			}
		}
	}
}
