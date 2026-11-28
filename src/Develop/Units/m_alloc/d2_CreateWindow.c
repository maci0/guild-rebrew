#include <string.h>

/* Window record: 0x3cc bytes, 96 slots after the 0x1015f40 base. */
typedef struct WinRec {
	char pad0[4];
	int x4;              /* 0x004 */
	int x8;              /* 0x008 */
	int xc;              /* 0x00c */
	int x10;             /* 0x010 */
	unsigned int flags;  /* 0x014 */
	int x18;             /* 0x018 */
	int x1c;             /* 0x01c */
	int x20;             /* 0x020 */
	int x24;             /* 0x024 */
	int x28;             /* 0x028 */
	char pad2c[4];
	int x30;             /* 0x030 */
	int x34;             /* 0x034 */
	int x38;             /* 0x038 */
	int x3c;             /* 0x03c */
	char pad40[0x214];   /* 0x040..0x253 */
	int x254;            /* 0x254 */
	int x258;            /* 0x258 */
	int x25c;            /* 0x25c */
	char pad260[0x10];   /* 0x260..0x26f */
	unsigned char x270;  /* 0x270 */
	char pad271[3];
	int x274;            /* 0x274 */
	int x278;            /* 0x278 */
	int x27c;            /* 0x27c */
	int x280;            /* 0x280 */
	int x284;            /* 0x284 */
	int x288;            /* 0x288 */
	int x28c;            /* 0x28c */
	int used;            /* 0x290 */
	char pad294[0x104];  /* 0x294..0x397 */
	int x398;            /* 0x398 */
	char pad39c[4];
	int x3a0;            /* 0x3a0 */
	float x3a4;          /* 0x3a4 */
	int x3a8;            /* 0x3a8 */
	int x3ac;            /* 0x3ac */
	int x3b0;            /* 0x3b0 */
	int x3b4;            /* 0x3b4 */
	int x3b8;            /* 0x3b8 */
	int x3bc;            /* 0x3bc */
	int x3c0;            /* 0x3c0 */
	int x3c4;            /* 0x3c4 */
	int x3c8;            /* 0x3c8 */
} WinRec;
// SIZE 0x3cc

/* Draw entity: 0x2f4 bytes in the g_1015ea0 table. */
typedef struct Ent {
	char pad0[8];
	int x8;              /* 0x008 */
	WinRec* rec;         /* 0x00c */
	int x10;             /* 0x010 */
	int x14;             /* 0x014 */
	int x18;             /* 0x018 */
	int x1c;             /* 0x01c */
	int x20;             /* 0x020 */
	int x24;             /* 0x024 */
	int x28;             /* 0x028 */
	int x2c;             /* 0x02c */
	int x30;             /* 0x030 */
	int x34;             /* 0x034 */
	char pad38[8];
	int x40;             /* 0x040 */
	char pad44[0x44];
	int x88;             /* 0x088 */
	char pad8c[0x268];
} Ent;
// SIZE 0x2f4

#include "Develop/Units/d2.v1/d2_gui.h"
extern int d2_CurrentWindowId;
extern char* d2_CurrentWindow;
extern int g_77259c;
extern int g_67d390;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_67d3a0;
extern char d2_Windows[];

int __cdecl d2_CreateSurface(int* p, int kind);
void __cdecl d2_ClearSurface(int h);
int __cdecl d2_AllocateElement(void);
int __cdecl m_alloc(int size, char* tag);
void __cdecl d2_AddElementToWindow(int x, int y, int id, int layer);

