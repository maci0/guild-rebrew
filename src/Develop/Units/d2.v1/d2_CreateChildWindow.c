#include "Develop/Units/d2.v1/gold_gui.h"
#include "Develop/Units/d2.v1/gold_window.h"
#include "Develop/client_types.h"
#include "Develop/Units/d2.v1/d2_gui.h"

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

extern GOLD_GUI_WINDOW g_00f8f120[];
extern GuiEnt* g_00f8f080;
extern Win_1015f40 d2_Windows[0x60];

int __cdecl d2_CreateGuiWindow(int x, int y, int width, int height, unsigned int flags);
void __cdecl d2_ReorderControlInWindow(int, GuiWin*);
void __cdecl d2_GetWindowBorderSize(void* context, int* out_v, int* out_h);
int __cdecl d2_CreateWindow(int x, int y, int w, int h, int a5);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x00472a90 */
int __cdecl d2_CreateChildWindow(short x, short y, short width, short height, unsigned int flags, int parent)
{
	GOLD_GUI_WINDOW* p;
	int idx;

	p = &g_00f8f120[parent];
	if (p->active == 0) {
		return -1;
	}
	idx = d2_CreateGuiWindow(p->x - *(int*) ((char*) p + 0x258) + x,
		p->y - *(int*) ((char*) p + 0x248) + y, width, height, flags);
	d2_ReorderControlInWindow(g_00f8f120[idx].id, (void*) p);
	p->list[p->count] = g_00f8f120[idx].id;
	g_00f8f080[g_00f8f120[idx].id].parent = (void*) p;
	g_00f8f080[g_00f8f120[idx].id].f22 = p->y + y;
	g_00f8f080[g_00f8f120[idx].id].f24 = y + height + p->y;
	g_00f8f080[g_00f8f120[idx].id].f1e = p->x + x;
	g_00f8f080[g_00f8f120[idx].id].f20 = p->x + x + width;
	g_00f8f080[g_00f8f120[idx].id].f40 = g_00f8f080[*(int*) ((char*) p + 0x26c)].f40;
	p->count++;
	d2_GetWindowBorderSize(p, (int*) &parent, (int*) &flags);
	if (g_00f8f120[idx].height + y > *(int*) ((char*) p + 0x244)) {
		*(int*) ((char*) p + 0x244) = g_00f8f120[idx].height + parent * 2 + y;
	}
	return idx;
}
#else
/* ADDRESS: GOLDTL 0x0046f100 */
/* ADDRESS: GOLDDE 0x00462690 */
int __cdecl d2_CreateChildWindow(int x, int y, int cx, int cy, int flags, int win)
{
	D2_CHILD_WIN* w;
	int id;

	w = &((D2_CHILD_WIN*)d2_Windows)[win];
	if (w->i[0x290 / 4] == 0) {
		return -1;
	}
	id = d2_CreateWindow(w->i[0x4 / 4] - w->i[0x268 / 4] + x, w->i[0x8 / 4] - w->i[0x258 / 4] + y, cx, cy, flags);
	((int*) w->i[0x28 / 4])[w->i[0x2c / 4]] = ((D2_CHILD_WIN*)d2_Windows)[id].i[0x27c / 4];
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[((D2_CHILD_WIN*)d2_Windows)[id].i[0x27c / 4]].parent) = (int) w;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[((D2_CHILD_WIN*)d2_Windows)[id].i[0x27c / 4]].clip_top) = w->i[0x8 / 4] + y;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[((D2_CHILD_WIN*)d2_Windows)[id].i[0x27c / 4]].clip_bottom) = w->i[0x8 / 4] + y + cy;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[((D2_CHILD_WIN*)d2_Windows)[id].i[0x27c / 4]].clip_left) = w->i[0x4 / 4] + x;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[((D2_CHILD_WIN*)d2_Windows)[id].i[0x27c / 4]].clip_right) = w->i[0x4 / 4] + x + cx;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[((D2_CHILD_WIN*)d2_Windows)[id].i[0x27c / 4]].value_050) = (*(int*)&((D2_CONTROL_TL*)d2_Controls)[w->i[0x27c / 4]].value_050);
	w->i[0x2c / 4]++;
	if (y + ((D2_CHILD_WIN*)d2_Windows)[id].i[0x10 / 4] > w->i[0x254 / 4]) {
		w->i[0x254 / 4] = y + ((D2_CHILD_WIN*)d2_Windows)[id].i[0x10 / 4];
	}
	return id;
}
#endif
