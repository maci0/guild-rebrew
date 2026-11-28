/* GOLD target GUI control layout.  D2_CONTROL_GOLD is the proposed common
 * view for GuiEnt, GOLD D2_TEXT_ENTRY and local 0x2ec raw control views.
 * Existing GuiEnt consumers remain unchanged until a reviewed migration.
 * GoldTL has a distinct 0x2f4 layout; this is not a server layout claim.
 * Neither type allocates table storage.
 * Resolved:
 * - Kept GuiEnt, its caller-used members, and the GuiEnt * table declaration;
 *   the separate proposed view requires reviewed casts and type bindings.
 * - Guarded the proposed view and duplicate-compatible extern for GOLD only.
 * - Kept the overlapping payload as bytes and retained full and low-byte
 *   flag views; value_2e4 is an integer with no asserted GoldTL counterpart.
 */
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
	char pad76[0x78 - 0x76];
	int bild_offset;
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


#if defined(REBREW_GOLD)
/* Proposed GOLD control view; target x86 layout.  This view describes the
 * same runtime records as GuiEnt but is not pointer-type compatible with it.
 * Variant payload accesses, including existing string operations, require
 * separately reviewed byte views. */
/* SIZE 0x2ec */
typedef struct D2_CONTROL_GOLD {
    int value_000;                    /* 0x000 */
    int used;                         /* 0x004 */
    int resource_id;                  /* 0x008 */
    void *data;                       /* 0x00c */
    short x;                          /* 0x010 */
    short y;                          /* 0x012 */
    short width;                      /* 0x014 */
    short height;                     /* 0x016 */
    int kind;                         /* 0x018 */
    short mode;                       /* 0x01c */
    short clip_left;                  /* 0x01e */
    short clip_right;                 /* 0x020 */
    short clip_top;                   /* 0x022 */
    short clip_bottom;                /* 0x024 */
    unsigned char unk_026[2];         /* 0x026 */
    int value_028;                    /* 0x028 */
    int value_02c;                    /* 0x02c */
    void *parent;                     /* 0x030 */
    unsigned char unk_034[4];         /* 0x034 */
    int value_038;                    /* 0x038 */
    int hidden;                       /* 0x03c */
    int value_040;                    /* 0x040 */
    unsigned char unk_044[4];         /* 0x044 */
    int value_048;                    /* 0x048 */
    int value_04c;                    /* 0x04c */
    unsigned char unk_050[0x0c];      /* 0x050 */
    int value_05c;                    /* 0x05c */
    unsigned char unk_060[0x0c];      /* 0x060 */
    unsigned char value_06c;          /* 0x06c */
    unsigned char value_06d;          /* 0x06d */
    unsigned char unk_06e[2];         /* 0x06e */
    int scale;                        /* 0x070 */
    short font;                       /* 0x074 */
    unsigned char unk_076[2];         /* 0x076 */
    int value_078;                    /* 0x078 */
    unsigned char payload[0x144];     /* 0x07c..0x1bf; overlapping views,
                                       * not a proven string bound */
    int flags_1c0;                    /* 0x1c0; low-byte access also used */
    int value_1c4;                    /* 0x1c4 */
    int value_1c8;                    /* 0x1c8 */
    int value_1cc;                    /* 0x1cc */
    int value_1d0;                    /* 0x1d0 */
    int value_1d4;                    /* 0x1d4 */
    int value_1d8;                    /* 0x1d8 */
    int value_1dc;                    /* 0x1dc */
    int value_1e0;                    /* 0x1e0 */
    union { float real; int bits; } value_1e4; /* 0x1e4 */
    unsigned char unknown_1e8[0xf8];  /* 0x1e8 */
    unsigned char direction_2e0;      /* 0x2e0 */
    unsigned char direction_2e1;      /* 0x2e1 */
    unsigned char unknown_2e2[2];     /* 0x2e2 */
    int value_2e4;                    /* 0x2e4; TL correspondence unproven */
    unsigned char unknown_2e8[4];     /* 0x2e8 */
} D2_CONTROL_GOLD;

/* Existing GOLD table pointer; this declaration does not allocate storage. */
extern GuiEnt *g_00f8f080;
#endif /* REBREW_GOLD */

#endif
