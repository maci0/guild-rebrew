

// SIZE 0x3cc
#include "Develop/Units/d2.v1/d2_win.h"












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
#include "Develop/Units/d2.v1/d2_gui.h"

int __cdecl fcn_00533f40(int x, int y, int owner, int other, int arg5, int* id2, int* id1, int* id3)
{
	D2_WIN* s;

	s = &((D2_WIN*)g_1015f40)[other];
	*id1 = fcn_0046f740(x, y, 3, owner);
	*(int*) &((D2_WIN*)g_1015f40)[owner].pad3a8[0x10] = *id1;
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[*id1].value_05c) = 1;
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[*id1].flags_1d0) = 3;
	*id2 = fcn_0046f740(x, y + 0x2a, 4, owner);
	*(int*) &((D2_WIN*)g_1015f40)[owner].pad3a8[0x14] = *id2;
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[*id2].value_05c) = 1;
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[*id2].flags_1d0) = 3;
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[*id2].value_1f0) = other;
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[*id1].value_1f0) = other;
	*id3 = d2_ShowTxt(x - 0x13, y + 0x19, g_6b5c60, owner);
	*(int*) &((D2_WIN*)g_1015f40)[owner].pad3a8[0x18] = *id3;
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[*id3].font) = 0x54;
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[*id3].value_06c) = 1;
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[*id3].width) = 0x30;
	*(int*) &s->pad3c[0x21c] = 0;
	*(int*) &s->pad3c[0x238] = arg5;
	return 1;
}
