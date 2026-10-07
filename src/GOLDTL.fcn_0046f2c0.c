typedef struct Win {
	int pad0;
	int left;
	int x;
	short h;
	short pad0e;
	int margin;
	unsigned char flags;
	char pad15[0x28 - 0x15];
	int* children;
	int count;
	char pad30[0x3c - 0x30];
	char* text;
	char pad40[0x254 - 0x40];
	int view;
	int base;
	int sel;
	int off;
	int pos;
	int scroll;
	char pad26c[0x290 - 0x26c];
	int used;
	char pad294[0x3a0 - 0x294];
	void* tex;
	float alpha;
	char pad3a8[0x3b8 - 0x3a8];
	int hot[3];
	char pad3c4[0x3cc - 0x3c4];
} Win;
// SIZE 0x3cc

typedef struct Slot {
	char pad0[0x20];
	int type;
	char pad24[0x2f4 - 0x24];
} Slot;
// SIZE 0x2f4

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;

void __cdecl fcn_0046b2b0(int slot);

// FUNCTION: GOLDTL 0x46f2c0
int __cdecl fcn_0046f2c0(int win, int keep)
{
	int i;

	if (win > 0x60) {
		return 0;
	}
	if (!((Win*)g_1015f40)[win].used) {
		return 0;
	}
	for (i = ((Win*)g_1015f40)[win].count - 1; i >= 0; i--) {
		if (((Win*)g_1015f40)[win].children[i] == ((Win*)g_1015f40)[win].hot[0]) {
			((Win*)g_1015f40)[win].hot[0] = -1;
		} else if (((Win*)g_1015f40)[win].children[i] == ((Win*)g_1015f40)[win].hot[1]) {
			((Win*)g_1015f40)[win].hot[1] = -1;
		} else if (((Win*)g_1015f40)[win].children[i] == ((Win*)g_1015f40)[win].hot[2]) {
			((Win*)g_1015f40)[win].hot[2] = -1;
		}
		if (((Slot*)g_1015ea0)[((Win*)g_1015f40)[win].children[i]].type != 0x40 || keep) {
			fcn_0046b2b0(((Win*)g_1015f40)[win].children[i]);
		}
	}
	if (((Win*)g_1015f40)[win].text) {
		((Win*)g_1015f40)[win].text[0] = 0;
	}
	((Win*)g_1015f40)[win].sel = -1;
	((Win*)g_1015f40)[win].base = 0;
	((Win*)g_1015f40)[win].view = 0;
	return 1;
}
