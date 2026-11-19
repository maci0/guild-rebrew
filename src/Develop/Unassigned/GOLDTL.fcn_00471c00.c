
// One call after both if/else pairs: msvc6 duplicates the call tail into
// each arm of the second test, as the reference does.

#include "Develop/Units/d2.v1/d2_window_view.h"








// SIZE 0x3cc

#include "client_types.h"

#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl fcn_00469c40(int x, int y, int slot);

void __cdecl fcn_00471c00(int k, unsigned char center)
{
	D2_WIN* w;
	int x;
	int y;

	w = &((D2_WIN*)g_1015f40)[k];
	if (center & 1) {
		x = d2_CenterX - w->width / 2;
	} else {
		x = w->left;
	}
	if (center & 2) {
		y = d2_DialogCenterY - w->height / 2;
	} else {
		y = w->top;
	}
	fcn_00469c40(x, y, w->slot);
}
