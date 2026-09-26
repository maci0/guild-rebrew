void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

// SIZE 0x5c
typedef struct
{
	int x0;
	int w;
	int h;
	char pc[0x50];
} fcn_0046eda0_Desc;

typedef struct
{
	int x0;
	int w;
	int h;
} fcn_0046eda0_Surf;

// SIZE 0x2f4
typedef struct
{
	char pad0[0x14];
	int y;
	int w;
	int h;
	char pad20[0x2c - 0x20];
	int right;
	char pad30[4];
	int bottom;
	char pad38[0x2f4 - 0x38];
} fcn_0046eda0_Ent;

typedef struct
{
	char pad0[0x50];
	short ox;
	short oy;
	char pad54[0x1a0 - 0x54];
	short gx;
	char pad1a2[0x39a - 0x1a2];
	short gy;
} fcn_0046eda0_Grid;

typedef struct
{
	char pad0[0x54];
} fcn_0046eda0_Def;

// SIZE 0x3cc
typedef struct
{
	int pad0;
	int x;
	int y;
	int w;
	int h;
	unsigned char flags;
	char pad15[0x28 - 0x15];
	int* children;
	int count;
	void* buf30;
	void* buf34;
	fcn_0046eda0_Surf* surf;
	char pad3c[0x27c - 0x3c];
	int ent;
	char pad280[0x288 - 0x280];
	int def;
	char pad28c[0x290 - 0x28c];
	int used;
	char pad294[0x3cc - 0x294];
} fcn_0046eda0_Win;

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;
extern char* g_772500;
extern int g_1040490;
extern int g_1040494;

void __cdecl fcn_0041ddd0(void* p);
fcn_0046eda0_Surf* __cdecl fcn_004770a0(fcn_0046eda0_Desc* d, int kind);
void __cdecl fcn_00476620(int a1, int a2, int w, int h, fcn_0046eda0_Surf* src, int a6, int a7, fcn_0046eda0_Surf* dst);
void __cdecl fcn_00475f80(fcn_0046eda0_Surf* s);

// FUNCTION: GOLDTL 0x0046eda0
// SIZE: 701
void __cdecl fcn_0046eda0(int w, int h, int win)
{
	fcn_0046eda0_Desc d;
	fcn_0046eda0_Win* p;
	fcn_0046eda0_Ent* e;
	fcn_0046eda0_Grid* g;
	fcn_0046eda0_Surf* s;
	int dw;
	int dh;
	int i;
	int ox;
	int oy;
	int gx;
	int gy;

	p = &((fcn_0046eda0_Win*)g_1015f40)[win];
	if (p->used == 0) {
		return;
	}
	dw = w - p->w;
	dh = h - p->h;
	for (i = 0; i < p->count; i++) {
		e = &((fcn_0046eda0_Ent*)g_1015ea0)[p->children[i]];
		if (p->y + p->h + dh < e->y + e->h) {
			dh = e->y - p->y - p->h + e->h + 8;
		}
	}
	if (p->buf30 != 0) {
		fcn_0041ddd0(p->buf30);
		p->buf30 = 0;
	}
	if (p->buf34 != 0) {
		fcn_0041ddd0(p->buf34);
		p->buf34 = 0;
	}
	if (p->surf != 0) {
		memset(&d, 0, sizeof(d));
		d.w = w;
		d.h = h;
		s = fcn_004770a0(&d, 0xb);
		fcn_00476620(0, 0, p->surf->w, p->surf->h, p->surf, 0, 0, s);
		fcn_00475f80(p->surf);
		p->surf = s;
	}
	p->w += dw;
	p->h += dh;
	if (p->flags & 4) {
		g = (fcn_0046eda0_Grid*)&((fcn_0046eda0_Def*)g_772500)[p->def];
		ox = g->ox;
		oy = g->oy;
		gx = g->gx;
		gy = g->gy;
		p->w = (p->w - ox * 2) / gx * gx + ox * 2;
		p->h = (p->h - oy * 2) / gy * gy + oy * 2;
	}
	e = &((fcn_0046eda0_Ent*)g_1015ea0)[p->ent];
	e->bottom = p->y + p->h;
	e->right = p->w + p->x;
	if (p->y + p->h > g_1040490) {
		p->h = g_1040490 - p->y;
	}
	if (p->x + p->w > g_1040494) {
		p->w = g_1040494 - p->x;
	}
	if (p->flags & 4) {
		g = (fcn_0046eda0_Grid*)&((fcn_0046eda0_Def*)g_772500)[p->def];
		ox = g->ox;
		oy = g->oy;
		gx = g->gx;
		gy = g->gy;
		p->w = (p->w - ox * 2) / gx * gx + ox * 2;
		p->h = (p->h - oy * 2) / gy * gy + oy * 2;
	}
	for (i = 0; i < p->count; i++) {
		e = &((fcn_0046eda0_Ent*)g_1015ea0)[p->children[i]];
		e->bottom = p->y + p->h;
		e->right = p->w + p->x;
	}
	e = &((fcn_0046eda0_Ent*)g_1015ea0)[p->ent];
	e->w = p->w;
	e->h = p->h;
}
