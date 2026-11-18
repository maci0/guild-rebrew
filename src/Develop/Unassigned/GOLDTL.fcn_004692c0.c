#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];

int __cdecl fcn_00469140(int x, int y, int a3, int a4, int a5);
void __cdecl fcn_00465eb0(int r, int i);

/* ADDRESS: GOLDTL 0x004692c0 */
int __cdecl fcn_004692c0(int dx, int dy, int a3, int a4, int a5, int i)
{
	int r;

	r = fcn_00469140(*(int*) (((char*)g_1015f40) + i * 0x3cc + 4) + dx, *(int*) (((char*)g_1015f40) + i * 0x3cc + 8) + dy, a3, a4, a5);
	fcn_00465eb0(r, i);
	return r;
}
