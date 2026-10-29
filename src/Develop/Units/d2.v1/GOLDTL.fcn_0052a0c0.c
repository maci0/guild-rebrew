

// SIZE 0x3cc
typedef struct {
	char pad0[0x274];
	int mode;
	char pad278[0x3b8 - 0x278];
	int h0;
	int h1;
	char pad3c0[0x3cc - 0x3c0];
} Slot;

// SIZE 0x2f4
typedef struct {
	char pad0[0x5c];
	int f5c;
	char pad60[0x1d0 - 0x60];
	int f1d0;
	char pad1d4[0x1f0 - 0x1d4];
	int owner;
	char pad1f4[0x2f4 - 0x1f4];
} Ent;

// SIZE 0x28
typedef struct {
	int a;
	int pad4;
	int b;
	int c;
	int d;
	int e;
	int f;
	int g;
	char pad20[8];
} Row;

// SIZE 0x21c
typedef struct {
	char pad0[0x164];
	char group;
	char pad165[0x188 - 0x165];
	char marked;
	char pad189[0x21c - 0x189];
} Obj;

extern int g_6a25b4;
extern int g_6a25b8;
extern char g_774724;
extern unsigned char g_77534c;
extern int g_1040494;
extern char g_6a2e94[];
extern char g_6a2ea8[];
extern int g_772514;
#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;
extern Row g_7e30c0[32];
extern char g_7f4ca0[];

int __cdecl fcn_00470820(int a, int b, char* s);
void __cdecl d2_SetForm(int h, int mode);
int __cdecl fcn_00472250(int h, int a, int b);
void __cdecl fcn_00471af0(int h, int v);
int __cdecl fcn_0046f7e0(int a, int b, int c, int d, int e);

void __cdecl fcn_0052a0c0(int unused, char arg)
{
	int owner;
	int id;
	int i;

	if (g_6a25b4 == -1) {
		g_774724 = arg;
		if ((*(char*)&g_77534c) == 0) {
			g_6a25b4 = fcn_00470820(g_1040494 - 0x68, 0x106, g_6a2ea8);
		} else {
			g_6a25b4 = fcn_00470820(g_1040494 - 0x68, 0x106, g_6a2e94);
		}
		d2_SetForm(g_6a25b4, 1);
		owner = g_772514;
		d2_SetForm(g_6a25b4, 2);
		id = fcn_00472250(g_6a25b4, 2, 0);
		((Ent*)g_1015ea0)[id].f1d0 = 3;
		((Slot*)g_1015f40)[g_772514].h0 = id;
		((Ent*)g_1015ea0)[id].owner = owner;
		id = fcn_00472250(g_6a25b4, 2, 1);
		((Ent*)g_1015ea0)[id].f1d0 = 3;
		((Slot*)g_1015f40)[g_772514].h1 = id;
		((Ent*)g_1015ea0)[id].owner = owner;
		((Slot*)g_1015f40)[owner].mode = 0x4e;
		if (g_6a25b4 != -1) {
			if (g_6a25b8 != -1) {
				fcn_00471af0(g_6a25b8, 0);
			}
			d2_SetForm(g_6a25b4, 1);
			for (i = 0; i < 32; i++) {
				g_7e30c0[i].a = -1;
				g_7e30c0[i].b = -1;
				g_7e30c0[i].c = -1;
				g_7e30c0[i].d = 0xffff;
				g_7e30c0[i].e = -1;
				g_7e30c0[i].f = -1;
				g_7e30c0[i].g = 0;
			}
			d2_SetForm(g_6a25b4, 2);
			id = fcn_0046f7e0(0x11, 4, 0x51d, g_772514, -2);
			((Ent*)g_1015ea0)[id].f5c = 1;
			((Ent*)g_1015ea0)[id].f1d0 = 3;
			for (i = 0; i < 768; i++) {
				if (((Obj*)g_7f4ca0)[i].marked != 0 && ((Obj*)g_7f4ca0)[i].group != 0) {
					((Obj*)g_7f4ca0)[i].marked = 0;
				}
			}
		}
	}
}
