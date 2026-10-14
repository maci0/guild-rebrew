/* GOLD twin of GOLDTL fcn_00465eb0. GOLD's window and entity records keep
 * their coordinates and the child count as shorts (window 0x3c4 bytes, entity
 * 0x2ec) where GOLDTL uses ints (0x3cc, 0x2f4). */

// SIZE 0x3c4
typedef struct Win_468ce0 {
	int a0;
	short x;
	short y;
	short w;
	short h;
	char pad0c[0x18 - 0xc];
	int* list;
	short count;
	char pad1e[0x244 - 0x1e];
	int bottom;
	char pad248[0x26c - 0x248];
	int parent;
	char pad270[0x280 - 0x270];
	int active;
	char pad284[0x3c4 - 0x284];
} Win_468ce0;

// SIZE 0x2ec
typedef struct Ent_468ce0 {
	char pad0[0x12];
	short f12;
	short pad14;
	short f16;
	char pad18[0x1e - 0x18];
	short left;
	short right;
	short top;
	short bottom;
	char pad26[0x30 - 0x26];
	Win_468ce0* win;
	int pad34;
	int f38;
	int pad3c;
	int f40;
	char pad44[0x2ec - 0x44];
} Ent_468ce0;

#include "client_types.h"
extern Win_f8f120 g_f8f120[];
extern char* g_f8f080;
extern char s_5fe7ac[];

void __cdecl fcn_004222b0(const char* msg);
void __cdecl fcn_004730d0(int slot, Win_468ce0* parent);

/* ADDRESS: GOLD 0x00468ce0 */
int __cdecl fcn_00468ce0(int id, int win)
{
	Win_468ce0* w;
	int bottom;

	if (win < 0 || win > 0x60) {
		return 0;
	}
	w = &((Win_468ce0*)g_f8f120)[win];
	if (w->active == 0) {
		return 0;
	}
	if (w->count >= 0x180) {
		fcn_004222b0(s_5fe7ac);
		return 0;
	}
	fcn_004730d0(id, w);
	((Ent_468ce0*)g_f8f080)[id].win = w;
	((Ent_468ce0*)g_f8f080)[id].f40 = ((Ent_468ce0*)g_f8f080)[w->parent].f40;
	((Ent_468ce0*)g_f8f080)[id].top = w->y;
	((Ent_468ce0*)g_f8f080)[id].bottom = w->h + w->y;
	((Ent_468ce0*)g_f8f080)[id].left = w->x;
	((Ent_468ce0*)g_f8f080)[id].right = w->w + w->x;
	((Ent_468ce0*)g_f8f080)[id].f38 = ((Ent_468ce0*)g_f8f080)[w->parent].f38;
	bottom = ((Ent_468ce0*)g_f8f080)[id].f16 + ((Ent_468ce0*)g_f8f080)[id].f12 - w->y;
	if (bottom > w->bottom) {
		w->bottom = bottom + 4;
	}
	w->list[w->count] = id;
	w->count++;
	return 1;
}
