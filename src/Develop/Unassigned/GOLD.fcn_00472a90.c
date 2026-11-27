#include "gold_gui.h"
#include "Develop/Units/d2.v1/gold_window.h"
extern GOLD_GUI_WINDOW g_00f8f120[];
extern GuiEnt* g_00f8f080;
int __cdecl d2_CreateGuiWindow(int x, int y, int width, int height, unsigned int flags);
void __cdecl fcn_004730d0(int, GuiWin*);
void __cdecl d2_GetWindowBorderSize(void* context, int* out_v, int* out_h);

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
	fcn_004730d0(g_00f8f120[idx].id, (void*) p);
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
