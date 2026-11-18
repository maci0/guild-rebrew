#include "Develop/Units/d2.v1/d2_window_view.h"


int __cdecl fcn_00469140(int x, int y, int a3, int a4, int a5);
void __cdecl fcn_00465eb0(int r, int i);

/* ADDRESS: GOLDTL 0x004692c0 */
int __cdecl fcn_004692c0(int dx, int dy, int a3, int a4, int a5, int i)
{
	int r;

	r = fcn_00469140(((D2_WIN*)g_1015f40)[i].left + dx, ((D2_WIN*)g_1015f40)[i].top + dy, a3, a4, a5);
	fcn_00465eb0(r, i);
	return r;
}
