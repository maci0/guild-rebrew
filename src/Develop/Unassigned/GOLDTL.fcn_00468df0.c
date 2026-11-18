#include "Develop/Units/d2.v1/d2_window_view.h"


int __cdecl fcn_00468cf0(int x, int y, int a3, int a4);
void __cdecl fcn_00465eb0(int r, int i);

/* ADDRESS: GOLDTL 0x00468df0 */
int __cdecl fcn_00468df0(int offsetX, int offsetY, int a3, int a4, int i)
{
	int r;

	r = fcn_00468cf0(((D2_WIN*)g_1015f40)[i].left + offsetX, ((D2_WIN*)g_1015f40)[i].top + offsetY, a3, a4);
	fcn_00465eb0(r, i);
	return r;
}
