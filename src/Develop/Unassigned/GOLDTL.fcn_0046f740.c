#include "Develop/Units/d2.v1/d2_win.h"

// SIZE 0x3cc

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char s_67d420[];

#include "Develop/Units/Error/error_message.h"
int __cdecl d2_CreateElement(int x, int y, int a3);
void __cdecl d2_AddWindowChild(int id, int win);

/* ADDRESS: GOLDTL 0x0046f740 */
int __cdecl d2_AddElementToWindow(int x, int y, int a3, int win)
{
	D2_WIN* w;
	int id;

	w = &((D2_WIN*)g_1015f40)[win];
	if (!w->active) {
		return -1;
	}
	if (w->count >= 0x180) {
		ReportClientMessage(s_67d420);
		return -1;
	}
	w->children[w->count] = d2_CreateElement(w->left - (*(int*) &w->pad3c[0x22c]) + x, w->top - (*(int*) &w->pad3c[0x21c]) + y, a3);
	id = w->children[w->count];
	if (id != -1) {
		d2_AddWindowChild(id, win);
	}
	return id;
}
