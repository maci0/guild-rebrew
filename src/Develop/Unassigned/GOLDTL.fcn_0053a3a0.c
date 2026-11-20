extern char* g_1015ea0;


int __cdecl fcn_00468df0(int, int, int, int, int);
void __cdecl fcn_00469110(int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl fcn_0053a3a0(int a1, int a2, int a3)
{
	int id;

	id = fcn_00468df0(0x20, a1 * 0x2b + 0xa, 0xbf, a2, a3);
	((D2_CONTROL_TL*) ((char*) g_1015ea0))[id].value_06c = 1;
	fcn_00469110(id, 0x12c);
	return id;
}
