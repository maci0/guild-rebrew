#include <stdio.h>
#include <string.h>

// SIZE 0xc
typedef struct {
	int id;
	int value;
	int p8;
} Item;

// SIZE 0x14
typedef struct {
	char p0[0xe];
	short x;
	short y;
	char p12[2];
} Slot;

// SIZE 0x54
typedef struct {
	char p0[0x50];
	short x50;
	char p52[2];
} Cls;

// SIZE 0xc
typedef struct {
	char p0[4];
	int w;
	int h;
} Ctx;

extern int g_7725c8;
extern int g_7725fc;
extern int g_67d964;
extern int g_7725f8;
extern int g_67d968;
extern int g_67d8cc;
extern short g_7725c4;
extern char* g_7725c0;
#include "client_types.h"
extern Anim_100e7a0 g_100e7a0[0x30];
extern int g_67d378;
extern int g_67d398;

extern char* g_772500;
extern int g_67d3ac;
extern int g_1015ea4;
extern int g_772568;
extern char* g_14a567c;

void __cdecl fcn_0047a040(int, int, int, int);
void __cdecl fcn_0047cba0(int, int, Ctx*, int, int);
void __cdecl fcn_0047cd70(int, Ctx*);
void __cdecl fcn_00472880(int);
int __cdecl d2_GetResourceData(int);
int __cdecl fcn_0047cc80(int, int, Ctx*, int, int, float, int);
void __cdecl fcn_0046bd20(int, int, int, int, Ctx*, char*, int);


/* ADDRESS: GOLDTL 0x00473800 */
void __cdecl fcn_00473800(Ctx* c, int x, int y)
{
	Item* p;
	int old;
	int y1;
	int x1;
	int y0;
	int x0;
	char buf[0x40];
	int k;
	int i;
	int px;
	int py;
	int h;
	int id;
	int v;

	if (g_7725c8 != 0) {
		return;
	}
	x0 = g_7725f8;
	y0 = g_7725fc;
	x1 = g_67d964;
	y1 = g_67d968;
	fcn_0047a040(0, 0, c->w, c->h);
	if (g_67d8cc == -1) {
		fcn_0047cba0(x, y, c, (*(int*)&g_7725c0), (*(int*)&g_7725c4) & 0xffff);
	} else {
		((Slot*)g_100e7a0)[g_67d8cc].x = (short) x;
		((Slot*)g_100e7a0)[g_67d8cc].y = (short) y;
		fcn_0047cd70(g_67d8cc, c);
	}
	old = g_67d378;
	fcn_00472880(g_67d398 + 1);
	k = 0;
	for (i = 0; i < 6; i++) {
		p = &((Item*)DisplayCounters)[i];
		if (p->id != -1) {
			px = x + ((Cls*)g_772500)[g_67d3ac].x50 + k % 3 * 0x1a;
			py = (g_1015ea4 + 0x1a) * (k / 3) + y;
			h = d2_GetResourceData(p->id);
			if (fcn_0047cc80(px, py, c, h, g_772568, 0.5f, 0)) {
				v = p->value;
				id = p->id;
				if (id >= 0xdf && id < 0x3bb) {
					if (v != -1) {
						sprintf(buf, "%i", v);
					} else {
						strcpy(buf, g_14a567c);
					}
				} else {
					sprintf(buf, "%i", v);
				}
				fcn_0046bd20(px - 8, py + 0x18, 0x28, g_1015ea4, c, buf, 8);
			}
			k++;
		}
	}
	fcn_00472880(old);
	fcn_0047a040(x0, y0, x1, y1);
}
