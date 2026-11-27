#include "Develop/Units/d2.v1/d2_window_view.h"


int __cdecl d2_CreateTextButton(int x, int y, int a3, int a4);
void __cdecl d2_AddWindowChild(int r, int i);

/* ADDRESS: GOLDTL 0x00468df0 */
int __cdecl d2_AddWindowTextButton(int offsetX, int offsetY, int a3, int a4, int i)
{
	int r;

	r = d2_CreateTextButton(((D2_WIN*)g_1015f40)[i].left + offsetX, ((D2_WIN*)g_1015f40)[i].top + offsetY, a3, a4);
	d2_AddWindowChild(r, i);
	return r;
}
