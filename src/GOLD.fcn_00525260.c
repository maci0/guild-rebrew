// FUNCTION: GOLD 0x00525260
// SIZE: 532
/* Twin of GOLDTL 0x52a0c0; GOLD has 0x2ec-byte entities (fields 0x10 lower), 0x3c4-byte slots and a 16-bit base value at 0xfb9072. */

// SIZE 0x3c4
typedef struct {
	char pad0[0x274];
	int mode;
	char pad278[0x3b8 - 0x278];
	int h0;
	int h1;
	char pad3c0[0x3c4 - 0x3c0];
} Slot;

// SIZE 0x2ec
typedef struct {
	char pad0[0x4c];
	int f5c;
	char pad50[0x1c0 - 0x50];
	int f1d0;
	char pad1c4[0x1e0 - 0x1c4];
	int owner;
	char pad1e4[0x2ec - 0x1e4];
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

extern int g_623864;
extern int g_623868;
extern char g_6f2368;
extern char g_6f2f94;
extern short g_fb9072;
extern char g_624144[];
extern char g_624158[];
extern int g_6ed938;
#include "client_types.h"
extern Slot_f8f110 g_f8f110[];
extern char* g_f8f080;
extern Row g_75f280[32];
extern Obj g_770b80[];

int __cdecl fcn_004741e0(short a, int b, char* s);
void __cdecl fcn_00475f60(int h, int mode);
int __cdecl fcn_00475b70(int h, int a, int b);
void __cdecl fcn_00475580(int h, int v);
int __cdecl fcn_00473340(int a, int b, int c, int d, int e);

void __cdecl fcn_00525260(int unused, char arg)
{
	int owner;
	int id;
	int i;

	if (g_623864 == -1) {
		g_6f2368 = arg;
		if (g_6f2f94 == 0) {
			g_623864 = fcn_004741e0((short) (g_fb9072 - 0x68), 0x106, g_624158);
		} else {
			g_623864 = fcn_004741e0((short) (g_fb9072 - 0x68), 0x106, g_624144);
		}
		fcn_00475f60(g_623864, 1);
		owner = g_6ed938;
		fcn_00475f60(g_623864, 2);
		id = fcn_00475b70(g_623864, 2, 0);
		((Ent*)g_f8f080)[id].f1d0 = 3;
		((Slot*)g_f8f110)[g_6ed938].h0 = id;
		((Ent*)g_f8f080)[id].owner = owner;
		id = fcn_00475b70(g_623864, 2, 1);
		((Ent*)g_f8f080)[id].f1d0 = 3;
		((Slot*)g_f8f110)[g_6ed938].h1 = id;
		((Ent*)g_f8f080)[id].owner = owner;
		((Slot*)g_f8f110)[owner].mode = 0x4e;
		if (g_623864 != -1) {
			if (g_623868 != -1) {
				fcn_00475580(g_623868, 0);
			}
			fcn_00475f60(g_623864, 1);
			for (i = 0; i < 32; i++) {
				g_75f280[i].a = -1;
				g_75f280[i].b = -1;
				g_75f280[i].c = -1;
				g_75f280[i].d = 0xffff;
				g_75f280[i].e = -1;
				g_75f280[i].f = -1;
				g_75f280[i].g = 0;
			}
			fcn_00475f60(g_623864, 2);
			id = fcn_00473340(0x11, 4, 0x51d, g_6ed938, -2);
			((Ent*)g_f8f080)[id].f5c = 1;
			((Ent*)g_f8f080)[id].f1d0 = 3;
			for (i = 0; i < 768; i++) {
				if (g_770b80[i].marked != 0 && g_770b80[i].group != 0) {
					g_770b80[i].marked = 0;
				}
			}
		}
	}
}
