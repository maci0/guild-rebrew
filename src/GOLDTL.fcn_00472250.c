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
#include "client_types.h"
typedef Obj_1038140 Obj;
// SIZE 0x2bc

extern Win_1015f40 g_1015f40[0x60];
extern Obj_1038140 g_1038140[];

// FUNCTION: GOLDTL 0x472250
int __cdecl fcn_00472250(int k, int i, int j)
{
	Win* w;

	if (k != -1) {
		w = &((Win*)g_1015f40)[g_1038140[k].wins[i]];
	} else {
		w = &((Win*)g_1015f40)[i];
	}
	if (j > w->count) {
		return -1;
	}
	return w->children[j];
}
