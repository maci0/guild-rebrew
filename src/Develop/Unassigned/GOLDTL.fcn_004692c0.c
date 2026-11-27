#include "Develop/Units/d2.v1/d2_window_view.h"


int __cdecl d2_CreateBitmapElement(int x, int y, int a3, int a4, int a5);
void __cdecl d2_AddWindowChild(int r, int i);

/* ADDRESS: GOLDTL 0x004692c0 */
int __cdecl d2_AddWindowBitmapElement(int dx, int dy, int a3, int a4, int a5, int i)
{
	int r;

	r = d2_CreateBitmapElement(((D2_WIN*)g_1015f40)[i].left + dx, ((D2_WIN*)g_1015f40)[i].top + dy, a3, a4, a5);
	d2_AddWindowChild(r, i);
	return r;
}
