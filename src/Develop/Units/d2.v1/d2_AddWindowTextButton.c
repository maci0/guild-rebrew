#include "Develop/Units/d2.v1/d2_window_view.h"


int __cdecl d2_CreateTextButton(int x, int y, int a3, int a4);
void __cdecl d2_AddWindowChild(int r, int i);

/* ADDRESS: GOLDTL 0x00468df0 */
int __cdecl d2_AddWindowTextButton(int offsetX, int offsetY, int resourceId, int text, int win)
{
	int r;

	r = d2_CreateTextButton(((D2_WIN*)d2_Windows)[win].left + offsetX, ((D2_WIN*)d2_Windows)[win].top + offsetY, resourceId, text);
	d2_AddWindowChild(r, win);
	return r;
}
