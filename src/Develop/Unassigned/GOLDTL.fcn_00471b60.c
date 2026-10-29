typedef struct Win {
	int pad0;
	int left;
	int top;
	int width;
	int height;
	char pad14[0x28 - 0x14];
	int* children;
	int count;
	char pad30[0x27c - 0x30];
	int slot;
	char pad280[0x3cc - 0x280];
} Win;
// SIZE 0x3cc
typedef struct Obj {
	int pad0;
	int wins[0x60];
	int count;
	char pad188[0x190 - 0x188];
	int used;
	char pad194[0x19c - 0x194];
	int shown;
	int active;
	char pad1a4[0x2bc - 0x1a4];
} Obj;
// SIZE 0x2bc

typedef struct Slot {
	char pad0[0x40];
	void* link;
	char pad44[0x2f4 - 0x44];
} Slot;
// SIZE 0x2f4

#include "client_types.h"
extern Obj_1038140 g_1038140[];
extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;
extern int g_1015ea8;
extern int g_1015eac;

void __cdecl fcn_00469c40(int x, int y, int slot);

/* ADDRESS: GOLDTL 0x00471b60 */
void __cdecl fcn_00471b60(int k)
{
	Obj* o;
	Win* w;
	int i;

	o = &((Obj*)g_1038140)[k];
	for (i = 0; i < o->count; i++) {
		w = &((Win*)g_1015f40)[o->wins[i]];
		if (((Slot*)g_1015ea0)[w->slot].link == 0) {
			fcn_00469c40(g_1015eac - w->width / 2, g_1015ea8 - w->height / 2, w->slot);
		}
	}
}
