

// SIZE 0x3c4
typedef struct {
	char pad0[0x258];
	int f258;
	char pad25c[0x274 - 0x25c];
	int f274;
	char pad278[0x3b8 - 0x278];
	int h0;
	int h1;
	int h2;
} Slot;

/* The same array seen from 0xf8f120: the tail stores address it there. */
// SIZE 0x3c4
typedef struct {
	char pad0[0x248];
	int f248;
	char pad24c[0x264 - 0x24c];
	int f264;
	char pad268[0x3c4 - 0x268];
} SlotTail;

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

#include "client_types.h"
extern Slot_f8f110 g_f8f110[];
extern Win_f8f120 g_f8f120[];
extern char* g_f8f080;
extern char g_631090[];

int __cdecl fcn_004731c0(int x, int y, int kind, int owner);
#include "Develop/Units/d2.v1/d2_gui.h"

int __cdecl fcn_0052e890(int x, int y, int owner, int other, int arg5, int* id2, int* id1, int* id3)
{
	SlotTail* s;

	s = &((SlotTail*)g_f8f120)[other];
	*id1 = fcn_004731c0(x, y, 3, owner);
	((Slot*)g_f8f110)[owner].h0 = *id1;
	((Ent*)g_f8f080)[*id1].f4c = 1;
	((Ent*)g_f8f080)[*id1].f1c0 = 3;
	*id2 = fcn_004731c0(x, y + 0x2a, 4, owner);
	((Slot*)g_f8f110)[owner].h1 = *id2;
	((Ent*)g_f8f080)[*id2].f4c = 1;
	((Ent*)g_f8f080)[*id2].f1c0 = 3;
	((Ent*)g_f8f080)[*id2].f1e0 = other;
	((Ent*)g_f8f080)[*id1].f1e0 = other;
	*id3 = d2_ShowTxt(x - 0x13, y + 0x19, g_631090, owner);
	((Slot*)g_f8f110)[owner].h2 = *id3;
	((Ent*)g_f8f080)[*id3].f74 = 0x54;
	((Ent*)g_f8f080)[*id3].f5c = 1;
	((Ent*)g_f8f080)[*id3].f14 = 0x30;
	s->f248 = 0;
	s->f264 = arg5;
	return 1;
}