/* ADDRESS: GOLDTL 0x0046e940 */
/* ADDRESS: GOLDDE 0x00461f70 */
int __cdecl d2_CreateWindow(unsigned int x, unsigned int y, unsigned int width, int height,
	unsigned int flags)
{
	WinRec* rec;
	int v9[23];
	unsigned int* p;
	int i;
	int ei;
	int h;

	g_77259c++;
	if (g_77259c > 0x60) {
		g_77259c = 1;
	}
	for (i = 0, p = (unsigned int*) (d2_Windows + 0x290); (int) p < (int) (d2_Windows + 0x16f10); p += 0xf3, i++) {
		if (*p == 0) {
			goto found;
		}
	}
	return -1;
found:
	if (i == -1) {
		return i;
	}
	rec = &((WinRec*) d2_Windows)[i];
	rec->x4 = x;
	rec->xc = width;
	rec->x8 = y;
	rec->x10 = height;
	rec->flags = flags;
	rec->x18 = 4;
	rec->x1c = 4;
	rec->x20 = 4;
	rec->x24 = 4;
	rec->x3a0 = 0;
	rec->x270 = 4;
	rec->x274 = 0;
	if (flags & 4) {
		rec->x288 = g_67d3a0;
	}
	if (flags & 0x200) {
		rec->x254 = height;
		rec->x258 = -height;
		rec->x25c = -height;
	}
	if (flags & 1) {
		rec->x3a4 = 0.65f;
	}
	if (flags & 0x1000) {
		memset(v9, 0, sizeof(v9));
		v9[1] = width;
		v9[2] = height;
		h = d2_CreateSurface(v9, 0xb);
		rec->x30 = h;
		if (h == 0) {
			return 0;
		}
	}
	if ((rec->flags & 1) && (rec->flags & 0x1000)) {
		memset(v9, 0, sizeof(v9));
		v9[1] = rec->xc;
		v9[2] = rec->x10;
		h = d2_CreateSurface(v9, 0xb);
		rec->x34 = h;
		if (h == 0) {
			return 0;
		}
	}
	if (rec->flags & 0x10000) {
		memset(v9, 0, sizeof(v9));
		v9[1] = rec->xc;
		v9[2] = rec->x10;
		v9[10] = 0x15;
		h = d2_CreateSurface(v9, 10);
		rec->x38 = h;
		d2_ClearSurface(h);
		if (rec->x38 == 0) {
			return 0;
		}
	}
	ei = d2_AllocateElement();
	((D2_CONTROL_TL*)d2_Controls)[ei].kind = 0x40;
	((D2_CONTROL_TL*)d2_Controls)[ei].x = rec->x4;
	((D2_CONTROL_TL*)d2_Controls)[ei].y = rec->x8;
	((D2_CONTROL_TL*)d2_Controls)[ei].width = rec->xc;
	((D2_CONTROL_TL*)d2_Controls)[ei].height = rec->x10;
	((D2_CONTROL_TL*)d2_Controls)[ei].value_008 = i + 0x400;
	((D2_CONTROL_TL*)d2_Controls)[ei].value_088 = i;
	((D2_CONTROL_TL*)d2_Controls)[ei].clip_top = rec->x8;
	((D2_CONTROL_TL*)d2_Controls)[ei].clip_right = rec->xc + rec->x4;
	((D2_CONTROL_TL*)d2_Controls)[ei].clip_left = rec->x4;
	((D2_CONTROL_TL*)d2_Controls)[ei].clip_bottom = rec->x10 + rec->x8;
	((D2_CONTROL_TL*)d2_Controls)[ei].mode = 2;
	((D2_CONTROL_TL*)d2_Controls)[ei].data = rec;
	((D2_CONTROL_TL*)d2_Controls)[ei].parent = 0;
	rec->x278 = 2;
	rec->x27c = ei;
	rec->x280 = 1;
	rec->x398 = -1;
	rec->x28c = d2_DefaultFont;
	rec->x284 = -1;
	rec->used = 1;
	rec->x3bc = -1;
	rec->x3b8 = -1;
	rec->x3c0 = -1;
	rec->x28 = m_alloc(0x600, "d2:win_obj");
	rec->x3a8 = 0;
	rec->x3ac = 0;
	rec->x3b0 = 0;
	rec->x3b4 = 0;
	if (flags & 8) {
		d2_AddElementToWindow(3, 3, g_67d390, i);
	}
	if (flags & 0x20) {
		d2_AddElementToWindow((short) (rec->xc - 0xc), 3, g_67d390 + 1, i);
		d2_AddElementToWindow((short) (rec->xc - 0xc), (short) (rec->x10 - 10), g_67d390 + 2, i);
	}
	if (flags & 0x10) {
		rec->x3c = m_alloc(0x17d0, "d2_t:w->txt");
	}
	d2_CurrentWindowId = i;
	d2_CurrentWindow = (char*) rec;
	return i;
}
