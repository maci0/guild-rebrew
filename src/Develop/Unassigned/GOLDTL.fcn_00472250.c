#include "Develop/Units/d2.v1/d2_window_view.h"












// SIZE 0x3cc
#include "client_types.h"
typedef Obj_1038140 Obj;
// SIZE 0x2bc


extern Obj_1038140 g_1038140[];

/* ADDRESS: GOLDTL 0x00472250 */
int __cdecl fcn_00472250(int k, int i, int j)
{
	D2_WIN* w;

	if (k != -1) {
		w = &((D2_WIN*)g_1015f40)[g_1038140[k].wins[i]];
	} else {
		w = &((D2_WIN*)g_1015f40)[i];
	}
	if (j > w->count) {
		return -1;
	}
	return w->children[j];
}
