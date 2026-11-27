

typedef struct D2_SCROLL_WINDOW {
	char pad0[0x10];
	int height;
	char pad14[0x254 - 0x14];
	int limit;
	int base;
	int pad25c;
	int scroll;
	int total;
	char pad268[0x3cc - 0x268];
} D2_SCROLL_WINDOW;
// SIZE 0x3cc

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];

void __cdecl d2_ScrollWindow(int delta, int step, int k)
{
	int scroll;
	int base;
	int sum;
	int v;

	scroll = *(int*)&((D2_SCROLL_WINDOW*)g_1015f40)[k].scroll;
	base = ((D2_SCROLL_WINDOW*)g_1015f40)[k].base;
	sum = base + scroll;
	if (sum > 0 && step < 0) {
		v = -sum;
		if (step > v) {
			v = step;
		}
		((D2_SCROLL_WINDOW*)g_1015f40)[k].scroll = v;
	} else if (sum + ((D2_SCROLL_WINDOW*)g_1015f40)[k].height < ((D2_SCROLL_WINDOW*)g_1015f40)[k].limit && step > 0) {
		v = ((D2_SCROLL_WINDOW*)g_1015f40)[k].limit - ((D2_SCROLL_WINDOW*)g_1015f40)[k].height - base - scroll;
		if (step < v) {
			v = step;
		}
		((D2_SCROLL_WINDOW*)g_1015f40)[k].scroll += v;
	}
	((D2_SCROLL_WINDOW*)g_1015f40)[k].total += delta;
}
