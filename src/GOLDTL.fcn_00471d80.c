#include "client_types.h"
typedef Obj_1038140 Obj;
// SIZE 0x2bc

extern Obj_1038140 g_1038140[];

void __cdecl fcn_00471c80(int win, int flags);

// FUNCTION: GOLDTL 0x471d80
// SIZE: 35
void __cdecl fcn_00471d80(int k, int flags)
{
	fcn_00471c80(g_1038140[k].wins[0], flags);
}
