// FUNCTION: GOLDTL 0x00533f40
// SIZE: 424

// SIZE 0x3cc
typedef struct {
	char pad0[0x258];
	int f258;
	char pad25c[0x274 - 0x25c];
	int f274;
	char pad278[0x3b8 - 0x278];
	int h0;
	int h1;
	int h2;
	char pad3c4[0x3cc - 0x3c4];
} Slot;

// SIZE 0x2f4
typedef struct {
	char pad0[0x18];
	int f18;
	char pad1c[0x5c - 0x1c];
	int f5c;
	char pad60[0x6c - 0x60];
	int f6c;
	char pad70[0x84 - 0x70];
	int f84;
	char pad88[0x1d0 - 0x88];
	int f1d0;
	char pad1d4[0x1f0 - 0x1d4];
	int f1f0;
	char pad1f4[0x2f4 - 0x1f4];
} Ent;

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;
extern char g_6b5c60[];

int __cdecl fcn_0046f740(int x, int y, int kind, int owner);
int __cdecl fcn_0046fac0(int x, int y, char* name, int owner);

int __cdecl fcn_00533f40(int x, int y, int owner, int other, int arg5, int* id2, int* id1, int* id3)
{
	Slot* s;

	s = &((Slot*)g_1015f40)[other];
	*id1 = fcn_0046f740(x, y, 3, owner);
	((Slot*)g_1015f40)[owner].h0 = *id1;
	((Ent*)g_1015ea0)[*id1].f5c = 1;
	((Ent*)g_1015ea0)[*id1].f1d0 = 3;
	*id2 = fcn_0046f740(x, y + 0x2a, 4, owner);
	((Slot*)g_1015f40)[owner].h1 = *id2;
	((Ent*)g_1015ea0)[*id2].f5c = 1;
	((Ent*)g_1015ea0)[*id2].f1d0 = 3;
	((Ent*)g_1015ea0)[*id2].f1f0 = other;
	((Ent*)g_1015ea0)[*id1].f1f0 = other;
	*id3 = fcn_0046fac0(x - 0x13, y + 0x19, g_6b5c60, owner);
	((Slot*)g_1015f40)[owner].h2 = *id3;
	((Ent*)g_1015ea0)[*id3].f84 = 0x54;
	((Ent*)g_1015ea0)[*id3].f6c = 1;
	((Ent*)g_1015ea0)[*id3].f18 = 0x30;
	s->f258 = 0;
	s->f274 = arg5;
	return 1;
}
