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
	char pad30[0x38 - 0x30];
	int surface;
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

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern int g_772514;
extern char s_67d844[];
extern char s_67d818[];

void __cdecl fcn_0041d9e0(const char* msg);
void __cdecl fcn_004772e0(int a, int b, int c, int d, int e);

// FUNCTION: GOLDTL 0x472ea0
// SIZE: 97
void __cdecl fcn_00472ea0(int a, int b, int c, int d)
{
	Win* w;

	w = &((Win*)g_1015f40)[g_772514];
	if (!w->used) {
		fcn_0041d9e0(s_67d844);
		return;
	}
	if (!w->surface) {
		fcn_0041d9e0(s_67d818);
		return;
	}
	fcn_004772e0(a, b, c, d, w->surface);
}
