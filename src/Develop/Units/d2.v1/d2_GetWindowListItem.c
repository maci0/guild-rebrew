#include "Develop/Units/d2.v1/gold_gui.h"
#include "Develop/Units/d2.v1/gold_window.h"
#include "Develop/Units/d2.v1/d2_window_view.h"
#include "Develop/client_types.h"

typedef D2_FORM_RECORD Obj;
// SIZE 0x2bc

extern GuiObj g_00fb1020[];
extern GOLD_GUI_WINDOW g_00f8f120[];
extern D2_FORM_RECORD d2_Forms[];

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x00475b70 */
int __cdecl d2_GetWindowListItem(int group, int item, int index)
{
	GOLD_GUI_WINDOW* p;

	if (group != -1) {
		p = &g_00f8f120[g_00fb1020[group].wins[item]];
	} else {
		p = &g_00f8f120[item];
	}
	if (index > p->count)
		return -1;
	return p->list[index];
}
#else
/* ADDRESS: GOLDTL 0x00472250 */
int __cdecl d2_GetWindowListItem(int k, int i, int j)
{
	D2_WIN* w;

	if (k != -1) {
		w = &((D2_WIN*)d2_Windows)[d2_Forms[k].wins[i]];
	} else {
		w = &((D2_WIN*)d2_Windows)[i];
	}
	if (j > w->count) {
		return -1;
	}
	return w->children[j];
}
#endif
