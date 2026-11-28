

// SIZE 0x3c4
#include "Develop/Units/d2.v1/gold_window.h"










/* The same array seen from 0xf8f120: the tail stores address it there. */
// SIZE 0x3c4








// SIZE 0x2ec
typedef struct {
	char pad0[0x14];
	short f14;
	char pad16[0x4c - 0x16];
	int f4c;
	char pad50[0x5c - 0x50];
	int f5c;
	char pad60[0x74 - 0x60];
	short f74;
	char pad76[0x1c0 - 0x76];
	int f1c0;
	char pad1c4[0x1e0 - 0x1c4];
	int f1e0;
	char pad1e4[0x2ec - 0x1e4];
} Ent;

#include "Develop/client_types.h"
extern Slot_f8f110 g_f8f110[];

extern char* g_f8f080;
extern char g_631090[];

int __cdecl d2_AddElementToWindow(int x, int y, int kind, int owner);
#include "Develop/Units/d2.v1/d2_gui.h"

int __cdecl d2_AddSpinControl(int x, int y, int owner, int other, int arg5, int* id2, int* id1, int* id3)
{
	GOLD_GUI_WINDOW* s;

	s = &g_f8f120[other];
	*id1 = d2_AddElementToWindow(x, y, 3, owner);
	((GOLD_GUI_WINDOW*) ((char*) g_f8f110 + 0x10))[owner].child[0] = *id1;
	((Ent*)g_f8f080)[*id1].f4c = 1;
	((Ent*)g_f8f080)[*id1].f1c0 = 3;
	*id2 = d2_AddElementToWindow(x, y + 0x2a, 4, owner);
	((GOLD_GUI_WINDOW*) ((char*) g_f8f110 + 0x10))[owner].child[1] = *id2;
	((Ent*)g_f8f080)[*id2].f4c = 1;
	((Ent*)g_f8f080)[*id2].f1c0 = 3;
	((Ent*)g_f8f080)[*id2].f1e0 = other;
	((Ent*)g_f8f080)[*id1].f1e0 = other;
	*id3 = d2_ShowTxt(x - 0x13, y + 0x19, g_631090, owner);
	((GOLD_GUI_WINDOW*) ((char*) g_f8f110 + 0x10))[owner].child[2] = *id3;
	((Ent*)g_f8f080)[*id3].f74 = 0x54;
	((Ent*)g_f8f080)[*id3].f5c = 1;
	((Ent*)g_f8f080)[*id3].f14 = 0x30;
	s->scroll = 0;
	s->step = arg5;
	return 1;
}
