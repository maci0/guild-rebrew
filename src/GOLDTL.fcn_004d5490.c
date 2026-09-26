// FUNCTION: GOLDTL 0x004d5490
// SIZE: 678

#include <stdio.h>
#include <string.h>

#pragma pack(push, 1)
typedef struct Item {
	unsigned short id;
	char pad2[0xa - 2];
	int owner;
	int count;
} Item;
#pragma pack(pop)

typedef struct Group {
	char pad0[0x14];
	int first;
} Group;

typedef struct Party {
	char pad0[0x100];
	int stores[3];
} Party;

typedef struct Slot {
	char pad0[0x18];
	int h;
	char pad1c[0x6c - 0x1c];
	int centered;
	char pad70[0x84 - 0x70];
	int color;
	char pad88[0x2f4 - 0x88];
} Slot;
// SIZE 0x2f4

extern Party* g_772eb4;
extern unsigned short g_774970;
extern int g_772514;
extern char g_6b5c60;
extern Slot* g_1015ea0;
extern char* g_14b52c0;
extern unsigned char g_773d75;

Group* __cdecl fcn_00502cd0(int a, int b, int c, ...);
int __cdecl fcn_0046f740(int x, int y, int id, int win);
int __cdecl fcn_0046fac0(int x, int y, char* text, int win);
void __cdecl fcn_0046f940(int, char*);
float __cdecl fcn_0050bb50(int, unsigned char);
void __cdecl fcn_0051af00(char*, char*, ...);
Item* __cdecl gm_NextEntityQueryMatch(void);

int __cdecl fcn_004d5490(int x, int y, int mode)
{
	int n;
	int total;
	int k;
	int tx;
	int lbl;
	char text[0x100];
	Item* e;
	int px;
	int py;

	n = 0;
	total = 0;
	for (k = 0; k < 3; k++) {
		if (g_772eb4->stores[k] == -1) {
			continue;
		}
		e = (Item*) fcn_00502cd0(0, 2, 7, 1, g_772eb4->stores[k]);
		e = (Item*) fcn_00502cd0(((Group*) e)->first, 1, 0, 0x1dd);
		e = (Item*) fcn_00502cd0(((Group*) e)->first, 1, 5);
		for (; e != 0; e = gm_NextEntityQueryMatch()) {
			if (mode != 0 && (mode != 1 || e->owner != g_774970) && (mode != 2 || e->owner == g_774970)) {
				continue;
			}
			px = x + n % 5 * 0x78;
			py = y + n / 5 * 0x60;
			fcn_0046f740(px, py, 0x525, g_772514);
			fcn_0046f740(px, py, e->id + 0xdf, g_772514);
			tx = px - 0x10;
			lbl = fcn_0046fac0(tx, py - 0xf, &g_6b5c60, g_772514);
			g_1015ea0[lbl].color = 0x56;
			g_1015ea0[lbl].h = 0x50;
			g_1015ea0[lbl].centered = 1;
			sprintf(text, "%i ", e->count);
			strcat(text, g_14b52c0);
			fcn_0046f940(lbl, text);
			lbl = fcn_0046fac0(tx, py + 0x34, &g_6b5c60, g_772514);
			g_1015ea0[lbl].color = 0x56;
			g_1015ea0[lbl].h = 0x50;
			g_1015ea0[lbl].centered = 1;
			fcn_0051af00(text, "%T", (int) fcn_0050bb50(e->id, g_773d75) * e->count);
			fcn_0046f940(lbl, text);
			total = fcn_0050bb50(e->id, g_773d75) * e->count + total;
			n++;
		}
	}
	return total;
}
