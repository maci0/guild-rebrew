// FUNCTION: GOLDTL 0x471c00
// SIZE: 128
// One call after both if/else pairs: msvc6 duplicates the call tail into
// each arm of the second test, as the reference does.

typedef struct Win0471c00 {
	int pad0;
	int left;
	int top;
	int width;
	int height;
	char pad14[0x27c - 0x14];
	int slot;
	char pad280[0x3cc - 0x280];
} Win0471c00;
// SIZE 0x3cc

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern int g_1015ea8;
extern int g_1015eac;

void __cdecl fcn_00469c40(int x, int y, int slot);

void __cdecl fcn_00471c00(int k, unsigned char center)
{
	Win0471c00* w;
	int x;
	int y;

	w = &((Win0471c00*)g_1015f40)[k];
	if (center & 1) {
		x = g_1015eac - w->width / 2;
	} else {
		x = w->left;
	}
	if (center & 2) {
		y = g_1015ea8 - w->height / 2;
	} else {
		y = w->top;
	}
	fcn_00469c40(x, y, w->slot);
}
