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

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char s_67d420[];

#include "Develop/Units/Error/error_message.h"
int __cdecl fcn_00469c30(int x, int y, int a3);
void __cdecl fcn_00465eb0(int id, int win);

/* ADDRESS: GOLDTL 0x0046f740 */
int __cdecl fcn_0046f740(int x, int y, int a3, int win)
{
	Win* w;
	int id;

	w = &((Win*)g_1015f40)[win];
	if (!w->used) {
		return -1;
	}
	if (w->count >= 0x180) {
		ReportClientMessage(s_67d420);
		return -1;
	}
	w->children[w->count] = fcn_00469c30(w->left - w->scroll + x, w->x - w->base + y, a3);
	id = w->children[w->count];
	if (id != -1) {
		fcn_00465eb0(id, win);
	}
	return id;
}
