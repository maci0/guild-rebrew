#include "Develop/Units/d2.v1/d2_gui.h"
#include "Develop/Units/d2.v1/gold_window.h"

extern GOLD_GUI_WINDOW g_1015f40[0x60];

/* ADDRESS: GOLD 0x0046cd90 */
void __cdecl fcn_0046cd90(short x, short y, int id)
{
	int kind;
	GuiEnt* rec;
	GuiWin* box;
	int h;
	GOLD_GUI_WINDOW* win;
	int old_x;
	int old_y;
	int i;
	int child;

	rec = &g_00f8f080[id];
	kind = rec->kind;
	rec->x = x;
	rec->y = y;
	*((char*) rec + 0x6c) = 8;
	*((char*) rec + 0x6d) = 8;
	if (kind != 0x40) {
		rec->f22 = 0;
		rec->f24 = g_00fb9070;
		rec->f1e = 0;
		rec->f20 = g_00fb9072;
	} else {
		rec->f22 = y;
		rec->f24 = rec->f16 + y;
		rec->f1e = x;
		rec->f20 = rec->w + x;
	}
	box = rec->parent;
	if (box != 0) {
		rec->f22 = box->y > rec->f22 ? box->y : rec->f22;
		h = box->height + box->y;
		rec->f24 = h < rec->f24 ? h : rec->f24;
		rec->f24 = rec->f24 < g_00fb9070 ? rec->f24 : g_00fb9070;
		rec->f1e = box->x > rec->f1e ? box->x : rec->f1e;
		rec->f20 = (box->x + box->width) < rec->f20 ? (box->x + box->width) : rec->f20;
		rec->f20 = rec->f20 < g_00fb9072 ? rec->f20 : g_00fb9072;
	}
	switch (kind) {
	case 4:
		*(short*) (0xf8a52d + rec->bild_offset * 17) = x;
		*(short*) (0xf8a52f + rec->bild_offset * 17) = rec->y;
		return;
	case 0x40:
		win = &g_1015f40[rec->bild_offset];
		old_x = win->x;
		old_y = win->y;
		win->y = y;
		win->x = x;
		if (rec->f20 > g_00fb9072) {
			rec->f20 = g_00fb9072;
		}
		if (rec->f24 > g_00fb9070) {
			rec->f24 = g_00fb9070;
		}
		for (i = 0; i < win->count; i++) {
			child = win->list[i];
			fcn_0046cd90(
				(short) (g_00f8f080[child].x - old_x + win->x),
				(short) (g_00f8f080[child].y - old_y + win->y),
				child);
		}
		return;
	case 0x41:
		*(int*) (0xfa6024 + rec->bild_offset * 0x160) = x;
		*(int*) (0xfa6028 + rec->bild_offset * 0x160) = rec->y;
		break;
	}
}
