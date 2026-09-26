#ifndef GOLD_GUI_H
#define GOLD_GUI_H

/* GOLD GUI tables: g_00f8f080 (GuiEnt pool, 0x300 slots), g_00f8f120
 * (GuiWin array), g_00fb1020 (GuiObj array) and g_006ed964 (GuiEnt* z-order
 * list, 0x300 entries).  Field names come from the functions that use them;
 * padN gaps are unknown. */

typedef struct GuiWin GuiWin;

typedef struct GuiEnt {
	int id;
	char pad04[0x8 - 0x4];
	int f08;
	char* data;
	short x;
	short y;
	short w;
	short f16;
	int kind;
	short f1c;
	short f1e;
	short f20;
	short f22;
	short f24;
	char pad26[0x28 - 0x26];
	int f28;
	int f2c;
	GuiWin* parent;
	char pad34[0x3c - 0x34];
	int hidden;
	int f40;
	char pad44[0x48 - 0x44];
	int dirty;
	int f4c;
	char pad50[0x74 - 0x50];
	short font;
	char pad76[0x7c - 0x76];
	char* buf;
	union {
		char text[0x1c0 - 0x80];
		struct {
			char copy[0x40];
			int len;
		} edit;
		struct {
			int f80;
			int f84;
			unsigned char f88;
			char pad89[0x90 - 0x89];
			int f90;
		} num;
	} u;
	int flags;
	char pad1c4[0x1e0 - 0x1c4];
	int target;
	char pad1e4[0x2ec - 0x1e4];
} GuiEnt;

struct GuiWin {
	char pad00[0x4];
	short x;
	short y;
	short width;
	short height;
	char pad0c[0x18 - 0xc];
	int* list;
	short count;
	char pad1e[0x28 - 0x1e];
	int f28;
	char pad2c[0x248 - 0x2c];
	short scroll;
	char pad24a[0x264 - 0x24a];
	int f264;
	char pad268[0x26c - 0x268];
	int id;
	char pad270[0x27c - 0x270];
	short font;
	char pad27e[0x280 - 0x27e];
	int active;
	char pad284[0x3a8 - 0x284];
	int f3a8;
	int f3ac;
	char pad3b0[0x3c4 - 0x3b0];
};

typedef struct GuiObj {
	int pad0;
	int wins[0x60];
	int count;
	char pad188[0x190 - 0x188];
	int used;
	char pad194[0x19c - 0x194];
	int shown;
	char pad1a0[0x2ac - 0x1a0];
} GuiObj;

#endif
