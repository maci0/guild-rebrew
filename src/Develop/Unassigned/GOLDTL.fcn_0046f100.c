typedef struct
{
	int i[0x3cc / 4];
} D2_CHILD_WIN;
// SIZE 0x3cc

typedef struct
{
	int i[0x2f4 / 4];
} D2_CHILD_WIN_ENT;
// SIZE 0x2f4

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
#include "Develop/Units/d2.v1/d2_gui.h"

int __cdecl d2_CreateWindow(int x, int y, int w, int h, int a5);

/* ADDRESS: GOLDTL 0x0046f100 */
int __cdecl d2_CreateChildWindow(int x, int y, int cx, int cy, int flags, int win)
{
	D2_CHILD_WIN* w;
	int id;

	w = &((D2_CHILD_WIN*)g_1015f40)[win];
	if (w->i[0x290 / 4] == 0) {
		return -1;
	}
	id = d2_CreateWindow(w->i[0x4 / 4] - w->i[0x268 / 4] + x, w->i[0x8 / 4] - w->i[0x258 / 4] + y, cx, cy, flags);
	((int*) w->i[0x28 / 4])[w->i[0x2c / 4]] = ((D2_CHILD_WIN*)g_1015f40)[id].i[0x27c / 4];
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[((D2_CHILD_WIN*)g_1015f40)[id].i[0x27c / 4]].parent) = (int) w;
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[((D2_CHILD_WIN*)g_1015f40)[id].i[0x27c / 4]].clip_top) = w->i[0x8 / 4] + y;
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[((D2_CHILD_WIN*)g_1015f40)[id].i[0x27c / 4]].clip_bottom) = w->i[0x8 / 4] + y + cy;
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[((D2_CHILD_WIN*)g_1015f40)[id].i[0x27c / 4]].clip_left) = w->i[0x4 / 4] + x;
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[((D2_CHILD_WIN*)g_1015f40)[id].i[0x27c / 4]].clip_right) = w->i[0x4 / 4] + x + cx;
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[((D2_CHILD_WIN*)g_1015f40)[id].i[0x27c / 4]].value_050) = (*(int*)&((D2_CONTROL_TL*)g_1015ea0)[w->i[0x27c / 4]].value_050);
	w->i[0x2c / 4]++;
	if (y + ((D2_CHILD_WIN*)g_1015f40)[id].i[0x10 / 4] > w->i[0x254 / 4]) {
		w->i[0x254 / 4] = y + ((D2_CHILD_WIN*)g_1015f40)[id].i[0x10 / 4];
	}
	return id;
}
