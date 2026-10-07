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
	char pad0[0x4c];
	int hidden;
	char pad50[0x2f4 - 0x50];
} Slot;
// SIZE 0x2f4

#include "client_types.h"
extern Obj_1038140 g_1038140[];
extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;

// FUNCTION: GOLDTL 0x471a30
void __cdecl fcn_00471a30(int k, int flag)
{
	Obj* o;
	Win* w;
	int i;
	int j;

	o = &((Obj*)g_1038140)[k];
	if (o->used) {
		for (i = 0; i < o->count; i++) {
			w = &((Win*)g_1015f40)[o->wins[i]];
			for (j = 0; j < w->count; j++) {
				((Slot*)g_1015ea0)[w->children[j]].hidden = (flag == 0);
			}
		}
		o->shown = flag;
	}
}
