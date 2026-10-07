typedef struct Slot {
	int id;
	int used;
	int value;
	char* data;
	int x;
	int y;
	int w;
	int h;
	int type;
	char pad24[0x38 - 0x24];
	int text;
	char pad3c[0x48 - 0x3c];
	int hidden;
	char pad4c[0x58 - 0x4c];
	int dirty;
	char pad5c[0x88 - 0x5c];
	int result;
	char* buf;
	char pad90[0x2f4 - 0x90];
} Slot;
// SIZE 0x2f4
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

extern char* g_1015ea0;
#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];

// FUNCTION: GOLDTL 0x472170
void __cdecl fcn_00472170(int slot, int flag)
{
	Slot* s;
	Win* w;
	int i;

	s = &((Slot*)g_1015ea0)[slot];
	s->hidden = (flag == 0);
	if (s->type == 0x40) {
		w = &((Win*)g_1015f40)[s->result];
		for (i = 0; i < w->count; i++) {
			fcn_00472170(w->children[i], flag);
		}
	}
}
