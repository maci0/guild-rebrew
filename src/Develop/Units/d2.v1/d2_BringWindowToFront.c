#include <string.h>

#include "Develop/Units/d2.v1/gold_gui.h"
#include "Develop/Units/d2.v1/gold_window.h"
#include "Develop/Units/d2.v1/d2_win.h"
#include "client_types.h"

typedef struct
{
	int id;
	char pad04[0x40 - 0x4];
	struct D2_WIN* parent;
	char pad44[0x2f4 - 0x44];
} D2_ZORDER_ELEMENT;

extern GOLD_GUI_WINDOW g_00f8f120[];
extern GuiEnt** g_006ed964;
extern Win_1015f40 g_1015f40[0x60];
extern void** g_772540;

void __cdecl d2_ReorderControlStack(int id);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x00472fc0 */
void __cdecl d2_BringWindowToFront(int win)
{
	GOLD_GUI_WINDOW* w;
	GuiEnt* tmp[0x181];
	int i;
	int first;
	int last;
	int n;

	first = -1;
	last = -1;
	w = &g_00f8f120[win];
	for (i = 0x2ff; i >= 0; i--) {
		if (g_006ed964[i] != 0 && g_006ed964[i]->id == w->id) {
			last = i;
			break;
		}
		if (g_006ed964[i] != 0 && g_006ed964[i]->parent == (void*) w && first == -1) {
			first = i;
		}
	}
	if (first == -1) {
		first = last;
	}
	n = (first - last) * 4 + 4;
	memcpy(tmp, &g_006ed964[last], n);
	memmove(&g_006ed964[last], &g_006ed964[first + 1], 0xbf8 - first * 4);
	for (i = 0x2ff; i >= 0; i--) {
		if (g_006ed964[i] != 0) {
			break;
		}
	}
	memcpy(&g_006ed964[i + 1], tmp, n);
	for (i = 0; i < w->count; i++) {
		d2_ReorderControlStack(w->list[i]);
	}
}
#else
/* ADDRESS: GOLDTL 0x0046f540 */
void __cdecl d2_BringWindowToFront(int win)
{
	D2_WIN* w;
	D2_ZORDER_ELEMENT* tmp[0x181];
	int i;
	int first;
	int last;
	int n;

	first = -1;
	last = -1;
	w = &((D2_WIN*)g_1015f40)[win];
	for (i = 0x3ff; i >= 0; i--) {
		if (((D2_ZORDER_ELEMENT**)g_772540)[i] != 0 && ((D2_ZORDER_ELEMENT**)g_772540)[i]->id == w->slot) {
			last = i;
			break;
		}
		if (((D2_ZORDER_ELEMENT**)g_772540)[i] != 0 && ((D2_ZORDER_ELEMENT**)g_772540)[i]->parent == w && first == -1) {
			first = i;
		}
	}
	if (first == -1) {
		first = last;
	}
	n = (first - last) * 4 + 4;
	memcpy(tmp, &((D2_ZORDER_ELEMENT**)g_772540)[last], n);
	memmove(&((D2_ZORDER_ELEMENT**)g_772540)[last], &((D2_ZORDER_ELEMENT**)g_772540)[first + 1], 0xff8 - first * 4);
	for (i = 0x3ff; i >= 0; i--) {
		if (((D2_ZORDER_ELEMENT**)g_772540)[i] != 0) {
			break;
		}
	}
	memcpy(&((D2_ZORDER_ELEMENT**)g_772540)[i + 1], tmp, n);
	for (i = 0; i < w->count; i++) {
		d2_ReorderControlStack(w->children[i]);
	}
}
#endif
