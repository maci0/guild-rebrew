#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];

int __cdecl fcn_00468cf0(int x, int y, int a3, int a4);
void __cdecl fcn_00465eb0(int r, int i);

// FUNCTION: GOLDTL 0x468df0
int __cdecl fcn_00468df0(int a1, int a2, int a3, int a4, int i)
{
	int r;

	r = fcn_00468cf0(*(int*) (((char*)g_1015f40) + i * 0x3cc + 4) + a1, *(int*) (((char*)g_1015f40) + i * 0x3cc + 8) + a2, a3, a4);
	fcn_00465eb0(r, i);
	return r;
}
